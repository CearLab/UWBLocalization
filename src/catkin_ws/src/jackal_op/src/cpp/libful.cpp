// define class with useful stuff

// standard includes
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>

// ros includes
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "std_msgs/String.h"
#include <gtec_msgs/Ranging.h>
#include <jackal_op/MeshUWB.h>

class jackAPI {

private:
    std::string name;
    ros::NodeHandle n;
    int Nanchors = 4;
    std::vector<_Float64> DT1, DT2;
    std::vector<int32_t> DT1_int, DT2_int;

public:

    /** **** ATTRIBUTES **** */
    ros::Subscriber jack_disthandle_S;
    ros::Publisher  jack_disthandle_T1_pub;
    ros::Publisher  jack_disthandle_T2_pub;

    /** **** CONSTRUCTOR **** */
    // constructor
    jackAPI(std::string name, int Nanchors){

        // set name
        this->name = name;

        // set mesh dimension
        this->Nanchors = Nanchors;

        // init distance vectors
        for (int i=0; i<Nanchors; i++) {
            this->DT1[i] = 0.0;
            this->DT2[i] = 0.0;
            this->DT1_int[i] = 0;
            this->DT2_int[i] = 0;
        }
    }

    // subscriber callback
    void chatterCallback(const gtec_msgs::Ranging::ConstPtr& msg) {

        // store distances in the vectors
        int i = msg.px->anchorId;

    }
};