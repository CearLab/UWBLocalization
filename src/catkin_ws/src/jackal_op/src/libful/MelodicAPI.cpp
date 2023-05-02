// class with utilities for jackal with UWB handling
#include "MelodicAPI.hpp"

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors, int tagID, int rate){

    // counters
    int i, j;

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
    _Tag.Nanchors = Nanchors;
    
    // counter
    _cnt = 0;

    // integration rate
    _dt = (float)1/rate;

    // observer state
    for (i=0;i<genAPI::stateDim;i++){
        _xnew.push_back(0.0);
    }
     

    // create transform
    if (_tagID == 0){
        _G.odom.child_frame_id = "rear_tag";
        _G.odom.header.frame_id = "base_link";      
    }
    else if (_tagID == 1){
        _G.odom.child_frame_id = "right_tag";
        _G.odom.header.frame_id = "base_link"; 
    }
    else if (_tagID == 2){
        _G.odom.child_frame_id = "left_tag";
        _G.odom.header.frame_id = "base_link";
    }
    else {
        _G.odom.child_frame_id = "imu_link";
        _G.odom.header.frame_id = "base_link";
    }

    // set covariance
    _G.odom.pose.covariance = 
    {
        0.2, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.2, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.2, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0 
    };
    _G.odom.twist.covariance = 
    {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0 
    };

    // init J, GJ, HJ
    _G.J = 0;
    for (i=0; i<3; i++) {
        _G.GJ.push_back(0.0);
    }
    for (i=0; i<9; i++) {
        _G.HJ.push_back(0.0);
    }
    
    // init p
    _p = {0.0, 0.0, 0.25};
    _Tag.p = {0.0, 0.0, 0.25};

    // init distance vectors
    for (i=0; i<_Nanchors; i++) {

        // init distances - class
        _DT.push_back(0.0);        
        _Dopt.push_back(0.0);
        _Tag.Dopt.push_back(0.0);        
        // init MeshUWB message        
        _DTmsg.D1.push_back(0.0);        
        _DTmsg.D2.push_back(0.0);
        _DTmsg.D3.push_back(0.0);
        _DTmsg.DTrue.push_back(0.0);
        
        // init Anchors position
        for (j=0; j<3; j++){
            _A.push_back(0.0);
            _Tag.A.push_back(0.0);
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
        }
        else if (msg.tagId == 1){
            _DTmsg.D2[msg.anchorId] = _DT[msg.anchorId];
        }
        else if (msg.tagId == 2){
            _DTmsg.D3[msg.anchorId] = _DT[msg.anchorId];
        }
        else {
            _DTmsg.DTrue[msg.anchorId] = _DT[msg.anchorId];
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

        // copy anchors
        _Tag.A = _A;

        //optimize
        int success = 0;
        auto t1 = std::chrono::high_resolution_clock::now();
        success = genAPI::OptimMin(p0, _Dopt, &_Tag, _GradientFlag);
        auto t2 = std::chrono::high_resolution_clock::now();

        /* Getting number of milliseconds as an integer. */
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        /* Getting number of milliseconds as a double. */
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;

        // info
        //ROS_WARN("Optim exec time: %g", (_Float64)ms_double.count());

        // fill messages
        // gradient normal stuff
        _G.A = _Tag.A;
        _G.p = _Tag.p;
        _G.J = _Tag.J;
        _G.GJ = _Tag.GJ;
        _G.header.stamp = _begin.now();

        // gradient odom
        _G.odom.header.stamp = _G.header.stamp;
        _G.odom.pose.pose.position.x = _G.p[0];
        _G.odom.pose.pose.position.y = _G.p[1];
        _G.odom.pose.pose.position.z = _G.p[2];

        // assign 
        _Godom = _G.odom;

        ROS_INFO("Trasl: %g %g %g", _transformStamped.transform.translation.x,
        _transformStamped.transform.translation.y,
        _transformStamped.transform.translation.z);
        ROS_INFO("Rot: %g %g %g %g", _transformStamped.transform.rotation.w,
        _transformStamped.transform.rotation.x,
        _transformStamped.transform.rotation.y,
        _transformStamped.transform.rotation.z);

        // transform
        _Godom.pose.pose.position.x = _G.p[0] + _transformStamped.transform.translation.x;
        _Godom.pose.pose.position.y = _G.p[1] + _transformStamped.transform.translation.y;
        _Godom.pose.pose.position.z = _G.p[2] + _transformStamped.transform.translation.z;

        // publish
        _jack_trilateration_P.publish(_G);
        _jack_odometry_P.publish(_Godom);

        ROS_INFO("Published gradient");
    }
    catch(...){
        ROS_INFO("Failed Optim + Transform");
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

    ROS_INFO("Trasl: %g %g %g", _transformStamped.transform.translation.x,
    _transformStamped.transform.translation.y,
    _transformStamped.transform.translation.z);
    ROS_INFO("Rot: %g %g %g %g", _transformStamped.transform.rotation.w,
    _transformStamped.transform.rotation.x,
    _transformStamped.transform.rotation.y,
    _transformStamped.transform.rotation.z);

    // transform position
    _Float64 x,y,z;
    x = msg.pose.pose.position.x + _transformStamped.transform.translation.x;
    y = msg.pose.pose.position.y + _transformStamped.transform.translation.y;
    z = msg.pose.pose.position.z + _transformStamped.transform.translation.z;

    // get true distances
    for (i=0;i<_Nanchors;i++){

        // get index
        idA = 3*i;  

        // compute true distance      
        _DT[i] = sqrt( pow((x -_A[idA]),2) + 
                          pow((y -_A[idA+1]),2) + 
                          pow((z -_A[idA+2]),2));

        // set other data in the messages
        _DTrueMsg.anchorId = i;
        _DTrueMsg.tagId = _tagID;
        _DTrueMsg.range = (int)(_DT[i]*1000);

        // publish on topic
        _jack_disthandle_P.publish(_DTrueMsg);
    }     

}

// subscriber callback - implements th jump map of the hybrid observer
void jackAPI::ChatterCallbackHybJump(const nav_msgs::Odometry& msg){

    // update the _xnew with the jump map
    std::vector<_Float64> xnow(genAPI::stateDim, 0.0);
    std::transform(xnow.begin(), xnow.end(), _xnew.begin(), xnow.begin(), std::plus<float>());

    // position
    _xnew[genAPI::pos_p[0]] = xnow[genAPI::pos_p[0]] + genAPI::theta[0] * (msg.pose.pose.position.x - xnow[genAPI::pos_p[0]]);
    _xnew[genAPI::pos_p[1]] = xnow[genAPI::pos_p[1]] + genAPI::theta[0] * (msg.pose.pose.position.y - xnow[genAPI::pos_p[1]]);
    _xnew[genAPI::pos_p[2]] = xnow[genAPI::pos_p[2]] + genAPI::theta[0] * (msg.pose.pose.position.z - xnow[genAPI::pos_p[2]]);

    // velocity
    _xnew[genAPI::pos_v[0]] = xnow[genAPI::pos_v[0]] + genAPI::theta[1] * (msg.pose.pose.position.x - xnow[genAPI::pos_p[0]] );
    _xnew[genAPI::pos_v[1]] = xnow[genAPI::pos_v[1]] + genAPI::theta[1] * (msg.pose.pose.position.y - xnow[genAPI::pos_p[1]] );
    _xnew[genAPI::pos_v[2]] = xnow[genAPI::pos_v[2]] + genAPI::theta[1] * (msg.pose.pose.position.z - xnow[genAPI::pos_p[2]] );

    // bias
    _xnew[genAPI::pos_b[0]] = xnow[genAPI::pos_b[0]] + genAPI::theta[2] * (msg.pose.pose.position.x - xnow[genAPI::pos_p[0]] );
    _xnew[genAPI::pos_b[1]] = xnow[genAPI::pos_b[1]] + genAPI::theta[2] * (msg.pose.pose.position.y - xnow[genAPI::pos_p[1]] );
    _xnew[genAPI::pos_b[2]] = xnow[genAPI::pos_b[2]] + genAPI::theta[2] * (msg.pose.pose.position.z - xnow[genAPI::pos_p[2]] );

    // acceleration
    _xnew[genAPI::pos_a[0]] = xnow[genAPI::pos_a[0]];
    _xnew[genAPI::pos_a[1]] = xnow[genAPI::pos_a[1]];
    _xnew[genAPI::pos_a[2]] = xnow[genAPI::pos_a[2]];

}

// subscriber callback - implements th jump map of the hybrid observer
void jackAPI::ChatterCallbackHybCont(const sensor_msgs::Imu& msg){

    // init IMU meas
    std::vector<_Float64> IMU(3, 0.0);
    IMU[0] = msg.linear_acceleration.x;
    IMU[1] = msg.linear_acceleration.y;
    IMU[2] = msg.linear_acceleration.z;

    //ROS_INFO("IMU meas: %g %g %g", IMU[0], IMU[1], IMU[2]);
    //ROS_INFO("dt: %g", _dt);

    // integrate
    _xnew = genAPI::odeEuler(_xnew, IMU, _dt);

    //ROS_INFO("Xnew: %g %g %g", _xnew[genAPI::pos_p[0]], _xnew[genAPI::pos_p[1]], _xnew[genAPI::pos_p[2]]);

    // fill message and publish - odometry
    _Godom.header = msg.header;
    _Godom.child_frame_id = msg.header.frame_id;

    // position
    _Godom.pose.pose.position.x = _xnew[genAPI::pos_p[0]];
    _Godom.pose.pose.position.y = _xnew[genAPI::pos_p[1]];
    _Godom.pose.pose.position.z = _xnew[genAPI::pos_p[2]];

    // velocity
    _Godom.twist.twist.linear.x = _xnew[genAPI::pos_v[0]];
    _Godom.twist.twist.linear.y = _xnew[genAPI::pos_v[1]];
    _Godom.twist.twist.linear.z = _xnew[genAPI::pos_v[2]];

    // publish
    _jack_odometry_P.publish(_Godom);

    // fill message and publish - IMU
    _Gimu.header = msg.header;
    
    // acceleration
    _Gimu.linear_acceleration.x = _xnew[genAPI::pos_a[0]];
    _Gimu.linear_acceleration.y = _xnew[genAPI::pos_a[1]];
    _Gimu.linear_acceleration.z = _xnew[genAPI::pos_a[2]];

    // publish
    _jack_IMU_P.publish(_Gimu);

    // fill message and publish - bias
    _Gbias.header = msg.header;
    
    // acceleration
    _Gbias.linear_acceleration.x = _xnew[genAPI::pos_b[0]];
    _Gbias.linear_acceleration.y = _xnew[genAPI::pos_b[1]];
    _Gbias.linear_acceleration.z = _xnew[genAPI::pos_b[2]];

    // publish
    _jack_Bias_P.publish(_Gbias);

}

