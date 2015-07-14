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
 * tables;
 * MIs that intend to use the macros should include this header.
 *
 * This header file belongs to the Technical Standard: Systems Management:
 * Common Manageability Programming Interface (CMPI) Issue 2 Version 1.
 *
 * This header file is provided as a convenience only. In the case of any
 * discrepancy between the header file and the Technical Standard
 * (incorporating any subsequent Technical Corrigenda), the Technical Standard
 * shall be definitive.
 *
   The convenience functions are NOT documented in the
   CMPI specification, just the existence of this header file.
 *
 * This file provides macros (and  in some cases alternatively
 * defined inline functions) as follows:
 *    @li one-one mapping to corresponding CMPI functions. These
 *        macros simplify the syntax of calls while keeping
 *        exactly the same set of arguments as the function
 *        calls in cmpift.h. These macros do not repeat the
 *        documentation of arguments but depend on the definiton
 *        in the defining function. The documentation for each
 *        convenience function points to the corresponding
 *        function. Each convenience function in this file
 *        corresponds to a single function call in cmpift.d.
 *        These convenience functions simplify the code largely by
          bypassing the added step of getting from the broker
          object argument to the function table and the
          function. Thus, for example:
         @code(.c)
                 inst->ft->getProperty(inst, name, rc);
             is simplified by a convenience function to:
                 CMGetProperty(inst, name, rc);
          @endcode
 *    @li macros that consolidate a group of cmpift.d calls into
 *        a single macro. The primary examples are CMPClone()
 *        and CMRelease() which call the clone() and release()
 *        functions for the function table of the object
 *        provided by the input arguments.
 *    @li Convience functions that aid the access to
 *        selected variables or otherwise provide functionality
 *        not directly available through a function. Examples of
 *        this are CMReturn() andCMIsNull()
 *    @li Macros that aid in the definition of providers,
 *        primarily in the definition of the function tables.
 *        The macro CMInstanceMIStub() is an example.
 *
 *    Not all cmpift.h functions have corresponding macros.
 *    However, all functions that have macros have a See Also
 *    reference to those macros.  Also, the macros have a
 *    reference back to the corresponding cmpift.d functions.
 *    @todo discuss inline vs macros.
 *    @todo KS macros is bad word.  Maybe we call them convenience
            functions to cover macro vs inline versions.
            Actually macros is good word.  Question is what do
            we call those things that can be either inline or
            macro. Convience function stinks.
 *    @todo AM: Should we move this description to the defgroup "CMPI
 *          Convenience Functions" in modules.h? Yes (KS)
 *    @todo KS: We need to create a CMPI_NO_INLINE symbol and
 *          make it user?? available. The default is inline.
 *          both set is error.  DOC_ONLY is only for doc
 *          preperation.  Remove DOC_ONLY. Why the includes for
 *          DOC_ONLY
 */

#ifndef _CMPIMACS_H_
#  define _CMPIMACS_H_

#ifdef DOC_ONLY
#  define _CMPI_INLINE_MOD // Doxygen does not handle these modifiers at all.
#else
#  define _CMPI_INLINE_MOD static inline
#endif

#if !defined(CMPI_INLINE) && !defined(CMPI_NO_INLINE)
#  define CMPI_INLINE // if none is defined, set the default
#endif
#if defined(CMPI_INLINE) && defined(CMPI_NO_INLINE)
#  error "Only one of CMPI_INLINE and CMPI_NO_INLINE may be defined."
#endif

#include <cmpift.h>

/**
 * @addtogroup convenience-func-helper
 * @{
 */

/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and no message.

    The CMReturn() macro builds a CMPIStatus object specifying a return code
    and no message and exits the function in which it was executed, causing it
    to return that CMPIStatus object. CMReturn() can only be used in functions
    that return CMPIStatus.

    @param rc A @ref CMPIrc value specifying the function return status.
    @return This macro never returns; it contains a `return` statement and
        therefore exits the function from which it was called.

    @par Examples
    Example of enumerateInstanceNames() MI function that returns CMPI_RC_OK to
    the MB.
    @code (.c)
        CMPIStatus testEnumInstanceNames (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* classPath)
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
        stat.rc = (rc); \
        stat.msg = NULL; \
        return stat; \
    } while (0)

/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and a CMPIString message.

    The CMReturnWithString() macro builds a CMPIStatus object specifying a
    return code and a CMPIString message and exits the function in which it was
    executed, causing it to return that CMPIStatus object. CMReturnWithString()
    can only be used in functions that return CMPIStatus.

    @param rc A @ref CMPIrc value specifying the function return status.
    @param str A pointer to a CMPIString object specifying the message.
    @return This macro never returns; it contains a `return` statement and
        therefore exits the function from which it was called.

    @par Examples
    Example of code in an MI function that checks for an optional MB capability
    and returns with an error to the MB if the capability is not available.
    @code (.c)
    static const CMPIBroker* _broker;
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
        stat.rc = (rc); \
        stat.msg = (str); \
        return stat; \
    } while (0)


/**
    @brief Return the calling function with CMPIStatus specifying a return code
        and a C string message.

    The CMReturnWithChars() macro builds a CMPIStatus object specifying a
    return code and a C string message and exits the function in which it was
    executed, causing it to return that CMPIStatus object. CMReturnWithChars()
    can only be used in functions that return CMPIStatus.

    @param mb Points to a CMPIBroker structure.
    @param rc A @ref CMPIrc value specifying the function return status.
    @param chars A pointer to a C string (`char*`) specifying the message.
    @return This macro never returns; it contains a `return` statement and
        therefore exits the function from which it was called.

    @par Examples
    Example of code in a modifyInstance() MI function that is not implemented
    and returns to the MB with CMPI_RC_ERR_NOT_SUPPORTED and an according error
    message.
    @code (.c)
    static const CMPIBroker* _broker;
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
        stat.rc = (rc); \
        if (mb) \
            stat.msg = (mb)->eft->newString((mb), (chars), NULL); \
        else \
            stat.msg = NULL; \
        return stat; \
    } while (0)

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

    @todo openpegasus No test for this macro
*/
#ifdef CMPI_NO_INLINE
#define CMSetStatus(st, rc) \
    do \
    { \
        if (st) \
        { \
            (st)->rc = (rc); \
            (st)->msg = NULL; \
        } \
    } while (0)
#else
_CMPI_INLINE_MOD void CMSetStatus (CMPIStatus* st, CMPIrc rc)
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
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD void CMSetStatusWithString(
    CMPIStatus * st,
    CMPIrc rc,
    const CMPIString * msg)
{
    if (st)
    {
        (st)->rc = (rc);
        (st)->msg = (msg);
    }
}
#   else
#      define CMSetStatusWithString(st_,rc_,msg_) \
      do \
      { \
          if (st_) \
          { \
              (st_)->rc = (rc_); \
              (st_)->msg = (msg_); \
          } \
      } while (0)
#   endif


/** @brief Initializes CMPIStatus struct with return code and
           message text message.

    CMSetStatusWithChars convenience function initializes a
    CMPIStatus struct with @p rcp and either a null msg or  a
    new CMPIString created from @p msg if @p msg is not NULL.

    @param mb Points to CMPIBroker. Required to create CMPIString.
    @param st Points to CMPIStatus object.
    @param rc CMPIrc return code to be inserted into into CMPIStatus @p st.
    @param msg C string character string containing the message
               text or NULL if no text is to be added to the
               CMPIStatus @p st.
    @see CMPIStatus
    @par Example
    @code(.c)
      static CMPIBroker *_broker; // Cany be populated with stub macro
      . . .
      CMPIStatus rc = { CMPI_RC_OK, NULL };
      CMSetStatusWithChars (_broker, &rc,
        CMPI_RC_ERR_NOT_SUPPORTED, "CIM_ERR_NOT_SUPPORTED");
    @endcode
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD void CMSetStatusWithChars(
    const CMPIBroker * mb,
    CMPIStatus * st,
    CMPIrc rc,
    const char *msg)
{
    if (st)
    {
        (st)->rc = (rc);
        if (mb)
        {
            (st)->msg = (mb)->eft->newString ((mb), (msg), NULL);
        }
        else
        {
            (st)->msg = NULL;
        }
    }
}
#   else
#      define CMSetStatusWithChars(mb_,st_,rc_,msg_) \
      do \
      { \
          if (st_) \
          { \
              (st_)->rc=(rc_); \
              if (mb_) \
                  (st_)->msg=(mb_)->eft->newString((mb_),(msg_),NULL); \
              else \
                  (st_)->msg=NULL; \
          } \
      } while (0)
#   endif


/** @brief Tests any CMPI object or function return to determine if it is
     a NULL object.

    CMIsNullObject() tests any CMPI object @p object or function
    return to determine if it is NULL. The function call is
    defined as void* to encompass any CMPI encapsulated type.
    @param obj points to any CMPI object.
    @retval true The object is NULL.
    @retval false The object is NOT NULL.
    @par Example
    @code(.c)
        cop = CMNewObjectPath(_broker,"root/SampleProvider", _ClassName, &rc);
        CMAddKey(cop2, "Identifier", (CMPIValue *)&value1, CMPI_uint8);
        // test for NULL before creating insance from cop
        if(!CMIsNullObject(cop))
        {
            instance2 = CMNewInstance(_broker, cop2, &rc);
            ...
        }
    @endcode
    @todo object is incorrect word.  Need to define what
          encompasses CMPI Object. Do we need list of all
          possibles?
    @todo test this to be sure it is correct, in particular
          function repsonse
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD CMPIBoolean CMIsNullObject (const void *obj)
{
    return ((obj) == NULL || *((void **) (obj)) == NULL);
}
#   else
#      define CMIsNullObject(obj) \
           ((obj)==NULL || *((void**)(obj))==NULL)
#   endif

/** @brief Tests a CMPIData object for null Value data item.

    CMIsNullValue() tests the state of a CMPIData object @p val
    for the CMPI_nullValue state.
    @param val CMPIValue object
    @retval true NULL value CMPIData.val value.
    @retval false Not NULL CMPIData.val value.
    @see CMPIData
    @par Example
    Process  received method call that includes a CIMObject path @p ref for
    classname, method name, arguments, argument name and value in the argument
    @code(.c)
    CMPIStatus* rc;
    className = CMGetClassName(ref, &rc);
    name = CMGetCharsPtr(className, &rc);
    if(!strcmp(name, _ClassName)){
       if(!strcmp ("SayHello", methodName)){
            // gets the number of arguments contained in "in"
            Args. if(CMGetArgCount(in, &rc) > 0){
                // gets Name argument value
                data = CMGetArg(in, "MethodName", &rc);
                // should we check rc on response.
                //check for data type and !null value of
                argument value rcvd if(data.type == CMPI_string
                && !(CMIsNullValue(data))) {
                    strCat = CMGetCharsPtr(data.value.string, &rc);
                    strcat(result, strCat);
                    strcat(result, "!");
                    // create the new string to return to client
                    str1 = CMNewString(_broker, result, &rc);
                    val1.string = str1;
                }
            . . .
    @endcode
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD CMPIBoolean CMIsNullValue (const CMPIData val)
{
  return ((val.state) & CMPI_nullValue);
}
#   else
#      define CMIsNullValue(val) \
           ((val.state) & CMPI_nullValue)
#   endif

/** @brief Tests CMPIData object for keyValue data item.

    CMIsKeyValue() tests @p val a CMPIValue to determine if it
    is a keyValue data item.
    @param val Points to CMPIValue object to be tested.
    @retval true CMPIData object is keyValue
    @retval false CMPIData object is NOT keyValue
    @see CMPIValueState CMPIData
    @todo No test for this in OpenPegasus
    @todo this is value call, not pointer.  Shouldn't this be
          pointer call?
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD CMPIBoolean CMIsKeyValue (CMPIData val)
{
  return ((val.state) & CMPI_keyValue);
}
#   else
#      define CMIsKeyValue(val) \
           ((val.state) & CMPI_keyValue)
#   endif

/** @brief Tests CMPIData object for array data item type.

    CMIsArray() tests @p val a CMPIValue to determine if it is
    an array.
    @param val Points to Value object
    @retval true CMPIData object is array type.
    @retval false CMPIData object is NOT array type
    @todo KS this needs example.
    @todo not tested in OpenPegasus
    @todo this is defined as
  */
#   ifdef CMPI_INLINE
_CMPI_INLINE_MOD CMPIBoolean CMIsArray (const CMPIData val)
{
  return ((val.type) & CMPI_ARRAY);
}
#   else
#      define CMIsArray(val) \
           ((val.type) & CMPI_ARRAY)
#   endif

// TODO: From here on down, adjust to the format proposed above.
/**
 * @}
 * @addtogroup convenience-func-edt
 * @{
 */


    // Life-cycle functions on EDTs


/**
   @def CMClone(obj,rc)

   CMClone() macro calls clone() function for any the objects of any CMPI
   function table since all function tables are required to have the clone()
   function.


   @param obj cmpi object to be cloned.
   @param [out] rc  If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
   @return @parblock If successful, returns a pointer to the
         copied clone of the object defined by @p obj.

     The returned CMPIEnumerationFilter object shall be explicitly
     released by the MI using CMPIEnumerationFilterFT.release().

     If not successful, returns NULL.
     @endparblock

   @par Errors
   The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` Operation successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` The @p ef handle is invalid.

   @par Example
   Clone an instance to add to an array
   @code(.c)
       // preexisting instance CMPIInstance * ci)
        {
            CMPIStatus rc = { CMPI_RC_OK, NULL };
            CMPIInstance * inst;
            if(ci)
            {
                // clone the instance to be added to the array
                inst = CMClone(ci, &rc);
                . . .
            }
   @endcode

   @see CMPIContextFT.clone(), CMPIResultFT.clone(), CMPIErrorFT.clone(),
     CMPIInstanceFT.clone(), CMPIObjectPathFT.clone(),
     CMPISelectExpFT.clone(), CMPISelectCondFT.clone(),
     CMPISubCondFT.clone(), CMPIPredicateFT.clone(),
     CMPIArgsFT.clone(), CMPIStringFT.clone(),
     CMPIIEnumerationFT.clone(), CMPIDateTimeFT.clone(),
     CMPIPropertyListFT.clone(), CMPIEnumerationFilterFT.clone(),
  @todo KS test if we need brief in this and release doc
*/
#   define CMClone(obj,rc) \
        ((obj)->ft->clone((obj),(rc)))

/**
   @def CMRelease(obj)

   Macro to call the function table release release function for an object of
   any CMPI function table since all function tables are required
   to have the clone() function.

   This indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free the
     resources associated with the object during the call to
     this function, or later during some garbage collection
     cycle.

     @param obj Points to the object to be released.
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
     CMPIIEnumerationFT.release(), CMPIDateTimeFT.release(),
     CMPIPropertyListFT.release(),
     CMPIEnumerationFilterFT.release(),
     @par Example
     Code to clean up after attempting to create an instance @p inst
     @code(.c)
         CMPIStatus rc = { CMPI_RC_OK, NULL };
         CMPISelectExp *se_def = NULL;
         clone = CMClone (se_def, &rc);
         // . . . test @rc for good completion and use clone if
         CMRelease (clone);
     @endcode
 */
#   define CMRelease(obj) \
        ((obj)->ft->release((obj)))


    // CMPIInstance macros


#   ifdef CMPI_INLINE
/** @brief Get a property in a CMPIInstance object by name.

     CMGetProperty() executes CMPIInstanceFT.getProperty() to get a property
     in @p inst a CMPIInstance by @p name.
     @param inst Instance this pointer.
     @param name Property name.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return CMPIData with Property value. If not successful CMPIData.state
     will have the @ref CMPI_badValue.
     @see CMPIInstanceFT.getProperty()
     @todo used  and tested extensively in OpenPegasus
     @par Example
     @code(.c)
     CMPIInstance* inst = NULL;
     // . . . make the inst
     CMPIData rtnData;
     const char* name1 = "propertyName";
     rtnData = CMGetProperty(inst, name1, &rc);
     assert(rtnData.state != CMPI_badValue);
     @endcode
      */
_CMPI_INLINE_MOD CMPIData CMGetProperty(
    const CMPIInstance * inst,
    const char *name,
    CMPIStatus * rc)
{
  return ((inst)->ft->getProperty ((inst), (name), (rc)));
}
#   else
#      define CMGetProperty(inst,n,rc) \
           ((inst)->ft->getProperty((inst),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a property in a CMPIInstance object by index.

     CMGetPropertyAt() executes CMPIInstanceFT.getPropertyAt().
     @param inst Instance this pointer.
     @param index Position in the internal data array.
     @param[out] name Returned property name (suppressed when NULL).
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return CMPIData with property value. If not successful CMPIData.state
     will have the @ref CMPI_badValue.
     @see CMPIInstanceFT.getPropertyAt()
     @todo used in OpenPegasus
      */
_CMPI_INLINE_MOD CMPIData CMGetPropertyAt(
    const CMPIInstance * inst,
    CMPICount index,
    CMPIString ** name,
    CMPIStatus * rc)
{
  return ((inst)->ft->getPropertyAt ((inst), (index), (name), (rc)));
}
#   else
#      define CMGetPropertyAt(inst,num,s,rc) \
           ((inst)->ft->getPropertyAt((inst),(num),(s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set a property value in a CMPIInstance object by name.
     CMSetProperty() executes CMPIInstanceFT.setProperty().
     @param inst Points to CMPIInstance.
     @param name Points to property name.
     @param value Address of value structure.
     @param type Value type.
     @return Service return status.
     @see CMPIInstanceFT.setProperty()
     @todo Used and tested extensively in OpenPegasus
      */
_CMPI_INLINE_MOD CMPIStatus CMSetProperty(
    const CMPIInstance * inst,
    const char *name,
    const CMPIValue * value,
    CMPIType type)
{
  return ((inst)->ft->setProperty ((inst), (name), (value), (type)));
}
#   else
#      define CMSetProperty(inst,n,v,t) \
           ((inst)->ft->setProperty((inst),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the number of properties in a CMPIInstance  object.
     CMGetPropertyCount() executes CMPIInstanceFT.getPropertyCount().
     @param inst Instance this pointer.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return Number of properties; 0 if not successful.
     @see CMPIInstanceFT.getPropertyCount()
      */
_CMPI_INLINE_MOD CMPICount CMGetPropertyCount(
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((inst)->ft->getPropertyCount ((inst), (rc)));
}
#   else
#      define CMGetPropertyCount(inst,rc) \
           ((inst)->ft->getPropertyCount((inst),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a CMPIObjectPath object from a CMPIInstance object.
    CMGetObjectPath() executes CMPIInstanceFT.getObjectPath() to
    get the CMPIObject path from @p inst.
    @param inst Points to CMPIInstance.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The generated CMPIObjectPath or NULL.
    @see CMPIInstanceFT.getObjectPath()
    @todo tested extensively in OpenPegasus cmpiTestMethodProvider.c
      */
_CMPI_INLINE_MOD CMPIObjectPath *CMGetObjectPath(
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((inst)->ft->getObjectPath ((inst), (rc)));
}
#   else
#      define CMGetObjectPath(inst,rc) \
           ((inst)->ft->getObjectPath((inst),(rc)))
#   endif

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** @brief Set the instance path component of a CMPIInstance object.

     CMSetObjectPath() executes CMPIInstanceFT.setObjectPath() to set
     @p obj.
     @param inst Points to the CMPIInstance structure.
     @param op Points to the new CMPIObjectPath.
     @return CMPIStatus structure containing the function return status.
     @see CMPIInstanceFT.setObjectPath()
     @todo Used in OpenPegasus
      */
_CMPI_INLINE_MOD CMPIStatus CMSetObjectPath(
    CMPIInstance * inst,
    const CMPIObjectPath * op)
{
  return ((inst)->ft->setObjectPath ((inst), (op)));
}
#   else
#      define CMSetObjectPath(inst,op) \
           ((inst)->ft->setObjectPath((inst),(op)))
#   endif
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_INLINE
/** @brief Attach a property filter to a CMPIInstance object.
     CMSetPropertyFilter() executes CMPIInstanceFT.setPropertyFilter() to
     attach @p propertyList to CMPIInstance @p inst.
     @param inst Points to the CMPIInstance structure.
     @param propertyList If not NULL, the members of the array define one
         or more Property names to be accepted by setProperty operations.
     @param keys Deprecated, ignored by MB, maintained here for compatibility.
     @return Function return status.
     @see CMPIInstanceFT.setPropertyFilter()
     @todo No use in OpenPegasus
      */
_CMPI_INLINE_MOD CMPIStatus CMSetPropertyFilter(
    CMPIInstance * inst,
    const char **propertyList,
    char **keys)
{
  return ((inst)->ft->setPropertyFilter ((inst), (propertyList), (keys)));
}
#   else
#      define CMSetPropertyFilter(inst,pl,k) \
           ((inst)->ft->setPropertyFilter((inst),(pl),(k)))
#   endif

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
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
*/
_CMPI_INLINE_MOD CMPIStatus CMSetPropertyWithOrigin(
    const CMPIInstance * inst,
    const char *name,
    const CMPIValue * value,
    CMPIType type,
    const char * origin)
{
  return ((inst)->ft->setPropertyWithOrigin (
      (inst), (name), (value), (type), (origin)));
}
#   else
#      define CMSetPropertyWithOrigin(inst,n,v,t,o) \
         ((inst)->ft->setPropertyWithOrigin((inst),(n),(CMPIValue*)(v),(t),(o)))
#   endif
#   endif /* CMPI_VER_200 */


   // CMPIObjectPath macros


#   ifdef CMPI_INLINE
/** @brief Set the host name component in a CMPIObjectPath object.

    CMSetHostName() executes CMPIObjectPathFT.setHostname().
     @param op Pointer to target CMPIObjectPath.
     @param hn The hostname string
     @return Function return CMPIStatus.
     @see CMPIObjectPathFT.setHostname()
     @todo OpenPegasus used.
      */
_CMPI_INLINE_MOD CMPIStatus
CMSetHostname (CMPIObjectPath * op, const char *hn)
{
  return ((op)->ft->setHostname ((op), (hn)));
}
#   else
#      define CMSetHostname(op,n) \
           ((op)->ft->setHostname((op),(n)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the host name component in a CMPIObjectPath object.

    CMGetHostName() executes CMPIObjectPathFT.getHostname() to
    get the host name component from @p op a CMPIObjectPath
    @see CMPIObjectPathFT.getHostname()
    @todo OpenPegasus used.
      */
_CMPI_INLINE_MOD CMPIString *CMGetHostname(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getHostname ((op), (rc)));
}
#   else
#      define CMGetHostname(op,rc) \
           ((op)->ft->getHostname((op),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set the host name component in a CMPIObjectPath object.
     CMSetNameSpace() executes CMPIObjectPathFT.setNameSpace()
     to set @p ns into @p op.
     @param op ObjectPath this pointer.
     @param ns The namespace string
     @return Service return status.
     @see CMPIObjectPathFT.setNameSpace()
     @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPIStatus
CMSetNameSpace (CMPIObjectPath * op, const char *ns)
{
  return ((op)->ft->setNameSpace ((op), (ns)));
}
#   else
#      define CMSetNameSpace(op,n) \
           ((op)->ft->setNameSpace((op),(n)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the namespace component from a CMPIObjectPath object.
     CMGetNameSpace() executes CMPIObjectPathFT.getNameSpace().
     @param op Points to CMPIObject.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return The namespace component.
     @see CMPIObjectPathFT.getNameSpace()
     @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPIString *CMGetNameSpace(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getNameSpace ((op), (rc)));
}
#   else
#      define CMGetNameSpace(op,rc) \
           ((op)->ft->getNameSpace((op),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set class name component in a CMPIObjectPath object.
    CMSetClassName() executes CMPIObjectPathFT.getNameSpace().
    @param op Points to CMPIObject.
    @param cn The new class name
    @return Function return status.
    @see CMPIObjectPathFT.getNameSpace()
*/
_CMPI_INLINE_MOD CMPIStatus CMSetClassName(
    CMPIObjectPath * op,
    const char *cn)
{
  return ((op)->ft->setClassName ((op), (cn)));
}
#   else
#      define CMSetClassName(op,n) \
           ((op)->ft->setClassName((op),(n)))
#   endif
#   ifdef CMPI_INLINE
/** Get the classname component from CMPIObjectPath.
    CMGetClassName() executes CMPIObjectPathFT.getClassName().
    @param op ObjectPath this pointer.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The classname component or NULL.
    @see CMPIObjectPathFT.getClassName()
    @todo OpenPegasus used and tested.
      */
_CMPI_INLINE_MOD CMPIString *CMGetClassName(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getClassName ((op), (rc)));
}
#   else
#      define CMGetClassName(op,rc) \
           ((op)->ft->getClassName((op),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Add or replace a key binding in a CMPIObjectPath object.
    CMAddKey() executes CMPIObjectPathFT.addKey()
    @param op Points to CMPIObjectPath.
    @param name Key property name.
    @param value Points to CMPIValue structure.
    @param type CMPIType Value type.
    @return function CMPIStatus return status.
    @see CMPIObjectPathFT.addKey()
    @todo OpenPegasus tested and used
*/
_CMPI_INLINE_MOD CMPIStatus CMAddKey(
    CMPIObjectPath * op,
    const char *name,
    const CMPIValue * value,
    const CMPIType type)
{
  return ((op)->ft->addKey ((op), (name), (value), (type)));
}
#   else
#      define CMAddKey(op,n,v,t) \
           ((op)->ft->addKey((op),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a key binding in a CMPIObjectPath object by name.
    CMGetKey() executes CMPIObjectPathFT.getKey() to get a
    key binding by name.
    @param op Points to CMPIObjectPath.
    @param[out] name Returned property name.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData.
    @see CMPIObjectPathFT.getKey()
    @todo OpenPegasus tested and used
      */
_CMPI_INLINE_MOD CMPIData CMGetKey(
    const CMPIObjectPath * op,
    const char *name,
    CMPIStatus * rc)
{
  return ((op)->ft->getKey ((op), (name), (rc)));
}
#   else
#      define CMGetKey(op,n,rc) \
           ((op)->ft->getKey((op),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a key binding in a CMPIObjectPath object by index.
    CMGetKeyAt() executes CMPIObjectPathFT.getKeyAt() to get a key
    binding defined by @p index.
    @param op Points to CMPIObjectPath.
    @param index Position in the internal Data array.
    @param[out] name Returned property name (suppressed when NULL).
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Data value.
    @see CMPIObjectPathFT.getKeyAt()
    @todo OpenPegasus used and tested
      */
_CMPI_INLINE_MOD CMPIData CMGetKeyAt(
    const CMPIObjectPath * op,
    CMPICount index,
    CMPIString ** name,
    CMPIStatus * rc)
{
  return ((op)->ft->getKeyAt ((op), (index), (name), (rc)));
}
#   else
#      define CMGetKeyAt(op,i,n,rc) \
           ((op)->ft->getKeyAt((op),(i),(n),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** @brief Get the number of key bindings in a CMPIObjectPath object.
    CMGetKeyCount() executes CMPIObjectPathFT.getKeyCount() to get the
    number of key bindings in a @p op a CMPIObjectPath object.
    @param op Points to CMPIObjectPath.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of properties.
    @see CMPIObjectPathFT.getKeyCount()
*/
_CMPI_INLINE_MOD CMPICount CMGetKeyCount(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getKeyCount ((op), (rc)));
}
#   else
#      define CMGetKeyCount(op,rc) \
           ((op)->ft->getKeyCount((op),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set/replace the namespace and class name components in a
    CMPIObjectPath object from another CMPIObjectPath object.
    CMSetNameSpaceFromObjectPath() executes
    CMPIObjectPathFT.setNameSpaceFromObjectPath().
    @param op Points to CMPIObjectPath.
    @param src Source input.
    @return Function return status.
    @see CMPIObjectPathFT.setNameSpaceFromObjectPath()
*/
_CMPI_INLINE_MOD CMPIStatus CMSetNameSpaceFromObjectPath(
    CMPIObjectPath * op,
    const CMPIObjectPath * src)
{
  return ((op)->ft->setNameSpaceFromObjectPath ((op), (src)));
}
#   else
#      define CMSetNameSpaceFromObjectPath(op,s) \
           ((op)->ft->setNameSpaceFromObjectPath((op),(s)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set host name, namespace, and class name components
     in a CMPIObjectPath object from another CMPIObjectPath
     object.
    CMSetHostAndNameSpaceFromObjectPath() executes
    CMSetHostAndNameSpaceFromObjectPath.
    @param op Points to CMPIObjectPath.
    @param src Source input.
    @return Function return status.
    @see CMSetHostAndNameSpaceFromObjectPath
      */
_CMPI_INLINE_MOD CMPIStatus CMSetHostAndNameSpaceFromObjectPath(
    CMPIObjectPath * op,
    const CMPIObjectPath * src)
{
  return ((op)->ft->setHostAndNameSpaceFromObjectPath ((op), (src)));
}
#   else
#      define CMSetHostAndNameSpaceFromObjectPath(op,s) \
           ((op)->ft->setHostAndNameSpaceFromObjectPath((op),(s)))
#   endif

#ifdef CMPI_INLINE
/** @brief Get a class qualifier.
    CMGetClassQualifier() executes CMPIObjectPathFT.getClassQualifier().
    @param op Points to CMPIObjectPath.
    @param qName Qualifier name.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getClassQualifier()
    @todo OpenPegasus Not implemented
*/
_CMPI_INLINE_MOD CMPIData CMGetClassQualifier(
    const CMPIObjectPath* op,
    const char *qName,
    CMPIStatus *rc)
{
    return ((op)->ft->getClassQualifier((op),(qName),(rc)));
}
#else
#   define CMGetClassQualifier(op,qName,rc) \
        ((op)->ft->getClassQualifier((op),(qName),(rc)))
#endif

#ifdef CMPI_INLINE
/** @brief Get a property qualifier.
    CMGetPropertyQualifier() executes CMPIObjectPathFT.getPropertyQualifier()
    @param op Points to CMPIObjectPath.
    @param pName Property name.
    @param qName Qualifier name.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getPropertyQualifier()
    @todo OpenPegasus Not implemented
*/
_CMPI_INLINE_MOD  CMPIData CMGetPropertyQualifier(
    const CMPIObjectPath* op,
    const char *pName,
    const char *qName,
    CMPIStatus *rc)
{
    return((op)->ft->getPropertyQualifier((op),(pName),(qName),(rc)));
}
#else
#   define CMGetPropertyQualifier(op,pName,qName,rc) \
        ((op)->ft->getPropertyQualifier((op),(pName),(qName),(rc)))
#endif

#ifdef CMPI_INLINE
/** @brief Get a method qualifier.
    @param op Points to CMPIObjectPath.
    @param methodName Method name.
    @param qName Qualifier name.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getMethodQualifier()
    @todo OpenPegasus Not implemented
*/
_CMPI_INLINE_MOD  CMPIData CMGetMethodQualifier(
    const CMPIObjectPath* op,
    const char *methodName,
    const char *qName,
    CMPIStatus *rc)
{
    return((op)->ft->getMethodQualifier((op),(methodName),(qName),(rc)));
}
#else
#   define CMGetMethodQualifier(op,methodName,qName,rc) \
        ((op)->ft->getMethodQualifier((op),(methodName),(qName),(rc)))
#endif

#ifdef CMPI_INLINE
/** @brief Get a parameter qualifier.
    CMGetParameterQualifier() executes CMPIObjectPathFT.getParameterQualifier().
    @param op Points to CMPIObjectPath.
    @param mName Method name.
    @param pName Parameter name.
    @param qName Qualifier name.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getParameterQualifier()
    @todo OpenPegasus Not implemented
*/
_CMPI_INLINE_MOD  CMPIData CMGetParameterQualifier(
    const CMPIObjectPath* op,
    const char *mName,
    const char *pName,
    const char *qName,
    CMPIStatus *rc)
{
    return((op)->ft->getParameterQualifier((op),(mName),(pName),(qName),(rc)));
}
#else
#   define CMGetParameterQualifier(op,mName,pName,qName,rc) \
        ((op)->ft->getParameterQualifier((op),(mName),(pName),(qName),(rc)))
#endif


    // CMPIArray macros


#   ifdef CMPI_INLINE
/** @brief Get the number of array elements in a CMPIArray object.
    CMGetArrayCount() executes CMPIArrayFT.getSize().
    Function name is different but not arugments or return.
    @param ar Points to CMPIArray.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSize()
    @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPICount CMGetArrayCount(
    const CMPIArray * ar,
    CMPIStatus * rc)
{
    return ((ar)->ft->getSize ((ar), (rc)));
}
#   else
#      define CMGetArrayCount(ar,rc) \
           ((ar)->ft->getSize((ar),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the type of the array elements in a CMPIArray object.
    CMGetArrayType() executes CMPIArrayFT.getSimpleType(). Function names
    are different but arguments and return are the same.
    @param ar Points to CMPIArray.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSimpleType()
    @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPIType CMGetArrayType(
    const CMPIArray * ar,
    CMPIStatus * rc)
{
    return ((ar)->ft->getSimpleType ((ar), (rc)));
}
#   else
#      define CMGetArrayType(ar,rc) \
           ((ar)->ft->getSimpleType((ar),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the value of an array element in a CMPIArray object by index.
    CMGetArrayElementAt() executes CMPIArrayFT.getElementAt().
    @param ar Points to CMPIArray.
    @param index Position in the internal data array.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIData Element value.
    @see CMPIArrayFT.getElementAt()
    @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPIData CMGetArrayElementAt(
    const CMPIArray * ar,
    CMPICount index,
    CMPIStatus * rc)
{
    return ((ar)->ft->getElementAt ((ar), (index), (rc)));
}
#   else
#      define CMGetArrayElementAt(ar,n,rc) \
           ((ar)->ft->getElementAt((ar),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Set the value of an existing array element in a CMPIArray object
         by index.
    CMSetArrayElementAt() executes CMPIArrayFT.setElementAt().
    @param ar  Points to CMPIArray.
    @param index Position in the internal data array.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIArrayFT.setElementAt()
    @todo OpenPegasus tested and used
*/
_CMPI_INLINE_MOD CMPIStatus CMSetArrayElementAt(
    CMPIArray * ar,
    CMPICount index,
    const CMPIValue * value,
    CMPIType type)
{
    return ((ar)->ft->setElementAt ((ar), (index), (value), (type)));
}
#   else
#      define CMSetArrayElementAt(ar,n,v,t) \
           ((ar)->ft->setElementAt((ar),(n),(CMPIValue*)(v),(t)))
#   endif


    // CMPIArgs macros


#   ifdef CMPI_INLINE
/** @brief Set a method parameter in a CMPIArgs object.
    CMAddArg() executes CMPIArgsFT.addArg() to add or replace a method
    parameter named @p name with the CMPIValue @p value and type @p type
    in a CMPIArgs object @p as.
    @param as Points to CMPIArgs.
    @param name Argument name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIArgsFT.addArg()
    @todo OpenPegasus used and tested
*/
_CMPI_INLINE_MOD CMPIStatus CMAddArg(
    CMPIArgs * as,
    char *name,
    const CMPIValue * value,
    const CMPIType type)
{
    return ((as)->ft->addArg ((as), (name), (CMPIValue*)(value), (type)));
}
#   else
#      define CMAddArg(as,n,v,t) \
           ((as)->ft->addArg((as),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a method parameter in a CMPIArgs object by name.

    CMGetArg() executes CMPIArgsFT.getArg() to get a method
    parameter from a CMPIArgs object by its name.
    @param as Args this pointer.
    @param name Argument name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see  CMPIArgsFT.getArg()
    @todo OpenPegasus used
*/
_CMPI_INLINE_MOD CMPIData CMGetArg(
    const CMPIArgs * as,
    const char *name,
    CMPIStatus * rc)
{
    return ((as)->ft->getArg ((as), (name), (rc)));
}
#   else
#      define CMGetArg(as,n,rc) \
           ((as)->ft->getArg((as),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a method parameter in a CMPIArgs object by index.
    CMGetArgAt() executes CMPIArgsFT.getArgAt() to get an
    argument value from a CMPIArgs object by its index.
    @param as Points to CMPIArgs.
    @param index Position in the internal Data array.
    @param name Output: Returned argument name (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see  CMPIArgsFT.getArgAt()
    @todo OpenPegasus used
    @todo removed all params and returns
*/
_CMPI_INLINE_MOD CMPIData CMGetArgAt(
    const CMPIArgs * as,
    CMPICount index,
    CMPIString ** name,
    CMPIStatus * rc)
{
    return ((as)->ft->getArgAt ((as), (index), (name), (rc)));
}
#   else
#      define CMGetArgAt(as,p,n,rc) \
           ((as)->ft->getArgAt((as),(p),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get number of arguments in a CMPIArgs array.

    CMGetArgCount() executes CMPIArgsFT.getArgCount() to get the
    number of arguments in the CMPIArgs array.
    @param as Points to CMPIArgs.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of properties.
    @see  CMPIArgsFT.getArgCount()
    @todo OpenPegasus used
*/
_CMPI_INLINE_MOD CMPICount CMGetArgCount (const CMPIArgs * as, CMPIStatus * rc)
{
    return ((as)->ft->getArgCount ((as), (rc)));
}
#   else
#      define CMGetArgCount(as,rc) \
           ((as)->ft->getArgCount((as),(rc)))
#   endif

/**
   @brief Macro to get the pointer to the C-language
      representation of a CMPIString. This macro provides NO
      argument checking or return code.
   @def CMGetCharPtr(st)
   @param st
   @par Example
   @code(.c)
    myObjPath= CMNewObjectPath(
        _broker,
        CMGetCharPtr(CMGetNameSpace(ref,0)),
        "TestCMPI_KeyReturned",
        0);
   @endcode
   @see CMGetCharsPtr()
   @todo - KS confirm this since the doc was just a guess right now
*/
#   define CMGetCharPtr(st) \
        ((char*)(st)->hdl)

#   ifdef CMPI_INLINE
/** @brief Get a pointer to a C-language string representation of a
         CMPIString object.
    CMGetCharsPtr() executes CMPIStringFT.getCharPtr() to get a pointer
    to the C-language string representation of @p st. it differs from
    CMGetCharPtr() in that it includes a CMPIStatus return code.
    @param st Points to CMPIString.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Pointer to char* representation.
    @see CMPIStringFT.getCharPtr()
    @par Example
    @code(.c)
      CMPIObjectPath *op = NULL;
      CMPIStatus rc = { CMPI_RC_OK, NULL };
      objPath = CMNewObjectPath (_broker,
          CMGetCharsPtr(CMGetNameSpace(ref, &rc), NULL),
          class,
          &rc);
    @endcode
*/
_CMPI_INLINE_MOD char * CMGetCharsPtr(
    const CMPIString * st,
    CMPIStatus * rc)
{
    return ((st)->ft->getCharPtr ((st), (rc)));
}
#   else
#      define CMGetCharsPtr(st,rc) \
           ((st)->ft->getCharPtr((st),(rc)))
#   endif


    // CMPIDateTime macros


#   ifdef CMPI_INLINE
/** @brief Get the value of a CMPIDateTime object in the string
         format defined for the CIM datetime type.
    CMGetStringFormat() executes CMPIDateTimeFT.getStringFormat().
    @param dt Points to the CMPIDateTime object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return DateTime as UTC string.
    @see CMPIDateTimeFT.getStringFormat()
      */
_CMPI_INLINE_MOD CMPIString *CMGetStringFormat(
    const CMPIDateTime * dt,
    CMPIStatus * rc)
{
    return ((dt)->ft->getStringFormat ((dt), (rc)));
}
#   else
#      define CMGetStringFormat(dt,rc) \
           ((dt)->ft->getStringFormat((dt),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the value of a CMPIDateTime object in binary format.
    CMGetBinaryFormat() executes CMPIDateTimeFT.getBinaryFormat().
    @param dt Points to the CMPIDateTime object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return DateTime in binary.
    @see CMPIDateTimeFT.getBinaryFormat()
    @todo OpenPegasus used and tested
      */
_CMPI_INLINE_MOD CMPIUint64 CMGetBinaryFormat(
    const CMPIDateTime * dt,
    CMPIStatus * rc)
{
    return ((dt)->ft->getBinaryFormat ((dt), (rc)));
}
#   else
#      define CMGetBinaryFormat(dt,rc) \
           ((dt)->ft->getBinaryFormat((dt),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Test whether a CMPIDateTime object contains an interval value.
    CMIsInterval() executes CMPIDateTimeFT.isInterval().
    @param dt Points to the CMPIDateTime object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return True if interval value.
    @see CMPIDateTimeFT.isInterval()
*/
_CMPI_INLINE_MOD CMPIBoolean CMIsInterval(
    const CMPIDateTime * dt,
    CMPIStatus * rc)
{
    return ((dt)->ft->isInterval ((dt), (rc)));
}
#   else
#      define CMIsInterval(dt,rc) \
           ((dt)->ft->isInterval((dt),(rc)))
#   endif


    // CMPIError macros


#   ifdef CMPI_VER_200

#   ifdef CMPI_INLINE
/** @brief Get the `ErrorType` attribute of a CMPIError object.
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPIErrorType
    @see CMPIErrorFT.getErrorType()
    @note Inline code fixed in CMPI 2.1
    @todo OpenPegasus used and tested
 */
_CMPI_INLINE_MOD CMPIErrorType CMGetErrorType(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getErrorType ((er), (rc)));
}
#   else
#      define CMGetErrorType(er,rc) \
           ((er)->ft->getErrorType((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `OtherErrorType` attribute of a CMPIError object.
    CMGetOtherErrorType() executes CMPIErrorFT.getOtherErrorType().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOtherErrorType()
    @note Inline code fixed in CMPI 2.1
    @todo OpenPegasus used and tested macro
 */
_CMPI_INLINE_MOD CMPIString* CMGetOtherErrorType(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getOtherErrorType ((er), (rc)));
}
#   else
#      define CMGetOtherErrorType(er,rc) \
           ((er)->ft->getOtherErrorType((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `OwningEntity` attribute of a CMPIError object.
    CMGetOwningEntity() executes CMPIErrorFT.getOwningEntity().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOwningEntity()
    @note Inline code fixed in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIString* CMGetOwningEntity(
    const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getOwningEntity ((er), (rc)));
}
#   else
#      define CMGetOwningEntity(er,rc) \
           ((er)->ft->getOwningEntity((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `MessageID` attribute of a CMPIError object.
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getMessageID()
    @note Inline code fixed in CMPI 2.1
    @todo OpenPegasus tested.
 */
_CMPI_INLINE_MOD CMPIString* CMGetMessageID(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getMessageID ((er), (rc)));
}
#   else
#      define CMGetMessageID(er,rc) \
           ((er)->ft->getMessageID((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `Message` attribute of a CMPIError object.
    CMGetErrorMessage() executes CMPIErrorFT.getMessage().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getMessage()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
    */
_CMPI_INLINE_MOD CMPIString* CMGetErrorMessage(
    const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getMessage ((er), (rc)));
}
#   else
#      define CMGetErrorMessage(er,rc) \
           ((er)->ft->getMessage((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `PerceivedSeverity` attribute of a CMPIError object.
    CMGetPerceivedSeverity() executes CMPIErrorFT.getPerceivedSeverity().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return the perceived severity
    @see CMPIErrorFT.getPerceivedSeverity()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIErrorSeverity CMGetPerceivedSeverity(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getPerceivedSeverity ((er), (rc)));
}
#   else
#      define CMGetPerceivedSeverity(er,rc) \
           ((er)->ft->getPerceivedSeverity((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `ProbableCause` attribute of a CMPIError object.
    CMGetProbableCause() executes CMPIErrorFT.getProbableCause().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A probable cause value
    @see CMPIErrorFT.getProbableCause()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIErrorProbableCause CMGetProbableCause(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getProbableCause ((er), (rc)));
}
#   else
#      define CMGetProbableCause(er,rc) \
           ((er)->ft->getProbableCause((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `ProbableCauseDescription` attribute of a CMPIError object.
    getProbableCauseDescription() executes
    CMPIErrorFT.getProbableCauseDescription().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getProbableCauseDescription()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIString* CMGetProbableCauseDescription(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getProbableCauseDescription ((er), (rc)));
}
#   else
#      define CMGetProbableCauseDescription(er,rc) \
           ((er)->ft->getProbableCauseDescription((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `RecommendedActions` array attribute of a CMPIError object.
    CMGetRecommendedActions() executes CMPIErrorFT.getRecommendedActions().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A array of strings, which can be NULL
    @see CMPIErrorFT.getRecommendedActions()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIArray* CMGetRecommendedActions(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getRecommendedActions ((er), (rc)));
}
#   else
#      define CMGetRecommendedActions(er,rc) \
           ((er)->ft->getRecommendedActions((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `ErrorSource` attribute of a CMPIError object.
    CMGetErrorSource executes CMPIErrorFT.getErrorSource().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getErrorSource()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIString* CMGetErrorSource(
    const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getErrorSource ((er), (rc)));
}
#   else
#      define CMGetErrorSource(er,rc) \
           ((er)->ft->CMGetErrorSourcegetErrorSource((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `ErrorSourceFormat` attribute of a CMPIError object.
    CMGetErrorSourceFormat() executes CMPIErrorFT.getErrorSourceFormat().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A error source format  code
    @see CMPIErrorFT.getErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIErrorSrcFormat CMGetErrorSourceFormat(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getErrorSourceFormat ((er), (rc)));
}
#   else
#      define CMGetErrorSourceFormat(er,rc) \
           ((er)->ft->getErrorSourceFormat((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `OtherErrorSourceFormat` attribute of a CMPIError object.
    CMGetOtherErrorSourceFormat() executes
    CMPIErrorFT.getOtherErrorSourceFormat().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOtherErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
 */
_CMPI_INLINE_MOD CMPIString* CMGetOtherErrorSourceFormat(
    const CMPIError* er,
    CMPIStatus* rc)
{
    return ((er)->ft->getOtherErrorSourceFormat ((er), (rc)));
}
#   else
#      define CMGetOtherErrorSourceFormat(er,rc) \
           ((er)->ft->getOtherErrorSourceFormat((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the `CIMStatusCode` attribute of a CMPIError object.
    CMGetCIMStatusCode() executes CMPIErrorFT.getCIMStatusCode().
    @param er Points to the CMPIError object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return A CMPI Status code
    @see CMPIErrorFT.getCIMStatusCode()
    @note Inline form corrected in CMPI 2.1
    @todo OpenPegasus tested
*/
_CMPI_INLINE_MOD CMPIrc CMGetCIMStatusCode(const CMPIError* er, CMPIStatus* rc)
{
    return ((er)->ft->getCIMStatusCode ((er), (rc)));
}
#   else
#      define CMGetCIMStatusCode(er,rc) \
           ((er)->ft->getCIMStatusCode((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get `CIMStatusCodeDescription` attribute of a CMPIError object.
    CMGetCIMStatusCodeDescription() executes
        CMPIErrorFT.getCIMStatusCodeDescription().
    @param er Points to the CMPIError object.
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getCIMStatusCodeDescription()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIString* CMGetCIMStatusCodeDescription(
    const CMPIError* er,
    CMPIStatus* rc)
{
    return ((er)->ft->getCIMStatusCodeDescription ((er), (rc)));
}
#   else
#      define CMGetCIMStatusCodeDescription(er,rc) \
           ((er)->ft->getCIMStatusCodeDescription((er),(rc)))
#   endif

// KS_TODO Furtherest point updated
#   ifdef CMPI_INLINE
/** @brief Get the `MessageArguments` array attribute of a CMPIError object.
    @param er Points to the CMPIError object.
    @param rc Output: Serbice return status (surpressed when NULL)
    @return An array of CMPIStrings which represents the dynamic values
    @see CMPIErrorFT.getMessageArguments()
    @note Inline form corrected in CMPI 2.1
*/
_CMPI_INLINE_MOD CMPIArray* CMGetMessageArguments(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getMessageArguments ((er), (rc)));
}
#   else
#      define CMGetMessageArguments(er,rc) \
           ((er)->ft->getMessageArguments((er),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the error type of this error object.
    @param er Points to the CMPIError object.
    @param et The error type
    @return Output: Service return status
    @see CMPIErrorFT.setErrorType()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetErrorType(
    CMPIError* er,
    const CMPIErrorType et)
{
  return ((er)->ft->setErrorType ((er), (et)));
}
#   else
#      define CMSetErrorType(er,et) \
           ((er)->ft->setErrorType((er),(et)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the 'other' error type of this error object.
    @param er Points to the CMPIError object.
    @param oet A string which describes the error type, it is only valis when
        error type is "OTHER"
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorType()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetOtherErrorType(
    CMPIError* er,
    const char * oet)
{
  return ((er)->ft->setOtherErrorType ((er), (oet)));
}
#   else
#      define CMSetOtherErrorType(er,oet) \
           ((er)->ft->setOtherErrorType((er),(oet)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the description of the probable cause.
    @param er Points to the CMPIError object.
    @param pcd The probable cause string
    @return CMPIStatus structure containing the function return status.
    @see CMPIErrorFT.setProbableCauseDescription()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetProbableCauseDescription(
    CMPIError* er,
    const char * pcd)
{
  return ((er)->ft->setProbableCauseDescription ((er), (pcd)));
}
#   else
#      define CMSetProbableCauseDescription(er,pcd) \
           ((er)->ft->setProbableCauseDescription((er),(pcd)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the recomended actions array.
    @param er Points to the CMPIError object.
    @param ra An array of strings describing actions that shoudl
              be taken t deal with this error
    @return Output: Service return status
    @see CMPIErrorFT.setRecommendedActions()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetRecommendedActions(
    CMPIError* er,
    const CMPIArray* ra)
{
  return ((er)->ft->setRecommendedActions ((er), (ra)));
}
#   else
#      define CMSetRecommendedActions(er,ra)                            \
           ((er)->ft->setRecommendedActions((er),(ra)))
#   endif

#   ifdef CMPI_INLINE
/** Specifies a string which specifes The identifying information of the entity
    (i.e., the instance) generating the error.
    @param er Points to the CMPIError object.
    @param es String which describes the source.
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSource()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetErrorSource(
    const CMPIError* er,
    const char* es);
{
  return ((er)->ft->setErrorSource ((er), (es)));
}
#   else
#      define CMSetErrorSource(er,es) \
           ((er)->ft->setErrorSource((er),(es)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the source format of the error object
    @param er Points to the CMPIError object.
    @param esf the string which describes the source format
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetErrorSourceFormat(
    CMPIError* er,
    const CMPIErrorSrcFormat esf);
{
  return ((er)->ft->setErrorSourceFormat ((er), (esf)));
}
#   else
#      define CMSetErrorSourceFormat(er,esf) \
           ((er)->ft->setErrorSourceFormat((er),(esf)))
#   endif

#   ifdef CMPI_INLINE
/** Specifies A string defining "Other" values for ErrorSourceFormat.

    @param er Points to the CMPIError object.
    @param oef String which describes the other source format.
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorSourceFormat()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetOtherErrorSourceFormat(
    CMPIError* er,
    const char* oef)
{
  return ((er)->ft->setOtherErrorSourceFormat ((er), (oef)));
}
#   else
#      define CMSetOtherErrorSourceFormat(er,oef) \
           ((er)->ft->setOtherErrorSourceFormat((er),(oef)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the description of the status code.
    @param er Points to the CMPIError object.
    @param scd A string whcih describes the status code.
    @return Output: Service return status
    @see CMPIErrorFT.setCIMStatusCodeDescription()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetCIMStatusCodeDescription(
    CMPIError* er,
    const char* scd);
{
  return ((er)->ft->setCIMStatusCodeDescription ((er), (scd)));
}
#   else
#      define CMSetCIMStatusCodeDescription(er,scd) \
           ((er)->ft->setCIMStatusCodeDescription((er),(scd)))
#   endif

#   ifdef CMPI_INLINE
/** Sets an array of strings for the dynamic content of the message
    @param er Points to the CMPIError object.
    @param values Specifies an array of CMPIStrings containing the dynamic
    content of the message.
    @return Service return status
    @see CMPIErrorFT.setCIMMessageArguments()
    @note Inline form corrected in CMPI 2.1
 */
_CMPI_INLINE_MOD CMPIStatus CMSetMessageArguments(CMPIError* er,
                                                  CMPIArray* values)
{
  return ((er)->ft->setMessageArguments ((er), (values)));
}
#   else
#      define CMSetMessageArguments(er,values) \
           ((er)->ft->setMessageArguments((er),(values)))
#   endif

#   endif /* CMPI_VER_200 */


    // CMPIEnumeration Macros


#   ifdef CMPI_INLINE
/** Get the next element of this Enumeration.
    @param en Points to the CMPIEnumeration object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Element value.
    @see CMPIEnumerationFT.getNext()
      */
_CMPI_INLINE_MOD CMPIData CMGetNext(
    const CMPIEnumeration * en,
    CMPIStatus * rc)
{
  return ((en)->ft->getNext ((en), (rc)));
}
#   else
#      define CMGetNext(en,rc) \
           ((en)->ft->getNext((en),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Test for any elements left in this Enumeration.

    CMHasNext() executes CMPIEnumerationFt.hasNext() that
    tests for any elements left in @p en the CMPIEnumeration object.
    @param en Points to the CMPIEnumeration object.
    @param rc Output: Service return status (suppressed when NULL).
    @return True or false.
    @see CMPIEnumerationFT.hasNext()
      */
_CMPI_INLINE_MOD CMPIBoolean CMHasNext(
   const CMPIEnumeration * en,
   CMPIStatus * rc)
{
  return ((en)->ft->hasNext ((en), (rc)));
}
#   else
#      define CMHasNext(en,rc) \
           ((en)->ft->hasNext((en),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Convert a CMPIEnumeration object to a CMPIArray object.

    CMToArray() executes CMPIEnumerationFT.toArray() converts the
    CMPIEnumeration object represented by the argument @p en into a CMPIArray.
     @param en Points to the CMPIEnumeration object.
     @param rc Output: Service return status (suppressed when NULL).
     @return The Array.
    @see CMPIEnumerationFT.toArray()
*/
_CMPI_INLINE_MOD CMPIArray *CMToArray(
   const CMPIEnumeration * en,
   CMPIStatus * rc)
{
  return ((en)->ft->toArray ((en), (rc)));
}
#   else
#      define CMToArray(en,rc) \
           ((en)->ft->toArray((en),(rc)))
#   endif


   // CMPIResult Macros


#   ifdef CMPI_INLINE
/** Return a value/type pair.
    @param rslt Points to CMPIResult.
    @param value Address of a Value object.
    @param type Type of the Value object.
    @return Service return status.
    @see CMPIResultFT.returnData()
      */
_CMPI_INLINE_MOD CMPIStatus CMReturnData(
    const CMPIResult * rslt,
    const CMPIValue * value,
    const CMPIType type)
{
  return ((rslt)->ft->returnData ((rslt), (value), (type)));
}
#   else
#      define CMReturnData(rslt,v,t) \
           ((rslt)->ft->returnData((rslt),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Return a Instance object.
    @param rslt Points to CMPIResult.
    @param inst Instance to be returned.
    @return Service return status.
    @see CMPIResultFT.returnInstance()
      */
_CMPI_INLINE_MOD CMPIStatus CMReturnInstance(
    const CMPIResult * rslt,
    const CMPIInstance * inst)
{
  return ((rslt)->ft->returnInstance ((rslt), (inst)));
}
#   else
#      define CMReturnInstance(rslt,i) \
           ((rslt)->ft->returnInstance((rslt),(i)))
#   endif

#   ifdef CMPI_INLINE
/** Return a ObjectPath object..
    @param rslt Points to CMPIResult.
    @param ref ObjectPath to be returned.
    @return Service return status.
    @see CMPIResultFT.returnObjectPath()
      */
_CMPI_INLINE_MOD CMPIStatus CMReturnObjectPath(
    const CMPIResult * rslt,
    const CMPIObjectPath * ref)
{
  return ((rslt)->ft->returnObjectPath ((rslt), (ref)));
}
#   else
#      define CMReturnObjectPath(rslt,o) \
           ((rslt)->ft->returnObjectPath((rslt),(o)))
#   endif

#   ifdef CMPI_INLINE
/** Indicates no further data to be returned.
    @param rslt Points to CMPIResult.
    @return Service return status.
    @see CMPIResultFT.returnDone()
      */
_CMPI_INLINE_MOD CMPIStatus CMReturnDone(const CMPIResult * rslt)
{
  return ((rslt)->ft->returnDone ((rslt)));
}
#   else
#      define CMReturnDone(rslt) \
           ((rslt)->ft->returnDone((rslt)))
#   endif

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Return a CMPIError object instance
    @param rslt Points to CMPIResult.
    @param er Error to be returned.
    @return Service return status.
    @see CMPIResultFT.returnError()
*/
_CMPI_INLINE_MOD CMPIStatus CMReturnError(
    const CMPIResult* rslt,
    const CMPIError* er)
{
  return ((rslt)->ft->returnError ((rslt), (er)));
}
#   else
#      define CMReturnError(rslt,e) \
           ((rslt)->ft->returnError((rslt),(e)))
#   endif
#   endif /* CMPI_VER_200 */


    // CMPIContext Macros


#   ifdef CMPI_INLINE
/** Gets a named Context entry value.
     @param ctx Points to CMPIContext.
     @param name Context entry name.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return Entry value.
     @see CMPIContextFT.getEntry()
*/
_CMPI_INLINE_MOD CMPIData CMGetContextEntry(
    const CMPIContext * ctx,
    const char *name,
    CMPIStatus * rc)
{
  return ((ctx)->ft->getEntry ((ctx), (name), (rc)));
}
#   else
#      define CMGetContextEntry(ctx,n,rc)  \
           ((ctx)->ft->getEntry((ctx),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a Context entry value defined by its index.
    @param ctx Points to CMPIContext.
    @param index Position in the internal Data array.
    @param name Output: Returned Context entry name (suppressed when NULL).
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Entry value.
    @see CMPIContextFT.getEntryAt()
*/
_CMPI_INLINE_MOD CMPIData CMGetContextEntryAt(
    const CMPIContext * ctx,
    CMPICount index,
    CMPIString ** name,
    CMPIStatus * rc)
{
  return ((ctx)->ft->getEntryAt ((ctx), (index), (name), (rc)));
}
#   else
#      define CMGetContextEntryAt(ctx,p,n,rc) \
           ((ctx)->ft->getEntryAt((ctx),(p),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets the number of entries contained in this Context.
     @param ctx Points to CMPIContext.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return Number of entries.
    @return Entry value.
    @see CMPIContextFT.getEntryCount()
*/
_CMPI_INLINE_MOD CMPICount CMGetContextEntryCount(
    const CMPIContext * ctx,
    CMPIStatus * rc)
{
  return ((ctx)->ft->getEntryCount ((ctx), (rc)));
}
#   else
#      define CMGetContextEntryCount(ctx,rc) \
           ((ctx)->ft->getEntryCount((ctx),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Add or replace a context entry in a CMPIContext object.
     CMAddContextEntry() executes CMPIContextFT.addEntry().
     @param ctx Points to CMPIContext.
     @param name Entry name.
     @param value Address of value structure.
     @param type Value type.
     @return Service return status.
    @see CMPIContextFT.addEntry()
    @todo OpenPegasus used
*/
_CMPI_INLINE_MOD CMPIStatus CMAddContextEntry(
    const CMPIContext * ctx,
    const char *name,
    const CMPIValue * value,
    const CMPIType type)
{
  return ((ctx)->ft->addEntry ((ctx), (name), (value), (type)));
}
#   else
#      define CMAddContextEntry(ctx,n,v,t) \
           ((ctx)->ft->addEntry((ctx),(n),(CMPIValue*)(v),(t)))
#   endif


    // CMPISelectExp macros


#   ifdef CMPI_INLINE
/** @brief Add or replace a context entry in a CMPIContext object.
     CMGetSelExpString() executes CMPISelectExpFT.getString().
     @param se SelectExp this pointer.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return The select expression.
     @see CMPISelectExpFT.getString()
     @todo OpenPegasus tested
*/
_CMPI_INLINE_MOD CMPIString *CMGetSelExpString(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getString ((se), (rc)));
}
#   else
#      define CMGetSelExpString(se,rc) \
           ((se)->ft->getString((se),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Test whether an instance matches the select expression in a
         CMPISelectExp object.
    CMEvaluateSelExp() executes CMPISelectExpFT.evaluate().
    @param se SelectExp this pointer.
    @param inst Instance to be evaluated.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluate()
    @todo OpenPegasus used
      */
_CMPI_INLINE_MOD CMPIBoolean CMEvaluateSelExp(
    const CMPISelectExp * se,
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((se)->ft->evaluate ((se), (inst), (rc)));
}
#   else
#      define CMEvaluateSelExp(se,i,r) \
           ((se)->ft->evaluate((se),(i),(r)))
#   endif

#   ifdef CMPI_VER_87
#   ifdef CMPI_INLINE
/** @brief Test whether the properties returned by an accessor
        function match the select expression in a CMPISelectExp object.
    CMEvaluateSelExpUsingAccessor executes
        CMPISelectExpFT.evaluateUsingAccessor()
    @param se SelectExp this pointer.
    @param accessor Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluateUsingAccessor()
    @todo OpenPegasus used
      */
_CMPI_INLINE_MOD CMPIBoolean CMEvaluateSelExpUsingAccessor(
    const CMPISelectExp * se,
    CMPIAccessor * accessor,
    void *parm,
    CMPIStatus * rc)
{
  return ((se)->ft->evaluateUsingAccessor ((se), (accessor), (parm), (rc)));
}
#   else
#      define CMEvaluateSelExpUsingAccessor(se,i,p,r) \
           ((se)->ft->evaluateUsingAccessor((se),(i),(p),(r)))
#   endif
#   endif /* CMPI_VER_87 */

#   ifdef CMPI_INLINE
/** @brief Get the select expression in a CMPISelectExp object
         as a disjunction of conjunctions.
    CMGetDoc() executes CMPISelectExpFT.getDoc().
     @param se SelectExp this pointer.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return The disjunction.
     @see CMPISelectExpFT.getDoc()
     @todo OpenPegasus used
*/
_CMPI_INLINE_MOD CMPISelectCond *CMGetDoc(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getDOC ((se), (rc)));
}
#   else
#      define CMGetDoc(se,rc) \
           ((se)->ft->getDOC((se),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get the select expression in a CMPISelectExp object as
         a conjunction of disjunctions.
     CMGetCod executes CMPISelectExpFT.getCOD().
     @param se SelectExp this pointer.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return The conjunction.
     @see CMPISelectExpFT.getCOD()
     @see OpenPegasus used
*/
_CMPI_INLINE_MOD CMPISelectCond *CMGetCod(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getCOD ((se), (rc)));
}
#   else
#      define CMGetCod(se,rc) \
           ((se)->ft->getCOD((se),(rc)))
#   endif


    // CMPISelectCond macros


#   ifdef CMPI_INLINE
/** @brief Get the number and type of subconditions in a CMPISelectCond object.
    Optionally, the CMPISelectCond type (COD or DOC) will be returned.
    CMGetSubCondCountAndType
    @param sc SelectCond this pointer.
    @param[out] type CMPISelectCond type (suppressed when NULL).
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of SubCond elements.
    @see CMPISelectCondFT.getCountAndType()
    @todo OpenPegasus tested
      */
_CMPI_INLINE_MOD CMPICount CMGetSubCondCountAndType(
    const CMPISelectCond * sc,
    int * type,
    CMPIStatus * rc)
{
  return ((sc)->ft->getCountAndType ((sc), (type), (rc)));
}
#   else
#      define CMGetSubCondCountAndType(sc,t,rc) \
           ((sc)->ft->getCountAndType((sc),(t),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a subcondition in a CMPISelectCond object by index.
    CMGetSubCondAt() executes CMPISelectCondFT.getSubCondAt().
    @param sc SelectCond this pointer.
    @param index Position in the internal SubCoind array.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The indexed SubCond element.
    @see CMPISelectCondFT.getSubCondAt()
    @todo OpenPegasus tested
      */
_CMPI_INLINE_MOD CMPISubCond *CMGetSubCondAt(
    const CMPISelectCond * sc,
    CMPICount index,
    CMPIStatus * rc)
{
  return ((sc)->ft->getSubCondAt ((sc), (index), (rc)));
}
#   else
#      define CMGetSubCondAt(sc,p,rc) \
           ((sc)->ft->getSubCondAt((sc),(p),(rc)))
#   endif


    // CMPISubCond macros


#   ifdef CMPI_INLINE
/** @brief Get the number of predicates in a CMPISubCond object.
    CMGetPredicateCount() executes CMPISubCondFT.getCount().
    @param sc SubCond this pointer.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Number of Predicate elements.
    @see CMPISubCondFT.getCount()
    @todo OpenPegasus tested
      */
_CMPI_INLINE_MOD CMPICount CMGetPredicateCount(
    const CMPISubCond * sc,
    CMPIStatus * rc)
{
  return ((sc)->ft->getCount ((sc), (rc)));
}
#   else
#      define CMGetPredicateCount(sc,rc) \
           ((sc)->ft->getCount((sc),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a predicate in a CMPISubCond object by index.
    CMGetPredicateAt() executes CMPISubCondFT.getPredicateAt().
    @param sc SubCond this pointer.
    @param index Position in the internal Predicate array.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The indexed Predicate element.
    @see CMPISubCondFT.getPredicateAt()
    @todo OpenPegasus tested
      */
_CMPI_INLINE_MOD CMPIPredicate *CMGetPredicateAt(
    const CMPISubCond * sc,
    CMPICount index,
    CMPIStatus * rc)
{
  return ((sc)->ft->getPredicateAt ((sc), (index), (rc)));
}
#   else
#      define CMGetPredicateAt(sc,p,rc) \
           ((sc)->ft->getPredicateAt((sc),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Get a predicate in a CMPISubCond object by name.
    CMGetPredicate() executes CMPISubCondFT.getPredicate().
    @param sc SubCond this pointer.
    @param name Predicate name (property name).
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The named Predicate element.
    @see CMPISubCondFT.getPredicate()
    @todo OpenPegasus tested
      */
_CMPI_INLINE_MOD CMPIPredicate *CMGetPredicate(
    const CMPISubCond * sc,
    const char *name,
    CMPIStatus * rc)
{
  return ((sc)->ft->getPredicate ((sc), (name), (rc)));
}
#   else
#      define CMGetPredicate(sc,n,rc) \
           ((sc)->ft->getPredicate((sc),(n),(rc)))
#   endif


    // CMPIPredicate macros


#   ifdef CMPI_INLINE
/** @brief Get the predicate components of a CMPIPredicate object.
    CMGetPredicateData() executes CMPIPredicateFT.getData().
    @param pr Predicate this pointer.
    @param[out] type CMPItype Property type.
    @param[out] prop CMPIPredOp operation.
    @param[out] lhs Left hand side of predicate.
    @param[out] rhs Right hand side of predicate.
    @return Service return status.
    @see CMPIPredicateFT.getData()
    @todo OpenPegasus tested
*/
_CMPI_INLINE_MOD CMPIStatus CMGetPredicateData(
    const CMPIPredicate * pr,
    CMPIType * type,
    CMPIPredOp * prop,
    CMPIString ** lhs,
    CMPIString ** rhs)
{
  return ((pr)->ft->getData ((pr), (type), (prop), (lhs), (rhs)));
}
#   else
#      define CMGetPredicateData(pr,t,o,n,v) \
           ((pr)->ft->getData((pr),(t),(o),(n),(v)))
#   endif

#   if defined(CMPI_VER_87) && !defined(CMPI_VER_100)
#   ifdef CMPI_INLINE
/** @brief KS_TODO
    @CMEvaluatePredicateparam pr Predicate this pointer.
    @param type Property type.
    @param value Address of value structure.
    @param type Value type.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Evaluation result.
    @todo KS Possibly no corresponding Function. Where did the function
    go since there is a macro. see
    TestProviders/CMPI/TestUtilLib/cmpiUtilLib.c
      */
_CMPI_INLINE_MOD   int CMEvaluatePredicate(
    CMPIPredicate* pr,
    void* value,
    CMPIType type,
    CMPIStatus* rc)
{
  return ((pr)->ft->evaluate((pr),(CMPIValue*)(value),(type),(rc)));
}
#   else
#      define CMEvaluatePredicate(pr,v,t,rc) \
           ((pr)->ft->evaluate((pr),(CMPIValue*)(v),(t),(rc)))
#   endif
#   endif /* CMPI_VER_87 && !CMPI_VER_100 */

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** @brief Test whether the properties returned by an accessor
         function match the predicate in a CMPIPredicate object.
    CMEvaluatePredicateUsingAccessor() executes
        CMPIPredicateFT.evaluateUsingAccessor().
    @param pr Points to the CMPIPredicate.
    @param accessorFnc Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param [out] rc Function return CMPIStatus (suppressed when NULL).
    @return Evaluation result.
    @see CMPIPredicateFT.evaluateUsingAccessor()
    @note Return type modified from int to CMPIBoolean in CMPI 2.1
      */
_CMPI_INLINE_MOD CMPIBoolean CMEvaluatePredicateUsingAccessor(
    const CMPIPredicate * pr,
    CMPIAccessor * accessorFnc,
    void *parm,
    CMPIStatus * rc)
{
  return ((pr)->ft->evaluateUsingAccessor ((pr), (accessorFnc), (parm), (rc)));
}
#   else
#      define CMEvaluatePredicateUsingAccessor(pr,a,parm,rc) \
          ((pr)->ft->evaluateUsingAccessor((pr),(a),(parm),(rc)))
#   endif
#   endif /* CMPI_VER_100 */


/**
 * @}
 * @addtogroup convenience-func-broker
 * @{
 */

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIInstance object initialized to a given instance
         path.

    CBNewInstance() convenience function executes CMPIBrokerEncFT.newInstance()
    with same arguments
    @param mb Points to CMPIBroker.
    @param instPath CMPIObjectPath containing namespace and classname.
    @param rc Output: Function return status (suppressed when NULL).
    @return Newly created Instance.
    @see CMPIBrokerEncFT.newInstance()
    @par Example
    @code(.c)
    CMPIStatus testProvEnumInstances
      (CMPIInstanceMI * cThis, const CMPIContext * ctx, const CMPIResult * rslt,
       const CMPIObjectPath * ref, const char **properties)
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
 */
_CMPI_INLINE_MOD CMPIInstance * CMNewInstance (
    const CMPIBroker * mb,
    const CMPIObjectPath * instPath,
    CMPIStatus * rc)
{
  return ((mb)->eft->newInstance ((mb), (instPath), (rc)));
}
#   else
#      define CMNewInstance(mb,instPath,rc) \
           ((b)->eft->newInstance((mb),(instPath),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIObjectPath initialized to a given namespace and
         class name

    CMNewObjectPath() convenience function executes
    CMPIBrokerEncFt.newObjectPath() to create a new CMPIObjectPath.

    @see CMPIBrokerEncFT.newObjectPath()
    @par Example
    @code(.c)
      const char* class = "myClass";
      CMPIObjectPath *objPath = NULL;
      CMPIStatus rc = { CMPI_RC_OK, NULL };
      objPath = CMNewObjectPath (broker, ns, class, &rc);
      assert ( rc.rc == CMPI_RC_OK);
      CMAddKey (objPath, "ElementName", (CMPIValue *) class, CMPI_chars);
    @endcode

*/
_CMPI_INLINE_MOD CMPIObjectPath * CMNewObjectPath (
    const CMPIBroker * mb,
    const char *ns,
    const char *cn,
    CMPIStatus * rc)
{
  return ((mb)->eft->newObjectPath ((mb), (ns), (cn), (rc)));
}
#   else
#      define CMNewObjectPath(mb,n,c,rc) \
           ((mb)->eft->newObjectPath((mb),(n),(c),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIString object initialized from a C string.

    CMNewString() convenience function executes CMPIBrokerEncFt.newString()
    to create a new CMPIString object that is initialized from  @p data a
    C-language string.

    @see CMPIBrokerEncFT.newString()
    @par Example
    @code(.c)

        CMPIString1 *cmpiStr;
        CMPIString2 *cmpiStr;
        cmpiStr1 = CMNewString(_broker, NULL, &rc);
        // test rc for OK
        cmpiStr2 = CMNewString(_broker, "Tracing for level 5", &rc);
        // test rc for OK
    @endcode
*/
_CMPI_INLINE_MOD CMPIString * CMNewString (
    const CMPIBroker * mb,
    const char *data,
    CMPIStatus * rc)
{
  return ((mb)->eft->newString ((mb), (data), (rc)));
}
#   else
#      define CMNewString(mb,s,rc) \
           ((mb)->eft->newString((mb),(s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIArgs object initialized to have no method
         parameters.
    CMNewArgs() executes CMPIBrokerEncFT.newArgs() to create a new
    CMPIArgs object.
    @param mb Points to CMPIBroker.
    @param[out] rc Function return status (suppressed when NULL).
    @return Newly created CMPIArgs object or NULL.
    @see CMPIBrokerEncFT.newArgs()
    @par Example
    @code(.c)
        CMPIArgs* args_ptr = NULL;
        CMPIStatus rc = { CMPI_RC_OK, NULL };
        args_ptr = CMNewArgs(_broker, &rc);
    @endcode
*/
_CMPI_INLINE_MOD CMPIArgs * CMNewArgs (const CMPIBroker * mb, CMPIStatus * rc)
{
  return ((mb)->eft->newArgs ((mb), (rc)));
}
#   else
#      define CMNewArgs(mb,rc) \
           ((mb)->eft->newArgs((mb),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Create a new CMPIArray object of a given fixed array size for a
         given type of elements.
    CMNewArray() executes CMPIBrokerEncFT.newArray() to create a new
    CMPIArray object
    @param mb Points to CMPIBroker.
    @param size Maximum number of elements
    @param type Element type
    @param[out] rc Function return status (suppressed when NULL).
    @return Newly created Array or NULL.
    @see CMPIBrokerEncFT.newArray()
    @todo KS confirm what size means
    @todo OpenPegasus OK. tested in cmpiTestMethodProvider.c
*/
_CMPI_INLINE_MOD CMPIArray * CMNewArray (
    const CMPIBroker * mb,
    CMPICount size,
    CMPIType type,
    CMPIStatus * rc)
{
  return ((mb)->eft->newArray ((mb), (max), (type), (rc)));
}
#   else
#      define CMNewArray(mb,c,t,rc) \
           ((mb)->eft->newArray((mb),(c),(t),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIDataTime object with current date and time.

    CBNewDateTime() executes CMPIBrokerEncFT.newDateTime() to create a
    new CMPIDateTime object().
    @param mb Pointer to CMPIBroker
    @param[out] rc Function return status (suppressed when NULL).
    @return The newly created DateTime or NULL.
    @see CMPIBrokerEncFT.newDateTime()
*/
_CMPI_INLINE_MOD CMPIDateTime * CMNewDateTime (
    const CMPIBroker * mb,
    CMPIStatus * rc)
{
  return ((mb)->eft->newDateTime ((mb), (rc)));
}
#   else
#      define CMNewDateTime(mb,rc) \
           ((mb)->eft->newDateTime((mb),(rc)))
#   endif

#   ifdef CMPI_INLINE
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
*/
_CMPI_INLINE_MOD CMPIDateTime *CMNewDateTimeFromBinary(
    const CMPIBroker * mb,
    CMPIUint64 binTime,
    CMPIBoolean interval,
    CMPIStatus * rc)
{
  return ((mb)->eft->
          newDateTimeFromBinary ((mb), (binTime), (interval), (rc)));
}
#   else
#      define CMNewDateTimeFromBinary(mb,d,i,rc) \
                      ((mb)->eft->newDateTimeFromBinary((mb),(d),(i),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPIDateTime object initialized from input.
    @param mb Points to CMPIBroker.
    @param datetime Date/Time definition in UTC format
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The newly created DateTime or NULL.
    @see CMPIBrokerEncFT.newDateTimeFromChars()
*/
_CMPI_INLINE_MOD CMPIDateTime *CMNewDateTimeFromChars(
    const CMPIBroker * mb,
    const char *datetime,
    CMPIStatus * rc)
{
  return ((mb)->eft->newDateTimeFromChars ((mb), (datetime), (rc)));
}
#   else
#      define CMNewDateTimeFromChars(mb,d,rc) \
           ((mb)->eft->newDateTimeFromChars((mb),(d),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Create a new CMPISelectExp object initialized from a select
         expression.

     CMNewSelectExp() executes CMPIBrokerEncFT.newSelectExp() to
     create a new CMPISelectExp
     @param mb Points to CMPIBroker.
     @param query The select expression.
     @param lang The query language.
     @param[out] projection Projection specification (suppressed when NULL).
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return The newly created SelectExp or NULL.
     @see CMPIBrokerEncFT.newSelectExp()
*/
_CMPI_INLINE_MOD CMPISelectExp *CMNewSelectExp(
    const CMPIBroker * mb,
    const char *query,
    const char *lang,
    CMPIArray ** projection,
    CMPIStatus * rc)
{
  return ((mb)->eft->
          newSelectExp ((mb), (query), (lang), (projection), (rc)));
}
#   else
#      define CMNewSelectExp(mb,q,l,p,rc) \
           ((mb)->eft->newSelectExp((mb),(q),(l),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Test whether a class path is of a specified class or any of its
        subclasses.

     CMClassPathIsA() executes CMPIBrokerEncFT.classPathIsA().
     @param mb Points to CMPIBroker.
     @param classPath The class path (namespace and classname
              components).
     @param className Specifies the class name to be tested for.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return
         @li True if test successful.
         @li False otherwise.
     @see CMPIBrokerEncFT.classPathIsA()
     @version. The className argument was named type and documented incorrectly
     prior to version 2.1.  The code did execute correctly
     @todo no test for this in OpenPegasus
     */
_CMPI_INLINE_MOD CMPIBoolean CMClassPathIsA(
    const CMPIBroker * mb,
    const CMPIObjectPath * classPath,
    const char *className,
    CMPIStatus * rc)
{
  return ((mb)->eft->classPathIsA ((mb), (classPath), (className), (rc)));
}
#   else
#      define CMClassPathIsA(mb,cp,cn,rc) \
           ((mb)->eft->classPathIsA((mb),(cp),(cn),(rc)))
#   endif


    // Debugging macros


#   ifdef CMPI_INLINE
/** @brief Convert CMPI encapsulated data type object into a string
         representation.

     CDToString() executes CMPIBrokerEncFT.toString() to  convert
     any CMPI encapsulated data type to a CMPIString with
     implementation-specific content representation.  Intended for
     debugging purposes only.
     @param mb Points to CMPIBroker.
     @param object A valid CMPI encapsulated data type object.
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return String from representation of @p object or NULL.
     @see CMPIBrokerEncFT.toString()
     */
_CMPI_INLINE_MOD CMPIString *CDToString(
    const CMPIBroker * mb,
    const void *object,
    CMPIStatus * rc)
{
  return ((mb)->eft->toString ((mb), (void *) (object), (rc)));
}
#   else
#      define CDToString(mb,o,rc) \
           ((mb)->eft->toString((mb),(void*)(o),(rc)))
#   endif

#    ifdef CMPI_INLINE
/** @brief Tests whether a CMPI encapsulated data type object is of a
         specified CMPI type.
    CDIsOfType() executes CMPIBrokerEncFT.isOfType() to verifies whether
    @p object is of CMPI type @p type.
    Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param type A string specifying a valid CMPI Object type
        ("CMPIInstance", "CMPIObjectPath", etc).
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return True if test successful.
    @see CMPIBrokerEncFT.isOfType()
    @todo OpenPegasus test OK
    @par Example
    @code(.c)
      CMPIStatus rc = { CMPI_RC_OK, NULL };
      CMPIBoolean isOfType = 0;
      CMInstance* inst = CMNewInstance(_broker, . . .);
      isOfType = CDIsOfType (_broker, inst, "CMPIInstance", &rc);
      assert(isOfType);
    @endcode
*/
_CMPI_INLINE_MOD CMPIBoolean CDIsOfType(
    const CMPIBroker * mb,
    const void *object,
    const char *type,
    CMPIStatus * rc)
{
  return ((mb)->eft->isOfType ((mb), (void *) (object), (type), (rc)));
}
#   else
#      define CDIsOfType(mb,o,t,rc) \
           (mb)->eft->isOfType((mb),(void*)(o),(t),(rc))
#   endif

#    ifdef CMPI_INLINE
/** @brief Get the type name of a CMPI ensapsulated data type object.
    CDGetType() executes CMPIBrokerEncFT.getType() to get the CMPI type.
    Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return CMPI object type or NULL.
    @see CMPIBrokerEncFT.getType()
*/
_CMPI_INLINE_MOD CMPIString *CDGetType(
    const CMPIBroker * mb,
    const void *object,
    CMPIStatus * rc)
{
  return ((mb)->eft->getType ((mb), (object), (rc)));
}
#   else
#      define CDGetType(mb,o,rc) \
           ((mb)->eft->getType((mb),(void*)(o),(rc)))
#   endif

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** @brief Log a diagnostic message.

     CMLogMessage() executes CMPIBrokerEncFT.logMessage().
     @param mb Points to CMPIBroker.
     @param severity integer severity code.
     @param id message ID or any other identifying string.
     @param text If not NULL, const char * with the message text to be logged.
     @param string If not NULL, CMPIString with message text to be logged;
       @p string will be ignored when @p text is not NULL.
     @return CMPIStatus containing function return status
     @par Example
     @code(.c)
         CMLogMessage(_broker, 1, "TestProvider",
             "Entering EnumerateInstance", NULL);
     @endcode
    @see CMPIBrokerEncFT.logMessage()
    @todo tested in OpenPegasus cmpiTestMethodProvider.c
*/

_CMPI_INLINE_MOD CMPIStatus CMLogMessage(
    const CMPIBroker * mb,
    int severity,
    const char *id,
    const char *text,
    const CMPIString * string)
{
  return ((mb)->eft->logMessage ((mb), (severity), (id), (text), (string)));
}
#   else
#      define CMLogMessage(mb,severity,id, text, string)  \
          ((b)->eft->logMessage((mb),(severity),(id),(text),(string)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
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
     @par Example
     @code(.c)
        CMPIStatus rc = { CMPI_RC_OK, NULL };
        CMPIString *str = CMNewString (_broker, "CMTraceMessage", &rc);
        rc = CMTraceMessage (_broker, 4, "Authorization", NULL, str);
     @endcode
     @todo tested in OpenPegasus  cmpiTestMethodProvider.c
     @todo OpenPegasus uses CMPILevel as type, not int.
*/
_CMPI_INLINE_MOD CMPIStatus CMTraceMessage(
    const CMPIBroker * mb,
    int level,
    const char *component,
    const char *text,
    const CMPIString * string)
{
  return ((mb)->eft->trace ((mb), (level), (component), (text), (string)));
}
#   else
#      define CMTraceMessage(mb,level,component, text, string)  \
           ((mb)->eft->trace((mb),(level),(component),(text),(string)))
#   endif
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** @brief Create a new CMPIError object initialized with attributes defined
         by the input parameters.

    CMNewCMPIError() executes CMPIBrokerEncFT.newCMPIError() to create a
       new CMPIError object.
    @param mb Points to CMPIBroker.
    @param owner Identifies the entity that owns the msg format definition.
    @param msgID Identifies the format of the message.
    @param msg Formatted and translated message.
    @param sev Perceived severity of this error.
    @param pc Probable caues of this error.
    @param cimStatusCode Status Code.
    @param[out] rc Function return status or NULL
    @return Pointer to a newly allocated CMPIError object or NULL.
    @see CMPIBrokerEncFT.newCMPIError()
    @par Example
    @code(.c)lt
      cmpiError = CMNewCMPIError(_broker, inOwningEntity, inMsgID, inMsg,
           inSev, inPc, inCIMStatusCode, &rc);
    @endcode
    @todo OpenPegasus tested in TestCMPIErrorProvider.c
*/
_CMPI_INLINE_MOD CMPIError* CMNewCMPIError(
    const CMPIBroker* mb,
    const char *owner,
    const char* msgID,
    const char* msg,
    const CMPIErrorSeverity sev,
    const CMPIErrorProbableCause pc,
    const CMPIrc cimStatusCode,
    CMPIStatus* rc)
{
  return ((mb)->eft->newCMPIError ((mb), (owner), (msgID), (msg), (sev),
          (pc), (cimStatusCode), (rc)));
}
#   else
#      define CMNewCMPIError(mb,owner,msgID,msg,sev,pc,cimStatusCode,rc)  \
           ((mb)->eft->newCMPIError((mb),(owner),(msgID),(msg),(sev), \
           (pc),(cimStatusCode),(rc)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** @brief Open a message file and return a handle to the file.
    CMOpenMessageFile() executes CMPIBrokerEncFT.openMessageFile() to
    open a new message file if the MB supports message files.
    @param mb Points to CMPIBroker.
    @param msgFile The message file identifier.
    @param[out] msgFileHandle The handle representing the open msg file or NULL.
    @return Service return status
    @see CMPIBrokerEncFT.openMessageFile()
    @par Example
    @code(.c)
        CMOpenMessageFile(_broker,"/path/msgFile",&msgFileHandle);
    @endcode
    @todo OpenPegasus used.
*/
_CMPI_INLINE_MOD CMPIStatus CMOpenMessageFile(
    const CMPIBroker* mb,
    const char *msgFile,
    CMPIMsgFileHandle *msgFileHandle)
{
  return ((mb)->eft->openMessageFile ((mb), (msgFile), (msgFileHandle)));
}
#   else
#      define CMOpenMessageFile(mb,mf,mfh) \
           ((mb)->eft->openMessageFile((mb),(mf),(mfh)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** @brief Close a message file.
    CMCloseMessageFile() exeuctes CMPIBrokerEncFT.closeMessageFile() to
    close a message file.
    @param mb Points to CMPIBroker.
    @param msgFileHandle CMPIMsgFileHandle handle representing the open
        message file.
    @return Function return status.
    @see CMPIBrokerEncFT.closeMessageFile()
    Example usage:
    @code(.c)
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
    @todo OpenPegasus tested in cmpiTestBrokerEncProvider.c
*/
_CMPI_INLINE_MOD CMPIStatus CMCloseMessageFile(
    const CMPIBroker* mb,
    const CMPIMsgFileHandle msgFileHandle)
{
  return ((mb)->eft->closeMessageFile ((mb), (msgFileHandle)));
}
#   else
#      define CMCloseMessageFile(mb,mfh)  \
           ((mb)->eft->closeMessageFile((mb),(mfh)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** @brief Get a translated message text from an open message file by
         message ID.
    CMGetMessage2() macro executes CMPIBrokerEncFT.getMessage2().
    There is no inline form of this convenience function.

    When using as macro, use CMFmtArgsX and CMFmtX macros (defined
    above) to generate the variable parameter list and ommit
    the count parameter.

    @param mb Points to CMPIBroker.
    @param msgId The message identifier.
    @param msgFileHandle The handle representing the open message file.
    @param defMsg The default message. See the function for details
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @param count The number of message insert values. Omit when using
         the CMFmtArgsXX macro.
    @param ... Up to 10 Message insert values.
        These are specified using the following macros:
           CMFmtSint(v)    integer value
           CMFmtUint(v)    unsigned integer value
           CMFmtSint64(v)  long integer value
           CMFmtUint64(v)  long unsigned integer vale
           CMFmtReal(v)    float or double real value
           CMFmtBoolean(v) CMPIBoolean value
           CMFmtChars(v)   char string
           CMFmtString(v)  CMPIString
    @return the translated message.
    @see CMPIBrokerEncFT.getMessage2()
    Example usage:
    @code(.c)
       CMGetMessage2(_broker,"msgid",msgFileHandle,"Test $0 $1",
       NULL,CMFmtArgs2(CMFmtChars("message"),CMFmtSint(1));
    @endcode
    @todo OpenPegasus tested in cmpiTestBrokerEncProvider.c
    @todo KS Pls review since it asks to do something if macro but it is
    only a macro. No inline version.
    @version Inline code modified; unsigned int last parameter
          to type CMPICount in 2.1
*/
_CMPI_INLINE_MOD CMPIString* CMGetMessage2(
    const CMPIBroker* mb,
    const char *msgId,
    const CMPIMsgFileHandle msgFileHandle,
    const char *defMsg,
    CMPIStatus* rc,
    CMPICount count, ...);
#   else
#      define CMGetMessage2(mb,id,mfh,def,rc,parms)  \
           ((mb)->eft->getMessage2((mb),(id),(mfh),(def),(rc),parms))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */


#   ifdef CMPI_INLINE
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

     @see @ref mb-capabilities CMPIBrokerFT

 */
_CMPI_INLINE_MOD unsigned long CBGetCapabilities (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerCapabilities);
}
#   else
#      define CBGetClassification(mb) \
           ((mb)->bft->brokerCapabilities)
#   endif

#   ifdef CMPI_INLINE
/** @brief Get CMPIBroker version

    CBBrokerVersion gets the CMPIVersion definition from the CMPIBroker
    function table. This can be used to determine which version of the
    CMPI Specification a broker implements.

    @param mb Pointer to CMPIBroker struct
    @return CMPIVersion containing the CMPIBroker version.

    It has no direct corresponding function. It directly access the
    CMPIBrokerFT.brokerVersion variable.

    @see CMPIBrokerFT
    @note not used by  OpenPegasus
     */
_CMPI_INLINE_MOD int CBBrokerVersion (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerVersion);
}
#   else
#      define CBBrokerVersion(mb) \
           ((mb)->bft->brokerVersion)
#   endif

#   ifdef CMPI_INLINE
/** @brief Get CMPIBroker Name

    CBBrokerName() convenience function gets the CMPIBroker name
    from CMPIBroker.brokerVersion

    @param mb Pointer to CMPIBroker struct
    @return C string (const char*) containing the informal name of the
        CMPIBroker.

    It has no direct corresponding function. It directly access the
    CMPIBroker.brokerVersion variable.
     */
_CMPI_INLINE_MOD const char CBBrokerName (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerName);
}
#   else
#      define CBBrokerName(mb) \
           ((bm)->bft->brokerName)
#   endif

#   ifdef CMPI_INLINE
 /** @brief Prepare the MB to accept a new thread that will be using MB
         functions.
     CBPrepareAttachThread() convenience function executes
     CMPIBrokerFT.prepareAttachThread()  to prepare the MB to
     accept a new thread that will be using MB functions. This
     function is expected to be called in the existing thread.
    @param mb Points to CMPIBroker..
     @param ctx Old Context object
     @return New Context object to be used by thread to be attached.

     @see CMPIBrokerFT.prepareAttachThread()
     */
_CMPI_INLINE_MOD CMPIContext *CBPrepareAttachThread(
    const CMPIBroker * mb,
    const CMPIContext * ctx)
{
  return ((mb)->bft->prepareAttachThread ((mb), (ctx)));
}
#   else
#      define CBPrepareAttachThread(mb,c) \
           ((mb)->bft->prepareAttachThread((mb),(c)))
#   endif

#   ifdef CMPI_INLINE
/** This function informs the CMPI run time system that the current
    thread with Context will begin using CMPI services.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.attachThread()
    @todo (KS)clean up doc
     */
_CMPI_INLINE_MOD CMPIStatus CBAttachThread(
    const CMPIBroker * mb,
    const CMPIContext * ctx)
{
  return ((mb)->bft->attachThread ((mb), (ctx)));
}
#   else
#      define CBAttachThread(mb,c) \
           ((mb)->bft->attachThread((mb),(c)))
#   endif

#   ifdef CMPI_INLINE
/** This function informs the CMPI run time system that the current thread
    will not be using CMPI services anymore. The Context object will be
    freed during this operation.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.detachThread()
    @todo (KS)clean up doc
     */
_CMPI_INLINE_MOD CMPIStatus CBDetachThread(
    const CMPIBroker * mb,
    const CMPIContext * ctx)
{
  return ((mb)->bft->detachThread ((mb), (ctx)));
}
#   else
#      define CBDetachThread(mb,c) \
           ((mb)->bft->detachThread((mb),(c)))
#   endif


#   ifdef CMPI_INLINE
/** This function requests delivery of an Indication. The CIMOM will
    locate pertinent subscribers and notify them about the event.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param ns Namespace
    @param ind Indication Instance
    @return Service return status.
    @see CMPIBrokerFT.deliverIndication()
    @todo (KS)clean up doc
     */
_CMPI_INLINE_MOD CMPIStatus CBDeliverIndication(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const char *ns,
    const CMPIInstance * ind)
{
  return ((mb)->bft->deliverIndication ((mb), (ctx), (ns), (ind)));
}
#   else
#      define CBDeliverIndication(mb,c,n,i) \
           ((mb)->bft->deliverIndication((mb),(c),(n),(i)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerate Instance Names of the class (and subclasses)
    defined by @p op.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param op ObjectPath containing namespace and classname components.
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return Enumeration of ObjectPaths.
    @see CMPIBrokerFT.enumerateInstanceNames()
    @todo (KS)clean up doc
     */
_CMPI_INLINE_MOD CMPIEnumeration *CBEnumInstanceNames(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((mb)->bft->enumerateInstanceNames ((mb), (ctx), (op), (rc)));
}
#   else
#      define CBEnumInstanceNames(mb,c,p,rc) \
           ((mb)->bft->enumerateInstanceNames((mb),(c),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
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
     @param[out] rc Function return CMPIStatus (suppressed when NULL).
     @return CMPIEnumeration of Instances.
     @see CMPIBrokerFT.enumerateInstances()

    @todo (KS)clean up doc
    @todo not used in Pegasus. i.e. no test
*/
_CMPI_INLINE_MOD CMPIEnumeration *CBEnumInstances(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * classPath,
    const char **properties,
    CMPIStatus * rc)
{
  return ((mb)->bft->enumerateInstances ((mb), (ctx), (classPath),
                                         (properties),(rc)));
}
#   else
#      define CBEnumInstances(mb,ctx,classPath,properties,rc) \
           (mb)->bft->enumerateInstances((mb),(ctx),(classPath),(properties), \
           (rc)))
#   endif

#   ifdef CMPI_INLINE
/** Get Instance using @p op as reference. Instance structure can be
    controled using the CMPIInvocationFlags entry in @p ctx.
    @param mb Points to CMPIBroker.
    @param ctx Context object
    @param op ObjectPath containing namespace, classname and key components.
    @param properties If not NULL, the members of the array
     define one or more Property names. Each returned
     Object MUST NOT include elements for any Properties
     missing from this list
    @param[out] rc Function return CMPIStatus (suppressed when NULL).
    @return The Instance.
    @see CMPIBrokerFT.getInstance()
    @todo (KS)clean up doc
*/
_CMPI_INLINE_MOD CMPIInstance *CBGetInstance(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char **properties,
    CMPIStatus * rc)
{
  return ((mb)->bft->getInstance ((mb), (ctx), (op), (properties), (rc)));
}
#   else
#      define CBGetInstance(mb,c,p,pr,rc) \
           ((mb)->bft->getInstance((mb),(c),(p),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
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
     */
_CMPI_INLINE_MOD CMPIObjectPath *CBCreateInstance(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((mb)->bft->createInstance ((mb), (ctx), (op), (inst), (rc)));
}
#   else
#      define CBCreateInstance(mb,c,p,i,rc) \
           ((mb)->bft->createInstance((mb),(c),(p),(i),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Modify property values of an existing instance.

    CBModifyInstance convenience function executes CMPIBrokerFT.modifyInstance()
    to modify the property values of an existing instance.

     @see CMPIBrokerFT.modifyInstance()
*/
#      ifdef CMPI_VER_100
_CMPI_INLINE_MOD CMPIStatus CBModifyInstance(
    const CMPIBroker* mb,
    const CMPIContext* ctx,
    const CMPIObjectPath* op,
    const CMPIInstance* inst,
    const char** properties)
{
  return ((mb)->bft->
          modifyInstance ((mb), (ctx), (op), (inst), (properties)));
}
#      else
_CMPI_INLINE_MOD CMPIStatus CBSetInstance(
    const CMPIBroker* mb,
    const CMPIContext* ctx,
    const CMPIObjectPath* op,
    const CMPIInstance* inst,
    const char** properties)
{
  return ((mb)->bft->
          setInstance ((mb), (ctx), (op), (inst), (properties)));
}
#      endif /* CMPI_VER_100 */
#   else
#      ifdef CMPI_VER_100
#         define CBModifyInstance(mb,c,p,i,pr) \
              ((mb)->bft->modifyInstance((mb),(c),(p),(i),(pr)))
#      else
#         define CBSetInstance(mb,c,p,i,pr) \
              ((mb)->bft->setInstance((mb),(c),(p),(i),(pr)))
#      endif /* CMPI_VER_100 */
#   endif

#   ifdef CMPI_INLINE
/** Delete an existing Instance using @p op as reference.

     @see CMPIBrokerFT.deleteInstance()
     */
_CMPI_INLINE_MOD CMPIStatus CBDeleteInstance(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op)
{
  return ((mb)->bft->deleteInstance ((mb), (ctx), (op)));
}
#   else
#      define CBDeleteInstance(mb,c,p) \
           ((mb)->bft->deleteInstance((mb),(c),(p)))
#   endif

#   ifdef CMPI_INLINE
/** Query the enumeration of instances of the class (and subclasses) defined
    by @p op using @p query expression.

    @see CMPIBrokerFT.execQuery()
*/
_CMPI_INLINE_MOD CMPIEnumeration *CBExecQuery(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *query,
    const char *lang,
   CMPIStatus * rc)
{
  return ((mb)->bft->execQuery ((mb), (ctx), (op), (query), (lang), (rc)));
}
#   else
#      define CBExecQuery(mb,c,p,l,q,rc) \
           ((mb)->bft->execQuery((mb),(c),(p),(l),(q),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** Enumerate instances associated with the Instance defined by the @p op.

    @see CMPIBrokerFT.associators()
     */
_CMPI_INLINE_MOD CMPIEnumeration *CBAssociators(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    const char **properties,
   CMPIStatus * rc)
{
  return ((mb)->bft->
          associators ((mb), (ctx), (op), (assocClass), (resultClass), (role),
                       (resultRole), (properties), (rc)));
}
#   else
#      define CBAssociators(mb,c,p,acl,rcl,r,rr,pr,rc) \
           ((mb)->bft->associators((mb),(c),(p),(acl),(rcl),(r),(rr),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerate ObjectPaths associated with the Instance defined by @p op.

    @see CMPIBrokerFT.associatorNames()
     */
_CMPI_INLINE_MOD CMPIEnumeration *CBAssociatorNames(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *assocClass,
    const char *resultClass,
    const char *role,
    const char *resultRole,
    CMPIStatus * rc)
{
  return ((mb)->bft->associatorNames ((mb), (ctx), (op),
                                      (assocClass), (resultClass), (role),
                                      (resultRole), (rc)));
}
#   else
#      define CBAssociatorNames(mb,c,p,acl,rcl,r,rr,rc) \
           ((mb)->bft->associatorNames((mb),(c),(p),(acl),(rcl),(r),(rr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** @brief Enumerate the association instances referencing a given source
         instance.

    CBReferenceNames convenience function executes CMPIBrokerFT.references()
    enumerating the association instances referencing a given source instance.

    @see CMPIBrokerFT.references()
     */
_CMPI_INLINE_MOD CMPIEnumeration *CBReferences(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *resultClass,
    const char *role,
    const char **properties,
    CMPIStatus * rc)
{
  return ((mb)->bft->references ((mb), (ctx), (op),
                                 (resultClass), (role), (properties), (rc)));
}
#   else
#      define CBReferences(mb,c,p,acl,r,pr,rc) \
           ((mb)->bft->references((mb),(c),(p),(acl),(r),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerates the association ObjectPaths referencing a given
    instance.

    CBReferenceNames convenience function executes the function
     CMPIBrokerFT.referenceNames() to enumerate the instance
     paths of the association instances referencing a given
     source instance @p op.

    @see CMPIBrokerFT.referenceNames()
    */
_CMPI_INLINE_MOD CMPIEnumeration *CBReferenceNames(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *resultClass,
    const char *role,
    CMPIStatus * rc)
{
  return ((mb)->bft->
          referenceNames ((mb), (ctx), (op), (resultClass), (role), (rc)));
}
#   else
#      define CBReferenceNames(mb,c,p,acl,r,rc) \
           ((mb)->bft->referenceNames((mb),(c),(p),(acl),(r),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** @brief Invoke a method on a given instance

    CBInvokeMethod executes CMPIFT.invokeMethod() to execute named, extrinsic
    method on a target object. Instance methods (i.e., non-static methods) can\
    be invoked only on instances. Class methods (i.e., static methods) can be
    invoked on instances and classes.

    Parameters are exactly as defined in CMPIBrokerFT.invokeMethod().
    @see CMPIBrokerFT.invokeMethod()
    @par Example
    Example executes CBInvokeMethod "TestCMPIError" on
    CMPIObjectPath and tests response for success and correct
    return data type.
    @code(.c)
        const CMPIArgs * in;
        CMPIArgs * out
        CMPIObjectPath* objPath;
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
*/
_CMPI_INLINE_MOD CMPIData CBInvokeMethod(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *method,
    const CMPIArgs * in,
    CMPIArgs * out,
    CMPIStatus * rc)
{
  return ((mb)->bft->
          invokeMethod ((mb), (ctx), (op), (method), (in), (out), (rc)));
}
#   else
#      define CBInvokeMethod(mb,c,p,m,ai,ao,rc) \
           ((mb)->bft->invokeMethod((mb),(c),(p),(m),(ai),(ao),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Set the named property value of an existing Instance. (**Deprecated**)

    CBSetProperty() executes the CMPIBrokderFt.setProperty()
    function to set a CMPIValue @ value into property of an
    existing instance.

    @see CMPIBrokerFT.setProperty()
    @deprecated because the function setProperty has been
                deprecated
    @note No example because this function is deprecated
      */
_CMPI_INLINE_MOD CMPIStatus CBSetProperty(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *name,
    const CMPIValue * value,
    const CMPIType type)
{
  return ((mb)->bft->setProperty ((mb), (ctx), (op), (name),
                                  (CMPIValue *) (value), (type)));
}
#   else
#      define CBSetProperty(mb,c,p,n,v,t) \
           ((mb)->bft->setProperty((mb),(c),(p),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Get the named property value of an Instance (**Deprecated**)

    CBGetProperty() convenience function executes CMPIBrokerFt.getProperty() to
    get the property named by @p name defined by @p op.
    @see CMPIBrokerFT.getProperty()
    @deprecated Because corresponding CMPIBrokerFT.getProperty() is deprecated.
    @note No example because deprecated.
      */
_CMPI_INLINE_MOD CMPIData CBGetProperty(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char *name,
    CMPIStatus * rc)
{
  return (mb)->bft->getProperty ((mb), (ctx), (op), (name), (rc));
}
#   else
#      define CBGetProperty(mb,c,p,n,rc) \
           (mb)->bft->getProperty((mb),(c),(p),(n),(rc))
#   endif

/*
    -----------------  C provider factories ---------------------
*/
/**
 * @}
 * @addtogroup convenience-func-mi-factory-stubs
 * @{
 */
#   ifndef DOC_ONLY
   // MI factory stubs

   // Used when the MI factory function is not going to call
   // a function during initialization.
#      define CMNoHook
#   endif


#   ifdef DOC_ONLY
/** The CMInstanceMIStub macro generates the function table and initialization
     stub for an instance provider. The initialization routine
     &lt;pnCreate_InstanceMI is called when this provider module is loaded by
     the broker. This macro is for CMPI providers written in plain C.
     @param pfx The prefix for all mandatory enumeration provider functions.
            This is a character string without quotes.
            Mandatory functions are:
            &lt;pfx&gt;Cleanup,&lt;pfx&gt;EnumInstanceNames,
            &lt;pfx&gt;EnumInstances, &lt;pfx&gt;GetInstance,
            &lt;pfx&gt;CreateInstance, &lt;pfx&gt;SetInstance,
            &lt;pfx&gt;DeleteInstance &lt;pfx&gt;ExecQuery.
            &lt;pfx&gt;DeleteInstance and
            &lt;pfx&gt;enumerateInstancesFiltered.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @param broker The name of the broker variable used by this macro to store
                   the CMPIBroker pointer
     @param hook A statement that is executed within
                 &lt;pn&gt;Create_InstanceMI routine. This
                 enables you to perform additional
                 initialization functions and is normally a
                 function call like furtherInit(broker) or
                 CMNoHook. Use CMNoHook if no further
                 intialization is required.
     @return The function table of this instance provider.
     @todo what about optional functions.  ex. ExecQuery
     @todo we have first cut at example.  Is this the way to go
           or would we be better with complete provider in an
           examples section?
     @par Example
     This example documents the general structure of an instance
     provider using the CMInstanceMIStub macro. Note that only a
     couple of required functions are actually defined.
     @code(.c)
         static const CMPIBroker *_broker;
         static void initialize()
        {
        ...
        }
        // Developer implements the following functions
        CMPIStatus InstProvCleanup (
            CMPIInstanceMI * mi,
            const CMPIContext * ctx,
            CMPIBoolean  term)
        {
            CMRelease(clone_arr_ptr);
            CMReturn (CMPI_RC_OK);
        }
        CMPIStatus InstProvEnumInstanceNames (
            CMPIInstanceMI * mi,
            const CMPIContext * ctx,
            const CMPIResult * rslt,
        // OtherRequired  but not shown Functions for
        //    InstProvEnumInstances InstProvGetInstance
        //    InstProvCreateInstance
        //    InstProvModifyInstance
        //    InstProvDeleteInstance
        // Optional Functions.
        //    InstProvExecQuery InstProvEnumerateInstancesFiltered

        CMInstanceMIStub(
            InstProv,
            CMPIInstanceProvider,
            _broker,
            initialize())
     @endcode
     @see CMPIInstanceMIFT, CMPIInstanceMIFT.cleanup(),
          CMPIInstanceMIFT.enumerateInstanceNames(),
          CMPIInstanceMIFT.enumerateInstances(),
          CMPIInstanceMIFT.getInstance(),
          CMPIInstanceMIFT.createInstance(),
          MPIInstanceMIFT.deleteInstance(),
          CMPIInstanceMIFT.execQuery(),
          CMPIInstanceMIFT.enumerateInstancesFiltered()
     @todo confirm that this @see works
     @todo Despite the documentation, this apparently requires
           implementations of all of the corresponding
           functions. How to we handle the two that may well be
           optional. (ExecQuery, EnumerateInstancesFiltered)
 */
CMPIInstanceMI *CMInstanceMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else

#      ifdef CMPI_VER_100
#         define CMInstanceMIStubChange(pfx) pfx##ModifyInstance
#      else
#         define CMInstanceMIStubChange(pfx) pfx##SetInstance
#      endif /* CMPI_VER_100 */

#      define CMInstanceMIStub(pfx,pn,broker,hook) \
  static CMPIInstanceMIFT instMIFT__={ \
   CMPICurrentVersion, \
   CMPICurrentVersion, \
   "instance" #pn, \
   pfx##Cleanup, \
   pfx##EnumInstanceNames, \
   pfx##EnumInstances, \
   pfx##GetInstance, \
   pfx##CreateInstance, \
   CMInstanceMIStubChange(pfx), \
   pfx##DeleteInstance, \
   pfx##ExecQuery, \
#        ifdef CMPI_VER_210
             pfx##EnumInstancesFiltered, \
#        endif
  }; \
  CMPI_EXTERN_C \
  CMPIInstanceMI* pn##_Create_InstanceMI( \
      const CMPIBroker* brkr, \
      const CMPIContext *ctx, \
      CMPIStatus *rc) { \
   static CMPIInstanceMI mi={ \
      NULL, \
      &instMIFT__, \
   }; \
   broker=brkr; \
   hook; \
   return &mi;  \
  }

#    endif

#   ifdef DOC_ONLY
/** @brief generate function table and stub for association provider.
   CMAssociationMIStub() macro generates the function table and initialization
   stub for an association provider. The initialization routine
   &lt;pn&gt;Create_AssociationMI is called when this provider module is
   loaded by the broker.

   This macro is for CMPI providers written in plain C.
     @param pfx The prefix for all mandatory instance provider functions.
        This is a character string without quotes.
        Mandatory functions are: &lt;pfx&gt;AssociationCleanup,
        &lt;pfx&gt;Associators,
        &lt;pfx&gt;AssociatorNames,&lt;pfx&gt;References and
        &lt;pfx&gt;ReferenceNames.
     @param pn The provider name under which this provider is registered.
        This is a character string without quotes.
     @param broker The name of the broker variable used by this macro to store
               the CMPIBroker pointer
     @param hook A statement that is executed
         within &lt;pn&gt;Create_AssociationMI routine. This
         enables you to perform additional initialization
         functions and is normally a function call like
         furtherInit(broker) or CMNoHook. Use CMNoHook if no
         further intialization is required.
     @return The function table of this association provider.
     @todo create example
     @todo what about optional functions
     @todo need note about creating function that parallel
           others but with cap
     @todo Need reference back to cmpift
     @todo expand for cmpi 2.1
*/
CMPIAssociationMI *CMAssociationMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else
#      define CMAssociationMIStub(pfx,pn,broker,hook) \
   static CMPIAssociationMIFT assocMIFT__={ \
   CMPICurrentVersion, \
   CMPICurrentVersion, \
   "association" #pn, \
   pfx##AssociationCleanup, \
   pfx##Associators, \
   pfx##AssociatorNames, \
   pfx##References, \
   pfx##ReferenceNames, \
#        ifdef CMPI_VER_210
             pfx##AssociatorsFiltered, \
             pfx##ReferencesFiltered, \
#        endif
  }; \
  CMPI_EXTERN_C \
  CMPIAssociationMI* pn##_Create_AssociationMI( \
      const CMPIBroker* brkr, \
      const CMPIContext *ctx, \
      CMPIStatus *rc) { \
      static CMPIAssociationMI mi={ \
          NULL, \
          &assocMIFT__, \
          }; \
      broker=brkr; \
      hook; \
      return &mi;  \
      }
#   endif

#   ifdef DOC_ONLY
/** @brief Generate the function table and initialization stub for a method
     provider.

    This macro generates the function table and initialization stub
       for a method provider. The initialization routine
       &lt;pn&gt;Create_MethodMI is called when this provider
       module is loaded by the broker. This macro is for CMPI
       providers written in plain C.
     @param pfx The prefix for all mandatory method provider functions.
            This is a character string without quotes.
            Mandatory functions are: &lt;pfx&gt;MthodCleanup and
            &lt;pfx&gt;InvokeMethod.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @param broker The name of the broker variable used by this macro to store
                   the CMPIBroker pointer
     @param hook A statement that is executed
            within &lt;pn&gt;Create_MethodMI routine. This
            enables you to perform additional initialization
            functions and is normally a function call like
            furtherInit(broker) or CMNoHook. Use CMNoHook
            if no further intialization is required.
     @return The function table of this method provider.
     @todo Need  see reference back to cmpift. Do example
      */
CMPIMethodMI *CMMethodMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else
#      define CMMethodMIStub(pfx,pn,broker,hook) \
  static CMPIMethodMIFT methMIFT__={ \
   CMPICurrentVersion, \
   CMPICurrentVersion, \
   "method" #pn, \
   pfx##MethodCleanup, \
   pfx##InvokeMethod, \
  }; \
  CMPI_EXTERN_C \
  CMPIMethodMI* pn##_Create_MethodMI( \
      const CMPIBroker* brkr, \
      const CMPIContext *ctx, \
      CMPIStatus *rc) { \
   static CMPIMethodMI mi={ \
      NULL, \
      &methMIFT__, \
   }; \
   broker=brkr; \
   hook; \
   return &mi; \
  }
#   endif

#   ifdef DOC_ONLY
/** Generates the function table and initialization stub
    for a property provider (**Deprecated**).
    This macro generates the function table and initialization stub
    for a property provider. The initialization
       routine &lt;pn&gt;Create_PropertyMI is called when
       this provider module is loaded by the broker. This
       macro is for CMPI providers written in plain C.
     @param pfx The prefix for all mandatory property provider functions.
            This is a character string without quotes.
            Mandatory functions are:
            &lt;pfx&gt;PropertyCleanup,
            &lt;pfx&gt;SetProperty and
            &lt;pfx&gt;GetProperty.

     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @param broker The name of the broker variable used by
                   this macro to store the CMPIBroker
                   pointer
     @param hook A statement that is executed within
                 &lt;pn&gt;Create_PropertyMI routine. This
                 enables you to perform additional
                 initialization functions and is normally a
                 function call like furtherInit(broker) or
                 CMNoHook. Use CMNoHook if no further
                 intialization is required.
     @return The function table of this property provider.
     @deprecated in CMPI 2.1 because property providers have been deprecated
     in the WBEM specifications.

     @todo Need reference back to cmpift. No example because
           deprecated.
      */
CMPIPropertyMI *CMPropertyMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else
#      define CMPropertyMIStub(pfx,pn,broker,hook) \
  static CMPIPropertyMIFT propMIFT__={ \
   CMPICurrentVersion, \
   CMPICurrentVersion, \
   "property" #pn, \
   pfx##PropertyCleanup, \
   pfx##SetProperty, \
   pfx##GetProperty, \
  }; \
  CMPI_EXTERN_C \
  CMPIPropertyMI* pn##_Create_PropertyMI( \
      const CMPIBroker* brkr, \
      const CMPIContext *ctx, \
      CMPIStatus *rc) { \
   static CMPIPropertyMI mi={ \
      NULL, \
      &propMIFT__, \
   }; \
   broker=brkr; \
   hook; \
   return &mi; \
  }
#   endif

#   ifdef DOC_ONLY
/** @brief generate the function table and initialization stub
   for an indication provider.

   This macro generates the function table and initialization
   stub for an indication provider. The initialization
       routine &lt;pn&gt;Create_IndicationMI is called when
       this provider module is loaded by the broker. This
       macro is for CMPI providers written in plain C.
     @param pfx The prefix for all mandatory indication provider functions.
            This is a character string without quotes.
            Mandatory functions are:
            &lt;pfx&gt;IndicationCleanup,
            &lt;pfx&gt;AuthorizeFilter, &lt;pfx&gt;MustPoll,
            &lt;pfx&gt;ActivateFilter and
            &lt;pfx&gt;DeActivateFilter.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @param broker The name of the broker variable used by
            this macro to store the CMPIBroker pointer
     @param hook A statement that is executed within
            &lt;pn&gt;Create_IndicationMI routine. This enables
            you to perform additional initialization functions
            and is normally a function call like
            furtherInit(broker) or CMNoHook. Use CMNoHook if
            no further intialization is required.
     @return The function table of this indication provider.

     @todo Need reference back to cmpift and example
      */
CMPIIndicationMI *CMIndicationMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else

#      ifdef CMPI_VER_86
#         define CMIndicationMIStubExtensions(pfx) \
            pfx##EnableIndications, \
            pfx##DisableIndications,
#      else
#         define CMIndicationMIStubExtensions(pfx)
#      endif /* CMPI_VER_86 */

#      define CMIndicationMIStub(pfx,pn,broker,hook) \
  static CMPIIndicationMIFT indMIFT__={ \
   CMPICurrentVersion, \
   CMPICurrentVersion, \
   "Indication" #pn, \
   pfx##IndicationCleanup, \
   pfx##AuthorizeFilter, \
   pfx##MustPoll, \
   pfx##ActivateFilter, \
   pfx##DeActivateFilter, \
   CMIndicationMIStubExtensions(pfx) \
 }; \
  CMPI_EXTERN_C \
  CMPIIndicationMI* pn##_Create_IndicationMI( \
      const CMPIBroker* brkr, \
      const CMPIContext *ctx, \
      CMPIStatus *rc) { \
   static CMPIIndicationMI mi={ \
      NULL, \
      &indMIFT__, \
   }; \
   broker=brkr; \
   hook; \
   return &mi; \
 }
#   endif

/*
    -----------------  C++ provider factories ---------------------
*/

#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
    for an instance provider. The initialization
    routine &lt;pn&gt;Create_IndicationMI is called when
    this provider module is loaded by the broker. This
    macro is for CMPI providers written in C++ using the
    Cmpi* classes.
     @param cn The C++ class name of this instance provider
            (a subclass of CmpiInstanceMI).
            This is a character string without quotes.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @return The function table of this instance provider.

     @todo Need reference back to cmpift
      */
CMPIInstanceMI *CMInstanceMIFactory (chars cn, chars pn);
#   else
#      define CMInstanceMIFactory(cn,pn) \
 CMPI_EXTERN_C \
  CMPIInstanceMI* pn##_Create_InstanceMI( \
      const CMPIBroker* broker, \
      const CMPIContext *ctxp, \
      CMPIStatus *rc) { \
   static CMPIInstanceMIFT instMIFT={ \
    CMPICurrentVersion, \
    CMPICurrentVersion, \
    "instance" #pn, \
       (CMPIStatus(*)( \
            CMPIInstanceMI*, \
            const CMPIContext*, \
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
   CmpiContext ctx((CMPIContext*)ctxp); \
   mi.ft=&instMIFT; \
   CmpiBaseMI *provider=base##pn.getBaseMI(); \
   if (provider == 0) {\
     provider = new cn(CmpiBroker((CMPIBroker*)broker),ctx); \
     provider->setProviderBase(&base##pn); \
       provider->initialize(ctx); \
     base##pn.setBaseMI(provider); \
    } \
   mi.hdl=provider; \
   base##pn.incUseCount(); \
    return &mi; \
 }
#   endif

//// ks - The above implemented differently.  Not sure yet why the
//// difference but there is try block in place of provider->initialize(ctx)
#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
    for an association provider. The initialization routine
    &lt;pn&gt;Create_AssociationMI
    is called when this provider module is loaded by the broker.
    This macro is for CMPI providers written in C++ using
    the Cmpi* classes.
     @param cn The C++ class name of this instance provider
            (a subclass of CmpiInstanceMI).
            This is a character string without quotes.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @return The function table of this instance provider.

     @todo Need reference back to cmpift
      */
CMPIAssociationMI *CMAssociationMIFactory (chars cn, chars pn);
#   else
#      define CMAssociationMIFactory(cn,pn) \
 CMPI_EXTERN_C \
  CMPIAssociationMI* pn##_Create_AssociationMI( \
      const CMPIBroker* broker, \
      const CMPIContext *ctxp, \
      CMPIStatus *rc) { \
   static CMPIAssociationMIFT assocMIFT={ \
    CMPICurrentVersion, \
    CMPICurrentVersion, \
    "association" #pn, \
    (CMPIStatus(*)( \
         CMPIAssociationMI*, \
         const CMPIContext*, \
         CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
    CmpiAssociationMI::driveAssociators, \
    CmpiAssociationMI::driveAssociatorNames, \
    CmpiAssociationMI::driveReferences, \
    CmpiAssociationMI::driveReferenceNames, \
  }; \
   static CMPIAssociationMI mi; \
   CmpiContext ctx((CMPIContext*)ctxp); \
   mi.ft=&assocMIFT; \
   CmpiBaseMI *provider=base##pn.getBaseMI(); \
   if (provider == 0) {\
     provider = new cn(CmpiBroker((CMPIBroker*)broker),ctx); \
     provider->setProviderBase(&base##pn); \
       provider->initialize(ctx); \
     base##pn.setBaseMI(provider); \
    } \
   mi.hdl=provider; \
   base##pn.incUseCount(); \
    return &mi; \
 }
#   endif
//// KS Above implemented differently in OpenPegasus. Try block in place
//// of provider->initialize(ctx)
#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
    for an method provider. The initialization routine
    &lt;pn&gt;Create_MethodMI is called when this
    provider module is loaded by the broker.
    This macro is for CMPI providers written in C++ using
    the Cmpi* classes.
     @param cn The C++ class name of this method provider
            (a subclass of CmpiMethodMI).
            This is a character string without quotes.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @return The function table of this association provider.

     @todo Need reference back to cmpift
     @todo KS Add macro for filtered operations.
      */
CMPIMethodMI *CMMethodMIFactory (chars cn, chars pn);
#   else
#      define CMMethodMIFactory(cn,pn) \
 CMPI_EXTERN_C \
 CMPIMethodMI* pn##_Create_MethodMI( \
     const CMPIBroker* broker, \
     const CMPIContext *ctxp, \
     CMPIStatus *rc) { \
   static CMPIMethodMIFT methMIFT={ \
    CMPICurrentVersion, \
    CMPICurrentVersion, \
    "method" #pn, \
    (CMPIStatus(*)( \
         CMPIMethodMI*, \
         const CMPIContext*, \
         CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
    CmpiMethodMI::driveInvokeMethod, \
   }; \
   static CMPIMethodMI mi; \
   CmpiContext ctx((CMPIContext*)ctxp); \
   mi.ft=&methMIFT; \
   CmpiBaseMI *provider=base##pn.getBaseMI(); \
   if (provider == 0) {\
     provider = new cn(CmpiBroker((CMPIBroker*)broker),ctx); \
     provider->setProviderBase(&base##pn); \
       provider->initialize(ctx); \
     base##pn.setBaseMI(provider); \
    } \
   mi.hdl=provider; \
   base##pn.incUseCount(); \
    return &mi; \
 }
#   endif
//// KS see comments above about provider->initialize(ctx)
#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
    for a property provider. The initialization routine
    &lt;pn&gt;Create_PropertyMI is called when this
    provider module is loaded by the broker. This macro
    is for CMPI providers written in C++ using the Cmpi*
    classes.
     @param cn The C++ class name of this method provider
            (a subclass of CmpiMethodMI).
            This is a character string without quotes.
     @param pn The provider name under which this provider is registered.
            This is a character string without quotes.
     @return The function table of this association provider.
     @todo Need reference back to cmpift
     @todo document as deprecated
     @deprecated The CMPIPropertyMIFT has been deprecated in
                 CMPI 2.1.
      */
CMPIPropertyMI *CMPropertyMIFactory(chars cn, chars pn);
#   else
#      define CMPropertyMIFactory(cn,pn) \
 CMPI_EXTERN_C \
  CMPIPropertyMI* pn##_Create_PropertyMI( \
      const CMPIBroker* broker, \
      const CMPIContext *ctxp, \
      CMPIStatus *rc) { \
   static CMPIPropertyMIFT propMIFT={ \
    CMPICurrentVersion, \
    CMPICurrentVersion, \
    "property" #pn, \
       (CMPIStatus(*)( \
            CMPIPropertyMI*, \
            const CMPIContext*, \
            CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
    CmpiPropertyMI::driveSetProperty, \
    CmpiPropertyMI::driveGetProperty, \
   }; \
   static CMPIPropertyMI mi; \
   CmpiContext ctx((CMPIContext*)ctxp); \
   mi.ft=&propMIFT; \
   CmpiBaseMI *provider=base##pn.getBaseMI(); \
   if (provider == 0) {\
     provider = new cn(CmpiBroker((CMPIBroker*)broker),ctx); \
     provider->setProviderBase(&base##pn); \
       provider->initialize(ctx); \
     base##pn.setBaseMI(provider); \
    } \
   mi.hdl=provider; \
   base##pn.incUseCount(); \
   return &mi; \
 }
#   endif
//// KS same comment about provider->initialize(ctx)

#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
    for an indication provider. The initialization routine
    &lt;pn&gt;Create_IndicationMI is called when this
    provider module is loaded by the broker. This macro
    is for CMPI providers written in C++ using the Cmpi*
    classes.
    @param cn The C++ class name of this indication provider
        (a subclass of CmpiIndicationMI).
        This is a character string without quotes.
    @param pn The provider name under which this provider is registered.
        This is a character string without quotes.
    @return The function table of this association provider.
      */
CMPIIndicationMI *CMIndicationMIFactory (chars cn, chars pn);
#   else

#      ifdef CMPI_VER_86
#          define CMIndicationMIFactoryExtensions \
               CmpiIndicationMI::driveEnableIndications, \
                CmpiIndicationMI::driveDisableIndications,
#      else
#         define CMIndicationMIFactoryExtensions
#      endif /* CMPI_VER_86 */

#      define CMIndicationMIFactory(cn,pn) \
 CMPI_EXTERN_C \
  CMPIIndicationMI* pn##_Create_IndicationMI( \
      const CMPIBroker* broker, \
      const CMPIContext *ctxp, \
      CMPIStatus *rc) { \
   static CMPIIndicationMIFT indMIFT={ \
    CMPICurrentVersion, \
    CMPICurrentVersion, \
    "indication" #pn, \
      (CMPIStatus(*)( \
           CMPIIndicationMI*, \
           const CMPIContext*, \
           CMPIBoolean))CmpiBaseMI::driveBaseCleanup, \
    CmpiIndicationMI::driveAuthorizeFilter, \
    CmpiIndicationMI::driveMustPoll, \
    CmpiIndicationMI::driveActivateFilter, \
    CmpiIndicationMI::driveDeActivateFilter, \
    CMIndicationMIFactoryExtensions \
   }; \
   static CMPIIndicationMI mi; \
   CmpiContext ctx((CMPIContext*)ctxp); \
   mi.ft=&indMIFT; \
   CmpiBaseMI *provider=base##pn.getBaseMI(); \
   if (provider == 0) {\
     provider = new cn(CmpiBroker((CMPIBroker*)broker),ctx); \
     provider->setProviderBase(&base##pn); \
       provider->initialize(ctx); \
     base##pn.setBaseMI(provider); \
    } \
   mi.hdl=provider; \
   base##pn.incUseCount(); \
  return &mi; \
 }
#   endif
//// KS Same comment about provider->intialize
/** KS_TODO
    @param pn KS_TODO
    @todo document this
*/
#   define CMProviderBase(pn) \
   CmpiProviderBase base##pn;

/**
 * @}
 */

#endif // _CMPIMACS_H_
