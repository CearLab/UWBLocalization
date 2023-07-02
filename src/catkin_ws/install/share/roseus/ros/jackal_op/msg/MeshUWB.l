;; Auto-generated. Do not edit!


(when (boundp 'jackal_op::MeshUWB)
  (if (not (find-package "JACKAL_OP"))
    (make-package "JACKAL_OP"))
  (shadow 'MeshUWB (find-package "JACKAL_OP")))
(unless (find-package "JACKAL_OP::MESHUWB")
  (make-package "JACKAL_OP::MESHUWB"))

(in-package "ROS")
;;//! \htmlinclude MeshUWB.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass jackal_op::MeshUWB
  :super ros::object
  :slots (_header _D1 _D2 _D3 ))

(defmethod jackal_op::MeshUWB
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:D1 __D1) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:D2 __D2) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:D3 __D3) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _D1 __D1)
   (setq _D2 __D2)
   (setq _D3 __D3)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:D1
   (&optional __D1)
   (if __D1 (setq _D1 __D1)) _D1)
  (:D2
   (&optional __D2)
   (if __D2 (setq _D2 __D2)) _D2)
  (:D3
   (&optional __D3)
   (if __D3 (setq _D3 __D3)) _D3)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64[] _D1
    (* 8    (length _D1)) 4
    ;; float64[] _D2
    (* 8    (length _D2)) 4
    ;; float64[] _D3
    (* 8    (length _D3)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64[] _D1
     (write-long (length _D1) s)
     (dotimes (i (length _D1))
       (sys::poke (elt _D1 i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _D2
     (write-long (length _D2) s)
     (dotimes (i (length _D2))
       (sys::poke (elt _D2 i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _D3
     (write-long (length _D3) s)
     (dotimes (i (length _D3))
       (sys::poke (elt _D3 i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64[] _D1
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _D1 (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _D1 i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _D2
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _D2 (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _D2 i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _D3
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _D3 (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _D3 i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get jackal_op::MeshUWB :md5sum-) "5b30149a17ef9828ca679ce567fad6c8")
(setf (get jackal_op::MeshUWB :datatype-) "jackal_op/MeshUWB")
(setf (get jackal_op::MeshUWB :definition-)
      "Header header
float64[] D1
float64[] D2
float64[] D3
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



(provide :jackal_op/MeshUWB "5b30149a17ef9828ca679ce567fad6c8")


