#include "MelodicAPI.hpp"

#include "DataStreamClient.h"
#include <sstream>

using namespace std;

// callback
void ChatterCallback(const nav_msgs::Odometry& msg); 

// main
int main(int argc, char** argv) {

  // init node
  ros::init(argc, argv, "jack_vicon");
  ros::NodeHandle np;

  // Create a TransformListener
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  // stuff
  int Nanchors = 0;
  int tagID = 5;
  int Ntags = 0;
  int rate = 100;
  
  // loop
  ros::Rate loop_rate(rate);

  // create class instance
  jackAPI jackNode = jackAPI("jackRemap", Nanchors, tagID, Ntags, rate);

  // publish
  jackNode._jack_disthandle_P = np.advertise<nav_msgs::Odometry>("/vicon", 1000);

  // Vicon class instance
  ViconDataStreamSDK::CPP::Client StackClient;

  // connect to Vicon stream
  ViconDataStreamSDK::CPP::Output_Connect Output = StackClient.Connect( "132.68.134.248" );
  ViconDataStreamSDK::CPP::Output_IsConnected Status;

  // spin with loop rate
  while (ros::ok()) {

      // check connection
      Status = StackClient.IsConnected();
      // ROS_WARN("Vicon connection status: %d", Status);
  
      //spin
      ros::spinOnce();

      // sleep
      loop_rate.sleep();
  }

  return 0;
}
