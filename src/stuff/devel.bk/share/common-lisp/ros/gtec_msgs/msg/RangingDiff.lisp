; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude RangingDiff.msg.html

(cl:defclass <RangingDiff> (roslisp-msg-protocol:ros-message)
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
    :type cl:float
    :initform 0.0)
   (distance
    :reader distance
    :initarg :distance
    :type cl:float
    :initform 0.0)
   (diff
    :reader diff
    :initarg :diff
    :type cl:float
    :initform 0.0))
)

(cl:defclass RangingDiff (<RangingDiff>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RangingDiff>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RangingDiff)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<RangingDiff> is deprecated: use gtec_msgs-msg:RangingDiff instead.")))

(cl:ensure-generic-function 'anchorId-val :lambda-list '(m))
(cl:defmethod anchorId-val ((m <RangingDiff>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:anchorId-val is deprecated.  Use gtec_msgs-msg:anchorId instead.")
  (anchorId m))

(cl:ensure-generic-function 'tagId-val :lambda-list '(m))
(cl:defmethod tagId-val ((m <RangingDiff>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:tagId-val is deprecated.  Use gtec_msgs-msg:tagId instead.")
  (tagId m))

(cl:ensure-generic-function 'range-val :lambda-list '(m))
(cl:defmethod range-val ((m <RangingDiff>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:range-val is deprecated.  Use gtec_msgs-msg:range instead.")
  (range m))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <RangingDiff>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:distance-val is deprecated.  Use gtec_msgs-msg:distance instead.")
  (distance m))

(cl:ensure-generic-function 'diff-val :lambda-list '(m))
(cl:defmethod diff-val ((m <RangingDiff>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:diff-val is deprecated.  Use gtec_msgs-msg:diff instead.")
  (diff m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RangingDiff>) ostream)
  "Serializes a message object of type '<RangingDiff>"
  (cl:let* ((signed (cl:slot-value msg 'anchorId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'tagId)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'range))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'distance))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'diff))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RangingDiff>) istream)
  "Deserializes a message object of type '<RangingDiff>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'anchorId) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'tagId) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'range) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'distance) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'diff) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RangingDiff>)))
  "Returns string type for a message object of type '<RangingDiff>"
  "gtec_msgs/RangingDiff")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RangingDiff)))
  "Returns string type for a message object of type 'RangingDiff"
  "gtec_msgs/RangingDiff")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RangingDiff>)))
  "Returns md5sum for a message object of type '<RangingDiff>"
  "c6a42b09b24a1d184442ec374c7c1cbf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RangingDiff)))
  "Returns md5sum for a message object of type 'RangingDiff"
  "c6a42b09b24a1d184442ec374c7c1cbf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RangingDiff>)))
  "Returns full string definition for message of type '<RangingDiff>"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%float32 range~%float32 distance~%float32 diff~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RangingDiff)))
  "Returns full string definition for message of type 'RangingDiff"
  (cl:format cl:nil "int16 anchorId~%int16 tagId~%float32 range~%float32 distance~%float32 diff~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RangingDiff>))
  (cl:+ 0
     2
     2
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RangingDiff>))
  "Converts a ROS message object to a list"
  (cl:list 'RangingDiff
    (cl:cons ':anchorId (anchorId msg))
    (cl:cons ':tagId (tagId msg))
    (cl:cons ':range (range msg))
    (cl:cons ':distance (distance msg))
    (cl:cons ':diff (diff msg))
))
