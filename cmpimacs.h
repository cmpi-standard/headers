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
 * @file cmpimacs.h
 * @brief A set of macro functions to ease the use of the various function
 *     tables;
 *
 * MIs that intend to use the macros should include this header.
 *
 * This header file belongs to the Technical Standard: Systems Management:
 * Common Manageability Programming Interface (CMPI) Issue 2 Version 1.
 *
 * This header file is provided as a convenience only. In the case of any
 * discrepancy between the header file and the Technical Standard
 * (incorporating any subsequent Technical Corrigenda), the Technical Standard
 * shall be definitive.
 */

#ifndef _CMPIMACS_H_
#define _CMPIMACS_H_

#include <cmpift.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
  @addtogroup convenience-func
  @{
    The convenience functions in `cmpimacs.h` are a set of macros and inline
    functions that ease the use of the various CMPI function tables. They are
    provided to help the CMPI developer and are NOT required to be used. They
    do, however, make cleaner and more readable code.

    In CMPI 1.0, the CMPI convenience functions were defined as C preprocessor
    macros, which coined the term "CMPI macros".

    Since CMPI 2.0, they are defined as C inline functions wherever possible.
    Only a small number of them is still defined as C preprocessor macros.

    Since CMPI 2.1, those convenience functions that are defined as C inline
    functions can also be generated as C preprocessor macros, if the CMPI user
    defines the symbol @ref sym-inline "CMPI_NO_INLINE".

    The convenience functions are NOT documented in the CMPI standard, just the
    existence of the `cmpimacs.h` header file. However, this online
    documentation includes hyperlinks between the convenience functions and the
    underlying MB functions or other components of CMPI used by the convenience
    functions. Further, it is the CMPI standard developers' goal to minimize
    the changes to the convenience functions in order to maintain compatibility
    between CMPI versions.

    The convenience functions can be broken down into the following groups:

    @li @parblock
      Convenience functions for MB functions in broker function tables.

      The use of these convenience functions simplifies the code, largely by
      bypassing the added step of getting from the CMPIBroker structure to the
      right one of its function tables and to the corresponding MB function.

      These convenience functions have the same set of arguments as the
      corresponding MB functions. They have a simplified description of their
      functionality and arguments. For a full description, the linked
      description of the corresponding MB functions and arguments may need to
      be consulted.

      For example, the following MB function call:
      @code
      _broker->bft->attachThread(_broker, ctx);
      @endcode
      is simplified when using a convenience function to:
      @code
      CBAttachThread(_broker, ctx);
      @endcode

      For a list of those convenience functions, see @ref convenience-func-broker
      "MB Functions in Broker Function Tables".
    @endparblock
    @li @parblock
      Convenience functions for MB functions of encapsulated data type objects.

      The use of these convenience functions simplifies the code, largely by
      bypassing the added step of getting from the encapsulated data type
      object to its function table and to the corresponding MB function.

      These convenience functions have the same set of arguments as the
      corresponding MB functions. They have a simplified description of their
      functionality and arguments. For a full description, the linked
      description of the corresponding MB functions and arguments may need to
      be consulted.

      For example, the following MB function call:
      @code
      inst->ft->getProperty(inst, name, rc);
      @endcode
      is simplified when using a convenience function to:
      @code
      CMGetProperty(inst, name, rc);
      @endcode

      For a list of those convenience functions, see @ref convenience-func-edt
      "MB Functions of Encapsulated Data Types".
    @endparblock
    @li @parblock
      Helper Functions and Macros

      The helper functions and macros encapsulate the access to selected
      structure members or otherwise provide functionality that is not directly
      available through an MB function.
      Examples of this are CMReturn() and CMIsNullObject().
      For details, see @ref convenience-func-helper
      "Helper Functions and Macros".
    @endparblock
    @li @parblock
      MI Factory Stubs

      The MI factory stubs are macros that generate the MI factory functions
      and function tables.
      Examples of this are CMInstanceMIStub() and CMInstanceMIFactory().
      For details, see @ref convenience-func-mi-factory-stubs
      "MI Factory Stubs".
    @endparblock
  @}
*/

/**
  @addtogroup sym-inline
  @{
    @brief Symbols controlling the definition of convenience functions.

    These symbols control whether the convenience functions are defined as
    static inline functions (when CMPI_INLINE is defined) or as preprocessor
    macros (when CMPI_NO_INLINE is defined).

    A user of the CMPI header files may define either CMPI_INLINE or
    CMPI_NO_INLINE. The default assumed by the CMPI header files is
    CMPI_INLINE.
  @}
*/

#if !defined(CMPI_INLINE) && !defined(CMPI_NO_INLINE)
#  define CMPI_INLINE // if none is defined, set the default
#endif
#if defined(CMPI_INLINE) && defined(CMPI_NO_INLINE)
#  error "Only one of CMPI_INLINE and CMPI_NO_INLINE may be defined."
#endif

/**
  @addtogroup convenience-func-helper
  @{
    Helper Functions and Macros.

    The helper functions and macros encapsulate the access to selected
    structure members or otherwise provide functionality that is not directly
    available through an MB function.
*/

/**
    @brief Initialize a CMPIStatus structure with a return code and no message.

    CMSetStatus() initializes a CMPIStatus structure with a return code and no
    message.

    @param st If not NULL, points to the CMPIStatus structure that is being
        intialized.
    @param rc A @ref CMPIrc value specifying the return code.
    @return Nothing.
    @examples
    @code (.c)
    CMPIStatus st = { CMPI_RC_OK, NULL };
    if (....) // something bad happened
    {
        CMSetStatus(&st, CMPI_RC_ERR_NOT_SUPPORTED);
        return st;
    }
    @endcode
    @see CMPIStatus
    @statusopenpegasus Not tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetStatus(st, rc_) \
do \
{ \
    if (st) \
    { \
        (st)->rc = (rc_); \
        (st)->msg = NULL; \
    } \
} while (0)
#else
static inline void CMSetStatus(
    CMPIStatus *st,
    CMPIrc rc)
{
    if (st)
    {
        st->rc = rc;
        st->msg = NULL;
    }
}
#endif

/** @brief Initializes a CMPIStatus object with CMPIStatus and message.

    CMSetStatusWithString() initialized the CMPIStatus object @p st with
    CMPIStatus @p rc and message text defined by @p msg

    @param st Points to target CMPIStatus object.
    @param rc A @ref CMPIrc value specifying the return code.
    @param msg CMPIString containing message text to be
                  inserted into @p st.
    @see CMPIStatus
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetStatusWithString(st, rc_, msg_) \
do \
{ \
    if (st) \
    { \
        (st)->rc = (rc_); \
        (st)->msg = (msg_); \
    } \
} while (0)
#else
static inline void CMSetStatusWithString(
    CMPIStatus *st,
    CMPIrc rc,
    CMPIString *msg)
{
    if (st)
    {
        st->rc = rc;
        st->msg = msg;
    }
}
#endif

/** @brief Initializes CMPIStatus struct with return code and message text
        message.

    CMSetStatusWithChars() initializes a CMPIStatus structure with @p rcp and
    either a null msg or a new CMPIString object created from @p msg if @p msg
    is not NULL.

    @param mb CMPIBroker structure.
    @param st Points to CMPIStatus object.
    @param rc A @ref CMPIrc value specifying the return code.
    @param msg C string character string containing the message
               text or NULL if no text is to be added to the
               CMPIStatus @p st.
    @examples
    @code (.c)
    static CMPIBroker *_broker; // Cany be populated with stub macro
    . . .
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMSetStatusWithChars (_broker, &rc,
        CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED");
    @endcode
    @see CMPIStatus
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetStatusWithChars(mb, st, rc_, msg_) \
do \
{ \
    if (st) \
    { \
        (st)->rc = (rc_); \
        if (mb) \
            (st)->msg = (mb)->eft->newString((mb), (msg_), NULL); \
        else \
            (st)->msg = NULL; \
    } \
} while (0)
#else
static inline void CMSetStatusWithChars(
    const CMPIBroker *mb,
    CMPIStatus *st,
    CMPIrc rc,
    const char *msg)
{
    if (st)
    {
        st->rc = rc;
        if (mb)
        {
            st->msg = mb->eft->newString(mb, msg, NULL);
        }
        else
        {
            st->msg = NULL;
        }
    }
}
#endif

/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and no message.

    The CMReturn() macro builds a CMPIStatus object specifying a return code
    and no message and exits the function in which it was called, causing it
    to return that CMPIStatus object. CMReturn() can only be used in functions
    that return CMPIStatus.

    @param rc A @ref CMPIrc value specifying the return code.
    @return This macro never returns to its caller; it contains a `return`
        statement and therefore exits the function from which it was called.
    @examples
    Example of enumerateInstanceNames() MI function that returns CMPI_RC_OK to
    the MB.
    @code (.c)
    CMPIStatus testEnumInstanceNames (CMPIInstanceMI *mi,
        const CMPIContext *ctx, const CMPIResult *rslt,
        const CMPIObjectPath *classPath)
    {
        // .... code to return instance names
        CMReturn(CMPI_RC_OK);
    }
    @endcode
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMReturn(rc) \
do \
{ \
    CMPIStatus stat; \
    CMSetStatus(&stat, rc); \
    return stat; \
} while (0)

/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and a message (from CMPIString object).

    The CMReturnWithString() macro builds a CMPIStatus object specifying a
    return code and a message and exits the function in which it was executed,
    causing it to return that CMPIStatus object. CMReturnWithString() can only
    be used in functions that return CMPIStatus.

    @param rc A @ref CMPIrc value specifying the return code.
    @param str Points to a CMPIString object specifying the message.
    @return This macro never returns to its caller; it contains a `return`
        statement and therefore exits the function from which it was called.
    @examples
    Example of code in an MI function that checks for an optional MB capability
    and returns with an error to the MB if the capability is not available.
    @code (.c)
    static const CMPIBroker * _broker;
    // ...
    if (_broker->brokerCapabilities & CMPI_MB_PropertyFiltering)
    {
        // ...
    }
    else
    {
        CMReturnWithString(CMPI_RC_ERR_NOT_SUPPORTED,
            CMNewString(_broker, "Property Filtering capability not available",
                NULL));
    }
    @endcode
    @see CMPIStatus
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMReturnWithString(rc, str) \
do \
{ \
    CMPIStatus stat; \
    CMSetStatusWithString(&stat, rc, str); \
    return stat; \
} while (0)

/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and a message (from C string).

    The CMReturnWithChars() macro builds a CMPIStatus object specifying a
    return code and a message and exits the function in which it was executed,
    causing it to return that CMPIStatus object. CMReturnWithChars() can only
    be used in functions that return CMPIStatus.

    @param mb CMPIBroker structure.
    @param rc A @ref CMPIrc value specifying the return code.
    @param chars A C string (`char*`) specifying the message.
    @return This macro never returns to its caller; it contains a `return`
        statement and therefore exits the function from which it was called.
    @examples
    Example of code in a modifyInstance() MI function that is not implemented
    and returns to the MB with CMPI_RC_ERR_NOT_SUPPORTED and an according error
    message.
    @code (.c)
    static const CMPIBroker * _broker;
    // ...
    CMPIStatus testModifyInstance (...)
    {
        CMReturnWithChars(_broker, CMPI_RC_ERR_NOT_SUPPORTED,
            "ModifyInstance is not supported");
    }
    @endcode
    @see CMPIStatus
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMReturnWithChars(mb, rc, chars) \
do \
{ \
    CMPIStatus stat; \
    CMSetStatusWithChars(mb, &stat, rc, chars); \
    return stat; \
} while (0)

/** @brief Test an encapsulated data type object pointer for NULL.

    This test is suitable for checking any pointers to encapsulated data type
    objects for NULL, including the pointers returned by their factory
    functions.
    @param objptr Pointer to the encapsulated data type object to be tested.
        This argument is defined as `void*` to encompass any encapsulated data
        type object.
    @retval true The object is NULL.
    @retval false The object is NOT NULL.
    @examples
    @code (.c)
    cop = CMNewObjectPath(_broker, "root/SampleProvider", _ClassName, &rc);
    CMAddKey(cop2, "Identifier", (CMPIValue *)&value1, CMPI_uint8);
    // test for NULL before creating instance from cop
    if (!CMIsNullObject(cop))
    {
        instance2 = CMNewInstance(_broker, cop2, &rc);
        ...
    }
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS The example seems to be somewhat confused. Why is a test
        of cop meaningful when it is not used at all, and cop2 is used
        instead?@n
        Karl to review the example.
*/
#ifdef CMPI_NO_INLINE
#define CMIsNullObject(objptr) \
    ((objptr) == NULL)
#else
static inline CMPIBoolean CMIsNullObject(
    const void *objptr)
{
    return objptr == NULL;
}
#endif

/** @brief Test a CMPIData value for NULL.

    CMIsNullValue() tests a CMPIData value for NULL.
    This is done based on the @ref CMPI_nullValue flag in its @p state member.
    @param data The CMPIData value to be tested.
    @retval true The CMPIData value is NULL.
    @retval false The CMPIData value is not NULL.
    @examples
    Process received method call that includes a CIMObject path @p ref for
    classname, method name, arguments, argument name and value in the argument
    @code (.c)
    CMPIStatus *rc;
    className = CMGetClassName(ref, &rc);
    name = CMGetCharsPtr(className, &rc);
    if (!strcmp(name, _ClassName))
    {
        if (!strcmp ("SayHello", methodName))
        {
            // gets the number of arguments contained in "in" Args.
            if (CMGetArgCount(in, &rc) > 0)
            {
                // gets Name argument value
                data = CMGetArg(in, "MethodName", &rc);
                // should we check rc on response.
                // check for data type and !null value of
                // argument value rcvd
                if (data.type == CMPI_string && !(CMIsNullValue(data)))
                {
                    strCat = CMGetCharsPtr(data.value.string, &rc);
                    strcat(result, strCat);
                    strcat(result, "!");
                    // create the new string to return to client
                    str1 = CMNewString(_broker, result, &rc);
                    val1.string = str1;
                }
            . . .
    @endcode
    @see CMPIData, CMPIValueState
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS The example is way too complex if it just intends to show
        how to use this function.@n
        Karl to come up with simpler example.
*/
#ifdef CMPI_NO_INLINE
#define CMIsNullValue(data) \
    (((data).state & CMPI_nullValue) != 0)
#else
static inline CMPIBoolean CMIsNullValue(
    CMPIData data)
{
    return (data.state & CMPI_nullValue) != 0;
}
#endif

/** @brief Test a CMPIData value for being a key.

    CMIsKeyValue() tests a CMPIData value for being a key.
    This is done based on the @ref CMPI_keyValue flag in its @p state member.
    @param data The CMPIData value to be tested.
    @retval true The CMPIData value is a key.
    @retval false The CMPIData value is not a key.
    @see CMPIData, CMPIValueState
    @statusopenpegasus Not tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMIsKeyValue(data) \
    (((data).state & CMPI_keyValue) != 0)
#else
static inline CMPIBoolean CMIsKeyValue(
    CMPIData data)
{
    return (data.state & CMPI_keyValue) != 0;
}
#endif

/** @brief Test a CMPIData value for having an array type.

    CMIsArray() tests a CMPIData value for having an array type.
    This is done based on the @ref CMPI_ARRAY flag in its @p type member.
    @param data The CMPIData value to be tested.
    @retval true The CMPIData value has array type.
    @retval false The CMPIData value does not have array type.
    @see CMPIData, CMPIType
    @statusopenpegasus Not tested
    @hideinitializer

    @todo TODO_KS This needs an example.
*/
#ifdef CMPI_NO_INLINE
#define CMIsArray(data) \
    (((data).type & CMPI_ARRAY) != 0)
#else
static inline CMPIBoolean CMIsArray(
    CMPIData data)
{
    return (data.type & CMPI_ARRAY) != 0;
}
#endif

/**
  @}
  @addtogroup convenience-func-edt
  @{
    MB Functions of Encapsulated Data Types.

    The convenience functions in this group call functions on encapsulated data
    type objects.

    The factory functions creating encapsulated data type objects are covered
    in @ref convenience-func-broker "MB Functions in Broker Function Tables".

    They simplify the code by eliminating the references to function tables.
*/

/**
    @brief Release an encapsulated data type object.

    CMRelease() releases an encapsulated data type object, by calling the
    release() function in the function table of the object.

    This indicates to the MB that the object (including any objects it
    contains) will no longer be used by the MI. The MB may free the resources
    associated with the object during the call to this function, or later
    during some garbage collection cycle.

    @param obj Points to the encapsulated data type object to be released.
    @return CMPIStatus structure indicating the function return status.
    @errors
    The function return status will indicate one of the following @ref CMPIrc
    codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid.
    @fulldescription CMPIContextFT.release(),
        CMPIResultFT.release(),
        CMPIStringFT.release(),
        CMPIArrayFT.release(),
        CMPIEnumerationFT.release(),
        CMPIInstanceFT.release(),
        CMPIObjectPathFT.release(),
        CMPIArgsFT.release(),
        CMPIDateTimeFT.release(),
        CMPISelectExpFT.release(),
        CMPISelectCondFT.release(),
        CMPISubCondFT.release(),
        CMPIPredicateFT.release(),
        CMPIErrorFT.release(),
        CMPIPropertyListFT.release(),
        CMPIEnumerationFilterFT.release()
    @examples
    Code to clean up after attempting to create an instance:
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPISelectExp *se_def = NULL;
    clone = CMClone(se_def, &rc);
    // . . . test @rc for good completion and use clone if
    CMRelease(clone);
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo TBD Review fulldescription and convfunction special commands.
*/
#define CMRelease(obj) \
    ((obj)->ft->release((obj)))

/** @brief Clone an encapsulated data type object.

    CMClone() clones an encapsulated data type object, by calling the
    clone() function in the function table of the object.

    @param obj Points to the encapsulated data type object to be cloned.
    @param [out] rc Function return status (suppressed when NULL).
    @return @parblock If successful, returns a pointer to the
        copied clone of the object defined by @p obj.

        The returned object shall be explicitly released by the MI using its
        release() function, or the CMRelease() macro.

        If not successful, returns NULL.
    @endparblock
    @errors
    The following @ref CMPIrc codes shall be recognized:
    @li `CMPI_RC_OK` Operation successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` The @p ef handle is invalid.
    @fulldescription CMPIContextFT.clone(),
        CMPIResultFT.clone(),
        CMPIStringFT.clone(),
        CMPIArrayFT.clone(),
        CMPIEnumerationFT.clone(),
        CMPIInstanceFT.clone(),
        CMPIObjectPathFT.clone(),
        CMPIArgsFT.clone(),
        CMPIDateTimeFT.clone(),
        CMPISelectExpFT.clone(),
        CMPISelectCondFT.clone(),
        CMPISubCondFT.clone(),
        CMPIPredicateFT.clone(),
        CMPIErrorFT.clone(),
        CMPIPropertyListFT.clone(),
        CMPIEnumerationFilterFT.clone()
    @examples
    Clone an instance to add to an array:
    @code (.c)
    // preexisting instance CMPIInstance *ci)
    {
        CMPIStatus rc = { CMPI_RC_OK, NULL };
        CMPIInstance *inst;
        if (ci)
        {
            // clone the instance to be added to the array
            inst = CMClone(ci, &rc);
            . . .
        }
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo KS test if we need brief in this and release doc
*/
#define CMClone(obj, rc) \
    ((obj)->ft->clone((obj), (rc)))


/**
  @}
  @addtogroup convenience-func-edt-context
  @{
*/

/** @brief Get a context entry in a CMPIContext object by name.

    @param ctx CMPIContext object.
    @param name Name of the context entry. See @ref
        def-context-fieldnames "Names of CMPIContext fields" for defined names.
    @param [out] rc Function return status (suppressed when NULL).
    @return Context entry value and type.
    @fulldescription CMPIContextFT.getEntry()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetContextEntry(ctx, name, rc)  \
    ((ctx)->ft->getEntry((ctx), (name), (rc)))
#else
static inline CMPIData CMGetContextEntry(
    const CMPIContext *ctx,
    const char *name,
    CMPIStatus *rc)
{
    return ctx->ft->getEntry(ctx, name, rc);
}
#endif

/** @brief Get a context entry in a CMPIContext object by index.

    @param ctx CMPIContext object.
    @param index Zero-based position of the context entry in the
         internal data array. The order of context entries in the internal data
         array is implementation-defined.
    @param [out] name Name of the returned context entry (suppressed when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return Context entry value and type.
    @fulldescription CMPIContextFT.getEntryAt()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetContextEntryAt(ctx, index, name, rc) \
    ((ctx)->ft->getEntryAt((ctx), (index), (name), (rc)))
#else
static inline CMPIData CMGetContextEntryAt(
    const CMPIContext *ctx,
    CMPICount index,
    CMPIString **name,
    CMPIStatus *rc)
{
    return ctx->ft->getEntryAt(ctx, index, name, rc);
}
#endif

/** @brief Get the number of context entries in a CMPIContext object.

    @param ctx CMPIContext object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of entries in the CMPIContext object.
    @fulldescription CMPIContextFT.getEntryCount()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetContextEntryCount(ctx, rc) \
    ((ctx)->ft->getEntryCount((ctx), (rc)))
#else
static inline CMPICount CMGetContextEntryCount(
    const CMPIContext *ctx,
    CMPIStatus *rc)
{
    return ctx->ft->getEntryCount(ctx, rc);
}
#endif

/** @brief Add or replace a context entry in a CMPIContext object.

    @param ctx CMPIContext object.
    @param name Name of the context entry.
        See @ref def-context-fieldnames "Names of CMPIContext fields" for
        defined names.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIContextFT.addEntry()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMAddContextEntry(ctx, name, value, type) \
    ((ctx)->ft->addEntry((ctx), (name), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMAddContextEntry(
    const CMPIContext *ctx,
    const char *name,
    const CMPIValue *value,
    const CMPIType type)
{
    return ctx->ft->addEntry(ctx, name, value, type);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-result
  @{
*/

/** @brief Add a value/type pair to a CMPIResult object.

    @param rslt CMPIResult object.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIResultFT.returnData()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMReturnData(rslt, value, type) \
    ((rslt)->ft->returnData((rslt), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMReturnData(
    const CMPIResult *rslt,
    const CMPIValue *value,
    const CMPIType type)
{
    return rslt->ft->returnData(rslt, value, type);
}
#endif

/** @brief Add an instance to a CMPIResult object.

    @param rslt CMPIResult object.
    @param inst Instance to be returned.
    @return Function return status.
    @fulldescription CMPIResultFT.returnInstance()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMReturnInstance(rslt, inst) \
    ((rslt)->ft->returnInstance((rslt), (inst)))
#else
static inline CMPIStatus CMReturnInstance(
    const CMPIResult *rslt,
    const CMPIInstance *inst)
{
    return rslt->ft->returnInstance(rslt, inst);
}
#endif

/** @brief Add an object path to a CMPIResult object.

    @param rslt CMPIResult object.
    @param op Object path to be returned.
    @return Function return status.
    @fulldescription CMPIResultFT.returnObjectPath()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMReturnObjectPath(rslt, op) \
    ((rslt)->ft->returnObjectPath((rslt), (op)))
#else
static inline CMPIStatus CMReturnObjectPath(
    const CMPIResult *rslt,
    const CMPIObjectPath *op)
{
    return rslt->ft->returnObjectPath(rslt, op);
}
#endif

/** @brief Indicate that no further items will be added to a CMPIResult object.

    @param rslt CMPIResult object.
    @return Function return status.
    @fulldescription CMPIResultFT.returnDone()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMReturnDone(rslt) \
    ((rslt)->ft->returnDone((rslt)))
#else
static inline CMPIStatus CMReturnDone(
    const CMPIResult *rslt)
{
    return rslt->ft->returnDone(rslt);
}
#endif

#ifdef CMPI_VER_200
/** @brief Add an error to a CMPIResult object.

    @param rslt CMPIResult object.
    @param er Error to be returned.
    @return Function return status.
    @fulldescription CMPIResultFT.returnError()
    @added200
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMReturnError(rslt, er) \
    ((rslt)->ft->returnError((rslt), (er)))
#else
static inline CMPIStatus CMReturnError(
    const CMPIResult *rslt,
    const CMPIError *er)
{
    return rslt->ft->returnError(rslt, er);
}
#endif
#endif /* CMPI_VER_200 */


/**
  @}
  @addtogroup convenience-func-edt-string
  @{
*/

/** @brief Get the C-language string representation of a CMPIString object
        (**Deprecated**).

    @param str CMPIString object.
    @return C-language string representation of the CMPIString object.
    @fulldescription CMPIStringFT.getCharPtr()
    @examples
    @code (.c)
    myObjPath = CMNewObjectPath(
        _broker,
        CMGetCharPtr(CMGetNameSpace(ref,0)),
        "TestCMPI_KeyReturned",
        0);
    @endcode
    @deprecated This macro is deprecated since CMPI 2.1, because it does not
        provide argument checking or a return code. Use CMGetCharsPtr(),
        instead.

    @see CMGetCharsPtr()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetCharPtr(str) \
    ((str)->ft->getCharPtr((str), NULL))
#else
static inline const char * CMGetCharPtr(
    const CMPIString *str)
{
    return str->ft->getCharPtr(str, NULL);
}
#endif

/** @brief Get a C-language string representation of a CMPIString object.

    @param str CMPIString object.
    @param [out] rc Function return status (suppressed when NULL).
    @return C-language string representation of the CMPIString object.
    @fulldescription CMPIStringFT.getCharPtr()
    @examples
    @code (.c)
    CMPIObjectPath *op = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    objPath = CMNewObjectPath (_broker,
        CMGetCharsPtr(CMGetNameSpace(ref, &rc), NULL),
        class,
        &rc);
    @endcode
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetCharsPtr(str, rc) \
    ((str)->ft->getCharPtr((str), (rc)))
#else
static inline const char * CMGetCharsPtr(
    const CMPIString *str,
    CMPIStatus *rc)
{
    return str->ft->getCharPtr(str, rc);
}
#endif

#ifdef CMPI_VER_210
/** @brief Create a C-language string that has converted a CMPIString
        object into a specific codepage.

    @param str CMPIString object.
    @param cpid CMPI-specific codepage ID for the codepage to convert to.
        See @ref CMPICodepageID for a list of supported codepages and their
        codepage ID values.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new C-language string will be returned, in the codepage specified
        in @p cpid.
    @fulldescription CMPIStringFT.newCharsCP()
    @examples
    @code (.c)
    CMPIString *str; // set up elsewhere
    char *chars;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    chars = CMNewCharsCP(str, CMPI_CPID_SYSTEM, &rc);
    @endcode
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewCharsCP(str, cpid, rc) \
    ((str)->ft->newCharsCP((str), (cpid), (rc)))
#else
static inline char * CMNewCharsCP(
    const CMPIString *str,
    const CMPICodepageID cpid,
    CMPIStatus *rc)
{
    return str->ft->newCharsCP(str, cpid, rc);
}
#endif
#endif /* CMPI_VER_210 */


/**
  @}
  @addtogroup convenience-func-edt-array
  @{
*/

/** @brief Get the number of array elements in a CMPIArray object.

    @param ar CMPIArray object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of aray elements.
    @fulldescription CMPIArrayFT.getSize() (function name is different, but
        arguments and return value are the same)
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArrayCount(ar, rc) \
    ((ar)->ft->getSize((ar), (rc)))
#else
static inline CMPICount CMGetArrayCount(
    const CMPIArray *ar,
    CMPIStatus *rc)
{
    return ar->ft->getSize(ar, rc);
}
#endif

/** @brief Get the type of the array elements in a CMPIArray object.

    @param ar CMPIArray object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Type of the array elements.
    @fulldescription CMPIArrayFT.getSimpleType() (function name is different,
        but arguments and return value are the same)
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArrayType(ar, rc) \
    ((ar)->ft->getSimpleType((ar), (rc)))
#else
static inline CMPIType CMGetArrayType(
    const CMPIArray *ar,
    CMPIStatus *rc)
{
    return ar->ft->getSimpleType(ar, rc);
}
#endif

/** @brief Get an array element in a CMPIArray object by index.

    @param ar CMPIArray object.
    @param index Zero-based position of the array element in the CMPIArray.
    @param [out] rc Function return status (suppressed when NULL).
    @return Array element value and type.
    @fulldescription CMPIArrayFT.getElementAt()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArrayElementAt(ar, index, rc) \
    ((ar)->ft->getElementAt((ar), (index), (rc)))
#else
static inline CMPIData CMGetArrayElementAt(
    const CMPIArray *ar,
    CMPICount index,
    CMPIStatus *rc)
{
    return ar->ft->getElementAt(ar, index, rc);
}
#endif

/** @brief Set the value of an existing array element in a CMPIArray object by
        index.

    @param ar CMPIArray object.
    @param index Zero-based position of the existing element in the
        CMPIArray object.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIArrayFT.setElementAt()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetArrayElementAt(ar, index, value, type) \
    ((ar)->ft->setElementAt((ar), (index), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMSetArrayElementAt(
    const CMPIArray *ar,
    CMPICount index,
    const CMPIValue *value,
    CMPIType type)
{
    return ar->ft->setElementAt(ar, index, value, type);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-enumeration
  @{
*/

/** @brief Get the next element in a CMPIEnumeration object.

    @param en CMPIEnumeration object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Element value and type.
    @fulldescription CMPIEnumerationFT.getNext()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetNext(en, rc) \
    ((en)->ft->getNext((en), (rc)))
#else
static inline CMPIData CMGetNext(
    const CMPIEnumeration *en,
    CMPIStatus *rc)
{
    return en->ft->getNext(en, rc);
}
#endif

/** @brief Test for any elements left in a CMPIEnumeration object.

    @param en CMPIEnumeration object.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The enumeration has more elements left.
    @retval false The enumeration has no more elements left.
    @fulldescription CMPIArrayFT.hasNext()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMHasNext(en, rc) \
    ((en)->ft->hasNext((en), (rc)))
#else
static inline CMPIBoolean CMHasNext(
    const CMPIEnumeration *en,
    CMPIStatus *rc)
{
    return en->ft->hasNext(en, rc);
}
#endif

/** @brief Convert a CMPIEnumeration object to a CMPIArray object.

    @param en CMPIEnumeration object.
    @param [out] rc Function return status (suppressed when NULL).
    @return CMPIArray object containing the elements from the CMPIEnumeration
        object.
    @fulldescription CMPIEnumerationFT.toArray()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMToArray(en, rc) \
    ((en)->ft->toArray((en), (rc)))
#else
static inline CMPIArray *CMToArray(
    const CMPIEnumeration *en,
    CMPIStatus *rc)
{
    return en->ft->toArray(en, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-instance
  @{
*/

/** @brief Get a property in a CMPIInstance object by name.

    @param inst CMPIInstance object.
    @param name Name of the property.
    @param [out] rc Function return status (suppressed when NULL).
    @return Property value and type.
    @fulldescription CMPIInstanceFT.getProperty()
    @examples
    @code (.c)
    CMPIInstance *inst = NULL;
    // . . . make the inst
    CMPIData rtnData;
    const char* name1 = "propertyName";
    rtnData = CMGetProperty(inst, name1, &rc);
    assert(rtnData.state != CMPI_badValue);
    @endcode
    @statusopenpegasus Used and tested extensively
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetProperty(inst, name, rc) \
    ((inst)->ft->getProperty((inst), (name), (rc)))
#else
static inline CMPIData CMGetProperty(
    const CMPIInstance *inst,
    const char *name,
    CMPIStatus *rc)
{
    return inst->ft->getProperty(inst, name, rc);
}
#endif

/** @brief Get a property in a CMPIInstance object by index.

    @param inst CMPIInstance object.
    @param index Zero-based position of the property in the internal data
         array.
    @param [out] name Name of the returned property (suppressed when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return Property value and type.
    @fulldescription CMPIInstanceFT.getPropertyAt()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPropertyAt(inst, index, name, rc) \
    ((inst)->ft->getPropertyAt((inst), (index), (name), (rc)))
#else
static inline CMPIData CMGetPropertyAt(
    const CMPIInstance *inst,
    CMPICount index,
    CMPIString **name,
    CMPIStatus *rc)
{
    return inst->ft->getPropertyAt(inst, index, name, rc);
}
#endif

/** @brief Get the number of properties in a CMPIInstance  object.

    @param inst CMPIInstance object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of properties in the instance.
    @fulldescription CMPIInstanceFT.getPropertyCount()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPropertyCount(inst, rc) \
    ((inst)->ft->getPropertyCount((inst), (rc)))
#else
static inline CMPICount CMGetPropertyCount(
    const CMPIInstance *inst,
    CMPIStatus *rc)
{
    return inst->ft->getPropertyCount(inst, rc);
}
#endif

/** @brief Add or replace a property value in a CMPIInstance object by name.

    @param inst CMPIInstance object.
    @param name Name of the property.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIInstanceFT.setProperty()
    @statusopenpegasus Used and tested extensively
    @hideinitializer

    @todo TODO_KS AM: Why do we have the `(CMPIValue *)` cast in the macro
        version?@n
        We agreed that the cast should be removed because it hides type
        errors and has no apparent value.@n
        Karl to test this against all of OpenPegasus providers.
*/
#ifdef CMPI_NO_INLINE
#define CMSetProperty(inst, name, value, type) \
    ((inst)->ft->setProperty((inst), (name), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMSetProperty(
    const CMPIInstance *inst,
    const char *name,
    const CMPIValue *value,
    const CMPIType type)
{
    return inst->ft->setProperty(inst, name, value, type);
}
#endif

/** @brief Get the instance path component of a CMPIInstance object.

    @param inst CMPIInstance object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Instance path component of the CMPIInstance object.
    @fulldescription CMPIInstanceFT.getObjectPath()
    @statusopenpegasus Used and tested extensively in cmpiTestMethodProvider.c
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetObjectPath(inst, rc) \
    ((inst)->ft->getObjectPath((inst), (rc)))
#else
static inline CMPIObjectPath *CMGetObjectPath(
    const CMPIInstance *inst,
    CMPIStatus *rc)
{
    return inst->ft->getObjectPath(inst, rc);
}
#endif

/** @brief Attach a property filter to a CMPIInstance object.

    @param inst CMPIInstance object.
    @param properties If not NULL, the members of the array define one
        or more property names to be accepted by subsequent setProperty()
        function calls.
    @param keyList Deprecated, ignored by MB, maintained here for compatibility.
    @return Function return status.
    @fulldescription CMPIInstanceFT.setPropertyFilter()
    @statusopenpegasus Not used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetPropertyFilter(inst, properties, keyList) \
    ((inst)->ft->setPropertyFilter((inst), (properties), (keyList)))
#else
static inline CMPIStatus CMSetPropertyFilter(
    const CMPIInstance *inst,
    const char **properties,
    const char **keyList)
{
    return inst->ft->setPropertyFilter(inst, properties, keyList);
}
#endif

/** @brief Set the instance path component of a CMPIInstance object.

    @param inst CMPIInstance object.
    @param op New instance path.
    @return Function return status.
    @fulldescription CMPIInstanceFT.setObjectPath()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetObjectPath(inst, op) \
    ((inst)->ft->setObjectPath((inst), (op)))
#else
static inline CMPIStatus CMSetObjectPath(
    const CMPIInstance *inst,
    const CMPIObjectPath *op)
{
    return inst->ft->setObjectPath(inst, op);
}
#endif

#ifdef CMPI_VER_200
/** @brief Add or replace a property value and class origin in a CMPIInstance
         object by name.

    @param inst CMPIInstance object.
    @param name Name of the property.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @param origin Class origin of the property. If NULL, no class origin is
        attached to the property.
    @return Function return status.
    @fulldescription CMPIInstanceFT.setPropertyWithOrigin()
    @added200
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetPropertyWithOrigin(inst, name, value, type, origin) \
    ((inst)->ft->setPropertyWithOrigin((inst), (name), (CMPIValue *)(value), \
                                       (type), (origin)))
#else
static inline CMPIStatus CMSetPropertyWithOrigin(
    const CMPIInstance *inst,
    const char *name,
    const CMPIValue *value,
    CMPIType type,
    const char *origin)
{
    return inst->ft->setPropertyWithOrigin(inst, name, value, type, origin);
}
#endif
#endif /* CMPI_VER_200 */


/**
  @}
  @addtogroup convenience-func-edt-objectpath
  @{
*/

/** @brief Set the namespace component in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param ns New namespace name.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.setNameSpace()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetNameSpace(op, ns) \
    ((op)->ft->setNameSpace((op), (ns)))
#else
static inline CMPIStatus CMSetNameSpace(
    const CMPIObjectPath *op,
    const char *ns)
{
    return op->ft->setNameSpace(op, ns);
}
#endif

/** @brief Get the namespace component from a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Namespace name.
    @fulldescription CMPIObjectPathFT.getNameSpace()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetNameSpace(op, rc) \
    ((op)->ft->getNameSpace((op), (rc)))
#else
static inline CMPIString *CMGetNameSpace(
    const CMPIObjectPath *op,
    CMPIStatus *rc)
{
    return op->ft->getNameSpace(op, rc);
}
#endif

/** @brief Set the host name component in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param hn New host name.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.setHostname()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetHostname(op, hn) \
    ((op)->ft->setHostname((op), (hn)))
#else
static inline CMPIStatus CMSetHostname (
    const CMPIObjectPath *op,
    const char *hn)
{
    return op->ft->setHostname(op, hn);
}
#endif

/** @brief Get the host name component in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Host name.
    @fulldescription CMPIObjectPathFT.getHostname()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetHostname(op, rc) \
    ((op)->ft->getHostname((op), (rc)))
#else
static inline CMPIString *CMGetHostname(
    const CMPIObjectPath *op,
    CMPIStatus *rc)
{
    return op->ft->getHostname(op, rc);
}
#endif

/** @brief Set class name component in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param cn New class name.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.setClassName()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetClassName(op, cn) \
    ((op)->ft->setClassName((op), (cn)))
#else
static inline CMPIStatus CMSetClassName(
    const CMPIObjectPath *op,
    const char *cn)
{
    return op->ft->setClassName(op, cn);
}
#endif

/** @brief Get the class name component from CMPIObjectPath.

    @param op CMPIObjectPath object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Class name.
    @fulldescription CMPIObjectPathFT.getClassName()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetClassName(op, rc) \
    ((op)->ft->getClassName((op), (rc)))
#else
static inline CMPIString *CMGetClassName(
    const CMPIObjectPath *op,
    CMPIStatus *rc)
{
    return op->ft->getClassName(op, rc);
}
#endif

/** @brief Add or replace a key binding in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param key Name of the key binding.
    @param value CMPIValue structure containing the value to be
         assigned to the key binding. Key bindings are not permitted to be NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.addKey()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMAddKey(op,key,value,type) \
    ((op)->ft->addKey((op), (key), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMAddKey(
    const CMPIObjectPath *op,
    const char *key,
    const CMPIValue *value,
    const CMPIType type)
{
    return op->ft->addKey(op, key, value, type);
}
#endif

/** @brief Get a key binding in a CMPIObjectPath object by name.

    @param op CMPIObjectPath object.
    @param [out] key Name of the key binding.
    @param [out] rc Function return status (suppressed when NULL).
    @return Key binding value and type.
    @fulldescription CMPIObjectPathFT.getKey()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetKey(op, key, rc) \
    ((op)->ft->getKey((op),(key),(rc)))
#else
static inline CMPIData CMGetKey(
    const CMPIObjectPath *op,
    const char *key,
    CMPIStatus *rc)
{
    return op->ft->getKey(op, key, rc);
}
#endif

/** @brief Get a key binding in a CMPIObjectPath object by index.

    @param op CMPIObjectPath object.
    @param index Zero-based position of the key binding within the internal
         data array.
    @param [out] name Name of the returned key binding (suppressed when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return Key binding value and type.
    @fulldescription CMPIObjectPathFT.getKeyAt()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetKeyAt(op, index, name, rc) \
    ((op)->ft->getKeyAt((op), (index), (name), (rc)))
#else
static inline CMPIData CMGetKeyAt(
    const CMPIObjectPath *op,
    CMPICount index,
    CMPIString **name,
    CMPIStatus *rc)
{
    return op->ft->getKeyAt(op, index, name, rc);
}
#endif


/** @brief Get the number of key bindings in a CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of key bindings in the CMPIObjectPath object.
    @fulldescription CMPIObjectPathFT.getKeyCount()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetKeyCount(op, rc) \
    ((op)->ft->getKeyCount((op), (rc)))
#else
static inline CMPICount CMGetKeyCount(
    const CMPIObjectPath *op,
    CMPIStatus *rc)
{
    return op->ft->getKeyCount(op, rc);
}
#endif

/** @brief Set the namespace and class name components in a CMPIObjectPath
         object from another CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param src The other CMPIObjectPath object.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.setNameSpaceFromObjectPath()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetNameSpaceFromObjectPath(op, src) \
    ((op)->ft->setNameSpaceFromObjectPath((op), (src)))
#else
static inline CMPIStatus CMSetNameSpaceFromObjectPath(
    const CMPIObjectPath *op,
    const CMPIObjectPath *src)
{
    return op->ft->setNameSpaceFromObjectPath(op, src);
}
#endif

/** @brief Set host name, namespace, and class name components in a
        CMPIObjectPath object from another CMPIObjectPath object.

    @param op CMPIObjectPath object.
    @param src The other CMPIObjectPath object.
    @return Function return status.
    @fulldescription CMPIObjectPathFT.setHostAndNameSpaceFromObjectPath()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetHostAndNameSpaceFromObjectPath(op, src) \
    ((op)->ft->setHostAndNameSpaceFromObjectPath((op), (src)))
#else
static inline CMPIStatus CMSetHostAndNameSpaceFromObjectPath(
    const CMPIObjectPath *op,
    const CMPIObjectPath *src)
{
    return op->ft->setHostAndNameSpaceFromObjectPath(op, src);
}
#endif

/** @brief Get a class qualifier.

    @param op CMPIObjectPath object containing namespace and class components.
    @param qName Qualifier name.
    @param [out] rc Function return status (suppressed when NULL).
    @return Qualifier value and type.
    @fulldescription CMPIObjectPathFT.getClassQualifier()
    @statusopenpegasus Not implemented
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetClassQualifier(op, qName, rc) \
    ((op)->ft->getClassQualifier((op), (qName), (rc)))
#else
static inline CMPIData CMGetClassQualifier(
    const CMPIObjectPath *op,
    const char *qName,
    CMPIStatus *rc)
{
    return op->ft->getClassQualifier(op, qName, rc);
}
#endif

/** @brief Get a property qualifier.

    @param op CMPIObjectPath object containing namespace and class components.
    @param pName Property name.
    @param qName Qualifier name.
    @param [out] rc Function return status (suppressed when NULL).
    @return Qualifier value and type.
    @fulldescription CMPIObjectPathFT.getPropertyQualifier()
    @statusopenpegasus Not implemented
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPropertyQualifier(op, pName, qName, rc) \
    ((op)->ft->getPropertyQualifier((op), (pName), (qName), (rc)))
#else
static inline CMPIData CMGetPropertyQualifier(
    const CMPIObjectPath *op,
    const char *pName,
    const char *qName,
    CMPIStatus *rc)
{
    return op->ft->getPropertyQualifier(op, pName, qName, rc);
}
#endif

/** @brief Get a method qualifier.

    @param op CMPIObjectPath object containing namespace and class components.
    @param mName Method name.
    @param qName Qualifier name.
    @param [out] rc Function return status (suppressed when NULL).
    @return Qualifier value and type.
    @fulldescription CMPIObjectPathFT.getMethodQualifier()
    @statusopenpegasus Not implemented
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetMethodQualifier(op, mName, qName, rc) \
    ((op)->ft->getMethodQualifier((op), (mName), (qName), (rc)))
#else
static inline CMPIData CMGetMethodQualifier(
    const CMPIObjectPath *op,
    const char *mName,
    const char *qName,
    CMPIStatus *rc)
{
    return op->ft->getMethodQualifier(op, mName, qName, rc);
}
#endif

/** @brief Get a parameter qualifier.

    @param op CMPIObjectPath object containing namespace and class components.
    @param mName Method name.
    @param pName Parameter name.
    @param qName Qualifier name.
    @param [out] rc Function return status (suppressed when NULL).
    @return Qualifier value and type.
    @fulldescription CMPIObjectPathFT.getParameterQualifier()
    @statusopenpegasus Not implemented
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetParameterQualifier(op, mName, pName, qName,rc) \
    ((op)->ft->getParameterQualifier((op), (mName), (pName), (qName), (rc)))
#else
static inline CMPIData CMGetParameterQualifier(
    const CMPIObjectPath *op,
    const char *mName,
    const char *pName,
    const char *qName,
    CMPIStatus *rc)
{
    return op->ft->getParameterQualifier(op, mName, pName, qName, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-args
  @{
*/

/** @brief Add or replace a method parameter in a CMPIArgs object.

    @param args CMPIArgs object.
    @param name Name of the method parameter.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the element, or NULL to assign NULL.
    @param type Type of the value.
    @return Function return status.
    @fulldescription CMPIArgsFT.addArg()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMAddArg(args, name, value, type) \
    ((args)->ft->addArg((args), (name), (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CMAddArg(
    const CMPIArgs *args,
    const char *name,
    const CMPIValue *value,
    const CMPIType type)
{
    return args->ft->addArg(args, name, (CMPIValue *)value, type);
}
#endif

/** @brief Get a method parameter in a CMPIArgs object by name.

    @param args CMPIArgs object.
    @param name Name of the method parameter.
    @param [out] rc Function return status (suppressed when NULL).
    @return Method parameter value and type.
    @fulldescription CMPIArgsFT.getArg()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArg(args, name, rc) \
    ((args)->ft->getArg((args), (name), (rc)))
#else
static inline CMPIData CMGetArg(
    const CMPIArgs *args,
    const char *name,
    CMPIStatus *rc)
{
    return args->ft->getArg(args, name, rc);
}
#endif

/** @brief Get a method parameter in a CMPIArgs object by index.

    @param args CMPIArgs object.
    @param index Zero-based position of the method parameter in the internal
         data array.
    @param [out] name Name of the returned method parameter (suppressed when
         NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return Method parameter value and type.
    @fulldescription CMPIArgsFT.getArgAt()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArgAt(args, index, name, rc) \
    ((args)->ft->getArgAt((args), (index), (name), (rc)))
#else
static inline CMPIData CMGetArgAt(
    const CMPIArgs *args,
    CMPICount index,
    CMPIString **name,
    CMPIStatus *rc)
{
    return args->ft->getArgAt(args, index, name, rc);
}
#endif

/** @brief Get the number of method parameters in a CMPIArgs object.

    @param args CMPIArgs object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of method parameters.
    @fulldescription CMPIArgsFT.getArgCount()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetArgCount(args, rc) \
    ((args)->ft->getArgCount((args), (rc)))
#else
static inline CMPICount CMGetArgCount(
    const CMPIArgs *args,
    CMPIStatus *rc)
{
    return args->ft->getArgCount(args, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-datetime
  @{
*/

/** @brief Get the value of a CMPIDateTime object in binary format.

    @param dt CMPIDateTime object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Value of the CMPIDateTime object in binary format: As a 64-bit
        unsigned integer in microseconds starting since 00:00:00 GMT, January
        1, 1970, or as an interval in microseconds, depending on what kind of
        value the CMPIDateTime object contains.
    @fulldescription CMPIDateTimeFT.getBinaryFormat()
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetBinaryFormat(dt, rc) \
    ((dt)->ft->getBinaryFormat((dt), (rc)))
#else
static inline CMPIUint64 CMGetBinaryFormat(
    const CMPIDateTime *dt,
    CMPIStatus *rc)
{
    return dt->ft->getBinaryFormat(dt, rc);
}
#endif

/** @brief Get the value of a CMPIDateTime object in the string format defined
        for the CIM ``datetime`` type.

    @param dt CMPIDateTime object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Value of the CMPIDateTime object as a string in the format defined
        in @ref ref-dmtf-dsp0004 "DSP0004" for the CIM ``datetime`` type.
    @fulldescription CMPIDateTimeFT.getStringFormat()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetStringFormat(dt, rc) \
    ((dt)->ft->getStringFormat((dt), (rc)))
#else
static inline CMPIString *CMGetStringFormat(
    const CMPIDateTime *dt,
    CMPIStatus *rc)
{
    return dt->ft->getStringFormat(dt, rc);
}
#endif

/** @brief Test whether a CMPIDateTime object contains an interval value.

    @param dt CMPIDateTime object.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The CMPIDateTime object contains an interval value.
    @retval false The CMPIDateTime object does not contain an interval value.
    @fulldescription CMPIDateTimeFT.isInterval()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMIsInterval(dt, rc) \
    ((dt)->ft->isInterval((dt), (rc)))
#else
static inline CMPIBoolean CMIsInterval(
    const CMPIDateTime *dt,
    CMPIStatus *rc)
{
    return dt->ft->isInterval(dt, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-selectexp
  @{
*/

/** @brief Test whether an instance matches the select expression in a
        CMPISelectExp object.

    @param se SelectExp object.
    @param inst Instance to be evaluated.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The instance matches the select expression.
    @retval false The instance does not match the select expression.
    @fulldescription CMPISelectExpFT.evaluate()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMEvaluateSelExp(se, inst, rc) \
    ((se)->ft->evaluate((se), (inst), (rc)))
#else
static inline CMPIBoolean CMEvaluateSelExp(
    const CMPISelectExp *se,
    const CMPIInstance *inst,
    CMPIStatus *rc)
{
    return se->ft->evaluate(se, inst, rc);
}
#endif

/** @brief Get the select expression in a CMPISelectExp object as a string.

    @param se SelectExp object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The select expression as a string.
    @fulldescription CMPISelectExpFT.getString()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetSelExpString(se, rc) \
    ((se)->ft->getString((se), (rc)))
#else
static inline CMPIString *CMGetSelExpString(
    const CMPISelectExp *se,
    CMPIStatus *rc)
{
    return se->ft->getString(se, rc);
}
#endif

/** @brief Get the select expression in a CMPISelectExp object as a disjunction
        of conjunctions.

    @param se SelectExp object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Select expression as a disjunction of conjunctions.
    @fulldescription CMPISelectExpFT.getDoc()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetDoc(se, rc) \
    ((se)->ft->getDOC((se), (rc)))
#else
static inline CMPISelectCond *CMGetDoc(
    const CMPISelectExp *se,
    CMPIStatus *rc)
{
    return se->ft->getDOC(se, rc);
}
#endif

/** @brief Get the select expression in a CMPISelectExp object as a conjunction
        of disjunctions.

    @param se SelectExp object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Select expression as a conjunction of disjunctions.
    @fulldescription CMPISelectExpFT.getCOD()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetCod(se, rc) \
    ((se)->ft->getCOD((se), (rc)))
#else
static inline CMPISelectCond *CMGetCod(
    const CMPISelectExp *se,
    CMPIStatus *rc)
{
    return se->ft->getCOD(se, rc);
}
#endif

/** @brief Test whether the properties returned by an accessor function match
        the select expression in a CMPISelectExp object.

    @param se SelectExp object.
    @param accessor Property value accessor function.
    @param parm A parameter that will be passed to the accessor function.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The properties returned by the accessor function match the
        select expression.
    @retval false The properties returned by the accessor function do not match
        the select expression.
    @fulldescription CMPISelectExpFT.evaluateUsingAccessor()
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMEvaluateSelExpUsingAccessor(se, accessor, parm, rc) \
    ((se)->ft->evaluateUsingAccessor((se), (accessor), (parm), (rc)))
#else
static inline CMPIBoolean CMEvaluateSelExpUsingAccessor(
    const CMPISelectExp *se,
    const CMPIAccessor *accessor,
    void *parm,
    CMPIStatus *rc)
{
    return se->ft->evaluateUsingAccessor(se, accessor, parm, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-selectcond
  @{
*/

/** @brief Get the number and type of subconditions in a CMPISelectCond object.

    Optionally, the subcondition type (COD or DOC) will be returned.
    @param sc SelectCond object.
    @param [out] type Subcondition type (suppressed when NULL). A value of 0
        indicates a DOC type, and a value of 1 indicates a COD type.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of subconditions.
    @fulldescription CMPISelectCondFT.getCountAndType()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetSubCondCountAndType(sc, type, rc) \
    ((sc)->ft->getCountAndType((sc), (type), (rc)))
#else
static inline CMPICount CMGetSubCondCountAndType(
    const CMPISelectCond *sc,
    int *type,
    CMPIStatus *rc)
{
    return sc->ft->getCountAndType(sc, type, rc);
}
#endif

/** @brief Get a subcondition in a CMPISelectCond object by index.

    @param sc SelectCond object.
    @param index Zero-based position of the subcondition in the internal data
        array.
    @param [out] rc Function return status (suppressed when NULL).
    @return The subcondition.
    @fulldescription CMPISelectCondFT.getSubCondAt()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetSubCondAt(sc, index, rc) \
    ((sc)->ft->getSubCondAt((sc), (index), (rc)))
#else
static inline CMPISubCond *CMGetSubCondAt(
    const CMPISelectCond *sc,
    CMPICount index,
    CMPIStatus *rc)
{
    return sc->ft->getSubCondAt(sc, index, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-subcond
  @{
*/

/** @brief Get the number of predicates in a CMPISubCond object.

    @param sc CMPISubCond object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Number of predicates.
    @fulldescription CMPISubCondFT.getCount()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPredicateCount(sc, rc) \
    ((sc)->ft->getCount((sc), (rc)))
#else
static inline CMPICount CMGetPredicateCount(
    const CMPISubCond *sc,
    CMPIStatus *rc)
{
    return sc->ft->getCount(sc, rc);
}
#endif

/** @brief Get a predicate in a CMPISubCond object by index.

    @param sc CMPISubCond object.
    @param index Zero-based position of the predicate in the internal data
        array.
    @param [out] rc Function return status (suppressed when NULL).
    @return The specified predicate.
    @fulldescription CMPISubCondFT.getPredicateAt()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPredicateAt(sc, index, rc) \
    ((sc)->ft->getPredicateAt((sc), (index), (rc)))
#else
static inline CMPIPredicate *CMGetPredicateAt(
    const CMPISubCond *sc,
    CMPICount index,
    CMPIStatus *rc)
{
    return sc->ft->getPredicateAt(sc, index, rc);
}
#endif

/** @brief Get a predicate in a CMPISubCond object by name.

    @param sc CMPISubCond object.
    @param name Predicate name. The name is the left-hand side of the predicate.
    @param [out] rc Function return status (suppressed when NULL).
    @return The specified predicate.
    @fulldescription CMPISubCondFT.getPredicate()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPredicate(sc, name, rc) \
    ((sc)->ft->getPredicate((sc), (name), (rc)))
#else
static inline CMPIPredicate *CMGetPredicate(
    const CMPISubCond *sc,
    const char *name,
    CMPIStatus *rc)
{
    return sc->ft->getPredicate(sc, name, rc);
}
#endif


/**
  @}
  @addtogroup convenience-func-edt-predicate
  @{
*/

/** @brief Get the predicate components of a CMPIPredicate object.

    @param pr CMPIPredicate object.
    @param [out] type Data type of the predicate (suppressed when NULL).
    @param [out] prop Predicate operation (suppressed when NULL).
    @param [out] lhs Left-hand side of predicate (suppressed when NULL).
    @param [out] rhs Right-hand side of predicate (suppressed when NULL).
    @return Function return status.
    @fulldescription CMPIPredicateFT.getData()
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPredicateData(pr, type, prop, lhs, rhs) \
    ((pr)->ft->getData((pr), (type), (prop), (lhs), (rhs)))
#else
static inline CMPIStatus CMGetPredicateData(
    const CMPIPredicate *pr,
    CMPIType *type,
    CMPIPredOp *prop,
    CMPIString **lhs,
    CMPIString **rhs)
{
    return pr->ft->getData(pr, type, prop, lhs, rhs);
}
#endif

/** @brief Test whether the properties returned by an accessor function match
        the predicate in a CMPIPredicate object.

    @param pr CMPIPredicate object.
    @param accessorFnc Property value accessor function.
    @param parm A parameter that will be passed to the accessor function.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The properties returned by the accessor function match the
        predicate.
    @retval false The properties returned by the accessor function do not match
        the predicate.
    @fulldescription CMPIPredicateFT.evaluateUsingAccessor()
    @changed210 In CMPI 2.1, the return type of ths function has been changed
        from **int** to @ref CMPIBoolean.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMEvaluatePredicateUsingAccessor(pr, accessorFnc, parm, rc) \
    ((pr)->ft->evaluateUsingAccessor((pr), (accessorFnc), (parm), (rc)))
#else
static inline CMPIBoolean CMEvaluatePredicateUsingAccessor(
    const CMPIPredicate *pr,
    const CMPIAccessor *accessorFnc,
    void *parm,
    CMPIStatus *rc)
{
    return pr->ft->evaluateUsingAccessor(pr, accessorFnc, parm, rc);
}
#endif

/**
  @}
  @addtogroup convenience-func-edt-error
  @{
*/

#ifdef CMPI_VER_200

/** @brief Get the `ErrorType` attribute of a CMPIError object.

    For a description of the `ErrorType` attribute, see @ref CMPIErrorType and
    the description of the `ErrorType` property in the `CIM_Error` class in the
    CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `ErrorType` attribute.
    @fulldescription CMPIErrorFT.getErrorType()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetErrorType(er, rc) \
    ((er)->ft->getErrorType((er), (rc)))
#else
static inline CMPIErrorType CMGetErrorType(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getErrorType(er, rc);
}
#endif

/** @brief Get the `OtherErrorType` attribute of a CMPIError object.

    For a description of the `OtherErrorType` attribute, see the description of
    the `OtherErrorType` property in the `CIM_Error` class in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `OtherErrorType` attribute.
    @fulldescription CMPIErrorFT.getOtherErrorType()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Used and tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetOtherErrorType(er, rc) \
    ((er)->ft->getOtherErrorType((er), (rc)))
#else
static inline CMPIString *CMGetOtherErrorType(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getOtherErrorType(er, rc);
}
#endif

/** @brief Get the `OwningEntity` attribute of a CMPIError object.

    For a description of the `OwningEntity` attribute, see the description of
    the `OwningEntity` property in the `CIM_Error` class in the CIM Schema, and
    the description of the @p owner argument of CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `OwningEntity` attribute.
    @fulldescription CMPIErrorFT.getOwningEntity()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetOwningEntity(er, rc) \
    ((er)->ft->getOwningEntity((er), (rc)))
#else
static inline CMPIString *CMGetOwningEntity(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getOwningEntity(er, rc);
}
#endif

/** @brief Get the `MessageID` attribute of a CMPIError object.

    For a description of the `MessageID` attribute, see the description of the
    `MessageID` property in the `CIM_Error` class in the CIM Schema, and the
    description of the @p msgID argument of CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `MessageID` attribute.
    @fulldescription CMPIErrorFT.getMessageID()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetMessageID(er, rc) \
    ((er)->ft->getMessageID((er), (rc)))
#else
static inline CMPIString *CMGetMessageID(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getMessageID(er, rc);
}
#endif

/** @brief Get the `Message` attribute of a CMPIError object.

    For a description of the `Message` attribute, see the description of the
    `Message` property in the `CIM_Error` class in the CIM Schema, and the
    description of the @p msg argument of CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `Message` attribute.
    @fulldescription CMPIErrorFT.getMessage()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetErrorMessage(er, rc) \
    ((er)->ft->getMessage((er), (rc)))
#else
static inline CMPIString *CMGetErrorMessage(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getMessage(er, rc);
}
#endif

/** @brief Get the `PerceivedSeverity` attribute of a CMPIError object.

    For a description of the `PerceivedSeverity` attribute, see @ref
    CMPIErrorSeverity, the description of the `PerceivedSeverity` property in
    the `CIM_Error` class in the CIM Schema, and the description of the @p sev
    argument of CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `PerceivedSeverity` attribute.
    @fulldescription CMPIErrorFT.getPerceivedSeverity()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetPerceivedSeverity(er, rc) \
    ((er)->ft->getPerceivedSeverity((er), (rc)))
#else
static inline CMPIErrorSeverity CMGetPerceivedSeverity(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getPerceivedSeverity(er, rc);
}
#endif

/** @brief Get the `ProbableCause` attribute of a CMPIError object.

    For a description of the `ProbableCause` attribute, see @ref
    CMPIErrorProbableCause, the description of the `ProbableCause` property in
    the `CIM_Error` class in the CIM Schema, and the description of the @p pc
    argument of CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `ProbableCause` attribute.
    @fulldescription CMPIErrorFT.getProbableCause()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetProbableCause(er, rc) \
    ((er)->ft->getProbableCause((er), (rc)))
#else
static inline CMPIErrorProbableCause CMGetProbableCause(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getProbableCause(er, rc);
}
#endif

/** @brief Get the `ProbableCauseDescription` attribute of a CMPIError object.

    For a description of the `ProbableCauseDescription` attribute, see the
    description of the `ProbableCauseDescription` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `ProbableCauseDescription` attribute.
    @fulldescription CMPIErrorFT.getProbableCauseDescription()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetProbableCauseDescription(er, rc) \
    ((er)->ft->getProbableCauseDescription((er), (rc)))
#else
static inline CMPIString * CMGetProbableCauseDescription(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getProbableCauseDescription(er, rc);
}
#endif

/** @brief Get the `RecommendedActions` array attribute of a CMPIError object.

    For a description of the `RecommendedActions` attribute, see the
    description of the `RecommendedActions` property in the `CIM_Error` class
    in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `RecommendedActions` array attribute.
    @fulldescription CMPIErrorFT.getRecommendedActions()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetRecommendedActions(er, rc) \
    ((er)->ft->getRecommendedActions((er), (rc)))
#else
static inline CMPIArray * CMGetRecommendedActions(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getRecommendedActions(er, rc);
}
#endif

/** @brief Get the `ErrorSource` attribute of a CMPIError object.

    For a description of the `ErrorSource` attribute, see the description of
    the `ErrorSource` property in the `CIM_Error` class in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `ErrorSource` attribute.
    @fulldescription CMPIErrorFT.getErrorSource()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetErrorSource(er, rc) \
    ((er)->ft->CMGetErrorSourcegetErrorSource((er), (rc)))
#else
static inline CMPIString * CMGetErrorSource(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getErrorSource(er, rc);
}
#endif

/** @brief Get the `ErrorSourceFormat` attribute of a CMPIError object.

    For a description of the `ErrorSourceFormat` attribute, see the description
    of the `ErrorSourceFormat` property in the `CIM_Error` class in the CIM
    Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `ErrorSourceFormat` attribute.
    @fulldescription CMPIErrorFT.getErrorSourceFormat()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetErrorSourceFormat(er, rc) \
    ((er)->ft->getErrorSourceFormat((er), (rc)))
#else
static inline CMPIErrorSrcFormat CMGetErrorSourceFormat(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getErrorSourceFormat(er, rc);
}
#endif

/** @brief Get the `OtherErrorSourceFormat` attribute of a CMPIError object.

    For a description of the `OtherErrorSourceFormat` attribute, see the
    description of the `OtherErrorSourceFormat` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `OtherErrorSourceFormat` attribute.
    @fulldescription CMPIErrorFT.getOtherErrorSourceFormat()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetOtherErrorSourceFormat(er, rc) \
    ((er)->ft->getOtherErrorSourceFormat((er), (rc)))
#else
static inline CMPIString * CMGetOtherErrorSourceFormat(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getOtherErrorSourceFormat(er, rc);
}
#endif

/** @brief Get the `CIMStatusCode` attribute of a CMPIError object.

    For a description of the `CIMStatusCode` attribute, see the description of
    the `CIMStatusCode` property in the `CIM_Error` class in the CIM Schema,
    and the description of the @p cimStatusCode argument of
    CMPIBrokerEncFT.newCMPIError().

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `CIMStatusCode` attribute.
    @fulldescription CMPIErrorFT.getCIMStatusCode()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetCIMStatusCode(er, rc) \
    ((er)->ft->getCIMStatusCode((er), (rc)))
#else
static inline CMPIrc CMGetCIMStatusCode(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getCIMStatusCode(er, rc);
}
#endif

/** @brief Get the `CIMStatusCodeDescription` attribute of a CMPIError object.

    For a description of the `CIMStatusCodeDescription` attribute, see the
    description of the `CIMStatusCodeDescription` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `CIMStatusCodeDescription` attribute.
    @fulldescription CMPIErrorFT.getCIMStatusCodeDescription()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetCIMStatusCodeDescription(er, rc) \
    ((er)->ft->getCIMStatusCodeDescription((er), (rc)))
#else
static inline CMPIString * CMGetCIMStatusCodeDescription(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getCIMStatusCodeDescription(er, rc);
}
#endif

/** @brief Get the `MessageArguments` array attribute of a CMPIError object.

    For a description of the `MessageArguments` attribute, see the description
    of the `MessageArguments` property in the `CIM_Error` class in the CIM
    Schema.

    @param er CMPIError object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The `MessageArguments` array attribute.
    @fulldescription CMPIErrorFT.getMessageArguments()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetMessageArguments(er, rc) \
    ((er)->ft->getMessageArguments((er), (rc)))
#else
static inline CMPIArray * CMGetMessageArguments(
    const CMPIError *er,
    CMPIStatus *rc)
{
    return er->ft->getMessageArguments(er, rc);
}
#endif

/** @brief Set the `ErrorType` attribute of a CMPIError object.

    For a description of the `ErrorType` attribute, see @ref CMPIErrorType and
    the description of the `ErrorType` property in the `CIM_Error` class in the
    CIM Schema.

    @param er CMPIError object.
    @param et The `ErrorType` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setErrorType()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetErrorType(er, et) \
    ((er)->ft->setErrorType((er), (et)))
#else
static inline CMPIStatus CMSetErrorType(
    const CMPIError *er,
    const CMPIErrorType et)
{
    return er->ft->setErrorType(er, et);
}
#endif

/** @brief Set the `OtherErrorType` attribute of a CMPIError object.

    For a description of the `OtherErrorType` attribute, see the description of
    the `OtherErrorType` property in the `CIM_Error` class in the CIM Schema.

    @param er CMPIError object.
    @param ot The `OtherErrorType` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setOtherErrorType()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetOtherErrorType(er, ot) \
    ((er)->ft->setOtherErrorType((er), (ot)))
#else
static inline CMPIStatus CMSetOtherErrorType(
    const CMPIError *er,
    const char *ot)
{
    return er->ft->setOtherErrorType(er, ot);
}
#endif

/** @brief Set the `ProbableCauseDescription` attribute of a CMPIError object.

    For a description of the `ProbableCauseDescription` attribute, see the
    description of the `ProbableCauseDescription` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param pcd The `ProbableCauseDescription` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setProbableCauseDescription()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetProbableCauseDescription(er, pcd) \
    ((er)->ft->setProbableCauseDescription((er), (pcd)))
#else
static inline CMPIStatus CMSetProbableCauseDescription(
    const CMPIError *er,
    const char *pcd)
{
    return er->ft->setProbableCauseDescription(er, pcd);
}
#endif

/** @brief Set the `RecommendedActions` array attribute of a CMPIError object.

    For a description of the `RecommendedActions` attribute, see the
    description of the `RecommendedActions` property in the `CIM_Error` class
    in the CIM Schema.

    @param er CMPIError object.
    @param ra The `RecommendedActions` array attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setRecommendedActions()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetRecommendedActions(er, ra)                            \
    ((er)->ft->setRecommendedActions((er), (ra)))
#else
static inline CMPIStatus CMSetRecommendedActions(
    const CMPIError *er,
    const CMPIArray *ra)
{
    return er->ft->setRecommendedActions(er, ra);
}
#endif

/** @brief Set the `ErrorSource` attribute of a CMPIError object.

    For a description of the `ErrorSource` attribute, see the description of
    the `ErrorSource` property in the `CIM_Error` class in the CIM Schema.

    @param er CMPIError object.
    @param es The `ErrorSource` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setErrorSource()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetErrorSource(er, es) \
    ((er)->ft->setErrorSource((er), (es)))
#else
static inline CMPIStatus CMSetErrorSource(
    const CMPIError *er,
    const char* es)
{
    return er->ft->setErrorSource(er, es);
}
#endif

/** @brief Set the `ErrorSourceFormat` attribute of a CMPIError object.

    For a description of the `ErrorSourceFormat` attribute, see the description
    of the `ErrorSourceFormat` property in the `CIM_Error` class in the CIM
    Schema.

    @param er CMPIError object.
    @param esf The `ErrorSourceFormat` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setErrorSourceFormat()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetErrorSourceFormat(er, esf) \
    ((er)->ft->setErrorSourceFormat((er), (esf)))
#else
static inline CMPIStatus CMSetErrorSourceFormat(
    const CMPIError *er,
    const CMPIErrorSrcFormat esf)
{
    return er->ft->setErrorSourceFormat(er, esf);
}
#endif

/** @brief Set the `OtherErrorSourceFormat` attribute of a CMPIError object.

    For a description of the `OtherErrorSourceFormat` attribute, see the
    description of the `OtherErrorSourceFormat` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param oef The `OtherErrorSourceFormat` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setOtherErrorSourceFormat()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetOtherErrorSourceFormat(er, oef) \
    ((er)->ft->setOtherErrorSourceFormat((er), (oef)))
#else
static inline CMPIStatus CMSetOtherErrorSourceFormat(
    const CMPIError *er,
    const char* oef)
{
    return er->ft->setOtherErrorSourceFormat(er, oef);
}
#endif

/** @brief Set the `CIMStatusCodeDescription` attribute of a CMPIError object.

    For a description of the `CIMStatusCodeDescription` attribute, see the
    description of the `CIMStatusCodeDescription` property in the `CIM_Error`
    class in the CIM Schema.

    @param er CMPIError object.
    @param scd The `CIMStatusCodeDescription` attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setCIMStatusCodeDescription()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetCIMStatusCodeDescription(er, scd) \
    ((er)->ft->setCIMStatusCodeDescription((er), (scd)))
#else
static inline CMPIStatus CMSetCIMStatusCodeDescription(
    const CMPIError *er,
    const char* scd)
{
    return er->ft->setCIMStatusCodeDescription(er, scd);
}
#endif

/** @brief Set the `MessageArguments` array attribute of a CMPIError object.

    For a description of the `MessageArguments` attribute, see the description
    of the `MessageArguments` property in the `CIM_Error` class in the CIM
    Schema.

    @param er CMPIError object.
    @param values The `MessageArguments` array attribute.
    @return Function return status.
    @fulldescription CMPIErrorFT.setMessageArguments()
    @added200
    @changed210 The inline function was fixed in CMPI 2.1.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMSetMessageArguments(er, values) \
    ((er)->ft->setMessageArguments((er), (values)))
#else
static inline CMPIStatus CMSetMessageArguments(
    const CMPIError *er,
    const CMPIArray *values)
{
    return er->ft->setMessageArguments(er, values);
}
#endif

#endif /* CMPI_VER_200 */

#ifdef CMPI_VER_210
/** @brief Test whether a property is in the property list represented by a
        CMPIPropertyList object.

    @param plist CMPIPropertyList object.
    @param pname Name of the property to be tested.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The property is in the property list.
    @retval false The property is not in the property list.
    @fulldescription CMPIPropertyListFT.isPropertyInList()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMIsPropertyInList(plist, pname, rc) \
    ((plist)->ft->isPropertyInList((plist), (pname), (rc)))
#else
static inline CMPIBoolean CMIsPropertyInList(
    const CMPIPropertyList *plist,
    const char *pname,
    CMPIStatus *rc)
{
    return plist->ft->isPropertyInList(plist, pname, rc);
}
#endif
#endif /* CMPI_VER_210 */

#ifdef CMPI_VER_210
/** @brief Return the property list represented by a CMPIPropertyList object
        as an array of C-language strings.

    @param plist CMPIPropertyList object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The property list.
    @fulldescription CMPIPropertyListFT.getProperties()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMGetListProperties(plist, rc) \
    ((plist)->ft->getProperties((plist), (rc)))
#else
static inline const char** CMGetListProperties(
    const CMPIPropertyList *plist,
    CMPIStatus *rc)
{
    return plist->ft->getProperties(plist, rc);
}
#endif
#endif /* CMPI_VER_210 */

#ifdef CMPI_VER_210
/** @brief Test whether an instance matches the filter represented by a
        CMPIEnumerationFilter object.

    @param ef CMPIEnumerationFilter object.
    @param inst Instance to be tested against the filter.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The instance matches the filter.
    @retval false The instance does not match the filter.
    @fulldescription CMPIEnumerationFilterFT.match()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMFilterMatch(ef, inst, rc) \
    ((ef)->ft->match((ef), (inst), (rc)))
#else
static inline CMPIBoolean CMFilterMatch(
    const CMPIEnumerationFilter *ef,
    const CMPIInstance *inst,
    CMPIStatus *rc)
{
    return ef->ft->match(ef, inst, rc);
}
#endif
#endif /* CMPI_VER_210 */

/**
  @}
  @addtogroup convenience-func-helper
  @{
*/

/** @brief Get the MB capabilities

    The MB capabilities are defined as bits in the returned integer value. See
    @ref mb-capabilities "MB Capabilities" for details.
    @param mb CMPIBroker structure.
    @return MB capabilities.
    @fulldescription CMPIBrokerFT.brokerCapabilities
    @changed210 In CMPI 2.1, CBGetClassification() was removed as not working,
        and this function was introduced.
    @see @ref mb-capabilities "MB Capabilities"
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBGetCapabilities(mb) \
    ((mb)->bft->brokerCapabilities)
#else
static inline unsigned int CBGetCapabilities(
    const CMPIBroker *mb)
{
    return mb->bft->brokerCapabilities;
}
#endif

/** @brief Get the CMPI version supported by the MB.

    Any earlier CMPI versions are implicitly also supported. See @ref
    sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI version numbers.

    Note: This is not the version of the MB.

    @param mb CMPIBroker structure.
    @return CMPI version supported by the MB.
    @fulldescription CMPIBrokerFT.brokerVersion
    @statusopenpegasus Not used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBBrokerVersion(mb) \
    ((mb)->bft->brokerVersion)
#else
static inline CMPIVersion CBBrokerVersion(
    const CMPIBroker *mb)
{
    return mb->bft->brokerVersion;
}
#endif

/** @brief Get the MB name

    The MB name is an informal MB-specific string.

    @param mb CMPIBroker structure.
    @return Name of the MB.
    @fulldescription CMPIBrokerFT.brokerName
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBBrokerName(mb) \
    ((bm)->bft->brokerName)
#else
static inline const char * CBBrokerName(
    const CMPIBroker *mb)
{
    return mb->bft->brokerName;
}
#endif

/**
  @}
  @addtogroup convenience-func-broker
  @{
    MB Functions in Broker Function Tables.

    The convenience functions in this group call MB functions provided by the
    broker function tables (that is, the function tables pointed to by
    CMPIBroker members).

    They simplify the code by eliminating the references to function tables,
    and by eliminating the need to know which of the function tables has the
    desired function.
*/

/** @brief Prepare the MB to accept a new thread that will be using MB
        functions.

    This function is expected to be called in the existing thread.
    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @return CMPIContext object that is to be used by the thread to be attached.
    @fulldescription CMPIBrokerFT.prepareAttachThread()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBPrepareAttachThread(mb, ctx) \
    ((mb)->bft->prepareAttachThread((mb), (ctx)))
#else
static inline CMPIContext *CBPrepareAttachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->prepareAttachThread(mb, ctx);
}
#endif

/** @brief Inform the MB that the current thread will begin using MB functions.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object that was returned by a prior call to
        CBPrepareAttachThread().
    @return Function return status.
    @fulldescription CMPIBrokerFT.attachThread()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAttachThread(mb, ctx) \
    ((mb)->bft->attachThread((mb), (ctx)))
#else
static inline CMPIStatus CBAttachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->attachThread(mb, ctx);
}
#endif

/** @brief Inform the MB that the current thread will no longer use MB
        functions.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object that was returned by a prior call to
        CBPrepareAttachThread().
    @return Function return status.
    @fulldescription CMPIBrokerFT.detachThread()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBDetachThread(mb, ctx) \
    ((mb)->bft->detachThread((mb), (ctx)))
#else
static inline CMPIStatus CBDetachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->detachThread(mb, ctx);
}
#endif


/** @brief Request delivery of an indication.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param ns Name of the *origin namespace* of the indication (see
         @ref ref-dmtf-dsp1054 "DSP1054" for a definition).
    @param ind The indication instance.
    @return Function return status.
    @fulldescription CMPIBrokerFT.deliverIndication()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBDeliverIndication(mb, ctx, ns, ind) \
    ((mb)->bft->deliverIndication((mb), (ctx), (ns), (ind)))
#else
static inline CMPIStatus CBDeliverIndication(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const char *ns,
    const CMPIInstance *ind)
{
    return mb->bft->deliverIndication(mb, ctx, ns, ind);
}
#endif

/** @brief Enumerate the instance paths of the instances of a given class (and
        its subclasses).

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param classPath Class path of the given class.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIObjectPath objects that
        represent the enumerated instance paths.
    @fulldescription CMPIBrokerFT.enumerateInstanceNames()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBEnumInstanceNames(mb, ctx, classPath, rc) \
    ((mb)->bft->enumerateInstanceNames((mb), (ctx), (classPath), (rc)))
#else
static inline CMPIEnumeration *CBEnumInstanceNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *classPath,
    CMPIStatus *rc)
{
    return mb->bft->enumerateInstanceNames(mb, ctx, classPath, rc);
}
#endif

/** @brief Enumerate the instances of a given class (and its subclasses).

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param classPath Class path of the given class.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.enumerateInstances()
    @statusopenpegasus Not used, not tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBEnumInstances(mb, ctx, classPath, properties, rc) \
           (mb)->bft->enumerateInstances((mb), (ctx), (classPath), \
           (properties), (rc)))
#else
static inline CMPIEnumeration *CBEnumInstances(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *classPath,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->enumerateInstances(mb, ctx, classPath, properties, rc);
}
#endif

/** @brief Get an existing instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the instance to be retrieved.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return The instance.
    @fulldescription CMPIBrokerFT.getInstance()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBGetInstance(mb, ctx, instPath, properties, rc) \
    ((mb)->bft->getInstance((mb), (ctx), (instPath), (properties), (rc)))
#else
static inline CMPIInstance *CBGetInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->getInstance(mb, ctx, instPath, properties, rc);
}
#endif

/** @brief Create an instance of a given class.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param classPath Class path of the creation class for the new instance.
    @param newInst Property values for the new instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return Instance path of the new instance.
    @fulldescription CMPIBrokerFT.createInstance()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBCreateInstance(mb, ctx, classPath, newInst, rc) \
    ((mb)->bft->createInstance((mb), (ctx), (classPath), (newInst), (rc)))
#else
static inline CMPIObjectPath *CBCreateInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *classPath,
    const CMPIInstance *newInst,
    CMPIStatus *rc)
{
    return mb->bft->createInstance(mb, ctx, classPath, newInst, rc);
}
#endif

/** @brief Modify property values of an existing instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the instance to be modified.
    @param modInst New property values for the instance to be modified.
    @param properties The names of the properties to be modified. If NULL, all
        properties will be modified.
    @return Function return status.
    @fulldescription CMPIBrokerFT.modifyInstance()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBModifyInstance(mb, ctx, instPath, modInst, properties) \
    ((mb)->bft->modifyInstance((mb), (ctx), (instPath), (modInst), \
                               (properties)))
#else
static inline CMPIStatus CBModifyInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const CMPIInstance *modInst,
    const char** properties)
{
    return mb->bft->modifyInstance(mb, ctx, instPath, modInst, properties);
}
#endif

/** @brief Delete an existing instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the instance to be deleted.
    @return Function return status.
    @fulldescription CMPIBrokerFT.deleteInstance()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBDeleteInstance(mb, ctx, instPath) \
    ((mb)->bft->deleteInstance((mb), (ctx), (instPath)))
#else
static inline CMPIStatus CBDeleteInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath)
{
    return mb->bft->deleteInstance(mb, ctx, instPath);
}
#endif

/** @brief Execute a query on a given class and return the query result.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param classPath Class path of the class to be queried.
    @param query Select expression.
    @param lang Query language.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the query result.
    @fulldescription CMPIBrokerFT.execQuery()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBExecQuery(mb, ctx, classPath, query, lang, rc) \
    ((mb)->bft->execQuery((mb), (ctx), (classPath), (query), (lang), (rc)))
#else
static inline CMPIEnumeration *CBExecQuery(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *classPath,
    const char *query,
    const char *lang,
    CMPIStatus *rc)
{
    return mb->bft->execQuery(mb, ctx, classPath, query, lang, rc);
}
#endif

/** @brief Enumerate the instances associated with a given source instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param assocClass If not NULL, a valid association class name that acts as
        a filter on the returned set of instances by mandating that each
        returned instance shall be associated to the source instance via an
        instance of this class or one of its subclasses.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param resultRole If not NULL, a valid property name that acts as a filter
        on the returned set of instances by mandating that each returned
        instance shall be associated to the source instance via an association
        in which the returned instance plays the specified role.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.associators()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAssociators(mb, ctx, instPath, assocClass, resultClass, role, \
                      resultRole, properties, rc) \
    ((mb)->bft->associators((mb), (ctx), (instPath), (assocClass), \
                            (resultClass), (role), (resultRole), (properties), \
                            (rc)))
#else
static inline CMPIEnumeration *CBAssociators(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->associators(mb, ctx, instPath, assocClass, resultClass,
                                role, resultRole, properties, rc);
}
#endif

/** @brief Enumerate the instance paths of the instances associated with a
        given source instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param assocClass If not NULL, a valid association class name that acts as
        a filter on the returned set of instances by mandating that each
        returned instance shall be associated to the source instance via an
        instance of this class or one of its subclasses.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param resultRole If not NULL, a valid property name that acts as a filter
        on the returned set of instances by mandating that each returned
        instance shall be associated to the source instance via an association
        in which the returned instance plays the specified role.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIObjectPath objects that
        represent the enumerated instance paths.
    @fulldescription CMPIBrokerFT.associatorNames()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAssociatorNames(mb, ctx, instPath, assocClass, resultClass, role, \
                          resultRole, rc) \
    ((mb)->bft->associatorNames((mb), (ctx), (instPath), (assocClass), \
                                (resultClass), (role), (resultRole), (rc)))
#else
static inline CMPIEnumeration *CBAssociatorNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    CMPIStatus *rc)
{
    return mb->bft->associatorNames(mb, ctx, instPath, assocClass, resultClass,
                                    role, resultRole, rc);
}
#endif

/** @brief Enumerate the association instances referencing a given source
        instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.references()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBReferences(mb, ctx, instPath, resultClass, role, properties, rc) \
    ((mb)->bft->references((mb), (ctx), (instPath), (resultClass), (role), \
                           (properties), (rc)))
#else
static inline CMPIEnumeration *CBReferences(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *resultClass,
    const char *role,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->references(mb, ctx, instPath, resultClass, role, properties,
                               rc);
}
#endif

/** @brief Enumerate the instance paths of the association instances
        referencing a given source instance.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIObjectPath objects that
        represent the enumerated instance paths.
    @fulldescription CMPIBrokerFT.referenceNames()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBReferenceNames(mb, ctx, instPath, resultClass, role, rc) \
    ((mb)->bft->referenceNames((mb), (ctx), (instPath), (resultClass), (role), \
                               (rc)))
#else
static inline CMPIEnumeration *CBReferenceNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *resultClass,
    const char *role,
    CMPIStatus *rc)
{
    return mb->bft->referenceNames(mb, ctx, instPath, resultClass, role, rc);
}
#endif

/** @brief Invoke a method on a target object.

    Instance methods (i.e., non-static methods) can be invoked only on
    instances. Class methods (i.e., static methods) can be invoked on instances
    and classes.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param objPath Object path of the target object.
    @param method	Method name.
    @param in A CMPIArgs object containing the method input parameters.
    @param [out] out An empty CMPIArgs object that, upon successful return of
        the method, will have been updated to contain the method output
        parameters.
    @param [out] rc Function return status (suppressed when NULL).
    @return The method return value and type.
    @fulldescription CMPIBrokerFT.invokeMethod()
    @examples
    The example invokes static method "TestCMPIError" on class
    "TestCMPI_BrokerInstance" in namespace "test/TestProvider", and tests for
    success and correct data type of the method return value.
    @code (.c)
    const CMPIArgs *in;
    CMPIArgs *out
    CMPIObjectPath *objPath;
    CMPIData retData;
    // define input arguments here

    objPath = CMNewObjectPath(_broker, "test/TestProvider",
        "TestCMPI_BrokerInstance", &rc);

    retData = CBInvokeMethod(_broker, ctx, objPath, "TestCMPIError",
        in, out, &rc);
        PROV_LOG_OPEN (_ClassName, _ProviderLocation);

    // test to confirm return date data type and return status
    if (!retData.value.uint32 && rc.rc != CMPI_RC_OK)
    {
        // execute error function
    }
    // clean up and use retData
    rc = CMRelease(objPath);
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo TBD AM: I think the CMRelease() is incorrect, because the
        object is not a result of CMClone().
*/
#ifdef CMPI_NO_INLINE
#define CBInvokeMethod(mb,c,p,m,ai,ao,rc) \
    ((mb)->bft->invokeMethod((mb),(c),(p),(m),(ai),(ao),(rc)))
#else
static inline CMPIData CBInvokeMethod(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *method,
    const CMPIArgs *in,
    CMPIArgs *out,
    CMPIStatus *rc)
{
    return mb->bft->invokeMethod(mb, ctx, op, method, in, out, rc);
}
#endif

/** @brief Set or modify a property of an existing instance. (**Deprecated**)

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the instance to be modified.
    @param name Property name.
    @param value CMPIValue structure containing the non-NULL value to be
        assigned to the property, or NULL to specify that NULL is to be
        assigned.
    @param type Type of the value to be assigned.
    @return Function return status.
    @fulldescription CMPIBrokerFT.setProperty()
    @deprecated This function is deprecated since CMPI 2.1, in accord with the
        deprecation of property client operations in DMTF specifications.

    @note No example because this function is deprecated.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBSetProperty(mb, ctx, instPath, name, value, type) \
    ((mb)->bft->setProperty((mb), (ctx), (instPath), (name), \
                            (CMPIValue *)(value), (type)))
#else
static inline CMPIStatus CBSetProperty(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *name,
    const CMPIValue *value,
    const CMPIType type)
{
    return mb->bft->setProperty(mb, ctx, instPath, name, (CMPIValue *)value,
                                type);
}
#endif

/** @brief Get a property of an existing instance. (**Deprecated**)

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the instance to be retrieved.
    @param name Property name.
    @param [out] rc Function return status (suppressed when NULL).
    @return Property value and type.
    @fulldescription CMPIBrokerFT.setProperty()
    @deprecated This function is deprecated since CMPI 2.1, in accord with the
        deprecation of property client operations in DMTF specifications.

    @note No example because this function is deprecated.
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBGetProperty(mb, ctx, instPath, name, rc) \
    (mb)->bft->getProperty((mb), (ctx), (instPath), (name), (rc))
#else
static inline CMPIData CBGetProperty(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *name,
    CMPIStatus *rc)
{
    return mb->bft->getProperty(mb, ctx, instPath, name, rc);
}
#endif

/** @brief Enumerate the instances of a given class (and its subclasses),
         returning only those that match the given query filter.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param classPath Class path of the given class.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param filterQueryLanguage Query language used by @p filterQuery (no
        filtering when NULL).
    @param filterQuery Query for filtering the result (no filtering when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.enumerateInstancesFiltered()
    @statusopenpegasus Not used, not tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBEnumInstancesFiltered(mb, ctx, classPath, properties, \
            filterQueryLanguage, filterQuery, rc) \
    (mb)->bft->enumerateInstancesFiltered((mb), (ctx), (classPath), \
        (properties), (filterQueryLanguage), (filterQuery), (rc)))
#else
static inline CMPIEnumeration *CBEnumInstancesFiltered(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *classPath,
    const char **properties,
    const char *filterQueryLanguage,
    const char *filterQuery,
    CMPIStatus *rc)
{
    return mb->bft->enumerateInstancesFiltered(mb, ctx, classPath, properties,
         filterQueryLanguage, filterQuery, rc);
}
#endif

/** @brief Enumerate the instances associated with a given source instance,
         returning only those that match the given filters.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param assocClass If not NULL, a valid association class name that acts as
        a filter on the returned set of instances by mandating that each
        returned instance shall be associated to the source instance via an
        instance of this class or one of its subclasses.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param resultRole If not NULL, a valid property name that acts as a filter
        on the returned set of instances by mandating that each returned
        instance shall be associated to the source instance via an association
        in which the returned instance plays the specified role.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param filterQueryLanguage Query language used by @p filterQuery (no
        filtering when NULL).
    @param filterQuery Query for filtering the result (no filtering when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.associatorsFiltered()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAssociatorsFiltered(mb, ctx, instPath, assocClass, resultClass, \
            role, resultRole, properties, filterQueryLanguage, filterQuery, \
            rc) \
    ((mb)->bft->associatorsFiltered((mb), (ctx), (instPath), (assocClass), \
        (resultClass), (role), (resultRole), (properties), \
        (filterQueryLanguage), (filterQuery), (rc)))
#else
static inline CMPIEnumeration *CBAssociatorsFiltered(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    const char **properties,
    const char *filterQueryLanguage,
    const char *filterQuery,
    CMPIStatus *rc)
{
    return mb->bft->associatorsFiltered(mb, ctx, instPath, assocClass,
        resultClass, role, resultRole, properties, filterQueryLanguage,
        filterQuery, rc);
}
#endif

/** @brief Enumerate the instances referencing a given source instance,
         returning only those that match the given filters.

    @param mb CMPIBroker structure.
    @param ctx CMPIContext object.
    @param instPath Instance path of the given source instance.
    @param resultClass If not NULL, a valid class name that acts as a filter on
        the returned set of instances by mandating that each returned instance
        shall be either an instance of this class or one of its subclasses.
    @param role If not NULL, a valid property name that acts as a filter on the
        returned set of instances by mandating that each returned instance
        shall be associated to the source instance via an association in which
        the source instance plays the specified role.
    @param properties Property list controlling the properties in the returned
        instances: Each returned instance will not include properties missing
        from this list. If @ properties is NULL, all properties will be
        included in each returned instance.
    @param filterQueryLanguage Query language used by @p filterQuery (no
        filtering when NULL).
    @param filterQuery Query for filtering the result (no filtering when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return A new CMPIEnumeration object containing CMPIInstance objects that
        represent the enumerated instances.
    @fulldescription CMPIBrokerFT.referencesFiltered()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBReferencesFiltered(mb, ctx, instPath, resultClass, role, properties, \
            filterQueryLanguage, filterQuery, rc) \
    ((mb)->bft->referencesFiltered((mb), (ctx), (instPath), (resultClass), \
        (role), (properties), (filterQueryLanguage), (filterQuery), (rc)))
#else
static inline CMPIEnumeration *CBReferencesFiltered(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *instPath,
    const char *resultClass,
    const char *role,
    const char **properties,
    const char *filterQueryLanguage,
    const char *filterQuery,
    CMPIStatus *rc)
{
    return mb->bft->referencesFiltered(mb, ctx, instPath, resultClass, role,
        properties, filterQueryLanguage, filterQuery, rc);
}
#endif

/** @brief Create a new CMPIInstance object initialized to a given instance
        path.

    @param mb CMPIBroker structure.
    @param instPath The class path or instance path for the new CMPIInstance
        object.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIInstance object.
    @fulldescription CMPIBrokerEncFT.newInstance()
    @examples
    @code (.c)
    CMPIStatus testProvEnumInstances (CMPIInstanceMI *cThis,
        const CMPIContext *ctx, const CMPIResult *rslt,
        const CMPIObjectPath *ref, const char **properties)
    {
        int i;
        CMPIStatus rc;
        CMPIObjectPath *cop;
        CMPIInstance *inst;

        cop = CMNewObjectPath(
                  broker,
                  CMGetCharsPtr(CMGetNameSpace(ref, &rc), NULL),
                  CMGetCharsPtr(CMGetClassName (ref, &rc),NULL),
                  &rc);
        for (i = 0; i < dataNext; i++)
        {
            CMAddKey (cop, "Identifier", &store[i].key, CMPI_string);
            inst = CMNewInstance (broker, cop, &rc);
            CMSetProperty (inst, "Identifier", &store[i].key, CMPI_string);
            CMSetProperty (inst, "data", &store[i].data, CMPI_string);
            CMReturnInstance (rslt, inst);
        }
        CMReturnDone (rslt);
        CMReturn (CMPI_RC_OK);
    }
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS AM: Example is too complex for this function. Simplify.
*/
#ifdef CMPI_NO_INLINE
#define CMNewInstance(mb, instPath, rc) \
    ((mb)->eft->newInstance((mb), (instPath), (rc)))
#else
static inline CMPIInstance *CMNewInstance (
    const CMPIBroker *mb,
    const CMPIObjectPath *instPath,
    CMPIStatus *rc)
{
    return mb->eft->newInstance(mb, instPath, rc);
}
#endif

/** @brief Create a new CMPIObjectPath initialized to a given namespace and
        class name.

    @param mb CMPIBroker structure.
    @param ns Namespace name.
    @param cn Class name.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIObjectPath object.
    @fulldescription CMPIBrokerEncFT.newObjectPath()
    @examples
    @code (.c)
    const char* class = "myClass";
    CMPIObjectPath *objPath = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    objPath = CMNewObjectPath (broker, ns, class, &rc);
    assert ( rc.rc == CMPI_RC_OK);
    CMAddKey (objPath, "ElementName", (CMPIValue *) class, CMPI_chars);
    @endcode
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewObjectPath(mb, ns, cn, rc) \
    ((mb)->eft->newObjectPath((mb), (ns), (cn), (rc)))
#else
static inline CMPIObjectPath *CMNewObjectPath (
    const CMPIBroker *mb,
    const char *ns,
    const char *cn,
    CMPIStatus *rc)
{
    return mb->eft->newObjectPath(mb, ns, cn, rc);
}
#endif

/** @brief Create a new CMPIArgs object initialized to have no method
        parameters.

    @param mb CMPIBroker structure.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIArgs object.
    @fulldescription CMPIBrokerEncFT.newArgs()
    @examples
    @code (.c)
    CMPIArgs *args_ptr = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    args_ptr = CMNewArgs(_broker, &rc);
    @endcode
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewArgs(mb, rc) \
    ((mb)->eft->newArgs((mb), (rc)))
#else
static inline CMPIArgs *CMNewArgs (
    const CMPIBroker *mb,
    CMPIStatus *rc)
{
    return mb->eft->newArgs(mb, rc);
}
#endif

/** @brief Create a new CMPIString object initialized from a C-language string.

    @param mb CMPIBroker structure.
    @param data	C-language string.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIString object.
    @fulldescription CMPIBrokerEncFT.newString()
    @examples
    @code (.c)
    CMPIStatus rc;
    CMPIString *cmpiStr1;
    CMPIString *cmpiStr2;
    cmpiStr1 = CMNewString(_broker, NULL, &rc);
    // test rc for OK
    cmpiStr2 = CMNewString(_broker, "Tracing for level 5", &rc);
    // test rc for OK
    @endcode
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS AM: Clarify whether NULL is allowed as `data` argument.
        The example in the convenience function specifies NULL, but the 2.1 and
        2.0 specs are silent about whether NULL is allowed.@n
        Karl to double check in the implementation.
*/
#ifdef CMPI_NO_INLINE
#define CMNewString(mb, data, rc) \
    ((mb)->eft->newString((mb), (data), (rc)))
#else
static inline CMPIString *CMNewString (
    const CMPIBroker *mb,
    const char *data,
    CMPIStatus *rc)
{
    return mb->eft->newString(mb, data, rc);
}
#endif

/** @brief Create a new CMPIArray object of a given size and type of elements.

    @param mb CMPIBroker structure.
    @param size Size of the array. A value of 0 is valid and specifies an empty
        array.
    @param type Type of each array element.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIArray object.
    @fulldescription CMPIBrokerEncFT.newArray()
    @statusopenpegasus Tested in cmpiTestMethodProvider.c
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewArray(mb, size, type, rc) \
    ((mb)->eft->newArray((mb), (size), (type), (rc)))
#else
static inline CMPIArray *CMNewArray (
    const CMPIBroker *mb,
    CMPICount size,
    CMPIType type,
    CMPIStatus *rc)
{
    return mb->eft->newArray(mb, size, type, rc);
}
#endif

/** @brief Create a new CMPIDataTime object to the current date and time.

    @param mb CMPIBroker structure.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIDateTime object.
    @fulldescription CMPIBrokerEncFT.newDateTime()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTime(mb, rc) \
    ((mb)->eft->newDateTime((mb), (rc)))
#else
static inline CMPIDateTime *CMNewDateTime (
    const CMPIBroker *mb,
    CMPIStatus *rc)
{
    return mb->eft->newDateTime(mb, rc);
}
#endif

/** @brief Create a new CMPIDateTime object initialized to a specific value.

    CMNewDateTimeFromBinary() executes CMPIBrokerEncFT.newDateTimeFromBinary()
    to create a new CMPIDateTime object initialized from @p binTime.

    @param mb CMPIBroker structure.
    @param binTime When `interval` is false, a point in time value expressed as
        a 64-bit unsigned integer in microseconds since 00:00:00 GMT, January
        1, 1970. Otherwise, a time interval expressed as a 64-bit unsigned
        integer in microseconds.
    @param interval If true, indicates that `binTime` is considered to be a
        time interval.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIDateTime object.
    @fulldescription CMPIBrokerEncFT.newDateTimeFromBinary()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTimeFromBinary(mb, binTime, interval, rc) \
    ((mb)->eft->newDateTimeFromBinary((mb), (binTime), (interval), (rc)))
#else
static inline CMPIDateTime *CMNewDateTimeFromBinary(
    const CMPIBroker *mb,
    CMPIUint64 binTime,
    CMPIBoolean interval,
    CMPIStatus *rc)
{
    return mb->eft->newDateTimeFromBinary(mb, binTime, interval, rc);
}
#endif

/** @brief Create a new CMPIDateTime object initialized to a specified value.

    @param mb CMPIBroker structure.
    @param datetime Date/time value to be used for the new object in the string
        format for CIM datetime values defined in @ref ref-dmtf-dsp0004
        "DSP0004". Both the interval and point in time formats are supported.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIDateTime object.
    @fulldescription CMPIBrokerEncFT.newDateTimeFromChars()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTimeFromChars(mb, datetime, rc) \
    ((mb)->eft->newDateTimeFromChars((mb), (datetime), (rc)))
#else
static inline CMPIDateTime *CMNewDateTimeFromChars(
    const CMPIBroker *mb,
    const char *datetime,
    CMPIStatus *rc)
{
    return mb->eft->newDateTimeFromChars(mb, datetime, rc);
}
#endif

/** @brief Create a new CMPISelectExp object initialized from a select
        expression specified in a query language.

    @param mb CMPIBroker structure.
    @param query Select expression.
    @param lang Query language.
    @param [out] projection A new CMPIArray object of CMPIString entries
        containing the projection specification.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPISelectExp object.
    @fulldescription CMPIBrokerEncFT.newSelectExp()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewSelectExp(mb, query, lang, projection, rc) \
    ((mb)->eft->newSelectExp((mb), (query), (lang), (projection), (rc)))
#else
static inline CMPISelectExp *CMNewSelectExp(
    const CMPIBroker *mb,
    const char *query,
    const char *lang,
    CMPIArray **projection,
    CMPIStatus *rc)
{
    return mb->eft->newSelectExp(mb, query, lang, projection, rc);
}
#endif

#ifdef CMPI_VER_200
/** @brief Create a new CMPIError object initialized with certain core
        attributes.

    @param mb CMPIBroker structure.
    @param owner Value for the `OwningEntity` attribute of the CMPIError object.
        For a description of the `OwningEntity` attribute, see the description
        of the `OwningEntity` property in the `CIM_Error` class in the CIM
        Schema. If the error message is defined in a DMTF message registry, the
        string value of owner shall be the content of the OWNING_ENTITY element
        defined for the registry.
    @param msgID Value for the `MessageID` attribute of the CMPIError object.
        For a description of the `MessageID` attribute, see the description of
        the `MessageID` property in the `CIM_Error` class in the CIM Schema. If
        the error message is defined in a DMTF message registry, the string
        value of @p msgID shall be the message ID defined for the message in
        the registry (the concatenation of the values of the PREFIX and
        SEQUENCE_NUMBER attributes of the MESSAGE_ID element for the message).
    @param msg Value for the `Message` attribute of the CMPIError object. For a
        description of the `Message` attribute, see the description of the
        `Message` property in the `CIM_Error` class in the CIM Schema. This
        message is the formatted and translated message, with any dynamic
        values expanded.
    @param sev Value for the `PerceivedSeverity` attribute of the CMPIError
        object. For a description of the `PerceivedSeverity` attribute, see the
        description of the `PerceivedSeverity` property in the `CIM_Error`
        class in the CIM Schema. If the error message is defined in a DMTF
        message registry, the string value of @p sev shall be the content of
        the PERCEIVED_SEVERITY element defined for the message in the registry.
    @param pc value for the `ProbableCause` attribute of the CMPIError
        object. For a description of the `ProbableCause` attribute, see the
        description of the `ProbableCause` property in the `CIM_Error` class in
        the CIM Schema. If the error message is defined in a DMTF message
        registry, note that the string value of @p pc is not defined in the
        message in the registry.
    @param cimStatusCode Value for the `CIMStatusCode` attribute of the
        CMPIError object. For a description of the `CIMStatusCode` attribute,
        see the description of the `CIMStatusCode` property in the `CIM_Error`
        class in the CIM Schema. Not all status codes are valid for each
        operation. The specification for each MI function defines the status
        codes that may be returned. If the error message is defined in a DMTF
        message registry, cimStatusCode shall reflect the content of the
        CIMSTATUSCODE element defined for the message in the registry.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIError object.
    @fulldescription CMPIBrokerEncFT.newCMPIError()
    @examples
    @code (.c)
    cmpiError = CMNewCMPIError(_broker, inOwningEntity, inMsgID, inMsg,
                    inSev, inPc, inCIMStatusCode, &rc);
    @endcode
    @added200
    @statusopenpegasus Tested in TestCMPIErrorProvider.c
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewCMPIError(mb, owner, msgID, msg, sev, pc, cimStatusCode, rc)  \
    ((mb)->eft->newCMPIError((mb), (owner), (msgID), (msg), (sev), \
                             (pc), (cimStatusCode), (rc)))
#else
static inline CMPIError * CMNewCMPIError(
    const CMPIBroker *mb,
    const char *owner,
    const char* msgID,
    const char* msg,
    const CMPIErrorSeverity sev,
    const CMPIErrorProbableCause pc,
    const CMPIrc cimStatusCode,
    CMPIStatus *rc)
{
    return mb->eft->newCMPIError(mb, owner, msgID, msg, sev, pc, cimStatusCode,
                                 rc);
}
#endif
#endif /* CMPI_VER_200 */

#ifdef CMPI_VER_210
/** @brief Create a new CMPIPropertyList object initialized to a list of
        property names.

    @param mb CMPIBroker structure.
    @param properties The property names in the property list, in any order and
        in any lexical case.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIPropertyList object.
    @fulldescription CMPIBrokerEncFT.newPropertyList()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewCMPIPropertyList(mb, properties, rc) \
    ((mb)->eft->newPropertyList((mb), (properties), (rc)))
#else
static inline CMPIPropertyList *CMNewCMPIPropertyList(
    const CMPIBroker *mb,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->eft->newPropertyList(mb, properties, rc);
}
#endif
#endif /* CMPI_VER_210 */

#ifdef CMPI_VER_210
/** @brief Create a new CMPIString object from a C-language string in a
         specific codepage.

    @param mb CMPIBroker structure.
    @param data C-language string represented in the codepage specified in
        @p cpid. @p data is used to initialize the new CMPIString object after
        converting it from its codepage to UTF-8.
    @param cpid CMPI-specific codepage ID for the codepage that is used to
        interpret the Bytes in the @p data argument. See @ref CMPICodepageID
        for a list of supported codepages and their codepage ID values.
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIString object.
    @fulldescription CMPIBrokerEncFT.newStringCP()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewCMPIStringCP(mb, data, cpid, rc) \
    ((mb)->eft->newStringCP((mb), (data), (cpid), (rc)))
#else
static inline CMPIString *CMNewCMPIStringCP(
    const CMPIBroker *mb,
    const char* data,
    const CMPICodepageID cpid,
    CMPIStatus *rc)
{
    return mb->eft->newStringCP(mb, data, cpid, rc);
}
#endif
#endif /* CMPI_VER_210 */

#ifdef CMPI_VER_210
/** @brief Create a new CMPIEnumerationFilter object initialized with a
        filter query.

    @param mb CMPIBroker structure.
    @param filterQueryLanguage Query language used by @p filterQuery (no
        filtering when NULL).
    @param filterQuery Filter query (no filtering when NULL).
    @param [out] rc Function return status (suppressed when NULL).
    @return The new CMPIEnumerationFilter object.
    @fulldescription CMPIBrokerEncFT.newEnumerationFilter()
    @added210
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewCMPIEnumerationFilter(mb, filterQueryLanguage, filterQuery, rc) \
    ((mb)->eft->newEnumerationFilter((mb), (filterQueryLanguage), \
        (filterQuery), (rc)))
#else
static inline CMPIEnumerationFilter *CMNewCMPIEnumerationFilter(
    const CMPIBroker *mb,
    const char* filterQueryLanguage,
    const char* filterQuery,
    CMPIStatus *rc)
{
    return mb->eft->newEnumerationFilter(mb, filterQueryLanguage, filterQuery,
        rc);
}
#endif
#endif /* CMPI_VER_210 */

/** @brief Test whether a class path is of a specified class or any of its
        subclasses.

    @param mb CMPIBroker structure.
    @param classPath Class path that is being tested.
    @param className Class name to be tested for.
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The class path is of the specified class or any of that
        class's subclasses.
    @retval false The class path is not of the specified class nor any of that
        class's subclasses.
    @fulldescription CMPIBrokerEncFT.classPathIsA()
    @changed210 The className argument was named type and documented incorrectly
        prior to CMPI 2.1. However, the code did execute correctly.
    @statusopenpegasus Not tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMClassPathIsA(mb, classPath, className, rc) \
    ((mb)->eft->classPathIsA((mb), (classPath), (className), (rc)))
#else
static inline CMPIBoolean CMClassPathIsA(
    const CMPIBroker *mb,
    const CMPIObjectPath *classPath,
    const char *className,
    CMPIStatus *rc)
{
    return mb->eft->classPathIsA(mb, classPath, className, rc);
}
#endif

/** @brief Convert an encapsulated data type object into a string
        representation.

    @param mb CMPIBroker structure.
    @param object Encapsulated data type object.
    @param [out] rc Function return status (suppressed when NULL).
    @return MB implementation-specific string representation of the
        encapsulated data type object.
    @fulldescription CMPIBrokerEncFT.toString()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CDToString(mb, object, rc) \
    ((mb)->eft->toString((mb), (void*)(object), (rc)))
#else
static inline CMPIString *CDToString(
    const CMPIBroker *mb,
    const void *object,
    CMPIStatus *rc)
{
    return mb->eft->toString(mb, (void *)object, rc);
}
#endif

/** @brief Test whether an encapsulated data type object is of a specified CMPI
        type.

    @param mb CMPIBroker structure.
    @param object Encapsulated data type object.
    @param type Type name of the encapsulated data type to be tested for (e.g.,
        "CMPIInstance").
    @param [out] rc Function return status (suppressed when NULL).
    @retval true The object is of the specified CMPI type.
    @retval false The object is not of the specified CMPI type.
    @fulldescription CMPIBrokerEncFT.isOfType()
    @examples
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPIBoolean isOfType = 0;
    CMInstance* inst = CMNewInstance(_broker, . . .);
    isOfType = CDIsOfType (_broker, inst, "CMPIInstance", &rc);
    assert(isOfType);
    @endcode
    @statusopenpegasus Tested
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CDIsOfType(mb, object, type, rc) \
    (mb)->eft->isOfType((mb), (void*)(object), (type), (rc))
#else
static inline CMPIBoolean CDIsOfType(
    const CMPIBroker *mb,
    const void *object,
    const char *type,
    CMPIStatus *rc)
{
    return mb->eft->isOfType(mb, (void *)object, type, rc);
}
#endif

/** @brief Get the type name of an ensapsulated data type object.

    @param mb CMPIBroker structure.
    @param object Encapsulated data type object.
    @param [out] rc Function return status (suppressed when NULL).
    @return Type name of the encapsulated data type (e.g., "CMPIInstance").
    @fulldescription CMPIBrokerEncFT.getType()
    @statusopenpegasus TBD
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CDGetType(mb, object, rc) \
    ((mb)->eft->getType((mb), (void*)(object), (rc)))
#else
static inline CMPIString *CDGetType(
    const CMPIBroker *mb,
    const void *object,
    CMPIStatus *rc)
{
    return mb->eft->getType(mb, object, rc);
}
#endif

/** @brief Get a translated MB implementation-specific message text by message
         ID. (**Deprecated**)

    @param mb CMPIBroker structure.
    @param msgId Message ID that is used by the MB to locate a message
         template. The message ID values and corresponding message templates
         are MB implementation-specific.
    @param defMsg The default message. See the full description for details.
    @param [out] rc Function return status (suppressed when NULL).
    @param args The message insert values, specified as @ref cmfmt-args
        "CMFmtArgs\<N\>(\<vlist\>)", where \<N\> is the number of values, and
        \<vlist\> is a comma-separated list of @ref cmfmt-val
        "CMFmt\<type\>(\<v\>)" macros.
    @return Points to a CMPIString object representing the translated message.
    @fulldescription CMPIBrokerEncFT.getMessage()
    @examples
    Assuming the message identified by the message ID is the same as the
    default message "Test $0 $1", the following example creates a message "Test
    message 42" where "message" is passed as a C string for the first message
    trigger ($0), and "42" is passed as an integer for the second message
    trigger ($1):
    @code (.c)
    CMGetMessage(_broker, "msgid", "Test $0 $1",
        NULL, CMFmtArgs2(CMFmtChars("message"), CMFmtSint(42)));
    @endcode
    @deprecated This function is deprecated since CMPI 2.1. Use
        CMGetMessage2() instead.
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMGetMessage(mb, msgId, defMsg, rc, args) \
    ((mb)->eft->getMessage((mb), (msgId), (defMsg), (rc), args))

/** @brief Log a diagnostic message.

    @param mb CMPIBroker structure.
    @param severity Severity of the log message. Severity levels are defined in
        @ref CMPISeverity.
    @param id If not NULL, message ID or any other identifying string.
    @param text If not NULL, message text to be logged.
    @param string If not NULL, message text to be logged. @p string will be
        ignored when @p text is not NULL.
    @return Function return status.
    @examples
    @code (.c)
    CMLogMessage(_broker, 1, "TestProvider",
                 "Entering EnumerateInstance", NULL);
    @endcode
    @fulldescription CMPIBrokerEncFT.logMessage()
    @statusopenpegasus Tested in cmpiTestMethodProvider.c
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMLogMessage(mb, severity, id, text, string)  \
    ((mb)->eft->logMessage((mb), (severity), (id), (text), (string)))
#else
static inline CMPIStatus CMLogMessage(
    const CMPIBroker *mb,
    int severity,
    const char *id,
    const char *text,
    const CMPIString *string)
{
    return mb->eft->logMessage(mb, severity, id, text, string);
}
#endif

/** @brief Trace a diagnostic message with a specific trace level and
        component.

    @param mb CMPIBroker structure.
    @param level Trace level of the message. Trace levels are defined in @ref
        CMPILevel.
    @param component If not NULL, MI implementation-specific component ID.
    @param text If not NULL, message text to be traced.
    @param string If not NULL, message text to be logged. @p string will be
        ignored when @p text is not NULL.
    @return Function return status.
    @fulldescription CMPIBrokerEncFT.trace()
    @examples
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPIString *str = CMNewString(_broker, "CMTraceMessage", &rc);
    rc = CMTraceMessage(_broker, 4, "Authorization", NULL, str);
    @endcode
    @statusopenpegasus Tested in cmpiTestMethodProvider.c. Uses CMPILevel as
    @hideinitializer
        type, not int.
*/
#ifdef CMPI_NO_INLINE
#define CMTraceMessage(mb, level, component, text, string)  \
    ((mb)->eft->trace((mb), (level), (component), (text), (string)))
#else
static inline CMPIStatus CMTraceMessage(
    const CMPIBroker *mb,
    int level,
    const char *component,
    const char *text,
    const CMPIString *string)
{
    return mb->eft->trace(mb, level, component, text, string);
}
#endif

#ifdef CMPI_VER_200
/** @brief Open a message file and return a handle to the file.

    Depends on whether the MB supports the @ref cap-translation "Message
    Translation" capability.

    @param mb CMPIBroker structure.
    @param msgFile Implementation-specific file path to the message file, or a
        part thereof.
    @param [out] msgFileHandle Handle representing the open message file.
    @return Function return status
    @fulldescription CMPIBrokerEncFT.openMessageFile()
    @examples
    @code (.c)
    CMOpenMessageFile(_broker, "/path/msgFile", &msgFileHandle);
    @endcode
    @added200
    @statusopenpegasus Used
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMOpenMessageFile(mb, msgFile, msgFileHandle) \
    ((mb)->eft->openMessageFile((mb), (msgFile), (msgFileHandle)))
#else
static inline CMPIStatus CMOpenMessageFile(
    const CMPIBroker *mb,
    const char *msgFile,
    CMPIMsgFileHandle *msgFileHandle)
{
    return mb->eft->openMessageFile(mb, msgFile, msgFileHandle);
}
#endif
#endif /* CMPI_VER_200 */

#ifdef CMPI_VER_200
/** @brief Close a message file.

    @param mb CMPIBroker structure.
    @param msgFileHandle Handle representing the open message file.
    @return Function return status.
    @fulldescription CMPIBrokerEncFT.closeMessageFile()
    @examples
    @code (.c)
    CMPIString *msg;
    rc = CMOpenMessageFile(_broker, path, &msgFileHandle);
    msg = CMGetMessage2 (_broker,
        "Common.CIMStatusCode.CIM_ERR_SUCCESS",
        msgFileHandle,
        "Test $0 $1, $2, $3, $4, $5, $6, $7, $8",
        &rc,
        CMFmtArgs9(CMFmtChars("Sint32, Uint32, Sint64, Uint64, Real64,"
            " Boolean, chars, String :: "), CMFmtSint(-1),
            CMFmtUint(1), CMFmtSint64(-64), CMFmtUint64(64),
            CMFmtReal(64.64), CMFmtBoolean(1),
            CMFmtChars("chars"), CMFmtString(cmpiStr)));
    // . . . do something with msg
    rc = CMCloseMessageFile(_broker, msgFileHandle);
    @endcode
    @added200
    @statusopenpegasus Tested in cmpiTestBrokerEncProvider.c
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMCloseMessageFile(mb, msgFileHandle) \
    ((mb)->eft->closeMessageFile((mb), (msgFileHandle)))
#else
static inline CMPIStatus CMCloseMessageFile(
    const CMPIBroker *mb,
    const CMPIMsgFileHandle msgFileHandle)
{
    return mb->eft->closeMessageFile(mb, msgFileHandle);
}
#endif
#endif /* CMPI_VER_200 */

#ifdef CMPI_VER_200
/** @brief Get a translated message text from an open message file by
        message ID.

    @param mb CMPIBroker structure.
    @param msgId The message identifier.
    @param msgFileHandle The handle representing the open message file.
    @param defMsg The default message. See the full description for details.
    @param [out] rc Function return status (suppressed when NULL).
    @param args The message insert values, specified as @ref cmfmt-args
        "CMFmtArgs\<N\>(\<vlist\>)", where \<N\> is the number of values, and
        \<vlist\> is a comma-separated list of @ref cmfmt-val
        "CMFmt\<type\>(\<v\>)" macros.
    @return Points to a CMPIString object representing the translated message.
    @fulldescription CMPIBrokerEncFT.getMessage2()
    @examples
    Assuming the message identified by the message ID is the same as the
    default message "Test $0 $1", the following example creates a message "Test
    message 42" where "message" is passed as a C string for the first message
    trigger ($0), and "42" is passed as an integer for the second message
    trigger ($1):
    @code (.c)
    CMGetMessage2(_broker, "msgid", msgFileHandle, "Test $0 $1",
        NULL, CMFmtArgs2(CMFmtChars("message"), CMFmtSint(42)));
    @endcode
    @added200
    @statusopenpegasus Tested in cmpiTestBrokerEncProvider.c
    @hideinitializer
*/
#define CMGetMessage2(mb, msgId, msgFileHandle, defMsg, rc, args) \
    ((mb)->eft->getMessage2((mb), (msgId), (msgFileHandle), (defMsg), (rc), \
                            args))
#endif /* CMPI_VER_200 */

/**
    @defgroup cmfmt-args CMFmtArgs\<N\>()
    @{
      @brief Helper macros for message translation.

      These macros are used for the @p args argument of CMGetMessage() and
      CMGetMessage2().

      The argument of each of these macros is a comma-separated list of
      invocations of the @ref cmfmt-val "CMFmt\<type\>(\<v\>)" macros.

      @see CMGetMessage(), CMGetMessage2() for example code
*/

/// Args value for no message insert pairs
#define CMFmtArgs0() 0
/// Args value for 1 message insert pair
#define CMFmtArgs1(v1) \
                 1,v1
/// Args value for 2 message insert pairs
#define CMFmtArgs2(v1,v2) \
                 2,v1,v2
/// Args value for 3 message insert pairs
#define CMFmtArgs3(v1,v2,v3) \
                 3,v1,v2,v3
/// Args value for 4 message insert pairs
#define CMFmtArgs4(v1,v2,v3,v4) \
                 4,v1,v2,v3,v4
/// Args value for 5 message insert pairs
#define CMFmtArgs5(v1,v2,v3,v4,v5) \
                 5,v1,v2,v3,v4,v5
/// Args value for 6 message insert pairs
#define CMFmtArgs6(v1,v2,v3,v4,v5,v6) \
                 6,v1,v2,v3,v4,v5,v6
/// Args value for 7 message insert pairs
#define CMFmtArgs7(v1,v2,v3,v4,v5,v6,v7) \
                 7,v1,v2,v3,v4,v5,v6,v7
/// Args value for 8 message insert pairs
#define CMFmtArgs8(v1,v2,v3,v4,v5,v6,v7,v8) \
                 8,v1,v2,v3,v4,v5,v6,v7,v8
/// Args value for 9 message insert pairs
#define CMFmtArgs9(v1,v2,v3,v4,v5,v6,v7,v8,v9) \
                 9,v1,v2,v3,v4,v5,v6,v7,v8,v9
/// Args value for 10 message insert pairs
#define CMFmtArgs10(v1,v2,v3,v4,v5,v6,v7,v8,v9,v10) \
                 10,v1,v2,v3,v4,v5,v6,v7,v8,v9,v10

/**
    @}
    @defgroup cmfmt-val CMFmt\<type\>()
    @{
      @brief Helper macros for message translation.

      These macros are used in context of CMGetMessage() and CMGetMessage2(), as
      a comma-separated list of arguments to @ref cmfmt-args
      "CMFmtArgs\<N\>()".

      Each of these macros represents a message insert pair consisting of type
      and value.

      The argument of each of these macros is a value that is used to expand a
      message trigger ("$0", etc.) in the message.

      @see CMGetMessage(), CMGetMessage2() for example code
*/

/// Message insert pair for a signed integer value up to 32-bit
#define CMFmtSint(v)    CMPI_sint32,((long int)v)
/// Message insert pair for an unsigned integer value up to 32-bit
#define CMFmtUint(v)    CMPI_uint32,((unsigned long int)v)
/// Message insert pair for a signed integer value up to 64-bit
#define CMFmtSint64(v)  CMPI_sint64,((long long int)v)
/// Message insert pair for an unsigned integer value up to 64-bit
#define CMFmtUint64(v)  CMPI_uint64,((unsigned long long int)v)
/// Message insert pair for a CIM real64 value
#define CMFmtReal(v)    CMPI_real64,((double)v)
/// Message insert pair for a boolean value
#define CMFmtBoolean(v) CMPI_boolean,((int)v)
/// Message insert pair for a C string value
#define CMFmtChars(v)   CMPI_chars,((char*)v)
/// Message insert pair for a CMPIString value
#define CMFmtString(v)  CMPIString,((CMPIString*)v)

/**
   @}
*/


/**
  @}
  @addtogroup convenience-func-mi-factory-stubs
  @{
    MI Factory Stubs.

    The MI factory stubs are macros that generate the the @ref mi-factory
    "MI factory functions" and function tables.
*/

/** @brief Generate function table and factory function for an instance MI
        written in plain C.

    The CMInstanceMIStub() macro generates the function table and factory
    function for an instance MI (also known as *instance provider*)

    This macro is for CMPI MIs written in plain C. The code can be compiled with
    C or C++.

    The generated factory function is an @ref mi-factory-specific
    "MI-specific factory function" named `\<miname\>_Create_InstanceMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    instance MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    While the generated function table is a global variable in the MI file
    calling this macro, it should not be accessed directly by any MI code or in
    the code specified by the @p hook argument. Instead, the CMInitHook() macro
    should be used.

    Because the name of the global variable for the generated function table
    does not include the MI name, there is a limitation of one generated
    instance MI per source file; that is, this macro can be called at most
    once in a particular compile unit.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>\<pfx\>Cleanup()</TD>
        <TD>CMPIInstanceMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>EnumInstanceNames()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstanceNames()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>EnumInstances()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstances()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>GetInstance()</TD>
        <TD>CMPIInstanceMIFT.getInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>CreateInstance()</TD>
        <TD>CMPIInstanceMIFT.createInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>ModifyInstance()</TD>
        <TD>CMPIInstanceMIFT.modifyInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>DeleteInstance()</TD>
        <TD>CMPIInstanceMIFT.deleteInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>ExecQuery()</TD>
        <TD>CMPIInstanceMIFT.execQuery()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>EnumInstancesFiltered()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstancesFiltered()</TD><TD>2.1</TD></TR>
    </TABLE>
    @note For historical reasons, the name of the \<pfx\>Cleanup() function is
        not following the format \<pfx\>\<mitype\>Cleanup() used for the
        cleanup functions of the other MI types.
    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param miname The MI name for this MI.
        This is a character string without quotes.
    @param mbvar The name of a variable that upon return of the macro will have
        been updated with the CMPIBroker pointer passed by the MB to the
        factory function.
        This is a character string without quotes.
    @param hook
    @parblock
        A single C statement that is executed in the generated factory
        function, after the CMPIInstanceMI structure has been created. This is
        a character string without quotes, and without a trailing semicolon.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or CMInitHook(),
        or @ref CMNoHook if no further intialization is required.

        While that C statement is executed in the local scope of the factory
        function, it should not access the arguments or local variables of the
        factory function. Instead, the CMInitHook() macro should be used.
    @endparblock
    @return A pointer to the function table of this MI.
    @examples
    This example uses the CMInstanceMIStub() macro for an instance MI written
    in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

    static CMPIStatus MyProvInstanceInitialize(
        CMPIInstanceMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIInstanceMI object
        mi->ft->miVersion = 700; // Override the default MI version
        if (...error...)
            CMReturn(CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvCleanup (
        CMPIInstanceMI *mi,
        const CMPIContext *ctx,
        CMPIBoolean terminating)
    {
        . . . // Clean up code when unloading the MI load library
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvEnumInstanceNames (
        CMPIInstanceMI *mi,
        const CMPIContext *ctx,
        const CMPIResult *rslt,
        const CMPIObjectPath *classPath)
    {
        . . . // for an example, see TBD
        CMReturn(CMPI_RC_OK);
    }

    // Example of a function that is not going to be implemented.
    static CMPIStatus MyProvExecQuery (
        CMPIInstanceMI *mi,
        const CMPIContext *ctx,
        const CMPIResult *rslt,
        const CMPIObjectPath *classPath,
        const char *query,
        const char *lang)
    {
        CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
    }

    // Other functions not shown are:
    //    MyProvEnumInstances
    //    MyProvGetInstance
    //    MyProvCreateInstance
    //    MyProvModifyInstance
    //    MyProvDeleteInstance
    //    MyProvEnumerateInstancesFiltered

    CMInstanceMIStub(MyProv, MyProv, _broker, CMInitHook(MyProv,Instance));
    @endcode
    @see CMPIInstanceMI, CMPIInstanceMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TBD KS: We have first cut at example.  Is this the way to go or would
        we be better with complete provider in an examples section?@n AM: I
        think the example is good enough for the factory function. What would
        be good to have are the actual provider functions, somewhere. That is
        too much for this particular macro.
*/
#define CMInstanceMIStub(pfx, miname, mbvar, hook) \
static CMPIInstanceMIFT instMIFT__ = { \
    CMPI_VERSION, \
    CMPI_VERSION, \
    "instance" #miname, \
    pfx##Cleanup, \
    pfx##EnumInstanceNames, \
    pfx##EnumInstances, \
    pfx##GetInstance, \
    pfx##CreateInstance, \
    pfx##ModifyInstance, \
    pfx##DeleteInstance, \
    pfx##ExecQuery, \
    _CMInstanceMIStub_EnumInstancesFiltered(pfx) \
}; \
CMPI_EXTERN_C CMPIInstanceMI * miname##_Create_InstanceMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctx, \
    CMPIStatus *rc) \
{ \
    static CMPIInstanceMI mi = { \
        NULL, \
        &instMIFT__, \
    }; \
    (mbvar) = mb; \
    if (rc) \
    { \
        rc->rc = CMPI_RC_OK; \
        rc->msg = NULL; \
    } \
    hook; \
    return &mi;  \
}

/** @brief Generate function table and factory function for an association MI
        written in plain C.

    The CMAssociationMIStub() macro generates the function table and factory
    function for an association MI (also known as *association provider*)

    This macro is for CMPI MIs written in plain C. The code can be compiled with
    C or C++.

    The generated factory function is an @ref mi-factory-specific
    "MI-specific factory function" named `\<miname\>_Create_AssociationMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    association MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    While the generated function table is a global variable in the MI file
    calling this macro, it should not be accessed directly by any MI code or in
    the code specified by the @p hook argument. Instead, the CMInitHook() macro
    should be used.

    Because the name of the global variable for the generated function table
    does not include the MI name, there is a limitation of one generated
    association MI per source file; that is, this macro can be called at most
    once in a particular compile unit.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>\<pfx\>AssociationCleanup()</TD>
        <TD>CMPIAssociationMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>Associators()</TD>
        <TD>CMPIAssociationMIFT.associators()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>AssociatorNames()</TD>
        <TD>CMPIAssociationMIFT.associatorNames()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>References()</TD>
        <TD>CMPIAssociationMIFT.references()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>ReferenceNames()</TD>
        <TD>CMPIAssociationMIFT.referenceNames()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>AssociatorsFiltered()</TD>
        <TD>CMPIAssociationMIFT.associatorsFiltered()</TD><TD>2.1</TD></TR>
    <TR><TD>\<pfx\>ReferencesFiltered()</TD>
        <TD>CMPIAssociationMIFT.referencesFiltered()</TD><TD>2.1</TD></TR>
    </TABLE>
    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param miname The MI name for this MI.
        This is a character string without quotes.
    @param mbvar The name of a variable that upon return of the macro will have
        been updated with the CMPIBroker pointer passed by the MB to the
        factory function.
        This is a character string without quotes.
    @param hook
    @parblock
        A single C statement that is executed in the generated factory
        function, after the CMPIInstanceMI structure has been created. This is
        a character string without quotes, and without a trailing semicolon.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or CMInitHook(),
        or @ref CMNoHook if no further intialization is required.

        While that C statement is executed in the local scope of the factory
        function, it should not access the arguments or local variables of the
        factory function. Instead, the CMInitHook() macro should be used.
    @endparblock
    @return A pointer to the function table of this MI.
    @examples
    This example uses the CMAssociationMIStub() macro for an association MI
    written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

    static CMPIStatus MyProvAssociationInitialize(
        CMPIAssociationMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIAssociationMI object
        mi->ft->miVersion = 700; // Override the default MI version
        if (...error...)
            CMReturn(CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvAssociationCleanup (
        CMPIAssociationMI *mi,
        const CMPIContext *ctx,
        CMPIBoolean terminating)
    {
        . . . // Clean up code when unloading the MI load library
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvAssociators (
        CMPIAssociationMI *mi,
        const CMPIContext *ctx,
        const CMPIResult *rslt,
        const CMPIObjectPath *op,
        const char* assocClass,
        const char* resultClass,
        const char* role,
        const char* resultRole,
        const char** properties)
    {
        . . . // for an example, see TBD
        CMReturn(CMPI_RC_OK);
    }

    // Other functions not shown are:
    //    MyProvAssociatorNames
    //    MyProvReferences
    //    MyProvReferenceNames
    //    MyProvAssociatorsFiltered
    //    MyProvReferencesFiltered

    CMAssociationMIStub(MyProv, MyProv, _broker, CMInitHook(MyProv,
                                                            Association));
    @endcode
    @see CMPIAssociationMI, CMPIAssociationMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TBD KS: Need note about creating function that parallel others but
        with cap@n
        AM: ??
*/
#define CMAssociationMIStub(pfx, miname, mbvar, hook) \
static CMPIAssociationMIFT assocMIFT__ = { \
    CMPI_VERSION, \
    CMPI_VERSION, \
    "association" #miname, \
    pfx##AssociationCleanup, \
    pfx##Associators, \
    pfx##AssociatorNames, \
    pfx##References, \
    pfx##ReferenceNames, \
    _CMAssociationMIStub_AssociatorsFiltered(pfx) \
    _CMAssociationMIStub_ReferencesFiltered(pfx) \
}; \
CMPI_EXTERN_C CMPIAssociationMI * miname##_Create_AssociationMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctx, \
    CMPIStatus *rc) \
{ \
    static CMPIAssociationMI mi = { \
        NULL, \
        &assocMIFT__, \
    }; \
    (mbvar) = mb; \
    if (rc) \
    { \
        rc->rc = CMPI_RC_OK; \
        rc->msg = NULL; \
    } \
    hook; \
    return &mi;  \
}

/** @brief Generate function table and factory function for a method MI
        written in plain C.

    The CMMethodMIStub() macro generates the function table and factory
    function for a method MI (also known as *method provider*)

    This macro is for CMPI MIs written in plain C. The code can be compiled with
    C or C++.

    The generated factory function is an @ref mi-factory-specific
    "MI-specific factory function" named `\<miname\>_Create_MethodMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    method MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    While the generated function table is a global variable in the MI file
    calling this macro, it should not be accessed directly by any MI code or in
    the code specified by the @p hook argument. Instead, the CMInitHook() macro
    should be used.

    Because the name of the global variable for the generated function table
    does not include the MI name, there is a limitation of one generated
    method MI per source file; that is, this macro can be called at most
    once in a particular compile unit.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>\<pfx\>MethodCleanup()</TD>
        <TD>CMPIMethodMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>InvokeMethod()</TD>
        <TD>CMPIMethodMIFT.invokeMethod()</TD><TD>1.0</TD></TR>
    </TABLE>
    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param miname The MI name for this MI.
        This is a character string without quotes.
    @param mbvar The name of a variable that upon return of the macro will have
        been updated with the CMPIBroker pointer passed by the MB to the
        factory function.
        This is a character string without quotes.
    @param hook
    @parblock
        A single C statement that is executed in the generated factory
        function, after the CMPIInstanceMI structure has been created. This is
        a character string without quotes, and without a trailing semicolon.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or CMInitHook(),
        or @ref CMNoHook if no further intialization is required.

        While that C statement is executed in the local scope of the factory
        function, it should not access the arguments or local variables of the
        factory function. Instead, the CMInitHook() macro should be used.
    @endparblock
    @return A pointer to the function table of this MI.
    @examples
    This example uses the CMMethodMIStub() macro for a method MI written in
    plain C.
    @code (.c)
    static const CMPIBroker *_broker;

    static CMPIStatus MyProvMethodInitialize(
        CMPIMethodMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIMethodMI object
        mi->ft->miVersion = 700; // Override the default MI version
        if (...error...)
            CMReturn(CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvMethodCleanup (
        CMPIMethodMI *mi,
        const CMPIContext *ctx,
        CMPIBoolean terminating)
    {
        . . . // Clean up code when unloading the MI load library
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvInvokeMethod (
        CMPIMethodMI *mi,
        const CMPIContext *ctx,
        const CMPIResult *rslt,
        const CMPIObjectPath *objPath,
        const char* method,
        const CMPIArgs* in,
        CMPIArgs* out)
    {
        . . . // for an example, see TBD
        CMReturn(CMPI_RC_OK);
    }

    CMMethodMIStub(MyProv, MyProv, _broker, CMInitHook(MyProv, Method));
    @endcode
    @see CMPIMethodMI, CMPIMethodMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMMethodMIStub(pfx, miname, mbvar, hook) \
static CMPIMethodMIFT methMIFT__ = { \
    CMPI_VERSION, \
    CMPI_VERSION, \
    "method" #miname, \
    pfx##MethodCleanup, \
    pfx##InvokeMethod, \
}; \
CMPI_EXTERN_C CMPIMethodMI * miname##_Create_MethodMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctx, \
    CMPIStatus *rc) \
{ \
    static CMPIMethodMI mi = { \
        NULL, \
        &methMIFT__, \
    }; \
    (mbvar) = mb; \
    if (rc) \
    { \
        rc->rc = CMPI_RC_OK; \
        rc->msg = NULL; \
    } \
    hook; \
    return &mi; \
}

/** @brief Generate function table and factory function for a property MI
        written in plain C (**Deprecated**).

    The CMPropertyMIStub() macro generates the function table and factory
    function for a property MI (also known as *property provider*)

    This macro is for CMPI MIs written in plain C. The code can be compiled with
    C or C++.

    The generated factory function is an @ref mi-factory-specific
    "MI-specific factory function" named `\<miname\>_Create_PropertyMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    property MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    While the generated function table is a global variable in the MI file
    calling this macro, it should not be accessed directly by any MI code or in
    the code specified by the @p hook argument. Instead, the CMInitHook() macro
    should be used.

    Because the name of the global variable for the generated function table
    does not include the MI name, there is a limitation of one generated
    property MI per source file; that is, this macro can be called at most
    once in a particular compile unit.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>\<pfx\>PropertyCleanup()</TD>
        <TD>CMPIPropertyMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>SetProperty()</TD>
        <TD>CMPIPropertyMIFT.setProperty()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>GetProperty()</TD>
        <TD>CMPIPropertyMIFT.getProperty()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>SetPropertyWithOrigin()</TD>
        <TD>CMPIPropertyMIFT.setPropertyWithOrigin()</TD><TD>2.0</TD></TR>
    </TABLE>
    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param miname The MI name for this MI.
        This is a character string without quotes.
    @param mbvar The name of a variable that upon return of the macro will have
        been updated with the CMPIBroker pointer passed by the MB to the
        factory function.
        This is a character string without quotes.
    @param hook
    @parblock
        A single C statement that is executed in the generated factory
        function, after the CMPIInstanceMI structure has been created. This is
        a character string without quotes, and without a trailing semicolon.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or CMInitHook(),
        or @ref CMNoHook if no further intialization is required.

        While that C statement is executed in the local scope of the factory
        function, it should not access the arguments or local variables of the
        factory function. Instead, the CMInitHook() macro should be used.
    @endparblock
    @return A pointer to the function table of this MI.
    @see CMPIPropertyMI, CMPIPropertyMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMPropertyMIStub(pfx, miname, mbvar, hook) \
static CMPIPropertyMIFT propMIFT__ = { \
    CMPI_VERSION, \
    CMPI_VERSION, \
    "property" #miname, \
    pfx##PropertyCleanup, \
    pfx##SetProperty, \
    pfx##GetProperty, \
    _CMPropertyMIStub_SetPropertyWithOrigin(pfx) \
}; \
CMPI_EXTERN_C CMPIPropertyMI * miname##_Create_PropertyMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctx, \
    CMPIStatus *rc) \
{ \
    static CMPIPropertyMI mi = { \
        NULL, \
        &propMIFT__, \
    }; \
    (mbvar) = mb; \
    if (rc) \
    { \
        rc->rc = CMPI_RC_OK; \
        rc->msg = NULL; \
    } \
    hook; \
    return &mi; \
}

/** @brief Generate function table and factory function for an indication MI
        written in plain C.

    The CMIndicationMIStub() macro generates the function table and factory
    function for an indication MI (also known as *indication provider*)

    This macro is for CMPI MIs written in plain C. The code can be compiled with
    C or C++.

    The generated factory function is an @ref mi-factory-specific
    "MI-specific factory function" named `\<miname\>_Create_IndicationMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    indication MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    While the generated function table is a global variable in the MI file
    calling this macro, it should not be accessed directly by any MI code or in
    the code specified by the @p hook argument. Instead, the CMInitHook() macro
    should be used.

    Because the name of the global variable for the generated function table
    does not include the MI name, there is a limitation of one generated
    indication MI per source file; that is, this macro can be called at most
    once in a particular compile unit.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>\<pfx\>IndicationCleanup()</TD>
        <TD>CMPIIndicationMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>AuthorizeFilter()</TD>
        <TD>CMPIIndicationMIFT.authorizeFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>MustPoll()</TD>
        <TD>CMPIIndicationMIFT.mustPoll()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>ActivateFilter()</TD>
        <TD>CMPIIndicationMIFT.activateFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>DeActivateFilter()</TD>
        <TD>CMPIIndicationMIFT.deActivateFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>EnableIndications()</TD>
        <TD>CMPIIndicationMIFT.enableIndications()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>DisableIndications()</TD>
        <TD>CMPIIndicationMIFT.disableIndications()</TD><TD>1.0</TD></TR>
    <TR><TD>\<pfx\>AuthorizeFilterCollection()</TD>
        <TD>CMPIIndicationMIFT.authorizeFilterCollection()</TD><TD>2.1</TD></TR>
    <TR><TD>\<pfx\>ActivateFilterCollection()</TD>
        <TD>CMPIIndicationMIFT.activateFilterCollection()</TD><TD>2.1</TD></TR>
    <TR><TD>\<pfx\>DeActivateFilterCollection()</TD>
        <TD>CMPIIndicationMIFT.deActivateFilterCollection()</TD><TD>2.1</TD></TR>
    </TABLE>
    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param miname The MI name for this MI.
        This is a character string without quotes.
    @param mbvar The name of a variable that upon return of the macro will have
        been updated with the CMPIBroker pointer passed by the MB to the
        factory function.
        This is a character string without quotes.
    @param hook
    @parblock
        A single C statement that is executed in the generated factory
        function, after the CMPIInstanceMI structure has been created. This is
        a character string without quotes, and without a trailing semicolon.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or CMInitHook(),
        or @ref CMNoHook if no further intialization is required.

        While that C statement is executed in the local scope of the factory
        function, it should not access the arguments or local variables of the
        factory function. Instead, the CMInitHook() macro should be used.
    @endparblock
    @return A pointer to the function table of this MI.
    @examples
    This example uses the CMIndicationMIStub() macro for an indication MI
    written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

    static CMPIStatus MyProvIndicationInitialize(
        CMPIIndicationMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIIndicationMI object
        mi->ft->miVersion = 700; // Override the default MI version
        if (...error...)
            CMReturn(CMPI_RC_ERR_FAILED);
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvIndicationCleanup (
        CMPIIndicationMI *mi,
        const CMPIContext *ctx,
        CMPIBoolean terminating)
    {
        . . . // Clean up code when unloading the MI load library
        CMReturn(CMPI_RC_OK);
    }

    static CMPIStatus MyProvAuthorizeFilter (
        CMPIIndicationMI* mi,
        const CMPIContext* ctx,
        const CMPISelectExp* filter,
        const char* className,
        const CMPIObjectPath* classPath,
        const char* owner)
    {
        . . . // for an example, see TBD
        CMReturn(CMPI_RC_OK);
    }

    // Other functions not shown are:
    //    MyProvEnableIndications
    //    MyProvDisableIndications
    //    MyProvMustPoll
    //    MyProvActivateFilter
    //    MyProvDeActivateFilter
    //    MyProvAuthorizeFilterCollection
    //    MyProvActivateFilterCollection
    //    MyProvDeActivateFilterCollection

    CMIndicationMIStub(MyProv, MyProv, _broker, CMInitHook(MyProv, Indication));
    @endcode
    @see CMPIIndicationMI, CMPIIndicationMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMIndicationMIStub(pfx, miname, mbvar, hook) \
static CMPIIndicationMIFT indMIFT__ = { \
    CMPI_VERSION, \
    CMPI_VERSION, \
    "Indication" #miname, \
    pfx##IndicationCleanup, \
    pfx##AuthorizeFilter, \
    pfx##MustPoll, \
    pfx##ActivateFilter, \
    pfx##DeActivateFilter, \
    pfx##EnableIndications, \
    pfx##DisableIndications, \
    _CMIndicationMIStub_AuthorizeFilterCollection(pfx) \
    _CMIndicationMIStub_ActivateFilterCollection(pfx) \
    _CMIndicationMIStub_DeActivateFilterCollection(pfx) \
}; \
CMPI_EXTERN_C CMPIIndicationMI * miname##_Create_IndicationMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctx, \
    CMPIStatus *rc) \
{ \
    static CMPIIndicationMI mi = { \
        NULL, \
        &indMIFT__, \
    }; \
    (mbvar) = mb; \
    if (rc) \
    { \
        rc->rc = CMPI_RC_OK; \
        rc->msg = NULL; \
    } \
    hook; \
    return &mi; \
}

/**
    @brief MI factory stub hook statement specifying additional initialization.

    CMInitHook() is used as a value for the @p hook argument of MI factory stub
    macros for plain C, for specifying that the generated factory function is
    to execute an MI initialization function with the following name and
    signature:
    @code
    CMPIStatus <pfx><mitype>Initialize(
        const CMPI<mitype>MI *mi,
        const CMPIContext *ctx
    );
    @endcode

    @param pfx The prefix for all functions in the MI function table.
        This is a character string without quotes.
    @param mitype The MI type.
        This is a character string without quotes and can be one of:
        @li Instance
        @li Association
        @li Property (**Deprecated**)
        @li Method
        @li Indication
    @see CMInstanceMIStub(), CMAssociationMIStub(), CMMethodMIStub(),
        CMPropertyMIStub(), CMIndicationMIStub()
    @statusopenpegasus Not used
    @hideinitializer
*/
#define CMInitHook(pfx, mitype) \
do { \
    CMPIStatus st = pfx##mitype##Initialize(&mi, ctx); \
    if (st.rc != CMPI_RC_OK) \
    { \
        if (rc) { \
            *rc = st; \
        } \
        return NULL; \
    } \
} while (0)

/**
    @brief MI factory stub hook statement specifying no additional
        initialization.

    @ref CMNoHook is used as a value for the @p hook argument of MI factory
    stub macros for plain C, for specifying that the generated factory function
    is not going to execute any additional initialization code.

    @see CMInstanceMIStub(), CMAssociationMIStub(), CMMethodMIStub(),
        CMPropertyMIStub(), CMIndicationMIStub()
    @statusopenpegasus TBD
    @hideinitializer
*/
#define CMNoHook

#ifdef CMPI_VER_200
#define _CMPropertyMIStub_SetPropertyWithOrigin(pfx) \
    pfx##SetPropertyWithOrigin,
#else
#define _CMPropertyMIStub_SetPropertyWithOrigin(pfx)
#endif

#ifdef CMPI_VER_210
#define _CMInstanceMIStub_EnumInstancesFiltered(pfx) \
    pfx##EnumInstancesFiltered,
#define _CMAssociationMIStub_AssociatorsFiltered(pfx) \
    pfx##AssociatorsFiltered,
#define _CMAssociationMIStub_ReferencesFiltered(pfx) \
    pfx##ReferencesFiltered,
#define _CMIndicationMIStub_AuthorizeFilterCollection(pfx) \
    pfx##AuthorizeFilterCollection,
#define _CMIndicationMIStub_ActivateFilterCollection(pfx) \
    pfx##ActivateFilterCollection,
#define _CMIndicationMIStub_DeActivateFilterCollection(pfx) \
    pfx##DeActivateFilterCollection,
#else
#define _CMInstanceMIStub_EnumInstancesFiltered(pfx)
#define _CMAssociationMIStub_AssociatorsFiltered(pfx)
#define _CMAssociationMIStub_ReferencesFiltered(pfx)
#define _CMIndicationMIStub_AuthorizeFilterCollection(pfx)
#define _CMIndicationMIStub_ActivateFilterCollection(pfx)
#define _CMIndicationMIStub_DeActivateFilterCollection(pfx)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#ifdef __cplusplus

/** @brief Generate function table and factory function for an instance MI
        written in C++.

    The CMInstanceMIFactory() macro generates the function table and factory
    function for an instance MI (also known as *instance provider*)

    This macro is for CMPI MIs written in C++. The generated code uses some
    common C++ classes (named Cmpi*) that are not defined in the CMPI header
    files.

    @param cn The C++ class name of this instance provider
            (a subclass of CmpiInstanceMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this instance provider.
    @see CMPIInstanceMI, CMPIInstanceMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS This macro is implemented differently in OpenPegasus; there
        is a 'try' block in place of 'provider->initialize(ctx)'. Need to find
        out why the difference and whether to update this header file.
*/
#define CMInstanceMIFactory(cn,miname) \
CMPI_EXTERN_C CMPIInstanceMI *miname##_Create_InstanceMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctxp, \
    CMPIStatus *rc) \
{ \
    static CMPIInstanceMIFT instMIFT = { \
        CMPI_VERSION, \
        CMPI_VERSION, \
        "instance" #miname, \
        (CMPIStatus(*)( \
            CMPIInstanceMI *, \
            const CMPIContext *, \
            CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
        CmpiInstanceMI::driveEnumInstanceNames, \
        CmpiInstanceMI::driveEnumInstances, \
        CmpiInstanceMI::driveGetInstance, \
        CmpiInstanceMI::driveCreateInstance, \
        CmpiInstanceMI::driveSetInstance, \
        CmpiInstanceMI::driveDeleteInstance, \
        CmpiInstanceMI::driveExecQuery, \
        _CMInstanceMIFactory_EnumInstancesFiltered \
    }; \
    static CMPIInstanceMI mi; \
    CmpiContext ctx((CMPIContext *)ctxp); \
    mi.ft = &instMIFT; \
    CmpiBaseMI *provider = base##miname.getBaseMI(); \
    if (provider == 0) \
    { \
        provider = new cn(CmpiBroker((CMPIBroker *)mb),ctx); \
        provider->setProviderBase(&base##miname); \
        provider->initialize(ctx); \
        base##miname.setBaseMI(provider); \
    } \
    mi.hdl = provider; \
    base##miname.incUseCount(); \
    return &mi; \
}

/** @brief Generate function table and factory function for an association MI
        written in C++.

    The CMAssociationMIFactory() macro generates the function table and factory
    function for an association MI (also known as *association provider*)

    This macro is for CMPI MIs written in C++. The generated code uses some
    common C++ classes (named Cmpi*) that are not defined in the CMPI header
    files.

    @param cn The C++ class name of this association provider
            (a subclass of CmpiAssociationMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this association provider.
    @see CMPIAssociationMI, CMPIAssociationMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS This macro is implemented differently in OpenPegasus; there
        is a 'try' block in place of 'provider->initialize(ctx)'. Need to find
        out why the difference and whether to update this header file.
*/
#define CMAssociationMIFactory(cn,miname) \
CMPI_EXTERN_C CMPIAssociationMI *miname##_Create_AssociationMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctxp, \
    CMPIStatus *rc) \
{ \
    static CMPIAssociationMIFT assocMIFT = { \
        CMPI_VERSION, \
        CMPI_VERSION, \
        "association" #miname, \
        (CMPIStatus(*)( \
             CMPIAssociationMI *, \
             const CMPIContext *, \
             CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
        CmpiAssociationMI::driveAssociators, \
        CmpiAssociationMI::driveAssociatorNames, \
        CmpiAssociationMI::driveReferences, \
        CmpiAssociationMI::driveReferenceNames, \
        _CMAssociationMIFactory_AssociatorsFiltered \
        _CMAssociationMIFactory_ReferencesFiltered \
    }; \
    static CMPIAssociationMI mi; \
    CmpiContext ctx((CMPIContext *)ctxp); \
    mi.ft = &assocMIFT; \
    CmpiBaseMI *provider = base##miname.getBaseMI(); \
    if (provider == 0) \
    { \
        provider = new cn(CmpiBroker((CMPIBroker *)mb),ctx); \
        provider->setProviderBase(&base##miname); \
        provider->initialize(ctx); \
        base##miname.setBaseMI(provider); \
    } \
    mi.hdl = provider; \
    base##miname.incUseCount(); \
    return &mi; \
}

/** @brief Generate function table and factory function for a method MI
        written in C++.

    The CMMethodMIFactory() macro generates the function table and factory
    function for an method MI (also known as *method provider*)

    This macro is for CMPI MIs written in C++. The generated code uses some
    common C++ classes (named Cmpi*) that are not defined in the CMPI header
    files.

    @param cn The C++ class name of this method provider
            (a subclass of CmpiMethodMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this method provider.
    @see CMPIMethodMI, CMPIMethodMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS This macro is implemented differently in OpenPegasus; there
        is a 'try' block in place of 'provider->initialize(ctx)'. Need to find
        out why the difference and whether to update this header file.
*/
#define CMMethodMIFactory(cn,miname) \
CMPI_EXTERN_C CMPIMethodMI *miname##_Create_MethodMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctxp, \
    CMPIStatus *rc) \
{ \
    static CMPIMethodMIFT methMIFT = { \
        CMPI_VERSION, \
        CMPI_VERSION, \
        "method" #miname, \
        (CMPIStatus(*)( \
             CMPIMethodMI *, \
             const CMPIContext *, \
             CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
        CmpiMethodMI::driveInvokeMethod, \
    }; \
    static CMPIMethodMI mi; \
    CmpiContext ctx((CMPIContext *)ctxp); \
    mi.ft = &methMIFT; \
    CmpiBaseMI *provider = base##miname.getBaseMI(); \
    if (provider == 0) \
    { \
        provider = new cn(CmpiBroker((CMPIBroker *)mb),ctx); \
        provider->setProviderBase(&base##miname); \
        provider->initialize(ctx); \
        base##miname.setBaseMI(provider); \
    } \
    mi.hdl = provider; \
    base##miname.incUseCount(); \
    return &mi; \
}

/** @brief Generate function table and factory function for a property MI
        written in C++ (**Deprecated**).

    The CMPropertyMIFactory() macro generates the function table and factory
    function for an property MI (also known as *property provider*)

    This macro is for CMPI MIs written in C++. The generated code uses some
    common C++ classes (named Cmpi*) that are not defined in the CMPI header
    files.

    @param cn The C++ class name of this method provider
            (a subclass of CmpiPropertyMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this property provider.
    @deprecated The CMPropertyMIFactory() macro is deprecated since
        CMPI 2.1, in accord with the deprecation of property client operations
        in DMTF specifications.

    @see CMPIPropertyMI, CMPIPropertyMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS This macro is implemented differently in OpenPegasus; there
        is a 'try' block in place of 'provider->initialize(ctx)'. Need to find
        out why the difference and whether to update this header file.
*/
#define CMPropertyMIFactory(cn,miname) \
CMPI_EXTERN_C CMPIPropertyMI *miname##_Create_PropertyMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctxp, \
    CMPIStatus *rc) \
{ \
    static CMPIPropertyMIFT propMIFT = { \
        CMPI_VERSION, \
        CMPI_VERSION, \
        "property" #miname, \
        (CMPIStatus(*)( \
            CMPIPropertyMI *, \
            const CMPIContext *, \
            CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
        CmpiPropertyMI::driveSetProperty, \
        CmpiPropertyMI::driveGetProperty, \
        _CMPropertyMIFactory_SetPropertyWithOrigin \
    }; \
    static CMPIPropertyMI mi; \
    CmpiContext ctx((CMPIContext *)ctxp); \
    mi.ft = &propMIFT; \
    CmpiBaseMI *provider = base##miname.getBaseMI(); \
    if (provider == 0) \
    { \
        provider = new cn(CmpiBroker((CMPIBroker *)mb),ctx); \
        provider->setProviderBase(&base##miname); \
        provider->initialize(ctx); \
        base##miname.setBaseMI(provider); \
    } \
    mi.hdl = provider; \
    base##miname.incUseCount(); \
    return &mi; \
}

/** @brief Generate function table and factory function for an indication MI
        written in C++.

    The CMIndicationMIFactory() macro generates the function table and factory
    function for an indication MI (also known as *indication provider*)

    This macro is for CMPI MIs written in C++. The generated code uses some
    common C++ classes (named Cmpi*) that are not defined in the CMPI header
    files.

    @param cn The C++ class name of this indication provider
        (a subclass of CmpiIndicationMI).
        This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
        This is a character string without quotes.
    @return The function table of this indication provider.
    @see CMPIIndicationMI, CMPIIndicationMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS This macro is implemented differently in OpenPegasus; there
        is a 'try' block in place of 'provider->initialize(ctx)'. Need to find
        out why the difference and whether to update this header file.
*/
#define CMIndicationMIFactory(cn,miname) \
CMPI_EXTERN_C CMPIIndicationMI *miname##_Create_IndicationMI( \
    const CMPIBroker *mb, \
    const CMPIContext *ctxp, \
    CMPIStatus *rc) \
{ \
    static CMPIIndicationMIFT indMIFT = { \
        CMPI_VERSION, \
        CMPI_VERSION, \
        "indication" #miname, \
        (CMPIStatus(*)( \
            CMPIIndicationMI *, \
            const CMPIContext *, \
            CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
        CmpiIndicationMI::driveAuthorizeFilter, \
        CmpiIndicationMI::driveMustPoll, \
        CmpiIndicationMI::driveActivateFilter, \
        CmpiIndicationMI::driveDeActivateFilter, \
        CmpiIndicationMI::driveEnableIndications, \
        CmpiIndicationMI::driveDisableIndications, \
        _CMIndicationMIFactory_AuthorizeFilterCollection \
        _CMIndicationMIFactory_ActivateFilterCollection \
        _CMIndicationMIFactory_DeActivateFilterCollection \
    }; \
    static CMPIIndicationMI mi; \
    CmpiContext ctx((CMPIContext *)ctxp); \
    \
    mi.ft = &indMIFT; \
    CmpiBaseMI *provider = base##miname.getBaseMI(); \
    if (provider == 0) \
    { \
        provider = new cn(CmpiBroker((CMPIBroker *)mb),ctx); \
        provider->setProviderBase(&base##miname); \
        provider->initialize(ctx); \
        base##miname.setBaseMI(provider); \
    } \
    mi.hdl = provider; \
    base##miname.incUseCount(); \
    return &mi; \
}

#ifdef CMPI_VER_200
#define _CMPropertyMIFactory_SetPropertyWithOrigin \
    CmpiPropertyMI::driveSetPropertyWithOrigin,
#else
#define _CMPropertyMIFactory_SetPropertyWithOrigin
#endif

#ifdef CMPI_VER_210
#define _CMInstanceMIFactory_EnumInstancesFiltered \
    CmpiInstanceMI::driveEnumInstancesFiltered,
#define _CMAssociationMIFactory_AssociatorsFiltered \
    CmpiAssociationMI::driveAssociatorsFiltered,
#define _CMAssociationMIFactory_ReferencesFiltered \
    CmpiAssociationMI::driveReferencesFiltered,
#define _CMIndicationMIFactory_AuthorizeFilterCollection \
    CmpiIndicationMI::driveAuthorizeFilterCollection,
#define _CMIndicationMIFactory_ActivateFilterCollection \
    CmpiIndicationMI::driveActivateFilterCollection,
#define _CMIndicationMIFactory_DeActivateFilterCollection \
    CmpiIndicationMI::driveDeActivateFilterCollection,
#else
#define _CMInstanceMIFactory_EnumInstancesFiltered
#define _CMAssociationMIFactory_AssociatorsFiltered
#define _CMAssociationMIFactory_ReferencesFiltered
#define _CMIndicationMIFactory_AuthorizeFilterCollection
#define _CMIndicationMIFactory_ActivateFilterCollection
#define _CMIndicationMIFactory_DeActivateFilterCollection
#endif

/** @brief CMProviderBase macro

    @param miname MI name
    @statusopenpegasus TBD
    @hideinitializer

    @todo TODO_KS Document this macro.
*/
#define CMProviderBase(miname) \
    CmpiProviderBase base##miname;

#endif /* __cplusplus */

/**
 @}
*/

#endif // _CMPIMACS_H_
