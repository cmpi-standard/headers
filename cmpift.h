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
 * @defgroup mi-functions MI Functions (Subclause 6)
 * @{
 *   @defgroup instance-mi Instance MI Functions (Subclause 6.3)
 *   @{
 *   @}
 *   @defgroup association-mi Association MI Functions (Subclause 6.4)
 *   @{
 *   @}
 *   @defgroup method-mi Method MI Functions (Subclause 6.5)
 *   @{
 *   @}
 *   @defgroup indication-mi Indication MI support (Subclause 6.6)
 *   @{
 *   @}
 *   @defgroup property-mi Property MI functions (Subclause 6.7) (Deprecated)
 *   @{
 *   @}
 * @}
 * @defgroup mb-capabilities MB Capabilities (Subclause 7.1)
 * @{
 * @}
 * @defgroup mb-edt MB Encapsulated Data Type Support (Subclause 8)
 * @{
 *   @defgroup edt-context CMPIContext Support (Subclause 8.1)
 *   @{
 *     @defgroup def-context-fieldnames Names of CMPIContext fields
 *     @{
 *     @}
 *   @}
 *   @defgroup edt-result CMPIResult Support (Subclause 8.2)
 *   @{
 *   @}
 *   @defgroup edt-string CMPIString Support (Subclause 8.3)
 *   @{
 *   @}
 *   @defgroup edt-array CMPIArray Support (Subclause 8.4)
 *   @{
 *   @}
 *   @defgroup edt-enumeration CMPIEnumeration Support (Subclause 8.5)
 *   @{
 *   @}
 *   @defgroup edt-instance CMPIInstance Support (Subclause 8.6)
 *   @{
 *   @}
 *   @defgroup edt-objectpath CMPIObjectPath Support (Subclause 8.7)
 *   @{
 *   @}
 *   @defgroup edt-args CMPIArgs Support (Subclause 8.8)
 *   @{
 *   @}
 *   @defgroup edt-datetime CMPIDateTime Support (Subclause 8.9)
 *   @{
 *   @}
 *   @defgroup edt-selectexp CMPISelectExp Support (Subclause 8.10)
 *   @{
 *   @}
 *   @defgroup edt-selectcond CMPISelectCond Support (Subclause 8.11)
 *   @{
 *   @}
 *   @defgroup edt-subcond CMPISubCond Support (Subclause 8.12)
 *   @{
 *   @}
 *   @defgroup edt-predicate CMPIPredicate Support (Subclause 8.13)
 *   @{
 *   @}
 *   @defgroup edt-error CMPIError Support (Subclause 8.14)
 *   @{
 *   @}
 *   @defgroup edt-propertylist CMPIPropertyList Support (Subclause 8.15)
 *   @{
 *   @}
 *   @defgroup edt-enumerationfilter CMPIEnumerationFilter Support (Subclause 8.16)
 *   @{
 *   @}
 * @}
 * @defgroup mb-services MB Services (Subclause 9)
 * @{
 *   @defgroup brokerenc-factory Factory Services (Subclause 9.1)
 *   @{
 *   @}
 *   @defgroup brokerenc-misc Miscellaneous Services (Subclause 9.1)
 *   @{
 *   @}
 *   @defgroup mb-tables CMPIBroker and its MB Function Tables (Subclause 9.2)
 *   @{
 *   @}
 *   @defgroup broker-indications Indications Services (Subclause 9.3)
 *   @{
 *   @}
 *   @defgroup broker-client Client Services ("up-calls") (Subclause 9.4 - 9.11)
 *   @{
 *   @}
 *   @defgroup qualifier-services Qualifier Services (Subclause 9.12)
 *   @{
 *   @}
 *   @defgroup broker-thread-reg Thread Registration Services (Subclause 9.13)
 *   @{
 *   @}
 *   @defgroup brokerext-lib OS Encapsulation Services - Library Resolution (Subclause 9.14)
 *   @{
 *   @}
 *   @defgroup brokerext-thread OS Encapsulation Services - POSIX-conformant Threads (Subclause 9.14)
 *   @{
 *   @}
 *   @defgroup brokerext-mutex OS Encapsulation Services - POSIX-conformant Mutexes (Subclause 9.14)
 *   @{
 *   @}
 *   @defgroup brokerext-condition OS Encapsulation Services - POSIX-conformant Conditions (Subclause 9.14)
 *   @{
 *   @}
 *   @defgroup brokermem-all Memory Enhancement Services (Subclause 9.15)
 *   @{
 *   @}
 * @}
 */

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
 * [CMPIBroker object](@ref _CMPIBroker).
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
     *   @addtogroup broker-thread-reg
     *   @{
     */

    /** @brief Prepare the MB to accept a new thread that will use
           MB functions.

     The CMPIBrokerFT.prepareAttachThread() function prepares the CMPI run
     time system to accept a thread that will be using CMPI services.
     The returned CMPIContext object must be used by the subsequent
     attachThread() and detachThread() invocations.
     @param mb Pointer to the broker.
     @param ctx Pointer to the CMPIContext object that was used to invoke
         the MI function that calls this MB function (see Subclause 8.1).
     @return If successful, returns new Context object to be used by thread
         to be attached.

         If not successful, returns NULL.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>

     */
    CMPIContext* (*prepareAttachThread) (const CMPIBroker* mb,
            const CMPIContext* ctx);

    /** @brief Inform the MB that the current thread will begin
           using MB functions.

     The CMPIBrokerFT.attachThread() function informs the CMPI run time
     system that the current thread with <tt>ctx</tt>, Context, will
     begin using CMPI services.
     @param mb Pointer to the broker.
     @param ctx Context object returned by a prior call to
         prepareAttachThread().
     @return CMPIStatus structure indicating the function return status.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The <tt>mb</tt> handle or
        <tt>ctx</tt> handle is invalid.
    </ul>
     */
    CMPIStatus (*attachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /** @brief Inform the MB that the current thread will no longer
               use MB functions.

     This function informs the CMPI run time system that the current thread
     will not be using CMPI services anymore. The Context object will be
     freed during this operation.
     @param mb Pointer to the broker.
     @param ctx Context object returned by a prior call to
         prepareAttachThread().
     @return CMPIStatus structure indicating the function return status.

   The function return status indicates one of the following:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The <tt>mb</tt> handle or
        <tt>ctx</tt> handle is invalid.
    </ul>
     */
    CMPIStatus (*detachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /**
     *   @}
     *   @addtogroup broker-indications
     *   @{
     */

    /** @brief Request delivery of an indication.

     The CMPIBrokerFT.deliverIndication() function requests delivery of an
     indication. The MB will locate pertinent subscribers and notify
     them about the event.

     This function may be called by an MI regardless of whether or not there
     are any active indication filters or indication filter collections
     that cover the indication to be delivered. If there are no such filters
     or filter collections, this will not cause the function to fail. For
     the concept of coverage of indications by an indication filter or
     indication filter collection, see DSP1054.

     This function may be called by an MI regardless of whether or not
     the MB is ready for processing the delivery of indications, as
     communicated to the MI via CMPIIndicationMIFT.enableIndications()
     and  CMPIIndicationMIFT.disableIndications(). If the MB is not
     ready for processing the delivery of indications, this will not
     cause the function to fail. The MB implementation may choose to
     drop the indication in this case, or to queue the indication for
     later delivery.

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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful. Note: If the MB is not
            ready for processing the delivery of indications, it may drop
            the indication and still return success.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
        by the MB.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The handle specified by
        the ind argument is invalid.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The namespace specified
        by the <tt>ns</tt> argument is invalid, or the indication instance
        specified by the <tt>ind</tt> argument is invalid.
     </ul>
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

     The CMPIBrokerFT.enumerateInstanceNames() function enumerates
     instance names of the class (and subclasses) defined by
         <tt>classPath</tt>.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function
         that calls this MB function (see Subclause 8.1). Any
         invocation flags in the <tt>ctx</tt> argument will be ignored
         by this function.
     @param classPath Pointer to a CMPIObjectPath object that references
         the given class and that shall contain the namespace and
         class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful returns pointer to a new CIMEnumeration
         object containing CMPIObjectPaths objects that represent the
         enumerated instance paths. The new object will be released
         automatically by the MB.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified in
    the <tt>classPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <tt>classPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
    handle.
    </ul>

    Extended error handling is not supported by this MB function;
    thus, any CMPIError objects returned by the targeted MI cannot
    be made available to the calling MI
     */
    CMPIEnumeration* (*enumerateInstanceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            CMPIStatus* rc);

    /** @brief Get a given instance.

     The CMPIBrokerFT.getInstance() function gets  anInstance using
     <tt>instPath</tt> as reference. Instance structure can be controled
     using the CMPIInvocationFlags in <tt>ctx</tt>.

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
    the MI shall not use CMPIBrokerMemFT.freeInstance() on the new object.

    If not successful, returns NULL.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by
    this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
    in the <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The property list specified
        in the <tt>properties</tt> argument is invalid.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>

    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI.
     */

    CMPIInstance* (*getInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char** properties,
            CMPIStatus* rc);

    /** @brief Create an instance of a given class.

     The CMPIBrokerFT.createInstance() function creates an instance
     of a given class. The target MI is identified by the MB based
     on the classPath argument function creates an instance of a
     given class in the namespace of that class, by creating the
     underlying managed elements.

     @param mb Pointer to the broker.
     @param ctx <tt>CMPIContext</tt> object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the ctx argument will be ignored by this function.
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
         shall not use CMPIBrokerMemFT.freeObjectPath() on the new object.

        If not successful, returns NULL.

        The function return status will indicate one of the following
            CMPIrc codes:
        <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
        by this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
        in the classPath argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        classPath argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The instance specified
        in the inst argument is invalid.
        <li><tt>CMPI_RC_ERR_ALREADY_EXISTS</tt>	Instance already exists.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data
        type handle.
        </ul>

        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     */
    CMPIObjectPath* (*createInstance) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const CMPIInstance* newInst, CMPIStatus* rc);

    /** @brief Modify property values of a given instance.

     The CMPIBrokerFT.modifyInstance() function modifies property values
     of a given instance. The target MI is identified by the MB based on
     the <tt>instPath</tt> argument.

     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the ctx argument will be ignored by this function.
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

        The function return status indicates one of the following CMPIrc codes:
        <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not
            supported by this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>instPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in
            the <tt>instPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The instance specified
             in the <tt>modInst argument</tt>, or the properties specified in
             propertyList are invalid.
        <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
        data type handle.
        </ul>

        Extended error handling is not supported by this MB function; thus,
            any CMPIError objects returned by the targeted MI cannot be made
            available to the calling MI
     @todo Review this description.
     */

    CMPIStatus (*modifyInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const CMPIInstance* modInst,
            const char** properties);

    /** @brief delete a given instance.

     The CMPIBrokerFT.deleteInstance() function deletes a given instance.
     The target MI is identified by the MB based on the <tt>instPath</tt>
     argument.

     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the ctx argument will be ignored by this function.
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB.
     @return CMPIStatus structure indicating the function return status.

        The function return status indicates one of the following CMPIrc codes:
        <ul>
        <li> <tt>CMPI_RC_OK</tt>	Function successful.
        <li> <tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li> <tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
            by this MI.
        <li> <tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li> <tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>instPath</tt> argument does not exist.
        <li> <tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in
            the <tt>instPath</tt> argument does not exist.
        <li> <tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
        <li> <tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
        data type handle.
        </ul>
        Extended error handling is not supported by this MB function; thus,
            any CMPIError objects returned by the targeted MI cannot be made
            available to the calling MI
    */
    CMPIStatus (*deleteInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath);

    /** @brief execute a query on a given class and return the query
               result.

     The CMPIBrokerFT.execQuery() function executes a query on a given
     class and returns the query result. The target MI is identified by
     the MB based on the classPath argument.
     by <tt>op</tt> using <tt>query</tt> expression.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
         principal, role, accept language, and content language as the
         CMPIContext object that was used to invoke the MI function that
         calls this MB function (see Subclause 8.1). Any invocation flags
         in the ctx argument will be ignored by this function.
     @param classPath Pointer to to a CMPIObjectPath object that references
         the given class to be queried and that shall contain the namespace
         and class name components. The hostname and key components,
         if present, will be ignored by the MB..
     @param query Pointer to to a string containing the select expression
     @param lang Pointer to to a string containing the query language
     @param rc Output: if not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return If successful, returns a pointer to a new CMPIEnumeration object, containing CMPIInstance objects that represent the query result.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release
     the new object.

     If not successful, NULL will be returned.

     The function return status indicates one of the following:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecified error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified in
        the <tt>classPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <tt>classPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED</tt> Query language not
        supported.
    <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt>	Invalid query.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI.
     */
    CMPIEnumeration* (*execQuery) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const char* query, const char* lang, CMPIStatus* rc);

    /** @brief Enumerate the instances of a given class (and its
               subclasses).

     The CMPIBrokerFT.enumerateInstances() function enumerates the
     instances of a given class (and its subclasses). The set of properties
     in the result instances can be controlled using the
     LocalOnly and DeepInheritance flags in the CMPIInvocationFlags
     entry in <tt>ctx</tt> and the properties argument. The target MIs
     are identified by the MB based on the <tt>classPath</tt> argument.

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
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful returns a pointer to a new CMPIEnumerationObject
          containing CMPIInstance objects that represent the enumerated
          instances. The new object will be released automatically by the MB.

          If not successful returns NULL.

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
            by this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the classPath argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
            classPath argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The property list
            specified in the properties argument is invalid.
        <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>
    Extended error handling is not supported by this MB function; thus,
    any CMPIError objects returned by the targeted MI cannot be made
    available to the calling MI
     */
    CMPIEnumeration* (*enumerateInstances) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* classPath,
            const char** properties, CMPIStatus* rc);

    /** @brief Enumerate the instances associated with a given source instance.


     The CMPIBrokerFT.associators() function enumerates the instances
     associated with a given source instance. The target MIs are identified
     by the MB based on the <tt>instPath</tt> argument.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the same
     principal, role, accept language, and content language as the
     CMPIContext object that was used to invoke the MI function that
     calls this MB function (see Subclause 8.1). Any invocation flags
     in the ctx argument will be ignored by this function.
     @param instPath Pointer to a CMPIObjectPath object that references
     the given source instance and that shall contain the namespace,
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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by this
        MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified in the
    <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The <tt>assocClass</tt>,
        <tt>resultClass</tt>, <tt>role</tt>, <tt>resultRole</tt>, or
        <tt>properties</tt> arguments are invalid.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found. Instead of using
        this return code if the source instance does not exist, the MB should
        return success with an empty result set. The MI shall treat this
        return code as a successful return of an empty result set.
        <b>(Deprecated)</b>
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
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

     The CMPIBrokerFT.associatorNames() function enumerates the instance
        paths of the instances associated with a given source instance.
        The target MIs are identified by the MB based on the
        <tt>instPath</tt> argument.
     @param mb Pointer to the broker.
     @param ctx Pointer to a CMPIContext object that specifies the*
     same principal, role, accept language, and content language as*
     th* e CMPIContext object that was used to invoke the MI*
     function that* calls this MB function (see Subclause 8.1). Any*
     invocation flags* in the ctx argument will be ignored by this*
     function.**
     @param instPath Pointer to to a CMPIObjectPath object that references
         the given source instance and that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.

         If the source instance does not exist, this function shall either return
         success with an empty result set or
         CMPI_RC_ERR_NOT_FOUND.<b>(Deprecated) </b>.
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
     @param rc Output:  If not NULL, points to a CMPIStatus structure that
        upon return has been updated with the function return status.
     @return  if not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
        by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
        in the <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <tt>instPath</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The <tt>assocClass</tt>,
        <tt>resultClass</tt>, <tt>role</tt>, or <tt>resultRole</tt> arguments
        are invalid.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
    Instead of using this return code if the source instance does not exist,
    the MB should return success with an empty result set. The MI shall
    treat this return code as a successful return of an empty result set.
        <b>(Deprecated)</b>
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data
        type handle.
    </ul>
    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.
     */

    CMPIEnumeration* (*associatorNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* instPath,
            const char* assocClass, const char* resultClass, const char* role,
            const char* resultRole, CMPIStatus* rc);

    /** @brief enumerate the association instances referencing a given
       source instance.

     The CMPIBrokerFT.references() function Enumerates the
     association instances that refer to the instance defined
     by <tt>op</tt>.

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
     @return If successful, returns a pointer to a new CMPIEnumeration,
     containing CMPIInstance objects that represent the enumerated instances.

     The new object will be released automatically by the MB, as described
     in Subclause 4.1.7. There is no function to explicitly release the
     new object.

     If not successful, returns NULL.

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by
            this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>instPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
            <tt>instPath</tt> argument does not exist.
            <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The <tt>assocClass</tt>,
            <tt>resultClass</tt>, <tt>role</tt>, or <tt>resultRole</tt>
            arguments are invalid.
        <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found. Instead of
            using this return code if the source instance does not exist, the
            MB should return success with an empty result set. The MI shall
            treat this return code as a successful return of an empty
            result set. <b>(Deprecated)</b>.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
            handle.
        </ul>
        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     */
    CMPIEnumeration* (*references) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, const char** properties,
            CMPIStatus* rc);

    /** @brief enumerate the instance paths of the association instances
       referencing a given source instance.

     The CMPIBrokerFT.referenceNames() function enumerates the instance
     paths of the association instances referencing a given source
     instance. The target MIs are identified by the MB based on
     the <tt>instPath</tt> argument.
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
     @return If successful, returns a pointer to a new CMPIEnumeration object,
     containing CMPIObjectPath objects that represent the enumerated
     instance paths.

    The new object will be released automatically by the MB, as described
    in Subclause 4.1.7. There is no function to explicitly release the
    new object.

    If not successful, returns NULL.

    The function return status will indicate one of the following CMPIrc codes:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by
            this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>instPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
            <tt>instPath</tt> argument does not exist.
            <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The <tt>assocClass</tt>,
            <tt>resultClass</tt>, <tt>role</tt>, or <tt>resultRole</tt>
            arguments are invalid.
        <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found. Instead of
            using this return code if the source instance does not exist, the
            MB should return success with an empty result set. The MI shall
            treat this return code as a successful return of an empty
            result set. <b>(Deprecated)</b>.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
            handle.
        </ul>
        Extended error handling is not supported by this MB function; thus,
        any CMPIError objects returned by the targeted MI cannot be made
        available to the calling MI.
     */
    CMPIEnumeration* (*referenceNames) (const CMPIBroker* mb,
            const CMPIContext* ctx, const CMPIObjectPath* op,
            const char* resultClass, const char* role, CMPIStatus* rc);

    /** @brief  invoke a method on a target object.

     The CMPIBrokerFT.invokeMethod() function invokes a named, extrinsic
         method on a target object. Instance methods (i.e., non-static methods)
         can be invoked only on instances. Class methods (i.e., static methods)
         can be invoked on instances and classes. The target MI is
         identified by the MB based on the <tt>objPath</tt> argument.

     @param mb Pointer to the broker.
     @param ctx Context object
     @param objPath ObjectPath containing namespace, classname and key
     components.
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

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Invocation of extrinsic
            methods is not supported by the MB (that is, the Instance
            Manipulation capability is not available; see Subclause 7.1).
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>objPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
            <tt>objPath</tt> argument does not exist.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The method parameters
            specified in the in or out arguments are invalid.
        <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Instance not found.
        <li><tt>CMPI_RC_ERR_METHOD_NOT_AVAILABLE</tt> The extrinsic method is
            not supported by the targeted MI.
        <li><tt>CMPI_RC_ERR_METHOD_NOT_FOUND</tt>	Method not defined
            in the class.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>

    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.
     */
    CMPIData (*invokeMethod) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* objPath, const char* method,
            const CMPIArgs* in, CMPIArgs* out, CMPIStatus* rc);

    /** @brief Set a property of a given instance <b>(Deprecated)</b>.

     Set the named property value of an instance defined by the
     <tt>instPath</tt> parameter.*

     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname and
         key components.
     @param name Property name
     @param value Value.
     @param type Value type.
     @return CMPIStatus structure indicating the function return status .

    The function return status indicates one of the following:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
        in <tt>instPath</tt> is invalid.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <TT>instPath</TT> argument does not exist.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	The class specified in
        <tt>instPath</tt> is not found.
    <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt>	Property not found.
    <li><tt>CMPI_RC_ERR_TYPE_MISMATCH</tt>	Value types incompatible.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property
     client operations in DMTF specifications. MBs shall implement
     the CMPIBrokerFT.setProperty() function by invoking the
     modifyInstance() MI function if the setProperty() MI function
     is not implemented by the target MI. New MIs should
     replace the use of CMPIBrokerFT.setProperty() with the use of
     CMPIBrokerFT.modifyInstance().
     */
    CMPIStatus (*setProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief Get the named property of a given instance <b>(Deprecated)</b>.

     Get the named property value of an Instance defined by the
     <tt>instPath</tt> parameter.
     @param mb Pointer to the broker.
     @param ctx Context object
     @param instPath ObjectPath containing namespace, classname
      and key components.
     @param name Property name
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, Property value. If not successful
         CMPIData.state will have CMPI_BadValue flag set to true

    The function return status indicates one of the following:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
        in <tt>instPath</tt> is invalid.
    <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt>	The class specified in the
        <TT>instPath</TT> argument does not exist.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	The class specified in
        <tt>instPath</tt> is not found.
    <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt>	Property not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
    Extended error handling is not supported by this MB function; thus, any
    CMPIError objects returned by the targeted MI cannot be made available
    to the calling MI.

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property
     client operations in DMTF specifications. MBs shall implement
     the CMPIBrokerFT.getProperty() function by invoking the
     getInstance() MI function if the getProperty() MI function
     is not implemented by the target MI. New MIs should replace
     the use of CMPIBrokerFT.getProperty() with the use of
     CMPIBrokerFT.getInstance()
     */
    CMPIData (*getProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
            const CMPIObjectPath* instPath, const char* name, CMPIStatus* rc);

    /**
     *   @}
     */

};

/**
   @brief Function table for MB factory and miscellaneous services of
    [CMPIBroker object](@ref _CMPIBroker).

   The CMPIBrokerEncFT function table provides factory services for the CMPI
   data types, and functions for test, conversion, tracing and logging.

   The CMPIBrokerEncFT is the function table used as an anchor for these
   services. It is made available to MI via the
   <tt>\<mi name\>_Create_\<mi type\>MI()</tt> functions.

   For functions that are not supported, their function pointers in the
   CMPIBrokerEncFT function table shall not be NULL, but shall point to
   a function that can be called and then indicate back to the caller that
   it is not supported, as specified in the description of the function.
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
     *   @addtogroup brokerenc-factory
     *   @{
     */

    /** @brief Create a new CMPIInstance object initialized to a
           given instance path.

     The CMPIBrokerEncFT.newInstance() function creates a new CMPIInstance
     object. The new object should have no properties. The purpose
     of class-defined derault values for properties is to act as
     defaults for unspecified input properties when a client
     creates an instance, not to act as defualts for not explicity
     set properties when a client retrieves an instance.

     @param mb Pointer to the broker.
     @param instPath ObjectPath containing namespace and classname.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created instance. if
         not successful returns NULL.

     The new object will be automatically released by the MB.
     If the new object is no longer used by the MI, it
     may be explicitly released by the MI using CMPIBrokerMemFT.freeInstance().

     The function return status indicates one of the following:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
        in <tt>instPath</tt> is invalid.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	The class specified in
        <tt>instPath</tt> is not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
     */
    CMPIInstance* (*newInstance) (const CMPIBroker* mb,
            const CMPIObjectPath* instPath, CMPIStatus* rc);

    /** @brief Create a new CMPIObjectPath initialized to a given
           namespace and class name

     The CMPIBrokerEncFT.newObjectPath() function creates a new
         CMPIObjectPath object that is initialized to a given namespace
         and class name.
     @param mb Pointer to a CMPIBroker object.
     @param ns Pointer to a string specifying the namespace name.
     @param cn Pointer to a string specifying the class name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created
         CMPIObjectPath. If not successful returns NULL.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt>	The namespace specified
            in the <tt>ns</tt> argument does not exist.
    <li><tt>CMPI_RC_ERR_NOT_FOUND</tt>	Class in <tt>cn</tt> not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
        data type handle.
    </ul>
     */
    CMPIObjectPath* (*newObjectPath) (const CMPIBroker* mb, const char* ns,
            const char* cn, CMPIStatus* rc);

    /** @brief Create a new CMPIArgs object initialized to have no
           method parameters.

     Args container factory service to create a new CMPIArgs
     object with no method parameters
     @param mb Pointer to the broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns the newly created CMPIArgs
             object. If not successful returns NULL.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
        data type handle.
    </ul>
     */
    CMPIArgs* (*newArgs) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Create a new CMPIString object initialized from a
           C-language string.

     The CMPIBrokerEncFT.newString() function creates a new CMPIString
         object that is initialized from a C-language string.
     @param mb Pointer to the broker.
     @param data String data
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns the newly created CMPIString. If
         not successful returns NULL.

     The new object will be automatically released by the MB. If the new
     object is no longer used by the MI, it may be explicitly released
     by the MI using CMPIBrokerMemFT.freeString().

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>
     */
    CMPIString* (*newString) (const CMPIBroker* mb, const char* data,
            CMPIStatus* rc);

    /** @brief Create a new CMPIArray object of a given fixed array
          size for a given type of elements.

     Array container factory service returns a new CMPIArray
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

     The new object will be automatically released by the MB, as described in Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using CMPIBrokerMemFT.freeArray().

    If not successful, NULL will be returned.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_DATA_TYPE</tt>	Data type not valid.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>
     */
    CMPIArray* (*newArray) (const CMPIBroker* mb, CMPICount size,
            CMPIType type, CMPIStatus* rc);

    /** @brief Create a new CMPIDataTime object with current date
       and time.

     The CMPIBrokerEncFT.newDateTime() function creates a new CMPIDateTime
         object that is initialized with the current date and time.

     @param mb Pointer to the broker.
     @param rc Output: if not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful, returns a pointer to the new CMPIDateTime object.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. If the new object is no longer used by the MI,
     it may be explicitly released by the MI
     using CMPIBrokerMemFT.freeDateTime().

     If not successful, NULL will be returned.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>
     */
    CMPIDateTime* (*newDateTime) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Create a new CMPIdateTime object initialized to a
         specific value.
     The CMPIBrokerEncFT.newDateTimeFromBinary() function creates a new
         CMPIDateTime object that is initialized with the specified
         date and time from argument <tt>binTime</tt>.

     @param mb Pointer to the broker.
     @param binTime When interval is false, the <tt>binTime</tt> argument
         contains a point in time value expressed as a 64-bit unsigned integer
         in microseconds since 00:00:00 GMT, January 1, 1970. Otherwise,
         the <tt>binTime</tt> argument contains a time interval expressed as
         a 64-bit unsigned integer in microseconds
     @param interval When true, defines <TT>binTime</tt> definition to be
     an interval value.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to the new CMPIDateTime object.

     The new object will be automatically released by the MB, as described
     in Subclause 4.1.7. If the new object is no longer used by the MI,
     it may be explicitly released by the MI
     using CMPIBrokerMemFT.freeDateTime().

     If not successful, returns NULL.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>

     */
    CMPIDateTime* (*newDateTimeFromBinary) (const CMPIBroker* mb,
            CMPIUint64 binTime, CMPIBoolean interval, CMPIStatus* rc);

    /** @brief Create a new CMPIDateTime object initialized from input.

     The CMPIBrokerEncFT.newDateTimeFromChars() function creates a new
     CMPIDateTime object that is initialized with the the argument
     <tt>utcTime</tt>, the specified date and time.

     @param mb Pointer to the broker.
     @param datetime Date/Time definition in CIM datetime string format.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a pointer to the new CMPIArray object.

     The new object will be automatically released by the MB,
     as described in Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using CMPIBrokerMemFT.freeDateTime().

    If not successful, NULL will be returned.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_INVALID_PARAMETER</tt>	The utcTime format is invalid.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated
            data type handle.
    </ul>
     */
    CMPIDateTime* (*newDateTimeFromChars) (const CMPIBroker* mb,
            const char* datetime, CMPIStatus* rc);

    /** @brief Create a new CMPISelectExp object initialized from a
       select expression.

     The CMPIBrokerEncFT.newSelectExp() function creates a new CMPISelectExp
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
         object of CMPIString entries containing the projection specification.
         The pointer will be set to NULL if no projection was specified in
         the select expression. The projection specification is query
         language-specific. Hence the entries format of the projection
         output array CMPIString might be different depending on the query
         language. Be sure to check the lang argument for the query
         language your MI will support.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return will have been updated with the function return status.
     @return If successful,returns a pointer to the new CMPIArray object.

     The new object will be automatically released by the MB,
     as described in Subclause 4.1.7.
     If the new object is no longer used by the MI, it may be explicitly
     released by the MI using CMPIBrokerMemFT.freeDateTime().

    If not successful, NULL will be returned.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by
            the MB.
        <li><tt>CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED</tt>  The query
        language is not supported.
        <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt>	The query expression is not
            valid.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid <tt>mb</tt> handle.
    </ul>
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

     Function to determine whether a <tt>className</tt> is of
     <tt>classPath</tt> or any of <tt>classPath</tt> subclasses.
     @param mb Pointer to the broker.
     @param classPath The class path (namespace and classname components).
     @param char className
     @param rc Output: Service return status (suppressed when NULL).
     @return True if test successful.

     @todo add status codes
     @todo Review this description - it was a complete change.
     */
    CMPIBoolean (*classPathIsA) (const CMPIBroker* mb,
        const CMPIObjectPath* classPath, const char* className,
        CMPIStatus* rc);

    /** @brief Convert CMPIEncapsulated data type object int a
           string representation.

     Attempts to transforms an CMPI object to a broker specific
       string format. Intended for debugging purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns CMPIString from representation
         of <tt>object</tt>. If not successful returns NULL.

     @todo add status codes
     */
    CMPIString* (*toString) (const CMPIBroker* mb,
        const void* object, CMPIStatus* rc);

    /** @brief Tests whether a CMPI encapsulated data type object is
           of a specified CMPI type.

     Verifies whether <tt>object</tt> is of CMPI type <tt>type</tt>.
     Intended for debugging purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param type A string specifying a valid CMPI Object type
     ("CMPIInstance", "CMPIObjectPath", etc).
     @param rc Output: Service return status (suppressed when NULL).
     @retval True: test successful
     @retval False; test unsuccesful.

     @todo add status codes
     */
    CMPIBoolean (*isOfType) (const CMPIBroker* mb,
        const void* object, const char* type, CMPIStatus* rc);

    /** @brief Get the type name of a CMPI ensapsulated data type
     *         object.
     *
     * Retrieves the CMPI type of <tt>object</tt>. The returned
     * CMPIString object shall not be explicitly released by the MI,
     * because it may be an internal object of the CMPI encapsulated
     * data type object which will be released along with that
     * object, or a new object created by the MB which will be
     * released automatically by the MB. Intended for debugging
     * purposes only.
     @param mb Pointer to the broker.
     @param object A valid CMPI object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful returns CMPI object type. Otherwise
     *       returns NULL.
     *
     @todo add status codes
     */
    CMPIString* (*getType) (const CMPIBroker* mb,
        const void* object, CMPIStatus* rc);

    /** @brief Get translated MB implementation specific message text
       <b>(Deprecated)</b>.

     Retrieves translated message defined by <tt>msgId</tt>

     Use CMPIBrokerEncFT.getMessage2() in place of this function.
     @param mb Pointer to the broker.
     @param msgId The message identifier.
     @param defMsg The default message. Used when message
         translation is not supported
     @param rc Output: Service return status (suppressed when NULL).
     @param count The number of message substitution values.
     @return If successful returns the translated
         message.Otherwise returns NULL.

     @todo add status codes
     */
    CMPIString* (*getMessage) (const CMPIBroker* mb,
        const char* msgId, const char* defMsg, CMPIStatus* rc,
        CMPICount count, ...);

    /** @brief Log a diagnostic message.

     This function logs a diagnostic message defined by the input
     arguments. It exists to provide a mechanism to MIs to
     provider information about errors, status, etc.
     This function is supported by the MB if the Logging
     capability is available.@param mb The mb argument points to a
     CMPIBroker structure.
     @param severity  The level argument describes the level of
         logmessage. Levels are defined in Subclause 4.9.
     @param id The component argument, if not NULL, is the component ID.
     @param text  The text argument, if not NULL, is the message text to be
     logged.
     @param string The string argument, if not NULL, is the message text to be
         logged. string will be ignored when text is not NULL.
     @return Service return status.

     @todo add status codes
     */
    CMPIStatus (*logMessage) (const CMPIBroker* mb,
        int severity, const char* id, const char* text,
        const CMPIString* string);

    /** @brief Trace a diagnostic message with a specific trace
           level and component definition.

     Logs a trace entry. Intended for debugging purposes.
     This function is supported by the MB if the Tracing
     capability is available.
     @param mb Pointer to to a CMPIBroker structure.
     @param level  Describes the level of log message.
         Levels are defined in Subclause 4.9.
     @param component If not NULL, is
         the implementation specific component ID.
     @param text  If not NULL, is the message text to be
         output.
     @param string If not NULL, is the message text to
        be output. string will be ignored when text is not NULL.
     @return Service return status.
     @todo add status codes
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

     The CMPIBrokerEncFT.newCMPIError() function creates a new CMPIError
     object that is initialized with certain core attributes.

     The input data may (or may not) be defined in a DMTF message
     registry (see DSP0228 for the format of message registries,
     and DSP8016 for the messages defined for the MI functions of CMPI).

     @param mb Pointer to the broker.
     @param owner A string specifying the value for the OwningEntity attribute
     @param msgID A string which uniquely identifies the
         MessageID attribute of the CMPIError object For a description of
         the MessageID attribute, see the description of the
         MessageID property in the CIM_Error class in the CIM
         Schema. If the error message is defined in a DMTF message
         registry, the string value of the msgID argument shall be
         the message ID defined for the message in the registry
         (that is, the concatenation of the values of the PREFIX and
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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The mb argument is invalid.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	One of the parameters is
            invalid.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported
        by the MB. In CMPI 2.1, this return code has been deprecated; It
        will not be returned because the Extended Errors capability will
        be available. <b>(Deprecated)</b>
        <li><tt>CMPI_RC_ERR_FAILED</tt>	A generic error occurred.
    </ul>

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

    /** @brief Open a message file and return a handle to the file
     * Opens a message file.
     @param mb pointer to the broker
     @param msgFile The message file identifier.
     @param msgFileHandle Output: The handle representing the open message file.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*openMessageFile) (const CMPIBroker* mb,
        const char* msgFile,
        CMPIMsgFileHandle* msgFileHandle);

    /** @brief Close a message file.
     *
     * Closes a message file previously opened by
     * CMPIBrokerEncFt.openMessageFile(). If the message file handle
     * is NULL, the message file is not closed and this is not
     * considered a failure.
     @param mb Broker this pointer
     @param msgFileHandle The handle representing the open message file.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*closeMessageFile) (const CMPIBroker* mb,
        const CMPIMsgFileHandle msgFileHandle);

    /** @brief Get a translated message text from an open message
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
     @todo add status codes
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
     *         list of property names
     *
     * This function creates a new CMPIPropertyList that is
     * initialized to a list of property names specified by
     * <tt>properties</tt>
     * @param mb pointer to the broker
     * @param properties pointer to the first entry of a
     *                   NULL-terminated array of pointers to C
     *                   strings that specify the property names for
     *                   the property list.
     * @param rc Output: Service return status (suppressed when
     *           NULL).
     * @return KS_todo
     @todo add status codes
     @todo add return description
     */
    CMPIPropertyList* (*newPropertyList) (const CMPIBroker* mb,
            const char** properties, CMPIStatus* rc);

    /** @brief Create a new CMPIString object from a C-language
              string in a specific codepage.

       The CMPIBrokerEncFT.newStringCP() function creates a new
       CMPIString object that is initialized from a C-language
       string in a specific codepage

       @param mb Pointer to to a CMPIBroker object.
       @param data Pointer to to a string that is represented in the
       codepage specified in the cpid argument. The data argument
           is used to initialize the new CMPIString object after
           converting it from its codepage to UTF-8.
       @param cpid specifies the CMPI-specific codepage ID for the
           codepage that is used to interpret the Bytes in the data
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
          CMPIBrokerMemFT.freeString().

          If not successful, NULL will be returned.

         The function return status will indicate one of the following
            CMPIrc codes:
         <ul>
            <li><tt>CMPI_RC_OK</tt>	Function successful.
            <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The mb handle is invalid.
            <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	The cpid argument is
                invalid.
            <li><tt>CMPI_RC_ERR_NOT_IN_CODEPAGE</tt>	The string in the
                data argument contains characters that are invalid for
                the codepage specified in the cpid argument
                (e.g., 7-bit US-ASCII), or that cannot be represented in UTF-8.
        </ul>
       @version Added in CMPI 2.1
     */
    CMPIString* (*newStringCP) (const CMPIBroker* mb, const char* data,
            const CMPICodepageID cpid, CMPIStatus* rc);

    /** @brief  Create a new CMPIEnumerationFilter object initialized
           with a filter query.

     The CMPIBrokerEncFT.newEnumerationFilter() function creates a new
     CMPIEnumerationFilter object initialized with
       <tt>filterquery</tt> argument if the
       <tt>filterQueryLanguage</tt> argument is valid. If the
       <tt>filterquery</tt> is NULL the new object will be set to do
       no filtering.
     @param mb Pointer to a CMPIBroker object
     @param filterQueryLanguage Pointer to a string specifying the query
         language used for the filterQuery argument. If this argument is
         NULL, the new CMPIEnumerationFilter object will be set
         to define that no filtering is to be performed.
     @param filterQuery Pointer to a string specifying a valid query
         in the query language defined by the filterQueryLanguage argument.
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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Operation successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The <tt> mb</tt> handle
         is invalid.
    <li><tt>CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED</tt> The
        <tt>filterQueryLanguage</tt> argument defines a query language
        that the MI does not recognize.
    <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt>	The <tt>filterQuery</tt> is not
        a valid query in the specified filter query language
    <li><tt>CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED</tt> A feature of the
        query language is not supported.
    </ul>
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
     *   @addtogroup brokerext-lib
     *   @{
     */

    /** @brief Resolve a generic load library name to its file name.

     This function complements a generic dynamic library name to its
         OS-dependent native format.
     @param filename Pointer to the generic library name,
     @return The returned char* pointer to the complemented library
         name in native OS format.
     Space for this string has been obtained using <tt>malloc()</tt> and must
         be released using <tt>free()</tt> by the caller.
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

     Start a new thread using the POSIX threading semantics.
     @param start Pointer to the function to be started as a thread.
     @param parm Pointer to argument(s) to be passed to that function.
     @param detached If not zero, defines that the thread should run
         in detached mode. In detached mode, termination of the
         thread that called this function does not cause the new
         thread to be canceled. See IEEE 1003.1 for details on
         detached mode.
     @return If successful, the handle of the started thread will be returned.
         If not successful, returns NULL.
     */
    CMPI_THREAD_TYPE (*newThread)
            (CMPI_THREAD_RETURN (CMPI_THREAD_CDECL* start)(void*),
            void* parm, int detached);

    /** @brief Wait until the specified thread ends.

     Suspends the current thread until the specified thread ends using
         the POSIX threading semantics.
     @param thread The thread ID of the thread waiting for completion.
     @param retval Pointer to the return value of the thread.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.

    The Error codes are defined in <errno.h>, specifically for
    the <tt>pthread_join()</tt> function; both are defined in IEEE 1003.1.
     @todo add status codes
     */
    int (*joinThread) (CMPI_THREAD_TYPE thread, CMPI_THREAD_RETURN* retval);

    /** @brief Cause current thread to exit with the passed-in return code,

    Causes the current thread to exit with the passed in return
       code using POSIX threading semantics.

    The current thread can also exit by simply returning from its thread
     function; the purpose of the
     <tt>CMPIBrokerExtFT.exitThread()</tt> function is to make
     premature returns more convenient.
     @param return_code Is the return code that should be used for the thread.
     @return The function never returns, regardless of whether it is
         successful or encounters errors.
     @todo add status codes
     */
    int (*exitThread) (CMPI_THREAD_RETURN return_code);

    /** @brief Cancel a running thread.

     Cancel the thread using the POSIX threading semantics.
     @param thread  The thread to be canceled.
     @return Completion code as defined by POSIX threading semantics
     (pthread_cancel)
     @todo add status codes
     */
    int (*cancelThread) (CMPI_THREAD_TYPE thread);

    /** @brief Suspend execution of current thread for a specified duration.

     Suspends the execution of the current thread for the specified duration.
     @param msec The suspend duration in milliseconds.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.
     @todo add status codes

     */
    int (*threadSleep) (CMPIUint32 msec);

    /** @brief Call a function once for a given once-object.

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
     @param once Pointer to the <tt>int</tt> once object.
     @param function The function to be called
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned.
     @todo add status codes

     */
    int (*threadOnce) (int* once, void (*function) (void));

    /** @brief Create a POSIX threading-conformant thread key for
       accessing the thread local store.

     Create a POSIX threading conformant thread key. This key can be used as
         a key to access the thread local store.
     @param key Pointer to the thread key to be returned.
     @param cleanup Function to be invoked during thread local store cleanup.
     @return Completion code as defined by POSIX threading semantics.
     @todo add status codes
     */
    int (*createThreadKey) (CMPI_THREAD_KEY_TYPE* key, void (*cleanup)(void*));

    /** @brief Destroy a thread key for accessing the thread local store

     Destroy a POSIX threading conformant thread key for accessing the
         thread local store.
     @param key The thread key to be destroyed.
     @return If successful, zero will be returned.
     @todo add status codes
     */
    int (*destroyThreadKey) (CMPI_THREAD_KEY_TYPE key);

    /** @brief  get a data pointer from the thread local store using
       a thread key.

     Return data from the thread local store using a thread key.
     @param key The key to be used to retrieve the data pointer.
     @return If successful, returns the data pointer.
     If not successful, returns NULL.
     @todo add status codes
     */
    void* (*getThreadSpecific) (CMPI_THREAD_KEY_TYPE key);

    /** @brief Set a data pointer in the thread local store using a
               thread key.

     Set a data pointer in the therad local store using a POSIX
         threading-conformant  thread key.
     @param key The key to be used.
     @param value The data pointer that is stored in the thread local store.
     @return If successful, returns zero.
         If not successful, returns a non-zero error code. Error
         codes are defined in <errno.h>, specifically for the
         &lt;pthread_setspecific()&gt; function; both are defined in
         IEEE 1003.1.
     @todo add status codes
     */
    int (*setThreadSpecific) (CMPI_THREAD_KEY_TYPE key, void* value);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

    /** @brief Create a POSIX thread conformant mutex.

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

     @return If successful, returns the handle of the new mutex.
         If not successful, returns NULL.
     @todo add status codes
     */
    CMPI_MUTEX_TYPE (*newMutex) (int opt);

    /** @brief Destroy a POSIX threading-conformant mutex <b>(Deprecated)</b>.

     Destroy a POSIX threading conformant mutex.

     @param mutex The mutex to be destroyed.

     @todo add status codes

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use CMPIBrokerExtFT::destroyMutex2() instead.

     @see destroyMutex2()
     */
    void (*destroyMutex) (CMPI_MUTEX_TYPE mutex);

    /** @brief Lock a POSIX threading-conformant mutex. <b>(Deprecated)</b>

     If the mutex is locked by another thread, the current thread is suspended
     until the lock is granted. The behavior in case the mutex is already
     locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;.

     @param mutex The mutex to be locked.

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use CMPIBrokerExtFT::lockMutex2() instead.

     @see lockMutex2()

     @todo add status codes
     */
    void (*lockMutex) (CMPI_MUTEX_TYPE mutex);

    /** @brief Unlock a POSIX threading-conformant mutex <b>(Deprecated)</b>.

     Release control of the mutex. The behavior in case the mutex is not
     locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;.

     @param mutex The mutex to be unlocked.

     @todo add status codes

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use CMPIBrokerExtFT::unlockMutex2() instead.

     @see unlockMutex2()
     */
    void (*unlockMutex) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /** @brief  Create a new condition variable.

     Create a new POSIX threading-conformant condition variable.
     @param opt for future use. It should be ignored by the MB, and MIs
     should pass a value of 0.
     @return If successful, handle of newly created condition
         variable. If not successful, NULL

     For historical reasons, no additional error information is passed back.
     */
    CMPI_COND_TYPE (*newCondition) (int opt);

    /** @brief Destroy a condition variable <b>(Deprecated)</b>

     Destroy a POSIX threading conformant condition variable <b>(Deprecated)</b>.

     Deprecated because it does not indicate whether it succeeded
     or failed. Use CMPIBrokerExtFt.destroyCondition2() instead.
     @param cond The condition variable to be destroyed.
     @return None. For historical reasons, this function does not
         indicate whether it succeeded or failed.
     @see destryCondition2()
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
        If not successful, returns a non-zero error code will be returned.
        For historical reasons, this function does not indicate whether it
        succeeded or failed.

     @deprecated This function is deprecated since CMPI 2.1,
     because it does not indicate whether it succeeded or failed.
     Use destroyCondition2() instead.

     @see destroyCondition2()
     */
    int (*condWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex);

    /** @brief Wait until the condition is signalled or a timeout
               value expires.

     The CMPIBrokerExtFT.timedCondWait function waits until a POSIX
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
         codes are defined in <tt><errno.h></tt>, specifically for the
         &lt;pthread_cond_timedwait()&gt; function; both are defined in
         IEEE 1003.1.
     @todo we do not specify the timeout value characteristics either
           here or in the spec. Commented in FINAL RC3 vote.
     */
    int (*timedCondWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex,
            struct timespec* wait);

    /** @brief Send a signal to a condition variable.

     The CMPIBrokerExtFT.signalCondition() function Sends a signal
     to a POSIX threading-conformant condition variable.

     @param cond Specifies the handle of the condition variable to
                 send the signal.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error
         codes are defined in <tt><errno.h></tt>, specifically for the
         &lt;pthread_cond_signal()&gt; function; both are defined in
         IEEE 1003.1.
    */
    int (*signalCondition) (CMPI_COND_TYPE cond);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

#ifdef CMPI_VER_210

    /** @brief Destroy a POSIX threading-conformant mutex.

     Destroy a POSIX threading conformant mutex.
     @param mutex The mutex to be destroyed. This function superceedes the
     original &lt;destroyMutex&gt; function.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_destroy()&gt; function; both are defined in
            IEEE 1003.1.
     @version 2.1
     */
    int (*destroyMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Lock a POSIX threading-conformant mutex.

     Lock a POSIX threading conformant mutex. If the mutex is locked by another
     thread, the current thread is suspended until the lock is granted.
     The behavior in case the mutex is already locked by the current thread
     is defined in the description of &lt;CMPIBrokerExtFT.newMutex()&gt;.

     This function superceedes the original &lt;lockMutex()&gt;*
     function.
     @param mutex The mutex to be locked.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_lock()&gt; function; both are defined in
            IEEE 1003.1.
     @version 2.1
     */
    int (*lockMutex2) (CMPI_MUTEX_TYPE mutex);

    /** @brief Unlock a POSIX threading-conformant mutex.

     Unlock a POSIX threading conformant mutex. The behavior in case the mutex
     is not locked by the current thread is defined in the description of
     &lt;CMPIBrokerExtFT.newMutex()&gt;.

     This function superceedes the original &lt;unlockMutex()&gt;
     function.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_mutex_lock()&gt; function; both are defined in
            IEEE 1003.1.
     @version 2.1
     */
    int (*unlockMutex2) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /** @brief Destroy a POSIX threading-conformant condition
               variable.

     This function destroys a POSIX threading-conformant condition
     variable.

     This function superceedes the original &lt;unlockMutex()&gt;
     function.
     @return If successful, zero will be returned.
         If not successful, a non-zero error code will be returned. Error codes
            are defined in <errno.h>, specifically for the
            &lt;pthread_cond_destroy()&gt; function; both are defined in
           IEEE 1003.1.
     @version 2.1
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
     *   @addtogroup brokermem-all
     *   @{
     */

    /** @brief Mark a new object lifecycle level for subsequent
           newly created CMPI encapsulated data type objects.

     Invoking this function marks a new object lifecycle level for the
     calling MI. Subsequent newly created CMPI encapsulated data type objects
     in that MI will be associated with that new object lifecycle level.
     A subsequent invocation of the &lt;CMPIBrokerMemFT.release()&gt; function
     with the returned <tt>CMPIGcStat</tt> pointer will release only the
     objects associated with that object lifecycle level.

     The &lt;mark()&gt; and &lt;release()&gt; function calls may be stacked.

     Stacked object lifecycle levels shall not overlap.

     @param mb The broker.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a <tt>CMPIGcStat</tt>
     structure, for use with the &lt;CMPIBrokerMemFT.release()&gt; function.

     If not successful, returns NULL.

    The function return status indicates one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecified error occurred.
    </ul>
     */
    CMPIGcStat* (*mark) (const CMPIBroker* mb, CMPIStatus* rc);

    /** @brief Release all CMPI encapsulated data type objects
       created at the specified object lifecycle level, and remove
       that level.

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
     @return <tt>CMPIStatus</tt> structure indicating the function return
         status.
     @sa CMPIBrokerMemFT.mark()
     The function return status indicates one of the following CMPIrc codes:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecified error occurred.
     </ul>
     */
    CMPIStatus (*release) (const CMPIBroker* mb, const CMPIGcStat* gc);

    /** @brief Allocate an uninitalized memory block of specified
               size.

     This function allocates an uninitalized memory block of the specified
     size. This function behaves consistently with the POSIX
     &lt; malloc()&gt; function (see IEEE 1003.1).

     The allocated memory block can be explicitly released by the MI using
     CMPIBrokerMemFT.cmpiFree(), or will be automatically released by the
     MB after cleanup of the MI.
     @param mb Pointer to a CMPIBroker structure.
     @param size Specifies the amount of memory to allocate in Bytes.
     @return Returns a pointer to the allocated memory, or NULL if the memory
         could not be allocated. No additional error information is returned.
     */
    void* (*cmpiMalloc) (const CMPIBroker* mb, size_t size);

    /** @brief Change the size of a memory block.

     The CMPIBrokerMemFT.cmpiCalloc() function function changes the size of
     the memory block pointed to by ptr which had been returned by a previous
     call to &lt;cmpiMalloc()&gt; or &lt;cmpiCalloc()&gt;. This function
     behaves consistently with the POSIX &lt;realloc()&gt; function
     (see IEEE 1003.1).

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

     The CMPIBrokerMemFT.cmpiRealloc() function function changes the size of
     the memory block pointed to by <tt>ptr</tt> which had returned by a
     previous call to &lt;cmpiMalloc()&gt; or &lt;cmpiCalloc()&gt;. This
     function behaves consistently with the POSIX &lt;realloc()&gt; function
     (see IEEE 1003.1).

     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb Pointer to a CMPIBroker structure.
     @param ptr Pointer to previosuly allocated memory.  Passing a pointer
     to this function which was not allocated explicitly by &lt;cmpiMalloc&gt;
     or &lt;cmpiCalloc&gt; is undefined.
     @param size The new size of the memory block in Bytes.
     @return If successful, a pointer to the resized allocated memory block
     NULL if the new memory is not allcoated. If the function fails
     the original <tt>ptr</tt> argument is unchanged.
     */
    void* (*cmpiRealloc) (const CMPIBroker* mb, void* ptr, size_t size);

    /** @brief allocate a memory block and initialize it with a string.

     The CMPIBrokerMemFT.cmpiStrDup() function function allocates a memory
     block and initializes it by copying a C-language string into it. This
     function behaves consistently with the POSIX strdup() function
     (see IEEE 1003.1). The allocated memory block can be explicitly
     released by the MI using  CMPIBrokerMemFT.cmpiFree(), or will be
     automatically released by the MB after cleanup of the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param str The C-language string to duplicate.
     @return a pointer pointer to the new memory block (that is, to the new
        C-language string, or NULL if unsuccessful.
     */
    char* (*cmpiStrDup) (const CMPIBroker* mb, const char* str);

    /** @brief Free a memory block.

     The CMPIBrokerMemFT.cmpiFree() function releases a memory block
     allocated via the <tt>cmpiMalloc()</tt>, <tt>cmpiCalloc()</tt>, or
     <tt>cmpiRealloc()</tt> functions.

     This function behaves consistently with the POSIX free() function
     (see IEEE 1003.1). This indicates to the MB that the memory block will
     no longer be used by the MI. The MB may free (=reclaim) the memory
     block during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7). Memory blocks that have not
     been explicitly released that way, will be automatically released
     after cleanup of the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param ptr The memory to free. This memory MUST have been allocated via
     the cmpiMalloc, cmpiCalloc or cmpiRealloc functions.
     @return None. Does not indicate whether it succeeded or failed.
     @see cmpiMalloc(), cmpiCalloc(), cmpiRealloc().
     */
    void (*cmpiFree) (const CMPIBroker* mb, void* ptr);

    /** @brief Release a <tt>CMPIInstance</tt> object.

     This function releases a CMPIInstance object. This indicates to the
     MB that the object (including any objects it contains) will no
     longer be used by the MI. The MB may free the resources
     associated with the object during the call to this function, or
     later during some garbage collection cycle.

     Allows a MI to free memory associated to a <tt>CMPIInstance</tt>
     which was allocated via &lt;CMPIBrokerEncFT.newInstance()&gt;.
     this function should be called when an instance is no longer
     being used by the MI. This function will free all contained
     objects (e.g. properties).
     @param mb Pointer to a CMPIBroker structure.
     @param inst Pointer to to the CMPIInstance object to be released.
         This object shall have been created via CMPIBrokerEncFT.newInstance().
     @return None.  Does not indicate whether it succeeded or failed.
     */
    void (*freeInstance) (const CMPIBroker* mb, CMPIInstance* inst);

    /** @brief Release a <tt>CMPIObjectPath</tt> object.

     The CMPIBrokerMemFT.freeInstance() function releases a
     <tt>CMPIObjectPath</tt> object. This indicates to the MB that the object
     (including any objects it contains) will no longer be used by the MI.
     The MB may free the resources associated with the object during the call
     to this function, or later during some garbage collection cycle.

     Allows a MI to free memory associated to a
     <tt>CMPIObjectPath</tt> which was allocated via
     &lt;CMPIBrokerEncFT.newObjectPath()&gt;. this function should
     be called when a <tt>CMPIObjectPath</tt> is no longer being
     used by the MI. This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param obj Pointer to the CMPIObjectPath object that is to be released.
     This object shall have been created via CMPIBrokerEncFT.newObjectPath().
     @return None
     */
    void (*freeObjectPath) (const CMPIBroker* mb, CMPIObjectPath* obj);

    /** @brief Release a <tt>CMPIArgs</tt> object.

    The CMPIBrokerMemFT.freeArgs() function releases a CMPIArgs object.
    This indicates to the MB that the object (including any objects it
    contains) will no longer be used by the MI. The MB may free (=reclaim)
    the memory associated with the object during the call to this function,
    or later during some garbage collection cycle (see Subclause 4.1.7).

     @param mb Pointer to a CMPIBroker structure.
     @param args Pointer to to the CMPIArgs object that is to be released. This
         object shall have been created via CMPIBrokerEncFT.newArgs().
     @return None.
     */
    void (*freeArgs) (const CMPIBroker* mb, CMPIArgs* args);

    /** @brief Release a <tt>CMPIString</tt> object.

     The CMPIBrokerMemFT.freeString() function releases a CMPIString object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows an MI to free memory associated to a <tt>CMPIString</tt> which was
     allocated via &lt;CMPIBrokerEncFT.newString()&gt;. this function should be
     called when an instance is no longer being used by the MI.

     @param mb Pointer to a CMPIBroker structure.
     @param args The string to free.
     @return None.
     */
    void (*freeString) (const CMPIBroker* mb, CMPIString* str);

    /** @brief Release a <tt>CMPIArray</tt> object.

     The CMPIBrokerMemFT.freeArray() function releases a CMPIArray object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a <tt>CMPIArray</tt> which was
     allocated via &lt;CMPIBrokerEncFT.newArray()&gt;. this function should
     be called when an instance is no longer being used by the MI. This
     function will free all contained objects (e.g. the array elements).

     @param mb Pointer to a CMPIBroker structure.
     @param array Pointer to to the CMPIArray object that is to be released. This
     object shall have been created via CMPIBrokerEncFT.newArray().
     @return None.
     */
    void (*freeArray) (const CMPIBroker* mb, CMPIArray* array);

    /** @brief Release a <tt>CMPIDateTime</tt> object.

     The CMPIBrokerMemFT.freeDateTime() function releases a CMPIDateTime
     object. This indicates to the MB that the object (including any objects
     it contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a CMPIDateTime which was
     allocated via CMPIBrokerEncFT.newDateTime functions. this function
     should be called when an instance is no longer being used by the MI.
     This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param dt Pointer to to the CMPIDateTime object that is to be released.
         This object shall have been created via CMPIBrokerEncFT.newDateTime().
     @return None.
     */
    void (*freeDateTime) (const CMPIBroker* mb, CMPIDateTime* dt);

    /** @brief Release a <tt>CMPISelectExp</tt> object.

     The CMPIBrokerMemFT.freeSelectExp() function releases a CMPISelectExp
     object. This indicates to the MB that the object (including any objects
     it contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle (see Subclause 4.1.7).

     Allows a MI to free memory associated to a CMPISelectExp which was
     allocated via CMPIBrokerEncFT.newSelectExp functions. this function
     should be called when an instance is no longer being used by the MI.

     This function will free all contained objects.

     @param mb Pointer to a CMPIBroker structure.
     @param se Pointer to to the CMPISelectExp object that is to be released.
         This object shall have been created via CMPIBrokerEncFT.newSelectExp().
     @return None.
     */
    void (*freeSelectExp) (const CMPIBroker* mb, CMPISelectExp* se);

#ifdef CMPI_VER_210

    /** @brief Free the memory of a C-language string.

     The CMPIBrokerMemFT.freeChars() function releases a C-language string
     (see Subclause 5.2.1). This indicates to the MB that the string will
     no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the string during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7).

     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.
     Availability of the Codepage Conversion capability can be queried by
     an MI using the CMPI_MB_CodepageConversion test mask on the
     <tt>brokerCapabilities</tt> member of the <tt>CMPIBrokerFT</tt>
     structure.

     @param mb Pointer to a CMPIBroker structure.
     @param chars Pointer to to the C-language string to be released.
         This C-language string shall have been created via
         CMPIStringFT.newCharsCP()..
     @return None.
     @version 2.1
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

    /** @brief Release a <tt>CMPIContext</tt> object.

     The Context object will not be used any further and may be freed by
     CMPI run time system.
     @param ctx Pointer to <tt>CMPIContext</tt> to be released.
     @return <tt>CMPIStatus</tt> structure indicating the function
       return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIContext* ctx);

    /** @brief Create an independent copy of a <tt>CMPIContext</tt>
               object.

     Creates an independent copy of the CMPIContext object.
     @param ctx Context this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status..
     @return Pointer to copied <tt>CMPIContext</tt> object. The returned
         <tt>CMPIContext</tt> object shall be explicity released by the
         MI using &lt;CMPIContextFT.release()&gt;.
     @todo add status codes
     */
    CMPIContext* (*clone) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief Get a context entry in a CMPIContext object by name.

     Gets a context entry in a CMPIContext object by supplying its name.
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
     @todo add status codes
     */
    CMPIData (*getEntry) (const CMPIContext* ctx, const char* name,
            CMPIStatus* rc);

    /** @brief  Get a context entry in a CMPIContext object by index.

     Gets a Context entry value defined by its index.
     @param ctx CMPIContext this pointer.
     @param index Specifies the zero-based position of the
         context entry in the internal data array. The order of
         context entries in the internal data array is
         implementation-defined.
     @param name Output: Returned Context entry name (suppressed when NULL).
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status..
     @return if not NULL, points to a CMPIStatus structure that upon return
         updated with the function return status.
     @todo add status codes
     */
    CMPIData (*getEntryAt) (const CMPIContext* ctx, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get the number of context entries in a CMPIContext
               object.

     Gets the number of entries contained in this Context.
     @param ctx CMPIContext object for this function.
     @return If successful, a CMPICount value indicating the number of entries
         in the CMPIContext object. If not successful, the return value will
         be undefined.
     @todo add status codes
     */
    CMPICount (*getEntryCount) (const CMPIContext* ctx, CMPIStatus* rc);

    /** @brief Add or replace a context entry in a CMPIContext object.

     Adds/replaces a named Context entry in a CMPIContext object
     @param ctx Context this pointer.
     @param name Entry name. Pointer to a CMPIString defining a context name.
         See @link def-context-fieldnames definition of context
         entry names @endlink for defined names.
     @param value Address of CMPIValue structure containing the
         non-NULL value to be assigned to the context entry
         or NULL to specify that NULL is to be assigned.
     @param CMPIType value specifying the type of the value to be
         assigned
     @return Service return status.
     @todo add status codes
     @todo should the link above be a ref to the names definitions for
           context entries. Also really poor description
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

    /** @brief  release a CMPIResult object.

     Releases a CMPIResult object. This indicates to the MB that
         the object (including any objects it contains) will no longer
         be used by the MI. The MB may free the resources associated with
         the object during the call to this function, or later during
         some garbage collection cycle.
     @param rslt Pointer to the CMPIResult object to be released.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIResult* rslt);

    /** @brief Create an independent copy of a CMPIResult object.
     @todo KS_todo

     Create an independent copy of the CMPIResult object defined by
     <tt>rslt</tt>.
     @param rslt Pointer to CMPIResult object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
     @return If successful, returns a pointer to the copied CMPIPropertyList
         object.

         The returned CMPIResult object shall be explicitly released by
         the MI using CMPIResultFT.release().

         If not successful, returns NULL.
     @todo add status codes
     */
    CMPIResult* (*clone) (const CMPIResult* rslt, CMPIStatus* rc);

    /** @brief Add a value/type pair to a CMPIResult object
         Adds a value/type pair to be returned to the MB, to a CMPIResult.
         object.
     @param rslt CMPIResult object for this function.
     @param value Pointer to CMPIValue structure specifying the non-NULL value
         to be returned, or is NULL to specify that NULL is to be returned
     @param type CMPIType value specifying the type to be returned
     @return If the value of the type argument is CMPI_chars or CMPI_charsA,
         the C-language string to which the chars member of the value argument
         points is copied by this function and the original string memory
         may be freed by the MI right after this function returns
     @todo add status codes
     */
    CMPIStatus (*returnData) (const CMPIResult* rslt, const CMPIValue* value,
            const CMPIType type);

    /** @brief  add an instance to a CMPIResult object
        Adds an instance to be returned to the MB, to a CMPIResult object
     @param rslt Result this pointer.
     @param inst Instance to be returned.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*returnInstance) (const CMPIResult* rslt,
            const CMPIInstance* inst);

    /** @brief  Add an object path to a CMPIResult object
        Adds an object path to be returned to the MB, to a CMPIResult object.
     @param rslt CMPIResult object for this function.
     @param ref ObjectPath to be returned.
     @return CMPIStatus structure indicating the function return*
        status.
     @todo add status codes
     */
    CMPIStatus (*returnObjectPath) (const CMPIResult* rslt,
            const CMPIObjectPath* ref);

    /** @brief Indicate that no more items will be added to a
         CMPIResult object Indicates to the MB that no further items
         will be added to a CMPIResult object; that is, the MI will
         not return any more data to the MB
     @param rslt CMPIResult object for this function.
     @return CMPIStatus structure indicating the function return status
     @todo add status codes
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
         (see todo). From CMPI 2.1 on, the Extended Errors capability
         shall be available.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     @todo review this description, particularly "see todo".
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
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIError* er);

    /** @brief Create an independent copy of a CMPIError object.
        Create an independent copy of this Error object.
     @param er Pointer to the CMPIError object to be copied.
     @param rc Output: if not NULL, points to a CMPIStatus
        structure* that upon return will have been updated with the
        function return status.
     @return If successful, returns a pointer to the copied CMPIError object.
         The returned CMPIError object shall be explicitly released by the MI
         using CMPIErrorFT.release().If not successful, returns NULL.
     @todo add status codes
     */
    CMPIError* (*clone) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorType attribute of a CMPIError object.
         Gets the type of this Error
     @param er Pointer to the CMPIError object for this function
     @param rc Output: If not NULL, points to a CMPIStatus*
     *   structure* that updated wit the function return status.
     @return If successful, returns a CMPIErrorType enumeration value,
         indicating the value of the ErrorType attribute in the CMPIError
         object.
         If not successful, the returned value is undefined.
     @todo add status codes
     */
    CMPIErrorType (*getErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the OtherErrorType attribute of a CMPIError
       object Returns a string which describes the alternate error
       type.
     @param er Pointer to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure that
         upon return updated with the function return status.
     @return If successful and the OtherErrorType attribute of the CMPIError
         object is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the OtherErrorType attribute of the CMPIError
         object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether the
         function failed.
     @todo add status codes
     */
    CMPIString* (*getOtherErrorType) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the OwningEntity attribute of a CMPIError object.
        Returns a string which describes the owning entity
     @param er Error this pointer
     @param rc Output: if not NULL, points to a CMPIStatus structure
         updated with the function return status.
     @return If successful and the OwningEntity attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the OwningEntity attribute of the CMPIError
         object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.
     @todo add status codes

     */
    CMPIString* (*getOwningEntity) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the MessageID attribute of a CMPIError object
        Returns a string which is the message ID.
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
     @todo add status codes
     */
    CMPIString* (*getMessageID) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the Message attribute of a CMPIError object
     Returns a string comnating an error message.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful and the Message attribute of the CMPIError object
         is non-NULL, returns a pointer to a CMPIString object,
         indicating the value of the Message attribute of the CMPIError object.
         Otherwise,returns NULL.
        The caller must inspect the function return status to see whether
        the function failed.
     @todo add status codes
     */
    CMPIString* (*getMessage) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the PerceivedSeverity attribute of a CMPIError object

     Returns the PerceivedSeverity attribute of a CMPIError object.
     @param er  Pointer to to the CMPIError object for this function
     @param rc Output: , if not NULL, points to a CMPIStatus structure updated
         with the function return status.
     @return If successful, a CMPIErrorSeverity enumeration value will be
         returned, indicating the value of the PerceivedSeverity attribute of
         the CMPIError object. If not successful, the returned value is
         undefined.
     @todo add status codes
     */
    CMPIErrorSeverity (*getPerceivedSeverity) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the ProbableCause attribute of a CMPIError object.

     Returns the ProbableCause attribute of a CMPIError object
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         updated with the function return status..
     @return If successful, a CMPIErrorProbableCause enumeration value
         will be returned, indicating the value of the ProbableCause attribute
         of the CMPIError object.
         If not successful, the returned value is undefined.
     @todo add status codes
     */
    CMPIErrorProbableCause (*getProbableCause) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the ProbableCauseDescription attribute of a
       CMPIError object.

     Returns a string which describes the probable cause.
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
     @todo add status codes
     */
    CMPIString* (*getProbableCauseDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the RecommendedActions array attribute of a
       CMPIError object.

       Returns an array of strings which describes recomended actions of
       the CMPIError object.
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
     @todo add status codes
     */
    CMPIArray* (*getRecommendedActions) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorSource attribute of a CMPIError object.

     Returns a string which describes the Error source of the
         CMPIError object.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful and the ErrorSource attribute of the CMPIError
         object is non-NULL, returnsa pointer to a CMPIString object,
         indicating the value of the ErrorSource attribute of the
         CMPIError object. Otherwise, returns NULL.
         The caller must inspect the function return status to see whether
         the function failed.
     @todo add status codes
     */
    CMPIString* (*getErrorSource) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get the ErrorSourceFormat attribute of a CMPIError
     object.

     Returns a the format that the error src is in.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, returns a CMPIErrorSrcFormat enumeration,
         indicating the value of the ErrorSourceFormat attribute of
         the CMPIError object.
         If not successful, the returned value is undefined.
     @todo add status codes
     */
    CMPIErrorSrcFormat (*getErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the OtherErrorSourceFormat attribute of a
     CMPIError object.

     Returns a string which describes the 'other' format; only available
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
     @todo add status codes
     */
    CMPIString* (*getOtherErrorSourceFormat) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief  get the CIMStatusCode attribute of a CMPIError object.

     Returns the status code of this error.
     @param er Pointer to the CMPIError object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure updated with the function return status.
     @return If successful, returns a CMPIrc value indicating the value of the
         CIMStatusCode attribute of the CMPIError object.
         Please note that not all status codes apply to all situations.
         It is up to the MI to ensure the correct status code is set.
         If not successful, the returned value is undefined.
     @todo add status codes
     */
    CMPIrc (*getCIMStatusCode) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Get CIMStatusCodeDescription attribute of a CMPIError object.

     Returns a string which describes the status code error.
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
     @todo add status codes
     */
    CMPIString* (*getCIMStatusCodeDescription) (const CMPIError* er,
            CMPIStatus* rc);

    /** @brief Get the MessageArguments array attribute of a CMPIError object.

     Returns an array which contains the dynamic content of the message.
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
     @todo add status codes

     */
    CMPIArray* (*getMessageArguments) (const CMPIError* er, CMPIStatus* rc);

    /** @brief Set the ErrorType attribute of a CMPIError object.

     Sets the error type attribute of this error object.
     @param er Pointer to the CMPIError object for this function.
     @param et CMPIErrorType enumeration value specifying the new value for
         the ErrorType attribute. If the error message in the CMPIError object
         is defined in a DMTF message registry, the et argument shall
         reflect the content of the ERROR_TYPE element defined for
         the message in the registry
     @return Output: CMPIStatus structure indicating the function return status
     @todo add status codes
     */
    CMPIStatus (*setErrorType) (const CMPIError* er, const CMPIErrorType et);

    /** @brief  set the OtherErrorType attribute of a CMPIError
     object Sets the 'other' error type of this error object.
     @param er Pointer to the CMPIError object for this function.
     @param oet Pointer to a string specifying the new non-NULL*
        value for the OtherErrorType attribute, or is NULL
        specifying that the attribute will be set to NULL. If the
        error message is defined in a DMTF message registry, the
        string value of the oet argument shall be the content of
        the OTHER_ERROR_TYPE element defined for the message in the
         registry It is only valid when error type is "OTHER"
     @return Output: CMPIStatus structure indicating the function return
     status.
     @todo add status codes
     */
    CMPIStatus (*setOtherErrorType) (const CMPIError* er, const char* oet);

    /** @brief  set the ProbableCauseDescription attribute of a
     CMPIError object.

     Sets the description of the probable cause.
     @param er Pointer to the CMPIError object for this function.
     @param pcd string specifying the new non-NULL value for the
         ProbableCauseDescription attribute, or is NULL specifying that the
         attribute will be set to NULL. If the error message is defined in a
         DMTF message registry, note that the string value of the pcd argument
         is not defined in the message in the registry.
     @return Output: CMPIStatus structure indicating the function return status
     @todo add status codes
     */
    CMPIStatus (*setProbableCauseDescription) (const CMPIError* er,
            const char* pcd);

    /** @brief Set the RecommendedActions array attribute of a
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
     @todo add status codes
     */
    CMPIStatus (*setRecommendedActions) (const CMPIError* er,
            const CMPIArray* ra);

    /** @brief Set the ErrorSource attribute of a CMPIError object.

     Specifies a string which specifes The identifying information
     of the entity (i.e., the instance) generating the error..*
     @param er Pointer to the CMPIError object for this function.
     @param es string specifying the new non-NULL value for the ErrorSource
         attribute, or is NULL specifying that the attribute will be set to
         NULL. If the error message is defined in a DMTF message registry,
         the string value of the es argument shall be the content of the
         ERROR_SOURCE element defined for the message in the registry.
     @return CMPIStatus structure indicating the function return status
     @todo add status codes
     */
    CMPIStatus (*setErrorSource) (const CMPIError* er, const char* es);

    /** @brief Set the <tt>ErrorSourceFormat</tt> attribute of a
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
     @todo add status codes
     */
    CMPIStatus (*setErrorSourceFormat) (const CMPIError* er,
            const CMPIErrorSrcFormat esf);

    /** @brief Set the <tt>OtherErrorSourceFormat</tt> attribute of a
     CMPIError object

     Specifies a string defining "Other" values for <tt>ErrorSourceFormat</tt>
     @param er Pointer to the <tt>CMPIError</tt> object for this function.
     @param oef Pointer to a string specifying the new non-NULL value for
         the <tt>OtherErrorSourceFormat</tt> attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is
         defined in a DMTF message registry, the string value of the
         <tt>oef</tt> argument shall be the content of the
         OTHER_ERROR_SOURCE_FORMAT element defined for the message in the
         registry.
     @return <tt>CMPIStatus</tt> structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setOtherErrorSourceFormat) (const CMPIError* er,
            const char* oef);

    /** @brief Set the <tt>CIMStatusCodeDescription</tt> attribute of
       a <tt>CMPIError</tt> object

     Sets the description of the status code. For a description of the
         <tt>CIMStatusCodeDescription</tt> attribute, see the description of the
         <tt>CIMStatusCodeDescription</tt> property in the <tt>CIM_Error</tt>
         class in the CIM Schema.
     @param er Pointer to the <tt>CMPIError</tt> object for this function.
     @param scd A Pointer to a string specifying the new non-NULL value
         for the <tt>CIMStatusCodeDescription</tt> attribute, or NULL specifying
         that the attribute will be set to NULL. If the error message is defined
         in a DMTF message registry, note that the string value of the
         <tt>scd</tt> argument is not defined in the message in the registry.
     @return <tt>CMPIStatus</tt> structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setCIMStatusCodeDescription) (const CMPIError* er,
            const char* scd);

    /** @brief Get the <tt>MessageArguments</tt> array attribute of a
           <tt>CMPIError</tt> object.

     Sets an array of strings for the dynamic content of the message. For a
         description of the <tt>MessageArguments</tt> attribute, see the
         description of the <tt>MessageArguments</tt> property in the
         <tt>CIM_Error</tt> class in the CIM Schema.
     @param er Pointer to the <tt>CMPIError</tt> object for this function.
     @param values <tt>CMPIArray</tt> object specifying the new array value
         for the <tt>MessageArguments</tt> array attribute. The <tt>CMPIArray</tt>
         object contains <tt>CMPIString</tt> objects or NULL values as array
         elements. The values argument may be NULL, specifying that the
         <tt>MessageArguments</tt> array attribute will be set to NULL. If the
         error message is defined in a DMTF message registry, the values
         argument shall reflect the values defined in the DYNAMIC_ELEMENT
         elements defined for the message in the registry, in the order
         defined there.
     @return <tt>CMPIStatus</tt> structure indicating the function return status.
     @todo add status codes
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

    /** @brief Release a <tt>CMPIInstance</tt> object.

     The Instance object will not be used any further and may be freed by
     CMPI run time system. This will also release the contained objects.
     @param inst Pointer to CMPIInstance to be releases.
     @return Service return status.
     */
    CMPIStatus (*release) (CMPIInstance* inst);

    /** @brief Create an independent copy of a <tt>CMPIInstance</tt> object.

     Create an independent copy of this Instance object. The resulting
     object must be released explicitly.
     @param inst Pointer to the <tt>CMPIInstance</tt> to be cloned.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied <tt>CMPIInstance</tt> object.
     @todo add status codes
     */
    CMPIInstance* (*clone) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief Get a property in a <tt>CMPIInstance</tt> object by
               name.

     Gets a named property value from an instance.
     @param inst Instance this pointer.
     @param name Points to a string containing the property name.
     @param rc Output: if not NULL, points to a <tt>CMPIStatus</tt> structure
     that upon return is updated with the function return status.
     @return If successful, a CMPIData structure containing the specified
     property will be returned.

     If not successful, CMPIData.state will have the CMPI_badValue flag
     set to true.
     @todo add status codes
     */
    CMPIData (*getProperty) (const CMPIInstance* inst, const char* name,
            CMPIStatus* rc);

    /** @brief Get a property in a <tt>CMPIInstance</tt> object by
               index.

     Gets a Property value defined by its index.
     @param inst Pointer to the instance.
     @param index Zero-based index number of the property in the internal
         data array.
     @param name Output: If not NULL, points to a <tt>CMPIString</tt> pointer
     that upon success is updated to point to a <tt>CMPIString</tt> object
     containing the property name. The returned <tt>CMPIString</tt> object
     shall not be explicitly released by the MI, because it may be an internal
     object of the <tt>CMPIString</tt> object which will be released
     along with that object, or a new object created by the MB which will be
     released automatically by the MB.
     @param rc Output: If not NULL, points to a CMPIStatus structure
     updated with the function return status.
     @return If successful, a <tt>CMPIData</tt> structure containing the
     specified property.
     If not successful, <tt>CMPIData</tt>  state will have the
     <tt>CMPI_badValue</tt> flag set to true
     @todo add status codes
     */
    CMPIData (*getPropertyAt)
    (const CMPIInstance* inst, CMPICount index, CMPIString** name,
            CMPIStatus* rc);

    /** @brief Get the number of properties in a CMPIInstance
     *         object.

     Gets the number of properties contained in this instance.
     @param inst Pointer to the instance.
     @param rc Output: If not NULL, points to a <tt>CMPIStatus</tt> structure
     updated with the function return status.
     @return If successful, a <tt>CMPICount</tt> value indicating the number
     of properties in the instance. If not successful, 0.
     @todo add status codes
     */
    CMPICount (*getPropertyCount) (const CMPIInstance* inst, CMPIStatus* rc);

    /** @brief Set a property value in a <tt>CMPIInstance</tt> object by name.

     Adds or replace the named Property in the instanced defined by
         <tt>inst</tt>. If the property is a key property, the function may
         or may not in addition add or update the key binding in the object
         path of the instance. In order for MIs not to be dependent on this
         behavior, MIs should set key property values in instances and key
         binding values in object paths separately. Key binding values can
         be set during CMPIBrokerEncFT.newInstance() and by using
         &lt;CMPIInstanceFT.setObjectPath()*gt;. The MI shall specify
         consistent values for key bindings and key properties.
     @param inst pointer to the <tt>CMPIInstance</tt>.
     @param name Pointer to a string containing the property name.
     @param value <tt>CMPIValue</tt> structure containing the non-NULL
         value to be assigned to the property, or NULL to specify that
         NULL is to be assigned.
     @param type <tt>CMPIType</tt> value specifying the type of the value to
        be assigned to the property. All types of CIM values are supported.

        If the value of the type argument is <tt>CMPI_chars</tt> or
        <tt>CMPI_charsA</tt>, the C-language string to which the chars member
        of the value argument points is copied by this function and the
        original string memory may be freed by the MI right after
        this function returns.
     @return <tt>CMPIStatus</tt> structure indicating the function
         return status.
     @todo add status codes
     */
    CMPIStatus (*setProperty) (const CMPIInstance* inst, const char* name,
            const CMPIValue* value, CMPIType type);

    /** @brief Get a <tt>CMPIObjecPath</tt> object from a <tt>CMPIInstance</tt>
       object.

     Generates a <tt>CMPIObjectPath</tt> object from the namespace, class name,
         and key properties of a <tt>CMPIInstance</tt> object.
     @param inst Pointer to the <tt>CMPIInstance</tt>>.
     @param rc Output: , If not NULL, points to a <tt>CMPIStatus</tt> structure
        that upon return has been updated with the function return status.
     @return If successful, a pointer to a <tt>CMPIObjectPath</tt> object
     representing the instance path of the <tt>CMPIInstance</tt>.
    The returned <tt>CMPIObjectPath</tt> object shall not be explicitly
    released by the MI, because it may be an internal object of the
    <tt>CMPIInstance</tt> object which will be released along with that object,
    or a new object created by the MB which will be released automatically
    by the MB.
     @todo add status codes
     */
    CMPIObjectPath* (*getObjectPath) (const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief Attach a property filter to a <tt>CMPIInstance</tt>
               object.

     This function attaches a property filter to a <tt>CMPIInstance</tt> object,
     replacing any previous property filter settings for this object.
     By calling this function, the MI delegates property list filtering
     to the MB for this CMPIInstance object, for all of its properties
     including those that had already been set before the call to
     <tt>setPropertyFilter()</tt>.

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
     @todo add status codes
     */
    CMPIStatus (*setPropertyFilter) (const CMPIInstance* inst,
            const char** propertyList, const char** keys);

    /** @brief Set the instance path component of a CMPIInstance
               object.

     Set or replace the CMPIObjectPath component in an instance.

     The function may or may not in addition update the key property
     values in the instance to the values of the key bindings in the object
     path. In order for MIs not to be dependent on this behavior, MIs should
     set key property values in instances and key binding values in
     object paths separately. Property values can be set by using
     &lt;CMPIInstanceFT.setProperty()&gt; or
     &lt;CMPIInstanceFT.setPropertyWithOrigin()&gt;. The MI shall specify
     consistent values for key bindings and key properties.

     @param inst Pointer to the CMPIInstance object.
     @param op Pointer to CMPIObjectPath structure. This objectpath
     shall contain a non-NULL namespace, non-NULL classname, as well as all
     keys for the specified instance. The object path may specify a non-NULL
     host for the instance (this is used for instances returned by
     cross-host associations).

     @return  CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setObjectPath) (const CMPIInstance* inst,
            const CMPIObjectPath* op);

#ifdef CMPI_VER_200

    /** @brief Add or replace a property value in a CMPIInstance
               object by name.

     Adds or replaces a Property value and origin in a CMPIInstance.

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
     @param value Pointer to to a CMPIValue structure containing the value
     to be assigned to the property.
     @param type CMPIType structure defining the type of the value.
     @param origin the name of the class in which this property was
     originally defined. If NULL, then no origin is attached to  the
     property.
     @return CMPIStatus structure indicating the function return status.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_TYPE_MISMATCH</tt>	type does not correspond
            to class-defined type.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The inst handle is invalid.
    </ul>
     @version CMPI 2.0
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
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIObjectPath* op);

    /** @brief Create an independent copy of a CMPIObjectPath
     *         object.

     Create an independent copy of this CMPI ObjectPath object. The resulting
     object must be released explicitly.
     @param op Pointer to CMPIObjectPath to be cloned.
     @param rc Output: Service return status (suppressed when NULL).
     @return CMPIStatus structure indicating the function return*
         status.
     @todo add status codes
     */
    CMPIObjectPath* (*clone) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Add the namespace component to a <tt>CIMObjectPath</tt>
           object.

     Set or replace the namespace component in the CMPIObjectPath object
     defined by <tt>op</tt>.
     @param op Pointer to the CMPIObjectPath object.
     @param ns CMPI String containing the namespace to add.
     @return CMPIStatus structure indicating the function return*
         status.
     @todo add status codes
     */
    CMPIStatus (*setNameSpace) (const CMPIObjectPath* op, const char* ns);

    /** @brief Get the namespace component from a <tt>CIMObjectPath</tt>.
           object.

     Get the namespace component from a <tt>CIMObjectPath</tt> object.
     @param op Pointer to the <tt>CIMObjectPath</tt> object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, a pointer to a CMPIString object containing*
         the namespace component of the object path will be returned.
         The returned CMPIString object shall not be explicitly released
         by the MI, because it may be an internal object of the
         CMPIObjectPath object which will be released along with that object,
         or a new object created by the MB which will be released
         automatically by the MB.
     @todo add status codes
     */
    CMPIString* (*getNameSpace) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set the host name component in a <tt>CIMObjectPath</tt> object.

     Set or replace the host name component in  <tt>op</tt> a
         <tt>CIMObjectPath</tt> object with <tt>hn</tt>.
     @param op Pointer to the CMPIObjectPath.
     @param hn Pointer to a CMPIString containing the host name.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setHostname) (const CMPIObjectPath* op, const char* hn);

    /** @brief Get the host name component  in a <tt>CIMObjectPath</tt> object.

     Get the host name component.
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
     @todo add status codes
     */
    CMPIString* (*getHostname) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Set class name component in a <tt>CIMObjectPath</tt>
        object.

     Set/replace the class name component in the <tt>CIMObjectPath</tt>
        object.
     @param op Pointer to CMPIObjectPath.
     @param cn CMPIString containing the class name.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setClassName) (const CMPIObjectPath* op, const char* cn);

    /** @brief Set class name component in a <tt>CIMObjectPath</tt>  object.

     Get the classname componentin a <tt>CIMObjectPath</tt> object.
     @param op Pointer to CMPIObjectPath.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object
        containing the class name component of the object path.
        The returned CMPIString object shall not be explicitly released
        by the MI, because it may be an internal object of the
        CMPIObjectPath object which will be released along with
        that object, or a new object created by the MB which will be
        released automatically by the MB
     @todo add status codes
     */
    CMPIString* (*getClassName) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief Add or replace a key binding in a CMPIObjectPath object.

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
    @todo add status codes
    */
    CMPIStatus (*addKey) (const CMPIObjectPath* op, const char* name,
            const CMPIValue* value, const CMPIType type);

    /** @brief Get a key binding in a CMPIObjectPath object by name.

    @param op Points to the CMPIObjectPath object for this function.
    @param name Name of the key binding.
    @param rc Output: If not NULL, points to a CMPIStatus structure
        that upon return will have been updated with the function return
        status.
    @return A CMPIData structure

    If successful, the returned CMPIData structure contains the value of the
    key binding.

    The MB will attempt to set the type in the returned CMPIData structure
    to the precise CIM type, if available. Versions of the CIM-XML protocol
    before DSP0200 Version 1.4 did not mandate the presence of the precise
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

    In addition, the CMPI_keyValue flag will be set in CMPIData.state to
    indicate that the value is a key binding.

    If not successful, CMPIData.state will have the CMPI_badValue flag set to
    true.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt> Key not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt> The `op` handle is invalid.
    </ul>
    */
    CMPIData (*getKey) (const CMPIObjectPath* op, const char* name,
            CMPIStatus* rc);

    /** @brief Get a key binding in a CMPIObjectPath object by index.

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
    before DSP0200 Version 1.4 did not mandate the presence of the precise
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

    In addition, the CMPI_keyValue flag will be set in CMPIData.state
    to indicate that the value is a key binding.

    If not successful, CMPIData.state will have the CMPI_badValue flag set to
    true.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt> Key not found.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt> The `op` handle is invalid.
    </ul>
    */
    CMPIData (*getKeyAt) (const CMPIObjectPath* op, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief  get the number of key bindings in a CMPIObjectPath object.

     Gets the number of key bindingscontained in this CMPIObjectPath.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param rc Output: If not NULL, points to a CMPIStatus structure
         that upon return is updated with the function return
         status.
     @return If successful, a CMPICount value indicating the number of
         key bindings will be returned. If the CMPIObjectPath object
         does not have a key component, the function will succeed and
         return 0.

         If not successful, 0 will be returned.
     @todo add status codes
     */
    CMPICount (*getKeyCount) (const CMPIObjectPath* op, CMPIStatus* rc);

    /** @brief ? set or replace the namespace and class name components in a
       CMPIObjectPath object from another CMPIObjectPath object

       Set or replace namespace and classname components in CMPIObjectPath
         <tt>op</tt> from CMPIObjectPath <tt>src</tt>.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param src a CMPIObjectPath object used as the source for the new
         namespace and class name components.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    /** @brief Set host name, namespace, and class name components
       in a CMPIObjectPath object from another CMPIObjectPath
       object.

       Set/replace hostname, namespace and classname components in the
       CMPIObjectPath <tt>op</tt> from the CMPIObjectPath <tt>src</tt>.
     @param op Pointer to CMPIObjectPath object to be modified..

     @param src CMPIObjectPath object used as the source for the new host name,
         namespace, and class name components.
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*setHostAndNameSpaceFromObjectPath) (const CMPIObjectPath* op,
            const CMPIObjectPath* src);

    /** @brief Get a class qualifier.

     Gets a class qualifier in the class identified by this object path
         This function shall be supported by the MB if the Basic Qualifier
         capability is available; otherwise, it shall not be supported.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param qName Qualifier name.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return is updated with the function return status..
     @return If successful, returns a CMPIData structure containing the
         specified qualifier. If not successful, CMPIData.state
         CMPI_badValue flag set to true
     @todo add status codes
     */
    CMPIData (*getClassQualifier) (const CMPIObjectPath* op,
            const char* qName, CMPIStatus* rc);

    /** @brief Get a property qualifier
     @todo ?

     Gets a property qualifier in the class identified by this
     object path. This function shall be supported by the MB if the
     Basic Qualifier.* capability is available; otherwise, it
     shall not be supported.
     @param op Pointer to <tt>CMPIObjectPath</tt>object that references the
         class and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by the MB.
     @param pName Property name.
     @param qName Pointer to a string specifying the qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set
      to true.
     @todo add status codes
     */
    CMPIData (*getPropertyQualifier) (const CMPIObjectPath* op,
            const char* pName, const char* qName, CMPIStatus* rc);

    /** @brief Get a method qualifier.

     Get method qualifier value.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param mName Method name.
     @param qName Qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return Qualifier value.
     @todo add status codes
     @todo review return description.
     */
    CMPIData (*getMethodQualifier) (const CMPIObjectPath* op,
            const char* methodName, const char* qName, CMPIStatus* rc);

    /** @brief Get a parameter qualifier.

     Gets a parameter qualifier in the class identified by this
     object path.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param mName Method name.
     @param pName Parameter name.
     @param qName Qualifier name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing
     the specified qualifier will be returned.

     If not successful, returns CMPIData.state with CMPI_badValue flag set
      to true..
     @todo add status codes
     */
    CMPIData (*getParameterQualifier) (const CMPIObjectPath* op,
            const char* mName, const char* pName, const char* qName,
            CMPIStatus* rc);

    /** @brief Convert a CMPIObjectPath object into a string format.

     Generates a well formed implementation-specific string representation
     of this CMPIObjectPath.
     @param op Pointer to <tt>CMPIObjectPath</tt>.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a CMPIString object containing
         the string representation of the object path.

     The returned CMPIString object shall not be explicitly released
     by the MI, because it may be an internal object of the CMPIObjectPath
     object which will be released along with that object, or a
     new object created by the MB which will be released automatically
     by the MB

     If not successful, returns NULL.
     @todo add status codes
     */
    CMPIString* (*toString) (const CMPIObjectPath* op, CMPIStatus* rc);

};

/**
 * @}
 * @addtogroup qualifier-services
 * @{
 *   The qualifier services are the following member functions from the
 *   [CMPIObjectPath encapsulated data type object](@ref _CMPIObjectPathFT):
 *     <UL>
 *     <LI>@ref _CMPIObjectPathFT::getClassQualifier
 *     <LI>@ref _CMPIObjectPathFT::getPropertyQualifier
 *     <LI>@ref _CMPIObjectPathFT::getMethodQualifier
 *     <LI>@ref _CMPIObjectPathFT::getParameterQualifier
 *     </UL>
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

    /** @brief Create an independent copy of a CMPISelectExp object.

     Create an independent copy of this CMPISelectExp object. The resulting
         object must be released explicitly.
     @param se Pointer to CMPISelectExp to clone.
     @param rc Output: Service return status (suppressed when NULL).
     @return If not NULL points to copied SelectExp object.
     @todo add status codes
     */
    CMPISelectExp* (*clone) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Test whether an instance matches the select
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
     @todo add status codes
     */
    CMPIBoolean (*evaluate) (const CMPISelectExp* se, const CMPIInstance* inst,
            CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object as a string.

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
     @todo add status codes
     */
    CMPIString* (*getString) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object
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

    If not successful, returns NULL.

     @todo add status codes
     */
    CMPISelectCond* (*getDOC) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Get the select expression in a CMPISelectExp object as
       a conjunction of disjunctions.

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

    If not successful, returns NULL.
     @todo add status codes
     */
    CMPISelectCond* (*getCOD) (const CMPISelectExp* se, CMPIStatus* rc);

    /** @brief Test whether the properties returned by an accessor
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
     @todo add status codes
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

    /** @brief  release a <tt>CMPISelectCond</tt> object.

     The SelectCond object will not be used any further and may be freed by
     CMPI run time system.
     @param sc SelectCond this pointer.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPISelectCond* sc);

    /** @brief Create an independent copy of a
               <tt>CMPISelectCond</tt> object.

     *Create an independent copy of this SelectCond object. The resulting
     object must be released explicitly.
     @todo KS_todo
     @param sc SelectCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied SelectExp object.
     @todo add status codes
     */
    CMPISelectCond* (*clone) (const CMPISelectCond* sc, CMPIStatus* rc);

    /** @brief Get the number and type of subconditions in a
       CMPISelectCond object.

     Return the number of subconditions that are part of this SelectCond.
     Optionally, the SelectCond type (COD or DOC) will be returned.
     @todo KS_todo

     This function shall be supported by the MB if the Query Normalization
        capability is available; otherwise, it shall not be
        supported.
     @param sc SelectCond this pointer.
     @param type Output: SelectCond type (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPICount value indicating the number of
     subconditions.

     If not successful, returns 0.
     @todo add status codes
     */
    CMPICount (*getCountAndType) (const CMPISelectCond* sc, int* type,
            CMPIStatus* rc);

    /** @brief Get a subcondition in a CMPISelectCond object by
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

     If not successful, returns NULL.
     @todo add status codes

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

    /** @brief  release a <tt>CMPISubCond</tt> object.

     The SubCond object will not be used any further and may be freed by
     CMPI run time system.
     @param sc SubCond this pointer.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPISubCond* sc);

    /** @brief Create an independent copy of a <tt>CMPISubCond</tt>
               object.

     Create an independent copy of this SubCond object. The resulting
     object must be released explicitly.
     @param se SubCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied SelectExp object.
     @todo add status codes
     */
    CMPISubCond* (*clone) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief Get the number of predicates in a CMPISubCond object.

     Return the number of predicates that are part of sub condition.

     This function shall be supported by the MB if the Query Normalization
     capability is available; otherwise, it shall
     not be supported.
     @todo KS_todo add to others
     @param sc SubCond this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Number of Predicate elements.
     @todo add status codes
     */
    CMPICount (*getCount) (const CMPISubCond* sc, CMPIStatus* rc);

    /** @brief Get a predicate in a <tt>CMPISubCond</tt> object by
               index.

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

         If not successful, returns NULL.
     @todo add status codes

     */
    CMPIPredicate* (*getPredicateAt) (const CMPISubCond* sc, CMPICount index,
            CMPIStatus* rc);

    /** @brief Get a predicate in a <tt>CMPISubCond</tt> object by name.

     Returns a predicate element in a <tt>CMPISubCond</tt> based on name
     in <tt>name</tt>

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
     @todo add status codes
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
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIPredicate* pr);

    /** @brief Create an independent copy of a CMPIPredicate object.

     Create an independent copy of this Predicate object. The resulting
     object must be released explicitly.
     @param pr Predicate this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Predicate object.
     @todo add status codes
     */
    CMPIPredicate* (*clone) (const CMPIPredicate* pr, CMPIStatus* rc);

    /** @brief Get the predicate components of a CMPIPredicate object.

     Get the predicate components.
     @todo KS_todo

     @param pr Predicate this pointer.
     @param type Property type.
     @param prop Predicate operation.
     @param lhs Left hand side of predicate.
     @param rhs Right hand side of predicate.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*getData) (const CMPIPredicate* pr, CMPIType* type,
            CMPIPredOp* prop, CMPIString** lhs, CMPIString** rhs);

    /** @brief Test whether the properties returned by an accessor
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
     @todo add status codes
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
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIArgs* as);

    /** @brief Create an independent copy of a CMPIResult object.

     Create an independent copy of this Args object. The resulting
     object must be released explicitly.
     @param as Args this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Args object.
     @todo add status codes
     */
    CMPIArgs* (*clone) (const CMPIArgs* as, CMPIStatus* rc);

    /** @brief Set a method parameter in a CMPIArgs object.

     Adds or replaces a method parameter in a CMPIArgs object.
     @param as Args this pointer.
     @param name Argument name.
     @param value CMPIValue structure containing the non-NULL value to be
         assigned to the method parameter, or is NULL to specify
         that NULL is to be assigned.
     @param type type of the method parameter. All types of CIM values are
         supported
     @return CMPIStatus structure indicating the function return status.
     @todo add status codes
     */
    CMPIStatus (*addArg) (const CMPIArgs* as, const char* name,
            const CMPIValue* value,
            const CMPIType type);

    /** @brief Get a method parameter in a CMPIArgs object by name.

     This function gets a method parameter in a CMPIArgs object,
        by its name..
     @param as Args this pointer.
     @param name Argument name.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful,returns a CMPIData structure containing the
     specified method parameter.

    If not successful, CMPIData.state will have the CMPI_badValue flag
    set to true
     @todo add status codes
     */
    CMPIData (*getArg) (const CMPIArgs* as, const char* name, CMPIStatus* rc);

    /** @brief Get a method parameter in a CMPIArgs object by index.

     Gets a Argument value defined by its index.
     @param as Args this pointer.
     @param index Position in the internal Data array.
     @param name Output: Returned argument name (suppressed when NULL).
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.

    If not successful, CMPIData.state will have the CMPI_badValue flag
    set to true
     @todo add status codes
     */
    CMPIData (*getArgAt) (const CMPIArgs* as, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /** @brief Get a method parameter in a CMPIArgs object by index.

     Gets the number of arguments contained in this CMPIArgs object.
     @param as Args this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIData structure containing the
     specified method parameter.

    If not successful, CMPIData.state will have the CMPI_badValue flag
    set to true
     @todo add status codes
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
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIString* st);

    /**
     Create an independent copy of this String object. The resulting
     object must be released explicitly.
     @param st Pointer to CMPIString object.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied String object.
     @todo add status codes
     */
    CMPIString* (*clone) (const CMPIString* st, CMPIStatus* rc);

    /** @brief Get a pointer to a C-language string representation of a
       CMPIString object.

     Get a pointer to a C char* representation of this CMPIString object.
     @param st Pointer to CMPIString object.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a pointer to a C-language string
     will be returned.
     @todo KS_todo ref to where defined.

     The character array of the returned string shall not be explicitly
     released by the MI, because it may point to an internal data area in the
     CMPIString object which will be released along with that object, or it
     may point to a new character array created by the MB which will be
     released automatically by the MB.

     If not successful, returns NULL.
     @todo add status codes
     */
    const char* (*getCharPtr) (const CMPIString* st, CMPIStatus* rc);

#ifdef CMPI_VER_210

    /** @brief Create a C-language string that has converted a CMPIString
           object into a specific codepage

     Creates a new C-language string (see Subclause 5.2.1) that contains
     the string in a CMPIString object, converted into a specific codepage.

     This function shall be supported by the MB if the Codepage Conversion
     capability is available; otherwise, it shall not be supported.

     @param str Pointer to the CMPIString object for this function.
     @param cpid <tt>CMPICodePageID</tt> specifies the CMPI-specific codepage
         ID for the codepage to convert to. See the CMPI Specification
         section 5.2.2 (CodePage for a list of supported codepages and their codepage
         ID values.
     @param rc If not NULL, points to a CMPIStatus structure that
     upon return has been updated with the function return status.
     @return If successful, returns a new C-language string, in the codepage
     specified in the cpid argument.
     The returned C-language string must be freed by the MI using
     &lt;CMPIBrokerMemFT.freeChars()&gt;.

     If not successful, returns NULL.
     @version CMPI specification 2.1
     @todo add status codes
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

    /** @brief  release a <tt>CMPIArray</tt> object.

     The Array object will not be used any further and may be freed by
     CMPI run time system.
     @param ar Pointer to this <tt>CMPIArray</tt>.
     @return Service return status.
     @todo add status codes
     */
    CMPIStatus (*release) (CMPIArray* ar);

    /** @brief Create an independent copy of a <tt>CMPIArray</tt> object.

     Create an independent copy of this Array object. The resulting
     object must be released explicitly.
     @param ar Pointer to this <tt>CMPIArray</tt> object.
     @param rc Output: Service return status (suppressed when NULL).
     @return Pointer to copied Array object.
     @todo add status codes
     */
    CMPIArray* (*clone) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief Get the number of array elements in a CMPIArray
               object.

     Gets the number of elements contained in this Array.
     @param ar Array this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
     upon return has been updated with the function return status.
     @return If successful, a CMPICount value indicating the number of
         array elements will be returned.

         If not successful, 0 will be returned.
     @todo add status codes
     */
    CMPICount (*getSize) (const CMPIArray* ar, CMPIStatus* rc);

    /**
     Gets the element type.
     @todo Sync description with spec. KS_todo not in spec.
     @param ar Array this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return Number of elements.
     */
    CMPIType (*getSimpleType) (const CMPIArray* ar, CMPIStatus* rc);

    /** @brief Get the value of an array element in a CMPIArray
               object by index.

     Gets the value of an array element defined by the zero-based position
     <tt>index</tt> of the array element in a CMPIArray object <tt>ar</tt>.
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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt> <tt>index</tt> value
            out of range.
        <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The <tt>ar</tt>
            handle is invalid.
    </ul>
     */
    CMPIData (*getElementAt) (const CMPIArray* ar, CMPICount index,
            CMPIStatus* rc);

    /** @brief Set the value of an existing array element in a CMPIArray
       object by index

     This function sets the value <tt>value</tt> and <tt>type</tt>
     into an existing element defined by <tt>&ltindex</tt> in the
     array object defined by <tt>ar</tt>.

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

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
     <li><tt>CMPI_RC_OK</tt>	Function successful.
     <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt>	<tt>index</tt> value out of
         range.
     <li><tt>CMPI_RC_ERR_TYPE_MISMATCH</tt>	<tt>type</tt> does not correspond
         to the simple base type of <tt>ar</tt>.
     <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	The <tt>ar</tt> handle is invalid.
     </ul>

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

    /** @brief Release a <tt>CMPIEnumeration</tt> object.

     releases a CMPIEnumeration object. This indicates to the MB that
     the object (including any objects it contains) will no longer
     be used by the MI. The MB may free the resources associated with
     the object during the call to this function, or later during some
     garbage collection cycle.
     @param en Pointer to to the <tt>CMPIEnumeration</tt> object to be
        released. That object shall have been created using
         CMPIEnumerationFT.clone().
     @return CMPIStatus structure indicating the function return status.
    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
     */
    CMPIStatus (*release) (CMPIEnumeration* en);

    /** @brief Create an independent copy of a <tt>CMPIEnumeration</tt> object.

     Creates an independent copy of this <tt>CMPIEnumeration</tt> object.
         The resulting object must be released explicitly.
     @param en Pointer to the <tt>CMPIEnumeration</tt> object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
        return has been updated with the function return status.
     @return If successful, returns a pointer to the copied
     CMPIEnumeration object.

     The returned CMPIEnumeration object shall be explicitly released by
     the MI using CMPIEnumerationFT.release().

     If not successful, returns NULL.
     @todo add status codes
     */
    CMPIEnumeration* (*clone) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief  Get the next element in a CMPIEnumeration object.

     Get the next element of the CMPIEnumeration &lten&gt.
     @param en Pointer to the CMPIEnumeration object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the function
         return status.
     @return If successful, a CMPIData structure containing the next
         element will be returned.

         If not successful, CMPIData.state will have the CMPI_badValue
         flag set to true
     @todo add status codes
     */
    CMPIData (*getNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief Test for any elements left in a CMPIEnumeration object.

     Test for any elements left in <tt>en</tt> the CMPIEnumeration object.
     @param en Pointer to the CMPIEnumeration object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus
         structure that upon return will have been updated with the function
         return status.
     @return If successful, returns a CMPIBoolean value indicating the
     test result will be returned, as follows: True indicates that the
     enumeration has more elements left; False indicates that this is
     not the case.

     If not successful, False will be returned
     @todo add status codes
     */
    CMPIBoolean (*hasNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /** @brief Convert a CMPIEnumeration object to a CMPIArray object.

     Converts <tt>en</tt> the Enumeration into a CMPIArray.
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
     @todo add status codes
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

    /** @brief Release a <tt>CMPIDateTime</tt> object.

     Releases a CMPIDateTime object. This indicates to the MB that the
     object (including any objects it contains) will no longer be used
     by the MI. The MB may free the resources associated with the object
     during the call to this function, or later during some
     garbage collection cycle.
     @param dt Pointer to the CMPIDateTime object to be released. That
        object shall have been created using CMPIDateTimeFT.clone()..
     @return CMPIStatus structure indicating the function return status.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
     */
    CMPIStatus (*release) (CMPIDateTime* dt);

    /** @brief Create an independent copy of a CMPIDateTime object.

     Create an independent copy of <tt>dt</tt> a CMPIDateTime object. The
         resulting object must be released explicitly.
     @param dt DateTime this pointer.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status..
     @return If successful,returns a pointer to the copied CMPIDateTime object.

         The returned CMPIDateTime object shall be explicitly released by the MI
         using CMPIDateTimeFT.release().

         If not successful, returns NULL

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
     */
    CMPIDateTime* (*clone) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** @brief Get the value of a CMPIDateTime object in binary
     format. Gets the value of a CMPIDateTime object as a 64-bit
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

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
     */
    CMPIUint64 (*getBinaryFormat) (const CMPIDateTime* dt,
            CMPIStatus* rc);
    /** @brief Get the value of a CMPIDateTime object in the string
          format defined for the CIM datetime type.

     @todo KS_todo how to spec DSP0004 in standard way

     Gets the value of a CMPIDateTime object as a string in the format defined
     in DMTF specification DSP0004 for the CIM datetime type.
     @param dt Pointer to the CMPIDateTime object for this function.
     @param rc Output: If not NULL, points to a CMPIStatus structure that
         upon return has been updated with the function return status.
     @return If successful, returns a pointer to a CMPIString object
     containing the value of a CMPIDateTime object in the format
     defined in DSP0004 for the CIM datetime type.

     The returned CMPIString object shall not be explicitly released by
     the MI, because it may be an internal object of the CMPIDateTime
     object which will be released along with that object, or a new
     object created by the MB which will be released automatically by
     the MB (see Subclause 4.1.7).

     If not successful, returns NULL

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>     */
    CMPIString* (*getStringFormat) (const CMPIDateTime* dt, CMPIStatus* rc);

    /** @brief Test whether a CMPIDateTime object contains an interval value.

     Tests whether DateTime is an interval value.
     @param dt DateTime this pointer.
     @param rc Output: Service return status (suppressed when NULL).
     @return If successful, returns a CMPIBoolean value indicating the test
         result, as follows:
         <ul>
         <li>True indicates that the CMPIDateTime object contains an interval
         value;
         <li>False indicates that this is not an interval.
         </ul>

    If not successful, False will be returned.

    The function return status will indicate one of the following CMPIrc codes:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>	Invalid encapsulated data type
        handle.
    </ul>
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

    /**  @brief  release a CMPIPropertyList object.

     Releases <tt>plist</tt>, a CMPIPropertyList object.
         This indicates to the MB that the object (including any objects it
         contains) will no longer be used by the MI. The MB may free
         the resources associated with the object during the call to
         this function, or later during some garbage collection cycle.
     @param plist Pointer to the CMPIPropertyList object to be released.
     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>Invalid <tt>plist</tt>.
     </ul>
     */
    CMPIStatus (*release) (CMPIPropertyList* plist);

    /** @brief  create an independent copy of a CMPIPropertyList
                object.

     Creates an independent copy of <tt>plist</tt>, the CMPIPropertyList object.
     @param plist Pointer to the CMPIPropertyList object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return If successful, returns a pointer to the copied CMPIPropertyList
         object.

         The returned CMPIPropertyList object shall be explicitly released by
         the MI using CMPIPropertyListFT.release().

         If not successful, returns NULL.

     The following CMPIrc codes shall be recognized:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>Invalid <tt>plist</tt>.
     </ul>
     */
    CMPIPropertyList* (*clone) (const CMPIPropertyList* plist, CMPIStatus* rc);

    /** @brief Test whether a property is in the property list represented
           by a CMPIPropertyList object

       This function tests whether a property is in the property list
       represented by a CMPIPropertyList object.

       The MB's implementation of this function should be efficient. However,
       it is recommended that MIs when returning many instances invoke this
       function only once for each property, and cache the result.

     @param plist Pointer to the CMPIPropertyList object to be for this function.
     @param pname A CMPISstring specifying the name of the property to be
         tested.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return If successful, a CMPIBoolean value indicating the test result
     will be returned, as follows: True indicates that the property is in
     the property list; False indicates that this is not the case.

     If not successful, returns False.

     The following CMPIrc codes shall be recognized:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt>Invalid <tt>plist</tt>.
         <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>Invalid <tt>pname</tt>.
     </ul>
     */
    CMPIBoolean (*isPropertyInList) (const CMPIPropertyList* plist,
            const char* pname, CMPIStatus* rc);

    /** @brief Get CMPIPropertyList as an array of strings.

     Returns the property list represented by <tt>plist</tt>
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
        (possibly different than originally specified in the
        &lt;CMPIBrokerEncFT.newPropertyList()&gt; factory function).

        The returned array shall not be explicitly released by the MI, because
        it may point to an internal data area in the CMPIPropertyList object
        which will be released along with that object, or it may point to a
        new array created by the MB which will be released automatically
        by the MB (see Subclause 4.1.7).
        @todo KS_TODO

        If not successful, returns NULL.
     The following CMPIrc codes shall be recognized:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt> The <tt>plist</tt> handle is
             invalid.
     </ul>
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
 * @brief Function table of
 * [CMPIEnumerationFilter encapsulated data type object]
 * (@ref _CMPIEnumerationFilter).
 * @version 2.1
 */
struct _CMPIEnumerationFilterFT {

    /**
     * CMPI version supported by the MB for this function table.
     * Any earlier CMPI versions are implicitly also supported.
     * See the CMPIVersion<nnn> symbols in cmpidt.h for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /** @brief  release a CMPIResult object.

     Releases a CMPIEnumerationFilter object. This indicates to the MB that
         the object (including any objects it contains) will no longer
         be used by the MI. The MB may free the resources associated with
         the object during the call to this function, or later during
         some garbage collection cycle.
     @param rslt Pointer to the CMPIResult object to be released.
     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <ul>
         <li>CMPI_RC_OK Operation successful.
         <li>CMPI_RC_ERR_INVALID_HANDLE The <tt>ef</tt> handle is invalid.
     </ul>
     @version 2.1
     */
    CMPIStatus (*release) (CMPIEnumerationFilter* ef);

    /** @brief Create an independent copy of a CMPIEnumerationFilter
               object.

     Create an independent copy of the CMPIEnumerationFilter object defined by
     <tt>rslt</tt>.
     @param rslt Pointer to CMPIEnumerationFilter object to be copied.
     @param rc Output: If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status.
     @return If successful, returns a pointer to the copied
         CMPIEnumerationFilter object.

         The returned CMPIEnumerationFilter object shall be explicitly
         released by the MI using CMPIEnumerationFilter.release().

         If not successful, returns NULL.

     The following CMPIrc codes shall be recognized:
     <ul>
         <li>CMPI_RC_OK Operation successful.
         <li>CMPI_RC_ERR_INVALID_HANDLE The <tt>ef</tt> handle is invalid.
     </ul>
     @version 2.1
     */
    CMPIEnumerationFilter* (*clone) (const CMPIEnumerationFilter* ef,
            CMPIStatus* rc);

    /** @brief Instance matches the filter represented by a
           CMPIEnumerationFilter object

       This function tests whether an instance matches the filter
       represented by the CMPIEnumerationFilter object <tt>ef</tt>.
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

     The function return status will indicate one of the following CMPIrc codes:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt> The <tt>ef</tt> handle is
             invalid.
        <li>CMPI_RC_ERR_INVALID_QUERY	The filterQuery is not a valid query
            in the specified filter query language
        <li>CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED A feature of the query
            language is not supported.
        <li>CMPI_RC_FAILED	Error not defined by one of the above codes occurred.
    </ul>
     @version 2.1
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

    /** @brief Perform cleanup for an Instance MI.

     This function shall perform any necessary cleanup operation
     of the library of which this Instance MI <tt>mi</tt> unless the MI
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
     cleanup, by returning <tt>CMPI_RC_NEVER_UNLOAD</tt>. This will cause the
     MB to consider this MI still to be initialized, and the MB may call
     further MI functions of this MI. The MB will not call this function again
     until the MB terminates (at which time the MB calls this function with
     terminating set to true).
    </ul>
     @return Function return status.
     The following CMPIrc codes shall be recognized:
     <ul>
     <li> <tt>CMPI_RC_OK</tt> Operation successful.
     <li> <tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li> <tt>CMPI_RC_DO_NOT_UNLOAD</tt> Operation successful - do
         not unload now.
     <li> <tt>CMPI_RC_NEVER_UNLOAD</tt> Operation successful -  never unload.
     </ul>
     */
    CMPIStatus (*cleanup) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Enumerate instance paths of instances of a given
       class serviced by this MI.

     Enumerate the instance paths of instances of a given class define by
         <tt>classPthy</tt> that are serviced by this MI <tt>mi</tt>>, by
         accessing the underlying managed elements.

         This function is provided by the MI in <tt>mi</tt> the context
         of a particular MI name.

         The class of the <tt>op</tt>> argument for which this
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
         container. Upon successful return, the MI shall have put all instance
         paths representing the result set into this container.
     @param classPath CMPIObjectPath containing namespace and classname components.
         Hostname and key components, if present, have no meaning and
         should be ignored.
     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*enumerateInstanceNames) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* classPath);

    /** @brief Enumerate the instances of a given class serviced by
               this MI.

     This MI function shall enumerate the instances of a given class that are
         serviced by this MI, by accessing the underlying managed elements.

         This function is provided by the MI in context of <tt>mi</tt>
         a particular MI name.

         The class of the <tt>op</tt> argument for which this
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

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*enumerateInstances) (CMPIInstanceMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* classPath , const char** properties);

    /** @brief Get a given instance.

     Get the instance defined by  the CMPIObjectPath <tt>op</tt>.
         This function is provided by the MI in context of <tt>mi</tt>
         a particular MI name.

         The class of the <tt>op</tt> argument for which this function will
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
         MUST NOT include elements for any Properties missing from this list..
     @return CMPIStatus structure indicating the function return status.
     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
    @todo KS_TODD Why no server limits exceeded
    @todo KS_todo should we change to classPath as property name.
    @todo KS_todo Clarify formatting for error codes and also CMPIError usage
     */
    CMPIStatus (*getInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char** properties);

    /** @brief Create an instance of a given class.

     Create an instance of a given class <tt>op</tt> in the namespace of
     that class defined in <tt>op</tt> and the properties defined in
         <tt>inst</tt>.

         This function is provided by the MI in context of a particular MI
         name. The class of the classPath argument for which this function
         will be called by the MB depends on the specifics of how the MB
         relates classes and MI names, which is out of scope for this
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

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ALREADY_EXISTS</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance already exists.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
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

     Modify property values of <tt>mi</tt>, a given instance with properties
     defined in <tt>modInst</tt> and using <tt>properties</tt>, an array of
     pointers to property names, as a filter,

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
         <tt>modInst</tt> are modified

     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NO_SUCH_ PROPERTY</tt></TD><TD>WIPG0220</TD>
     <TD>No such property.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*modifyInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* instPath,
            const CMPIInstance* modInst, const char** properties);

    /** @brief Delete a given instance.

     Delete an existing instance defined by <tt>instPath</tt>.

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

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0228</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*deleteInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op);

    /** @brief  execute a query on a given class and return the
                query result.

     Query the enumeration of instances of the class (and subclasses) defined
     by <tt>op</tt> using <tt>query</tt> expression.

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

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED</tt></TD>
     <TD>WIPG0221</TD>
     <TD>Query language not supported..</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED</tt></TD>
     <TD>WIPG0222</TD>
     <TD>A feature of the query language is not supported..</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_QUERY</tt></TD>
     <TD>WIPG02223</TD>
     <TD>Invalid Query.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*execQuery) (CMPIInstanceMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* classPath,
            const char* query, const char* lang);

#ifdef CMPI_VER_210

    /** @brief enumerate the instances of a given class that are
         serviced by this MI, returning only those that match the
         <tt>filterQuery</tt> argument.

      The CMPIInstanceMIFT.enumerateInstancesFiltered() MI function shall
      enumerate the instances of a given class that are serviced by this MI,
      returning only those instances that match the filterQuery argument,
      by enumerating the underlying managed elements. The returned instances
      shall have their instance paths set. If no such instances are found,
      the function shall return success with an empty result data container.

     @param mi Pointer to to a CMPIInstanceMI structure.
     @param ctx Pointer to to a CMPIContext object containing the invocation context.
     @param rslt Pointer to to a CMPIResult object that is the result data
         container. Upon successful return the MI shall have put all
         instances representing the result set into this container (see Subclause 8.2).
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
     from this list. If the properties argument is NULL, this indicates
     that all properties shall be included in each returned instance.
     @param filterquerylanguage
     @param filterquery defines the query language used by the filterQuery
     argument. If it is NULL, the filterQuery argument is ignored and
     no filtering is performed. Note that FQL is required to be supported
     by MIs as a query language; see Subclause 4.5.
     @param continueOnerror
     @return CMPIStatus structure indicating the function return status.

     The following table lists the CMPIrc codes that shall be used by the MI
     in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports extended
     error handling (see Subclause 8.14):
          <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD>>/TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD><TD>Other error occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED</tt></TD>
         <TD>WIPG0221</TD><TD>Query language not supported.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED</tt></TD>
         <TD>WIPG0222</TD>
         <TD>A feature of the query language is not supported.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_QUERY</tt></TD>
         <TD>WIPG0223</TD><TD>Invalid query.</TD></TR>
     </TABLE>
     @version 2.1
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

    /** @brief Perform cleanup for an @ref CMPIAssociationMI object.

     This function shall perform any necessary cleanup operations prior to the
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

     The following CMPIrc codes shall be recognized:
     <ul>
         <li><tt>CMPI_RC_OK</tt> Operation successful.
         <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
         <li><tt>CMPI_RC_DO_NOT_UNLOAD</tt> Function successful, do not unload
             now; the MB may retry an unload later.
         <li><tt>CMPI_RC_NEVER_UNLOAD</tt> Function successful, never unload;
            the MB will not retry an unload later unless it shuts
            down.
     </ul>
     */
    CMPIStatus (*cleanup) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Enumerate the instances associated with a given source
          instance that are serviced by this MI.

     The CMPIAssociationMIFT.associators() MI function shall enumerate the
     instances associated with a given source instance and that are serviced
     by this MI, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of the instPath argument for which this function will be called
     by the MB depends on the specifics of how the MB relates classes and MI
     names, which is out of scope for this standard. As a result, the MB may
     call this function for classes for which the MI is not responsible. In
     order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether it
     services the class specified in the <tt>instPath</tt> argument.

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
     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*associators) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* asscClass, const char* resultClass, const char* role,
            const char* resultRole, const char** properties);

    /** @brief Enumerate the instance paths of instances associated
       with a given source instance that are serviced by this MI.

     The CMPIAssociationMIFT.associatorNames() MI function shall enumerate the
     instance paths of instances associated with a given source instance and
     that are serviced by this MI, by accessing the underlying managed elements.

    This function is provided by the MI in context of a particular MI name.
    The class of the <tt>instPath</tt> argument for which this function will
    be called by the MB depends on the specifics of how the MB relates classes
    and MI names, which is out of scope for this standard.  As a result, the
    MB may call this function for classes for which the MI is not responsible.
    In order for an MI to be portable across MB implementations with different
    approaches to relate MI names and classes, the MI must check whether it
    services the class specified in the <tt>instPath</tt> argument.

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
         via an Association in which the returned Object plays the specified role
         (i.e. the name of the Property in the Association Class that refers to
         the returned Object MUST match the value of this parameter).
     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD><TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*associatorNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* instPath, const char* assocClass,
            const char* resultClass, const char* role,
            const char* resultRole);

    /** @brief enumerate the instance paths of instances associated
       with a given source instance that are serviced by this MI.

     The CMPIAssociationMIFT.associatorNames() MI function shall
     enumerate the instance paths of instances associated with <tt>instPath</tt>
     a given source instance and that are serviced by this MI, by accessing
     the underlying managed elements.

    If the <tt>assocClass</tt> or <tt>resultClass</tt> filters are specified
    in a call to this function, the MB is not required to scope calls to this
    function to only the MIs that service these classes.  As a result, the MB
    may (and will, in most implementations) call this function for classes in
    the <tt>assocClass</tt> or <tt>resultClass</tt> arguments for which the MI
    is not responsible.  In order for an MI to be portable across MB
    implementations, the MI must check whether it services the classes
    specified in the <tt>assocClass</tt> and <tt>resultClass</tt> arguments.

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
     @param properties If not NULL, the members of the array define one or more Property
     names. Each returned Object MUST NOT include elements for any Properties
     missing from this list
     @return CMPIStatus structure indicating the function return status.
     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*references) (CMPIAssociationMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* op,
            const char* resultClass, const char* role,
            const char** properties);

    /** @brief Enumerate the instance paths of association instances
           referencing a given source instance that are serviced by this MI.

     The CMPIAssociationMIFT.referenceNames() MI function shall enumerate
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
     services the class specified in the <tt>instPath</tt> argument.

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
         to the source Object MUST match the value of this parameter).
     @return CMPIStatus structure indicating the function return status.
     The following CMPIrc codes shall be recognized:
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD><tt>CMPI_RC_OK</tt></TD> <TD>N/A</TD><TD>Function Successful</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt></TD> <TD>WIPG0228</TD>
     <TD>Function is not supported by this MB</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt></TD> <TD>WIPG0249</TD>
     <TD>Invalid filter parameters.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_ACCESS_DENIED</tt></TD> <TD>WIPG0201</TD>
     <TD>Not authorized.</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_NOT_FOUND</tt></TD> <TD>WIPG0213</TD>
     <TD>Instance not found. Instead of using this return code if the source
     instance does not exist, the MI should return success with an empty result
     data container. The MB shall treat this return code as a successful
     return of an empty result set. (Deprecated)</TD>
     </TR>
     <TR><TD><tt>CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED</tt></TD><TD>WIPG0240</TD>
     <TD>Limits exceeded.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0243</TD>
     <TD>Timeout occurred.</TD></TR>
     <TR><TD><tt>CMPI_RC_ERR_FAILED</tt></TD><TD>WIPG0227+implementation
     specific message</TD> <TD>Other error occurred.</TD></TR>
     </TABLE>
     */
    CMPIStatus (*referenceNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* instPath, const char* resultClass,
            const char* role);

#ifdef CMPI_VER_210

    /** @brief TODO
     @todo KS_TODO
     */
    CMPIStatus (*associatorsFiltered)
        ( CMPIAssociationMI* mi, const CMPIContext* ctx, const CMPIResult* rslt,
         const CMPIObjectPath* instPath, const char* assocClass,
         const char* resultClass, const char* role, const char* resultRole,
         const char** properties, const char* filterQueryLanguage,
         const char* filterQuery, CMPIBoolean continueOnError);

    /** @brief enumerate the association instances referencing a
     *         given source instance that are serviced by this MI,
     *         returning only those instances that match the
     *         filterQuery argument
     *  @todo KS_TODO
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

    /** @brief Perform cleanup for an Instance MI.

     The CMPIMethodMIFT.cleanup() function shall perform any
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

     The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_DO_NOT_UNLOAD</tt> Operation successful - do not unload
         now.
     <li><tt>CMPI_RC_NEVER_UNLOAD</tt> Operation successful - never unload.
     </ul>
     */
    CMPIStatus (*cleanup) (CMPIMethodMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Invoke a method on a target object.

     The CMPIMethodMIFT.invokeMethod() MI function shall invoke a named,
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
        shall be returned using CMPIResultFT.returnInstance().
    <li>Return values declared with type <tt>ref</tt>
         &lt;classname&gt; (see Subclause 4.1.3) shall be returned
         using CMPIResultFT.returnObjectPath().
    <li>Any other return values shall be returned using
        CMPIResultFT.returnData().
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
     @param out[in out] Pointer to to an empty CMPIArgs object (whether the method has
         any output parameters or not) that, upon successful return
         of the method, shall have been updated by the MI to contain
         the method output parameters.
     @return CMPIStatus structure indicating the function return status.

     The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt> Operation not supported by this MI.
     <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt> Not authorized.
     <li><tt>CMPI_RC_ERR_NOT_FOUND</tt> Instance not found.
     <li><tt>CMPI_RC_ERR_METHOD_NOT_AVAILABLE</tt> Method not available.
     <li><tt>CMPI_RC_ERR_METHOD_NOT_FOUND</tt> Method not found.
     </ul>
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

    /** @brief Perform cleanup for a Property MI <b>(Deprecated)</b>.

     This function shall perform any necessary cleanup operations prior to the
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
     The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_DO_NOT_UNLOAD</tt> Function successful - do not unload
         now; the MB may retry an unload later..
     <li><tt>CMPI_RC_NEVER_UNLOAD</tt> Function successful - never unload;
         the MB will not retry an unload later unless it shuts down.
     </ul>

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property client operations in DMTF
     specifications.
     */
    CMPIStatus (*cleanup) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating); /*Deprecated*/

    /** @brief Set or modify the value of a property of a given
               instance <b>(Deprecated)</b>.

     Set or modify the named property value of an instance defined by
     the <tt>instPath</tt> parameter.

     This function is provided by the MI in context of a particular MI name.
         The class of the instPath argument for which this function will be
         called by the MB depends on the specifics of how the MB relates
         classes and MI names, which is out of scope for this standard. As
         a result, the MB may call this function for classes for which the
         MI is not responsible. In order for an MI to be portable across
         MB implementations with different approaches to relate MI names
         and classes, the MI must check whether it services the class
         specified in the instPath argument.
     @param mi Pointer to a <tt>CMPIPropertyMI</tt>structure.
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
     status. The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_TYPE_MISATCH</tt> type does not correspond
     to class-defined type.
     <li><tt>CMPI_RC_ERR_INVALID_HANDLE</tt> The <tt>inst</tt> handle is
         invalid.
     </ul>
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

     Get the named property value of an instance defined by the
         <tt>>instPath</tt> parameter.
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
            CMPIResultFT.returnInstance().
         <li>The values of references (see Subclause 4.1.3) shall be returned
            using CMPIResultFT.returnObjectPath().
         <li>Any other property values shall be returned using
            CMPIResultFT.returnData().
        </ul>
     @param instPath Pointer to a CMPIObjectPath object that references
         the given instance and that contains the namespace, class name,
         and key components. The hostname component, if present, has no
         meaning and should be ignored.
     @param name Pointer to a string specifying the property name
     @return CMPIStatus structure indicating the function return
     status. The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt> Not authorized.
     <li><tt>CMPI_RC_ERR_INVALID_NAMESPACE</tt> The namespace is
     invalid.
     <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt> The parameter is invalid.
     <li><tt>CMPI_RC_ERR_INVALID_CLASS</tt> The CIM class does not exist
        in the specified namespace.
     <li><tt>CMPI_RC_ERR_NOT_FOUND</tt> Instance not found.
     <li><tt>CMPI_RC_ERR_NO_SUCH_PROPERTY</tt> Entry not found.
     </ul>

     @deprecated This function is deprecated since CMPI 2.1,
     in accord with the deprecation of property client operations in DMTF
     specifications.
     */
    CMPIStatus (*getProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            const CMPIResult* rslt, const CMPIObjectPath* instPath,
            const char* name);

#ifdef CMPI_VER_200

    /** @brief Set or modify the value of a property of a given
               instance
       <b>(Deprecated)</b>.

     @todo KS_todo resolve what to do about this function

     Add/replace a named Property value and origin. Removed in CMPI
     2.1
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

    /** @brief Perform cleanup for an Indication MI.

    This function shall perform any necessary cleanup operations prior to the
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
    The following CMPIrc codes shall be recognized:
    <ul>
    <li><tt>CMPI_RC_OK</tt> Operation successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
    <li><tt>CMPI_RC_DO_NOT_UNLOAD</tt> Function successful, do not
        unload now; the MB may retry an unload later..
    <li><tt>CMPI_RC_NEVER_UNLOAD</tt> Function successful, never unload;
        the MB will not retry an unload later unless it shuts down.
    </ul>
    */
    CMPIStatus (*cleanup) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /** @brief Ask an MI to verify whether an indication filter is
       supported by the MI.

     This MI function shall verify whether  an indication filter is
         supported by the MI.

     An MB implementation is free to choose whether this function is called
         when the MB starts up independently of whether or not there are
         any subscriptions for the filter, or only when the first
         subscription to the filter is made.

     In any case, for any particular filter this function is called on,
     it shall be called by the MB before CMPIIndicationMIFT.activateFilter()
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
      @param owner The owner argument points to a string specifying the
          destination owner.
      @param owner The owner argument is the destination owner.
      @return This function shall structure containing the service return
      status.
      The following CMPIrc codes shall be recognized:
      <ul>
      <li><tt>CMPI_RC_OK</tt> Operation successful.
      <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
      <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt> Operation not supported by this
      <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt> Not authorized.
      <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt> Invalid query or too complex.
      </ul>

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

     Ask the MI whether polling mode should be used.

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
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt> Operation not supported by this MI.
     <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt> Not authorized.
     <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt> Invalid query or too complex.
     </ul>

     @deprecated This function is deprecated since CMPI 2.1,
     because the concept of indication polling has been deprecated in CMPI 2.1.
     */
    CMPIStatus (*mustPoll) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            const CMPISelectExp* filter, const char* className,
            const CMPIObjectPath* classPath);

    /** @brief informs the MI that an indication filter has become active.

     The CMPIIndicationMIFT.activateFilter() MI function informs the MI
     that the specified indication filter has become active. This function
     shall be called by the MB when a client creates a subscription to
     an indication filter, and if persisted subscriptions are supported
     by the MB, for any persisted subscriptions to indication filters
     when the MB starts up.

     An MB implementation is free to choose whether this function
     is called upon each subscription to a particular filter, or only upon
     the first subscription (see the firstActivation argument). As a result,
     the MI will always be informed about the first activation of the filter
     after having been inactive, but has no guarantee to be informed about
     subsequent activations of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI needs to start the monitoring of any resources that
     trigger indications that are covered by the specified indication
     filter, during the first activation of the filter. For the concept
     of coverage of indications by an indication filter, see DSP1054.

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext structure containing the Invocation
         Context.
     @param filter Pointer to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is activated.
     @param className argument points to a string specifying the class name
         extracted from the FROM clause of the filter specification contained
         in the filter argument. If the filter specification contains joins,
         it is undefined which of the joined classes is used for this argument.
     @param classPath Pointer to a CMPIObjectPath object that is a
         reference to a class or to a namespace, as follows:
         <ul>
            <li>If the filter specification covers lifecycle indications,
            the CMPIObjectPath object specifies the class path of the class
            for which lifecycle monitoring is required. Note that this class
            may be a subclass of the class specified in the <tt>>className</tt>
            argument, for example when the filter query constrains the
            class to be monitored using constructs such as the <tt>ISA</tt>
            operator of CQL.
            <li>If the filter specification covers process indications,
            the CMPIObjectPath object specifies the namespace path of
            the origin namespace of the process indications.
        </ul>
     <tt>className</tt>.
     @return CMPIStatus structure containing the function return status.
     The following CMPIrc codes shall be recognized:
     <ul>
     <li><tt>CMPI_RC_OK</tt> Operation successful.
     <li><tt>CMPI_RC_ERR_FAILED</tt> Unspecific error occurred.
     <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt> Operation Function or filter is
         not supported by this MI.
     <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt> Not authorized.Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter itself would not be authorized.
     <li><tt>CMPI_RC_ERR_INVALID_QUERY</tt> Invalid query or too complex.
     </ul>
     */
    CMPIStatus (*activateFilter) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPISelectExp* filter,
            const char* className, const CMPIObjectPath* classPath,
            CMPIBoolean firstActivation);

    /** @brief Inform the MI that an indication filter has become
               inactive.

     Inform the MI that monitoring using this filter should stop.
         This function shall be called by the MB when a client deletes a
         subscription to an indication filter, and for any existing
         subscriptions to indication filters when the MB shuts down.

     The function invocation mandates the MI to stop monitoring the resource
     using this filter.

     An MB implementation is free to choose whether this function is called
     for each deletion of a subscription to a particular filter, or
     only upon the last deletion (see the lastDeActivation argument).
     As a result, the MI will always be informed about the last
     deactivation of the filter, but has no guarantee to be informed
     about prior deactivations of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI should stop the monitoring of any resources that
     trigger indications that are covered by the specified indication
     filter, during the last deactivation of the filter. For the concept
     of coverage of indications by an indication filter, see DSP1054.

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
        filter argument. If the filter specification contains joins,
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

    /** @brief Inform the MI that the MB is now ready to process the
           delivery of indications.

    Informs the MI that the MB is now ready to process the delivery of
        indications. This function is typically called when the MB is starting
        up its indication services (from either a permanent or temporary
        shutdown of its indication services).

        The relative order in which an MB enables indications using this
        function and activates filters and filter collections is not defined.
        As a result, MIs need to track the readiness of the MB to process
        the delivery of indications and check that readiness before calling
        the CMPIBrokerFT.deliverIndication() function.

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx Pointer to a CMPIContext object containing the context data
         for the invocation (see Subclause 8.1). There is no defined client
         operation that determines the context data. As a result, not all
         context data entries may be present.
     @return CMPIStatus structure indicating the function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     */
    CMPIStatus (*enableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** @brief Inform the MI that the MB is no longer ready to
           process the delivery of indications.

    Informs the MI that the MB is no longer ready to process the delivery of
        indications.  This function is typically called when the MB is shutting
        down its indication services either temporarily or permanently.

    The relative order in which an MB disables indications using this
        function and deactivates filters and filter collections is not
        defined. As a result, MIs need to track the readiness of the MB
        to process the delivery of indications and check that readiness
        before calling the CMPIBrokerFT.deliverIndication() function.

     @param mi Pointer to a CMPIIndicationMI structure.
     @param ctx The ctx argument is a pointer to a CMPIContext structure
       containing the Invocation Context.   There is no defined client
       operation that determines the context data. As a result, not all
       context data entries may be present.
     @return CMPIStatus structure containing the function return status.
     The following CMPIrc codes shall be recognized:
     CMPI_RC_OK Operation successful.
     CMPI_RC_ERR_FAILED Unspecific error occurred.
     CMPI_RC_ERR_NOT_SUPPORTED Operation not supported by this MI.
     */
    CMPIStatus (*disableIndications) (CMPIIndicationMI* mi,
            const CMPIContext* ctx);

    /** @brief Ask an MI to verify whether an indication filter
           collection is supported by the MI.

       This function shall verify whether an indication filter collection
       is supported by the MI.

    An MB implementation is free to choose whether this function
       is called when the MB starts up independently of whether or not
       there are any subscriptions for the filter collection, or only
       when the first subscription to the filter collection is made.

       In any case, for any particular filter collection this function
       is called on, it shall be called by the MB before
       CMPIIndicationMIFT.activateFilterCollection() is called for the
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

        The following CMPIrc codes shall be recognized:
        CMPI_RC_OK	Function successful, filter collection is supported by the MI.
        CMPI_RC_ERR_FAILED	Unspecific error occurred.
        CMPI_RC_ERR_NOT_SUPPORTED	Function is not supported by this MI, or filter collection is not supported by this MI.
        CMPI_RC_ERR_ACCESS_DENIED	Not authorized.
            Note: This return code indicates general authorization related issues and does not specifically indicate that the filter collection itself would not be authorized.
        CMPI_RC_ERR_INVALID_PARAMETER	Invalid indication filter collection.
     @version 2.1
        */
    CMPIStatus (*authorizeFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst);

    /** @brief Inform the MI that an indication filter collection
           has become active.

       The CMPIIndicationMIFT.activateFilterCollection() function informs the
       MI that the specified indication filter collection has become active.
       This function shall be called by the MB when a client creates a
       subscription to an indication filter collection, and if persisted
       subscriptions are supported by the MB, for any persisted subscriptions
       to indication filter collections when the MB starts up.

       An MB implementation is free to choose whether this function is
       called upon each subscription to a particular filter collection, or
       only upon the first subscription (see the <tt>firstActivation</tt>
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
       indication filter collection, see DSP1054.

       As described in DSP1054, a filter collection conceptually has
       members, but these members do not need to be instantiated using
       CIM. An MB shall handle subscriptions to a filter collection by
       calling CMPIIndicationMIFT.activateFilterCollection() for that
       filter collection; the MB shall not additionally call the activation
       functions for the individual members of the filter collection.
       The implementation of CMPIIndicationMIFT.activateFilterCollection()
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
       @return CMPIStatus structure containing the function return status

     The following CMPIrc codes shall be recognized:
     <ul>
        <li><tt>CMPI_RC_OK</tt>	Function successful.
        <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
        <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not
            supported by this MI, or filter collection is not
            supported by this MI.
        <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized.
        Note: This return code indicates general authorization related issues
            and does not specifically indicate that the filter collection
            itself would not be authorized.
        <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	Invalid
            indication filter collection.
       </ul>
       @version 2.1
       @todo fix format codes.
       */
    CMPIStatus (*activateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean firstActivation);

    /** @brief  Informs the MI that an indication filter collection has
       become inactive.

    The CMPIIndicationMIFT.deActivateFilterCollection() function informs
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
    (see the lastDeActivation argument). As a result, the MI will
    always be informed about the last deactivation of the filter
    collection, but has no guarantee to be informed about prior
    deactivations of the same filter collection.

    Generally, MIs should disable the monitoring of any resources for
    indications if there is no interest in them. Consequently, in this
    function the MI should stop the monitoring of any resources that
    trigger indications that are covered by the specified indication
    filter collection, during the last deactivation of the filter. For
    the concept of coverage of indications by an indication filter
    collection, see DSP1054.

    As described in DSP1054, a filter collection conceptually has
    members, but these members do not need to be instantiated using CIM.
    An MB shall handle deletions to subscriptions to a filter collection
    by calling CMPIIndicationMIFT.deActivateFilterCollection() for that
    filter collection; the MB shall not additionally call the deactivation
    functions for the individual members of the filter collection.
    The implementation of CMPIIndicationMIFT.deActivateFilterCollection()
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

    The following CMPIrc codes shall be recognized:
    <ul>
    <li><tt>CMPI_RC_OK</tt>	Function successful.
    <li><tt>CMPI_RC_ERR_FAILED</tt>	Unspecific error occurred.
    <li><tt>CMPI_RC_ERR_NOT_SUPPORTED</tt>	Function is not supported by
        this MI, or filter collection is not supported by this MI.
    <li><tt>CMPI_RC_ERR_ACCESS_DENIED</tt>	Not authorized. Note: This
        return code indicates general authorization related issues and
        does not specifically indicate that the filter collection itself
        would not be authorized.
    <li><tt>CMPI_RC_ERR_INVALID_PARAMETER</tt>	Invalid indication
        filter collection.
    </ul>
     @version 2.1
     */
    CMPIStatus (*deActivateFilterCollection) (CMPIIndicationMI* mi,
            const CMPIContext* ctx, const CMPIInstance* collInst,
            CMPIBoolean lastDeActivation);

};

/**
 * @}
 */

/** @todo KS_todo cmpimacs not required. Removed
 #include "cmpimacs.h"
 */

#ifdef __cplusplus
}
#endif

#endif /*_CMPIFT_H_ */
