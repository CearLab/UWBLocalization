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

class UWBRanging {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.anchorId = null;
      this.tagId = null;
      this.range = null;
      this.rawrange = null;
      this.biasCorrection = null;
      this.seq = null;
      this.maxNoise = null;
      this.stdNoise = null;
      this.firstPathAmp1 = null;
      this.firstPathAmp2 = null;
      this.firstPathAmp3 = null;
      this.maxGrowthCIR = null;
      this.rxPreamCount = null;
      this.firstPath = null;
      this.channel = null;
      this.prf = null;
      this.datarate = null;
      this.preambleLength = null;
      this.pacSize = null;
      this.errorEstimation = null;
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
      if (initObj.hasOwnProperty('rawrange')) {
        this.rawrange = initObj.rawrange
      }
      else {
        this.rawrange = 0;
      }
      if (initObj.hasOwnProperty('biasCorrection')) {
        this.biasCorrection = initObj.biasCorrection
      }
      else {
        this.biasCorrection = 0;
      }
      if (initObj.hasOwnProperty('seq')) {
        this.seq = initObj.seq
      }
      else {
        this.seq = 0;
      }
      if (initObj.hasOwnProperty('maxNoise')) {
        this.maxNoise = initObj.maxNoise
      }
      else {
        this.maxNoise = 0;
      }
      if (initObj.hasOwnProperty('stdNoise')) {
        this.stdNoise = initObj.stdNoise
      }
      else {
        this.stdNoise = 0;
      }
      if (initObj.hasOwnProperty('firstPathAmp1')) {
        this.firstPathAmp1 = initObj.firstPathAmp1
      }
      else {
        this.firstPathAmp1 = 0;
      }
      if (initObj.hasOwnProperty('firstPathAmp2')) {
        this.firstPathAmp2 = initObj.firstPathAmp2
      }
      else {
        this.firstPathAmp2 = 0;
      }
      if (initObj.hasOwnProperty('firstPathAmp3')) {
        this.firstPathAmp3 = initObj.firstPathAmp3
      }
      else {
        this.firstPathAmp3 = 0;
      }
      if (initObj.hasOwnProperty('maxGrowthCIR')) {
        this.maxGrowthCIR = initObj.maxGrowthCIR
      }
      else {
        this.maxGrowthCIR = 0;
      }
      if (initObj.hasOwnProperty('rxPreamCount')) {
        this.rxPreamCount = initObj.rxPreamCount
      }
      else {
        this.rxPreamCount = 0;
      }
      if (initObj.hasOwnProperty('firstPath')) {
        this.firstPath = initObj.firstPath
      }
      else {
        this.firstPath = 0;
      }
      if (initObj.hasOwnProperty('channel')) {
        this.channel = initObj.channel
      }
      else {
        this.channel = 0.0;
      }
      if (initObj.hasOwnProperty('prf')) {
        this.prf = initObj.prf
      }
      else {
        this.prf = 0;
      }
      if (initObj.hasOwnProperty('datarate')) {
        this.datarate = initObj.datarate
      }
      else {
        this.datarate = 0.0;
      }
      if (initObj.hasOwnProperty('preambleLength')) {
        this.preambleLength = initObj.preambleLength
      }
      else {
        this.preambleLength = 0;
      }
      if (initObj.hasOwnProperty('pacSize')) {
        this.pacSize = initObj.pacSize
      }
      else {
        this.pacSize = 0;
      }
      if (initObj.hasOwnProperty('errorEstimation')) {
        this.errorEstimation = initObj.errorEstimation
      }
      else {
        this.errorEstimation = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type UWBRanging
    // Serialize message field [anchorId]
    bufferOffset = _serializer.int16(obj.anchorId, buffer, bufferOffset);
    // Serialize message field [tagId]
    bufferOffset = _serializer.int16(obj.tagId, buffer, bufferOffset);
    // Serialize message field [range]
    bufferOffset = _serializer.int32(obj.range, buffer, bufferOffset);
    // Serialize message field [rawrange]
    bufferOffset = _serializer.int32(obj.rawrange, buffer, bufferOffset);
    // Serialize message field [biasCorrection]
    bufferOffset = _serializer.int32(obj.biasCorrection, buffer, bufferOffset);
    // Serialize message field [seq]
    bufferOffset = _serializer.int32(obj.seq, buffer, bufferOffset);
    // Serialize message field [maxNoise]
    bufferOffset = _serializer.int32(obj.maxNoise, buffer, bufferOffset);
    // Serialize message field [stdNoise]
    bufferOffset = _serializer.int32(obj.stdNoise, buffer, bufferOffset);
    // Serialize message field [firstPathAmp1]
    bufferOffset = _serializer.int32(obj.firstPathAmp1, buffer, bufferOffset);
    // Serialize message field [firstPathAmp2]
    bufferOffset = _serializer.int32(obj.firstPathAmp2, buffer, bufferOffset);
    // Serialize message field [firstPathAmp3]
    bufferOffset = _serializer.int32(obj.firstPathAmp3, buffer, bufferOffset);
    // Serialize message field [maxGrowthCIR]
    bufferOffset = _serializer.int32(obj.maxGrowthCIR, buffer, bufferOffset);
    // Serialize message field [rxPreamCount]
    bufferOffset = _serializer.int32(obj.rxPreamCount, buffer, bufferOffset);
    // Serialize message field [firstPath]
    bufferOffset = _serializer.int32(obj.firstPath, buffer, bufferOffset);
    // Serialize message field [channel]
    bufferOffset = _serializer.float64(obj.channel, buffer, bufferOffset);
    // Serialize message field [prf]
    bufferOffset = _serializer.int32(obj.prf, buffer, bufferOffset);
    // Serialize message field [datarate]
    bufferOffset = _serializer.float64(obj.datarate, buffer, bufferOffset);
    // Serialize message field [preambleLength]
    bufferOffset = _serializer.int32(obj.preambleLength, buffer, bufferOffset);
    // Serialize message field [pacSize]
    bufferOffset = _serializer.int32(obj.pacSize, buffer, bufferOffset);
    // Serialize message field [errorEstimation]
    bufferOffset = _serializer.float64(obj.errorEstimation, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type UWBRanging
    let len;
    let data = new UWBRanging(null);
    // Deserialize message field [anchorId]
    data.anchorId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [tagId]
    data.tagId = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [range]
    data.range = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [rawrange]
    data.rawrange = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [biasCorrection]
    data.biasCorrection = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [seq]
    data.seq = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [maxNoise]
    data.maxNoise = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [stdNoise]
    data.stdNoise = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [firstPathAmp1]
    data.firstPathAmp1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [firstPathAmp2]
    data.firstPathAmp2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [firstPathAmp3]
    data.firstPathAmp3 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [maxGrowthCIR]
    data.maxGrowthCIR = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [rxPreamCount]
    data.rxPreamCount = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [firstPath]
    data.firstPath = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [channel]
    data.channel = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [prf]
    data.prf = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [datarate]
    data.datarate = _deserializer.float64(buffer, bufferOffset);
    // Deserialize message field [preambleLength]
    data.preambleLength = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [pacSize]
    data.pacSize = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [errorEstimation]
    data.errorEstimation = _deserializer.float64(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 88;
  }

  static datatype() {
    // Returns string type for a message object
    return 'gtec_msgs/UWBRanging';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a2ecb2ec6e49b5856c7d150d936a536b';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 anchorId
    int16 tagId
    int32 range
    int32 rawrange
    int32 biasCorrection
    int32 seq
    int32 maxNoise
    int32 stdNoise
    int32 firstPathAmp1
    int32 firstPathAmp2
    int32 firstPathAmp3
    int32 maxGrowthCIR
    int32 rxPreamCount
    int32 firstPath
    float64 channel
    int32 prf
    float64 datarate
    int32 preambleLength
    int32 pacSize
    float64 errorEstimation
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new UWBRanging(null);
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

    if (msg.rawrange !== undefined) {
      resolved.rawrange = msg.rawrange;
    }
    else {
      resolved.rawrange = 0
    }

    if (msg.biasCorrection !== undefined) {
      resolved.biasCorrection = msg.biasCorrection;
    }
    else {
      resolved.biasCorrection = 0
    }

    if (msg.seq !== undefined) {
      resolved.seq = msg.seq;
    }
    else {
      resolved.seq = 0
    }

    if (msg.maxNoise !== undefined) {
      resolved.maxNoise = msg.maxNoise;
    }
    else {
      resolved.maxNoise = 0
    }

    if (msg.stdNoise !== undefined) {
      resolved.stdNoise = msg.stdNoise;
    }
    else {
      resolved.stdNoise = 0
    }

    if (msg.firstPathAmp1 !== undefined) {
      resolved.firstPathAmp1 = msg.firstPathAmp1;
    }
    else {
      resolved.firstPathAmp1 = 0
    }

    if (msg.firstPathAmp2 !== undefined) {
      resolved.firstPathAmp2 = msg.firstPathAmp2;
    }
    else {
      resolved.firstPathAmp2 = 0
    }

    if (msg.firstPathAmp3 !== undefined) {
      resolved.firstPathAmp3 = msg.firstPathAmp3;
    }
    else {
      resolved.firstPathAmp3 = 0
    }

    if (msg.maxGrowthCIR !== undefined) {
      resolved.maxGrowthCIR = msg.maxGrowthCIR;
    }
    else {
      resolved.maxGrowthCIR = 0
    }

    if (msg.rxPreamCount !== undefined) {
      resolved.rxPreamCount = msg.rxPreamCount;
    }
    else {
      resolved.rxPreamCount = 0
    }

    if (msg.firstPath !== undefined) {
      resolved.firstPath = msg.firstPath;
    }
    else {
      resolved.firstPath = 0
    }

    if (msg.channel !== undefined) {
      resolved.channel = msg.channel;
    }
    else {
      resolved.channel = 0.0
    }

    if (msg.prf !== undefined) {
      resolved.prf = msg.prf;
    }
    else {
      resolved.prf = 0
    }

    if (msg.datarate !== undefined) {
      resolved.datarate = msg.datarate;
    }
    else {
      resolved.datarate = 0.0
    }

    if (msg.preambleLength !== undefined) {
      resolved.preambleLength = msg.preambleLength;
    }
    else {
      resolved.preambleLength = 0
    }

    if (msg.pacSize !== undefined) {
      resolved.pacSize = msg.pacSize;
    }
    else {
      resolved.pacSize = 0
    }

    if (msg.errorEstimation !== undefined) {
      resolved.errorEstimation = msg.errorEstimation;
    }
    else {
      resolved.errorEstimation = 0.0
    }

    return resolved;
    }
};

module.exports = UWBRanging;
