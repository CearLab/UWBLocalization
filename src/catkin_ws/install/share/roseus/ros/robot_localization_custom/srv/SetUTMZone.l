;; Auto-generated. Do not edit!


(when (boundp 'robot_localization_custom::SetUTMZone)
  (if (not (find-package "ROBOT_LOCALIZATION_CUSTOM"))
    (make-package "ROBOT_LOCALIZATION_CUSTOM"))
  (shadow 'SetUTMZone (find-package "ROBOT_LOCALIZATION_CUSTOM")))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONE")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONE"))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONEREQUEST")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONEREQUEST"))
(unless (find-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONERESPONSE")
  (make-package "ROBOT_LOCALIZATION_CUSTOM::SETUTMZONERESPONSE"))

(in-package "ROS")





(defclass robot_localization_custom::SetUTMZoneRequest
  :super ros::object
  :slots (_utm_zone ))

(defmethod robot_localization_custom::SetUTMZoneRequest
  (:init
   (&key
    ((:utm_zone __utm_zone) "")
    )
   (send-super :init)
   (setq _utm_zone (string __utm_zone))
   self)
  (:utm_zone
   (&optional __utm_zone)
   (if __utm_zone (setq _utm_zone __utm_zone)) _utm_zone)
  (:serialization-length
   ()
   (+
    ;; string _utm_zone
    4 (length _utm_zone)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _utm_zone
       (write-long (length _utm_zone) s) (princ _utm_zone s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _utm_zone
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _utm_zone (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;;
   self)
  )

(defclass robot_localization_custom::SetUTMZoneResponse
  :super ros::object
  :slots ())

(defmethod robot_localization_custom::SetUTMZoneResponse
  (:init
   (&key
    )
   (send-super :init)
   self)
  (:serialization-length
   ()
   (+
    0
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;;
   self)
  )

(defclass robot_localization_custom::SetUTMZone
  :super ros::object
  :slots ())

(setf (get robot_localization_custom::SetUTMZone :md5sum-) "893fd74d45efde020666acda18d3cccc")
(setf (get robot_localization_custom::SetUTMZone :datatype-) "robot_localization_custom/SetUTMZone")
(setf (get robot_localization_custom::SetUTMZone :request) robot_localization_custom::SetUTMZoneRequest)
(setf (get robot_localization_custom::SetUTMZone :response) robot_localization_custom::SetUTMZoneResponse)

(defmethod robot_localization_custom::SetUTMZoneRequest
  (:response () (instance robot_localization_custom::SetUTMZoneResponse :init)))

(setf (get robot_localization_custom::SetUTMZoneRequest :md5sum-) "893fd74d45efde020666acda18d3cccc")
(setf (get robot_localization_custom::SetUTMZoneRequest :datatype-) "robot_localization_custom/SetUTMZoneRequest")
(setf (get robot_localization_custom::SetUTMZoneRequest :definition-)
      "# Set an UTM zone navsat_transform should stick to.
# Example: 31U
string utm_zone
---

")

(setf (get robot_localization_custom::SetUTMZoneResponse :md5sum-) "893fd74d45efde020666acda18d3cccc")
(setf (get robot_localization_custom::SetUTMZoneResponse :datatype-) "robot_localization_custom/SetUTMZoneResponse")
(setf (get robot_localization_custom::SetUTMZoneResponse :definition-)
      "# Set an UTM zone navsat_transform should stick to.
# Example: 31U
string utm_zone
---

")



(provide :robot_localization_custom/SetUTMZone "893fd74d45efde020666acda18d3cccc")


