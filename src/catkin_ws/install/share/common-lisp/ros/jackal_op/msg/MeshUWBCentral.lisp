; Auto-generated. Do not edit!


(cl:in-package jackal_op-msg)


;//! \htmlinclude MeshUWBCentral.msg.html

(cl:defclass <MeshUWBCentral> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (DC
    :reader DC
    :initarg :DC
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass MeshUWBCentral (<MeshUWBCentral>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <MeshUWBCentral>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'MeshUWBCentral)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name jackal_op-msg:<MeshUWBCentral> is deprecated: use jackal_op-msg:MeshUWBCentral instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <MeshUWBCentral>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_op-msg:header-val is deprecated.  Use jackal_op-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'DC-val :lambda-list '(m))
(cl:defmethod DC-val ((m <MeshUWBCentral>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader jackal_op-msg:DC-val is deprecated.  Use jackal_op-msg:DC instead.")
  (DC m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <MeshUWBCentral>) ostream)
  "Serializes a message object of type '<MeshUWBCentral>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'DC))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'DC))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <MeshUWBCentral>) istream)
  "Deserializes a message object of type '<MeshUWBCentral>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'DC) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'DC)))
    (cl:dotimes (i __ros_arr_len)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<MeshUWBCentral>)))
  "Returns string type for a message object of type '<MeshUWBCentral>"
  "jackal_op/MeshUWBCentral")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'MeshUWBCentral)))
  "Returns string type for a message object of type 'MeshUWBCentral"
  "jackal_op/MeshUWBCentral")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<MeshUWBCentral>)))
  "Returns md5sum for a message object of type '<MeshUWBCentral>"
  "5bbc7e1874ce4e720dbb04b3a0e1e74b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'MeshUWBCentral)))
  "Returns md5sum for a message object of type 'MeshUWBCentral"
  "5bbc7e1874ce4e720dbb04b3a0e1e74b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<MeshUWBCentral>)))
  "Returns full string definition for message of type '<MeshUWBCentral>"
  (cl:format cl:nil "Header header~%float64[] DC~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'MeshUWBCentral)))
  "Returns full string definition for message of type 'MeshUWBCentral"
  (cl:format cl:nil "Header header~%float64[] DC~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <MeshUWBCentral>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'DC) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <MeshUWBCentral>))
  "Converts a ROS message object to a list"
  (cl:list 'MeshUWBCentral
    (cl:cons ':header (header msg))
    (cl:cons ':DC (DC msg))
))
