#ifndef JACKAL_OP__VISIBILITY_CONTROL_H_
#define JACKAL_OP__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define JACKAL_OP_EXPORT __attribute__ ((dllexport))
    #define JACKAL_OP_IMPORT __attribute__ ((dllimport))
  #else
    #define JACKAL_OP_EXPORT __declspec(dllexport)
    #define JACKAL_OP_IMPORT __declspec(dllimport)
  #endif
  #ifdef JACKAL_OP_BUILDING_LIBRARY
    #define JACKAL_OP_PUBLIC JACKAL_OP_EXPORT
  #else
    #define JACKAL_OP_PUBLIC JACKAL_OP_IMPORT
  #endif
  #define JACKAL_OP_PUBLIC_TYPE JACKAL_OP_PUBLIC
  #define JACKAL_OP_LOCAL
#else
  #define JACKAL_OP_EXPORT __attribute__ ((visibility("default")))
  #define JACKAL_OP_IMPORT
  #if __GNUC__ >= 4
    #define JACKAL_OP_PUBLIC __attribute__ ((visibility("default")))
    #define JACKAL_OP_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define JACKAL_OP_PUBLIC
    #define JACKAL_OP_LOCAL
  #endif
  #define JACKAL_OP_PUBLIC_TYPE
#endif
#endif  // JACKAL_OP__VISIBILITY_CONTROL_H_
// Generated 05-Jul-2023 17:03:01
// Copyright 2019-2020 The MathWorks, Inc.
