;; Auto-generated. Do not edit!


(when (boundp 'robot_localization_custom::ToLL)
  (if (not (find-package "ROBOT_LOCALIZATION_CUSTOM"))
    (make-package "ROBOT_LOCALIZATION_CUSTOM"))
  (shadow 'ToLL (find-package "ROBOT_LOCALIZATION_CUSTOM")))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::TOLL")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::TOLL"))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::TOLLREQUEST")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::TOLLREQUEST"))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::TOLLRESPONSE")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::TOLLRESPONSE"))

(in-package "ROS")

(if (not (find-package "GEOMETRY_MSGS"))
  (ros::roseus-add-msgs "geometry_msgs"))


(if (not (find-package "GEOGRAPHIC_MSGS"))
  (ros::roseus-add-msgs "geographic_msgs"))


(defclass robot_localization_custom::ToLLRequest
  :super ros::object
  :slots (_map_point ))

(defmethod robot_localization_custom::ToLLRequest
  (:init
   (&key
    ((:map_point __map_point) (instance geometry_msgs::Point :init))
    )
   (send-super :init)
   (setq _map_point __map_point)
   self)
  (:map_point
   (&rest __map_point)
   (if (keywordp (car __map_point))
       (send* _map_point __map_point)
     (progn
       (if __map_point (setq _map_point (car __map_point)))
       _map_point)))
  (:serialization-length
   ()
   (+
    ;; geometry_msgs/Point _map_point
    (send _map_point :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geometry_msgs/Point _map_point
       (send _map_point :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geometry_msgs/Point _map_point
     (send _map_point :deserialize buf ptr-) (incf ptr- (send _map_point :serialization-length))
   ;;
   self)
  )

(defclass robot_localization_custom::ToLLResponse
  :super ros::object
  :slots (_ll_point ))

(defmethod robot_localization_custom::ToLLResponse
  (:init
   (&key
    ((:ll_point __ll_point) (instance geographic_msgs::GeoPoint :init))
    )
   (send-super :init)
   (setq _ll_point __ll_point)
   self)
  (:ll_point
   (&rest __ll_point)
   (if (keywordp (car __ll_point))
       (send* _ll_point __ll_point)
     (progn
       (if __ll_point (setq _ll_point (car __ll_point)))
       _ll_point)))
  (:serialization-length
   ()
   (+
    ;; geographic_msgs/GeoPoint _ll_point
    (send _ll_point :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; geographic_msgs/GeoPoint _ll_point
       (send _ll_point :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; geographic_msgs/GeoPoint _ll_point
     (send _ll_point :deserialize buf ptr-) (incf ptr- (send _ll_point :serialization-length))
   ;;
   self)
  )

(defclass robot_localization_custom::ToLL
  :super ros::object
  :slots ())

(setf (get robot_localization_custom::ToLL :md5sum-) "ad0cbea3b8423e9ccf1b2ebeefc50b92")
(setf (get robot_localization_custom::ToLL :datatype-) "robot_localization_custom/ToLL")
(setf (get robot_localization_custom::ToLL :request) robot_localization_custom::ToLLRequest)
(setf (get robot_localization_custom::ToLL :response) robot_localization_custom::ToLLResponse)

(defmethod robot_localization_custom::ToLLRequest
  (:response () (instance robot_localization_custom::ToLLResponse :init)))

(setf (get robot_localization_custom::ToLLRequest :md5sum-) "ad0cbea3b8423e9ccf1b2ebeefc50b92")
(setf (get robot_localization_custom::ToLLRequest :datatype-) "robot_localization_custom/ToLLRequest")
(setf (get robot_localization_custom::ToLLRequest :definition-)
      "geometry_msgs/Point map_point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
geographic_msgs/GeoPoint ll_point


================================================================================
MSG: geographic_msgs/GeoPoint
# Geographic point, using the WGS 84 reference ellipsoid.

# Latitude [degrees]. Positive is north of equator; negative is south
# (-90 <= latitude <= +90).
float64 latitude

# Longitude [degrees]. Positive is east of prime meridian; negative is
# west (-180 <= longitude <= +180). At the poles, latitude is -90 or
# +90, and longitude is irrelevant, but must be in range.
float64 longitude

# Altitude [m]. Positive is above the WGS 84 ellipsoid (NaN if unspecified).
float64 altitude
")

(setf (get robot_localization_custom::ToLLResponse :md5sum-) "ad0cbea3b8423e9ccf1b2ebeefc50b92")
(setf (get robot_localization_custom::ToLLResponse :datatype-) "robot_localization_custom/ToLLResponse")
(setf (get robot_localization_custom::ToLLResponse :definition-)
      "geometry_msgs/Point map_point

================================================================================
MSG: geometry_msgs/Point
# This contains the position of a point in free space
float64 x
float64 y
float64 z
---
geographic_msgs/GeoPoint ll_point


================================================================================
MSG: geographic_msgs/GeoPoint
# Geographic point, using the WGS 84 reference ellipsoid.

# Latitude [degrees]. Positive is north of equator; negative is south
# (-90 <= latitude <= +90).
float64 latitude

# Longitude [degrees]. Positive is east of prime meridian; negative is
# west (-180 <= longitude <= +180). At the poles, latitude is -90 or
# +90, and longitude is irrelevant, but must be in range.
float64 longitude

# Altitude [m]. Positive is above the WGS 84 ellipsoid (NaN if unspecified).
float64 altitude
")



(provide :robot_localization_custom/ToLL "ad0cbea3b8423e9ccf1b2ebeefc50b92")


