function [Object,Markers,SystemData]=NatyStream(flag)
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% Copyright (C) OMG Plc 2009.
% All rights reserved.  This software is protected by copyright
% law and international treaties.  No part of this software / document
% may be reproduced or distributed in any form or by any means,
% whether transiently or incidentally to some other use of this software,
% without the written permission of the copyright owner.
%
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Part of the Vicon DataStream SDK for MATLAB.
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


if nargin<1
    flag=1;
end
Object=[];
Markers=[];
SystemData=[];
% Program options
TransmitMulticast = false;

% A dialog to stop the loop
MessageBox = msgbox( 'Stop DataStream Client', 'Vicon DataStream SDK' );

% Load the SDK
fprintf( 'Loading SDK...' );
Client.LoadViconDataStreamSDK();
fprintf( 'done\n' );

% Program options
HostName = '132.68.134.248:801';

% Make a new client
MyClient = Client();

% Connect to a server

fprintf( 'Connecting to %s ...', HostName );

while ~MyClient.IsConnected().Connected
    % Direct connection
    MyClient.Connect( HostName );
    
    % Multicast connection
    % MyClient.ConnectToMulticast( HostName, '224.0.0.0' );
    
    fprintf( '.' );
end
fprintf( '\n' );

% Enable some different data types
MyClient.EnableSegmentData();
MyClient.EnableMarkerData();
MyClient.EnableUnlabeledMarkerData();
MyClient.EnableDeviceData();

% fprintf( 'Segment Data Enabled: %s\n',          AdaptBool( MyClient.IsSegmentDataEnabled().Enabled ) );
% fprintf( 'Marker Data Enabled: %s\n',           AdaptBool( MyClient.IsMarkerDataEnabled().Enabled ) );
% fprintf( 'Unlabeled Marker Data Enabled: %s\n', AdaptBool( MyClient.IsUnlabeledMarkerDataEnabled().Enabled ) );
% fprintf( 'Device Data Enabled: %s\n',           AdaptBool( MyClient.IsDeviceDataEnabled().Enabled ) );

% Set the streaming mode
%MyClient.SetStreamMode( StreamMode.ClientPull );
% MyClient.SetStreamMode( StreamMode.ClientPullPreFetch );
 MyClient.SetStreamMode( StreamMode.ServerPush );

% Set the global up axis
MyClient.SetAxisMapping( Direction.Forward, ...
    Direction.Left,    ...
    Direction.Up );    % Z-up
% MyClient.SetAxisMapping( Direction.Forward, ...
%                          Direction.Up,      ...
%                          Direction.Right ); % Y-up

Output_GetAxisMapping = MyClient.GetAxisMapping();
if flag==1;
fprintf( 'Axis Mapping: X-%s Y-%s Z-%s\n', Output_GetAxisMapping.XAxis.ToString(), ...
    Output_GetAxisMapping.YAxis.ToString(), ...
    Output_GetAxisMapping.ZAxis.ToString() );
end

% Discover the version number
Output_GetVersion = MyClient.GetVersion();
if flag==1;
fprintf( 'Version: %d.%d.%d\n', Output_GetVersion.Major, ...
    Output_GetVersion.Minor, ...
    Output_GetVersion.Point );
end
if TransmitMulticast
    MyClient.StartTransmittingMulticast( 'localhost', '224.0.0.0' );
end
ii=1;
% Loop until the message box is dismissed
while ishandle( MessageBox )
    drawnow;
    
    % Get a frame
    if flag==1;
    fprintf( 'Waiting for new frame...' );
    while MyClient.GetFrame().Result.Value ~= Result.Success
        fprintf( '.' );
    end% while
    fprintf( '\n' );
    end
    % Get the frame number
    Output_GetFrameNumber = MyClient.GetFrameNumber();
    if flag==1;
    fprintf( 'Frame Number: %d\n', Output_GetFrameNumber.FrameNumber );
    end
    SystemData.FrameNumber(ii)= Output_GetFrameNumber.FrameNumber ;
    % Get the frame rate
    Output_GetFrameRate = MyClient.GetFrameRate();
    if flag==1;
    fprintf( 'Frame rate: %g\n', Output_GetFrameRate.FrameRateHz );
    end
    SystemData.FrameRate(ii)=Output_GetFrameRate.FrameRateHz;
    % Get the timecode
    Output_GetTimecode = MyClient.GetTimecode();
    SystemData.time(ii,:)=[Output_GetTimecode.Hours,                  ...
                Output_GetTimecode.Minutes,                ...
                 Output_GetTimecode.Seconds];
    
    if flag==1;
    fprintf( 'Timecode: %dh %dm %ds %df %dsf %s %d %d %d\n\n',    ...
        Output_GetTimecode.Hours,                  ...
        Output_GetTimecode.Minutes,                ...
        Output_GetTimecode.Seconds,                ...
        Output_GetTimecode.Frames,                 ...
        Output_GetTimecode.SubFrame,               ...
        AdaptBool( Output_GetTimecode.FieldFlag ), ...
        Output_GetTimecode.Standard.Value,         ...
        Output_GetTimecode.SubFramesPerFrame,      ...
        Output_GetTimecode.UserBits );
   
    % Get the latency
    fprintf( 'Latency: %gs\n', MyClient.GetLatencyTotal().Total );
     end
    for LatencySampleIndex = 1:MyClient.GetLatencySampleCount().Count
        SampleName  = MyClient.GetLatencySampleName( LatencySampleIndex ).Name;
        SampleValue = MyClient.GetLatencySampleValue( SampleName ).Value;
           if flag==1;
        fprintf( '  %s %gs\n', SampleName, SampleValue );
           end
    end% for
      if flag==1;
    fprintf( '\n' );
      end
    % Count the number of subjects
    SubjectCount = MyClient.GetSubjectCount().SubjectCount;
      if flag==1;
    fprintf( 'Subjects (%d):\n', SubjectCount );
      end
    for SubjectIndex = 1:SubjectCount
        
        
        % Get the subject name
        SubjectName = MyClient.GetSubjectName( SubjectIndex ).SubjectName;
        % Get the root segment
        RootSegment = MyClient.GetSubjectRootSegmentName( SubjectName ).SegmentName;      
        % Count the number of segments
        SegmentCount = MyClient.GetSegmentCount( SubjectName ).SegmentCount;
        
         if flag==1;
            fprintf( '  Subject #%d\n', SubjectIndex - 1 );
            fprintf( '    Root Segment: %s\n', RootSegment );
            fprintf( '    Segments (%d):\n', SegmentCount );
        end
        for SegmentIndex = 1:SegmentCount
            
%             fprintf( '      Segment #%d\n', SegmentIndex - 1 );
            
            % Get the segment name
            SegmentName = MyClient.GetSegmentName( SubjectName, SegmentIndex ).SegmentName;
%             fprintf( '        Name: %s\n', SegmentName );
            
            % Get the segment parent
            SegmentParentName = MyClient.GetSegmentParentName( SubjectName, SegmentName ).SegmentName;
%             fprintf( '        Parent: %s\n',  SegmentParentName );
            
            % Get the segment's children
            ChildCount = MyClient.GetSegmentChildCount( SubjectName, SegmentName ).SegmentCount;
%             fprintf( '     Children (%d):\n', ChildCount );
            for ChildIndex = 1:ChildCount
                ChildName = MyClient.GetSegmentChildName( SubjectName, SegmentName, ChildIndex ).SegmentName;
%                 fprintf( '       %s\n', ChildName );
            end% for
            
            % Get the static segment translation
            Output_GetSegmentStaticTranslation = MyClient.GetSegmentStaticTranslation( SubjectName, SegmentName );
%             fprintf( '        Static Translation: (%g, %g, %g)\n',                  ...
%                 Output_GetSegmentStaticTranslation.Translation( 1 ), ...
%                 Output_GetSegmentStaticTranslation.Translation( 2 ), ...
%                 Output_GetSegmentStaticTranslation.Translation( 3 ) );

            
        end% SegmentIndex
        % Count the number of markers
        MarkerCount = MyClient.GetMarkerCount( SubjectName ).MarkerCount;
        if ii==1
        Object(SubjectIndex).ObjName=SubjectName;
        MarkersCount(SubjectIndex)=MarkerCount;
        end
        Object(SubjectIndex).Translation(ii,:)=Output_GetSegmentStaticTranslation.Translation;
        %         fprintf( '    Markers (%d):\n', MarkerCount );
        for MarkerIndex = 1:MarkerCount
            %% get global Marker Index
            if SubjectIndex>1
                MarkerGlobal=MarkerIndex+sum(MarkersCount(1:SubjectIndex-1));
            else
                MarkerGlobal=MarkerIndex;
            end
            
            
            
            % Get the marker name
            MarkerName = MyClient.GetMarkerName( SubjectName, MarkerIndex ).MarkerName;
            if ii==1
            Markers(MarkerGlobal).Markernames(1,1:length(MarkerName))=(MarkerName);
            end
            % Get the marker parent
            MarkerParentName = MyClient.GetMarkerParentName( SubjectName, MarkerName ).SegmentName;
            
            % Get the global marker translation
            Output_GetMarkerGlobalTranslation = MyClient.GetMarkerGlobalTranslation( SubjectName, MarkerName );
            Markers(MarkerGlobal).Pos(ii,:)=Output_GetMarkerGlobalTranslation.Translation;
            if flag==1
            fprintf( '      Marker #%d: %s (%g, %g, %g) %s\n',                     ...
                MarkerIndex - 1,                                    ...
                MarkerName,                                         ...
                Output_GetMarkerGlobalTranslation.Translation( 1 ), ...
                Output_GetMarkerGlobalTranslation.Translation( 2 ), ...
                Output_GetMarkerGlobalTranslation.Translation( 3 ), ...
                AdaptBool( Output_GetMarkerGlobalTranslation.Occluded ) );
            end
        end% MarkerIndex
        
    end% SubjectIndex
    
    % Get the unlabeled markers
    UnlabeledMarkerCount = MyClient.GetUnlabeledMarkerCount().MarkerCount;
%     fprintf( '    Unlabeled Markers (%d):\n', UnlabeledMarkerCount );
    for UnlabeledMarkerIndex = 1:UnlabeledMarkerCount
        % Get the global marker translation
        Output_GetUnlabeledMarkerGlobalTranslation = MyClient.GetUnlabeledMarkerGlobalTranslation( UnlabeledMarkerIndex );
%         ret.Output_GetUnlabeledMarkerGlobalTranslation=Output_GetUnlabeledMarkerGlobalTranslation;
        if flag==1
        fprintf( '      Marker #%d: (%g, %g, %g)\n',                                    ...
            UnlabeledMarkerIndex - 1,                                    ...
            Output_GetUnlabeledMarkerGlobalTranslation.Translation( 1 ), ...
            Output_GetUnlabeledMarkerGlobalTranslation.Translation( 2 ), ...
            Output_GetUnlabeledMarkerGlobalTranslation.Translation( 3 ) );
        end
    end% UnlabeledMarkerIndex
 ii=ii+1;   
end% while true

if TransmitMulticast
    MyClient.StopTransmittingMulticast();
end

% Disconnect and dispose
MyClient.Disconnect();

% Unload the SDK
fprintf( 'Unloading SDK...' );
Client.UnloadViconDataStreamSDK();
fprintf( 'done\n' );
