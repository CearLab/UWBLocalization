#!/bin/bash

# Stanis project aliases.
#
# Roberto Masocco <robmasocco@gmail.com>
#
# May 16, 2022

# Routine to access the drone NX board
function ssh-nx {
  ssh -t nxdrone@10.0.0.3 "zsh -i -c 'attach-base'; zsh"
}

# Routine to access the drone Up2 board
function ssh-up {
  ssh -t updrone@10.0.0.4 "zsh -i -c 'attach-base'; zsh"
}

# Routine to access the GCS development container
function attach-gcs {
  docker exec -it $(docker ps -q -f "name=stanis-nvidia") zsh
}

# Routine to access the GCS development container
function attach-dev {
  docker exec -it $(docker ps -q -f "name=stanis-dev") zsh
}

# Routine to move and show the last reel
function view_reel {
  # Check input arguments
  if [[ $# -eq 0 ]]; then
    photo=($(ls -t "${HOME}/Documents/ISL/stanis/pics/tgt/" | head -1))
    open "${HOME}/Documents/ISL/stanis/pics/tgt/${photo}"
  else
    photo=($(ls -t "${HOME}/Documents/ISL/stanis/pics/raw/" | head -1))
    cp "${HOME}/Documents/ISL/stanis/pics/raw/${photo}" "${HOME}/Documents/ISL/stanis/pics/tgt/${photo}"
    open "${HOME}/Documents/ISL/stanis/pics/tgt/${photo}"
  fi
}
