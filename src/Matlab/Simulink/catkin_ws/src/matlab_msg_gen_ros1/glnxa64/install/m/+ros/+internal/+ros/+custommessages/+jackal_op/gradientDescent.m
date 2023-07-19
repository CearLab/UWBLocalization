function [data, info] = gradientDescent
%GradientDescent gives an empty data for jackal_op/GradientDescent
% Copyright 2019-2020 The MathWorks, Inc.
%#codegen
data = struct();
data.MessageType = 'jackal_op/GradientDescent';
[data.Header, info.Header] = ros.internal.ros.messages.std_msgs.header;
info.Header.MLdataType = 'struct';
[data.J, info.J] = ros.internal.ros.messages.ros.default_type('double',1);
[data.GJ, info.GJ] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.HJ, info.HJ] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.A, info.A] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.P, info.P] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.Pg, info.Pg] = ros.internal.ros.messages.ros.default_type('double',NaN);
[data.N, info.N] = ros.internal.ros.messages.ros.default_type('double',NaN);
info.MessageType = 'jackal_op/GradientDescent';
info.constant = 0;
info.default = 0;
info.maxstrlen = NaN;
info.MaxLen = 1;
info.MinLen = 1;
info.MatPath = cell(1,13);
info.MatPath{1} = 'header';
info.MatPath{2} = 'header.seq';
info.MatPath{3} = 'header.stamp';
info.MatPath{4} = 'header.stamp.sec';
info.MatPath{5} = 'header.stamp.nsec';
info.MatPath{6} = 'header.frame_id';
info.MatPath{7} = 'J';
info.MatPath{8} = 'GJ';
info.MatPath{9} = 'HJ';
info.MatPath{10} = 'A';
info.MatPath{11} = 'p';
info.MatPath{12} = 'pg';
info.MatPath{13} = 'N';
