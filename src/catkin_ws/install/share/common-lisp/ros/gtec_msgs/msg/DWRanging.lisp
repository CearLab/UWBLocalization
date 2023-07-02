; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude DWRanging.msg.html

(cl:defclass <DWRanging> (roslisp-msg-protocol:ros-message)
  ((anchorId
    :reader anchorId
    :initarg :anchorId
    :type cl:fixnum
    :initform 0)
   (tagId
    :reader tagId
    :initarg :tagId
    :type cl:fixnum
    :initform 0)
   (range
    :reader range
    :initarg :range
    :type cl:integer
    :initform 0)
   (rawrange
    :reader rawrange
    :initarg :rawrange
    :type cl:integer
    :initform 0)
   (seq
    :reader seq
    :initarg :seq
    :type cl:integer
    :initform 0)
   (maxNoise
    :reader maxNoise
    :initarg :maxNoise
    :type cl:integer
    :initform 0)
   (stdNoise
    :reader stdNoise
    :initarg :stdNoise
    :type cl:integer
    :initform 0)
   (firstPathAmp1
    :reader firstPathAmp1
    :initarg :firstPathAmp1
    :type cl:integer
    :initform 0)
   (firstPathAmp2
    :reader firstPathAmp2
    :initarg :firstPathAmp2
    :type cl:integer
    :initform 0)
   (firstPathAmp3
    :reader firstPathAmp3
    :initarg :firstPathAmp3
    :type cl:integer
    :initform 0)
   (maxGrowthCIR
    :reader maxGrowthCIR
    :initarg :maxGrowthCIR
    :type cl:integer
    :initform 0)
   (rxPreamCount
    :reader rxPreamCount
    :initarg :rxPreamCount
    :type cl:integer
    :initform 0)
   (firstPath
    :reader firstPath
    :initarg :firstPath
    :type cl:integer
    :initform 0)
   (channel
    :reader channel
    :initarg :channel
    :type cl:float
    :initform 0.0)
   (prf
    :reader prf
    :initarg :prf
    :type cl:integer
    :initform 0)
   (datarate
    :reader datarate
    :initarg :datarate
    :type cl:float
    :initform 0.0)
   (preambleLength
    :reader preambleLength
    :initarg :preambleLength
    :type cl:integer
    :initform 0)
   (pacSize
    :reader pacSize
    :initarg :pacSize
    :type cl:integer
    :initform 0))
)

(cl:defclass DWRanging (<DWRanging>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <DWRanging>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'DWRanging)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<DWRanging> is deprecated: use gtec_msgs-msg:DWRanging instead.")))

(cl:ensure-generic-function 'anchorId-val :lambda-list '(m))
(cl:defmethod anchorId-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:anchorId-val is deprecated.  Use gtec_msgs-msg:anchorId instead.")
  (anchorId m))

(cl:ensure-generic-function 'tagId-val :lambda-list '(m))
(cl:defmethod tagId-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:tagId-val is deprecated.  Use gtec_msgs-msg:tagId instead.")
  (tagId m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:range-val is deprecated.  Use gtec_msgs-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'rawrange-val :lambda-list '(m))
(cl:defmethod rawrange-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rawrange-val is deprecated.  Use gtec_msgs-msg:rawrange instead.")
  (rawrange m))

(cl:ensure-generic-function 'seq-val :lambda-list '(m))
(cl:defmethod seq-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:seq-val is deprecated.  Use gtec_msgs-msg:seq instead.")
  (seq m))

(cl:ensure-generic-function 'maxNoise-val :lambda-list '(m))
(cl:defmethod maxNoise-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:maxNoise-val is deprecated.  Use gtec_msgs-msg:maxNoise instead.")
  (maxNoise m))

(cl:ensure-generic-function 'stdNoise-val :lambda-list '(m))
(cl:defmethod stdNoise-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:stdNoise-val is deprecated.  Use gtec_msgs-msg:stdNoise instead.")
  (stdNoise m))

(cl:ensure-generic-function 'firstPathAmp1-val :lambda-list '(m))
(cl:defmethod firstPathAmp1-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:firstPathAmp1-val is deprecated.  Use gtec_msgs-msg:firstPathAmp1 instead.")
  (firstPathAmp1 m))

(cl:ensure-generic-function 'firstPathAmp2-val :lambda-list '(m))
(cl:defmethod firstPathAmp2-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:firstPathAmp2-val is deprecated.  Use gtec_msgs-msg:firstPathAmp2 instead.")
  (firstPathAmp2 m))

(cl:ensure-generic-function 'firstPathAmp3-val :lambda-list '(m))
(cl:defmethod firstPathAmp3-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:firstPathAmp3-val is deprecated.  Use gtec_msgs-msg:firstPathAmp3 instead.")
  (firstPathAmp3 m))

(cl:ensure-generic-function 'maxGrowthCIR-val :lambda-list '(m))
(cl:defmethod maxGrowthCIR-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:maxGrowthCIR-val is deprecated.  Use gtec_msgs-msg:maxGrowthCIR instead.")
  (maxGrowthCIR m))

(cl:ensure-generic-function 'rxPreamCount-val :lambda-list '(m))
(cl:defmethod rxPreamCount-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rxPreamCount-val is deprecated.  Use gtec_msgs-msg:rxPreamCount instead.")
  (rxPreamCount m))

(cl:ensure-generic-function 'firstPath-val :lambda-list '(m))
(cl:defmethod firstPath-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:firstPath-val is deprecated.  Use gtec_msgs-msg:firstPath instead.")
  (firstPath m))

(cl:ensure-generic-function 'channel-val :lambda-list '(m))
(cl:defmethod channel-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:channel-val is deprecated.  Use gtec_msgs-msg:channel instead.")
  (channel m))

(cl:ensure-generic-function 'prf-val :lambda-list '(m))
(cl:defmethod prf-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:prf-val is deprecated.  Use gtec_msgs-msg:prf instead.")
  (prf m))

(cl:ensure-generic-function 'datarate-val :lambda-list '(m))
(cl:defmethod datarate-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:datarate-val is deprecated.  Use gtec_msgs-msg:datarate instead.")
  (datarate m))

(cl:ensure-generic-function 'preambleLength-val :lambda-list '(m))
(cl:defmethod preambleLength-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:preambleLength-val is deprecated.  Use gtec_msgs-msg:preambleLength instead.")
  (preambleLength m))

(cl:ensure-generic-function 'pacSize-val :lambda-list '(m))
(cl:defmethod pacSize-val ((m <DWRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:pacSize-val is deprecated.  Use gtec_msgs-msg:pacSize instead.")
  (pacSize m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <DWRanging>) ostream)
  "Serializes a message object of type '<DWRanging>"
  (cl:let* ((signed (cl:slot-value msg 'anchorId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'tagId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'range)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rawrange)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'seq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'maxNoise)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'stdNoise)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'firstPathAmp1)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'firstPathAmp2)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'firstPathAmp3)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'maxGrowthCIR)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rxPreamCount)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'firstPath)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'channel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'prf)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'datarate))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'preambleLength)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'pacSize)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <DWRanging>) istream)
  "Deserializes a message object of type '<DWRanging>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'anchorId) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'tagId) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'range) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rawrange) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'seq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'maxNoise) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'stdNoise) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firstPathAmp1) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firstPathAmp2) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firstPathAmp3) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'maxGrowthCIR) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rxPreamCount) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'firstPath) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'channel) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'prf) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'datarate) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'preambleLength) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'pacSize) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<DWRanging>)))
  "Returns string type for a message object of type '<DWRanging>"
  "gtec_msgs/DWRanging")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'DWRanging)))
  "Returns string type for a message object of type 'DWRanging"
  "gtec_msgs/DWRanging")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<DWRanging>)))
  "Returns md5sum for a message object of type '<DWRanging>"
  "9c822fd6a75d14f97f7679d0a373d617")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'DWRanging)))
  "Returns md5sum for a message object of type 'DWRanging"
  "9c822fd6a75d14f97f7679d0a373d617")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<DWRanging>)))
  "Returns full string definition for message of type '<DWRanging>"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%int32 range~%int32 rawrange~%int32 seq~%int32 maxNoise~%int32 stdNoise~%int32 firstPathAmp1~%int32 firstPathAmp2~%int32 firstPathAmp3~%int32 maxGrowthCIR~%int32 rxPreamCount~%int32 firstPath~%float64 channel~%int32 prf~%float64 datarate~%int32 preambleLength~%int32 pacSize~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'DWRanging)))
  "Returns full string definition for message of type 'DWRanging"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%int32 range~%int32 rawrange~%int32 seq~%int32 maxNoise~%int32 stdNoise~%int32 firstPathAmp1~%int32 firstPathAmp2~%int32 firstPathAmp3~%int32 maxGrowthCIR~%int32 rxPreamCount~%int32 firstPath~%float64 channel~%int32 prf~%float64 datarate~%int32 preambleLength~%int32 pacSize~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <DWRanging>))
  (cl:+ 0
     2
     2
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     4
     8
     4
     8
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <DWRanging>))
  "Converts a ROS message object to a list"
  (cl:list 'DWRanging
    (cl:cons ':anchorId (anchorId msg))
    (cl:cons ':tagId (tagId msg))
    (cl:cons ':range (range msg))
    (cl:cons ':rawrange (rawrange msg))
    (cl:cons ':seq (seq msg))
    (cl:cons ':maxNoise (maxNoise msg))
    (cl:cons ':stdNoise (stdNoise msg))
    (cl:cons ':firstPathAmp1 (firstPathAmp1 msg))
    (cl:cons ':firstPathAmp2 (firstPathAmp2 msg))
    (cl:cons ':firstPathAmp3 (firstPathAmp3 msg))
    (cl:cons ':maxGrowthCIR (maxGrowthCIR msg))
    (cl:cons ':rxPreamCount (rxPreamCount msg))
    (cl:cons ':firstPath (firstPath msg))
    (cl:cons ':channel (channel msg))
    (cl:cons ':prf (prf msg))
    (cl:cons ':datarate (datarate msg))
    (cl:cons ':preambleLength (preambleLength msg))
    (cl:cons ':pacSize (pacSize msg))
))
