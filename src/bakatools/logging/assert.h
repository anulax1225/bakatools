#pragma once

/*! \file assert.h
This file contains the assert macros. CORE macros musn't be used by the application.
*/

#include "log.h"
#include <bakatools/string/format.h>

#define BK_STATIC_DEBUGBREAK() exit(1)


#define BK_STATIC_CORE_VAMSG_ASSERT(check, msg, ...) if(!(check)) { BK_STATIC_CORE_ERROR(Tools::format("Assertion [%s] failed at %s:%d\n\tError : %s", BK_STRINGIFY(check), __FILE__, __LINE__, msg), __VA_ARGS__); BK_STATIC_DEBUGBREAK(); }
#define BK_STATIC_CORE_MSG_ASSERT(check, msg) if(!(check)) { BK_STATIC_CORE_ERROR("Assertion [{0}] failed at {1}:{2}\n\tError : {3}", BK_STRINGIFY(check), __FILE__, __LINE__, msg); BK_STATIC_DEBUGBREAK(); }
#define BK_STATIC_CORE_ASSERT(check) if(!(check)) { BK_STATIC_CORE_ERROR("Assertion [{0}] failed at {1}:{2}", BK_STRINGIFY(check), __FILE__, __LINE__); BK_STATIC_DEBUGBREAK(); }

#define BK_STATIC_VAMSG_ASSERT(check, msg, ...) if(!(check)) { BK_STATIC_ERROR(Bk::Tools::format("Assertion [%s] failed at %s:%d\n\tError : %s", BK_STRINGIFY(check), __FILE__, __LINE__, msg), __VA_ARGS__); BK_STATIC_DEBUGBREAK(); }
#define BK_STATIC_MSG_ASSERT(check, msg) if(!(check)) { BK_STATIC_ERROR("Assertion [{0}] failed at {1}:{2}\n\tError : {3}", BK_STRINGIFY(check), __FILE__, __LINE__, msg); BK_STATIC_DEBUGBREAK(); }
#define BK_STATIC_ASSERT(check) if(!(check)) { BK_STATIC_ERROR("Assertion [{0}] failed at {1}:{2}", BK_STRINGIFY(check), __FILE__, __LINE__); BK_STATIC_DEBUGBREAK(); }

#ifdef BK_DEBUG
    #if defined(BK_PLATFORM_WINDOWS)
        #define BK_DEBUGBREAK() __debugbreak()
    #elif defined(BK_PLATFORM_LINUX)
        #include <signal.h>
        #define BK_DEBUGBREAK() raise(SIGTRAP)
    #else 
        #error "Plaform doesn't support debug yet"
    #endif
    /*! \def BK_CORE_VAMSG_ASSERT(check, msg, ...)
    Assertes a condition, and throw an error with the formatted message as description
    @param check : Condionne to assert
    @param msg : format string error message
    @param ... : variable arguments to put in the string
    */
    #define BK_CORE_VAMSG_ASSERT(check, msg, ...) if(!(check)) { BK_CORE_ERROR(Tools::format("Assertion [%s] failed at %s:%d\n\tError : %s", BK_STRINGIFY(check), __FILE__, __LINE__, msg), __VA_ARGS__); BK_DEBUGBREAK(); }
    #define BK_CORE_MSG_ASSERT(check, msg) if(!(check)) { BK_CORE_ERROR("Assertion [{0}] failed at {1}:{2}\n\tError : {3}", BK_STRINGIFY(check), __FILE__, __LINE__, msg); BK_DEBUGBREAK(); }
    #define BK_CORE_ASSERT(check) if(!(check)) { BK_CORE_ERROR("Assertion [{0}] failed at {1}:{2}", BK_STRINGIFY(check), __FILE__, __LINE__); BK_DEBUGBREAK(); }

    #define BK_VAMSG_ASSERT(check, msg, ...) if(!(check)) { BK_ERROR(Bk::Tools::format("Assertion [%s] failed at %s:%d\n\tError : %s", BK_STRINGIFY(check), __FILE__, __LINE__, msg), __VA_ARGS__); BK_DEBUGBREAK(); }
    #define BK_MSG_ASSERT(check, msg) if(!(check)) { BK_ERROR("Assertion [{0}] failed at {1}:{2}\n\tError : {3}", BK_STRINGIFY(check), __FILE__, __LINE__, msg); BK_DEBUGBREAK(); }
    #define BK_ASSERT(check) if(!(check)) { BK_ERROR("Assertion [{0}] failed at {1}:{2}", BK_STRINGIFY(check), __FILE__, __LINE__); BK_DEBUGBREAK(); }
#else 
    #define BK_DEBUGBREAK()
    #define BK_CORE_VAMSG_ASSERT(check, msg, ...) 
    #define BK_CORE_MSG_ASSERT(check, msg)
    #define BK_CORE_ASSERT(check)

    #define BK_VAMSG_ASSERT(check, msg, ...) 
    #define BK_MSG_ASSERT(check, msg) 
    #define BK_ASSERT(check)
#endif