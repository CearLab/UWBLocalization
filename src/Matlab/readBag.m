%%
function out = readBag(filename)

    % read stuff
    out.bag = rosbag(filename);
    out.bagInfo = rosbag('info',filename);
    out.vicon = select(out.bag,'Topic','/ground_truth/state');
    out.viconData = readMessages(out.vicon,'DataFormat','struct');
    out.EKF = select(out.bag,'Topic','/odometry/filtered');
    out.EKFData = readMessages(out.EKF,'DataFormat','struct');
    out.UWB = select(out.bag,'Topic','/DT5/DT');
    out.UWBData = readMessages(out.UWB,'DataFormat','struct');
    out.IMU = select(out.bag,'Topic','/imu/data');
    out.IMUData = readMessages(out.IMU,'DataFormat','struct');
    out.PJUMP = select(out.bag,'Topic','/DT5/gradientOdom');
    out.PJUMPData = readMessages(out.PJUMP,'DataFormat','struct');
    out.PHYB = select(out.bag,'Topic','/HYB5/Odom');
    out.PHYBData = readMessages(out.PHYB,'DataFormat','struct');
    out.IMUHYB = select(out.bag,'Topic','/HYB5/IMU');
    out.IMUHYBData = readMessages(out.IMUHYB,'DataFormat','struct');
    out.BiasHYB = select(out.bag,'Topic','/HYB5/Bias');
    out.BiasHYBData = readMessages(out.BiasHYB,'DataFormat','struct');

end