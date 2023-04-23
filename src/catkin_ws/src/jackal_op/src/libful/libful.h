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
#include <jackal_op/MeshUWB.h>
#include <jackal_op/GradientDescent.h>

// alglib include
#include "linalg.cpp"

class jackAPI {

private:

    /** **** ATTRIBUTES **** */
    int _cnt;
    int _Nanchors;

    std::vector<_Float64> _DT1, _DT2, _DT3;
    std::vector<_Float64> _A, _p;
    std::string _name;

    ros::Time _begin;

    jackal_op::MeshUWB _DT;
    jackal_op::GradientDescent _G;

public:

    /** **** ATTRIBUTES **** */
    ros::Subscriber _jack_disthandle_ST;
    ros::Subscriber _jack_disthandle_SA;
    ros::Publisher  _jack_disthandle_P;
    ros::Publisher  _jack_trilateration_P;

    /** **** CONSTRUCTOR **** */
    jackAPI(std::string name, int Nanchors);

    /** **** METHODS **** */
    // subscriber callback
    void ChatterCallbackT(const gtec_msgs::Ranging& msg);
    void ChatterCallbackA(const visualization_msgs::MarkerArray& msg);

    // cost function
    _Float64 Ji(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // cost function - gradient
    std::vector<_Float64> GJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // cost function - hessian
    std::vector<_Float64> HJi(std::vector<_Float64> p, std::vector<_Float64> A, _Float64 D);

    // Newton-Rhapson
    jackal_op::GradientDescent NewtonRaphson(std::vector<_Float64> p0, std::vector<_Float64> D, int Niter);

};