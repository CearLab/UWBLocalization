// Generated by gencpp from file jackal_op/MeshUWB.msg
// DO NOT EDIT!


#ifndef JACKAL_OP_MESSAGE_MESHUWB_H
#define JACKAL_OP_MESSAGE_MESHUWB_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>

namespace jackal_op
{
template <class ContainerAllocator>
struct MeshUWB_
{
  typedef MeshUWB_<ContainerAllocator> Type;

  MeshUWB_()
    : header()
    , D1()
    , D2()
    , D3()  {
    }
  MeshUWB_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , D1(_alloc)
    , D2(_alloc)
    , D3(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _D1_type;
  _D1_type D1;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _D2_type;
  _D2_type D2;

   typedef std::vector<double, typename ContainerAllocator::template rebind<double>::other >  _D3_type;
  _D3_type D3;





  typedef boost::shared_ptr< ::jackal_op::MeshUWB_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::jackal_op::MeshUWB_<ContainerAllocator> const> ConstPtr;

}; // struct MeshUWB_

typedef ::jackal_op::MeshUWB_<std::allocator<void> > MeshUWB;

typedef boost::shared_ptr< ::jackal_op::MeshUWB > MeshUWBPtr;
typedef boost::shared_ptr< ::jackal_op::MeshUWB const> MeshUWBConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::jackal_op::MeshUWB_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::jackal_op::MeshUWB_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::jackal_op::MeshUWB_<ContainerAllocator1> & lhs, const ::jackal_op::MeshUWB_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.D1 == rhs.D1 &&
    lhs.D2 == rhs.D2 &&
    lhs.D3 == rhs.D3;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::jackal_op::MeshUWB_<ContainerAllocator1> & lhs, const ::jackal_op::MeshUWB_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace jackal_op

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::jackal_op::MeshUWB_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::jackal_op::MeshUWB_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jackal_op::MeshUWB_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::jackal_op::MeshUWB_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jackal_op::MeshUWB_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::jackal_op::MeshUWB_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::jackal_op::MeshUWB_<ContainerAllocator> >
{
  static const char* value()
  {
    return "5b30149a17ef9828ca679ce567fad6c8";
  }

  static const char* value(const ::jackal_op::MeshUWB_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x5b30149a17ef9828ULL;
  static const uint64_t static_value2 = 0xca679ce567fad6c8ULL;
};

template<class ContainerAllocator>
struct DataType< ::jackal_op::MeshUWB_<ContainerAllocator> >
{
  static const char* value()
  {
    return "jackal_op/MeshUWB";
  }

  static const char* value(const ::jackal_op::MeshUWB_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::jackal_op::MeshUWB_<ContainerAllocator> >
{
  static const char* value()
  {
    return "Header header\n"
"float64[] D1\n"
"float64[] D2\n"
"float64[] D3\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
;
  }

  static const char* value(const ::jackal_op::MeshUWB_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::jackal_op::MeshUWB_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.D1);
      stream.next(m.D2);
      stream.next(m.D3);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct MeshUWB_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::jackal_op::MeshUWB_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::jackal_op::MeshUWB_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "D1[]" << std::endl;
    for (size_t i = 0; i < v.D1.size(); ++i)
    {
      s << indent << "  D1[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.D1[i]);
    }
    s << indent << "D2[]" << std::endl;
    for (size_t i = 0; i < v.D2.size(); ++i)
    {
      s << indent << "  D2[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.D2[i]);
    }
    s << indent << "D3[]" << std::endl;
    for (size_t i = 0; i < v.D3.size(); ++i)
    {
      s << indent << "  D3[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.D3[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // JACKAL_OP_MESSAGE_MESHUWB_H
