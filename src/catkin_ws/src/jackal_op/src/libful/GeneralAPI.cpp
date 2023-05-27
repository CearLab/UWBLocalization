// class with utilities for jackal with UWB handling
#include "GeneralAPI.hpp"
#include "ros/ros.h"

#define BLOCKSIZE 9

/* ############# CERESAPI NAMESPACE ############# */
/* ############################################ */
/**
 * @brief Ceres cost function constructor.
 */
ceresAPI::Function::Function(genAPI::TagSet* tag) : _tag(_tag)
{
    // iterator
    int i = 0;

    // assign tag
    _tag = tag;

    // NB: see https://stackoverflow.com/questions/58576579/when-to-define-multiple-residual-blocks-in-ceres

    // residual: ith cost function
    // _nresiduals: thepretically, Ntags + Npairs (Tag position + geometrical constraint for bearing)
    // _residuals: however, each residual should be initialized on its own in ceres
    // thus, I will just use one residual where I will store the entire cost function
    _nresiduals = 1;

    // block: jth part of the optimization variables (Ntags in this case)
    // _nblocks: theoretically Ntags(Tag position)
    // _nblocks: however, each block should be part of a separate residual 
    // thus, I will just use one block which will have all the tags positions 
    _nblocks = 1;

    // blocksize: 3 -> dimension of each position vector * number of tags
    _blocksize = 3*_tag->Ntags;

    // init
    std::vector<int32_t> *block_sizes = mutable_parameter_block_sizes();
    block_sizes->push_back(_blocksize);
    set_num_residuals(_nresiduals);

    // init the struct as well
    _CostFunctor._tag = _tag;
    _CostFunctor._blocksize = _blocksize;
    _CostFunctor._nblocks = _nblocks;
    _CostFunctor._nresiduals = _nresiduals;

}

/**
 * @brief Ceres cost function constructor.
 */
ceresAPI::FunctionSmall::FunctionSmall(genAPI::TagSet* tag, int i, int j) : _tag(_tag)
{
    // iteratot
    int k;

    // assign tag
    _tag = tag;

    // NB: see https://stackoverflow.com/questions/58576579/when-to-define-multiple-residual-blocks-in-ceres

    // residual: ith cost function
    // _nresiduals: thepretically, Ntags + Npairs (Tag position + geometrical constraint for bearing)
    // _residuals: however, each residual should be initialized on its own in ceres
    // thus, I will just use one residual where I will store the entire cost function
    _nresiduals = _tag->Nanchors*_tag->Ntags;

    // block: jth part of the optimization variables (Ntags in this case)
    // _nblocks: theoretically Ntags(Tag position)
    // _nblocks: however, each block should be part of a separate residual 
    // thus, I will just use one block which will have all the tags positions 
    _nblocks = _tag->Nanchors*_tag->Ntags;

    // blocksize: 3 -> dimension of each position vector * number of tags
    _blocksize = 3;

    // init
    std::vector<int32_t> *block_sizes = mutable_parameter_block_sizes();
    block_sizes->push_back(_blocksize);
    set_num_residuals(_nresiduals);

    // init J data
    _D = _tag->Tags[i].Dopt[j];
    for (k=0;k<3;k++){
        _A[k] = _tag->Tags[i].A[k];
    }
    

}

// Ceres solution - see user manual
ceresAPI::Result ceresAPI::solve(Function *function, arma::vec& p_arma, void* tag){

    // create problem
    ceres::Problem problem;

    // iterator
    int i, j;

    // init parameters: in R: NblocksXblocksize
    double p0[function->_blocksize];
    for (i=0;i<function->_blocksize;i++){
        p0[i] = p_arma(i);
    }
    
    // cast pointer
    genAPI::TagSet *tagP;
    tagP = (genAPI::TagSet *)tag;

    // assign anchors and distances
    for (i=0;i<tagP->Ntags;i++){
        function->_tag->Tags[i].A = tagP->Tags[i].A;
        function->_tag->Tags[i].Dopt = tagP->Tags[i].Dopt;
    }
    
    // add residuals: here one residual for all (meh..)
    problem.AddResidualBlock(function, nullptr, &p0[0]);

    // this is a test for the numerical differentiation
    // it is exclusive with the previous
    // ceresAPI::CostFunctor* tmp = new ceresAPI::CostFunctor;
    // *tmp = function->_CostFunctor;
    // CostFunction* cost_function = new ceres::NumericDiffCostFunction<ceresAPI::CostFunctor, ceres::FORWARD, 1, BLOCKSIZE>(tmp);
    // problem.AddResidualBlock(cost_function, nullptr, p0);
    
    // options
    Solver::Options options;
    options.max_num_iterations = 10000;
    // options.function_tolerance = 1e-10;
    // options.gradient_tolerance = 1e-14;
    // options.parameter_tolerance = 1e-12;
    options.minimizer_progress_to_stdout = false;
    options.linear_solver_type = ceres::DENSE_QR;
    //options.trust_region_strategy_type = ceres::DOGLEG;
    //options.line_search_direction_type = ceres::STEEPEST_DESCENT;
    
    // call solver
    Result result;

    // init result
    for (i=0;i<function->_blocksize;i++){
        result.p.push_back(0.0);
    }

    // solve problem
    Solve(options, &problem, &result.summary);
    ROS_WARN("SOLVED: %g %g", result.summary.initial_cost, result.summary.final_cost);

    // store results
    for (i=0;i<function->_blocksize;i++){
        result.p[i] = p0[i];
    }

    return result;
}

// solve for numerous blocks
ceresAPI::Result ceresAPI::solveSmall(arma::vec& p_arma, void* tag){

    // create problem
    ceres::Problem problem;

    // iterator
    int i, j;

    // init p0 (pos vector)
    double p0[3];

    // cast pointer
    genAPI::TagSet *tagP;
    tagP = (genAPI::TagSet *)tag;

    // cycle over residuals
    for (i=0; i<tagP->Ntags;i++){
        for (j=0; j<tagP->Nanchors;j++){

            // create functionSmall instance
            ceresAPI::FunctionSmall* function = new ceresAPI::FunctionSmall(tagP, i, j);

            // add residuals
            problem.AddResidualBlock(function, nullptr, &p0[0]);

            // delete function
            delete[] function;

        }
    }



}

/**
 * @brief Ceres cost function Evaluate.
 *
 * @param parameters
 * @param residuals
 * @param jacobians
 */
bool ceresAPI::Function::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const
{

    // iterators
    int i, j;

    // init storage
    double Jt;
    std::vector<double> p(_blocksize, 0.0);
    std::vector<double> grad_out(_blocksize,0.0);

    // init residuals: in R: Nresiduals
    residuals[0] = 0;

    // compute residuals
    // NB: theoretically here I am cycling over the blocks, because I am compute all the Ji (residual)
    // depending on xj (block). For a single block there could be more than one residual
    // but this is smth I will deal with in the residual assignment within the loop

    // However, I am now implementing a single block. Thus, I am simply computing the whole cost function
    // which is made in this case of Ntags (+ Npairs) terms
    for (i=0;i<_tag->Ntags;i++){

        // current position
        p[0] = parameters[0][3*i + 0];
        p[1] = parameters[0][3*i + 1];
        p[2] = parameters[0][3*i + 2];

        // compute Jt[i]
        // There is no bearing for now, so there is a residual for each block
        residuals[0] = residuals[0] + genAPI::Jtot(&p[0], &grad_out[0], (void*)&_tag->Tags[i]);

        if (jacobians != nullptr) {
            jacobians[0][3*i + 0] = grad_out[0];
            jacobians[0][3*i + 1] = grad_out[1];
            jacobians[0][3*i + 2] = grad_out[2];
            //ROS_WARN("GRAD: %g %g %g", jacobians[0][3*i + 0], jacobians[0][3*i + 1], jacobians[0][3*i + 2]);
        }
        
    }

    return true;
}

// evaluate for small function
bool ceresAPI::FunctionSmall::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const {

    return true;

}

// test template for numerical differentiation - develop if necessary
bool ceresAPI::CostFunctor::operator()(const double* const parameters, double* residuals) const {

    // iterators
    int i, j;

    // init storage
    double Jt;
    double p[_blocksize];
    double grad_out[_blocksize];

    // init residuals: in R: Nresiduals
    residuals[0] = 0;

    // assign storage - param and gradient
    // dim 3 (space)
    for (i = 0; i < 3; i++) {
        p[i] = 0.0;
        grad_out[i] = 0.0;
    }

    // compute residuals
    // NB: theoretically here I am cycling over the blocks, because I am compute all the Ji (residual)
    // depending on xj (block). For a single block there could be more than one residual
    // but this is smth I will deal with in the residual assignment within the loop

    // However, I am now implementing a single block. Thus, I am simply computing the whole cost function
    // which is made in this case of Ntags (+ Npairs) terms
    for (i=0;i<_tag->Ntags-2;i++){

        // current position
        p[0] = parameters[3*i + 0];
        p[1] = parameters[3*i + 1];
        p[2] = parameters[3*i + 2];

        // compute Jt[i]
        // There is no bearing for now, so there is a residual for each block
        //ROS_WARN("HERE: %g", _tag->Tags[i].Dopt[0]);
        Jt += genAPI::Jtot(p, grad_out, (void*)&_tag->Tags[i]);
        
    }

    residuals[0] = Jt;

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

// cost function - double
_Float64 genAPI::Jtot(double* p, double* grad_out, void* tag){

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
    double GJ[3];
    for (i=0;i<3;i++){
        GJ[i] = 0.0;
        grad_out[i] = 0.0;
    }

    // init norm
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
        norm = sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));    

        // NB: this is the cost function used in the paper
        //Jtmp = pow(norm - tagP->Dopt[i], 2);

        // however, ceres minimizes 0.5*|| f(x) ||^2
        // Thus, we do not need to use the quadratic form, as the positive definiteness 
        // is implied in ceres. This ease a lot the computation of the gradient
        Jtmp = norm - 1*tagP->Dopt[i];
        //Jtmp = (p[0]-tagP->Dopt[0])*(p[1]-tagP->Dopt[1]);
        
        // add term
        Jtot = Jtot + Jtmp;
        tagP->J = tagP->J + Jtmp;

        int ready = std::accumulate(tagP->Dopt.begin(), tagP->Dopt.end(), tagP->Nanchors);

        if (grad_out && true) {

            // compute cost function gradient for single distance on direction j       
            for (j=0;j<3;j++){

                // this is the gradient as for the paper version of the cost function
                //GJ[j] = 1*(p[j] - A[j]) * (1 - tagP->Dopt[i]/norm); 

                // this is the gradient as for the reduced cost function (see previous comment)
                GJ[j] = (p[j] - A[j]) / (norm); 

                // check nan
                if (std::isnan(GJ[j])){
                    GJ[j] = 0.0;
                }

                // update gradient
                grad_out[j] = grad_out[j] + GJ[j];
            }
      
        }

        //ROS_WARN("A %d: %g %g %g", i, A[0], A[1], A[2]);
        //ROS_WARN("D %d: %g", i, Jtmp);
        //ROS_WARN("P %d: %g %g %g", i, p[0], p[1], p[2]);
        ROS_WARN("GJ %d: %g %g %g", i, GJ[0], GJ[1], GJ[2]);

    }

    return Jtot;
}

// single J for ceres single block
_Float64 genAPI::J(double* p, double* grad_out, double* A, double D){

    // compute norm
    double norm = sqrt( pow((p[0]-A[0]),2) + pow((p[1]-A[1]),2) + pow((p[2]-A[2]),2));

    // compute J
    double J = norm - D;

    // compute gradient
    for (int j=0;j<3;j++){
        grad_out[j] = (p[j] - A[j]) / (norm);
    }

    return J;
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
    success = optim::nm(p0_arma,genAPI::Jtot_arma_bear,(void *)tag, optimset);

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
    ceresAPI::Function* function = new ceresAPI::Function(tag);
    ceresAPI::Result result = ceresAPI::solve(function, p0_arma, tag);

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