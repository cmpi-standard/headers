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
 * @addtogroup mb-tables
 * @{
 */

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

#endif /*CMPI_VER_200*/

};

/**
 * @brief Function table for some MB services of
 * @ref _CMPIBroker "CMPIBroker object".
 *
 * This function table provides
 * @link broker-thread-reg MB thread registration services @endlink,
 * @link broker-indications MB indications services @endlink, and
 * @link broker-client MB client services ("up-calls") @endlink.
 */
struct _CMPIBrokerFT {

    /**
     * MB capabilities.
     *
     * See the @link mb-capabilities definition of test masks for MB
     * capabilities @endlink.
     */
    unsigned int brokerCapabilities;

    /**
     * CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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
     *   @addtogroup broker-thread-reg
     *   @{
     */

    /** @brief Prepare the MB to accept a new thread that will use
           MB functions.

     `CMPIBrokerFT.prepareAttachThread()` prepares the CMPI run time
     system to accept a thread that will be using CMPI services. The
     returned CMPIContext object must be used by the subsequent
     attachThread() and detachThread() invocations.
     @param mb Pointer to the broker.
     @param ctx Pointer to the CMPIContext object that was used to invoke
         the MI function that calls this MB function (see Subclause 8.1).
     @return If successful, returns new Context object to be used by thread
         to be attached.

         If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc
    codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
           data type handle.

     */
    CMPIContext* (*prepareAttachThread) (const CMPIBroker* mb,
            const CMPIContext* ctx);

    /** @brief Inform the MB that the current thread will begin
           using MB functions.

     `CMPIBrokerFT.attachThread()` informs the CMPI run time
     system that the current thread with `ctx`, will
     begin using CMPI services.
     @param mb Pointer to the broker.
     @param ctx Pointer to the CMPIContext object returned by a
         prior call to `prepareAttachThread()`.
     @return CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following @ref CMPIrc
    codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb` handle
          or `ctx` handle is invalid.
     */
    CMPIStatus (*attachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /** @brief Inform the MB that the current thread will no longer
               use MB functions.

     `CMPIBrokerFT.detachThread()` informs the CMPI run time system that the
     current thread
     will not be using CMPI services anymore. The Context object will be
     freed during this operation.
     @param mb Pointer to the broker.
     @param ctx CMPIContext object returned by a prior call to
         `prepareAttachThread()`.
     @return CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb` handle or `ctx`    
        handle is invalid.
     */
    CMPIStatus (*detachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /**
     *   @}
     *   @addtogroup broker-indications
     *   @{
     */

    /** @brief Request delivery of an indication.

     `CMPIBrokerFT.deliverIndication()` requests delivery of an
     indication. The MB will locate pertinent subscribers and notify
     them about the event.

     This function may be called by an MI regardless of whether or not there
     are any active indication filters or indication filter collections
     that cover the indication to be delivered. If there are no such filters
     or filter collections, this will not cause the function to fail. For
     the concept of coverage of indications by an indication filter or
     indication filter collection, see @ref ref-dmtf-dsp1054 "DSP1054".

     This function may be called by an MI regardless of whether or not
     the MB is ready for processing the delivery of indications, as
     communicated to the MI via @ref _CMPIIndicationMIFT::enableIndications
     "CMPIIndicationMIFT.enableIndications()" and
     @ref _CMPIIndicationMIFT::disableIndications
     "CMPIIndicationMIFT.disableIndications()".
     If the MB is not
     ready for processing the delivery of indications, this will not
     cause the function to fail. The MB implementation may choose to
     drop the indication in this case, or to queue the indication
     for later delivery.

     This function may be called by any MI function, and by any threads
     created by MIs that are registered with the MB (see Subclause 9.13).

     This function shall be suppored by the MB if the Indications
     capability is available otherwise it shall not be supported.

     @param mb Pointer to the broker.
     @param ctx Pointer to the CMPIContext object that was used to
         invoke the MI function that calls this MB function (see
         Subclause 8.1), or that was used to register the thread
         that calls this MB function.
     @param ns Pointer to a string specifying the name of the origin
         namespace of the indication.
     @param ind Pointer to a CMPIInstance containing the indication
         instance. Any instance path in the instance will be ignored
         by the MB ignored.
     @return A CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following @ref CMPIrc
    codes:
        @li `CMPI_RC_OK` - Function successful. Note: If the MB is
            not ready for processing the delivery of indications, it
            may drop the indication and still return success.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The handle specified by
            the ind argument is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The namespace
            specified by the `ns` argument is invalid, or the
            indication instancespecified by the `ind` argument is
            invalid.
     */
    CMPIStatus (*deliverIndication) (const CMPIBroker* mb,
            const CMPIContext* ctx, const char* ns, const CMPIInstance* ind);

    /**
     *   @}
     *   @addtogroup broker-client
     *   @{
     */

    /** @brief Enumerate instance paths of instances of a given
            class (and its subclasses).

     `CMPIBrokerFT.enumerateInstanceNames()` enumerates instance
         names of the class (and subclasses) defined by the `classPath`
         argument.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function
         that calls this MB function (see Subclause 8.1). Any
         invocation flags in the `ctx` argument will be ignored
         by this function.
     @param classPath Pointer to a CMPIObjectPath object that references
         the given class and that shall contain the namespace and
         class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful returns pointer to a new CIMEnumeration
         object containing CMPIObjectPaths objects that represent the
         enumerated instance paths. The new object will be released
         automatically by the MB.

    The function return status indicates one of the following @ref CMPIrc
    codes:
        @li `CMPI_RC_OK`- Function successful.
        @li `CMPI_RC_ERR_FAILED`- Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by
             this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
        specified in the `classPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
            `classPath` argument does not exist.
        @li `CMPI_RC_ERR_NOT_FOUND`- Instance not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE`- Invalid encapsulated data
            type handle.

    Extended error handling is not supported by this MB function;
    thus, any CMPIError objects returned by the targeted MI cannot
    be made available to the calling MI
     */
    CMPIEnumeration* (*enumerateInstanceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            CMPIStatus* rc);

    /** @brief Get a given instance.

     `CMPIBrokerFT.getInstance()` gets a CMPIInstance using
     `instPath` argument as reference. Instance structure can be controled
     using the CMPIInvocationFlags in `ctx` argument.

     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the
         same principal, role, accept language, and content language as
         the CMPIContext object that was used to invoke the MI function
         that calls this MB function (see Subclause 8.1). The MI may
         specify invocation flags as needed.
     @param instPath Pointer to a CMPIObjectPath object that
         references the given instance and that shall contain the
         namespace, class name, and key components. The hostname
         component, if present, will be ignored by the MB.
     @param properties If not NULL, the members of the array define
     one or more Property names. Each returned Object MUST NOT
     include elements for any Properties missing from this list
     @param rc Output:  if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful, returns a pointer to a new CMPIInstance object
        containing the retrieved instance.

    The new object will be released automatically by the MB.
    There is no function to explicitly  release the new object. Specifically,
    the MI shall not use @ref _CMPIBrokerMemFT::freeInstance
    "CMPIBrokerMemFT.freeInstance()" on the new object.

    If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by
        this MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified
        in the `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
        `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property list specified
        in the `properties` argument is invalid.
    @li `CMPI_RC_ERR_NOT_FOUND`	- Instance not found.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data type
        handle.

    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI.
     */

    CMPIInstance* (*getInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char** properties,
            CMPIStatus* rc);

    /** @brief Create an instance of a given class.

     `CMPIBrokerFT.createInstance()` creates an instance
     of a given class. The target MI is identified by the MB based
     on the `classPath` argument function creates an instance of a
     given class in the namespace of that class, by creating the
     underlying managed elements.

     @param mb Pointer to the broker.
     @param ctx CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the `ctx` argument will be ignored by this function.
     @param classPath points to a CMPIObjectPath object that references
     the class of the instance to be created and that shall contain
     the namespace and class name components. The hostname and key
     components, if present, will be ignored by the MBs.
     @param newInstnst  points to a CMPIInstance object specifying property
         values for the new instance. The object path component within
         this CMPIInstance object has no meaning; it should not be provided
         by the calling MIs. The MB will pass the definition of the new
         instance on to the target MI, unchanged.
     @param rc Output: if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful, returns a pointer to a new
        CMPIObjectPath object containing the assigned instance path.

         The new object will be released automatically by the MB, as
         described in Subclause 4.1.7. There is no function to
         explicitly release the new object. Specifically, the MI
         shall not use @ref _CMPIBrokerMemFT::freeObjectPath
         "CMPIBrokerMemFT.freeObjectPath()" on the new object.

        If not successful, returns NULL.

        The function return status indicates one of the following
            @ref CMPIrc codes:
        @li `CMPI_RC_OK`	- Function successful.
        @li `CMPI_RC_ERR_FAILED`	- Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED`	- Function is not supported
        by this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED`	- Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE`	- The namespace specified
        in the `classPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS`	- The class specified in the
        `classPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER`	- The instance specified
        in the `inst` argument is invalid.
        @li `CMPI_RC_ERR_ALREADY_EXISTS`	- Instance already exists.
        @li `CMPI_RC_ERR_INVALID_HANDLE`	- Invalid encapsulated data
        type handle.

        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     */
    CMPIObjectPath* (*createInstance) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const CMPIInstance* newInst, CMPIStatus* rc);

    /** @brief Modify property values of a given instance.

     `CMPIBrokerFT.modifyInstance()` modifies property values
     of a given instance. The target MI is identified by the MB based on
     the `instPath` argument.

     @param mb Pointer to the CMPIBroker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the `ctx` argument will be ignored by this function.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB.
     @param modInst Pointer to a CMPIInstance object specifying new
         values for the properties to be modified. The object path
         component within this CMPIInstance object has no meaning; it
         should not be provided by the calling MIs and should not
         be used by the MB.
     @param properties  if not NULL, defines the list of property names to
         be modified. If NULL, all properties will be modified. The end of
         the list is signalled by a NULL character pointer.
     @return CMPIStatus structure indicating the function return status.

        The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
            specified in the `instPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS`	- The class
            specified in the `instPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The instance specified
            in the `modInst` argument, or the properties specified
            in `property` are invalid.
        @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data
            type handle.

        Extended error handling is not supported by this MB function; thus,
            any CMPIError objects returned by the targeted MI cannot be made
            available to the calling MI
     @todo Review this description.
     */

    CMPIStatus (*modifyInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const CMPIInstance* modInst,
            const char** properties);

    /** @brief Delete a given instance.

     `CMPIBrokerFT.deleteInstance()` deletes a given instance.
     The target MI is identified by the MB based on the `instPath`
     argument.

     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the `ctx` argument will be ignored by this function.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB.
     @return CMPIStatus structure indicating the function return status.

        The function return status indicates one of the following @ref CMPIrc
        codes:
        @li  `CMPI_RC_OK` - Function successful.
        @li  `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li  `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
        @li  `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        @li  `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespacespecified in the 
            `instPath` argument does not exist.
        @li  `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
             `instPath` argument does not exist.
        @li  `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
        @li  `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data type 
            handle.

        Extended error handling is not supported by this MB function; thus,
            any CMPIError objects returned by the targeted MI cannot be made
            available to the calling MI
    */
    CMPIStatus (*deleteInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath);

    /** @brief Execute a query on a given class and return the query
               result.

     `CMPIBrokerFT.execQuery()` executes a query on a given
     class and returns the query result. The target MI is identified by
     the MB based on the classPath argument.
     by `op` using `query` expression.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the ctx argument will be ignored by this function.
     @param classPath Pointer to to a CMPIObjectPath object that references
         the given class to be queried and that shall contain the namespace
         and class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @param query Pointer to to a string containing the select expression
     @param lang Pointer to to a string containing the query language
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, returns a pointer to a new
             CMPIEnumeration object, containing CMPIInstance objects that
             represent the query result. 

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release
     the new object.

     If not successful, NULL will be returned.

     The function return status indicates one of the following:

    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_FAILED` -  Unspecified error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` -  Function is not supported by this
        MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` -  Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` -  The namespace specified in
        the `classPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_CLASS` -  The class specified in the
        `classPath` argument does not exist.
    @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` Query language not
        supported.
    @li `CMPI_RC_ERR_INVALID_QUERY` -  Invalid query.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data type
        handle.

    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI.
     */
    CMPIEnumeration* (*execQuery) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const char* query, const char* lang, CMPIStatus* rc);

    /** @brief Enumerate the instances of a given class (and its
               subclasses).

     `CMPIBrokerFT.enumerateInstances()` enumerates the
     instances of a given class (and its subclasses). The set of properties
     in the result instances can be controlled using the
     LocalOnly and DeepInheritance flags in the CMPIInvocationFlags
     entry in `ctx` and the properties argument. The target MIs
     are identified by the MB based on the `classPath` argument.

     @param mb Pointer to the broker.
     @param ctx Pointer to to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). The MI may specify
         invocation flags as needed.
     @param classPath Pointer to to a CMPIObjectPath object that references
         the given class and that shall contain the namespace and class
         name components. The hostname and key components, if present,
         will be ignored by the MB.
     @param properties If not NULL, the members of the array define one or more
     property names. Each returned Object MUST NOT include elements
     for any Properties missing from this list.  The end of the
     array is identified by a NULL pointer. If NULL all properties
     will be returned.
     @param[out] rc If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful returns a pointer to a new CMPIEnumerationObject
          containing CMPIInstance objects that represent the enumerated
          instances. The new object will be released automatically by the MB.

          If not successful returns NULL.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` -  Function successful.
        @li `CMPI_RC_ERR_FAILED` -  Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` -  Function is not supported
            by this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` -  Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` -  The namespace specified
            in the `classPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS` -  The class specified in the
            `classPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` -  The property list
            specified in the `properties` argument is invalid.
        @li `CMPI_RC_ERR_NOT_FOUND` -  Instance not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
            data type handle.
    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI
     */
    CMPIEnumeration* (*enumerateInstances) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const char** properties, CMPIStatus* rc);

    /** @brief Enumerate the instances associated with a given
               source instance.

     `CMPIBrokerFT.associators()` enumerates the instances
     associated with a given source instance. The target MIs are identified
     by the MB based on the `instPath` argument.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
     principal, role, accept language, and content language as the
     CMPIContext object that was used to invoke the MI function that
     calls this MB function (see Subclause 8.1). Any invocation flags
     in the `ctx` argument will be ignored by this function.
     @param instPath Pointer to a CMPIObjectPath object that references
     the given source instance that shall contain the namespace,
     class name, and key components. The hostname component, if present,
     will be ignored by the MB.

     If the source instance does not exist, this function shall either
     return success with an empty result set or CMPI_RC_ERR_NOT_FOUND.
     <b>(Deprecated)</b>

     @param assocClass If not NULL, MUST be a valid association class name.
     It acts as a filter on the returned set of objects by mandating that
     each returned Object MUST be associated to the source Object via an
     Instance of this Class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid class name.
     It acts as a filter on the returned set of Objects by mandating that
     each returned Object MUST be either an instance of this class (or one
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
     @param rc Output: if not NULL, points to a CMPIStatus structure that
     upon return will have been updated with the function return status.
     @return If successful, returns a pointer to a new CMPIEnumeration
         object, containing CMPIInstance objects that represent the
         enumerated instances.

    The new object will be released automatically by the MB,
    as described in Subclause 4.1.7. There is no function to explicitly
    release the new object.

    If not successful, returns NULL.

    The function return status indicates one of the following
    @ref CMPIrc codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_FAILED` -  Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` -  Function is not supported by this
        MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` -  Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` -  The namespace specified in the
    `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_CLASS` -  The class specified in the
        `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` -  The `assocClass`,
        `resultClass`, `role`, `resultRole`, or
        `properties` arguments are invalid.
    @li `CMPI_RC_ERR_NOT_FOUND` -  Instance not found. Instead of using
        this return code if the source instance does not exist, the MB should
        return success with an empty result set. The MI shall treat this
        return code as a successful return of an empty result set.
        <b>(Deprecated)</b>
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data type
        handle.
     
    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI.
     */
    CMPIEnumeration* (*associators) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* instPath,
            const char* assocClass, const char* resultClass, const char* role,
            const char* resultRole, const char** properties, CMPIStatus* rc);

    /** @brief Enumerate the instance paths of the instances
           associated with a given source instance.

     `CMPIBrokerFT.associatorNames()` enumerates the instance
        paths of the instances associated with a given source instance.
        The target MIs are identified by the MB based on the
        `instPath` argument.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the
     same principal, role, accept language, and content language as
     the CMPIContext object that was used to invoke the MI function
     that* calls this MB function (see Subclause 8.1). Any
     invocation flags in this argument will be ignored by this
     function.
     @param instPath Pointer to to a CMPIObjectPath object that references
         the given source instance and that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.

         If the source instance does not exist, this function shall either
         return success with an empty result set or
         CMPI_RC_ERR_NOT_FOUND.<b>(Deprecated)</b>.
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
     @param[out] rc  If not NULL, points to a CMPIStatus structure that
        upon return has been updated with the function return status.
     @return  if not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.

     The function return status indicates one of the following @ref CMPIrc
     codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_FAILED` -  Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` -  Function is not supported
        by this MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` -  Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` -  The namespace specified
        in the `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_CLASS` -  The class specified in the
        `instPath` argument does not exist.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` -  The `assocClass`,
        `resultClass`, `role`, or `resultRole` arguments
        are invalid.
    @li `CMPI_RC_ERR_NOT_FOUND` -  Instance not found.
    Instead of using this return code if the source instance does not exist,
    the MB should return success with an empty result set. The MI shall
    treat this return code as a successful return of an empty result set.
        <b>(Deprecated)</b>
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data
        type handle.
        
    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.
    */

    CMPIEnumeration* (*associatorNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* instPath,
            const char* assocClass, const char* resultClass, const char* role,
            const char* resultRole, CMPIStatus* rc);

    /** @brief Enumerate the association instances referencing a
       given source instance.

     `CMPIBrokerFT.references()` enumerates the
     association instances that refer to the instance defined
     by `op`. The target MIs are identified by the MB based on the
     instPath argument.

     @param mb Pointer to a CMPIBroker structure.
     @param ctx Pointer  to a CMPIContext object that specifies the same
        principal, role, accept language, and content language as the
        CMPIContext object that was used to invoke the MI function that
        calls this MB function (see Subclause 8.1). Any invocation flags
        in the ctx argument will be ignored by this function.
     @param op Source Pointer to a CMPIObjectPath object that references the
         given source instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB. If the source instance does not exist, this
         function shall either return success with an empty result set or
         CMPI_RC_ERR_NOT_FOUND. <b>(Deprecated)</b>
     @param resultClass If not NULL, MUST be a valid Class name.
         It acts as a filter on the returned set of   by mandating that
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
         Properties missing from this list.
     @param[out] rc  If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the
         function return status.
     @return If successful, returns a pointer to a new CMPIEnumeration,
     containing CMPIInstance objects that represent the enumerated instances.

     The new object will be released automatically by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release the
     new object.

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by
            this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified
            in the `instPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
            `instPath` argument does not exist.
            @li `CMPI_RC_ERR_INVALID_PARAMETER` - The
            `resultClass`, or `role`  arguments are invalid.
        @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found. Instead of
            using this return code if the source instance does not exist, the
            MB should return success with an empty result set. The MI shall
            treat this return code as a successful return of an empty
            result set. <b>(Deprecated)</b>.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data type
            handle.
        
        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     @todo does not create link to  CMPIEnumeration automatically above (ks)
     */
    CMPIEnumeration* (*references) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, const char** properties,
            CMPIStatus* rc);

    /** @brief Enumerate the instance paths of the association
       instances referencing a given source instance.

     `CMPIBrokerFT.referenceNames()` enumerates the instance
     paths of the association instances referencing a given source
     instance. The target MIs are identified by the MB based on
     the `instPath` argument.
     @param mb Pointer to a CMPIBroker structure.
     @param ctx Pointer to a CMPIBroker structure
     @param op Source Pointer to a CMPIObjectPath object that references the
         given source instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB. If the source instance does not exist, this
         function shall either return success with an empty result set or
         CMPI_RC_ERR_NOT_FOUND. <b>(Deprecated)</b>
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
     @param[out] rc  If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the
         function return status.
     @return If successful, returns a pointer to a new CMPIEnumeration object,
     containing CMPIObjectPath objects that represent the enumerated
     instance paths.

    The new object will be released automatically by the MB, as described
    in Subclause 4.1.7. There is no function to explicitly release the
    new object.

    If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by
            this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
            specified
            in the `instPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
            `instPath` argument does not exist.
            @li `CMPI_RC_ERR_INVALID_PARAMETER` - The
            `resultClass`, or `role` arguments are invalid.
        @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found. Instead of
            using this return code if the source instance does not exist, the
            MB should return success with an empty result set. The MI shall
            treat this return code as a successful return of an empty
            result set. <b>(Deprecated)</b>.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data
            type handle.
        
        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     */
    CMPIEnumeration* (*referenceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, CMPIStatus* rc);

    /** @brief  Invoke a method on a target object.

     `CMPIBrokerFT.invokeMethod()` invokes a named, extrinsic
         method on a target object. Instance methods (i.e., non-static methods)
         can be invoked only on instances. Class methods (i.e., static methods)
         can be invoked on instances and classes. The target MI is
         identified by the MB based on the `objPath` argument.

     @param mb Pointer to the broker.
     @param ctx Context object
     @param objPath CMPIObjectPath containing namespace, classname  
     and key components.   
     @param Pointer to to a string containing the method name.
     @param Pointer to a CMPIArgs object containing the method input
         parameters.
     @param out Pointer to to an empty CMPIArgs object that, upon successful
         return of the method, will have been updated to contain the
         method output parameters. The returned CMPIArgs object shall
         not be explicitly released by the MI, because it will be
         released automatically by the MB (see Subclause 4.1.7).
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful, a CMPIData structure containing the method
     return value will be returned.

     If not successful, CMPIData.state will have the CMPI_badValue flag
     set to true.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK`	- Function successful.
        @li `CMPI_RC_ERR_FAILED`	- Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED`	- Invocation of extrinsic
            methods is not supported by the MB (that is, the Instance
            Manipulation capability is not available; see Subclause 7.1).
        @li `CMPI_RC_ERR_ACCESS_DENIED`	- Not authorized.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE`	The namespace specified
            in the `objPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_CLASS`	- The class specified in the
            `objPath` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER`	- The method parameters
            specified in the in or out arguments are invalid.
        @li `CMPI_RC_ERR_NOT_FOUND`	- Instance not found.
        @li `CMPI_RC_ERR_METHOD_NOT_AVAILABLE` - The extrinsic method is
            not supported by the targeted MI.
        @li `CMPI_RC_ERR_METHOD_NOT_FOUND` - Method not defined
            in the class.
        @li `CMPI_RC_ERR_INVALID_HANDLE`	- Invalid encapsulated
            data type handle.

    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.
     */
    CMPIData (*invokeMethod) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* objPath, const char* method,
            const CMPIArgs* in, CMPIArgs* out, CMPIStatus* rc);

    /** @brief Set a property of a given instance <b>(Deprecated)</b>.

     `CMPIBrokerFT.setProperty()` sets the named property value of an instance
     defined by the `instPath` parameter.

     @param mb Pointer to the CMPIBroker.
     @param ctx CMPIContext object
     @param instPath CMPIObjectPath containing namespace, classname
         and key components.
     @param name Property name
     @param value Value.
     @param type Value type.
     @return CMPIStatus structure indicating the function return status .

    The function return status indicates one of the following:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not
        supported by this MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
        specified in `instPath` is invalid.
    @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
    the  `instPath` argument does not exist.
    @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in
        `instPath` is not found.
    @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
    @li `CMPI_RC_ERR_TYPE_MISMATCH` - Value types
    incompatible.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
        data type handle.
        
    Extended error handling is not supported by this MB function;  
    thus, any CMPIError objects returned by the targeted MI cannot    
    be made available to the calling MI.    

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property
     client operations in DMTF specifications. MBs shall implement
     the @ref _CMPIBrokerFT::setProperty "CMPIBrokerFT.setProperty()"
     function by invoking the
     modifyInstance() MI function if the setProperty() MI function
     is not implemented by the target MI. New MIs should
     replace the use of CMPIBrokerFT.setProperty() with the use of
     @ref _CMPIBrokerFT::modifyInstance "CMPIBrokerFT.modifyInstance()".

     @todo TBD: Review and agree on the way this function is documented to be
           deprecated since CMPI 2.1 (using the `deprecated` statement with
           descriptive text). OK (ks)
     */
    CMPIStatus (*setProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief Get the named property of a given instance
               <b>(Deprecated)</b>.

     `CMPIBrokerFT.getProperty()` gets the named property value of an
     Instance defined by the `instPath` parameter.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname
      and key components.
     @param name Property name
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, Property value. If not successful
         CMPIData.state will have CMPI_BadValue flag set to true

    The function return status indicates one of the following:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not
        supported by this MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
    specified in `instPath` is invalid.
    @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
    the `instPath` argument does not exist.
    @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in
        `instPath` is not found.
    @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
        data type handle.

    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property
     client operations in DMTF specifications. MBs shall implement
     the @ref _CMPIBrokerFT::getProperty "CMPIBrokerFT.getProperty()"
     function by invoking the
     getInstance() MI function if the getProperty() MI function
     is not implemented by the target MI. New MIs should replace
     the use of @ref _CMPIBrokerFT::getProperty "CMPIBrokerFT.getProperty()"
     with the use of
     @ref _CMPIBrokerFT::getInstance "CMPIBrokerFT.getInstance()".
     */
    CMPIData (*getProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name, CMPIStatus* rc);

    /**
     *   @}
     */

};

/**
   @brief Function table for MB factory and miscellaneous services of
    @ref _CMPIBroker "CMPIBroker object".

   The CMPIBrokerEncFT function table provides factory services
   for the CMPI data types, and functions for test, conversion,
   tracing and logging.

   The CMPIBrokerEncFT is the function table used as an anchor for these
   services. It is made available to MI via the
   `<mi name>_Create_<mi type>MI()` functions.

   For functions that are not supported, their function pointers in the
   CMPIBrokerEncFT function table shall not be NULL, but shall point to
   a function that can be called and then indicate back to the caller that
   it is not supported, as specified in the description of the function.
 */
struct _CMPIBrokerEncFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokerenc-factory
     *   @{
     */

    /** @brief Create a new CMPIInstance object initialized to a
           given instance path.

     `CMPIBrokerEncFT.newInstance()` creates a new
     CMPIInstance object. The new object should have no properties.
     The purpose of class-defined derault values for properties is
     to act as defaults for unspecified input properties when a
     client creates an instance, not to act as defualts for not
     explicity set properties when a client retrieves an instance.

     @param mb Pointer to the broker.
     @param instPath ObjectPath containing namespace and classname.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created instance. if
         not successful returns NULL.

     The new object will be automatically released by the MB.
     If the new object is no longer used by the MI, it
     may be explicitly released by the MI using
     @ref _CMPIBrokerMemFT::freeInstance "CMPIBrokerMemFT.freeInstance()".

     The function return status indicates one of the following:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
        specified in `instPath` is invalid.
    @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in
        `instPath` is not found.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
        data type handle.

     */
    CMPIInstance* (*newInstance) (const CMPIBroker* mb,
            const CMPIObjectPath* instPath, CMPIStatus* rc);

    /** @brief Create a new CMPIObjectPath initialized to a given
           namespace and class name

     `CMPIBrokerEncFT.newObjectPath()` creates a new
         CMPIObjectPath object that is initialized to a given namespace
         and class name.
     @param mb Pointer to a CMPIBroker object.
     @param ns Pointer to a string specifying the namespace name.
     @param cn Pointer to a string specifying the class name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created
         CMPIObjectPath. If not successful returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace
    specified in the `ns` argument does not exist.
    @li `CMPI_RC_ERR_NOT_FOUND` -  Class in `cn` not found.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
        data type handle.

     */
    CMPIObjectPath* (*newObjectPath) (const CMPIBroker* mb, const char* ns,
            const char* cn, CMPIStatus* rc);

    /** @brief Create a new CMPIArgs object initialized to have no
           method parameters.

     `CMPIBrokerEncFT.newArgs()` creates a new CMPIArgs
     object with no method parameters
     @param mb Pointer to the broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns the newly created CMPIArgs
             object. If not successful returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
        data type handle.
     */
    CMPIArgs* (*newArgs) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Create a new CMPIString object initialized from a
           C-language string.

     `CMPIBrokerEncFT.newString()` creates a new
         CMPIString object that is initialized from a C-language
         string.
     @param mb Pointer to the broker.
     @param data String data
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created CMPIString. If
         not successful returns NULL.

     The new object will be automatically released by the MB. If the new
     object is no longer used by the MI, it may be explicitly released
     by the MI using @ref _CMPIBrokerMemFT::freeString
     "CMPIBrokerMemFT.freeString()".

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` -  Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
            data type handle.
     */
    CMPIString* (*newString) (const CMPIBroker* mb, const char* data,
            CMPIStatus* rc);

    /** @brief Create a new CMPIArray object of a given fixed array
          size for a given type of elements.

     `CMPIBrokerEncFT.newArray()` returns a new CMPIArray
     object. Once created, the size of the array is fixed and all
     elements are of the same time. The array in initialized to
     have no array elements.

     @param mb Pointer to the broker.
     @param size Number of elements
     @param type specifies the type of each element. The type argument
         specifies the type of single array elements; for example, the value
         for an array that contains CMPIString objects will be CMPI_string,
         and not CMPI_stringA.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a pointer to the new CMPIArray object.

     The new object will be automatically released by the MB, as described in
     Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using @ref _CMPIBrokerMemFT::freeArray
     "CMPIBrokerMemFT.freeArray()".

    If not successful, NULL will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` -  Function successful.
        @li `CMPI_RC_DATA_TYPE` -  Data type not valid.
        @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
            data type handle.
     */
    CMPIArray* (*newArray) (const CMPIBroker* mb, CMPICount size,
            CMPIType type, CMPIStatus* rc);

    /** @brief Create a new CMPIDataTime object with current date
       and time.

     `CMPIBrokerEncFT.newDateTime()` creates a new
         CMPIDateTime object that is initialized with the current
         date and time.

     @param mb Pointer to the broker.
     @param rc Output: if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful, returns a pointer to the new CMPIDateTime object.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. If the new object is no longer used by the MI,
     it may be explicitly released by the MI
     using @ref _CMPIBrokerMemFT::freeDateTime "CMPIBrokerMemFT.freeDateTime()".

     If not successful, NULL will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` -  Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
            data type handle.
     */
    CMPIDateTime* (*newDateTime) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Create a new CMPIDateTime object initialized to a
         specific value.

     `CMPIBrokerEncFT.newDateTimeFromBinary()` creates
         a new CMPIDateTime object that is initialized with the
         specified date and time from argument `binTime`.

     @param mb Pointer to the broker.
     @param binTime When interval is false, the `binTime` argument
         contains a point in time value expressed as a 64-bit unsigned integer
         in microseconds since 00:00:00 GMT, January 1, 1970. Otherwise,
         the `binTime` argument contains a time interval expressed as
         a 64-bit unsigned integer in microseconds
     @param interval When true, defines `binTime` definition to be
     an interval value.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to the new CMPIDateTime object.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. If the new object is no longer used by the MI,
     it may be explicitly released by the MI
     using @ref _CMPIBrokerMemFT::freeDateTime "CMPIBrokerMemFT.freeDateTime()".

     If not successful, returns NULL.

     The function return status indicates one of the following
     @ref CMPIrc codes:

     @li `CMPI_RC_OK` -  Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated
          data type handle.
     */
    CMPIDateTime* (*newDateTimeFromBinary) (const CMPIBroker* mb,
            CMPIUint64 binTime, CMPIBoolean interval, CMPIStatus* rc);

    /** @brief Create a new CMPIDateTime object initialized from input.

     `CMPIBrokerEncFT.newDateTimeFromChars()` creates a new
     CMPIDateTime object that is initialized with the the argument
     `utcTime`, the specified date and time.

     @param mb Pointer to the broker.
     @param datetime Date/Time definition in CIM datetime string format.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a pointer to the new CMPIArray object.

     The new object will be automatically released by the MB,
     as described in Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using
     @ref _CMPIBrokerMemFT::freeDateTime "CMPIBrokerMemFT.freeDateTime()".

     If not successful, NULL will be returned.

     The function return status indicates one of the following
     @ref CMPIrc codes:

     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_INVALID_PARAMETER` - The utcTime format is invalid.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
         data type handle.
     */
    CMPIDateTime* (*newDateTimeFromChars) (const CMPIBroker* mb,
            const char* datetime, CMPIStatus* rc);

    /** @brief Create a new CMPISelectExp object initialized from a
       select expression.

     `CMPIBrokerEncFT.newSelectExp()` creates a new CMPISelectExp
         object that is initialized from a select expression specified
         in a query language.

     This function and the CMPISelectExp encapsulated data type shall be
     supported by the MB if the Query Normalization capability is available
     (see Subclause 7.1); otherwise, they shall not be supported. Availability
     of the Query Normalization capability can be queried by an MI using
     the CMPI_MB_QueryNormalization test mask on the brokerCapabilities
     member of the CMPIBrokerFT structure.

     @param mb Pointer to the CMPIBroker .
     @param query Pointer to a string containing the select expression.
     @param lang Pointer to a string containing the query language.
     @param projection Output: Pointer to to a CMPIArray pointer that upon
         success will have been updated to point to a new CMPIArray
         object of @ref _CMPIString "CMPIString" entries containing
         the projection
         specification. The pointer will be set to NULL if no
         projection was specified in the select expression. The
         projection specification is query language-specific. Hence
         the entries format of the projection output array
         @ref _CMPIString "CMPIString" might be different depending on the query
         language. Be sure to check the lang argument for the query
         language your MI will support.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @retval Successful Returns a pointer to the new
     CMPIArray object. The new object will be automatically released
     by the MB, as described in Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using
     @ref _CMPIBrokerMemFT::freeDateTime "CMPIBrokerMemFT.freeDateTime()".

    @retval UnSuccessful  NULL will be returned.

    The function return status indicates one of the following @ref
     CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by
            the MB.
        @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The query
             language is not supported.
        @li `CMPI_RC_ERR_INVALID_QUERY` - The query expression is not
            valid.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb` handle is invalid.
    @todo test of use of retval again. Does this make sense.
     */

    CMPISelectExp* (*newSelectExp) (const CMPIBroker* mb, const char* query,
            const char* lang, CMPIArray** projection, CMPIStatus* st);

    /**
     *   @}
     *   @addtogroup brokerenc-misc
     *   @{
     */

    /** @brief Determine if a class path is of a specific class or
         its subclasses.

     `CMPIBrokerEncFT.classPathIsA()` tests whether a the
         argument `className` is of argument `classPath` or any of `classPath`
      subclasses.
     @param mb Pointer to a CMPIBroker structure.
     @param classPath Pointer to the CMPIObjectPath object representing
         the class path that is being tested. It shall contain the namespace
         and class name components. Any key components in that CMPIObjectPath
         object will be ignored.
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, a CMPIBoolean value indicating the test result will
         be returned, as follows: True indicates that the class path is of the
         specified class or any of that class,s subclasses; False indicates
         that this is not the case.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace implied by
         `classPath` is invalid.
    @li `CMPI_RC_ERR_NOT_FOUND` - The class implied by `classPath` is
         not found.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` - The type format is invalid.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
         `classPath` handle is invalid.

     @todo KS Spec includes CMPI_RC_INVALID_PARAMETER (type format
           is invalid. Does that Error make sense? There is no type
           arg
     */
    CMPIBoolean (*classPathIsA) (const CMPIBroker* mb,
        const CMPIObjectPath* classPath, const char* className,
        CMPIStatus* rc);

    /** @brief Convert CMPIEncapsulated data type object into a
           string representation.

     `CMPIBrokerEncFT.toString()` converts any CMPI encapsulated
         data type object into an MB implementation-specific string
         representation. Intended for debugging purposes only.
     @param mb Pointer to a CMPIBroker structure.
     @param object Pointer to a CMPI encapsulated data type object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns CMPIString from representation
         of `object`. If not successful returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
         `object` handle is invalid.
     */
    CMPIString* (*toString) (const CMPIBroker* mb,
        const void* object, CMPIStatus* rc);

    /** @brief Tests whether a CMPI encapsulated data type object is
           of a specified CMPI type.

     `CMPIBrokerEncFT.isOfType()` verifies whether `object` is of
     CMPI type `type`. Intended for debugging purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param type A string specifying a valid CMPI Object type
     ("CMPIInstance", "CMPIObjectPath", etc).
     @param rc Output: Service return status (suppressed when NULL).
     @retval True: test successful
     @retval False; test unsuccesful.

    The function return status indicates one of the following @ref CMPIrc codes:

    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `type` format is invalid.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
         `object` handle is invalid.
    @todo test of using retval for return. Does this make sense as
          an alternative.
     */
    CMPIBoolean (*isOfType) (const CMPIBroker* mb,
        const void* object, const char* type, CMPIStatus* rc);

    /** @brief Get the type name of a CMPI ensapsulated data type
           object.

    `CMPIBrokerEncFT.getType()` retrieves the CMPI type of `object`.
        The returned
        CMPIString object shall not be explicitly released by the MI,
        because it may be an internal object of the CMPI encapsulated
        data type object which will be released along with that
        object, or a new object created by the MB which will be
        released automatically by the MB. Intended for debugging
        purposes only.
    @param mb Pointer to the broker.
    @param[out] object If not NULL, points to a CMPIStatus structure that upon
       return will have been updated with the function return status
    @param[out] rc Service return status (suppressed when NULL).
    @return If successful, a pointer to a CMPIString object specifying the
    type name of the encapsulated data type (e.g., CMPIInstance) will be
    returned.

    The returned CMPIString object shall not be explicitly released by the MI,
    because it may be an internal object of the CMPI encapsulated data type
    object which will be released along with that object, or a new object
    created by the MB which will be automatically released by the MB
    (see Subclause 4.1.7).

    If not successful, NULL will be returned.

    The function return status indicates one of the following @ref CMPIrc codes: 
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
         `object` handle is invalid.
     */
    CMPIString* (*getType) (const CMPIBroker* mb,
        const void* object, CMPIStatus* rc);

    /** @brief Get translated MB implementation specific message
               text <b>(Deprecated)</b>.

     `CMPIBrokerEncFT.getMessage()` retrieves translated message defined by
         the `msgId` argument.

     Use @ref _CMPIBrokerEncFT::getMessage2 "CMPIBrokerEncFT.getMessage2()" in
     place of this function.
     @param mb Pointer to the broker.
     @param msgId The message identifier.
     @param defMsg The default message. Used when message translation is not
         supported
     @param rc Output: Service return status (suppressed when NULL).
     @param count The number of message substitution values.
     @return If successful returns the translated
         message.Otherwise returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_TYPE_MISMATCH` - Invalid insert pair.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - Count value range violation.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - `mb` handle is
            invalid.

     @deprecated This function was deprecated in CMPI 2.1 in favor of
     @ref _CMPIBrokerEncFT::getMessage2 "CMPIBrokerEncFT.getMessage2()".
     */
    CMPIString* (*getMessage) (const CMPIBroker* mb,
        const char* msgId, const char* defMsg, CMPIStatus* rc,
        CMPICount count, ...);

    /** @brief Log a diagnostic message.

     `CMPIBrokerEncFT.logMessage()` logs a diagnostic message defined by the
         input arguments. It exists to provide a mechanism to MIs to
     provider information about errors, status, etc.

     This function shall be supported by the MB if the Logging capability is
     available (see Subclause 7.1); otherwise, it shall not be supported.
     Availability of the Logging capability can be queried by an MI using the
     CMPI_MB_Logging test mask on the brokerCapabilities member of the
     CMPIBrokerFT structure (see Subclause 7.1).
     @param mb The mb argument points to a CMPIBroker structure.
     @param severity  The `level` argument describes the level of
         logmessage. Levels are defined in Subclause 4.9.
     @param id if not NULL, points to a string specifying a message ID or
         any other identifying string.
     @param text  If not NULL, points to a string specifying the
         message text to be logged.
     @param string If not NULL, points to a CMPIString object  specifying the
         message text to be logged. `string` will be ignored
         when text is not NULL.
     @return Service return status.

    The function return status indicates one of the following CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - `mb` or `string`
             handle is invalid.

     @todo ks The id argument talked about he component argument. Changed but
     check
     */
    CMPIStatus (*logMessage) (const CMPIBroker* mb,
        int severity, const char* id, const char* text,
        const CMPIString* string);

    /** @brief Trace a diagnostic message with a specific trace
           level and component definition.

     `CMPIBrokerEncFT.trace()` traces a diagnostic message with a
     specific trace level. This function exists to provide a mechanism to MIs
     by which debugging information may be generated.

     This function shall be supported by the MB if the Tracing capability
     is available (see Subclause 7.1); otherwise, it shall not be supported.
     Availability of the Tracing capability can be queried by an MI using the
     CMPI_MB_Tracing test mask on the brokerCapabilities member of the
     CMPIBrokerFT structure.

     MBs may support tracing in such a way that trace level and component
     ID can be used for deciding whether a diagnostic message is actually
     kept versus discarded.

     @param mb Pointer to to a CMPIBroker structure.

     @param level  Describes the level of log message. Levels are defined in
         Subclause 5.11.
     @param component If not NULL, is the implementation specific component ID.
     @param text  If not NULL, points to a string specifying the message text
         to be traced.
     @param string If not NULL, is the message text to
         be output. `string` will be ignored when text is not NULL.
     @return A CMPIStatus structure indicating the function return status
         will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - `mb` or `string`
             handle is invalid.
     */
    CMPIStatus (*trace) (const CMPIBroker* mb,
        CMPILevel level, const char* component, const char* text,
        const CMPIString* string);

#ifdef CMPI_VER_200

    /**
     *   @}
     *   @addtogroup brokerenc-factory
     *   @{
     */

    /** @brief Create a new CMPIError object initialized with
           attributes defined by the input parameters.

     `CMPIBrokerEncFT.newCMPIError()` creates a new CMPIError
     object that is initialized with certain core attributes.

     The input data may (or may not) be defined in a DMTF message
     registry (see @ref ref-dmtf-dsp0228 "DSP0228" for the format of message
     registries, and @ref ref-dmtf-dsp8016 "DSP8016" for the messages defined
     for the MI functions of CMPI).

     @param mb Pointer to the broker.
     @param owner A string specifying the value for the OwningEntity attribute
     @param msgID A string which uniquely identifies the
         MessageID attribute of the CMPIError object For a description of
         the MessageID attribute, see the description of the
         MessageID property in the CIM_Error class in the CIM
         Schema. If the error message is defined in a DMTF message
         registry, the string value of this argument shall be
         the message ID defined for the message in the registry
         (the concatenation of the values of the PREFIX and
         SEQUENCE_NUMBER attributes of the MESSAGE_ID element for
         the message).
     @param msg A string which represenst the formatted message.
     @param sev The percieved severity of the error.
     @param pc The probably cause of this error
     @param cimStatusCode CIM status code to be associated with this error.
     @param rc Output: Service return status.
     @return If successful, returns a pointer to the new CMPIError object.

     The new object will be released automatically by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release the
     new object.

     If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb` argument is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the parameters is
            invalid.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB. This return code is deprecated since CMPI 2.1;
            It will not be returned because the Extended Errors
            capability will be available. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     */
    CMPIError* (*newCMPIError) (const CMPIBroker* mb,
        const char* owner,
        const char* msgID,
        const char* msg,
        const CMPIErrorSeverity sev,
        const CMPIErrorProbableCause pc,
        const CMPIrc cimStatusCode,
        CMPIStatus* rc);

    /**
     *   @}
     *   @addtogroup brokerenc-misc
     *   @{
     */

    /** @brief Open a message file and return a handle to the file.

     If the MB supports message files, `CMPIBrokerEncFT.openMessageFile()`
     opens a message file and returns a message file handle to that
     file. This function will use the CMPIAcceptLanguage entry from the
     current context to determine the language for the messages, and will
     set the CMPIContentLanguage entry in the current context to the language
     that was used. All subsequent calls to
     @ref _CMPIBrokerEncFT::getMessage2 "CMPIBrokerEncFT.getMessage2()"
     using this message file handle will return messages based on
     that language.

     If the MB does not support message files, or if the function fails
     for other reasons, the function returns NULL as the message file handle.
     Subsequent calls to 
     @ref _CMPIBrokerEncFT::getMessage2 "CMPIBrokerEncFT.getMessage2()"
     using the
     NULL message file handle will cause the default message template to be
     used.

     @param mb Pointer to the broker
     @param msgFile Points to a string specifying the implementation-specific
     file path to the message file, or a part thereof. Examples for such
     implementation-specific file paths are:
     <ul>
        <li>Base name of the message file (does not include file extension and
        directory path). The message file contains all languages, and the
        language is used to locate the message in the correct language within
        the message file.
        <li>Base name of the message file (does not include file extension and
        directory path). The message file contains messages in only one
        language, and some identifier for that language is part of the base
        name.
        <li>Absolute path of the message file. The message file contains all
        languages, and the language is used to locate the message in the correct
        language within the message file.
        <li>Absolute path of the message file. The message file contains
        messages in only one language, and some identifier for that language
        is part of the file path.
     </ul>
     The format of the content of the message file is also
     implementation-specific.

     @param[out] msgFileHandle points to a CMPIMsgFileHandle structure that
     will have been updated with a handle that can be passed to the
     @ref _CMPIBrokerEncFT::getMessage2 "CMPIBrokerEncFT.getMessage2()" and
     @ref _CMPIBrokerEncFT::closeMessageFile
     "CMPIBrokerEncFT.closeMessageFile()"
     functions. If the MB supports message files and the function was
     successful, the CMPIMsgFileHandle structure will have been updated
     with a non-NULL handle to the open message file. If the MB does not
     support message files, or if the function failed for other reasons,
     the CMPIMsgFileHandle structure will have been updated with a NULL handle.
     @return A CMPIStatus structure indicating the function return status
     will be returned.

     The function return status indicates one of the following
        @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_FOUND` - The MB supports message files and the
             message file was not found, or the MB does not support message
             files.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb`  handle is invalid.
     */
    CMPIStatus (*openMessageFile) (const CMPIBroker* mb,
        const char* msgFile,
        CMPIMsgFileHandle* msgFileHandle);

    /** @brief Close a message file.

     `CMPIBrokerEncFT.closeMessageFile()` closes a message file
     previously opened by
     @ref _CMPIBrokerEncFT::openMessageFile "CMPIBrokerEncFT.openMessageFile()".
     If the message
     file handle is NULL, the message file is not closed, and this is not
     considered a failure.
     @param mb Pointer to a CMPIBroker structure
     @param msgFileHandle The msgFileHandle argument contains a message file
         handle (including NULL) that was returned by a previous call to
         @ref _CMPIBrokerEncFT::openMessageFile
         "CMPIBrokerEncFT.openMessageFile()".
     @return A CMPIStatus structure indicating the function return status
         will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
            `msgFileHandle` handle is invalid.
     */
    CMPIStatus (*closeMessageFile) (const CMPIBroker* mb,
        const CMPIMsgFileHandle msgFileHandle);

    /** @brief Get a translated message text from an open message
           file by message ID

     `CMPIBrokerEncFT.getMessage2()` gets a translated message text
     from an open message file, by `msgId`.

     The variable arguments of this function are count pairs of arguments
     representing the message insert pairs as follows:
     type, value
     whereby type is a CMPIType value and value is a value of that type.
     The following types are supported: CMPI_Sint32, CMPI_uint32, CMPI_sint64,
     CMPI_uint64, CMPI_real64, CMPI_Boolean, CMPI_chars, and CMPI_string.

     @param mb Broker this pointer
     @param msgId Pointer to a string specifying a message ID that is used to
         locate a message template in the open message file.
     @param msgFileHandle The handle representing the open message
        file that was returned by a call to openMessageFile(). If
        the MB does not support message files the handle is NULL.
     @param defMsg Pointer to a string specifying the default message template
        that will be used when the MB does not support message files or when
        the message ID cannot be located.
        The message template string specified in the defMsg argument
        may contain up to ten message insert triggers ($0 through
        $9). Each insert trigger will be expanded; that is, the
        insert trigger string will be replaced with a string
        representation of the value of the corresponding insert pair
        in the variable arguments of this function. The MI is not
        affected when the MB does not support message files or when
        the message ID cannot be located, because this function still
        succeeds and returns a message with expanded message insert
        triggers.
     @param[out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @param count The number of message substitution values.
     @return If successful returns the translated message; otherwise
         the default message template without any insert triggers
         expanded is returned.

         In both cases, the new object will be automatically released by the
         MB, as described in Subclause 4.1.7. There is no function to
         explicitly release the new object. Specifically, the MI shall
         not use @ref _CMPIBrokerMemFT::freeString
         "CMPIBrokerMemFT.freeString()" on the new object.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_TYPE_MISMATCH` - Invalid insert pair.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` - Count value range violation.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Either the `mb` or
             `msgFileHandle` handle is invalid. NULL is a valid value for
             the `msgFileHandle` handle.

     @todo ks confirm formatting
     */
    CMPIString* (*getMessage2) (
        const CMPIBroker* mb,
        const char* msgId,
        const CMPIMsgFileHandle msgFileHandle,
        const char* defMsg,
        CMPIStatus* rc,
        CMPICount count, ...);

#endif /*CMPI_VER_200*/

    /**
     *   @}
     *   @addtogroup brokerenc-factory
     *   @{
     */

#ifdef CMPI_VER_210

    /** @brief Create a new CIMPropertyList object initialized to a
           list of property names.

     `CMPIBrokerEncFT.newPropertyList()` creates a new
     CMPIPropertyList that is initialized to a list of property names
     specified by the `properties` argument.
     @param mb pointer to a CMPIBroker object.
     @param properties pointer to the first entry of a
         NULL-terminated array of pointers to C strings that specify the
         property names for the property list.
     @param[out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, returns a pointer to the new CMPIPropertyList
     object.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release the new
     object.

     If not successful, NULL will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `mb` handle.
     */
    CMPIPropertyList* (*newPropertyList) (const CMPIBroker* mb,
            const char** properties, CMPIStatus* rc);

    /** @brief Create a new CMPIString object from a C-language
              string in a specific codepage.

       `CMPIBrokerEncFT.newStringCP()` creates a new
       CMPIString object that is initialized from a C-language
       string in a specific codepage

       @param mb Pointer to to a CMPIBroker object.
       @param data Pointer to to a string that is represented in the
           codepage specified in the `cpid` argument. The `data`
           argument is used to initialize the new CMPIString object after
           converting it from its codepage to UTF-8.
       @param cpid specifies the CMPI-specific codepage ID for the
           codepage that is used to interpret the Bytes in the `data`
           argument. See Subclause 5.2.2 for a list of supported
           codepages and their codepage ID values.
       @param rc If not NULL, points to a CMPIStatus structure
           that upon return will have been updated with the
           function return status.
       @return If successful, a pointer to the new CMPIString object
           containing the UTF-8 represented string will be returned.

          The new object will be released automatically by the MB, as
          described in Subclause 4.1.7. If the new object is no longer
          used by the MI, it may be explicitly released by the MI using
          @ref _CMPIBrokerMemFT::freeString "CMPIBrokerMemFT.freeString()".

          If not successful, NULL will be returned.

         The function return status indicates one of the following
            @ref CMPIrc codes:
            @li `CMPI_RC_OK` - Function successful.
            @li `CMPI_RC_ERR_INVALID_HANDLE` - The `mb` handle is invalid.

       @version Added in CMPI 2.1.
       @todo TBD: Review and agree on the way this function is documented to be
           added in CMPI 2.1 (using the `version` statement with descriptive
           text). AGREED Karl
     */
    CMPIString* (*newStringCP) (const CMPIBroker* mb, const char* data,
            const CMPICodepageID cpid, CMPIStatus* rc);

    /** @brief Create a new CMPIEnumerationFilter object
           initialized with a filter query.

     `CMPIBrokerEncFT.newEnumerationFilter()` creates a new 
     CMPIEnumerationFilter object initialized with `filterquery` argument if
        the `filterQueryLanguage` argument is valid. If the `filterquery` is
        NULL the new object will be set to do no filtering.
     @param mb Pointer to a CMPIBroker object
     @param filterQueryLanguage Pointer to a string specifying the query
         language used for the `filterQuery` argument. If this argument
         is NULL, the new CMPIEnumerationFilter object will be set
         to define that no filtering is to be performed.
     @param filterQuery Pointer to a string specifying a valid query
         in the query language defined by the `filterQueryLanguage`
         argument.
         If this argument is NULL, the new CMPIEnumerationFilter object
         will be set to define that no filtering is to be performed.
     @param rc If not NULL, pointer to a CMPIStatus structure that upon
         return has been updated with the function return status.
     @return If successful, a pointer to a new CMPIEnumerationFilter
     object will be returned.

     The new object will be released automatically by the MB,
     as described in Subclause 4.1.7. There is no function to
     explicitly release the new object.

     If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Operation successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - The ` mb` handle
             is invalid.
    @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The
            `filterQueryLanguage` argument defines a query language
            that the MI does not recognize.
    @li `CMPI_RC_ERR_INVALID_QUERY` - The `filterQuery` is
             not a valid query in the specified filter query language.
    @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of the
            query language is not supported.

     @version This function added in CMPI 2.1
     @todo in description. What does set to do no filtering mean?
     */
    CMPIEnumerationFilter* (*newEnumerationFilter) (const CMPIBroker* mb,
            const char* filterQueryLanguage, const char* filterQuery,
            CMPIStatus* rc);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

};

struct timespec;

/**
 * @brief Function table for MB operating system encapsulation services of
 * @ref _CMPIBroker "CMPIBroker object".
 *
 * This function table provides operating system encapsulation services, such as
 * library name resolution services and services for POSIX-conformant threads,
 * mutexes, and conditions.
 */
struct _CMPIBrokerExtFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokerext-lib
     *   @{
     */

    /** @brief Resolve a generic load library name to its file name.

     `CMPIBrokerExtFT.resolveFileName()` complements a generic dynamic library
     name to its OS-dependent native format.
     @param filename Pointer to the generic library name,
     @return The returned char* pointer to the complemented library
         name in native OS format.
     Space for this string has been obtained using POSIX ``malloc()`` and must
         be released using POSIX ``free()`` by the caller.
     In case no storage could be obtained for the complemented library
         name, returns NULL.
     */
    char* (*resolveFileName) (const char* filename);

    /**
     *   @}
     *   @addtogroup brokerext-thread
     *   @{
     */

    /** @brief Start a new thread.

     `CMPIBrokerExtFT.newThread()` starts a new thread,
     using POSIX threading semantics.

     Creating a thread using `CMPIBrokerExtFT.newThread()` does not inform
     the MB that the current thread will begin using MB functions. Thus,
     @ref _CMPIBrokerFT::attachThread "CMPIBrokerFT.attachThread()"
     must be called by the new thread before
     it uses MB functions.

     For historical reasons no additional error information is returned.

     @param start Pointer to the function to be started as a thread.
     @param parm Pointer to argument(s) to be passed to that function.
     @param detached If not zero, defines that the new thread should
         run in detached mode. In detached mode, termination of the
         thread that called this function does not cause the new
         thread to be canceled. See @ref ref-ieee-1003-1 "IEEE 1003.1"
         for details on detached mode.
     @return If successful, the handle of the started thread will be returned.
         If not successful, returns NULL.

     @todo TBD: Doxygen does not deal well with arguments that are
         function pointers (`start` in this case). It generates warnings
         and (worse!) the generated function prototype is incorrect.
         How about a typedef for the function pointer? Only way is
         to try it (ks)
     */
    CMPI_THREAD_TYPE (*newThread)
            (CMPI_THREAD_RETURN (CMPI_THREAD_CDECL* start)(void*),
            void* parm, int detached);

    /** @brief Wait until the specified thread ends.

     `CMPIBrokerExtFT.joinThread()` suspends the current thread   
         until the specified thread ends using the POSIX threading semantics.
     @param thread The thread ID of the thread waiting for completion.
     @param retval Pointer to the return value of the thread.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     The Error codes are defined in <errno.h>, specifically for
     the `pthread_join()` function; both are defined in
     @ref ref-ieee-1003-1 "IEEE 1003.1".
     */
    int (*joinThread) (CMPI_THREAD_TYPE thread, CMPI_THREAD_RETURN* retval);

    /** @brief Cause current thread to exit with the passed-in return code,

    `CMPIBrokerExtFT.exitThread()` causes the current thread to exit
        with the passed in return code using POSIX threading semantics.

    The current thread can also exit by simply returning from its thread
        function; the purpose of the
        @ref _CMPIBrokerExtFT::exitThread "CMPIBrokerExtFT.exitThread()"
        function is to make premature returns more convenient.
     @param return_code Is the return code that should be used for the thread.
     @return The function never returns, regardless of whether it is
         successful or encounters errors.
     */
    int (*exitThread) (CMPI_THREAD_RETURN return_code);

    /** @brief Cancel a running thread.

     `CMPIBrokerExtFT.cancelThread()` cancels the thread 
         identified by the thread argument, using POSIX threading
         semantics.
     @param thread  The thread to be canceled.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.
         Error codes are defined in <errno.h>, specifically for the
         `pthread_cancel()` function; both are defined in IEEE 1003.1. The
         `pthread_cancel()` function does not define any error codes in
         IEEE 1003.1. Some POSIX implementations use the following error code
         for that function:
          @li `ESRCH` -The specified thread could not be found.
     @todo validate formatting of return. ESRCH should be a separate paragraph
     */
    int (*cancelThread) (CMPI_THREAD_TYPE thread);

    /** @brief Suspend execution of current thread for a specified duration.

     `CMPIBrokerExtFT.threadSleep()` suspends the execution of the
     current thread for the duration specified by the `msec` argument.
     @param msec The suspend duration in milliseconds.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     Error codes are defined in <errno.h>, defined in IEEE 1003.1.
     */
    int (*threadSleep) (CMPIUint32 msec);

    /** @brief Call a function once for a given once-object.

       `CMPIBrokerExtFT.threadOnce()` executes the specified 
          function procedure only once during the lifetime of the
          thread. The once-object is an integer that initially shall
          have a value of zero. The first call to
           `CMPIBrokerExtFT.threadOnce()` with an initialized
           once-object will call the specified function. On return from
           `CMPIBrokerExtFT.threadOnce()`, it is guaranteed that the
           specified function has completed, and that the once-object has
           been updated to indicate that. Subsequent calls to
           `CMPIBrokerExtFT.threadOnce()` by any thread within the
           process with that once-object will not call the specified function.
     @param once Pointer to the ` once` object. The value of the
         once-object controls whether the specified function has yet to be
         called. The once-object may be located in thread-specific memory
         (that is, each thread has its own separate copy), or in memory
         that is accessible to all threads of the process. The function
         will behave in a thread-safe way. The once-object shall be
         initialized to zero before the first call to the
         `CMPIBrokerExtFT.threadOnce()` function.
     @param function The function to be invoked.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

     Error codes are defined in <errno.h>, specifically for the pthread_once()
         function; both are defined in IEEE 1003.1.
     */
    int (*threadOnce) (int* once, void (*function) (void));

    /** @brief Create a POSIX threading-conformant thread key for
       accessing the thread local store.

     `CMPIBrokerExtFT.createThreadKey()` creates a POSIX threading  
         conformant thread key. This key can be used as a key to
         access the thread local store.
     @param key Pointer to the thread key to be returned.
     @param cleanup Function to be invoked during thread local store cleanup.
     @return If successful, zero will be returned.
        If not successful, a non-zero error code will be returned.
        If successful, zero will be returned.
        Error codes are defined in <errno.h>, specifically for the
        pthread_key_create() function; both are defined in IEEE
        1003.1.
     @todo member detached not documented. Error code in output KS
     */
    int (*createThreadKey) (CMPI_THREAD_KEY_TYPE* key, void (*cleanup)(void*));

    /** @brief Destroy a thread key for accessing the thread local
               store

     `CMPIBrokerExtFT.destroyThreadKey()` destroys a POSIX threading conformant
     thread key for accessing the thread local store.
     @param key The thread key to be destroyed.
     @return If successful, zero will be returned. If not successful, a
     non-zero error code will be returned.
     Error codes are defined in <errno.h>, specifically for the
     pthread_key_delete() function; both are defined in IEEE 1003.1.
     */
    int (*destroyThreadKey) (CMPI_THREAD_KEY_TYPE key);

    /** @brief Get a data pointer from the thread local store using
       a thread key.

     `CMPIBrokerExtFT.getThreadSpecific()` gets a data 
     pointer from the thread local store using a POSIX 
     threading-conformant thread key. 
     @param key The key to be used to retrieve the data pointer.
     @return If successful, returns the data pointer.
     If not successful, returns NULL. For historical reasons, no additional
     error information is passed back.

     */
    void* (*getThreadSpecific) (CMPI_THREAD_KEY_TYPE key);

    /** @brief Set a data pointer in the thread local store using a
               thread key.

     `CMPIBrokerExtFT.setThreadSpecific()` sets a data pointer in the thread
         local store using a POSIX threading-conformant  thread key.
     @param key The key to be used.
     @param value The data pointer that is stored in the thread local store.
     @return If successful, returns zero.
         If not successful, returns a non-zero error code. Error
         codes are defined in <errno.h>, specifically for the
         `pthread_setspecific()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     */
    int (*setThreadSpecific) (CMPI_THREAD_KEY_TYPE key, void* value);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

    /** @brief Create a POSIX thread conformant mutex.

     `CMPIBrokerExtFT.newMutex()` creates a POSIX threading
     conformant recursive mutex.

     The mutex that is created shall exhibits the following behavior:

     <ul>
     <li>For locking a locked mutex: A thread that holds a lock on a
     mutex and attempts to lock that mutex again without first
     unlocking it shall succeed in locking the mutex. Multiple
     locks of the mutex (by the same thread) shall require the same
     number of unlocks (by that same thread) to release the mutex
     before another thread can acquire the mutex.

     <li>For unlocking an unlocked mutex: A thread attempting to
     unlock a mutex that is not locked by that thread (that is, the
     mutex is either entirely unlocked or locked by another thread)
     shall fail in unlocking the mutex.
     </ul>

     This behavior is consistent with mutex type PTHREAD_MUTEX_RECURSIVE
     defined in IEEE 1003.1.

     @param opt For future use. It should be ignored by the MB, and
         MIs should pass a value of 0

     @return If successful, returns the handle of the new mutex.
         If not successful, returns NULL.
         For historical reasons, no additional error information is passed back.
     */
    CMPI_MUTEX_TYPE (*newMutex) (int opt);

    /** @brief Destroy a POSIX threading-conformant mutex <b>(Deprecated)</b>.

     `CMPIBrokerExtFT.destroyMutex()` destroys a POSIX threading conformant
     mutex.

     @param mutex The mutex to be destroyed.

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use @ref _CMPIBrokerExtFT::destroyMutex2 "CMPIBrokerExtFT.destroyMutex2()"
     instead.
     */
    void (*destroyMutex) (CMPI_MUTEX_TYPE mutex);

    /** @brief Lock a POSIX threading-conformant mutex.
               <b>(Deprecated)</b>

     `CMPIBrokerExtFT.lockMutex()` locks a POSIX threading-conformant mutex.

     If the mutex is locked by another thread, the current thread is suspended
     until the lock is granted. The behavior in case the mutex is already
     locked by the current thread is defined in the description of
     @ref _CMPIBrokerExtFT::newMutex "CMPIBrokerExtFT.newMutex()".

     @param mutex The mutex to be locked.

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use @ref _CMPIBrokerExtFT::lockMutex2 "CMPIBrokerExtFT.lockMutex2()"
     instead.

     @retval None. For historical reasons, this function does not
         indicate whether it succeeded or failed.
     */
    void (*lockMutex) (CMPI_MUTEX_TYPE mutex);

    /** @brief Unlock a POSIX threading-conformant mutex <b>(Deprecated)</b>.

     `CMPIBrokerExtFT.unlockMutex()` releases control of the mutex.

     The behavior in case the mutex is not
     locked by the current thread is defined in the description of
     @ref _CMPIBrokerExtFT::newMutex "CMPIBrokerExtFT.newMutex()".

     @param mutex The mutex to be unlocked.

     @retval None. For historical reasons, this function does not
     indicate whether it succeeded or failed.

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use @ref _CMPIBrokerExtFT::unlockMutex2 "CMPIBrokerExtFT.unlockMutex2()"
     instead.

     @todo confirm that the retval is correct key name ks
     */
    void (*unlockMutex) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /** @brief Create a new condition variable.

     `CMPIBrokerExtFT.newCondition()` creates a new POSIX threading-conformant
         condition variable.
     @param opt for future use. It should be ignored by the MB, and MIs
     should pass a value of 0.
     @return If successful, handle of newly created condition
         variable. If not successful, NULL. For historical reasons,
         no additional error information is passed back.
     */
    CMPI_COND_TYPE (*newCondition) (int opt);

    /** @brief Destroy a condition variable <b>(Deprecated)</b>

     `CMPIBrokerExtFT.destroyCondition()` destroys a POSIX threading conformant
     condition variable <b>(Deprecated)</b>.

     @param cond The condition variable to be destroyed.
     @return None. For historical reasons, this function does not
         indicate whether it succeeded or failed.
     @deprecated Deprecated effective CMPI 2.1 because it does not indicate
     whether it succeeded or failed. Use
     @ref _CMPIBrokerExtFT::destroyCondition2
     "CMPIBrokerExtFT.destroyCondition2()" instead.
     */
    void (*destroyCondition) (CMPI_COND_TYPE cond);

    /** @brief Wait until condition is signalled.

     `CMPIBrokerExtFT.condWait()` waits until the condition has been
     signalled. If the condition variable has been signalled already, the
     function returns immediately; otherwise, it suspends the current thread
     to wait for the signal and then returns.

     @param cond  The handle of the condition variable to be used.
     @param mutex  The handle of a locked mutex guarding this
         condition variable.
     @return If successful, zero will be returned.
        If not successful, returns a non-zero error code will be returned.
        Error codes are defined in <errno.h>, specifically for the
        pthread_cond_wait() function; both are defined in IEEE 1003.1.

     */
    int (*condWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex);

    /** @brief Wait until the condition is signalled or a timeout
               value expires.

     `CMPIBrokerExtFT.timedCondWait()` waits until a POSIX
     threading-conformant condition variable is signalled. If the condition
     variable has been signalled already, the function returns immediately;
     otherwise, it suspends the current thread to wait for the signal and
     then returns. The function returns when the timeout expires before the
     condition is signalled.

     @param cond Specifies the handle of the condition variable to be used.
     @param mutex Specifies the handle of a locked mutex guarding
         this condition variable.
     @param wait Specifies the timeout value.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in `<errno.h>`, specifically for the
         `pthread_cond_timedwait()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @todo we do not specify the timeout value characteristics either
           here or in the spec. Commented in FINAL RC3 vote.
     */
    int (*timedCondWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex,
            struct timespec* wait);

    /** @brief Send a signal to a condition variable.

     `CMPIBrokerExtFT.signalCondition()` sends a signal
     to a POSIX threading-conformant condition variable.

     @param cond Specifies the handle of the condition variable to
                 send the signal.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in `<errno.h>`, specifically for the
         `pthread_cond_signal()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
    */
    int (*signalCondition) (CMPI_COND_TYPE cond);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

#ifdef CMPI_VER_210

    /** @brief Destroy a POSIX threading-conformant mutex.

     `CMPIBrokerExtFT.destroyMutex2()` destroys a POSIX threading conformant
     mutex.

     This function superceedes the original @ref _CMPIBrokerExtFT::destroyMutex
     "destroyMutex()" function.

     @param mutex The mutex to be destroyed.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            `pthread_mutex_destroy()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @version Added in CMPI 2.1.
     */
    int (*destroyMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Lock a POSIX threading-conformant mutex.

     `CMPIBrokerExtFT.lockMutex2()` locks a POSIX threading conformant mutex.
     If the mutex is locked by another
     thread, the current thread is suspended until the lock is granted.
     The behavior in case the mutex is already locked by the current thread
     is defined in the description of @ref _CMPIBrokerExtFT::newMutex
     "CMPIBrokerExtFT.newMutex()".

     This function superceedes the original @ref _CMPIBrokerExtFT::lockMutex
     "lockMutex()" function.
     @param mutex The mutex to be locked.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            `pthread_mutex_lock()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @version Added in CMPI 2.1 superceeding deprecated
     @ref _CMPIBrokerExtFT::lockMutex "CMPIBrokerExtFT.lockMutex()" function.
     */
    int (*lockMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Unlock a POSIX threading-conformant mutex.

     `CMPIBrokerExtFT.unlockMutex2()` unlocks a POSIX
     threading conformant mutex. The behavior in case the mutex
     is not locked by the current thread is defined in the description of
     @ref _CMPIBrokerExtFT::newMutex "CMPIBrokerExtFT.newMutex()".

     This function superceedes the original @ref _CMPIBrokerExtFT::unlockMutex
     "unlockMutex()" function.

     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            `pthread_mutex_lock()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @version Added in CMPI 2.1.
     */
    int (*unlockMutex2) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /** @brief Destroy a POSIX threading-conformant condition
               variable.

     `CMPIBrokerExtFT.destroyCondition2()` destroys a POSIX
     threading-conformant condition variable.

     This function superceedes the original
     @ref _CMPIBrokerExtFT::destroyCondition "destroyCondition()" function.

     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
         are defined in <errno.h>, specifically for the
         `pthread_cond_destroy()` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @version Added in CMPI 2.1.
     */
    int (*destroyCondition2) (CMPI_COND_TYPE cond);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

};

#ifdef CMPI_VER_200

/**
 * @brief Function table for MB memory enhancement services of
 * @ref _CMPIBroker "CMPIBroker object".
 *
 * This function table provides memory management services.
 */
struct _CMPIBrokerMemFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokermem-all
     *   @{
     */

    /** @brief Mark a new object lifecycle level for subsequent
           newly created CMPI encapsulated data type objects.

     `CMPIBrokerMemFT.mark()` marks a new object lifecycle level for the
     calling MI. Subsequent newly created CMPI encapsulated data type objects
     in that MI will be associated with that new object lifecycle level.
     A subsequent invocation of @ref _CMPIBrokerMemFT::release
     "CMPIBrokerMemFT.release()"
     with the returned @ref CMPIGcStat pointer will release only the
     objects associated with that object lifecycle level.

     The mark() and release() function calls may be stacked.

     Stacked object lifecycle levels shall not overlap.

     @param mb The broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a @ref CMPIGcStat
     structure, for use with @ref _CMPIBrokerMemFT::release
     "CMPIBrokerMemFT.release()".

     If not successful, returns NULL.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_FAILED` - Unspecified error occurred.

     */
    CMPIGcStat* (*mark) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Release all CMPI encapsulated data type objects
       created at the specified object lifecycle level, and remove
       that level.

     `CMPIBrokerMemFT.release()` releases all CMPI encapsulated data type
     objects created
     other than with `clone()` at the specified object lifecycle
     level, and removes that object lifecycle level. This indicates
     to the MB that these objects (including any objects they
     contain) will no longer be used by the MI. The MB may free the
     resources associated with these objects during the call to this
     function, or later during some garbage collection cycle.

     The mark() and release() function calls may be stacked.

     @param mb Pointer to the broker.
     @param gc The handle returned from the mark() operation.
     @return CMPIStatus structure indicating the function return
         status.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_FAILED` - Unspecified error occurred.
     */
    CMPIStatus (*release) (const CMPIBroker* mb, const CMPIGcStat* gc);

    /** @brief Allocate an uninitalized memory block of specified
               size.

     `CMPIBrokerMemFT.cmpiMalloc()` allocates an uninitalized memory block of
     the specified size. This function behaves consistently with the
     POSIX `` malloc()`` function (see @ref ref-ieee-1003-1 "IEEE 1003.1").

     The allocated memory block can be explicitly released by the MI using
     @ref _CMPIBrokerMemFT::cmpiFree "CMPIBrokerMemFT.cmpiFree()", or will be
     automatically released by the MB after cleanup of the MI.
     @param mb Pointer to a CMPIBroker structure.
     @param size Specifies the amount of memory to allocate in Bytes.
     @return Returns a pointer to the allocated memory, or NULL if the memory
         could not be allocated. No additional error information is returned.
     */
    void* (*cmpiMalloc) (const CMPIBroker* mb, size_t size);

    /** @brief Change the size of a memory block.

     `CMPIBrokerMemFT.cmpiCalloc()` changes the size of the memory block
     pointed to by ptr which had been returned by a previous call to
     @ref _CMPIBrokerMemFT::cmpiMalloc "CMPIBrokerMemFT.cmpiMalloc()" or
     @ref _CMPIBrokerMemFT::cmpiCalloc "CMPIBrokerMemFT.cmpiCalloc()".
     This function behaves consistently with the POSIX ``realloc()`` function
     (see @ref ref-ieee-1003-1 "IEEE 1003.1").

     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb Pointer to a CMPIBroker structure.
     @param nElems The number of elements to allocate.
     @param sizeElem The size of each element to allocate.
     @return Returns a pointer to the allocated memory, or NULL if the memory
         could not be allocated. No additional error information is returned.
     */
    void* (*cmpiCalloc) (const CMPIBroker* mb, size_t nElems, size_t sizeElem);

    /** @brief Change the size of a memory block.

     `CMPIBrokerMemFT.cmpiRealloc()` changes the size of the memory block
     pointed to by `ptr` which had been returned by a previous call to
     @ref _CMPIBrokerMemFT::cmpiMalloc "CMPIBrokerMemFT.cmpiMalloc()" or
     @ref _CMPIBrokerMemFT::cmpiCalloc "CMPIBrokerMemFT.cmpiCalloc()".
     This function behaves consistently with the POSIX ``realloc()`` function
     (see @ref ref-ieee-1003-1 "IEEE 1003.1").

     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb Pointer to a CMPIBroker structure.
     @param ptr Pointer to previosuly allocated memory.  Passing a pointer
     to this function which was not allocated explicitly by cmpiMalloc()
     or cmpiCalloc() is undefined.
     @param size The new size of the memory block in Bytes.
     @return If successful, a pointer to the resized allocated memory block
     NULL if the new memory is not allcoated. If the function fails
     the original `ptr` argument is unchanged.
     */
    void* (*cmpiRealloc) (const CMPIBroker* mb, void* ptr, size_t size);

    /** @brief Allocate a memory block and initialize it with a string.

     `CMPIBrokerMemFT.cmpiStrDup()` allocates a memory
     block and initializes it by copying a C-language string into it. This
     function behaves consistently with the POSIX ``strdup()`` function
     (see @ref ref-ieee-1003-1 "IEEE 1003.1").
     The allocated memory block can be explicitly
     released by the MI using
     @ref _CMPIBrokerMemFT::cmpiFree "CMPIBrokerMemFT.cmpiFree()", or will be
     automatically released by the MB after cleanup of the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param str The C-language string to duplicate.
     @return a pointer pointer to the new memory block (that is, to the new
        C-language string, or NULL if unsuccessful.
     */
    char* (*cmpiStrDup) (const CMPIBroker* mb, const char* str);

    /** @brief Free a memory block.

     `CMPIBrokerMemFT.cmpiFree()` releases a memory block allocated via
     @ref _CMPIBrokerMemFT::cmpiMalloc "CMPIBrokerMemFT.cmpiMalloc()",
     @ref _CMPIBrokerMemFT::cmpiCalloc "CMPIBrokerMemFT.cmpiCalloc()", or
     @ref _CMPIBrokerMemFT::cmpiRealloc "CMPIBrokerMemFT.cmpiRealloc()".

     This function behaves consistently with the POSIX ``free()`` function
     (see @ref ref-ieee-1003-1 "IEEE 1003.1").
     This indicates to the MB that the memory block will
     no longer be used by the MI. The MB may free (=reclaim) the memory
     block during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7). Memory blocks that have not
     been explicitly released that way, will be automatically released
     after cleanup of the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param ptr The memory to free. This memory MUST have been allocated via
     the cmpiMalloc, cmpiCalloc or cmpiRealloc functions.
     @return None. Does not indicate whether it succeeded or failed.
     */
    void (*cmpiFree) (const CMPIBroker* mb, void* ptr);

    /** @brief Release a CMPIInstance object.

     `CMPIBrokerMemFT.freeInstance()` releases a CMPIInstance object.
     This indicates to the
     MB that the object (including any objects it contains) will no
     longer be used by the MI. The MB may free the resources
     associated with the object during the call to this function, or
     later during some garbage collection cycle.

     Allows a MI to free memory associated to a CMPIInstance
     which was allocated via @ref _CMPIBrokerEncFT::newInstance
     "CMPIBrokerEncFT.newInstance()".
     this function should be called when an instance is no longer
     being used by the MI. This function will free all contained
     objects (e.g. properties).
     @param mb Pointer to a CMPIBroker structure.
     @param inst Pointer to to the CMPIInstance object to be released.
         This object shall have been created via
         @ref _CMPIBrokerEncFT::newInstance "CMPIBrokerEncFT.newInstance()".
     @return None.  Does not indicate whether it succeeded or failed.
     */
    void (*freeInstance) (const CMPIBroker* mb, CMPIInstance* inst);

    /** @brief Release a CMPIObjectPath object.

     `CMPIBrokerMemFT.freeInstance()` releases a
     CMPIObjectPath object. This indicates to the MB that the object
     (including any objects it contains) will no longer be used by the MI.
     The MB may free the resources associated with the object during the call
     to this function, or later during some garbage collection cycle.

     Allows a MI to free memory associated to a
     CMPIObjectPath which was allocated via
     @ref _CMPIBrokerEncFT::newObjectPath "CMPIBrokerEncFT.newObjectPath()".
     This function should
     be called when a CMPIObjectPath is no longer being
     used by the MI. This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param obj Pointer to the CMPIObjectPath object that is to be released.
     This object shall have been created via
     @ref _CMPIBrokerEncFT::newObjectPath "CMPIBrokerEncFT.newObjectPath()".
     @return None
     */
    void (*freeObjectPath) (const CMPIBroker* mb, CMPIObjectPath* obj);

    /** @brief Release a CMPIArgs object.

    `CMPIBrokerMemFT.freeArgs()` releases a CMPIArgs object.
    This indicates to the MB that the object (including any objects it
    contains) will no longer be used by the MI. The MB may free (=reclaim)
    the memory associated with the object during the call to this function,
    or later during some garbage collection cycle (see Subclause 4.1.7).

     @param mb Pointer to a CMPIBroker structure.
     @param args Pointer to to the CMPIArgs object that is to be released. This
         object shall have been created via
         @ref _CMPIBrokerEncFT::newArgs "CMPIBrokerEncFT.newArgs()".
     @return None.
     */
    void (*freeArgs) (const CMPIBroker* mb, CMPIArgs* args);

    /** @brief Release a CMPIString object.

     `CMPIBrokerMemFT.freeString()` releases a CMPIString object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows an MI to free memory associated to a CMPIString which was
     allocated via
     @ref _CMPIBrokerEncFT::newString "CMPIBrokerEncFT.newString()".
     This function should be called when an instance is no longer being used
     by the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param args The string to free.
     @return None.
     */
    void (*freeString) (const CMPIBroker* mb, CMPIString* str);

    /** @brief Release a CMPIArray object.

     `CMPIBrokerMemFT.freeArray()` releases a CMPIArray object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a CMPIArray which was
     allocated via
     @ref _CMPIBrokerEncFT::newArray "CMPIBrokerEncFT.newArray()".
     This function should
     be called when an instance is no longer being used by the MI. This
     function will free all contained objects (e.g. the array elements).

     @param mb Pointer to a CMPIBroker structure.
     @param array Pointer to to the CMPIArray object that is to be 
     released.This object shall have been created via 
     @ref _CMPIBrokerEncFT::newArray "CMPIBrokerEncFT.newArray()".
     @return None.
     */
    void (*freeArray) (const CMPIBroker* mb, CMPIArray* array);

    /** @brief Release a CMPIDateTime object.

     `CMPIBrokerMemFT.freeDateTime()` releases a
     CMPIDateTime object. This indicates to the MB that the object
     (including any objects it contains) will no longer be used by
     the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during
     some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a CMPIDateTime which was
     allocated via
     @ref _CMPIBrokerEncFT::newDateTime "CMPIBrokerEncFT.newDateTime()".
     This function
     should be called when an instance is no longer being used by the MI.
     This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param dt Pointer to to the CMPIDateTime object that is to be released.
         This object shall have been created via
         @ref _CMPIBrokerEncFT::newDateTime "CMPIBrokerEncFT.newDateTime()".
     @return None.
     */
    void (*freeDateTime) (const CMPIBroker* mb, CMPIDateTime* dt);

    /** @brief Release a CMPISelectExp object.

    `CMPIBrokerMemFT.freeSelectExp()` releases a
     CMPISelectExp object. This indicates to the MB that the object
     (including any objects it contains) will no longer be used by
     the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during
     some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a CMPISelectExp which was
     allocated via
     @ref _CMPIBrokerEncFT::newSelectExp "CMPIBrokerEncFT.newSelectExp()".
     This function
     should be called when an instance is no longer being used by the MI.

     This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param se Pointer to to the CMPISelectExp object that is to be released.
         This object shall have been created via
         @ref _CMPIBrokerEncFT::newSelectExp "CMPIBrokerEncFT.newSelectExp()".
     @return None.
     */
    void (*freeSelectExp) (const CMPIBroker* mb, CMPISelectExp* se);

#ifdef CMPI_VER_210

    /** @brief Free the memory of a C-language string.

     `CMPIBrokerMemFT.freeChars()` releases a C-language string
     (see Subclause 5.2.1). This indicates to the MB that the string will
     no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the string during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7).

     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.
     Availability of the Codepage Conversion capability can be queried by
     an MI using the CMPI_MB_CodepageConversion test mask on the
     `brokerCapabilities` member of the CMPIBrokerFT
     structure.

     @param mb Pointer to a CMPIBroker structure.
     @param chars Pointer to to the C-language string to be released.
         This C-language string shall have been created via
         @ref _CMPIStringFT::newCharsCP "CMPIStringFT.newCharsCP()".
     @return None.
     @version Added in CMPI 2.1.
     @todo could we more precisely define  broker, ex.
           CMPIBrokerFT.brokerCapabilities
     */
    void (*freeChars) (const CMPIBroker* mb, char* chars);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

};

#endif /*CMPI_VER_200*/

/**
 * @}
 * @addtogroup edt-context
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
 * @brief Function table of @ref _CMPIContext
 *     "CMPIContext encapsulated data type object".
 */
struct _CMPIContextFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIContext object.

    `CMPIContextFT.release()` releases a CMPIContext object.

    The CMPIContext object will not be used any further and may be freed by
    CMPI run time system.
    @param ctx Pointer to CMPIContext to be released.
    @return CMPIStatus structure indicating the function return status.
        The function return status indicates one of the following
    @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.

     @todo ks CMPIContext does not resolve to a link.
     */
    CMPIStatus (*release) (CMPIContext* ctx);

    /** @brief Create an independent copy of a CMPIContext
               object.

     `CMPIContextFT.clone()` creates an independent copy of the
         CMPIContext object.
     @param ctx Context this pointer.
     @param[out] rc If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return
         status.
     @return Pointer to copied CMPIContext object. The returned
         CMPIContext object shall be explicity released by the
         MI using @ref _CMPIContextFT::release "CMPIContextFT.release()".

     The function return status indicates one of the following @ref CMPIrc
         codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
    */
    CMPIContext* (*clone) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief Get a context entry in a CMPIContext object by name.

     `CMPIContextFT.getEntry()` gets a context entry in a
     CMPIContext object by supplying its name.

     @param ctx CMPIContext object for this function
     @param name string specifying the context entry name.See
         @link def-context-fieldnames definition of context
         entry names @endlink for defined names
     @param rc  Output: The rc output argument, if not NULL, points to a
         CMPIStatus structure that upon return will have been
         updated with the function return status
     @return If successful, a CMPIData structure containing the specified
        context entry will be returned. If not successful,
        CMPIData.state will have the CMPI_badValue flag set to true.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
     */
    CMPIData (*getEntry) (const CMPIContext* ctx, const char* name,
            CMPIStatus* rc);

    /** @brief Get a context entry in a CMPIContext object by index.

     `CMPIContextFT.getEntryAt()` gets a Context entry value defined
     by its index.
     @param ctx Pointer to the CMPIContext object for this function.
     @param index Specifies the zero-based position of the
         context entry in the internal data array. The order of
         context entries in the internal data array is
         implementation-defined.
     @param[out] name If not NULL, points to a CMPIString pointer that upon
         success will have been updated to point to a CMPIString object
         containing the name of the returned context entry. The returned
         CMPIString object shall not be explicitly released by the MI, because
         it may be an internal object of the CMPIContext object which will be
         released along with that object, or a new object created by the MB
         which will be automatically released by the MB (see Subclause 4.1.7).
     @param[out] rc If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return
         status.
     @return If successful, returns a CMPIData structure containing 
     the specified context entry. 
     If not successful, CMPIData.state will have the CMPI_badValue
         flag set to true.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
     */
    CMPIData (*getEntryAt) (const CMPIContext* ctx, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get the number of context entries in a CMPIContext
               object.

     `CMPIContextFT.getEntryCount()` gets the number of entries
     contained in this CMPIContext.
     @param ctx CMPIContext object for this function.
     @return If successful, a CMPICount value indicating the number of entries
         in the CMPIContext object. If not successful, the return value will
         be undefined.

     The function return status indicates one of the following @ref
     CMPIrc odes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
     */
    CMPICount (*getEntryCount) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief Add or replace a context entry in a CMPIContext object.

     `CMPIContextFT.addEntry()`  adds or replaces a context entry
        in a CMPIContext object. See Subclause 8.1 for defined context entries.
     @param ctx Context this pointer.
     @param name Entry name. Pointer to a CMPIString defining a context name.
         See @link def-context-fieldnames definition of context
         entry names @endlink for defined names.
     @param value Address of CMPIValue structure containing the
         non-NULL value to be assigned to the context entry
         or NULL to specify that NULL is to be assigned.
     @param type CMPIType value specifying the type of the value to be
         assigned. If the value of the type argument is CMPI_chars or
         CMPI_charsA, the C-language string to which the chars member of the
         value argument points is copied by this function and the original
         string memory may be freed by the MI right after this function returns.
     @return A CMPIStatus structure indicating the function return status will
         be returned.

     The function return status indicates one of the following @ref CMPIrc
         codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - `type` not supported for
             this call, or `type` is not recognized.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.

     @todo should the link above be a ref to the names definitions for
           context entries. Also really poor description. Description now sam
           as spec. (ks)
     */
    CMPIStatus (*addEntry) (const CMPIContext* ctx, const char* name,
            const CMPIValue* value, const CMPIType type);

};

/**
 * @}
 * @addtogroup edt-result
 * @{
 */

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
 * @brief Function table of @ref _CMPIResult
 *     "CMPIResult encapsulated data type object".
 */
struct _CMPIResultFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIResult object.

     `CMPIResultFT.release()` releases a CMPIResult object.
         This indicates to the MB that
         the object (including any objects it contains) will no longer
         be used by the MI. The MB may free the resources associated with
         the object during the call to this function, or later during
         some garbage collection cycle.
     @param rslt Pointer to the CMPIResult object to be released.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid.
     */
    CMPIStatus (*release) (CMPIResult* rslt);

    /** @brief Create an independent copy of a CMPIResult object.

     `CMPIResultFT.clone()` creates an independent copy of the
     CMPIResult object defined by `rslt`.
     @param rslt Pointer to CMPIResult object to be copied.
     @param[out] rc If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
     @return If successful, returns a pointer to the copied CMPIPropertyList
         object.

         The returned CMPIResult object shall be explicitly released by
         the MI using @ref _CMPIResultFT::release "CMPIResultFT.release()".

         If not successful, returns NULL.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid.

     */
    CMPIResult* (*clone) (const CMPIResult* rslt, CMPIStatus* rc);

    /** @brief Add a value/type pair to a CMPIResult object.

     `CMPIResultFT.returnData()` adds a value/type pair to be
     returned to the MB, to a CMPIResult object.
     @param rslt CMPIResult object for this function.
     @param value Pointer to CMPIValue structure specifying the non-NULL value
         to be returned, or is NULL to specify that NULL is to be returned
     @param type CMPIType value specifying the type to be returned.
     If the value of the `type` argument is CMPI_chars or
         CMPI_charsA, the C-language string to which the chars member of the
         `value` argument points is copied by this function and the
         original string memory may be freed by the MI right after this
         function returns.

     @return A CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
         codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - An attempt to return a data type
                that is not allowed for this MI function invocation
                or `type` is not recognized.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid
               or NULL, or the MB has aborted the request operation for which
               this data is being returned.
     */
    CMPIStatus (*returnData) (const CMPIResult* rslt, const CMPIValue* value,
            const CMPIType type);

    /** @brief Add an instance to a CMPIResult object.

     `CMPIResultFT.returnInstance()` adds an instance to be returned to the MB,
         to a CMPIResult object.
     @param rslt Pointer to the CMPIResult object for this function.
     @param inst Instance to be returned.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid
             or the MB has aborted the request for which this data
             is returned.
    */
    CMPIStatus (*returnInstance) (const CMPIResult* rslt,
            const CMPIInstance* inst);

    /** @brief Add an object path to a CMPIResult object.

        `CMPIResultFT.returnInstance()` adds an instance to
        be returned to the MB, to a CMPIResult object.
     @param rslt CMPIResult object for this function.
     @param ref CMPIObjectPath to be returned.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid
             or the MB has aborted the request for which this data
             is returned.

     @todo arg 2 is op in spec (ks) Should we modify here to match
           spec?
     */
    CMPIStatus (*returnObjectPath) (const CMPIResult* rslt,
            const CMPIObjectPath* ref);

    /** @brief Indicate that no more items will be added to a
         CMPIResult object.

     `CMPIResultFT.returnDone()` indicates to the MB that
         no further items will be added to a CMPIResult object; that
         is, the MI will not return any more data to the MB.
     @param rslt CMPIResult object for this function.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid
             or the MB has aborted the request for which this data is returned.
     */
    CMPIStatus (*returnDone) (const CMPIResult* rslt);

#ifdef CMPI_VER_200

    /** @brief Add an error to a CMPIResult object.

     `CMPIResultFT.returnError()` adds an error to be returned to the MB, to a
         CMPIResult object.

     In WBEM protocols that support multiple extended errors in an error
     response, the MB shall represent the extended errors in the protocol in
     the order of calls to this function. In WBEM protocols that support only
     one extended error in an error response, the MB shall represent the
     extended error from the first call to this function for a particular
     result.

     This function is part of the Extended Errors capability of an MB
         (see tSubclause 8.14). From CMPI 2.1 on, the Extended Errors
         capability shall be available.
     @param rslt CMPIResult object for this function.
     @param er Pointer to aCMPIError object representing the error to be
         returned. This function may be called multiple times, each time adding
         one CMPIError object to the set of extended errors for this result.
         This function is part of the Extended Errors capability of an MB
         (see todo). From CMPI 2.1 on, the Extended Errors capability
         shall be available.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `rslt` handle is invalid
             or the MB has aborted the request for which this data is returned.

     @todo review this description, particularly "see todo". Moved the part of
     cmt
     @version Added CMPI 2.0.
     */
    CMPIStatus (*returnError) (const CMPIResult* rslt, const CMPIError* er);

#endif /*CMPI_VER_200*/

};

/**
 * @}
 * @addtogroup edt-error
 * @{
 */

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
 * @brief Function table of @ref _CMPIError
 *     "CMPIError encapsulated data type object".
 */
struct _CMPIErrorFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIError object.

     `CMPIErrorFT.release()` releases a CMPIError object.

         The Error object will not be used any further and may be freed by
         CMPI run time system. The MB may free the resources associated with the
         object during the call to this function, or later during some garbage
         collection cycle.
     @param er Pointer to the CMPIError object to be released.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `er` argument is
             invalid.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     @todo ordering here diff than spec.  This is sect 8.14
     */
    CMPIStatus (*release) (CMPIError* er);

    /** @brief Create an independent copy of a CMPIError object.

     `CMPIErrorFT.clone()` creates an independent copy of a CMPIError object.

     @param er Pointer to the CMPIError object to be copied.
     @param rc Output: if not NULL, points to a CMPIStatus
        structure* that upon return will have been updated with the
        function return status.
     @return If successful, returns a pointer to the copied CMPIError object.
         The returned CMPIError object shall be explicitly released by the MI
         using @ref _CMPIErrorFT::release "CMPIErrorFT.release()".
         If not successful, returns NULL. If
         not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIError* (*clone) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorType attribute of a CMPIError object.

     `CMPIErrorFT.getErrorType()` gets the value of the
         ErrorType attribute in a CMPIError object.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: If not NULL, points to a CMPIStatus
         structure* that updated wit the function return status.
     @return If successful, returns a CMPIErrorType enumeration value,
         indicating the value of the ErrorType attribute in the CMPIError
         object.
         If not successful, the returned value is undefined.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIErrorType (*getErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the OtherErrorType attribute of a CMPIError
       object.

     `CMPIErrorFT.getOtherErrorType()` gets a string which describes
     the alternate error type.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful and the OtherErrorType attribute of the CMPIError
         object is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the OtherErrorType attribute of the CMPIError
         object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether the
         function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getOtherErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the OwningEntity attribute of a CMPIError object.

     `CMPIErrorFT.getOwningEntity()` returns a string which describes the
     owning entity.
     @param er Error this pointer
     @param rc Output: if not NULL, points to a CMPIStatus structure
         updated with the function return status.
     @return If successful and the OwningEntity attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the OwningEntity attribute of the CMPIError
         object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getOwningEntity) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the MessageID attribute of a CMPIError object.

     `CMPIErrorFT.getMessageID()` returns a string which is the message ID.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful and the MessageID attribute of the CMPIError object
         is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the MessageID attribute of the CMPIError
         object. The returned CMPIString object shall not be explicitly
         released by the MI, because it may be an internal object of the
         CMPIError object which will be released along with that object, or a
         new object created by the MB which will be released automatically by
         the MB. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether the
         function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement     */
    CMPIString* (*getMessageID) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the Message attribute of a CMPIError object.

     `CMPIErrorFT.getMessage()` returns a string comnating an error message.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful and the Message attribute of the CMPIError object
         is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the Message attribute of the CMPIError object.
         Otherwise,returns NULL.
        The caller must inspect the function return status to see whether
        the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement     */
    CMPIString* (*getMessage) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the PerceivedSeverity attribute of a CMPIError object

     `CMPIErrorFT.getPerceivedSeverity()` returns the PerceivedSeverity
     attribute of a CMPIError object.
     @param er  Pointer to to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful, a CMPIErrorSeverity enumeration value will be
         returned, indicating the value of the PerceivedSeverity attribute of
         the CMPIError object. If not successful, the returned value is
         undefined.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
    */
    CMPIErrorSeverity (*getPerceivedSeverity) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the ProbableCause attribute of a CMPIError object.

     `CMPIErrorFT.getProbableCause()` returns the ProbableCause attribute
     of a CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         updated with the function return status.
     @return If successful, a CMPIErrorProbableCause enumeration value
         will be returned, indicating the value of the ProbableCause attribute
         of the CMPIError object.
         If not successful, the returned value is undefined.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
    */
    CMPIErrorProbableCause (*getProbableCause) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the ProbableCauseDescription attribute of a
       CMPIError object.

     `CMPIErrorFT.getProbableCauseDescription()` returns a string which
     describes the probable cause.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful and the ProbableCauseDescription attribute of the
         CMPIError object is non-NULL, returnsa pointer to a CMPIString object,
         indicating the value of the ProbableCauseDescription
         attribute of the CMPIError object.
         Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getProbableCauseDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the RecommendedActions array attribute of a
       CMPIError object.

     `CMPIErrorFT.getRecommendedActions()` returns an array of strings which
     describes recomended actions of the CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the RecommendedActions array attribute of the
         CMPIError object is non-NULL, returns a pointer to a CMPIArray object,
         containing CMPIString elements that represent the
         array elements of the RecommendedActions array attribute in the
         CMPIError object.
         Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIArray* (*getRecommendedActions) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorSource attribute of a CMPIError object.

     `CMPIErrorFT.getErrorSource()` returns a string which describes the
     Error source of the CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the ErrorSource attribute of the CMPIError
         object is non-NULL, returnsa pointer to a CMPIString object,
         indicating the value of the ErrorSource attribute of the
         CMPIError object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getErrorSource) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorSourceFormat attribute of a CMPIError
     object.

     `CMPIErrorFT.getErrorSourceFormat()` returns a the format that the
     error src is in.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, returns a CMPIErrorSrcFormat enumeration,
         indicating the value of the ErrorSourceFormat attribute of
         the CMPIError object.
         If not successful, the returned value is undefined.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIErrorSrcFormat (*getErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the OtherErrorSourceFormat attribute of a
     CMPIError object.

     `CMPIErrorFT.getOtherErrorSourceFormat()` returns a string which
     describes the 'other' format; only available
     if the error source is OTHER.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the OtherErrorSource attribute of the CMPIError
         object is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the OtherErrorSourceFormat attribute of the
         CMPIError object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getOtherErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the CIMStatusCode attribute of a CMPIError
               object.

     `CMPIErrorFT.getCIMStatusCode()` gets the value of the
     CIMStatusCode attribute of a CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, returns a @ref CMPIrc value indicating the value 
         of the CIMStatusCode attribute of the CMPIError object.
         Please note that not all status codes apply to all situations.
         It is up to the MI to ensure the correct status code is set.
         If not successful, the returned value is undefined.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIrc (*getCIMStatusCode) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get CIMStatusCodeDescription attribute of a CMPIError object.

     `CMPIErrorFT.getCIMStatusCodeDescription()` gets the
     value of the CIMStatusCodeDescription attribute of a CMPIError
     object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the CIMStatusCodeDescription attribute of the
         CMPIError object is non-NULL, returns a pointer to a CMPIString
         object, indicating the value of the CIMStatusCodeDescription
         attribute of the CMPIError object.
         Otherwise, returns NULL.

         The caller must inspect the function return status to see whether
         the function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIString* (*getCIMStatusCodeDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the MessageArguments array attribute of a CMPIError object.

     `CMPIErrorFT.getMessageArguments()` gets the value of
     the MessageArguments array attribute of a CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the MessageArguments array attribute of the
         CMPIError object is non-NULL, returns a pointer to a CMPIArray
         object, containing CMPIString objects that
         represent the array elements of the MessageArguments array
         attribute of the CMPIError object. Otherwise, returns NULL.

         The caller must inspect the function return status to see whether the
         function failed.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
             by the MB. In CMPI 2.1, this return code has been
             deprecated. It will not be returned because the
             Extended Errors capability will be available.
             (Deprecated)
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a
       requirement
     */
    CMPIArray* (*getMessageArguments) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Set the `ErrorType` attribute of a CMPIError object.

     `CMPIErrorFT.setErrorType()` sets the value of the ErrorType
     attribute of this CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param et CMPIErrorType enumeration value specifying the new value for
         the `ErrorType` attribute. If the error message in the
         CMPIError object
         is defined in a DMTF message registry, the `et` argument shall
         reflect the content of the ERROR_TYPE element defined for
         the message in the registry.
     @return Output: CMPIStatus structure indicating the function return status

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     @todo we are inconsistent in the formatting of the various
           attributes for CMPIError. Need to generalize this
    */
    CMPIStatus (*setErrorType) (const CMPIError* er, const CMPIErrorType et);

    /** @brief Set the OtherErrorType attribute of a CMPIError object.

     `CMPIErrorFT.setOtherErrorType()` sets the 'other' error type
         of this CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param oet Pointer to a string specifying the new non-NULL
        value for the OtherErrorType attribute, or is NULL
        specifying that the attribute will be set to NULL. If the
        error message is defined in a DMTF message registry, the
        string value of the oet argument shall be the content of
        the OTHER_ERROR_TYPE element defined for the message in the
         registry It is only valid when error type is "OTHER"
     @return Output: CMPIStatus structure indicating the function return
     status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setOtherErrorType) (const CMPIError* er, const char* oet);

    /** @brief Set the `ProbableCauseDescription` attribute of a
     CMPIError object.

     `CMPIErrorFT.setProbableCauseDescription()` sets the description of the
     probable cause.
     @param er Pointer to the CMPIError object for this function.
     @param pcd string specifying the new non-NULL value for the
         `ProbableCauseDescription` attribute, or is NULL specifying
         that the attribute will be set to NULL. If the error
         message is defined in a DMTF message registry, note that
         the string value of the pcd argument is not defined in the
         message in the registry.
     @return Output: CMPIStatus structure indicating the function
             return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setProbableCauseDescription) (const CMPIError* er,
            const char* pcd);

    /** @brief Set the RecommendedActions array attribute of a
         CMPIError object.

     `CMPIErrorFT.setRecommendedActions()` sets the value
         of the RecommendedActions array attribute of a CMPIError
         object.

         For a description of the RecommendedActions attribute, see
         the description of the RecommendedActions property in the
         CIM_Error class in the CIM Schema.
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

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setRecommendedActions) (const CMPIError* er,
            const CMPIArray* ra);

    /** @brief Set the ErrorSource attribute of a CMPIError object.

     `CMPIErrorFT.setErrorSource()` sets the value of the ErrorSource
         attribute of a CMPIError object.

     For a description of the ErrorSource attribute, see the
     description of the ErrorSource property in the CIM_Error class
     in the CIM Schema

     @param er Pointer to the CMPIError object for this function.
     @param es string specifying the new non-NULL value for the ErrorSource
         attribute, or is NULL specifying that the attribute will be set to
         NULL. If the error message is defined in a DMTF message registry,
         the string value of the es argument shall be the content of the
         ERROR_SOURCE element defined for the message in the registry.
     @return CMPIStatus structure indicating the function return status
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setErrorSource) (const CMPIError* er, const char* es);

    /** @brief Set the `ErrorSourceFormat` attribute of a
         CMPIError object.

     `CMPIErrorFT.setErrorSourceFormat()` sets the source format of
     the error object. For a description of the ErrorSourceFormat
     attribute, see the description of the ErrorSourceFormat
     property in the CIM_Error class in the CIM Schema.
     @param er Pointer to the CMPIError object for this function.
     @param esf CMPIErrorSrcFormat enumeration value specifying the new value
         for the ErrorSourceFormat attribute. If the error message is defined
         in a DMTF message registry, the string value of the esf argument shall
         be the content of the ERROR_SOURCE_FORMAT element defined for the
         message in the registry
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setErrorSourceFormat) (const CMPIError* er,
            const CMPIErrorSrcFormat esf);

    /** @brief Set the `OtherErrorSourceFormat` attribute of a
     CMPIError object

     `CMPIErrorFT.setOtherErrorSourceFormat()` specifies a string
     defining "Other" values for `ErrorSourceFormat`
     @param er Pointer to the CMPIError object for this function.
     @param oef Pointer to a string specifying the new non-NULL value for
         the `OtherErrorSourceFormat` attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is
         defined in a DMTF message registry, the string value of the
         `oef` argument shall be the content of the
         OTHER_ERROR_SOURCE_FORMAT element defined for the message in the
         registry.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setOtherErrorSourceFormat) (const CMPIError* er,
            const char* oef);

    /** @brief Set the `CIMStatusCodeDescription` attribute of
       a CMPIError object

     `CMPIErrorFT.setCIMStatusCodeDescription()` sets the
         description of the status code. For a description of the
         `CIMStatusCodeDescription` attribute, see the description of the
         `CIMStatusCodeDescription` property in the `CIM_Error`
         class in the CIM Schema.
     @param er Pointer to the CMPIError object for this function.
     @param scd A Pointer to a string specifying the new non-NULL value
         for the `CIMStatusCodeDescription` attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is defined
         in a DMTF message registry, note that the string value of the
         `scd` argument is not defined in the message in the registry.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. (Deprecated)
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setCIMStatusCodeDescription) (const CMPIError* er,
            const char* scd);

    /** @brief Set the `MessageArguments` array attribute of
           a CMPIError object.

     `CMPIErrorFT.setMessageArguments()` sets an array of strings
         for the dynamic content of the message. For a
         description of the `MessageArguments` attribute, see the
         description of the `MessageArguments` property in the
         `CIM_Error` class in the CIM Schema.
     @param er Pointer to the CMPIError object for this function.
     @param values CMPIArray object specifying the new array value
         for the `MessageArguments` array attribute. The CMPIArray
         object contains CMPIString objects or NULL values as array
         elements. The values argument may be NULL, specifying that the
         `MessageArguments` array attribute will be set to NULL. If the
         error message is defined in a DMTF message registry, the values
         argument shall reflect the values defined in the DYNAMIC_ELEMENT
         elements defined for the message in the registry, in the order
         defined there.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. It will not be
             returned because the Extended Errors capability will be
             available. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
        @li `CMPI_RC_ERR_FAILED` - A generic error occurred.

     @version In CMPI 2.1 support for this function was made a requirement.
     */
    CMPIStatus (*setMessageArguments) (const CMPIError* er,
            const CMPIArray* values);

};

#endif /*CMPI_VER_200*/

/**
 * @}
 * @addtogroup edt-instance
 * @{
 */

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
 * @brief Function table of @ref _CMPIInstance
 *     "CMPIInstance encapsulated data type object".
 */
struct _CMPIInstanceFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIInstance object.

     `CMPIInstanceFT.release()` releases a CMPIInstance object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).
     @param inst Pointer to CMPIInstance to be releases.
     @return A CMPIStatus structure indicating the function return status
         will be returned.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
     */
    CMPIStatus (*release) (CMPIInstance* inst);

    /** @brief Create an independent copy of a CMPIInstance object.

     `CMPIInstanceFT.clone()` creates an independent copy of this
     Instance object. The resulting
     object must be released explicitly.
     @param inst Pointer to the CMPIInstance to be cloned.
     @param[out] rc Service return status (suppressed when NULL).
     @return If successful, a pointer to the copied CMPIInstance object
     will be returned.
     The returned CMPIInstance object shall be explicitly released by the
     MI using @ref _CMPIInstanceFT::release "CMPIInstanceFT.release()".
     If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
     */
    CMPIInstance* (*clone) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief Get a property in a CMPIInstance object by
               name.

     `CMPIInstanceFT.getProperty()` gets a named property value from
     an instance.
     @param inst Instance this pointer.
     @param name Points to a string containing the property name.
     @param rc Output: if not NULL, points to a CMPIStatus structure
     that upon return is updated with the function return status.
     @return If successful, a CMPIData structure containing the specified
     property will be returned.

     If not successful, CMPIData.state will have the CMPI_badValue flag
     set to true.
     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
    */
    CMPIData (*getProperty) (const CMPIInstance* inst, const char* name,
            CMPIStatus* rc);

    /** @brief Get a property in a CMPIInstance object by index.

     `CMPIInstanceFT.getPropertyAt()` gets a property at `index`
         in a CMPIInstance object .
     @param inst Pointer to the instance.
     @param index Zero-based index number of the property in the internal
         data array.
     @param[out] name If not NULL, points to a CMPIString pointer
     that upon success is updated to point to a CMPIString object
     containing the property name. The returned CMPIString object
     shall not be explicitly released by the MI, because it may be an internal
     object of the CMPIString object which will be released
     along with that object, or a new object created by the MB which will be
     released automatically by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure
     updated with the function return status.
     @return If successful, a CMPIData structure containing the
     specified property.
     If not successful, CMPIData state will have the `CMPI_badValue`
        is flag set to true.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
     */
    CMPIData (*getPropertyAt)
    (const CMPIInstance* inst, CMPICount index, CMPIString** name,
            CMPIStatus* rc);

    /** @brief Get the number of properties in a CMPIInstance  object.

     `CMPIInstanceFT.getPropertyCount()` gets the number of properties
     contained a CMPIInstance.
     @param inst Pointer to the CMPIInstance object for this
                 function.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         updated with the function return status.
     @return If successful, a CMPICount value indicating the number
     of properties in the instance. If not successful, 0 returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
     */
    CMPICount (*getPropertyCount) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief Set a property value in a CMPIInstance
               object by name.

     `CMPIInstanceFT.setProperty()` adds or replace the named Property in
         the instance defined by
         `inst`. If the property is a key property, the function may
         or may not in addition add or update the key binding in the object
         path of the instance. In order for MIs not to be dependent on this
         behavior, MIs should set key property values in instances and key
         binding values in object paths separately. Key binding values can
         be set during @ref _CMPIBrokerEncFT::newInstance
         "CMPIBrokerEncFT.newInstance()" and by using
         @ref _CMPIInstanceFT::setObjectPath "CMPIInstanceFT.setObjectPath()".
         The MI shall specify
         consistent values for key bindings and key properties.
     @param inst pointer to the CMPIInstance.
     @param name Pointer to a string containing the property name.
     @param value CMPIValue structure containing the non-NULL
         value to be assigned to the property, or NULL to specify that
         NULL is to be assigned.
     @param type CMPIType value specifying the type of the value to
        be assigned to the property. All types of CIM values are supported.

        If the value of the `type argument` is `CMPI_chars` or
        `CMPI_charsA`, the C-language string to which the chars member
        of the value argument points is copied by this function and the
        original string memory may be freed by the MI right after
        this function returns.
     @return CMPIStatus structure indicating the function
         return status.

     The function return status indicates one of the following @ref CMPIrc
     codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_TYPE_MISMATCH` - `type` does not correspond
             to the class-defined type.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - `name` is not a valid
             property name.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
     */
    CMPIStatus (*setProperty) (const CMPIInstance* inst, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief Get a CMPIObjectPath object from a CMPIInstance object.

     `CMPIInstanceFT.getObjectPath()` generates a CMPIObjectPath object from
         the namespace, class name, and key properties of a CMPIInstance
         object.
     @param inst Pointer to the CMPIInstance.
     @param[out] rc If not NULL, points to a CMPIStatus structure
        that upon return has been updated with the function return status.
     @return If successful, a pointer to a CMPIObjectPath object
        representing the instance path of the CMPIInstance.
        The returned CMPIObjectPath object shall not be explicitly
        released by the MI, because it may be an internal object of the
        CMPIInstance object which will be released along with that object,
        or a new object created by the MB which will be released automatically
        by the MB.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
     */
    CMPIObjectPath* (*getObjectPath) (const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief Attach a property filter to a CMPIInstance
               object.

     `CMPIInstanceFT.setPropertyFilter()` attaches a property filter to a
     CMPIInstance object, replacing any previous property filter settings for
     this object.
     By calling this function, the MI delegates property list filtering
     to the MB for this CMPIInstance object, for all of its properties
     including those that had already been set before the call to
     `setPropertyFilter()`.

     Filtering directs CMPI to ignore any setProperty operations for this
     instance for any properties not in this list.

     Support for this function is optional. Availability of this support is
     indicated by the flag CMPI_MB_PropertyFiltering in
     CMPIBrokerFT.brokerCapabilities

     @param inst Pointer to the instance.
     @param propertyList If not NULL, the members of the array define one
     or more Property names to be accepted by setProperty operations. A NULL
     value effectively means that all properties will be accepted.
     A pointer to an empty array means that no properties will be accepted.
     @param keys Deprecated, ignored by MB, maintained here for compatibility.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following
        @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `keyList` argument is missing.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle is invalid.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.

     */
    CMPIStatus (*setPropertyFilter) (const CMPIInstance* inst,
            const char** propertyList, const char** keys);

    /** @brief Set the instance path component of a CMPIInstance object.

     `CMPIInstanceFT.setObjectPath()` sets the CMPIObjectPath component
         in an instance.

     The function may or may not in addition update the key property
     values in the instance to the values of the key bindings in the object
     path. In order for MIs not to be dependent on this behavior, MIs should
     set key property values in instances and key binding values in
     object paths separately. Property values can be set by using
     @ref _CMPIInstanceFT::setProperty "CMPIInstanceFT.setProperty()" or
     @ref _CMPIInstanceFT::setPropertyWithOrigin
     "CMPIInstanceFT.setPropertyWithOrigin()". The MI shall specify
     consistent values for key bindings and key properties.

     @param inst Pointer to the CMPIInstance object.
     @param op Pointer to CMPIObjectPath structure. This objectpath
     shall contain a non-NULL namespace, non-NULL classname, as well as all
     keys for the specified instance. The object path may specify a non-NULL
     host for the instance (this is used for instances returned by
     cross-host associations).

     @return  CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `inst` handle or
            `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - Object path components specified
             in `op` are invalid.

     @todo using gt and lt around references here
     */
    CMPIStatus (*setObjectPath) (const CMPIInstance* inst,
            const CMPIObjectPath* op);

#ifdef CMPI_VER_200

    /** @brief Add or replace a property value in a CMPIInstance
               object by name.

     `CMPIInstanceFT.setPropertyWithOrigin()` adds or replaces a Property value
         and origin in a CMPIInstance.

     If the property is a key property, the function may or may not in addition
     add or update the key binding in the object path of the instance. In
     order for MIs not to be dependent on this behavior, MIs should set
     key property values in instances and key binding values in object
     paths separately. Key binding values can be set during
     @ref _CMPIBrokerEncFT::newInstance "CMPIBrokerEncFT.newInstance()" and by
     using
     @ref _CMPIInstanceFT::setObjectPath "CMPIInstanceFT.setObjectPath()".
     The MI shall specify consistent
     values for key bindings and key properties.
     @param inst Pointer to the CMPIInstance object.
     @param name CMPIString containing the property name.
     @param value Pointer to to a CMPIValue structure containing the value
     to be assigned to the property.
     @param type CMPIType structure defining the type of the value.
     @param origin the name of the class in which this property was
     originally defined. If NULL, then no origin is attached to  the
     property.
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_TYPE_MISMATCH` - `type` does not
            correspond to class-defined type.
        @li `CMPI_RC_ERR_INVALID_HANDLE` -  The `inst` handle
            is invalid.
     @version This function added in CMPI 2.0.
     */
    CMPIStatus (*setPropertyWithOrigin) (const CMPIInstance* inst,
            const char* name, const CMPIValue* value, const CMPIType type,
            const char* origin);

#endif /*CMPI_VER_200*/

};

/**
 * @}
 * @addtogroup edt-objectpath
 * @{
 */

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
 * @brief Function table of @ref _CMPIObjectPath
 *     "CMPIObjectPath encapsulated data type object".
 */
struct _CMPIObjectPathFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIObjectPath object.

     `CMPIObjectPathFT.release()` releases a CMPIObjectPath object.

     The CMPIObjectPath object will not be used any further and
     may be freed by CMPI run time system.
     @param op Pointer to CMPIObjectPath.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
         codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIStatus (*release) (CMPIObjectPath* op);

    /** @brief Create an independent copy of a CMPIObjectPath object.

     `CMPIObjectPathFT.clone()` creates an independent copy of this
     CMPIObjectPath object. The resulting
     object must be released explicitly.
     @param op Pointer to CMPIObjectPath to be cloned.
     @param rc Output: Service return status (suppressed when NULL).
     @return CMPIStatus structure indicating the function return
         status.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.

     */
    CMPIObjectPath* (*clone) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Add the namespace component to a `CIMObjectPath`
           object.

     `CMPIObjectPathFT.setNameSpace()` sets or replaces the namespace component
         in the CMPIObjectPath object defined by `op`.
     @param op Pointer to the CMPIObjectPath object.
     @param ns CMPI String containing the namespace to add.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIStatus (*setNameSpace) (const CMPIObjectPath* op, const char* ns);

    /** @brief Get the namespace component from a CMPIObjectPath.
           object.

     `CMPIObjectPathFT.getNameSpace()` gets the namespace component from a
         CMPIObjectPath object.
     @param op Pointer to the CMPIObjectPath object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to a CMPIString object
         containing the namespace component of the object path will
         be returned. The returned CMPIString object shall not be
         explicitly released by the MI, because it may be an
         internal object of the CMPIObjectPath object which will be
         released along with that object, or a new object created by
         the MB which will be released automatically by the MB.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
    */
    CMPIString* (*getNameSpace) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set the host name component in a CMPIObjectPath object.

     `CMPIObjectPathFT.setHostname()` sets or replaces the host name component
     in `op` a CMPIObjectPath object with argument `hn`.
     @param op Pointer to the CMPIObjectPath.
     @param hn Pointer to a CMPIString containing the host name.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIStatus (*setHostname) (const CMPIObjectPath* op, const char* hn);

    /** @brief Get the host name component  in a CMPIObjectPath object.

     `CMPIObjectPathFT.getHostname()` gets the host name component from a
         CMPIObjectPath object.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object
     containing the host name component of the object path.
     The returned CMPIString object shall not be explicitly released
     by the MI, because it may be an internal object of the
     CMPIObjectPath object which will be released along with that
     object, or a new object created by the MB which will be
     released automatically by the MB.

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIString* (*getHostname) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set class name component in a CMPIObjectPath object.

     Set/replace the class name component in the CMPIObjectPath object.
     @param op Pointer to CMPIObjectPath.
     @param cn specifies the new class name.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIStatus (*setClassName) (const CMPIObjectPath* op, const char* cn);

    /** @brief Get class name component in a `CIMObjectPath`  object.

     `CMPIObjectPathFT.getClassName()` gets the classname component in a
     CMPIObjectPath object.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object
        containing the class name component of the object path.
        The returned CMPIString object shall not be explicitly released
        by the MI, because it may be an internal object of the
        CMPIObjectPath object which will be released along with
        that object, or a new object created by the MB which will be
        released automatically by the MB

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPIString* (*getClassName) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Add or replace a key binding in a CMPIObjectPath object.

    `CMPIObjectPathFT.addKey()` adds or replaces a key binding in a
    CMPIObjectPath object.
    @param op Pointer to CMPIObjectPath.
    @param name Pointer to string containing key name.
    @param value CMPIValue containing the value to be assigned to the
        key binding Key binding values must NOT be NULL.
    @param type Value type to be assigned to the key binding. All types of CIM
        values are valid for keys are supported. If the value of the type
        argument is CMPI_chars or CMPI_charsA, the C-language string
        to which the chars member of the value argument points is
        copied by this function and the original string memory
        may be freed by the MI right after this function returns
    @return CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `key` or
             `value` argument is invalid.
    */
    CMPIStatus (*addKey) (const CMPIObjectPath* op, const char* name,
            const CMPIValue* value, const CMPIType type);

    /** @brief Get a key binding in a @ref _CMPIObjectPath "CMPIObjectPath"
          object by name.

     `CMPIObjectPathFT.getKey()` gets a key binding in a
     @ref _CMPIObjectPath "CMPIObjectPath" object by name.

     @param op Points to the @ref _CMPIObjectPath "CMPIObjectPath" object for
         this function.
     @param name Name of the key binding.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return A CMPIData structure.

     If successful, the returned CMPIData structure contains the value of the
     key binding.
     
     The MB will attempt to set the type in the returned CMPIData structure
     to the precise CIM type, if available. Versions of the CIM-XML protocol
     before @ref ref-dmtf-dsp0200 "DSP0200" Version 1.4 did not mandate the
     presence of the precise CIM type. In those versions, the precise CIM type
     was only recommended to be present. If the precise CIM type is not
     available to the MB, it will use the following more general types in the
     returned CMPIData structure:
     <pre>
         #define CMPI_keyInteger   (CMPI_sint64)
         #define CMPI_keyString    (CMPI_string)
         #define CMPI_keyBoolean   (CMPI_boolean)
         #define CMPI_keyRef       (CMPI_ref)
     </pre>
     
     In addition, the CMPI_keyValue flag will be set in CMPIData.state to
     indicate that the value is a key binding.
    
     If not successful, CMPIData.state will have the CMPI_badValue flag set to
     true.
    
     The function return status indicates one of the following
     @ref CMPIrc codes:
    
       @li `CMPI_RC_OK` - Function successful.
       @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Key not found.
       @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is
       invalid.
    
     @todo TBD: Review and agree upon way the CMPIObjectPathFT.getKey()
         function is documented, as a template for all other functions.<br/>
         Specifically:
         - Source formatting:
           - With vertical `*` line at the left.
           - 4 spaces of indentation if doxygen commands exceed the right
             boundary.
           - Prefer markdown over HTML tags, e.g. for return code lists.
         - Text is copied from spec but argument names are not repeated.
         - No repetition of brief description in long description.
         - Return statement just mentions datatype and description
           text covers "if successful ...".
         - Explicit linking where it does not work automatically (possibly the
           alternative can be used to move typedef into struct definition
           statement.
         - Dash between CMPIrc code name and description.
    */
    CMPIData (*getKey) (const CMPIObjectPath* op, const char* name,
            CMPIStatus* rc);

    /** @brief Get a key binding in a CMPIObjectPath object by
               index.

     `CMPIObjectPathFT.getKeyAt()` gets a key binding in a
     @ref _CMPIObjectPath "CMPIObjectPath" object by index.

    @param op Points to the CMPIObjectPath object for this function.
    @param index Zero-based position of the key binding within the internal data
        array.
    @param name Output: Points to a CMPIString pointer that upon success
        will have been updated to point to a CMPIString object specifying the
        name of the key binding. That CMPIString object shall not be explicitly
        released by the MI, because it may be an internal object of the
        CMPIObjectPath object which will be released along with that object, or
        a new object created by the MB which will be released automatically by
        the MB.
    @param rc Output: If not NULL, points to a CMPIStatus structure that upon
        return will have been updated with the function return status.
    @return A CMPIData structure.

    If successful, the returned CMPIData structure will contain the value of the
    key binding.

    The MB will attempt to set the type in the returned CMPIData structure
    to the precise CIM type, if available. Versions of the CIM-XML protocol
    before @ref ref-dmtf-dsp0200 "DSP0200" Version 1.4 did not mandate the
    presence of the precise
    CIM type. In those versions, the precise CIM type was only recommended
    to be present. If the precise CIM type is not available to the MB, it
    will use the following more general types in the returned CMPIData
    structure:
    <pre>
        #define CMPI_keyInteger   (CMPI_sint64)
        #define CMPI_keyString    (CMPI_string)
        #define CMPI_keyBoolean   (CMPI_boolean)
        #define CMPI_keyRef       (CMPI_ref)
    </pre>

    @todo TBD: The inline code with the defines creates doxygen warnings
        "explicit link request to 'define' could not be resolved".
        How to resolve this?

    In addition, the CMPI_keyValue flag will be set in CMPIData.state
    to indicate that the value is a key binding.

    If not successful, CMPIData.state will have the CMPI_badValue flag set to
    true.

    The function return status indicates one of the following
    @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Key not found.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
    */
    CMPIData (*getKeyAt) (const CMPIObjectPath* op, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get the number of key bindings in a CMPIObjectPath
               object.

     `CMPIObjectPathFT.getKeyCount()` gets the number of key bindings contained
         in this CMPIObjectPath.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, a CMPICount value indicating the number of
         key bindings will be returned. If the CMPIObjectPath object
         does not have a key component, the function will succeed and
         return 0.

         If not successful, 0 will be returned.
     The function return status indicates one of the following
        @ref CMPIrc codes:
         @li `CMPI_RC_OK` - Function successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
     */
    CMPICount (*getKeyCount) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set/replace the namespace and class name components in a
       CMPIObjectPath object from another CMPIObjectPath object

     `CMPIObjectPathFT.setNameSpaceFromObjectPath()` sets or replace namespace
         and classname components in CMPIObjectPath
         `op` from CMPIObjectPath `src`.
     @param op Pointer to CMPIObjectPath.
     @param src a CMPIObjectPath object used as the source for the new
         namespace and class name components.
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` -The `src` argument is invalid.
     */
    CMPIStatus (*setNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    /** @brief Set host name, namespace, and class name components
       in a CMPIObjectPath object from another CMPIObjectPath
       object.

     `CMPIObjectPathFT.setHostAndNameSpaceFromObjectPath()` sets/replaces
     hostname, namespace and classname components in the
       CMPIObjectPath `op` from the CMPIObjectPath `src`.
     @param op Pointer to CMPIObjectPath object to be modified.

     @param src CMPIObjectPath object used as the source for the new host name,
         namespace, and class name components.
     @return CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `src` argument is invalid.
     */
    CMPIStatus (*setHostAndNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    /** @brief Get a class qualifier.

     `CMPIObjectPathFT.getClassQualifier()` gets a class qualifier in the class
         identified by the CMPIObjectPath `op` argument.

         This function shall be supported by the MB if the Basic Qualifier
         capability is available; otherwise, it shall not be supported.
     @param op Pointer CMPIObjectPath object that references the class and that
         shall contain the namespace and class components. The hostname and
         key components, if present, will be ignored by the MB.
     @param qName Qualifier name.
     @param[out] rc If not NULL, points to a CMPIStatus structure that upon
         return is updated with the function return status.
     @return If successful, returns a CMPIData structure containing the
         specified qualifier. If not successful, CMPIData.state
         `CMPI_badValue` flag set to true.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace implied by
             `op` is invalid.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
             `op` argument does not exist.
        @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in the
             `qName` argument is invalid for classes.
        @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     */
    CMPIData (*getClassQualifier) (const CMPIObjectPath* op,
            const char* qName, CMPIStatus* rc);

    /** @brief Get a property qualifier.

     `CMPIObjectPathFT.getPropertyQualifier()` function gets a property
         qualifier in the class identified by `op`>.

     This function shall be supported by the MB if theBasic Qualifier
         capability is available; otherwise, it shall not be supported.

     @param op Pointer to CMPIObjectPath object that references the
         class and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by the MB.
     @param pName Property name.
     @param qName Pointer to a string specifying the qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set
         to true.

     The function return status indicates one of the following @ref CMPIrc
         codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace implied by
             `op` is invalid.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
             `op` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property (or reference)
             specified in the pName argument is not exposed by the class
              specified in the `op` argument.
        @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in the
             `qNamet` argumen is invalid for classes.
        @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @todo in this set of functions we left the name op on the CMPIObjectPath
     whereas the spec changed that to classpath, etc. Should we modify???
     */
    CMPIData (*getPropertyQualifier) (const CMPIObjectPath* op,
            const char* pName, const char* qName, CMPIStatus* rc);

    /** @brief Get a method qualifier.

     `CMPIObjectPathFT.getMethodQualifier()` gets method qualifier value.

     This function shall be supported by the MB if the Basic Qualifier
         capability is available (see Subclause 7.1); otherwise, it shall
         not be supported. Availability of the Basic Qualifier capability
         can be queried by an MI using the CMPI_MB_BasicQualifierSupport
         test mask on the brokerCapabilities member of the CMPIBrokerFT
          structure.
     @param op Pointer to a CMPIObjectPath object that references the class
         and that shall contain the namespace and class components. The
          hostname and key components, if present, will be ignored by the MB.
     @param mName Method name.
     @param qName Qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a CMPIData structure containing the specified
         qualifier will be returned.
         If not successful, CMPIData.state will have the CMPI_badValue
          flag set to true.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace implied by
             `op` is invalid.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
             `op` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property (or reference)
             specified in the pName argument is not exposed by the class
              specified in the `op` argument.
        @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in the
             `qName` argument is invalid for classes.
        @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     */
    CMPIData (*getMethodQualifier) (const CMPIObjectPath* op,
            const char* methodName, const char* qName, CMPIStatus* rc);

    /** @brief Get a parameter qualifier.

     `CMPIObjectPathFT.getParameterQualifier()` gets a parameter qualifier in
        the class identified by this object path.

     This function shall be supported by the MB if the Basic Qualifier
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Basic Qualifier capability can be
         queried by an MI using the CMPI_MB_BasicQualifierSupport test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.

     @param op Pointer points to a CMPIObjectPath object that references the
          class and that shall contain the namespace and class components.
          The hostname and key components, if present, will be ignored by
          the MB.
     @param mName Pointer to a string specifying the method name.
     @param pName Pointer to a string specifying the parameter name.
     @param qName Pointer to a string specifying the qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set
      to true.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `op` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace implied by
             `op` is invalid.
        @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in the
             `op` argument does not exist.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The method
             specified in the mName argument is not exposed by the class
             specified in the `op` argument, or it does not have a
             parameter with the name specified in the pName argument.
        @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in the
             `qName` argument is invalid for classes.
        @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @todo used invalid rather than does not exist for invalid_namespace
     */
    CMPIData (*getParameterQualifier) (const CMPIObjectPath* op,
            const char* mName, const char* pName, const char* qName,
            CMPIStatus* rc);

    /** @brief Convert a CMPIObjectPath object into a string format.

     `CMPIObjectPathFT.toString()` generates a well formed
         implementation-specific string representation of this CMPIObjectPath.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object containing
         the string representation of the object path.

     The returned CMPIString object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPIObjectPath
     object which will be released along with that object, or a
     new object created by the MB which will be released automatically
     by the MB

     If not successful, returns NULL.
     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ctx` handle is invalid.
     */
    CMPIString* (*toString) (const CMPIObjectPath* op, CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup qualifier-services
 * @{
 *   The qualifier services are the following member functions from the
 *   @ref _CMPIObjectPathFT "CMPIObjectPath encapsulated data type object":
 *     @li @ref _CMPIObjectPathFT::getClassQualifier
 *         "CMPIObjectPathFT.getClassQualifier()"
 *     @li @ref _CMPIObjectPathFT::getPropertyQualifier
 *         "CMPIObjectPathFT.getPropertyQualifier()"
 *     @li @ref _CMPIObjectPathFT::getMethodQualifier
 *         "CMPIObjectPathFT.getMethodQualifier()"
 *     @li @ref _CMPIObjectPathFT::getParameterQualifier
 *         "CMPIObjectPathFT.getParameterQualifier()"
 *   @}
 *   @addtogroup edt-selectexp
 *   @{
 */

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
 * @brief Function table of @ref _CMPISelectExp
 *     "CMPISelectExp encapsulated data type object".
 */
struct _CMPISelectExpFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPISelectExp object.

     `CMPISelectExpFT.release()` releases a CMPISelectExp object. This
         indicates to the MB that the object (including any objects it
         contains) will no longer be used by the MI. The MB may free (=reclaim)
         the memory associated with the object during the call to this
         function, or later during some garbage collection cycle
         (see Subclause 4.1.7).
     @param se points to the CMPISelectExp object to be released. That object
          shall have been created using @ref _CMPISelectExpFT::clone
          "CMPISelectExpFT.clone()".
     @return CMPIStatus structure indicating the function return status.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
    */
    CMPIStatus (*release) (CMPISelectExp* se);

    /** @brief Create an independent copy of a CMPISelectExp object.

     `CMPISelectExpFT.clone()` creates an independent copy of this
     CMPISelectExp object. The resulting
         object must be released explicitly.
     @param se Pointer to CMPISelectExp to clone.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to the copied CMPISelectExp object
          will be returned.
          The returned CMPISelectExp object shall be explicitly released
          by the MI using @ref _CMPISelectExpFT::release
          "CMPISelectExpFT.release()".
          If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
     */
    CMPISelectExp* (*clone) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Test whether an instance matches the select
       expression in a CMPISelectExp object.

     `CMPISelectExpFT.evaluate()` evaluates the instance &ltinst& using this
         select expression.

     This function shall be supported by the MB if the Query Normalization
        capability is available); otherwise, it shall not be supported.
        Availability of the Query Normalization capability can be queried by
        an MI using the CMPI_MB_QueryNormalization test mask on the
        brokerCapabilities member of the CMPIBrokerFT structure.
     @param se Pointer to CMPISelectExp.
     @param inst Instance to be evaluated.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returnsCMPIBoolean value indicating the test result
         as follows: True indicates that the instance matches the select
         expression; False indicates that this is not the case.

         If not successful, False will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `inst` argument is invalid.
    */
    CMPIBoolean (*evaluate) (const CMPISelectExp* se, const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object
               as a string.

     `CMPISelectExpFT.getString()` returns the select expression in
     string format.

     This function shall be supported by the MB if the Query Normalization
        capability is available; otherwise, it shall not be supported.
        Availability of the Query Normalization capability can be queried by
        an MI using the CMPI_MB_QueryNormalization test mask on the
        brokerCapabilities member of the CMPIBrokerFT structure.
     @param se Pointer to a CMPISelectExp object for this function,
         containing the select expression.
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

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
     */
    CMPIString* (*getString) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object
       as a disjunction of conjunctions.

     `CMPISelectExpFT.getDOC()` gets the select expression as a
         disjunction of conjunctions. This function transforms the WHERE
         clause of the select expression into a canonical disjunction of
         onjunctions (DOC) form (OR?ing of AND?ed comparison expressions).
         This enables handling of the expression in the WHERE clause more
         easily than using a tree form.

     This function shall be supported by the MB if the Query Normalization
     capability is available.

     @param se Pointer to a CMPISelectExp object for this function,
         containing the select expression.
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

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. If the Query
             Normalization capability is not available, this function cannot
             be called by the MI because no instance of its encapsulated data
             type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
     */
    CMPISelectCond* (*getDOC) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object as
       a conjunction of disjunctions.

     `CMPISelectExpFT.getCOD()` returns the select expression as
     conjunction of disjunctions.

     This function shall be supported by the MB if the Query Normalization
     capability is available.
     @param se Pointer to a CMPISelectExp object for this function,
         containing the select expression.
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

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
             In CMPI 2.1, this return code has been deprecated. If the Query
             Normalization capability is not available, this function cannot
             be called by the MI because no instance of its encapsulated data
             type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.

     */
    CMPISelectCond* (*getCOD) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Test whether the properties returned by an accessor
           function match the select expression in a CMPISelectExp
           object.

     `CMPISelectExpFT.evaluateUsingAccessor()` tests whether the properties
     returned by an accessor
     function match the select expression in a CMPISelectExp object.
     This function is a variation of @ref _CMPISelectExpFT::evaluate
     "CMPISelectExpFT.evaluate()". It enables
     evaluation without the need to create a CMPIInstance object

     This function shall be supported by the MB if the Query Normalization
     capability is available.
     @param se Pointer to a CMPISelectExp object for this function,
         containing the select expression.
     @param accessor Address of data accessor routine.
     @param parm Data accessor routine parameter.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, returns a CMPIBoolean value indicating the test
     result will be returned, as follows: True indicates that the
     properties returned by the accessor function match the select
     expression; False indicates that this is not the case.

     If not successful, False will be returned

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `se` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `accessorFnc` handle is 
            invalid.
     */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPISelectExp* se,
            CMPIAccessor* accessor, void* parm, CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup edt-selectcond
 * @{
 */

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
 * @brief Function table of @ref _CMPISelectCond
 *     "CMPISelectCond encapsulated data type object".
 */
struct _CMPISelectCondFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPISelectCond object.

     `CMPISelectCondFT.release()` releases a CMPISelectCond object. This
         indicates to the MB that the object (including any objects it contains)
         will no longer be used by the MI. The MB may free (=reclaim) the
         memory associated with the object during the call to this function,
         or later during some garbage collection cycle (see Subclause 4.1.7).

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.

     @param sc points to the CMPISelectCond object to be released. That object
         shall have been created using @ref _CMPISelectCondFT::clone
         "CMPISelectCondFT.clone()".
     @return CMPIStatus structure indicating the function return status .
     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
            In CMPI 2.1, this return code has been deprecated. If the Query
            Normalization capability is not available, this function cannot
            be called by the MI because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `sc` handle is invalid.
    @todo add comment about condition for use. It is in only some of these
        descriptions.
    */
    CMPIStatus (*release) (CMPISelectCond* sc);

    /** @brief Create an independent copy of a CMPISelectCond object.

     `CMPISelectExpFT.clone()` creates an independent copy of this SelectCond
         object. The resulting object must be released explicitly.

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc SelectCond this pointer.
     @param[out] rc If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful, returns a pointer to the copied CMPISelectExp
        object.

        The returned CMPISelectExp object shall be explicitly released by
         the MI using @ref _CMPISelectExpFT::release
         "CMPISelectExpFT.release()".

        If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
            In CMPI 2.1, this return code has been deprecated. If the Query
            Normalization capability is not available, this function cannot
            be called by the MI because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `sc` handle is invalid.
     */
    CMPISelectCond* (*clone) (const CMPISelectCond* sc, CMPIStatus* rc);

    /** @brief Get the number and type of subconditions in a
       CMPISelectCond object.

     `CMPISelectCondFT.getCountAndType()` returns the number of subconditions
         that are part of this SelectCond.
     Optionally, the SelectCond type (COD or DOC) will be returned.

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc Pointer to a CMPISelectCond object for this function.
     @param type Output: If not NULL, points to an integer that upon success
         is updated with the subcondition type. A value of 0 indicates a
         DOC type, and a value of 1 indicates a COD type. If type is NULL,
         no type information is returned.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful, returns a CMPICount value indicating the number of
         subconditions.

     If not successful, returns 0.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
            In CMPI 2.1, this return code has been deprecated. If the Query
            Normalization capability is not available, this function cannot
            be called by the MI because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `sc` handle is invalid.
     */
    CMPICount (*getCountAndType) (const CMPISelectCond* sc, int* type,
            CMPIStatus* rc);

    /** @brief Get a subcondition in a CMPISelectCond object by index.

     `CMPISelectCondFT.getSubCondAt()` gets the subcondition in a
         CMPISelectCond object, by its index in the internal data array

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc Pointer to a CMPISelectCond object for this function.
     @param index Specifies the zero-based position of the subcondition in
         the internal data array.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful, returns a pointer to the specified CMPISubCond
     object will be returned.

     The returned CMPISubCond object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPISelectCond
     object which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB.

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
            In CMPI 2.1, this return code has been deprecated. If the Query
            Normalization capability is not available, this function cannot
            be called by the MI because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - `index` value out of bounds.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `sc` handle is invalid.
     */
    CMPISubCond* (*getSubCondAt) (const CMPISelectCond* sc, CMPICount index,
            CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup edt-subcond
 * @{
 */

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
 * @brief Function table of @ref _CMPISubCond
 *     "CMPISubCond encapsulated data type object".
 */
struct _CMPISubCondFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPISubCond object.

     `CMPISubCondFT.release()` releases argument `sc` a CMPISubCond
         object.

         This indicates to the MB that the object (including any
         objects it contains) will no longer be used by the MI. The
         MB may free (=reclaim) the memory associated with the
         object during the call to this function, or later during
         some garbage collection cycle (see Subclause 4.1.7).

         This function shall be supported by the MB if the Query
         Normalization capability is available (see Subclause 7.1);
         otherwise, it shall not be supported. Availability of the
         Query Normalization capability can be queried by an MI
         using the CMPI_MB_QueryNormalization test mask on the
         brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc Pointer to the CMPISubCond object to be released.
       That object shall have been created using
       @ref _CMPISubCondFT::clone "CMPISubCondFT.clone()".
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
                by the MB. In CMPI 2.1, this return code has been
                deprecated. If the Query Normalization capability is not
                available, this function cannot be called by the MI
                because no instance of its encapsulated data
                type can exist. <b>(Deprecated)</b>
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `sc` handle.
     */
    CMPIStatus (*release) (CMPISubCond* sc);

    /** @brief Create an independent copy of a CMPISubCond
               object.

     `CMPISubCondFT.clone()` creates an independent copy of a  `sc`
         CMPISubCond object.

         This function shall be supported by the MB if the Query
         Normalization capability is available (see Subclause 7.1);
         otherwise, it shall not be supported. Availability of the
         Query Normalization capability can be queried by an MI
         using the CMPI_MB_QueryNormalization test mask on the
         brokerCapabilities member of the CMPIBrokerFT structure.

     @param sc Pointer to the CMPISubCond object.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful, returns a CMPICount value indicating the number of
         subconditions.

     If not successful, returns 0.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
                by the MB. In CMPI 2.1, this return code has been
                deprecated. If the Query Normalization capability is not
                available, this function cannot be called by the MI
                because no instance of its encapsulated data
                type can exist. <b>(Deprecated)</b>
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `sc` handle.
     */
    CMPISubCond* (*clone) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief Get the number of predicates in a CMPISubCond object.

     `CMPISubCondFT.getCount()` gets the number of predicates in `sc`
     CMPISubCond object.

    This function shall be supported by the MB if the Query Normalization
        capability is available (see Subclause 7.1); otherwise, it shall not
        be supported. Availability of the Query Normalization capability can
        be queried by an MI using the CMPI_MB_QueryNormalization test mask on
        the brokerCapabilities member of the CMPIBrokerFT structure.

     @param sc Pointer to the CMPISubCond object.
     @param rc Output: Service return status (suppressed when NULL).
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful, returns a CMPICount value indicating the number of
         predicates in the CMPISubCond object.

     If not successful, returns 0.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
                by the MB. In CMPI 2.1, this return code has been
                deprecated. If the Query Normalization capability is not
                available, this function cannot be called by the MI
                because no instance of its encapsulated data
                type can exist. <b>(Deprecated)</b>
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `sc` handle.
     */
    CMPICount (*getCount) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief Get a predicate in a CMPISubCond object by index.

     `CMPISubCondFT.getPredicatAt()` gets a predicate in a CMPISubCond
         object, by its index in the internal data array.

     This function shall be supported by the MB if the Query Normalization
         capability is available; otherwise, it shall not be supported.

    This function shall be supported by the MB if the Query Normalization
        capability is available (see Subclause 7.1); otherwise, it shall not
        be supported. Availability of the Query Normalization capability can
        be queried by an MI using the CMPI_MB_QueryNormalization test mask on
        the brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc Pointer to the CMPISubCond object.
     @param index Specifies the zero-based index of the predicate in the
         internal data array.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIPredicate object
         containing the specified predicate.

         The returned CMPIPredicate object shall not be explicitly
         released by the MI, because it may be an internal object of
         the CMPISubCond object which will be released along with that
         object, or a new object created by the MB which will be released
         automatically by the MB.

         If not successful, returns NULL.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
                by the MB. In CMPI 2.1, this return code has been
                deprecated. If the Query Normalization capability is not
                available, this function cannot be called by the MI
                because no instance of its encapsulated data
                type can exist. <b>(Deprecated)</b>
         @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - `index` value out of bounds.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `sc` handle.
     @todo Ordering of the codes is different between this an
           following function. That is in the spec.
     */
    CMPIPredicate* (*getPredicateAt) (const CMPISubCond* sc, CMPICount index,
            CMPIStatus* rc);

    /** @brief Get a predicate in a CMPISubCond object by name.

     `CMPISubCondFT.getPredicate()` gets a predicate in a CMPISubCond
      object, by its `name` argument.

     This function shall be supported by the MB if the Query Normalization
         capability is available; otherwise, it shall not be supported.

    This function shall be supported by the MB if the Query Normalization
        capability is available (see Subclause 7.1); otherwise, it shall not
        be supported. Availability of the Query Normalization capability can
        be queried by an MI using the CMPI_MB_QueryNormalization test mask on
        the brokerCapabilities member of the CMPIBrokerFT structure.
     @param sc Pointer to the CMPISubCond object.
     @param name specifies the predicate name. The name is the left-hand side
         of the predicate.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIPredicate object
     containing the specified predicate.

     The returned CMPIPredicate object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPISubCond
     object which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB.

     If not successful, returns NULL.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
                by the MB. In CMPI 2.1, this return code has been
                deprecated. If the Query Normalization capability is not
                available, this function cannot be called by the MI
                because no instance of its encapsulated data
                type can exist. <b>(Deprecated)</b>
         @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - `index` value out of bounds.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `sc` handle.

     */
     */
    CMPIPredicate* (*getPredicate) (const CMPISubCond* sc, const char* name,
            CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup edt-predicate
 * @{
 */

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
 * @brief Function table of @ref _CMPIPredicate
 *     "CMPIPredicate encapsulated data type object".
 */
struct _CMPIPredicateFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPPredicate object.

     `CMPIPredicateFT.release()` releases a CMPIPredicate object. This
         indicates to the MB that the object (including any objects it contains)
         will no longer be used by the MI. The MB may free (=reclaim) the
         memory associated with the object during the call to this function,
         or later during some garbage collection cycle (see Subclause 4.1.7).

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param pr Pointer to the CMPIPredicate object to be released. That object
         shall have been created using @ref _CMPIPredicateFT::clone
         "CMPIPredicateFT.clone()".
     @return CMPIStatus structure indicating the function return
             status .
     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB. In CMPI 2.1, this return code has been
            deprecated. If the Query Normalization capability is not
            available, this function cannot be called by the MI
            because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `pr` handle is invalid.
        @todo in spec, the handle is refered to as sc, not pr
     */
    CMPIStatus (*release) (CMPIPredicate* pr);

    /** @brief Create an independent copy of a CMPIPredicate object.

     `CMPIPredicateFT.clone()` creates an independent copy of a
     CMPIPredicate object.

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param pr Pointer to the CMPIPredicate object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, a pointer to the copied CMPIPredicate object will
     be returned.
     The returned CMPIPredicate object shall be explicitly released by the
     MI using @ref _CMPIPredicateFT::release "CMPIPredicateFT.release()".

    If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB. In CMPI 2.1, this return code has been
            deprecated. If the Query Normalization capability is not
            available, this function cannot be called by the MI
            because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `pr` handle is invalid.
     @todo in spec, the handle is refered to as sc, not pr

     */
    CMPIPredicate* (*clone) (const CMPIPredicate* pr, CMPIStatus* rc);

    /** @brief Get the predicate components of a CMPIPredicate object.

     `CMPIPredicateFT.getData()` gets the predicate components of a
         CMPIPredicate object.

     The CMPIString objects returned by lhs and rhs shall not be explicitly
     released by the MI, because they may be internal objects of the
     CMPIContext object which will be released along with that object, or new
     objects created by the MB which will be automatically released by the
     MB (see Subclause 4.1.7).

     This function shall be supported by the MB if the Query Normalization
         capability is available (see Subclause 7.1); otherwise, it shall not
         be supported. Availability of the Query Normalization capability can
         be queried by an MI using the CMPI_MB_QueryNormalization test mask
         on the brokerCapabilities member of the CMPIBrokerFT structure.
     @param pr Pointer to the CMPIPredicate object.
     @param[out] type If not NULL, points to a CMPIType structure that upon
         success will have been updated with the data type of the predicate.
     @param[out] prop If not NULL, points to a CMPIPredOp object that upon
         success will have been updated with the predicate operation.
     @param[out] lhs if not NULL, points to a pointer to a CMPIString object
         that upon success will have been updated with the address of a
         CMPIString object representing the left-hand side of the predicate.
     @param[out] rhs , if not NULL, points to a pointer to a CMPIString object
         that upon success will have been updated with the address of a
         CMPIString object representing the right-hand side of the predicate.
     @return If successful, returns pointer to the copied CMPIPredicate object.
    The returned CMPIPredicate object shall be explicitly released by the MI
        using @ref _CMPIPredicateFT::release "CMPIPredicateFT.release()".

    If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB. In CMPI 2.1, this return code has been
            deprecated. If the Query Normalization capability is not
            available, this function cannot be called by the MI
            because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `pr` handle is invalid.
     @todo in spec, the handle is refered to as sc, not pr
     */
    CMPIStatus (*getData) (const CMPIPredicate* pr, CMPIType* type,
            CMPIPredOp* prop, CMPIString** lhs, CMPIString** rhs);

    /** @brief Test whether the properties returned by an accessor
           function match the predicate in a CMPIPredicate object.

     `CMPIPredicateFT.evaluateUsingAccessor()` tests whether the
         properties returned by an accessor function match the predicate in a
         CMPIPredicate object.

     The CMPIString objects returned by lhs and rhs shall not be explicitly
     released by the MI, because they may be internal objects of the
     CMPIContext object which will be released along with that object, or new
     objects created by the MB which will be automatically released by the
     MB (see Subclause 4.1.7).

     @param pr Pointer to the CMPIPredicate object.
     @param accessorFnc Pointer to a property value accessor
     function. The evaluation process will invoke this function to
     request a CMPIData structure for a particular property. The
     signature of the accessor function is: CMPIData
     CMPIAccessor(const char* propertyName, void* parm);
     @param parm Parameter that will be passed to the accessor function and
     can be used for providing context data to the accessor function.
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, a CMPIBoolean value indicating the test result
         will be returned, as follows: True indicates that the properties
         returned by the accessor function match the predicate; False
         indicates that this is not the case.

     If not successful, False will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported
            by the MB. In CMPI 2.1, this return code has been
            deprecated. If the Query Normalization capability is not
            available, this function cannot be called by the MI
            because no instance of its encapsulated data
            type can exist. <b>(Deprecated)</b>
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `pr` handle is invalid.
        @todo in spec, the handle is refered to as sc, not pr
     */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPIPredicate* pr,
            CMPIAccessor* accessorFnc, void* parm, CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup edt-args
 * @{
 */

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
 * @brief Function table of @ref _CMPIArgs
 *     "CMPIArgs encapsulated data type object".
 */
struct _CMPIArgsFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIArgs object.

     `CMPIArgsFT.release()` releases a CMPIArgs object. This indicates to the
      MB that the object (including any objects it contains) will no longer
      be used by the MI. The MB may free (=reclaim) the memory associated
      with the object during the call to this function, or later during some
      garbage collection cycle (see Subclause 4.1.7).
     @param as points to the CMPIArgs object to be released. That object shall
      have been created using @ref _CMPIArgsFT::clone "CMPIArgsFT.clone()".
     @return CMPIStatus structure indicating the function return status.
     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
    */
    CMPIStatus (*release) (CMPIArgs* as);

    /** @brief Create an independent copy of a CMPIRArgs object.

     `CMPIArgsFT.clone()` creates an independent copy of this Args object. The
        resulting object must be released explicitly.
     @param as Pointer to the CMPIArgs object to be copied.
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
          return will have been updated with the function return status
     @return If successful, a pointer to the copied CMPIArgs object
         will be returned.
         The returned CMPIArgs object shall be explicitly released by the MI
         using @ref _CMPIArgsFT::release "CMPIArgsFT.release()".

        If not successful, NULL will be returned

     The function return status indicates one of the following @ref CMPIrc
       codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
     */
    CMPIArgs* (*clone) (const CMPIArgs* as, CMPIStatus* rc);

    /**  @brief Set a method parameter in a CMPIArgs object.

     `CMPIArgsFT.addArg()` adds or replaces a method parameter in a CMPIArgs
     object.
     @param as Pointer to the CMPIArgs object.
     @param name Argument name.
     @param value Pointer to a CMPIValue structure containing the non-NULL
         value to be assigned to the method parameter, or NULL to specify that
         NULL is to be assigned
     @param type type of the method parameter. All types of CIM values are
         supported.
         If the value of the type argument is CMPI_chars or CMPI_charsA, the
         C-language string to which the chars member of the value argument
         points is copied by this function and the original string memory may
         be freed by the MI right after this function returns.
     @return CMPIStatus structure indicating the function return status.
        The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - Data type not valid.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
     */
    CMPIStatus (*addArg) (const CMPIArgs* as, const char* name,
            const CMPIValue* value,
            const CMPIType type);

    /** @brief Get a method parameter in a CMPIArgs object by name.

     `CMPIArgsFT.getArg()` gets a method parameter in a CMPIArgs object,
        by its name.
     @param as Args Pointer to the CMPIArgs object.
     @param name Specifies the name of the method parameter.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a CMPIData structure containing the
     specified method parameter.

     If not successful, CMPIData.state will have the CMPI_badValue flag
        set to true

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Method parameter not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
     */
    CMPIData (*getArg) (const CMPIArgs* as, const char* name, CMPIStatus* rc);

    /** @brief Get a method parameter in a CMPIArgs object by index.

     `CMPIArgsFT.getArgAt()` gets a Argument value defined by its index.
     @param as Pointer to the CMPIArgs object.
     @param index Position in the internal Data array.
     @param name Output: The name output argument, if not NULL, points to a
         CMPIString pointer that upon success will have been updated to point
         to a CMPIString object containing the method parameter name. The
         returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIArgs object
         which will be released along with that object, or a new object
         created by the MB which will be automatically released by the
         MB (see Subclause 4.1.7).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.

    If not successful, CMPIData.state will have the CMPI_badValue flag
    set to true

    The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Method parameter not found.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
     */
    CMPIData (*getArgAt) (const CMPIArgs* as, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get a method parameter in a CMPIArgs object by index.

     `CMPIArgsFT.getArgCount()` gets the number of arguments contained in this
      CMPIArgs object.
     @param as Pointer to the CMPIArgs object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.

    If not successful, CMPIData.state will have the CMPI_badValue flag
    set to true.

    The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `as` handle is invalid.
     */
    CMPICount (*getArgCount) (const CMPIArgs* as, CMPIStatus* rc);
};

/**
 * @}
 * @addtogroup edt-string
 * @{
 */

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
 * @brief Function table of @ref _CMPIString
 *     "CMPIString encapsulated data type object".
 */
struct _CMPIStringFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIString object.

     `CMPIStringFT.release()` releases a CMPIString object. This indicates to
      the MB that the object (including any objects it contains) will no longer
      be used by the MI. The MB may free (=reclaim) the memory associated with
      the object during the call to this function, or later during some
      garbage collection cycle (see Subclause 4.1.7).
     @param st  Pointer to the CMPIString object to be released. That
         object shall have been created using @ref _CMPIStringFT::clone
         "CMPIStringFT.clone()".
     @return A CMPIStatus structure indicating the function return status.
     @return CMPIStatus structure indicating the function return status .
        The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `str` handle is invalid.
     */
    CMPIStatus (*release) (CMPIString* st);

    /** @brief Create an independent copy of this String object.

     `CMPIStringFT.clone()` creates an independent copy of this String object.
     The resulting
     object must be released explicitly.
     @param st Pointer to the CMPIString object to be copied. That
         object shall have been created using @ref _CMPIStringFT::clone
         "CMPIStringFT.clone()".
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, a pointer to the copied CMPIString object will be
         returned.
         The returned CMPIString object shall be explicitly released by the
         MI using @ref _CMPIStringFT::release "CMPIStringFT.release()".

     If not successful, NULL will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `str` handle is invalid.
     */
    CMPIString* (*clone) (const CMPIString* st, CMPIStatus* rc);

    /** @brief Get a pointer to a C-language string representation of a
       CMPIString object.

     `CMPIStringFT.getCharPtr()` gets a pointer to a C char* representation of
     this CMPIString object.
     @param st Pointer to CMPIString object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, returns a pointer to a C-language string
     will be returned.

     The character array of the returned string shall not be explicitly
     released by the MI, because it may point to an internal data area in the
     CMPIString object which will be released along with that object, or it
     may point to a new character array created by the MB which will be
     released automatically by the MB.

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `str` handle is invalid.
     */
    const char* (*getCharPtr) (const CMPIString* st, CMPIStatus* rc);

#ifdef CMPI_VER_210

    /** @brief Create a C-language string that has converted a CMPIString
           object into a specific codepage

     `CMPIStringFT.newCharsCP()` creates a new C-language string
     (see Subclause 5.2.1) that contains the string in a CMPIString
     object, converted into a specific codepage.

     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.

     @param str Pointer to the CMPIString object for this function.
     @param cpid CMPICodePageID specifies the CMPI-specific codepage
         ID for the codepage to convert to. See the CMPI Specification
         section 5.2.2 (CodePage for a list of supported codepages and their
         codepage ID values.
     @param rc If not NULL, points to a CMPIStatus structure that
     upon return has been updated with the function return status.
     @return If successful, returns a new C-language string, in the codepage
     specified in the cpid argument.
     The returned C-language string must be freed by the MI using
     @ref _CMPIBrokerMemFT::freeChars "CMPIBrokerMemFT.freeChars()".

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `str` handle is invalid.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - The `cpid` argument is invalid.
        @li `CMPI_RC_ERR_NOT_IN_CODEPAGE` - The string contains characters that
             are not representable in the specified codepage.

     @version Added in CMPI 2.1.
     */
    char* (*newCharsCP) (const CMPIString* str, const CMPICodepageID cpid,
            CMPIStatus* rc);

#endif /*CMPI_VER_210*/

};

/**
 * @}
 * @addtogroup edt-array
 * @{
 */

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
 * @brief Function table of @ref _CMPIArray
 *     "CMPIArray encapsulated data type object".
 */
struct _CMPIArrayFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIArray object.

     `CMPIArrayFT.release()` releases a CMPIArray object. This indicates
         to the MB that the object (including any objects it contains) will
         no longer be used by the MI. The MB may free (=reclaim) the memory
         associated with the object during the call to this function, or
         later during some garbage collection cycle (see Subclause 4.1.7).
     @param ar Pointer to the CMPIArray object to be released. That object
         shall have been created using @ref _CMPIArrayFT::clone
         "CMPIArrayFT.clone()".
     @return CMPIStatus structure indicating the function return status .
        The function return status indicates one of the following @ref CMPIrc
        codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar`` handle is invalid.
     */
    CMPIStatus (*release) (CMPIArray* ar);

    /** @brief Create an independent copy of a CMPIArray object.

     `CMPIArrayFT.clone()` creates an independent copy of this
     CMPIArray object. The   
     resulting object must be released explicitly.   
     @param ar Pointer to the CMPIArray object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to the copied CMPIArray object will be
     returned.
     The returned CMPIArray object shall be explicitly released by the MI
         using @ref _CMPIArrayFT::release "CMPIArrayFT.release()".
     If not successful, NULL will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar` handle is invalid.
     */
    CMPIArray* (*clone) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief Get the number of array elements in a CMPIArray
               object.

     `CMPIArrayFT.getSize()` gets the number of array
         elements in a CMPIArray object.
     @param ar Pointer to the CMPIArray object for this function.
     @param[out] rc If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful, a CMPICount value indicating the number of
         array elements will be returned.

         If not successful, 0 will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar` handle is invalid.
     */
    CMPICount (*getSize) (const CMPIArray* ar, CMPIStatus* rc);

    /** Get the type of the array elements in a CMPIArray object.

     `CMPIArrayFT.getSimpleType()` gets the type of the array elements in a
     CMPIArray object.
     @param ar Pointer to the CMPIArray object for this function.
     @param[out] rc if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, a CMPIType value indicating the type of the
         CMPIArray elements will be returned. The returned value indicates
         the type of single array elements; for example, the value returned
         for a CMPIArray object that contains CMPIString objects, will be
         CMPI_string, and not CMPI_stringA.

     If not successful, CMPI_null will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:

        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar` handle is invalid.

     @todo CMPI_null should be linked somehow
     */
    CMPIType (*getSimpleType) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief Get the value of an array element in a CMPIArray
               object by index.

     `CMPIArrayFT.getElementAt()` gets the value of an array element defined
     by the zero-based position
     `index` of the array element in a CMPIArray object `ar`.
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

    The function return status indicates one of the following CMPIrc codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - `index` value
            out of range.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar`
            handle is invalid.
     */
    CMPIData (*getElementAt) (const CMPIArray* ar, CMPICount index,
            CMPIStatus* rc);

    /** @brief Set the value of an existing array element in a CMPIArray
       object by index

     `CMPIArrayFT.setElementAt()` sets the value `value` and `type`
     into an existing element defined by `index` in the
     array object defined by `ar`.

     @param ar Pointer to CMPIArray.
     @param index zero-based position of the existing element in the
         CMPIArray object. The position shall be equal to or greater than
         0 and less than the size of the array.
     @param value Pointer to to a CMPIValue structure containing
        the non-NULL value to be assigned to the element, or is NULL to
        specify that the element will be set to NULL.
     @param type Either the simple base type of the array or CMPI_null.
        If the value of the type argument is CMPI_chars, the C-language
        string to which the chars member of the value argument points is
        copied by this function and the original string memory may be
        freed by the MI right after this function returns

     @return A CMPIStatus structure indicating the function return status.

     If not successful, the array element's state shall be set to
     CMPI_nullValue, if possible.

     The function return status indicates one of the following @ref CMPIrc
         codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - `index`
         value out of range.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - `type` does not
         correspond to the simple base type of `ar`.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ar`
         handle is invalid.

     @deprecated The use of CMPI_null for the `type` argument is deprecated
     since CMPI 2.1.
     Specify the simple base type of the array instead.

     @deprecated The behavior of setting the array element's state to
     CMPI_nullValue when the function was not successful, is deprecated
     since CMPI 2.1.
     Instead, callers should assume that it is undefined whether the array
     element's state has changed when the function was not successful.
     */
    CMPIStatus (*setElementAt) (const CMPIArray* ar, CMPICount index,
            const CMPIValue* value, CMPIType type);
};

/**
 * @}
 * @addtogroup edt-enumeration
 * @{
 */

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
 * @brief Function table of @ref _CMPIEnumeration
 *     "CMPIEnumeration encapsulated data type object".
 */
struct _CMPIEnumerationFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIEnumeration object.

     `CMPIEnumerationFT.release()` releases a CMPIEnumeration object.
     This indicates to the MB that
     the object (including any objects it contains) will no longer
     be used by the MI. The MB may free the resources associated with
     the object during the call to this function, or later during some
     garbage collection cycle.
     @param en Pointer to to the CMPIEnumeration object to be
        released. That object shall have been created using
        @ref _CMPIEnumerationFT::clone "CMPIEnumerationFT.clone()".
     @return CMPIStatus structure indicating the function return status.
    The function return status indicates one of the following @ref CMPIrc
        codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated data    
        type handle.
     */
    CMPIStatus (*release) (CMPIEnumeration* en);

    /** @brief Create an independent copy of a CMPIEnumeration object.

     `CMPIEnumerationFT.clone()` creates an independent copy of this
     CMPIEnumeration object.
         The resulting object must be released explicitly.
     @param en Pointer to the CMPIEnumeration object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
        return has been updated with the function return status.
     @return If successful, returns a pointer to the copied
     CMPIEnumeration object.

     The returned CMPIEnumeration object shall be explicitly released by
     the MI using @ref _CMPIEnumerationFT::release
     "CMPIEnumerationFT.release()".

     If not successful, returns NULL.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `en` handle is invalid.
     */
    CMPIEnumeration* (*clone) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief Get the next element in a CMPIEnumeration object.

     `CMPIEnumerationFT.getNext()` gets the next element in a
     CMPIEnumeration object.
     @param en Pointer to the CMPIEnumeration object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the function
         return status.
     @return If successful, a CMPIData structure containing the next
         element will be returned.

         If not successful, CMPIData.state will have the CMPI_badValue
         flag set to true

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `en` handle is invalid.
     */
    CMPIData (*getNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief Test for any elements left in a CMPIEnumeration object.

     `CMPIEnumerationFT.hasNext()` tests for any elements left in `en` the
     CMPIEnumeration object.
     @param en Pointer to the CMPIEnumeration object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the function
         return status.
     @return If successful, returns a CMPIBoolean value indicating the
     test result will be returned, as follows: True indicates that the
     enumeration has more elements left; False indicates that this is
     not the case.

     If not successful, False will be returned.

     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `en` handle is invalid.
     */
    CMPIBoolean (*hasNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief Convert a CMPIEnumeration object to a CMPIArray object.

     `CMPIEnumerationFT.toArray()` converts  the CMPIEnumeration object
     represented by the argument `en` into a CMPIArray.
     @param en Pointer to the CMPIEnumeration object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the function
         return status.
     @return If successful, returns a pointer to a CMPIArray object
     containing the elements from the CMPIEnumeration object.

     The returned CMPIArray object shall not be explicitly released by
     the MI, because it may be an internal object of the CMPIEnumeration
     object which will be released along with that object, or a new object
     created by the MB which will be released automatically by the MB
     (see Subclause 4.1.7).

     If not successful, returns NULL.
     The function return status indicates one of the following @ref CMPIrc
        codes:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_INVALID_HANDLE` - The `en` handle is invalid.
     */
    CMPIArray* (*toArray) (const CMPIEnumeration* en, CMPIStatus* rc);
};

/**
 * @}
 * @addtogroup edt-datetime
 * @{
 */

/**
 * @brief CMPIDateTime Support (Subclause 8.9)
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
 * @brief Function table of @ref _CMPIDateTime
 *     "CMPIDateTime encapsulated data type object".
 */
struct _CMPIDateTimeFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIDateTime object.

     `CMPIDateTimeFT.release()` releases a CMPIDateTime object.
     This indicates to the MB that the
     object (including any objects it contains) will no longer be used
     by the MI. The MB may free the resources associated with the object
     during the call to this function, or later during some
     garbage collection cycle.
     @param dt Pointer to the CMPIDateTime object to be released. That
        object shall have been created using @ref _CMPIDateTimeFT::clone
        "CMPIDateTimeFT.clone()".
     @return CMPIStatus structure indicating the function return status.

    The function return status indicates one of the following @ref CMPIrc codes:

    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
        data type handle.

     */
    CMPIStatus (*release) (CMPIDateTime* dt);

    /** @brief Create an independent copy of a CMPIDateTime object.

     `CMPIDateTimeFT.clone()` creates an independent copy of `dt` a
     CMPIDateTime object. The
         resulting object must be released explicitly.
     @param dt DateTime this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful,returns a pointer to the copied CMPIDateTime object.

         The returned CMPIDateTime object shall be explicitly released by the MI
         using @ref _CMPIDateTimeFT::release "CMPIDateTimeFT.release()".

         If not successful, returns NULL

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data    
        type handle.

     */
    CMPIDateTime* (*clone) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** @brief Get the value of a CMPIDateTime object in binary format.

     `CMPIDateTimeFT.getBinaryFormat()` gets the value of a
     CMPIDateTime object as a 64-bit
         unsigned integer in microseconds starting since 00:00:00
         GMT, January 1, 1970, or as an interval in microseconds,
         depending on what kind of value the CMPIDateTime object
         contains
     @param dt  Pointer to to the CMPIDateTime object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful, returns a CMPIUint64 value containing the value of
         the CMPIDateTime object in binary format.

         If not successful, returns 0.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data    
        type handle.
     */
    CMPIUint64 (*getBinaryFormat) (const CMPIDateTime* dt,
            CMPIStatus* rc);

    /** @brief Get the value of a CMPIDateTime object in the string
          format defined for the CIM datetime type.

     `CMPIDateTimeFT.getStringFormat()` gets the value of a
     CMPIDateTime object as a string in the format defined
     in @ref ref-dmtf-dsp0004 "DSP0004" for the CIM datetime type.
     @param dt Pointer to the CMPIDateTime object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful, returns a pointer to a CMPIString object
     containing the value of a CMPIDateTime object in the format
     defined in @ref ref-dmtf-dsp0004 "DSP0004" for the CIM datetime type.

     The returned CMPIString object shall not be explicitly released by
     the MI, because it may be an internal object of the CMPIDateTime
     object which will be released along with that object, or a new
     object created by the MB which will be released automatically by
     the MB (see Subclause 4.1.7).

     If not successful, returns NULL

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` - Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid encapsulated
        data type handle.
     */ 
    CMPIString* (*getStringFormat) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** @brief Test whether a CMPIDateTime object contains an interval value.

     `CMPIDateTimeFT.isInterval()` tests whether DateTime is an interval value.
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIBoolean value indicating the test
         result, as follows:
         @li True indicates that the CMPIDateTime object contains an interval
         value;
         @li False indicates that this is not an interval.

    If not successful, False will be returned.

    The function return status indicates one of the following @ref CMPIrc codes:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_INVALID_HANDLE` -  Invalid encapsulated data    
        type handle.
     */
    CMPIBoolean (*isInterval) (const CMPIDateTime* dt, CMPIStatus* rc);
};

/**
 * @}
 * @addtogroup edt-propertylist
 * @{
 */

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
 * @brief Function table of @ref _CMPIPropertyList
 *     "CMPIPropertyList encapsulated data type object".
 */
struct _CMPIPropertyListFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**  @brief Release a CMPIPropertyList object.

     `CMPIPropertyListFT.release()` releases a CMPIPropertyList object.
         This indicates to the MB that the object (including any objects it
         contains) will no longer be used by the MI. The MB may free
         the resources associated with the object during the call to
         this function, or later during some garbage collection cycle.
     @param plist Pointer to the CMPIPropertyList object to be released.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` -Invalid `plist`.
     */
    CMPIStatus (*release) (CMPIPropertyList* plist);

    /** @brief Create an independent copy of a CMPIPropertyList
                object.

     `CMPIPropertyListFT.clone()` creates an independent copy of `plist`,
     the CMPIPropertyList object.
     @param plist Pointer to the CMPIPropertyList object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return If successful, returns a pointer to the copied CMPIPropertyList
         object.

         The returned CMPIPropertyList object shall be explicitly released by
         the MI using @ref _CMPIPropertyListFT::release
         "CMPIPropertyListFT.release()".

         If not successful, returns NULL.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `plist`.
     */
    CMPIPropertyList* (*clone) (const CMPIPropertyList* plist, CMPIStatus* rc);

    /** @brief Test whether a property is in the property list
           represented by a CMPIPropertyList object.

     `CMPIPropertyListFT.isPropertyInList()` tests whether a property is in
     the property list represented by a CMPIPropertyList object.

       The MB's implementation of this function should be efficient. However,
       it is recommended that MIs when returning many instances invoke this
       function only once for each property, and cache the result.

     @param plist Pointer to the CMPIPropertyList object to be for this
         function.
     @param pname A CMPISstring specifying the name of the property to be
         tested.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return If successful, a CMPIBoolean value indicating the test result
     will be returned, as follows: True indicates that the property is in
     the property list; False indicates that this is not the case.

     If not successful, returns False.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - Invalid `plist`.
         @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid `pname`.
     */
    CMPIBoolean (*isPropertyInList) (const CMPIPropertyList* plist,
            const char* pname, CMPIStatus* rc);

    /** @brief Get CMPIPropertyList as an array of strings.

     `CMPIPropertyListFT.getProperties()` returns the property list
     represented by `plist`
           CMPIPropertyList object as a NULL-terminated array of
           pointers to strings.
     @param plist Pointer to the CMPIResult object to be for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return If successful, returns a pointer to the first entry of a
         NULL-terminated array of pointers to strings that represent the
         property names in the property list represented by the
         CMPIPropertyList object.

        The entries in that array may be in any order and in any lexical case
        (possibly different than originally specified in
        @ref _CMPIBrokerEncFT::newPropertyList
        "CMPIBrokerEncFT.newPropertyList()").

        The returned array shall not be explicitly released by the MI, because
        it may point to an internal data area in the CMPIPropertyList object
        which will be released along with that object, or it may point to a
        new array created by the MB which will be released automatically
        by the MB (see Subclause 4.1.7).
        @todo KS_TODO

        If not successful, returns NULL.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - The `plist` handle is invalid.
     */
    const char** (*getProperties) (const CMPIPropertyList* plist,
            CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup edt-enumerationfilter
 * @{
 */

/**
 * @brief CMPIEnumerationFilter Support (Subclause 8.16)
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
 * @brief Function table of @ref _CMPIEnumerationFilter
 *     "CMPIEnumerationFilter encapsulated data type object".
 * @version Added in CMPI 2.1.
 */
struct _CMPIEnumerationFilterFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief Release a CMPIResult object.

     `CMPIEnumerationFilterFT.release()` releases a CMPIEnumerationFilter
         object. This indicates to the MB that
         the object (including any objects it contains) will no longer
         be used by the MI. The MB may free the resources associated with
         the object during the call to this function, or later during
         some garbage collection cycle.
     @param rslt Pointer to the CMPIResult object to be released.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
         @li CMPI_RC_OK Operation successful.
         @li CMPI_RC_ERR_INVALID_HANDLE The `ef` handle is invalid.
     @version Added in CMPI 2.1.
     */
    CMPIStatus (*release) (CMPIEnumerationFilter* ef);

    /** @brief Create an independent copy of a CMPIEnumerationFilter
               object.

     `CMPIEnumerationFilterFT.clone()` creates an independent copy of the
     CMPIEnumerationFilter object defined by `rslt`.
     @param rslt Pointer to CMPIEnumerationFilter object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
     @return If successful, returns a pointer to the copied
         CMPIEnumerationFilter object.

         The returned CMPIEnumerationFilter object shall be explicitly
         released by the MI using @ref _CMPIEnumerationFilterFT::release
         "CMPIEnumerationFilterFT.release()".

         If not successful, returns NULL.

     The following @ref CMPIrc codes shall be recognized:
         @li CMPI_RC_OK Operation successful.
         @li CMPI_RC_ERR_INVALID_HANDLE The `ef` handle is invalid.
     @version Added in CMPI 2.1.
     */
    CMPIEnumerationFilter* (*clone) (const CMPIEnumerationFilter* ef,
            CMPIStatus* rc);

    /** @brief Instance matches the filter represented by a
           CMPIEnumerationFilter object

     `CMPIEnumerationFilterFT.match()` tests whether an instance matches
       the filter 
       represented by the CMPIEnumerationFilter object `ef`.
       The filter matches the instance if the conditions defined in the
       filter are met by the properties of the instance.
       @param ef Pointer to the CMPIEnumerationFilter object for this function.
       @param inst CMPIInstance object to be tested against the filter.
       @param Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
       @return If successful, returns a CMPIBoolean value indicating the test
       result as follows: True indicates that the instance
       matches the filter; False indicates that this is not the case.

       If not successful, returns False.

     The function return status indicates one of the following @ref CMPIrc
     codes:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_INVALID_HANDLE` - The `ef` handle
             is invalid.
        @li `CMPI_RC_ERR_INVALID_QUERY` - The filterQuery is not a
            valid query in the specified filter query language
        @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of
            the query language is not supported.
        @li `CMPI_RC_FAILED` - Error not defined by one of the above
            codes occurred.
     @version Added in CMPI 2.1.
     */
    CMPIBoolean (*match) (const CMPIEnumerationFilter* ef,
            const CMPIInstance* inst, CMPIStatus* rc);

};

#endif /*CMPI_VER_210*/

/**
 * @}
 * @addtogroup instance-mi
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
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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

    /** @brief Perform cleanup for an Instance MI.

     `CMPIInstanceMIFT.cleanup()` shall perform any necessary cleanup operation
     of the library of which this Instance MI `mi` unless the MI
     postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. After this function returns, the MB may unload the load
     library this MI is part of, unless the MI postpones the cleanup
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data for
     the invocation(see Subclause 8.1).

     @param terminating When  is true, the MB is in the process of shutting
     down. The MI shall perform any necessary cleanup and shall not postpone
     the cleanup. After this function returns (successful or in error), the
     MB will consider this MI to be uninitialized and will not call further
     MI functions for this MI.

     When terminating is false, the MI can choose to perform or postpone the
     cleanup, by performing one of these actions:
     <ul>
     <li>The MI performs any necessary cleanup and does not request postponing
     the cleanup. After this function returns (successful or in error),
     the MB will consider this MI to be uninitialized and will not call further
     MI functions for this MI.

     <li>The MI does not perform any cleanup and temporarily postpones
     the cleanup, by returning CMPI_RC_DO_NOT_UNLOAD. This will cause
     the MB to consider this MI still to be initialized, and the MB may call
     further MI functions of this MI. The MB may call this function again
     after some MB implementation-specific time.

     <li>The MI does not perform any cleanup and permanently postpones the
     cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
     MB to consider this MI still to be initialized, and the MB may call
     further MI functions of this MI. The MB will not call this function again
     until the MB terminates (at which time the MB calls this function with
     terminating set to true).
    </ul>
     @return Function return status.
     The following @ref CMPIrc codes shall be recognized:
     @li  `CMPI_RC_OK` - Operation successful.
     @li  `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li  `CMPI_RC_DO_NOT_UNLOAD` - Operation successful - do
         not unload now.
     @li  `CMPI_RC_NEVER_UNLOAD` - Operation successful -  never   
          unload.
     */
    CMPIStatus (*cleanup) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Enumerate instance paths of instances of a given
       class serviced by this MI.

     `CMPIInstanceMIFT.enumerateInstanceNames()` enumerates the instance
     paths of instances of a given class define by
         `classPthy` that are serviced by this MI `mi`>, by
         accessing the underlying managed elements.

         This function is provided by the MI in `mi` the context
         of a particular MI name.

         The class of the `op`> argument for which this
         function will be called by the MB depends on the specifics
         of how the MB relates classes and MI names, which is out of
         scope for this standard. As a result, the MB may call this
         function for classes for which the MI is not responsible.
         In order for an MI to be portable across MB implementations
         with different approaches to relate MI names and classes,
         the MI must check whether it services the class specified
         in the `classPath` argument.
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all instance
         paths representing the result set into this container.
     @param classPath CMPIObjectPath containing namespace and classname
         components. Hostname and key components, if present, have
         no meaning and should be ignored.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*enumerateInstanceNames) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* classPath);

    /** @brief Enumerate the instances of a given class serviced by
               this MI.

     `CMPIInstanceMIFT.enumerateInstances()` shall enumerate the instances
     of a given class that are
         serviced by this MI, by accessing the underlying managed elements.

         This function is provided by the MI in context of `mi`
         a particular MI name.

         The class of the `op` argument for which this
         function will be called by the MB depends on the specifics
         of how the MB relates classes and MI names, which is out of
         scope for this standard. As a result, the MB may call this
         function for classes for which the MI is not responsible.
         In order for an MI to be portable across MB implementations
         with different approaches to relate MI names and classes,
         the MI must check whether it services the class specified
         in the classPath argument.
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all instances
         representing the result set into this container.
     @param classPath CMPIObjectPath containing namespace and classname
         components.Hostname and key components, if present, have no meaning
         and should be ignored.
     @param properties If not NULL, an array of zero or more pointers
         to strings, each specifying a property name. The members of the
         array define one or more property names. Each returned object
         MUST NOT include elements for any properties missing from this list.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*enumerateInstances) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* classPath , const char** properties);

    /** @brief Get a given instance.

     `CMPIInstanceMIFT.getInstance()` shall get the instance defined
     by the CMPIObjectPath `op`.
         This function is provided by the MI in context of `mi`
         a particular MI name.

         The class of the `op` argument for which this function will
         be called by the MB depends on the specifics of how the MB relates
         classes and MI names, which is out of scope for this standard.
         As a result, the MB may call this function for classes for which
         the MI is not responsible. In order for an MI to be portable across
         MB implementations with different approaches to relate MI names
         and classes, the MI must check whether it services the class
         specified in the classPath argument.

     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the instance
         representing the result set into this container.
     @param op CMPIObjectPath containing namespace and classname components.
         Hostname and key components, if present, have no meaning and
         should be ignored.
     @param properties If not NULL,  an array of zero or more pointers
         to strings, each specifying a property name. The members of the
         array define one or more Property names. Each returned object
         MUST NOT include elements for any Properties missing from this list.
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
    @todo TBD: KS_TODO Why no server limits exceeded
    @todo TBD: KS_todo should we change to classPath as property name.
    @todo KS_todo Clarify formatting for error codes and also CMPIError usage
     */
    CMPIStatus (*getInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char** properties);

    /** @brief Create an instance of a given class.

     `CMPIInstanceMIFT.createInstance()` shall create an instance of a
     given class `op` in the namespace of
     that class defined in `op` and the properties defined in
         `inst`.

         This function is provided by the MI in context of a particular MI
         name. The class of the `classPath` argument for which this
         function will be called by the MB depends on the specifics of how the
         MB relates classes and MI names, which is out of scope for this
         standard. As a result, the MB may call this function for classes
         for which the MI is not responsible. In order for an MI to be
         portable across MB implementations with different approaches to
         relate MI names and classes, the MI must check whether it services
         the class specified in the classPath argument.
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the
         instance path of the created instance into this container
         (see Subclause 8.2).
     @param classPath Pointer to a CMPIObjectPath object that references
         the given class. The hostname and key components, if present, have
         no meaning and should be ignored.
     @param inst Pointer to a CMPIInstance object specifying
         property values for the new instance. The object path
         component within this CMPIInstance object has no meaning;
         it should not be provided by MBs and should not be used by
         MIs
     @return Function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ALREADY_EXISTS`</TD> <TD>WIPG0213</TD>
     <TD>Instance already exists.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>

     @deprecated The use of the key component in the `classPath` argument is
     deprecated since CMPI 2.1; the key component should not be provided by MBs
     and should not be used by MIs.
     */
    CMPIStatus (*createInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* classPath,
            const CMPIInstance* inst);

    /** @brief Modify property values of a given instance.

     `CMPIInstanceMIFT.modifyInstance()` shall modify property values of
     `mi`, a given instance with properties
     defined in `modInst` and using `properties`, an array of
     pointers to property names, as a filter,

     This function is provided by the MI in context of a particular MI name.
     The class in the `instPath` argument for which this function will
     be called by the MB depends on the specifics of how the MB relates classes
     and MI names, which is out of scope for this standard. As a result, the MB
     may call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether
     it services the class specified in the instPath argument.

     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that contains the namespace, class name,
         and key components. The hostname component, if present, has no
         meaning and should be ignored.
     @param modInst Pointer to a CMIPInstance object specifying new values
         for the properties to be modified. The object path component within
         this CMPIInstance object has no meaning; it should not be provided by
         MBs and should not be used by MIs.
     @param properties if not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in
         the CMPIInvocationFlags entry of the ctx argument have no meaning
         for this function. The function shall not modify elements for any
         properties missing from this list. If the properties argument
         is NULL, this indicates that all properties specified in
         `modInst` are modified

     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NO_SUCH_ PROPERTY`</TD><TD>WIPG0220</TD>
     <TD>No such property.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*modifyInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* instPath,
            const CMPIInstance* modInst, const char** properties);

    /** @brief Delete a given instance.

     `CMPIInstanceMIFT.deleteInstance()` shall delete an existing instance
     defined by `instPath`.

     This function is provided by the MI in context of a particular MI name.
     The class in the instPath argument for which this function will be called
     by the MB depends on the specifics of how the MB relates classes and MI
     names, which is out of scope for this standard. As a result, the MB may
     call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether
     it services the class specified in the instPath argument.
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that contains the namespace, class name,
         and key components. The hostname component, if present, has no
         meaning and should be ignored.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*deleteInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op);

    /** @brief Execute a query on a given class and return the
                query result.

     `CMPIInstanceMIFT.execQuery()` shall query the enumeration of instances
     of the class (and subclasses) defined
     by `op` using `query` expression.

     This function is provided by the MI in context of a particular MI name.
     The class in the instPath argument for which this function will be called
     by the MB depends on the specifics of how the MB relates classes and MI
     names, which is out of scope for this standard. As a result, the MB may
     call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether
     it services the class specified in the instPath argument.
     @param mi Pointer to a CMPIInstanceMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param classPath Pointer to a CMPIObjectPath object that references
         the given class. The hostname and key components, if present, have
         no meaning and should be ignored.
     @param query Pointer to a string containing the select expression.
     @param lang Pointer to a case-sensitive string containing the query
     language.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED`</TD>
     <TD>WIPG0221</TD>
     <TD>Query language not supported.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED`</TD>
     <TD>WIPG0222</TD>
     <TD>A feature of the query language is not supported.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_QUERY`</TD>
     <TD>WIPG02223</TD>
     <TD>Invalid Query.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*execQuery) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* classPath,
            const char* query, const char* lang);

#ifdef CMPI_VER_210

    /** @brief Enumerate the instances of a given class that are
         serviced by this MI, returning only those that match the
         `filterQuery` argument.

      `CMPIInstanceMIFT.enumerateInstancesFiltered()` shall
      enumerate the instances of a given class that are serviced by this MI,
      returning only those instances that match the filterQuery argument,
      by enumerating the underlying managed elements. The returned instances
      shall have their instance paths set. If no such instances are found,
      the function shall return success with an empty result data container.

     @param mi Pointer to to a CMPIInstanceMI structure.
     @param ctx Pointer to to a CMPIContext object containing the invocation
       context.
     @param rslt Pointer to to a CMPIResult object that is the result data
         container. Upon successful return the MI shall have put all
         instances representing the result set into this container
         (see Subclause 8.2).
     @param classPath Pointer to to a CMPIObjectPath object that references
     the given class and that contains namespace and class name components.
     The hostname and key components, if present, have no meaning and
     should be ignored.
     @param properties If not NULL, is an array of zero or more pointers
     to strings, each specifying a property name. The end of the array
     is identified by a NULL pointer. This set of property names will
     reflect the effects of any invocation flags specified in the
     CMPIInvocationFlags entry of the ctx argument. Each returned
     instance shall not include elements for any properties missing
     from this list. If the `properties` argument is NULL, this indicates
     that all properties shall be included in each returned instance.
     @param filterquerylanguage
     @param filterquery defines the query language used by the filterQuery
     argument. If it is NULL, the filterQuery argument is ignored and
     no filtering is performed. Note that FQL is required to be supported
     by MIs as a query language; see Subclause 4.5.
     @param continueOnerror
     @return CMPIStatus structure indicating the function return status.

     The following table lists the @ref CMPIrc codes that shall be used by
     the MI in the function return status, as well as the WBEM
     operation messages that should be used in the CMPIError object
     if the MI supports extended error handling (see Subclause
     8.14):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD>>/TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD><TD>Other error occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED`</TD>
         <TD>WIPG0221</TD><TD>Query language not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED`</TD>
         <TD>WIPG0222</TD>
         <TD>A feature of the query language is not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_QUERY`</TD>
         <TD>WIPG0223</TD><TD>Invalid query.</TD></TR>
     </TABLE>
     @version Added in CMPI 2.1.
     @todo fill out filterQueryLanguage argument text
     */
    CMPIStatus (*enumerateInstancesFiltered) (CMPIInstanceMI* mi,
         const CMPIContext* ctx, const CMPIResult* rslt,
         const CMPIObjectPath* classPath,
         const char** properties, const char*filterQuerylanguage,

#endif /*CMPI_VER_210*/

};

/**
 * @}
 * @addtogroup association-mi
 * @{
 */

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
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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

    /** @brief Perform cleanup for an @ref CMPIAssociationMI object.

     `CMPIAssociationMIFT.cleanup()` shall perform any necessary cleanup
     operations prior to the
     unloading of the library of which this MI group is part.

     While this function executes, the MB will not call any other MI functions
         for this MI. This function will be called once for a specific MI
         (unless the MI postpones the cleanup), even if that MI services more
         than one namespace. After this function returns, the MB may unload
         the load library this MI is part of, unless the MI postpones the
         cleanup.
     @param mi Pointer to a CMPIAssociationMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1). The context data entries
         are MB implementation-specific.
     @param terminating When true, the MB is in the process of shutting down.
         The MI shall perform any necessary cleanup and shall not postpone
         the cleanup. After this function returns (successful or in error),
         the MB will consider this MI to be uninitialized and will not call
         further MI functions for this MI.

    When false, the MI can choose to perform or postpone the cleanup, by
    performing one of these actions:
    <ul>
    <li>The MI performs any necessary cleanup and does not request postponing
    the cleanup. After this function returns (successful or in error), the
    MB will consider this MI to be uninitialized and will not call further
    MI functions for this MI.
    <li>The MI does not perform any cleanup and temporarily postpones the
    cleanup, by returning CMPI_RC_DO_NOT_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call further
    MI functions of this MI. The MB may call this function again after
    some MB implementation-specific time.
    <li>The MI does not perform any cleanup and permanently postpones the
    cleanup, by returning CMPI_RC_NEVER_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call
    further MI functions of this MI. The MB will not call this function
    again, until the MB terminates (at which time the MB calls this function
    with terminating set to true).
     </ul>
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
         @li `CMPI_RC_OK` - Operation successful.
         @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
         @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not
             unload now; the MB may retry an unload later.
         @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never
            unload; the MB will not retry an unload later unless it
            shuts down.
     */
    CMPIStatus (*cleanup) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Enumerate the instances associated with a given
          source instance that are serviced by this MI.

     `CMPIAssociationMIFT.associators()` shall enumerate the
     instances associated with a given source instance and that are serviced
     by this MI, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of the `instPath` argument for which this function will
     be called by the MB depends on the specifics of how the MB relates classes
     and MI names, which is out of scope for this standard. As a result, the MB
     may call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether it
     services the class specified in the `instPath` argument.

     @param mi Pointer to an associated instance.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container
         (see Subclause 8.2).
     @param instPath Pointer to to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name,
         and key components. The hostname component, if present,
         has no meaning and should be ignored. If the source instance
         does not exist, this function shall either return success with
         an empty result data container or CMPI_RC_ERR_NOT_FOUND. (Deprecated)
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
     @param properties If not NULL, the members of the array define one or more
     Property names. Each returned Object MUST NOT include elements for any
     Properties missing from this list. If NULL all properties must be returned.
     the returned Object MUST match the value of this parameter).

     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*associators) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* asscClass, const char* resultClass, const char* role,
            const char* resultRole, const char** properties);

    /** @brief Enumerate the instance paths of instances associated
       with a given source instance that are serviced by this MI.

     `CMPIAssociationMIFT.associatorNames()` shall enumerate
     the instance paths of instances associated with a given source instance
     and that are serviced by this MI, by accessing the underlying managed
     elements.

    This function is provided by the MI in context of a particular MI name.
    The class of the `instPath` argument for which this function will
    be called by the MB depends on the specifics of how the MB relates classes
    and MI names, which is out of scope for this standard.  As a result, the
    MB may call this function for classes for which the MI is not responsible.
    In order for an MI to be portable across MB implementations with different
    approaches to relate MI names and classes, the MI must check whether it
    services the class specified in the `instPath` argument.

     @param mi Pointer to an association instance.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container
         (see Subclause 8.2).
     @param instPath Pointer to to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name,
         and key components. The hostname component, if present,
         has no meaning and should be ignored. If the source instance
         does not exist, this function shall either return success with
         an empty result data container or CMPI_RC_ERR_NOT_FOUND. (Deprecated)
     @param assocClass If not NULL, MUST be a valid Association Class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object MUST be associated to the source Object via an
         instance of this class or one of its subclasses.
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
         via an Association in which the returned Object plays the specified
         role (i.e. the name of the Property in the Association
         Class that refers to the returned Object MUST match the
         value of this parameter).
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD><TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*associatorNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* instPath, const char* assocClass,
            const char* resultClass, const char* role,
            const char* resultRole);

    /** @brief Enumerate the instance paths of instances associated
       with a given source instance that are serviced by this MI.

     `CMPIAssociationMIFT.associatorNames()` shall
     enumerate the instance paths of instances associated with `instPath`
     a given source instance and that are serviced by this MI, by accessing
     the underlying managed elements.

    If the `assocClass` or `resultClass` filters are specified
    in a call to this function, the MB is not required to scope calls to this
    function to only the MIs that service these classes.  As a result, the MB
    may (and will, in most implementations) call this function for classes in
    the `assocClass` or `resultClass` arguments for which the MI
    is not responsible.  In order for an MI to be portable across MB
    implementations, the MI must check whether it services the classes
    specified in the `assocClass` and `resultClass` arguments.

     @param mi Pointer to an association instance.
     @param ctx Invocation Context
     @param rslt Result data container.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given source instance and that contains the namespace,
         class name, and key components. The hostname component,
         if present, has no meaning and should be ignored.
         If the source instance does not exist, this function
         shall either return success with an empty result data
         container or CMPI_RC_ERR_NOT_FOUND. <b>(Deprecated)</b>
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
     @param properties If not NULL, the members of the array define one or
     more Property names. Each returned Object MUST NOT include
     elements for any Properties missing from this list
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*references) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* resultClass, const char* role,
            const char** properties);

    /** @brief Enumerate the instance paths of association instances
           referencing a given source instance that are serviced by this MI.

     `CMPIAssociationMIFT.referenceNames()` shall enumerate
     the instance paths of the association instances referencing a given
     source instance and that are serviced by this MI, by accessing the
     underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of the instPath argument for which this function will be called
     by the MB depends on the specifics of how the MB relates classes and MI
     names, which is out of scope for this standard. As a result, the MB may
     call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether it
     services the class specified in the `instPath` argument.

     @param mi Pointer to an association instance.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container
         (see Subclause 8.2).
     @param instPath Pointer to to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name,
         and key components. The hostname component, if present,
         has no meaning and should be ignored. If the source instance
         does not exist, this function shall either return success with
         an empty result data container or CMPI_RC_ERR_NOT_FOUND. (Deprecated)
     @param resultClass If not NULL, MUST be a valid Class name.
         It acts as a filter on the returned set of Objects by mandating that
         each returned Object MUST be either an Instance of this Class (or one
         of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
         It acts as a filter on the returned set of Objects by mandating
         that each returned Object MUST be associated to the source Object
         via an Association in which the source Object plays the specified role
         (i.e. the name of the Property in the Association Class that refers
         to the source Object MUST match the value of this argument).
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*referenceNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* instPath, const char* resultClass,
            const char* role);

#ifdef CMPI_VER_210

    /** @brief Enumerate the instances associated with a given
      source instance serviced by this MI, returning only instances
      that match the `filterQuery` argument.

     `CMPIAssociationMIFT.associatorsFiltered()` shall
         enumerate instances associated with a source instance and that
         are serviced by this MI, returning only those instances that
         match the `filterQuery argument`, by accessing the underlying
         managed elements. The returned instances shall have their
         instance paths set. If no such instances are found, the
         function shall return success with an empty result data
         container.
     @param mi Pointer to an association instance.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container
         (see Subclause 8.2).
     @param instPath Pointer to to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name,
         and key components. The hostname component, if present,
         has no meaning and should be ignored. If the source instance
         does not exist, this function shall either return success with
         an empty result data container or CMPI_RC_ERR_NOT_FOUND.
         <b>(Deprecated)</b>
     @param assocClass if not NULL, shall be a valid association class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be associated with the source object via
         an instance of this class or one of its subclasses.
     @param resultClass If not NULL, MUST be a valid Class name.
         It acts as a filter on the returned set of Objects by mandating that
         each returned Object MUST be either an Instance of this Class (or one
         of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
         It acts as a filter on the returned set of Objects by mandating
         that each returned Object MUST be associated to the source Object
         via an Association in which the source Object plays the specified role
         (i.e. the name of the Property in the Association Class that refers
         to the source Object MUST match the value of this argument).
     @param resultRole if not NULL, shall be a valid property name. 
         It acts as a filter on the returned set of objects by
         mandating that each returned object shall be associated
         with the source object via an association in which the
         returned object plays the specified role (i.e., the name of
         the property in the association class that refers to the
         returned object shall match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         CMPIInvocationFlags entry of the ctx argument have no meaning for
         this function. Each returned instance shall not include elements for
         any properties missing from this list. If the properties argument is
         NULL, this indicates that all properties shall be included in each
         returned instance.
     @param filterQueryLanguage defines the query language used by the
         `filterQuery` argument. If it is NULL, the `filterQuery` argument
         is ignored and no filtering is performed. Note that FQL is required
         to be supported by MIs as a query language; see Subclause 4.5.
     @param filterQuery defines the query in the query language defined by
         the filterQueryLanguage argument. If NULL, no filtering is performed.
         A request that specifies a filter through valid and non-NULL
         `filterQueryLanguage` and `filterQuery` arguments shall return only
         instances that match that filter as defined in the filter
         specification.
     @param continueOnError defines whether this operation may continue to
         return objects after it returns an error. If false, the MI shall
         terminate after returning an error to the result data container.
         If true, the MI may continue to returning data (objects and subsequent
         errors) to the result data container after returning an error. An MI
         that cannot continue after returning an error shall ignore the value
         of the `continueOnError` argument and shall behave as if it was
         specified as false.
     @return CMPIStatus structure indicating the function return status.
         The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     @version Added in CMPI 2.1 as part of the support for pulled client
         operations.
     @todo probably need more specific ref to FQL than this.
     */
    CMPIStatus (*associatorsFiltered)
        ( CMPIAssociationMI* mi, const CMPIContext* ctx, const CMPIResult* rslt,
         const CMPIObjectPath* instPath, const char* assocClass,
         const char* resultClass, const char* role, const char* resultRole,
         const char** properties, const char* filterQueryLanguage,
         const char* filterQuery, CMPIBoolean continueOnError);

    /** @brief Enumerate the association instances referencing a given source
       instance that are serviced by this MI, returning only those instances
       that match the `filterQuery` argument.

       `CMPIAssociationMIFT.referencesFiltered()` shall
       enumerate the association instances referencing a given source instance
       and that are serviced by this MI, returning only those instances that
       match the `filterQuery` argument, by accessing the underlying managed
       elements. The returned instances shall have their instance paths set.
       If no such instances are found, the function shall return success with
       an empty result data container.
     @param mi Pointer to an association instance.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1).
     @param rslt Pointer to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container
         (see Subclause 8.2).
     @param instPath Pointer to to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name,
         and key components. The hostname component, if present,
         has no meaning and should be ignored. If the source instance
         does not exist, this function shall either return success with
         an empty result data container or CMPI_RC_ERR_NOT_FOUND. (Deprecated)
     @param resultClass If not NULL, MUST be a valid Class name.
         It acts as a filter on the returned set of Objects by mandating that
         each returned Object MUST be either an Instance of this Class (or one
         of its subclasses).
     @param role If not NULL, MUST be a valid Property name.
         It acts as a filter on the returned set of Objects by mandating
         that each returned Object MUST be associated to the source Object
         via an Association in which the source Object plays the specified role
         (i.e. the name of the Property in the Association Class that refers
         to the source Object MUST match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         CMPIInvocationFlags entry of the ctx argument have no meaning for
         this function. Each returned instance shall not include elements for
         any properties missing from this list. If the properties argument is
         NULL, this indicates that all properties shall be included in each
         returned instance.
     @param filterQueryLanguage defines the query language used by the
         `filterQuery` argument. If it is NULL, the `filterQuery` argument
         is ignored and no filtering is performed. Note that FQL is required
         to be supported by MIs as a query language; see Subclause 4.5.
     @param filterQuery defines the query in the query language defined by
         the filterQueryLanguage argument. If NULL, no filtering is performed.
         A request that specifies a filter through valid and non-NULL
         `filterQueryLanguage` and `filterQuery` arguments shall return only
         instances that match that filter as defined in the filter
         specification.
     @param continueOnError defines whether this operation may continue to
         return objects after it returns an error. If false, the MI shall
         terminate after returning an error to the result data container.
         If true, the MI may continue to returning data (objects and subsequent
         errors) to the result data container after returning an error. An MI
         that cannot continue after returning an error shall ignore the value
         of the `continueOnError` argument and shall behave as if it was
         specified as false.
     @return CMPIStatus structure indicating the function return status.
         The following @ref CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     @version Added in CMPI 2.1 as part of the support for pulled client
         operations.
     @todo probably need more specific ref to FQL than this.
     */
    CMPIStatus (*referencesFiltered)
        ( CMPIAssociationMI* mi, const CMPIContext* ctx, const CMPIResult* rslt,
         const CMPIObjectPath* instPath, const char* resultClass,
         const char* role, const char** properties,
         const char* filterQueryLanguage, const char* filterQuery,
         CMPIBoolean continueOnError);

#endif /*CMPI_VER_210*/

};

/**
 * @}
 * @addtogroup method-mi
 * @{
 */

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
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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

    /** @brief Perform cleanup for an Instance MI.

     `CMPIMethodMIFT.cleanup()` shall perform any
     necessary cleanup operation prior to the unloading of the
     library of which this MI group is part. This function is called
     prior to the unloading of the provider.

     @param mi The mi argument is a pointer to a CMPIMethodMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
     containing the Invocation Context.
     @param terminating When true, the terminating argument indicates that
     the MB is in the process of terminating and that cleanup must be done.
     When set to false, the MI may respond with CMPI_IRC_DO_NOT_UNLOAD,
     or CMPI_IRC_NEVER_UNLOAD, indicating that unload will
     interfere with current MI processing.
     @return Function return status.

     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Operation successful - do not   
         unload now.
     @li `CMPI_RC_NEVER_UNLOAD` - Operation successful - never   
         unload.
     */
    CMPIStatus (*cleanup) (CMPIMethodMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Invoke a method on a target object.

     `CMPIMethodMIFT.invokeMethod()` shall invoke a named,
     extrinsic method on a target object, by accessing the underlying
     managed elements. Instance methods (i.e., non-static methods)
     can be invoked only on instances. Class methods (i.e., static methods)
     can be invoked on instances and classes

     This function is provided by the MI in context of a particular
     MI name. The class of the objPath argument for which this function
     will be called by the MB depends on the specifics of how the MB
     relates classes and MI names, which is out of scope for this
     standard. As a result, the MB may call this function for classes
     for which the MI is not responsible. In order for an MI to be
     portable across MB implementations with different approaches
     to relate MI names and classes, the MI must check whether
     it services the class specified in the objPath argument.

     @param mi Pointer to a CMPIMethodMI object.
     @param ctx Pointer to a CMPIContext object containing the context
         data for the invocation
     @param rslt Pointer to a CMPIResult object that is the result
         data container. Upon successful return, the MI shall have put the
         return value of the method into this container (see Subclause 8.2).
         The CMPIResultFT function to be used for that depends on the
         data type of the method return, as follows:
    <ul>
    <li>Return values declared as embedded instances (see Subclause 4.1.3)
        shall be returned using @ref _CMPIResultFT::returnInstance
        "CMPIResultFT.returnInstance()".
    <li>Return values declared with type `ref <classname>`
         (see Subclause 4.1.3) shall be returned
         using @ref _CMPIResultFT::returnObjectPath
         "CMPIResultFT.returnObjectPath()".
    <li>Any other return values shall be returned using
        @ref _CMPIResultFT::returnData "CMPIResultFT.returnData()".
    </ul>
     @param objPath Pointer to to the CMPIObjectPath object that references
         the target object on which the method is invoked. If the target
         object is an instance, this object path will contain the namespace,
         class name, and key components. The hostname component, if present,
         has no meaning and should be ignored. If the target object is
         a class, this object path will contain the namespace and
         class name components. The hostname and key components,
         if present, have no meaning and should be ignored.
     @param method Pointer to to a string containing the method name.
     @param in Pointer to to a CMPIArgs object (whether the method has any
         input parameters or not) that contains the method input parameters.
     @param out[in out] Pointer to to an empty CMPIArgs object (whether the
         method has any output parameters or not) that, upon
         successful return of the method, shall have been updated by
         the MI to contain the method output parameters.
     @return CMPIStatus structure indicating the function return status.

     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by   
         this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_METHOD_NOT_AVAILABLE` - Method not available.
     @li `CMPI_RC_ERR_METHOD_NOT_FOUND` - Method not found.

    @todo KS_todo fix the error codes.
     */
    CMPIStatus (*invokeMethod) (CMPIMethodMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* objPath,
            const char* method, const CMPIArgs* in, CMPIArgs* out);

};

/**
 * @}
 * @addtogroup property-mi
 * @{
 */

/**
 * @brief CMPIPropertyMI object.
 *
 * This object is provided by a property MI through MI factory functions
 * (see CMPI specification), in order to make its MI functions available to the
 * MB.
 *
 * @deprecated Property MIs are deprecated since CMPI 2.1,
 * in accord with the deprecation of property client operations in DMTF
 * specifications.
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
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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

    /** @brief Perform cleanup for a Property MI <b>(Deprecated)</b>.

     `CMPIPropertyMIFT.cleanup()` shall perform any necessary cleanup
     operations prior to the
     unloading of the library of which this MI group is part.

     While this function executes, the MB will not call any other MI functions
         for this MI. This function will be called once for a specific MI
         (unless the MI postpones the cleanup), even if that MI services more
         than one namespace. After this function returns, the MB may unload
         the load library this MI is part of, unless the MI postpones the
         cleanup.
     @param mi Pointer to a CMPIPropertyMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1). The context data entries
         are MB implementation-specific.
     @param terminating When true, the MB is in the process of shutting down.
         The MI shall perform any necessary cleanup and shall not postpone
         the cleanup. After this function returns (successful or in error),
         the MB will consider this MI to be uninitialized and will not call
         further MI functions for this MI.

    When false, the MI can choose to perform or postpone the cleanup, by
    performing one of these actions:
    <ul>
    <li>The MI performs any necessary cleanup and does not request postponing
    the cleanup. After this function returns (successful or in error), the
    MB will consider this MI to be uninitialized and will not call further
    MI functions for this MI.
    <li>The MI does not perform any cleanup and temporarily postpones the
    cleanup, by returning CMPI_RC_DO_NOT_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call further
    MI functions of this MI. The MB may call this function again after
    some MB implementation-specific time.
    <li>The MI does not perform any cleanup and permanently postpones the
    cleanup, by returning CMPI_RC_NEVER_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call
    further MI functions of this MI. The MB will not call this function
    again, until the MB terminates (at which time the MB calls this function
    with terminating set to true).
     </ul>
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:

     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful - do not   
         unload now; the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful - never   
         unload; the MB will not retry an unload later unless it
         shuts down.

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property client operations in DMTF
     specifications.
     */
    CMPIStatus (*cleanup) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating); /*Deprecated*/

    /** @brief Set or modify the value of a property of a given
               instance <b>(Deprecated)</b>.

     `CMPIPropertyMIFT.setProperty()` shall set or modify the named property
     value of an instance defined by
     the `instPath` parameter.

     This function is provided by the MI in context of a particular MI name.
         The class of the instPath argument for which this function will be
         called by the MB depends on the specifics of how the MB relates
         classes and MI names, which is out of scope for this standard. As
         a result, the MB may call this function for classes for which the
         MI is not responsible. In order for an MI to be portable across
         MB implementations with different approaches to relate MI names
         and classes, the MI must check whether it services the class
         specified in the instPath argument.
     @param mi Pointer to a CMPIPropertyMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
     for the invocation.
     @param rslt Pointer to a CMPIResult object that is the result data
     container. Upon successful return, the MI shall have left this
     container empty.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that contains the namespace, class name,
         and key components. The hostname component, if present, has no
         meaning and should be ignored.
     @param name Pointer to a string specifying the property name.
     @param data CMPIData structure specifying the value to be assigned
         to the property
     @return CMPIStatus structure indicating the function return
     status. The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_TYPE_MISATCH` - `type` does not correspond
     to class-defined type.
     @li `CMPI_RC_ERR_INVALID_HANDLE` The `inst` handle is
         invalid.
     @todo KS_todo. The list of error codes is very inaccurate

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property client operations in DMTF
     specifications.
     */
    CMPIStatus (*setProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op, const char* name,
            const CMPIData data);

    /** @brief Retrieve property value of a given instance
               <b>(Deprecated)</b>.

     `CMPIPropertyMIFT.getProperty()` shall get the named property value
     of an instance defined by the
         `instPath` parameter.
     @param mi Provider this pointer.
     @param ctx Invocation Context
     @param rslt Pointer to to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the
         retrieved property value into this container (see Subclause 8.2).
         The CMPIResultFT function to be used for that depends on the data
         type of the property, as follows:
         <ul>
         <li>The values of properties declared as embedded instances
            (see Subclause 4.1.3) shall be returned using
            @ref _CMPIResultFT::returnInstance "CMPIResultFT.returnInstance()".
         <li>The values of references (see Subclause 4.1.3) shall be returned
            using @ref _CMPIResultFT::returnObjectPath
            "CMPIResultFT.returnObjectPath()".
         <li>Any other property values shall be returned using
            CMPIResultFT.returnData().
        </ul>
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that contains the namespace, class name,
         and key components. The hostname component, if present, has no
         meaning and should be ignored.
     @param name Pointer to a string specifying the property name
     @return CMPIStatus structure indicating the function return
     status. The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace is
     invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The parameter is invalid.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The CIM class does not exist
        in the specified namespace.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property client operations in DMTF
     specifications.
     */
    CMPIStatus (*getProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* instPath,
            const char* name);

#ifdef CMPI_VER_200

    /** @brief Set or modify the value of a property of a given
               instance <b>(Deprecated)</b>.

     @todo KS_todo resolve what to do about this function.

     `CMPIPropertyMIFT.setPropertyWithOrigin()` shall add/replace a named
     Property value and origin. Removed in CMPI 2.1.
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
     @todo no error codes 
     */
    CMPIStatus (*setPropertyWithOrigin) (CMPIPropertyMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            CMPIObjectPath* instPath, const char* name, const CMPIData data,
            const char* origin);

#endif /*CMPI_VER_200*/

};

/**
 * @}
 * @addtogroup indication-mi
 * @{
 */

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
     * See @ref sym-version-nnn "CMPIVersion{NNN}" for valid CMPI
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

    /** @brief Perform cleanup for an Indication MI.

    `CMPIIndicationMIFT.cleanup()` shall perform any necessary cleanup
    operations prior to the
    unloading of the library of which this MI group is part.

    While this function executes, the MB will not call any other MI functions
    for this MI. This function will be called once for a specific MI
    (unless the MI postpones the cleanup), even if that MI services more
    than one namespace. After this function returns, the MB may unload
    the load library this MI is part of, unless the MI postpones the
    cleanup.
    @param mi Pointer to a CMPIIndicationMI structure.
    @param ctx Pointer to a CMPIContext object containing the context data
        for the invocation (see Subclause 8.1). The context data entries
        are MB implementation-specific.
    @param terminating When true, the MB is in the process of shutting down.
        The MI shall perform any necessary cleanup and shall not postpone
        the cleanup. After this function returns (successful or in error),
        the MB will consider this MI to be uninitialized and will not call
        further MI functions for this MI.

    When false, the MI can choose to perform or postpone the cleanup, by
    performing one of these actions:
    <ul>
    <li>The MI performs any necessary cleanup and does not request postponing
    the cleanup. After this function returns (successful or in error), the
    MB will consider this MI to be uninitialized and will not call further
    MI functions for this MI.
    <li>The MI does not perform any cleanup and temporarily postpones the
    cleanup, by returning CMPI_RC_DO_NOT_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call further
    MI functions of this MI. The MB may call this function again after
    some MB implementation-specific time.
    <li>The MI does not perform any cleanup and permanently postpones the
    cleanup, by returning CMPI_RC_NEVER_UNLOAD. This will cause the MB
    to consider this MI still to be initialized, and the MB may call
    further MI functions of this MI. The MB will not call this function
    again, until the MB terminates (at which time the MB calls this function
    with terminating set to true).
    </ul>

    @return CMPIStatus structure indicating the function return status.
    The following @ref CMPIrc codes shall be recognized:
    @li `CMPI_RC_OK` - Operation successful.
    @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
    @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not
        unload now; the MB may retry an unload later.
    @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
        the MB will not retry an unload later unless it shuts down.
    */
    CMPIStatus (*cleanup) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Ask an MI to verify whether an indication filter is
       supported by the MI.

     `CMPIIndicationMIFT.authorizeFilter()` shall verify whether an
     indication filter is supported by the MI.

     An MB implementation is free to choose whether this function is called
         when the MB starts up independently of whether or not there are
         any subscriptions for the filter, or only when the first
         subscription to the filter is made.

     In any case, for any particular filter this function is called on,
     it shall be called by the MB before
     @ref _CMPIIndicationMIFT::activateFilter
     "CMPIIndicationMIFT.activateFilter()"
     is called for the first time on the same filter.

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext structure containing the
         Invocation Context. There is no defined client operation that
         determines the context data. As a result, not all context data
         entries may be present.
     @param filter Pointer to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is being
         suthorized.
     @param className Pointer to a string specifying the class name extracted
         from the FROM clause of the filter specification contained in the
         filter argument. If the filter specification contains joins, it
         is undefined which of the joined classes is used for this argument.
     @param classPath Pointer to to a CMPIObjectPath object that is a reference
         to a class or to a namespace, as follows:
         <ul>
            <li>If the filter specification covers lifecycle indications,
            the CMPIObjectPath object specifies the class path of the class
            for which lifecycle monitoring is required. Note that this class
            may be a subclass of the class specified in the className argument,
            for example when the filter query constrains the class to be
            monitored using constructs such as the ISA operator of CQL.
            <li>If the filter specification covers process indications,
            the CMPIObjectPath object specifies the namespace path of the
            origin namespace of the process indications.
         </ul>
      @param owner The `owner` argument points to a string
          specifying the destination owner.
      @return This function shall return a structure containing the service
      return status.
      The following @ref CMPIrc codes shall be recognized:
      @li `CMPI_RC_OK` - Operation successful.
      @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
      @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by  
          this
      @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
      @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query or too  
          complex.

      @deprecated The `owner` argument is deprecated since CMPI 2.1.
      MBs may pass an empty string in the owner argument. For
      compatibility reasons, MBs shall not pass a NULL pointer
      in the owner argument.
     */
    CMPIStatus (*authorizeFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx,  const CMPISelectExp* filter,
            const char* className,  const CMPIObjectPath* classPath,
            const char* owner);

    /** @brief Ask the MI whether indication polling should be used
       for an indication filter. <b>(Deprecated)</b>

     `CMPIIndicationMIFT.mustPoll()` asks the MI whether polling mode
     should be used.

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
     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by   
         this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query or too complex.

     @deprecated This function is deprecated since CMPI 2.1,
     because the concept of indication polling has been deprecated in CMPI 2.1.
     */
    CMPIStatus (*mustPoll) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            const CMPISelectExp* filter, const char* className,
            const CMPIObjectPath* classPath);

    /** @brief informs the MI that an indication filter has become
               active.

     `CMPIIndicationMIFT.activateFilter()` informs the MI
     that the specified indication filter has become active. This function
     shall be called by the MB when a client creates a subscription to
     an indication filter, and if persisted subscriptions are supported
     by the MB, for any persisted subscriptions to indication filters
     when the MB starts up.

     An MB implementation is free to choose whether this function
     is called upon each subscription to a particular filter, or only upon
     the first subscription (see the `firstActivation` argument). As a
     result, the MI will always be informed about the first activation of the
     filter after having been inactive, but has no guarantee to be informed
     about subsequent activations of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI needs to start the monitoring of any resources that
     trigger indications that are covered by the specified indication
     filter, during the first activation of the filter. For the concept
     of coverage of indications by an indication filter, see
     @ref ref-dmtf-dsp1054 "DSP1054".

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext structure containing the Invocation
         Context.
     @param filter Pointer to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is activated.
     @param className argument points to a string specifying the class name
         extracted from the FROM clause of the filter specification contained
         in the `filter` argument. If the filter specification contains
         joins, it is undefined which of the joined classes is used for this
         argument.
     @param classPath Pointer to a CMPIObjectPath object that is a
         reference to a class or to a namespace, as follows:
         <ul>
            <li>If the filter specification covers lifecycle indications,
            the CMPIObjectPath object specifies the class path of the class
            for which lifecycle monitoring is required. Note that this class
            may be a subclass of the class specified in the `>className`
            argument, for example when the filter query constrains the
            class to be monitored using constructs such as the `ISA`
            operator of CQL.
            <li>If the filter specification covers process indications,
            the CMPIObjectPath object specifies the namespace path of
            the origin namespace of the process indications.
        </ul>
     `className`.
     @return CMPIStatus structure containing the function return status.
     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation Function or filter 
         is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.Note: This   
         return code indicates general authorization related issues
         and does not specifically indicate that the filter itself
         would not be authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query or too complex.
     @todo in above classname by itself on a line KS_TODO 
     */
    CMPIStatus (*activateFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPISelectExp* filter,
            const char* className, const CMPIObjectPath* classPath,
            CMPIBoolean firstActivation);

    /** @brief Inform the MI that an indication filter has become
               inactive.

     `CMPIIndicationMIFT.deActivateFilter()` informs the MI that monitoring
     using this filter should stop.
         This function shall be called by the MB when a client deletes a
         subscription to an indication filter, and for any existing
         subscriptions to indication filters when the MB shuts down.

     The function invocation mandates the MI to stop monitoring the resource
     using this filter.

     An MB implementation is free to choose whether this function is called
     for each deletion of a subscription to a particular filter, or
     only upon the last deletion (see the `lastDeActivation` argument).
     As a result, the MI will always be informed about the last
     deactivation of the filter, but has no guarantee to be informed
     about prior deactivations of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI should stop the monitoring of any resources that
     trigger indications that are covered by the specified indication
     filter, during the last deactivation of the filter. For the concept
     of coverage of indications by an indication filter, see
     @ref ref-dmtf-dsp1054 "DSP1054".

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext structure containing the
         Invocation Context. If the filter is deactivated
         because a client deletes a subscription to the filter, the client
         operation that deletes the subscription determines the context data.
         If the filter is deactivated during MB shutdown, the client operation
         that originally created the subscription determines the context data
     @param filter Pointer to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is deactivated.
     @param className Pointer to a string specifying the class name extracted
        from the FROM clause of the filter specification contained in the
        `filter` argument. If the filter specification contains joins,
        it is undefined which of the joined classes is used for this argument.
     @param classPath Pointer to a CMPIObjectPath object is a reference to
         a class or to a namespace, as follows:
     <ul>
        <li>If the filter specification covers lifecycle indications, the
        CMPIObjectPath object specifies the class path of the class for which
        lifecycle monitoring is required.  Note that this class may be a
        subclass of the class specified in the className argument, for example
        when the filter query constrains the class to be monitored using
        constructs such as the ISA operator of CQL.
        <li>If the filter specification covers process indications, the
        CMPIObjectPath object specifies the namespace path of the origin
        namespace of the process indications
    </ul>
     @param lastActiviation Set to true if this is the last filter for
     className.
     @return  CMPIStatus structure containing the function return status.
     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by   
         this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query or too   
         complex.
     */
    CMPIStatus (*deActivateFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPISelectExp* filter,
            const char* className, const CMPIObjectPath* classPath,
            CMPIBoolean lastDeActiviation);

    /** @brief Inform the MI that the MB is now ready to process the
           delivery of indications.

    `CMPIIndicationMIFT.enableIndications()` informs the MI that the MB
    is now ready to process the delivery of
        indications. This function is typically called when the MB is starting
        up its indication services (from either a permanent or temporary
        shutdown of its indication services).

        The relative order in which an MB enables indications using this
        function and activates filters and filter collections is not defined.
        As a result, MIs need to track the readiness of the MB to process
        the delivery of indications and check that readiness before calling
        @ref _CMPIBrokerFT::deliverIndication
        "CMPIBrokerFT.deliverIndication()".

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1). There is no defined client
         operation that determines the context data. As a result, not all
         context data entries may be present.
     @return CMPIStatus structure indicating the function return status.
     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by   
         this MI.
     */
    CMPIStatus (*enableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** @brief Inform the MI that the MB is no longer ready to
           process the delivery of indications.

    `CMPIIndicationMIFT.disableIndications()` informs the MI that the MB
    is no longer ready to process the delivery of
        indications.  This function is typically called when the MB is shutting
        down its indication services either temporarily or permanently.

    The relative order in which an MB disables indications using this
        function and deactivates filters and filter collections is not
        defined. As a result, MIs need to track the readiness of the MB
        to process the delivery of indications and check that readiness
        before calling @ref _CMPIBrokerFT::deliverIndication
        "CMPIBrokerFT.deliverIndication()".

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext structure
       containing the Invocation Context.   There is no defined client
       operation that determines the context data. As a result, not all
       context data entries may be present.
     @return CMPIStatus structure containing the function return status.
     The following @ref CMPIrc codes shall be recognized:
     @li `CMPI_RC_OK` - Operation successful.
     @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Operation not supported by   
         this MI.
     */
    CMPIStatus (*disableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** @brief Ask an MI to verify whether an indication filter
           collection is supported by the MI.

     `CMPIIndicationMIFT.authorizeFilterCollection()` shall verify whether an
     indication filter collection is supported by the MI.

    An MB implementation is free to choose whether this function
       is called when the MB starts up independently of whether or not
       there are any subscriptions for the filter collection, or only
       when the first subscription to the filter collection is made.

       In any case, for any particular filter collection this function
       is called on, it shall be called by the MB before
       @ref _CMPIIndicationMIFT::activateFilterCollection
       "CMPIIndicationMIFT.activateFilterCollection()" is called for the
       first time on the same filter collection.
     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
       containing the Invocation Context.   There is no defined client
       operation that determines the context data. As a result, not all
       context data entries may be present.
       @param collInst Pointer to a CMPIInstance object with the
           CIM_FilterCollection instance representing the indication
           filter collection. Note that the indication filter collection
           can be identified by inspecting the CollectionName property
           of this instance
      @return CMPIStatus structure containing the service return status.
        The following @ref CMPIrc codes shall be recognized:
        @li `CMPI_RC_OK` - Function successful, filter collection is supported
           by the MI.
        @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI,
           or filter collection is not supported by this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
            Note: This return code indicates general authorization related
            issues and does not specifically indicate that the filter
            collection itself would not be authorized.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid indication filter
            collection.
     @version Added in CMPI 2.1.
        */
    CMPIStatus (*authorizeFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst);

    /** @brief Inform the MI that an indication filter collection
           has become active.

       `CMPIIndicationMIFT.activateFilterCollection()` informs the
       MI that the specified indication filter collection has become active.
       This function shall be called by the MB when a client creates a
       subscription to an indication filter collection, and if persisted
       subscriptions are supported by the MB, for any persisted subscriptions
       to indication filter collections when the MB starts up.

       An MB implementation is free to choose whether this function is
       called upon each subscription to a particular filter collection, or
       only upon the first subscription (see the `firstActivation`
       argument).

       As a result, the MI will always be informed about the first
       activation of the filter collection, but has no guarantee to be
       informed about subsequent activations of the same filter collection.

       Generally, MIs should disable the monitoring of any resources for
       indications if there is no interest in them. Consequently, in this
       function the MI needs to start the monitoring of any resources that
       trigger indications that are covered by the specified indication
       filter collection, during the first activation of the filter
       collection. For the concept of coverage of indications by an
       indication filter collection, see @ref ref-dmtf-dsp1054 "DSP1054".

       As described in DSP1054, a filter collection conceptually has
       members, but these members do not need to be instantiated using
       CIM. An MB shall handle subscriptions to a filter collection by
       calling `CMPIIndicationMIFT.activateFilterCollection()` for that
       filter collection; the MB shall not additionally call the activation
       functions for the individual members of the filter collection.
       The implementation of `CMPIIndicationMIFT.activateFilterCollection()`
       is responsible for activating the entire filter collection including
       all of its members (regardless of whether or not these members are
       instantiated using CIM).

       @param mi Pointer to a CMPIIndicationMI structure
       @param ctx Pointer to a CMPIContext encapsulated data object containing
           the context data for the invocation (see Subclause 8.1). If the
           filter collection is activated because a client creates a
           subscription to the filter collection, the client operation
           that creates the subscription determines the context data.
           If the filter collection is activated during MB startup on
           behalf of a persisted earlier subscription, the client operation
           that originally created the subscription determines the context
           data.
       @param collInst Pointer to a CMPIInstance object with the
           CIM_FilterCollection instance representing the indication
           filter collection. Note that the indication filter collection
           can be identified by inspecting the CollectionName property
           of this instance.
       @param firstActivation set to true if this is the first activation
           of this indication filter collection after having been inactive,
           and is set to false otherwise
       @return CMPIStatus structure containing the function return
               status. The following @ref CMPIrc codes shall be recognized:
        @li `CMPI_RC_OK` - Function successful.
        @li `CMPI_RC_ERR_FAILED` - Unspecific error occurred.
        @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not
            supported by this MI, or filter collection is not
            supported by this MI.
        @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
        Note: This return code indicates general authorization related issues
            and does not specifically indicate that the filter collection
            itself would not be authorized.
        @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid
            indication filter collection.
       @version Added in CMPI 2.1.
       @todo fix format codes.
       */
    CMPIStatus (*activateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean firstActivation);

    /** @brief Informs the MI that an indication filter collection
       has become inactive.

    `CMPIIndicationMIFT.deActivateFilterCollection()` informs
    the MI that the specified indication filter collection has become
    inactive. This function shall be called by the MB when a client
    deletes a subscription to an indication filter collection, and for
    any existing subscriptions to indication filter collections when
    the MB shuts down.

    This function is called either when a client deletes a subscription
    to an indication filter collection, or when the MB shuts down
    and deactivates a subscription.

    An MB implementation is free to choose whether this function is
    called upon each deletion of a subscription to a particular
    filter collection, or only upon the last deletion
    (see the `lastDeActivation` argument). As a result, the MI will
    always be informed about the last deactivation of the filter
    collection, but has no guarantee to be informed about prior
    deactivations of the same filter collection.

    Generally, MIs should disable the monitoring of any resources for
    indications if there is no interest in them. Consequently, in this
    function the MI should stop the monitoring of any resources that
    trigger indications that are covered by the specified indication
    filter collection, during the last deactivation of the filter. For
    the concept of coverage of indications by an indication filter
    collection, see @ref ref-dmtf-dsp1054 "DSP1054".

    As described in DSP1054, a filter collection conceptually has
    members, but these members do not need to be instantiated using CIM.
    An MB shall handle deletions to subscriptions to a filter collection
    by calling `CMPIIndicationMIFT.deActivateFilterCollection()` for that
    filter collection; the MB shall not additionally call the deactivation
    functions for the individual members of the filter collection.
    The implementation of `CMPIIndicationMIFT.deActivateFilterCollection()`
    is responsible for deactivating the entire filter collection including
    all of its members (regardless of whether or not these members are
    instantiated using CIM).
    @param mi Pointer to a CMPIIndicationMI structure
    @param ctx Pointer to a CMPIContext encapsulated data object containing
       the context data for the invocation (see Subclause 8.1). If the
       filter collection is activated because a client creates a
       subscription to the filter collection, the client operation
       that creates the subscription determines the context data.
       If the filter collection is activated during MB startup on
       behalf of a persisted earlier subscription, the client operation
       that originally created the subscription determines the context
       data.
    @param collInst Pointer to a CMPIInstance object with the
       CIM_FilterCollection instance representing the indication
       filter collection. Note that the indication filter collection
       can be identified by inspecting the CollectionName property
       of this instance.
    @param lastDeactivation set to true if this is the last deactivation
    of this indication filter collection after having been active;
    set to false otherwise.
    @return  CMPIStatus structure containing the service return status.
    The following @ref CMPIrc codes shall be recognized:
    @li `CMPI_RC_OK` -  Function successful.
    @li `CMPI_RC_ERR_FAILED` -  Unspecific error occurred.
    @li `CMPI_RC_ERR_NOT_SUPPORTED` -  Function is not supported by
        this MI, or filter collection is not supported by this MI.
    @li `CMPI_RC_ERR_ACCESS_DENIED` -  Not authorized. Note: This
        return code indicates general authorization related issues and
        does not specifically indicate that the filter collection itself
        would not be authorized.
    @li `CMPI_RC_ERR_INVALID_PARAMETER` -  Invalid indication
        filter collection.
     @version Added in CMPI 2.1.
     */
    CMPIStatus (*deActivateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean lastDeActivation);

};

/**
 * @}
 */

/** @todo KS_todo cmpimacs not required. Removed.
 *        TBD: Can we remove this todo and the include statement?
 #include "cmpimacs.h"
 */

#ifdef __cplusplus
}
#endif

#endif /*_CMPIFT_H_ */
