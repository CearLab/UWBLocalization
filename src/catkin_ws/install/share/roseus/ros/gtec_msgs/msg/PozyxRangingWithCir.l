;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::PozyxRangingWithCir)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'PozyxRangingWithCir (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::POZYXRANGINGWITHCIR")
  (make-package "GTEC_MSGS::POZYXRANGINGWITHCIR"))

(in-package "ROS")
;;//! \htmlinclude PozyxRangingWithCir.msg.html


(defclass gtec_msgs::PozyxRangingWithCir
  :super ros::object
  :slots (_originId _originType _destinationId _destinationType _range _ts _seq _rxPower _channel _datarate _prf _preambleLength _txGain _angle _cir ))

(defmethod gtec_msgs::PozyxRangingWithCir
  (:init
   (&key
    ((:originId __originId) 0)
    ((:originType __originType) 0)
    ((:destinationId __destinationId) 0)
    ((:destinationType __destinationType) 0)
    ((:range __range) 0)
    ((:ts __ts) 0)
    ((:seq __seq) 0)
    ((:rxPower __rxPower) 0.0)
    ((:channel __channel) 0.0)
    ((:datarate __datarate) 0.0)
    ((:prf __prf) 0)
    ((:preambleLength __preambleLength) 0)
    ((:txGain __txGain) 0.0)
    ((:angle __angle) 0.0)
    ((:cir __cir) (make-array 0 :initial-element 0 :element-type :integer))
    )
   (send-super :init)
   (setq _originId (round __originId))
   (setq _originType (round __originType))
   (setq _destinationId (round __destinationId))
   (setq _destinationType (round __destinationType))
   (setq _range (round __range))
   (setq _ts (round __ts))
   (setq _seq (round __seq))
   (setq _rxPower (float __rxPower))
   (setq _channel (float __channel))
   (setq _datarate (float __datarate))
   (setq _prf (round __prf))
   (setq _preambleLength (round __preambleLength))
   (setq _txGain (float __txGain))
   (setq _angle (float __angle))
   (setq _cir __cir)
   self)
  (:originId
   (&optional __originId)
   (if __originId (setq _originId __originId)) _originId)
  (:originType
   (&optional __originType)
   (if __originType (setq _originType __originType)) _originType)
  (:destinationId
   (&optional __destinationId)
   (if __destinationId (setq _destinationId __destinationId)) _destinationId)
  (:destinationType
   (&optional __destinationType)
   (if __destinationType (setq _destinationType __destinationType)) _destinationType)
  (:range
   (&optional __range)
   (if __range (setq _range __range)) _range)
  (:ts
   (&optional __ts)
   (if __ts (setq _ts __ts)) _ts)
  (:seq
   (&optional __seq)
   (if __seq (setq _seq __seq)) _seq)
  (:rxPower
   (&optional __rxPower)
   (if __rxPower (setq _rxPower __rxPower)) _rxPower)
  (:channel
   (&optional __channel)
   (if __channel (setq _channel __channel)) _channel)
  (:datarate
   (&optional __datarate)
   (if __datarate (setq _datarate __datarate)) _datarate)
  (:prf
   (&optional __prf)
   (if __prf (setq _prf __prf)) _prf)
  (:preambleLength
   (&optional __preambleLength)
   (if __preambleLength (setq _preambleLength __preambleLength)) _preambleLength)
  (:txGain
   (&optional __txGain)
   (if __txGain (setq _txGain __txGain)) _txGain)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:cir
   (&optional __cir)
   (if __cir (setq _cir __cir)) _cir)
  (:serialization-length
   ()
   (+
    ;; int32 _originId
    4
    ;; int16 _originType
    2
    ;; int32 _destinationId
    4
    ;; int16 _destinationType
    2
    ;; int32 _range
    4
    ;; int32 _ts
    4
    ;; int32 _seq
    4
    ;; float64 _rxPower
    8
    ;; float64 _channel
    8
    ;; float64 _datarate
    8
    ;; int32 _prf
    4
    ;; int32 _preambleLength
    4
    ;; float64 _txGain
    8
    ;; float64 _angle
    8
    ;; int16[] _cir
    (* 2    (length _cir)) 4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int32 _originId
       (write-long _originId s)
     ;; int16 _originType
       (write-word _originType s)
     ;; int32 _destinationId
       (write-long _destinationId s)
     ;; int16 _destinationType
       (write-word _destinationType s)
     ;; int32 _range
       (write-long _range s)
     ;; int32 _ts
       (write-long _ts s)
     ;; int32 _seq
       (write-long _seq s)
     ;; float64 _rxPower
       (sys::poke _rxPower (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _channel
       (sys::poke _channel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _datarate
       (sys::poke _datarate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _prf
       (write-long _prf s)
     ;; int32 _preambleLength
       (write-long _preambleLength s)
     ;; float64 _txGain
       (sys::poke _txGain (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; float64 _angle
       (sys::poke _angle (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int16[] _cir
     (write-long (length _cir) s)
     (dotimes (i (length _cir))
       (write-word (elt _cir i) s)
       )
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int32 _originId
     (setq _originId (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int16 _originType
     (setq _originType (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int32 _destinationId
     (setq _destinationId (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int16 _destinationType
     (setq _destinationType (sys::peek buf ptr- :short)) (incf ptr- 2)
   ;; int32 _range
     (setq _range (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _ts
     (setq _ts (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _seq
     (setq _seq (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _rxPower
     (setq _rxPower (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _channel
     (setq _channel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _datarate
     (setq _datarate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _prf
     (setq _prf (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _preambleLength
     (setq _preambleLength (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _txGain
     (setq _txGain (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; float64 _angle
     (setq _angle (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int16[] _cir
   (let (n)
     (setq n (sys::peek buf ptr- :integer)) (incf ptr- 4)
     (setq _cir (instantiate integer-vector n))
     (dotimes (i n)
     (setf (elt _cir i) (sys::peek buf ptr- :short)) (incf ptr- 2)
     ))
   ;;
   self)
  )

(setf (get gtec_msgs::PozyxRangingWithCir :md5sum-) "57228d0a630edec43d8b895ec4dc9202")
(setf (get gtec_msgs::PozyxRangingWithCir :datatype-) "gtec_msgs/PozyxRangingWithCir")
(setf (get gtec_msgs::PozyxRangingWithCir :definition-)
      "int32 originId
int16 originType
int32 destinationId
int16 destinationType
int32 range
int32 ts
int32 seq
float64 rxPower
float64 channel
float64 datarate
int32 prf
int32 preambleLength
float64 txGain
float64 angle
int16[] cir
")



(provide :gtec_msgs/PozyxRangingWithCir "57228d0a630edec43d8b895ec4dc9202")


