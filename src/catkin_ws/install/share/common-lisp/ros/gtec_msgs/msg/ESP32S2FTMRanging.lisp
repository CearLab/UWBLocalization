; Auto-generated. Do not edit!


(cl:in-package gtec_msgs-msg)


;//! \htmlinclude ESP32S2FTMRanging.msg.html

(cl:defclass <ESP32S2FTMRanging> (roslisp-msg-protocol:ros-message)
  ((anchorId
    :reader anchorId
    :initarg :anchorId
    :type cl:string
    :initform "")
   (rtt_est
    :reader rtt_est
    :initarg :rtt_est
    :type cl:integer
    :initform 0)
   (rtt_raw
    :reader rtt_raw
    :initarg :rtt_raw
    :type cl:integer
    :initform 0)
   (dist_est
    :reader dist_est
    :initarg :dist_est
    :type cl:float
    :initform 0.0)
   (num_frames
    :reader num_frames
    :initarg :num_frames
    :type cl:integer
    :initform 0)
   (frames
    :reader frames
    :initarg :frames
    :type (cl:vector gtec_msgs-msg:ESP32S2FTMFrame)
   :initform (cl:make-array 0 :element-type 'gtec_msgs-msg:ESP32S2FTMFrame :initial-element (cl:make-instance 'gtec_msgs-msg:ESP32S2FTMFrame))))
)

(cl:defclass ESP32S2FTMRanging (<ESP32S2FTMRanging>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <ESP32S2FTMRanging>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'ESP32S2FTMRanging)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name gtec_msgs-msg:<ESP32S2FTMRanging> is deprecated: use gtec_msgs-msg:ESP32S2FTMRanging instead.")))

(cl:ensure-generic-function 'anchorId-val :lambda-list '(m))
(cl:defmethod anchorId-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:anchorId-val is deprecated.  Use gtec_msgs-msg:anchorId instead.")
  (anchorId m))

(cl:ensure-generic-function 'rtt_est-val :lambda-list '(m))
(cl:defmethod rtt_est-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rtt_est-val is deprecated.  Use gtec_msgs-msg:rtt_est instead.")
  (rtt_est m))

(cl:ensure-generic-function 'rtt_raw-val :lambda-list '(m))
(cl:defmethod rtt_raw-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:rtt_raw-val is deprecated.  Use gtec_msgs-msg:rtt_raw instead.")
  (rtt_raw m))

(cl:ensure-generic-function 'dist_est-val :lambda-list '(m))
(cl:defmethod dist_est-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:dist_est-val is deprecated.  Use gtec_msgs-msg:dist_est instead.")
  (dist_est m))

(cl:ensure-generic-function 'num_frames-val :lambda-list '(m))
(cl:defmethod num_frames-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:num_frames-val is deprecated.  Use gtec_msgs-msg:num_frames instead.")
  (num_frames m))

(cl:ensure-generic-function 'frames-val :lambda-list '(m))
(cl:defmethod frames-val ((m <ESP32S2FTMRanging>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader gtec_msgs-msg:frames-val is deprecated.  Use gtec_msgs-msg:frames instead.")
  (frames m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <ESP32S2FTMRanging>) ostream)
  "Serializes a message object of type '<ESP32S2FTMRanging>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'anchorId))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'anchorId))
  (cl:let* ((signed (cl:slot-value msg 'rtt_est)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'rtt_raw)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'dist_est))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let* ((signed (cl:slot-value msg 'num_frames)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((__ros_arr_len (cl:length (cl:slot-value msg 'frames))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_arr_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_arr_len) ostream))
  (cl:map cl:nil #'(cl:lambda (ele) (roslisp-msg-protocol:serialize ele ostream))
   (cl:slot-value msg 'frames))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <ESP32S2FTMRanging>) istream)
  "Deserializes a message object of type '<ESP32S2FTMRanging>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'anchorId) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'anchorId) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rtt_est) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'rtt_raw) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'dist_est) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'num_frames) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  (cl:let ((__ros_arr_len 0))
    (cl:setf (cl:ldb (cl:byte 8 0) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 8) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 16) __ros_arr_len) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 24) __ros_arr_len) (cl:read-byte istream))
  (cl:setf (cl:slot-value msg 'frames) (cl:make-array __ros_arr_len))
  (cl:let ((vals (cl:slot-value msg 'frames)))
    (cl:dotimes (i __ros_arr_len)
    (cl:setf (cl:aref vals i) (cl:make-instance 'gtec_msgs-msg:ESP32S2FTMFrame))
  (roslisp-msg-protocol:deserialize (cl:aref vals i) istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<ESP32S2FTMRanging>)))
  "Returns string type for a message object of type '<ESP32S2FTMRanging>"
  "gtec_msgs/ESP32S2FTMRanging")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'ESP32S2FTMRanging)))
  "Returns string type for a message object of type 'ESP32S2FTMRanging"
  "gtec_msgs/ESP32S2FTMRanging")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<ESP32S2FTMRanging>)))
  "Returns md5sum for a message object of type '<ESP32S2FTMRanging>"
  "300ca8dcfb5379b480056ad93a9bfd81")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'ESP32S2FTMRanging)))
  "Returns md5sum for a message object of type 'ESP32S2FTMRanging"
  "300ca8dcfb5379b480056ad93a9bfd81")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<ESP32S2FTMRanging>)))
  "Returns full string definition for message of type '<ESP32S2FTMRanging>"
  (cl:format cl:nil "string anchorId~%int32 rtt_est~%int32 rtt_raw~%float32 dist_est~%int32 num_frames~%gtec_msgs/ESP32S2FTMFrame[] frames~%~%================================================================================~%MSG: gtec_msgs/ESP32S2FTMFrame~%int32 rssi~%int32 rtt~%int64 t1~%int64 t2~%int64 t3~%int64 t4~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'ESP32S2FTMRanging)))
  "Returns full string definition for message of type 'ESP32S2FTMRanging"
  (cl:format cl:nil "string anchorId~%int32 rtt_est~%int32 rtt_raw~%float32 dist_est~%int32 num_frames~%gtec_msgs/ESP32S2FTMFrame[] frames~%~%================================================================================~%MSG: gtec_msgs/ESP32S2FTMFrame~%int32 rssi~%int32 rtt~%int64 t1~%int64 t2~%int64 t3~%int64 t4~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <ESP32S2FTMRanging>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'anchorId))
     4
     4
     4
     4
     4 (cl:reduce #'cl:+ (cl:slot-value msg 'frames) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ (roslisp-msg-protocol:serialization-length ele))))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <ESP32S2FTMRanging>))
  "Converts a ROS message object to a list"
  (cl:list 'ESP32S2FTMRanging
    (cl:cons ':anchorId (anchorId msg))
    (cl:cons ':rtt_est (rtt_est msg))
    (cl:cons ':rtt_raw (rtt_raw msg))
    (cl:cons ':dist_est (dist_est msg))
    (cl:cons ':num_frames (num_frames msg))
    (cl:cons ':frames (frames msg))
))
