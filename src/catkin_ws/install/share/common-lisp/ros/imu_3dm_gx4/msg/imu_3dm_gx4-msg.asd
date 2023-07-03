
(cl:in-package :asdf)

(defsystem "imu_3dm_gx4-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :std_msgs-msg
)
  :components ((:file "_package")
    (:file "FilterOutput" :depends-on ("_package_FilterOutput"))
    (:file "_package_FilterOutput" :depends-on ("_package"))
  ))