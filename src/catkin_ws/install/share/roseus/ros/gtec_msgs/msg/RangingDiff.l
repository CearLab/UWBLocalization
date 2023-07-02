;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::RangingDiff)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'RangingDiff (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::RANGINGDIFF")
  (make-package "GTEC_MSGS::RANGINGDIFF"))

(in-package "ROS")
;;//! \htmlinclude RangingDiff.msg.html


(defclass gtec_msgs::RangingDiff
  :super ros::object
  :slots (_anchorId _tagId _range _distance _diff ))

(defmethod gtec_msgs::RangingDiff
  (:init
   (&key
    ((:anchorId __anchorId) 0)
    ((:tagId __tagId) 0)
    ((:range __range) 0.0)
    ((:distance __distance) 0.0)
    ((:diff __diff) 0.0)
    )
   (send-super :init)
   (setq _anchorId (round __anchorId))
   (setq _tagId (round __tagId))
   (setq _range (float __range))
   (setq _distance (float __distance))
   (setq _diff (float __diff))
   self)
  (:anchorId
   (&optional __anchorId)
   (if __anchorId (setq _anchorId __anchorId)) _anchorId)
  (:tagId
   (&optional __tagId)
   (if __tagId (setq _tagId __tagId)) _tagId)
  (:range
   (&optional __range)
   (if __range (setq _range __range)) _range)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:diff
   (&optional __diff)
   (if __diff (setq _diff __diff)) _diff)
  (:serialization-length
   ()
   (+
    ;; int16 _anchorId
    2
    ;; int16 _tagId
    2
    ;; float32 _range
    4
    ;; float32 _distance
    4
    ;; float32 _diff
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _anchorId
       (write-word _anchorId s)
     ;; int16 _tagId
       (write-word _tagId s)
     ;; float32 _range
       (sys::poke _range (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _distance
       (sys::poke _distance (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _diff
       (sys::poke _diff (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _anchorId
     (setq _anchorId (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _tagId
     (setq _tagId (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; float32 _range
     (setq _range (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _distance
     (setq _distance (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _diff
     (setq _diff (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get gtec_msgs::RangingDiff :md5sum-) "c6a42b09b24a1d184442ec374c7c1cbf")
(setf (get gtec_msgs::RangingDiff :datatype-) "gtec_msgs/RangingDiff")
(setf (get gtec_msgs::RangingDiff :definition-)
      "int16 anchorId
int16 tagId
float32 range
float32 distance
float32 diff
")



(provide :gtec_msgs/RangingDiff "c6a42b09b24a1d184442ec374c7c1cbf")


