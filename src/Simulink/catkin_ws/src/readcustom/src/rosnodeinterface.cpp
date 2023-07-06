//
// File rosnodeinterface.cpp
//
// Code generated for Simulink model 'ReadCustom'.
//
// Model version                  : 10.3
// Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
// C/C++ source code generated on : Tue Jul 04 22:53:49 2023
//

#ifdef _MSC_VER

#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)
#pragma comment(lib, "Ws2_32.lib")

#else

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#pragma GCC diagnostic ignored "-Wredundant-decls"
#pragma GCC diagnostic ignored "-Wnon-virtual-dtor"
#pragma GCC diagnostic ignored "-Wdelete-non-virtual-dtor"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wshadow"

#endif                                 //_MSC_VER

#include "ReadCustom.h"
#include "rosnodeinterface.h"
#include <thread>
#include <chrono>
#include <utility>

//
// Forward declare the ROS Time stepping and notification related
// functions and global flags/variables
//
// Flag to determine that model should continue to run
static volatile bool modelRuns;
static uint32_t _clock_msg_sec;
static uint32_t _clock_msg_nsec;

// Counter to determine the number of overruns
static int numOverruns;

// Function to publish notification update status of step call
static void publishDone(bool status);
namespace ros
{
  namespace matlab
  {
    NodeInterface::NodeInterface()
      : mNode()
      , mBaseRateSem()
      , mBaseRateThread()
      , mSchedulerThread()
      , mExtModeThread()
      , mStopSem()
      , mRunModel(true)
    {
    }

    NodeInterface::~NodeInterface()
    {
      terminate();
    }

    void NodeInterface::initialize(int argc, char ** argv)
    {
      try {
        mNode = std::make_shared<ros::NodeHandle>();
        ROS_INFO("** Starting the model \"ReadCustom\" **\n");

        {
          char* extmodeArg[] = { "-port", "17725", "-blocking", "1", "-verbose",
            "0" };

          rtExtModeParseArgs(6, (const char_T **)extmodeArg, NULL);
        }

        // initialize the model which will initialize the publishers and subscribers
        rtmSetErrorStatus(ReadCustom_M, (NULL));
        ReadCustom_initialize();

        /* External mode */
        rtSetTFinalForExtMode(&rtmGetTFinal(ReadCustom_M));
        rtExtModeCheckInit(1);

        {
          boolean_T rtmStopReq = false;
          rtExtModeWaitForStartPkt(ReadCustom_M->extModeInfo, 1,
            &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(ReadCustom_M, true);
          }
        }

        rtERTExtModeStartMsg();
        mExtModeThread = std::make_shared<std::thread>(&NodeInterface::
          extmodeBackgroundTask, this);

        // create the threads for the rates in the Model
        mBaseRateThread = std::make_shared<std::thread>(&NodeInterface::
          baseRateTask, this);

        // create scheduler task for "/clock" topic subscriber
        mSchedulerThread = std::make_shared<std::thread>(&NodeInterface::
          schedulerThread, this);
      } catch (std::exception& ex) {
        std::cout << ex.what() << std::endl;
        throw ex;
      }
    }

    int NodeInterface::run()
    {
      // Wait for ROSTime scheduler to finish
      mStopSem.wait();
      mRunModel = false;
      return 0;
    }

    boolean_T NodeInterface::getStopRequestedFlag(void)
    {

#ifndef rtmGetStopRequested

      return (!(rtmGetErrorStatus(ReadCustom_M)
                == (NULL)));

#else

      return (!(rtmGetErrorStatus(ReadCustom_M)
                == (NULL)) || rtmGetStopRequested(ReadCustom_M));

#endif

    }

    void NodeInterface::terminate(void)
    {
      if (mBaseRateThread.get()) {
        mBaseRateSem.notify();
        mBaseRateThread->join();
        mRunModel = false;
        mBaseRateThread.reset();
        if (mSchedulerThread.get()) {
          mSchedulerThread->join();
          mSchedulerThread.reset();
        }

        ReadCustom_terminate();
        rtExtModeShutdown(1);
        mNode.reset();
      }
    }

    //
    // Notify step function
    //
    static void publishDone(bool status)
    {
      if (status == true) {
        modelRuns = false;
      }
    }

    //
    // ROS Clock topic subscriber callback to run the base rate task
    //
    void NodeInterface::rosClockSubscriberCallback(const rosgraph_msgs::Clock &
      msg)
    {
      static uint64_t lastEndTime = 0;
      const uint64_t baseRateNanoSec = 10000000;
      const uint64_t currentTime = msg.clock.toNSec();
      if (lastEndTime == 0) {
        ROS_INFO("** Unblocking base-rate at %.6f", (double)currentTime/1E9);

        // Notify model stepping
        modelRuns = true;
        mBaseRateSem.notify();

        // Update lastEndTime
        lastEndTime = currentTime;
      } else {
        const uint64_t interval = currentTime - lastEndTime;
        if (interval >= baseRateNanoSec) {
          uint64_t missedSteps = interval/baseRateNanoSec;
          if (missedSteps < 2) {
            // Missed only one step
            if (modelRuns) {
              // Overrun happens
              ++numOverruns;
              ROS_ERROR("Overrun %d", numOverruns);
            }

            // Notify model stepping
            modelRuns = true;
            mBaseRateSem.notify();
          } else {
            for (uint64_t i=0; i<missedSteps; ++i) {
              while (modelRuns) {
                // Wait until model finishing the current step
              }

              // Notify model stepping
              modelRuns = true;
              mBaseRateSem.notify();
            }
          }

          lastEndTime = currentTime;
        } else {
          // Publish "done", because there is nothing to do in this time slot
          publishDone(false);
        }
      }
    }

    //
    // Scheduler Task using ROS Time published by "/clock" topic to run base-rate
    //
    void NodeInterface::schedulerThread(void)
    {

#ifdef MW_DEBUG_LOG

      ROS_INFO("ROS schedulerTask entered\n");

#endif

      std::string sClockTopic = "/clock";
      ros::NodeHandle n;
      ros::Subscriber sub = n.subscribe(sClockTopic, 10, &ros::matlab::
        NodeInterface::rosClockSubscriberCallback, this);
      if (sub == NULL) {
        ROS_INFO("Error: cannot subscribe the '%s'", sClockTopic.c_str());
        return;
      }

      ros::spin();

      // Unblock main thread and terminate
      mStopSem.notify();
      return;
    }

    // Base-rate task
    void NodeInterface::baseRateTask(void)
    {
      mRunModel = (rtmGetErrorStatus(ReadCustom_M) ==
                   (NULL));
      while (mRunModel) {
        mBaseRateSem.wait();

#ifdef MW_DEBUG_LOG

        ROS_INFO("** Base rate task semaphore received\n");

#endif

        if (!mRunModel)
          break;

        /* External mode */
        {
          boolean_T rtmStopReq = false;
          rtExtModePauseIfNeeded(ReadCustom_M->extModeInfo, 1,
            &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(ReadCustom_M, true);
          }

          if (rtmGetStopRequested(ReadCustom_M) == true) {
            rtmSetErrorStatus(ReadCustom_M, "Simulation finished");
            mRunModel = false;
            break;
          }
        }

        ReadCustom_step();
        publishDone(true);
        rtExtModeCheckEndTrigger();
        mRunModel = !NodeInterface::getStopRequestedFlag();
      }

      // Shutdown the ROS node
      ros::shutdown();
    }

    void NodeInterface::extmodeBackgroundTask(void)
    {
      while (mRunModel) {
        /* External mode */
        {
          boolean_T rtmStopReq = false;
          rtExtModeOneStep(ReadCustom_M->extModeInfo, 1,
                           &rtmStopReq);
          if (rtmStopReq) {
            rtmSetStopRequested(ReadCustom_M, true);
          }
        }
      }
    }
  }                                    //namespace matlab
}                                      //namespace ros

#ifdef _MSC_VER

#pragma warning(pop)

#else

#pragma GCC diagnostic pop

#endif                                 //_MSC_VER
