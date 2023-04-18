;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::Ranging)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'Ranging (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::RANGING")
  (make-package "GTEC_MSGS::RANGING"))

(in-package "ROS")
;;//! \htmlinclude Ranging.msg.html


(defclass gtec_msgs::Ranging
  :super ros::object
  :slots (_anchorId _tagId _range _seq _rss _errorEstimation ))

(defmethod gtec_msgs::Ranging
  (:init
   (&key
    ((:anchorId __anchorId) 0)
    ((:tagId __tagId) 0)
    ((:range __range) 0)
    ((:seq __seq) 0)
    ((:rss __rss) 0.0)
    ((:errorEstimation __errorEstimation) 0.0)
    )
   (send-super :init)
   (setq _anchorId (round __anchorId))
   (setq _tagId (round __tagId))
   (setq _range (round __range))
   (setq _seq (round __seq))
   (setq _rss (float __rss))
   (setq _errorEstimation (float __errorEstimation))
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
  (:rss
   (&optional __rss)
   (if __rss (setq _rss __rss)) _rss)
  (:errorEstimation
   (&optional __errorEstimation)
   (if __errorEstimation (setq _errorEstimation __errorEstimation)) _errorEstimation)
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
    ;; float64 _rss
    8
    ;; float64 _errorEstimation
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
     ;; float64 _rss
       (sys::poke _rss (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _errorEstimation
       (sys::poke _errorEstimation (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
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
   ;; float64 _rss
     (setq _rss (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _errorEstimation
     (setq _errorEstimation (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get gtec_msgs::Ranging :md5sum-) "d30ca10e8481651a0f8849efb5e0d638")
(setf (get gtec_msgs::Ranging :datatype-) "gtec_msgs/Ranging")
(setf (get gtec_msgs::Ranging :definition-)
      "int16 anchorId
int16 tagId
int32 range
int32 seq
float64 rss
float64 errorEstimation
")



(provide :gtec_msgs/Ranging "d30ca10e8481651a0f8849efb5e0d638")


