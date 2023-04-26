cmake_minimum_required(VERSION 3.0.2)
project(jackal_op)

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
  geometry_msgs
  gtec_msgs
  nav_msgs
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

## Specify additional locations of header files
## Your package locations should be listed before other locations
set(ALGLIBCPP_INCLUDE_DIR
/home/ros/workspace/stuff/alglib-cpp/src
)
set(LIBFUL_INCLUDE_DIR
src/libful
)
set(OPTIM_INCLUDE_DIR
/usr/local/include/optim/BaseMatrixOps/include/
/usr/local/include/optim/BaseMatrixOps/include/core
/usr/local/include/optim/BaseMatrixOps/include/extra
/usr/local/include/optim/BaseMatrixOps/include/misc
/usr/local/include/optim/BaseMatrixOps/include/stats
/usr/local/include/optim/constrained
/usr/local/include/optim/line_search
/usr/local/include/optim/misc
/usr/local/include/optim/stats
/usr/local/include/optim/unconstrained
/usr/local/include/optim/zeros
/usr/local/include/optim
)

# include
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${ALGLIBCPP_INCLUDE_DIR}
  ${OPTIM_INCLUDE_DIR}
  ${LIBFUL_INCLUDE_DIR}
)

## Declare a C++ library
set(ALGLIBCPP_SOURCES
  /home/ros/workspace/stuff/alglib-cpp/src/alglibinternal.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/alglibmisc.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/ap.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/dataanalysis.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/diffequations.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/fasttransforms.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/integration.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/interpolation.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/kernels_avx2.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/kernels_fma.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/kernels_sse2.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/linalg.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/optimization.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/solvers.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/specialfunctions.cpp
  /home/ros/workspace/stuff/alglib-cpp/src/statistics.cpp
)
add_library(alglib ${ALGLIBCPP_SOURCES})

set(LIBFUL_SOURCES
  src/libful/libful.cpp
)
add_library(libful ${LIBFUL_SOURCES})

## Declare a C++ executable
add_executable(jack_disthandle src/cpp/jack_disthandle.cpp)
add_executable(jack_disttrue src/cpp/jack_disttrue.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(jack_disthandle
${catkin_LIBRARIES} 
alglib
libful
armadillo
optim
)

target_link_libraries(jack_disttrue
${catkin_LIBRARIES} 
alglib
libful
armadillo
optim
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