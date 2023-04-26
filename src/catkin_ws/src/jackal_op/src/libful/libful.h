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

// ros includes
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/MarkerArray.h"
#include "std_msgs/String.h"
#include <gtec_msgs/Ranging.h>
#include <nav_msgs/Odometry.h>
#include <jackal_op/MeshUWB.h>
#include <jackal_op/GradientDescent.h>

// alglib include
#include "linalg.cpp"

// armadillo include
#include <armadillo>

// defines and inlclude for optim
#define OPTIM_ENABLE_ARMA_WRAPPERS
#include <optim.hpp>

// LIB functions - no class

class jackAPI {

private:

    /** **** ATTRIBUTES **** */
    int _cnt;   // counter (DEBUG)
    std::string _name;  // class instance name
    ros::Time _begin;   // timer

public:

    /** **** ATTRIBUTES **** */
    int _Nanchors;  // number of anchors for a single mesh
    std::vector<_Float64> _DT, _Dopt;  // distance vector on the measured tag + 1 dist used for opt
    std::vector<_Float64> _A, _p;   // matrix with anchors estimated position
    int _tagID; // ID of the tag read by the node
    int _GradientFlag;

    jackal_op::MeshUWB _DTmsg; // message containing the distances measured (subscribed)
    jackal_op::GradientDescent _G;  // message with the optimization info
    gtec_msgs::Ranging _DTrueMsg;   // message with the synthetic true distances

    ros::Subscriber _jack_disthandle_ST;    // subscriber to tag distances
    ros::Subscriber _jack_disthandle_SA;    // subscriber to anchors positions
    ros::Publisher  _jack_disthandle_P;     // publisher on the distance wrapper
    ros::Publisher  _jack_trilateration_P;  // publisher on the trilateration topic    

    /** **** CONSTRUCTOR **** */
    jackAPI(std::string name, int Nanchors, int tagID);

    /** **** METHODS **** */
    // subscriber callback
    void ChatterCallbackT(const gtec_msgs::Ranging& msg);   // callback for the tag trilateration
    void ChatterCallbackA(const visualization_msgs::MarkerArray& msg);  // callback for the anchor positions
    void ChatterCallbackDtrue(const nav_msgs::Odometry& msg);   // callback for the true measurement handling

    // cost function
    _Float64 Ji(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // cost function - gradient
    std::vector<_Float64> GJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // cost function - hessian
    std::vector<_Float64> HJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // Total cost function
    _Float64 Jtot(std::vector<_Float64> p, std::vector<_Float64> D);

    // Newton-Rhapson - analytic
    jackal_op::GradientDescent NewtonRaphson(std::vector<_Float64> p0, std::vector<_Float64> D, int Niter);

    // Optim lib minimization
    jackal_op::GradientDescent OptimMin(std::vector<_Float64> p0, std::vector<_Float64> D);

};