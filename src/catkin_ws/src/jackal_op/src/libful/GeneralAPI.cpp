// class with utilities for jackal with UWB handling
#include "GeneralAPI.hpp"
#include "ros/ros.h"

#define BLOCKSIZE 9

/* ############# CERESAPI NAMESPACE ############# */
/* ############################################ */

/**
 * @brief Ceres cost function constructor.
 */
ceresAPI::FunctionSmall::FunctionSmall(genAPI::TagSet* tag, int i, int j, int k){

    this->Setup(tag, i, j, k);
}

// setup class
bool ceresAPI::FunctionSmall::Setup(genAPI::TagSet* tag, int i, int j, int k)
{
    // iteratot
    int it;

    // iterator
    _i = i;
    _j = j;
    _k = k;

    // assign tag
    _tag = tag;

    // NB: see https://stackoverflow.com/questions/58576579/when-to-define-multiple-residual-blocks-in-ceres

    // residual: ith cost function
    // _nresiduals: Ntags*Nanchors + Npairs (Tag position + geometrical constraint for bearing)
    _nresiduals = _tag->Nanchors*_tag->Ntags;

    // block: jth part of the optimization variables (Ntags in this case)
    // _nblocks: 1 -> I will use all the Ntags*3 pos variables 
    _nblocks = 1;

    // blocksize: 3 -> dimension of each position vector * number of tags + Npairs*Nangles (1 bearing)
    // currently we are not optimizing on the angle, let's see where we go
    _blocksize = 3*_tag->Ntags;

    // init
    std::vector<int32_t> *block_sizes = mutable_parameter_block_sizes();
    for (it=0;it<_nblocks;it++){
        block_sizes->push_back(_blocksize);
    }
    set_num_residuals(_nresiduals);

    // init J data
    _D = _tag->Tags[i].Dopt[j];
    
    return true;
}

// solve for numerous blocks
ceresAPI::Result ceresAPI::solveSmall(arma::vec& p_arma, void* tag){

    // create problem
    ceres::Problem problem;

    // iterator
    int i, j, k;
    bool success;

    // cast pointer
    genAPI::TagSet *tagP;
    tagP = (genAPI::TagSet *)tag;

    // init p0 (pos vector)
    double p0[tagP->Ntags*3];
    // add positions
    for (k=0;k<3*tagP->Ntags;k++){
        p0[k] = p_arma(k);
    }

    // cycle over residuals - position terms
    for (i=0; i<tagP->Ntags;i++){
        for (j=0; j<tagP->Nanchors;j++){  
            // add residuals
            problem.AddResidualBlock(new ceresAPI::FunctionSmall(tagP, i, j, i), nullptr, &p0[0]);      
        }
    }

    // options
    Solver::Options options;
    options.max_num_iterations = 1000;
    options.minimizer_progress_to_stdout = false;

    // minimizer - trust region
    // options.minimizer_type = ceres::TRUST_REGION;
    // options.trust_region_strategy_type = ceres::DOGLEG;
    // options.dogleg_type = ceres::TRADITIONAL_DOGLEG;
    // options.use_inner_iterations = false;
    // options.use_nonmonotonic_steps = false;

    // minimizer - line search
    // options.minimizer_type = ceres::LINE_SEARCH;
    // options.line_search_direction_type = ceres::BFGS;
    
    // minimizer - linear solver
    options.linear_solver_type = ceres::DENSE_QR;

    // call solver
    Result result;
    
    // init result
    for (i=0;i<3*tagP->Ntags;i++){
        result.p.push_back(0.0);
    }
    
    // solve problem
    Solve(options, &problem, &result.summary);
    ROS_INFO("SOLVED: %g %g", result.summary.initial_cost, result.summary.final_cost);

    // store results
    for (i=0;i<3*tagP->Ntags;i++){
        result.p[i] = p0[i];
    }

    return result;

}

// evaluate for small function
bool ceresAPI::FunctionSmall::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const {
    
    // iterator
    int i, j;
    int idJ, idR;

    // init storage
    double Jt;
    std::vector<double> A(3,0.0);           // position 
    std::vector<double> p(3, 0.0);          // position
    std::vector<double> grad_out(3,0.0);    // position

    // current position
    p[0] = parameters[0][3*_i + 0];
    p[1] = parameters[0][3*_i + 1];
    p[2] = parameters[0][3*_i + 2];    

    // init residual
    for (i=0;i<_nresiduals;i++){
        residuals[i] = 0.0;
    }
    
    // store anchors (_A is const)
    for (i=0;i<3;i++){
        A[i] = _tag->Tags[_i].A[3*_j+i];
    }
    // ROS_WARN("A %d: %g %g %g", _j, A[0], A[1], A[2]);

    // compute residuals
    // NB: theoretically here I am cycling over the blocks, because I am compute all the Ji (residual)
    // depending on xj (block). For a single block there could be more than one residual
    // but this is smth I will deal with in the residual assignment within the loop

    // compute Jt[i]
    // Compute the block number (depends if bearing is used)
    idR = _tag->Nanchors*_i + _j;
    
    residuals[idR] = genAPI::J(&p[0], &grad_out[0], &A[0], _D);
    // ROS_WARN("RES %d: %g", idR, residuals[idR]);

    // gradient positions
    idJ = (_tag->Nanchors*_i)*_blocksize + _j*_blocksize + 3*_i;
    if (jacobians != nullptr && jacobians[0] != nullptr) {

        // init jacobians - only at the beginning 
        for (i=0;i<_blocksize;i++){
            for (j=0;j<_nresiduals;j++){
                    jacobians[0][j*_blocksize + i] = 0.0;      
            }
        }

        // assign gradients
        // gradient on position of tags - always
        jacobians[0][idJ + 0] = grad_out[0];
        jacobians[0][idJ + 1] = grad_out[1];
        jacobians[0][idJ + 2] = grad_out[2];
    }
    

    return true;

}

/* ############# GENAPI NAMESPACE ############# */
/* ############################################ */

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

        if (grad_out && false) {

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

// single J for ceres single block
_Float64 genAPI::J(double* p, double* grad_out, double* A, double D){

    // init J
    double J = 0;

    // iterator
    int j;

    // compute norm
    double norm = sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));

    // compute J
    // J = norm - D;
    J = pow(norm,2) - pow(D,2);   

    // compute gradient
    for (j=0;j<3;j++){
        // grad_out[j] = (p[j] - A[j]) / (norm);
        grad_out[j] = 2*(p[j] - A[j]);

        // check nan
        if (std::isnan(grad_out[j])){
            grad_out[j] = 0.0;
        }
    }
    return J;
    
}

// Optim lib minimization - genberal for position and bearing
int genAPI::OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D, TagSet* tag){

    
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
    success = optim::nm(p0_arma,genAPI::Jtot_arma,(void *)tag, optimset);

    // copy p0_arma in _p (different types)
    for (i=0;i<tag->Ntags;i++){
        for (j=0;j<3;j++){
            tag->Tags[i].p[j] = p0_arma[3*i + j];
        }
    }
    
    return (int)success;

}

// Ceres lib minimization - currently only position
int genAPI::CeresMin(std::vector<_Float64> p0, std::vector<_Float64> D, TagSet* tag){

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

    // call optimlib - simplex like in this case
    ceresAPI::Result result = ceresAPI::solveSmall(p0_arma, tag);

    // copy p0_arma in _p (different types)
    for (i=0;i<tag->Ntags;i++){
        for (j=0;j<3;j++){
            tag->Tags[i].p[j] = result.p[3*i + j];
        }
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

// Gram-Schmidt
arma::mat genAPI::gramschmidt(arma::mat U){

    // define vars
    arma::vec u = arma::zeros(3,1);
    arma::vec v = arma::zeros(3,1);
    arma::mat V = arma::zeros(3,3);
    int i;

    // start process - 3 dim for now
    // see: https://math.hmc.edu/calculus/hmc-mathematics-calculus-online-tutorials/linear-algebra/gram-schmidt-method/
    V.col(0) = U.col(0);
    V.col(1) = U.col(1) - arma::dot(U.col(1),V.col(0))*V.col(0)/arma::norm(V.col(0));
    V.col(2) = U.col(2) - arma::dot(U.col(2),V.col(0))*V.col(0)/arma::norm(V.col(0)) - arma::dot(U.col(2),V.col(1))*V.col(1)/arma::norm(V.col(1));

    // normalization
    for (i=0;i<3;i++){
        V.col(i) = arma::normalise(V.col(i));
    }

    // test
    // ROS_WARN("test: %g %g %g %g %g %g %g %g %g", U(0,0),U(1,0), U(2,0), U(0,1),U(1,1), U(2,1), U(0,2),U(1,2), U(2,2));
    // ROS_WARN("test: %g %g %g %g %g %g %g %g %g", V(0,0),V(1,0), V(2,0), V(0,1),V(1,1), V(2,1), V(0,2),V(1,2), V(2,2));
    // ROS_WARN("test dotprod: %g %g %g", arma::dot(V.col(0),V.col(1)), arma::dot(V.col(0),V.col(2)), arma::dot(V.col(1),V.col(2)));
    // ROS_WARN("test norm: %g %g %g", arma::norm(V.col(0)), arma::norm(V.col(1)), arma::norm(V.col(2)));
    
    return V;
}

// Procustes
arma::mat genAPI::procustes(arma::mat Cw, arma::mat Co){

    // each column of W is a vector in the world frame
    // each column of U is a vector in the odom frame
    // we want to solve Oi = R*Wi forall i, with R orthogonal
    // check (21/06) solution at: https://simonensemble.github.io/posts/2018-10-27-orthogonal
    // -procrustes/#:~:text=The%20orthogonal%20Procrustes%20problem%20is,molecular%20modeling%2C%20and%20speech%20translation.

    // variables
    arma::mat R = arma::zeros(3,3);

    // SVD variables
    arma::mat U = arma::zeros(3,3);
    arma::mat V = arma::zeros(3,3);
    arma::vec omega = arma::zeros(3,1);

    // compute singular value decomposition
    arma::svd(U,omega,V,Cw*Co.t());

    // compute result
    R = V*U.t();

    return R;

}