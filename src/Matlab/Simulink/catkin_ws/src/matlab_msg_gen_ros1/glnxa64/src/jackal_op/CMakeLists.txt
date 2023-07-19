cmake_minimum_required(VERSION 3.9)
project(jackal_op)
set(CMAKE_VERBOSE_MAKEFILE ON)
# Set CMAKE_BUILD_TYPE
set(CMAKE_BUILD_TYPE Release)
# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
if(ALIAS_ROS1_CLASS_LOADER)
    add_definitions(-Dclass_loader=ros1_class_loader)
endif()
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  geometry_msgs
  message_generation
)
## System dependencies are found with CMake''s conventions
################################################
## Declare ROS messages, services and actions ##
################################################
add_message_files(
    FILES
    GradientDescent.msg
    MeshUWB.msg
    MeshUWBCentral.msg
    TransformArray.msg
)
## Generate added messages, services and actions with any dependencies listed here
generate_messages(
  DEPENDENCIES
  std_msgs
  geometry_msgs
  std_msgs
)
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
  CATKIN_DEPENDS
  message_runtime
  message_runtime
  geometry_msgs
  roscpp
  std_msgs
  INCLUDE_DIRS include
)
###########
## Build ##
###########
## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  include
  ${PROJECT_SOURCE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${catkin_INCLUDE_DIRS}
 "/opt/matlab/R2023a/extern/include"
 "/opt/matlab/R2023a/extern/include/MatlabDataArray"
 "/opt/matlab/R2023a/toolbox/ros/include/ros1"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/include"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/include/class_loader"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/console_bridge/include"
 "/opt/matlab/R2023a/toolbox/ros/mlroscpp/custom_messages/include"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/bzip2/include"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lz4/include"
 "/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/boost/include"
  "include/jackal_op"
)
set (CMAKE_SKIP_BUILD_RPATH false)
set (CMAKE_BUILD_WITH_INSTALL_RPATH true)
set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
set (CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
## Get list of .c files in project source directory
file(GLOB ${PROJECT_NAME}_C_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.c)
## Get list of .cpp files in project source directory
file(GLOB ${PROJECT_NAME}_CPP_SOURCES RELATIVE ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/*.cpp)
link_directories("/opt/matlab/R2023a/extern/bin/glnxa64")
link_directories("/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/console_bridge/lib")
link_directories("/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib")
link_directories("/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/boost/lib")
# Declare library
add_library(
    jackal_op_matlab 
    SHARED
    src/jackal_op_GradientDescent_message.cpp
    src/jackal_op_MeshUWB_message.cpp
    src/jackal_op_MeshUWBCentral_message.cpp
    src/jackal_op_TransformArray_message.cpp
)
target_include_directories(jackal_op_matlab PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#target_compile_options(jackal_op_matlab PUBLIC $<$<OR:$<COMPILE_LANGUAGE:CXX>,$<COMPILE_LANGUAGE:C>>: -Wall -Wextra -Wpedantic>)
endif()
target_link_libraries( jackal_op_matlab
	"/opt/matlab/R2023a/extern/bin/glnxa64/libMatlabDataArray.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/console_bridge/lib/libconsole_bridge.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libros1_class_loader.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/librosconsole.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libroscpp.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libroscpp_serialization.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/librostime.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/librosbag_storage.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libroslz4.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libtopic_tools.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libmatlab_rosbag.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/lib/libactionlib.so"
	"/opt/matlab/R2023a/sys/ros1/glnxa64/ros1/boost/lib/libmwboost_thread.so"
	${Boost_LIBRARIES}
	${CMAKE_DL_LIBS}
	)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
add_dependencies(
  jackal_op_matlab
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)
# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(jackal_op_matlab PRIVATE "JACKAL_OP_BUILDING_LIBRARY")
install(
  DIRECTORY include/
  DESTINATION include
)
install(
  TARGETS jackal_op_matlab
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)
install (DIRECTORY m/ DESTINATION m/ FILES_MATCHING PATTERN "*.m")
foreach(file_i ${CUDA_BINS})
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CATKIN_DEVEL_PREFIX}/codegen/exe//${file_i}
				   )
add_custom_command(
                   TARGET 
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND}
                   ARGS -E copy ${PROJECT_SOURCE_DIR}/src/${file_i} ${CATKIN_DEVEL_PREFIX}/_ert_rtw/${file_i}
				   )
endforeach(file_i)
# Generated on Thu Jul 06 16:54:05 2023
