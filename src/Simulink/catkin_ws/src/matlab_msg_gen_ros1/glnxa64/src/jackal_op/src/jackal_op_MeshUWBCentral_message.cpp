// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for jackal_op/MeshUWBCentral
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
#include "jackal_op/MeshUWBCentral.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class JACKAL_OP_EXPORT jackal_op_msg_MeshUWBCentral_common : public MATLABROSMsgInterface<jackal_op::MeshUWBCentral> {
  public:
    virtual ~jackal_op_msg_MeshUWBCentral_common(){}
    virtual void copy_from_struct(jackal_op::MeshUWBCentral* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const jackal_op::MeshUWBCentral* msg, MultiLibLoader loader, size_t size = 1);
};
  void jackal_op_msg_MeshUWBCentral_common::copy_from_struct(jackal_op::MeshUWBCentral* msg, const matlab::data::Struct& arr,
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
        //DC
        const matlab::data::TypedArray<double> DC_arr = arr["DC"];
        size_t nelem = DC_arr.getNumberOfElements();
        	msg->DC.resize(nelem);
        	std::copy(DC_arr.begin(), DC_arr.begin()+nelem, msg->DC.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'DC' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'DC' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T jackal_op_msg_MeshUWBCentral_common::get_arr(MDFactory_T& factory, const jackal_op::MeshUWBCentral* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","Header","DC"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("jackal_op/MeshUWBCentral");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::Header>("std_msgs_msg_Header_common",loader);
    outArray[ctr]["Header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // DC
    auto currentElement_DC = (msg + ctr)->DC;
    outArray[ctr]["DC"] = factory.createArray<jackal_op::MeshUWBCentral::_DC_type::const_iterator, double>({currentElement_DC.size(),1}, currentElement_DC.begin(), currentElement_DC.end());
    }
    return std::move(outArray);
  } 
class JACKAL_OP_EXPORT jackal_op_MeshUWBCentral_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~jackal_op_MeshUWBCentral_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          jackal_op_MeshUWBCentral_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<jackal_op::MeshUWBCentral,jackal_op_msg_MeshUWBCentral_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         jackal_op_MeshUWBCentral_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<jackal_op::MeshUWBCentral,jackal_op::MeshUWBCentral::ConstPtr,jackal_op_msg_MeshUWBCentral_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         jackal_op_MeshUWBCentral_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<jackal_op::MeshUWBCentral,jackal_op_msg_MeshUWBCentral_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(jackal_op_msg_MeshUWBCentral_common, MATLABROSMsgInterface<jackal_op::MeshUWBCentral>)
CLASS_LOADER_REGISTER_CLASS(jackal_op_MeshUWBCentral_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1