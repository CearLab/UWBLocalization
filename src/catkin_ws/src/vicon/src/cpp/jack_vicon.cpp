// ros includes
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>

#include "DataStreamClient.h"
#include <sstream>

// callback
void ChatterCallback(const nav_msgs::Odometry& msg); 

// main
int main(int argc, char** argv) {

  // init node
  ros::init(argc, argv, "jack_vicon");
  ros::NodeHandle np;

  int rate = 100;
  
  // loop
  ros::Rate loop_rate(rate);

  // Vicon class instance
  ViconDataStreamSDK::CPP::Client StackClient;

  // connect to Vicon stream
  ViconDataStreamSDK::CPP::Output_Connect Output = StackClient.Connect( "132.68.134.248" );
  ViconDataStreamSDK::CPP::Output_IsConnected Status;

  // spin with loop rate
  while (ros::ok()) {

      // check connection
      Status = StackClient.IsConnected();
      ROS_WARN("Vicon connection status: %d", Status.Connected);
  
      //spin
      ros::spinOnce();

      // sleep
      loop_rate.sleep();
  }

  return 0;
}
