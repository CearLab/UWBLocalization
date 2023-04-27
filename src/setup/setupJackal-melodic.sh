#!/bin/bash
# Remark: It's best if you attach vscode to the running container

# install stuff - melodic
sudo apt-get install ros-melodic-jackal-simulator ros-melodic-jackal-desktop ros-melodic-jackal-navigation

# build 
cd
cd ~/workspace/catkin_ws
rospack profile