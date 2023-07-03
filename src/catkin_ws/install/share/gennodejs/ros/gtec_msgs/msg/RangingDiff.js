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

class RangingDiff {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.anchorId = null;
      this.tagId = null;
      this.range = null;
      this.distance = null;
      this.diff = null;
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
        this.range = 0.0;
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0.0;
      }
      if (initObj.hasOwnProperty('diff')) {
        this.diff = initObj.diff
      }
      else {
        this.diff = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type RangingDiff
    // Serialize message field [anchorId]
    bufferOffset = _serializer.int16(obj.anchorId, buffer, bufferOffset);
    // Serialize message field [tagId]
    bufferOffset = _serializer.int16(obj.tagId, buffer, bufferOffset);
    // Serialize message field [range]
    bufferOffset = _serializer.float32(obj.range, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = _serializer.float32(obj.distance, buffer, bufferOffset);
    // Serialize message field [diff]
    bufferOffset = _serializer.float32(obj.diff, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type RangingDiff
    let len;
    let data = new RangingDiff(null);
    // Deserialize message field [anchorId]
    data.anchorId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [tagId]
    data.tagId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [diff]
    data.diff = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/RangingDiff';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c6a42b09b24a1d184442ec374c7c1cbf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 anchorId
    int16 tagId
    float32 range
    float32 distance
    float32 diff
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new RangingDiff(null);
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
      resolved.range = 0.0
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0.0
    }

    if (msg.diff !== undefined) {
      resolved.diff = msg.diff;
    }
    else {
      resolved.diff = 0.0
    }

    return resolved;
    }
};

module.exports = RangingDiff;
