cmake_minimum_required(VERSION 3.0.2)
project(jackal_op)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  geometry_msgs
  gtec_msgs
  tf
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
add_message_files(
  FILES
  MeshUWB.msg
  GradientDescent.msg
)

## Generate services in the 'srv' folder
add_service_files(
  FILES
)

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
  gtec_msgs
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
set(ALGLIBCPP_INCLUDE_DIR
src/alglib-cpp/src
)
set(LIBFUL_INCLUDE_DIR
src/libful
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${LIBFUL_INCLUDE_DIR}
  ${ALGLIBCPP_INCLUDE_DIR}
)

## Declare a C++ library
set(ALGLIBCPP_SOURCES
  src/alglib-cpp/src/alglibinternal.cpp
  src/alglib-cpp/src/alglibmisc.cpp
  src/alglib-cpp/src/ap.cpp
  src/alglib-cpp/src/dataanalysis.cpp
  src/alglib-cpp/src/diffequations.cpp
  src/alglib-cpp/src/fasttransforms.cpp
  src/alglib-cpp/src/integration.cpp
  src/alglib-cpp/src/interpolation.cpp
  src/alglib-cpp/src/kernels_avx2.cpp
  src/alglib-cpp/src/kernels_fma.cpp
  src/alglib-cpp/src/kernels_sse2.cpp
  src/alglib-cpp/src/linalg.cpp
  src/alglib-cpp/src/optimization.cpp
  src/alglib-cpp/src/solvers.cpp
  src/alglib-cpp/src/specialfunctions.cpp
  src/alglib-cpp/src/statistics.cpp
)
set(LIBFUL_SOURCES
  src/libful/libful.cpp
)
add_library(alglib ${ALGLIBCPP_SOURCES})
add_library(libful ${LIBFUL_SOURCES})

## Declare a C++ executable
add_executable(jack_disthandle src/cpp/jack_disthandle.cpp)
#add_executable(jack_disthandle src/cpp/jack_disthandle_dummy.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(jack_disthandle
${catkin_LIBRARIES} 
alglib
libful
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