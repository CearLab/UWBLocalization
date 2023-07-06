// Auto-generated. Do not edit!

// (in-package imu_3dm_gx4.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let geometry_msgs = _finder('geometry_msgs');
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class FilterOutput {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.quat_status = null;
      this.bias_status = null;
      this.orientation = null;
      this.orientation_covariance = null;
      this.bias = null;
      this.bias_covariance = null;
      this.bias_covariance_status = null;
      this.orientation_covariance_status = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('quat_status')) {
        this.quat_status = initObj.quat_status
      }
      else {
        this.quat_status = 0;
      }
      if (initObj.hasOwnProperty('bias_status')) {
        this.bias_status = initObj.bias_status
      }
      else {
        this.bias_status = 0;
      }
      if (initObj.hasOwnProperty('orientation')) {
        this.orientation = initObj.orientation
      }
      else {
        this.orientation = new geometry_msgs.msg.Quaternion();
      }
      if (initObj.hasOwnProperty('orientation_covariance')) {
        this.orientation_covariance = initObj.orientation_covariance
      }
      else {
        this.orientation_covariance = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('bias')) {
        this.bias = initObj.bias
      }
      else {
        this.bias = new geometry_msgs.msg.Vector3();
      }
      if (initObj.hasOwnProperty('bias_covariance')) {
        this.bias_covariance = initObj.bias_covariance
      }
      else {
        this.bias_covariance = new Array(9).fill(0);
      }
      if (initObj.hasOwnProperty('bias_covariance_status')) {
        this.bias_covariance_status = initObj.bias_covariance_status
      }
      else {
        this.bias_covariance_status = 0;
      }
      if (initObj.hasOwnProperty('orientation_covariance_status')) {
        this.orientation_covariance_status = initObj.orientation_covariance_status
      }
      else {
        this.orientation_covariance_status = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type FilterOutput
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [quat_status]
    bufferOffset = _serializer.uint16(obj.quat_status, buffer, bufferOffset);
    // Serialize message field [bias_status]
    bufferOffset = _serializer.uint16(obj.bias_status, buffer, bufferOffset);
    // Serialize message field [orientation]
    bufferOffset = geometry_msgs.msg.Quaternion.serialize(obj.orientation, buffer, bufferOffset);
    // Check that the constant length array field [orientation_covariance] has the right length
    if (obj.orientation_covariance.length !== 9) {
      throw new Error('Unable to serialize array field orientation_covariance - length must be 9')
    }
    // Serialize message field [orientation_covariance]
    bufferOffset = _arraySerializer.float64(obj.orientation_covariance, buffer, bufferOffset, 9);
    // Serialize message field [bias]
    bufferOffset = geometry_msgs.msg.Vector3.serialize(obj.bias, buffer, bufferOffset);
    // Check that the constant length array field [bias_covariance] has the right length
    if (obj.bias_covariance.length !== 9) {
      throw new Error('Unable to serialize array field bias_covariance - length must be 9')
    }
    // Serialize message field [bias_covariance]
    bufferOffset = _arraySerializer.float64(obj.bias_covariance, buffer, bufferOffset, 9);
    // Serialize message field [bias_covariance_status]
    bufferOffset = _serializer.uint16(obj.bias_covariance_status, buffer, bufferOffset);
    // Serialize message field [orientation_covariance_status]
    bufferOffset = _serializer.uint16(obj.orientation_covariance_status, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type FilterOutput
    let len;
    let data = new FilterOutput(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [quat_status]
    data.quat_status = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [bias_status]
    data.bias_status = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [orientation]
    data.orientation = geometry_msgs.msg.Quaternion.deserialize(buffer, bufferOffset);
    // Deserialize message field [orientation_covariance]
    data.orientation_covariance = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [bias]
    data.bias = geometry_msgs.msg.Vector3.deserialize(buffer, bufferOffset);
    // Deserialize message field [bias_covariance]
    data.bias_covariance = _arrayDeserializer.float64(buffer, bufferOffset, 9)
    // Deserialize message field [bias_covariance_status]
    data.bias_covariance_status = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [orientation_covariance_status]
    data.orientation_covariance_status = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 208;
  }

  static datatype() {
    // Returns string type for a message object
    return 'imu_3dm_gx4/FilterOutput';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '40af8b09da9b33d02fc6b6288f52b159';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    # Output from the 3DM-GX4 attitude estimation filter.
    std_msgs/Header header
    
    # Node on status flags:
    # Status flags are implemented as bit-fields.
    #  0 = invalid
    #  1 = valid
    #  2 = valid and geo-magnetically referenced (quat_status only)
    #
    # Note that covariance on orientation becomes invalid as pitch angle exceeds 70 # degrees. This will be indicated by the status flag.
    
    # Quaternion status:
    uint16 quat_status
    
    # Bias status
    uint16 bias_status
    
    # Orientation estimate and diagonal covariance
    geometry_msgs/Quaternion orientation
    float64[9] orientation_covariance
    
    # Gyro bias and diagonal covariance
    geometry_msgs/Vector3 bias
    float64[9] bias_covariance
    
    # Covariance statuses
    uint16 bias_covariance_status
    uint16 orientation_covariance_status
    
    # Constants
    uint16 STATUS_INVALID = 0
    uint16 STATUS_VALID = 1
    uint16 STATUS_VALID_REFERENCED = 2
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    ================================================================================
    MSG: geometry_msgs/Quaternion
    # This represents an orientation in free space in quaternion form.
    
    float64 x
    float64 y
    float64 z
    float64 w
    
    ================================================================================
    MSG: geometry_msgs/Vector3
    # This represents a vector in free space. 
    # It is only meant to represent a direction. Therefore, it does not
    # make sense to apply a translation to it (e.g., when applying a 
    # generic rigid transformation to a Vector3, tf2 will only apply the
    # rotation). If you want your data to be translatable too, use the
    # geometry_msgs/Point message instead.
    
    float64 x
    float64 y
    float64 z
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new FilterOutput(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.quat_status !== undefined) {
      resolved.quat_status = msg.quat_status;
    }
    else {
      resolved.quat_status = 0
    }

    if (msg.bias_status !== undefined) {
      resolved.bias_status = msg.bias_status;
    }
    else {
      resolved.bias_status = 0
    }

    if (msg.orientation !== undefined) {
      resolved.orientation = geometry_msgs.msg.Quaternion.Resolve(msg.orientation)
    }
    else {
      resolved.orientation = new geometry_msgs.msg.Quaternion()
    }

    if (msg.orientation_covariance !== undefined) {
      resolved.orientation_covariance = msg.orientation_covariance;
    }
    else {
      resolved.orientation_covariance = new Array(9).fill(0)
    }

    if (msg.bias !== undefined) {
      resolved.bias = geometry_msgs.msg.Vector3.Resolve(msg.bias)
    }
    else {
      resolved.bias = new geometry_msgs.msg.Vector3()
    }

    if (msg.bias_covariance !== undefined) {
      resolved.bias_covariance = msg.bias_covariance;
    }
    else {
      resolved.bias_covariance = new Array(9).fill(0)
    }

    if (msg.bias_covariance_status !== undefined) {
      resolved.bias_covariance_status = msg.bias_covariance_status;
    }
    else {
      resolved.bias_covariance_status = 0
    }

    if (msg.orientation_covariance_status !== undefined) {
      resolved.orientation_covariance_status = msg.orientation_covariance_status;
    }
    else {
      resolved.orientation_covariance_status = 0
    }

    return resolved;
    }
};

// Constants for message
FilterOutput.Constants = {
  STATUS_INVALID: 0,
  STATUS_VALID: 1,
  STATUS_VALID_REFERENCED: 2,
}

module.exports = FilterOutput;
