%% plot data
function data = plotBag(out,plotF)

    % init
    fig_count = 0;
    fontsize = 15;
    close all
    set(0,'DefaultFigureWindowStyle','docked');

    % define time ofr gorund truth and estimation
    time = out.vicon.MessageList.Time - out.vicon.StartTime;
    timehat = out.EKF.MessageList.Time - out.EKF.StartTime;
    startpos = floor(numel(time)/2);
    endpos = numel(time)-1;

    %% position estimation
    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    x = cellfun(@(m) double(m.Pose.Pose.Position.X),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Position.X),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.p(:,1) = x;
    data.phat(:,1) = xhat;

    x = cellfun(@(m) double(m.Pose.Pose.Position.Y),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Position.Y),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.p(:,2) = x;
    data.phat(:,2) = xhat;

    x = cellfun(@(m) double(m.Pose.Pose.Position.Z),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Position.Z),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.p(:,3) = x;
    data.phat(:,3) = xhat;

    if plotF
        for i=1:3
            subplot(3,1,i);
            box on
            hold on
            grid on
            plot(time,data.p(:,i),'b','LineWidth',2);
            plot(time,data.phat(:,i),'r','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['p_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Pos')   
        xlabel('time [s]') 
    end

    %% position estimation error
    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    data.ep = data.p - data.phat;
    data.epMean = mean(data.ep(startpos:endpos,:),1);
    data.epSigma = std(data.ep(startpos:endpos,:),0,1);

    if plotF
        for i=1:3
            subplot(3,1,i);
            box on
            hold on
            grid on
            plot(time,data.ep(:,i),'b','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['e_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Err')   
        xlabel('time [s]') 
    end

    %% pose estimation
    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    x = cellfun(@(m) double(m.Pose.Pose.Orientation.X),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Orientation.X),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.q(:,2) = x;
    data.qhat(:,2) = xhat;

    x = cellfun(@(m) double(m.Pose.Pose.Orientation.Y),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Orientation.Y),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.q(:,3) = x;
    data.qhat(:,3) = xhat;

    x = cellfun(@(m) double(m.Pose.Pose.Orientation.Z),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Orientation.Z),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.q(:,4) = x;
    data.qhat(:,4) = xhat;

    x = cellfun(@(m) double(m.Pose.Pose.Orientation.W),out.viconData);
    xhat = cellfun(@(m) double(m.Pose.Pose.Orientation.W),out.EKFData);
    xhat = resample(xhat,numel(x),numel(xhat));
    data.q(:,1) = x;
    data.qhat(:,1) = xhat;

    [pitch, roll, yaw] = quat2angle( data.q, 'YXZ' );
    data.RPY(:,1) = wrapToPi(roll);
    data.RPY(:,2) = wrapToPi(pitch);
    data.RPY(:,3) = wrapToPi(yaw);

    [pitch, roll, yaw] = quat2angle( data.qhat, 'YXZ' );
    data.RPYhat(:,1) = wrapToPi(roll);
    data.RPYhat(:,2) = wrapToPi(pitch);
    data.RPYhat(:,3) = wrapToPi(yaw);

    if plotF
        for i=1:3
            subplot(3,1,i);
            box on
            hold on
            grid on
            plot(time,data.RPY(:,i),'b','LineWidth',2);
            plot(time,data.RPYhat(:,i),'r','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['\theta_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Ang')   
        xlabel('time [s]') 
    end

    %% pose estimation error
    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    data.eang = data.RPY - data.RPYhat;
    data.eangMean = mean(data.eang(startpos:endpos,:),1);
    data.eangSigma = std(data.eang(startpos:endpos,:),0,1);

    if plotF
        for i=1:3
            subplot(3,1,i);
            box on
            hold on
            grid on
            plot(time,data.eang(:,i),'b','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['e_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Err')   
        xlabel('time [s]') 
    end
   

end