// ros includes
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>

#include "DataStreamClient.h"
#include <sstream>

using namespace ViconDataStreamSDK::CPP;

// callback
void ChatterCallback(const nav_msgs::Odometry& msg); 

// main
int main(int argc, char** argv) {

  // init node
  ros::init(argc, argv, "jack_vicon");
  ros::NodeHandle np;
  
  // loop
  int rate = 100;
  ros::Rate loop_rate(rate);

  // Vicon class instance
  Client MyClient;

  // vicon setup
  bool bFetch = false;
  bool bReadCentroids = false;

  // connect to Vicon stream
  const Output_Connect ConnectResult = MyClient.Connect( "132.68.134.248" );
  const bool ok = (ConnectResult.Result == Result::Success );
  Output_IsConnected Status;

  // setup
  MyClient.SetConnectionTimeout(1000);

  // check connection
  if ( !ok )
  {
    ROS_WARN("Warning - connect failed... ");
    switch (ConnectResult.Result)
    {
    case Result::ClientAlreadyConnected:
      ROS_WARN("Client Already Connected");
      break;
    case Result::InvalidHostName:
      ROS_WARN("Invalid Host Name");
      break;
    case Result::ClientConnectionFailed:
      ROS_WARN("Client Connection Failed");
      break;
    default:
      ROS_WARN("Unrecognized Error: %d", ConnectResult.Result);
      break;
    }
  }
  else {
    ROS_WARN("Vicon connected!");
  }

  // enable data
  Output_EnableSegmentData OutputSegmentData = MyClient.EnableSegmentData();
  Output_EnableMarkerData OutputMarkerData = MyClient.EnableMarkerData();
  Output_EnableCentroidData OutputCentroidData = MyClient.EnableCentroidData();

  // set reception
  MyClient.SetBufferSize(5);

  // set stream mode
  MyClient.SetStreamMode( ViconDataStreamSDK::CPP::StreamMode::ClientPull );

  // set reference frame
  Output_GetAxisMapping OutputAxisMapping = MyClient.GetAxisMapping();

  // frames attributes
  Output_GetFrame OutputFrame;
  Output_GetFrameNumber OutputFrameNumber;
  Output_GetTimecode OutputTimeCode;
  Output_GetFrameRate OutputFrameRate;

  // subjects attributes
  Output_GetSubjectCount OutputSubjectCount;
  Output_GetSubjectName OutputSubjectName;
  Output_GetSubjectRootSegmentName OutputRootSegmentName;
  std::string Name, Root;

  // translation
  Output_GetSegmentGlobalTranslation OutputTransl;

  // publishers
  ros::Publisher ViconPub = np.advertise<nav_msgs::Odometry>("ground_truth/state", 1000);

  // msg
  nav_msgs::Odometry ViconMsg;

  // spin with loop rate
  while (ros::ok()) {

      // get frame
      OutputFrame = MyClient.GetFrame();

      // get frame number
      OutputFrameNumber = MyClient.GetFrameNumber();

      // get time code
      OutputTimeCode = MyClient.GetTimecode();

      // frame
      OutputFrameRate = MyClient.GetFrameRate();

      // subject count and name of the first
      OutputSubjectCount = MyClient.GetSubjectCount();
      OutputSubjectName = MyClient.GetSubjectName(0);
      Name = OutputSubjectName.SubjectName;
      OutputRootSegmentName = MyClient.GetSubjectRootSegmentName(Name);
      Root = OutputRootSegmentName.SegmentName;

      // translation
      OutputTransl =  MyClient.GetSegmentGlobalTranslation(Name, Root);

      // check
      // ROS_WARN("TEST Frame: %s", Root.c_str());
      // ROS_WARN("TEST: %g %g %g", OutputTransl.Translation[0], OutputTransl.Translation[1], OutputTransl.Translation[2]);

      // publish
      ViconMsg.header.stamp = ros::Time::now();
      ViconMsg.header.frame_id = "world";
      ViconMsg.child_frame_id = "base_link";
      ViconMsg.pose.pose.position.x = OutputTransl.Translation[0]/1000;
      ViconMsg.pose.pose.position.y = OutputTransl.Translation[1]/1000;
      ViconMsg.pose.pose.position.z = OutputTransl.Translation[2]/1000;
      ViconPub.publish(ViconMsg);

      //spin
      ros::spinOnce();

      // sleep
      loop_rate.sleep();
  }

  // disconnect
  MyClient.Disconnect();

  return 0;
}
