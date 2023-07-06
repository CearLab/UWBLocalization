// Auto-generated. Do not edit!

// (in-package jackal_op.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class GradientDescent {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.J = null;
      this.GJ = null;
      this.HJ = null;
      this.A = null;
      this.p = null;
      this.pg = null;
      this.N = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('J')) {
        this.J = initObj.J
      }
      else {
        this.J = 0.0;
      }
      if (initObj.hasOwnProperty('GJ')) {
        this.GJ = initObj.GJ
      }
      else {
        this.GJ = [];
      }
      if (initObj.hasOwnProperty('HJ')) {
        this.HJ = initObj.HJ
      }
      else {
        this.HJ = [];
      }
      if (initObj.hasOwnProperty('A')) {
        this.A = initObj.A
      }
      else {
        this.A = [];
      }
      if (initObj.hasOwnProperty('p')) {
        this.p = initObj.p
      }
      else {
        this.p = [];
      }
      if (initObj.hasOwnProperty('pg')) {
        this.pg = initObj.pg
      }
      else {
        this.pg = [];
      }
      if (initObj.hasOwnProperty('N')) {
        this.N = initObj.N
      }
      else {
        this.N = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GradientDescent
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [J]
    bufferOffset = _serializer.float64(obj.J, buffer, bufferOffset);
    // Serialize message field [GJ]
    bufferOffset = _arraySerializer.float64(obj.GJ, buffer, bufferOffset, null);
    // Serialize message field [HJ]
    bufferOffset = _arraySerializer.float64(obj.HJ, buffer, bufferOffset, null);
    // Serialize message field [A]
    bufferOffset = _arraySerializer.float64(obj.A, buffer, bufferOffset, null);
    // Serialize message field [p]
    bufferOffset = _arraySerializer.float64(obj.p, buffer, bufferOffset, null);
    // Serialize message field [pg]
    bufferOffset = _arraySerializer.float64(obj.pg, buffer, bufferOffset, null);
    // Serialize message field [N]
    bufferOffset = _arraySerializer.float64(obj.N, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GradientDescent
    let len;
    let data = new GradientDescent(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [J]
    data.J = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [GJ]
    data.GJ = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [HJ]
    data.HJ = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [A]
    data.A = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [p]
    data.p = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [pg]
    data.pg = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [N]
    data.N = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.GJ.length;
    length += 8 * object.HJ.length;
    length += 8 * object.A.length;
    length += 8 * object.p.length;
    length += 8 * object.pg.length;
    length += 8 * object.N.length;
    return length + 32;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_op/GradientDescent';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bf70146ab5f0d8094fd0d6f86f797d43';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64 J
    float64[] GJ
    float64[] HJ
    float64[] A
    float64[] p
    float64[] pg
    float64[] N
    
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
    const resolved = new GradientDescent(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.J !== undefined) {
      resolved.J = msg.J;
    }
    else {
      resolved.J = 0.0
    }

    if (msg.GJ !== undefined) {
      resolved.GJ = msg.GJ;
    }
    else {
      resolved.GJ = []
    }

    if (msg.HJ !== undefined) {
      resolved.HJ = msg.HJ;
    }
    else {
      resolved.HJ = []
    }

    if (msg.A !== undefined) {
      resolved.A = msg.A;
    }
    else {
      resolved.A = []
    }

    if (msg.p !== undefined) {
      resolved.p = msg.p;
    }
    else {
      resolved.p = []
    }

    if (msg.pg !== undefined) {
      resolved.pg = msg.pg;
    }
    else {
      resolved.pg = []
    }

    if (msg.N !== undefined) {
      resolved.N = msg.N;
    }
    else {
      resolved.N = []
    }

    return resolved;
    }
};

module.exports = GradientDescent;
