#!/bin/bash

# Useful functions and stuff to manage ROS 2 from the Zsh shell.
#
# Roberto Masocco <robmasocco@gmail.com>
# Alessandro Tenaglia <alessandro.tenaglia42@gmail.com>
#
# January 27, 2022

# Initialize ROS 2 environment according to the Zsh shell.
# @param domain Domain ID to set initially; can be omitted.
ros2init() {
  if [[ $# -ne 0 ]]; then
    export ROS_DOMAIN_ID=$1
  fi
  export ROS_VERSION=2
  export ROS_PYTHON_VERSION=3
  export ROS_DISTRO=galactic

  if echo "$SHELL" | grep -q 'bash'; then
    source /opt/ros/$ROS_DISTRO/setup.bash
    source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash
  elif echo "$SHELL" | grep -q 'zsh'; then
    source /opt/ros/$ROS_DISTRO/setup.zsh
    source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.zsh
    eval "$(register-python-argcomplete3 ros2)"
  else
    source /opt/ros/$ROS_DISTRO/setup.sh
  fi

  # Search system libraries first to get Boost dependencies from system
  # NOTE: This won't fix CMake warnings, but will prevent the runtime loader
  #       from making mistakes.
  if echo "$USER" | grep -q 'nx'; then
    export LD_LIBRARY_PATH=/usr/lib/aarch64-linux-gnu:$LD_LIBRARY_PATH
  else
    export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu:$LD_LIBRARY_PATH
  fi
}

# Initializes a ROS 2 workspace; must be ran inside it.
ros2wsinit() {
  if [[ -z "$ROS_DISTRO" ]]; then
    echo >&2 "No ROS 2 installation sourced!"
    return 1
  fi
  sudo rosdep init
  rosdep update
  rosdep install -i --from-path src --rosdistro $ROS_DISTRO -y
}

# Alias for Gazebo that includes environment variables for HiDPI
alias gazebo='QT_AUTO_SCREEN_SCALE_FACTOR=0 QT_SCREEN_SCALE_FACTORS=[1.0] /usr/bin/gazebo'
