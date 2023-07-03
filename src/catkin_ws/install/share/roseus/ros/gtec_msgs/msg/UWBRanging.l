;; Auto-generated. Do not edit!


(when (boundp 'gtec_msgs::UWBRanging)
  (if (not (find-package "GTEC_MSGS"))
    (make-package "GTEC_MSGS"))
  (shadow 'UWBRanging (find-package "GTEC_MSGS")))
(unless (find-package "GTEC_MSGS::UWBRANGING")
  (make-package "GTEC_MSGS::UWBRANGING"))

(in-package "ROS")
;;//! \htmlinclude UWBRanging.msg.html


(defclass gtec_msgs::UWBRanging
  :super ros::object
  :slots (_anchorId _tagId _range _rawrange _biasCorrection _seq _maxNoise _stdNoise _firstPathAmp1 _firstPathAmp2 _firstPathAmp3 _maxGrowthCIR _rxPreamCount _firstPath _channel _prf _datarate _preambleLength _pacSize _errorEstimation ))

(defmethod gtec_msgs::UWBRanging
  (:init
   (&key
    ((:anchorId __anchorId) 0)
    ((:tagId __tagId) 0)
    ((:range __range) 0)
    ((:rawrange __rawrange) 0)
    ((:biasCorrection __biasCorrection) 0)
    ((:seq __seq) 0)
    ((:maxNoise __maxNoise) 0)
    ((:stdNoise __stdNoise) 0)
    ((:firstPathAmp1 __firstPathAmp1) 0)
    ((:firstPathAmp2 __firstPathAmp2) 0)
    ((:firstPathAmp3 __firstPathAmp3) 0)
    ((:maxGrowthCIR __maxGrowthCIR) 0)
    ((:rxPreamCount __rxPreamCount) 0)
    ((:firstPath __firstPath) 0)
    ((:channel __channel) 0.0)
    ((:prf __prf) 0)
    ((:datarate __datarate) 0.0)
    ((:preambleLength __preambleLength) 0)
    ((:pacSize __pacSize) 0)
    ((:errorEstimation __errorEstimation) 0.0)
    )
   (send-super :init)
   (setq _anchorId (round __anchorId))
   (setq _tagId (round __tagId))
   (setq _range (round __range))
   (setq _rawrange (round __rawrange))
   (setq _biasCorrection (round __biasCorrection))
   (setq _seq (round __seq))
   (setq _maxNoise (round __maxNoise))
   (setq _stdNoise (round __stdNoise))
   (setq _firstPathAmp1 (round __firstPathAmp1))
   (setq _firstPathAmp2 (round __firstPathAmp2))
   (setq _firstPathAmp3 (round __firstPathAmp3))
   (setq _maxGrowthCIR (round __maxGrowthCIR))
   (setq _rxPreamCount (round __rxPreamCount))
   (setq _firstPath (round __firstPath))
   (setq _channel (float __channel))
   (setq _prf (round __prf))
   (setq _datarate (float __datarate))
   (setq _preambleLength (round __preambleLength))
   (setq _pacSize (round __pacSize))
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
  (:rawrange
   (&optional __rawrange)
   (if __rawrange (setq _rawrange __rawrange)) _rawrange)
  (:biasCorrection
   (&optional __biasCorrection)
   (if __biasCorrection (setq _biasCorrection __biasCorrection)) _biasCorrection)
  (:seq
   (&optional __seq)
   (if __seq (setq _seq __seq)) _seq)
  (:maxNoise
   (&optional __maxNoise)
   (if __maxNoise (setq _maxNoise __maxNoise)) _maxNoise)
  (:stdNoise
   (&optional __stdNoise)
   (if __stdNoise (setq _stdNoise __stdNoise)) _stdNoise)
  (:firstPathAmp1
   (&optional __firstPathAmp1)
   (if __firstPathAmp1 (setq _firstPathAmp1 __firstPathAmp1)) _firstPathAmp1)
  (:firstPathAmp2
   (&optional __firstPathAmp2)
   (if __firstPathAmp2 (setq _firstPathAmp2 __firstPathAmp2)) _firstPathAmp2)
  (:firstPathAmp3
   (&optional __firstPathAmp3)
   (if __firstPathAmp3 (setq _firstPathAmp3 __firstPathAmp3)) _firstPathAmp3)
  (:maxGrowthCIR
   (&optional __maxGrowthCIR)
   (if __maxGrowthCIR (setq _maxGrowthCIR __maxGrowthCIR)) _maxGrowthCIR)
  (:rxPreamCount
   (&optional __rxPreamCount)
   (if __rxPreamCount (setq _rxPreamCount __rxPreamCount)) _rxPreamCount)
  (:firstPath
   (&optional __firstPath)
   (if __firstPath (setq _firstPath __firstPath)) _firstPath)
  (:channel
   (&optional __channel)
   (if __channel (setq _channel __channel)) _channel)
  (:prf
   (&optional __prf)
   (if __prf (setq _prf __prf)) _prf)
  (:datarate
   (&optional __datarate)
   (if __datarate (setq _datarate __datarate)) _datarate)
  (:preambleLength
   (&optional __preambleLength)
   (if __preambleLength (setq _preambleLength __preambleLength)) _preambleLength)
  (:pacSize
   (&optional __pacSize)
   (if __pacSize (setq _pacSize __pacSize)) _pacSize)
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
    ;; int32 _rawrange
    4
    ;; int32 _biasCorrection
    4
    ;; int32 _seq
    4
    ;; int32 _maxNoise
    4
    ;; int32 _stdNoise
    4
    ;; int32 _firstPathAmp1
    4
    ;; int32 _firstPathAmp2
    4
    ;; int32 _firstPathAmp3
    4
    ;; int32 _maxGrowthCIR
    4
    ;; int32 _rxPreamCount
    4
    ;; int32 _firstPath
    4
    ;; float64 _channel
    8
    ;; int32 _prf
    4
    ;; float64 _datarate
    8
    ;; int32 _preambleLength
    4
    ;; int32 _pacSize
    4
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
     ;; int32 _rawrange
       (write-long _rawrange s)
     ;; int32 _biasCorrection
       (write-long _biasCorrection s)
     ;; int32 _seq
       (write-long _seq s)
     ;; int32 _maxNoise
       (write-long _maxNoise s)
     ;; int32 _stdNoise
       (write-long _stdNoise s)
     ;; int32 _firstPathAmp1
       (write-long _firstPathAmp1 s)
     ;; int32 _firstPathAmp2
       (write-long _firstPathAmp2 s)
     ;; int32 _firstPathAmp3
       (write-long _firstPathAmp3 s)
     ;; int32 _maxGrowthCIR
       (write-long _maxGrowthCIR s)
     ;; int32 _rxPreamCount
       (write-long _rxPreamCount s)
     ;; int32 _firstPath
       (write-long _firstPath s)
     ;; float64 _channel
       (sys::poke _channel (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _prf
       (write-long _prf s)
     ;; float64 _datarate
       (sys::poke _datarate (send s :buffer) (send s :count) :double) (incf (stream-count s) 8)
     ;; int32 _preambleLength
       (write-long _preambleLength s)
     ;; int32 _pacSize
       (write-long _pacSize s)
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
   ;; int32 _rawrange
     (setq _rawrange (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _biasCorrection
     (setq _biasCorrection (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _seq
     (setq _seq (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _maxNoise
     (setq _maxNoise (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _stdNoise
     (setq _stdNoise (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _firstPathAmp1
     (setq _firstPathAmp1 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _firstPathAmp2
     (setq _firstPathAmp2 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _firstPathAmp3
     (setq _firstPathAmp3 (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _maxGrowthCIR
     (setq _maxGrowthCIR (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _rxPreamCount
     (setq _rxPreamCount (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _firstPath
     (setq _firstPath (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _channel
     (setq _channel (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _prf
     (setq _prf (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _datarate
     (setq _datarate (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;; int32 _preambleLength
     (setq _preambleLength (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; int32 _pacSize
     (setq _pacSize (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;; float64 _errorEstimation
     (setq _errorEstimation (sys::peek buf ptr- :double)) (incf ptr- 8)
   ;;
   self)
  )

(setf (get gtec_msgs::UWBRanging :md5sum-) "a2ecb2ec6e49b5856c7d150d936a536b")
(setf (get gtec_msgs::UWBRanging :datatype-) "gtec_msgs/UWBRanging")
(setf (get gtec_msgs::UWBRanging :definition-)
      "int16 anchorId
int16 tagId
int32 range
int32 rawrange
int32 biasCorrection
int32 seq
int32 maxNoise
int32 stdNoise
int32 firstPathAmp1
int32 firstPathAmp2
int32 firstPathAmp3
int32 maxGrowthCIR
int32 rxPreamCount
int32 firstPath
float64 channel
int32 prf
float64 datarate
int32 preambleLength
int32 pacSize
float64 errorEstimation
")



(provide :gtec_msgs/UWBRanging "a2ecb2ec6e49b5856c7d150d936a536b")


