// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for jackal_op/MeshUWB
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
#include "jackal_op/MeshUWB.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class JACKAL_OP_EXPORT jackal_op_msg_MeshUWB_common : public MATLABROSMsgInterface<jackal_op::MeshUWB> {
  public:
    virtual ~jackal_op_msg_MeshUWB_common(){}
    virtual void copy_from_struct(jackal_op::MeshUWB* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const jackal_op::MeshUWB* msg, MultiLibLoader loader, size_t size = 1);
};
  void jackal_op_msg_MeshUWB_common::copy_from_struct(jackal_op::MeshUWB* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //header
        const matlab::data::StructArray header_arr = arr["Header"];
        auto msgClassPtr_header = getCommonObject<std_msgs::Header>("std_msgs_msg_Header_common",loader);
        msgClassPtr_header->copy_from_struct(&msg->header,header_arr[0],loader);
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Header' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Header' is wrong type; expected a struct.");
    }
    try {
        //D1
        const matlab::data::TypedArray<double> D1_arr = arr["D1"];
        size_t nelem = D1_arr.getNumberOfElements();
        	msg->D1.resize(nelem);
        	std::copy(D1_arr.begin(), D1_arr.begin()+nelem, msg->D1.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'D1' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'D1' is wrong type; expected a double.");
    }
    try {
        //D2
        const matlab::data::TypedArray<double> D2_arr = arr["D2"];
        size_t nelem = D2_arr.getNumberOfElements();
        	msg->D2.resize(nelem);
        	std::copy(D2_arr.begin(), D2_arr.begin()+nelem, msg->D2.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'D2' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'D2' is wrong type; expected a double.");
    }
    try {
        //D3
        const matlab::data::TypedArray<double> D3_arr = arr["D3"];
        size_t nelem = D3_arr.getNumberOfElements();
        	msg->D3.resize(nelem);
        	std::copy(D3_arr.begin(), D3_arr.begin()+nelem, msg->D3.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'D3' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'D3' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T jackal_op_msg_MeshUWB_common::get_arr(MDFactory_T& factory, const jackal_op::MeshUWB* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","Header","D1","D2","D3"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("jackal_op/MeshUWB");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::Header>("std_msgs_msg_Header_common",loader);
    outArray[ctr]["Header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // D1
    auto currentElement_D1 = (msg + ctr)->D1;
    outArray[ctr]["D1"] = factory.createArray<jackal_op::MeshUWB::_D1_type::const_iterator, double>({currentElement_D1.size(),1}, currentElement_D1.begin(), currentElement_D1.end());
    // D2
    auto currentElement_D2 = (msg + ctr)->D2;
    outArray[ctr]["D2"] = factory.createArray<jackal_op::MeshUWB::_D2_type::const_iterator, double>({currentElement_D2.size(),1}, currentElement_D2.begin(), currentElement_D2.end());
    // D3
    auto currentElement_D3 = (msg + ctr)->D3;
    outArray[ctr]["D3"] = factory.createArray<jackal_op::MeshUWB::_D3_type::const_iterator, double>({currentElement_D3.size(),1}, currentElement_D3.begin(), currentElement_D3.end());
    }
    return std::move(outArray);
  } 
class JACKAL_OP_EXPORT jackal_op_MeshUWB_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~jackal_op_MeshUWB_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          jackal_op_MeshUWB_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<jackal_op::MeshUWB,jackal_op_msg_MeshUWB_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         jackal_op_MeshUWB_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<jackal_op::MeshUWB,jackal_op::MeshUWB::ConstPtr,jackal_op_msg_MeshUWB_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         jackal_op_MeshUWB_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<jackal_op::MeshUWB,jackal_op_msg_MeshUWB_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(jackal_op_msg_MeshUWB_common, MATLABROSMsgInterface<jackal_op::MeshUWB>)
CLASS_LOADER_REGISTER_CLASS(jackal_op_MeshUWB_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1