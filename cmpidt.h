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
 * @file cmpidt.h
 * @brief Defines CMPI data types;
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

#ifndef _CMPIDT_H_
#define _CMPIDT_H_

#include "cmpipl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sym-version-nnn
 * @{
 */

#define CMPIVersion100 100  ///< CMPI 1.0.0
#define CMPIVersion200 200  ///< CMPI 2.0.0
#define CMPIVersion210 210  ///< CMPI 2.1.0

/**
 * @}
 * @addtogroup sym-current-version
 * @{
 */

/**
 * @brief The current CMPI version.
 *
 * The current CMPI version is the version described by this version of
 * the online documentation.
 *
 * At the same time, this is the highest CMPI version supported by the
 * corresponding CMPI header files. See @ref sym-version "CMPI_VERSION"
 * for implementing a lower CMPI version.
 */
#define CMPICurrentVersion CMPIVersion210

/**
 * @}
 * @addtogroup sym-version
 * @{
 */

/**
 * @brief The CMPI version that is implemented.
 *
 * This symbol is only set in this header file if not set outside of this
 * header file. Its default value is @ref sym-current-version
 * "CMPICurrentVersion", and it can be overridden outside of the CMPI
 * header files if a lower CMPI version is intended to be implemented.
 */
#ifndef CMPI_VERSION
#  define CMPI_VERSION CMPICurrentVersion
#endif

/**
 * @}
 * @addtogroup sym-ver-nnn
 * @{
 */

#if (CMPI_VERSION == CMPIVersion210)
#  define CMPI_VER_210 1  ///< Check for features introduced in CMPI 2.1.0
#  define CMPI_VER_200 1  ///< Check for features introduced in CMPI 2.0.0
#  define CMPI_VER_100 1  ///< Check for features introduced in CMPI 1.0.0
#elif (CMPI_VERSION == CMPIVersion200)
#  define CMPI_VER_200 1  ///< Check for features introduced in CMPI 2.0.0
#  define CMPI_VER_100 1  ///< Check for features introduced in CMPI 1.0.0
#elif (CMPI_VERSION == CMPIVersion100)
#  define CMPI_VER_100 1  ///< Check for features introduced in CMPI 1.0.0
#else
#  error Unsupported CMPI version defined in CMPI_VERSION symbol
#endif

/**
 * @}
 * @{
 */

/*
 * Forward declarations of structures and their typedefs.
 */

struct _CMPIBroker;
struct _CMPIBrokerFT;
struct _CMPIBrokerEncFT;
struct _CMPIBrokerExtFT;
#ifdef CMPI_VER_200
struct _CMPIBrokerMemFT;
#endif
typedef struct _CMPIBroker CMPIBroker;
typedef struct _CMPIBrokerFT CMPIBrokerFT;
typedef struct _CMPIBrokerEncFT CMPIBrokerEncFT;
typedef struct _CMPIBrokerExtFT CMPIBrokerExtFT;
#ifdef CMPI_VER_200
typedef struct _CMPIBrokerMemFT CMPIBrokerMemFT;
#endif

struct _CMPIContext;
struct _CMPIResult;
struct _CMPIString;
struct _CMPIArray;
struct _CMPIEnumeration;
struct _CMPIInstance;
struct _CMPIObjectPath;
struct _CMPIArgs;
struct _CMPIDateTime;
struct _CMPISelectExp;
struct _CMPISelectCond;
struct _CMPISubCond;
struct _CMPIPredicate;
#ifdef CMPI_VER_200
struct _CMPIError;
#endif
#ifdef CMPI_VER_210
struct _CMPIPropertyList;
struct _CMPIEnumerationFilter;
#endif
typedef struct _CMPIContext CMPIContext;
typedef struct _CMPIResult CMPIResult;
typedef struct _CMPIString CMPIString;
typedef struct _CMPIArray CMPIArray;
typedef struct _CMPIEnumeration CMPIEnumeration;
typedef struct _CMPIInstance CMPIInstance;
typedef struct _CMPIObjectPath CMPIObjectPath;
typedef struct _CMPIArgs CMPIArgs;
typedef struct _CMPIDateTime CMPIDateTime;
typedef struct _CMPISelectExp CMPISelectExp;
typedef struct _CMPISelectCond CMPISelectCond;
typedef struct _CMPISubCond CMPISubCond;
typedef struct _CMPIPredicate CMPIPredicate;
#ifdef CMPI_VER_200
typedef struct _CMPIError CMPIError;
#endif
#ifdef CMPI_VER_210
typedef struct _CMPIPropertyList CMPIPropertyList;
typedef struct _CMPIEnumerationFilter CMPIEnumerationFilter;
#endif
struct _CMPIContextFT;
struct _CMPIResultFT;
struct _CMPIStringFT;
struct _CMPIArrayFT;
struct _CMPIEnumerationFT;
struct _CMPIInstanceFT;
struct _CMPIObjectPathFT;
struct _CMPIArgsFT;
struct _CMPIDateTimeFT;
struct _CMPISelectExpFT;
struct _CMPISelectCondFT;
struct _CMPISelectCondDocFT;
struct _CMPISelectCondCodFT;
struct _CMPISubCondFT;
struct _CMPIPredicateFT;
#ifdef CMPI_VER_200
struct _CMPIErrorFT;
#endif
#ifdef CMPI_VER_210
struct _CMPIPropertyListFT;
struct _CMPIEnumerationFilterFT;
#endif
typedef struct _CMPIContextFT CMPIContextFT;
typedef struct _CMPIResultFT CMPIResultFT;
typedef struct _CMPIStringFT CMPIStringFT;
typedef struct _CMPIArrayFT CMPIArrayFT;
typedef struct _CMPIEnumerationFT CMPIEnumerationFT;
typedef struct _CMPIInstanceFT CMPIInstanceFT;
typedef struct _CMPIObjectPathFT CMPIObjectPathFT;
typedef struct _CMPIArgsFT CMPIArgsFT;
typedef struct _CMPIDateTimeFT CMPIDateTimeFT;
typedef struct _CMPISelectExpFT CMPISelectExpFT;
typedef struct _CMPISelectCondFT CMPISelectCondFT;
typedef struct _CMPISubCondFT CMPISubCondFT;
typedef struct _CMPIPredicateFT CMPIPredicateFT;
#ifdef CMPI_VER_200
typedef struct _CMPIErrorFT CMPIErrorFT;
#endif
#ifdef CMPI_VER_210
typedef struct _CMPIPropertyListFT CMPIPropertyListFT;
typedef struct _CMPIEnumerationFilterFT CMPIEnumerationFilterFT;
#endif

typedef struct _CMPIInstanceMIFT CMPIInstanceMIFT;
typedef struct _CMPIAssociationMIFT CMPIAssociationMIFT;
typedef struct _CMPIMethodMIFT CMPIMethodMIFT;
typedef struct _CMPIPropertyMIFT CMPIPropertyMIFT;
typedef struct _CMPIIndicationMIFT CMPIIndicationMIFT;

/**
 * @}
 * @addtogroup types-cim-types
 * @{
 *
 * The Typedefs defined in this module cover most CIM data types. The remaining
 * CIM data types are defined as CMPI encapsulated data types, and are:
 *
 * @li CMPIString - CIM data type `string`.
 * @li CMPIDateTime - CIM data type `datetime`.
 * @li CMPIObjectPath - CIM data type `reference`.
 * @li CMPIInstance - for embedded instances.
 */

typedef unsigned char CMPIBoolean;     ///< CIM data type `boolean`.
typedef unsigned short CMPIChar16;     ///< CIM data type `char16`.
typedef unsigned char CMPIUint8;       ///< CIM data type `uint8`.
typedef unsigned short CMPIUint16;     ///< CIM data type `uint16`.
typedef unsigned int CMPIUint32;       ///< CIM data type `uint32`.

/**
 * @brief CIM data type `uint64`.
 *
 * @platformspecific The underlying data type for the
 *     CMPIUint64 type depends on the platform (see @ref sym-platform).
 *     For details, examine the source code of `cmpidt.h`.
 */
#ifndef CMPI_PLATFORM_WIN32_IX86_MSVC
typedef unsigned long long CMPIUint64;
#else
typedef unsigned __int64 CMPIUint64;
#endif

typedef signed char CMPISint8;         ///< CIM data type `sint8`.
typedef short CMPISint16;              ///< CIM data type `sint16`.
typedef signed int CMPISint32;         ///< CIM data type `sint32`.

/**
 * @brief CIM data type `sint64`.
 *
 * @platformspecific The underlying data type for the
 *     CMPISint64 type depends on the platform (see @ref sym-platform).
 *     For details, examine the source code of `cmpidt.h`.
 */
#ifndef CMPI_PLATFORM_WIN32_IX86_MSVC
typedef long long CMPISint64;
#else
typedef __int64 CMPISint64;
#endif

typedef float CMPIReal32;              ///< CIM data type `real32`.
typedef double CMPIReal64;             ///< CIM data type `real64`.

/**
 * @}
 * @addtogroup type-count
 * @{
 */

/**
 * @brief An unsigned integer that specifies a number of elements or position
 *     in a sequential data type.
 *
 * It is used as argument or return type of other functions and specifies e.g.
 * number of items in or index into CMPIArray,
 * number of Bytes in CMPIValuePtr, or
 * number of variable function arguments.
 */
typedef unsigned int CMPICount;

/**
 * @}
 * @addtogroup type-valueptr
 * @{
 */

/**
 * @brief A raw unformatted data area of a specified size.
 *
 * CMPIValuePtr is used for context data only.
 */
typedef struct _CMPIValuePtr {

    /**
     * @brief Pointer to the first Byte of the chunk of data.
     */
    void *ptr;

    /**
     * @brief Size of the chunk of data, in Bytes.
     */
    CMPICount length;

} CMPIValuePtr;

/**
 * @}
 * @addtogroup type-value
 * @{
 */

/**
 * @brief A union that can hold a value of any of the data types defined in
 *     CMPI.
 *
 * CMPIValue is used in CMPIData, but also standalone.
 */
typedef union _CMPIValue {

    CMPIBoolean boolean;    ///< Value of CIM type `boolean` and other booleans
    CMPIChar16 char16;      ///< Value of CIM type `char16`
    CMPIUint8 uint8;        ///< Value of CIM type `uint8`
    CMPIUint16 uint16;      ///< Value of CIM type `uint16`
    CMPIUint32 uint32;      ///< Value of CIM type `uint32`
    CMPIUint64 uint64;      ///< Value of CIM type `uint64`
    CMPISint8 sint8;        ///< Value of CIM type `sint8`
    CMPISint16 sint16;      ///< Value of CIM type `sint16`
    CMPISint32 sint32;      ///< Value of CIM type `sint32`
    CMPISint64 sint64;      ///< Value of CIM type `sint64`
    CMPIReal32 real32;      ///< Value of CIM type `real32`
    CMPIReal64 real64;      ///< Value of CIM type `real64`

    CMPIInstance* inst;     ///< @brief Value of a CMPIInstance object,
                            ///<        used for CIM embedded instances
    CMPIObjectPath* ref;    ///< @brief Value of a CMPIObjectPath object,
                            ///<        used for CIM type `reference`
    CMPIArgs* args;         ///< Value of a CMPIArgs object
    CMPISelectExp* filter;  ///< Value of a CMPISelectExp object
    CMPIEnumeration* Enum;  ///< Value of a CMPIEnumeration object
    CMPIArray* array;       ///< Value of a CMPIArray object
    CMPIString* string;     ///< Value of a CMPIString object
    char* chars;            ///< Value of a C string
    CMPIDateTime* dateTime; ///< Value of a CMPIDateTime object
    CMPIValuePtr dataPtr;   ///< Value of a CMPIValuePtr object

    CMPISint8  Byte;   /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p sint8 instead. */
    CMPISint16 Short;  /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p sint16 instead. */
    CMPISint32 Int;    /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p sint32 instead. */
    CMPISint64 Long;   /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p sint64 instead. */
    CMPIReal32 Float;  /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p real32 instead. */
    CMPIReal64 Double; /**< @brief Deprecated. @deprecated This member is
                            deprecated since CMPI 2.1. Use @p real64 instead. */

} CMPIValue;

/**
 * @}
 * @addtogroup type-type CMPIType
 * @{
 */

/**
 * @brief An integral bitmask type representing a CMPI type.
 *
 * @ref CMPIType is used mainly in CMPI data items (see CMPIData)
 * and is also used standalone in some cases.
 *
 * Test masks for @ref CMPIType are defined @ref def-cmpitype-symbols "here".
 */
typedef unsigned short CMPIType;

/**
 *   @anchor def-cmpitype-symbols
 *   @name Test masks and values for CMPIType
 *   @{
 *
 * These test masks and values are used on @ref CMPIType.
 */

#define CMPI_null         0             ///< No type

/// Test mask for CIM simple types
#define CMPI_SIMPLE       (2)
#define CMPI_boolean      (2+0)         ///< Indicates a CMPIValue.boolean value
#define CMPI_char16       (2+1)         ///< Indicates a CMPIValue.char16 value

/// Test mask for CIM real number types
#define CMPI_REAL         ((2)<<2)
#define CMPI_real32       ((2+0)<<2)    ///< Indicates a CMPIValue.real32 value
#define CMPI_real64       ((2+1)<<2)    ///< Indicates a CMPIValue.real64 value

/// Test mask for CIM unsigned integer types
#define CMPI_UINT         ((8)<<4)
#define CMPI_uint8        ((8+0)<<4)    ///< Indicates a CMPIValue.uint8 value
#define CMPI_uint16       ((8+1)<<4)    ///< Indicates a CMPIValue.uint16 value
#define CMPI_uint32       ((8+2)<<4)    ///< Indicates a CMPIValue.uint32 value
#define CMPI_uint64       ((8+3)<<4)    ///< Indicates a CMPIValue.uint64 value
/// Test mask for CIM signed integer types
#define CMPI_SINT         ((8+4)<<4)
#define CMPI_sint8        ((8+4)<<4)    ///< Indicates a CMPIValue.uint8 value
#define CMPI_sint16       ((8+5)<<4)    ///< Indicates a CMPIValue.uint16 value
#define CMPI_sint32       ((8+6)<<4)    ///< Indicates a CMPIValue.uint32 value
#define CMPI_sint64       ((8+7)<<4)    ///< Indicates a CMPIValue.uint64 value
/// Test mask for CIM integer types
#define CMPI_INTEGER      ((CMPI_UINT|CMPI_SINT))

/// Test mask for CMPI encapsulated data types
#define CMPI_ENC          ((16)<<8)
#define CMPI_instance     ((16+0)<<8)  ///< Indicates a CMPIValue.inst value
#define CMPI_ref          ((16+1)<<8)  ///< Indicates a CMPIValue.ref value
#define CMPI_args         ((16+2)<<8)  ///< Indicates a CMPIValue.args value
#define CMPI_class        ((16+3)<<8)  ///< Not used
#define CMPI_filter       ((16+4)<<8)  ///< Indicates a CMPIValue.filter value
#define CMPI_enumeration  ((16+5)<<8)  ///< Indicates a CMPIValue.Enum value
#define CMPI_string       ((16+6)<<8)  ///< Indicates a CMPIValue.string value
#define CMPI_chars        ((16+7)<<8)  ///< Indicates a CMPIValue.chars value
#define CMPI_dateTime     ((16+8)<<8)  ///< Indicates a CMPIValue.dateTime value
#define CMPI_ptr          ((16+9)<<8)  ///< Indicates a CMPIValue.dataPtr value
#define CMPI_charsptr     ((16+10)<<8) ///< Not used

/// Test mask for arrays
#define CMPI_ARRAY        ((1)<<13)

/// Test mask for array of CIM simple types
#define CMPI_SIMPLEA      (CMPI_ARRAY|CMPI_SIMPLE)
/// Indicates a CMPIValue.array value with @ref CMPIBoolean entries
#define CMPI_booleanA     (CMPI_ARRAY|CMPI_boolean)
/// Indicates a CMPIValue.array value with @ref CMPIChar16 entries
#define CMPI_char16A      (CMPI_ARRAY|CMPI_char16)

/// Test mask for array of CIM real numbers
#define CMPI_REALA        (CMPI_ARRAY|CMPI_REAL)
/// Indicates a CMPIValue.array value with @ref CMPIReal32 entries
#define CMPI_real32A      (CMPI_ARRAY|CMPI_real32)
/// Indicates a CMPIValue.array value with @ref CMPIReal64 entries
#define CMPI_real64A      (CMPI_ARRAY|CMPI_real64)

/// Test mask for array of CIM unsigned integers
#define CMPI_UINTA        (CMPI_ARRAY|CMPI_UINT)
/// Indicates a CMPIValue.array value with @ref CMPIUint8 entries
#define CMPI_uint8A       (CMPI_ARRAY|CMPI_uint8)
/// Indicates a CMPIValue.array value with @ref CMPIUint16 entries
#define CMPI_uint16A      (CMPI_ARRAY|CMPI_uint16)
/// Indicates a CMPIValue.array value with @ref CMPIUint32 entries
#define CMPI_uint32A      (CMPI_ARRAY|CMPI_uint32)
/// Indicates a CMPIValue.array value with @ref CMPIUint64 entries
#define CMPI_uint64A      (CMPI_ARRAY|CMPI_uint64)
/// Test mask for array of CIM signed integers
#define CMPI_SINTA        (CMPI_ARRAY|CMPI_SINT)
/// Indicates a CMPIValue.array value with @ref CMPISint8 entries
#define CMPI_sint8A       (CMPI_ARRAY|CMPI_sint8)
/// Indicates a CMPIValue.array value with @ref CMPISint16 entries
#define CMPI_sint16A      (CMPI_ARRAY|CMPI_sint16)
/// Indicates a CMPIValue.array value with @ref CMPISint32 entries
#define CMPI_sint32A      (CMPI_ARRAY|CMPI_sint32)
/// Indicates a CMPIValue.array value with @ref CMPISint64 entries
#define CMPI_sint64A      (CMPI_ARRAY|CMPI_sint64)
/// Test mask for array of CIM integers
#define CMPI_INTEGERA     (CMPI_ARRAY|CMPI_INTEGER)

/// Test mask for array of CMPI encapsulated data types
#define CMPI_ENCA         (CMPI_ARRAY|CMPI_ENC)
/// Indicates a CMPIValue.array value with @ref CMPIInstance entries
#define CMPI_instanceA    (CMPI_ARRAY|CMPI_instance)
/// Indicates a CMPIValue.array value with @ref CMPIObjectPath entries
#define CMPI_refA         (CMPI_ARRAY|CMPI_ref)
/// Indicates a CMPIValue.array value with @ref CMPIString entries
#define CMPI_stringA      (CMPI_ARRAY|CMPI_string)
/// Indicates a CMPIValue.array value with C string entries
#define CMPI_charsA       (CMPI_ARRAY|CMPI_chars)
/// Indicates a CMPIValue.array value with @ref CMPIDateTime entries
#define CMPI_dateTimeA    (CMPI_ARRAY|CMPI_dateTime)
/// Not used
#define CMPI_charsptrA    (CMPI_ARRAY|CMPI_charsptr)

// The following are generic types for key bindings in
// CMPIObjectPath objects, that are used when the
// specific CIM types are not available.

/// Generic integer type in CMPIObjectPath
#define CMPI_keyInteger      (CMPI_sint64)
/// Generic string type in CMPIObjectPath
#define CMPI_keyString       (CMPI_string)
/// Generic boolean type in CMPIObjectPath
#define CMPI_keyBoolean      (CMPI_boolean)
/// Generic reference type in CMPIObjectPath
#define CMPI_keyRef          (CMPI_ref)

// The following are predicate types only.

/// Predicate type for strings
#define CMPI_charString      (CMPI_string)
/// Predicate type for integers
#define CMPI_integerString   (CMPI_string | CMPI_sint64)
/// Predicate type for real numbers
#define CMPI_realString      (CMPI_string | CMPI_real64)
/// Predicate type for numbers
#define CMPI_numericString   (CMPI_string | CMPI_sint64 | CMPI_real64)
/// Predicate type for booleans
#define CMPI_booleanString   (CMPI_string | CMPI_boolean)
/// Predicate type for datetime
#define CMPI_dateTimeString  (CMPI_string | CMPI_dateTime)
/// Predicate type for class names
#define CMPI_classNameString (CMPI_string | CMPI_class)
/// Predicate type for names
#define CMPI_nameString      (CMPI_string | ((16+10)<<8))

// Deprecated: The following symbols are synonyms for other symbols and are
// defined only for backward compatibility. They are not part of the CMPI
// Technical Standard, and their use is deprecated.
#ifndef CMPI_NO_SYNONYM_SUPPORT
#  define CMPI_Byte    CMPI_sint8
#  define CMPI_Short   CMPI_sint16
#  define CMPI_Int     CMPI_sint32
#  define CMPI_Long    CMPI_sint64
#  define CMPI_Float   CMPI_real32
#  define CMPI_Double  CMPI_real64
#  define CMPI_ByteA   CMPI_sint8A
#  define CMPI_ShortA  CMPI_sint16A
#  define CMPI_IntA    CMPI_sint32A
#  define CMPI_LongA   CMPI_sint64A
#  define CMPI_FloatA  CMPI_real32A
#  define CMPI_DoubleA CMPI_real64A
#endif // CMPI_NO_SYNONYM_SUPPORT

/**
 *   @}
 * @}
 * @addtogroup type-value-state
 * @{
 */

/**
 * @brief An integral bitmask type representing the state of a value in
 *     a CMPIData object.
 *
 * Test masks for @ref CMPIValueState are defined
 * @ref def-cmpivaluestate-symbols "here".
 */
typedef unsigned short CMPIValueState;

/**
 *   @anchor def-cmpivaluestate-symbols
 *   @name Test masks for @ref CMPIValueState
 *   @{
 *
 * They are used on @ref CMPIValueState.
 */
#define CMPI_goodValue (0)    /**< All flags are false */
#define CMPI_nullValue (1<<8) /**< Flag indicating that the data item is NULL */
#define CMPI_keyValue  (2<<8) /**< Flag indicating that the data item is a key
                                   binding */
#define CMPI_notFound  (4<<8) /**< `CMPI_notFound` is deprecated since CMPI 2.1;
                                   Use the return code to indicate that a
                                   data item has not been found */
#define CMPI_badValue  (0x80<<8) /**< Flag indicating that the data item is in
                                      error */

/**
 *   @}
 * @}
 * @addtogroup type-data
 * @{
 */

/**
 * @brief A structure type representing a CMPI data item.
 *
 * CMPI data items have type, state and value; they are used by MIs when
 * transferring data to the MB.
 */
typedef struct _CMPIData {

    /**
     * @brief Type of the data item.
     *
     * Undefined, if the data item is in error as per its state.
     */
    CMPIType type;

    /**
     * @brief State of the data item.
     */
    CMPIValueState state;

    /**
     * @brief Value of the data item.
     *
     * Undefined, if the data item is NULL or in error as per its state.
     */
    CMPIValue value;

} CMPIData;

/**
 * @}
 * @addtogroup type-accessor
 * @{
 */

/**
 * @brief A function type for accessing data during query processing.
 */
typedef CMPIData CMPIAccessor(const char* propertyName, void* parm);

/**
 * @}
 * @addtogroup type-msg-file-handle
 * @{
 */

/**
 * @brief An opaque type representing a handle to an open message file.
 */
typedef void* CMPIMsgFileHandle;

/**
 * @}
 * @addtogroup type-gc-stat
 * @{
 */

/**
 * @brief An opaque type that is used by the MB for use with the
 *   CMPIBrokerMemFT.mark() and CMPIBrokerMemFT.release() functions.
 */
typedef void CMPIGcStat;

/**
 * @}
 * @addtogroup type-flags
 * @{
 */

/**
 * @brief An integral bitmask type that represents options specified by the
 *     WBEM client and passed on to the MI for certain requests.
 *
 * The @ref CMPIFlags value is passed to MIs via the CMPIContext object, using
 * the context data entry @ref CMPIInvocationFlags.
 *
 * Test masks for @ref CMPIFlags are defined @ref def-cmpiflags-symbols "here".
 */
typedef unsigned int CMPIFlags;

/**
 *   @anchor def-cmpiflags-symbols
 *   @name Test masks for CMPIFlags
 *   @{
 *
 * They are used on @ref CMPIFlags. For a description of `LocalOnly` etc., see
 * @ref ref-dmtf-dsp0200 "DSP0200".
 */
#define CMPI_FLAG_LocalOnly          1
#define CMPI_FLAG_DeepInheritance    2
#define CMPI_FLAG_IncludeQualifiers  4
#define CMPI_FLAG_IncludeClassOrigin 8

/**
 *   @}
 * @}
 * @addtogroup type-version
 * @{
 */

/**
 * @brief An integral type for CMPI version fields (mainly in function tables).
 *
 * The values of entities of this type are numeric CMPI version numbers
 * (see @ref sym-version-nnn).
 */
typedef int CMPIVersion;

/**
 * @}
 * @addtogroup def-context-fieldnames
 * @{
 *
 * The fields in a CMPIContext object are set and accessed
 * by name using the the @ref CMPIContextFT::addEntry "addEntry()" and
 * @ref CMPIContextFT::getEntry "getEntry()" functions.
 *
 * The symbols defined in this module are the ASCII strings representing the
 * names of these fields.
 *
 * The description of each symbol indicates the C type that is to be used for
 * the corresponding field (e.g. for the `type` argument of
 * @ref CMPIContextFT::addEntry "addEntry()")
 */

/**
 * @brief Name of the target namespace for the invoked operation.
 *
 * Type: @ref CMPI_string
 */
#define CMPIInitNameSpace   "CMPIInitNameSpace"

/**
 * @brief Invocation flags for the invoked operation; see @ref CMPIFlags.
 *
 * Type: @ref CMPI_uint32
 */
#define CMPIInvocationFlags "CMPIInvocationFlags"

/**
 * @brief Authenticated ID of the user requesting the invoked operation.
 *
 * Type: @ref CMPI_string
 */
#define CMPIPrincipal       "CMPIPrincipal"

/**
 * @brief The role assumed by the current authenticated user.
 *
 * If the role is not available, the value of this entry shall be an empty
 * string.
 *
 * Type: @ref CMPI_string
 */
#define CMPIRole            "CMPIRole"

/**
 * @brief The preferred language(s) to be used by the MI.
 *
 * The preferred language(s) to be used by the MI for any language-specific
 * data in any results from MI functions, in the format of the
 * `Accept-Language` header field defined in @ref ref-ietf-rfc-2616 "RFC2616"
 * (a set of language tags, each with an optional quality value).
 *
 * If this information is not available, the value of this entry shall be an
 * empty string with the default meaning described in
 * @ref ref-ietf-rfc-2616 "RFC2616".
 *
 * Type: @ref CMPI_string
 */
#define CMPIAcceptLanguage  "CMPIAcceptLanguage"

/**
 * @brief The language(s) used by the MB.
 *
 * The language(s) used by the MB for any language-specific data passed to MI
 * functions, in the format of the `Content-Language` header field defined in
 * @ref ref-ietf-rfc-2616 "RFC2616" (a set of language tags).
 *
 * If this information is not available, the value of this entry shall be an
 * empty string with the default meaning described in
 * @ref ref-ietf-rfc-2616 "RFC2616".
 *
 * Type: @ref CMPI_string
 */
#define CMPIContentLanguage "CMPIContentLanguage"

/**
 * @}
 * @addtogroup type-rc
 * @{
 */

/**
 * @brief An enumeration type that defines CMPI return code values.
 *
 * CMPI return code values are used mainly for @ref CMPIStatus.rc, and in rare
 * cases directly in MB functions.
 *
 * The enumerators can be categorized into these groups:
 *
 * @li `CMPI_RC_OK` to `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED`:@n
 *     Return codes matching CIM status codes. They are sometimes used for
 *     CMPI-specific purposes as well.
 * @li `CMPI_RC_DO_NOT_UNLOAD` to `CMPI_RC_NEVER_UNLOAD`:@n
 *     Return codes used only by the MI `cleanup()` functions (e.g.
       CMPIInstanceMIFT.cleanup()).
 * @li `CMPI_RC_ERR_INVALID_HANDLE` to `CMPI_RC_ERR_NOT_IN_CODEPAGE`:@n
 *     Return codes for other errors detected by CMPI.
 * @li `CMPI_RC_ERROR_SYSTEM` to `CMPI_RC_ERROR`:@n
 *     Return codes for errors returned by the underlying operating system.
 *
 * The descriptions of the enumerators in this module are meant to provide for
 * a general understanding; their exact meaning is described in the MB or MI
 * functions using them.
 */
typedef enum _CMPIrc {

    /*
     * Return codes matching CIM status codes
     */

    /** Success */
    CMPI_RC_OK = 0,
    /** Unspecific error occurred */
    CMPI_RC_ERR_FAILED = 1,
    /** Not authorized */
    CMPI_RC_ERR_ACCESS_DENIED = 2,
    /** Invalid namespace */
    CMPI_RC_ERR_INVALID_NAMESPACE = 3,
    /** Invalid parameter */
    CMPI_RC_ERR_INVALID_PARAMETER = 4,
    /** Invalid class */
    CMPI_RC_ERR_INVALID_CLASS = 5,
    /** Item (class, instance, message file, etc.) not found */
    CMPI_RC_ERR_NOT_FOUND = 6,
    /** Operation not supported */
    CMPI_RC_ERR_NOT_SUPPORTED = 7,
    /** Class has subclasses */
    CMPI_RC_ERR_CLASS_HAS_CHILDREN = 8,
    /** Class has instances */
    CMPI_RC_ERR_CLASS_HAS_INSTANCES = 9,
    /** Invalid superclass */
    CMPI_RC_ERR_INVALID_SUPERCLASS = 10,
    /** Object already exists */
    CMPI_RC_ERR_ALREADY_EXISTS = 11,
    /** Property not found (e.g. not defined in the class) */
    CMPI_RC_ERR_NO_SUCH_PROPERTY = 12,
    /** Type mismatch */
    CMPI_RC_ERR_TYPE_MISMATCH = 13,
    /** Query language not supported */
    CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED = 14,
    /** Invalid query */
    CMPI_RC_ERR_INVALID_QUERY = 15,
    /** Method not available (e.g. not supported / implemented) */
    CMPI_RC_ERR_METHOD_NOT_AVAILABLE = 16,
    /** Method not found (e.g. not defined in the class) */
    CMPI_RC_ERR_METHOD_NOT_FOUND = 17,
    /** No more elements */
    CMPI_RC_NO_MORE_ELEMENTS = 18,
    /** Server limits exceeded */
    CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED = 27,
    /** Query feature not supported */
    CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED = 29,

    /*
     * Return codes used only by the MI cleanup() functions
     */

    /** Operation successful - Do not unload the MI now */
    CMPI_RC_DO_NOT_UNLOAD = 50,
    /** Operation successful - Never unload the MI */
    CMPI_RC_NEVER_UNLOAD = 51,

    /*
     * Return codes for other errors detected by CMPI
     */

    /** Invalid handle to CMPI data */
    CMPI_RC_ERR_INVALID_HANDLE = 60,
    /** Invalid data type */
    CMPI_RC_ERR_INVALID_DATA_TYPE = 61,
    /** Characters are not representable in the specified codepage */
    CMPI_RC_ERR_NOT_IN_CODEPAGE = 62,

    /*
     * Return codes for errors returned by the underlying operating system
     */

    /** Not currently used */
    CMPI_RC_ERROR_SYSTEM = 100,
    /** Not currently used */
    CMPI_RC_ERROR = 200

} CMPIrc;

/**
 * @}
 * @addtogroup type-status
 * @{
 */

/**
 * @brief A structure that indicates success or failure of MB and MI functions.
 *
 * It is used either as a function return value, or as an output parameter.
 */
typedef struct _CMPIStatus {

    /**
     * @brief A return code.
     *
     * @see @ref CMPIrc.
     */
    CMPIrc rc;

    /**
     * @brief An error message.
     *
     * Points to a CMPIString object representing an error message, or is
     * NULL if no error message is available.
     */
    CMPIString* msg;

} CMPIStatus;

/**
 * @}
 * @addtogroup mb-capabilities
 * @{
 *
 * These symbols define test masks for MB capabilities, for use on
 * CMPIBrokerFT.brokerCapabilities.
 *
 * If a bit in the value of CMPIBrokerFT.brokerCapabilities is set to 1,
 * the corresponding capability is available; otherwise, it is not available.
 *
 * For historical reasons, the test mask values have the bits for any dependent
 * capabilities also set to 1, in addition to the bit for the capability they
 * actually represent.
 *
 * Bits that are unassigned in this version of CMPI are reserved for future
 * extensions and shall not be used for implementation-specific purposes.
 */

#define CMPI_MB_BasicRead                0x00000001  ///< Basic Read
#define CMPI_MB_BasicWrite               0x00000003  ///< Basic Write
#define CMPI_MB_InstanceManipulation     0x00000007  ///< Instance Manipulation
#define CMPI_MB_AssociationTraversal     0x00000009  ///< Association Traversal
#define CMPI_MB_QueryExecution           0x00000011  ///< Query Execution
/**
 * @brief Query Normalization.
 *
 * Optional to be supported.
 */
#define CMPI_MB_QueryNormalization       0x00000031
/**
 * @brief Basic Qualifier.
 *
 * Optional to be supported.
 */
#define CMPI_MB_BasicQualifierSupport       0x00000047
/**
 * @brief Indications.
 *
 * Optional to be supported.
 */
#define CMPI_MB_Indications                 0x00000081
/**
 * @brief OS Encapsulation Services
 *
 * @required200 Required to be supported since CMPI 2.0.0.
 */
#define CMPI_MB_OSEncapsulationSupport      0x00000100

#ifdef CMPI_VER_200

/**
 * @brief Memory Enhancement Services
 *
 * Optional to be supported.
 *
 * @added200 Added in CMPI 2.0.0.
 */
#define CMPI_MB_Supports_MemEnhancements    0x00004000
/**
 * @brief Extended Errors
 *
 * @added200 Added in CMPI 2.0.0.
 * @required210 Required to be supported since CMPI 2.1.0.
 */
#define CMPI_MB_Supports_Extended_Error     0x00008000

#endif

#ifdef CMPI_VER_210

/**
 * @brief Logging
 *
 * Optional to be supported.
 *
 * @added210 Added the capability flag in CMPI 2.1.0; the capability itself
 *     existed since CMPI 1.0.0.
 */
#define CMPI_MB_Logging                     0x00010000
/**
 * @brief Tracing
 *
 * Optional to be supported.
 *
 * @added210 Added the capability flag in CMPI 2.1.0; the capability itself
 *     existed since CMPI 1.0.0.
 */
#define CMPI_MB_Tracing                     0x00020000
/**
 * @brief Property Filtering
 *
 * Optional to be supported.
 *
 * @added210 Added the capability flag in CMPI 2.1.0; the capability itself
 *     existed since CMPI 1.0.0.
 */
#define CMPI_MB_PropertyFiltering           0x00040001
/**
 * @brief Codepage Conversion
 *
 * Optional to be supported.
 *
 * @added210 Added in CMPI 2.1.0.
 */
#define CMPI_MB_CodepageConversion          0x00080000

#endif

// Deprecated: The following symbols are synonyms for other symbols and are
// defined only for backward compatibility. They are not part of the CMPI
// Technical Standard, and their use is deprecated.
#ifndef CMPI_NO_SYNONYM_SUPPORT
#  define CMPI_MB_Class_0                   CMPI_MB_BasicRead
#  define CMPI_MB_Class_1                   CMPI_MB_BasicWrite
#  define CMPI_MB_Class_2                   CMPI_MB_InstanceManipulation
#endif // CMPI_NO_SYNONYM_SUPPORT

// Deprecated: The following symbols probably represent capability flags that
// pre-date the first CMPI Technical Standard. Note that some of their values
// are in conflict with values that are officially defined. These symbols are
// disabled by default and can be enabled by defining the
// CMPI_PRE_STANDARD_CAPABILITY_SUPPORT symbol. These symbols are not part of
// the CMPI Technical Standard, and their use is deprecated.
#ifdef CMPI_PRE_STANDARD_CAPABILITY_SUPPORT
#  define CMPI_MB_Supports_PropertyMI         0x00000100
#  define CMPI_MB_Supports_IndicationMI       0x00000200
#  define CMPI_MB_Supports_IndicationPolling  0x00000400
#  define CMPI_MB_Supports_QueryNormalization 0x00000800
#  define CMPI_MB_Supports_Qualifier          0x00001000
#  define CMPI_MB_Supports_Schema             0x00003000
#endif

/**
 * @}
 * @addtogroup type-pred-op
 * @{
 */

/**
 * @brief An enumeration type that defines predicate operators in parsed
 *     queries.
 */
typedef enum _CMPIPredOp {
    CMPI_PredOp_Equals = 1,
    CMPI_PredOp_NotEquals = 2,
    CMPI_PredOp_LessThan = 3,
    CMPI_PredOp_GreaterThanOrEquals = 4,
    CMPI_PredOp_GreaterThan = 5,
    CMPI_PredOp_LessThanOrEquals = 6,
    CMPI_PredOp_Isa = 7,
    CMPI_PredOp_NotIsa = 8,
    CMPI_PredOp_Like = 9,
    CMPI_PredOp_NotLike = 10
#ifdef CMPI_VER_200
    ,
    CMPI_PredOp_Not_Null = 11,
    CMPI_PredOp_Null = 12,
    CMPI_PredOp_And = 13,
    CMPI_PredOp_Or = 14
#endif
} CMPIPredOp;

/**
 * @}
 * @addtogroup type-severity
 * @{
 */

/**
 * @brief An enumeration type that defines severity levels for logging
 *     functions.
 */
typedef enum _CMPISeverity {
    /** Error */
    CMPI_SEV_ERROR = 1,
    /** General info */
    CMPI_SEV_INFO = 2,
    /** Warning message */
    CMPI_SEV_WARNING = 3,
    /** Debug message */
    CMPI_DEV_DEBUG = 4
} CMPISeverity;

/**
 * @}
 * @addtogroup type-level
 * @{
 */

/**
 * @brief An enumeration type that defines logging levels for trace functions.
 */
typedef enum _CMPILevel {
    /** Generic information */
    CMPI_LEV_INFO = 1,
    /** warnings */
    CMPI_LEV_WARNING = 2,
    /** detailed/specific information */
    CMPI_LEV_VERBOSE = 3
} CMPILevel;

/**
 * @}
 */

#ifdef CMPI_DEFINE_CMPISelectCondType

/**
 * @addtogroup type-select-cond-type
 * @{
 */

/**
 * @brief An enumeration type defining the normalization type a query
 *     expression is normalized to.
 *
 * It is defined conditionally, when the @ref CMPI_DEFINE_CMPISelectCondType
 * symbol is defined.
 *
 * @deprecated This enumeration has never been part of the CMPI Technical
 *     Standard; it is defined for backward compatibility of the CMPI header
 *     files, and its use is deprecated.
 */
typedef enum _CMPISelectCondType {
    /** Disjuntion Of Conjunctions */
    CMPI_COND_DOC = 0,
    /** Conjuction of disjunctions */
    CMPI_COND_COD = 1
} CMPISelectCondType;

/**
 * @}
 */

#endif

#ifdef CMPI_VER_200

/**
 * @addtogroup type-error-type
 * @{
 */

/**
 * @brief An enumeration type that defines possible values for the error
 *     type in a CMPIError object.
 */
typedef enum _CMPIErrorType {
    /** Unkown */
    UnknownErrorType = 0,
    /** Other */
    OtherErrorType = 1,
    /** Communications error */
    CommunicationsError = 2,
    /** QoS error */
    QualityOfServiceError = 3,
    /** Software error */
    SoftwareError = 4,
    /** Hardware error */
    HardwareError = 5,
    /** Environmental error */
    EnvironmentalError = 6,
    /** Security error */
    SecurityError = 7,
    /** Over subscription error */
    OversubscriptionError = 8,
    /** Over subscription error.
     *  Deprecated, use @p OversubscriptionError instead */
    Oversubscription_Error = OversubscriptionError,
    /** Unavailable resource */
    UnavailableResourceError = 9,
    /** Unsupported operation */
    UnsupportedOperationError = 10
} CMPIErrorType;

/**
 * @}
 * @addtogroup type-error-severity
 * @{
 */

/**
 * @brief An enumeration type that defines possible values for the
 *     error severity in a CMPIError object.
 */
typedef enum _CMPIErrorSeverity {
    /** Unknown */
    ErrorSevUnknown = 0,
    /** Low severity */
    ErrorSevLow = 2,
    /** Medium Severity */
    ErrorSevMedium = 3,
    /** High severity */
    ErrorSevHigh = 4,
    /** Fatal error */
    ErrorSevFatal = 5,
} CMPIErrorSeverity;

/**
 * @}
 * @addtogroup type-error-probable-cause
 * @{
 */

/**
 * @brief An enumeration type that defines possible values for
 *     the probable cause in a CMPIError object.
 */
typedef enum _CMPIErrorProbableCause {
    /** Unknown */
    ErrorProbCauseUnknown = 0,
    /** Other cause */
    ErrorProbCauseOther = 1,
    /** Adpater card failure */
    Adapter_Card_Error = 2,
    /** Subsystem failure */
    Application_Subsystem_Failure = 3,
    /** Reduced bandwidth */
    Bandwidth_Reduced = 4,
    /** Could not establish connection */
    Connection_Establishment_Error = 5,
    /** protocol error */
    Communications_Protocol_Error = 6,
    /** Subsystem failure */
    Communications_Subsystem_Failure = 7,
    /** Configuration error */
    ConfigurationCustomization_Error = 8,
    /** Congested */
    Congestion = 9,
    /** Data is corrupt */
    Corrupt_Data = 10,
    /** CPU cycles exceeded */
    CPU_Cycles_Limit_Exceeded = 11,
    /** Dataset modem error */
    DatasetModem_Error = 12,
    /** Degraded signal */
    Degraded_Signal = 13,
    /** STE/DCE Interface Error */
    DTE_DCE_Interface_Error = 14,
    /** Door open */
    Enclosure_Door_Open = 15,
    /** Equipment malfunction */
    Equipment_Malfunction = 16,
    /** Excessive Vibration */
    Excessive_Vibration = 17,
    /** File format error */
    File_Format_Error = 18,
    /** Fire detected */
    Fire_Detected = 19,
    /** Flood detected */
    Flood_Detected = 20,
    /** framing error */
    Framing_Error = 21,
    /** HVAC problem */
    HVAC_Problem = 22,
    /** Humidity unacceptable */
    Humidity_Unacceptable = 23,
    /** IO device error */
    IO_Device_Error = 24,
    /** Input device error */
    Input_Device_Error = 25,
    /** LAN Error */
    LAN_Error = 26,
    /** Non-toxic leak detected */
    Non_Toxic_Leak_Detected = 27,
    /** Local node transmission error */
    Local_Node_Transmission_Error = 28,
    /** loss of frame */
    Loss_of_Frame = 29,
    /** loss of signal */
    Loss_of_Signal = 30,
    /** Material supply exhausted */
    Material_Supply_Exhausted = 31,
    /** Multiplexer problem */
    Multiplexer_Problem = 32,
    /** Out of memory */
    Out_of_Memory = 33,
    /** Output device error */
    Output_Device_Error = 34,
    /** Performance degraded */
    Performance_Degraded = 35,
    /** Power problem */
    Power_Problem = 36,
    /** Pressure unacceptable */
    Pressure_Unacceptable = 37,
    /** Processor problem */
    Processor_Problem = 38,
    /** Pump failure */
    Pump_Failure = 39,
    /** Queue size exceeded */
    Queue_Size_Exceeded = 40,
    /** Receive failure */
    Receive_Failure = 41,
    /** Receiver failure */
    Receiver_Failure = 42,
    /** Remote node transmission error */
    Remote_Node_Transmission_Error = 43,
    /** Resource at or nearing capacity */
    Resource_at_or_Nearing_Capacity = 44,
    /** Response time excessive */
    Response_Time_Excessive = 45,
    /** Retransmission rate excessive */
    Retransmission_Rate_Excessive = 46,
    /** Software Error */
    Software_Error = 47,
    /** Software terminated abnormally */
    Software_Program_Abnormally_Terminated = 48,
    /** Program error */
    Software_Program_Error = 49,
    /** Storage capacity problem */
    Storage_Capacity_Problem = 50,
    /** Temperature_Unacceptable */
    Temperature_Unacceptable = 51,
    /** Threshold_Crossed */
    Threshold_Crossed = 52,
    /** Timing_Problem */
    Timing_Problem = 53,
    /** Toxic_Leak_Detected */
    Toxic_Leak_Detected = 54,
    /** Transmit_Failure */
    Transmit_Failure = 55,
    /** Transmitter_Failure */
    Transmitter_Failure = 56,
    /** Underlying_Resource_Unavailable */
    Underlying_Resource_Unavailable = 57,
    /** Version_Mismatch */
    Version_Mismatch = 58,
    /** Previous_Alert_Cleared */
    Previous_Alert_Cleared = 59,
    /** Login_Attempts_Failed */
    Login_Attempts_Failed = 60,
    /** Software_Virus_Detected */
    Software_Virus_Detected = 61,
    /** Hardware_Security_Breached */
    Hardware_Security_Breached = 62,
    /** Denial_of_Service_Detected */
    Denial_of_Service_Detected = 63,
    /** Security_Credential_Mismatch */
    Security_Credential_Mismatch = 64,
    /** Unauthorized_Access */
    Unauthorized_Access = 65,
    /** Alarm_Received */
    Alarm_Received = 66,
    /** Loss_of_Pointer */
    Loss_of_Pointer = 67,
    /** Payload_Mismatch */
    Payload_Mismatch = 68,
    /** Transmission_Error */
    Transmission_Error = 69,
    /** Excessive_Error_Rate */
    Excessive_Error_Rate = 70,
    /** Trace_Problem */
    Trace_Problem = 71,
    /** Element_Unavailable */
    Element_Unavailable = 72,
    /** Element_Missing */
    Element_Missing = 73,
    /** Loss_of_Multi_Frame */
    Loss_of_Multi_Frame = 74,
    /** Broadcast_Channel_Failure */
    Broadcast_Channel_Failure = 75,
    /** Invalid_Message_Received */
    Invalid_Message_Received = 76,
    /** Routing_Failure */
    Routing_Failure = 77,
    /** Backplane_Failure */
    Backplane_Failure = 78,
    /** Identifier_Duplication */
    Identifier_Duplication = 79,
    /** Protection_Path_Failure */
    Protection_Path_Failure = 80,
    /** Sync_Loss_or_Mismatch */
    Sync_Loss_or_Mismatch = 81,
    /** Terminal_Problem */
    Terminal_Problem = 82,
    /** Real_Time_Clock_Failure */
    Real_Time_Clock_Failure = 83,
    /** Antenna_Failure */
    Antenna_Failure = 84,
    /** Battery_Charging_Failure */
    Battery_Charging_Failure = 85,
    /** Disk_Failure */
    Disk_Failure = 86,
    /** Frequency_Hopping_Failure */
    Frequency_Hopping_Failure = 87,
    /** Loss_of_Redundancy */
    Loss_of_Redundancy = 88,
    /** Power_Supply_Failure */
    Power_Supply_Failure = 89,
    /** Signal_Quality_Problem */
    Signal_Quality_Problem = 90,
    /** Battery_Discharging */
    Battery_Discharging = 91,
    /** Battery_Failure */
    Battery_Failure = 92,
    /** Commercial_Power_Problem */
    Commercial_Power_Problem = 93,
    /** Fan_Failure */
    Fan_Failure = 94,
    /** Engine_Failure */
    Engine_Failure = 95,
    /** Sensor_Failure */
    Sensor_Failure = 96,
    /** Fuse_Failure */
    Fuse_Failure = 97,
    /** Generator_Failure */
    Generator_Failure = 98,
    /** Low_Battery */
    Low_Battery = 99,
    /** Low_Fuel */
    Low_Fuel = 100,
    /** Low_Water */
    Low_Water = 101,
    /** Explosive_Gas */
    Explosive_Gas = 102,
    /** High_Winds */
    High_Winds = 103,
    /** Ice_Buildup */
    Ice_Buildup = 104,
    /** Smoke */
    Smoke = 105,
    /** Memory_Mismatch */
    Memory_Mismatch = 106,
    /** Out_of_CPU_Cycles */
    Out_of_CPU_Cycles = 107,
    /** Software_Environment_Problem */
    Software_Environment_Problem = 108,
    /** Software_Download_Failure */
    Software_Download_Failure = 109,
    /** Element_Reinitialized */
    Element_Reinitialized = 110,
    /** Timeout */
    Timeout = 111,
    /** Logging_Problems */
    Logging_Problems = 112,
    /** Leak_Detected */
    Leak_Detected = 113,
    /** Protection_Mechanism_Failure */
    Protection_Mechanism_Failure = 114,
    /** Protecting_Resource_Failure */
    Protecting_Resource_Failure = 115,
    /** Database_Inconsistency */
    Database_Inconsistency = 116,
    /** Authentication_Failure */
    Authentication_Failure = 117,
    /** Breach_of_Confidentiality */
    Breach_of_Confidentiality = 118,
    /** Cable_Tamper */
    Cable_Tamper = 119,
    /** Delayed_Information */
    Delayed_Information = 120,
    /** Duplicate_Information */
    Duplicate_Information = 121,
    /** Information_Missing */
    Information_Missing = 122,
    /** Information_Modification */
    Information_Modification = 123,
    /** Information_Out_of_Sequence */
    Information_Out_of_Sequence = 124,
    /** Key_Expired */
    Key_Expired = 125,
    /** Non_Repudiation_Failure */
    Non_Repudiation_Failure = 126,
    /** Out_of_Hours_Activity */
    Out_of_Hours_Activity = 127,
    /** Out_of_Service */
    Out_of_Service = 128,
    /** Procedural_Error */
    Procedural_Error = 129,
    /** Unexpected_Information */
    Unexpected_Information = 130
} CMPIErrorProbableCause;

/**
 * @}
 * @addtogroup type-error-src-format
 * @{
 */

/**
 * @brief An enumeration type that defines possible values for the
 *     source format in a CMPIError object.
 */
typedef enum _CMPIErrorSrcFormat {
    /** Unknown source */
    CMPIErrSrcUnknown = 0,
    /** Other source */
    CMPIErrSrcOther = 1,
    /** Object handle */
    CIMObjectHandle = 2
} CMPIErrorSrcFormat;

/**
 * @}
 */

#endif // CMPI_VER_200

#ifdef CMPI_VER_210

/**
 * @addtogroup type-codepage-id
 * @{
 */

/**
 * @brief An enumeration type that identifies a codepage for CMPI codepage
 *     support.
 *
 * @added210 Added in CMPI 2.1.0.
 */
typedef enum _CMPICodepageID {
    /** Current system codepage for the MB */
    CMPI_CPID_SYSTEM = 1,
    /** 7-bit US-ASCII as defined in
        @ref ref-iso-iec-646-1991 "ISO/IEC 646:1991" */
    CMPI_CPID_USASCII = 2,
    /** UTF-16 */
    CMPI_CPID_UTF16 = 3
} CMPICodepageID;

/**
 * @}
 */

#endif // CMPI_VER_210

#ifdef __cplusplus
}
#endif

#endif // _CMPIDT_H_
