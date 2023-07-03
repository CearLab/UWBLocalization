;; Auto-generated. Do not edit!


(when (boundp 'jackal_op::MeshUWBCentral)
  (if (not (find-package "JACKAL_OP"))
    (make-package "JACKAL_OP"))
  (shadow 'MeshUWBCentral (find-package "JACKAL_OP")))
(unless (find-package "JACKAL_OP::MESHUWBCENTRAL")
  (make-package "JACKAL_OP::MESHUWBCENTRAL"))

(in-package "ROS")
;;//! \htmlinclude MeshUWBCentral.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass jackal_op::MeshUWBCentral
  :super ros::object
  :slots (_header _DC ))

(defmethod jackal_op::MeshUWBCentral
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:DC __DC) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _DC __DC)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:DC
   (&optional __DC)
   (if __DC (setq _DC __DC)) _DC)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[] _DC
    (* 8    (length _DC)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[] _DC
     (write-long (length _DC) s)
     (dotimes (i (length _DC))
       (sys::poke (elt _DC i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[] _DC
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _DC (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _DC i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get jackal_op::MeshUWBCentral :md5sum-) "5bbc7e1874ce4e720dbb04b3a0e1e74b")
(setf (get jackal_op::MeshUWBCentral :datatype-) "jackal_op/MeshUWBCentral")
(setf (get jackal_op::MeshUWBCentral :definition-)
      "Header header
float64[] DC
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :jackal_op/MeshUWBCentral "5bbc7e1874ce4e720dbb04b3a0e1e74b")


