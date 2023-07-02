// Generated by gencpp from file robot_localization_custom/SetUTMZoneRequest.msg
// DO NOT EDIT!


#ifndef ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETUTMZONEREQUEST_H
#define ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETUTMZONEREQUEST_H


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
struct SetUTMZoneRequest_
{
  typedef SetUTMZoneRequest_<ContainerAllocator> Type;

  SetUTMZoneRequest_()
    : utm_zone()  {
    }
  SetUTMZoneRequest_(const ContainerAllocator& _alloc)
    : utm_zone(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _utm_zone_type;
  _utm_zone_type utm_zone;





  typedef boost::shared_ptr< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> const> ConstPtr;

}; // struct SetUTMZoneRequest_

typedef ::robot_localization_custom::SetUTMZoneRequest_<std::allocator<void> > SetUTMZoneRequest;

typedef boost::shared_ptr< ::robot_localization_custom::SetUTMZoneRequest > SetUTMZoneRequestPtr;
typedef boost::shared_ptr< ::robot_localization_custom::SetUTMZoneRequest const> SetUTMZoneRequestConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator1> & lhs, const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator2> & rhs)
{
  return lhs.utm_zone == rhs.utm_zone;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator1> & lhs, const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace robot_localization_custom

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsFixedSize< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "893fd74d45efde020666acda18d3cccc";
  }

  static const char* value(const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x893fd74d45efde02ULL;
  static const uint64_t static_value2 = 0x0666acda18d3ccccULL;
};

template<class ContainerAllocator>
struct DataType< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "robot_localization_custom/SetUTMZoneRequest";
  }

  static const char* value(const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
{
  static const char* value()
  {
    return "# Set an UTM zone navsat_transform should stick to.\n"
"# Example: 31U\n"
"string utm_zone\n"
;
  }

  static const char* value(const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.utm_zone);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct SetUTMZoneRequest_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::robot_localization_custom::SetUTMZoneRequest_<ContainerAllocator>& v)
  {
    s << indent << "utm_zone: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.utm_zone);
  }
};

} // namespace message_operations
} // namespace ros

#endif // ROBOT_LOCALIZATION_CUSTOM_MESSAGE_SETUTMZONEREQUEST_H