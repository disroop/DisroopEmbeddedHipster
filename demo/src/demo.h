#pragma once

#ifdef WIN32
  #define demo_EXPORT __declspec(dllexport)
#else
  #define demo_EXPORT
#endif

demo_EXPORT void demo();
