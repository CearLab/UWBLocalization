;; Auto-generated. Do not edit!


(when (boundp 'jackal_op::GradientDescent)
  (if (not (find-package "JACKAL_OP"))
    (make-package "JACKAL_OP"))
  (shadow 'GradientDescent (find-package "JACKAL_OP")))
(unless (find-package "JACKAL_OP::GRADIENTDESCENT")
  (make-package "JACKAL_OP::GRADIENTDESCENT"))

(in-package "ROS")
;;//! \htmlinclude GradientDescent.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass jackal_op::GradientDescent
  :super ros::object
  :slots (_header _J _GJ _HJ _A _p _pg _N ))

(defmethod jackal_op::GradientDescent
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:J __J) 0.0)
    ((:GJ __GJ) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:HJ __HJ) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:A __A) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:p __p) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:pg __pg) (make-array 0 :initial-element 0.0 :element-type :float))
    ((:N __N) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _J (float __J))
   (setq _GJ __GJ)
   (setq _HJ __HJ)
   (setq _A __A)
   (setq _p __p)
   (setq _pg __pg)
   (setq _N __N)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:J
   (&optional __J)
   (if __J (setq _J __J)) _J)
  (:GJ
   (&optional __GJ)
   (if __GJ (setq _GJ __GJ)) _GJ)
  (:HJ
   (&optional __HJ)
   (if __HJ (setq _HJ __HJ)) _HJ)
  (:A
   (&optional __A)
   (if __A (setq _A __A)) _A)
  (:p
   (&optional __p)
   (if __p (setq _p __p)) _p)
  (:pg
   (&optional __pg)
   (if __pg (setq _pg __pg)) _pg)
  (:N
   (&optional __N)
   (if __N (setq _N __N)) _N)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; float64 _J
    8
    ;; float64[] _GJ
    (* 8    (length _GJ)) 4
    ;; float64[] _HJ
    (* 8    (length _HJ)) 4
    ;; float64[] _A
    (* 8    (length _A)) 4
    ;; float64[] _p
    (* 8    (length _p)) 4
    ;; float64[] _pg
    (* 8    (length _pg)) 4
    ;; float64[] _N
    (* 8    (length _N)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; float64 _J
       (sys::poke _J (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64[] _GJ
     (write-long (length _GJ) s)
     (dotimes (i (length _GJ))
       (sys::poke (elt _GJ i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _HJ
     (write-long (length _HJ) s)
     (dotimes (i (length _HJ))
       (sys::poke (elt _HJ i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _A
     (write-long (length _A) s)
     (dotimes (i (length _A))
       (sys::poke (elt _A i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _p
     (write-long (length _p) s)
     (dotimes (i (length _p))
       (sys::poke (elt _p i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _pg
     (write-long (length _pg) s)
     (dotimes (i (length _pg))
       (sys::poke (elt _pg i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; float64[] _N
     (write-long (length _N) s)
     (dotimes (i (length _N))
       (sys::poke (elt _N i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; float64 _J
     (setq _J (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64[] _GJ
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _GJ (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _GJ i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _HJ
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _HJ (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _HJ i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _A
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _A (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _A i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _p
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _p (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _p i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _pg
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _pg (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _pg i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;; float64[] _N
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _N (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _N i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get jackal_op::GradientDescent :md5sum-) "bf70146ab5f0d8094fd0d6f86f797d43")
(setf (get jackal_op::GradientDescent :datatype-) "jackal_op/GradientDescent")
(setf (get jackal_op::GradientDescent :definition-)
      "Header header
float64 J
float64[] GJ
float64[] HJ
float64[] A
float64[] p
float64[] pg
float64[] N

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



(provide :jackal_op/GradientDescent "bf70146ab5f0d8094fd0d6f86f797d43")


