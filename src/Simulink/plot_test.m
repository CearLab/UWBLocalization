%% setup
Ts = 0.01;
data.time = 0:Ts:(size(data.p,1)-1)*Ts;
clear Ts

fig_count = 0;
fontsize = 15;
close all

set(0,'DefaultFigureWindowStyle','docked');     

%% position estimation
fig_count = fig_count +1;
try
    figure(fig_count);
    sgtitle('Position estimation')
    ax = zeros(1,3);
    for i=1:3
        subplot(3,1,i);
        hold on
        grid on
        box on

        % indicize axes        
        ax(i)=subplot(3,1,i);     
        
        
        plot(data.time,data.p(:,i),'LineWidth',2,'Color','b');
        plot(data.time,data.phat(:,i),'LineWidth',2,'Color','r');
            
        % labels
        set(gca,'fontsize', fontsize)         
        ylabel(['p_',num2str(i)])
    end
    %linkaxes(ax);
    legend('True','Est')   
    xlabel('time [s]') 
catch ME
    close
    fig_count = fig_count -1;
end

%% position estimation error
fig_count = fig_count +1;
try
    figure(fig_count);
    sgtitle('Position estimation error')
    ax = zeros(1,3);
    for i=1:3
        subplot(3,1,i);
        hold on
        grid on
        box on

        % indicize axes        
        ax(i)=subplot(3,1,i);     
        
        
        plot(data.time,data.e(:,i),'LineWidth',2,'Color','b');     
        % labels
        set(gca,'fontsize', fontsize)         
        ylabel(['e_',num2str(i)])
    end
    %linkaxes(ax);
    legend('Err')   
    xlabel('time [s]') 
catch ME
    close
    fig_count = fig_count -1;
end

%% velocity
fig_count = fig_count +1;
try
    figure(fig_count);
    sgtitle('Velocity ground truth')
    ax = zeros(1,3);
    for i=1:3
        subplot(3,1,i);
        hold on
        grid on
        box on

        % indicize axes        
        ax(i)=subplot(3,1,i);     
        
        
        plot(data.time,data.v(:,i),'LineWidth',2,'Color','b');
            
        % labels
        set(gca,'fontsize', fontsize)         
        ylabel(['v_',num2str(i)])
    end
    %linkaxes(ax);
    legend('True') 
catch ME
    close
    fig_count = fig_count -1;
end

%% Distances
fig_count = fig_count +1;
try
    figure(fig_count);
    sgtitle('Tag distances')
    ax = zeros(1,3);
    for i=1:3
        subplot(3,1,i);
        hold on
        grid on
        box on

        % indicize axes        
        ax(i)=subplot(3,1,i);     
        
        
        plot(data.time,data.D(:,4*(i-1)+1),'LineWidth',2,'Color','r');
        plot(data.time,data.D(:,4*(i-1)+2),'LineWidth',2,'Color','g');
        plot(data.time,data.D(:,4*(i-1)+3),'LineWidth',2,'Color','b');
        plot(data.time,data.D(:,4*(i-1)+4),'LineWidth',2,'Color','k');
            
        % labels
        set(gca,'fontsize', fontsize)         
        ylabel(['DT_',num2str(i)])
    end
    %linkaxes(ax);
    legend('Meas')   
    xlabel('time [s]') 
catch ME
    close
    fig_count = fig_count -1;
end

%% cleanup
clear i ax fig_count fontsize ME