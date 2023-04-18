// Auto-generated. Do not edit!

// (in-package gtec_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class GenericRanging {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.anchorId = null;
      this.tagId = null;
      this.range = null;
      this.seq = null;
      this.rxPower = null;
    }
    else {
      if (initObj.hasOwnProperty('anchorId')) {
        this.anchorId = initObj.anchorId
      }
      else {
        this.anchorId = 0;
      }
      if (initObj.hasOwnProperty('tagId')) {
        this.tagId = initObj.tagId
      }
      else {
        this.tagId = 0;
      }
      if (initObj.hasOwnProperty('range')) {
        this.range = initObj.range
      }
      else {
        this.range = 0;
      }
      if (initObj.hasOwnProperty('seq')) {
        this.seq = initObj.seq
      }
      else {
        this.seq = 0;
      }
      if (initObj.hasOwnProperty('rxPower')) {
        this.rxPower = initObj.rxPower
      }
      else {
        this.rxPower = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type GenericRanging
    // Serialize message field [anchorId]
    bufferOffset = _serializer.int16(obj.anchorId, buffer, bufferOffset);
    // Serialize message field [tagId]
    bufferOffset = _serializer.int16(obj.tagId, buffer, bufferOffset);
    // Serialize message field [range]
    bufferOffset = _serializer.int32(obj.range, buffer, bufferOffset);
    // Serialize message field [seq]
    bufferOffset = _serializer.int32(obj.seq, buffer, bufferOffset);
    // Serialize message field [rxPower]
    bufferOffset = _serializer.float64(obj.rxPower, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type GenericRanging
    let len;
    let data = new GenericRanging(null);
    // Deserialize message field [anchorId]
    data.anchorId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [tagId]
    data.tagId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [seq]
    data.seq = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [rxPower]
    data.rxPower = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/GenericRanging';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'bb14e8b4057fd81e694cb16617eec599';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 anchorId
    int16 tagId
    int32 range
    int32 seq
    float64 rxPower
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new GenericRanging(null);
    if (msg.anchorId !== undefined) {
      resolved.anchorId = msg.anchorId;
    }
    else {
      resolved.anchorId = 0
    }

    if (msg.tagId !== undefined) {
      resolved.tagId = msg.tagId;
    }
    else {
      resolved.tagId = 0
    }

    if (msg.range !== undefined) {
      resolved.range = msg.range;
    }
    else {
      resolved.range = 0
    }

    if (msg.seq !== undefined) {
      resolved.seq = msg.seq;
    }
    else {
      resolved.seq = 0
    }

    if (msg.rxPower !== undefined) {
      resolved.rxPower = msg.rxPower;
    }
    else {
      resolved.rxPower = 0.0
    }

    return resolved;
    }
};

module.exports = GenericRanging;
