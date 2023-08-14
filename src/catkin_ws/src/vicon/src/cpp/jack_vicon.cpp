// ros includes
#include "ros/ros.h"
#include <nav_msgs/Odometry.h>

// tf msgs
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include "geometry_msgs/TransformStamped.h"

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
  ROS_WARN("START");
  Output_GetVersion Output = MyClient.GetVersion();
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
  Output_GetSegmentGlobalRotationQuaternion OutputQuat;

  // publishers
  ros::Publisher ViconPub = np.advertise<nav_msgs::Odometry>("ground_truth/state", 1000);

  // msg
  nav_msgs::Odometry ViconMsg;

  // stuff
  bool isFramePresent;

  // init buffer and listener
  static tf2_ros::Buffer tfBuffer; // problem line
  tf2_ros::TransformListener tfListener(tfBuffer);
  geometry_msgs::TransformStamped Transform;

  // transforms
  tf2::Quaternion quatPos, quatRot, quatStart, quatEnd;
  double roll = 0.0;
  double pitch = 0.0; 
  double yaw = 0*(0.5*M_PI);
  tf2::Matrix3x3 RPos;
  tf2::Vector3 PosOld, PosNew, delta;
      
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
      OutputQuat = MyClient.GetSegmentGlobalRotationQuaternion(Name, Root);

      // check
      // ROS_WARN("TEST Frame: %s", Root.c_str());
      // ROS_WARN("TEST: %g %g %g", OutputTransl.Translation[0], OutputTransl.Translation[1], OutputTransl.Translation[2]);

      // publish
      ViconMsg.header.stamp = ros::Time::now();
      ViconMsg.header.frame_id = "world";
      ViconMsg.child_frame_id = "base_link";

      // position
      isFramePresent = (tfBuffer._frameExists("base_link") && tfBuffer._frameExists("vicon_link"));
      if (isFramePresent){
          Transform = tfBuffer.lookupTransform("vicon_link","base_link",ros::Time(0));
          // Transform = tfBuffer.lookupTransform("base_link","vicon_link",ros::Time(0));
      }
      quatPos.setW(Transform.transform.rotation.w);
      quatPos.setX(Transform.transform.rotation.x);
      quatPos.setY(Transform.transform.rotation.y);
      quatPos.setZ(Transform.transform.rotation.z);
      RPos.setRotation(quatPos);
      PosOld[0] = OutputTransl.Translation[0]/1000;
      PosOld[1] = OutputTransl.Translation[1]/1000;
      PosOld[2] = OutputTransl.Translation[2]/1000;
      delta[0] = Transform.transform.translation.x;
      delta[1] = Transform.transform.translation.y;
      delta[2] = Transform.transform.translation.z;
      PosNew = RPos*PosOld + delta;
      PosNew = PosOld;

      ViconMsg.pose.pose.position.x = PosNew[0];
      ViconMsg.pose.pose.position.y = PosNew[1];
      ViconMsg.pose.pose.position.z = PosNew[2];

      // orientation
      // get RPY
      quatRot.setRPY(roll, pitch, yaw);
      quatStart.setX(OutputQuat.Rotation[0]);
      quatStart.setY(OutputQuat.Rotation[1]);
      quatStart.setZ(OutputQuat.Rotation[2]);
      quatStart.setW(OutputQuat.Rotation[3]);
      quatEnd = quatStart*quatRot;

      ViconMsg.pose.pose.orientation.x = quatEnd.getX();
      ViconMsg.pose.pose.orientation.y = quatEnd.getY();
      ViconMsg.pose.pose.orientation.z = quatEnd.getZ();
      ViconMsg.pose.pose.orientation.w = quatEnd.getW();
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
