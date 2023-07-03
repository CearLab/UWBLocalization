;; Auto-generated. Do not edit!


(when (boundp 'imu_3dm_gx4::FilterOutput)
  (if (not (find-package "IMU_3DM_GX4"))
    (make-package "IMU_3DM_GX4"))
  (shadow 'FilterOutput (find-package "IMU_3DM_GX4")))
(unless (find-package "IMU_3DM_GX4::FILTEROUTPUT")
  (make-package "IMU_3DM_GX4::FILTEROUTPUT"))

(in-package "ROS")
;;//! \htmlinclude FilterOutput.msg.html
(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(intern "*STATUS_INVALID*" (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(shadow '*STATUS_INVALID* (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(defconstant imu_3dm_gx4::FilterOutput::*STATUS_INVALID* 0)
(intern "*STATUS_VALID*" (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(shadow '*STATUS_VALID* (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(defconstant imu_3dm_gx4::FilterOutput::*STATUS_VALID* 1)
(intern "*STATUS_VALID_REFERENCED*" (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(shadow '*STATUS_VALID_REFERENCED* (find-package "IMU_3DM_GX4::FILTEROUTPUT"))
(defconstant imu_3dm_gx4::FilterOutput::*STATUS_VALID_REFERENCED* 2)
(defclass imu_3dm_gx4::FilterOutput
  :super ros::object
  :slots (_header _quat_status _bias_status _orientation _orientation_covariance _bias _bias_covariance _bias_covariance_status _orientation_covariance_status ))

(defmethod imu_3dm_gx4::FilterOutput
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:quat_status __quat_status) 0)
    ((:bias_status __bias_status) 0)
    ((:orientation __orientation) (instance geometry_msgs::Quaternion :init))
    ((:orientation_covariance __orientation_covariance) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:bias __bias) (instance geometry_msgs::Vector3 :init))
    ((:bias_covariance __bias_covariance) (make-array 9 :initial-element 0.0 :element-type :float))
    ((:bias_covariance_status __bias_covariance_status) 0)
    ((:orientation_covariance_status __orientation_covariance_status) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _quat_status (round __quat_status))
   (setq _bias_status (round __bias_status))
   (setq _orientation __orientation)
   (setq _orientation_covariance __orientation_covariance)
   (setq _bias __bias)
   (setq _bias_covariance __bias_covariance)
   (setq _bias_covariance_status (round __bias_covariance_status))
   (setq _orientation_covariance_status (round __orientation_covariance_status))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:quat_status
   (&optional __quat_status)
   (if __quat_status (setq _quat_status __quat_status)) _quat_status)
  (:bias_status
   (&optional __bias_status)
   (if __bias_status (setq _bias_status __bias_status)) _bias_status)
  (:orientation
   (&rest __orientation)
   (if (keywordp (car __orientation))
       (send* _orientation __orientation)
     (progn
       (if __orientation (setq _orientation (car __orientation)))
       _orientation)))
  (:orientation_covariance
   (&optional __orientation_covariance)
   (if __orientation_covariance (setq _orientation_covariance __orientation_covariance)) _orientation_covariance)
  (:bias
   (&rest __bias)
   (if (keywordp (car __bias))
       (send* _bias __bias)
     (progn
       (if __bias (setq _bias (car __bias)))
       _bias)))
  (:bias_covariance
   (&optional __bias_covariance)
   (if __bias_covariance (setq _bias_covariance __bias_covariance)) _bias_covariance)
  (:bias_covariance_status
   (&optional __bias_covariance_status)
   (if __bias_covariance_status (setq _bias_covariance_status __bias_covariance_status)) _bias_covariance_status)
  (:orientation_covariance_status
   (&optional __orientation_covariance_status)
   (if __orientation_covariance_status (setq _orientation_covariance_status __orientation_covariance_status)) _orientation_covariance_status)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; uint16 _quat_status
    2
    ;; uint16 _bias_status
    2
    ;; geometry_msgs/Quaternion _orientation
    (send _orientation :serialization-length)
    ;; float64[9] _orientation_covariance
    (* 8    9)
    ;; geometry_msgs/Vector3 _bias
    (send _bias :serialization-length)
    ;; float64[9] _bias_covariance
    (* 8    9)
    ;; uint16 _bias_covariance_status
    2
    ;; uint16 _orientation_covariance_status
    2
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; uint16 _quat_status
       (write-word _quat_status s)
     ;; uint16 _bias_status
       (write-word _bias_status s)
     ;; geometry_msgs/Quaternion _orientation
       (send _orientation :serialize s)
     ;; float64[9] _orientation_covariance
     (dotimes (i 9)
       (sys::poke (elt _orientation_covariance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; geometry_msgs/Vector3 _bias
       (send _bias :serialize s)
     ;; float64[9] _bias_covariance
     (dotimes (i 9)
       (sys::poke (elt _bias_covariance i) (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
       )
     ;; uint16 _bias_covariance_status
       (write-word _bias_covariance_status s)
     ;; uint16 _orientation_covariance_status
       (write-word _orientation_covariance_status s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; uint16 _quat_status
     (setq _quat_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _bias_status
     (setq _bias_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; geometry_msgs/Quaternion _orientation
     (send _orientation :deserialize buf ptr-) (incf ptr- (send _orientation :serialization-length))
   ;; float64[9] _orientation_covariance
   (dotimes (i (length _orientation_covariance))
     (setf (elt _orientation_covariance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; geometry_msgs/Vector3 _bias
     (send _bias :deserialize buf ptr-) (incf ptr- (send _bias :serialization-length))
   ;; float64[9] _bias_covariance
   (dotimes (i (length _bias_covariance))
     (setf (elt _bias_covariance i) (sys::peek buf ptr- :double)) (incf ptr- 8)
     )
   ;; uint16 _bias_covariance_status
     (setq _bias_covariance_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; uint16 _orientation_covariance_status
     (setq _orientation_covariance_status (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;;
   self)
  )

(setf (get imu_3dm_gx4::FilterOutput :md5sum-) "40af8b09da9b33d02fc6b6288f52b159")
(setf (get imu_3dm_gx4::FilterOutput :datatype-) "imu_3dm_gx4/FilterOutput")
(setf (get imu_3dm_gx4::FilterOutput :definition-)
      "# Output from the 3DM-GX4 attitude estimation filter.
std_msgs/Header header

# Node on status flags:
# Status flags are implemented as bit-fields.
#  0 = invalid
#  1 = valid
#  2 = valid and geo-magnetically referenced (quat_status only)
#
# Note that covariance on orientation becomes invalid as pitch angle exceeds 70 # degrees. This will be indicated by the status flag.

# Quaternion status:
uint16 quat_status

# Bias status
uint16 bias_status

# Orientation estimate and diagonal covariance
geometry_msgs/Quaternion orientation
float64[9] orientation_covariance

# Gyro bias and diagonal covariance
geometry_msgs/Vector3 bias
float64[9] bias_covariance

# Covariance statuses
uint16 bias_covariance_status
uint16 orientation_covariance_status

# Constants
uint16 STATUS_INVALID = 0
uint16 STATUS_VALID = 1
uint16 STATUS_VALID_REFERENCED = 2

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

================================================================================
MSG: geometry_msgs/Quaternion
# This represents an orientation in free space in quaternion form.

float64 x
float64 y
float64 z
float64 w

================================================================================
MSG: geometry_msgs/Vector3
# This represents a vector in free space. 
# It is only meant to represent a direction. Therefore, it does not
# make sense to apply a translation to it (e.g., when applying a 
# generic rigid transformation to a Vector3, tf2 will only apply the
# rotation). If you want your data to be translatable too, use the
# geometry_msgs/Point message instead.

float64 x
float64 y
float64 z
")



(provide :imu_3dm_gx4/FilterOutput "40af8b09da9b33d02fc6b6288f52b159")


