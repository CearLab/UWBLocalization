// class with utilities for jackal with UWB handling
#include "GeneralAPI.hpp"
#include "ros/ros.h"

// init Tag
genAPI::Tag genAPI::TagInit(int Nanchors){

    // counters
    int i, j;

    // init Tag
    genAPI::Tag TagZero;

    // set Nanchors
    TagZero.Nanchors = Nanchors;

    // init anchors
    for (i=0;i<Nanchors;i++){

        for (j=0;j<3;j++){
            TagZero.A.push_back(0.0);
        }

        // measures
        TagZero.Dopt.push_back(0.0);
    }

    // other stuff
    TagZero.p = {0.0, 0.0, 0.0};
    TagZero.J = 0.0;
    TagZero.GJ = {0.0, 0.0, 0.0};

    return TagZero;

}

// cost function - gradient on single anchor
std::vector<_Float64> genAPI::GJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D){

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

// total cost function - armadillo - position only (struct Tag)
_Float64 genAPI::Jtot_arma(const arma::vec& p_arma, arma::vec* grad_out, void* tag){

    // define index and iterators
    int i;
    int j;
    int idA;

    // stuff to save mid-operations
    std::vector<_Float64> A(3, 0.0);     
    genAPI::Tag *tagP;
    
    // define Jtot
    _Float64 Jtot = 0;
    _Float64 Jtmp = 0;   

    // init - gradient
    std::vector<_Float64> GJ(3, 0.0);
    _Float64 norm = 0.0;    

    // define pointer class
    tagP = (genAPI::Tag *)tag; 
    tagP->J = 0;    // init cost fcn

    for (i=0;i<tagP->Nanchors;i++){

        // anchor startpos
        idA = (i)*3;

        // get anchor position
        for (j=0;j<3;j++){
            A[j] = tagP->A[idA+j];
        }

        // compute Ji and add    
        norm = sqrt( pow((p_arma[0]-A[0]),2) + pow((p_arma[1]-A[1]),2) + pow((p_arma[2]-A[2]),2));    
        Jtmp = pow(norm - tagP->Dopt[i], 2);
        Jtot = Jtot + Jtmp;
        tagP->J = tagP->J + Jtmp;

        if (grad_out){

            // compute cost function gradient for single distance on direction j       
            for (j=0;j<3;j++){
                GJ[j] = (p_arma[j] - A[j]) * (1 - tagP->Dopt[i]/norm);
                grad_out[j] = grad_out[j] + GJ[j];
                tagP->GJ[i] = GJ[j];
            }             
        }

    }

    return Jtot;

}

// total cost function - armadillo - bearing (struct Tags)
_Float64 genAPI::Jtot_arma_bear(const arma::vec& p_arma, arma::vec* grad_out, void* tag){

    // NB: assuming 2 tags only here

    // define index and iterators
    int i;
    int j;
    int k;

    // cast pointer
    genAPI::TagSet *tagP;
    tagP = (genAPI::TagSet *)tag;

    // define cost function arrays
    std::vector<_Float64> Jp(tagP->Npairs,0.0);
    std::vector<_Float64> Jt(tagP->Ntags,0.0);
    _Float64 Jtot = 0.0;

    // position array
    arma::vec p0 = arma::zeros(3,1);
    arma::vec ptilde1 = arma::zeros(3,1);   // 2 support arrays for a pair of tags 
    arma::vec ptilde2 = arma::zeros(3,1);

    // bearing var (single var now)
    _Float32x theta = 0.0;
    _Float64 Dtag = 0.0;

    _Float64 JpS = 0.0;
    _Float64 JpT = 0.0;

    // cost function - tags
    for (i=0;i<tagP->Ntags;i++){

        // copy initial condition - tag ith
        for (j=0;j<3;j++){
            p0[j] = p_arma[3*i + j];
        }

        // compute Jt[i]
        Jt[i] = genAPI::Jtot_arma(p0, grad_out, (void*)&tagP->Tags[i]);

    }

    // accumulate
    for (i=0;i<tagP->Ntags;i++){
        JpT += Jt[i];
    }

    for (j=0;j<tagP->Npairs;j++){
        JpS += Jp[j];
    }

    Jtot = JpT;

    for (j=0;i<tagP->Ntags;j++){
        tagP->Tags[j].J = Jtot;
    }

     if (grad_out){
        // assign the gradient here
     }

    return Jtot;

}

// Optim lib minimization - genberal for position and bearing
int genAPI::OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D, TagSet* tag, int GradientFlag){

    
    // define iterators and stuff
    int i, j;
    bool success;
    
    // define initial condition in armalib type
    arma::vec p0_arma = arma::zeros(p0.size(),1);
    
    // cycleover the tagse and anchors
    for (i=0;i<tag->Ntags;i++){
        for (j=0;j<tag->Nanchors;j++){
            // copy distance to be optimized
            tag->Tags[i].Dopt[j] = D[tag->Nanchors*i + j];
        }
    }
    
    // copy p0 in p0_arma (different types)
    for (i=0;i<p0.size();i++){
        p0_arma(i) = p0[i];        
    }

    // settings
    optim::algo_settings_t optimset;
    optimset.iter_max = 5000;

    // call optimlib - simplex like in this case
    if (GradientFlag == 0){
        success = optim::nm(p0_arma,genAPI::Jtot_arma_bear,(void *)tag, optimset);
    }
    else{
        success = optim::bfgs(p0_arma,genAPI::Jtot_arma_bear,(void *)tag);
    }

    // copy p0_arma in _p (different types)
    for (i=0;i<tag->Ntags;i++){
        for (j=0;j<3;j++){
            tag->Tags[i].p[j] = p0_arma[3*i + j];
        }
    }
    
    return (int)success;

}

// Ceres lib minimization - currently only position
int genAPI::CeresMin(std::vector<_Float64> p0, std::vector<_Float64> D, Tag* tag){

    // define iterators and stuff
    int i;
    bool success;

    // define vars for ceres built-in fcn
    std::vector<_Float64> poles1_x, poles1_y, poles1_z, poles2_x, poles2_y, poles2_z;
    std::array<_Float64, 3> pc1, pc2;
    
    // cycleover the anchors
    for (i=0;i<tag->Nanchors;i++){

        // copy distance to be optimized
        tag->Dopt[i] = D[i];

        // copy anchor position
        // x position - mesh 1/2
        poles1_x.push_back(tag->A[3*i]);
        poles2_x.push_back(tag->A[3*i]);   

        // y position - mesh 1/2
        poles1_y.push_back(tag->A[3*i+1]);
        poles2_y.push_back(tag->A[3*i+1]); 

        // y position - mesh 1/2
        poles1_z.push_back(tag->A[3*i+2]);
        poles2_z.push_back(tag->A[3*i+2]); 

    }

    // fill p0
    for (i=0;i<3;i++){
        pc1[i] = p0[i];
        pc2[i] = p0[i];
    }

    // call optimlib - simplex like in this case
    Function* function = new Function(tag->Nanchors, tag->Nanchors, 0, 0, 
    D, D, poles1_x, poles1_y, poles1_z, poles2_x, poles2_y, poles2_z);
    Result result = solve(function, pc1, pc2);

    // copy p0_arma in _p (different types)
    for (i=0;i<3;i++){
        tag->p[i] = result.p1[i];
    }
    
    return (int)success;

}

// model observer
std::vector<_Float64> genAPI::modelObserver(std::vector<_Float64> x, std::vector<_Float64> u){

    std::vector<_Float64> xdot(genAPI::stateDim, 0.0);

    // integrate position
    xdot[genAPI::pos_p[0]] = x[genAPI::pos_v[0]];
    xdot[genAPI::pos_p[1]] = x[genAPI::pos_v[1]];
    xdot[genAPI::pos_p[2]] = x[genAPI::pos_v[2]];

    // integrate position
    xdot[genAPI::pos_v[0]] = x[genAPI::pos_a[0]] - x[genAPI::pos_b[0]];
    xdot[genAPI::pos_v[1]] = x[genAPI::pos_a[1]] - x[genAPI::pos_b[1]];
    xdot[genAPI::pos_v[2]] = x[genAPI::pos_a[2]] - x[genAPI::pos_b[2]];

    // integrate bias
    xdot[genAPI::pos_b[0]] = 0.0;
    xdot[genAPI::pos_b[1]] = 0.0;
    xdot[genAPI::pos_b[2]] = 0.0;

    // filter acceleration
    xdot[genAPI::pos_a[0]] = genAPI::alpha * (u[0] - x[genAPI::pos_a[0]]);
    xdot[genAPI::pos_a[1]] = genAPI::alpha * (u[1] - x[genAPI::pos_a[1]]);
    xdot[genAPI::pos_a[2]] = genAPI::alpha * (u[2] - x[genAPI::pos_a[2]]);


    return xdot;
}

// Euler integration - hybrid system
std::vector<_Float64> genAPI::odeEuler(std::vector<_Float64> x, std::vector<_Float64> u, _Float64 dt){

    // init
    std::vector<_Float64> xdot(genAPI::stateDim, 0.0);
    std::vector<_Float64> xnew(genAPI::stateDim, 0.0);
    std::vector<_Float64> DT(genAPI::stateDim, dt);
    std::vector<_Float64> xstep(genAPI::stateDim, 0.0);

    // compute xdot
    xdot = genAPI::modelObserver(x, u);

    // integrate - forward 
    std::transform(DT.begin(), DT.end(), xdot.begin(), xstep.begin(), std::multiplies<float>());
    std::transform(x.begin(), x.end(), xstep.begin(), xnew.begin(), std::plus<float>());

    return xnew;
}