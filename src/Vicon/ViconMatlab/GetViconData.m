clc
clear all


TransmitMulticast = false;
% Program options
TransmitMulticast = false;

% A dialog to stop the loop
% MessageBox = msgbox( 'Stop DataStream Client', 'Vicon DataStream SDK' );

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
%MyClient.EnableSegmentData();
MyClient.EnableMarkerData();
MyClient.EnableUnlabeledMarkerData();
%MyClient.EnableDeviceData();

% fprintf( 'Segment Data Enabled: %s\n',          AdaptBool( MyClient.IsSegmentDataEnabled().Enabled ) );
% fprintf( 'Marker Data Enabled: %s\n',           AdaptBool( MyClient.IsMarkerDataEnabled().Enabled ) );
% fprintf( 'Unlabeled Marker Data Enabled: %s\n', AdaptBool( MyClient.IsUnlabeledMarkerDataEnabled().Enabled ) );
% fprintf( 'Device Data Enabled: %s\n',           AdaptBool( MyClient.IsDeviceDataEnabled().Enabled ) );

% Set the streaming mode
MyClient.SetStreamMode( StreamMode.ClientPull );
% MyClient.SetStreamMode( StreamMode.ClientPullPreFetch );
% MyClient.SetStreamMode( StreamMode.ServerPush );

% Set the global up axis
MyClient.SetAxisMapping( Direction.Forward, ...
                         Direction.Left,    ...
                         Direction.Up );    % Z-up
% MyClient.SetAxisMapping( Direction.Forward, ...
%                          Direction.Up,      ...
%                          Direction.Right ); % Y-up

Output_GetAxisMapping = MyClient.GetAxisMapping();
fprintf( 'Axis Mapping: X-%s Y-%s Z-%s\n', Output_GetAxisMapping.XAxis.ToString(), ...
                                           Output_GetAxisMapping.YAxis.ToString(), ...
                                           Output_GetAxisMapping.ZAxis.ToString() );


% Discover the version number
Output_GetVersion = MyClient.GetVersion();
fprintf( 'Version: %d.%d.%d\n', Output_GetVersion.Major, ...
                                Output_GetVersion.Minor, ...
                                Output_GetVersion.Point );
  
if TransmitMulticast
  MyClient.StartTransmittingMulticast( 'localhost', '224.0.0.0' );
end 
flag=0;%fprint or not
for i=1:1:10
res=MarkerPosFunc(flag,MyClient);
end

% Disconnect and dispose
MyClient.Disconnect();

% Unload the SDK
fprintf( 'Unloading SDK...' );
Client.UnloadViconDataStreamSDK();
fprintf( 'done\n' );