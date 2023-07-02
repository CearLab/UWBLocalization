;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::ESP32S2FTMRanging)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'ESP32S2FTMRanging (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::ESP32S2FTMRANGING")
  (make-package "GTEC_MSGS::ESP32S2FTMRANGING"))

(in-package "ROS")
;;//! \htmlinclude ESP32S2FTMRanging.msg.html


(defclass gtec_msgs::ESP32S2FTMRanging
  :super ros::object
  :slots (_anchorId _rtt_est _rtt_raw _dist_est _num_frames _frames ))

(defmethod gtec_msgs::ESP32S2FTMRanging
  (:init
   (&key
    ((:anchorId __anchorId) "")
    ((:rtt_est __rtt_est) 0)
    ((:rtt_raw __rtt_raw) 0)
    ((:dist_est __dist_est) 0.0)
    ((:num_frames __num_frames) 0)
    ((:frames __frames) (let (r) (dotimes (i 0) (push (instance gtec_msgs::ESP32S2FTMFrame :init) r)) r))
    )
   (send-super :init)
   (setq _anchorId (string __anchorId))
   (setq _rtt_est (round __rtt_est))
   (setq _rtt_raw (round __rtt_raw))
   (setq _dist_est (float __dist_est))
   (setq _num_frames (round __num_frames))
   (setq _frames __frames)
   self)
  (:anchorId
   (&optional __anchorId)
   (if __anchorId (setq _anchorId __anchorId)) _anchorId)
  (:rtt_est
   (&optional __rtt_est)
   (if __rtt_est (setq _rtt_est __rtt_est)) _rtt_est)
  (:rtt_raw
   (&optional __rtt_raw)
   (if __rtt_raw (setq _rtt_raw __rtt_raw)) _rtt_raw)
  (:dist_est
   (&optional __dist_est)
   (if __dist_est (setq _dist_est __dist_est)) _dist_est)
  (:num_frames
   (&optional __num_frames)
   (if __num_frames (setq _num_frames __num_frames)) _num_frames)
  (:frames
   (&rest __frames)
   (if (keywordp (car __frames))
       (send* _frames __frames)
     (progn
       (if __frames (setq _frames (car __frames)))
       _frames)))
  (:serialization-length
   ()
   (+
    ;; string _anchorId
    4 (length _anchorId)
    ;; int32 _rtt_est
    4
    ;; int32 _rtt_raw
    4
    ;; float32 _dist_est
    4
    ;; int32 _num_frames
    4
    ;; gtec_msgs/ESP32S2FTMFrame[] _frames
    (apply #'+ (send-all _frames :serialization-length)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; string _anchorId
       (write-long (length _anchorId) s) (princ _anchorId s)
     ;; int32 _rtt_est
       (write-long _rtt_est s)
     ;; int32 _rtt_raw
       (write-long _rtt_raw s)
     ;; float32 _dist_est
       (sys::poke _dist_est (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; int32 _num_frames
       (write-long _num_frames s)
     ;; gtec_msgs/ESP32S2FTMFrame[] _frames
     (write-long (length _frames) s)
     (dolist (elem _frames)
       (send elem :serialize s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; string _anchorId
     (let (n) (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4) (setq _anchorId (subseq buf ptr- (+ ptr- n))) (incf ptr- n))
   ;; int32 _rtt_est
     (setq _rtt_est (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _rtt_raw
     (setq _rtt_raw (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float32 _dist_est
     (setq _dist_est (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; int32 _num_frames
     (setq _num_frames (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; gtec_msgs/ESP32S2FTMFrame[] _frames
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _frames (let (r) (dotimes (i n) (push (instance gtec_msgs::ESP32S2FTMFrame :init) r)) r))
     (dolist (elem- _frames)
     (send elem- :deserialize buf ptr-) (incf ptr- (send elem- :serialization-length))
     ))
   ;;
   self)
  )

(setf (get gtec_msgs::ESP32S2FTMRanging :md5sum-) "300ca8dcfb5379b480056ad93a9bfd81")
(setf (get gtec_msgs::ESP32S2FTMRanging :datatype-) "gtec_msgs/ESP32S2FTMRanging")
(setf (get gtec_msgs::ESP32S2FTMRanging :definition-)
      "string anchorId
int32 rtt_est
int32 rtt_raw
float32 dist_est
int32 num_frames
gtec_msgs/ESP32S2FTMFrame[] frames

================================================================================
MSG: gtec_msgs/ESP32S2FTMFrame
int32 rssi
int32 rtt
int64 t1
int64 t2
int64 t3
int64 t4
")



(provide :gtec_msgs/ESP32S2FTMRanging "300ca8dcfb5379b480056ad93a9bfd81")


