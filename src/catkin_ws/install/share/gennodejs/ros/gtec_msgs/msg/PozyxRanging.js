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

class PozyxRanging {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.originId = null;
      this.originType = null;
      this.destinationId = null;
      this.destinationType = null;
      this.range = null;
      this.ts = null;
      this.seq = null;
      this.rxPower = null;
      this.channel = null;
      this.datarate = null;
      this.prf = null;
      this.preambleLength = null;
      this.txGain = null;
      this.angle = null;
    }
    else {
      if (initObj.hasOwnProperty('originId')) {
        this.originId = initObj.originId
      }
      else {
        this.originId = 0;
      }
      if (initObj.hasOwnProperty('originType')) {
        this.originType = initObj.originType
      }
      else {
        this.originType = 0;
      }
      if (initObj.hasOwnProperty('destinationId')) {
        this.destinationId = initObj.destinationId
      }
      else {
        this.destinationId = 0;
      }
      if (initObj.hasOwnProperty('destinationType')) {
        this.destinationType = initObj.destinationType
      }
      else {
        this.destinationType = 0;
      }
      if (initObj.hasOwnProperty('range')) {
        this.range = initObj.range
      }
      else {
        this.range = 0;
      }
      if (initObj.hasOwnProperty('ts')) {
        this.ts = initObj.ts
      }
      else {
        this.ts = 0;
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
      if (initObj.hasOwnProperty('channel')) {
        this.channel = initObj.channel
      }
      else {
        this.channel = 0.0;
      }
      if (initObj.hasOwnProperty('datarate')) {
        this.datarate = initObj.datarate
      }
      else {
        this.datarate = 0.0;
      }
      if (initObj.hasOwnProperty('prf')) {
        this.prf = initObj.prf
      }
      else {
        this.prf = 0;
      }
      if (initObj.hasOwnProperty('preambleLength')) {
        this.preambleLength = initObj.preambleLength
      }
      else {
        this.preambleLength = 0;
      }
      if (initObj.hasOwnProperty('txGain')) {
        this.txGain = initObj.txGain
      }
      else {
        this.txGain = 0.0;
      }
      if (initObj.hasOwnProperty('angle')) {
        this.angle = initObj.angle
      }
      else {
        this.angle = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PozyxRanging
    // Serialize message field [originId]
    bufferOffset = _serializer.int32(obj.originId, buffer, bufferOffset);
    // Serialize message field [originType]
    bufferOffset = _serializer.int16(obj.originType, buffer, bufferOffset);
    // Serialize message field [destinationId]
    bufferOffset = _serializer.int32(obj.destinationId, buffer, bufferOffset);
    // Serialize message field [destinationType]
    bufferOffset = _serializer.int16(obj.destinationType, buffer, bufferOffset);
    // Serialize message field [range]
    bufferOffset = _serializer.int32(obj.range, buffer, bufferOffset);
    // Serialize message field [ts]
    bufferOffset = _serializer.int32(obj.ts, buffer, bufferOffset);
    // Serialize message field [seq]
    bufferOffset = _serializer.int32(obj.seq, buffer, bufferOffset);
    // Serialize message field [rxPower]
    bufferOffset = _serializer.float64(obj.rxPower, buffer, bufferOffset);
    // Serialize message field [channel]
    bufferOffset = _serializer.float64(obj.channel, buffer, bufferOffset);
    // Serialize message field [datarate]
    bufferOffset = _serializer.float64(obj.datarate, buffer, bufferOffset);
    // Serialize message field [prf]
    bufferOffset = _serializer.int32(obj.prf, buffer, bufferOffset);
    // Serialize message field [preambleLength]
    bufferOffset = _serializer.int32(obj.preambleLength, buffer, bufferOffset);
    // Serialize message field [txGain]
    bufferOffset = _serializer.float64(obj.txGain, buffer, bufferOffset);
    // Serialize message field [angle]
    bufferOffset = _serializer.float64(obj.angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PozyxRanging
    let len;
    let data = new PozyxRanging(null);
    // Deserialize message field [originId]
    data.originId = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [originType]
    data.originType = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [destinationId]
    data.destinationId = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [destinationType]
    data.destinationType = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [ts]
    data.ts = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [seq]
    data.seq = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [rxPower]
    data.rxPower = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [channel]
    data.channel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [datarate]
    data.datarate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [prf]
    data.prf = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [preambleLength]
    data.preambleLength = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [txGain]
    data.txGain = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [angle]
    data.angle = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 72;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/PozyxRanging';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '2b846533027dd07c0ff5d2424addc37b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32 originId
    int16 originType
    int32 destinationId
    int16 destinationType
    int32 range
    int32 ts
    int32 seq
    float64 rxPower
    float64 channel
    float64 datarate
    int32 prf
    int32 preambleLength
    float64 txGain
    float64 angle
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PozyxRanging(null);
    if (msg.originId !== undefined) {
      resolved.originId = msg.originId;
    }
    else {
      resolved.originId = 0
    }

    if (msg.originType !== undefined) {
      resolved.originType = msg.originType;
    }
    else {
      resolved.originType = 0
    }

    if (msg.destinationId !== undefined) {
      resolved.destinationId = msg.destinationId;
    }
    else {
      resolved.destinationId = 0
    }

    if (msg.destinationType !== undefined) {
      resolved.destinationType = msg.destinationType;
    }
    else {
      resolved.destinationType = 0
    }

    if (msg.range !== undefined) {
      resolved.range = msg.range;
    }
    else {
      resolved.range = 0
    }

    if (msg.ts !== undefined) {
      resolved.ts = msg.ts;
    }
    else {
      resolved.ts = 0
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

    if (msg.channel !== undefined) {
      resolved.channel = msg.channel;
    }
    else {
      resolved.channel = 0.0
    }

    if (msg.datarate !== undefined) {
      resolved.datarate = msg.datarate;
    }
    else {
      resolved.datarate = 0.0
    }

    if (msg.prf !== undefined) {
      resolved.prf = msg.prf;
    }
    else {
      resolved.prf = 0
    }

    if (msg.preambleLength !== undefined) {
      resolved.preambleLength = msg.preambleLength;
    }
    else {
      resolved.preambleLength = 0
    }

    if (msg.txGain !== undefined) {
      resolved.txGain = msg.txGain;
    }
    else {
      resolved.txGain = 0.0
    }

    if (msg.angle !== undefined) {
      resolved.angle = msg.angle;
    }
    else {
      resolved.angle = 0.0
    }

    return resolved;
    }
};

module.exports = PozyxRanging;
