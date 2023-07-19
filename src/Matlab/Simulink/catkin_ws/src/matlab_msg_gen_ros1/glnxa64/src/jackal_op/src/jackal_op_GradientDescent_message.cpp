// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for jackal_op/GradientDescent
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
#include "jackal_op/GradientDescent.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class JACKAL_OP_EXPORT jackal_op_msg_GradientDescent_common : public MATLABROSMsgInterface<jackal_op::GradientDescent> {
  public:
    virtual ~jackal_op_msg_GradientDescent_common(){}
    virtual void copy_from_struct(jackal_op::GradientDescent* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const jackal_op::GradientDescent* msg, MultiLibLoader loader, size_t size = 1);
};
  void jackal_op_msg_GradientDescent_common::copy_from_struct(jackal_op::GradientDescent* msg, const matlab::data::Struct& arr,
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
        //J
        const matlab::data::TypedArray<double> J_arr = arr["J"];
        msg->J = J_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'J' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'J' is wrong type; expected a double.");
    }
    try {
        //GJ
        const matlab::data::TypedArray<double> GJ_arr = arr["GJ"];
        size_t nelem = GJ_arr.getNumberOfElements();
        	msg->GJ.resize(nelem);
        	std::copy(GJ_arr.begin(), GJ_arr.begin()+nelem, msg->GJ.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'GJ' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'GJ' is wrong type; expected a double.");
    }
    try {
        //HJ
        const matlab::data::TypedArray<double> HJ_arr = arr["HJ"];
        size_t nelem = HJ_arr.getNumberOfElements();
        	msg->HJ.resize(nelem);
        	std::copy(HJ_arr.begin(), HJ_arr.begin()+nelem, msg->HJ.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'HJ' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'HJ' is wrong type; expected a double.");
    }
    try {
        //A
        const matlab::data::TypedArray<double> A_arr = arr["A"];
        size_t nelem = A_arr.getNumberOfElements();
        	msg->A.resize(nelem);
        	std::copy(A_arr.begin(), A_arr.begin()+nelem, msg->A.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'A' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'A' is wrong type; expected a double.");
    }
    try {
        //p
        const matlab::data::TypedArray<double> p_arr = arr["P"];
        size_t nelem = p_arr.getNumberOfElements();
        	msg->p.resize(nelem);
        	std::copy(p_arr.begin(), p_arr.begin()+nelem, msg->p.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'P' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'P' is wrong type; expected a double.");
    }
    try {
        //pg
        const matlab::data::TypedArray<double> pg_arr = arr["Pg"];
        size_t nelem = pg_arr.getNumberOfElements();
        	msg->pg.resize(nelem);
        	std::copy(pg_arr.begin(), pg_arr.begin()+nelem, msg->pg.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Pg' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Pg' is wrong type; expected a double.");
    }
    try {
        //N
        const matlab::data::TypedArray<double> N_arr = arr["N"];
        size_t nelem = N_arr.getNumberOfElements();
        	msg->N.resize(nelem);
        	std::copy(N_arr.begin(), N_arr.begin()+nelem, msg->N.begin());
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'N' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'N' is wrong type; expected a double.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T jackal_op_msg_GradientDescent_common::get_arr(MDFactory_T& factory, const jackal_op::GradientDescent* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","Header","J","GJ","HJ","A","P","Pg","N"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("jackal_op/GradientDescent");
    // header
    auto currentElement_header = (msg + ctr)->header;
    auto msgClassPtr_header = getCommonObject<std_msgs::Header>("std_msgs_msg_Header_common",loader);
    outArray[ctr]["Header"] = msgClassPtr_header->get_arr(factory, &currentElement_header, loader);
    // J
    auto currentElement_J = (msg + ctr)->J;
    outArray[ctr]["J"] = factory.createScalar(currentElement_J);
    // GJ
    auto currentElement_GJ = (msg + ctr)->GJ;
    outArray[ctr]["GJ"] = factory.createArray<jackal_op::GradientDescent::_GJ_type::const_iterator, double>({currentElement_GJ.size(),1}, currentElement_GJ.begin(), currentElement_GJ.end());
    // HJ
    auto currentElement_HJ = (msg + ctr)->HJ;
    outArray[ctr]["HJ"] = factory.createArray<jackal_op::GradientDescent::_HJ_type::const_iterator, double>({currentElement_HJ.size(),1}, currentElement_HJ.begin(), currentElement_HJ.end());
    // A
    auto currentElement_A = (msg + ctr)->A;
    outArray[ctr]["A"] = factory.createArray<jackal_op::GradientDescent::_A_type::const_iterator, double>({currentElement_A.size(),1}, currentElement_A.begin(), currentElement_A.end());
    // p
    auto currentElement_p = (msg + ctr)->p;
    outArray[ctr]["P"] = factory.createArray<jackal_op::GradientDescent::_p_type::const_iterator, double>({currentElement_p.size(),1}, currentElement_p.begin(), currentElement_p.end());
    // pg
    auto currentElement_pg = (msg + ctr)->pg;
    outArray[ctr]["Pg"] = factory.createArray<jackal_op::GradientDescent::_pg_type::const_iterator, double>({currentElement_pg.size(),1}, currentElement_pg.begin(), currentElement_pg.end());
    // N
    auto currentElement_N = (msg + ctr)->N;
    outArray[ctr]["N"] = factory.createArray<jackal_op::GradientDescent::_N_type::const_iterator, double>({currentElement_N.size(),1}, currentElement_N.begin(), currentElement_N.end());
    }
    return std::move(outArray);
  } 
class JACKAL_OP_EXPORT jackal_op_GradientDescent_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~jackal_op_GradientDescent_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          jackal_op_GradientDescent_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<jackal_op::GradientDescent,jackal_op_msg_GradientDescent_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         jackal_op_GradientDescent_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<jackal_op::GradientDescent,jackal_op::GradientDescent::ConstPtr,jackal_op_msg_GradientDescent_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         jackal_op_GradientDescent_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<jackal_op::GradientDescent,jackal_op_msg_GradientDescent_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(jackal_op_msg_GradientDescent_common, MATLABROSMsgInterface<jackal_op::GradientDescent>)
CLASS_LOADER_REGISTER_CLASS(jackal_op_GradientDescent_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1