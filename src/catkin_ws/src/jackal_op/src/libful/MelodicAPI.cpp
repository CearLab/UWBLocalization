// class with utilities for jackal with UWB handling
#include "MelodicAPI.hpp"

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors, int tagID){

    // init timer
    _begin = ros::Time::now();

    // set name
    _name = name;

    // set tagID
    _tagID = tagID;

    // set gradient flag
    _GradientFlag = 0;

    // set mesh dimension
    _Nanchors = Nanchors;
    _Tag->Nanchors = Nanchors;
    
    // counter
    _cnt = 0;

    // init J, GJ, HJ
    _G.J = 0;
    for (int i=0; i<3; i++) {
        _G.GJ.push_back(0.0);
    }
    for (int i=0; i<9; i++) {
        _G.HJ.push_back(0.0);
    }

    // init p
    _p = {0.0, 0.0, 0.25};
    _Tag->p = {0.0, 0.0, 0.25};

    // init distance vectors
    for (int i=0; i<_Nanchors; i++) {

        // init distances - class
        _DT.push_back(0.0);        
        _Dopt.push_back(0.0);
        _Tag->Dopt.push_back(0.0);

        // init MeshUWB message
        _DTmsg.D1.push_back(0.0);
        _DTmsg.D2.push_back(0.0);
        _DTmsg.D3.push_back(0.0);
        _DTmsg.DTrue.push_back(0.0);

        // init Anchors position
        for (int j=0; j<3; j++){
            _A.push_back(0.0);
            _Tag->A.push_back(0.0);
        }
    }

    //ROS_INFO("Consructor: ok");

}

/** **** METHODS **** */

// subscriber callback - used in the trilateration
void jackAPI::ChatterCallbackT(const gtec_msgs::Ranging& msg) {

    std::vector<_Float64> p0(3, 0.0);

    // store distances in the vectors
    ROS_INFO("AnchorID: %d", msg.anchorId);
    ROS_INFO("TagID: %d", msg.tagId);
    try {

        // save distance read from tag
        _DT[msg.anchorId] = (double)msg.range/1000;

        // populate correct tag in the UWB message
        if (msg.tagId == 0){            
            _DTmsg.D1[msg.anchorId] = _DT[msg.anchorId];   
            _Godom.child_frame_id = "tagrear";
            _Godom.header.frame_id = "base_link";         
        }
        else if (msg.tagId == 1){
            _DTmsg.D2[msg.anchorId] = _DT[msg.anchorId];
        }
        else if (msg.tagId == 2){
            _DTmsg.D3[msg.anchorId] = _DT[msg.anchorId];
        }
        else {
            _DTmsg.DTrue[msg.anchorId] = _DT[msg.anchorId];
            _Godom.child_frame_id = "base_link";
            _Godom.header.frame_id = "odom";
        }
    }
    catch(...){
        ROS_INFO("WRONG tag ID");
    }

    // set distance used to optimize
    if (msg.tagId == _tagID){
        _Dopt[msg.anchorId] = _DT[msg.anchorId];
    }
        
    //_get time
    _DTmsg.header.stamp = _begin.now();

    // publish the distance wrapper
    _jack_disthandle_P.publish(_DTmsg);

    ROS_INFO("Published distances");

    // call newton raphson
    try {

        //optimize
        int success = 0;
        success = genAPI::OptimMin(p0, _Dopt, _Tag, _GradientFlag);

        // get time
        _G.A = _Tag->A;
        _G.p = _Tag->p;
        _G.J = _Tag->J;
        _G.GJ = _Tag->GJ;
        _G.header.stamp = _begin.now();
        _G.odom.header.stamp = _G.header.stamp;
        _Godom.header.stamp = _G.odom.header.stamp;
        _Godom.pose.pose.position.x = _G.odom.pose.pose.position.x;
        _Godom.pose.pose.position.y = _G.odom.pose.pose.position.y;
        _Godom.pose.pose.position.z = _G.odom.pose.pose.position.z;

        // publish
        _jack_trilateration_P.publish(_G);
        _jack_odometry_P.publish(_Godom);

        ROS_INFO("Published gradient");
    }
    catch(...){
        ROS_INFO("Failed gradient");
    }
    
    // DEBUG
    _cnt++;

}

// subscriber callback - used to get the position of the anchors
void jackAPI::ChatterCallbackA(const visualization_msgs::MarkerArray& msg) {

    // init
    int id = 0;

    // store anchors positions
    for (int i=0;i<_Nanchors;i++){

        id = (i)*3;
        _A[id] = msg.markers[i].pose.position.x;
        _A[id+1] = msg.markers[i].pose.position.y;
        _A[id+2] = msg.markers[i].pose.position.z;

    }    

    ROS_INFO("Anchors received");

}

// subscriber callback - used to create synthetic true distances from ptrue
void jackAPI::ChatterCallbackDtrue(const nav_msgs::Odometry& msg){

    // define position
    std::vector<_Float64> ptrue(3,0.0);

    // init general stuff
    int i, idA;

    // init useless fields in MeshUWB
    _DTrueMsg.seq = 0;
    _DTrueMsg.rss = 0;
    _DTrueMsg.errorEstimation = 0;

    // get true distances
    for (i=0;i<_Nanchors;i++){

        // get index
        idA = 3*i;  

        // compute true distance      
        _DT[i] = sqrt( pow((msg.pose.pose.position.x -_A[idA]),2) + 
                          pow((msg.pose.pose.position.y -_A[idA+1]),2) + 
                          pow((msg.pose.pose.position.z -_A[idA+2]),2));

        // set other data in the messages
        _DTrueMsg.anchorId = i;
        _DTrueMsg.tagId = 7;    // id = 7 is the one identified with true dist
        _DTrueMsg.range = (int)(_DT[i]*1000);

        // info 
        // ROS_INFO("Tag %d Dtrue %d : %g", _DTrueMsg.tagId, _DTrueMsg.anchorId, _DTrue[i]);

        // publish on topic
        _jack_disthandle_P.publish(_DTrueMsg);
    }     

}
