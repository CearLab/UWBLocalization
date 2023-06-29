// class with utilities for jackal with UWB handling
#include "MelodicAPI.hpp"

/** **** CONSTRUCTOR **** */
jackAPI::jackAPI(std::string name, int Nanchors, int tagID, int Ntags, int rate) 
: _gen(std::random_device{}()), _distribution(0.0,0.2){

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

    // push back transformations
    geometry_msgs::TransformStamped TransZero;
    // use it for pushbacks
    // for each tag I want the child-odom and I also want the odom-world transform
    for (i=0; i<_Ntags+1; i++){
        _transformStamped.transforms.push_back(TransZero);
    }

    // setup Tag set
    _TagSet.Ntags =_Ntags;
    for (i=0; i<_Ntags; i++){
        _TagSet.Tags[i].Nanchors = _Nanchors;
    }
    _TagSet.Npairs = 0; // there is no need to put theta in the optimization rn
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
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
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

    // quaternion
    for (i=0; i<3; i++) {
        _G.N.push_back(0.0);
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
        base = "odom";      
    }
    else if (tagID == 1){
        child = "right_tag";
        base = "odom";  
    }
    else if (tagID == 2){
        child  = "left_tag";
        base = "odom";  
    }
    else {
        child  =  "imu_link";
        base = "odom";  
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
            ROS_ERROR("WRONG ID - ChatterCallback: tag %d Ntag %d", msg.tagId, _Ntags);
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

        // if orientation is computed ok, otherwise unused
        arma::mat W = arma::zeros(3,_Ntags);
        arma::mat O = arma::zeros(3,_Ntags);
        arma::mat DELTA = arma::zeros(3,_Ntags);
        arma::mat R = arma::zeros(3,3);
        arma::vec Pwo = arma::zeros(3,1);
        arma::vec delta = arma::zeros(3,1);

        // test vectors
        arma::mat TEST = arma::zeros(3,2);
        arma::vec test = arma::zeros(3,1);

        // now we get the orientation
        if (_Ntags == 3){

            // fill matrix W with the WORLD coordinates
            // these coordinates have been obtained with 
            // the optimization process
            for (i=0;i<_Ntags;i++){
                W.col(i) = {p0[3*i+0], p0[3*i+1], p0[3*i+2]};
            }
            
            // fill matrix O with the Tags coordinates with
            // respect to the ODOM reference frame. They are 
            // gathered form the _transform array
            for (i=0;i<_Ntags;i++){
                O.col(i) = {-_transformStamped.transforms[i].transform.translation.x,
                            -_transformStamped.transforms[i].transform.translation.y,
                            -_transformStamped.transforms[i].transform.translation.z};
            }
        
            // get the translation vector:
            // fromn the outcome of the optimization we 
            // can get an estimate of the ODOM frame.
            // If the tags were perfectly symmetric wr2
            // ODOM, we could just take the mean. If not, 
            // check some workarounds, as in this case:
            // mean over the 2 xy symmetric, and remove the common
            // offset on z.
            TEST.col(0) = W.col(1);
            TEST.col(1) = W.col(2);
            Pwo = arma::mean(TEST,1);
            Pwo(2) = Pwo(2) - O.col(0)(2);
            Pwo = -Pwo;
                
            // remove translation from WORLD coordinates:
            // R*(W - T) = O --> R*DELTA = O
            for (i=0;i<3;i++){
                DELTA.col(i) = W.col(i) + Pwo;
            }
            
            // compute Rotation matrix: 
            // Solve analytically R*DELTA = O
            // This is indeed Rwo
            R = genAPI::procustes(DELTA,O);

        }
        else
        {
            // solution with 1 tag only - no orientation
            Pwo = {p0[0], 
                   p0[1], 
                   p0[2]};
            Pwo = -Pwo;
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

        // RESET ESTIMATE (we want odom-world)
        // This uses Pow = -Pwo as a current estimate of 
        // ODOM reference frame
        _Godom.pose.pose.position.x = -Pwo(0);
        _Godom.pose.pose.position.y = -Pwo(1);
        _Godom.pose.pose.position.z = -Pwo(2);   

        // assign orientation from Rwo
        tf2::Quaternion quat;
        tf2::Matrix3x3 Mat;
        // first: I want Row = Rwo.t()
        R = R.t();
        // set to tf2 var
        Mat.setValue(R(0,0), R(0,1), R(0,2),
                     R(1,0), R(1,1), R(1,2),
                     R(2,0), R(2,1), R(2,2));
        // get quaternion
        Mat.getRotation(quat);
        // assign quaternion
        _Godom.pose.pose.orientation.w = quat.getW();
        _Godom.pose.pose.orientation.x = quat.getX();
        _Godom.pose.pose.orientation.y = quat.getY();
        _Godom.pose.pose.orientation.z = quat.getZ();
        
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
    geometry_msgs::PoseStamped input, target;
    geometry_msgs::TransformStamped transformStamped;
    input.header = msg.header;
    input.pose = msg.pose.pose;
    transformStamped = _transformStamped.transforms[_tagID];
    tf2::doTransform(input, target, transformStamped);

    // orientation
    tf2::Quaternion quaternion;
    quaternion.setW(input.pose.orientation.w);  
    quaternion.setX(input.pose.orientation.x);
    quaternion.setY(input.pose.orientation.y);
    quaternion.setZ(input.pose.orientation.z);
    tf2::Matrix3x3 matrix(quaternion);
    // init
    tf2::Vector3 p0 = {input.pose.position.x, input.pose.position.y, input.pose.position.z};
    tf2::Vector3 delta = {_transformStamped.transforms[_tagID].transform.translation.x,
                          _transformStamped.transforms[_tagID].transform.translation.y,
                          _transformStamped.transforms[_tagID].transform.translation.z};
    tf2::Vector3 p1;

    // rotation + translation of array
    p1 = matrix*(delta) + p0;

    // final
    _Float64 x,y,z;
    x = p1[0];
    y = p1[1];
    z = p1[2];

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

    // get orientation from msg
    _G.N[0] = msg.pose.pose.orientation.w;
    _G.N[1] = msg.pose.pose.orientation.x;
    _G.N[2] = msg.pose.pose.orientation.y;
    _G.N[3] = msg.pose.pose.orientation.z;

    // set quaternion
    tf2::Quaternion quat;
    quat.setW(_G.N[0]);
    quat.setX(_G.N[1]);
    quat.setY(_G.N[2]);
    quat.setZ(_G.N[3]);

    // get RPY
    tf2::Matrix3x3 mat(quat);
    double roll, pitch, yaw;
    mat.getRPY(roll, pitch, yaw);

    // orientation
    _xnew[genAPI::pos_ang[0]] = xnow[genAPI::pos_ang[0]] + genAPI::theta[0] * (roll     - xnow[genAPI::pos_ang[0]]);
    _xnew[genAPI::pos_ang[1]] = xnow[genAPI::pos_ang[1]] + genAPI::theta[0] * (pitch    - xnow[genAPI::pos_ang[1]]);
    _xnew[genAPI::pos_ang[2]] = xnow[genAPI::pos_ang[2]] + genAPI::theta[0] * (yaw      - xnow[genAPI::pos_ang[2]]);

    // angular velocity bias
    _xnew[genAPI::pos_bw[0]] = xnow[genAPI::pos_bw[0]] + 0*genAPI::theta[0] * (roll     - xnow[genAPI::pos_ang[0]]);
    _xnew[genAPI::pos_bw[1]] = xnow[genAPI::pos_bw[1]] + 0*genAPI::theta[0] * (pitch    - xnow[genAPI::pos_ang[1]]);
    _xnew[genAPI::pos_bw[2]] = xnow[genAPI::pos_bw[2]] + 0*genAPI::theta[0] * (yaw      - xnow[genAPI::pos_ang[2]]);

    // angular velocity
    _xnew[genAPI::pos_w[0]] = xnow[genAPI::pos_w[0]];
    _xnew[genAPI::pos_w[1]] = xnow[genAPI::pos_w[1]];
    _xnew[genAPI::pos_w[2]] = xnow[genAPI::pos_w[2]];

}

// subscriber callback - implements th jump map of the hybrid observer
void jackAPI::ChatterCallbackHybCont(const sensor_msgs::Imu& msg){

    // init IMU meas
    std::vector<_Float64> IMU(3, 0.0);
    IMU[0] = msg.linear_acceleration.x;
    IMU[1] = msg.linear_acceleration.y;
    IMU[2] = msg.linear_acceleration.z;

    // init omega meas
    std::vector<_Float64> OMEGA(3, 0.0);
    OMEGA[0] = msg.angular_velocity.x;
    OMEGA[1] = msg.angular_velocity.y;
    OMEGA[2] = msg.angular_velocity.z;

    // input vector
    std::vector<_Float64> U = {IMU[0], IMU[1], IMU[2], OMEGA[0], OMEGA[1], OMEGA[2]};

    // transform from imu_link to base_link
    // set quaternion from the rotation
    tf2::Quaternion quat;
    quat.setW(_transformStamped.transforms[_Ntags].transform.rotation.w);
    quat.setX(_transformStamped.transforms[_Ntags].transform.rotation.x);
    quat.setY(_transformStamped.transforms[_Ntags].transform.rotation.y);
    quat.setZ(_transformStamped.transforms[_Ntags].transform.rotation.z);
    // change frame for angular velocity
    tf2::Matrix3x3 R(quat);
    tf2::Vector3 omegaold = {OMEGA[0], OMEGA[1], OMEGA[2]};
    tf2::Vector3 delta = {_transformStamped.transforms[_Ntags].transform.translation.x, 
                          _transformStamped.transforms[_Ntags].transform.translation.y,
                          _transformStamped.transforms[_Ntags].transform.translation.z};
    tf2::Vector3 omeganew;
    omeganew = R*omegaold + delta;

    //ROS_INFO("IMU meas: %g %g %g", IMU[0], IMU[1], IMU[2])z
    //ROS_INFO("dt: %g", _dt)z

    // integrate
    _xnew = genAPI::odeEuler(_xnew, U, _dt);

    //ROS_INFO("Xnew: %g %g %g", _xnew[genAPI::pos_p[0]], _xnew[genAPI::pos_p[1]], _xnew[genAPI::pos_p[2]]);

    // fill message and publish - odometry
    _Godom.header = msg.header;
    _Godom.header.frame_id = "world";
    _Godom.child_frame_id = "base_link";

    // position
    _Godom.pose.pose.position.x = _xnew[genAPI::pos_p[0]];
    _Godom.pose.pose.position.y = _xnew[genAPI::pos_p[1]];
    _Godom.pose.pose.position.z = _xnew[genAPI::pos_p[2]];

    // orientation
    quat.setRPY(_xnew[genAPI::pos_ang[0]], _xnew[genAPI::pos_ang[1]], _xnew[genAPI::pos_ang[2]]);
    _Godom.pose.pose.orientation.w = quat.getW();
    _Godom.pose.pose.orientation.x = quat.getX();
    _Godom.pose.pose.orientation.y = quat.getY();
    _Godom.pose.pose.orientation.z = quat.getZ();

    // velocity - linear
    _Godom.twist.twist.linear.x = _xnew[genAPI::pos_v[0]];
    _Godom.twist.twist.linear.y = _xnew[genAPI::pos_v[1]];
    _Godom.twist.twist.linear.z = _xnew[genAPI::pos_v[2]];

    // velocity - angular
    _Godom.twist.twist.angular.x = _xnew[genAPI::pos_w[0]];
    _Godom.twist.twist.angular.y = _xnew[genAPI::pos_w[1]];
    _Godom.twist.twist.angular.z = _xnew[genAPI::pos_w[2]];

    // publish
    _jack_odometry_P.publish(_Godom);

    // fill message and publish - IMU
    _Gimu.header = msg.header;
    
    // acceleration - linear
    _Gimu.linear_acceleration.x = _xnew[genAPI::pos_a[0]] - _xnew[genAPI::pos_b[0]];
    _Gimu.linear_acceleration.y = _xnew[genAPI::pos_a[1]] - _xnew[genAPI::pos_b[1]];
    _Gimu.linear_acceleration.z = _xnew[genAPI::pos_a[2]] - _xnew[genAPI::pos_b[2]];

    // velocity - angular
    _Gimu.angular_velocity.x = _xnew[genAPI::pos_w[0]] - _xnew[genAPI::pos_bw[0]];
    _Gimu.angular_velocity.y = _xnew[genAPI::pos_w[1]] - _xnew[genAPI::pos_bw[1]];
    _Gimu.angular_velocity.z = _xnew[genAPI::pos_w[2]] - _xnew[genAPI::pos_bw[2]];

    // publish
    _jack_IMU_P.publish(_Gimu);

    // fill message and publish - bias
    _Gbias.header = msg.header;
    
    // acceleration - linear
    _Gbias.linear_acceleration.x = _xnew[genAPI::pos_b[0]];
    _Gbias.linear_acceleration.y = _xnew[genAPI::pos_b[1]];
    _Gbias.linear_acceleration.z = _xnew[genAPI::pos_b[2]];

    // velocity - angular
    _Gbias.angular_velocity.x = _xnew[genAPI::pos_bw[0]];
    _Gbias.angular_velocity.y = _xnew[genAPI::pos_bw[1]];
    _Gbias.angular_velocity.z = _xnew[genAPI::pos_bw[2]];

    // publish
    _jack_Bias_P.publish(_Gbias);

}

// callback to remap odometry to another frame
void jackAPI::ChatterCallbackRemap(const nav_msgs::Odometry& msg){

    // copy the msg - very dummy
    // ROS_WARN("startFrame IN: %s", msg.header.frame_id.c_str());
    _Godom = msg;
}

