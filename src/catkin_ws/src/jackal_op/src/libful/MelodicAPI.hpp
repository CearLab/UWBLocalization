// define class with useful stuff

// non-ros include
#include <chrono>

// ros includes
#include "ros/ros.h"

// geometry msgs
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/TransformStamped.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/PoseStamped.h"

// visualization msgs
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"

// std msgs
#include "std_msgs/String.h"

// gtec msgs
#include <gtec_msgs/Ranging.h>

// nav msgs
#include <nav_msgs/Odometry.h>

// tf msgs
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

// sensor msgs
#include <sensor_msgs/Imu.h>

// user msgs
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
    _Float64 _dt;   // integration step
    std::vector<_Float64> _DT, _Dopt;  // distance vector on the measured tag + 1 dist used for opt
    std::vector<_Float64> _A, _p;   // matrix with anchors estimated position
    std::vector<_Float64> _xnew;    // observer state
    genAPI::Tag _Tag;

    jackal_op::MeshUWB _DTmsg; // message containing the distances measured (subscribed)
    jackal_op::GradientDescent _G;  // message with the optimization info
    gtec_msgs::Ranging _DTrueMsg;   // message with the synthetic true distances
    visualization_msgs::MarkerArray _AtrueMsg; // message with the synthetic true anchors
    nav_msgs::Odometry _Godom;      // message with the odometry
    sensor_msgs::Imu _Gimu;      // message with the IMU
    sensor_msgs::Imu _Gbias;      // message with the IMU

    // frame transformation
    geometry_msgs::TransformStamped _transformStamped; // actual transformation

    ros::Subscriber _jack_disthandle_ST;    // subscriber to tag distances
    ros::Subscriber _jack_disthandle_SA;    // subscriber to anchors positions
    ros::Subscriber _jack_disthandle_SIMU;  // subscriber to IMU measurements
    ros::Subscriber _jack_disthandle_SJump;  // subscriber to Jump Map
    ros::Publisher  _jack_disthandle_P;     // publisher on the distance wrapper
    ros::Publisher  _jack_disthandle_PA;     // publisher on the achor wrapper
    ros::Publisher  _jack_trilateration_P;  // publisher on the trilateration topic    
    ros::Publisher  _jack_odometry_P;       // publisher on odometry topic
    ros::Publisher  _jack_IMU_P;       // publisher on IMU topic
    ros::Publisher  _jack_Bias_P;       // publisher on IMU topic

    /** **** CONSTRUCTOR **** */
    jackAPI(std::string name, int Nanchors, int tagID, int rate);

    /** **** METHODS **** */
    // subscriber callback
    void ChatterCallbackT(const gtec_msgs::Ranging& msg);   // callback for the tag trilateration
    void ChatterCallbackA(const visualization_msgs::MarkerArray& msg);  // callback for the anchor positions
    void ChatterCallbackDtrue(const nav_msgs::Odometry& msg);   // callback for the true measurement handling
    void ChatterCallbackAtrue(const ros::TimerEvent& event);   // callback for the true anchors publishing
    void ChatterCallbackHybCont(const sensor_msgs::Imu& msg);   // callback for the continuous dynamics of the observer
    void ChatterCallbackHybJump(const nav_msgs::Odometry& msg);   // callback for the discrete dynamics of the observer

};