cmake_minimum_required(VERSION 3.0.2)
project(UWB_driver)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 17) 

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  visualization_msgs
  message_generation
)

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
#add_message_files(
#  FILES
#)

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
  gtec_msgs
  visualization_msgs
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

## Specify additional locations of header files
## Your package locations should be listed before other locations
set(SERIAL_INCLUDE_DIR
/usr/local/include/
)

# include
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${SERIAL_INCLUDE_DIR}
)

## Declare a C++ executable

# UWB setup
#add_executable(UWB_setup src/cpp/UWB_setup.cpp)
#target_link_libraries(UWB_setup
#serial
#${catkin_LIBRARIES}
#)

## Add cmake target dependencies of the library
#add_dependencies(jack_disthandle jackal_op_generate_messages_cpp)

## Rename C++ executable without prefix

## Add cmake target dependencies of the executable

#############
## Install ##
#############

## Mark executable scripts (Python etc.) for installation
catkin_install_python(PROGRAMS src/python/UWB_setup.py src/python/UWB_read.py
                      DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
#target_link_libraries(UWB_setup ${catkin_LIBRARIES})


## Mark executables for installation

## Mark libraries for installation

## Mark cpp header files for installation

## Mark other files for installation (e.g. launch and bag files, etc.)

#install(TARGETS UWB_setup
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)

#############
## Testing ##
#############