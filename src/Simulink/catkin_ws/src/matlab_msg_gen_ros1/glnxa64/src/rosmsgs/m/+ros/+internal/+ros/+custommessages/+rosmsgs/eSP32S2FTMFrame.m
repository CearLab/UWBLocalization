function [data, info] = eSP32S2FTMFrame
%ESP32S2FTMFrame gives an empty data for rosmsgs/ESP32S2FTMFrame
% Copyright 2019-2020 The MathWorks, Inc.
%#codegen
data = struct();
data.MessageType = 'rosmsgs/ESP32S2FTMFrame';
[data.Rssi, info.Rssi] = ros.internal.ros.messages.ros.default_type('int32',1);
[data.Rtt, info.Rtt] = ros.internal.ros.messages.ros.default_type('int32',1);
[data.T1, info.T1] = ros.internal.ros.messages.ros.default_type('int64',1);
[data.T2, info.T2] = ros.internal.ros.messages.ros.default_type('int64',1);
[data.T3, info.T3] = ros.internal.ros.messages.ros.default_type('int64',1);
[data.T4, info.T4] = ros.internal.ros.messages.ros.default_type('int64',1);
info.MessageType = 'rosmsgs/ESP32S2FTMFrame';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,6);
info.MatPath{1} = 'rssi';
info.MatPath{2} = 'rtt';
info.MatPath{3} = 't1';
info.MatPath{4} = 't2';
info.MatPath{5} = 't3';
info.MatPath{6} = 't4';
