; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude Ranging.msg.html

(cl:defclass <Ranging> (roslisp-msg-protocol:ros-message)
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
   (seq
    :reader seq
    :initarg :seq
    :type cl:integer
    :initform 0)
   (rss
    :reader rss
    :initarg :rss
    :type cl:float
    :initform 0.0)
   (errorEstimation
    :reader errorEstimation
    :initarg :errorEstimation
    :type cl:float
    :initform 0.0))
)

(cl:defclass Ranging (<Ranging>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Ranging>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Ranging)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<Ranging> is deprecated: use gtec_msgs-msg:Ranging instead.")))

(cl:ensure-generic-function 'anchorId-val :lambda-list '(m))
(cl:defmethod anchorId-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:anchorId-val is deprecated.  Use gtec_msgs-msg:anchorId instead.")
  (anchorId m))

(cl:ensure-generic-function 'tagId-val :lambda-list '(m))
(cl:defmethod tagId-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:tagId-val is deprecated.  Use gtec_msgs-msg:tagId instead.")
  (tagId m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:range-val is deprecated.  Use gtec_msgs-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'seq-val :lambda-list '(m))
(cl:defmethod seq-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:seq-val is deprecated.  Use gtec_msgs-msg:seq instead.")
  (seq m))

(cl:ensure-generic-function 'rss-val :lambda-list '(m))
(cl:defmethod rss-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rss-val is deprecated.  Use gtec_msgs-msg:rss instead.")
  (rss m))

(cl:ensure-generic-function 'errorEstimation-val :lambda-list '(m))
(cl:defmethod errorEstimation-val ((m <Ranging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:errorEstimation-val is deprecated.  Use gtec_msgs-msg:errorEstimation instead.")
  (errorEstimation m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Ranging>) ostream)
  "Serializes a message object of type '<Ranging>"
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
  (cl:let* ((signed (cl:slot-value msg 'seq)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'rss))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'errorEstimation))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Ranging>) istream)
  "Deserializes a message object of type '<Ranging>"
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
    (cl:setf (cl:slot-value msg 'rss) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'errorEstimation) (roslisp-utils:decode-double-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Ranging>)))
  "Returns string type for a message object of type '<Ranging>"
  "gtec_msgs/Ranging")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Ranging)))
  "Returns string type for a message object of type 'Ranging"
  "gtec_msgs/Ranging")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Ranging>)))
  "Returns md5sum for a message object of type '<Ranging>"
  "d30ca10e8481651a0f8849efb5e0d638")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Ranging)))
  "Returns md5sum for a message object of type 'Ranging"
  "d30ca10e8481651a0f8849efb5e0d638")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Ranging>)))
  "Returns full string definition for message of type '<Ranging>"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%int32 range~%int32 seq~%float64 rss~%float64 errorEstimation~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Ranging)))
  "Returns full string definition for message of type 'Ranging"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%int32 range~%int32 seq~%float64 rss~%float64 errorEstimation~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Ranging>))
  (cl:+ 0
     2
     2
     4
     4
     8
     8
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Ranging>))
  "Converts a ROS message object to a list"
  (cl:list 'Ranging
    (cl:cons ':anchorId (anchorId msg))
    (cl:cons ':tagId (tagId msg))
    (cl:cons ':range (range msg))
    (cl:cons ':seq (seq msg))
    (cl:cons ':rss (rss msg))
    (cl:cons ':errorEstimation (errorEstimation msg))
))
