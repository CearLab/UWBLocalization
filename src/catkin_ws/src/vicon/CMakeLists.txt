cmake_minimum_required(VERSION 3.0.2)
project(vicon)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++14)
# set(CMAKE_CXX_FLAGS "-Wl,--rpath=/home/ros/glibc-2.29/build")
# set(CMAKE_CXX_FLAGS "-Wl,--dynamic-linker=/home/ros/glibc-2.29/build/lib/ld-2.29.so")
set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_INSTALL_RPATH "/home/ros/glibc-2.29/build/lib")

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf2_ros
  std_msgs
  geometry_msgs
  tf2_geometry_msgs
  nav_msgs
  message_filters
  message_generation
)

# install package
# set(THIRD_LIBRARY_PATH /home/ros/workspace/setup/lib/ViconAPI/F1/Release/Linux64/Source/bin/Debug)
# link_directories(${THIRD_LIBRARY_PATH})
set(VICON_LIBRARY_PATH /home/ros/workspace/setup/lib/ViconAPI/F1/Release/Linux64/Source/bin/Debug)
link_directories(${VICON_LIBRARY_PATH})

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

## Uncomment this if the package has a setup.py. This macro ensures
## modules and global scripts declared therein get installed
## See http://ros.org/doc/api/catkin/html/user_guide/setup_dot_py.html
# catkin_python_setup()

################################################
## Declare ROS messages, services and actions ##
################################################

## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
# )

## Generate services in the 'srv' folder
#add_service_files(
#  FILES
#)

## Generate actions in the 'action' folder
# add_action_files(
#   FILES
#   Action1
# )

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  nav_msgs
)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################


###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########
set(VICON_INCLUDE_DIR
/home/ros/workspace/setup/lib/ViconAPI/F1/Release/Linux64/Source/Vicon/CrossMarket/DataStream/ViconDataStreamSDK_CPP
)

# include
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${VICON_INCLUDE_DIR}
)


# Vicon
add_executable(jack_vicon src/cpp/jack_vicon.cpp)
target_link_libraries(jack_vicon
${catkin_LIBRARIES}
ViconDataStreamSDK_CPP
)

## Add cmake target dependencies of the library
#add_dependencies(jack_disthandle jackal_op_generate_messages_cpp)

## Rename C++ executable without prefix

## Add cmake target dependencies of the executable

#############
## Install ##
#############

## Mark executable scripts (Python etc.) for installation

## Mark executables for installation

## Mark libraries for installation

## Mark cpp header files for installation

## Mark other files for installation (e.g. launch and bag files, etc.)

#############
## Testing ##
#############
