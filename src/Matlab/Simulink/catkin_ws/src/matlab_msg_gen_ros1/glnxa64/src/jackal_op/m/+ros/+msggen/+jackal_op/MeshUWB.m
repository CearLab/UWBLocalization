
classdef MeshUWB < ros.Message
    %MeshUWB MATLAB implementation of jackal_op/MeshUWB
    %   This class was automatically generated by
    %   ros.internal.pubsubEmitter.
    %   Copyright 2014-2020 The MathWorks, Inc.
    properties (Constant)
        MessageType = 'jackal_op/MeshUWB' % The ROS message type
    end
    properties (Constant, Hidden)
        MD5Checksum = '5b30149a17ef9828ca679ce567fad6c8' % The MD5 Checksum of the message definition
        PropertyList = { 'Header' 'D1' 'D2' 'D3' } % List of non-constant message properties
        ROSPropertyList = { 'header' 'D1' 'D2' 'D3' } % List of non-constant ROS message properties
        PropertyMessageTypes = { 'ros.msggen.std_msgs.Header' ...
            '' ...
            '' ...
            '' ...
            } % Types of contained nested messages
    end
    properties (Constant)
    end
    properties
        Header
        D1
        D2
        D3
    end
    methods
        function set.Header(obj, val)
            validAttributes = {'nonempty', 'scalar'};
            validClasses = {'ros.msggen.std_msgs.Header'};
            validateattributes(val, validClasses, validAttributes, 'MeshUWB', 'Header')
            obj.Header = val;
        end
        function set.D1(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = double.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'MeshUWB', 'D1');
            obj.D1 = double(val);
        end
        function set.D2(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = double.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'MeshUWB', 'D2');
            obj.D2 = double(val);
        end
        function set.D3(obj, val)
            validClasses = {'numeric'};
            if isempty(val)
                % Allow empty [] input
                val = double.empty(0, 1);
            end
            val = val(:);
            validAttributes = {'vector'};
            validateattributes(val, validClasses, validAttributes, 'MeshUWB', 'D3');
            obj.D3 = double(val);
        end
    end
    methods (Static, Access = {?matlab.unittest.TestCase, ?ros.Message})
        function obj = loadobj(strObj)
        %loadobj Implements loading of message from MAT file
        % Return an empty object array if the structure element is not defined
            if isempty(strObj)
                obj = ros.msggen.jackal_op.MeshUWB.empty(0,1);
                return
            end
            % Create an empty message object
            obj = ros.msggen.jackal_op.MeshUWB(strObj);
        end
    end
end
