/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright (c) 2006-2015 The Open Group                                    */
/*                                                                           */
/* Permission is hereby granted, free of charge, to any person obtaining a   */
/* copy of this software (the "Software"), to deal in the Software without   */
/* restriction, including without limitation the rights to use, copy,        */
/* modify, merge, publish, distribute, sublicense, and/or sell copies of     */
/* the Software, and to permit persons to whom the Software is furnished     */
/* to do so, subject to the following conditions:                            */
/*                                                                           */
/* The above copyright notice and this permission notice shall be included   */
/* in all copies or substantial portions of the Software.                    */
/*                                                                           */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS   */
/* OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF                */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.    */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY      */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT */
/* OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR  */
/* THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                */
/*                                                                           */
/* ------------------------------------------------------------------------- */

/**
 * @file cmpios.h
 * @brief Defines OS-specific symbols for threading structures, etc.;
 * MIs do not need to include this header because it is included by `cmpift.h`.
 *
 * This header file belongs to the Technical Standard: Systems Management:
 * Common Manageability Programming Interface (CMPI) Issue 2 Version 1.
 *
 * This header file is provided as a convenience only. In the case of any
 * discrepancy between the header file and the Technical Standard
 * (incorporating any subsequent Technical Corrigenda), the Technical Standard
 * shall be definitive.
 */

#ifndef _CMPIOS_H_
#define _CMPIOS_H_

#include "cmpipl.h"

#include <stdlib.h>          // To get size_t

/**
 * @addtogroup sym-thread-type
 * @{
 */

/**
 * @brief Type for the handle of a thread.
 */
#define CMPI_THREAD_TYPE        void*

/**
 * @}
 * @addtogroup sym-thread-return
 * @{
 */

/**
 * @brief Type for the return value of a thread function.
 *
 * @platformspecific The definition of the
 *     @ref sym-thread-return "CMPI_THREAD_RETURN"
 *     symbol depends on the platform (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  define CMPI_THREAD_RETURN      unsigned
#else // all other platforms
#  define CMPI_THREAD_RETURN      void*
#endif

/**
 * @}
 * @addtogroup sym-thread-cdecl
 * @{
 */

/**
 * @brief Modifier defining the calling convention for a thread function.
 *
 * @platformspecific The definition of the
 *     @ref sym-thread-cdecl "CMPI_THREAD_CDECL"
 *     symbol depends on the platform (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  define CMPI_THREAD_CDECL    __stdcall
#elif defined(CMPI_PLATFORM_ZOS_ZSERIES_IBM)
#  ifdef __cplusplus
#    define CMPI_THREAD_CDECL __cdecl
#  else
#    define CMPI_THREAD_CDECL
#  endif
#else // all other platforms
#  define CMPI_THREAD_CDECL
#endif

/**
 * @}
 * @defgroup sym-thread-key-type CMPI_THREAD_KEY_TYPE
 * @{
 */

/**
 * @brief Type for a thread key of a thread.
 *
 * @platformspecific The definition of the
 *     @ref sym-thread-key-type "CMPI_THREAD_KEY_TYPE"
 *     symbol depends on the platform (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  define CMPI_THREAD_KEY_TYPE unsigned int
#elif defined(CMPI_PLATFORM_ZOS_ZSERIES_IBM)
#  include <pthread.h>
#  define CMPI_THREAD_KEY_TYPE pthread_key_t
#else // all other platforms
#  define CMPI_THREAD_KEY_TYPE unsigned int
#endif

/**
 * @}
 * @addtogroup sym-mutex-type
 * @{
 */

/**
 * @brief Type for the handle of a mutex.
 */
#define CMPI_MUTEX_TYPE         void*

/**
 * @}
 * @addtogroup sym-cond-type
 * @{
 */

/**
 * @brief Type for the handle of a condition.
 */
#define CMPI_COND_TYPE          void*

/**
 * @}
 */

#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  ifndef HAVE_STRUCT_TIMESPEC
#    define HAVE_STRUCT_TIMESPEC
struct timespec {
    long tv_sec;
    long tv_nsec;
};
#  endif // HAVE_STRUCT_TIMESPEC
#endif

/**
 * @addtogroup sym-export
 * @{
 */

/**
 * @brief Modifier on non-CMPI functions or data that are to be exported
 *     from MI load libraries
 *
 * The compile mode (C vs. C++) needs to match between the exporter and the
 * importer (see @ref sym-import "CMPI_IMPORT").
 *
 * CMPI related data or functions do not need to be exported by MBs or MIs
 * using this modifier; however, it can be used for non-CMPI-related
 * purposes.
 *
 * @platformspecific The definition of CMPI_EXPORT depends on the platform
 *     (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  define CMPI_EXPORT __declspec(dllexport)
#elif defined(CMPI_PLATFORM_LINUX_GENERIC_GNU) && (__GNUC__ >= 4)
#  define CMPI_EXPORT __attribute__((visibility("default")))
#else // all other platforms
#  define CMPI_EXPORT
#endif

/**
 * @}
 * @addtogroup sym-import
 * @{
 */

/**
 * @brief Modifier on non-CMPI functions or data that are to be imported
 *     into MI load libraries
 *
 * The compile mode (C vs. C++) needs to match between the exporter and the
 * importer (see @ref sym-export "CMPI_EXPORT").
 *
 * CMPI related data or functions do not need to be exported by MBs or MIs
 * using this modifier; however, it can be used for non-CMPI-related
 * purposes.
 *
 * @platformspecific The definition of CMPI_IMPORT depends on the platform
 *     (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#if defined(CMPI_PLATFORM_WIN32_IX86_MSVC)
#  define CMPI_IMPORT __declspec(dllimport)
#elif defined(CMPI_PLATFORM_LINUX_GENERIC_GNU) && (__GNUC__ >= 4)
#  define CMPI_IMPORT __attribute__((visibility("default")))
#else // all other platforms
#  define CMPI_IMPORT
#endif

/**
 * @}
 * @addtogroup sym-extern-c
 * @{
 */

/**
 * @brief Modifier for specifying the linkage of CMPI functions
 *     that are to be exported from MI load libraries
 *
 * This modifier needs to be specified on the MI factory functions provided
 * by MI load libraries.  MB functions and other MI functions do not need to
 * specifiy this modifier.
 *
 * @cxxspecific The definition of CMPI_EXTERN_C depends on whether the
 *     headers are compiled for C or for C++.
 *     For details, examine the source code of `cmpios.h`.
 *
 * @platformspecific The definition of CMPI_EXTERN_C depends on
 *     @ref sym-export "CMPI_EXPORT", which in turn depends on the platform
 *     (see @ref sym-platform).
 *     For details, examine the source code of `cmpios.h`.
 */
#ifdef __cplusplus
#  define CMPI_EXTERN_C extern "C" CMPI_EXPORT
#else
#  define CMPI_EXTERN_C CMPI_EXPORT
#endif

/**
 * @}
 */

#endif // _CMPIOS_H_
