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
    @todo TBD KS: 'macros' is bad word.  Maybe we call them convenience
        functions to cover macro vs inline versions.@n
        KS: Actually 'macros' is good word.  Question is what do we call those
        things that can be either inline or macro. 'Convenience function'
        stinks.

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
      Convenience functions with a one-to-one mapping to corresponding MB
      functions.

      The use of these convenience functions simplifies the code, largely by
      bypassing the added step of getting from the broker object or
      encapsulated data type object to the function table and to the
      corresponding MB function.

      These convenience functions have the same set of arguments as the
      corresponding MB functions. They have a simplified description of their
      functionality and arguments. For a full description, the description of
      the corresponding MB functions and arguments may need to be consulted. The
      description of each convenience function has a link to the description of
      the corresponding MB function.

      For example, the following MB function call:
      @code
      inst->ft->getProperty(inst, name, rc);
      @endcode
      is simplified when using a convenience function to:
      @code
      CMGetProperty(inst, name, rc);
      @endcode

      For details, see @ref convenience-func-broker
      "MB Functions in Broker Function Tables" and @ref convenience-func-edt
      "MB Functions of Encapsulated Data Types".
    @endparblock
    @li @parblock
      Macros that consolidate a group of MB functions into a single macro.

      The only examples are CMClone() and CMRelease() which call the clone()
      and release() functions for the function table of the object provided by
      the input arguments.

      @todo TBD AM: This definition boils down to having only these two macros
          in this group. It seems to me that splitting the MB functions into
          the two categories we have in the two MB function related sub-modules
          of @ref convenience-func "CMPI Convenience Functions" (i.e. EDT vs.
          Broker Tables) may be a better way. Definitely, we should use the
          same way of splitting them in this bullet list here, as we use in the
          sub-modules.
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
    @see CMPIStatus
    @par Examples
    @code (.c)
    CMPIStatus st = { CMPI_RC_OK, NULL };
    if (....) // something bad happened
    {
        CMSetStatus(&st, CMPI_RC_ERR_NOT_SUPPORTED);
        return st;
    }
    @endcode
    @hideinitializer
    @statusopenpegasus Not tested
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
    @param rc CMPIrc return code to be inserted int @p st.
    @param msg CMPIString containing message text to be
                  inserted into @p st.
    @see CMPIStatus
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

    @param mb Points to CMPIBroker. Required to create CMPIString.
    @param st Points to CMPIStatus object.
    @param rc CMPIrc return code to be inserted into into CMPIStatus @p st.
    @param msg C string character string containing the message
               text or NULL if no text is to be added to the
               CMPIStatus @p st.
    @see CMPIStatus
    @par Examples
    @code (.c)
    static CMPIBroker *_broker; // Cany be populated with stub macro
    . . .
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMSetStatusWithChars (_broker, &rc,
        CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED");
    @endcode
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

    @par Examples
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
    @see CMPIStatus

    @par Examples
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

    @param mb Points to a CMPIBroker structure.
    @param rc A @ref CMPIrc value specifying the return code.
    @param chars A C string (`char*`) specifying the message.
    @return This macro never returns to its caller; it contains a `return`
        statement and therefore exits the function from which it was called.
    @see CMPIStatus

    @par Examples
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
    @hideinitializer
*/
#define CMReturnWithChars(mb, rc, chars) \
do \
{ \
    CMPIStatus stat; \
    CMSetStatusWithChars(mb, &stat, rc, chars); \
    return stat; \
} while (0)

/** @brief Test a CMPI object or function return for NULL.

    CMIsNullObject() tests a CMPI object or function return for NULL. This test
    is suitable for error checking of any factory functions that return NULL in
    case of error.
    @param obj Points to the CMPI object to be tested. This argument is defined
        as `void*` to encompass any CMPI encapsulated data type object.
    @retval true The object is NULL.
    @retval false The object is NOT NULL.
    @par Examples
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
    @hideinitializer

    @todo TBD KS: object is incorrect word.  Need to define what
          encompasses CMPI Object. Do we need list of all
          possibles?@n
          AM. What is 'function return'?
    @todo KS: test this to be sure it is correct, in particular
          function repsonse
    @todo TBD AM: It seems to me that the second part of the comparison
        is implementation-specific. Plus, the casting is dubious. The macro
        version should instead access the hdl member, if that was the
        intention. But again, indicating a NULL object via obj->hdl=NULL to me
        seems to be implementation-specific.
    @todo TBD AM: The example seems to be somewhat confused. Why is a test of
        cop meaningful when it is not used at all, and cop2 is used instead?
*/
#ifdef CMPI_NO_INLINE
#define CMIsNullObject(obj) \
    ((obj) == NULL || *((void**)(obj)) == NULL)
#else
static inline CMPIBoolean CMIsNullObject(
    const void *obj)
{
    return obj == NULL || *((void **)obj) == NULL;
}
#endif

/** @brief Test a CMPIData value for NULL.

    CMIsNullValue() tests a CMPIData value for NULL.
    This is done based on the @ref CMPI_nullValue flag in its @p state member.
    @param data The CMPIData value to be tested.
    @retval true The CMPIData value is NULL.
    @retval false The CMPIData value is not NULL.
    @see CMPIData, CMPIValueState

    @par Examples
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
    @hideinitializer

    @todo TBD AM: The expression in the return statement causes a GCC warning
        "overflow in implicit constant conversion". Need to fix somehow.
    @todo TBD AM: The example is way too complex if it just intends to show
        how to use this function.
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

    @hideinitializer
    @statusopenpegasus Not tested

    @todo KS: This is value call, not pointer.  Shouldn't this be
          pointer call?@n
          AM: It works with a CMPIData value, and I dont't think we can change
          it to a pointer, for compatibility. I fixed the description.
    @todo TBD AM: The expression in the return statement causes a GCC warning
        "overflow in implicit constant conversion". Need to fix somehow.
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

    @hideinitializer
    @statusopenpegasus Not tested

    @todo KS this needs example.
    @todo KS: this is defined as...@n
          AM: ...a pointer? Same comment and fix as for CMIsKeyValue().
    @todo TBD AM: The expression in the return statement causes a GCC warning
        "overflow in implicit constant conversion". Need to fix somehow.
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

    @par Errors
    The function return status will indicate one of the following @ref CMPIrc
    codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid.

    @see CMPIContextFT.release(),
        CMPIResultFT.release(), CMPIErrorFT.release(),
        CMPIInstanceFT.release(), CMPIObjectPathFT.release(),
        CMPISelectExpFT.release(), CMPISelectCondFT.release(),
        CMPISubCondFT.release(), CMPIPredicateFT.release(),
        CMPIArgsFT.release(), CMPIStringFT.release(),
        CMPIEnumerationFT.release(), CMPIDateTimeFT.release(),
        CMPIPropertyListFT.release(),
        CMPIEnumerationFilterFT.release(),

    @par Examples
    Code to clean up after attempting to create an instance:
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPISelectExp *se_def = NULL;
    clone = CMClone(se_def, &rc);
    // . . . test @rc for good completion and use clone if
    CMRelease(clone);
    @endcode
    @hideinitializer
*/
#define CMRelease(obj) \
    ((obj)->ft->release((obj)))

/**
    @brief Clone an encapsulated data type object.

    CMClone() clones an encapsulated data type object, by calling the
    clone() function in the function table of the object.

    @param obj Points to the encapsulated data type object to be cloned.
    @param [out] rc  If not NULL, points to a CMPIStatus structure that upon
        return has been updated with the function return status.
    @return @parblock If successful, returns a pointer to the
        copied clone of the object defined by @p obj.

        The returned object shall be explicitly released by the MI using its
        release() function, or the CMRelease() macro.

        If not successful, returns NULL.
    @endparblock

    @par Errors
    The following @ref CMPIrc codes shall be recognized:
    @li `CMPI_RC_OK` Operation successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` The @p ef handle is invalid.

    @see CMPIContextFT.clone(), CMPIResultFT.clone(), CMPIErrorFT.clone(),
        CMPIInstanceFT.clone(), CMPIObjectPathFT.clone(),
        CMPISelectExpFT.clone(), CMPISelectCondFT.clone(),
        CMPISubCondFT.clone(), CMPIPredicateFT.clone(),
        CMPIArgsFT.clone(), CMPIStringFT.clone(),
        CMPIEnumerationFT.clone(), CMPIDateTimeFT.clone(),
        CMPIPropertyListFT.clone(), CMPIEnumerationFilterFT.clone(),

    @par Examples
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

// KS_TODO Update CMPIContext macros from here on down
/** Gets a named Context entry value.
    @param ctx Points to CMPIContext.
    @param name Context entry name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Entry value.
    @see CMPIContextFT.getEntry()
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

/** Gets a Context entry value defined by its index.
    @param ctx Points to CMPIContext.
    @param index Position in the internal Data array.
    @param name Output: Returned Context entry name (suppressed when NULL).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Entry value.
    @see CMPIContextFT.getEntryAt()
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

/** Gets the number of entries contained in this Context.
    @param ctx Points to CMPIContext.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of entries.
    @return Entry value.
    @see CMPIContextFT.getEntryCount()
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

    CMAddContextEntry() executes CMPIContextFT.addEntry().
    @param ctx Points to CMPIContext.
    @param name Entry name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIContextFT.addEntry()
    @hideinitializer
    @statusopenpegasus Used
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

// KS_TODO Update CMPIResult macros from here on down
/** Return a value/type pair.
    @param rslt Points to CMPIResult.
    @param value Address of a Value object.
    @param type Type of the Value object.
    @return Service return status.
    @see CMPIResultFT.returnData()
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

/** Return a Instance object.
    @param rslt Points to CMPIResult.
    @param inst Instance to be returned.
    @return Service return status.
    @see CMPIResultFT.returnInstance()
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

/** Return a ObjectPath object..
    @param rslt Points to CMPIResult.
    @param op ObjectPath to be returned.
    @return Service return status.
    @see CMPIResultFT.returnObjectPath()
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

/** Indicates no further data to be returned.
    @param rslt Points to CMPIResult.
    @return Service return status.
    @see CMPIResultFT.returnDone()
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
/** Return a CMPIError object instance
    @param rslt Points to CMPIResult.
    @param er Error to be returned.
    @return Service return status.
    @see CMPIResultFT.returnError()
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

/** @brief Get a pointer to the C-language representation of a CMPIString
        object (**Deprecated**).

    This macro provides NO argument checking or return code and is therefore
    deprecated. Use CMGetCharsPtr(), instead.
    @param str Points to a CMPIString object.
    @return Pointer to char* representation.
    @see CMGetCharsPtr(), CMPIStringFT.getCharPtr()

    @par Examples
    @code (.c)
    myObjPath = CMNewObjectPath(
        _broker,
        CMGetCharPtr(CMGetNameSpace(ref,0)),
        "TestCMPI_KeyReturned",
        0);
    @endcode
    @deprecated This macro is deprecated since CMPI 2.1. Use CMGetCharsPtr(),
        instead.
    @hideinitializer

    @todo DONE KS: Confirm this since the doc was just a guess right now.@n
        AM: Reviewed and fixed.
    @todo DONE AM: Should this not invoke the respective function? Why is the
        hdl the string?@n
        WG: We need to modify the implementation of this one so that it is not
        implementation dependent but just calls CMGetCharsPtr. Also deprecate.@n
        AM: It is now deprecated and the implementation calls the function
        but without rc (Passing NULL is allowed).
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

/** @brief Get a pointer to a C-language string representation of a CMPIString
        object.

    CMGetCharsPtr() executes CMPIStringFT.getCharPtr() to get a pointer to the
    C-language string representation of @p str. It differs from CMGetCharPtr()
    in that it includes a CMPIStatus return code.
    @param str Points to a CMPIString object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Pointer to char* representation.
    @see CMPIStringFT.getCharPtr()

    @par Examples
    @code (.c)
    CMPIObjectPath *op = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    objPath = CMNewObjectPath (_broker,
        CMGetCharsPtr(CMGetNameSpace(ref, &rc), NULL),
        class,
        &rc);
    @endcode
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


/**
  @}
  @addtogroup convenience-func-edt-array
  @{
*/

/** @brief Get the number of array elements in a CMPIArray object.

    CMGetArrayCount() executes CMPIArrayFT.getSize().
    Function name is different but not arugments or return.
    @param ar Points to CMPIArray.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSize()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetArrayType() executes CMPIArrayFT.getSimpleType(). Function names
    are different but arguments and return are the same.
    @param ar Points to CMPIArray.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSimpleType()
    @hideinitializer
    @statusopenpegasus Used and tested
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

/** @brief Get the value of an array element in a CMPIArray object by index.

    CMGetArrayElementAt() executes CMPIArrayFT.getElementAt().
    @param ar Points to CMPIArray.
    @param index Position in the internal data array.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData Element value.
    @see CMPIArrayFT.getElementAt()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMSetArrayElementAt() executes CMPIArrayFT.setElementAt().
    @param ar Points to CMPIArray.
    @param index Position in the internal data array.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIArrayFT.setElementAt()
    @hideinitializer
    @statusopenpegasus Used and tested
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

// KS_TODO Update CMPIEnumeration macros from here on down
/** Get the next element of this Enumeration.
    @param en Points to the CMPIEnumeration object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Element value.
    @see CMPIEnumerationFT.getNext()
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

/** @brief Test for any elements left in this Enumeration.

    CMHasNext() executes CMPIEnumerationFT.hasNext() that
    tests for any elements left in @p en the CMPIEnumeration object.
    @param en Points to the CMPIEnumeration object.
    @param [out] rc Service return status (suppressed
          when NULL).
    @return True or false.
    @see CMPIArrayFT.hasNext()
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

    CMToArray() executes CMPIEnumerationFT.toArray() converts the
    CMPIEnumeration object represented by the argument @p en into a CMPIArray.
    @param en Points to the CMPIEnumeration object.
    @param rc Output: Service return status (suppressed when NULL).
    @return The Array.
    @see CMPIEnumerationFT.toArray()
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

    CMGetProperty() executes CMPIInstanceFT.getProperty() to get a property
    in @p inst a CMPIInstance by @p name.
    @param inst Instance this pointer.
    @param name Property name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData with Property value. If not successful CMPIData.state
        will have the @ref CMPI_badValue.
    @see CMPIInstanceFT.getProperty()

    @par Examples
    @code (.c)
    CMPIInstance *inst = NULL;
    // . . . make the inst
    CMPIData rtnData;
    const char* name1 = "propertyName";
    rtnData = CMGetProperty(inst, name1, &rc);
    assert(rtnData.state != CMPI_badValue);
    @endcode
    @hideinitializer
    @statusopenpegasus Used and tested extensively
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

    CMGetPropertyAt() executes CMPIInstanceFT.getPropertyAt().
    @param inst Instance this pointer.
    @param index Position in the internal data array.
    @param [out] name Returned property name (suppressed when NULL).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData with property value. If not successful CMPIData.state
        will have the @ref CMPI_badValue.
    @see CMPIInstanceFT.getPropertyAt()
    @hideinitializer
    @statusopenpegasus Used
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

    CMGetPropertyCount() executes CMPIInstanceFT.getPropertyCount().
    @param inst Instance this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of properties; 0 if not successful.
    @see CMPIInstanceFT.getPropertyCount()
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

/** @brief Set a property value in a CMPIInstance object by name.

    CMSetProperty() executes CMPIInstanceFT.setProperty().
    @param inst Points to CMPIInstance.
    @param name Points to property name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIInstanceFT.setProperty()
    @hideinitializer
    @statusopenpegasus Used and tested extensively

    @todo TBD AM: Why do we have the `(CMPIValue *)` cast in the macro version?
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

/** @brief Get a CMPIObjectPath object from a CMPIInstance object.

    CMGetObjectPath() executes CMPIInstanceFT.getObjectPath() to get the
    CMPIObject path from @p inst.
    @param inst Points to CMPIInstance.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The generated CMPIObjectPath or NULL.
    @see CMPIInstanceFT.getObjectPath()
    @hideinitializer
    @statusopenpegasus Used and tested extensively in cmpiTestMethodProvider.c
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

    CMSetPropertyFilter() executes CMPIInstanceFT.setPropertyFilter() to
    attach @p propertyList to CMPIInstance @p inst.
    @param inst Points to the CMPIInstance structure.
    @param properties If not NULL, the members of the array define one
        or more Property names to be accepted by setProperty operations.
    @param keyList Deprecated, ignored by MB, maintained here for compatibility.
    @return Function return status.
    @see CMPIInstanceFT.setPropertyFilter()
    @hideinitializer
    @statusopenpegasus Not used
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

    CMSetObjectPath() executes CMPIInstanceFT.setObjectPath() to set
    @p obj.
    @param inst Points to the CMPIInstance structure.
    @param op Points to the new CMPIObjectPath.
    @return CMPIStatus structure containing the function return status.
    @see CMPIInstanceFT.setObjectPath()
    @hideinitializer
    @statusopenpegasus Used
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
/** @brief Add or replace a property value in a CMPIInstance object by name.

    @param inst Points to the CMPIInstance structure.
    @param name is a string containing the Property name.
    @param value points to a CMPIValue structure containing the
        value to be assigned to the Property.
    @param type CMPIType structure defining the type of the value.
    @param origin specifies the instance origin.  If NULL, noorigin is
        attached to  the property
    @return Function return CMPIStatus.
    @see CMPIInstanceFT.setPropertyWithOrigin()
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

/** @brief Set the host name component in a CMPIObjectPath object.

    CMSetNameSpace() executes CMPIObjectPathFT.setNameSpace() to set @p ns into
    @p op.
    @param op ObjectPath this pointer.
    @param ns The namespace string
    @return Service return status.
    @see CMPIObjectPathFT.setNameSpace()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetNameSpace() executes CMPIObjectPathFT.getNameSpace().
    @param op Points to CMPIObject.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The namespace component.
    @see CMPIObjectPathFT.getNameSpace()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMSetHostName() executes CMPIObjectPathFT.setHostname().
    @param op Pointer to target CMPIObjectPath.
    @param hn The hostname string
    @return Function return CMPIStatus.
    @see CMPIObjectPathFT.setHostname()
    @hideinitializer
    @statusopenpegasus Used
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

    CMGetHostName() executes CMPIObjectPathFT.getHostname() to
    get the host name component from @p op a CMPIObjectPath
    @see CMPIObjectPathFT.getHostname()
    @hideinitializer
    @statusopenpegasus Used
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

    CMSetClassName() executes CMPIObjectPathFT.setClassName().
    @param op Points to CMPIObject.
    @param cn The new class name
    @return Function return status.
    @see CMPIObjectPathFT.setClassName()
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

/** @brief Get the classname component from CMPIObjectPath.

    CMGetClassName() executes CMPIObjectPathFT.getClassName().
    @param op ObjectPath this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The classname component or NULL.
    @see CMPIObjectPathFT.getClassName()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMAddKey() executes CMPIObjectPathFT.addKey()
    @param op Points to CMPIObjectPath.
    @param key Key property name.
    @param value Points to CMPIValue structure.
    @param type CMPIType Value type.
    @return function CMPIStatus return status.
    @see CMPIObjectPathFT.addKey()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetKey() executes CMPIObjectPathFT.getKey() to get a key binding by name.
    @param op Points to CMPIObjectPath.
    @param [out] key Returned property name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData.
    @see CMPIObjectPathFT.getKey()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetKeyAt() executes CMPIObjectPathFT.getKeyAt() to get a key binding
    defined by @p index.
    @param op Points to CMPIObjectPath.
    @param index Position in the internal Data array.
    @param [out] name Returned property name (suppressed when NULL).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Data value.
    @see CMPIObjectPathFT.getKeyAt()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetKeyCount() executes CMPIObjectPathFT.getKeyCount() to get the number
    of key bindings in a @p op a CMPIObjectPath object.
    @param op Points to CMPIObjectPath.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of properties.
    @see CMPIObjectPathFT.getKeyCount()
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

/** @brief Set/replace the namespace and class name components in a

    CMPIObjectPath object from another CMPIObjectPath object.
    CMSetNameSpaceFromObjectPath() executes
    CMPIObjectPathFT.setNameSpaceFromObjectPath().
    @param op Points to CMPIObjectPath.
    @param src Source input.
    @return Function return status.
    @see CMPIObjectPathFT.setNameSpaceFromObjectPath()
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

    CMSetHostAndNameSpaceFromObjectPath() executes
    CMSetHostAndNameSpaceFromObjectPath.
    @param op Points to CMPIObjectPath.
    @param src Source input.
    @return Function return status.
    @see CMPIObjectPathFT.setHostAndNameSpaceFromObjectPath()
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

    CMGetClassQualifier() executes CMPIObjectPathFT.getClassQualifier().
    @param op Points to CMPIObjectPath.
    @param qName Qualifier name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getClassQualifier()
    @hideinitializer
    @statusopenpegasus Not implemented
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

    CMGetPropertyQualifier() executes CMPIObjectPathFT.getPropertyQualifier()
    @param op Points to CMPIObjectPath.
    @param pName Property name.
    @param qName Qualifier name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getPropertyQualifier()
    @hideinitializer
    @statusopenpegasus Not implemented
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

    @param op Points to CMPIObjectPath.
    @param mName Method name.
    @param qName Qualifier name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getMethodQualifier()
    @hideinitializer
    @statusopenpegasus Not implemented
*/
#ifdef CMPI_NO_INLINE
#define CMGetMethodQualifier(op, mName, qName, rc) \
    ((op)->ft->getMethodQualifier((op), (mName), (qName), (rc)))
#else
static inline  CMPIData CMGetMethodQualifier(
    const CMPIObjectPath *op,
    const char *mName,
    const char *qName,
    CMPIStatus *rc)
{
    return op->ft->getMethodQualifier(op, mName, qName, rc);
}
#endif

/** @brief Get a parameter qualifier.

    CMGetParameterQualifier() executes CMPIObjectPathFT.getParameterQualifier().
    @param op Points to CMPIObjectPath.
    @param mName Method name.
    @param pName Parameter name.
    @param qName Qualifier name.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getParameterQualifier()
    @hideinitializer
    @statusopenpegasus Not implemented
*/
#ifdef CMPI_NO_INLINE
#define CMGetParameterQualifier(op, mName, pName, qName,rc) \
    ((op)->ft->getParameterQualifier((op), (mName), (pName), (qName), (rc)))
#else
static inline  CMPIData CMGetParameterQualifier(
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

/** @brief Set a method parameter in a CMPIArgs object.

    CMAddArg() executes CMPIArgsFT.addArg() to add or replace a method
    parameter named @p name with the CMPIValue @p value and type @p type
    in a CMPIArgs object @p args.
    @param args Points to CMPIArgs.
    @param name Argument name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIArgsFT.addArg()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetArg() executes CMPIArgsFT.getArg() to get a method
    parameter from a CMPIArgs object by its name.
    @param args Args this pointer.
    @param name Argument name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see CMPIArgsFT.getArg()
    @hideinitializer
    @statusopenpegasus Used
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

    CMGetArgAt() executes CMPIArgsFT.getArgAt() to get an argument value from a
    CMPIArgs object by its index.
    @param args Points to CMPIArgs.
    @param index Position in the internal Data array.
    @param name Output: Returned argument name (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see  CMPIArgsFT.getArgAt()
    @hideinitializer
    @statusopenpegasus Used

    @todo removed all params and returns
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

/** @brief Get number of arguments in a CMPIArgs array.

    CMGetArgCount() executes CMPIArgsFT.getArgCount() to get the number of
    arguments in the CMPIArgs array.
    @param args Points to CMPIArgs.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of properties.
    @see CMPIArgsFT.getArgCount()
    @hideinitializer
    @statusopenpegasus Used
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

    CMGetBinaryFormat() executes CMPIDateTimeFT.getBinaryFormat().
    @param dt Points to the CMPIDateTime object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return DateTime in binary.
    @see CMPIDateTimeFT.getBinaryFormat()
    @hideinitializer
    @statusopenpegasus Used and tested
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
        for the CIM datetime type.

    CMGetStringFormat() executes CMPIDateTimeFT.getStringFormat().
    @param dt Points to the CMPIDateTime object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return DateTime as UTC string.
    @see CMPIDateTimeFT.getStringFormat()
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

    CMIsInterval() executes CMPIDateTimeFT.isInterval().
    @param dt Points to the CMPIDateTime object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return True if interval value.
    @see CMPIDateTimeFT.isInterval()
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

// KS_TODO Update CMPISelectExp macros from here on down
/** @brief Test whether an instance matches the select expression in a
        CMPISelectExp object.

    CMEvaluateSelExp() executes CMPISelectExpFT.evaluate().
    @param se SelectExp this pointer.
    @param inst Instance to be evaluated.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluate()
    @hideinitializer
    @statusopenpegasus Used
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

/** @brief Add or replace a context entry in a CMPIContext object.

    CMGetSelExpString() executes CMPISelectExpFT.getString().
    @param se SelectExp this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The select expression.
    @see CMPISelectExpFT.getString()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetDoc() executes CMPISelectExpFT.getDoc().
    @param se SelectExp this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The disjunction.
    @see CMPISelectExpFT.getDoc()
    @hideinitializer
    @statusopenpegasus Used
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

    CMGetCod executes CMPISelectExpFT.getCOD().
    @param se SelectExp this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The conjunction.
    @see CMPISelectExpFT.getCOD()
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

    CMEvaluateSelExpUsingAccessor executes
    CMPISelectExpFT.evaluateUsingAccessor().
    @param se SelectExp this pointer.
    @param accessor Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluateUsingAccessor()
    @hideinitializer
    @statusopenpegasus Used
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

// KS_TODO Update CMPISelectCond macros from here on down
/** @brief Get the number and type of subconditions in a CMPISelectCond object.

    Optionally, the CMPISelectCond type (COD or DOC) will be returned.
    CMGetSubCondCountAndType
    @param sc SelectCond this pointer.
    @param [out] type CMPISelectCond type (suppressed when NULL).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of SubCond elements.
    @see CMPISelectCondFT.getCountAndType()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetSubCondAt() executes CMPISelectCondFT.getSubCondAt().
    @param sc SelectCond this pointer.
    @param index Position in the internal SubCoind array.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The indexed SubCond element.
    @see CMPISelectCondFT.getSubCondAt()
    @hideinitializer
    @statusopenpegasus Tested
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

// KS_TODO Update CMPISubCond macros from here on down
/** @brief Get the number of predicates in a CMPISubCond object.

    CMGetPredicateCount() executes CMPISubCondFT.getCount().
    @param sc SubCond this pointer.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of Predicate elements.
    @see CMPISubCondFT.getCount()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetPredicateAt() executes CMPISubCondFT.getPredicateAt().
    @param sc SubCond this pointer.
    @param index Position in the internal Predicate array.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The indexed Predicate element.
    @see CMPISubCondFT.getPredicateAt()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetPredicate() executes CMPISubCondFT.getPredicate().
    @param sc SubCond this pointer.
    @param name Predicate name (property name).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The named Predicate element.
    @see CMPISubCondFT.getPredicate()
    @hideinitializer
    @statusopenpegasus Tested
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

// KS_TODO Update CMPIPredicate macros from here on down
/** @brief Get the predicate components of a CMPIPredicate object.

    CMGetPredicateData() executes CMPIPredicateFT.getData().
    @param pr Predicate this pointer.
    @param [out] type CMPItype Property type.
    @param [out] prop CMPIPredOp operation.
    @param [out] lhs Left hand side of predicate.
    @param [out] rhs Right hand side of predicate.
    @return Service return status.
    @see CMPIPredicateFT.getData()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMEvaluatePredicateUsingAccessor() executes
    CMPIPredicateFT.evaluateUsingAccessor().
    @param pr Points to the CMPIPredicate.
    @param accessorFnc Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Evaluation result.
    @see CMPIPredicateFT.evaluateUsingAccessor()

    @note Return type modified from int to CMPIBoolean in CMPI 2.1
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

    CMGetErrorType() executes CMPIErrorFT.getErrorType().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIErrorType
    @see CMPIErrorFT.getErrorType()

    @note Inline code fixed in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetOtherErrorType() executes CMPIErrorFT.getOtherErrorType().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @note Inline code fixed in CMPI 2.1
    @see CMPIErrorFT.getOtherErrorType()
    @hideinitializer
    @statusopenpegasus Used and tested
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

    CMGetOwningEntity() executes CMPIErrorFT.getOwningEntity().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOwningEntity()
    @note Inline code fixed in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getMessageID()
    @note Inline code fixed in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetErrorMessage() executes CMPIErrorFT.getMessage().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @note Inline form corrected in CMPI 2.1
    @see CMPIErrorFT.getMessage()
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetPerceivedSeverity() executes CMPIErrorFT.getPerceivedSeverity().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return the perceived severity
    @see CMPIErrorFT.getPerceivedSeverity()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetProbableCause() executes CMPIErrorFT.getProbableCause().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A probable cause value
    @see CMPIErrorFT.getProbableCause()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    getProbableCauseDescription() executes
    CMPIErrorFT.getProbableCauseDescription().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getProbableCauseDescription()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetRecommendedActions() executes CMPIErrorFT.getRecommendedActions().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A array of strings, which can be NULL
    @see CMPIErrorFT.getRecommendedActions()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetErrorSource executes CMPIErrorFT.getErrorSource().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getErrorSource()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetErrorSourceFormat() executes CMPIErrorFT.getErrorSourceFormat().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A error source format  code
    @see CMPIErrorFT.getErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetOtherErrorSourceFormat() executes
    CMPIErrorFT.getOtherErrorSourceFormat().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOtherErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

    CMGetCIMStatusCode() executes CMPIErrorFT.getCIMStatusCode().
    @param er Points to the CMPIError object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return A CMPI Status code
    @see CMPIErrorFT.getCIMStatusCode()
    @note Inline form corrected in CMPI 2.1
    @hideinitializer
    @statusopenpegasus Tested
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

/** @brief Get `CIMStatusCodeDescription` attribute of a CMPIError object.

    CMGetCIMStatusCodeDescription() executes
    CMPIErrorFT.getCIMStatusCodeDescription().
    @param er Points to the CMPIError object.
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getCIMStatusCodeDescription()
    @note Inline form corrected in CMPI 2.1
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

    @param er Points to the CMPIError object.
    @param rc Output: Serbice return status (surpressed when NULL)
    @return An array of CMPIStrings which represents the dynamic values
    @see CMPIErrorFT.getMessageArguments()
    @note Inline form corrected in CMPI 2.1
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

/** @brief Sets the error type of this error object.

    CMSetErrorType() executesCMPIErrorFT.setErrorType() with corresponding
    arguments.
    @param er Points to the CMPIError object.
    @param et The error type
    @return Output: Service return status
    @see CMPIErrorFT.setErrorType()
    @note Inline form corrected in CMPI 2.1
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

// KS_TODO Update CMPIError macros from here on down
/** Sets the 'other' error type of this error object.
    @param er Points to the CMPIError object.
    @param ot A string which describes the error type, it is only valis when
        error type is "OTHER"
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorType()
    @note Inline form corrected in CMPI 2.1
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

/** Sets the description of the probable cause.
    @param er Points to the CMPIError object.
    @param pcd The probable cause string
    @return CMPIStatus structure containing the function return status.
    @see CMPIErrorFT.setProbableCauseDescription()
    @note Inline form corrected in CMPI 2.1
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

/** Sets the recomended actions array.
    @param er Points to the CMPIError object.
    @param ra An array of strings describing actions that shoudl
        be taken t deal with this error
    @return Output: Service return status
    @see CMPIErrorFT.setRecommendedActions()
    @note Inline form corrected in CMPI 2.1
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

/** Specifies a string which specifes The identifying information of the entity
    (i.e., the instance) generating the error.
    @param er Points to the CMPIError object.
    @param es String which describes the source.
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSource()
    @note Inline form corrected in CMPI 2.1
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

/** Sets the source format of the error object
    @param er Points to the CMPIError object.
    @param esf the string which describes the source format
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
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

/** Specifies A string defining "Other" values for ErrorSourceFormat.
    @param er Points to the CMPIError object.
    @param oef String which describes the other source format.
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
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

/** Sets the description of the status code.
    @param er Points to the CMPIError object.
    @param scd A string whcih describes the status code.
    @return Output: Service return status
    @see CMPIErrorFT.setCIMStatusCodeDescription()
    @note Inline form corrected in CMPI 2.1
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

/** Sets an array of strings for the dynamic content of the message
    @param er Points to the CMPIError object.
    @param values Specifies an array of CMPIStrings containing the dynamic
    content of the message.
    @return Service return status
    @see CMPIErrorFT.setMessageArguments()
    @note Inline form corrected in CMPI 2.1
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

// AM_TODO Bring argument names in sync with ft functions from here on down
// KS_TODO Update CMPIBroker(bft+eft) macros from here on down
/** @brief get the CMPIBroker brokerCapabilities variable

    CBGetCapabilities() convenience function directly access the
    CMPIBrokerFT.brokerCapabilities variable, an unsigned  32
    bit variable describing CMPI features supported by this MB.
    MB capabilities are defined by  @ref mb-capabilities flags.
    @param mb pointer to CMPIBroker struct
    @return unsigned int containing the capabilities flags.
    @since CMPI version 2.1. Previous versions included an
        incorrect convenience function CBGetClassification()
        which has been removed as not working.
    @see @ref mb-capabilities "MB Capabilities", CMPIBrokerFT.brokerCapabilities
    @hideinitializer

    @todo TBD AM: The macro version is called CBGetClassification(). Should we
        rename that to the inline function's name CBGetCapabilities()?
    @todo TBD AM: Should this function be moved to "Helper Functions"?
*/
#ifdef CMPI_NO_INLINE
#define CBGetClassification(mb) \
    ((mb)->bft->brokerCapabilities)
#else
static inline unsigned int CBGetCapabilities(
    const CMPIBroker *mb)
{
    return mb->bft->brokerCapabilities;
}
#endif

/** @brief Get CMPIBroker version

    CBBrokerVersion gets the CMPIVersion definition from the CMPIBroker
    function table. This can be used to determine which version of the
    CMPI Specification a broker implements.

    @param mb Pointer to CMPIBroker struct
    @return CMPIVersion containing the CMPIBroker version.

    It has no direct corresponding function. It directly access the
    CMPIBrokerFT.brokerVersion variable.

    @see CMPIBrokerFT.brokerVersion

    @statusopenpegasus Not used
    @hideinitializer

    @todo TBD AM: Should this function be moved to "Helper Functions"?
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

/** @brief Get CMPIBroker Name

    CBBrokerName() convenience function gets the MB name
    from CMPIBrokerFT.brokerName

    @param mb Pointer to CMPIBroker struct
    @return C string (const char*) containing the informal name of the
        MB.

    It has no direct corresponding function. It directly access the
    CMPIBrokerFT.brokerName variable.
    @see CMPIBrokerFT.brokerName
    @hideinitializer

    @todo TBD AM: Should this function be moved to "Helper Functions"?
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

/** @brief Prepare the MB to accept a new thread that will be using MB
        functions.

    CBPrepareAttachThread() convenience function executes
    CMPIBrokerFT.prepareAttachThread()  to prepare the MB to accept a new
    thread that will be using MB functions. This function is expected to be
    called in the existing thread.
    @param mb Points to CMPIBroker..
    @param ctx Old Context object
    @return New Context object to be used by thread to be attached.
    @see CMPIBrokerFT.prepareAttachThread()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBPrepareAttachThread(mb,c) \
    ((mb)->bft->prepareAttachThread((mb),(c)))
#else
static inline CMPIContext *CBPrepareAttachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->prepareAttachThread(mb, ctx);
}
#endif

/** This function informs the CMPI run time system that the current
    thread with Context will begin using CMPI services.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.attachThread()
    @hideinitializer

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBAttachThread(mb,c) \
    ((mb)->bft->attachThread((mb),(c)))
#else
static inline CMPIStatus CBAttachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->attachThread(mb, ctx);
}
#endif

/** This function informs the CMPI run time system that the current thread
    will not be using CMPI services anymore. The Context object will be
    freed during this operation.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.detachThread()
    @hideinitializer

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBDetachThread(mb,c) \
    ((mb)->bft->detachThread((mb),(c)))
#else
static inline CMPIStatus CBDetachThread(
    const CMPIBroker *mb,
    const CMPIContext *ctx)
{
    return mb->bft->detachThread(mb, ctx);
}
#endif


/** This function requests delivery of an Indication. The CIMOM will
    locate pertinent subscribers and notify them about the event.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param ns Namespace
    @param ind Indication Instance
    @return Service return status.
    @see CMPIBrokerFT.deliverIndication()
    @hideinitializer

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBDeliverIndication(mb,c,n,i) \
    ((mb)->bft->deliverIndication((mb),(c),(n),(i)))
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

/** Enumerate Instance Names of the class (and subclasses)
    defined by @p op.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param op ObjectPath containing namespace and classname components.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Enumeration of ObjectPaths.
    @see CMPIBrokerFT.enumerateInstanceNames()
    @hideinitializer

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBEnumInstanceNames(mb,c,p,rc) \
    ((mb)->bft->enumerateInstanceNames((mb),(c),(p),(rc)))
#else
static inline CMPIEnumeration *CBEnumInstanceNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    CMPIStatus *rc)
{
    return mb->bft->enumerateInstanceNames(mb, ctx, op, rc);
}
#endif

/** Enumerate Instances of the class (and subclasses) defined by @p op.
    Instance structure and inheritance scope can be controled using the
    CMPIInvocationFlags entry in @p ctx.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param classPath ObjectPath containing namespace and
              classname components.
    @param properties If not NULL, the members of the array define
         one or more Property names. Each returned Object MUST NOT
         include elements for any Properties missing from this list
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIEnumeration of Instances.
    @see CMPIBrokerFT.enumerateInstances()
    @hideinitializer
    @statusopenpegasus Not used, not tested

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBEnumInstances(mb,ctx,classPath,properties,rc) \
           (mb)->bft->enumerateInstances((mb),(ctx),(classPath),(properties), \
           (rc)))
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

/** Get Instance using @p op as reference. Instance structure can be
    controled using the CMPIInvocationFlags entry in @p ctx.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param op ObjectPath containing namespace, classname and key components.
    @param properties If not NULL, the members of the array
    define one or more Property names. Each returned
    Object MUST NOT include elements for any Properties
    missing from this list
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The Instance.
    @see CMPIBrokerFT.getInstance()
    @hideinitializer

    @todo (KS)clean up doc
*/
#ifdef CMPI_NO_INLINE
#define CBGetInstance(mb,c,p,pr,rc) \
    ((mb)->bft->getInstance((mb),(c),(p),(pr),(rc)))
#else
static inline CMPIInstance *CBGetInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->getInstance(mb, ctx, op, properties, rc);
}
#endif

/** @brief Create an instance of a given class.

    CBCreateInstance() convenience function executes
    CMPIBrokerFT.createInstance() to create an instance of a given class.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param op ObjectPath containing namespace, classname
       and key components.
    @param inst Complete instance.
    @param rc Output: Service return status (suppressed when NULL).
    @return The assigned instance reference.
    @see CMPIBrokerFT.createInstance()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBCreateInstance(mb,c,p,i,rc) \
    ((mb)->bft->createInstance((mb),(c),(p),(i),(rc)))
#else
static inline CMPIObjectPath *CBCreateInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const CMPIInstance *inst,
    CMPIStatus *rc)
{
    return mb->bft->createInstance(mb, ctx, op, inst, rc);
}
#endif

/** @brief Modify property values of an existing instance.

    CBModifyInstance convenience function executes CMPIBrokerFT.modifyInstance()
    to modify the property values of an existing instance.

    @see CMPIBrokerFT.modifyInstance()
*/
#ifdef CMPI_NO_INLINE
#define CBModifyInstance(mb,c,p,i,pr) \
    ((mb)->bft->modifyInstance((mb),(c),(p),(i),(pr)))
#else
static inline CMPIStatus CBModifyInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const CMPIInstance *inst,
    const char** properties)
{
    return mb->bft->modifyInstance(mb, ctx, op, inst, properties);
}
#endif

/** Delete an existing CMPIInstance using @p op as reference.
    CBDeleteInstance() executes CMPIBrokerFT.deleteInstance() with
    corresponding arguments to delete an existing CMPIInstance.

    @see CMPIBrokerFT.deleteInstance()
    @hideinitializer

    @todo KS add params back
*/
#ifdef CMPI_NO_INLINE
#define CBDeleteInstance(mb,c,p) \
    ((mb)->bft->deleteInstance((mb),(c),(p)))
#else
static inline CMPIStatus CBDeleteInstance(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op)
{
    return mb->bft->deleteInstance(mb, ctx, op);
}
#endif

/** Query the enumeration of instances of the class (and subclasses) defined
    by @p op using @p query expression.

    @see CMPIBrokerFT.execQuery()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBExecQuery(mb,c,p,l,q,rc) \
    ((mb)->bft->execQuery((mb),(c),(p),(l),(q),(rc)))
#else
static inline CMPIEnumeration *CBExecQuery(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *query,
    const char *lang,
    CMPIStatus *rc)
{
    return mb->bft->execQuery(mb, ctx, op, query, lang, rc);
}
#endif

/** Enumerate instances associated with the Instance defined by the @p op.

    @see CMPIBrokerFT.associators()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAssociators(mb,c,p,acl,rcl,r,rr,pr,rc) \
    ((mb)->bft->associators((mb),(c),(p),(acl),(rcl),(r),(rr),(pr),(rc)))
#else
static inline CMPIEnumeration *CBAssociators(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->associators(mb, ctx, op, assocClass, resultClass, role,
                                resultRole, properties, rc);
}
#endif

/** Enumerate ObjectPaths associated with the Instance defined by @p op.

    @see CMPIBrokerFT.associatorNames()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBAssociatorNames(mb,c,p,acl,rcl,r,rr,rc) \
    ((mb)->bft->associatorNames((mb),(c),(p),(acl),(rcl),(r),(rr),(rc)))
#else
static inline CMPIEnumeration *CBAssociatorNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    CMPIStatus *rc)
{
    return mb->bft->associatorNames(mb, ctx, op, assocClass, resultClass, role, resultRole, rc);
}
#endif

/** @brief Enumerate the association instances referencing a given source
        instance.

    CBReferenceNames convenience function executes CMPIBrokerFT.references()
    enumerating the association instances referencing a given source instance.

    @see CMPIBrokerFT.references()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBReferences(mb,c,p,acl,r,pr,rc) \
    ((mb)->bft->references((mb),(c),(p),(acl),(r),(pr),(rc)))
#else
static inline CMPIEnumeration *CBReferences(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *resultClass,
    const char *role,
    const char **properties,
    CMPIStatus *rc)
{
    return mb->bft->references(mb, ctx, op, resultClass, role, properties, rc);
}
#endif

/** Enumerates the association ObjectPaths referencing a given
    instance.

    CBReferenceNames convenience function executes the function
    CMPIBrokerFT.referenceNames() to enumerate the instance
    paths of the association instances referencing a given
    source instance @p op.

    @see CMPIBrokerFT.referenceNames()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBReferenceNames(mb,c,p,acl,r,rc) \
    ((mb)->bft->referenceNames((mb),(c),(p),(acl),(r),(rc)))
#else
static inline CMPIEnumeration *CBReferenceNames(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *resultClass,
    const char *role,
    CMPIStatus *rc)
{
    return mb->bft->referenceNames(mb, ctx, op, resultClass, role, rc);
}
#endif

/** @brief Invoke a method on a given instance

    CBInvokeMethod() executes CMPBrokerIFT.invokeMethod() to
    execute named, extrinsic method on a target object. Instance
    methods (i.e., non-static methods) can\ be invoked only on
    instances. Class methods (i.e., static methods) can be
    invoked on instances and classes.
    Arguments are as defined in CMPIBrokerFT.invokeMethod().
    @see CMPIBrokerFT.invokeMethod()

    @par Examples
    The example executes CBInvokeMethod "TestCMPIError" on
    CMPIObjectPath and tests response for success and correct
    return data type.
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
    @hideinitializer
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

/** Set the named property value of an existing Instance. (**Deprecated**)

    CBSetProperty() executes the CMPIBrokerFT.setProperty()
    function to set a CMPIValue @ value into property of an
    existing instance.

    @see CMPIBrokerFT.setProperty()

    @deprecated because the function setProperty has been
                deprecated

    @note No example because this function is deprecated
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBSetProperty(mb,c,p,n,v,t) \
    ((mb)->bft->setProperty((mb),(c),(p),(n),(CMPIValue *)(v),(t)))
#else
static inline CMPIStatus CBSetProperty(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *name,
    const CMPIValue *value,
    const CMPIType type)
{
    return mb->bft->setProperty(mb, ctx, op, name, (CMPIValue *)value, type);
}
#endif

/** Get the named property value of an Instance (**Deprecated**)

    CBGetProperty() executes CMPIBrokerFT.getProperty() to
    get the property named by @p name defined by @p op.
    @see CMPIBrokerFT.getProperty()

    @deprecated Because corresponding CMPIBrokerFT.getProperty() is deprecated.

    @note No example because deprecated.
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CBGetProperty(mb,c,p,n,rc) \
    (mb)->bft->getProperty((mb),(c),(p),(n),(rc))
#else
static inline CMPIData CBGetProperty(
    const CMPIBroker *mb,
    const CMPIContext *ctx,
    const CMPIObjectPath *op,
    const char *name,
    CMPIStatus *rc)
{
    return mb->bft->getProperty(mb, ctx, op, name, rc);
}
#endif

/** @brief Create a new CMPIInstance object initialized to a given instance
        path.

    CBNewInstance() executes CMPIBrokerEncFT.newInstance() with same arguments
    @param mb Points to CMPIBroker.
    @param instPath CMPIObjectPath containing namespace and classname.
    @param [out] rc Function return status (suppressed when NULL).
    @return Newly created Instance.
    @see CMPIBrokerEncFT.newInstance()

    @par Examples
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
    @hideinitializer
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

    CMNewObjectPath() executes CMPIBrokerEncFT.newObjectPath() to create a new
    CMPIObjectPath.
    @param mb Points to CMPIBroker.
    @param ns namespace
    @param cn class name
    @param [out] rc Function return status (suppressed when NULL).
    @see CMPIBrokerEncFT.newObjectPath()

    @par Examples
    @code (.c)
    const char* class = "myClass";
    CMPIObjectPath *objPath = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    objPath = CMNewObjectPath (broker, ns, class, &rc);
    assert ( rc.rc == CMPI_RC_OK);
    CMAddKey (objPath, "ElementName", (CMPIValue *) class, CMPI_chars);
    @endcode
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewObjectPath(mb,n,c,rc) \
    ((mb)->eft->newObjectPath((mb),(n),(c),(rc)))
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

/** @brief Create a new CMPIString object initialized from a C string.

    CMNewString() convenience function executes CMPIBrokerEncFT.newString()
    to create a new CMPIString object that is initialized from  @p data a
    C-language string.
    @see CMPIBrokerEncFT.newString()

    @par Examples
    @todo add params
    @code (.c)
    CMPIString1 *cmpiStr;
    CMPIString2 *cmpiStr;
    cmpiStr1 = CMNewString(_broker, NULL, &rc);
    // test rc for OK
    cmpiStr2 = CMNewString(_broker, "Tracing for level 5", &rc);
    // test rc for OK
    @endcode
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewString(mb,s,rc) \
    ((mb)->eft->newString((mb),(s),(rc)))
#else
static inline CMPIString *CMNewString (
    const CMPIBroker *mb,
    const char *data,
    CMPIStatus *rc)
{
    return mb->eft->newString(mb, data, rc);
}
#endif

/** @brief Create a new CMPIArgs object initialized to have no method
        parameters.

    CMNewArgs() executes CMPIBrokerEncFT.newArgs() to create a new CMPIArgs
    object.
    @param mb Points to CMPIBroker.
    @param [out] rc Function return status (suppressed when NULL).
    @return Newly created CMPIArgs object or NULL.
    @see CMPIBrokerEncFT.newArgs()

    @par Examples
    @code (.c)
    CMPIArgs *args_ptr = NULL;
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    args_ptr = CMNewArgs(_broker, &rc);
    @endcode
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewArgs(mb,rc) \
    ((mb)->eft->newArgs((mb),(rc)))
#else
static inline CMPIArgs *CMNewArgs (const CMPIBroker *mb, CMPIStatus *rc)
{
    return mb->eft->newArgs(mb, rc);
}
#endif

/** Create a new CMPIArray object of a given fixed array size for a
        given type of elements.

    CMNewArray() executes CMPIBrokerEncFT.newArray() to create a new
    CMPIArray object
    @param mb Points to CMPIBroker.
    @param size Number of elements
    @param type Element type
    @param [out] rc Function return status (suppressed when NULL).
    @return Newly created Array or NULL.
    @see CMPIBrokerEncFT.newArray()

    @hideinitializer
    @statusopenpegasus Tested in cmpiTestMethodProvider.c

    @todo KS confirm what size means
*/
#ifdef CMPI_NO_INLINE
#define CMNewArray(mb,c,t,rc) \
    ((mb)->eft->newArray((mb),(c),(t),(rc)))
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

/** @brief Create a new CMPIDataTime object with current date and time.

    CBNewDateTime() executes CMPIBrokerEncFT.newDateTime() to create a
    new CMPIDateTime object().
    @param mb Pointer to CMPIBroker
    @param [out] rc Function return status (suppressed when NULL).
    @return The newly created DateTime or NULL.
    @see CMPIBrokerEncFT.newDateTime()

    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTime(mb,rc) \
    ((mb)->eft->newDateTime((mb),(rc)))
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

    @param mb Points to CMPIBroker.
    @param binTime Date/Time definition in binary format in microsecods
    starting since 00:00:00 GMT, Jan 1,1970.
    @param interval Wenn true, defines Date/Time definition to be an
         interval value
    @param rc Output: Function return CMPIStatus (suppressed when NULL).
    @return The newly created DateTime or NULL.
    @see CMPIBrokerEncFT.newDateTimeFromBinary()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTimeFromBinary(mb,d,i,rc) \
    ((mb)->eft->newDateTimeFromBinary((mb),(d),(i),(rc)))
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

/** @brief Create a new CMPIDateTime object initialized from input.

    @param mb Points to CMPIBroker.
    @param datetime Date/Time definition in UTC format
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The newly created DateTime or NULL.
    @see CMPIBrokerEncFT.newDateTimeFromChars()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewDateTimeFromChars(mb,d,rc) \
    ((mb)->eft->newDateTimeFromChars((mb),(d),(rc)))
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
        expression.

    CMNewSelectExp() executes CMPIBrokerEncFT.newSelectExp() to create a new
    CMPISelectExp
    @param mb Points to CMPIBroker.
    @param query The select expression.
    @param lang The query language.
    @param [out] projection Projection specification (suppressed when NULL).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return The newly created SelectExp or NULL.
    @see CMPIBrokerEncFT.newSelectExp()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CMNewSelectExp(mb,q,l,p,rc) \
    ((mb)->eft->newSelectExp((mb),(q),(l),(p),(rc)))
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

/** @brief Test whether a class path is of a specified class or any of its
        subclasses.

    CMClassPathIsA() executes CMPIBrokerEncFT.classPathIsA().
    @param mb Points to CMPIBroker.
    @param classPath The class path (namespace and classname
              components).
    @param className Specifies the class name to be tested for.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return
         @li True if test successful.
         @li False otherwise.
    @see CMPIBrokerEncFT.classPathIsA()
    @version The className argument was named type and documented incorrectly
    prior to version 2.1.  The code did execute correctly
    @hideinitializer
    @statusopenpegasus Not tested
*/
#ifdef CMPI_NO_INLINE
#define CMClassPathIsA(mb,cp,cn,rc) \
    ((mb)->eft->classPathIsA((mb),(cp),(cn),(rc)))
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

/** @brief Convert CMPI encapsulated data type object into a string
        representation.

    CDToString() executes CMPIBrokerEncFT.toString() to  convert any CMPI
    encapsulated data type to a CMPIString with implementation-specific content
    representation.  Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI encapsulated data type object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return String from representation of @p object or NULL.
    @see CMPIBrokerEncFT.toString()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CDToString(mb,o,rc) \
    ((mb)->eft->toString((mb),(void*)(o),(rc)))
#else
static inline CMPIString *CDToString(
    const CMPIBroker *mb,
    const void *object,
    CMPIStatus *rc)
{
    return mb->eft->toString(mb, (void *)object, rc);
}
#endif

/** @brief Tests whether a CMPI encapsulated data type object is of a
        specified CMPI type.

    CDIsOfType() executes CMPIBrokerEncFT.isOfType() to verifies whether @p
    object is of CMPI type @p type. Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param type A string specifying a valid CMPI Object type
        ("CMPIInstance", "CMPIObjectPath", etc).
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return True if test successful.
    @see CMPIBrokerEncFT.isOfType()
    @par Examples
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPIBoolean isOfType = 0;
    CMInstance* inst = CMNewInstance(_broker, . . .);
    isOfType = CDIsOfType (_broker, inst, "CMPIInstance", &rc);
    assert(isOfType);
    @endcode
    @hideinitializer
    @statusopenpegasus Tested
*/
#ifdef CMPI_NO_INLINE
#define CDIsOfType(mb,o,t,rc) \
           (mb)->eft->isOfType((mb),(void*)(o),(t),(rc))
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

/** @brief Get the type name of a CMPI ensapsulated data type object.

    CDGetType() executes CMPIBrokerEncFT.getType() to get the CMPI type.
    Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPI object type or NULL.
    @see CMPIBrokerEncFT.getType()
    @hideinitializer
*/
#ifdef CMPI_NO_INLINE
#define CDGetType(mb,o,rc) \
    ((mb)->eft->getType((mb),(void*)(o),(rc)))
#else
static inline CMPIString *CDGetType(
    const CMPIBroker *mb,
    const void *object,
    CMPIStatus *rc)
{
    return mb->eft->getType(mb, object, rc);
}
#endif

/** @brief Log a diagnostic message.

    CMLogMessage() executes CMPIBrokerEncFT.logMessage().
    @param mb Points to CMPIBroker.
    @param severity integer severity code.
    @param id message ID or any other identifying string.
    @param text If not NULL, const char * with the message text to be logged.
    @param string If not NULL, CMPIString with message text to be logged;
       @p string will be ignored when @p text is not NULL.
    @return CMPIStatus containing function return status
    @par Examples
    @code (.c)
    CMLogMessage(_broker, 1, "TestProvider",
                 "Entering EnumerateInstance", NULL);
    @endcode
    @see CMPIBrokerEncFT.logMessage()
    @hideinitializer
    @statusopenpegasus Tested in cmpiTestMethodProvider.c
*/
#ifdef CMPI_NO_INLINE
#define CMLogMessage(mb,severity,id, text, string)  \
    ((mb)->eft->logMessage((mb),(severity),(id),(text),(string)))
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
        component definition.

    CMTraceMessage() exeuctes CMPIBrokerEncFT.trace() to send a diagnostic
    message to a trace output facility.
    @param mb Points to CMPIBroker.
    @param level The severity
    @param component NULL or implementation specific ID.
    @param text NULL or message text.
    @param string NULL, or CMPIString with message
       text to be logged. @p string will be ignored when text is not
       NULL.
    @see CMPIBrokerEncFT.trace()
    @par Examples
    @code (.c)
    CMPIStatus rc = { CMPI_RC_OK, NULL };
    CMPIString *str = CMNewString (_broker, "CMTraceMessage", &rc);
    rc = CMTraceMessage (_broker, 4, "Authorization", NULL, str);
    @endcode
    @hideinitializer
    @statusopenpegasus Tested in cmpiTestMethodProvider.c. Uses CMPILevel as
         type, not int.
*/
#ifdef CMPI_NO_INLINE
#define CMTraceMessage(mb,level,component, text, string)  \
    ((mb)->eft->trace((mb),(level),(component),(text),(string)))
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
/** @brief Create a new CMPIError object initialized with attributes defined
        by the input parameters.

    CMNewCMPIError() executes CMPIBrokerEncFT.newCMPIError() to create a new
    CMPIError object.
    @param mb Points to CMPIBroker.
    @param owner Identifies the entity that owns the msg format definition.
    @param msgID Identifies the format of the message.
    @param msg Formatted and translated message.
    @param sev Perceived severity of this error.
    @param pc Probable caues of this error.
    @param cimStatusCode Status Code.
    @param [out] rc Function return status or NULL
    @return Pointer to a newly allocated CMPIError object or NULL.
    @see CMPIBrokerEncFT.newCMPIError()

    @par Examples
    @code (.c)
    cmpiError = CMNewCMPIError(_broker, inOwningEntity, inMsgID, inMsg,
                    inSev, inPc, inCIMStatusCode, &rc);
    @endcode
    @hideinitializer
    @statusopenpegasus Tested in TestCMPIErrorProvider.c
*/
#ifdef CMPI_NO_INLINE
#define CMNewCMPIError(mb,owner,msgID,msg,sev,pc,cimStatusCode,rc)  \
    ((mb)->eft->newCMPIError((mb),(owner),(msgID),(msg),(sev), \
                             (pc),(cimStatusCode),(rc)))
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
    return mb->eft->newCMPIError(mb, owner, msgID, msg, sev, pc, cimStatusCode, rc);
}
#endif
#endif /* CMPI_VER_200 */

#ifdef CMPI_VER_200
/** @brief Open a message file and return a handle to the file.

    CMOpenMessageFile() executes CMPIBrokerEncFT.openMessageFile() to open a
    new message file if the MB supports message files.
    @param mb Points to CMPIBroker.
    @param msgFile The message file identifier.
    @param [out] msgFileHandle The handle representing the open msg file or NULL.
    @return Service return status
    @see CMPIBrokerEncFT.openMessageFile()

    @par Examples
    @code (.c)
    CMOpenMessageFile(_broker,"/path/msgFile",&msgFileHandle);
    @endcode
    @hideinitializer
    @statusopenpegasus Used
*/
#ifdef CMPI_NO_INLINE
#define CMOpenMessageFile(mb,mf,mfh) \
    ((mb)->eft->openMessageFile((mb),(mf),(mfh)))
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

    CMCloseMessageFile() exeuctes CMPIBrokerEncFT.closeMessageFile() to close a
    message file.
    @param mb Points to CMPIBroker.
    @param msgFileHandle CMPIMsgFileHandle handle representing the open
        message file.
    @return Function return status.
    @see CMPIBrokerEncFT.closeMessageFile()

    @par Examples
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
    @hideinitializer
    @statusopenpegasus Tested in cmpiTestBrokerEncProvider.c
*/
#ifdef CMPI_NO_INLINE
#define CMCloseMessageFile(mb,mfh)  \
    ((mb)->eft->closeMessageFile((mb),(mfh)))
#else
static inline CMPIStatus CMCloseMessageFile(
    const CMPIBroker *mb,
    const CMPIMsgFileHandle msgFileHandle)
{
    return mb->eft->closeMessageFile(mb, msgFileHandle);
}
#endif
#endif /* CMPI_VER_200 */

/**
    @defgroup cmfmt-args CMFmtArgs{N}() helper macros for CMGetMessage2()
    @{
      @brief CMFmtArgs{N}() helper macros for CMGetMessage2().

      These macros are used for the @p args argument of CMGetMessage2(). Their argument
      is a comma-separated list of invocations of the @ref cmfmt-val
      "CMFmt{type}({v})" macros.
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
    @defgroup cmfmt-val CMFmt{type}() helper macros for CMGetMessage2()
    @{
      @brief CMFmt{type}() helper macros for CMGetMessage2().

      Each of these macros represents a message insert pair consisting of type
      and value. These macros are used as a comma-separated list of arguments
      to @ref cmfmt-args "CMFmtArgs{N}()".
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
#define CMFmtString(v)  CMPI_String,((CMPI_String*)v)

/**
   @}
*/

#ifdef CMPI_VER_200
/** @brief Get a translated message text from an open message file by
        message ID.

    The CMGetMessage2() macro executes CMPIBrokerEncFT.getMessage2().
    There is no inline form of this convenience function.

    @param mb Points to CMPIBroker.
    @param msgId The message identifier.
    @param msgFileHandle The handle representing the open message file.
    @param defMsg The default message. See the function for details
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @param args The message insert values, specified as @ref cmfmt-args
        "CMFmtArgs{N}({vlist})", where {N} is the number of values, and {vlist}
        is a comma-separated list of @ref cmfmt-val "CMFmt{type}({v})" macros.
    @return Points to a CMPIString object representing the translated message.
    @see CMPIBrokerEncFT.getMessage2()

    @par Examples
    Assuming the message identified by the message ID is the same as the
    default message "Test $0 $1", the following example creates a message "Test
    message 42" where "message" is passed as a C string for the first message
    trigger ($0), and "42" is passed as an integer for the second message
    trigger ($1):
    @code (.c)
    CMGetMessage2(_broker, "msgid", msgFileHandle, "Test $0 $1",
        NULL, CMFmtArgs2(CMFmtChars("message"), CMFmtSint(42)));
    @endcode
    @version Inline code modified; unsigned int last parameter
          to type CMPICount in 2.1
    @hideinitializer
    @statusopenpegasus Tested in cmpiTestBrokerEncProvider.c

    @todo TBD KS: Pls review since it asks to do something if macro but it is
        only a macro. No inline version.@n
        AM: I removed the inline function, added the CMFmtArgsX() and CMFmtX()
        macros back in, and improved the description. Please review.
    @todo TBD AM: Not sure I understand the text of the Version section. There
        was no change for the macro between CMPI 2.0 and 2.1.
*/
#define CMGetMessage2(mb, msgId, msgFileHandle, defMsg, rc, args) \
    ((mb)->eft->getMessage2((mb), (msgId), (msgFileHandle), (defMsg), (rc), \
                            args))
#endif /* CMPI_VER_200 */


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
    "MI-specific factory function" named `{miname}_Create_InstanceMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    instance MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>{pfx}Cleanup()</TD>
        <TD>CMPIInstanceMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}EnumInstanceNames()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstanceNames()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}EnumInstances()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstances()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}GetInstance()</TD>
        <TD>CMPIInstanceMIFT.getInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}CreateInstance()</TD>
        <TD>CMPIInstanceMIFT.createInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}ModifyInstance()</TD>
        <TD>CMPIInstanceMIFT.modifyInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}DeleteInstance()</TD>
        <TD>CMPIInstanceMIFT.deleteInstance()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}ExecQuery()</TD>
        <TD>CMPIInstanceMIFT.execQuery()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}EnumInstancesFiltered()</TD>
        <TD>CMPIInstanceMIFT.enumerateInstancesFiltered()</TD><TD>2.1</TD></TR>
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
        function, after the CMPIInstanceMI structure has been created.

        That C statement can access function arguments and local variables of
        the generated factory function. The names of these arguments and local
        variables in the generated function will not change in future CMPI
        versions, and are:
        @li @p mb, @p ctx, @p rc - see the like-named arguments of the @ref
            mi-factory-specific "factory function".
        @li @p mi - local variable which is the initialized CMPIInstanceMI
            object.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or
        `furtherInit(&mi)` or @ref CMNoHook if no further intialization is
        required.
    @endparblock
    @return A pointer to the function table of this MI.

    @par Examples
    This example uses the CMInstanceMIStub() macro for a rudimentary instance
    MI written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

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

    static CMPIStatus MyProvInitialize(
        CMPIInstanceMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIInstanceMI object
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
    @hideinitializer

    @todo DONE KS: Confirm that this 'see' statement works@n
        AM: It worked, but I have minimized it because the functions are now
        in a table.
    @todo TBD KS: we have first cut at example.  Is this the way to go or would
        we be better with complete provider in an examples section?@n AM: I
        think the example is good enough for the factory function. What would
        be good to have are the actual provider functions, somewhere. That is
        too much for this particular macro.
    @todo TBD KS: Despite the documentation, this apparently requires
        implementations of all of the corresponding functions. How to we handle
        the two that may well be optional. (ExecQuery,
        EnumerateInstancesFiltered)?@n
        AM: The spec requires that the MIFT table always has all functions.
        Those that are not implemented, still exist and return 'not
        implemented'. I have updated the example to show ExecQuery() that way.
    @todo TBD AM: Why is the MIFT file static and the MI local static? The
        variable name used for the file static table is the same for all
        providers, making it impossible to have more than one provider per
        source file. This seems like an unnecessary limitation. Suggestion:
        Make both tables local static.
    @todo TBD AM: We document the CMPI_VERSION is the version that is
        implemented. If we are serious about this, we should use CMPI_VERSION
        instead of CMPICurrentVersion, for the first version in the MIFT.
    @todo TBD AM: The second version in the MIFT is the MI development version,
        and has nothing to do with the CMPI version. Ideally, it would be
        passed as an argument to the macro. For now, I have set it also to
        CMPI_VERSION, for compatibility.
    @todo TBD AM: We should make sure that the code works for both C and C++
        compilation. I have added ifdef __cplusplus around the C stubs, and
        around any inline functions. While this causes differently named linker
        symbols to be created for the inline convenience functions, they are
        MI-local and thus binary compatibility to the MB is not affected. It is
        still source code compatible for recompiles of the MI.
    @todo TBD AM: While we document that the returned pointer indicates success
        or error to the MB, it is still also required to set CMPIStatus.rc upon
        return. The current macro does not set that at all. Do we expect the
        init hook to set that, or was that just oversight? I have added code
        to the generated factory function that sets rc OK before the init
        hook is called, so that the hook code can still overwrite that to a
        bad rc. However, for that to happen, the init hook needs to expand to
        some more code than just a function call. I have added a
        CMInitHook(pfx) macro to the example code that does that and calls a
        properly defined initialize function. We could add the
        CMInitHook() macro to the cmpimacs.h header file, if you like it.
        it also encapsulates the knowledge about the local variable and argument
        names in the generated factory function, so we could again "undocument"
        them.
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
    "MI-specific factory function" named `{miname}_Create_AssociationMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    association MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>{pfx}AssociationCleanup()</TD>
        <TD>CMPIAssociationMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}Associators()</TD>
        <TD>CMPIAssociationMIFT.associators()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}AssociatorNames()</TD>
        <TD>CMPIAssociationMIFT.associatorNames()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}References()</TD>
        <TD>CMPIAssociationMIFT.references()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}ReferenceNames()</TD>
        <TD>CMPIAssociationMIFT.referenceNames()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}AssociatorsFiltered()</TD>
        <TD>CMPIAssociationMIFT.associatorsFiltered()</TD><TD>2.1</TD></TR>
    <TR><TD>{pfx}ReferencesFiltered()</TD>
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
        function, after the CMPIAssociationMI structure has been created.

        That C statement can access function arguments and local variables of
        the generated factory function. The names of these arguments and local
        variables in the generated function will not change in future CMPI
        versions, and are:
        @li @p mb, @p ctx, @p rc - see the like-named arguments of the @ref
            mi-factory-specific "factory function".
        @li @p mi - local variable which is the initialized CMPIAssociationMI
            object.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or
        `furtherInit(&mi)` or @ref CMNoHook if no further intialization is
        required.
    @endparblock
    @return A pointer to the function table of this MI.

    @par Examples
    This example uses the CMAssociationMIStub() macro for a rudimentary
    association MI written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

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

    static CMPIStatus MyProvAssociationInitialize(
        CMPIAssociationMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIAssociationMI object
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
    @hideinitializer

    @todo DONE. create example
    @todo DONE, SEE INSTANCE STUB. what about optional functions
    @todo need note about creating function that parallel
           others but with cap
    @todo DONE? Need reference back to cmpift
    @todo DONE. expand for cmpi 2.1
    @todo DONE. AM: Apply updates from CMInstanceMIStub().
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
    "MI-specific factory function" named `{miname}_Create_MethodMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    method MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>{pfx}MethodCleanup()</TD>
        <TD>CMPIMethodMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}InvokeMethod()</TD>
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
        function, after the CMPIMethodMI structure has been created.

        That C statement can access function arguments and local variables of
        the generated factory function. The names of these arguments and local
        variables in the generated function will not change in future CMPI
        versions, and are:
        @li @p mb, @p ctx, @p rc - see the like-named arguments of the @ref
            mi-factory-specific "factory function".
        @li @p mi - local variable which is the initialized CMPIMethodMI
            object.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or
        `furtherInit(&mi)` or @ref CMNoHook if no further intialization is
        required.
    @endparblock
    @return A pointer to the function table of this MI.

    @par Examples
    This example uses the CMMethodMIStub() macro for a rudimentary
    method MI written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

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

    static CMPIStatus MyProvMethodInitialize(
        CMPIMethodMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIMethodMI object
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
    @hideinitializer

    @todo DONE. Need see reference back to cmpift. Do example
    @todo DONE. AM: Apply updates from CMInstanceMIStub().
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
    "MI-specific factory function" named `{miname}_Create_PropertyMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    property MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>{pfx}PropertyCleanup()</TD>
        <TD>CMPIPropertyMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}SetProperty()</TD>
        <TD>CMPIPropertyMIFT.setProperty()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}GetProperty()</TD>
        <TD>CMPIPropertyMIFT.getProperty()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}SetPropertyWithOrigin()</TD>
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
        function, after the CMPIPropertyMI structure has been created.

        That C statement can access function arguments and local variables of
        the generated factory function. The names of these arguments and local
        variables in the generated function will not change in future CMPI
        versions, and are:
        @li @p mb, @p ctx, @p rc - see the like-named arguments of the @ref
            mi-factory-specific "factory function".
        @li @p mi - local variable which is the initialized CMPIPropertyMI
            object.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or
        `furtherInit(&mi)` or @ref CMNoHook if no further intialization is
        required.
    @endparblock
    @return A pointer to the function table of this MI.

    @see CMPIPropertyMI, CMPIPropertyMIFT,
        @ref mi-factory-specific "MI-specific factory function"
    @hideinitializer

    @todo DONE. Need reference back to cmpift. No example because
           deprecated.
    @todo DONE. AM: Apply updates from CMInstanceMIStub().
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
    "MI-specific factory function" named `{miname}_Create_IndicationMI()`.
    It is exported by the MI load library and is called when the libary is
    loaded by the MB.

    The generated MI function table contains pointers to all functions for
    indication MIs as defined in the CMPI version that is implemented (see
    @ref CMPI_VERSION). The user of this macro needs to provide all of these
    functions. Those functions that are not going to be implemented, still need
    to be provided and implemented by returning @ref CMPI_RC_ERR_NOT_SUPPORTED.

    The function names are fixed, and are generated with a prefix specified
    using the @p pfx argument of the macro:
    <TABLE>
    <TR><TH>Function name</TH>
        <TH>Description</TH><TH>CMPI version</TH></TR>
    <TR><TD>{pfx}IndicationCleanup()</TD>
        <TD>CMPIIndicationMIFT.cleanup()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}AuthorizeFilter()</TD>
        <TD>CMPIIndicationMIFT.authorizeFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}MustPoll()</TD>
        <TD>CMPIIndicationMIFT.mustPoll()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}ActivateFilter()</TD>
        <TD>CMPIIndicationMIFT.activateFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}DeActivateFilter()</TD>
        <TD>CMPIIndicationMIFT.deActivateFilter()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}EnableIndications()</TD>
        <TD>CMPIIndicationMIFT.enableIndications()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}DisableIndications()</TD>
        <TD>CMPIIndicationMIFT.disableIndications()</TD><TD>1.0</TD></TR>
    <TR><TD>{pfx}AuthorizeFilterCollection()</TD>
        <TD>CMPIIndicationMIFT.authorizeFilterCollection()</TD><TD>2.1</TD></TR>
    <TR><TD>{pfx}ActivateFilterCollection()</TD>
        <TD>CMPIIndicationMIFT.activateFilterCollection()</TD><TD>2.1</TD></TR>
    <TR><TD>{pfx}DeActivateFilterCollection()</TD>
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
        function, after the CMPIIndicationMI structure has been created.

        That C statement can access function arguments and local variables of
        the generated factory function. The names of these arguments and local
        variables in the generated function will not change in future CMPI
        versions, and are:
        @li @p mb, @p ctx, @p rc - see the like-named arguments of the @ref
            mi-factory-specific "factory function".
        @li @p mi - local variable which is the initialized CMPIIndicationMI
            object.

        This enables you to perform additional initialization functions and is
        normally a function call like `furtherInit(broker)`, or
        `furtherInit(&mi)` or @ref CMNoHook if no further intialization is
        required.
    @endparblock
    @return A pointer to the function table of this MI.

    @par Examples
    This example uses the CMIndicationMIStub() macro for a rudimentary
    indication MI written in plain C.
    @code (.c)
    static const CMPIBroker *_broker;

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

    static CMPIStatus MyProvIndicationInitialize(
        CMPIIndicationMI *mi,
        const CMPIContext *ctx)
    {
        . . . // Initialization code when loading the MI load library
        mi->hdl = . . . // You can store data in the CMPIIndicationMI object
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
    @hideinitializer

    @todo DONE. Need reference back to cmpift and example
    @todo DONE. AM: Apply updates from CMInstanceMIStub().
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
    @brief Symbol for specifying that there is no further intialization needed
        in an MI factory function.

    @ref CMNoHook is used as a value for the @p hook argument of MI factory
    stub macros for plain C, for specifying that the macro is not going to
    execute any additional initialization code in the generated factory
    function.

    @see CMInstanceMIStub(), CMAssociationMIStub(), CMMethodMIStub(),
        CMPropertyMIStub(), CMIndicationMIStub()
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

    The initialization
    routine &lt;miname&gt;Create_IndicationMI is called when
    this provider module is loaded by the broker. This
    macro is for CMPI providers written in C++ using the
    Cmpi* classes.
    @param cn The C++ class name of this instance provider
            (a subclass of CmpiInstanceMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this instance provider.
    @hideinitializer

    @todo Need reference back to cmpift
    @todo TBD AM: Where are the C++ classes documented that are used by this
        macro?
    @todo TBD AM: I have added ifdef __cplusplus around the C++ stubs, because
        they do not make sense when compiling for C. They would probably not
        hurt, but I think it is cleaner that way.
*/
#define CMInstanceMIFactory(cn,miname) \
 CMPI_EXTERN_C \
  CMPIInstanceMI *miname##_Create_InstanceMI( \
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
//// ks - The above implemented differently.  Not sure yet why the
//// difference but there is try block in place of provider->initialize(ctx)

/** @brief Generate function table and factory function for an association MI
        written in C++.

    The initialization routine
    &lt;miname&gt;Create_AssociationMI
    is called when this provider module is loaded by the broker.
    This macro is for CMPI providers written in C++ using
    the Cmpi* classes.
    @param cn The C++ class name of this instance provider
            (a subclass of CmpiInstanceMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this instance provider.
    @hideinitializer

    @todo Need reference back to cmpift
*/
#define CMAssociationMIFactory(cn,miname) \
 CMPI_EXTERN_C \
  CMPIAssociationMI *miname##_Create_AssociationMI( \
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
//// KS Above implemented differently in OpenPegasus. Try block in place
//// of provider->initialize(ctx)

/** @brief Generate function table and factory function for a method MI
        written in C++.

    The initialization routine
    &lt;miname&gt;Create_MethodMI is called when this
    provider module is loaded by the broker.
    This macro is for CMPI providers written in C++ using
    the Cmpi* classes.
    @param cn The C++ class name of this method provider
            (a subclass of CmpiMethodMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this association provider.
    @hideinitializer

    @todo Need reference back to cmpift
    @todo KS Add macro for filtered operations.
*/
#define CMMethodMIFactory(cn,miname) \
 CMPI_EXTERN_C \
 CMPIMethodMI *miname##_Create_MethodMI( \
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
//// KS see comments above about provider->initialize(ctx)

/** @brief Generate function table and factory function for a property MI
        written in C++ (**Deprecated**).

    The initialization routine
    &lt;miname&gt;Create_PropertyMI is called when this
    provider module is loaded by the broker. This macro
    is for CMPI providers written in C++ using the Cmpi*
    classes.
    @param cn The C++ class name of this method provider
            (a subclass of CmpiMethodMI).
            This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
            This is a character string without quotes.
    @return The function table of this association provider.
    @deprecated The CMPIPropertyMIFT has been deprecated in
                 CMPI 2.1.
    @hideinitializer

    @todo Need reference back to cmpift
    @todo document as deprecated
*/
#define CMPropertyMIFactory(cn,miname) \
 CMPI_EXTERN_C \
  CMPIPropertyMI *miname##_Create_PropertyMI( \
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
//// KS same comment about provider->initialize(ctx)

/** @brief Generate function table and factory function for an indication MI
        written in C++.

    The initialization routine
    &lt;miname&gt;Create_IndicationMI is called when this
    provider module is loaded by the broker. This macro
    is for CMPI providers written in C++ using the Cmpi*
    classes.
    @param cn The C++ class name of this indication provider
        (a subclass of CmpiIndicationMI).
        This is a character string without quotes.
    @param miname The provider name under which this provider is registered.
        This is a character string without quotes.
    @return The function table of this association provider.
    @hideinitializer

    @todo AM_TODO: Add filter collection functions, conditional on CMPI 2.1.
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
//// KS Same comment about provider->intialize

/** KS_TODO
    @param miname KS_TODO
    @hideinitializer

    @todo KS: document this
    @todo AM: This macro is not used in this file. Its CmpiProviderBase symbol
        is not defined. What the purpose of this macro?
*/
#define CMProviderBase(miname) \
    CmpiProviderBase base##miname;

#endif /* __cplusplus */

/**
 @}
*/

#endif // _CMPIMACS_H_
