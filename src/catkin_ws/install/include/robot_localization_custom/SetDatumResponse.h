// Generated by gencpp from file robot_localization_custom/SetDatumResponse.msg
// DO NOT EDIT!


#ifndef ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETDATUMRESPONSE_H
#define ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETDATUMRESPONSE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace robot_localization_custom
{
template <class ContainerAllocator>
struct SetDatumResponse_
{
  typedef SetDatumResponse_<ContainerAllocator> Type;

  SetDatumResponse_()
    {
    }
  SetDatumResponse_(const ContainerAllocator& _alloc)
    {
  (void)_alloc;
    }







  typedef boost::shared_ptr< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> const> ConstPtr;

}; // struct SetDatumResponse_

typedef ::robot_localization_custom::SetDatumResponse_<std::allocator<void> > SetDatumResponse;

typedef boost::shared_ptr< ::robot_localization_custom::SetDatumResponse > SetDatumResponsePtr;
typedef boost::shared_ptr< ::robot_localization_custom::SetDatumResponse const> SetDatumResponseConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >::stream(s, "", v);
return s;
}


} // namespace robot_localization_custom

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "d41d8cd98f00b204e9800998ecf8427e";
  }

  static const char* value(const ::robot_localization_custom::SetDatumResponse_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xd41d8cd98f00b204ULL;
  static const uint64_t static_value2 = 0xe9800998ecf8427eULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_localization_custom/SetDatumResponse";
  }

  static const char* value(const ::robot_localization_custom::SetDatumResponse_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
{
  static const char* value()
  {
    return "\n"
;
  }

  static const char* value(const ::robot_localization_custom::SetDatumResponse_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream&, T)
    {}

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetDatumResponse_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_localization_custom::SetDatumResponse_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream&, const std::string&, const ::robot_localization_custom::SetDatumResponse_<ContainerAllocator>&)
  {}
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETDATUMRESPONSE_H