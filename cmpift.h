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
 * @file cmpift.h
 * @brief Defines the various CMPI structures and function tables;
 * all MIs should include this header.
 *
 * This header file belongs to the Technical Standard: Systems Management:
 * Common Manageability Programming Interface (CMPI) Issue 2 Version 1.
 *
 * This header file is provided as a convenience only. In the case of any
 * discrepancy between the header file and the Technical Standard
 * (incorporating any subsequent Technical Corrigenda), the Technical Standard
 * shall be definitive.
 */

#ifndef _CMPIFT_H_
#define _CMPIFT_H_

#include "cmpidt.h"
#include "cmpios.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief CMPIBroker object.
 *
 * The CMPIBroker structure is the anchor object of the MB (Management Broker,
 * also known as CIMOM). It provides access to the function tables for MB
 * services and is passed to every MI function.
 */
struct _CMPIBroker {

    /**
     * Opaque pointer to MB-specific implementation data for the MB.
     */
    const void* hdl;

    /**
     * Pointer to function table for some MB services.
     */
    const CMPIBrokerFT* bft;

    /**
     * Pointer to function table for MB factory and miscellaneous services.
     */
    const CMPIBrokerEncFT* eft;

    /**
     * Pointer to function table for MB operating system encapsulation services.
     */
    const CMPIBrokerExtFT* xft;

#ifdef CMPI_VER_200

    /**
     * Pointer to function table for MB memory enhancement services.
     */
    const CMPIBrokerMemFT* mft;

#endif // CMPI_VER_200

};

/**
 * @brief Function table for some MB services of
 * [CMPIBroker object](@ref _CMPIBroker).
 *
 * This function table provides
 * @link broker-thread-registration MB thread registration services @endlink,
 * @link broker-indications MB indications services @endlink, and
 * @link broker-client MB client services ("up-calls") @endlink.
 */
struct _CMPIBrokerFT {

    /**
     * MB capabilities.
     *
     * See the @link def-mb-capabilities definition of test masks for MB
     * capabilities @endlink.
     */
    unsigned int brokerCapabilities;

    /**
     * CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     *
     * Note: This is not the version of the MB.
     */
    CMPIVersion brokerVersion;

    /**
     * Informal MB-specific name for this MB.
     */
    const char* brokerName;

    /**
     * @defgroup broker-thread-registration MB thread registration services
     * @{
     */

    /** @brief prepare the MB to accept a new thread that will use
     *         MB functions
     * This function prepares the CMPI run time system to accept
     a thread that will be using CMPI services. The returned
     CMPIContext object must be used by the subsequent attachThread()
     and detachThread() invocations.
     @param mb Pointer to the broker.
     @param ctx Old Context object
     @return New Context object to be used by thread to be attached.
     */
    CMPIContext* (*prepareAttachThread) (const CMPIBroker* mb,
            const CMPIContext* ctx);

    /** @brief inform the MB that the current thread will begin
     *         using MB functions
     * This function informs the CMPI run time system that the current
     thread with Context will begin using CMPI services.
     @param mb Pointer to the broker.
     @param ctx Context object returned by a prior call to
         prepareAttachThread()
     @return Service return status.
     */
    CMPIStatus (*attachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /** @brief inform the MB that the current thread will no longer
               use MB functions
     *
     * This function informs the CMPI run time system that the current thread
     will not be using CMPI services anymore. The Context object will be
     freed during this operation.
     @param mb Pointer to the broker.
     @param ctx Context object retyrned by a prior call to
         prepareAttachThread()
     @return Service return status.
     */
    CMPIStatus (*detachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

     /**
     * @}
     * @defgroup broker-indications MB indications services
     * @{
     */

    /** @brief request delivery of an indication.

     This function requests delivery of an Indication. The MB will
     locate pertinent subscribers and notify them about the event.
     This function shall be suppored by the MB if the Indications
     capability is available otherwise it shall not be supported.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param ns pointer to a string specifying the name of the origin
         namespace of the indication.
     @param ind pointer to a CMPIInstance containing the indication
         instance. Any instance path in the instance will be ignored
         by the MB ignored.
     @return Service return status.
     */
    CMPIStatus (*deliverIndication) (const CMPIBroker* mb,
            const CMPIContext* ctx, const char* ns, const CMPIInstance* ind);

     /**
     * @}
     * @defgroup broker-client MB client services ("up-calls")
     * @{
     */

    /** @brief enumerate instance paths of the instances of a given
            class (and its subclasses).
     
     Enumerate Instance Names of the class (and subclasses) defined by
         &lt;op&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param classPath CMPIObjectPath containing namespace
         and classname* components.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns pointer to a new* CIMEnumeration
         object containing CMPIObjectPaths objects that represent the
         enumerated instance paths. The new object will be released
         automatically by the MBB. If not successfull NULL will be returned.
     */
    CMPIEnumeration* (*enumerateInstanceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            CMPIStatus* rc);

    /** @brief get a given instance.
     *
     * Get Instance using &lt;instPath&gt; as reference. Instance
     structure can be controled using the CMPIInvocationFlags
     entry in &lt;ctx&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname and*
     *        key* components.
     @param properties If not NULL, the members of the array define
     one or more Property names. Each returned Object MUST NOT
     include elements for any Properties missing from this list
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, pointer to a new CMPIInstance. The new*
     *       object will be released automatically by the MB. If not
     *       successful NULL will be returned.
     */
    CMPIInstance* (*getInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char** properties,
            CMPIStatus* rc);

    /* @brief create an instance of a given class.
     
     MI function creates an instance of a given class in the namespace
     of that class, by creating the underlying managed elements.
     
     Creates instance from &lt;inst&gt; using &lt;op&gt; as reference.
     
     @param mb Pointer to the broker.
     @param ctx &lt;CMPIContext&gt; object containing the context data for
         the invocation
     @param op &lt;CMPIObjectPath&gt; containing namespace, classname and
         key components.
     @param inst Complete instance.
     @param rc Output: Service return status (suppressed when NULL).
     @return The assigned instance reference.
     */
    CMPIObjectPath* (*createInstance) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const CMPIInstance* inst, CMPIStatus* rc);

    /** TODO: Sync description with spec.
       Replace an existing Instance from &lt;inst&gt; using
       &lt;op&gt; as reference.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op ObjectPath containing namespace, classname and key components.
     @param inst Complete instance.
     @return Service return status.
     */
    CMPIStatus (*modifyInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* op, const CMPIInstance* inst,
            const char** properties);

    /** TODO: Sync description with spec.
     * Delete an existing Instance using &lt;op&gt; as reference.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op ObjectPath containing namespace, classname and key components.
     @return Service return status.
     */
    CMPIStatus (*deleteInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* op);

    /** TODO: Sync description with spec.
     * Query the enumeration of instances of the class (and subclasses) defined
     by &lt;op&gt; using &lt;query&gt; expression.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op ObjectPath containing namespace and classname components.
     @param query Query expression
     @param lang Query Language
     @param rc Output: Service return status (suppressed when NULL).
     @return Resulting eumeration of Instances.
     */
    CMPIEnumeration* (*execQuery) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* query, const char* lang, CMPIStatus* rc);

    /** @brief enumerate the instances of a given class (and its
     *         subclasses).
     *
     * Enumerate Instances of the class (and subclasses) defined by &lt;op&gt;.
     Instance structure and inheritance scope can be controled using the
     CMPIInvocationFlags entry in &lt;ctx&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param classPath ObjectPath containing namespace and classname
         components.
     @param properties If not NULL, the members of the array define one or more
     property names. Each returned Object MUST NOT include elements
     for any Properties missing from this list.  The end of the
     array is identified by a NULL pointer. If NULL all properties
     will be returned.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful a pointer to a new CMPIEnumerationObject*
         will be returned containing CMPIInstance objects that
         represent the enumerated instances. The new object will be
         released automatically by the MB.  If not successful NULL
         will be returned.
     */
    CMPIEnumeration* (*enumerateInstances) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const char** properties, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Enumerate instances associated with the Instance defined by the
     * &lt;op&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op Source ObjectPath containing namespace, classname and key
     components.
     @param assocClass If not NULL, MUST be a valid Association Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be associated to the source Object via an
     Instance of this Class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param resultRole If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the returned Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers to
     the returned Object MUST match the value of this parameter).
     @param properties If not NULL, the members of the array define one or more
     Property names. Each returned Object MUST NOT include elements for any
     Properties missing from this list.
     @param rc Output: Service return status (suppressed when NULL).
     @return Enumeration of Instances.
     */
    CMPIEnumeration* (*associators) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* assocClass, const char* resultClass, const char* role,
            const char* resultRole, const char** properties, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Enumerate ObjectPaths associated with the Instance defined by &lt;op&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op Source ObjectPath containing namespace, classname and key
     components.
     @param assocClass If not NULL, MUST be a valid Association Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be associated to the source Object via an
     Instance of this Class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param resultRole If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the returned Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers to
     the returned Object MUST match the value of this parameter).
     @param rc Output: Service return status (suppressed when NULL).
     @return Enumeration of ObjectPaths.
     */
    CMPIEnumeration* (*associatorNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* assocClass, const char* resultClass, const char* role,
            const char* resultRole, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     Enumerates the association instances that refer to the instance defined
     by &lt;op&gt;.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op Source ObjectPath containing namespace, classname and key
     components.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param properties If not NULL, the members of the array define one or more
     Property names. Each returned Object MUST NOT include elements for any
     Properties missing from this list/
     @param rc Output: Service return status (suppressed when NULL).
     @return Enumeration of ObjectPaths.
     */
    CMPIEnumeration* (*references) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, const char** properties,
            CMPIStatus* rc);

    /** TODO: Sync description with spec.
     Enumerates the association ObjectPaths that refer to the
     instance defined by &lt;op&gt;.*
     @param mb Pointer to the broker.
     @param ctx Context object
     @param op Source ObjectPath containing namespace, classname and key
     components.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param rc Output: Service return status (suppressed when NULL).
     @return Enumeration of ObjectPaths.
     */
    CMPIEnumeration* (*referenceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Invoke a named, extrinsic method of an Instance
     defined by the &lt;op&gt; parameter.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param objPath ObjectPath containing namespace, classname and key
     components.
     @param method Method name
     @param in Input parameters.
     @param out Output parameters.
     @param rc Output: Service return status (suppressed when NULL).
     @return Method return value.
     */
    CMPIData (*invokeMethod) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* objPath, const char* method,
            const CMPIArgs* in, CMPIArgs* out, CMPIStatus* rc);

    /** @brief set a property of a given instance (Deprecated)
     * Set the named property value of an Instance defined by the
     &lt;instPath&gt; parameter.*
     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname and*
     *        key* components.
     @param name Property name
     @param value Value.
     @param type Value type.
     @return Service return status.
     */
    CMPIStatus (*setProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief get the named property of a given
               instance(Deprecated).
     *
     * Get the named property value of an Instance defined by the
     &lt;instPath&gt; parameter.*
     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname*
     *        and* key components.
     @param name Property name
     @param rc Output: Service return status (suppressed when NULL).
     @return If successfulProperty value. If not successful*
     *       CMPIData.state will have CMPI_BadValue flag set to true
     */
    CMPIData (*getProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name, CMPIStatus* rc);

     /**
     * @}
     */

};

/**
 * @brief Function table for MB factory and miscellaneous services of
 * [CMPIBroker object](@ref _CMPIBroker).
 *
 * This function table provides factory services for the CMPI data types, and
 * functions for test, conversion, tracing and logging.
 */
struct _CMPIBrokerEncFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

     /**
     * @defgroup brokerenc-factory MB factory services
     * @{
     */

    /** @brief create a new CMPIInstance object initialized to a
     *         given instance path
     *
     * Instance factory service that creates a new CMPIInstance
     * object. The new object should nav eno properties. The purpose
     * of class-defined derault values for properties is to act as
     * defaults for unspecified input properties when a client
     * creates an instance, not to act as defualts for not explicity
     * set properties when a client retrieves an instance.
     @param mb Pointer to the broker.
     @param instPath ObjectPath containing namespace and classname.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created instance. if*
     *       not successful NULL will be returned.
     */
    CMPIInstance* (*newInstance) (const CMPIBroker* mb,
            const CMPIObjectPath* instPath, CMPIStatus* rc);

    /** @brief create a new CMPIObjectPath initialized to a given
     *         namespace and class name
     *
     * ObjectPath factory service that creates a new CMPIObjectPath.
     @param mb Pointer to the broker.
     @param ns Namespace
     @param cn Classname.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created*
     *       CMPIObjectPath. If not successful returns NULL.
     */
    CMPIObjectPath* (*newObjectPath) (const CMPIBroker* mb, const char* ns,
            const char* cn, CMPIStatus* rc);

    /** @brief create a new CMPIArgs object initialized to have no
     *         method parameters
     * Args container factory service to create a new CMPIArgs
     * object with no method parameters
     @param mb Pointer to the broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns the newly created CMPIArgs
     *       object. If not successful NULL will be returned.
     */
    CMPIArgs* (*newArgs) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief create a new CMPIString object initialized from a
     *         C-language string.
     * String container factory service that creates a new
     * CMPIString.
     @param mb Pointer to the broker.
     @param data String data
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created CMPIString. If*
     *       not successful returns NULL.
     */
    CMPIString* (*newString) (const CMPIBroker* mb, const char* data,
            CMPIStatus* rc);

    /** @brief create a new CMPIArray object of a given fixed array
     *         size for a given type of elements.
     * Array container factory service returns a new CMPIArray
     * object. Once created, the size of the array is fixed and all
     * elements are of the same time. The array in initialized to
     * ahve no array elements.
     @param mb Pointer to the broker.
     @param size Number of elements
     @param type Element type
     @param rc Output: Service return status (suppressed when NULL).
     @return If successfull returns thhe newly created Array. If not*
     *       successful returns NULL.
     */
    CMPIArray* (*newArray) (const CMPIBroker* mb, CMPICount size,
            CMPIType type, CMPIStatus* rc);

    /** @brief create a new CMPIDataTime object with current date
     *         and time
     * DateTime factory service. Initialized with the current time
     * of day.
     @param mb Pointer to the broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created DateTime. If*
     *       not successful returns NULL.
     */
    CMPIDateTime* (*newDateTime) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief create a new CMPIdateTime object initialized to a
     *         specific alue
     * DateTime factory service. Initialized from &lt;binTime&gt;.
     @param mb Pointer to the broker.
     @param binTime Date/Time definition in binary format in microsecods
     starting since 00:00:00 GMT, Jan 1,1970.
     @param interval Wenn true, defines Date/Time definition to be an interval
     value
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created DateTime. If*
     *       not succesful, returns NULL.
     */
    CMPIDateTime* (*newDateTimeFromBinary) (const CMPIBroker* mb,
            CMPIUint64 binTime, CMPIBoolean interval, CMPIStatus* rc);

    /** @brief create a new CMPIDateTime object initialized from
     *         input
     * DateTime factory service. Is initialized from &lt;utcTime&gt;.
     @param mb Pointer to the broker.
     @param datetime Date/Time definition in CIM datetime string format.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created DateTime. If*
     *       not successful returns NULL.
     */
    CMPIDateTime* (*newDateTimeFromChars) (const CMPIBroker* mb,
            const char* datetime, CMPIStatus* rc);

    /** @brief create a new CMPISelectExp object initialized from a
     *         select expression
     * SelectExp factory service. TODO
     @param mb Pointer to the broker.
     @param query The select expression.
     @param lang The query language.
     @param projection Output: Projection specification (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created SelectExp. If*
     *       not successful returns NULL.
     */
    CMPISelectExp* (*newSelectExp) (const CMPIBroker* mb, const char* query,
            const char* lang, CMPIArray** projection, CMPIStatus* st);

     /**
     * @}
     * @defgroup brokerenc-misc MB miscellaneous services (test,
     * conversion, tracing and logging) @{
     */
// TODO next one was complete change. confirm KS
    /** @brief determine if a class path is of a specific class or
     *         its subclasses
     * Function to determine whether a &lt;className&gt: is of
     &lt;classPath&gt; or any of &lt;classPath&gt; subclasses.*
     @param mb Pointer to the broker.
     @param classPath The class path (namespace and classname components).
     @param char* className
     @param rc Output: Service return status (suppressed when NULL).
     @return True if test successful.
     */
    CMPIBoolean (*classPathIsA) (const CMPIBroker* mb,
        const CMPIObjectPath* classPath, const char* className,
        CMPIStatus* rc);

    /** @brief convert CMPIEncapsulated data type object int a
     *         string representation.
     *
     * Attempts to transforms an CMPI object to a broker specific
     * string format. Intended for debugging purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns CMPIString from representation*
     *       of* &lt;object&gt;. If not successful returns NULL.
     */
    CMPIString* (*toString) (
        const CMPIBroker* mb,
        const void* object,
        CMPIStatus* rc);

    /** @brief tests whether a CMPI encapsulated data type object is
     *     of a specified CMPI type.
     *
     * Verifies whether &lt;object&gt; is of CMPI type &lt;type&gt;.
     Intended for debugging purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param type A string specifying a valid CMPI Object type
     ("CMPIInstance", "CMPIObjectPath", etc).
     @param rc Output: Service return status (suppressed when NULL).
     @return True if test successful; otherwise false.
     */
    CMPIBoolean (*isOfType) (
        const CMPIBroker* mb,
        const void* object,
        const char* type, CMPIStatus* rc);

    /** @brief get the type name of a CMPI ensapsulated data type
     *         object.
     *
     * Retrieves the CMPI type of &lt;object&gt;. The returned
     * CMPIString object shall not be explicitly released by the MI,
     * because it may be an internal object of the CMPI encapsulated
     * data type object which will be released along with that
     * object, or a new object created by the MB which will be
     * released automatically by the MB. Intended for debugging
     * purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns CMPI object type. Otherwise*
     *       returns NULL.
     */
    CMPIString* (*getType) (
        const CMPIBroker* mb,
        const void* object,
        CMPIStatus* rc);

    /** @brief get a translated MB implementation specific message
     *         text (Deprecated)
     *
     * Retrieves translated message defined by &lt;msgId&gt;
     * Use CMPIBrokerEncFT.getMessage2() in place of this function.
     @param mb Pointer to the broker.
     @param msgId The message identifier.
     @param defMsg The default message. Used when message*
     *             translation is not supported
     @param rc Output: Service return status (suppressed when NULL).
     @param count The number of message substitution values.
     @return if successful returns the translated message.Otherwisereturns
         NULL.
     */
    CMPIString* (*getMessage) (
        const CMPIBroker* mb,
        const char* msgId,
        const char* defMsg,
        CMPIStatus* rc,
        CMPICount count, ...);

    /** @brief log a diagnostic message
     *
     * This function logs a diagnostic message defined by the input
     * arguments. It exists to provide a mechanism to MIs to
     * provider information about errors, status, etc.
     * This function is supported by the MB if the Logging
     * capability is available.@param mb The mb argument points to a
     * CMPIBroker structure.
     @param severity  The level argument describes the level of
         logmessage. Levels are defined in Section 4.9.
     @param id The component argument, if not NULL, is the component ID.
     @param text  The text argument, if not NULL, is the message text to be
     logged.
     @param string The string argument, if not NULL, is the message text to be
     logged. string will be ignored when text is not NULL.
     @return Service return status.
     */
    CMPIStatus (*logMessage) (
        const CMPIBroker* mb,
        int severity,
        const char* id,
        const char* text,
        const CMPIString* string);

    /** @brief trace a diagnostic message with a specific trace
     *         level and component definition.
     * Logs a trace entry. Intended for debugging purposes.
     * This function is supported by the MB if the Tracing
     * capability is available.
     @param mb The mb argument points to a CMPIBroker structure.
     @param level  The level argument describes the level of log message.
         Levels are defined in Section 4.9.
     @param component The component argument, if not NULL, is*
     *                the*implementation specific component ID.
     @param text  The text argument, if not NULL, is the message text to be
         output.
     @param string The string argument, if not NULL, is the message text to
        be output. string will be ignored when text is not NULL.
     @return Service return status.
     */
    CMPIStatus (*trace) (
        const CMPIBroker* mb,
        CMPILevel level,
        const char* component,
        const char* text,
        const CMPIString* string);

#ifdef CMPI_VER_200

     /**
     * @}
     * @addtogroup brokerenc-factory
     * @{
     */

    /* @brief create a new CMPIError object initialized with
     *         attributes defined by the input parameters
     * Error factory service.
     @param mb Pointer to the broker.
     @param owner A string specifying the value for the OwningEntity attribute
     @param msgID A string which uniquely identifies the*
     *   MessageID attribute of the CMPIError object For a description of
     *   the MessageID attribute, see the description of the
     *   MessageID property in the CIM_Error class in the CIM
     *   Schema. If the error message is defined in a DMTF message
     *   registry, the string value of the msgID argument shall be
     *   the message ID defined for the message in the registry
     *   (that is, the concatenation of the values of the PREFIX and
     *   SEQUENCE_NUMBER attributes of the MESSAGE_ID element for
     *   the message).
     @param msg A string which represenst the formatted message.
     @param sev The percieved severity of the error.
     @param pc The probably cause of this error
     @param cimStatusCode CIM status code to be associated with this error.
     @param rc Service return status.
     @return The newly created Error.
     */
    CMPIError* (*newCMPIError) (
        const CMPIBroker* mb,
        const char* owner,
        const char* msgID,
        const char* msg,
        const CMPIErrorSeverity sev,
        const CMPIErrorProbableCause pc,
        const CMPIrc cimStatusCode,
        CMPIStatus* rc);

     /**
     * @}
     * @addtogroup brokerenc-misc
     * @{
     */

    /** @brief open a message file and return a handle to the file
     * Opens a message file.
     @param mb pointer to the broker
     @param msgFile The message file identifier.
     @param msgFileHandle Output: The handle representing the open message file.
     @return Service return status.
     */
    CMPIStatus (*openMessageFile) (
        const CMPIBroker* mb,
        const char* msgFile,
        CMPIMsgFileHandle* msgFileHandle);

    /** @brief cloase a message file.
     *
     * Closes a message file previously opened by
     * CMPIBrokerEncFt.openMessageFile(). If the message file handle
     * is NULL, the message file is not closed and this is not
     * considered a failure.
     @param mb Broker this pointer
     @param msgFileHandle The handle representing the open message file.
     @return Service return status.
     */
    CMPIStatus (*closeMessageFile) (
        const CMPIBroker* mb,
        const CMPIMsgFileHandle msgFileHandle);

    /** @brief get a translated message text from an open message
     *         file by message ID
     *
     * Retrieves translated message.
     @param mb Broker this pointer
     @param msgId The message identifier.
     @param msgFileHandle The handle representing the open message*
     *   file that was returned by a call to OpenMessageFile(). If
     *   the MB does not support message files the handle is NULL.
     @param defMsg The default message that will be used if the MB*
     * does not support message files or the the message ID cannot
     * be located.
     * The message template string specified in the defMsg argument
     * may contain up to ten message insert triggers ($0 through
     * $9). Each insert trigger will be expanded; that is, the
     * insert trigger string will be replaced with a string
     * representation of the value of the corresponding insert pair
     * in the variable arguments of this function. The MI is not
     * affected when the MB does not support message files or when
     * the message ID cannot be located, because this function still
     * succeeds and returns a message with expanded message insert
     * triggers.
     @param rc Output: Service return status (suppressed when NULL).
     @param count The number of message substitution values.
     @return If successful returns the translated message; otherwise*
     *    the default message template without any insert triggers
     *    expanded is returned.
     */
    CMPIString* (*getMessage2) (
        const CMPIBroker* mb,
        const char* msgId,
        const CMPIMsgFileHandle msgFileHandle,
        const char* defMsg,
        CMPIStatus* rc,
        CMPICount count, ...);

#endif // CMPI_VER_200

#ifdef CMPI_VER_210

     /**
     * @}
     * @addtogroup brokerenc-factory
     * @{
     */

    /** @brief create a new CIMPropertyList object initialized to a
     *         list of property names
     *
     * This function creates a new CMPIPropertyList that is
     * initialized to a list of property names specified by
     * &lt;properties&gt;
     * @param mb pointer to the broker
     * @param properties pointer to the first entry of a
     *                   NULL-terminated array of pointers to C
     *                   strings that specify the property names for
     *                   the property list.
     * @param rc Output: Service return status (suppressed when
     *           NULL).
     * @return KS_TODO
     */
    CMPIPropertyList* (*newPropertyList) (const CMPIBroker* mb,
            const char** properties, CMPIStatus* rc);

    /** @brief create a new CMPIString object from a C-language
     *         string in a specific codepage
     *
     * @param mb TODO
     * @param data
     * @param cpid
     * @param rc
     * @return
     */
    CMPIString* (*newStringCP) (const CMPIBroker* mb, const char* data,
            const CMPICodepageID cpid, CMPIStatus* rc);

    /** @brief  create a new CMPIEnumerationFilter object
     *          initialized with a filter query
     *
     *  create a new CMPIEnumerationFilter object initialized with
     *  &lt;filterquery&gt; argument if the
     *  &lt;filterQueryLanguage&gt; argument is valid. if the
     *  &lt;filterquery&gt; is NULL the new object will be set to do
     *  no filtering
     * @param mb TODO
     * @param filterQueryLanguage
     * @param filterQuery
     * @param rc
     * @return
     */
    CMPIEnumerationFilter* (*newEnumerationFilter) (const CMPIBroker* mb,
            const char* filterQueryLanguage, const char* filterQuery,
            CMPIStatus* rc);
     /**
     * @}
     */

#endif // CMPI_VER_210

};

struct timespec;

/**
 * @brief Function table for MB operating system encapsulation services of
 * [CMPIBroker object](@ref _CMPIBroker).
 *
 * This function table provides operating system encapsulation services, such as
 * library name resolution services and services for POSIX-conformant threads,
 * mutexes, and conditions.
 */
struct _CMPIBrokerExtFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

     /**
     * @defgroup brokerext-library MB operating system encapsulation
     * services for library name resolution @{
     */

    /* @brief resolve a generic load library name to its file name
     * This function complements a generic dynamic library name to its
         OS-dependent native format.
     @param filename Pointer to the generic library name,
     @return The returned char* pointer points to the complemented library
         name in native OS format.
     Space for this string has been obtained using malloc() and must be
         released using free() by the caller.
     In case no storage could be obtained for the complemented library
         name, NULL will be returned.
     */
    char* (*resolveFileName) (const char* filename);

     /**
     * @}
     * @defgroup brokerext-thread MB operating system encapsulation
     * services for POSIX-conformant threads @{
     */

    /** @brief Start a new thread.

     Start a new thread using the POSIX threading semantics.
     @param start Pointer to the function to be started as a thread.
     @param parm Pointer to argument(s) to be passed to that function..
     @param Detached If not zero, defines that the thread should run in
         detached mode. In detached mode, termination of the thread that
         called this function does not cause the new thread to be canceled.
         See IEEE 1003.1 for details on detached mode.
     @return If successful, the handle of the started thread will be returned.
         If not successful, NULL will be returned.

     */
    CMPI_THREAD_TYPE (*newThread)
            (CMPI_THREAD_RETURN (CMPI_THREAD_CDECL* start)(void*),
            void* parm, int detached);

    /** @brief wait until the specified thread ends.

     Suspends the current thread until the specified thread ends using
         the POSIX threading semantics.
     @param thread The thread ID of the thread waiting for completion.
     @param retval Pointer to the return value of the thread.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     */
    int (*joinThread) (CMPI_THREAD_TYPE thread, CMPI_THREAD_RETURN* retval);

    /** @brief cause the current thread to exit with the passed-in return code,

    Causes the current thread to exit with the passed in return
       code using POSIX threading semantics.

    The current thread can also exit by simply returning from its thread
     function; the purpose of the &lt;CMPIBrokerExtFT.exitThread()&gt; function
     is to make premature returns more convenient.
     @param return_code Is the return code that should be used for the thread.
     @return The function never returns, regardless of whether it is
         successful or encounters errors. .
     */
    int (*exitThread) (CMPI_THREAD_RETURN return_code);

    /** @brief cancel a running thread.

     Cancel the thread using the POSIX threading semantics.
     @param thread  The thread to be canceled.
     @return Completion code as defined by POSIX threading semantics
     (pthread_cancel)
     */
    int (*cancelThread) (CMPI_THREAD_TYPE thread);

    /** @brief  suspend execution of the current thread for a
                specified duration.

     Suspends the execution of the current thread for the specified duration.
     @param msec The suspend duration in milliseconds.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     */
    int (*threadSleep) (CMPIUint32 msec);

    /** @brief call a function once for a given once-object.

       Executes the specified function procedure only once during the lifetime
           of the thread. The once-object is an integer that initially
           shall have a value of zero. The first call to
           &lt;CMPIBrokerExtFT.threadOnce()&gt; with an initialized
           once-object will call the specified function. On return from
           &lt;CMPIBrokerExtFT.threadOnce()&gt;, it is guaranteed that the
           specified function has completed, and that the once-object has
           been updated to indicate that. Subsequent calls to
           &lt;CMPIBrokerExtFT.threadOnce()&gt; by any thread within the
           process with that once-object will not call the specified function.
     @param once Pointer to the &lt;int&gt; once object.
     @param function The function to be called
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     */
    int (*threadOnce) (int* once, void (*function) (void));

    /** @brief create a POSIX threading-conformant thread key for accessing
       the thread local store.

     Create a POSIX threading conformant thread key. This key can be used as
         a key to access the thread local store.
     @param key Pointer to the thread key to be returned.
     @param cleanup Function to be invoked during thread local store cleanup.
     @return Completion code as defined by POSIX threading semantics.
     */
    int (*createThreadKey) (CMPI_THREAD_KEY_TYPE* key, void (*cleanup)(void*));

    /** @brief Destroy a thread key for accessing the thread local store

     Destroy a POSIX threading conformant thread key for accessing the
         thread local store.
     @param key The thread key to be destroyed.
     @return If successful, zero will be returned.
     */
    int (*destroyThreadKey) (CMPI_THREAD_KEY_TYPE key);

    /** @brief  get a data pointer from the thread local store using a
       thread key.

     Return data from the thread local store using a thread key.
     @param key The key to be used to retrieve the data pointer.
     @return If successful, the data pointer will be returned.
         If not successful, NULL will be returned.
     */
    void* (*getThreadSpecific) (CMPI_THREAD_KEY_TYPE key);

    /** @brief set a data pointer in the thread local store using a thread key.

     Set a data pointer in the therad local store using a POSIX
         threading-conformant  thread key.
     @param key The key to be used.
     @param value The data pointer that is stored in the thread local store.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in <errno.h>, specifically for the
         &lt;pthread_setspecific()&gt; function; both are defined in
         IEEE 1003.1.
     */
    int (*setThreadSpecific) (CMPI_THREAD_KEY_TYPE key, void* value);

     /**
     * @}
     * @defgroup brokerext-mutex MB operating system encapsulation services
     * for POSIX-conformant mutexes @{
     */

    /** @brief create a POSIX thread conformant  mutex.
     
     Create a POSIX threading conformant recursive mutex.
     
     The mutex that is created shall exhibits the following behavior:
      
     <ul> 
     <li>For locking a locked mutex: A thread that holds a lock on a
     mutex and attempts to lock that mutex again without first
     unlocking it shall* succeed in locking the mutex. Multiple
     locks of the mutex (by the* same thread) shall require the same
     number of unlocks (by that same* thread) to release the mutex
     before another thread can acquire the mutex.
     
     <li>For unlocking an unlocked mutex: A thread attempting to
     unlock a mutex that is not locked by that thread (that is, the
     mutex is either entirely unlocked or locked by another thread)
     shall fail in unlocking the mutex.
     </ul> 

     @param opt For future use. It should be ignored by the MB, and
         MIs should pass a value of 0
     
     @return If successful, the handle of the new mutex will be returned.
         If not successful, NULL will be returned.
     */
    CMPI_MUTEX_TYPE (*newMutex) (int opt);

    /* @brief destroy a POSIX threading-conformant mutex. (Deprecated)
     
     Destroy a POSIX threading conformant mutex. This function is deprecated
     because it does not indicate whether it succeeded or failed.
     Use &lt;CMPIBrokerExtFT.destroyMutex2()&gt; instead
     @param mutex The mutex to be destroyed.
     */
    void (*destroyMutex) (CMPI_MUTEX_TYPE mutex);

    /* @briefLock a POSIX threading-conformant mutex. (Deprecated)
     
     If the mutex is locked by another thread, the current thread is suspended
     until the lock is granted. The behavior in case the mutex is already
     locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;.
     
     This function is deprecated because it does not indicate whether it
     succeeded or failed. Use CMPIBrokerExtFT.lockMutex2() instead. (Deprecated)

     @param mutex The mutex to be locked.
     */
    void (*lockMutex) (CMPI_MUTEX_TYPE mutex);

    /** @brief unlock a POSIX threading-conformant mutex (Deprecated)
                                          .
     Release control of the mutex. The behavior in case the mutex is not
     locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;.
     
     This function is deprecated because it does not indicate whether it
     succeeded or failed. Use &lt;CMPIBrokerExtFT.unlockMutex2()&gt;
     instead. (Deprecated)

     @param mutex The mutex to be unlocked.
     */
    void (*unlockMutex) (CMPI_MUTEX_TYPE mutex);

     /**
     * @}
     * @defgroup brokerext-condition MB operating system encapsulation
     * services for POSIX-conformant conditions @{
     */

    /** @brief  Create a new condition variable.
     
     Create a new POSIX threading-conformant condition variable
     @param opt for future use. It should be ignored by the MB, and MIs
     should pass a value of 0..
     @return If successful, handle of newly created condition*
         variable. If not successful, NULL
     */
    CMPI_COND_TYPE (*newCondition) (int opt);

    /** @brief Destroy a condition variable (Deprecated)
     
     Destroy a POSIX threading conformant condition variable(Deprecated).
     
     Deprecated because it does not indicate whether it succeeded
     or failed. Use CMPIBrokerExtFt.destroyCondition2() instead.
     @param cond The condition variable to be destroyed.
     */
    void (*destroyCondition) (CMPI_COND_TYPE cond);

    /** @brief Wait until condition is signalled.
     
     This function waits until he condition has been signalled. If the
     condition variable has been signalled already, the function returns
     immediately; otherwise, it suspends the current thread to wait for
     the signal and then returns.
     @param cond  The handle of the condition variable to be used.
     @param mutex  The handle of a locked mutex guarding this
         condition variable.
     @return If successful, zero will be returned.
        If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_cond_wait()&gt; function; both are defined in
            IEEE 1003.1.
     */
    int (*condWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex);

    /** @brief Wait until the condition is signalled using a timeout
               value.
     
     This function waits until a POSIX threading-conformant condition
         variable is signalled. If the condition variable has been signalled
         already, the function returns immediately; otherwise, it suspends the
         current thread to wait for the signal and then returns. The function
         returns when the timeout expires before the condition is signalled.
     
     @param cond Specifies the handle of the condition variable to be used.
     @param mutex Specifies the handle of a locked mutex guarding*
     *            thiscondition variable.
     @param wait Specifies the timeout value.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in &lt;<errno.h>&gt;, specifically for the
         &lt;pthread_cond_timedwait()&gt; function; both are defined in
         IEEE 1003.1.
     */
    int (*timedCondWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex,
            struct timespec* wait);

    /* @brief Sends a signal to a condition variable.
     
     Sends a signal to a POSIX threading-conformant condition variable.
     @param cond Specifies the handle of the condition variable to
                 send thesignal.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in &lt;<errno.h>&gt;, specifically for the
         &lt;pthread_cond_signal()&gt; function; both are defined in
         IEEE 1003.1.
    */
    int (*signalCondition) (CMPI_COND_TYPE cond);

#ifdef CMPI_VER_210

     /**
     * @}
     * @addtogroup brokerext-mutex
     * @{
     */

    /** @brief destroy a POSIX threading-conformant mutex.
     
     Destroy a POSIX threading conformant mutex.
     @param mutex The mutex to be destroyed. This function superceedes the
     original &lt;destroyMutex&gt;.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_destroy()&gt; function; both are defined in
            IEEE 1003.1.
     */
    int (*destroyMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Lock a POSIX threading-conformant mutex.
     
     Lock a POSIX threading conformant mutex. If the mutex is locked by another
     thread, the current thread is suspended until the lock is granted.
     The behavior in case the mutex is already locked by the current thread
     is defined in the description of &lt;CMPIBrokerExtFT.newMutex()&gt;.

     This function superceedes the original &lt;lockMutex&gt;.
     @param mutex The mutex to be locked.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_lock()&gt; function; both are defined in
            IEEE 1003.1.
     */
    int (*lockMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Unlock a POSIX threading-conformant mutex.
     
     Unlock a POSIX threading conformant mutex. The behavior in case the mutex
     is not locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;. 

     This function superceedes the original &lt;unlockMutex&gt;.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_lock()&gt; function; both are defined in
            IEEE 1003.1.
     */
    int (*unlockMutex2) (CMPI_MUTEX_TYPE mutex);

     /**
     * @}
     * @addtogroup brokerext-condition
     * @{
     */

    /* @brief function destroys a POSIX threading-conformant ondition variable.
     
     This function function destroys a POSIX threading-conformant condition
     variable.
     
     This function superceedes the original &lt;unlockMutex&gt;.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_cond_destroy()&gt; function; both are defined in
            IEEE 1003.1.
     */
    int (*destroyCondition2) (CMPI_COND_TYPE cond);

     /**
     * @}
     */

#endif // CMPI_VER_210

};

#ifdef CMPI_VER_200

/**
 * @brief Function table for MB memory enhancement services of
 * [CMPIBroker object](@ref _CMPIBroker).
 *
 * This function table provides memory management services.
 */
struct _CMPIBrokerMemFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

     /**
     * @defgroup brokermem-memory MB memory enhancement services
     * @{
     */

    /** @brief mark a new object lifecycle level for subsequent
           newly created CMPI encapsulated data type objects.
     
     Invoking this function marks a new object lifecycle level for the
     calling MI. Subsequent newly created CMPI encapsulated data type objects
     in that MI will be associated with that new object lifecycle level.
     A subsequent invocation of the &lt;CMPIBrokerMemFT.release()&gt; function
     with the returned &lt;CMPIGcStat&gt; pointer will release only the
     objects associated with that object lifecycle level.
     
     The &lt;mark()&gt; and &lt;release()&gt; function calls may be stacked.
     
     Stacked object lifecycle levels shall not overlap.

     @param mb The broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to a &lt;CMPIGcStat&gt; structure will be
     returned, for use with the &lt;CMPIBrokerMemFT.release()&gt; function.
     
     If not successful, NULL will be returned.

     */
    CMPIGcStat* (*mark) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Release all CMPI encapsulated data type objects created at the
       specified object lifecycle level, and remove that level.
     
     This function releases all CMPI encapsulated data type objects created
     other than with &lt;clone()&gt; at the specified object lifecycle level,
     and removes that object lifecycle level. This indicates to the MB that
     these objects (including any objects they contain) will no longer be
     used by the MI. The MB may free the resources associated with these
     objects during the call to this function, or later during some garbage
     collection cycle.
     
     The &lt;mark()&gt; and &lt;release()&gt; function calls may be stacked.

     @param mb Pointer to the broker.
     @param gc The handle returned from the &lt;mark()&gt; operation.
     @return &lt;CMPIStatus&gt; structure indicating the function return status .
     @sa CMPIBrokerMemFT.mark()
     */
    CMPIStatus (*release) (const CMPIBroker* mb, const CMPIGcStat* gc);

    /** @brief allocate an uninitalized memory block of the
               specified size.
     
     This function allocates an uninitalized memory block of the specified
         size. This function behaves consistently with the POSIX
         &lt; malloc()&gt; function (see IEEE 1003.1)
     @param mb Specifies the broker.
     @param size Specifies the amount of memory to allocate in Bytes.
     @return Returns a pointer to the allocated memory, or NULL if the memory
     could not be allocated
     */
    void* (*cmpiMalloc) (const CMPIBroker* mb, size_t size);

    /* @brief Change the size of a memory block.
     * This function function changes the size of the memory block pointed
     to by ptr which shall have been returned by a previous call to
     &lt;cmpiMalloc()&gt; or &lt;cmpiCalloc()&gt;. This function behaves
     consistently with the POSIX &lt;realloc()&gt; function (see IEEE 1003.1).
     
     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb The broker.
     @param nElems The number of elements to allocate.
     @param sizeElem The number of elements to allocate.
     @return Returns a pointer to the allocated memory, or NULL if the memory
     could not be allocated
     */
    void* (*cmpiCalloc) (const CMPIBroker* mb, size_t nElems, size_t sizeElem);

    /* @brief Change the size of a memory block.
     
     This function function changes the size of the memory block pointed
     to by ptr which shall have been returned by a previous call to
     &lt;cmpiMalloc()&gt; or &lt;cmpiCalloc()&gt;. This function behaves
     consistently with the POSIX &lt;realloc()&gt; function (see IEEE 1003.1).
     
     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb The broker.
     @param ptr Pointer to previosuly allocated memory.  Passing a pointer
     to this function which was not allocated explicitly by &lt;cmpiMalloc&gt;
     or &lt;cmpiCalloc&gt; is undefined.
     @param size The new size of the memory block in Bytes.
     @return If successful, a pointer to the resized allocated memory block
     NULL if the new memory is not allcoated. If the function fails
     the original &lt;ptr&gt; argument is unchanged.
     */
    void* (*cmpiRealloc) (const CMPIBroker* mb, void* ptr, size_t size);

    /** TODO: Sync description with spec.
     * This function returns a pointer to a new string which is a
     duplicate of the string src.
     @param mb The broker
     @param str The string to duplicate
     @return a pointer to the duplicated string, or NULL if insufficient
     memory was available.
     */
    char* (*cmpiStrDup) (const CMPIBroker* mb, const char* str);

    /** @brief Free a memory block
     * This function frees memory allocated via the &lt;cmpiMalloc()&gt;,
     &lt;cmpiCalloc()&gt; or *lt;cmpiRealloc()&gt; functions.
     
     This function behaves consistently with the POSIX &lt;free()&gt; function
     (see IEEE 1003.1).
     @param mb The broker.
     @param ptr The memory to free. This memory MUST have been allocated via
     the cmpiMalloc, cmpiCalloc or cmpiRealloc functions.
     @return None
     */
    void (*cmpiFree) (const CMPIBroker* mb, void* ptr);

    /** @brief Release a &lt;CMPIInstance&gt; object.
     
     This function releases a CMPIInstance object. This indicates to the 
     MB that the object (including any objects it contains) will no 
     longer be used by the MI. The MB may free the resources 
     associated with the object during the call to this function, or 
     later during some garbage collection cycle. 
     
     Allows a MI to free memory associated to a &lt;CMPIInstance&gt; which was
     allocated via &lt;CMPIBrokerEncFT.newInstance()&gt;. this function should
     be called when an instance is no longer being used by the MI. This
     function will free all contained objects (e.g. properties).
     @param mb the broker.
     @param inst The instance to free.
     @return None
     */
    void (*freeInstance) (const CMPIBroker* mb, CMPIInstance* inst);

    /** @brief Release a &lt;CMPIObjectPath&gt; object.
     
     This function releases a &lt;CMPIObjectPath&gt; object. This 
     indicates to the MB that the object (including any objects it 
     contains) will no longer be used by the MI. The MB may free the 
     resources associated with the object during the call to this 
     function, or later during some garbage collection cycle. 
     
     Allows a MI to free memory associated to a &lt;CMPIObjectPath&gt which was
     allocated via &lt;CMPIBrokerEncFT.newObjectPath()&gt;. this function
     should be called when a &lt;CMPIObjectPath&gt; is no longer being used by
     the MI. This function will free all contained objects.
     @param mb the broker.
     @param obj The object path to free.
     @return None
     */
    void (*freeObjectPath) (const CMPIBroker* mb, CMPIObjectPath* obj);

    /** @brief Release a &lt;CMPIArgs&gt; object.
     
     Allows an MI to free memory associated to a &lt;MPIArgs&gt; which was
     allocated via CMPIBrokerEncFT.newArgs. this function should be called
     when an instance is no longer being used by the MI. This function will
     free all contained objects.
     @param mb the broker.
     @param args The argument to free.
     @return None.
     */
    void (*freeArgs) (const CMPIBroker* mb, CMPIArgs* args);

    /** @brief release a &lt;CMPIString&gt; object.
     
     Allows an MI to free memory associated to a &lt;CMPIString&gt; which was
     allocated via &lt;CMPIBrokerEncFT.newString()&gt;. this function should be
     called when an instance is no longer being used by the MI. This
     function will free all contained objects.
     @param mb Pointer tothe broker.
     @param args The string to free.
     @return None.
     */
    void (*freeString) (const CMPIBroker* mb, CMPIString* str);

    /** @brief release a &lt;CMPIArray&gt; object.
     
     Allows a MI to free memory associated to a &lt;CMPIArray&gt; which was
     allocated via &lt;CMPIBrokerEncFT.newArray()&gt;. this function should
     be called when an instance is no longer being used by the MI. This
     function will free all contained objects (e.g. the array elements).
     
     The MB may free the resources associated with the object during the call
     to this function, or later during some garbage collection cycle 
     @param mb Pointer to the broker.
     @param args The string to free.
     @return None.
     */
    void (*freeArray) (const CMPIBroker* mb, CMPIArray* array);

    /** @brief release a &lt;CMPIDateTime&gt; object.
     
     Allows a MI to free memory associated to a CMPIDateTime which was
     allocated via CMPIBrokerEncFT.newDateTime functions. this function
     should be called when an instance is no longer being used by the MI.
     This function will free all contained objects.
     
     The MB may free the resources associated with the object during the call
     to this function, or later during some garbage collection cycle 
     @param mb the broker.
     @param args The string to free.
     @return None.
     */
    void (*freeDateTime) (const CMPIBroker* mb, CMPIDateTime* date);

    /** @brief release a &lt;CMPISelectExp&gt; object.
     
     Allows a MI to free memory associated to a CMPISelectExp which was
     allocated via CMPIBrokerEncFT.newSelectExp functions. this function
     should be called when an instance is no longer being used by the MI.
     
     This function will free all contained objects.
     
     The MB may free the resources associated with the object during the call
     to this function, or later during some garbage collection cycle 
     @param mb the broker.
     @param args The string to free.
     @return None.
     */
    void (*freeSelectExp) (const CMPIBroker* mb, CMPISelectExp* se);

#ifdef CMPI_VER_210

    /** @brief free the memory of a C-language string.
     
     function releases a C-language string. This indicates to the MB that
     the string will no longer be used by the MI. The MB may free the
     memory associated with the string during the call to this function,
     or later during some garbage collection cycle.
     
     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.
     Availability of the Codepage Conversion capability can be queried by
     an MI using the CMPI_MB_CodepageConversion test mask on the
     &lt;brokerCapabilitie&gt;s member of the &lt;CMPIBrokerFT structure&gt;.
     
     @param mb Pointer to the broker.
     @param chars The C language string to free.
     @return None.
     */
    void (*freeChars) (const CMPIBroker* mb, char* chars);

#endif // CMPI_VER_210

     /**
     * @}
     */

};

#endif // CMPI_VER_200

/**
 * @defgroup mb-edt MB encapsulated data types
 * @{
 */

/**
 * @brief CMPIContext encapsulated data type object.
 *
 * CMPIContext objects are used by the MB to pass context data about the
 * invoked operation to the MI.
 */
struct _CMPIContext {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIContextFT* ft;

};

/**
 * @brief Function table of
 * [CMPIContext encapsulated data type object](@ref _CMPIContext).
 */
struct _CMPIContextFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a &lt;CMPIContext&gt; object.
     
     The Context object will not be used any further and may be freed by
     CMPI run time system.
     @param ctx Pointer to &lt;CMPIContext&gt; to be released.
     @return &lt;CMPIStatus&gt; structure indication the function return status.
     */
    CMPIStatus (*release) (CMPIContext* ctx);

    /** @brief Create an independent copy of a &lt;CMPIContext&gt;
               object.
     
     Create an independent copy of the Context object.
     @param ctx Context this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied &lt;CMPIContext&gt; object. The returned
         &lt;CMPIContext&gt; object shall be explicity released by the
         MI using &lt;CMPIContextFT.release()&gt;.
     */
    CMPIContext* (*clone) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief get a context entry in a CMPIContext object by name.
     
     Gets a context entry in a CMPIContext object by supplying its name.
     @param ctx CMPIContext object for this function
     @param name string specifying the context entry name.
     @param rc  Output: The rc output argument, if not NULL, points to a
         CMPIStatus structure that upon return will have been
         updated with the function return status
     @return If successful, a CMPIData structure containing the specified
        context entry will be returned. If not successful,
        CMPIData.state will have the CMPI_badValue flag set to true.
     */
    CMPIData (*getEntry) (const CMPIContext* ctx, const char* name,
            CMPIStatus* rc);

    /** @brief  Get a context entry in a CMPIContext object by index
     * Gets a Context entry value defined by its index.
     @param ctx CMPIContext this pointer.
     @param index specifies the zero-based position of the contextentry in the
         internal data array. The order of context entries in the internal
         data array is implementation-defined.
     @param name Output: Returned Context entry name (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return if not NULL, points to a CMPIStatus structure that upon return
         updated with the function return status.
     */
    CMPIData (*getEntryAt) (const CMPIContext* ctx, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get the number of context entries in a CMPIContext
     *         object
     * Gets the number of entries contained in this Context.
     @param ctx CMPIContext object for this function.
     @return If successful, a CMPICount value indicating the number of entries
         in the CMPIContext object. If not successful, the return value will
         be undefined.
     */
    CMPICount (*getEntryCount) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief add or replace a context entry in a CMPIContext
     *         object
     * Adds/replaces a named Context entry in a CMPIContext object
     @param ctx Context this pointer.
     @param name Entry name. See @link def-context-names definition of context
     entry names @endlink for defined names.
     @param value Address of CMPIValue structure containing the
     *            non-NULL value to be assigned to the context entry
     *            or NULL to specify that NULL is to be assigned.
     @param CMPIType value specifying the type of the value to be
     *               assigned
     @return Service return status.
     */
    CMPIStatus (*addEntry) (const CMPIContext* ctx, const char* name,
            const CMPIValue* value, const CMPIType type);

};

/**
 * @brief CMPIResult encapsulated data type object.
 */
struct _CMPIResult {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIResultFT* ft;

};

/**
 * @brief Function table of
 * [CMPIResult encapsulated data type object](@ref _CMPIResult).
 */
struct _CMPIResultFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPIResult object
       The Result object will not be used any further and may be freed by
     CMPI run time system.
     @param rslt Result this pointer.
     @return CMPIStatus structure indicating the function return status.
     */
    CMPIStatus (*release) (CMPIResult* rslt);

    /** @brief create an independent copy of a CMPIResult object.
     *         KS_TODO
     
     Create an independent copy of the CMPIResult object defined by 
     &lt;rslt&gt;. 
     @param rslt Pointer to CMPIResult object to be copied.
     @param rc Output: Service return status (suppressed when NULL)
     @return If not NULL, points to cloned CMPIResult object.
     */ 
    CMPIResult* (*clone) (const CMPIResult* rslt, CMPIStatus* rc);

    /** @brief add a value/type pair to a CMPIResult object
         Adds a value/type pair to be returned to the MB, to a CMPIResult      .
         object.
     @param rslt CMPIResult object for this function.
     @param value Pointer to CMPIValue structure specifying the non-NULL value
         to be returned, or is NULL to specify that NULL is to be returned
     @param type CMPIType value specifying the type to be returned
     @return If the value of the type argument is CMPI_chars or CMPI_charsA,
         the C-language string to which the chars member of the value argument
         points is copied by this function and the original string memory
         may be freed by the MI right after this function returns
     */
    CMPIStatus (*returnData) (const CMPIResult* rslt, const CMPIValue* value,
            const CMPIType type);

    /** @brief  add an instance to a CMPIResult object
        Adds an instance to be returned to the MB, to a CMPIResult object
     @param rslt Result this pointer.
     @param inst Instance to be returned.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*returnInstance) (const CMPIResult* rslt,
            const CMPIInstance* inst);

    /** @brief  Add an object path to a CMPIResult object
        Adds an object path to be returned to the MB, to a CMPIResult object.
     @param rslt CMPIResult object for this function.
     @param ref ObjectPath to be returned.
     @return CMPIStatus structure indicating the function return*
        status.
     */
    CMPIStatus (*returnObjectPath) (const CMPIResult* rslt,
            const CMPIObjectPath* ref);

    /** @brief Indicate that no more items will be added to a
         CMPIResult object Indicates to the MB that no further items
         will be added to a CMPIResult object; that is, the MI will
         not return any more data to the MB
     @param rslt CMPIResult object for this function.
     @return CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*returnDone) (const CMPIResult* rslt);

#ifdef CMPI_VER_200

    /** @brief Add an error to a CMPIResult object
        Adds an error to be returned to the MB, to a CMPIResult object
     @param rslt CMPIResult object for this function.
     @param er CMPIError object representing the error to be returned. This
         function may be called multiple times, each time adding one CMPIError
         object to the set of extended errors for this result.
         This function is part of the Extended Errors capability of an MB
         (see TODO). From CMPI 2.1 on, the Extended Errors capability
         shall be available.
     @return CMPIStatus structure indicating the function return status.
     */
    CMPIStatus (*returnError) (const CMPIResult* rslt, const CMPIError* er);

#endif

};

#ifdef CMPI_VER_200

/**
 * @brief CMPIError encapsulated data type object.
 */
struct _CMPIError {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIErrorFT* ft;

};

/**
 * @brief Function table of
 * [CMPIError encapsulated data type object](@ref _CMPIError).
 */
struct _CMPIErrorFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIError object
         The Error object will not be used any further and may be freed by
         CMPI run time system. The MB may free the resources associated with the
         object during the call to this function, or later during some garbage
         collection cycle.
     @param er Pointer to the CMPIError object to be released.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*release) (CMPIError* er);

    /** @brief create an independent copy of a CMPIError object.
        Create an independent copy of this Error object.
     @param er Pointer to the CMPIError object to be copied.
     @param rc if not NULL, points to a CMPIStatus structure that upon return
         will have been updated with the function return status.
     @return If successful, a pointer to the copied CMPIError object. The
         returned CMPIError object shall be explicitly released by the MI
         using CMPIErrorFT.release().If not successful, NULL will be returned.
     */
    CMPIError* (*clone) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorType attribute of a CMPIError object.
         Gets the type of this Error
     @param er Pointer to the CMPIError object for this function
     @param rc if not NULL, points to a CMPIStatus structure that updated wit
         the function return status.
     @return If successful, returns a CMPIErrorType enumeration value,
         indicating the value of the ErrorType attribute in the CMPIError
         object.
         If not successful, the returned value is undefined.
     */
    CMPIErrorType (*getErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the OtherErrorType attribute of a CMPIError
       object Returns a string which describes the alternate error
       type.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful and the OtherErrorType attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the OtherErrorType attribute of the CMPIError
         object. Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether the
         function failed.
     */
    CMPIString* (*getOtherErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the OwningEntity attribute of a CMPIError object.
        Returns a string which describes the owning entity
     @param er Error this pointer
     @param rc Output: if not NULL, points to a CMPIStatus structure
         updated with the function return status.
     @return If successful and the OwningEntity attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the OwningEntity attribute of the CMPIError
         object. Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether
         the function failed.

     */
    CMPIString* (*getOwningEntity) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the MessageID attribute of a CMPIError object
        Returns a string which is the message ID.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful and the MessageID attribute of the CMPIError object
         is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the MessageID attribute of the CMPIError
         object. The returned CMPIString object shall not be explicitly
         released by the MI, because it may be an internal object of the
         CMPIError object which will be released along with that object, or a
         new object created by the MB which will be released automatically by
         the MB. Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether the
         function failed.
     */
    CMPIString* (*getMessageID) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the Message attribute of a CMPIError object
     Returns a string comnating an error message.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful and the Message attribute of the CMPIError object
         is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the Message attribute of the CMPIError object.
         Otherwise, NULL will be returned.
        The caller must inspect the function return status to see whether
        the function failed.
     */
    CMPIString* (*getMessage) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the PerceivedSeverity attribute of a CMPIError
     object. Returns the PerceivedSeverity attribute of a CMPIError
     object.
     @param er  points to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful, a CMPIErrorSeverity enumeration value will be
         returned, indicating the value of the PerceivedSeverity attribute of
         the CMPIError object. If not successful, the returned value is
         undefined.
     */
    CMPIErrorSeverity (*getPerceivedSeverity) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief get the ProbableCause attribute of a CMPIError object
     Returns the ProbableCause attribute of a CMPIError object
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         updated with the function return status..
     @return If successful, a CMPIErrorProbableCause enumeration value
         will be returned, indicating the value of the ProbableCause attribute
         of the CMPIError object.
         If not successful, the returned value is undefined.
     */
    CMPIErrorProbableCause (*getProbableCause) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the ProbableCauseDescription attribute of a
       CMPIError object Returns a string which describes the
       probable cause.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful and the ProbableCauseDescription attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIString object will
         be returned, indicating the value of the ProbableCauseDescription
         attribute of the CMPIError object.
         Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether
         the function failed.

     */
    CMPIString* (*getProbableCauseDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the RecommendedActions array attribute of a
       CMPIError object Returns an array of strings which describes
     recomended actions of the CMPIError object
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the RecommendedActions array attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIArray object will
         be returned, containing CMPIString elements that represent the
         array elements of the RecommendedActions array attribute in the
         CMPIError object.
         Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether the function failed.
     */
    CMPIArray* (*getRecommendedActions) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the ErrorSource attribute of a CMPIError object
     Returns a string which describes the Error source of the
         CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the ErrorSource attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be
         returned, indicating the value of the ErrorSource attribute of the
         CMPIError object. Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether
         the function failed.
     */
    CMPIString* (*getErrorSource) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the ErrorSourceFormat attribute of a CMPIError bject
     Returns a the format that the error src is in.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, a CMPIErrorSrcFormat enumeration value will be
         returned, indicating the value of the ErrorSourceFormat attribute of
         the CMPIError object .
         If not successful, the returned value is undefined.
     */
    CMPIErrorSrcFormat (*getErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief get the OtherErrorSourceFormat attribute of a CMPIError object
     Returns a string which describes the 'other' format, only available if
         the error source is OTHER.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the OtherErrorSource attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the OtherErrorSourceFormat attribute of the
         CMPIError object. Otherwise, NULL will be returned.
         The caller must inspect the function return status to see whether
         the function failed.
     */
    CMPIString* (*getOtherErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief  get the CIMStatusCode attribute of a CMPIError object
     Returns the status code of this error.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, a CMPIrc value indicating the value of the
         CIMStatusCode attribute of the CMPIError object will be returned.
         Please note that not all status codes apply to all situations.
         It is up to the MI to ensure the correct status code is set.
         If not successful, the returned value is undefined.
     */
    CMPIrc (*getCIMStatusCode) (const CMPIError* er, CMPIStatus* rc);

    /** @brief get the CIMStatusCodeDescription attribute of a CMPIError object.
     Returns a string which describes the status code error.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the CIMStatusCodeDescription attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIString object will
         be returned, indicating the value of the CIMStatusCodeDescription
         attribute of the CMPIError object.
         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.

     */
    CMPIString* (*getCIMStatusCodeDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief get the MessageArguments array attribute of a
     CMPIError object Returns an array which contains the dynamic
     content of the message.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the MessageArguments array attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIArray object will be
         returned, containing CMPIString objects that represent the array
         elements of the MessageArguments array attribute of the CMPIError object.
         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether the
         function failed.

     */
    CMPIArray* (*getMessageArguments) (const CMPIError* er, CMPIStatus* rc);

    /** @brief set the ErrorType attribute of a CMPIError object
     Sets the error type of this error object.
     @param er Pointer to the CMPIError object for this function.
     @param et CMPIErrorType enumeration value specifying the new value for
         the ErrorType attribute. If the error message in the CMPIError object
         is defined in a DMTF message registry, the et argument shall
         reflect the content of the ERROR_TYPE element defined for
         the message in the registry
     @return Output: CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*setErrorType) (const CMPIError* er, const CMPIErrorType et);

    /** @brief  set the OtherErrorType attribute of a CMPIError
     object Sets the 'other' error type of this error object.
     @param er Pointer to the CMPIError object for this function.
     @param oet points to a string specifying the new non-NULL value for the
         OtherErrorType attribute, or is NULL specifying that the attribute
         will be set to NULL. If the error message is defined in a DMTF
         message registry, the string value of the oet argument shall be
         the content of the OTHER_ERROR_TYPE element defined for the message
         in the registry
         It is only valid when error type is "OTHER"
     @return Output: CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*setOtherErrorType) (const CMPIError* er, const char* oet);

    /** @brief  set the ProbableCauseDescription attribute of a
     CMPIError object. Sets the description of the probable cause.
     @param er Pointer to the CMPIError object for this function.
     @param pcd string specifying the new non-NULL value for the
         ProbableCauseDescription attribute, or is NULL specifying that the
         attribute will be set to NULL. If the error message is defined in a
         DMTF message registry, note that the string value of the pcd argument
         is not defined in the message in the registry.
     @return Output: CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*setProbableCauseDescription) (const CMPIError* er,
            const char* pcd);

    /** @brief set the RecommendedActions array attribute of a
         CMPIError object.

     Sets the recommended actions array. For a description of the
         RecommendedActions attribute, see the description of the
         RecommendedActions property in the CIM_Error class in the CIM Schema.
     @param er Pointer to the CMPIError object for this function.
     @param ra pointer to a CMPIArray object specifying the new array value
         for the RecommendedActions array attribute. The CMPIArray object
         contains CMPIString objects or NULL values as array elements. The
         ra argument may be NULL, specifying that the RecommendedActions array
         attribute will be set to NULL. If the error message is defined in a
         DMTF message registry, the ra argument shall reflect the values
         defined in the RECOMMENDED_ACTION elements defined for the message
         in the registry, in the order defined there.
     @return CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*setRecommendedActions) (const CMPIError* er,
            const CMPIArray* ra);

    /** @brief set the ErrorSource attribute of a CMPIError object.

     Specifies a string which specifes The identifying information
     of the entity (i.e., the instance) generating the error..*
     @param er Pointer to the CMPIError object for this function.
     @param es string specifying the new non-NULL value for the ErrorSource
         attribute, or is NULL specifying that the attribute will be set to
         NULL. If the error message is defined in a DMTF message registry,
         the string value of the es argument shall be the content of the
         ERROR_SOURCE element defined for the message in the registry.
     @return CMPIStatus structure indicating the function return status
     */
    CMPIStatus (*setErrorSource) (const CMPIError* er, const char* es);

    /** @brief set the &lt;ErrorSourceFormat&gt; attribute of a
         CMPIError object.

     Sets the source format of the error object. For a
     description of the ErrorSourceFormat attribute, see the
     description of the ErrorSourceFormat property in the CIM_Error
     class in the CIM Schema.
     @param er Pointer to the CMPIError object for this function.
     @param esf CMPIErrorSrcFormat enumeration value specifying the new value
         for the ErrorSourceFormat attribute. If the error message is defined
         in a DMTF message registry, the string value of the esf argument shall
         be the content of the ERROR_SOURCE_FORMAT element defined for the
         message in the registry
     @return CMPIStatus structure indicating the function return status.
     */
    CMPIStatus (*setErrorSourceFormat) (const CMPIError* er,
            const CMPIErrorSrcFormat esf);

    /** @brief set the &lt;OtherErrorSourceFormat&gt; attribute of a
     &lt;CMPIError&gt; object

     Specifies a string defining "Other" values for &lt;ErrorSourceFormat&gt;
     @param er Pointer to the &lt;CMPIError&gt; object for this function.
     @param oef Pointer to a string specifying the new non-NULL value for
         the &lt;OtherErrorSourceFormat&gt; attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is
         defined in a DMTF message registry, the string value of the
         &lt;oef&gt; argument shall be the content of the
         OTHER_ERROR_SOURCE_FORMAT element defined for the message in the
         registry.
     @return &lt;CMPIStatus&gt; structure indicating the function return status.
     */
    CMPIStatus (*setOtherErrorSourceFormat) (const CMPIError* er,
            const char* oef);

    /** @brief set the &lt;CIMStatusCodeDescription&gt; attribute of a
       &lt;CMPIError&gt; object

     Sets the description of the status code. For a description of the
         &lt;CIMStatusCodeDescription&gt; attribute, see the description of the
         &lt;CIMStatusCodeDescription&gt; property in the &lt;CIM_Error&gt;
         class in the CIM Schema.
     @param er Pointer to the &lt;CMPIError&gt; object for this function.
     @param scd A Pointer to a string specifying the new non-NULL value
         for the &lt;CIMStatusCodeDescription&gt; attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is defined
         in a DMTF message registry, note that the string value of the
         &lt;scd&gt; argument is not defined in the message in the registry.
     @return &lt;CMPIStatus&gt; structure indicating the function return status.
     */
    CMPIStatus (*setCIMStatusCodeDescription) (const CMPIError* er,
            const char* scd);

    /** @brief set the &lt;MessageArguments&gt; array attribute of a
           &lt;CMPIError&gt; object.

     Sets an array of strings for the dynamic content of the message. For a
         description of the &lt;MessageArguments&gt; attribute, see the
         description of the &lt;MessageArguments&gt; property in the
         &lt;CIM_Error&gt; class in the CIM Schema.
     @param er Pointer to the &lt;CMPIError&gt; object for this function.
     @param values &lt;CMPIArray&gt; object specifying the new array value
         for the &lt;MessageArguments&gt; array attribute. The &lt;CMPIArray&gt;
         object contains &lt;CMPIString&gt; objects or NULL values as array
         elements. The values argument may be NULL, specifying that the
         &lt;MessageArguments&gt; array attribute will be set to NULL. If the
         error message is defined in a DMTF message registry, the values
         argument shall reflect the values defined in the DYNAMIC_ELEMENT
         elements defined for the message in the registry, in the order
         defined there.
     @return &lt;CMPIStatus&gt; structure indicating the function return status.
     */
    CMPIStatus (*setMessageArguments) (const CMPIError* er,
            const CMPIArray* values);

};

#endif // CMPI_VER_200

/**
 * @brief CMPIInstance encapsulated data type object.
 */
struct _CMPIInstance {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIInstanceFT* ft;

};

/**
 * @brief Function table of
 * [CMPIInstance encapsulated data type object](@ref _CMPIInstance).
 */
struct _CMPIInstanceFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /* @brief Release a &lt:CMPIInstance&gt; object.
     
     The Instance object will not be used any further and may be freed by
     CMPI run time system. This will also release the contained objects.
     @param inst Pointer to CMPIInstance to be releases.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIInstance* inst);

    /* @brief Create an independent copy of a &lt:CMPIInstance&gt; object
     
     Create an independent copy of this Instance object. The resulting
     object must be released explicitly.
     @param inst Pointer to the &lt:CMPIInstance&gt; to be cloned.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied &lt:CMPIInstance&gt; object.
     */
    CMPIInstance* (*clone) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief get a property in a &lt;CMPIInstance&gt; object by
               name.
     
     Gets a named property value from an instance.
     @param inst Instance this pointer.
     @param name Points to a string containing the property name.
     @param rc Output: if not NULL, points to a &lt;CMPIStatus&gt; structure
     that upon return is updated with the function return status.
     @return If successful, a CMPIData structure containing the specified
     property will be returned.
     
     If not successful, CMPIData.state will have the CMPI_badValue flag
     set to true.
     */
    CMPIData (*getProperty) (const CMPIInstance* inst, const char* name,
            CMPIStatus* rc);

    /** @brief get a property in a &lt;CMPIInstance&gt; object by index.

     Gets a Property value defined by its index.
     @param inst Pointer to the instance.
     @param index Zero-based index number of the property in the internal
         data array.
     @param name Output: If not NULL, points to a &lt;CMPIString&gt; pointer
     that upon success is updated to point to a &lt;CMPIString&gt; object
     containing the property name. The returned &lt;CMPIString&gt; object
     shall not be explicitly released by the MI, because it may be an internal
     object of the &lt;CMPIString&gt; object which will be released
     along with that object, or a new object created by the MB which will be
     released automatically by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure
     updated with the function return status.
     @return If successful, a &lt;CMPIData&gt; structure containing the
     specified property.
     If not successful, &lt;CMPIData&gt;  state will have the
     &lt;CMPI_badValue&gt; flag set to true
     */
    CMPIData (*getPropertyAt)
    (const CMPIInstance* inst, CMPICount index, CMPIString** name,
            CMPIStatus* rc);

    /** @brief get the number of properties in a CMPIInstance
                                                                   object.
     . Gets the number of properties contained in this Instance. 
     @param inst Pointer to the instance.
     @param rc Output: If not NULL, points to a &lt;CMPIStatus&gt; structure
     updated with the function return status.
     @return If successful, a &lt;CMPICount&gt; value indicating the number
     of properties in the instance. If not successful, 0.
     */
    CMPICount (*getPropertyCount) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief add/replace a property value in a &lt;CMPIInstance&gt;
       object by name.
                                            .
     Adds or replace the named Property in the instanced defined by
         &lt;inst&gt;. If the property is a key property, the function may
         or may not in addition add or update the key binding in the object
         path of the instance. In order for MIs not to be dependent on this
         behavior, MIs should set key property values in instances and key
         binding values in object paths separately. Key binding values can
         be set during CMPIBrokerEncFT.newInstance() and by using
         &lt;CMPIInstanceFT.setObjectPath()*gt;. The MI shall specify
         consistent values for key bindings and key properties.
     @param inst pointer to the &lt;CMPIInstance&gt;.
     @param name Pointer to a string containing the property name.
     @param value &lt;CMPIValue&gt; structure containing the non-NULL
         value to be assigned to the property, or NULL to specify that
         NULL is to be assigned.
     @param type &lt;CMPIType&gt; value specifying the type of the value to
        be assigned to the property. All types of CIM values are supported.
     
        If the value of the type argument is &lt;CMPI&gt;_chars or
        &lt;CMPI_charsA&gt;, the C-language string to which the chars member
        of the value argument points is copied by this function and the
        original string memory may be freed by the MI right after
        this function returns.
     @return &ltCMPIStatus&gt structure indicating the function return status.
     */
    CMPIStatus (*setProperty) (const CMPIInstance* inst, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief Get a &lt;CMPIObjecPath&gt; object from a &lt;CMPIInstance&gt;
       object.
     
     Generates a &lt;CMPIObjectPath&gt; object from the namespace, class name,
         and key properties of a &lt;CMPIInstance&gt; object.
     @param inst Pointer to the %lt;CMPIInstance&gt;.
     @param rc Output: , If not NULL, points to a &lt;CMPIStatus&gt; structure
        that upon return has been updated with the function return status.
     @return If successful, a pointer to a &lt;CMPIObjectPath&gt; object
     representing the instance path of the &lt;CMPIInstance&gt;.
    The returned &lt;CMPIObjectPath&gt; object shall not be explicitly 
    released by the MI, because it may be an internal object of the 
    &lt;CMPIInstance&gt; object which will be released along with that object, 
    or a new object created by the MB which will be released automatically 
    by the MB.
     */
    CMPIObjectPath* (*getObjectPath) (const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief Attach a property filter to a &lt;CMPIInstance&gt
               object.
     
     This function attaches a property filter to a &lt;CMPIInstance&gt object,
         replacing any previous property filter settings for this object.
         By calling this function, the MI delegates property list filtering
         to the MB for this CMPIInstance object, for all of its properties
         including those that had already been set before the call to
         &lt;setPropertyFilter()&gt;.
     
         Filtering directs CMPI to ignore any setProperty operations for this
         instance for any properties not in this list.
     
         Support for this function is optional. Availability of this support is
         indicated by the CMPI_MB_PropertyFiltering flag in
         CMPIBrokerFT.brokerCapabilities
     
     @param inst Pointer to the instance.
     @param propertyList If not NULL, the members of the array define one
     or more Property names to be accepted by setProperty operations. A NULL
     value effectively means that all properties will be accepted.
     A pointer to an empty array means that no properties will be accepted.
     @param keys Deprecated, ignored by MB, maintained here for compatibility.
     @return CMPIStatus structure indicating the function return status
         will be returned.
     */
    CMPIStatus (*setPropertyFilter) (const CMPIInstance* inst,
            const char** propertyList, const char** keys);

    /** @brief Set the instance path component of a CMPIInstance object.
     
     Set or replace the CMPIObjectPath component in an instance.
     @param inst Pointer to the CMPIInstance object.
     @param op The CMPIObjectPath structure. This objectpath
     shall contain a non-NULL namespace, non-NULL classname, as well as all
     keys for the specified instance. The object path may specify a non-NULL
     host for the instance (this is used for instances returned by
     cross-host associations).
     
     The function may or may not in addition update the key property
     values in the instance to the values of the key bindings in the object
     path. In order for MIs not to be dependent on this behavior, MIs should
     set key property values in instances and key binding values in
     object paths separately. Property values can be set by using
     &lt;CMPIInstanceFT.setProperty()&gt; or
     &lt;CMPIInstanceFT.setPropertyWithOrigin()&gt;. The MI shall specify
     consistent values for key bindings and key properties.
     @return  CMPIStatus structure indicating the function return status.
.
     */
    CMPIStatus (*setObjectPath) (const CMPIInstance* inst,
            const CMPIObjectPath* op);

#ifdef CMPI_VER_200

    /** @brief add or replace a property value in a CMPIInstance
               object by name.
     
     Adds or replaces a Property value and origin.
     
     If the property is a key property, the function may or may not in addition
     add or update the key binding in the object path of the instance. In
     order for MIs not to be dependent on this behavior, MIs should set
     key property values in instances and key binding values in object
     paths separately. Key binding values can be set during
     &lt;CMPIBrokerEncFT.newInstance()&gt; and by using
     &lt;CMPIInstanceFT.setObjectPath()&gt;. The MI shall specify consistent
     values for key bindings and key properties.
     @param inst Pointer to the CMPIInstance object.
     @param name CMPIString containing the property name.
     @param value points to a CMPIValue structure containing the value
     to be assigned to the property.
     @param type CMPIType structure defining the type of the value.
     @param origin specifies the instance origin. If NULL, then
     no origin is attached to  the property.
     @return CMPIStatus structure indicating the function return status.*  
     @version CMPI 2.0 
     */
    CMPIStatus (*setPropertyWithOrigin) (const CMPIInstance* inst,
            const char* name, const CMPIValue* value, const CMPIType type,
            const char* origin);

#endif // CMPI_VER_200

};

/**
 * @brief CMPIObjectPath encapsulated data type object.
 */
struct _CMPIObjectPath {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIObjectPathFT* ft;

};

/**
 * @brief Function table of
 * [CMPIObjectPath encapsulated data type object](@ref _CMPIObjectPath).
 */
struct _CMPIObjectPathFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPIObjectPath object.
     
     The CMPIObjectPath object will not be used any further and 
     may be freed by CMPI run time system.
     @param op Pointer to CMPIObjectPath.
     @return CMPIStatus structure indicating the function return status.
     */
    CMPIStatus (*release) (CMPIObjectPath* op);

    /** @brief create an independent copy of a CMPIObjectPath
               object.
     
     Create an independent copy of this CMPI ObjectPath object. The resulting
     object must be released explicitly.
     @param op Pointer to CMPIObjectPath to be cloned.
     @param rc Output: Service return status (suppressed when NULL).
     @return CMPIStatus structure indicating the function return*  
         status.
     */
    CMPIObjectPath* (*clone) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Add the namespace component to a &lt;CIMObjectPath&gt;
           object.
     
     Set or replace the namespace component in the CMPIObjectPath object
     defined by &lt;op&gt;.
     @param op Pointer to the CMPIObjectPath object.
     @param ns CMPI String containing the namespace to add.
     @return CMPIStatus structure indicating the function return*  
         status.
     */
    CMPIStatus (*setNameSpace) (const CMPIObjectPath* op, const char* ns);

    /** @brief Get the namespace component from a
     *       &lt;CIMObjectPath&gt;
           object.

     Get the namespace component.
     @param op Pointer to the CMPIObjectPath object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to a CMPIString object containing*  
         the namespace component of the object path will be returned.
         The returned CMPIString object shall not be explicitly released
         by the MI, because it may be an internal object of the
         CMPIObjectPath object which will be released along with that object,
         or a new object created by the MB which will be released
         automatically by the MB.
.
     */
    CMPIString* (*getNameSpace) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set the host name component in a &lt;CIMObjectPath&gt
        object.
     
     Set or replace the host name component in a CMPIObjectPath object.
     @param op Pointer to the CMPIObjectPath.
     @param hn Pointer to a CMPIString containing the host name.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*setHostname) (const CMPIObjectPath* op, const char* hn);

    /** @brief get the host name component  in a
        &lt;CIMObjectPath&gt object.
     
     Get the host name component.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, teturns a pointer to a CMPIString object containing
     the host name component of the object path.
     The returned CMPIString object shall not be explicitly released
     by the MI, because it may be an internal object of the
     CMPIObjectPath object which will be released along with that
     object, or a new object created by the MB which will be
     released automatically by the MB.
     
     If not successful, returns NULL.
     */
    CMPIString* (*getHostname) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set class name component in a &lt;CIMObjectPath&gt
        object.
     
     Set/replace the class name component in the &lt;CIMObjectPath&gt
        object.
     @param op Pointer to CMPIObjectPath.
     @param cn CMPIString containing the class name.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*setClassName) (const CMPIObjectPath* op, const char* cn);

    /** @brief Set class name component in a &lt;CIMObjectPath&gt
                                                                   object.
     . Get the classname componentin a &lt;CIMObjectPath&gt object. 
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object
        containing the class name component of the object path.
        The returned CMPIString object shall not be explicitly released
        by the MI, because it may be an internal object of the
        CMPIObjectPath object which will be released along with
        that object, or a new object created by the MB which will be
        released automatically by the MB 
     */
    CMPIString* (*getClassName) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief add a key binding in a CMPIObjectPath object.
                                            .
     Adds or replaces a key binding in a CMPIObjectPath object.
     @param op Pointer to CMPIObjectPath.
     @param name Pointer to string containing key name.
     @param value CMPIValue containing the value to be assigned to the                 .
        key binding Key binding values must NOT be NULL.
     @param type Value type to be assigned to the key binding. All types of CIM
         values are valid for keys are supported. If the value of the type
         argument is CMPI_chars or CMPI_charsA, the C-language string
         to which the chars member of the value argument points is
         copied by this function and the original string memory
         may be freed by the MI right after this function returns
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*addKey) (const CMPIObjectPath* op, const char* name,
            const CMPIValue* value, const CMPIType type);

    /** @brief get a key binding in a CMPIObjectPath object by name.
                                                                   .
     Gets a key binding named key property value.
     @param op Pointer to CMPIObjectPath.
     @param name Key property name.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon
         . return will have been updated with the function return
         status.
     @return If successful, returns a CMPIData structure containing the                                                                     .
     specified key binding                                                                                                                  .
                                                                                                                                            .
     If not successful, returns CMPIData.state will have the CMPI_badValue                                                                  .
     flag set to true.
     
    The MB will attempt to set the type in the returned CMPIData structure 
    to the precise CIM type, if available. Versions of the CIM-XML protocol 
    before DSP0200 Version 1.4 did not mandate the presence of the precise 
    CIM type. In those versions, the precise CIM type was only recommended 
    to be present. If the precise CIM type is not available to the MB, it 
    will use the following more general types in the returned CMPIData 
    structure: 
    <code> 
    #define CMPI_keyInteger   (CMPI_sint64)
    #define CMPI_keyString    (CMPI_string)
    #define CMPI_keyBoolean   (CMPI_boolean)
    #define CMPI_keyRef       (CMPI_ref) 
    </endcode> 
     
    In addition, the CMPI_keyValue flag will be set in CMPIData.state to 
    indicate that the value is a key binding

     */
    CMPIData (*getKey) (const CMPIObjectPath* op, const char* name,
            CMPIStatus* rc);

    /** @brief get a key binding in a CMPIObjectPath object by index.
     
     Gets a key binding value defined by its index.
     @param op Pointer to CMPIObjectPath.
     @param index Zero-based position of the key in the CMPIObjectPath object.
     @param name Output: points to a CMPIString object that upon success will
     have been updated with the name of the key binding. The returned
     CMPIString object shall not be explicitly released by the MI,
     because it may be an internal object of the CMPIObjectPath object
     which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon                                                              .
         return  updated with the function return status.
     @return If successful, returns a CMPIData structure containing the
     specified key binding.
     
    If not successful, CMPIData.state will have the CMPI_badValue flag 
    set to true. 
     
    The MB will attempt to set the type in the returned CMPIData 
    structure to the precise CIM type, if available. Versions of the 
    CIM-XML protocol before DSP0200 Version 1.4 did not mandate 
    the presence of the precise CIM type. In those versions, 
    the precise CIM type was only recommended to be present. 
    If the precise CIM type is not available to the MB, it will 
    use the following more general types in the returned CMPIData structure: 
    <code> 
        #define CMPI_keyInteger   (CMPI_sint64)
        #define CMPI_keyString    (CMPI_string)
        #define CMPI_keyBoolean   (CMPI_boolean)
        #define CMPI_keyRef       (CMPI_ref)
    </code> 
     
    In addition, the CMPI_keyValue flag will be set in CMPIData.state 
    to indicate that the value is a key binding.
     */
    CMPIData (*getKeyAt) (const CMPIObjectPath* op, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief  get the number of key bindings in a CMPIObjectPath object.
                                                                     .
     Gets the number of key bindingscontained in this CMPIObjectPath.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, a CMPICount value indicating the number of                                                                                                                                  .
         key bindings will be returned. If the CMPIObjectPath object                                                                                                                                    .
         does not have a key component, the function will succeed and                                                                                                                                   .
         return 0                                                                                                                                                                                       .
                                                                                                                                                                                                        .
         If not successful, 0 will be returned.
     */
    CMPICount (*getKeyCount) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief ? set or replace the namespace and class name components in a
       CMPIObjectPath object from another CMPIObjectPath object
     
       Set or replace namespace and classname components in CMPIObjectPath
         &lt;op&gt; from CMPIObjectPath &lt;src&gt;.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param src a CMPIObjectPath object used as the source for the new
         namespace and class name components.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*setNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    /** @brief set host name, namespace, and class name components
       in a CMPIObjectPath object from another CMPIObjectPath
       object.
     
       Set/replace hostname, namespace and classname components in the
       CMPIObjectPath &lt;op&gt; from the CMPIObjectPath &lt;src&gt;.
     @param op Pointer to CMPIObjectPath object to be modified..

     @param src CMPIObjectPath object used as the source for the new host name,
         namespace, and class name components.
     @return CMPIStatus structure indicating the function return status .
     */
    CMPIStatus (*setHostAndNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    // optional qualifier support  KS_TODO be sure the optional is clear in doc

    /** @brief Get a class qualifier.
     
     Gets a class qualifier in the class identified by this object path
         This function shall be supported by the MB if the Basic Qualifier
         capability is available; otherwise, it shall not be supported.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param qName Qualifier name.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return is updated with the function return status..
     @return If successful, returns a CMPIData structure containing the
         specified qualifier. If not successful, CMPIData.state
         CMPI_badValue flag set to true
     */
    CMPIData (*getClassQualifier) (const CMPIObjectPath* op,
            const char* qName, CMPIStatus* rc);

    /** @brief Get a property qualifier TODO

     Gets a property qualifier in the class identified by this
     object path. This function shall be supported by the MB if the
     Basic Qualifier.* capability is available; otherwise, it
     shall not be supported.
     @param op Pointer to &lt;CMPIObjectPath&gt;object that references the
         class and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by the MB.
     @param pName Property name.
     @param qName Pointer to a string specifying the qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set 
      to true.
.
     */
    CMPIData (*getPropertyQualifier) (const CMPIObjectPath* op,
            const char* pName, const char* qName, CMPIStatus* rc);

    /** @brief get a method qualifier.
                                                                   .
     Get method qualifier value.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param mName Method name.
     @param qName Qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return Qualifier value. TODO
     */
    CMPIData (*getMethodQualifier) (const CMPIObjectPath* op,
            const char* methodName, const char* qName, CMPIStatus* rc);

    /** @brief get a parameter qualifier.

     Gets a parameter qualifier in the class identified by this
     object path.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param mName Method name.
     @param pName Parameter name.
     @param qName Qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set 
      to true..
     */
    CMPIData (*getParameterQualifier) (const CMPIObjectPath* op,
            const char* mName, const char* pName, const char* qName,
            CMPIStatus* rc);

    /** @brief Convert a CMPIObjectPath object into a string format.
     
     Generates a well formed implementation-specific string representation
     of this CMPIObjectPath.
     @param op Pointer to &lt;CMPIObjectPath&gt;.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to a CMPIString object containing
         the string representation of the object path.
     
     The returned CMPIString object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPIObjectPath
     object which will be released along with that object, or a
     new object created by the MB which will be released automatically
     by the MB 
     
     If not successful, returns NULL.
     */
    CMPIString* (*toString) (const CMPIObjectPath* op, CMPIStatus* rc);

};

/**
 * @brief CMPISelectExp encapsulated data type object.
 */
struct _CMPISelectExp {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPISelectExpFT* ft;

};

/**
 * @brief Function table of
 * [CMPISelectExp encapsulated data type object](@ref _CMPISelectExp).
 */
struct _CMPISelectExpFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPISelectExp object.
     
     The SelectExp object will not be used any further and may be freed by
     CMPI run time system.
     @param se SelectExp this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPISelectExp* se);

    /** @brief create an independent copy of a CMPISelectExp object.

     Create an independent copy of this CMPISelectExp object. The resulting
         object must be released explicitly.
     @param se Pointer to CMPISelectExp to clone.
     @param rc Output: Service return status (suppressed when NULL).
     @return If not NULL points to copied SelectExp object.
     */
    CMPISelectExp* (*clone) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief test whether an instance matches the select
       expression in a CMPISelectExp object.

     Evaluates the instance &ltinst& using this select expression.
     This unction shall be supported by the MB if the Query Normalization     
        capability is available); otherwise, it shall not be supported
     @param se Pointer to CMPISelectExp.
     @param inst Instance to be evaluated.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returnsCMPIBoolean value indicating the test result
     as follows: True indicates that the instance matches the select
     expression; False indicates that this is not the case.

     If not successful, False will be returned.
     */
    CMPIBoolean (*evaluate) (const CMPISelectExp* se, const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief get the select expression in a CMPISelectExp object as a string

     Return the select expression in string format
     
     This function shall be supported by the MB if the Query Normalization
     capability is available; otherwise, it shall not be supported
     @param se SelectExp this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, returns a pointer to a CMPIString object cointaining
         the select expression in string format.
     
     The returned CMPIString object shall not be explicitly released by
     the MI, because it may be an internal object of the CMPISelectExp
     object which will be released along with that object, or a new
     object created by the MB which will be released automatically by the MB.
     
     If not successful, returns NULL.
     */
    CMPIString* (*getString) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief get the select expression in a CMPISelectExp object
       as a disjunction of conjunctions.

     Return the select expression as disjunction of conjunctions.
     
     This function shall be supported by the MB if the Query Normalization
     capability is available.

     @param se SelectExp this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status..
     @return If successful, returns a pointer to a CMPISelectCond object
     containing the transformed select expression.
     
     The returned CMPISelectCond object shall not be explicitly released
     by the MI, because it may be an internal object of the
     CMPISelectExp object which will be released along with that
     object, or a new object created by the MB which will be
     released automatically by the MB.
     
    If not successful, NULL will be returned.

     */
    CMPISelectCond* (*getDOC) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief get the select expression in a CMPISelectExp object as a
       conjunction of disjunctions.
     
     Return the select expression as conjunction of disjunctions.
     
     This function shall be supported by the MB if the Query Normalization
     capability is available.
     @param se SelectExp this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, returns a pointer to a CMPISelectCond object
     containing the transformed select expression.
     
     The returned CMPISelectCond object shall not be explicitly released
     by the MI, because it may be an internal object of the
     CMPISelectExp object which will be released along with that
     object, or a new object created by the MB which will be
     released automatically by the MB.
     
    If not successful, NULL will be returned.
     */
    CMPISelectCond* (*getCOD) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief test whether the properties returned by an accessor
           function match the select expression in a CMPISelectExp
           object.

     This function tests whether the properties returned by an accessor
     function match the select expression in a CMPISelectExp object.
     This function is a variation of CMPISelectExpFT.evaluate(). it enables
     evaluation without the need to create a CMPIInstance object
     
     This function shall be supported by the MB if the Query Normalization
     capability is available.
     @param se SelectExp this pointer.
     @param accessor Address of data accessor routine.
     @param parm Data accessor routine parameter.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status..
     @return If successful, returns a CMPIBoolean value indicating the test
     result will be returned, as follows: True indicates that the
     properties returned by the accessor function match the select
     expression; False indicates that this is not the case.
     
     If not successful, False will be returned
.
     */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPISelectExp* se,
            CMPIAccessor* accessor, void* parm, CMPIStatus* rc);

};

/**
 * @brief CMPISelectCond encapsulated data type object.
 */
struct _CMPISelectCond {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPISelectCondFT* ft;

};

/**
 * @brief Function table of
 * [CMPISelectCond encapsulated data type object](@ref _CMPISelectCond).
 */
struct _CMPISelectCondFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a &lt;CMPISelectCond&gt; object.
     
     The SelectCond object will not be used any further and may be freed by
     CMPI run time system.
     @param sc SelectCond this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPISelectCond* sc);

    /** @brief create an independent copy of a
               &lt;CMPISelectCond&gt; object.
     
     *Create an independent copy of this SelectCond object. The resulting
     object must be released explicitly. KS_TODO
     @param sc SelectCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied SelectExp object.
     */
    CMPISelectCond* (*clone) (const CMPISelectCond* sc, CMPIStatus* rc);

    /** @brief get the number and type of subconditions in a
       CMPISelectCond object.

     Return the number of subconditions that are part of this SelectCond.
     Optionally, the SelectCond type (COD or DOC) will be returned. KS_TODO

     This function shall be supported by the MB if the Query Normalization     
        capability is available; otherwise, it shall not be
        supported.
     @param sc SelectCond this pointer.
     @param type Output: SelectCond type (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPICount value indicating the number of
     subconditions.
     
     If not successful, returns 0.
.
     */
    CMPICount (*getCountAndType) (const CMPISelectCond* sc, int* type,
            CMPIStatus* rc);

    /** @brief get a subcondition in a CMPISelectCond object by
               index.

     Return a SubCond element based on its index.
     
     This function shall be supported by the MB if the Query Normalization     
        capability is available; otherwise, it shall not be supported.
     @param sc SelectCond this pointer.
     @param index Position in the internal SubCoind array.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to the specified CMPISubCond
     object will be returned.
     
     The returned CMPISubCond object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPISelectCond
     object which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB.
     
     If not successful, NULL will be returned.

     */
    CMPISubCond* (*getSubCondAt) (const CMPISelectCond* sc, CMPICount index,
            CMPIStatus* rc);

};

/**
 * @brief CMPISubCond encapsulated data type object.
 */
struct _CMPISubCond {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPISubCondFT* ft;

};

/**
 * @brief Function table of
 * [CMPISubCond encapsulated data type object](@ref _CMPISubCond).
 */
struct _CMPISubCondFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a &lt;CMPISubCond&gt; object.
     
     The SubCond object will not be used any further and may be freed by
     CMPI run time system.
     @param sc SubCond this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPISubCond* sc);

    /** @brief create an independent copy of a &lt;CMPISubCond&gt;
               object.
     
     Create an independent copy of this SubCond object. The resulting
     object must be released explicitly.
     @param se SubCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied SelectExp object.
     */
    CMPISubCond* (*clone) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief get the number of predicates in a CMPISubCond object.

     Return the number of predicates that are part of sub condition.
     
     This function shall be supported by the MB if the Query Normalization
     capability is available; otherwise, it shall
     not be supported. KS_TODO add to others
     @param sc SubCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Number of Predicate elements.
     */
    CMPICount (*getCount) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief get a predicate in a &lt;CMPISubCond&gt object by index.

     Return a Predicate element based on its index. KS_TOD word
     predicate
     
     This function shall be supported by the MB if the Query Normalization
         capability is available; otherwise, it shall not be supported.
     @param sc SubCond this pointer.
     @param index Position in the internal Predicate array.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIPredicate object
         containing the specified predicate will be returned.
     
         The returned CMPIPredicate object shall not be explicitly
         released by the MI, because it may be an internal object of
         the CMPISubCond object which will be released along with that
         object, or a new object created by the MB which will be released
         automatically by the MB.
     
         If not successful, NULL will be returned.

     */
    CMPIPredicate* (*getPredicateAt) (const CMPISubCond* sc, CMPICount index,
            CMPIStatus* rc);

    /** @brief get a predicate in a &lt;CMPISubCond&gt; object by name.

     Returns a predicate element in a &lt;CMPISubCond&gt; based on name
     in &lt;name&gt;
     
     This function shall be supported by the MB if the Query Normalization
         capability is available; otherwise, it shall not be supported.
     @param sc SubCond this pointer.
     @param name Predicate name (property name).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIPredicate object
     containing the specified predicate.
     
     The returned CMPIPredicate object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPISubCond
     object which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB.
     
     If not successful, returns NULL.
     */
    CMPIPredicate* (*getPredicate) (const CMPISubCond* sc, const char* name,
            CMPIStatus* rc);

};

/**
 * @brief CMPIPredicate encapsulated data type object.
 */
struct _CMPIPredicate {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIPredicateFT* ft;

};

/**
 * @brief Function table of
 * [CMPIPredicate encapsulated data type object](@ref _CMPIPredicate).
 */
struct _CMPIPredicateFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPPredicate object.
     
     The Predicate object will not be used any further and may be freed by
     CMPI run time system.
     @param pr Predicate this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIPredicate* pr);

    /* @brief create an independent copy of a CMPIPredicate object.

     Create an independent copy of this Predicate object. The resulting
     object must be released explicitly.
     @param pr Predicate this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Predicate object.
     */
    CMPIPredicate* (*clone) (const CMPIPredicate* pr, CMPIStatus* rc);

    /** @brief get the predicate components of a CMPIPredicate object.

     Get the predicate components. KS_TODO

     @param pr Predicate this pointer.
     @param type Property type.
     @param prop Predicate operation.
     @param lhs Left hand side of predicate.
     @param rhs Right hand side of predicate.
     @return Service return status.
     */
    CMPIStatus (*getData) (const CMPIPredicate* pr, CMPIType* type,
            CMPIPredOp* prop, CMPIString** lhs, CMPIString** rhs);

    /** @brief test whether the properties returned by an accessor
           function match the predicate in a CMPIPredicate object.
     
     Evaluate the predicate using a property data accessor function.
     
     @param pr Predicate this pointer.
     @param accessorFnc Pointer to a property value accessor
     function. The evaluation process will invoke this function to
     request a CMPIData structure for a particular property. The
     signature of the accessor function is: CMPIData
     CMPIAccessor(const char* propertyName, void* parm);
     @param parm Parameter that will be passed to the accessor function and
     can be used for providing context data to the accessor function.
     @param rc Output: Service return status (suppressed when NULL).
     @return Evaluation result.
     */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPIPredicate* pr,
            CMPIAccessor* accessorFnc, void* parm, CMPIStatus* rc);

};

/**
 * @brief CMPIArgs encapsulated data type object.
 */
struct _CMPIArgs {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIArgsFT* ft;

};

/**
 * @brief Function table of
 * [CMPIArgs encapsulated data type object](@ref _CMPIArgs).
 */
struct _CMPIArgsFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPIArgs object.
     
     The Args object will not be used any further and may be freed by
     CMPI run time system.
     @param as Args this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIArgs* as);

    /** @brief create an independent copy of a CMPIResult object.

     Create an independent copy of this Args object. The resulting
     object must be released explicitly.
     @param as Args this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Args object.
     */
    CMPIArgs* (*clone) (const CMPIArgs* as, CMPIStatus* rc);

    /** @brief set a method parameter in a CMPIArgs object.

     Adds or replaces a method parameter in a CMPIArgs object.
     @param as Args this pointer.
     @param name Argument name.
     @param value CMPIValue structure containing the non-NULL value to be
         assigned to the method parameter, or is NULL to specify
         that NULL is to be assigned.
     @param type type of the method parameter. All types of CIM values are
         supported 
     @return CMPIStatus structure indicating the function return status.
     */
    CMPIStatus (*addArg) (const CMPIArgs* as, const char* name,
            const CMPIValue* value,
            const CMPIType type);

    /** @brief get a method parameter in a CMPIArgs object by name.

     This function gets a method parameter in a CMPIArgs object,
        by its name..
     @param as Args this pointer.
     @param name Argument name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a CMPIData structure containing the
     specified method parameter.
     
    If not successful, CMPIData.state will have the CMPI_badValue flag 
    set to true
.
     */
    CMPIData (*getArg) (const CMPIArgs* as, const char* name, CMPIStatus* rc);

    /** @brief get a method parameter in a CMPIArgs object by index.

     Gets a Argument value defined by its index.
     @param as Args this pointer.
     @param index Position in the internal Data array.
     @param name Output: Returned argument name (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.
     
    If not successful, CMPIData.state will have the CMPI_badValue flag 
    set to true
     */
    CMPIData (*getArgAt) (const CMPIArgs* as, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief get a method parameter in a CMPIArgs object by index.

     Gets the number of arguments contained in this CMPIArgs object.
     @param as Args this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.
     
    If not successful, CMPIData.state will have the CMPI_badValue flag 
    set to true
     */
    CMPICount (*getArgCount) (const CMPIArgs* as, CMPIStatus* rc);
};

/**
 * @brief CMPIString encapsulated data type object.
 */
struct _CMPIString {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIStringFT* ft;

};

/**
 * @brief Function table of
 * [CMPIString encapsulated data type object](@ref _CMPIString).
 */
struct _CMPIStringFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  Release a CMPIString object.

     The String object will not be used any further and may be freed by
     CMPI run time system.
     @param st String this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIString* st);

    /**
     Create an independent copy of this String object. The resulting
     object must be released explicitly.
     @param st Pointer to CMPIString object.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied String object.
     */
    CMPIString* (*clone) (const CMPIString* st, CMPIStatus* rc);

    /** @brief get a pointer to a C-language string representation of a
       CMPIString object.

     Get a pointer to a C char* representation of this CMPIString object.
     @param st Pointer to CMPIString object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a C-language string
     will be returned. KS_TODO ref to where defined.
     
     The character array of the returned string shall not be explicitly
     released by the MI, because it may point to an internal data area in the
     CMPIString object which will be released along with that object, or it
     may point to a new character array created by the MB which will be
     released automatically by the MB.
     
     If not successful, NULL will be returned.
     */
    const char* (*getCharPtr) (const CMPIString* st, CMPIStatus* rc);

#ifdef CMPI_VER_210

    /* @brief create a C-language string that has converted a CMPIString
           object into a specific codepage
     
     Creates a new C-language string (see Subclause 5.2.1) that contains
     the string in a CMPIString object, converted into a specific codepage.
     
     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.
     
     @param str Pointer to the CMPIString object for this function.
     @param cpid &lt;CMPICodePageID&gt; specifies the CMPI-specific codepage
         ID for the codepage to convert to. See the CMPI Specification
         section 5.2.2 (CodePage for a list of supported codepages and their codepage
         ID values.
     @param rc , If not NULL, points to a CMPIStatus structure that upon
     return has been updated with the function return status.
     @return If successful, returns a new C-language string, in the codepage
     specified in the cpid argument.
     The returned C-language string must be freed by the MI using
     &lt;CMPIBrokerMemFT.freeChars()&gt;.
     
     If not successful, NULL will be returned.
     @version CMPI specification 2.1
     */
    char* (*newCharsCP) (const CMPIString* str, const CMPICodepageID cpid,
            CMPIStatus* rc);

#endif // CMPI_VER_210

};

/**
 * @brief CMPIArray encapsulated data type object.
 */
struct _CMPIArray {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIArrayFT* ft;

};

/**
 * @brief Function table of
 * [CMPIArray encapsulated data type object](@ref _CMPIArray).
 */
struct _CMPIArrayFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a &lt;CMPIArray&gt; object.

     The Array object will not be used any further and may be freed by
     CMPI run time system.
     @param ar Pointer to this &lt;CMPIArray&gt;.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIArray* ar);

    /** @brief create an independent copy of a &lt;CMPIArray&gt; object.

     Create an independent copy of this Array object. The resulting
     object must be released explicitly.
     @param ar Pointer to this &lt;CMPIArray&gt; object.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Array object.
     */
    CMPIArray* (*clone) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief get the number of array elements in a CMPIArray
               object.
     
     Gets the number of elements contained in this Array.
     @param ar Array this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
     upon return has been updated with the function return status.
     @return If successful, a CMPICount value indicating the number of
         array elements will be returned.
     
         If not successful, 0 will be returned
.
     */
    CMPICount (*getSize) (const CMPIArray* ar, CMPIStatus* rc);

    /** TODO: Sync description with spec. KS_TODO not in spec
     * Gets the element type.
     @param ar Array this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Number of elements.
     */
    CMPIType (*getSimpleType) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief get the value of an array element in a CMPIArray
               object by index.

     Gets the value of an array element defined by the zero-based position
     &lt;index&gt; of the array element in a CMPIArray object &lt;ar&gt;.
     @param ar Pointer to the CMPIArray for this function.
     @param index Zero-based position in the CMPIArray. The position shall
         be equal to or greater than 0 and less than the size of the array.
         Returns error if index out of range of the array.
     @param rc Output: if not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful, returns a CMPIData structure containing the
         specified array element.
     
         If not successful, CMPIData.state will have the CMPI_badValue flag
         set to true
     */
    CMPIData (*getElementAt) (const CMPIArray* ar, CMPICount index,
            CMPIStatus* rc);

    /* TODO: Sync description with spec.
     * Sets an element value defined by its index.
     @param ar Array this pointer.
     @param index Position in the internal Data array.
     @param value Address of value structure.
     @param type Value type.
     @return Service return status.
     */
    CMPIStatus (*setElementAt) (const CMPIArray* ar, CMPICount index,
            const CMPIValue* value, CMPIType type);
};

/**
 * @brief CMPIEnumeration encapsulated data type object.
 */
struct _CMPIEnumeration {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIEnumerationFT* ft;

};

/**
 * @brief Function table of
 * [CMPIEnumeration encapsulated data type object](@ref _CMPIEnumeration).
 */
struct _CMPIEnumerationFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** TODO: Sync description with spec.
     * The Enumeration object will not be used any further and may be freed by
     CMPI run time system.
     @param en Enumeration this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIEnumeration* en);

    /** TODO: Sync description with spec.
     * Create an independent copy of this Enumeration object. The resulting
     object must be released explicitly.
     @param en Enumeration this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Enumeration object.
     */
    CMPIEnumeration* (*clone) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Get the next element of this Enumeration.
     @param en Enumeration this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Element value.
     */
    CMPIData (*getNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Test for any elements left in this Enumeration.
     @param en Enumeration this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return True or false.
     */
    CMPIBoolean (*hasNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Convert this Enumeration into an Array.
     @param en Enumeration this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return The Array.
     */
    CMPIArray* (*toArray) (const CMPIEnumeration* en, CMPIStatus* rc);
};

/**
 * @brief CMPIDateTime encapsulated data type object.
 */
struct _CMPIDateTime {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIDateTimeFT* ft;

};

/**
 * @brief Function table of
 * [CMPIDateTime encapsulated data type object](@ref _CMPIDateTime).
 */
struct _CMPIDateTimeFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** TODO: Sync description with spec.
     * The DateTime object will not be used any further and may be freed by
     CMPI run time system.
     @param dt DateTime this pointer.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIDateTime* dt);

    /** TODO: Sync description with spec.
     * Create an independent copy of this DateTime object. The resulting
     object must be released explicitly.
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied DateTime object.
     */
    CMPIDateTime* (*clone) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Get DateTime setting in binary format (in microsecods
     starting since 00:00:00 GMT, Jan 1,1970).
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return DateTime in binary.
     */
    CMPIUint64 (*getBinaryFormat) (const CMPIDateTime* dt,
            CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Get DateTime setting in UTC string format.
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return DateTime as UTC string.
     */
    CMPIString* (*getStringFormat) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** TODO: Sync description with spec.
     * Tests whether DateTime is an interval value.
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return True if interval value.
     */
    CMPIBoolean (*isInterval) (const CMPIDateTime* dt, CMPIStatus* rc);
};

#ifdef CMPI_VER_210

/**
 * @brief CMPIPropertyList encapsulated data type object.
 */
struct _CMPIPropertyList {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIPropertyListFT* ft;

};

/**
 * @brief Function table of
 * [CMPIPropertyList encapsulated data type object](@ref _CMPIPropertyList).
 */
struct _CMPIPropertyListFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** TODO: Add description
     */
    CMPIStatus (*release) (CMPIPropertyList* plist);

    /** TODO: Add description
     */
    CMPIPropertyList* (*clone) (const CMPIPropertyList* plist, CMPIStatus* rc);

    /** TODO: Add description
     */
    CMPIBoolean (*isPropertyInList) (const CMPIPropertyList* plist,
            const char* pname, CMPIStatus* rc);

    /** TODO: Add description
     */
    const char** (*getProperties) (const CMPIPropertyList* plist,
            CMPIStatus* rc);

};

/**
 * @brief CMPIEnumerationFilter encapsulated data type object.
 */
struct _CMPIEnumerationFilter {

    /**
     * Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this object.
     */
    const CMPIEnumerationFilterFT* ft;

};

/**
 * @brief Function table of
 * [CMPIEnumerationFilter encapsulated data type object]
 * (@ref _CMPIEnumerationFilter).
 */
struct _CMPIEnumerationFilterFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** TODO: Add description
     */
    CMPIStatus (*release) (CMPIEnumerationFilter* ef);

    /** TODO: Add description
     */
    CMPIEnumerationFilter* (*clone) (const CMPIEnumerationFilter* ef,
            CMPIStatus* rc);

    /** TODO: Add description
     */
    CMPIBoolean (*match) (const CMPIEnumerationFilter* ef,
            const CMPIInstance* inst, CMPIStatus* rc);

};

#endif // CMPI_VER_210

/**
 * @}
 */

/**
 * @defgroup mi-functions MI functions
 * @{
 */

/**
 * @brief CMPIInstanceMI object.
 *
 * This object is provided by an instance MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 */
typedef struct _CMPIInstanceMI {

    /**
     * Opaque pointer to MB-specific implementation data for this MI object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this MI object.
     */
    const CMPIInstanceMIFT* ft;

} CMPIInstanceMI;

/**
 * @brief Function table of @ref CMPIInstanceMI object.
 */
struct _CMPIInstanceMIFT {

    /**
     * CMPI version supported by the MI for this function table.
     * Any later CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * Informal MI-specific version number for this MI
     */
    int miVersion;

    /**
     * Informal MI-specific name for this MI
     */
    const char* miName;

    /** TODO: Sync description with spec.
     * The CMPIInstanceMIFT.cleanup() function shall perform any necessary
     cleanup operation prior to the unloading of the library of which this MI
     group is part.
     This function is called prior to the unloading of the provider.
     @param mi The mi argument is a pointer to a CMPIInstanceMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param terminating When true, the terminating argument indicates that
     the MB is in the process of terminating and that cleanup must be done.
     When set to false, the MI may respond with CMPI_IRC_DO_NOT_UNLOAD, or
     CMPI_IRC_NEVER_UNLOAD, indicating that unload will interfere with current
     MI processing.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_DO_NOT_UNLOAD Operation successful - do not unload now.
     CMPI_RC_NEVER_UNLOAD Operation successful -  never unload.o
     */
    CMPIStatus (*cleanup) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** TODO: Sync description with spec.
     * Enumerate ObjectPaths of Instances serviced by this provider.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace and classname components.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*enumerateInstanceNames) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* op);

    /** TODO: Sync description with spec.
     * Enumerate the Instances serviced by this provider.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace and classname components.
     @param properties If not NULL, the members of the array define one or
     more Property names. Each returned Object MUST NOT include elements
     for any Properties missing from this list.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*enumerateInstances) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* op, const char** properties);

    /** TODO: Sync description with spec.
     * Get the Instances defined by &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace, classname and key components.
     @param properties If not NULL, the members of the array define one or
     more Property names. Each returned Object MUST NOT include elements
     for any Properties missing from this list.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*getInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char** properties);

    /** TODO: Sync description with spec.
     * Create Instance from &lt;inst&gt; using &lt;op&gt; as reference.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace, classname and key components.
     @param inst The Instance.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ALREADY_EXISTS Instance already exists.
     */
    CMPIStatus (*createInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const CMPIInstance* inst);

    /** TODO: Sync description with spec.
     * Replace an existing Instance from &lt;inst&gt; using &lt;op&gt; as reference.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace, classname and key components.
     @param inst The Instance.
     @param properties If not NULL, the members of the array define one or
     more Property names. The process MUST NOT replace elements
     for any Properties missing from this list. If NULL all properties
     will be replaced.
     @return Function return status.
     */
    CMPIStatus (*modifyInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const CMPIInstance* inst, const char** properties);

    /** TODO: Sync description with spec.
     * Delete an existing Instance defined by &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context.
     @param rslt Result data container.
     @param op ObjectPath containing namespace, classname and key components.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*deleteInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op);

    /** TODO: Sync description with spec.
     * Query the enumeration of instances of the class (and subclasses) defined
     by &lt;op&gt; using &lt;query&gt; expression.
     @param mi Provider this pointer.
     @param ctx Context object
     @param rslt Result data container.
     @param op ObjectPath containing namespace and classname components.
     @param query Query expression
     @param lang Query language
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED Query language not supported.
     CMPI_RC_ERR_INVALID_QUERY Invalid query.
     */
    CMPIStatus (*execQuery) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* query, const char* lang);

};

/**
 * @brief CMPIAssociationMI object.
 *
 * This object is provided by an association MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 */
typedef struct _CMPIAssociationMI {

    /**
     * Opaque pointer to MB-specific implementation data for this MI object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this MI object.
     */
    const CMPIAssociationMIFT* ft;

} CMPIAssociationMI;

/**
 * @brief Function table of @ref CMPIAssociationMI object.
 */
struct _CMPIAssociationMIFT {

    /**
     * CMPI version supported by the MI for this function table.
     * Any later CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * Informal MI-specific version number for this MI
     */
    int miVersion;

    /**
     * Informal MI-specific name for this MI
     */
    const char* miName;

    /** TODO: Sync description with spec.
     * Cleanup is called prior to unloading of the provider.
     This function shall perform any necessary cleanup
     operations prior to the unloading of the library of which this MI group is part.
     @param mi This argument is a pointer to a CMPIAssociationMI structure.
     @param ctx This argument is a pointer to a CMPIContext structure containing the Invocation Context.
     @param terminating When true, the terminating argument indicates that the MB is in the process of
     terminating and that cleanup must be done. When set to false, the MI may respond with
     CMPI_IRC_DO_NOT_UNLOAD, or CMPI_IRC_NEVER_UNLOAD, indicating that unload will
     interfere with current MI processing.
     @return Function return status. The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_DO_NOT_UNLOAD Operation successful - do not unload now.
     CMPI_RC_NEVER_UNLOAD Operation successful - never unload.
     */
    CMPIStatus (*cleanup) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** TODO: Sync description with spec.
     * Enumerate ObjectPaths associated with the Instance defined by &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param op Source ObjectPath containing namespace, classname and key components.
     @param assocClass If not NULL, MUST be a valid Association Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be associated to the source Object via an
     Instance of this Class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param resultRole If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the returned Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers to
     @param properties If not NULL, the members of the array define one or more Property
     names. Each returned Object MUST NOT include elements for any Properties
     missing from this list. If NULL all properties must be returned.
     the returned Object MUST match the value of this parameter).
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*associators) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* asscClass, const char* resultClass, const char* role,
            const char* resultRole, const char** properties);

    /** TODO: Sync description with spec.
     * Enumerate ObjectPaths associated with the Instance defined by &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param op Source ObjectPath containing namespace, classname and key components.
     @param assocClass If not NULL, MUST be a valid Association Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be associated to the source Object via an
     Instance of this Class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param resultRole If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the returned Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers to
     the returned Object MUST match the value of this parameter).
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*associatorNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* op, const char* assocClass,
            const char* resultClass, const char* role,
            const char* resultRole);

    /** TODO: Sync description with spec.
     * Enumerates the association instances that refer to the instance defined by
     &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param op Source ObjectPath containing namespace, classname and key components.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @param properties If not NULL, the members of the array define one or more Property
     names. Each returned Object MUST NOT include elements for any Properties
     missing from this list
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*references) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* resultClass, const char* role,
            const char** properties);

    /** TODO: Sync description with spec.
     * Enumerates the association ObjectPaths that refer to the instance defined by
     &lt;op&gt;.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param op Source ObjectPath containing namespace, classname and key components.
     @param resultClass If not NULL, MUST be a valid Class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an Instance of this Class (or one
     of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
     It acts as a filter on the returned set of Objects by mandating
     that each returned Object MUST be associated to the source Object
     via an Association in which the source Object plays the specified role
     (i.e. the name of the Property in the Association Class that refers
     to the source Object MUST match the value of this parameter).
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     */
    CMPIStatus (*referenceNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* op, const char* resultClass,
            const char* role);

};

/**
 * @brief CMPIMethodMI object.
 *
 * This object is provided by a method MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 */
typedef struct _CMPIMethodMI {

    /**
     * Opaque pointer to MB-specific implementation data for this MI object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this MI object.
     */
    const CMPIMethodMIFT* ft;

} CMPIMethodMI;

/**
 * @brief Function table of @ref CMPIMethodMI object.
 */
struct _CMPIMethodMIFT {

    /**
     * CMPI version supported by the MI for this function table.
     * Any later CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * Informal MI-specific version number for this MI
     */
    int miVersion;

    /**
     * Informal MI-specific name for this MI
     */
    const char* miName;

    /** TODO: Sync description with spec.
     * The CMPIMethodMIFT.cleanup() function shall perform any necessary cleanup operation
     prior to the unloading of the library of which this MI group is part. This function is called
     prior to the unloading of the provider.

     @param mi The mi argument is a pointer to a CMPIMethodMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure containing the Invocation
     Context.
     @param terminating When true, the terminating argument indicates that the MB is in the process of
     terminating and that cleanup must be done. When set to false, the MI may respond with
     CMPI_IRC_DO_NOT_UNLOAD, or CMPI_IRC_NEVER_UNLOAD, indicating that unload will
     interfere with current MI processing.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_DO_NOT_UNLOAD Operation successful - do not unload now.
     CMPI_RC_NEVER_UNLOAD Operation successful - never unload.
     */
    CMPIStatus (*cleanup) (CMPIMethodMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** TODO: Sync description with spec.
     * Invoke a named, extrinsic method of an Instance
     defined by the &lt;op&gt; parameter.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param objPath ObjectPath containing namespace, classname and key components.
     @param method Method name
     @param in Input parameters.
     @param out Output parameters.
     @return Function return status. The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     CMPI_RC_ERR_METHOD_NOT_AVAILABLE Method not available.
     CMPI_RC_ERR_METHOD_NOT_FOUND Method not found.
     */
    CMPIStatus (*invokeMethod) (CMPIMethodMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* objPath,
            const char* method, const CMPIArgs* in, CMPIArgs* out);

};

/**
 * @brief CMPIPropertyMI object.
 *
 * This object is provided by a property MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 *
 * Note: Property MIs are deprecated in CMPI.
 */
typedef struct _CMPIPropertyMI {

    /**
     * Opaque pointer to MB-specific implementation data for this MI object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this MI object.
     */
    const CMPIPropertyMIFT* ft;

} CMPIPropertyMI;

/**
 * @brief Function table of @ref CMPIPropertyMI object.
 */
struct _CMPIPropertyMIFT {

    /**
     * CMPI version supported by the MI for this function table.
     * Any later CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * Informal MI-specific version number for this MI
     */
    int miVersion;

    /**
     * Informal MI-specific name for this MI
     */
    const char* miName;

    /** TODO: Sync description with spec.
     * Cleanup is called prior to unloading of the provider.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param terminating When true, the terminating argument indicates that the MB is in the process of
     terminating and that cleanup must be done. When set to false, the MI may respond with
     CMPI_IRC_DO_NOT_UNLOAD, or CMPI_IRC_NEVER_UNLOAD, indicating that unload will
     interfere with current MI processing.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_DO_NOT_UNLOAD Operation successful - do not unload now.
     CMPI_RC_NEVER_UNLOAD Operation successful  -  never unload.
     */
    CMPIStatus (*cleanup) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** TODO: Sync description with spec.
     * Set the named property value of an Instance defined by the &lt;op&gt; parameter.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param op ObjectPath containing namespace, classname and key components.
     @param name Property name
     @param data Property value.
     @return Function return status. The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_TYPE_MISATCH type does not correspond to class-defined type.
     CMPI_RC_ERR_INVALID_HANDLE The inst handle is invalid.
     */
    CMPIStatus (*setProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op, const char* name,
            const CMPIData data);

    /** TODO: Sync description with spec.
     * Get the named property value of an Instance defined by the &lt;op&gt; parameter.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param instPath ObjectPath containing namespace, classname and key components.
     @param name Property name
     @return Function return status. The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_INVALID_NAMESPACE The namespace is invalid.
     CMPI_RC_ERR_INVALID_PARAMETER The parameter is invalid.
     CMPI_RC_ERR_INVALID_CLASS The CIM class does not exist in the specified
     namespace.
     CMPI_RC_ERR_NOT_FOUND Instance not found.
     CMPI_RC_ERR_NO_SUCH_PROPERTY Entry not found.
     */
    CMPIStatus (*getProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* instPath,
            const char* name);

#ifdef CMPI_VER_200

    /** TODO: Sync description with spec.
     * add/replace a named Property value and origin
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param instPath ObjectPath containing namespace, classname and
     key components
     @param name Property name
     @param data Property value.
     @param origin specifies the instance origin.  If NULL, then
     no origin is attached to  the property
     @return Service return status
     */
    CMPIStatus (*setPropertyWithOrigin) (CMPIPropertyMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            CMPIObjectPath* instPath, const char* name, const CMPIData data,
            const char* origin);

#endif // CMPI_VER_200

};

/**
 * @brief CMPIIndicationMI object.
 *
 * This object is provided by an indication MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 */
typedef struct _CMPIIndicationMI {

    /**
     * Opaque pointer to MB-specific implementation data for this MI object.
     */
    const void* hdl;

    /**
     * Pointer to the function table for this MI object.
     */
    const CMPIIndicationMIFT* ft;

} CMPIIndicationMI;

/**
 * @brief Function table of @ref CMPIIndicationMI object.
 */
struct _CMPIIndicationMIFT {

    /**
     * CMPI version supported by the MI for this function table.
     * Any later CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * Informal MI-specific version number for this MI
     */
    int miVersion;

    /**
     * Informal MI-specific name for this MI
     */
    const char* miName;

    /** TODO: Sync description with spec.
     * Cleanup is called prior to unloading of the provider.
     This function shall perform any necessary cleanup
     operation prior to the unloading of the library of which this MI group is part.

     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param terminating When true, the terminating argument indicates that
     the MB is in the process of terminating and that cleanup must be done.
     When set to false, the MI may respond with
     CMPI_RC_DO_NOT_UNLOAD, or CMPI_RC_NEVER_UNLOAD, indicating that
     unload will interfere with current MI processing.
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_DO_NOT_UNLOAD Operation successful do not unload now.
     CMPI_RC_NEVER_UNLOAD Operation successful never unload
     */
    CMPIStatus (*cleanup) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** TODO: Sync description with spec.
     * Ask the provider to verify whether this filter is allowed.
     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param filter Contains the filter that must be authorized.
     @param className Contains the class name extracted from the filter FROM
     clause.
     @param op The name of the class for which monitoring is required. Only
     the namespace part is set if className is a process indication.
     @param owner The owner argument is the destination owner.
     @return This function shall structure containing the service return
     status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_INVALID_QUERY Invalid query or too complex.
     */
    CMPIStatus (*authorizeFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx,  const CMPISelectExp* filter,
            const char* className,  const CMPIObjectPath* op,
            const char* owner);

    /** TODO: Sync description with spec.
     * Ask the MI whether polling mode should be used.
     This function enables very simple MIs to support indications without
     providing a complete indication support implementation. When true
     is returned, the MB will enumerate the instances of this MI at
     regular intervals and apply indication filters.
     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param className The class name extracted from the filter FROM clause.
     @param filter  The name of the class for which monitoring is required.
     Only the namespace part is set if eventType is a process indication.
     @param classPath The name of the class for which polling would be used.
     Only the namespace part is set if  className is a process indication.
     @return This function shall return a CMPIStatus structure containing
     the service return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_INVALID_QUERY Invalid query or too complex.
     */
    CMPIStatus (*mustPoll) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            const CMPISelectExp* filter, const char* className,
            const CMPIObjectPath* classPath);

    /** TODO: Sync description with spec.
     * Ask the provider to begin monitoring a resource.
     The function shall begin monitoring the resource according to the
     filter express only.
     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param filter The filter argument contains the filter specification for
     this subscription to become active.
     @param className The class name extracted from the filter FROM clause.
     @param classPath The name of the class for which monitoring is required.
     Only the namespace part is set if eventType is a process indication.
     @param firstActivation Set to true if this is the first filter for
     className.
     @return The function shall return a CMPIStatus structure containing
     the service return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_INVALID_QUERY Invalid query or too complex.
     */
    CMPIStatus (*activateFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPISelectExp* filter,
            const char* className, const CMPIObjectPath* classPath,
            CMPIBoolean firstActivation);

    /** TODO: Sync description with spec.
     * Inform the MI that monitoring using this filter should stop.
     The function invocation mandates the MI to stop monitoring the resource
     using this filter.
     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param filter The filter argument contains the filter specification for
     this subscription to become active.
     @param className The class name extracted from the filter FROM clause.
     @param classPath The name of the class for which monitoring is required.
     Only the namespace part is set if className is a process indication.
     @param lastActiviation Set to true if this is the last filter for
     className.
     @return The function shall return a CMPIStatus structure containing the
     service return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     CMPI_RC_ERR_ACCESS_DENIED Not authorized.
     CMPI_RC_ERR_INVALID_QUERY Invalid query or too complex.
     */
    CMPIStatus (*deActivateFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPISelectExp* filter,
            const char* className, const CMPIObjectPath* classPath,
            CMPIBoolean lastDeActiviation);

    /** TODO: Sync description with spec.
     * Tell the MI that indications can now be generated.  The MB is now
     prepared
     to process indications. The function is normally called by the MB
     after having done its intialization and processing of persistent
     subscription requests.
     @param mi The mi argument is a pointer to a CMPIIndicationMI
     structure.
     @param ctx The ctx argument is a pointer to a CMPIContext
     structure containing the Invocation Context.
     @return The function shall return a CMPIStatus structure containing the
     service return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     */
    CMPIStatus (*enableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** TODO: Sync description with spec.
     * Tell the MI to stop generating indications.  MB will not accept any
     indications until enabled again. The function is normally called
     when the MB is shutting down indication services either temporarily
     or permanently.
     @param mi The mi argument is a pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @return The function shall return a CMPIStatus structure containing the
     service return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     */
    CMPIStatus (*disableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** TODO: Add description from spec. */
    CMPIStatus (*authorizeFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst);

    /** TODO: Add description from spec. */
    CMPIStatus (*activateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean firstActivation);

    /** TODO: Add description from spec. */
    CMPIStatus (*deActivateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean lastDeActivation);
};

/**
 * @}
 */

#include "cmpimacs.h"

#ifdef __cplusplus
}
#endif

#endif // _CMPIFT_H_
