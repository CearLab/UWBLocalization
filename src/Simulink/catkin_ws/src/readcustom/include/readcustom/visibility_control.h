#ifndef READCUSTOM__VISIBILITY_CONTROL_H_
#define READCUSTOM__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define READCUSTOM_EXPORT __attribute__ ((dllexport))
    #define READCUSTOM_IMPORT __attribute__ ((dllimport))
  #else
    #define READCUSTOM_EXPORT __declspec(dllexport)
    #define READCUSTOM_IMPORT __declspec(dllimport)
  #endif
  #ifdef READCUSTOM_BUILDING_LIBRARY
    #define READCUSTOM_PUBLIC READCUSTOM_EXPORT
  #else
    #define READCUSTOM_PUBLIC READCUSTOM_IMPORT
  #endif
  #define READCUSTOM_PUBLIC_TYPE READCUSTOM_PUBLIC
  #define READCUSTOM_LOCAL
#else
  #define READCUSTOM_EXPORT __attribute__ ((visibility("default")))
  #define READCUSTOM_IMPORT
  #if __GNUC__ >= 4
    #define READCUSTOM_PUBLIC __attribute__ ((visibility("default")))
    #define READCUSTOM_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define READCUSTOM_PUBLIC
    #define READCUSTOM_LOCAL
  #endif
  #define READCUSTOM_PUBLIC_TYPE
#endif
#endif  // READCUSTOM__VISIBILITY_CONTROL_H_
// Generated 04-Jul-2023 22:53:50
// Copyright 2019-2020 The MathWorks, Inc.
