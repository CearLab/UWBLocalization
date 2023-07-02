; Auto-generated. Do not edit!


(cl:in-package imu_3dm_gx4-msg)


;//! \htmlinclude FilterOutput.msg.html

(cl:defclass <FilterOutput> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (quat_status
    :reader quat_status
    :initarg :quat_status
    :type cl:fixnum
    :initform 0)
   (bias_status
    :reader bias_status
    :initarg :bias_status
    :type cl:fixnum
    :initform 0)
   (orientation
    :reader orientation
    :initarg :orientation
    :type geometry_msgs-msg:Quaternion
    :initform (cl:make-instance 'geometry_msgs-msg:Quaternion))
   (orientation_covariance
    :reader orientation_covariance
    :initarg :orientation_covariance
    :type (cl:vector cl:float)
   :initform (cl:make-array 9 :element-type 'cl:float :initial-element 0.0))
   (bias
    :reader bias
    :initarg :bias
    :type geometry_msgs-msg:Vector3
    :initform (cl:make-instance 'geometry_msgs-msg:Vector3))
   (bias_covariance
    :reader bias_covariance
    :initarg :bias_covariance
    :type (cl:vector cl:float)
   :initform (cl:make-array 9 :element-type 'cl:float :initial-element 0.0))
   (bias_covariance_status
    :reader bias_covariance_status
    :initarg :bias_covariance_status
    :type cl:fixnum
    :initform 0)
   (orientation_covariance_status
    :reader orientation_covariance_status
    :initarg :orientation_covariance_status
    :type cl:fixnum
    :initform 0))
)

(cl:defclass FilterOutput (<FilterOutput>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <FilterOutput>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'FilterOutput)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name imu_3dm_gx4-msg:<FilterOutput> is deprecated: use imu_3dm_gx4-msg:FilterOutput instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:header-val is deprecated.  Use imu_3dm_gx4-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'quat_status-val :lambda-list '(m))
(cl:defmethod quat_status-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:quat_status-val is deprecated.  Use imu_3dm_gx4-msg:quat_status instead.")
  (quat_status m))

(cl:ensure-generic-function 'bias_status-val :lambda-list '(m))
(cl:defmethod bias_status-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:bias_status-val is deprecated.  Use imu_3dm_gx4-msg:bias_status instead.")
  (bias_status m))

(cl:ensure-generic-function 'orientation-val :lambda-list '(m))
(cl:defmethod orientation-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:orientation-val is deprecated.  Use imu_3dm_gx4-msg:orientation instead.")
  (orientation m))

(cl:ensure-generic-function 'orientation_covariance-val :lambda-list '(m))
(cl:defmethod orientation_covariance-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:orientation_covariance-val is deprecated.  Use imu_3dm_gx4-msg:orientation_covariance instead.")
  (orientation_covariance m))

(cl:ensure-generic-function 'bias-val :lambda-list '(m))
(cl:defmethod bias-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:bias-val is deprecated.  Use imu_3dm_gx4-msg:bias instead.")
  (bias m))

(cl:ensure-generic-function 'bias_covariance-val :lambda-list '(m))
(cl:defmethod bias_covariance-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:bias_covariance-val is deprecated.  Use imu_3dm_gx4-msg:bias_covariance instead.")
  (bias_covariance m))

(cl:ensure-generic-function 'bias_covariance_status-val :lambda-list '(m))
(cl:defmethod bias_covariance_status-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:bias_covariance_status-val is deprecated.  Use imu_3dm_gx4-msg:bias_covariance_status instead.")
  (bias_covariance_status m))

(cl:ensure-generic-function 'orientation_covariance_status-val :lambda-list '(m))
(cl:defmethod orientation_covariance_status-val ((m <FilterOutput>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader imu_3dm_gx4-msg:orientation_covariance_status-val is deprecated.  Use imu_3dm_gx4-msg:orientation_covariance_status instead.")
  (orientation_covariance_status m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<FilterOutput>)))
    "Constants for message type '<FilterOutput>"
  '((:STATUS_INVALID . 0)
    (:STATUS_VALID . 1)
    (:STATUS_VALID_REFERENCED . 2))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'FilterOutput)))
    "Constants for message type 'FilterOutput"
  '((:STATUS_INVALID . 0)
    (:STATUS_VALID . 1)
    (:STATUS_VALID_REFERENCED . 2))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <FilterOutput>) ostream)
  "Serializes a message object of type '<FilterOutput>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quat_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'quat_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bias_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'bias_status)) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'orientation) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'orientation_covariance))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'bias) ostream)
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'bias_covariance))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bias_covariance_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'bias_covariance_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'orientation_covariance_status)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'orientation_covariance_status)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <FilterOutput>) istream)
  "Deserializes a message object of type '<FilterOutput>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'quat_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'quat_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bias_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'bias_status)) (cl:read-byte istream))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'orientation) istream)
  (cl:setf (cl:slot-value msg 'orientation_covariance) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'orientation_covariance)))
    (cl:dotimes (i 9)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'bias) istream)
  (cl:setf (cl:slot-value msg 'bias_covariance) (cl:make-array 9))
  (cl:let ((vals (cl:slot-value msg 'bias_covariance)))
    (cl:dotimes (i 9)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'bias_covariance_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'bias_covariance_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'orientation_covariance_status)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) (cl:slot-value msg 'orientation_covariance_status)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<FilterOutput>)))
  "Returns string type for a message object of type '<FilterOutput>"
  "imu_3dm_gx4/FilterOutput")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'FilterOutput)))
  "Returns string type for a message object of type 'FilterOutput"
  "imu_3dm_gx4/FilterOutput")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<FilterOutput>)))
  "Returns md5sum for a message object of type '<FilterOutput>"
  "40af8b09da9b33d02fc6b6288f52b159")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'FilterOutput)))
  "Returns md5sum for a message object of type 'FilterOutput"
  "40af8b09da9b33d02fc6b6288f52b159")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<FilterOutput>)))
  "Returns full string definition for message of type '<FilterOutput>"
  (cl:format cl:nil "# Output from the 3DM-GX4 attitude estimation filter.~%std_msgs/Header header~%~%# Node on status flags:~%# Status flags are implemented as bit-fields.~%#  0 = invalid~%#  1 = valid~%#  2 = valid and geo-magnetically referenced (quat_status only)~%#~%# Note that covariance on orientation becomes invalid as pitch angle exceeds 70 # degrees. This will be indicated by the status flag.~%~%# Quaternion status:~%uint16 quat_status~%~%# Bias status~%uint16 bias_status~%~%# Orientation estimate and diagonal covariance~%geometry_msgs/Quaternion orientation~%float64[9] orientation_covariance~%~%# Gyro bias and diagonal covariance~%geometry_msgs/Vector3 bias~%float64[9] bias_covariance~%~%# Covariance statuses~%uint16 bias_covariance_status~%uint16 orientation_covariance_status~%~%# Constants~%uint16 STATUS_INVALID = 0~%uint16 STATUS_VALID = 1~%uint16 STATUS_VALID_REFERENCED = 2~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'FilterOutput)))
  "Returns full string definition for message of type 'FilterOutput"
  (cl:format cl:nil "# Output from the 3DM-GX4 attitude estimation filter.~%std_msgs/Header header~%~%# Node on status flags:~%# Status flags are implemented as bit-fields.~%#  0 = invalid~%#  1 = valid~%#  2 = valid and geo-magnetically referenced (quat_status only)~%#~%# Note that covariance on orientation becomes invalid as pitch angle exceeds 70 # degrees. This will be indicated by the status flag.~%~%# Quaternion status:~%uint16 quat_status~%~%# Bias status~%uint16 bias_status~%~%# Orientation estimate and diagonal covariance~%geometry_msgs/Quaternion orientation~%float64[9] orientation_covariance~%~%# Gyro bias and diagonal covariance~%geometry_msgs/Vector3 bias~%float64[9] bias_covariance~%~%# Covariance statuses~%uint16 bias_covariance_status~%uint16 orientation_covariance_status~%~%# Constants~%uint16 STATUS_INVALID = 0~%uint16 STATUS_VALID = 1~%uint16 STATUS_VALID_REFERENCED = 2~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%================================================================================~%MSG: geometry_msgs/Vector3~%# This represents a vector in free space. ~%# It is only meant to represent a direction. Therefore, it does not~%# make sense to apply a translation to it (e.g., when applying a ~%# generic rigid transformation to a Vector3, tf2 will only apply the~%# rotation). If you want your data to be translatable too, use the~%# geometry_msgs/Point message instead.~%~%float64 x~%float64 y~%float64 z~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <FilterOutput>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'orientation))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'orientation_covariance) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'bias))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'bias_covariance) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
     2
     2
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <FilterOutput>))
  "Converts a ROS message object to a list"
  (cl:list 'FilterOutput
    (cl:cons ':header (header msg))
    (cl:cons ':quat_status (quat_status msg))
    (cl:cons ':bias_status (bias_status msg))
    (cl:cons ':orientation (orientation msg))
    (cl:cons ':orientation_covariance (orientation_covariance msg))
    (cl:cons ':bias (bias msg))
    (cl:cons ':bias_covariance (bias_covariance msg))
    (cl:cons ':bias_covariance_status (bias_covariance_status msg))
    (cl:cons ':orientation_covariance_status (orientation_covariance_status msg))
))
