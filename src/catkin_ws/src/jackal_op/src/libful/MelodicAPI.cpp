// class with utilities for jackal with UWB handling
#include "MelodicAPI.hpp"

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors, int tagID, int Ntags, std::vector<_Float64> TagDists, int rate) 
: _gen(std::random_device{}()), _distribution(0.0,0.0){

    // counters
    int i, j, k;

    // empty messages
    visualization_msgs::Marker zeroMark;

    // init timer
    _begin = ros::Time::now();

    // set name
    _name = name;

    // set tagID
    _tagID = tagID;

    ROS_WARN("ID init: %d", _tagID);
    
    // dimensions of mesh
    _Nanchors = Nanchors;
    _Ntags = Ntags;
    _Npairs = 0;
    //_Npairs = (int)(0*0.25*_Ntags*(_Ntags-1));

    // push back TagSet
    genAPI::Tag TagZero = genAPI::TagInit(Nanchors);
    for (i=0; i<_Ntags; i++){
        _TagSet.Tags.push_back(TagZero);
    }
    _TagSet.CurrPair.push_back(tagID);

    // push back transformations
    geometry_msgs::TransformStamped TransZero;
    // use it for pushbacks
    for (i=0; i<_Ntags; i++){
        _transformStamped.transforms.push_back(TransZero);
    }

    // setup Tag set
    _TagSet.Ntags =_Ntags;
    for (i=0; i<_Ntags; i++){
        _TagSet.Tags[i].Nanchors = _Nanchors;
    }
    _TagSet.TagDists = TagDists;
    _TagSet.Npairs = _Npairs;
    _TagSet.Nanchors = _Nanchors;
    
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
        _Godom.child_frame_id = "rear_tag";
        _Godom.header.frame_id = "base_link";      
    }
    else if (_tagID == 1){
        _Godom.child_frame_id = "right_tag";
        _Godom.header.frame_id = "base_link"; 
    }
    else if (_tagID == 2){
        _Godom.child_frame_id = "left_tag";
        _Godom.header.frame_id = "base_link";
    }
    else {
        _Godom.child_frame_id = "imu_link";
        _Godom.header.frame_id = "base_link";
    }

    // set covariance
    _Godom.pose.covariance = 
    {
        0.2, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.2, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.2, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0 
    };
    _Godom.twist.covariance = 
    {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0 
    };
    _Gimu.angular_velocity_covariance = 
    {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };
    _Gimu.linear_acceleration_covariance = 
    {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };
    _Gbias.angular_velocity_covariance = 
    {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
    };
    _Gbias.linear_acceleration_covariance = 
    {
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0,
        0.0, 0.0, 0.0
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
    std::vector<_Float64> p(_Ntags*3 + _Npairs, 0.0);
    _p = p;
    for (i=0; i<_Ntags; i++){
        _TagSet.Tags[i].p = _p;
    }
    
    // init distance vectors
    for (i=0; i<_Nanchors; i++) {

        // init distances - class
        _DT.push_back(0.0);

        for (j=0; j<_Ntags; j++){

            _DoptCentral.push_back(0.0);
            _DTmsgCentral.DC.push_back(0.0);

            _G.p.push_back(0.0);
            _G.pg.push_back(0.0);

        }

        // init markerarray
        _AtrueMsg.markers.push_back(zeroMark);
        
        // init Anchors position
        for (j=0; j<3; j++){

            for (k=0; k<_Ntags; k++){
            _A.push_back(0.0);
            _G.A.push_back(0.0);
            _TagSet.Tags[k].A.push_back(0.0);
            }
        }
    }

    //ROS_INFO("Consructor: ok");

}

/** **** METHODS **** */

// set links
void jackAPI::GetFrames(std::string& child, std::string& base, int tagID){

    // create transform
    if (tagID == 0){
        child = "rear_tag";
        base = "base_link";      
    }
    else if (tagID == 1){
        child = "right_tag";
        base = "base_link";  
    }
    else if (tagID == 2){
        child  = "left_tag";
        base = "base_link";  
    }
    else {
        child  =  "imu_link";
        base = "base_link";  
    }

}

// subscriber callback - centralized
void jackAPI::ChatterCallbackTCentral(const gtec_msgs::Ranging& msg){

    std::vector<_Float64> p0(_p.size(), 0.0);
    int i, j;

    //init with current estimate
    p0 = _p;

    try {

        // save distance read from tag
        _DT[msg.anchorId] = (double)msg.range/1000;

        // populate correct tag in the UWB message
        if (msg.tagId < _Ntags){            
              
            // set distance used to optimize
            _DoptCentral[_Nanchors*msg.tagId  + msg.anchorId] = _DT[msg.anchorId];

        }
        else {
            ROS_ERROR("WRONG ID - ChatterCallback");
        }
    }
    catch(...){
        ROS_INFO("WRONG tag ID");
    }

    // set the message
    _DTmsgCentral.DC = _DoptCentral; 
        
    //_get time
    _DTmsgCentral.header.stamp = _begin.now();

    // publish the distance wrapper
    _jack_disthandle_P.publish(_DTmsgCentral);

    //ROS_INFO("Published distances");

    // call newton raphson
    try {

        // copy anchors
        for (i=0;i<_Ntags;i++){
            _TagSet.Tags[i].A = _A;
        }
        
        //optimize
        int success = 0;
        auto t1 = std::chrono::high_resolution_clock::now();
        // success = genAPI::OptimMin(p0, _DoptCentral, &_TagSet);
        success = genAPI::CeresMin(p0, _DoptCentral, &_TagSet);
        auto t2 = std::chrono::high_resolution_clock::now();

        /* Getting number of milliseconds as an integer. */
        auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        /* Getting number of milliseconds as a double. */
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;

        // info
        //ROS_WARN("Optim exec time: %g", (_Float64)ms_double.count());

        // get final cumulative position
        for (i=0;i<_Ntags;i++){
            p0[3*i] = _TagSet.Tags[i].p[0];
            p0[3*i + 1] = _TagSet.Tags[i].p[1];
            p0[3*i + 2] = _TagSet.Tags[i].p[2];
        }

        // fill messages
        // gradient normal stuff
        _G.A = _A;
        _G.p = p0;
        _G.J = _TagSet.Tags[0].J;
        _G.GJ = _TagSet.Tags[0].GJ;
        _G.header.stamp = _begin.now();

        // gradient odom
        _Godom.header.stamp = _G.header.stamp;

        // transform
        for (i=0;i<_Ntags;i++){

            _G.pg[3*i] = _G.p[3*i] + _transformStamped.transforms[i].transform.translation.x;
            _G.pg[3*i + 1] = _G.p[3*i + 1] + _transformStamped.transforms[i].transform.translation.y;
            _G.pg[3*i + 2] = _G.p[3*i + 2] + _transformStamped.transforms[i].transform.translation.z;

        }

        // RESET ESTIMATE
        _Godom.pose.pose.position.x = 0.0;
        _Godom.pose.pose.position.y = 0.0;
        _Godom.pose.pose.position.z = 0.0;   

        // mean over Ntags estimates
        for (i=0;i<_Ntags;i++){

            _Godom.pose.pose.position.x += _G.pg[3*i];
            _Godom.pose.pose.position.y += _G.pg[3*i + 1];
            _Godom.pose.pose.position.z += _G.pg[3*i + 2];
        }

        // mean
        _Godom.pose.pose.position.x = _Godom.pose.pose.position.x/_Ntags;
        _Godom.pose.pose.position.y = _Godom.pose.pose.position.y/_Ntags;
        _Godom.pose.pose.position.z = _Godom.pose.pose.position.z/_Ntags;   
        
        // publish
        _jack_trilateration_P.publish(_G);
        _jack_odometry_P.publish(_Godom);

        //ROS_INFO("Published gradient");
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

    //ROS_INFO("Anchors received");

}

// subscriber callback - used to create synthetic true distances from ptrue
void jackAPI::ChatterCallbackDtrue(const nav_msgs::Odometry& msg){

    // define position
    std::vector<_Float64> ptrue(3,0.0);

    // random noise

    // init general stuff
    int i, idA;

    // noise
    double noise = 0;

    // init useless fields in MeshUWB
    _DTrueMsg.seq = 0;
    _DTrueMsg.rss = 0;
    _DTrueMsg.errorEstimation = 0;

    // transform position
    _Float64 x,y,z;
    x = msg.pose.pose.position.x + _transformStamped.transforms[0].transform.translation.x;
    y = msg.pose.pose.position.y + _transformStamped.transforms[0].transform.translation.y;
    z = msg.pose.pose.position.z + _transformStamped.transforms[0].transform.translation.z;

    // get true distances
    for (i=0;i<_Nanchors;i++){

        // get index
        idA = 3*i;  

        // noise
        noise = _distribution(_gen);

        // compute true distance      
        _DT[i] = sqrt( pow((x -_A[idA]),2) + 
                          pow((y -_A[idA+1]),2) + 
                          pow((z -_A[idA+2]),2)) + noise;

        // set other data in the messages
        _DTrueMsg.anchorId = i;
        _DTrueMsg.tagId = _tagID;
        _DTrueMsg.range = (int)(_DT[i]*1000);

        // publish on topic
        _jack_disthandle_P.publish(_DTrueMsg);
    }     

}

// callback for the true anchors publishing
void jackAPI::ChatterCallbackAtrue(const ros::TimerEvent& event){


    int i, idx;

    for (i=0;i<_Nanchors;i++) {

        // index for x,y,z
        idx = 3*i;

        // set anchor header
        _AtrueMsg.markers[i].header.seq = 0;
        _AtrueMsg.markers[i].header.stamp = ros::Time::now();
        _AtrueMsg.markers[i].id = i;

        // set anchor position (ith)
        _AtrueMsg.markers[i].pose.position.x = genAPI::Anchors[idx];
        _AtrueMsg.markers[i].pose.position.y = genAPI::Anchors[idx+1];
        _AtrueMsg.markers[i].pose.position.z = genAPI::Anchors[idx+2];
    }

    _jack_disthandle_PA.publish(_AtrueMsg);


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
    _Godom.header.frame_id = "world";
    _Godom.child_frame_id = "base_link";

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

// callback to remap odometry to another frame
void jackAPI::ChatterCallbackRemap(const nav_msgs::Odometry& msg){

    // copy the msg - very dummy
    // ROS_WARN("startFrame IN: %s", msg.header.frame_id.c_str());
    _Godom = msg;
}

