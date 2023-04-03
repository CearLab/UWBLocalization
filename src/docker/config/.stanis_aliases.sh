#!/bin/bash

# Aliases for drone commands and utilities, available inside containers.
#
# Roberto Masocco <robmasocco@gmail.com>
#
# March 15, 2022

# Routine to convert an angle in degrees [-180° +180°] to radians [-PI +PI]
function degrad {
  if [[ $# -ne 1 ]] || [[ $1 -lt -180 ]] || [[ $1 -gt 180 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    degrad ANGLE"
    echo >&2 "ANGLE must be in degrees and in [-180° +180°]"
    return 1
  fi
  local OP
  local FIRST
  local SECOND
  local RES
  OP="scale=6;$1*3.14159265359/180.0"
  RES="$(bc <<<"$OP")"
  FIRST="${RES:0:1}"
  SECOND="${RES:1:1}"
  if [[ $FIRST == "." ]]; then
    RES="0${RES}"
  fi
  if [[ $FIRST == "-" ]] && [[ $SECOND == "." ]]; then
    RES="-0.${RES:2:6}"
  fi
  echo "$RES"
}

### SYSTEM COMMANDS ###
# Routine to check battery voltage
function batcheck {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic echo /fmu/battery_status/out | grep 'voltage_v:'
}

# Legacy routine to check Z estimation (symptom of internal filter failure)
function kal {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic echo /fmu/vehicle_local_position/out | grep 'z:'
}

# Routine to check PX4 Kalman filter status
function kalcheck {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic echo /fmu/estimator_status_flags/out
}

# Routine to build PX4 firmware (for development containers)
if ! echo "$BOARD" | grep -q 'up' && ! echo "$BOARD" | grep -q 'nx'; then
  function buildpx4 {
    cd /home/ros/workspace/thirdparty/PX4-Autopilot || return 1
    if [[ ! -d build/px4_fmu-v5_rtps ]] || [[ ! -d build/px4_sitl_rtps ]]; then
      echo "Building PX4 firmware..."
      sleep 3
      make px4_fmu-v5_rtps "-j$(nproc --all)"
      make px4_sitl_rtps "-j$(nproc --all)"
      make px4_sitl_rtps sitl_gazebo "-j$(nproc --all)"
    fi
    echo "Flashable binary in build/px4_fmu-v5_rtps/px4_fmu-v5_rtps.px4"
  }
fi

# Routine to build ORB_SLAM2 library
function buildorb2 {
  cd /home/ros/workspace/thirdparty/ORBSLAM2 || return 1
  echo "Building ORB_SLAM2..."
  sleep 3
  ./build.sh "-j$(nproc --all)" Release OFF OFF
}

# Routine to start the STIL PX4 executable
function px4 {
  export PX4_SIM_MODEL=iris
  /home/ros/workspace/thirdparty/PX4-Autopilot/build/px4_sitl_rtps/bin/px4 /home/ros/workspace/thirdparty/PX4-Autopilot/build/px4_sitl_rtps/etc -w /home/ros/workspace/thirdparty/PX4-Autopilot/build/px4_sitl_rtps/sitl_iris_0 -s /home/ros/workspace/thirdparty/PX4-Autopilot/build/px4_sitl_rtps/etc/init.d-posix/rcS
}

# Routine to kill all running Gazebo and PX4 instances
function px4cleanup {
	pkill -x px4
	pkill gzclient
	pkill gzserver
}

# Routine to start Gazebo simulation
function simstart {
  local OPTIND opt sim

  # Parse input arguments
  while getopts ":s" opt; do
    case "${opt}" in
      s)
        sim="y"
        ;;
      *)
        return 1
        ;;
    esac
  done
  shift $((OPTIND - 1))

  ros2init; source /home/ros/workspace/install/local_setup.zsh
  if [[ -n $sim ]]; then
    ros2 launch gazebo_simulation create_world_noagent.launch.py
  else
    ros2 launch gazebo_simulation create_world.launch.py
  fi
}

# Routine to manage RGB cameras
function rgbcam {
  function rgbcam_usage {
    echo >&2 "Usage:"
    echo >&2 "    rgbcam -b|-t|-f [-l BRIGHTNESS] [-e EXPOSURE] [-w WB_TEMPERATURE] [on|off]"
    echo >&2 "-b selects bottom camera"
    echo >&2 "-t selects tilted camera"
    echo >&2 "-f selects front D435i camera"
    echo >&2 "Parameters must be expressed as doubles"
  }

  local OPTIND opt cam brt exp wb_temp

  # Parse input arguments
  if [[ $# -eq 0 ]]; then
    rgbcam_usage
    return 1
  fi
  while getopts ":btfl:e:w:" opt; do
    case "${opt}" in
      b)
        cam="bottom"
        ;;
      t)
        cam="tilted"
        ;;
      f)
        cam="front"
        ;;
      l)
        brt="${OPTARG}"
        ;;
      e)
        exp="${OPTARG}"
        ;;
      w)
        wb_temp="${OPTARG}"
        ;;
      *)
        rgbcam_usage
        return 1
        ;;
    esac
  done
  shift $((OPTIND - 1))

  ros2init; source /home/ros/workspace/install/local_setup.zsh

  if [[ $cam == "bottom" ]]; then
    if [[ -n $brt ]]; then
      # Setting brightness
      ros2 param set /bottom_camera_driver brightness "$brt"
    fi
    if [[ -n $exp ]]; then
      # Setting exposure
      ros2 param set /bottom_camera_driver exposure "$exp"
    fi
    if [[ -n $wb_temp ]]; then
      # Setting WB temperature
      ros2 param set /bottom_camera_driver wb_temperature "$wb_temp"
    fi
    if [[ -n $1 ]]; then
      if [[ $1 == "on" ]]; then
        ros2 service call /bottom_camera_driver/enable_camera std_srvs/srv/SetBool "{data: true}"
      elif [[ $1 == "off" ]]; then
        ros2 service call /bottom_camera_driver/enable_camera std_srvs/srv/SetBool "{data: false}"
      else
        echo >&2 "Invalid operation"
        return 1
      fi
    fi
  elif [[ $cam == "tilted" ]]; then
    if [[ -n $brt ]]; then
      # Setting brightness
      ros2 param set /tilted_camera_driver brightness "$brt"
    fi
    if [[ -n $exp ]]; then
      # Setting exposure
      ros2 param set /tilted_camera_driver exposure "$exp"
    fi
    if [[ -n $wb_temp ]]; then
      # Setting WB temperature
      ros2 param set /tilted_camera_driver wb_temperature "$wb_temp"
    fi
    if [[ -n $1 ]]; then
      if [[ $1 == "on" ]]; then
        ros2 service call /tilted_camera_driver/enable_camera std_srvs/srv/SetBool "{data: true}"
      elif [[ $1 == "off" ]]; then
        ros2 service call /tilted_camera_driver/enable_camera std_srvs/srv/SetBool "{data: false}"
      else
        echo >&2 "Invalid operation"
        return 1
      fi
    fi
  elif [[ $cam == "front" ]]; then
    if [[ $1 == "on" ]]; then
      ros2 service call /perceptor/front_rgb_enable std_srvs/srv/SetBool "{data: true}"
    elif [[ $1 == "off" ]]; then
      ros2 service call /perceptor/front_rgb_enable std_srvs/srv/SetBool "{data: false}"
    fi
  else
    echo >&2 "Invalid camera"
    return 1
  fi
}

# Routine to manage target detectors
function detector {
  function detector_usage {
    echo >&2 "Usage:"
    echo >&2 "    detector -b|-t|-f on|off"
    echo >&2 "-b selects bottom detector"
    echo >&2 "-t selects tilted detector"
    echo >&2 "-f selects front detector"
    echo >&2 "Multiple detectors can be addressed in a same command"
  }

  local OPTIND opt bottom b_state tilted t_state front f_state

  # Parse input arguments
  if [[ $# -eq 0 ]]; then
    detector_usage
    return 1
  fi
  while getopts ":b:t:f:" opt; do
    case "${opt}" in
      b)
        bottom="y"
        b_state="${OPTARG}"
        ;;
      t)
        tilted="y"
        t_state="${OPTARG}"
        ;;
      f)
        front="y"
        f_state="${OPTARG}"
        ;;
      *)
        detector_usage
        return 1
        ;;
    esac
  done
  shift $((OPTIND - 1))

  ros2init; source /home/ros/workspace/install/local_setup.zsh

  # Manage the detectors
  if [[ -n $bottom ]]; then
    if [[ $b_state == "on" ]]; then
      ros2 service call /bottom_detector/enable std_srvs/srv/SetBool "{data: true}"
    elif [[ $b_state == "off" ]]; then
      ros2 service call /bottom_detector/enable std_srvs/srv/SetBool "{data: false}"
    else
      echo >&2 "Invalid operation"
      return 1
    fi
  fi
  if [[ -n $tilted ]]; then
    if [[ $t_state == "on" ]]; then
      ros2 service call /tilted_detector/enable std_srvs/srv/SetBool "{data: true}"
    elif [[ $t_state == "off" ]]; then
      ros2 service call /tilted_detector/enable std_srvs/srv/SetBool "{data: false}"
    else
      echo >&2 "Invalid operation"
      return 1
    fi
  fi
  if [[ -n $front ]]; then
    if [[ $f_state == "on" ]]; then
      ros2 service call /front_detector/enable std_srvs/srv/SetBool "{data: true}"
    elif [[ $f_state == "off" ]]; then
      ros2 service call /front_detector/enable std_srvs/srv/SetBool "{data: false}"
    else
      echo >&2 "Invalid operation"
      return 1
    fi
  fi
}

# Routine to start the best-effort video streams visualizer
function viewbe {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 run rqt_image_view rqt_image_view
}

# Routine to start the data logger
function blogger {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 run blogger blogger
}

# Routine to start the video stream logger
function tiktoker {
  # Parse input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    tiktoker CAMERA_TOPIC"
    echo >&2 "CAMERA_TOPIC must be the base topic name (i.e. the one without the transport)"
    return 1
  fi

  # Start the module specifying the camera topic to subscribe to
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 run blogger tiktoker --ros-args -p camera_topic:="$1"
}

# Routine to start the local screenshot utility
function stalker {
  function stalker_usage {
    echo >&2 "Usage:"
    echo >&2 "    stalker [-s]"
    echo >&2 "-s enables subscribers to Gazebo camera topics"
  }

  local OPTIND opt sim

  # Parse input arguments
  if [[ $# -gt 1 ]]; then
    stalker_usage
    return 1
  fi
  while getopts ":s" opt; do
    case "${opt}" in
      s)
        sim="y"
        ;;
      *)
        stalker_usage
        return 1
        ;;
    esac
  done
  shift $((OPTIND - 1))

  ros2init; source /home/ros/workspace/install/local_setup.zsh

  # Start the correct instance
  if [[ -z "$sim" ]]; then
    ros2 launch blogger stalker_app.launch.py
  else
    ros2 launch blogger stalker_app_sim.launch.py
  fi
}

# Routine to trigger the local screenshot utility
function stalk {
  # Parse input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    stalk true|false"
    echo >&2 "Good or bad take"
    return 1
  fi

  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /stalker/trigger std_srvs/srv/SetBool "{data: $1}"
}
### SYSTEM COMMANDS END ###

### FSM COMMANDS ###
# Routine to start the FSM
function start {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /fsm/start std_srvs/srv/Trigger "{}"
}

# Routine to send the mission sequence
function mission {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    mission TASKS"
    echo >&2 "TASKS must be formatted as: 'TYPE-SCORE-CELL TYPE-SCORE-CELL...'"
    return 1
  fi

  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /fsm/mission stanis_interfaces/srv/MissionSequence "{sequence: $1}"
}
### FSM COMMANDS END ###

### FLIGHT CONTROL COMMANDS ###
# Arms the drone
function arm {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/arm stanis_interfaces/action/Arm "{}"
}

# Disarms the drone
function disarm {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/disarm stanis_interfaces/action/Disarm "{}"
}

# Performs the landing procedure
function landing {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/landing stanis_interfaces/action/Landing "{}"
}

# Moves the drone to a target position
function reach {
  # Check input arguments
  if [[ $# -ne 5 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    reach X Y Z YAW RADIUS"
    echo >&2 "XYZ must be w.r.t. a NED reference frame, YAW must be in [-180° +180°], RADIUS is absolute."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/reach stanis_interfaces/action/Reach "{position: {x: $1, y: $2, z: $3}, heading: $(degrad $4), reach_radius: $5, stabilize: true}"
}

# Performs the takeoff procedure
function takeoff {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    takeoff ALTITUDE"
    echo >&2 "Altitude must be w.r.t. a NED reference frame."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/takeoff stanis_interfaces/action/Takeoff "{takeoff_altitude: $1}"
}

# Performs a turn to the desired heading
function turn {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    turn YAW"
    echo >&2 "YAW must be in [-180° +180°]."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /flight_control/turn stanis_interfaces/action/Turn "{yaw: $(degrad $1)}"
}

# Calls the FC Reset service
function fc-reset {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /flight_control/reset stanis_interfaces/srv/Reset "{}"
}

# Turns on the setpoints stream
function setpoints-on {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /flight_control/setpoints_switch stanis_interfaces/srv/SetpointsSwitch "{stream_active: true}"
}

# Turns off the setpoints stream
function setpoints-off {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /flight_control/setpoints_switch stanis_interfaces/srv/SetpointsSwitch "{stream_active: false}"
}

# Sends a new position setpoint to FC
function position {
  # Check input arguments
  if [[ $# -ne 4 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    position X Y Z YAW"
    echo >&2 "XYZ must be w.r.t. a NED reference frame, YAW must be in [-180° +180°]."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic pub -t 3 /flight_control/position_setpoint stanis_interfaces/msg/PositionSetpoint "{x_setpoint: $1, y_setpoint: $2, z_setpoint: $3, yaw_setpoint: $(degrad $4)}"
}

# Sends a new velocity setpoint to FC
function velocity {
  # Check input arguments
  if [[ $# -ne 5 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    velocity VX VY VZ YAW VYAW"
    echo >&2 "VX VY VZ must be w.r.t. a NED reference frame, YAW must be in [-180° +180°], VYAW must be in [-180°/s +180°/s]."
    echo >&2 "YAW may be NAN to control yaw speed by setting VYAW."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  if [[ $4 != "NAN" ]]; then
    ros2 topic pub -1 /flight_control/velocity_setpoint stanis_interfaces/msg/VelocitySetpoint "{vx_setpoint: $1, vy_setpoint: $2, vz_setpoint: $3, yaw_setpoint: $(degrad $4), vyaw_setpoint: $(degrad $5)}"
  else
    ros2 topic pub -1 /flight_control/velocity_setpoint stanis_interfaces/msg/VelocitySetpoint "{vx_setpoint: $1, vy_setpoint: $2, vz_setpoint: $3, yaw_setpoint: NAN, vyaw_setpoint: $(degrad $5)}"
  fi
}
### FLIGHT CONTROL COMMANDS END ###

### NAVIGATION STACK COMMANDS ###
# Requests a path to reach a target position
function find_path {
  # Check input arguments
  if [[ $# -ne 3 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    find_path X Y Z"
    echo >&2 "XYZ must be w.r.t. a NED reference frame"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /path_finder/find_path stanis_interfaces/action/FindPath "{target: {x: $1, y: $2, z: $3}}"
}

# Moves the drone to a target position
function navigate {
  # Check input arguments
  if [[ $# -ne 3 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    navigate X Y Z"
    echo >&2 "XYZ must be w.r.t. a NED reference frame."
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /navigator/navigate stanis_interfaces/action/Navigate "{target: {x: $1, y: $2, z: $3}}"
}

# Starts the exploration routine
function explore {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    explore SHITCAM"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /explorer/explore stanis_interfaces/action/Explore "{shitcam: $1}"
}
### NAVIGATION STACK COMMANDS END ###

### TARGET DETECTION COMMANDS ###
# Publishes a fake target message
function target {
  # Check input arguments
  if [[ $# -ne 2 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    target CAMERA_ID"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic pub -1 /targets stanis_interfaces/msg/Target "{camera: $1, id: $2}"
}
### TARGET DETECTION COMMANDS END ###

### TARGET TRACKING COMMANDS ###
# Routine to start tracking
function track {
  # Check input arguments
  if [[ $# -ne 2 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    track ID TEST"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /drone_roomba_tracker/tracking stanis_interfaces/action/RoombaTracking "{aruco_number: $1, test: $2}"
}

# Routine to terminate tracking
function trackstop {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /drone_roomba_tracker/stop std_srvs/srv/Trigger "{}"
}
### TARGET TRACKING COMMANDS END ###

### INSTAGRAMMER COMMANDS ###
# Routine to start a Reel
function reel {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    translate CELL"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 action send_goal -f /instagrammer/reel stanis_interfaces/action/Reel "{cell: $1}"
}
### INSTAGRAMMER COMMANDS END ###

### STREET VIEW COMMANDS ###
# Routine to publish an empty pointcloud
function view_map {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 topic pub -1 /perceptor/pointcloud sensor_msgs/msg/PointCloud2 "{}"
}
### STREET VIEW COMMANDS END ###

### TRECCANI COMMANDS ###
# Routine to query the map database
function translate {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    translate CELL"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /treccani/translate stanis_interfaces/srv/Translate "{cell: $1}"
}
### TRECCANI COMMANDS END ###

### MISSION PLANNER COMMANDS ###
# Routine to query the mission planner
function tenny {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    tenny SEQUENCE"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 service call /mission_planner/tenny stanis_interfaces/srv/CazzoFamo "{sequence: $1}"
}
### MISSION PLANNER COMMANDS END ###

### PRECISION LANDING COMMANDS ###
# Routine to start a PL test with the Treccani in Gazebo
function pltest {
  # Check input arguments
  if [[ $# -ne 1 ]]; then
    echo >&2 "Usage:"
    echo >&2 "    pltest CELL"
    return 1
  fi
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 run gazebo_simulation pl_tester.py "$1"
}
### PRECISION LANDING COMMANDS END ###

### MISSION COMMANDS ###
function nav {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup navigation_stack.launch.py
}

function insta {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup inspection.launch.py
}

function street {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch street_view sv_app.launch.py
}

function pr {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch perceptor pr_vslam_zedm.launch.py
}

function nx {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup nx.launch.py
}

function fs {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup flight_stack.launch.py
}

function cam {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup gcs_rob.launch.py
}

function fsm {
  ros2init; source /home/ros/workspace/install/local_setup.zsh
  ros2 launch stanis_bringup supervisors.launch.py
}
### MISSION COMMANDS END ###
