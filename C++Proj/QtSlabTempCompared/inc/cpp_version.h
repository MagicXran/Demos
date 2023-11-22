#ifndef CPP_HPP
#define CPP_HPP

#ifdef _WIN32 //(Windows 64bit and 32 bit is common)

#ifdef _WIN64 //define somethings for windows 64 bit

#else //define somethings for windows 32 bit

#endif // _WIN64

#endif // _WIN32 //(Windows 64bit and 32 bit is common)


#if defined(__clang__) || defined(__GNUC__)

#define CPP_STANDARD __cplusplus

#elif defined(_MSC_VER)

#define CPP_STANDARD _MSVC_LANG

#endif

#if CPP_STANDARD >= 199711L
#define CPP_03_STANDARD 1
#endif
#if CPP_STANDARD >= 201103L
#define CPP_11_STANDARD 1
#endif
#if CPP_STANDARD >= 201402L
#define CPP_14_STANDARD 1
#endif
#if CPP_STANDARD >= 201703L
#define CPP_17_STANDARD 1
#endif

#endif

