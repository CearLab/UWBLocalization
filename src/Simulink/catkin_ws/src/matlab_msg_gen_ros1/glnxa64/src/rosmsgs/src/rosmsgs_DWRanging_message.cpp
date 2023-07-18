// Copyright 2019-2021 The MathWorks, Inc.
// Common copy functions for rosmsgs/DWRanging
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
#include "rosmsgs/DWRanging.h"
#include "visibility_control.h"
#include "MATLABROSMsgInterface.hpp"
#include "ROSPubSubTemplates.hpp"
class ROSMSGS_EXPORT rosmsgs_msg_DWRanging_common : public MATLABROSMsgInterface<rosmsgs::DWRanging> {
  public:
    virtual ~rosmsgs_msg_DWRanging_common(){}
    virtual void copy_from_struct(rosmsgs::DWRanging* msg, const matlab::data::Struct& arr, MultiLibLoader loader); 
    //----------------------------------------------------------------------------
    virtual MDArray_T get_arr(MDFactory_T& factory, const rosmsgs::DWRanging* msg, MultiLibLoader loader, size_t size = 1);
};
  void rosmsgs_msg_DWRanging_common::copy_from_struct(rosmsgs::DWRanging* msg, const matlab::data::Struct& arr,
               MultiLibLoader loader) {
    try {
        //anchorId
        const matlab::data::TypedArray<int16_t> anchorId_arr = arr["AnchorId"];
        msg->anchorId = anchorId_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'AnchorId' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'AnchorId' is wrong type; expected a int16.");
    }
    try {
        //tagId
        const matlab::data::TypedArray<int16_t> tagId_arr = arr["TagId"];
        msg->tagId = tagId_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'TagId' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'TagId' is wrong type; expected a int16.");
    }
    try {
        //range
        const matlab::data::TypedArray<int32_t> range_arr = arr["Range"];
        msg->range = range_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Range' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Range' is wrong type; expected a int32.");
    }
    try {
        //rawrange
        const matlab::data::TypedArray<int32_t> rawrange_arr = arr["Rawrange"];
        msg->rawrange = rawrange_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Rawrange' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Rawrange' is wrong type; expected a int32.");
    }
    try {
        //seq
        const matlab::data::TypedArray<int32_t> seq_arr = arr["Seq"];
        msg->seq = seq_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Seq' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Seq' is wrong type; expected a int32.");
    }
    try {
        //maxNoise
        const matlab::data::TypedArray<int32_t> maxNoise_arr = arr["MaxNoise"];
        msg->maxNoise = maxNoise_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'MaxNoise' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'MaxNoise' is wrong type; expected a int32.");
    }
    try {
        //stdNoise
        const matlab::data::TypedArray<int32_t> stdNoise_arr = arr["StdNoise"];
        msg->stdNoise = stdNoise_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'StdNoise' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'StdNoise' is wrong type; expected a int32.");
    }
    try {
        //firstPathAmp1
        const matlab::data::TypedArray<int32_t> firstPathAmp1_arr = arr["FirstPathAmp1"];
        msg->firstPathAmp1 = firstPathAmp1_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'FirstPathAmp1' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'FirstPathAmp1' is wrong type; expected a int32.");
    }
    try {
        //firstPathAmp2
        const matlab::data::TypedArray<int32_t> firstPathAmp2_arr = arr["FirstPathAmp2"];
        msg->firstPathAmp2 = firstPathAmp2_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'FirstPathAmp2' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'FirstPathAmp2' is wrong type; expected a int32.");
    }
    try {
        //firstPathAmp3
        const matlab::data::TypedArray<int32_t> firstPathAmp3_arr = arr["FirstPathAmp3"];
        msg->firstPathAmp3 = firstPathAmp3_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'FirstPathAmp3' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'FirstPathAmp3' is wrong type; expected a int32.");
    }
    try {
        //maxGrowthCIR
        const matlab::data::TypedArray<int32_t> maxGrowthCIR_arr = arr["MaxGrowthCIR"];
        msg->maxGrowthCIR = maxGrowthCIR_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'MaxGrowthCIR' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'MaxGrowthCIR' is wrong type; expected a int32.");
    }
    try {
        //rxPreamCount
        const matlab::data::TypedArray<int32_t> rxPreamCount_arr = arr["RxPreamCount"];
        msg->rxPreamCount = rxPreamCount_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'RxPreamCount' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'RxPreamCount' is wrong type; expected a int32.");
    }
    try {
        //firstPath
        const matlab::data::TypedArray<int32_t> firstPath_arr = arr["FirstPath"];
        msg->firstPath = firstPath_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'FirstPath' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'FirstPath' is wrong type; expected a int32.");
    }
    try {
        //channel
        const matlab::data::TypedArray<double> channel_arr = arr["Channel"];
        msg->channel = channel_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Channel' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Channel' is wrong type; expected a double.");
    }
    try {
        //prf
        const matlab::data::TypedArray<int32_t> prf_arr = arr["Prf"];
        msg->prf = prf_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Prf' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Prf' is wrong type; expected a int32.");
    }
    try {
        //datarate
        const matlab::data::TypedArray<double> datarate_arr = arr["Datarate"];
        msg->datarate = datarate_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'Datarate' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'Datarate' is wrong type; expected a double.");
    }
    try {
        //preambleLength
        const matlab::data::TypedArray<int32_t> preambleLength_arr = arr["PreambleLength"];
        msg->preambleLength = preambleLength_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'PreambleLength' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'PreambleLength' is wrong type; expected a int32.");
    }
    try {
        //pacSize
        const matlab::data::TypedArray<int32_t> pacSize_arr = arr["PacSize"];
        msg->pacSize = pacSize_arr[0];
    } catch (matlab::data::InvalidFieldNameException&) {
        throw std::invalid_argument("Field 'PacSize' is missing.");
    } catch (matlab::Exception&) {
        throw std::invalid_argument("Field 'PacSize' is wrong type; expected a int32.");
    }
  }
  //----------------------------------------------------------------------------
  MDArray_T rosmsgs_msg_DWRanging_common::get_arr(MDFactory_T& factory, const rosmsgs::DWRanging* msg,
       MultiLibLoader loader, size_t size) {
    auto outArray = factory.createStructArray({size,1},{"MessageType","AnchorId","TagId","Range","Rawrange","Seq","MaxNoise","StdNoise","FirstPathAmp1","FirstPathAmp2","FirstPathAmp3","MaxGrowthCIR","RxPreamCount","FirstPath","Channel","Prf","Datarate","PreambleLength","PacSize"});
    for(size_t ctr = 0; ctr < size; ctr++){
    outArray[ctr]["MessageType"] = factory.createCharArray("rosmsgs/DWRanging");
    // anchorId
    auto currentElement_anchorId = (msg + ctr)->anchorId;
    outArray[ctr]["AnchorId"] = factory.createScalar(currentElement_anchorId);
    // tagId
    auto currentElement_tagId = (msg + ctr)->tagId;
    outArray[ctr]["TagId"] = factory.createScalar(currentElement_tagId);
    // range
    auto currentElement_range = (msg + ctr)->range;
    outArray[ctr]["Range"] = factory.createScalar(currentElement_range);
    // rawrange
    auto currentElement_rawrange = (msg + ctr)->rawrange;
    outArray[ctr]["Rawrange"] = factory.createScalar(currentElement_rawrange);
    // seq
    auto currentElement_seq = (msg + ctr)->seq;
    outArray[ctr]["Seq"] = factory.createScalar(currentElement_seq);
    // maxNoise
    auto currentElement_maxNoise = (msg + ctr)->maxNoise;
    outArray[ctr]["MaxNoise"] = factory.createScalar(currentElement_maxNoise);
    // stdNoise
    auto currentElement_stdNoise = (msg + ctr)->stdNoise;
    outArray[ctr]["StdNoise"] = factory.createScalar(currentElement_stdNoise);
    // firstPathAmp1
    auto currentElement_firstPathAmp1 = (msg + ctr)->firstPathAmp1;
    outArray[ctr]["FirstPathAmp1"] = factory.createScalar(currentElement_firstPathAmp1);
    // firstPathAmp2
    auto currentElement_firstPathAmp2 = (msg + ctr)->firstPathAmp2;
    outArray[ctr]["FirstPathAmp2"] = factory.createScalar(currentElement_firstPathAmp2);
    // firstPathAmp3
    auto currentElement_firstPathAmp3 = (msg + ctr)->firstPathAmp3;
    outArray[ctr]["FirstPathAmp3"] = factory.createScalar(currentElement_firstPathAmp3);
    // maxGrowthCIR
    auto currentElement_maxGrowthCIR = (msg + ctr)->maxGrowthCIR;
    outArray[ctr]["MaxGrowthCIR"] = factory.createScalar(currentElement_maxGrowthCIR);
    // rxPreamCount
    auto currentElement_rxPreamCount = (msg + ctr)->rxPreamCount;
    outArray[ctr]["RxPreamCount"] = factory.createScalar(currentElement_rxPreamCount);
    // firstPath
    auto currentElement_firstPath = (msg + ctr)->firstPath;
    outArray[ctr]["FirstPath"] = factory.createScalar(currentElement_firstPath);
    // channel
    auto currentElement_channel = (msg + ctr)->channel;
    outArray[ctr]["Channel"] = factory.createScalar(currentElement_channel);
    // prf
    auto currentElement_prf = (msg + ctr)->prf;
    outArray[ctr]["Prf"] = factory.createScalar(currentElement_prf);
    // datarate
    auto currentElement_datarate = (msg + ctr)->datarate;
    outArray[ctr]["Datarate"] = factory.createScalar(currentElement_datarate);
    // preambleLength
    auto currentElement_preambleLength = (msg + ctr)->preambleLength;
    outArray[ctr]["PreambleLength"] = factory.createScalar(currentElement_preambleLength);
    // pacSize
    auto currentElement_pacSize = (msg + ctr)->pacSize;
    outArray[ctr]["PacSize"] = factory.createScalar(currentElement_pacSize);
    }
    return std::move(outArray);
  } 
class ROSMSGS_EXPORT rosmsgs_DWRanging_message : public ROSMsgElementInterfaceFactory {
  public:
    virtual ~rosmsgs_DWRanging_message(){}
    virtual std::shared_ptr<MATLABPublisherInterface> generatePublisherInterface(ElementType type);
    virtual std::shared_ptr<MATLABSubscriberInterface> generateSubscriberInterface(ElementType type);
    virtual std::shared_ptr<MATLABRosbagWriterInterface> generateRosbagWriterInterface(ElementType type);
};  
  std::shared_ptr<MATLABPublisherInterface> 
          rosmsgs_DWRanging_message::generatePublisherInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSPublisherImpl<rosmsgs::DWRanging,rosmsgs_msg_DWRanging_common>>();
  }
  std::shared_ptr<MATLABSubscriberInterface> 
         rosmsgs_DWRanging_message::generateSubscriberInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSSubscriberImpl<rosmsgs::DWRanging,rosmsgs::DWRanging::ConstPtr,rosmsgs_msg_DWRanging_common>>();
  }
#include "ROSbagTemplates.hpp" 
  std::shared_ptr<MATLABRosbagWriterInterface>
         rosmsgs_DWRanging_message::generateRosbagWriterInterface(ElementType type){
    if(type != eMessage){
        throw std::invalid_argument("Wrong input, Expected eMessage");
    }
    return std::make_shared<ROSBagWriterImpl<rosmsgs::DWRanging,rosmsgs_msg_DWRanging_common>>();
  }
#include "register_macro.hpp"
// Register the component with class_loader.
// This acts as a sort of entry point, allowing the component to be discoverable when its library
// is being loaded into a running process.
CLASS_LOADER_REGISTER_CLASS(rosmsgs_msg_DWRanging_common, MATLABROSMsgInterface<rosmsgs::DWRanging>)
CLASS_LOADER_REGISTER_CLASS(rosmsgs_DWRanging_message, ROSMsgElementInterfaceFactory)
#ifdef _MSC_VER
#pragma warning(pop)
#else
#pragma GCC diagnostic pop
#endif //_MSC_VER
//gen-1