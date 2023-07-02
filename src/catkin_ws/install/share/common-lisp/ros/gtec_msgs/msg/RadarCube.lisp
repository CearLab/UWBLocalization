; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude RadarCube.msg.html

(cl:defclass <RadarCube> (roslisp-msg-protocol:ros-message)
  ((header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header))
   (fftSize
    :reader fftSize
    :initarg :fftSize
    :type cl:fixnum
    :initform 0)
   (angleBins
    :reader angleBins
    :initarg :angleBins
    :type cl:fixnum
    :initform 0)
   (data
    :reader data
    :initarg :data
    :type (cl:vector cl:float)
   :initform (cl:make-array 0 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass RadarCube (<RadarCube>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <RadarCube>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'RadarCube)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<RadarCube> is deprecated: use gtec_msgs-msg:RadarCube instead.")))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <RadarCube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:header-val is deprecated.  Use gtec_msgs-msg:header instead.")
  (header m))

(cl:ensure-generic-function 'fftSize-val :lambda-list '(m))
(cl:defmethod fftSize-val ((m <RadarCube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:fftSize-val is deprecated.  Use gtec_msgs-msg:fftSize instead.")
  (fftSize m))

(cl:ensure-generic-function 'angleBins-val :lambda-list '(m))
(cl:defmethod angleBins-val ((m <RadarCube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:angleBins-val is deprecated.  Use gtec_msgs-msg:angleBins instead.")
  (angleBins m))

(cl:ensure-generic-function 'data-val :lambda-list '(m))
(cl:defmethod data-val ((m <RadarCube>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:data-val is deprecated.  Use gtec_msgs-msg:data instead.")
  (data m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <RadarCube>) ostream)
  "Serializes a message object of type '<RadarCube>"
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
  (cl:let* ((signed (cl:slot-value msg 'fftSize)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'angleBins)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'data))))
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
   (cl:slot-value msg 'data))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <RadarCube>) istream)
  "Deserializes a message object of type '<RadarCube>"
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'fftSize) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angleBins) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'data) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'data)))
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
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<RadarCube>)))
  "Returns string type for a message object of type '<RadarCube>"
  "gtec_msgs/RadarCube")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'RadarCube)))
  "Returns string type for a message object of type 'RadarCube"
  "gtec_msgs/RadarCube")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<RadarCube>)))
  "Returns md5sum for a message object of type '<RadarCube>"
  "fc958423e7f6a6996cbc895eb0a5e0b2")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'RadarCube)))
  "Returns md5sum for a message object of type 'RadarCube"
  "fc958423e7f6a6996cbc895eb0a5e0b2")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<RadarCube>)))
  "Returns full string definition for message of type '<RadarCube>"
  (cl:format cl:nil "Header header~%int16 fftSize~%int16 angleBins~%float64[] data~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'RadarCube)))
  "Returns full string definition for message of type 'RadarCube"
  (cl:format cl:nil "Header header~%int16 fftSize~%int16 angleBins~%float64[] data~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <RadarCube>))
  (cl:+ 0
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
     2
     2
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'data) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <RadarCube>))
  "Converts a ROS message object to a list"
  (cl:list 'RadarCube
    (cl:cons ':header (header msg))
    (cl:cons ':fftSize (fftSize msg))
    (cl:cons ':angleBins (angleBins msg))
    (cl:cons ':data (data msg))
))
