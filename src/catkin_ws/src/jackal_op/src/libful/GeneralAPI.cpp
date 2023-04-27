// class with utilities for jackal with UWB handling
#include "GeneralAPI.hpp"

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

// total cost function - armadillo
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

// Optim lib minimization
int genAPI::OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D, Tag* tag, int GradientFlag){

    
    // define iterators and stuff
    int i;
    bool success;
    
    // define initial condition in armalib type
    arma::vec p0_arma = arma::zeros(3,1);
    
    // cycleover the anchors
    for (i=0;i<tag->Nanchors;i++){

        // copy distance to be optimized
        tag->Dopt[i] = D[i];
    }

    // copy p0 in p0_arma (different types)
    for (i=0;i<3;i++){
        p0_arma(i) = p0[i];        
    }

    // call optimlib - simplex like in this case
    if (GradientFlag == 0){
        success = optim::nm(p0_arma,genAPI::Jtot_arma,(void *)tag);
    }
    else{
        success = optim::bfgs(p0_arma,genAPI::Jtot_arma,(void *)tag);
    }

    // copy p0_arma in _p (different types)
    for (i=0;i<3;i++){
        tag->p[i] = p0_arma[i];
    }
    
    return (int)success;

}