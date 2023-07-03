; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude PozyxRangingWithCir.msg.html

(cl:defclass <PozyxRangingWithCir> (roslisp-msg-protocol:ros-message)
  ((originId
    :reader originId
    :initarg :originId
    :type cl:integer
    :initform 0)
   (originType
    :reader originType
    :initarg :originType
    :type cl:fixnum
    :initform 0)
   (destinationId
    :reader destinationId
    :initarg :destinationId
    :type cl:integer
    :initform 0)
   (destinationType
    :reader destinationType
    :initarg :destinationType
    :type cl:fixnum
    :initform 0)
   (range
    :reader range
    :initarg :range
    :type cl:integer
    :initform 0)
   (ts
    :reader ts
    :initarg :ts
    :type cl:integer
    :initform 0)
   (seq
    :reader seq
    :initarg :seq
    :type cl:integer
    :initform 0)
   (rxPower
    :reader rxPower
    :initarg :rxPower
    :type cl:float
    :initform 0.0)
   (channel
    :reader channel
    :initarg :channel
    :type cl:float
    :initform 0.0)
   (datarate
    :reader datarate
    :initarg :datarate
    :type cl:float
    :initform 0.0)
   (prf
    :reader prf
    :initarg :prf
    :type cl:integer
    :initform 0)
   (preambleLength
    :reader preambleLength
    :initarg :preambleLength
    :type cl:integer
    :initform 0)
   (txGain
    :reader txGain
    :initarg :txGain
    :type cl:float
    :initform 0.0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:float
    :initform 0.0)
   (cir
    :reader cir
    :initarg :cir
    :type (cl:vector cl:fixnum)
   :initform (cl:make-array 0 :element-type 'cl:fixnum :initial-element 0)))
)

(cl:defclass PozyxRangingWithCir (<PozyxRangingWithCir>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <PozyxRangingWithCir>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'PozyxRangingWithCir)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<PozyxRangingWithCir> is deprecated: use gtec_msgs-msg:PozyxRangingWithCir instead.")))

(cl:ensure-generic-function 'originId-val :lambda-list '(m))
(cl:defmethod originId-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:originId-val is deprecated.  Use gtec_msgs-msg:originId instead.")
  (originId m))

(cl:ensure-generic-function 'originType-val :lambda-list '(m))
(cl:defmethod originType-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:originType-val is deprecated.  Use gtec_msgs-msg:originType instead.")
  (originType m))

(cl:ensure-generic-function 'destinationId-val :lambda-list '(m))
(cl:defmethod destinationId-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:destinationId-val is deprecated.  Use gtec_msgs-msg:destinationId instead.")
  (destinationId m))

(cl:ensure-generic-function 'destinationType-val :lambda-list '(m))
(cl:defmethod destinationType-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:destinationType-val is deprecated.  Use gtec_msgs-msg:destinationType instead.")
  (destinationType m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:range-val is deprecated.  Use gtec_msgs-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'ts-val :lambda-list '(m))
(cl:defmethod ts-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:ts-val is deprecated.  Use gtec_msgs-msg:ts instead.")
  (ts m))

(cl:ensure-generic-function 'seq-val :lambda-list '(m))
(cl:defmethod seq-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:seq-val is deprecated.  Use gtec_msgs-msg:seq instead.")
  (seq m))

(cl:ensure-generic-function 'rxPower-val :lambda-list '(m))
(cl:defmethod rxPower-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rxPower-val is deprecated.  Use gtec_msgs-msg:rxPower instead.")
  (rxPower m))

(cl:ensure-generic-function 'channel-val :lambda-list '(m))
(cl:defmethod channel-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:channel-val is deprecated.  Use gtec_msgs-msg:channel instead.")
  (channel m))

(cl:ensure-generic-function 'datarate-val :lambda-list '(m))
(cl:defmethod datarate-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:datarate-val is deprecated.  Use gtec_msgs-msg:datarate instead.")
  (datarate m))

(cl:ensure-generic-function 'prf-val :lambda-list '(m))
(cl:defmethod prf-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:prf-val is deprecated.  Use gtec_msgs-msg:prf instead.")
  (prf m))

(cl:ensure-generic-function 'preambleLength-val :lambda-list '(m))
(cl:defmethod preambleLength-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:preambleLength-val is deprecated.  Use gtec_msgs-msg:preambleLength instead.")
  (preambleLength m))

(cl:ensure-generic-function 'txGain-val :lambda-list '(m))
(cl:defmethod txGain-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:txGain-val is deprecated.  Use gtec_msgs-msg:txGain instead.")
  (txGain m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:angle-val is deprecated.  Use gtec_msgs-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'cir-val :lambda-list '(m))
(cl:defmethod cir-val ((m <PozyxRangingWithCir>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:cir-val is deprecated.  Use gtec_msgs-msg:cir instead.")
  (cir m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <PozyxRangingWithCir>) ostream)
  "Serializes a message object of type '<PozyxRangingWithCir>"
  (cl:let* ((signed (cl:slot-value msg 'originId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'originType)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'destinationId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'destinationType)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'range)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'ts)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
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
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rxPower))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'channel))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'datarate))))
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
  (cl:let* ((signed (cl:slot-value msg 'preambleLength)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'txGain))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'angle))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'cir))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    ))
   (cl:slot-value msg 'cir))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <PozyxRangingWithCir>) istream)
  "Deserializes a message object of type '<PozyxRangingWithCir>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'originId) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'originType) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'destinationId) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'destinationType) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
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
      (cl:setf (cl:slot-value msg 'ts) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'seq) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'rxPower) (roslisp-utils:decode-double-float-bits bits)))
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
      (cl:setf (cl:slot-value msg 'prf) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'preambleLength) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'txGain) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'angle) (roslisp-utils:decode-double-float-bits bits)))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'cir) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'cir)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536)))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<PozyxRangingWithCir>)))
  "Returns string type for a message object of type '<PozyxRangingWithCir>"
  "gtec_msgs/PozyxRangingWithCir")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'PozyxRangingWithCir)))
  "Returns string type for a message object of type 'PozyxRangingWithCir"
  "gtec_msgs/PozyxRangingWithCir")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<PozyxRangingWithCir>)))
  "Returns md5sum for a message object of type '<PozyxRangingWithCir>"
  "57228d0a630edec43d8b895ec4dc9202")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'PozyxRangingWithCir)))
  "Returns md5sum for a message object of type 'PozyxRangingWithCir"
  "57228d0a630edec43d8b895ec4dc9202")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<PozyxRangingWithCir>)))
  "Returns full string definition for message of type '<PozyxRangingWithCir>"
  (cl:format cl:nil "int32 originId~%int16 originType~%int32 destinationId~%int16 destinationType~%int32 range~%int32 ts~%int32 seq~%float64 rxPower~%float64 channel~%float64 datarate~%int32 prf~%int32 preambleLength~%float64 txGain~%float64 angle~%int16[] cir~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'PozyxRangingWithCir)))
  "Returns full string definition for message of type 'PozyxRangingWithCir"
  (cl:format cl:nil "int32 originId~%int16 originType~%int32 destinationId~%int16 destinationType~%int32 range~%int32 ts~%int32 seq~%float64 rxPower~%float64 channel~%float64 datarate~%int32 prf~%int32 preambleLength~%float64 txGain~%float64 angle~%int16[] cir~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <PozyxRangingWithCir>))
  (cl:+ 0
     4
     2
     4
     2
     4
     4
     4
     8
     8
     8
     4
     4
     8
     8
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'cir) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 2)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <PozyxRangingWithCir>))
  "Converts a ROS message object to a list"
  (cl:list 'PozyxRangingWithCir
    (cl:cons ':originId (originId msg))
    (cl:cons ':originType (originType msg))
    (cl:cons ':destinationId (destinationId msg))
    (cl:cons ':destinationType (destinationType msg))
    (cl:cons ':range (range msg))
    (cl:cons ':ts (ts msg))
    (cl:cons ':seq (seq msg))
    (cl:cons ':rxPower (rxPower msg))
    (cl:cons ':channel (channel msg))
    (cl:cons ':datarate (datarate msg))
    (cl:cons ':prf (prf msg))
    (cl:cons ':preambleLength (preambleLength msg))
    (cl:cons ':txGain (txGain msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':cir (cir msg))
))
