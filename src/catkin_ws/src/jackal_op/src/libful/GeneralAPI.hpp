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

// alglib include
//#include "linalg.cpp"

// armadillo include
#include <armadillo>

// defines and inlclude for optim
#define OPTIM_ENABLE_ARMA_WRAPPERS
#include <optim.hpp>

namespace genAPI {

    struct Tag {
        int Nanchors;
        _Float64 J;
        std::vector<_Float64> A;
        std::vector<_Float64> Dopt;
        std::vector<_Float64> p;
        std::vector<_Float64> GJ;
    };

    /** **** METHODS **** */
    // cost function - gradient
    std::vector<_Float64> GJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // Total cost function
    _Float64 Jtot_arma(const arma::vec& p_arma, arma::vec* grad_out, void* tag);

    // Optim lib minimization
    int OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D, Tag* tag, int GradientFlag);

}