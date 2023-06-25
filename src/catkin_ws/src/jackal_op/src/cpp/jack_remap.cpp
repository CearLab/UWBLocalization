#include "MelodicAPI.hpp"

// callback
void ChatterCallback(const nav_msgs::Odometry& msg); 

// main
int main(int argc, char** argv) {

  // init node
  ros::init(argc, argv, "jack_remap");
  ros::NodeHandle np;

  // Create a TransformListener
  tf2_ros::Buffer tfBuffer;
  tf2_ros::TransformListener tfListener(tfBuffer);

  // stuff
  int Nanchors = 0;
  int tagID = 5;
  int Ntags = 0;
  int rate = 5;
  std::string goalFrame = "odom";
  std::string currentTopic = "/odometry/filtered";
  nav_msgs::Odometry goalOdom;

  // set goal frame
  if (argc > 1){
      goalFrame = argv[1];
  }

  // set current topic
  if (argc > 2){
      currentTopic = argv[2];
  }

  // set rate
  if (argc > 3){
      std::string value_from_cl = argv[3];
      rate = atoi(value_from_cl.c_str());
  }

  // loop
  ros::Rate loop_rate(rate);

  // create class instance
  jackAPI jackNode = jackAPI("jackRemap", Nanchors, tagID, Ntags, rate);

  // subscriber
  jackNode._jack_disthandle_SA = np.subscribe(currentTopic, 1000, &jackAPI::ChatterCallbackRemap, &jackNode);
    
  // set the goal pose in the "goal" frame
  goalOdom.header.frame_id = goalFrame;
  goalOdom.child_frame_id = jackNode._Godom.child_frame_id;

  // publish
  jackNode._jack_disthandle_P = np.advertise<nav_msgs::Odometry>("/odometry/remap", 1000);

  // spin with loop rate
  while (ros::ok()) {
  
      //spin
      ros::spinOnce();

      // Perform the transformation
      geometry_msgs::TransformStamped transformStamped;
      try {

        // ROS_WARN("goalFrame: %s", goalOdom.header.frame_id.c_str());
        // ROS_WARN("startFrame: %s", jackNode._Godom.header.frame_id.c_str());
        transformStamped = tfBuffer.lookupTransform(goalOdom.header.frame_id, jackNode._Godom.header.frame_id, ros::Time(0));

        // Apply the transformation to the goal pose
        tf2::doTransform(jackNode._Godom.pose.pose, goalOdom.pose.pose, transformStamped);

        jackNode._jack_disthandle_P.publish(goalOdom);

      } catch (tf2::TransformException& ex) {

        ROS_WARN("%s", ex.what());

      }

      // sleep
      loop_rate.sleep();
  }

  return 0;
}
