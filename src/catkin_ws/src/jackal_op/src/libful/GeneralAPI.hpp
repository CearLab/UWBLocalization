// define class with useful stuff

// standard includes
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <functional>

// alglib include
// #include "linalg.cpp"

// armadillo include
#include <armadillo>

// defines and inlclude for optim
#define OPTIM_ENABLE_ARMA_WRAPPERS
#include <optim.hpp>

// ceres
#define CERES_SHOW_RESIDUALS
#include <ceres/ceres.h>

// stuff
#define LEN(arr) ((int)(sizeof(arr) / sizeof(arr)[0]))

using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;

namespace genAPI
{

    // model parameters
    const _Float64 alpha = 100.0;
    const int stateDim = 4 * 3 + 4 + 3 * 2;
    const int inputDim = 3;
    const std::vector<int> pos_p = {0, 7, 14};
    const std::vector<int> pos_v = {1, 8, 15};
    const std::vector<int> pos_b = {2, 9, 16};
    const std::vector<int> pos_a = {3, 10, 17};
    const std::vector<int> pos_ang = {4, 11, 18, 21}; // this is the quaternion
    const std::vector<int> pos_bw = {5, 12, 19};
    const std::vector<int> pos_w = {6, 13, 20};
    // const std::vector<_Float64> gamma = {0.5, 0, 0};
    const std::vector<_Float64> gamma = {1.8112, 0.6373, 1.0015};
    const std::vector<_Float64> theta = {0.4221, 0.2888, -0.0281};
    // const std::vector<_Float64> theta = {1, 1.2662, -0.5457};
    // const std::vector<_Float64> theta = {0.8, 0.1862, -0.0250};

    // env params
    const std::vector<_Float64> Anchors = {
        // 0, -4, 3.5,
        // 0, +4, 3.5,
        // 4, +4, 3.5,
        // 4, -4, 3.5
        +0.0, +0.0, +3.3,
        +0.0, +4.70, +3.3,
        +7.0, +4.70, +3.3,
        +7.0, +0.0, +3.3};

    struct Tag
    {
        int Nanchors;
        _Float64 J;
        std::vector<_Float64> A;
        std::vector<_Float64> Dopt;
        std::vector<_Float64> p;
        std::vector<_Float64> GJ;
    };

    struct TagSet
    {

        int Ntags;
        int Npairs;
        int Nanchors;
        std::vector<genAPI::Tag> Tags;
    };

    struct EKF
    {

        double L;
        double T = 0.01;
        int stateDim = 22;
        int measDim = 18;
        int procDim = 9;
        arma::mat Phat = 0.1 * arma::eye<arma::mat>(stateDim, stateDim);
        arma::vec4 q;
        arma::vec3 p;
        arma::vec3 w;
        arma::vec3 MU;
        arma::mat33 R;
        arma::mat44 OMEGA;
        arma::mat33 M1, M2, M3, M4;
        arma::mat44 S1, S2, S3;
        arma::mat GFX = arma::zeros(stateDim, stateDim);
        arma::mat GFW = arma::zeros(stateDim, procDim);
        arma::mat GHX = arma::zeros(measDim, stateDim);

        // measure
        arma::mat Rmeas = 0.01 * arma::eye<arma::mat>(measDim, measDim);
        arma::mat Qproc = 100 * arma::eye<arma::mat>(procDim, procDim);
    };

    genAPI::EKF *_EKF;

    /** **** METHODS **** */

    // init Tag
    Tag TagInit(int Nanchors);

    // cost function single miniblock
    _Float64 J(double *p, double *grad_out, double *A, double D);

    // Total cost function - position only
    _Float64 Jtot_arma(const arma::vec &p_arma, arma::vec *grad_out, void *tag);

    // Optim lib minimization
    int OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D, TagSet *tag);

    // Ceres lib minimization
    int CeresMin(std::vector<_Float64> p0, std::vector<_Float64> D, TagSet *tag);

    // model observer
    std::vector<_Float64> modelObserver(std::vector<_Float64> x, std::vector<_Float64> u);

    // Euler integration - hybrid system
    std::vector<_Float64> odeEuler(std::vector<_Float64> x, std::vector<_Float64> u, _Float64 dt);

    // Gram-Schmidt
    arma::mat gramschmidt(arma::mat U);

    // Procustes
    arma::mat procustes(arma::mat W, arma::mat O);

    // EKF //
    // init EKF
    int EKFInit();

    // model EKF
    std::vector<_Float64> modelEKF(std::vector<_Float64> x, std::vector<_Float64> u);

    // R(q)
    int ROT();

    // R(q) derivative
    int M();

    // P with anchor terms derivative
    int MU(arma::mat33 TagPos, int i, int j);

    // L with anchor term derivative
    int L(arma::mat33 TagPos, int i, int j);

    // OMEGA(w)
    int OMEGA();

    // OMEGA(w) derivative
    int S();

    // Jacobian constructor
    int G(arma::mat33 TagPos);

    // Euler integration - EKF
    std::vector<_Float64> odeEulerEKF(std::vector<_Float64> x, std::vector<_Float64> u, _Float64 dt);

    // EKF step
    int EKF_step(std::vector<_Float64> X, std::vector<_Float64> Y, arma::mat33 TagPos, int full);

}

namespace ceresAPI
{

    struct Result
    {
        Result() {}

        std::vector<_Float64> p;
        ceres::Solver::Summary summary;
    };

    class FunctionSmall : public CostFunction
    {
    public:
        // attributes
        int _blocksize;
        int _nblocks;
        int _nresiduals;
        int _i;
        int _j;
        int _k;

        genAPI::TagSet *_tag;

        double _D;

        FunctionSmall(genAPI::TagSet *tag, int i, int j, int k);
        bool Setup(genAPI::TagSet *tag, int i, int j, int k);
        bool Evaluate(double const *const *parameters, double *residuals, double **jacobians) const;

    private:
    };

    Result solveSmall(arma::vec &p_arma, void *tag);
}