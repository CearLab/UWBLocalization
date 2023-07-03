// Auto-generated. Do not edit!

// (in-package gtec_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class RadarCube {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.fftSize = null;
      this.angleBins = null;
      this.data = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('fftSize')) {
        this.fftSize = initObj.fftSize
      }
      else {
        this.fftSize = 0;
      }
      if (initObj.hasOwnProperty('angleBins')) {
        this.angleBins = initObj.angleBins
      }
      else {
        this.angleBins = 0;
      }
      if (initObj.hasOwnProperty('data')) {
        this.data = initObj.data
      }
      else {
        this.data = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RadarCube
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [fftSize]
    bufferOffset = _serializer.int16(obj.fftSize, buffer, bufferOffset);
    // Serialize message field [angleBins]
    bufferOffset = _serializer.int16(obj.angleBins, buffer, bufferOffset);
    // Serialize message field [data]
    bufferOffset = _arraySerializer.float64(obj.data, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RadarCube
    let len;
    let data = new RadarCube(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [fftSize]
    data.fftSize = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [angleBins]
    data.angleBins = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [data]
    data.data = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.data.length;
    return length + 8;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/RadarCube';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'fc958423e7f6a6996cbc895eb0a5e0b2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    int16 fftSize
    int16 angleBins
    float64[] data
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RadarCube(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.fftSize !== undefined) {
      resolved.fftSize = msg.fftSize;
    }
    else {
      resolved.fftSize = 0
    }

    if (msg.angleBins !== undefined) {
      resolved.angleBins = msg.angleBins;
    }
    else {
      resolved.angleBins = 0
    }

    if (msg.data !== undefined) {
      resolved.data = msg.data;
    }
    else {
      resolved.data = []
    }

    return resolved;
    }
};

module.exports = RadarCube;
