# post installation steps

## CHECK THE DATE

# $ timedatectl --> should return the correct date. 
# IF NOT:
#	1) save the current /etc/apt/sources.list in /etc/apt/sources.list.old
#	2) create/edit /etc/apt/sources.list with only one line: deb mirror://mirrors.ubuntu.com/mirrors.txt bionic main
#	3)      $ sudo apt update
#	4)	$ sudo systemctl stop systemd-timesyncd
#	5)	$ sudo apt install ntpdate ntp
#	6)	$ sudo systemctl stop ntp
#	7)	$ sudo timedatectl set-timezone /Asia/Jerusalem
#	8)	$ sudo timedatectl set-ntp off
#	9)	$ sudo ntpdate time1.google.com	(if it does not work try other time servers. Search the web for ntp servers.)
#	10)	$ timedatectl --> now should be synchronized. If not, go back to step 9 and change server
#	11) edit /etc/ntp.conf and add as first the server you used to syncrhonize (search for line 'pool 0.pool.ntp.org' or similar)
#	12)	$ sudo systemctl enable ntp
#	13)	$ sudo systemctl restart ntp
#	14)	$ sudo systemctl restart systemd-timesyncd
#	15) reboot and check date (timedatectl)

#   NB: whenever you have wrong date run: $ sudo ntpdate time1.google.com

# silly thing, I like gedit
# $ sudo apt install gedit

## SETUP SSH SERVER ON STATIC IP
# $ sudo apt install openssh-server
# edit /etc/ssh/sshd_config with your preferred settings
# $ sudo systemctl restart sshd 
# now you can connect from ssh. 
# Suggestion: use Vscode and install remotely: C/C++, C/C++ Themes, Docker, Jupyter Keymap

## ADD SSH KEY
# $ ssh-keygen -t ed25519 (follow the prompt instructions. remember to store the key in /home/user/.ssh)
# $ eval $(ssh-agent -s)
# $ ssh-add ~/.ssh/keyname
# $ cat ~/.ssh/keyname.pub --> copy the output and add the key on your github.com account

## CLONE THE PROJECT REPO
# $ git clone git@github.com:fedeoli/TechnionProject.git
# $ git submodule init
# $ git submodule update --recursive
# If you have permission issues try to add the ssh key again, with the logout it could have been lost

## INSTALL DOCKER
# $ sudo apt update
# $ sudo apt install apt-transport-https ca-certificates curl software-properties-common
# $ sudo install -m 0755 -d /etc/apt/keyrings
# $ curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
# $ sudo chmod a+r /etc/apt/keyrings/docker.gpg
# $ echo \
#  "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
#  "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable" | \
#  sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
# This last command will add the repository to the sources.list directory
# $ sudo apt update (Check in the links at the beginning: there should be a docker link)
# $ sudo apt-get install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
# $ sudo docker run hello-world
# Now we add the user to the docker group. Run $ groups and read the groups your user has access to
# Now add the docker group
# $ sudo groupadd docker (if it is already present never mind)
# $ sudo usermod -aG docker $USER (add yuur user to docker group)
# Now reboot and run $ groups and check again 
# check that you can call docker without sudo
# $ docker run hello-world
# Now enable docker at startup
# $ sudo systemctl enable docker.service
# $ sudo systemctl enable containerd.service

## BUILD DOCKER IMAGE FOR BIONIC (18.04) WITH ROS-MELODIC
# The whole thing is pretty simple. In the src/docker folder there is a docker-compose.yml
# Each service of the .yml is linked to a Dockerfile where the image is built. 
# Starting from the base environment, you need to run a detached container, the image will build and tag autonomously:
# $ docker compose --file src/docker/docker-compose.yml up -d ros-melodic-base
# $ docker compose --file src/docker/docker-compose.yml up -d jackal-melodic-dev
# now you should have 2 images and 2 containers. Check with
# $ docker images
# $ docker ps -a
# from now on you will use the dev container.
# NB: if you want to instantiate a new container, just run docker compose for jackal-melodic-dev again. 
# NB: for nvidia jackal, check the jackal-melodic-nvidia service in the docker-compose.yml

## ATTACH TO CONTAINER AND BUILD PROJECT
# Suggestion: attach to running container from vscode (check online, it is like remote connection)
# If you do so, remember to install the extension as you did before for ssh
# Otherwise: $docker exec -it docker-jackal-melodic-dev-1 zsh
# if everything is fine you should run: $ whoami 
# and see 'ros' as output
# Now:
# $ sudo apt update
# $ sudo apt upgrade
# general jackal environment
# $ sudo apt-get install ros-melodic-jackal-simulator --fix-missing
# $ sudo apt-get install ros-melodic-jackal-desktop --fix-missing
# $ sudo apt-get install ros-melodic-jackal-navigation --fix-missing
# general python stuff
# $ sudo apt install python-pygments
# $ sudo apt install python3-rosinstall-generator ros-melodic-rqt ros-melodic-rqt-common-plugins
# add ros path to bash and zsh
# $ echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
# $ echo "source /opt/ros/melodic/setup.zsh" >> ~/.zshrc
# $ source ~/.zshrc
# Now, the catkin is already there, it is just not built
# Check the path
# $ cd ~/workspace
# $ echo $ROS_PACKAGE_PATH
# set nano as editor 
# $ export EDITOR='nano -w'
# Now we start with the project build. 
# First, install optimization general libraries
# $ sudo apt install libopenblas-dev liblapack-dev
# Now let's make and go in the setup/lib folder and start building stuff
# $ mkdir setup/lib
# $ cd setup/lib
# ALGLIB: general optimization (check link: 30/05/2023)
# $ wget https://www.alglib.net/translator/re/alglib-4.00.0.cpp.gpl.tgz
# $ tar -xf alglib-4.00.0.cpp.gpl.tgz
# $ rm alglib-4.00.0.cpp.gpl.tgz
# ARMADILLO: general matrix computations and optimization (check link: 30/05/2023)
# $ wget https://sourceforge.net/projects/arma/files/armadillo-12.4.0.tar.xz
# $ tar -xf armadillo-12.4.0.tar.xz
# $ rm armadillo-12.4.0.tar.xz
# $ cd armadillo-12.4.0
# standard installation in /usr/lib
# $ cmake .
# $ sudo make install
# check installation
# $ ls /usr/lib | grep arma 
# export path
# $ export ARMA_INCLUDE_PATH=/usr/lib
# $ cd ..
# ARMADILLO: general matrix computations and optimization (check link: 30/05/2023 - following README)
# $ git clone --recurse-submodules git@github.com:kthohr/optim.git
# $ cd optim
# $ ./configure -i "/usr/local" -l arma -p
# $ sudo make
# $ sudo make install
# check installation
# $ ls /usr/local/lib | grep optim
# $ cd ..
# CERES: nonlinear optimization (check link: 30/05/2023 - following install instructions)
# $ sudo apt-get install libgoogle-glog-dev libgflags-dev
# $ sudo apt-get install libatlas-base-dev
# $ sudo apt-get install libeigen3-dev
# $ sudo apt-get install libsuitesparse-dev
# $ wget http://ceres-solver.org/ceres-solver-2.1.0.tar.gz
# $ tar -xf ceres-solver-2.1.0.tar.gz
# $ rm ceres-solver-2.1.0.tar.gz
# $ sudo mkdir ceres-bin
# $ cd ceres-bin
# $ sudo cmake -DBUILD_SHARED_LIBS='ON' ../ceres-solver-2.1.0
# $ sudo make (very slow, check RAM because could be an issue)
# if you can't compile the library, compile on your local pc and copy:
# the .so files in /usr/local/lib
# the .h files in /usr/local/include/ceres
# the .cmake files in /usr/local/lib/cmake/Ceres
# this is what I've done on jack19, I could not compile ceres, too much RAM required
#
# cd ~/workspace
# Now let's add the libraries to path
# $ echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib" >> ~/.zshrc
# $ echo "export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/lib:/usr/local/lib" >> ~/.bashrc
# $ source ~/.zshrc (we use zsh)
# $ sudo apt update
# $ sudo apt upgrade
#
# add last ros packages 
# $ sudo apt install ros-melodic-roslint  
# $ sudo apt install ros-melodic-sick-tim
# $ sudo apt install ros-melodic-rqt-tf-tree
# $ sudo apt install ros-melodic-roscpp-tutorials
# $ sudo apt install ros-melodic-tf2-web-republisher
#
# now get ready for the catkin build
# $ cd ~/workspace/catkin_ws
# $ rospack profile
# 
# Now we build the project
# rename the following fils: 
# catkin_ws/src/jackal_op/package.xml catkin_ws/src/jackal_op/package.xml.old
# catkin_ws/src/jackal_custom/package.xml catkin_ws/src/jackal_custom/package.xml.old
# catkin_ws/src/UWB_driver/package.xml catkin_ws/src/ackal_op/package.xml.old
# catkin_ws/src/robot_localization_custom/package.xml catkin_ws/src/robot_localization_custom/package.xml.old
# now run 
# $ catkin_make
# this will build the gtec messages which are needed in the following packages
# now rename these files:
# catkin_ws/src/jackal_custom/package.xml.old catkin_ws/src/jackal_custom/package.xml
# catkin_ws/src/UWB_driver/package.xml.old catkin_ws/src/ackal_op/package.xml
# now run 
# $ catkin_make
# this will build the launch files and the UWB drivers to read DWM1001 from serial
# now rename these files:
# catkin_ws/src/jackal_op/package.xml.old catkin_ws/src/jackal_op/package.xml
# now go in catkin_ws/src/jackal_op/CmakeLists.txt and comment all the cpp executables and GeneralAPI and MelodicAPI
# $ catkin_make (this build the messages)
# now you can decomment everything and compile the whole jackal_op
