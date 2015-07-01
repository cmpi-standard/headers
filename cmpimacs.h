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
 */

/**
 * Important Note: The work on this header file is not complete yet; the
 * definitions in ths header file may not always be consistent with the
 * Technical Standard.
 */

#ifndef _CMPIMACS_H_
#   define _CMPIMACS_H_

#   ifndef DOC_ONLY
#      include "cmpidt.h"
#      include "cmpift.h"
#   endif

#   ifdef DOC_ONLY
#      define CMPI_INLINE
#   endif

#   ifdef DOC_ONLY
/** This macro builds a CMPIStatus object with @p rc as
      return code and returns to the CIMOM.
      @param rc the CMPI return code
      @return This macro contains a return statement and leaves the function.
   */
noReturn CMReturn (CMPIrc rc);
#   else
#      define CMReturn(rc_) \
     do \
     { \
         CMPIStatus stat; \
         stat.rc=rc_; \
         stat.msg=NULL; \
         return stat; \
     } while (0)
#   endif

#   ifdef DOC_ONLY
/** This macro builds a CMPIStatus object with @p rc as return code and
    @p str as message and returns to the Broker.
    @param rc the CMPI return code
    @param str the message as String object
    @return This macro contains a return statement and leaves the function.
   */
noReturn CMReturnWithString (CMPIrc rc, CMPIString * str);
#   else
#      define CMReturnWithString(rc_,str_) \
     do \
     { \
         CMPIStatus stat; \
         stat.rc=rc_; \
         stat.msg=str_; \
         return stat; \
     } while (0)
#   endif

#   ifdef DOC_ONLY
/** CMReturnWithChars macro builds a CMPIStatus object with
    @p rc as return code and @p msg as message and returns to the CMPIBroker
    and executes a return statement.

    This macro does not correspond to one single CMPI function.
    @param mb Points to CMPIBroker
    @param rc the CMPIrc return code to be inserted into the created CMPIStatus.
    @param msg the message as character string to be inserted into the
        created CMPIStatus.
    @return This macro contains a return statement and leaves the function.
    @todo example
*/
noReturn CMReturnWithChars (const CMPIBroker * mb, CMPIrc rc, char *msg);
#   else
#      define CMReturnWithChars(mb_,rc_,chars_) \
      do \
      { \
          CMPIStatus stat; \
          stat.rc=rc_; \
          if (mb_) \
              stat.msg=(mb_)->eft->newString((mb_),(chars_),NULL); \
          else \
              stat.msg=NULL; \
          return stat; \
      } while (0)
#   endif


#   ifdef CMPI_INLINE
/** @brief Initializes status object @p st with @p rcp and NULL
           message.
    @param st Pointer to CMPIStatus object in which @rcp is to
              be inserted.
    @param rcp CMPI return code
  */
_CMPI_INLINE_MOD void CMSetStatus (CMPIStatus * st, CMPIrc rcp)
{
    if (st)
    {
        (st)->rc = (rcp);
        (st)->msg = NULL;
    }
}
#   else
#      define CMSetStatus(st_,rcp_) \
      do \
      { \
          if (st_) \
          { \
              (st_)->rc=(rcp_); \
              (st_)->msg=NULL; \
          } \
      } while (0)
#   endif


#   ifdef CMPI_INLINE
/** @brief Initializes CMPIStatus object with @p rc CMPIStatus
    and @p string message.

    @param st Points to target CMPIStatus object.
    @param rcp CMPIrc return code to be insered int @st.
    @param string CMPIString containing Message to be inserted into @st.
  */
_CMPI_INLINE_MOD void CMSetStatusWithString(
    CMPIStatus * st,
    CMPIrc rcp,
    const CMPIString * string)
{
    if (st)
    {
        (st)->rc = (rcp);
        (st)->msg = (string);
    }
}
#   else
#      define CMSetStatusWithString(st_,rcp_,string_) \
      do \
      { \
          if (st_) \
          { \
              (st_)->rc=(rcp_); \
              (st_)->msg=(string_); \
          } \
      } while (0)
#   endif


#   ifdef CMPI_INLINE
/** @brief Initializes CMPIstatus object with @p rcp and message @p chars.

    This function creates a new string or NULL if @chars is NULL
    and puts the string and @p rcp code into the provided
    CMPIStatus @p st.
    @param mb Points to CMPIBroker.
    @param st Points to CMPIStatus object.
    @param rcp CMPIrc return code.
    @param chars Message character string.
    @see CMPIStatus
  */
_CMPI_INLINE_MOD void CMSetStatusWithChars(
    const CMPIBroker * mb,
    CMPIStatus * st,
    CMPIrc rcp,
    const char *chars)
{
    if (st)
    {
        (st)->rc = (rcp);
        if (mb)
        {
            (st)->msg = (mb)->eft->newString ((mb), (chars), NULL);
        }
        else
        {
            (st)->msg = NULL;
        }
    }
}
#   else
#      define CMSetStatusWithChars(mb_,st_,rcp_,chars_) \
      do \
      { \
          if (st_) \
          { \
              (st_)->rc=(rcp_); \
              if (mb_) \
                  (st_)->msg=(mb_)->eft->newString((mb_),(chars_),NULL); \
              else \
                  (st_)->msg=NULL; \
          } \
      } while (0)
#   endif


#   ifdef CMPI_INLINE
/** @brief Tests any CMPI object to determine if it is a NULL
           object.
    @param obj CMPI Object pointer
    @retval true The object is not NULL
    @retval false The object is NULL
  */
_CMPI_INLINE_MOD CMPIBoolean CMIsNullObject (const void *obj)
{
    return ((obj) == NULL || *((void **) (obj)) == NULL);
}
#   else
#      define CMIsNullObject(o) ((o)==NULL || *((void**)(o))==NULL)
#   endif

#   ifdef CMPI_INLINE
/** @brief Tests a CMPIData object for nullValue data item.
    @param val CMPIValue object
    @retval true NULL value CMPIData value.
    @retval false Not NULL CMPIData value.
    @todo needs example
    @see CMPIData
  */
_CMPI_INLINE_MOD CMPIBoolean CMIsNullValue (const CMPIData val)
{
  return ((val.state) & CMPI_nullValue);
}
#   else
#      define CMIsNullValue(v)      ((v.state) & CMPI_nullValue)
#   endif

#   ifdef CMPI_INLINE
/** brief Tests  CMPIData object for keyValue data item.
      @param val CMPIValue object.
      @retval true CMPIData object is KeyValue
      @retval false CMPIData object is NOT KeyValue
      @see CMPIValueState CMPIData
  */
_CMPI_INLINE_MOD CMPIBoolean CMIsKeyValue (CMPIData val)
{
  return ((val.state) & CMPI_keyValue);
}
#   else
#      define CMIsKeyValue(v)      ((v.state) & CMPI_keyValue)
#   endif

#   ifdef CMPI_INLINE
/** brief Tests CMPIData object for array data item type.
    @param val Value object
    @retval true CMPIData object is array type.
    @retval false CMPIData object is NOT array type
    @todo this needs example.
  */
_CMPI_INLINE_MOD CMPIBoolean CMIsArray (const CMPIData val)
{
  return ((val.type) & CMPI_ARRAY);
}
#   else
#      define CMIsArray(v)      ((v.type) & CMPI_ARRAY)
#   endif


    // Life-cycle macros.clone
/**
   @def CMClone(0,rc)

   Macro to call clone for any  the objects of anyCMPI function table since
   all function tables are required to have the clone() function.

   There is no inline function to allow the same call to be used
   for the objects of all of the function tables.

   @param o Object to be copied.
   @param [out] rc  If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
   @return @parblock If successful, returns a pointer to the
         copied clone of the object defined by @0 object.

     The returned CMPIEnumerationFilter object shall be explicitly
     released by the MI using CMPIEnumerationFilterFT.release().

     If not successful, returns NULL.
     @endparblock

     @par Errors
     The following @ref CMPIrc codes shall be recognized:
     @li CMPI_RC_OK Operation successful.
     @li CMPI_RC_ERR_INVALID_HANDLE The @p ef handle is invalid.
     @see CMPIContextFT.clone(), CMPIResultFT.clone(), CMPIErrorFT.clone(),
     CMPIInstanceFT.clone(), CMPIObjectPathFT.clone(),
     CMPISelectExpFT.clone(), CMPISelectCondFT.clone(),
     CMPISubCondFT.clone(), CMPIPredicateFT.clone(),
     CMPIArgsFT.clone(), CMPIStringFT.clone(),
     CMPIIEnumerationFT.clone(), CMPIDateTimeFT.clone(),
     CMPIPropertyListFT.clone(), CMPIEnumerationFilterFT.clone(),
*/
#   define CMClone(o,rc)       ((o)->ft->clone((o),(rc)))

/**
   @def CMRelease(o)

   Macro to call release release function for object of  any
   CMPI function table  since all function tables are required
   to have the clone() function.

   There is no inline function to allow the same call to be used
   for the objects of all of the function tables.

   This indicates to
     the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free the
     resources associated with the object during the call to
     this function, or later during some garbage collection
     cycle.

     @param o Pointer to the object to be released.
     @return CMPIStatus structure indicating the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid.
     @todo create list of functions. This should be copy from clone above
 */
#   define CMRelease(o)        ((o)->ft->release((o)))

    // CMPIBroker factory macros

#   ifdef CMPI_INLINE
/** Instance factory service.
    @param mb Points to CMPIBroker.
    @param op ObjectPath containing namespace and classname.
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created Instance.
    @see CMPIBrokerEncFT.newInstance()
 */
_CMPI_INLINE_MOD CMPIInstance * CMNewInstance (
    const CMPIBroker * mb,
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((mb)->eft->newInstance ((mb), (op), (rc)));
}
#   else
#      define CMNewInstance(b,c,rc) ((b)->eft->newInstance((b),(c),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** ObjectPath factory service.
    @param mb Points to CMPIBroker.
    @param ns Namespace
    @param cn Classname.
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created ObjectPath.
    @see CMPIBrokerEncFT.newObjectPath()
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
#      define CMNewObjectPath(b,n,c,rc) \
           ((b)->eft->newObjectPath((b),(n),(c),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** String container factory service.
    @param mb Points to CMPIBroker.
    @param data String data
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created String.
    @see CMPIBrokerEncFT.newString()
*/
_CMPI_INLINE_MOD CMPIString * CMNewString (
    const CMPIBroker * mb,
    const char *data,
    CMPIStatus * rc)
{
  return ((mb)->eft->newString ((mb), (data), (rc)));
}
#   else
#      define CMNewString(b,s,rc) ((b)->eft->newString((b),(s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Args container factory service.
    @param mb Points to CMPIBroker.
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created Args container.
    @see CMPIBrokerEncFT.newArgs()
*/
_CMPI_INLINE_MOD CMPIArgs * CMNewArgs (const CMPIBroker * mb, CMPIStatus * rc)
{
  return ((mb)->eft->newArgs ((mb), (rc)));
}
#   else
#      define CMNewArgs(b,rc) ((b)->eft->newArgs((b),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Array container factory service.
    @param mb Points to CMPIBroker.
    @param max Maximum number of elements
    @param type Element type
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created Array.
    @see CMPIBrokerEncFT.newArray()
*/
_CMPI_INLINE_MOD CMPIArray * CMNewArray (
    const CMPIBroker * mb,
    CMPICount max,
    CMPIType type,
    CMPIStatus * rc)
{
  return ((mb)->eft->newArray ((mb), (max), (type), (rc)));
}
#   else
#      define CMNewArray(b,c,t,rc)     ((b)->eft->newArray((b),(c),(t),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** DateTime factory service. Initialized with the time of day.
    @param mb Pointer to CMPIBroker
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created DateTime.
    @see CMPIBrokerEncFT.newDateTime()
*/
_CMPI_INLINE_MOD CMPIDateTime * CMNewDateTime (
    const CMPIBroker * mb,
    CMPIStatus * rc)
{
  return ((mb)->eft->newDateTime ((mb), (rc)));
}
#   else
#      define CMNewDateTime(b,rc)           ((b)->eft->newDateTime((b),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** DateTime factory service. Initialized from @p binTime.
     @param mb Points to CMPIBroker.
     @param binTime Date/Time definition in binary format in microsecods
     starting since 00:00:00 GMT, Jan 1,1970.
     @param interval Wenn true, defines Date/Time definition to be an
         interval value
     @param rc Output: Service return status (suppressed when NULL).
     @return The newly created DateTime.
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
#      define CMNewDateTimeFromBinary(b,d,i,rc) \
                      ((b)->eft->newDateTimeFromBinary((b),(d),(i),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** DateTime factory service. Is initialized from @p utcTime .
    @param mb Points to CMPIBroker.
    @param utcTime Date/Time definition in UTC format
    @param rc Output: Service return status (suppressed when NULL).
    @return The newly created DateTime
    @see CMPIBrokerEncFT.newDateTimeFromChars()
*/
_CMPI_INLINE_MOD CMPIDateTime *CMNewDateTimeFromChars(
    const CMPIBroker * mb,
    const char *utcTime,
    CMPIStatus * rc)
{
  return ((mb)->eft->newDateTimeFromChars ((mb), (utcTime), (rc)));
}
#   else
#      define CMNewDateTimeFromChars(b,d,rc) \
           ((b)->eft->newDateTimeFromChars((b),(d),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** SelectExp factory service. This structure encompasses queries
     and provides mechanism to operate on the query.
     @param mb Points to CMPIBroker.
     @param query The select expression.
     @param lang The query language.
     @param projection Output: Projection specification
                (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return The newly created SelectExp.
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
#      define CMNewSelectExp(b,q,l,p,rc) \
           ((b)->eft->newSelectExp((b),(q),(l),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Function to determine whether a CIM class is of @p type or any of
         @p type subclasses.
     @param mb Points to CMPIBroker.
     @param op The class path (namespace and classname components).
     @param type The type to tested for.
     @param rc Output: Service return status (suppressed when NULL).
     @return True if test successful.
     @see CMPIBrokerEncFT.classPathIsA()
     */
_CMPI_INLINE_MOD CMPIBoolean CMClassPathIsA(
    const CMPIBroker * mb,
    const CMPIObjectPath * op,
    const char *type,
    CMPIStatus * rc)
{
  return ((mb)->eft->classPathIsA ((mb), (op), (type), (rc)));
}
#   else
#      define CMClassPathIsA(b,p,pn,rc) \
           ((b)->eft->classPathIsA((b),(p),(pn),(rc)))
#   endif

    // Debugging macros

#   ifdef CMPI_INLINE
/** Attempts to transforms an CMPI object to a broker specific string format.
         Intended for debugging purposes only.
     @param mb Points to CMPIBroker.
     @param object A valid CMPI object.
     @param rc Output: Service return status (suppressed when NULL).
     @return String from representation of @p object.
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
#      define CDToString(b,o,rc)    ((b)->eft->toString((b),(void*)(o),(rc)))
#   endif

#    ifdef CMPI_INLINE
/**
    Verifies whether @p object is of CMPI type @p type.
    Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param type A string specifying a valid CMPI Object type
        ("CMPIInstance", "CMPIObjectPath", etc).
    @param rc Output: Service return status (suppressed when NULL).
    @return True if test successful.
    @see CMPIBrokerEncFT.isOfType()
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
#      define CDIsOfType(b,o,t,rc) \
           (b)->eft->isOfType((b),(void*)(o),(t),(rc))
#   endif

#    ifdef CMPI_INLINE
/**
    Retrieves the CMPI type of @p object.
    Intended for debugging purposes only.
    @param mb Points to CMPIBroker.
    @param object A valid CMPI object.
    @param rc Output: Service return status (suppressed when NULL).
    @return CMPI object type.
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
#      define CDGetType(b,o,rc)      ((b)->eft->getType((b),(void*)(o),(rc)))
#   endif

// KS commented out completely _85 version code.

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** Logs the message to the standard logging facility.
     @param mb Points to CMPIBroker.
     @param severity The severity is from 1-4. 1 is for information,
       2, is for warning, 3 for severe and 4 for fatal.
     @param id The ID of the provider.
     @param text The message. If not NULL, is the message text to be logged.
     @param string The message. If not NULL,  is the message text to be logged.
       string will be ignored when text is not NULL.
     @param rc Output: Service return status

    Example usage:
     <PRE>
         CMLogMessage(_broker, 1, "TestProvider",
             "Entering EnumerateInstance", NULL);
     </PRE>
    @see CMPIBrokerEncFT.logMessage()
*/

_CMPI_INLINE_MOD CMPIStatus CMLogMessage(
    const CMPIBroker * b,
    int severity,
    const char *id,
    const char *text,
    const CMPIString * string)
{
  return ((b)->eft->logMessage ((b), (severity), (id), (text), (string)));
}
#   else
#      define CMLogMessage(b,severity,id, text, string)  \
          ((b)->eft->logMessage((b),(severity),(id),(text),(string)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
// KS There is an issue here int the documentaiton for component.  No
// such file as TraceComponents.h
// KS Issue here. OpenPegasus file uses CMPILevel as type, not int
/**  Logs the message to the trace facility.
     @param mb Points to CMPIBroker.
     @param level The severity is from 1-4.
     @param component The component name to use for logging. The available
      facilities are defined in TraceComponents.h file.
     @param text The message. If not NULL, is the message text to be logged.
     @param string The message. If not NULL,  is the message
       text to belogged. string will be ignored when text is not
       NULL.
     @param rc Output: Service return status
     @see CMPIBrokerEncFT.trace()

     Example usage:
     <PRE>
           CMTraceMessage( );
     </PRE>

*/
_CMPI_INLINE_MOD CMPIStatus CMTraceMessage(
    const CMPIBroker * b,
    int level,
    const char *component,
    const char *text,
    const CMPIString * string)
{
  return ((b)->eft->trace ((b), (level), (component), (text), (string)));
}
#   else
#      define CMTraceMessage(b,level,component, text, string)  \
           ((b)->eft->trace((b),(level),(component),(text),(string)))
#   endif
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Create a new CMPIError object.
    @param b Points to CMPIBroker.
    @param owner Identifies the entity that owns the msg format definition.
    @param msgID Identifies the format of the message.
    @param msg Formatted and translated message.
    @param sev Perceived severity of this error.
    @param pc Probable caues of this error.
    @param cimStatusCode Status Code.
    @param rc Service return status
    @return Pointer to a newly allocated CMPIError object.
    @see CMPIBrokerEncFT.newCMPIError()

    Example usage:
    <PRE>
        CMNewCMPIError( );
    </PRE>
*/
_CMPI_INLINE_MOD CMPIError* CMNewCMPIError(
    const CMPIBroker* b,
    const char *owner,
    const char* msgID,
    const char* msg,
    const CMPIErrorSeverity sev,
    const CMPIErrorProbableCause pc,
    const CMPIrc cimStatusCode,
    CMPIStatus* rc)
{
  return ((b)->eft->newCMPIError ((b), (owner), (msgID), (msg), (sev),
          (pc), (cimStatusCode), (rc)));
}
#   else
#      define CMNewCMPIError(b,owner,msgID,msg,sev,pc,cimStatusCode,rc)  \
           ((b)->eft->newCMPIError((b),(owner),(msgID),(msg),(sev), \
           (pc),(cimStatusCode),(rc)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Opens a message file and returns a handle to it.
    @param b Points to CMPIBroker.
    @param msgFile The message file identifier.
    @param msgFileHandle Output: The handle representing the open msg file.
    @return Service return status
    @see CMPIBrokerEncFT.openMessageFile()

    Example usage:
    <PRE>
        CMOpenMessageFile(_broker,"/path/msgFile",&msgFileHandle);
    </PRE>
*/
_CMPI_INLINE_MOD CMPIStatus CMOpenMessageFile(
    const CMPIBroker* b,
    const char *msgFile,
    CMPIMsgFileHandle *msgFileHandle)
{
  return ((b)->eft->openMessageFile ((b), (msgFile), (msgFileHandle)));
}
#   else
#      define CMOpenMessageFile(b,mf,mfh) \
           ((b)->eft->openMessageFile((b),(mf),(mfh)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Closes a message file and returns a handle to it.
    @param mb Points to CMPIBroker.
    @param msgFileHandle The handle representing the open message file.
    @return Service return status
    @see CMPIBrokerEncFT.closeMessageFile()
    Example usage:
    <PRE>
        CMCloseMessageFile(_broker,msgFileHandle);
    </PRE>
*/
_CMPI_INLINE_MOD CMPIStatus CMCloseMessageFile(
    const CMPIBroker* b,
    const CMPIMsgFileHandle msgFilehandle)
{
  return ((b)->eft->closeMessageFile ((b), (msgFileHandle)));
}
#   else
#      define CMCloseMessageFile(b,mfh)  \
           ((b)->eft->closeMessageFile((b),(mfh)))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Retrieves translated message from a message file.
    When using as macro, use CMFmtArgsX and CMFmtX macros (defined
    above) to generate the variable parameter list and ommit
    the count parameter.

    @param mb Points to CMPIBroker.
    @param msgId The message identifier.
    @param msgFileHandle The handle representing the open message file.
    @param defMsg The default message. The message can have up to 10 msg
        insert placeholders ($0 through $9). The placeholders will be
        replaced by the corresponding message insert values.
    @param rc Output: Service return status (suppressed when NULL).
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
    <PRE>
       CMGetMessage2(_broker,"msgid",msgFileHandle,"Test $0 $1",
       NULL,CMFmtArgs2(CMFmtChars("message"),CMFmtSint(1));
    </PRE>
*/
_CMPI_INLINE_MOD CMPIString* CMGetMessage2(
    const CMPIBroker* mb,
    const char *msgId,
    const CMPIMsgFileHandle msgFilehandle,
    const char *defMsg,
    CMPIStatus* rc,
    unsigned int, ...);
#   else
#      define CMGetMessage2(b,id,mfh,def,rc,parms)  \
           ((b)->eft->getMessage2((b),(id),(mfh),(def),(rc),parms))
#   endif /* CMPI_INLINE */
#   endif /* CMPI_VER_200 */


    // CMPIInstance macros


#   ifdef CMPI_INLINE
/** Gets a named property value.
     @param inst Instance this pointer.
     @param name Property name.
     @param rc Output: Service return status (suppressed when NULL).
     @return Property value.
     @see CMPIInstanceFT.getProperty()
      */
_CMPI_INLINE_MOD CMPIData CMGetProperty(
    const CMPIInstance * inst,
    const char *name,
    CMPIStatus * rc)
{
  return ((inst)->ft->getProperty ((inst), (name), (rc)));
}
#   else
#      define CMGetProperty(i,n,rc)      ((i)->ft->getProperty((i),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a Property value defined by its index.
     @param inst Instance this pointer.
     @param index Position in the internal Data array.
     @param name Output: Returned property name (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return Property value.
     @see CMPIInstanceFT.getPropertyAt()
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
#      define CMGetPropertyAt(i,num,s,rc) \
           ((i)->ft->getPropertyAt((i),(num),(s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Adds/replaces a named Property.
     @param inst Instance this pointer.
     @param name Entry name.
     @param value Address of value structure.
     @param type Value type.
     @return Service return status.
     @see CMPIInstanceFT.setProperty()

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
#      define CMSetProperty(i,n,v,t) \
           ((i)->ft->setProperty((i),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Gets the number of properties contained in this Instance.
     @param inst Instance this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Number of properties.
     @see CMPIInstanceFT.getPropertyCount()
      */
_CMPI_INLINE_MOD CMPICount CMGetPropertyCount(
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((inst)->ft->getPropertyCount ((inst), (rc)));
}
#   else
#      define CMGetPropertyCount(i,rc)   ((i)->ft->getPropertyCount((i),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Generates an ObjectPath out of the namespace, classname and
    key propeties of this Instance.
    @param inst Instance this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return the generated ObjectPath.
    @see CMPIInstanceFT.getObjectPath()
      */
_CMPI_INLINE_MOD CMPIObjectPath *CMGetObjectPath(
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((inst)->ft->getObjectPath ((inst), (rc)));
}
#   else
#      define CMGetObjectPath(i,rc) ((i)->ft->getObjectPath((i),(rc)))
#   endif

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** Replaces the ObjectPath of the instance.
     @param inst Instance this pointer.
     @param obj Pointer to the new object path. This objectpath shall
     contain the namespace, classname, as well as all keys for the
     specified instance.
     @param rc Output: Service return status (suppressed when NULL).
     @return the generated ObjectPath.
     @see CMPIInstanceFT.setObjectPath()
      */
_CMPI_INLINE_MOD CMPIStatus CMSetObjectPath(
    CMPIInstance * inst,
    const CMPIObjectPath * obj)
{
  return ((inst)->ft->setObjectPath ((inst), (obj)));
}
#   else
#      define CMSetObjectPath(i,obj)  ((i)->ft->setObjectPath((i),(obj)))
#   endif
#   endif /* CMPI_VER_100 */

#   ifdef CMPI_INLINE
/** Directs CMPI to ignore any setProperty operations for this
      instance for any properties not in this list.
     @param inst Instance this pointer.
     @param propertyList If not NULL, the members of the array define one
         or more Property names to be accepted by setProperty operations.
     @param keys Deprecated, ignored by MB, maintained here for compatibility.
     @return Service return status.
     @see CMPIInstanceFT.setPropertyFilter()
      */
_CMPI_INLINE_MOD CMPIStatus CMSetPropertyFilter(
    CMPIInstance * inst,
    const char **propertyList,
    char **keys)
{
  return ((inst)->ft->setPropertyFilter ((inst), (propertyList), (keys)));
}
#   else
#      define CMSetPropertyFilter(i,pl,k) \
           ((i)->ft->setPropertyFilter((i),(pl),(k)))
#   endif

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Add/replace a named Property value and origin
    @param inst is a pointer to the CMPIInstance structure.
    @param name is a string containing the Property name.
    @param value points to a CMPIValue structure containing the
           value to be assigned to the Property.
    @param type is a CMPIType structure defining the type of the
           value.
    @param origin specifies the instance origin.  If NULL, then
           no origin is attached to  the property
    @return Service return status
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
#      define CMSetPropertyWithOrigin(i,n,v,t,o) \
           ((i)->ft->setPropertyWithOrigin((i),(n),(CMPIValue*)(v),(t),(o)))
#   endif
#   endif /* CMPI_VER_200 */


   // CMPIObjectPath macros


#   ifdef CMPI_INLINE
/** Set/replace the hostname component.
     @param op ObjectPath this pointer.
     @param hn The hostname string
     @return Service return status.
     @see CMPIObjectPathFT.setHostname()
      */
_CMPI_INLINE_MOD CMPIStatus
CMSetHostname (CMPIObjectPath * op, const char *hn)
{
  return ((op)->ft->setHostname ((op), (hn)));
}
#   else
#      define CMSetHostname(p,n) ((p)->ft->setHostname((p),(n)))
#   endif

#   ifdef CMPI_INLINE
/** Get the hostname component.
     @param op ObjectPath this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The hostname component.
     @see CMPIObjectPathFT.setHostname()
      */
_CMPI_INLINE_MOD CMPIString *CMGetHostname(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getHostname ((op), (rc)));
}
#   else
#      define CMGetHostname(p,rc) ((p)->ft->getHostname((p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Set/replace the namespace component.
     @param op ObjectPath this pointer.
     @param ns The namespace string
     @return Service return status.
     @see CMPIObjectPathFT.setNameSpace()
*/
_CMPI_INLINE_MOD CMPIStatus
CMSetNameSpace (CMPIObjectPath * op, const char *ns)
{
  return ((op)->ft->setNameSpace ((op), (ns)));
}
#   else
#      define CMSetNameSpace(p,n) ((p)->ft->setNameSpace((p),(n)))
#   endif

#   ifdef CMPI_INLINE
/** Get the namespace component.
     @param op ObjectPath this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The namespace component.
     @see CMPIObjectPathFT.getNameSpace()
*/
_CMPI_INLINE_MOD CMPIString *CMGetNameSpace(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getNameSpace ((op), (rc)));
}
#   else
#      define CMGetNameSpace(p,rc) ((p)->ft->getNameSpace((p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Set/replace the classname component.
    @param op ObjectPath this pointer.
    @param cn The hostname string
    @return Service return status.
    @see CMPIObjectPathFT.setClassName()
*/
_CMPI_INLINE_MOD CMPIStatus CMSetClassName(
    CMPIObjectPath * op,
    const char *cn)
{
  return ((op)->ft->setClassName ((op), (cn)));
}
#   else
#      define CMSetClassName(p,n) ((p)->ft->setClassName((p),(n)))
#   endif

#   ifdef CMPI_INLINE
/** Get the classname component.
    @param op ObjectPath this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return The classname component.
    @see CMPIObjectPathFT.getClassName()
      */
_CMPI_INLINE_MOD CMPIString *CMGetClassName(
    const CMPIObjectPath * op,
    CMPIStatus * rc)
{
  return ((op)->ft->getClassName ((op), (rc)));
}
#   else
#      define CMGetClassName(p,rc) ((p)->ft->getClassName((p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Adds/replaces a named key property.
    @param op ObjectPath this pointer.
    @param name Key property name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIObjectPathFT.addKey()
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
#      define CMAddKey(p,n,v,t) \
           ((p)->ft->addKey((p),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a named key property value.
    @param op ObjectPath this pointer.
    @param name Key property name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Entry value.
    @see CMPIObjectPathFT.getKey()
      */
_CMPI_INLINE_MOD CMPIData CMGetKey(
    const CMPIObjectPath * op,
    const char *name,
    CMPIStatus * rc)
{
  return ((op)->ft->getKey ((op), (name), (rc)));
}
#   else
#      define CMGetKey(p,n,rc) ((p)->ft->getKey((p),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a key property value defined by its index.
    @param op ObjectPath this pointer.
    @param index Position in the internal Data array.
    @param name Output: Returned property name (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
    @return Data value.
    @see CMPIObjectPathFT.getKeyAt()
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
#      define CMGetKeyAt(p,i,n,rc) ((p)->ft->getKeyAt((p),(i),(n),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** Gets the number of key properties contained in this ObjectPath.
    @param op ObjectPath this pointer.
    @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetKeyCount(p,rc) ((p)->ft->getKeyCount((p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Set/replace namespace and classname components from @p src.
    @param op ObjectPath this pointer.
    @param src Source input.
    @return Service return status.
    @see CMPIObjectPathFT.setNameSpaceFromObjectPath()
*/
_CMPI_INLINE_MOD CMPIStatus CMSetNameSpaceFromObjectPath(
    CMPIObjectPath * op,
    const CMPIObjectPath * src)
{
  return ((op)->ft->setNameSpaceFromObjectPath ((op), (src)));
}
#   else
#      define CMSetNameSpaceFromObjectPath(p,s) \
           ((p)->ft->setNameSpaceFromObjectPath((p),(s)))
#   endif

#   ifdef CMPI_INLINE
/** Set/replace hostname, namespace and classname components from @p src.
    @param op ObjectPath this pointer.
    @param src Source input.
    @return Service return status.
    @see CMPIObjectPathFT.setHostAndNameSpaceFromObjectPath()
      */
_CMPI_INLINE_MOD CMPIStatus CMSetHostAndNameSpaceFromObjectPath(
    CMPIObjectPath * op,
    const CMPIObjectPath * src)
{
  return ((op)->ft->setHostAndNameSpaceFromObjectPath ((op), (src)));
}
#   else
#      define CMSetHostAndNameSpaceFromObjectPath(p,s) \
           ((p)->ft->setHostAndNameSpaceFromObjectPath((p),(s)))
#   endif

#ifdef CMPI_INLINE
/** Get class qualifier value.
    @param op ObjectPath this pointer.
    @param qName Qualifier name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getClassQualifier()
*/
_CMPI_INLINE_MOD CMPIData CMGetClassQualifier(
    const CMPIObjectPath* op,
    const char *qName,
    CMPIStatus *rc)
{
    return ((op)->ft->getClassQualifier((op),(qName),(rc)));
}
#else
  #define CMGetClassQualifier(op,qName,rc) \
                     ((op)->ft->getClassQualifier((op),(qName),(rc)))
#endif

#ifdef CMPI_INLINE
/** Get property qualifier value.
    @param op ObjectPath this pointer.
    @param pName Property name.
    @param qName Qualifier name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getPropertyQualifier()
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
/** Get method qualifier value.
    @param op ObjectPath this pointer.
    @param methodName Method name.
    @param qName Qualifier name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getMethodQualifier()
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
  #define CMGetMethodQualifier(op,methodName,qName,rc) \
       ((op)->ft->getMethodQualifier((op),(methodName),(qName),(rc)))
#endif

#ifdef CMPI_INLINE
/** Get method parameter qualifier value.
    @param op ObjectPath this pointer.
    @param mName Method name.
    @param pName Parameter name.
    @param qName Qualifier name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Qualifier value.
    @see CMPIObjectPathFT.getParameterQualifier()
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
/** Gets the number of elements contained in this Array.
    @param ar Array this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSize()
*/
_CMPI_INLINE_MOD CMPICount CMGetArrayCount(
    const CMPIArray * ar,
    CMPIStatus * rc)
{
    return ((ar)->ft->getSize ((ar), (rc)));
}
#   else
#      define CMGetArrayCount(a,rc) ((a)->ft->getSize((a),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets the element type.
    @param ar Array this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of elements.
    @see CMPIArrayFT.getSimpleType()
*/
_CMPI_INLINE_MOD CMPIType CMGetArrayType(
    const CMPIArray * ar,
    CMPIStatus * rc)
{
    return ((ar)->ft->getSimpleType ((ar), (rc)));
}
#   else
#      define CMGetArrayType(a,rc)  ((a)->ft->getSimpleType((a),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets an element value defined by its index.
    @param ar Array this pointer.
    @param index Position in the internal Data array.
    @param rc Output: Service return status (suppressed when NULL).
    @return Element value.
    @see CMPIArrayFT.getElementAt()
*/
_CMPI_INLINE_MOD CMPIData CMGetArrayElementAt(
    const CMPIArray * ar,
    CMPICount index,
    CMPIStatus * rc)
{
    return ((ar)->ft->getElementAt ((ar), (index), (rc)));
}
#   else
#      define CMGetArrayElementAt(a,n,rc) \
                                    ((a)->ft->getElementAt((a),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Sets an element value defined by its index.
    @param ar Array this pointer.
    @param index Position in the internal Data array.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see CMPIArrayFT.setElementAt()
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
#      define CMSetArrayElementAt(a,n,v,t) \
           ((a)->ft->setElementAt((a),(n),(CMPIValue*)(v),(t)))
#   endif



    // CMPIArgs macros


#   ifdef CMPI_INLINE
/** Adds/replaces a named argument.
    @param as Args this pointer.
    @param name Argument name.
    @param value Address of value structure.
    @param type Value type.
    @return Service return status.
    @see  CMPIArgsFT.addArg()
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
#      define CMAddArg(a,n,v,t) \
           ((a)->ft->addArg((a),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a named argument value.
    @param as Args this pointer.
    @param name Argument name.
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see  CMPIArgsFT.getArg()
*/
_CMPI_INLINE_MOD CMPIData CMGetArg(
    const CMPIArgs * as,
    const char *name,
    CMPIStatus * rc)
{
    return ((as)->ft->getArg ((as), (name), (rc)));
}
#   else
#      define CMGetArg(a,n,rc) ((a)->ft->getArg((a),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a Argument value defined by its index.
    @param as Args this pointer.
    @param index Position in the internal Data array.
    @param name Output: Returned argument name (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
    @return Argument value.
    @see  CMPIArgsFT.getArgAt()
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
#      define CMGetArgAt(a,p,n,rc) ((a)->ft->getArgAt((a),(p),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets the number of arguments contained in this Args.
    @param as Args this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of properties.
    @see  CMPIArgsFT.getArgCount()
*/
_CMPI_INLINE_MOD CMPICount CMGetArgCount (const CMPIArgs * as, CMPIStatus * rc)
{
    return ((as)->ft->getArgCount ((as), (rc)));
}
#   else
#      define CMGetArgCount(a,rc) ((a)->ft->getArgCount((a),(rc)))
#   endif

/**
   @brief KS_TODO
   @def CMGetCharPtr(s)
   @param s
   @todo - KS confirm this since the doc was just a guess right
         now
*/
#   define CMGetCharPtr(s) ((char*)s->hdl)

#   ifdef CMPI_INLINE
/** Get a pointer to a C char* representation of this String.
    @param st Points to CMPIString.
    @param rc Output: Service return status (suppressed when NULL).
    @return Pointer to char* representation.
    @see CMPIStringFT.getCharPtr()
*/
_CMPI_INLINE_MOD char * CMGetCharsPtr(
    const CMPIString * st,
    CMPIStatus * rc)
{
    return ((st)->ft->getCharPtr ((st), (rc)));
}
#   else
#      define CMGetCharsPtr(st,rc) ((st)->ft->getCharPtr((st),(rc)))
#   endif



    // CMPIDateTime macros


#   ifdef CMPI_INLINE
/** Get DateTime setting in UTC string format.
    @param dt DateTime this pointer.
    @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetStringFormat(d,rc)    ((d)->ft->getStringFormat((d),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Get DateTime setting in binary format (in microsecods
    starting since 00:00:00 GMT, Jan 1,1970).
    @param dt DateTime this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return DateTime in binary.
      */
_CMPI_INLINE_MOD CMPIUint64 CMGetBinaryFormat(
    const CMPIDateTime * dt,
    CMPIStatus * rc)
{
    return ((dt)->ft->getBinaryFormat ((dt), (rc)));
}
#   else
#      define CMGetBinaryFormat(d,rc)  ((d)->ft->getBinaryFormat((d),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Tests whether DateTime is an interval value.
    @param dt DateTime this pointer.
    @param rc Output: Service return status (suppressed when NULL).
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
#      define CMIsInterval(d,rc) ((d)->ft->isInterval((d),(rc)))
#   endif



    // CMPIError macros

#   ifdef CMPI_VER_200

#   ifdef CMPI_INLINE
/** Gets the type of this Error
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return the error type this Error object conatins
    @see CMPIErrorFT.getErrorType()
    @todo Looks like the inline form of this is
          wrong. the Macro is CMGetErrorType. but it is
          (*getErrorType) in line
 */
_CMPI_INLINE_MOD CMPIErrorType (*getErrorType)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getErrorType ((er), (rc)));
}
#   else
#      define CMGetErrorType(e,rc) ((e)->ft->getErrorType((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the alternate error type.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOtherErrorType()
    @looks like the inline form of this is wrong
 */
_CMPI_INLINE_MOD CMPIString* (*getOtherErrorType)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getOtherErrorType ((er), (rc)));
}
#   else
#      define CMGetOtherErrorType(e,rc) ((e)->ft->getOtherErrorType((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the owneing entity
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOwningEntity()
 */
_CMPI_INLINE_MOD CMPIString* (*getOwningEntity)(
    const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getOwningEntity ((er), (rc)));
}
#   else
#      define CMGetOwningEntity(e,rc) ((e)->ft->getOwningEntity((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which is the message ID.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getMessageID()
    @todo inline form wrong
 */
_CMPI_INLINE_MOD CMPIString* (*getMessageID)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getMessageID ((er), (rc)));
}
#   else
#      define CMGetMessageID(e,rc) ((e)->ft->getMessageID((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string comnating an error message.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getMessage()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIString* (*getMessage)(const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getMessage ((er), (rc)));
}
#   else
#      define CMGetErrorMessage(e,rc) ((e)->ft->getMessage((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns the perceieved severity of this error.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return the perceived severity
    @see CMPIErrorFT.getPerceivedSeverity()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIErrorSeverity (*getPerceivedSeverity)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getPerceivedSeverity ((er), (rc)));
}
#   else
#      define CMGetPerceivedSeverity(e,rc)  \
              ((e)->ft->getPerceivedSeverity((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns the probable cause of this error.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A probable cause value
    @see CMPIErrorFT.getProbableCause()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIErrorProbableCause (*getProbableCause)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getProbableCause ((er), (rc)));
}
#   else
#      define CMGetProbableCause(e,rc) \
              ((e)->ft->getProbableCause((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the probable cause.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getProbableCauseDescription()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIString* (*getProbableCauseDescription)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getProbableCauseDescription ((er), (rc)));
}
#   else
#      define CMGetProbableCauseDescription(e,rc) \
              ((e)->ft->getProbableCauseDescription((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns an array of strings which describes recomended actions.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A array of strings, which can be NULL
    @see CMPIErrorFT.getRecommendedActions()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIArray* (*getRecommendedActions)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getRecommendedActions ((er), (rc)));
}
#   else
#      define CMGetRecommendedActions(e,rc) \
          ((e)->ft->getRecommendedActions((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the Error source.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getErrorSource()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIString* (*getErrorSource)(
    const CMPIError* er, CMPIStatus* rc)
{
  return ((er)->ft->getErrorSource ((er), (rc)));
}
#   else
#      define CMGetErrorSource(e,rc) \
              ((e)->ft->getErrorSource((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a the format that the error src is in.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A error source format  code
    @see CMPIErrorFT.getErrorSourceFormat()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIErrorSrcFormat (*getErrorSourceFormat)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getErrorSourceFormat ((er), (rc)));
}
#   else
#      define CMGetErrorSourceFormat(e,rc)  \
              ((e)->ft->getErrorSourceFormat((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the 'other' format, only available if
    the error source is OTHER.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getOtherErrorSourceFormat()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIString* (*getOtherErrorSourceFormat)(
    const CMPIError* er,
    CMPIStatus* rc)
{
    return ((er)->ft->getOtherErrorSourceFormat ((er), (rc)));
}
#   else
#      define CMGetOtherErrorSourceFormat(e,rc)  \
              ((e)->ft->getOtherErrorSourceFormat((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns the status code of this error.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A CMPI Status code
    @see CMPIErrorFT.getCIMStatusCode()
    @todo inline form wrong.
*/
_CMPI_INLINE_MOD CMPIrc (*getCIMStatusCode)(const CMPIError* er, CMPIStatus* rc)
{
    return ((er)->ft->getCIMStatusCode ((er), (rc)));
}
#   else
#      define CMGetCIMStatusCode(e,rc) \
              ((e)->ft->getCIMStatusCode((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns a string which describes the status code error.
    @param er Error this pointer
    @param rc Output: Service return status (suppressed when NULL).
    @return A string, which can be NULL
    @see CMPIErrorFT.getCIMStatusCodeDescription()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIString* (*getCIMStatusCodeDescription)(
    const CMPIError* er,
    CMPIStatus* rc)
{
    return ((er)->ft->getCIMStatusCodeDescription ((er), (rc)));
}
#   else
#      define CMGetCIMStatusCodeDescription(e,rc) \
              ((e)->ft->getCIMStatusCodeDescription((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Returns an array which contains the dynamic content of the message.
    @param er The Error this pointer
    @param rc Output: Serbice return status (surpressed when NULL)
    @return An array of CMPIStrings which represents the dynamic values
    @see CMPIErrorFT.getMessageArguments()
    @todo inline form wrong.
*/
_CMPI_INLINE_MOD CMPIArray* (*getMessageArguments)(
    const CMPIError* er,
    CMPIStatus* rc)
{
  return ((er)->ft->getMessageArguments ((er), (rc)));
}
#   else
#      define CMGetMessageArguments(e,rc) \
              ((e)->ft->getMessageArguments((e),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the error type of this error object.
    @param er Error this pointer
    @param et The error type
    @return Output: Service return status
    @see CMPIErrorFT.setErrorType()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setErrorType)(
    CMPIError* er,
    const CMPIErrorType et)
{
  return ((er)->ft->setErrorType ((er), (et)));
}
#   else
#      define CMSetErrorType(e,et) \
              ((e)->ft->setErrorType((e),(et)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the 'other' error type of this error object.
    @param er Error this pointer
    @param oet A string which describes the error type, it is only valis when
        error type is "OTHER"
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorType()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setOtherErrorType)(
    CMPIError* er,
    const char * oet)
{
  return ((er)->ft->setOtherErrorType ((er), (oet)));
}
#   else
#      define CMSetOtherErrorType(e,oet) \
              ((e)->ft->setOtherErrorType((e),(oet)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the description of the probable cause.
    @param er Error this pointer
    @param pc The probable cause string
    @return Output: Service return status
    @see CMPIErrorFT.setProbableCauseDescription()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setProbableCauseDescription)(
    CMPIError* er,
    const char * pcd)
{
  return ((er)->ft->setProbableCauseDescription ((er), (pcd)));
}
#   else
#      define CMSetProbableCauseDescription(e,pcd) \
              ((e)->ft->setProbableCauseDescription((e),(pcd)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the recomended actions array.
    @param er Error this pointer
    @param ar An array of strings describing actions that shoudl
              be taken t deal with this error
    @return Output: Service return status
    @see CMPIErrorFT.setRecommendedActions()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setRecommendedActions)(
    CMPIError* er,
    const CMPIArray* ra)
{
  return ((er)->ft->setRecommendedActions ((er), (ra)));
}
#   else
#      define CMSetRecommendedActions(e,ra)                            \
              ((e)->ft->setRecommendedActions((e),(ra)))
#   endif

#   ifdef CMPI_INLINE
/** Specifies a string which specifes The identifying information of the entity
    (i.e., the instance) generating the error..
    @param er Error this pointer
    @param es the string which describes the source
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSource()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setErrorSource)(CMPIError* er, const char* es);
{
  return ((er)->ft->setErrorSource ((er), (es)));
}
#   else
#      define CMSetErrorSource(e,es) \
              ((e)->ft->setErrorSource((e),(es)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the source format of the error object
    @param er Error this pointer
    @param esf the string which describes the source format
    @return Output: Service return status
    @see CMPIErrorFT.setErrorSourceFormat()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setErrorSourceFormat)(
    CMPIError* er,
    const CMPIErrorSrcFormat esf);
{
  return ((er)->ft->setErrorSourceFormat ((er), (esf)));
}
#   else
#      define CMSetErrorSourceFormat(e,esf) \
              ((e)->ft->setErrorSourceFormat((e),(esf)))
#   endif

#   ifdef CMPI_INLINE
/** specifies A string defining "Other" values for ErrorSourceFormat
    @param er Error this pointer
    @param oef the string which describes the other source format
    @return Output: Service return status
    @see CMPIErrorFT.setOtherErrorSourceFormat()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setOtherErrorSourceFormat)(
    CMPIError* er,
    const char* oesf)
{
  return ((er)->ft->setOtherErrorSourceFormat ((er), (oesf)));
}
#   else
#      define CMSetOtherErrorSourceFormat(e,oesf) \
              ((e)->ft->setOtherErrorSourceFormat((e),(oesf)))
#   endif

#   ifdef CMPI_INLINE
/** Sets the description of the status code.
    @param er Error this pointer
    @param scd A string whcih describes the status code.
    @return Output: Service return status
    @see CMPIErrorFT.setCIMStatusCodeDescription()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setCIMStatusCodeDescription)(
    CMPIError* er,
    const char* cd);
{
  return ((er)->ft->setCIMStatusCodeDescription ((er), (cd)));
}
#   else
#      define CMSetCIMStatusCodeDescription(e,cd) \
              ((e)->ft->setCIMStatusCodeDescription((e),(cd)))
#   endif
#   ifdef CMPI_INLINE
/** Sets an array of strings for the dynamic content of the message
    @param er Error this pointer
    @param values Specifies an array of CMPIStrings containing the dynamic
    content of the message.
    @return Service return status
    @see CMPIErrorFT.setCIMMessageArguments()
    @todo inline form wrong.
 */
_CMPI_INLINE_MOD CMPIStatus (*setMessageArguments)(CMPIError* er, CMPIArray* ma)
{
  return ((er)->ft->setMessageArguments ((er), (ma)));
}
#   else
#      define CMSetMessageArguments(e,ma) \
              ((e)->ft->setMessageArguments((e),(ma)))
#   endif

#   endif /* CMPI_VER_200 */


    // CMPIEnumeration Macros


#   ifdef CMPI_INLINE
/** Get the next element of this Enumeration.
    @param en Enumeration this pointer.
    @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetNext(n,rc)  ((n)->ft->getNext((n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Test for any elements left in this Enumeration.
    @param en Enumeration this pointer.
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
#      define CMHasNext(n,rc) ((n)->ft->hasNext((n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Convert this Enumeration into an Array.
     @param en Enumeration this pointer.
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
#      define CMToArray(n,rc) ((n)->ft->toArray((n),(rc)))
#   endif


   // CMPIResult Macros


#   ifdef CMPI_INLINE
/** Return a value/type pair.
    @param rslt Result this pointer.
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
#      define CMReturnData(r,v,t) \
          ((r)->ft->returnData((r),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Return a Instance object.
    @param rslt Result this pointer.
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
#      define CMReturnInstance(r,i)  ((r)->ft->returnInstance((r),(i)))
#   endif

#   ifdef CMPI_INLINE
/** Return a ObjectPath object..
    @param rslt Result this pointer.
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
#      define CMReturnObjectPath(r,o) ((r)->ft->returnObjectPath((r),(o)))
#   endif

#   ifdef CMPI_INLINE
/** Indicates no further data to be returned.
    @param rslt Result this pointer.
    @return Service return status.
    @see CMPIResultFT.returnDone()
      */
_CMPI_INLINE_MOD CMPIStatus CMReturnDone(const CMPIResult * rslt)
{
  return ((rslt)->ft->returnDone ((rslt)));
}
#   else
#      define CMReturnDone(r) ((r)->ft->returnDone((r)))
#   endif

#   ifdef CMPI_VER_200
#   ifdef CMPI_INLINE
/** Return a CMPIError object instance
    @param rslt Result this pointer.
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
#      define CMReturnError(r,e) \
                           ((r)->ft->returnError((r),(e)))
#   endif
#   endif /* CMPI_VER_200 */


    // CMPIContext Macros


#   ifdef CMPI_INLINE
/** Gets a named Context entry value.
     @param ctx Context this pointer.
     @param name Context entry name.
     @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetContextEntry(c,n,rc)  \
                                 ((c)->ft->getEntry((c),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets a Context entry value defined by its index.
    @param ctx Context this pointer.
    @param index Position in the internal Data array.
    @param name Output: Returned Context entry name (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetContextEntryAt(c,p,n,rc) \
                         ((c)->ft->getEntryAt((c),(p),(n),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Gets the number of entries contained in this Context.
     @param ctx Context this pointer.
     @param rc Output: Service return status (suppressed when NULL).
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
#      define CMGetContextEntryCount(c,rc) \
                                ((c)->ft->getEntryCount((c),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** adds/replaces a named Context entry
     @param ctx Context this pointer.
     @param name Entry name.
     @param value Address of value structure.
     @param type Value type.
     @return Service return status.
    @see CMPIContextFT.addEntry()
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
#      define CMAddContextEntry(c,n,v,t) \
                  ((c)->ft->addEntry((c),(n),(CMPIValue*)(v),(t)))
#   endif



    // CMPISelectExp macros



#   ifdef CMPI_INLINE
/** Return the select expression in string format.
     @param se SelectExp this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The select expression.
     @see CMPISelectExpFT.getString()
*/
_CMPI_INLINE_MOD CMPIString *CMGetSelExpString(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getString ((se), (rc)));
}
#   else
#      define CMGetSelExpString(s,rc)          ((s)->ft->getString((s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Evaluate the instance using this select expression.
    @param se SelectExp this pointer.
    @param inst Instance to be evaluated.
    @param rc Output: Service return status (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluate()
      */
_CMPI_INLINE_MOD CMPIBoolean CMEvaluateSelExp(
    const CMPISelectExp * se,
    const CMPIInstance * inst,
    CMPIStatus * rc)
{
  return ((se)->ft->evaluate ((se), (inst), (rc)));
}
#   else
#      define CMEvaluateSelExp(s,i,r)        ((s)->ft->evaluate((s),(i),(r)))
#   endif

#   ifdef CMPI_VER_87
#   ifdef CMPI_INLINE
/** Evaluate this select expression by using a data value accessor routine. .
    @param se SelectExp this pointer.
    @param accessor Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param rc Output: Service return status (suppressed when NULL).
    @return True or false incicator.
    @see CMPISelectExpFT.evaluateUsingAccessor()
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
#      define CMEvaluateSelExpUsingAccessor(s,i,p,r) \
                            ((s)->ft->evaluateUsingAccessor((s),(i),(p),(r)))
#   endif
#   endif /* CMPI_VER_87 */

#   ifdef CMPI_INLINE
/** Return the select expression as disjunction of conjunctions.
     @param se SelectExp this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The disjunction.
     @see CMPISelectExpFT.getDoc()
*/
_CMPI_INLINE_MOD CMPISelectCond *CMGetDoc(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getDOC ((se), (rc)));
}
#   else
#      define CMGetDoc(s,rc) ((s)->ft->getDOC((s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Return the select expression as conjunction of disjunctions.
     @param se SelectExp this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The conjunction.
     @see CMPISelectExpFT.getCOD()
*/
_CMPI_INLINE_MOD CMPISelectCond *CMGetCod(
    const CMPISelectExp * se,
    CMPIStatus * rc)
{
  return ((se)->ft->getCOD ((se), (rc)));
}
#   else
#      define CMGetCod(s,rc) ((s)->ft->getCOD((s),(rc)))
#   endif



    // CMPISelectCond macros



#   ifdef CMPI_INLINE
/** Return the number of sub conditions that are partof this SelectCond.
    Optionally, the SelectCond type (COD or DOC) will be returned.
    @param sc SelectCond this pointer.
    @param type Output: SelectCond type (suppressed when NULL).
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of SubCond elements.
    @see CMPISelectCondFT.getCountAndType()
      */
_CMPI_INLINE_MOD CMPICount CMGetSubCondCountAndType(
    const CMPISelectCond * sc,
    int * type,
    CMPIStatus * rc)
{
  return ((sc)->ft->getCountAndType ((sc), (type), (rc)));
}
#   else
#      define CMGetSubCondCountAndType(c,t,rc) \
                                ((c)->ft->getCountAndType((c),(t),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Return a SubCond element based on its index.
    @param sc SelectCond this pointer.
    @param index Position in the internal SubCoind array.
    @param rc Output: Service return status (suppressed when NULL).
    @return The indexed SubCond element.
    @see CMPISelectCondFT.getSubCondAt()
      */
_CMPI_INLINE_MOD CMPISubCond *CMGetSubCondAt(
    const CMPISelectCond * sc,
    CMPICount index,
    CMPIStatus * rc)
{
  return ((sc)->ft->getSubCondAt ((sc), (index), (rc)));
}
#   else
#      define CMGetSubCondAt(c,p,rc)    ((c)->ft->getSubCondAt((c),(p),(rc)))
#   endif



    // CMPISubCond macros



#   ifdef CMPI_INLINE
/** Return the number of predicates that are part of sub condition.
    @param sc SubCond this pointer.
    @param rc Output: Service return status (suppressed when NULL).
    @return Number of Predicate elements.
    @see CMPISubCondFT.getCount()
      */
_CMPI_INLINE_MOD CMPICount CMGetPredicateCount(
    const CMPISubCond * sc,
    CMPIStatus * rc)
{
  return ((sc)->ft->getCount ((sc), (rc)));
}
#   else
#      define CMGetPredicateCount(s,rc) ((s)->ft->getCount((s),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Return a Predicate element based on its index.
    @param sc SubCond this pointer.
    @param index Position in the internal Predicate array.
    @param rc Output: Service return status (suppressed when NULL).
    @return The indexed Predicate element.
    @see CMPISubCondFT.getPredicateAt()
      */
_CMPI_INLINE_MOD CMPIPredicate *CMGetPredicateAt(
    const CMPISubCond * sc,
    CMPICount index,
    CMPIStatus * rc)
{
  return ((sc)->ft->getPredicateAt ((sc), (index), (rc)));
}
#   else
#      define CMGetPredicateAt(s,p,rc) \
                                  ((s)->ft->getPredicateAt((s),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Return a named Predicate element.
    @param sc SubCond this pointer.
    @param name Predicate name (property name).
    @param rc Output: Service return status (suppressed when NULL).
    @return The named Predicate element.
    @see CMPISubCondFT.getPredicate()
      */
_CMPI_INLINE_MOD CMPIPredicate *CMGetPredicate(
    const CMPISubCond * sc,
    const char *name,
    CMPIStatus * rc)
{
  return ((sc)->ft->getPredicate ((sc), (name), (rc)));
}
#   else
#      define CMGetPredicate(s,n,rc)    ((s)->ft->getPredicate((s),(n),(rc)))
#   endif



    // CMPIPredicate macros


#   ifdef CMPI_INLINE
/** Get the predicate components.
    @param pr Predicate this pointer.
    @param type Property type.
    @param op Predicate operation.
    @param lhs Left hand side of predicate.
    @param rhs Right hand side of predicate.
    @return Service return status.
    @see CMPIPredicateFT.getData()
*/
_CMPI_INLINE_MOD CMPIStatus CMGetPredicateData(
    const CMPIPredicate * pr,
    CMPIType * type,
    CMPIPredOp * op,
    CMPIString ** lhs,
    CMPIString ** rhs)
{
  return ((pr)->ft->getData ((pr), (type), (op), (lhs), (rhs)));
}
#   else
#      define CMGetPredicateData(p,t,o,n,v) \
          ((p)->ft->getData((p),(t),(o),(n),(v)))
#   endif

#   if defined(CMPI_VER_87) && !defined(CMPI_VER_100)
#   ifdef CMPI_INLINE
/** Evaluate the predicate using a specific value.
    @param pr Predicate this pointer.
    @param type Property type.
    @param value Address of value structure.
    @param type Value type.
    @param rc Output: Service return status (suppressed when NULL).
    @return Evaluation result.
    @todo Possibly no corresponding Function.
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
#      define CMEvaluatePredicate(p,v,t,rc) \
           ((p)->ft->evaluate((p),(CMPIValue*)(v),(t),(rc)))
#   endif
#   endif /* CMPI_VER_87 && !CMPI_VER_100 */

#   ifdef CMPI_VER_100
#   ifdef CMPI_INLINE
/** Evaluate this predicate  by using a data value accessor routine. .
    @param accessor Data accessor routine to be used.
    @param parm Data accessor parameter.
    @param rc Output: Service return status (suppressed when NULL).
    @return Evaluation result.
    @see CMPIPredicateFT.evaluateUsingAccessor()
      */
_CMPI_INLINE_MOD int CMEvaluatePredicateUsingAccessor(
    const CMPIPredicate * pr,
    CMPIAccessor * accessor,
    void *parm,
    CMPIStatus * rc)
{
  return ((pr)->ft->evaluateUsingAccessor ((pr), (accessor), (parm), (rc)));
}
#   else
#      define CMEvaluatePredicateUsingAccessor(p,a,parm,rc) \
          ((p)->ft->evaluateUsingAccessor((p),(a),(parm),(rc)))
#   endif
#   endif /* CMPI_VER_100 */



    // CMPIBroker Macros



#   ifdef CMPI_INLINE
/** 32 bits describing CMPI features supported by this CIMOM.
     See CMPI_MB_Class_x and CMPI_MB_Supports_xxx flags.
     @todo no direct correspondence. In fact, there is no
     brokerClassification at all. I assume it is
     brokerCapabilities.
 */
_CMPI_INLINE_MOD unsigned long CBGetClassification (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerClassification);
}
#   else
#      define CBGetClassification(b) ((b)->bft->brokerClassification)
#   endif

#   ifdef CMPI_INLINE
/** CIMOM version as defined by CIMOM.

    This shortcut had no direct corresponding function. It
    directly access the CMPIBroker.brokerVersion variable
     */
_CMPI_INLINE_MOD int CBBrokerVersion (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerVersion);
}
#   else
#      define CBBrokerVersion(b) ((b)->bft->brokerVersion)
#   endif

#   ifdef CMPI_INLINE
/** CIMOM name

    This shortcut had no direct corresponding function. It
    directly access the CMPIBroker.brokerVersion
     */
_CMPI_INLINE_MOD const char CBBrokerName (const CMPIBroker * mb)
{
  return ((mb)->bft->brokerName);
}
#   else
#      define CBBrokerName(b)                          ((b)->bft->brokerName)
#   endif

#ifdef DOC_ONLY
#define _CMPI_INLINE_MOD
#else
#define _CMPI_INLINE_MOD _CMPI_INLINE_MOD
#endif

#   ifdef CMPI_INLINE
 /** This function prepares the CMPI run time system to accept
     a thread that will be using CMPI services. The returned
     CMPIContext object must be used by the subsequent attachThread()
     and detachThread() invocations.
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
#      define CBPrepareAttachThread(b,c) \
                                 ((b)->bft->prepareAttachThread((b),(c)))
#   endif

#   ifdef CMPI_INLINE
/** This function informs the CMPI run time system that the current
    thread with Context will begin using CMPI services.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.attachThread()
     */
_CMPI_INLINE_MOD CMPIStatus CBAttachThread(
    const CMPIBroker * mb,
    const CMPIContext * ctx)
{
  return ((mb)->bft->attachThread ((mb), (ctx)));
}
#   else
#      define CBAttachThread(b,c)           ((b)->bft->attachThread((b),(c)))
#   endif

#   ifdef CMPI_INLINE
/** This function informs the CMPI run time system that the current thread
    will not be using CMPI services anymore. The Context object will be
    freed during this operation.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @return Service return status.
    @see CMPIBrokerFT.detachThread()
     */
_CMPI_INLINE_MOD CMPIStatus CBDetachThread(
    const CMPIBroker * mb,
    const CMPIContext * ctx)
{
  return ((mb)->bft->detachThread ((mb), (ctx)));
}
#   else
#      define CBDetachThread(b,c)           ((b)->bft->detachThread((b),(c)))
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
#      define CBDeliverIndication(b,c,n,i) \
                           ((b)->bft->deliverIndication((b),(c),(n),(i)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerate Instance Names of the class (and subclasses)
    defined by @p op.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op ObjectPath containing namespace and classname components.
    @param rc Output: Service return status (suppressed when NULL).
    @return Enumeration of ObjectPaths.
    @see CMPIBrokerFT.enumerateInstanceNames()
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
#      define CBEnumInstanceNames(b,c,p,rc) \
           ((b)->bft->enumerateInstanceNames((b),(c),(p),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerate Instances of the class (and subclasses) defined by @p op.
     Instance structure and inheritance scope can be controled using the
     CMPIInvocationFlags entry in @p ctx.
     @param mb Points to CMPIBroker..
     @param ctx Context object
     @param op ObjectPath containing namespace and classname components.
     @param properties If not NULL, the members of the array define
         one or more Property names. Each returned Object MUST NOT
         include elements for any Properties missing from this list
     @param rc Output: Service return status (suppressed when NULL).
     @return Enumeration of Instances.
     @see CMPIBrokerFT.enumerateInstances()
*/
_CMPI_INLINE_MOD CMPIEnumeration *CBEnumInstances(
    const CMPIBroker * mb,
    const CMPIContext * ctx,
    const CMPIObjectPath * op,
    const char **properties,
    CMPIStatus * rc)
{
  return ((mb)->bft->enumerateInstances ((mb), (ctx), (op), (properties),(rc)));
}
#   else
#      define CBEnumInstances(b,c,p,pr,rc) \
                         ((b)->bft->enumerateInstances((b),(c),(p),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Get Instance using @p op as reference. Instance structure can be
    controled using the CMPIInvocationFlags entry in @p ctx.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op ObjectPath containing namespace, classname and key components.
    @param properties If not NULL, the members of the array
     define one or more Property names. Each returned
     Object MUST NOT include elements for any Properties
     missing from this list
    @param rc Output: Service return status (suppressed when NULL).
    @return The Instance.
    @see CMPIBrokerFT.getInstance()
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
#      define CBGetInstance(b,c,p,pr,rc) \
                           ((b)->bft->getInstance((b),(c),(p),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Create Instance from @p inst using @p op as reference.
    @param mb Points to CMPIBroker..
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
#      define CBCreateInstance(b,c,p,i,rc) \
                             ((b)->bft->createInstance((b),(c),(p),(i),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Replace an existing Instance from @p inst using @p op as reference.
     @param mb Points to CMPIBroker..
     @param ctx Context object
     @param op ObjectPath containing namespace, classname and key components.
     @param inst Complete instance.
     @param properties Specifies which properties to set. All properties
         will be ste if NULL.
     @return Service return status.
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
#         define CBModifyInstance(b,c,p,i,pr) \
              ((b)->bft->modifyInstance((b),(c),(p),(i),(pr)))
#      else
#         define CBSetInstance(b,c,p,i,pr) \
              ((b)->bft->setInstance((b),(c),(p),(i),(pr)))
#      endif /* CMPI_VER_100 */
#   endif

#   ifdef CMPI_INLINE
/** Delete an existing Instance using @p op as reference.
     @param mb Points to CMPIBroker..
     @param ctx Context object
     @param op ObjectPath containing namespace, classname and key components.
     @return Service return status.
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
#      define CBDeleteInstance(b,c,p)  ((b)->bft->deleteInstance((b),(c),(p)))
#   endif

#   ifdef CMPI_INLINE
/** Query the enumeration of instances of the class (and subclasses) defined
    by @p op using @p query expression.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op ObjectPath containing namespace and classname components.
    @param query Query expression
    @param lang Query Language
    @param rc Output: Service return status (suppressed when NULL).
    @return Resulting eumeration of Instances.
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
#      define CBExecQuery(b,c,p,l,q,rc) \
                          ((b)->bft->execQuery((b),(c),(p),(l),(q),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** Enumerate instances associated with the Instance defined by the @p op.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op Source ObjectPath containing namespace, classname and key
        components.
    @param assocClass If not NULL, MUST be a valid Association Class name.
        It acts as a filter on the returned set of Objects by mandating that
        each returned Object MUST be associated to the source Object via an
        Instance of this Class or one of its subclasses.
    @param resultClass If not NULL, MUST be a valid Class name.
        It acts as a filter on the returned set of Objects by mandating that
        each returned Object MUST be either an Instance of
        this Class (or one of its subclasses).
    @param role If not NULL, MUST be a valid Property name.
        It acts as a filter on the returned set of Objects by mandating
        that each returned Object MUST be associated to the source Object
        via an Association in which the source Object plays
        the specified role (i.e. the name of the Property in
        the Association Class that refers to the source
        Object MUST match the value of this parameter).
    @param resultRole If not NULL, MUST be a valid Property name.
        It acts as a filter on the returned set of Objects by mandating
        that each returned Object MUST be associated to the source Object
        via an Association in which the returned Object plays the specified
        ole (i.e. the name of the Property in the
        Association Class that refers to the returned Object
        MUST match the value of this parameter).
    @param properties If not NULL, the members of the array
         define one or more Property names. Each returned
         Object MUST NOT include elements for any Properties
         missing from this list
    @param rc Output: Service return status (suppressed when NULL).
    @return Enumeration of Instances.
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
#      define CBAssociators(b,c,p,acl,rcl,r,rr,pr,rc) \
      ((b)->bft->associators((b),(c),(p),(acl),(rcl),(r),(rr),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerate ObjectPaths associated with the Instance defined by @p op.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op Source ObjectPath containing namespace,
           classname and key components.
    @param assocClass If not NULL, MUST be a valid Association Class name.
        It acts as a filter on the returned set of Objects by mandating that
        each returned Object MUST be associated to the source Object via an
        Instance of this Class or one of its subclasses.
    @param resultClass If not NULL, MUST be a valid Class name.
        It acts as a filter on the returned set of Objects by mandating that
        each returned Object MUST be either an Instance of
        this Class (or one of its subclasses).
    @param role If not NULL, MUST be a valid Property name.
        It acts as a filter on the returned set of Objects by mandating
        that each returned Object MUST be associated to the source Object
        via an Association in which the source Object plays
        the specified role (i.e. the name of the Property in
        the Association Class that refers to the source
        Object MUST match the value of this parameter).
    @param resultRole If not NULL, MUST be a valid Property name.
        It acts as a filter on the returned set of Objects by mandating
        that each returned Object MUST be associated to the source Object
        via an Association in which the returned Object
        plays the specified
        role (i.e. the name of the Property in the
        Association Class that refers to the returned Object
        MUST match the value of this parameter).
    @param rc Output: Service return status (suppressed when NULL).
    @return Enumeration of ObjectPaths.
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
#      define CBAssociatorNames(b,c,p,acl,rcl,r,rr,rc) \
       ((b)->bft->associatorNames((b),(c),(p),(acl),(rcl),(r),(rr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerates the association instances that refer to the instance defined by
    @p op.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op Source ObjectPath containing namespace,
           classname and key components.
    @param resultClass If not NULL, MUST be a valid Class name.
    It acts as a filter on the returned set of Objects
    by mandating that each returned Object MUST be
    either an Instance of this Class (or one of its
    subclasses).
    @param role If not NULL, MUST be a valid Property name.
    It acts as a filter on the returned set of Objects by mandating
    that each returned Object MUST be associated to the source Object
    via an Association in which the source Object plays
    the specified role (i.e. the name of the Property in
    the Association Class that refers to the source
    Object MUST match the value of this parameter).
    @param properties If not NULL, the members of the array
     define one or more Property names. Each returned
     Object MUST NOT include elements for any Properties
     missing from this list
    @param rc Output: Service return status (suppressed when NULL).
    @return Enumeration of ObjectPaths.
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
#      define CBReferences(b,c,p,acl,r,pr,rc) \
       ((b)->bft->references((b),(c),(p),(acl),(r),(pr),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Enumerates the association ObjectPaths that refer to the instance defined by
       @p op.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op Source ObjectPath containing namespace,
    classname and key components.
    @param resultClass If not NULL, MUST be a valid Class name.
    It acts as a filter on the returned set of Objects by mandating that
    each returned Object MUST be either an Instance of
    this Class (or one of its subclasses).
    @param role If not NULL, MUST be a valid Property name.
    It acts as a filter on the returned set of Objects by mandating
    that each returned Object MUST be associated to the source Object
    via an Association in which the source Object plays
    the specified role (i.e. the name of the Property in
    the Association Class that refers to the source
    Object MUST match the value of this parameter).
    @param rc Output: Service return status (suppressed when NULL).
    @return Enumeration of ObjectPaths.
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
#      define CBReferenceNames(b,c,p,acl,r,rc) \
       ((b)->bft->referenceNames((b),(c),(p),(acl),(r),(rc)))
#   endif


#   ifdef CMPI_INLINE
/** Invoke a named, extrinsic method of an Instance
    defined by the @p op parameter.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op ObjectPath containing namespace, classname and key components.
    @param method Method name
    @param in Input parameters.
    @param out Output parameters.
    @param rc Output: Service return status (suppressed when NULL).
    @return Method return value.
    @see CMPIBrokerFT.invokeMethod()
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
#      define CBInvokeMethod(b,c,p,m,ai,ao,rc) \
                 ((b)->bft->invokeMethod((b),(c),(p),(m),(ai),(ao),(rc)))
#   endif

#   ifdef CMPI_INLINE
/** Set the named property value of an Instance defined by the
    @p opparameter.
    @param mb Points to CMPIBroker..
    @param ctx Context object
    @param op ObjectPath containing namespace, classname and key components.
    @param name Property name
    @param value Value.
    @param type Value type.
    @return Service return status.
    @see CMPIBrokerFT.setProperty()
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
#      define CBSetProperty(b,c,p,n,v,t) \
             ((b)->bft->setProperty((b),(c),(p),(n),(CMPIValue*)(v),(t)))
#   endif

#   ifdef CMPI_INLINE
/** Get the named property value of an Instance defined by the
        @p opparameter.
        @param mb Points to CMPIBroker..
        @param ctx Context object
        @param op ObjectPath containing namespace, classname and key components.
        @param name Property name
        @param rc Output: Service return status (suppressed when NULL).
        @return Property value.
        @see CMPIBrokerFT.getProperty()
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
#      define CBGetProperty(b,c,p,n,rc) \
             (b)->bft->getProperty((b),(c),(p),(n),(rc))
#   endif


#   ifndef DOC_ONLY
   // MI factory stubs

   // Used when the MI factory function is not going to call
   // a function during initialization.
#      define CMNoHook
#   endif

/*
    -----------------  C provider factories ---------------------
*/

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
            &lt;pfx&gt;DeleteInstance and &lt;pfx&gt;ExecQuery.
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
     @par Example
     @code
         static const CMPIBroker *_broker;
         static void initialize()
        {
        ...
        }
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
            const CMPIObjectPath * ref)
        { .... }
        Functions for  InstProvEnumInstances
            InstProvGetInstance
            InstProvCreateInstance
            InstProvModifyInstance
            InstProvDeleteInstance
            Optional
            InstProvExecQuery

        CMInstanceMIStub(
            InstProv,
            CMPIInstanceProvider,
            _broker,
            initialize())
     @endcode
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

#   endif

#   ifdef DOC_ONLY
/** This macro generates the function table and initialization stub
   for an association provider. The initialization routine
   &lt;pn&gt;Create_AssociationMI
   is called when this provider module is loaded by the broker.
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
/** This macro generates the function table and initialization stub
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
/** This macro generates the function table and initialization stub
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
/** This macro generates the function table and initialization stub
   for an indication provider. The initialization
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
      */
CMPIIndicationMI *CMIndicationMIStub(
    chars pfx,
    chars pn,
    CMPIBroker * broker,
    statement hook);
#   else

#      ifdef CMPI_VER_86
#         define CMIndicationMIStubExtensions(pfx) pfx##EnableIndications, \
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
#   define CMProviderBase(pn) \
   CmpiProviderBase base##pn;

#endif // _CMPIMACS_H_
