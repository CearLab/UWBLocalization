#!/bin/bash
# Remark: It's best if you attach vscode to the running container

# cd into dir
cd catkin_ws/src

# clone first repo - UWBJackalWorld
git clone https://github.com/AUVSL/UWB-Jackal-World.git

# install stuff - melodic
sudo apt-get install ros-melodic-jackal-simulator ros-melodic-jackal-desktop ros-melodic-jackal-navigation

# gtec repo
mkdir gtec
cd gtec

# clone UWB repos
git clone https://github.com/AUVSL/UWB-Gazebo-Plugin.git
git clone https://github.com/valentinbarral/rosmsgs

# build 
cd
cd workspace/catkin_ws
rospack profile