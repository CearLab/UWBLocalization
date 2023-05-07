#!/bin/bash
# Remark: It's best if you attach vscode to the running container

# check procedure at http://wiki.ros.org/melodic/Installation/Ubuntu

# add repo
# sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

# add keys - curl already installed
# curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

# update repo
sudo apt update

# install jackal stuff
sudo apt-get install ros-melodic-jackal-simulator --fix-missing
sudo apt-get install ros-melodic-jackal-desktop --fix-missing
sudo apt-get install ros-melodic-jackal-navigation --fix-missing

# install tf tutorials
# sudo apt-get install ros-melodic-ros-tutorials ros-melodic-geometry-tutorials ros-melodic-rviz ros-melodic-rosbash ros-melodic-rqt-tf-tree

# setup environment
# change with your shell (bash/sh/zsh)
sudo apt install python-pygments
echo "source /opt/ros/melodic/setup.zsh" >> ~/.zshrc
source ~/.zshrc

# useful stuff
sudo apt install python3-rosinstall-generator ros-melodic-rqt ros-melodic-rqt-common-plugins

# create catkin workspace
cd ~/workspace
#mkdir -p catkin_ws/src
#cd catkin_ws
#catkin_make
#source devel/setup.zsh  # change with your shell
echo $ROS_PACKAGE_PATH  # check the path

# set nano as editor 
export EDITOR='nano -w'

# NOTE FOR VSCODE: remebmer to add /opt/ros/noetic/include/ in include path

# install husky for tutorials
# sudo apt install ros-melodic-husky-desktop
# sudo apt-get install ros-melodic-husky-simulator

### ONLY AFTER PULLING TechnionProject ###
# install libs for optimization
sudo apt install libopenblas-dev liblapack-dev
cd setup/lib

### install alglib: https://www.alglib.net/download.php
tar -xf alglib-3.20.0.cpp.gpl.tgz
mv alglib-3.20.0.cpp.gpl.tgz alglib-cpp/

### install armadillo: https://arma.sourceforge.net/ ##
tar -xf armadillo-12.2.0.tar.xz 
mv armadillo-12.2.0.tar.xz armadillo-12.2.0/
#! now enter the armadillo version folder 
cd armadillo-12.2.0
# standard installation in /usr/lib
# to change directory see README in armadillo dir
cmake .
sudo make install
ls /usr/lib | grep arma 
export ARMA_INCLUDE_PATH=/usr/lib
cd ..

### install optim: https://optimlib.readthedocs.io/en/latest/
git clone --recurse-submodules git@github.com:kthohr/optim.git
#! cd to the optim folder
cd optim
./configure -i "/usr/local" -l arma -p
sudo make
sudo make install
ls /usr/local/lib | grep optim
cd ..

# add libs
echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib" >> ~/.zshrc
source ~/.zshrc

# just for safety
sudo apt update
sudo apt upgrade

# remember to update the submodules before building - outside docker if you need

# setup for the build
cd ~/workspace/catkin_ws
rospack profile

# IN THE JACKAL_OP CMAKELIST:
# FIRST BUILD THE MESSAGES ONLY
# THEN ALSO LIBFUL AND JACKAL_OP

# testing for the navigation
sudo apt install ros-melodic-roslint  
sudo apt install ros-melodic-sick-tim
sudo apt install ros-melodic-rqt-tf-tree