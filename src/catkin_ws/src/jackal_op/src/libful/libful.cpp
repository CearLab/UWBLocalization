// class with utilities for jackal with UWB handling
#include "libful.h"

/* ** LIB FUNCTIONS - NOT IN C LASS** */

// total cost function - armadillo
_Float64 Jtot_arma(const arma::vec& p_arma, arma::vec* grad_out, void* jack){

    // define index and iterators
    int i;
    int j;
    int idA;

    // stuff to save mid-operations
    std::vector<_Float64> A(3, 0.0);     
    jackAPI *Jack;
    
    // define Jtot
    _Float64 Jtot = 0;
    _Float64 Jtmp = 0;   

    // init - gradient
    std::vector<_Float64> GJ(3, 0.0);
    _Float64 norm = 0.0;    

    // define pointer class
    Jack = (jackAPI *)jack; 

    for (i=0;i<Jack->_Nanchors;i++){

        // info
        //ROS_INFO("Distance available: %d: %g", i, Jack->_Dopt[i]);
        //ROS_INFO("Anchor available: %d: %g %g %g", i, Jack->_A[3*i], Jack->_A[3*i+1], Jack->_A[3*i+2]);

        // anchor startpos
        idA = (i)*3;

        // get anchor position
        for (j=0;j<3;j++){
            A[j] = Jack->_A[idA+j];
        }

        // compute Ji and add    
        norm = sqrt( pow((p_arma[0]-A[0]),2) + pow((p_arma[1]-A[1]),2) + pow((p_arma[2]-A[2]),2));    
        Jtmp = pow(norm - Jack->_Dopt[i], 2);
        Jtot = Jtot + Jtmp;

        if (grad_out){

            // compute cost function gradient for single distance on direction j       
            for (j=0;j<3;j++){
                GJ[j] = (p_arma[j] - A[j]) * (1 - Jack->_Dopt[i]/norm);
                grad_out[j] = grad_out[j] + GJ[j];
            }             
        }

    }

    // info
    //ROS_INFO("J: %g", Jtot);
    //ROS_INFO("GJ: %g %g %g", grad_out[0], grad_out[1], grad_out[2]);

    return Jtot;

}

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors, int tagID){

    // init timer
    _begin = ros::Time::now();

    // set name
    _name = name;

    // set tagID
    _tagID = tagID;

    // set gradient flag
    _GradientFlag = 0;

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

        // init distances - class
        _DT.push_back(0.0);        
        _Dopt.push_back(0.0);

        // init MeshUWB message
        _DTmsg.D1.push_back(0.0);
        _DTmsg.D2.push_back(0.0);
        _DTmsg.D3.push_back(0.0);
        _DTmsg.DTrue.push_back(0.0);

        // init Anchors position
        for (int j=0; j<3; j++){
            _A.push_back(0.0);
        }
    }

    //ROS_INFO("Consructor: ok");

}

/** **** METHODS **** */

// subscriber callback - used in the trilateration
void jackAPI::ChatterCallbackT(const gtec_msgs::Ranging& msg) {

    std::vector<_Float64> p0(3, 0.0);

    // store distances in the vectors
    ROS_INFO("AnchorID: %d", msg.anchorId);
    ROS_INFO("TagID: %d", msg.tagId);
    try {

        // save distance read from tag
        _DT[msg.anchorId] = (double)msg.range/1000;

        // populate correct tag in the UWB message
        if (msg.tagId == 0){            
            _DTmsg.D1[msg.anchorId] = _DT[msg.anchorId];            
        }
        else if (msg.tagId == 1){
            _DTmsg.D2[msg.anchorId] = _DT[msg.anchorId];
        }
        else if (msg.tagId == 2){
            _DTmsg.D3[msg.anchorId] = _DT[msg.anchorId];
        }
        else {
            _DTmsg.DTrue[msg.anchorId] = _DT[msg.anchorId];
        }
    }
    catch(...){
        ROS_INFO("WRONG tg ID");
    }

    // set distance used to optimize
    if (msg.tagId == _tagID){
        _Dopt[msg.anchorId] = _DT[msg.anchorId];
    }
        
    //_get time
    _DTmsg.header.stamp = _begin.now();

    // publish the distance wrapper
    _jack_disthandle_P.publish(_DTmsg);

    ROS_INFO("Published distances");

    // call newton raphson
    try {

        //_G = NewtonRaphson(p0, _DTrue, 10);
        _G = OptimMin(p0, _Dopt);

        // get time
        _G.header.stamp = _begin.now();
        _G.odom.header.stamp = _G.header.stamp;
        _Godom.header.stamp = _G.odom.header.stamp;
        _Godom.pose.pose.position.x = _G.odom.pose.pose.position.x;
        _Godom.pose.pose.position.y = _G.odom.pose.pose.position.y;
        _Godom.pose.pose.position.z = _G.odom.pose.pose.position.z;

        // publish
        _jack_trilateration_P.publish(_G);
        _jack_odometry_P.publish(_Godom);

        ROS_INFO("Published gradient");
    }
    catch(...){
        ROS_INFO("Failed gradient");
    }
    
    // DEBUG
    _cnt++;

}

// subscriber callback - used to get the position of the anchors
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

// subscriber callback - used to create synthetic true distances from ptrue
void jackAPI::ChatterCallbackDtrue(const nav_msgs::Odometry& msg){

    // define position
    std::vector<_Float64> ptrue(3,0.0);

    // init general stuff
    int i, idA;

    // init useless fields in MeshUWB
    _DTrueMsg.seq = 0;
    _DTrueMsg.rss = 0;
    _DTrueMsg.errorEstimation = 0;

    // get true distances
    for (i=0;i<_Nanchors;i++){

        // get index
        idA = 3*i;  

        // compute true distance      
        _DT[i] = sqrt( pow((msg.pose.pose.position.x -_A[idA]),2) + 
                          pow((msg.pose.pose.position.y -_A[idA+1]),2) + 
                          pow((msg.pose.pose.position.z -_A[idA+2]),2));

        // set other data in the messages
        _DTrueMsg.anchorId = i;
        _DTrueMsg.tagId = 7;    // id = 7 is the one identified with true dist
        _DTrueMsg.range = (int)(_DT[i]*1000);

        // info 
        // ROS_INFO("Tag %d Dtrue %d : %g", _DTrueMsg.tagId, _DTrueMsg.anchorId, _DTrue[i]);

        // publish on topic
        _jack_disthandle_P.publish(_DTrueMsg);
    }     

}

// cost function - term on single anchor
_Float64 jackAPI::Ji(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

    // init 
    _Float64 J = 0;

    // compute cost function for single distance
    J = pow(sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2)) - D, 2);

    return J;
}

// cost function - gradient on single anchor
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

// cost function - hessian on single anchor
std::vector<_Float64> jackAPI::HJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

    // init
    std::vector<_Float64> HJ(9, 0.0);
    _Float64 norm = 0.0;
    int id;

    // compute cost function gradient for single distance on direction k
    norm = sqrt(pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));
    for (int k=0;k<3;k++){
        for (int r=0;r<3;r++){

            // index
            id = 3*k + r;

            // diagonal and off diagonal terms
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

// total cost function
_Float64 jackAPI::Jtot(std::vector<_Float64> p, std::vector<_Float64> D){

    // define index and iterators
    int i;
    int j;
    int idA;

    // stuff to save mid-operations
    std::vector<_Float64> A(3, 0.0);
    _Float64 Jtmp = 0;

    // define Jtot
    _Float64 Jtot = 0;

    // iterate over the whole set of anchors
    for (i=0;i<_Nanchors;i++){

        // anchor startpos
        idA = (i)*3;

        // get anchor position
        for (j=0;j<3;j++){
            A[j] = _A[idA+j];
        }

        // compute Ji and add
        Jtmp = Ji(p, A, D[i]);
        Jtot += Jtmp;

    }

    return Jtot;

}

// Optim lib minimization
jackal_op::GradientDescent jackAPI::OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D){

    // define iterators and stuff
    int i;
    bool success;
    
    // define initial condition in armalib type
    arma::vec p0_arma = arma::zeros(3,1);

    // cpointer to class jackAPI - handle
    jackAPI JackTmp = jackAPI("tmp",_Nanchors, _tagID);
    jackAPI *JackTmpPtr;
    JackTmpPtr = &JackTmp;

    // cycleover the anchors
    for (i=0;i<_Nanchors;i++){

        // copy distance to be optimized
        JackTmpPtr->_Dopt[i] = D[i];

        // info
        //ROS_INFO("Distance copied: %d: %g", i, JackTmpPtr->_Dopt[i]);

        // copy anchors
        JackTmpPtr->_A[3*i] = _A[3*i];
        JackTmpPtr->_A[3*i+1] = _A[3*i+1];
        JackTmpPtr->_A[3*i+2] = _A[3*i+2];

        // info
        //ROS_INFO("Anchor copied: %d: %g %g %g", i, JackTmpPtr->_A[3*i], JackTmpPtr->_A[3*i+1], JackTmpPtr->_A[3*i+2]);
    }

    // copy p0 in p0_arma (different types)
    for (i=0;i<3;i++){
        p0_arma(i) = p0[i];        
    }

    // info
    ROS_INFO("Init point: %g %g %g", p0_arma(0), p0_arma(1), p0_arma(2));

    // call optimlib - simplex like in this case
    if (_GradientFlag == 0){
        success = optim::nm(p0_arma,Jtot_arma,(void *)JackTmpPtr);
    }
    else{
        success = optim::bfgs(p0_arma,Jtot_arma,(void *)JackTmpPtr);
    }

    // info
    ROS_INFO("Opt point: %g %g %g", p0_arma(0), p0_arma(1), p0_arma(2));

    // copy p0_arma in _p (different types)
    for (i=0;i<3;i++){
        _p[i] = p0_arma[i];
    }

    // assign to GradientDescent
    _G.p = _p;
    _G.odom.pose.pose.position.x = _p[0];
    _G.odom.pose.pose.position.y = _p[1];
    _G.odom.pose.pose.position.z = _p[2];
    _G.A = _A;

    return _G;

}

// Newton-Rhapson
jackal_op::GradientDescent jackAPI::NewtonRaphson(std::vector<_Float64> p0, std::vector<_Float64> D, int Niter){
    
    // init cost function - tmp
    _Float64 Jtmp = 0;
    std::vector<_Float64> GJtmp(3, 0.0);
    std::vector<_Float64> HJtmp(9, 0.0);

    // init cost function - final
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

            // gradient
            GJLIB(k) = GJ[k];

            // hessian
            for (r=0;r<3;r++){
                idH = 3*k + r;
                HJINV(k,r) = HJ[idH];
            }
        }
        
        // try the newton-raphson step
        try {

            // compute inverse
            alglib::rmatrixinverse(HJINV, info, rep); 

            // compute step
            alglib::rmatrixmv(3, 3, HJINV, 0, 0, 0, GJLIB, 0, StepVector, 0, Xparams);

            // update _p
            for (k=0;k<3;k++){
                _p[k] = _p[k] - StepVector[k];                
            }     

            // info
            ROS_INFO("Newton-Raphson: OK");
        }
        catch(...) {

            // info
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