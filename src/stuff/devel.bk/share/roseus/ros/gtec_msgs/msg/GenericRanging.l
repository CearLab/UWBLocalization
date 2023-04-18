;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::GenericRanging)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'GenericRanging (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::GENERICRANGING")
  (make-package "GTEC_MSGS::GENERICRANGING"))

(in-package "ROS")
;;//! \htmlinclude GenericRanging.msg.html


(defclass gtec_msgs::GenericRanging
  :super ros::object
  :slots (_anchorId _tagId _range _seq _rxPower ))

(defmethod gtec_msgs::GenericRanging
  (:init
   (&key
    ((:anchorId __anchorId) 0)
    ((:tagId __tagId) 0)
    ((:range __range) 0)
    ((:seq __seq) 0)
    ((:rxPower __rxPower) 0.0)
    )
   (send-super :init)
   (setq _anchorId (round __anchorId))
   (setq _tagId (round __tagId))
   (setq _range (round __range))
   (setq _seq (round __seq))
   (setq _rxPower (float __rxPower))
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
  (:seq
   (&optional __seq)
   (if __seq (setq _seq __seq)) _seq)
  (:rxPower
   (&optional __rxPower)
   (if __rxPower (setq _rxPower __rxPower)) _rxPower)
  (:serialization-length
   ()
   (+
    ;; int16 _anchorId
    2
    ;; int16 _tagId
    2
    ;; int32 _range
    4
    ;; int32 _seq
    4
    ;; float64 _rxPower
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int16 _anchorId
       (write-word _anchorId s)
     ;; int16 _tagId
       (write-word _tagId s)
     ;; int32 _range
       (write-long _range s)
     ;; int32 _seq
       (write-long _seq s)
     ;; float64 _rxPower
       (sys::poke _rxPower (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int16 _anchorId
     (setq _anchorId (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int16 _tagId
     (setq _tagId (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int32 _range
     (setq _range (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _seq
     (setq _seq (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _rxPower
     (setq _rxPower (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get gtec_msgs::GenericRanging :md5sum-) "bb14e8b4057fd81e694cb16617eec599")
(setf (get gtec_msgs::GenericRanging :datatype-) "gtec_msgs/GenericRanging")
(setf (get gtec_msgs::GenericRanging :definition-)
      "int16 anchorId
int16 tagId
int32 range
int32 seq
float64 rxPower
")



(provide :gtec_msgs/GenericRanging "bb14e8b4057fd81e694cb16617eec599")


