function [data, info] = meshUWB
%MeshUWB gives an empty data for jackal_op/MeshUWB
% Copyright 2019-2020 The MathWorks, Inc.
%#codegen
data = struct();
data.MessageType = 'jackal_op/MeshUWB';
[data.Header, info.Header] = ros.internal.ros.messages.std_msgs.header;
info.Header.MLdataType = 'struct';
[data.D1, info.D1] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.D2, info.D2] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.D3, info.D3] = ros.internal.ros.messages.ros.default_type('double',NaN);
info.MessageType = 'jackal_op/MeshUWB';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,9);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'D1';
info.MatPath{8} = 'D2';
info.MatPath{9} = 'D3';
