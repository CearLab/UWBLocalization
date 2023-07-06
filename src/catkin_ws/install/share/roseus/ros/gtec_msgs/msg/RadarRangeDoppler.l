;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::RadarRangeDoppler)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'RadarRangeDoppler (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::RADARRANGEDOPPLER")
  (make-package "GTEC_MSGS::RADARRANGEDOPPLER"))

(in-package "ROS")
;;//! \htmlinclude RadarRangeDoppler.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass gtec_msgs::RadarRangeDoppler
  :super ros::object
  :slots (_header _numRangeBins _numDopplerBins _data ))

(defmethod gtec_msgs::RadarRangeDoppler
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:numRangeBins __numRangeBins) 0)
    ((:numDopplerBins __numDopplerBins) 0)
    ((:data __data) (make-array 0 :initial-element 0.0 :element-type :float))
    )
   (send-super :init)
   (setq _header __header)
   (setq _numRangeBins (round __numRangeBins))
   (setq _numDopplerBins (round __numDopplerBins))
   (setq _data __data)
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:numRangeBins
   (&optional __numRangeBins)
   (if __numRangeBins (setq _numRangeBins __numRangeBins)) _numRangeBins)
  (:numDopplerBins
   (&optional __numDopplerBins)
   (if __numDopplerBins (setq _numDopplerBins __numDopplerBins)) _numDopplerBins)
  (:data
   (&optional __data)
   (if __data (setq _data __data)) _data)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int16 _numRangeBins
    2
    ;; int16 _numDopplerBins
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
     ;; int16 _numRangeBins
       (write-word _numRangeBins s)
     ;; int16 _numDopplerBins
       (write-word _numDopplerBins s)
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
   ;; int16 _numRangeBins
     (setq _numRangeBins (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _numDopplerBins
     (setq _numDopplerBins (sys::peek buf ptr- :short)) (incf ptr- 2)
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

(setf (get gtec_msgs::RadarRangeDoppler :md5sum-) "54bb64bfdc5d84bbb760ced1e7d42afe")
(setf (get gtec_msgs::RadarRangeDoppler :datatype-) "gtec_msgs/RadarRangeDoppler")
(setf (get gtec_msgs::RadarRangeDoppler :definition-)
      "Header header
int16 numRangeBins
int16 numDopplerBins
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



(provide :gtec_msgs/RadarRangeDoppler "54bb64bfdc5d84bbb760ced1e7d42afe")


