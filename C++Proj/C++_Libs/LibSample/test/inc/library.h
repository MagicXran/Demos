#ifndef LOGLIB_H
#define LOGLIB_H

#ifdef _WIN32
#ifdef LOGLIB_EXPORTS
#define LOGLIB_API __declspec(dllexport)
#else
#define LOGLIB_API __declspec(dllimport)
#endif
#else
#define LOGLIB_API
#endif

LOGLIB_API void  hello();

#endif



