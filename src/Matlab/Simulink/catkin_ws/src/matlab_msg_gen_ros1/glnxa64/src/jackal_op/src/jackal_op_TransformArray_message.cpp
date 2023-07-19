// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for jackal_op/TransformArray
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
#include "jackal_op/TransformArray.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class JACKAL_OP_EXPORT jackal_op_msg_TransformArray_common : public MATLABROSMsgInterface<jackal_op::TransformArray> {
  public:
    virtual ~jackal_op_msg_TransformArray_common(){}
    virtual void copy_from_struct(jackal_op::TransformArray* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const jackal_op::TransformArray* msg, MultiLibLoader loader, size_t size = 1);
};
  void jackal_op_msg_TransformArray_common::copy_from_struct(jackal_op::TransformArray* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //transforms
        const matlab::data::StructArray transforms_arr = arr["Transforms"];
        for (auto _transformsarr : transforms_arr) {
        	geometry_msgs::TransformStamped _val;
        auto msgClassPtr_transforms = getCommonObject<geometry_msgs::TransformStamped>("geometry_msgs_msg_TransformStamped_common",loader);
        msgClassPtr_transforms->copy_from_struct(&_val,_transformsarr,loader);
        	msg->transforms.push_back(_val);
        }
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Transforms' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Transforms' is wrong type; expected a struct.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T jackal_op_msg_TransformArray_common::get_arr(MDFactory_T& factory, const jackal_op::TransformArray* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","Transforms"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("jackal_op/TransformArray");
    // transforms
    auto currentElement_transforms = (msg + ctr)->transforms;
    auto msgClassPtr_transforms = getCommonObject<geometry_msgs::TransformStamped>("geometry_msgs_msg_TransformStamped_common",loader);
    outArray[ctr]["Transforms"] = msgClassPtr_transforms->get_arr(factory,&currentElement_transforms[0],loader,currentElement_transforms.size());
    }
    return std::move(outArray);
  } 
class JACKAL_OP_EXPORT jackal_op_TransformArray_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~jackal_op_TransformArray_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          jackal_op_TransformArray_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<jackal_op::TransformArray,jackal_op_msg_TransformArray_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         jackal_op_TransformArray_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<jackal_op::TransformArray,jackal_op::TransformArray::ConstPtr,jackal_op_msg_TransformArray_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         jackal_op_TransformArray_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<jackal_op::TransformArray,jackal_op_msg_TransformArray_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(jackal_op_msg_TransformArray_common, MATLABROSMsgInterface<jackal_op::TransformArray>)
CLASS_LOADER_REGISTER_CLASS(jackal_op_TransformArray_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1