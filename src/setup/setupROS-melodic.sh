#!/bin/bash
# Remark: It's best if you attach vscode to the running container

# check procedure at http://wiki.ros.org/melodic/Installation/Ubuntu

# add repo
# sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'

# add keys - curl already installed
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -

# update repo
sudo apt update

# install jackal stuff
sudo apt-get install ros-melodic-jackal-simulator --fix-missing
sudo apt-get install ros-melodic-jackal-desktop --fix-missing

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
cd catkin_ws
#catkin_make
source devel/setup.zsh  # change with your shell
echo $ROS_PACKAGE_PATH  # check the path

# set nano as editor 
export EDITOR='nano -w'

# NOTE FOR VSCODE: remebmer to add /opt/ros/noetic/include/ in include path

# install husky for tutorials
sudo apt install ros-melodic-husky-desktop
sudo apt-get install ros-melodic-husky-simulator

### ONLY AFTER PULLING TechnionProject ###
# install libs for optimization
sudo apt install libopenblas-dev liblapack-dev
cd ~/workspace/catkin_ws/src/jackal_op/
#! now enter the armadillo version folder 
#! cd armadilloV.V.V
# standard installation in /usr/local
# to change directory see README in armadillo dir
cmake .
sudo make install
# install optim
#! cd to the optim folder
export ARMA_INCLUDE_PATH=/usr/lib
./configure -i "/usr/local" -l arma -p
sudo make
sudo make install

# add libs
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib
