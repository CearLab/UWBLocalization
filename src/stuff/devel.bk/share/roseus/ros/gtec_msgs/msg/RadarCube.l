;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::RadarCube)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'RadarCube (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::RADARCUBE")
  (make-package "GTEC_MSGS::RADARCUBE"))

(in-package "ROS")
;;//! \htmlinclude RadarCube.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass gtec_msgs::RadarCube
  :super ros::object
  :slots (_header _fftSize _angleBins _data ))

(defmethod gtec_msgs::RadarCube
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:fftSize __fftSize) 0)
    ((:angleBins __angleBins) 0)
    ((:data __data) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _fftSize (round __fftSize))
   (setq _angleBins (round __angleBins))
   (setq _data __data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:fftSize
   (&optional __fftSize)
   (if __fftSize (setq _fftSize __fftSize)) _fftSize)
  (:angleBins
   (&optional __angleBins)
   (if __angleBins (setq _angleBins __angleBins)) _angleBins)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _fftSize
    2
    ;; int16 _angleBins
    2
    ;; float64[] _data
    (* 8    (length _data)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int16 _fftSize
       (write-word _fftSize s)
     ;; int16 _angleBins
       (write-word _angleBins s)
     ;; float64[] _data
     (write-long (length _data) s)
     (dotimes (i (length _data))
       (sys::poke (elt _data i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int16 _fftSize
     (setq _fftSize (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _angleBins
     (setq _angleBins (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float64[] _data
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _data (instantiate float-vector n))
     (dotimes (i n)
     (setf (elt _data i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     ))
   ;;
   self)
  )

(setf (get gtec_msgs::RadarCube :md5sum-) "fc958423e7f6a6996cbc895eb0a5e0b2")
(setf (get gtec_msgs::RadarCube :datatype-) "gtec_msgs/RadarCube")
(setf (get gtec_msgs::RadarCube :definition-)
      "Header header
int16 fftSize
int16 angleBins
float64[] data
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



(provide :gtec_msgs/RadarCube "fc958423e7f6a6996cbc895eb0a5e0b2")


