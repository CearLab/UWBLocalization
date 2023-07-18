// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for rosmsgs/ESP32S2FTMFrame
#include "boost/date_time.hpp"
#include "boost/shared_array.hpp"
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4244)
#pragma warning(disable : 4265)
#pragma warning(disable : 4458)
#pragma warning(disable : 4100)
#pragma warning(disable : 4127)
#pragma warning(disable : 4267)
#pragma warning(disable : 4068)
#pragma warning(disable : 4245)
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
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif //_MSC_VER
#include "ros/ros.h"
#include "rosmsgs/ESP32S2FTMFrame.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class ROSMSGS_EXPORT rosmsgs_msg_ESP32S2FTMFrame_common : public MATLABROSMsgInterface<rosmsgs::ESP32S2FTMFrame> {
  public:
    virtual ~rosmsgs_msg_ESP32S2FTMFrame_common(){}
    virtual void copy_from_struct(rosmsgs::ESP32S2FTMFrame* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const rosmsgs::ESP32S2FTMFrame* msg, MultiLibLoader loader, size_t size = 1);
};
  void rosmsgs_msg_ESP32S2FTMFrame_common::copy_from_struct(rosmsgs::ESP32S2FTMFrame* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //rssi
        const matlab::data::TypedArray<int32_t> rssi_arr = arr["Rssi"];
        msg->rssi = rssi_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Rssi' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Rssi' is wrong type; expected a int32.");
    }
    try {
        //rtt
        const matlab::data::TypedArray<int32_t> rtt_arr = arr["Rtt"];
        msg->rtt = rtt_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Rtt' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Rtt' is wrong type; expected a int32.");
    }
    try {
        //t1
        const matlab::data::TypedArray<int64_t> t1_arr = arr["T1"];
        msg->t1 = t1_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'T1' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'T1' is wrong type; expected a int64.");
    }
    try {
        //t2
        const matlab::data::TypedArray<int64_t> t2_arr = arr["T2"];
        msg->t2 = t2_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'T2' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'T2' is wrong type; expected a int64.");
    }
    try {
        //t3
        const matlab::data::TypedArray<int64_t> t3_arr = arr["T3"];
        msg->t3 = t3_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'T3' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'T3' is wrong type; expected a int64.");
    }
    try {
        //t4
        const matlab::data::TypedArray<int64_t> t4_arr = arr["T4"];
        msg->t4 = t4_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'T4' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'T4' is wrong type; expected a int64.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T rosmsgs_msg_ESP32S2FTMFrame_common::get_arr(MDFactory_T& factory, const rosmsgs::ESP32S2FTMFrame* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","Rssi","Rtt","T1","T2","T3","T4"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("rosmsgs/ESP32S2FTMFrame");
    // rssi
    auto currentElement_rssi = (msg + ctr)->rssi;
    outArray[ctr]["Rssi"] = factory.createScalar(currentElement_rssi);
    // rtt
    auto currentElement_rtt = (msg + ctr)->rtt;
    outArray[ctr]["Rtt"] = factory.createScalar(currentElement_rtt);
    // t1
    auto currentElement_t1 = (msg + ctr)->t1;
    outArray[ctr]["T1"] = factory.createScalar(currentElement_t1);
    // t2
    auto currentElement_t2 = (msg + ctr)->t2;
    outArray[ctr]["T2"] = factory.createScalar(currentElement_t2);
    // t3
    auto currentElement_t3 = (msg + ctr)->t3;
    outArray[ctr]["T3"] = factory.createScalar(currentElement_t3);
    // t4
    auto currentElement_t4 = (msg + ctr)->t4;
    outArray[ctr]["T4"] = factory.createScalar(currentElement_t4);
    }
    return std::move(outArray);
  } 
class ROSMSGS_EXPORT rosmsgs_ESP32S2FTMFrame_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~rosmsgs_ESP32S2FTMFrame_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          rosmsgs_ESP32S2FTMFrame_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<rosmsgs::ESP32S2FTMFrame,rosmsgs_msg_ESP32S2FTMFrame_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         rosmsgs_ESP32S2FTMFrame_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<rosmsgs::ESP32S2FTMFrame,rosmsgs::ESP32S2FTMFrame::ConstPtr,rosmsgs_msg_ESP32S2FTMFrame_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         rosmsgs_ESP32S2FTMFrame_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<rosmsgs::ESP32S2FTMFrame,rosmsgs_msg_ESP32S2FTMFrame_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(rosmsgs_msg_ESP32S2FTMFrame_common, MATLABROSMsgInterface<rosmsgs::ESP32S2FTMFrame>)
CLASS_LOADER_REGISTER_CLASS(rosmsgs_ESP32S2FTMFrame_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1