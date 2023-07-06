//
// File rosnodeinterface.h
//
// Code generated for Simulink model 'ReadCustom'.
//
// Model version                  : 10.3
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Tue Jul 04 22:53:49 2023
//

#ifndef _ROS_MATLAB_NODEINTERFACE_
#define _ROS_MATLAB_NODEINTERFACE_
#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)

#else

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"

#endif                                 //_MSC_VER

#include "ReadCustom.h"
#include "ReadCustom_types.h"
#include <thread>
#include <atomic>
#include <chrono>
#include <utility>
#include <mutex>
#include <condition_variable>
#include <ros/ros.h>
#include "std_msgs/Bool.h"
#include "std_msgs/String.h"
#include "rosgraph_msgs/Clock.h"

namespace ros
{
  namespace matlab
  {
    //Semaphore using std::CV and std::mutex
    class Semaphore {
     public:
      std::mutex mMutex;
      std::condition_variable mCV;
      std::atomic_uint mCount;

      //
      Semaphore(int count = 0)
        : mCount(count)
      {
      }

      //
      inline void notify()
      {
        std::unique_lock<std::mutex> lock(mMutex);
        mCount++;
        mCV.notify_all();
      }

      //
      inline void wait()
      {
        std::unique_lock<std::mutex> lock(mMutex);
        while (mCount == 0) {
          mCV.wait(lock);
        }

        if (mCount)
          mCount--;
      }
    };

    //NodeInterface
    class NodeInterface {
      NodeInterface(const NodeInterface& );
      NodeInterface& operator= (const NodeInterface& );

      //
      std::shared_ptr<ros::NodeHandle> mNode;
      Semaphore mBaseRateSem;
      std::shared_ptr<std::thread> mBaseRateThread;
      std::shared_ptr<std::thread> mSchedulerThread;

      //
      //
      Semaphore mStopSem;
      volatile boolean_T mRunModel;

      // External mode background thread
      std::shared_ptr<std::thread> mExtModeThread;
     public:
      NodeInterface();
      ~NodeInterface();

      //
      void initialize(int argc, char ** argv);
      int run();
      void stop(void);
      void terminate(void);

      //
      boolean_T getStopRequestedFlag(void);
      void schedulerThread(void);
      void rosClockSubscriberCallback(const rosgraph_msgs::Clock&);
      void baseRateTask(void);
      void extmodeBackgroundTask(void);
      std::shared_ptr<ros::NodeHandle> getNode()
      {
        return mNode;
      }
    };                                 //class NodeInterface

    std::shared_ptr<ros::matlab::NodeInterface> getNodeInterface();
  }                                    //namespace matlab
}                                      //namespace ros

#ifdef _MSC_VER

#pragma warning(pop)

#else

#pragma GCC diagnostic pop

#endif                                 //_MSC_VER
#endif                                 //_ROS_MATLAB_ROS2CGEN_MULTIRATE_
