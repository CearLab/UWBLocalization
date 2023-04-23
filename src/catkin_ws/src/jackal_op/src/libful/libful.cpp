#include "libful.h"

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors){

    _begin = ros::Time::now();

    // set name
    _name = name;

    // set mesh dimension
    _Nanchors = Nanchors;
    
    // counter
    _cnt = 0;

    // init J, GJ, HJ
    _G.J = 0;
    for (int i=0; i<3; i++) {
        _G.GJ.push_back(0.0);
    }
    for (int i=0; i<9; i++) {
        _G.HJ.push_back(0.0);
    }

    // init p
    _p = {0.0, 0.0, 0.25};

    
    // init distance vectors
    for (int i=0; i<_Nanchors; i++) {

        // init distances
        _DT1.push_back(0.0);
        _DT2.push_back(0.0);
        _DT3.push_back(0.0);
        _DT.D1.push_back(0.0);
        _DT.D2.push_back(0.0);
        _DT.D3.push_back(0.0);

        // init Anchors position
        for (int j=0; j<3; j++){
            _A.push_back(0.0);
        }
    }

    ROS_INFO("Consructor: ok");

}

/** **** METHODS **** */

// subscriber callback
void jackAPI::ChatterCallbackT(const gtec_msgs::Ranging& msg) {

    std::vector<_Float64> p0(3, 0.0);

    // store distances in the vectors
    if (msg.tagId == 1){
        _DT1[msg.anchorId] = (double)msg.range/1000;
        _DT.D1[msg.anchorId] = _DT1[msg.anchorId];
    }
    else if (msg.tagId == 2){
        _DT2[msg.anchorId] = (double)msg.range/1000;
        _DT.D2[msg.anchorId] = _DT2[msg.anchorId];
    }
    else {
        _DT3[msg.anchorId] = (double)msg.range/1000;
        _DT.D3[msg.anchorId] = _DT3[msg.anchorId];
    }

    //_time
    _DT.header.stamp = _begin.now();

    // publish
    _jack_disthandle_P.publish(_DT);

    ROS_INFO("Published distances");

    // call newton raphson
    _G = NewtonRaphson(p0, _DT3, 20);

    // time
    _G.header.stamp = _begin.now();

    // publish
    _jack_trilateration_P.publish(_G);

    ROS_INFO("Published gradient");

    // DEBUG
    _cnt++;

}

// subscriber callback
void jackAPI::ChatterCallbackA(const visualization_msgs::MarkerArray& msg) {

    // init
    int id = 0;

    // store anchors positions
    for (int i=0;i<_Nanchors;i++){

        id = (i)*3;
        _A[id] = msg.markers[i].pose.position.x;
        _A[id+1] = msg.markers[i].pose.position.y;
        _A[id+2] = msg.markers[i].pose.position.z;

    }

    ROS_INFO("Anchors received");

}

// cost function
_Float64 jackAPI::Ji(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

    // init 
    _Float64 J = 0;

    // compute cost function for single distance
    J = pow(sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2)) - D, 2);

    return J;
}

// cost function - gradient
std::vector<_Float64> jackAPI::GJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

    // init
    std::vector<_Float64> GJ(3, 0.0);
    _Float64 norm = 0.0;

    // compute cost function gradient for single distance on direction k
    norm = sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));
    for (int k=0;k<3;k++){
        GJ[k] = (p[k] - A[k]) * (1 - D/norm);
    }
    
    return GJ;
}

// cost function - hessian
std::vector<_Float64> jackAPI::HJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

    // init
    std::vector<_Float64> HJ(9, 0.0);
    _Float64 norm = 0.0;
    int id;

    // compute cost function gradient for single distance on direction k
    norm = sqrt(pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));
    for (int k=0;k<3;k++){
        for (int r=0;r<3;r++){
            id = 3*k + r;
            if (k == r){
                HJ[id] = (1 - D / norm) + D * pow((p[k] - A[k]),2) / norm;
            }
            else{
                HJ[id] = D * (p[k] - A[k]) * (p[r] - A[r]) / norm;
            }
        }
    }
    
    return HJ;
}

// Newton-Rhapson
jackal_op::GradientDescent jackAPI::NewtonRaphson(std::vector<_Float64> p0, std::vector<_Float64> D, int Niter){
    
    // init cost function 
    _Float64 Jtmp = 0;
    std::vector<_Float64> GJtmp(3, 0.0);
    std::vector<_Float64> HJtmp(9, 0.0);

    _Float64 J = 0;
    std::vector<_Float64> GJ(3, 0.0);
    std::vector<_Float64> HJ(9, 0.0);

    // alglib for matrix inversion
    alglib::real_2d_array HJINV = "[[1,0,0],[0,1,0],[0,0,1]]";
    alglib::real_1d_array GJLIB = "[0,0,0]";
    alglib::ae_int_t info;
    alglib::matinvreport rep;
    alglib::xparams Xparams;

    // stuff to save mid-operations
    std::vector<_Float64> A(3, 0.0);
    alglib::real_1d_array StepVector = "[0,0,0]";
    
    // init index
    int idA = 0;
    int idH = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    int r = 0;
    int iter = 0;

    // initial condition - optional
    for (k=0;k<3;k++){
        _p[k] = p0[k];
    }

    // cycle optimization
    for (iter=0;iter<Niter;iter++){

        // get gradient and hessian
        for (i=0;i<_Nanchors;i++){

            // anchor startpos
            idA = (i)*3;

            // get anchor position
            for (j=0;j<3;j++){
                A[j] = _A[idA+j];
            }

            // compute J, GJ, HJ
            Jtmp = Ji(_p, A, D[i]);
            GJtmp = GJi(_p, A, D[i]);
            HJtmp = HJi(_p, A, D[i]);

            // sum of terms
            J = J + Jtmp;
            for (k=0;k<3;k++){
                GJ[k] = GJ[k] + GJtmp[k];
                for (r=0;r<3;r++){
                    idH = 3*k + r;
                    HJ[idH] = HJ[idH] + HJtmp[idH];
                }
            }
        }

        /*
        * compute Newton-Raphson
        */ 
        // assign HJ to HJINV and GJ to GJLIB
        for (k=0;k<3;k++){
            GJLIB(k) = GJ[k];
            for (r=0;r<3;r++){
                idH = 3*k + r;
                HJINV(k,r) = HJ[idH];
            }
        }
        
        try {

            // compute inverse
            alglib::rmatrixinverse(HJINV, info, rep);   
            // compute step
            alglib::rmatrixmv(3, 3, HJINV, 0, 0, 0, GJLIB, 0, StepVector, 0, Xparams);
            // update _p
            for (k=0;k<3;k++){
                _p[k] = _p[k] - StepVector[k];
                //_p[k] = _p[k] -0.5*GJ[k];
            }     

            ROS_INFO("Newton-Raphson: OK");
        }
        catch(...) {
            ROS_INFO("Newton-Raphson: FAILED");
        }
        
        
    }
    

    // assign to GradientDescent and publish
    _G.J = J;
    _G.GJ = GJ;
    _G.HJ = HJ;
    _G.A = _A;
    _G.p = _p;

    return _G;
    
}