// Auto-generated. Do not edit!

// (in-package gtec_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let ESP32S2FTMFrame = require('./ESP32S2FTMFrame.js');

//-----------------------------------------------------------

class ESP32S2FTMRangingExtra {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.anchorId = null;
      this.rtt_est = null;
      this.rtt_raw = null;
      this.dist_est = null;
      this.own_est = null;
      this.num_frames = null;
      this.frames = null;
    }
    else {
      if (initObj.hasOwnProperty('anchorId')) {
        this.anchorId = initObj.anchorId
      }
      else {
        this.anchorId = '';
      }
      if (initObj.hasOwnProperty('rtt_est')) {
        this.rtt_est = initObj.rtt_est
      }
      else {
        this.rtt_est = 0;
      }
      if (initObj.hasOwnProperty('rtt_raw')) {
        this.rtt_raw = initObj.rtt_raw
      }
      else {
        this.rtt_raw = 0;
      }
      if (initObj.hasOwnProperty('dist_est')) {
        this.dist_est = initObj.dist_est
      }
      else {
        this.dist_est = 0.0;
      }
      if (initObj.hasOwnProperty('own_est')) {
        this.own_est = initObj.own_est
      }
      else {
        this.own_est = 0.0;
      }
      if (initObj.hasOwnProperty('num_frames')) {
        this.num_frames = initObj.num_frames
      }
      else {
        this.num_frames = 0;
      }
      if (initObj.hasOwnProperty('frames')) {
        this.frames = initObj.frames
      }
      else {
        this.frames = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type ESP32S2FTMRangingExtra
    // Serialize message field [anchorId]
    bufferOffset = _serializer.string(obj.anchorId, buffer, bufferOffset);
    // Serialize message field [rtt_est]
    bufferOffset = _serializer.int32(obj.rtt_est, buffer, bufferOffset);
    // Serialize message field [rtt_raw]
    bufferOffset = _serializer.int32(obj.rtt_raw, buffer, bufferOffset);
    // Serialize message field [dist_est]
    bufferOffset = _serializer.float32(obj.dist_est, buffer, bufferOffset);
    // Serialize message field [own_est]
    bufferOffset = _serializer.float32(obj.own_est, buffer, bufferOffset);
    // Serialize message field [num_frames]
    bufferOffset = _serializer.int32(obj.num_frames, buffer, bufferOffset);
    // Serialize message field [frames]
    // Serialize the length for message field [frames]
    bufferOffset = _serializer.uint32(obj.frames.length, buffer, bufferOffset);
    obj.frames.forEach((val) => {
      bufferOffset = ESP32S2FTMFrame.serialize(val, buffer, bufferOffset);
    });
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type ESP32S2FTMRangingExtra
    let len;
    let data = new ESP32S2FTMRangingExtra(null);
    // Deserialize message field [anchorId]
    data.anchorId = _deserializer.string(buffer, bufferOffset);
    // Deserialize message field [rtt_est]
    data.rtt_est = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [rtt_raw]
    data.rtt_raw = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [dist_est]
    data.dist_est = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [own_est]
    data.own_est = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [num_frames]
    data.num_frames = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [frames]
    // Deserialize array length for message field [frames]
    len = _deserializer.uint32(buffer, bufferOffset);
    data.frames = new Array(len);
    for (let i = 0; i < len; ++i) {
      data.frames[i] = ESP32S2FTMFrame.deserialize(buffer, bufferOffset)
    }
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += object.anchorId.length;
    length += 40 * object.frames.length;
    return length + 28;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/ESP32S2FTMRangingExtra';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '6ee26c63cfee1bff93dc663fa5bfe36d';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    string anchorId
    int32 rtt_est
    int32 rtt_raw
    float32 dist_est
    float32 own_est
    int32 num_frames
    gtec_msgs/ESP32S2FTMFrame[] frames
    
    ================================================================================
    MSG: gtec_msgs/ESP32S2FTMFrame
    int32 rssi
    int32 rtt
    int64 t1
    int64 t2
    int64 t3
    int64 t4
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new ESP32S2FTMRangingExtra(null);
    if (msg.anchorId !== undefined) {
      resolved.anchorId = msg.anchorId;
    }
    else {
      resolved.anchorId = ''
    }

    if (msg.rtt_est !== undefined) {
      resolved.rtt_est = msg.rtt_est;
    }
    else {
      resolved.rtt_est = 0
    }

    if (msg.rtt_raw !== undefined) {
      resolved.rtt_raw = msg.rtt_raw;
    }
    else {
      resolved.rtt_raw = 0
    }

    if (msg.dist_est !== undefined) {
      resolved.dist_est = msg.dist_est;
    }
    else {
      resolved.dist_est = 0.0
    }

    if (msg.own_est !== undefined) {
      resolved.own_est = msg.own_est;
    }
    else {
      resolved.own_est = 0.0
    }

    if (msg.num_frames !== undefined) {
      resolved.num_frames = msg.num_frames;
    }
    else {
      resolved.num_frames = 0
    }

    if (msg.frames !== undefined) {
      resolved.frames = new Array(msg.frames.length);
      for (let i = 0; i < resolved.frames.length; ++i) {
        resolved.frames[i] = ESP32S2FTMFrame.Resolve(msg.frames[i]);
      }
    }
    else {
      resolved.frames = []
    }

    return resolved;
    }
};

module.exports = ESP32S2FTMRangingExtra;
