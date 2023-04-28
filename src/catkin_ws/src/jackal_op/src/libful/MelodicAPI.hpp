// define class with useful stuff

// ros includes
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "visualization_msgs/MarkerArray.h"
#include "std_msgs/String.h"
#include <gtec_msgs/Ranging.h>
#include <nav_msgs/Odometry.h>
#include <jackal_op/MeshUWB.h>
#include <jackal_op/GradientDescent.h>

// standard includes
#include "GeneralAPI.hpp"

// class for jackal rover
class jackAPI {

private:

    /** **** ATTRIBUTES **** */
    int _cnt;   // counter (DEBUG)
    std::string _name;  // class instance name
    ros::Time _begin;   // timer

public:

    /** **** ATTRIBUTES **** */
    int _Nanchors;  // number of anchors for a single mesh
    int _tagID; // ID of the tag read by the node
    int _GradientFlag;  // gradient based optimization
    std::vector<_Float64> _DT, _Dopt;  // distance vector on the measured tag + 1 dist used for opt
    std::vector<_Float64> _A, _p;   // matrix with anchors estimated position
    genAPI::Tag _Tag;

    jackal_op::MeshUWB _DTmsg; // message containing the distances measured (subscribed)
    jackal_op::GradientDescent _G;  // message with the optimization info
    gtec_msgs::Ranging _DTrueMsg;   // message with the synthetic true distances
    nav_msgs::Odometry _Godom;      // message with the odometry

    ros::Subscriber _jack_disthandle_ST;    // subscriber to tag distances
    ros::Subscriber _jack_disthandle_SA;    // subscriber to anchors positions
    ros::Publisher  _jack_disthandle_P;     // publisher on the distance wrapper
    ros::Publisher  _jack_trilateration_P;  // publisher on the trilateration topic    
    ros::Publisher  _jack_odometry_P;       // publisher on odometry topic    

    /** **** CONSTRUCTOR **** */
    jackAPI(std::string name, int Nanchors, int tagID);

    /** **** METHODS **** */
    // subscriber callback
    void ChatterCallbackT(const gtec_msgs::Ranging& msg);   // callback for the tag trilateration
    void ChatterCallbackA(const visualization_msgs::MarkerArray& msg);  // callback for the anchor positions
    void ChatterCallbackDtrue(const nav_msgs::Odometry& msg);   // callback for the true measurement handling

};