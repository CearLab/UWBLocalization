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

class MeshUWB {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.D1 = null;
      this.D2 = null;
      this.D3 = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('D1')) {
        this.D1 = initObj.D1
      }
      else {
        this.D1 = [];
      }
      if (initObj.hasOwnProperty('D2')) {
        this.D2 = initObj.D2
      }
      else {
        this.D2 = [];
      }
      if (initObj.hasOwnProperty('D3')) {
        this.D3 = initObj.D3
      }
      else {
        this.D3 = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type MeshUWB
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [D1]
    bufferOffset = _arraySerializer.float64(obj.D1, buffer, bufferOffset, null);
    // Serialize message field [D2]
    bufferOffset = _arraySerializer.float64(obj.D2, buffer, bufferOffset, null);
    // Serialize message field [D3]
    bufferOffset = _arraySerializer.float64(obj.D3, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type MeshUWB
    let len;
    let data = new MeshUWB(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [D1]
    data.D1 = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [D2]
    data.D2 = _arrayDeserializer.float64(buffer, bufferOffset, null)
    // Deserialize message field [D3]
    data.D3 = _arrayDeserializer.float64(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    length += 8 * object.D1.length;
    length += 8 * object.D2.length;
    length += 8 * object.D3.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'jackal_op/MeshUWB';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '5b30149a17ef9828ca679ce567fad6c8';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    float64[] D1
    float64[] D2
    float64[] D3
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
    const resolved = new MeshUWB(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.D1 !== undefined) {
      resolved.D1 = msg.D1;
    }
    else {
      resolved.D1 = []
    }

    if (msg.D2 !== undefined) {
      resolved.D2 = msg.D2;
    }
    else {
      resolved.D2 = []
    }

    if (msg.D3 !== undefined) {
      resolved.D3 = msg.D3;
    }
    else {
      resolved.D3 = []
    }

    return resolved;
    }
};

module.exports = MeshUWB;
