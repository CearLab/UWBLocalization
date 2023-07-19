%%
function out = readBag(filename)

    % read stuff
    out.bag = rosbag(filename);
    out.bagInfo = rosbag('info',filename);
    out.vicon = select(out.bag,'Topic','/ground_truth/state');
    out.viconData = readMessages(out.vicon,'DataFormat','struct');
    out.EKF = select(out.bag,'Topic','/odometry/filtered');
    out.EKFData = readMessages(out.EKF,'DataFormat','struct');

end