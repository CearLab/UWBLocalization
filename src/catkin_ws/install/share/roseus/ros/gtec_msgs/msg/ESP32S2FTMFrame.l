;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::ESP32S2FTMFrame)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'ESP32S2FTMFrame (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::ESP32S2FTMFRAME")
  (make-package "GTEC_MSGS::ESP32S2FTMFRAME"))

(in-package "ROS")
;;//! \htmlinclude ESP32S2FTMFrame.msg.html


(defclass gtec_msgs::ESP32S2FTMFrame
  :super ros::object
  :slots (_rssi _rtt _t1 _t2 _t3 _t4 ))

(defmethod gtec_msgs::ESP32S2FTMFrame
  (:init
   (&key
    ((:rssi __rssi) 0)
    ((:rtt __rtt) 0)
    ((:t1 __t1) 0)
    ((:t2 __t2) 0)
    ((:t3 __t3) 0)
    ((:t4 __t4) 0)
    )
   (send-super :init)
   (setq _rssi (round __rssi))
   (setq _rtt (round __rtt))
   (setq _t1 (round __t1))
   (setq _t2 (round __t2))
   (setq _t3 (round __t3))
   (setq _t4 (round __t4))
   self)
  (:rssi
   (&optional __rssi)
   (if __rssi (setq _rssi __rssi)) _rssi)
  (:rtt
   (&optional __rtt)
   (if __rtt (setq _rtt __rtt)) _rtt)
  (:t1
   (&optional __t1)
   (if __t1 (setq _t1 __t1)) _t1)
  (:t2
   (&optional __t2)
   (if __t2 (setq _t2 __t2)) _t2)
  (:t3
   (&optional __t3)
   (if __t3 (setq _t3 __t3)) _t3)
  (:t4
   (&optional __t4)
   (if __t4 (setq _t4 __t4)) _t4)
  (:serialization-length
   ()
   (+
    ;; int32 _rssi
    4
    ;; int32 _rtt
    4
    ;; int64 _t1
    8
    ;; int64 _t2
    8
    ;; int64 _t3
    8
    ;; int64 _t4
    8
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _rssi
       (write-long _rssi s)
     ;; int32 _rtt
       (write-long _rtt s)
     ;; int64 _t1
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _t1 (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _t1) (= (length (_t1 . bv)) 2)) ;; bignum
              (write-long (ash (elt (_t1 . bv) 0) 0) s)
              (write-long (ash (elt (_t1 . bv) 1) -1) s))
             ((and (class _t1) (= (length (_t1 . bv)) 1)) ;; big1
              (write-long (elt (_t1 . bv) 0) s)
              (write-long (if (>= _t1 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _t1 s)(write-long (if (>= _t1 0) 0 #xffffffff) s)))
     ;; int64 _t2
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _t2 (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _t2) (= (length (_t2 . bv)) 2)) ;; bignum
              (write-long (ash (elt (_t2 . bv) 0) 0) s)
              (write-long (ash (elt (_t2 . bv) 1) -1) s))
             ((and (class _t2) (= (length (_t2 . bv)) 1)) ;; big1
              (write-long (elt (_t2 . bv) 0) s)
              (write-long (if (>= _t2 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _t2 s)(write-long (if (>= _t2 0) 0 #xffffffff) s)))
     ;; int64 _t3
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _t3 (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _t3) (= (length (_t3 . bv)) 2)) ;; bignum
              (write-long (ash (elt (_t3 . bv) 0) 0) s)
              (write-long (ash (elt (_t3 . bv) 1) -1) s))
             ((and (class _t3) (= (length (_t3 . bv)) 1)) ;; big1
              (write-long (elt (_t3 . bv) 0) s)
              (write-long (if (>= _t3 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _t3 s)(write-long (if (>= _t3 0) 0 #xffffffff) s)))
     ;; int64 _t4
#+(or :alpha :irix6 :x86_64)
       (progn (sys::poke _t4 (send s :buffer) (send s :count) :long) (incf (stream-count s) 8))
#-(or :alpha :irix6 :x86_64)
       (cond ((and (class _t4) (= (length (_t4 . bv)) 2)) ;; bignum
              (write-long (ash (elt (_t4 . bv) 0) 0) s)
              (write-long (ash (elt (_t4 . bv) 1) -1) s))
             ((and (class _t4) (= (length (_t4 . bv)) 1)) ;; big1
              (write-long (elt (_t4 . bv) 0) s)
              (write-long (if (>= _t4 0) 0 #xffffffff) s))
             (t                                         ;; integer
              (write-long _t4 s)(write-long (if (>= _t4 0) 0 #xffffffff) s)))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _rssi
     (setq _rssi (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _rtt
     (setq _rtt (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int64 _t1
#+(or :alpha :irix6 :x86_64)
      (setf _t1 (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _t1 (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _t2
#+(or :alpha :irix6 :x86_64)
      (setf _t2 (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _t2 (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _t3
#+(or :alpha :irix6 :x86_64)
      (setf _t3 (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _t3 (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;; int64 _t4
#+(or :alpha :irix6 :x86_64)
      (setf _t4 (prog1 (sys::peek buf ptr- :long) (incf ptr- 8)))
#-(or :alpha :irix6 :x86_64)
      (setf _t4 (let ((b0 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4)))
                  (b1 (prog1 (sys::peek buf ptr- :integer) (incf ptr- 4))))
              (cond ((= b1 -1) b0)
                     ((and (= b1  0)
                           (<= lisp::most-negative-fixnum b0 lisp::most-positive-fixnum))
                      b0)
                    ((= b1  0) (make-instance bignum :size 1 :bv (integer-vector b0)))
                    (t (make-instance bignum :size 2 :bv (integer-vector b0 (ash b1 1)))))))
   ;;
   self)
  )

(setf (get gtec_msgs::ESP32S2FTMFrame :md5sum-) "a1b894ddb8209b3399fd6809e514d068")
(setf (get gtec_msgs::ESP32S2FTMFrame :datatype-) "gtec_msgs/ESP32S2FTMFrame")
(setf (get gtec_msgs::ESP32S2FTMFrame :definition-)
      "int32 rssi
int32 rtt
int64 t1
int64 t2
int64 t3
int64 t4
")



(provide :gtec_msgs/ESP32S2FTMFrame "a1b894ddb8209b3399fd6809e514d068")


