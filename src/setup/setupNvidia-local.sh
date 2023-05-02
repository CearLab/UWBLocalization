# steps to run gazebo and rviz in a container from a nvidia PC
## install drivers : https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html

## 1 - install docker-nvidia2 (https://gist.github.com/nathzi1505/d2aab27ff93a3a9d82dada1336c45041)
# starting from a working docker installation

# Nvidia Docker
sudo apt install curl
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list

sudo apt-get update && sudo apt-get install -y nvidia-container-toolkit
sudo systemctl restart docker

# Check Docker image
docker run --gpus all nvidia/cuda:10.0-base nvidia-smi

## 2 - adding the Nvidia runtime gpu capability 
# (https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/user-guide.html)

sudo mkdir -p /etc/systemd/system/docker.service.d

sudo tee /etc/systemd/system/docker.service.d/override.conf <<EOF
[Service]
ExecStart=
ExecStart=/usr/bin/dockerd --host=fd:// --add-runtime=nvidia=/usr/bin/nvidia-container-runtime
EOF

sudo systemctl daemon-reload \
  && sudo systemctl restart docker

# 3 - add in the dockerfile the following
# nvidia-container-runtime
# ENV NVIDIA_VISIBLE_DEVICES \
#     ${NVIDIA_VISIBLE_DEVICES:-all}
# ENV NVIDIA_DRIVER_CAPABILITIES \
#     ${NVIDIA_DRIVER_CAPABILITIES:+$NVIDIA_DRIVER_CAPABILITIES,}graphics
