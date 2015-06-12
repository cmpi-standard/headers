/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Copyright (c) 2006-2014 The Open Group                                    */
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
 * MIs do not need to include this header because it is included by cmpift.h.
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
 * @defgroup symbols Preprocessor Symbols
 * @{
 *   @defgroup sym-version-nnn CMPIVersionNNN - Symbols encapsulating the numerical CMPI versions
 *   @{
 *   @}
 *   @defgroup sym-current-version CMPICurrentVersion - Symbol defining the current CMPI version
 *   @{
 *   @}
 *   @defgroup sym-version CMPI_VERSION - Symbol defining the implemented CMPI version
 *   @{
 *   @}
 *   @defgroup sym-ver-nnn CMPI_VER_NNN - Symbols for testing CMPI version-dependent features
 *   @{
 *   @}
 * @}
 * @defgroup data-types Data Types (Sect. 5)
 * @{
 *   @defgroup type-codepage-id Codepage Conversion (Sect. 5.2.2)
 *   @{
 *   @}
 *   @defgroup types-cim-types C Data Types for CIM Data Types (Sect. 5.4)
 *   @{
 *   @}
 *   @defgroup types-misc CMPI Miscellaneous Data Types (Sect. 5.5)
 *   @{
 *     @defgroup type-valueptr CMPIValuePtr
 *     @{
 *     @}
 *     @defgroup type-accessor CMPIAccessor
 *     @{
 *     @}
 *     @defgroup type-select-cond-type CMPISelectCondType
 *     @{
 *     @}
 *   @}
 *   @defgroup types-data-items CMPI Data Items (Sect. 5.6)
 *   @{
 *     @defgroup type-data CMPIData
 *     @{
 *     @}
 *     @defgroup type-type CMPIType
 *     @{
 *     @}
 *     @defgroup type-value-state CMPIValueState
 *     @{
 *     @}
 *     @defgroup type-value CMPIValue
 *     @{
 *     @}
 *     @defgroup type-pred-op CMPIPredOp
 *     @{
 *     @}
 *     @defgroup type-count CMPICount
 *     @{
 *     @}
 *     @defgroup type-msg-file-handle CMPIMsgFileHandle
 *     @{
 *     @}
 *     @defgroup type-gc-stat CMPIGcStat
 *     @{
 *     @}
 *     @defgroup type-version CMPIVersion
 *     @{
 *     @}
 *   @}
 *   @defgroup type-status CMPIStatus (Sect. 5.8)
 *   @{
 *   @}
 *   @defgroup type-rc CMPIRc (Return Codes) (Sect. 5.9)
 *   @{
 *   @}
 *   @defgroup type-severity CMPISeverity (Severity Codes) (Sect. 5.10)
 *   @{
 *   @}
 *   @defgroup type-level CMPILevel (Trace Levels) (Sect. 5.11)
 *   @{
 *   @}
 *   @defgroup type-error-type CMPIErrorType (Extended Error Types) (Sect. 5.12)
 *   @{
 *   @}
 *   @defgroup type-error-severity CMPIErrorSeverity (Extended Error Severity Levels) (Sect. 5.13)
 *   @{
 *   @}
 *   @defgroup type-error-probable-cause CMPIErrorProbableCause (Extended Error Probable Causes) (Sect. 5.14)
 *   @{
 *   @}
 *   @defgroup type-error-src-format CMPIErrorSrcFormat (Extended Error Source Formats) (Sect. 5.15)
 *   @{
 *   @}
 *   @defgroup type-flags CMPIFlags (Sect. 5.16)
 *   @{
 *   @}
 * @}
 */

/**
 * @addtogroup sym-version-nnn
 * @{
 */

/**
 * @brief These symbols encapsulate the values for the numeric CMPI version numbers.
 *
 * Note: Historical CMPI levels (before the first CMPI Technical Standard, e.g.
 * 86, 90) are not supported by this header file.
 *
 * @todo TODO_AM Description above is assigned to first symbol, but should be for all of them.
 *   @{
 */
#define CMPIVersion100 100  ///<  CMPI 1.0.0
#define CMPIVersion200 200  ///<  CMPI 2.0.0
#define CMPIVersion210 210  ///<  CMPI 2.1.0

/**
 *   @}
 * @}
 * @addtogroup sym-current-version
 * @{
 */

/**
 * @brief The CMPI version to which this version of the header files belong.
 * 
 * At the same time, this is the highest CMPI version supported by these
 * header files.
 */
#define CMPICurrentVersion CMPIVersion210

/**
 * @}
 * @addtogroup sym-version
 * @{
 */

/**
 * @brief The CMPI version that is implemented by the MI or MB code using these
 * header files.
 *
 * This symbol is only set in this header file if not set outside of this header
 * file. Its default value defined here is @ref CMPICurrentVersion, and it can
 * be overridden outside of the CMPI header files if an older CMPI version is
 * intended to be implemented.
 */
#ifndef CMPI_VERSION
#  define CMPI_VERSION CMPICurrentVersion
#endif

/**
 * @}
 * @addtogroup sym-ver-nnn
 * @{
 */

/**
 * @brief Boolean flags for testing whether CMPI version dependent features
 * should be available, given the implemented version.
 *
 * Available means that the feature is defined in the header files and
 * subsequently can be supported in the MB or MI implementation.
 *
 * A symbol for a particular version (e.g. CMPI_VER_200) is defined if its
 * version is lower than or equal to the CMPI version that is implemented (as
 * indicated by @ref CMPI_VERSION). Otherwise, it is undefined.
 *
 * This allows a feature that was introduced in a particular CMPI version to
 * be defined like in the following example:
 *
 *     #ifdef CMPI_VER_200
 *     // definition of feature that was added in CMPI 2.0.0
 *     #endif
 *
 * @todo TODO_AM Description above is assigned to first symbol, but should be for all of them.
 */

#if (CMPI_VERSION == CMPIVersion210)
///  Check for features introduced in CMPI 2.1.0
#  define CMPI_VER_210 1
///  Check for features introduced in CMPI 2.0.0
#  define CMPI_VER_200 1
///  Check for features introduced in CMPI 1.0.0
#  define CMPI_VER_100 1
#elif (CMPI_VERSION == CMPIVersion200)
///  Check for features introduced in CMPI 2.0.0
#  define CMPI_VER_200 1
///  Check for features introduced in CMPI 1.0.0
#  define CMPI_VER_100 1
#elif (CMPI_VERSION == CMPIVersion100)
///  Check for features introduced in CMPI 1.0.0
#  define CMPI_VER_100 1
#else
#  error Unsupported CMPI version defined in CMPI_VERSION symbol
#endif

/**
 * @}
 */

/**
 * @{
 * Forward declarations and typedefs for the CMPIBroker object and its function
 * tables.
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
/**
 * @}
 */

/**
 * @{
 * Forward declarations and typedefs for encapsulated data types and their
 * function tables.
 */
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
/**
 * @}
 * @{
 * Forward declarations for MI function table types.
 */
typedef struct _CMPIInstanceMIFT CMPIInstanceMIFT;
typedef struct _CMPIAssociationMIFT CMPIAssociationMIFT;
typedef struct _CMPIMethodMIFT CMPIMethodMIFT;
typedef struct _CMPIPropertyMIFT CMPIPropertyMIFT;
typedef struct _CMPIIndicationMIFT CMPIIndicationMIFT;
/**
 * @}
 */

/**
 * @addtogroup types-cim-types
 * @{
 */

/**
 * @brief C types for CIM data types.
 *
 * These types cover most CIM data types. The remaining CIM data types
 * are defined as encapsulated data types:
 *
 *   * [CMPIString](@ref _CMPIString) - CIM data type string
 *   * [CMPIDateTime](@ref _CMPIDateTime) - CIM data type datetime
 *   * [CMPIObjectPath](@ref _CMPIObjectPath) - CIM data type reference
 *   * [CMPIInstance](@ref _CMPIInstance) - for embedded instances
 *
 * Note that some of the types shown in the documentation generated
 * from this header file depend on the platform (see cmpipl.h), and are shown
 * for CMPI_PLATFORM_LINUX_GENERIC_GNU. For details, examine the source code of
 * cmpidt.h.
 *
 * @todo TODO_AM Description above is assigned to first type, but should be for all of them.
 */
typedef unsigned char CMPIBoolean;     ///< CIM data type boolean
typedef unsigned short CMPIChar16;     ///< CIM data type char16
typedef unsigned char CMPIUint8;       ///< CIM data type uint8
typedef unsigned short CMPIUint16;     ///< CIM data type uint16
typedef unsigned int CMPIUint32;       ///< CIM data type uint32
#ifndef CMPI_PLATFORM_WIN32_IX86_MSVC
typedef unsigned long long CMPIUint64; ///< CIM data type uint64
#else
typedef unsigned __int64 CMPIUint64;   ///< CIM data type uint64
#endif
typedef signed char CMPISint8;         ///< CIM data type sint8
 typedef short CMPISint16;             ///< CIM data type sint16
 typedef signed int CMPISint32;        ///< CIM data type sint32
#ifndef CMPI_PLATFORM_WIN32_IX86_MSVC
typedef long long CMPISint64;          ///< CIM data type sint64
#else
typedef __int64 CMPISint64;            ///< CIM data type sint64 
#endif
typedef float CMPIReal32;              ///< CIM data type real32
typedef double CMPIReal64;             ///< CIM data type real64

/**
 * @}
 * @addtogroup type-count
 * @{
 */

/** 
 * @brief An unsigned integer that specifies a number of elements or position
 * in a sequential data type.
 *
 * It is used as argument or return type of other functions and specifies e.g.
 * number of items in [CMPIArray](@ref _CMPIArray),
 * number of Bytes in @ref CMPIValuePtr,
 * number of variable function arguments, or
 * index into [CMPIArray](@ref _CMPIArray).
 */
typedef unsigned int CMPICount;

/**
 * @}
 * @addtogroup type-valueptr
 * @{
 */

/**
 * @brief A raw unformatted data area of a specified site.
 *
 * CMPIValuePtr is used for context data only.
 */
typedef struct _CMPIValuePtr {

    /**
     * Pointer to the first Byte of the chunk of data.
     */
    void *ptr;

    /**
     * Size of the chunk of data, in Bytes.
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
 * CMPI.
 *
 * CMPIValue is used in [CMPIData](@ref type-data), but also standalone.
 */
typedef union _CMPIValue {
    CMPIBoolean boolean; ///< boolean CMPIvalue. Corresponds to CIMBoolean type
    CMPIChar16 char16;   ///< char16 CIMType
    CMPIUint8 uint8;     ///< uint8 CIMType
    CMPIUint16 uint16;   ///< uint16 CIMType
    CMPIUint32 uint32;   ///< uint32 CIMType
    CMPIUint64 uint64;   ///< uint64 CIMType
    CMPISint8 sint8;     ///< sint8 CIMType
    CMPISint16 sint16;   ///< sint16 CIMType
    CMPISint32 sint32;   ///< sint32 CIMType
    CMPISint64 sint64;   ///< sint64 CIMType
    CMPIReal32 real32;   ///< real32 CIMType
    CMPIReal64 real64;   ///< real64 CIMType

    CMPIInstance* inst;     ///< pointer to CMPIInstance
    CMPIObjectPath* ref;    ///< pointer to CMPIObjectPath
    CMPIArgs* args;         ///< Pointer to CMPIArgs
    CMPISelectExp* filter;  ///< Pointer to CMPISelectExp
    CMPIEnumeration* Enum;  ///< Pointer to CMPIEnumeration
    CMPIArray* array;       ///< Pointer to CMPIArray
    CMPIString* string;     ///< Pointer to CMPIString
    char* chars;            ///< Pointer to C String
    CMPIDateTime* dateTime; ///< Pointer to CMPIDateTIme
    CMPIValuePtr dataPtr;   ///< Pointer to CMPIValue

    // Deprecated: The following union members
    // are deprecated. Use the members defined
    // earlier in this union, instead.
    CMPISint8  Byte;   ///< Deprecated: Use sint8
    CMPISint16 Short;  ///< Deprecated: Use sint16
    CMPISint32 Int;    ///< Deprecated: Use sint32
    CMPISint64 Long;   ///< Deprecated: Use sint64
    CMPIReal32 Float;  ///< Deprecated: Use real32
    CMPIReal64 Double; ///< Deprecated: Use real64

} CMPIValue;

/**
 * @}
 * @addtogroup type-type CMPIType
 * @{
 */

/**
 * @brief An integral bitmask type representing a CMPI type.
 *
 * CMPIType is used mainly in CMPI data items (see [CMPIData](@ref type-data))
 * and is also used standalone in some cases.
 *
 * Test masks for CMPIType are defined [here](@ref def-cmpitype-symbols).
 */
typedef unsigned short CMPIType;

/** 
 *   @anchor def-cmpitype-symbols
 *   @name Test masks for CMPIType
 *   @{
 *
 * They are used on @ref CMPIType.
 */
#define CMPI_null         0

#define CMPI_SIMPLE       (2)
#define CMPI_boolean      (2+0)
#define CMPI_char16       (2+1)

#define CMPI_REAL         ((2)<<2)
#define CMPI_real32       ((2+0)<<2)
#define CMPI_real64       ((2+1)<<2)

#define CMPI_UINT         ((8)<<4)
#define CMPI_uint8        ((8+0)<<4)
#define CMPI_uint16       ((8+1)<<4)
#define CMPI_uint32       ((8+2)<<4)
#define CMPI_uint64       ((8+3)<<4)
#define CMPI_SINT         ((8+4)<<4)
#define CMPI_sint8        ((8+4)<<4)
#define CMPI_sint16       ((8+5)<<4)
#define CMPI_sint32       ((8+6)<<4)
#define CMPI_sint64       ((8+7)<<4)
#define CMPI_INTEGER      ((CMPI_UINT | CMPI_SINT))

#define CMPI_ENC          ((16)<<8)
#define CMPI_instance     ((16+0)<<8)
#define CMPI_ref          ((16+1)<<8)
#define CMPI_args         ((16+2)<<8)
#define CMPI_class        ((16+3)<<8)
#define CMPI_filter       ((16+4)<<8)
#define CMPI_enumeration  ((16+5)<<8)
#define CMPI_string       ((16+6)<<8)
#define CMPI_chars        ((16+7)<<8)
#define CMPI_dateTime     ((16+8)<<8)
#define CMPI_ptr          ((16+9)<<8)
#define CMPI_charsptr     ((16+10)<<8)

#define CMPI_ARRAY        ((1)<<13)

#define CMPI_SIMPLEA      (CMPI_ARRAY | CMPI_SIMPLE)
#define CMPI_booleanA     (CMPI_ARRAY | CMPI_boolean)
#define CMPI_char16A      (CMPI_ARRAY | CMPI_char16)

#define CMPI_REALA        (CMPI_ARRAY | CMPI_REAL)
#define CMPI_real32A      (CMPI_ARRAY | CMPI_real32)
#define CMPI_real64A      (CMPI_ARRAY | CMPI_real64)

#define CMPI_UINTA        (CMPI_ARRAY | CMPI_UINT)
#define CMPI_uint8A       (CMPI_ARRAY | CMPI_uint8)
#define CMPI_uint16A      (CMPI_ARRAY | CMPI_uint16)
#define CMPI_uint32A      (CMPI_ARRAY | CMPI_uint32)
#define CMPI_uint64A      (CMPI_ARRAY | CMPI_uint64)
#define CMPI_SINTA        (CMPI_ARRAY | CMPI_SINT)
#define CMPI_sint8A       (CMPI_ARRAY | CMPI_sint8)
#define CMPI_sint16A      (CMPI_ARRAY | CMPI_sint16)
#define CMPI_sint32A      (CMPI_ARRAY | CMPI_sint32)
#define CMPI_sint64A      (CMPI_ARRAY | CMPI_sint64)
#define CMPI_INTEGERA     (CMPI_ARRAY | CMPI_INTEGER)

#define CMPI_ENCA         (CMPI_ARRAY | CMPI_ENC)
#define CMPI_stringA      (CMPI_ARRAY | CMPI_string)
#define CMPI_charsA       (CMPI_ARRAY | CMPI_chars)
#define CMPI_dateTimeA    (CMPI_ARRAY | CMPI_dateTime)
#define CMPI_instanceA    (CMPI_ARRAY | CMPI_instance)
#define CMPI_refA         (CMPI_ARRAY | CMPI_ref)
#define CMPI_charsptrA    (CMPI_ARRAY | CMPI_charsptr)

// The following are generic types for key bindings in
// CMPIObjectPath objects, that are used when the
// specific CIM types are not available.

#define CMPI_keyInteger   (CMPI_sint64)
#define CMPI_keyString    (CMPI_string)
#define CMPI_keyBoolean   (CMPI_boolean)
#define CMPI_keyRef       (CMPI_ref)

// The following are predicate types only.

#define CMPI_charString      (CMPI_string)
#define CMPI_integerString   (CMPI_string | CMPI_sint64)
#define CMPI_realString      (CMPI_string | CMPI_real64)
#define CMPI_numericString   (CMPI_string | CMPI_sint64 | CMPI_real64)
#define CMPI_booleanString   (CMPI_string | CMPI_boolean)
#define CMPI_dateTimeString  (CMPI_string | CMPI_dateTime)
#define CMPI_classNameString (CMPI_string | CMPI_class)
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
 * a [CMPIData](@ref type-data) object.
 *
 * Test masks for CMPIValueState are defined
 * [here](@ref def-cmpivaluestate-symbols).
 */
typedef unsigned short CMPIValueState;

/**
 *   @anchor def-cmpivaluestate-symbols
 *   @name Test masks for CMPIValueState
 *   @{
 *
 * They are used on @ref CMPIValueState.
 */
#define CMPI_goodValue (0)    /**< All flags are false */
#define CMPI_nullValue (1<<8) /**< Flag indicating that the data item is NULL */
#define CMPI_keyValue  (2<<8) /**< Flag indicating that the data item is a key
                                   binding */
#define CMPI_notFound  (4<<8) /**< CMPI_notFound has been deprecated in CMPI
                                   2.1; Use the return code to indicate that a
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
     * Type of the data item.
     *
     * Undefined, if the data item is in error as per its state.
     */
    CMPIType type;

    /**
     * State of the data item.
     */
    CMPIValueState state;

    /**
     * Value of the data item.
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
 * @brief An opaque type representing a handle to an open message
 * file.
 */
typedef void* CMPIMsgFileHandle;

/**
 * @}
 * @addtogroup type-gc-stat
 * @{
 */

/**
 * @brief An opaque type that is used by the MB for use with the
 * CMPIBrokerMemFT.mark() and CMPIBrokerMemFT.release() functions.
 */
typedef void CMPIGcStat;

/**
 * @}
 * @addtogroup type-flags
 * @{
 */

/**
 * @brief An integral bitmask type that represents options specified by the
 * WBEM client and passed on to the MI for certain requests.
 *
 * The CMPIFlags value is passed to MIs via the [CMPIContext](@ref _CMPIContext)
 * object, using the context data entry @ref CMPIInvocationFlags.
 *
 * Test masks for CMPIFlags are defined [here](@ref def-cmpiflags-symbols).
 */
typedef unsigned int CMPIFlags;

/**
 *   @anchor def-cmpiflags-symbols
 *   @name Test masks for CMPIFlags
 *   @{
 *
 * They are used on @ref CMPIFlags. For a description of LocalOnly etc., see
 * [DSP0200].
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
 * @brief An integral type for CMPI version fields (mainly in function
 * tables).
 *
 * The values of entities of this type are numeric CMPI version numbers
 * (see @ref sym-version-nnn).
 */
typedef int CMPIVersion;

/**
 * @}
 * @addtogroup def-context-fieldnames
 * @{
 */

/**
 * The entries in a [CMPIContext](@ref _CMPIContext) are set and accessed by name
 * using the the  addEntry() and getEntry() functions.
 *
 * These definitions are the ASCII strings representing these CMPIContext types.
 */
// KS_TODO review the above
/** Namespace for which the MI is started. */
#define CMPIInitNameSpace   "CMPIInitNameSpace"
/** Invocation flags as specified by the WBEM client; see @ref CMPIFlags. */
#define CMPIInvocationFlags "CMPIInvocationFlags"
/** Authenticated ID of the user requesting this MI invocation. */
#define CMPIPrincipal       "CMPIPrincipal"
/** The role assumed by the current authenticated user. */
#define CMPIRole            "CMPIRole"
/** The accept language from the request. */
#define CMPIAcceptLanguage  "CMPIAcceptLanguage"
/** The content language from the request. */
#define CMPIContentLanguage "CMPIContentLanguage"

/**
 * @}
 * @addtogroup type-rc
 * @{
 */

/**
 * @brief An enumeration type that defines CMPI return code values.
 *
 * CMPI return code values are used mainly for the rc member of the
 * [CMPIStatus](@ref type-status) structure, and in rare cases directly in MB
 * functions.
 */
typedef enum _CMPIrc {
    /** Success */
    CMPI_RC_OK = 0,
    /** Generic failure */
    CMPI_RC_ERR_FAILED = 1,
    /** Specified user does not have access to perform the requested action */
    CMPI_RC_ERR_ACCESS_DENIED = 2,
    /** invalid namespace specified */
    CMPI_RC_ERR_INVALID_NAMESPACE = 3,
    /** invalid parameter specified */
    CMPI_RC_ERR_INVALID_PARAMETER = 4,
    /** Invalid class specified */
    CMPI_RC_ERR_INVALID_CLASS = 5,
    /** Item was not found */
    CMPI_RC_ERR_NOT_FOUND = 6,
    /** Operation not supported */
    CMPI_RC_ERR_NOT_SUPPORTED = 7,
    /** Object has child objects */
    CMPI_RC_ERR_CLASS_HAS_CHILDREN = 8,
    /** Object has instances */
    CMPI_RC_ERR_CLASS_HAS_INSTANCES = 9,
    /** Invalid super class specified */
    CMPI_RC_ERR_INVALID_SUPERCLASS = 10,
    /** specified object already exists */
    CMPI_RC_ERR_ALREADY_EXISTS = 11,
    /** Property does not exist */
    CMPI_RC_ERR_NO_SUCH_PROPERTY = 12,
    /** This is a type mismatch */
    CMPI_RC_ERR_TYPE_MISMATCH = 13,
    /** Query language not supported */
    CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED = 14,
    /** Invalid query */
    CMPI_RC_ERR_INVALID_QUERY = 15,
    /** Method is not available */
    CMPI_RC_ERR_METHOD_NOT_AVAILABLE = 16,
    /** Could not find the specified method */
    CMPI_RC_ERR_METHOD_NOT_FOUND = 17,
    /** No more elements */
    CMPI_RC_NO_MORE_ELEMENTS = 18,
    /** Server limits exceeded */
    CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED = 27,
    /** Query feature not supported */
    CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED = 29,

    /* The following return codes are used by cleanup()
       calls only. */

    /** Returned by a MI to indicate that it should not be unloaded, only
     returned via a cleanup() call */
    CMPI_RC_DO_NOT_UNLOAD = 50,
    /** Returned by a MI to indicate that it should never be unloaded, only
     returned via a cleanup() call */
    CMPI_RC_NEVER_UNLOAD = 51,

    /* Internal CMPI return codes. */

    CMPI_RC_ERR_INVALID_HANDLE = 60,
    CMPI_RC_ERR_INVALID_DATA_TYPE = 61,
    CMPI_RC_ERR_NOT_IN_CODEPAGE = 62,

    /* Hosting OS errors. */

    CMPI_RC_ERROR_SYSTEM = 100,
    CMPI_RC_ERROR = 200

} CMPIrc;

/**
 * @}
 * @addtogroup type-status
 * @{
 */

/**
 * @brief A structure that indicates success or failure of MB and MI
 * functions.
 *
 * It is used either as a function return value, or as an output parameter.
 */
typedef struct _CMPIStatus {

    /**
     * A return code, for valid values.
     * @see CMPIrc.
     */
    CMPIrc rc;

    /**
     * An error message, or NULL if no error message is available.
     */
    CMPIString* msg;

} CMPIStatus;

/**
 * @}
 * @addtogroup mb-capabilities
 * @{
 */

/**
 * These definitions are test masks for MB capabilities, for use on the
 * _CMPIBrokerFT::brokerCapabilities member.
 * The test mask for each capability includes any prerequisite capabilities.
 */
#define CMPI_MB_BasicRead                   0x00000001
#define CMPI_MB_BasicWrite                  0x00000003
#define CMPI_MB_InstanceManipulation        0x00000007
#define CMPI_MB_AssociationTraversal        0x00000009
#define CMPI_MB_QueryExecution              0x00000011
#define CMPI_MB_QueryNormalization          0x00000031
#define CMPI_MB_BasicQualifierSupport       0x00000047
#define CMPI_MB_Indications                 0x00000081
#define CMPI_MB_OSEncapsulationSupport      0x00000100

#ifdef CMPI_VER_200
#define CMPI_MB_Supports_MemEnhancements    0x00004000
#define CMPI_MB_Supports_Extended_Error     0x00008000
#endif

#ifdef CMPI_VER_210
#define CMPI_MB_Logging                     0x00010000
#define CMPI_MB_Tracing                     0x00020000
#define CMPI_MB_PropertyFiltering           0x00040001
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
 * queries.
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
 * functions.
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
 * @brief An enumeration defining the normalization type a query
 * expression is normalized to.
 *
 * Deprecated: This enumeration is not part of the CMPI Technical Standard;
 * it is defined for backward compatibility and its use is deprecated.
 *
 * It is defined conditionally, when the CMPI_DEFINE_CMPISelectCondType
 * symbol is defined.
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
 */

/**
 * @brief An enumeration type that defines possible values for the error
 * type in a [CMPIError](@ref _CMPIError) object.
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
    Oversubscription_Error = OversubscriptionError,
    /** Unavailable resource  Deprecated, use
     *  OversubscriptionError instea */
    UnavailableResourceError = 9,
    /** Unsupported operation */
    UnsupportedOperationError = 10
} CMPIErrorType;

/**
 * @}
 * @addtogroup type-error-severity
 */

/**
 * @brief An enumeration type that defines possible values for the
 * error severity in a [CMPIError](@ref _CMPIError) object.
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
 */

/**
 * @brief An enumeration type that defines possible values for
 * the probable cause in a [CMPIError](@ref _CMPIError) object.
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
 * source format in a [CMPIError](@ref _CMPIError) object.
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
 * @brief An enumeration type that identifies a codepage for CMPI
 * codepage support.
 * @version 2.10
 */
typedef enum _CMPICodepageID {
    /** Current system codepage for the MB */
    CMPI_CPID_SYSTEM = 1,
    /** 7-bit US-ASCII as defined in ISO/IEC 646 */
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
