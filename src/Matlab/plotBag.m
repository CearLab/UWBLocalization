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
    data.time = time;
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
            ylim([-3 3]);
        end
        %linkaxes(ax);
        legend('Pos')   
        xlabel('time [s]')
        xlim('auto');
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
            ylim([-3 3]);
        end
        %linkaxes(ax);
        legend('Err')   
        xlabel('time [s]') 
        xlim('auto');
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

    data.q = quatnormalize(data.q);
    data.qhat = quatnormalize(data.qhat);

    [pitch, roll, yaw] = quat2angle( data.q, 'YXZ' );
    data.RPY(:,1) = roll;
    data.RPY(:,2) = pitch;
    data.RPY(:,3) = yaw;

    [pitch, roll, yaw] = quat2angle( data.qhat, 'YXZ' );
    data.RPYhat(:,1) = roll;
    data.RPYhat(:,2) = pitch;
    data.RPYhat(:,3) = yaw;

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

    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
        for i=1:4
            subplot(4,1,i);
            box on
            hold on
            grid on
            plot(time,data.q(:,i),'b','LineWidth',2);
            plot(time,data.qhat(:,i),'r','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['e_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Quat')   
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
        legend('Ang Err')   
        xlabel('time [s]') 
    end

    %% quaternion estimation error
    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    data.equat = quatmultiply(data.q,data.qhat);
    data.eangMean = mean(data.equat(startpos:endpos,:),1);
    data.eangSigma = std(data.equat(startpos:endpos,:),0,1);

    if plotF
        for i=1:4
            subplot(4,1,i);
            box on
            hold on
            grid on
            plot(time,data.equat(:,i),'b','LineWidth',2);
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['e_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Quat Err')   
        xlabel('time [s]') 
    end

    %% distances

    if plotF
        fig_count = fig_count +1;
        figure(fig_count)
    end

    xhat = zeros(12,length(out.UWBData));
    xhat = cell2mat(cellfun(@(m) double(m.DC),out.UWBData,'UniformOutput',false));
    xhat = reshape(xhat,12,length(out.UWBData))';
    for i=1:size(xhat,2)
        tmp(:,i) = resample(xhat(:,i),numel(x),size(xhat,1));
    end
    xhat = tmp;
    data.UWB = xhat;

    if plotF
        sgtitle('Tag distances')
        ax = zeros(1,3);
        for i=1:3
            subplot(3,1,i);
            hold on
            grid on
            box on
    
            % indicize axes        
            ax(i)=subplot(3,1,i);     
            
            
            plot(time,data.UWB(:,4*(i-1)+1),'LineWidth',2,'Color','r');
            plot(time,data.UWB(:,4*(i-1)+2),'LineWidth',2,'Color','g');
            plot(time,data.UWB(:,4*(i-1)+3),'LineWidth',2,'Color','b');
            plot(time,data.UWB(:,4*(i-1)+4),'LineWidth',2,'Color','k');
                
            % labels
            set(gca,'fontsize', fontsize)         
            ylabel(['DT_',num2str(i)])
        end
        %linkaxes(ax);
        legend('Meas')   
        xlabel('time [s]') 
    end

    %% getIMU
    data.IMU(:,1) = cellfun(@(m) double(m.LinearAcceleration.X),out.IMUData);
    data.IMU(:,2) = cellfun(@(m) double(m.LinearAcceleration.Y),out.IMUData);
    data.IMU(:,3) = cellfun(@(m) double(m.LinearAcceleration.Z),out.IMUData);
    for i = 1:3
        tmp(:,i) = resample(data.IMU(:,i),numel(x),size(data.IMU(:,i),1));
    end
    data.IMU = tmp;

    data.W(:,1) = cellfun(@(m) double(m.AngularVelocity.X),out.IMUData);
    data.W(:,2) = cellfun(@(m) double(m.AngularVelocity.Y),out.IMUData);
    data.W(:,3) = cellfun(@(m) double(m.AngularVelocity.Z),out.IMUData);
    for i = 1:3
        tmp(:,i) = resample(data.W(:,i),numel(x),size(data.W(:,i),1));
    end
    data.W = tmp;
   

end