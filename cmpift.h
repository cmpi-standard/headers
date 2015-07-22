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

#include "cmpios.h"
#include "cmpidt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup mi-factory
 * @{
 *   For details on how MI factory functions are used by an MB, including
 *   precedence in the presence of both generic and MI-specific factory
 *   functions, and extensibility,
 *   see Subclause 6.1 of the @ref ref-cmpi-standard "CMPI Standard".
 */

/**
 @defgroup mi-factory-specific MI-specific MI factory function.

 <b>@ref CMPI_EXTERN_C CMPI\<mitype\>MI* \<miname\>_Create_\<mitype\>MI(
 const @ref CMPIBroker* mb, const @ref CMPIContext* ctx,
 @ref CMPIStatus* rc);</b>

 @ref mi-factory-specific "\<miname\>_Create_\<mitype\>MI()" is an
 MI-specific factory function for an MI and is responsible for intializing the
 MI of type \<mitype\> with the predefined name \<miname\>.

 \<mitype\> can be one of:
 @li Instance
 @li Association
 @li Property (**Deprecated**)
 @li Method
 @li Indication

 While this function executes, the MB will not call any other MI functions for
 this MI. This function will be called once for a specific MI, even if that MI
 services more than one namespace.

 This function shall be declared with the @ref CMPI_EXTERN_C modifier or
 an equivalent modifier; the name of this function shall be exported from the
 MI load library.

 @param mb Points to a CMPIBroker structure.
     This structure can be used throughout the life of this MI function group
     to invoke MB services.
 @param ctx Points to a CMPIContext object containing the context data
     for the invocation.
     This CMPIContext object contains the @ref CMPIInitNameSpace entry
     indicating the namespace for which this MI is to be initialized.
     If this MI services more than one namespace, the @ref CMPIInitNameSpace
     entry indicates one of those namespaces.
 @param [out] rc Points to a CMPIStatus structure that upon return shall
     have been updated with the function return status.
 @return @parblock
     If successful, a pointer to a valid CMPI\<mitype\>MI structure
     (CMPIInstanceMI, CMPIAssociationMI, CMPIPropertyMI, CMPIMethodMI,
     CMPIIndicationMI) for the MI identified by \<mitype\> and \<miname\>
     shall be returned, and the MB will consider this MI to be initialized
     (that is, functioning).

     If not successful, NULL shall be returned, and the MI identified by
     \<mitype\> and \<miname\> is considered uninitialized (that is,
     malfunctioning) and will not be used by the MB. Specifically, the
     cleanup function for this MI (e.g. CMPIInstanceMIFT.cleanup()) will not be
     invoked by the MB in that case.
 @endparblock

 @par Errors
 The following @ref CMPIrc codes shall be used by the MI in the
 function return status:
 @li `CMPI_RC_OK` - Function successful.
 @li `CMPI_RC_ERR_NOT_SUPPORTED` - MI type not supported for this MI name.
 @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
 @li `CMPI_RC_ERR_FAILED` - Other error occurred.

 CMPI 2.1 documented these return codes for the first time. For backwards
 compatibility, MBs conforming to CMPI 2.1 that use MIs conforming to prior
 CMPI releases shall tolerate other uses of these return codes as well as
 additional return codes.

 @deprecated The \<miname\>_Create_PropertyMI() function is deprecated since
     CMPI 2.1, in accord with the deprecation of property client operations in
     DMTF specifications.
*/

/**
 @defgroup mi-factory-generic Generic MI factory function.

 <b>@ref CMPI_EXTERN_C CMPI\<mitype\>MI* _Generic_Create_\<mitype\>MI(
 const @ref CMPIBroker* mb, const @ref CMPIContext* ctx, const char* miName,
 @ref CMPIStatus* rc);</b>

 @ref mi-factory-generic "_Generic_Create_\<mitype\>MI()" is a generic factory
 function for an MI and is responsible for intializing the MI of type
 \<mitype>\ with the name passed in @p miName.

 \<mitype\> can be one of:
 @li Instance
 @li Association
 @li Property (**Deprecated**)
 @li Method
 @li Indication

 While this function executes, the MB will not call any other MI functions for
 this MI. This function will be called once for a specific MI, even if that MI
 services more than one namespace.

 This function shall be declared with the @ref CMPI_EXTERN_C modifier or
 an equivalent modifier; the name of this function shall be exported from the
 MI load library.

 @param mb Points to a CMPIBroker structure.
     This structure can be used throughout the life of this MI function group
     to invoke MB services.
 @param ctx Points to a CMPIContext object containing the context data
     for the invocation.
     This CMPIContext object contains the @ref CMPIInitNameSpace entry
     indicating the namespace for which this MI is to be initialized.
     If this MI services more than one namespace, the @ref CMPIInitNameSpace
     entry indicates one of those namespaces.
 @param miName Name of the MI to be initialized.
 @param [out] rc Points to a CMPIStatus structure that upon return shall
     have been updated with the function return status.
 @return @parblock
     If successful, a pointer to a valid CMPI\<mitype\>MI structure
     (CMPIInstanceMI, CMPIAssociationMI, CMPIPropertyMI, CMPIMethodMI,
     CMPIIndicationMI) for the MI identified by \<mitype\> and @p miName shall
     be returned, and the MB will consider this MI to be initialized (that is,
     functioning).

     If not successful, NULL shall be returned, and the MI identified by
     \<mitype\> and @p miName is considered uninitialized (that is,
     malfunctioning) and will not be used by the MB. Specifically, the
     cleanup function for this MI (e.g. CMPIInstanceMIFT.cleanup()) will not be
     invoked by the MB in that case.
 @endparblock

 @par Errors
 The following @ref CMPIrc codes shall be used by the MI in the
 function return status:
 @li `CMPI_RC_OK` - Function successful.
 @li `CMPI_RC_ERR_NOT_FOUND` - MI name not found.
 @li `CMPI_RC_ERR_NOT_SUPPORTED` - MI type not supported for this MI name.
 @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
 @li `CMPI_RC_ERR_FAILED` - Other error occurred.

 CMPI 2.1 documented these return codes for the first time. For backwards
 compatibility, MBs conforming to CMPI 2.1 that use MIs conforming to prior
 CMPI releases shall tolerate other uses of these return codes as well as
 additional return codes.

 @deprecated The _Generic_Create_PropertyMI() function is deprecated since
     CMPI 2.1, in accord with the deprecation of property client operations in
     DMTF specifications.
*/

/**
 * @}
 * @addtogroup mb-tables
 * @{
 */

/**
 * @brief CMPIBroker structure.
 *
 * The CMPIBroker structure is the anchor object of the MB (Management Broker,
 * also known as CIMOM). A pointer to this structure is passed to the MI in its
 * factory function (see @ref mi-factory "MI Factory Functions") and needs to
 * be passed to many MB services.
 */
typedef struct _CMPIBroker {

    /**
     * @brief Opaque pointer to MB-specific implementation data for the MB.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for some MB services (thread
     *     registration, indications services, and client services).
     */
    const CMPIBrokerFT* bft;

    /**
     * @brief Pointer to the function table for some MB services (factory and
     *     miscellaneous services).
     */
    const CMPIBrokerEncFT* eft;

    /**
     * @brief Pointer to the function table for MB operating system
     *     encapsulation services.
     */
    const CMPIBrokerExtFT* xft;

#ifdef CMPI_VER_200

    /**
     * @brief Pointer to the function table for MB memory enhancement services.
     *
     * If the
     * @ref CMPI_MB_Supports_MemEnhancements "Memory Enhancement Services"
     * capability is not available, this pointer is NULL.
     *
     * @added200 Added in CMPI 2.0.
     */
    const CMPIBrokerMemFT* mft;

#endif /*CMPI_VER_200*/

} CMPIBroker;

/**
 * @brief Function table for some MB services (thread registration, indications
 *     services, and client services).
 *
 * This function table is referenced by the CMPIBroker structure, and provides
 * @ref broker-thread-reg "Thread Registration Services",
 * @ref broker-indications "Indications Services", and
 * @ref broker-client "Client Services (\"up-calls\")".
 *
 * For functions that are not supported, their function pointers in this
 * function table shall not be NULL, but shall point to a function that can be
 * called and then indicate back to the caller that it is not supported, as
 * specified in the description of the function.
 */
typedef struct _CMPIBrokerFT {

    /**
     * @brief MB capabilities.
     *
     * For a definition of the test masks, see
     * @ref mb-capabilities "MB Capabilities".
     */
    unsigned int brokerCapabilities;

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     *
     * Note: This is not the version of the MB.
     * @convfunction CBBrokerVersion()
     */
    CMPIVersion brokerVersion;

    /**
     * @brief Informal MB-specific name for this MB.
     *
     * @convfunction CBBrokerName()
     */
    const char* brokerName;

    /**
     *   @addtogroup broker-thread-reg
     *   @{
     */

    /**
     @brief Prepare the MB to accept a new thread that will be using MB
         functions.

     CMPIBrokerFT.prepareAttachThread() prepares the MB to accept a new thread
     that will be using MB functions. This function is expected to be called in
     the existing thread.

     @param mb Points to a CMPIBroker structure.
     @param ctx
     @parblock
         Points to the CMPIContext object that was used to invoke the MI
         function that calls this MB function.

         The opaque part of the CMPIContext object can be used by the MB to
         carry the MB internal security context. Such MBs can maintain the
         security context for the new thread in the returned copy of the
         CMPIContext object.
     @endparblock
     @return @parblock
         If successful, a pointer to a CMPIContext object that is to be used by
         the thread to be attached will be returned. This is used for
         subsequent CMPIBrokerFT.attachThread() and CMPIBrokerFT.detachThread()
         invocations.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     For historical reasons, no additional error information is passed back.

     @convfunction CBPrepareAttachThread()
    */
    CMPIContext* (*prepareAttachThread) (const CMPIBroker* mb,
        const CMPIContext* ctx);

    /**
     @brief Inform the MB that the current thread will begin using MB functions.

     CMPIBrokerFT.attachThread() informs the MB that the current (newly created)
     thread with the specified context will begin using MB functions.

     @param mb Points to a CMPIBroker structure.
     @param ctx
     @parblock
         Points to the CMPIContext object that was returned by a prior call to
         CMPIBrokerFT.prepareAttachThread().

         The opaque part of the CMPIContext object can be used by the MB to
         carry the MB internal security context. Such MBs can set up the
         security context for the current thread in this function.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p ctx handle is invalid.

     @convfunction CBAttachThread()
    */
    CMPIStatus (*attachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /**
     @brief Inform the MB that the current thread will no longer use MB
         functions.

     CMPIBrokerFT.detachThread() informs the MB that the current thread will no
     longer be using MB functions.

     @param mb Points to a CMPIBroker structure.
     @param ctx
     @parblock
         Points to the CMPIContext object that was returned by the prior call to
         CMPIBrokerFT.prepareAttachThread().

         The opaque part of the CMPIContext object can be used by the MB to
         carry the MB internal security context. Such MBs can set up the
         security context for the current thread in this function.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p ctx handle is invalid.

     @convfunction CBDetachThread()
    */
    CMPIStatus (*detachThread) (const CMPIBroker* mb, const CMPIContext* ctx);

    /**
     *   @}
     *   @addtogroup broker-indications
     *   @{
     */

    /**
     @brief Request delivery of an indication.

     CMPIBrokerFT.deliverIndication() requests the delivery of an indication.

     The MB will locate pertinent subscribers and send the indication to each
     of them.

     This function may be called by an MI regardless of whether or not there
     are any active indication filters or indication filter collections
     that cover the indication to be delivered. If there are no such filters
     or filter collections, this will not cause the function to fail. For
     the concept of coverage of indications by an indication filter or
     indication filter collection, see @ref ref-dmtf-dsp1054 "DSP1054".

     This function may be called by an MI regardless of whether or not
     the MB is ready for processing the delivery of indications, as
     communicated to the MI via CMPIIndicationMIFT.enableIndications() and
     CMPIIndicationMIFT.disableIndications().  If the MB is not
     ready for processing the delivery of indications, this will not
     cause the function to fail. The MB implementation may choose to
     drop the indication in this case, or to queue the indication
     for later delivery.

     This function may be called by any MI function, and by any threads
     created by MIs that are registered with the MB (see
     @ref broker-thread-reg "Thread Registration Services").

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to the CMPIContext object that was used to invoke the MI
         function that calls this MB function, or that was used to register the
         thread that calls this MB function.
     @param ns Name of the *origin namespace* of the indication (see
         @ref ref-dmtf-dsp1054 "DSP1054" for a definition).
     @param ind Points to a CMPIInstance object containing the indication
         instance. An instance path specified in that CMPIInstance object is
         meaningless for indication instances and will be ignored by the MB.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.@n
         Note: If the MB is not ready for processing the delivery of
         indications, it may drop the indication and still return success.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb, @p ctx, or @p ind handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The namespace specified by
         @p ns is invalid, or the indication instance specified by
         @p ind is invalid.
     @capindications This function is part of the Indications capability.

     @convfunction CBDeliverIndication()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
    */
    CMPIStatus (*deliverIndication) (const CMPIBroker* mb,
        const CMPIContext* ctx, const char* ns, const CMPIInstance* ind);

    /**
     *   @}
     *   @addtogroup broker-client
     *   @{
     */

    /**
     @brief Enumerate the instance paths of the instances of a given class (and
         its subclasses).

     CMPIBrokerFT.enumerateInstanceNames() enumerates the instance paths of the
     instances of a given class (and its subclasses).

     The target MIs are identified by the MB based on @p classPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param classPath Points to a CMPIObjectPath object that references the
         given class and that shall contain the namespace and class name
         components. The hostname and key components, if present, will be
         ignored by the MB.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIObjectPath objects that represent the
         enumerated instance paths.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p classPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - No instances found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capread This function is part of the Basic Read capability.

     @convfunction CBEnumInstanceNames()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE` and `CMPI_RC_ERR_INVALID_CLASS`. It is
         believed that MB implementations needed to use these return codes
         already, so that their addition only fixes an omission in this
         standard and does not create a compatibility issue for MIs that
         conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*enumerateInstanceNames) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* classPath,
        CMPIStatus* rc);

    /**
     @brief Get an existing instance.

     CMPIBrokerFT.getInstance() gets an existing instance.

     The target MI is identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         The MI may specify invocation flags (@ref CMPIInvocationFlags entry)
         as needed.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be retrieved and that shall contain the namespace, class
         name, and key components. The hostname component, if present, will be
         ignored by the MB.
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The returned instance will not include
         elements for any properties missing from this list. If @p properties
         is NULL, this indicates that all properties will be included
         in the returned instance.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIInstance object containing the
         retrieved instance will be returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.
         Specifically, the MI shall not use CMPIBrokerMemFT.freeInstance() on
         the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb, @p ctx or @p instPath handle
         is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property list specified
         in @p properties is invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capread This function is part of the Basic Read capability.

     @convfunction CBGetInstance()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
    */
    CMPIInstance* (*getInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* instPath, const char** properties,
        CMPIStatus* rc);

    /**
     @brief Create an instance of a given class.

     CMPIBrokerFT.createInstance() creates an instance of a given class.

     The target MI is identified by the MB based on @p classPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param classPath Points to a CMPIObjectPath object that references the
         class of the instance to be created and that shall contain the
         namespace and class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @param newInst Points to a CMPIInstance object specifying property values
         for the new instance. The object path component within this
         CMPIInstance object has no meaning; it should not be provided by the
         calling MIs. The MB will pass the definition of the new instance on to
         the target MI, unchanged.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIObjectPath object containing the
         assigned instance path will be returned.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.
         Specifically, the MI shall not use CMPIBrokerMemFT.freeObjectPath()
         on the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb, @p ctx, @p classPath, or
         @p newInst handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The instance specified in
         @p inst is invalid.
     @li `CMPI_RC_ERR_ALREADY_EXISTS` - Instance already exists.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capmanipulation This function is part of the Instance Manipulation
         capability.

     @convfunction CBCreateInstance()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The use of the key component within @p classPath
         is deprecated since CMPI 2.1; this key component should not be provided
         by the calling MIs. Initial key values can be supplied as properties
         in @p newInst.
    */
    CMPIObjectPath* (*createInstance) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* classPath,
        const CMPIInstance* newInst, CMPIStatus* rc);

    /**
     @brief Modify property values of an existing instance.

     CMPIBrokerFT.modifyInstance() modifies property values of an existing
     instance.

     The target MI is identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references
         the instance to be modified and that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @param modInst Points to a CMPIInstance object specifying new
         values for the properties to be modified. The object path
         component within this CMPIInstance object has no meaning; it
         should not be provided by the calling MIs and should not
         be used by the MB.
     @param propertyList If not NULL, defines the list of property names to
         be modified. If NULL, all properties will be modified. The end of
         the list is signaled by a NULL character pointer.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb, @p ctx, @p instPath, or
         @p modInst handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The instance specified in
         @p modInst, or the properties specified in @p propertyList are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capmanipulation This function is part of the Instance Manipulation
         capability.

     @convfunction CBModifyInstance()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
    */
    CMPIStatus (*modifyInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* instPath, const CMPIInstance* modInst,
        const char** properties);

    /**
     @brief Delete an existing instance.

     CMPIBrokerFT.deleteInstance() deletes an existing instance.

     The target MI is identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be deleted and that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capmanipulation This function is part of the Instance Manipulation
         capability.

     @convfunction CBDeleteInstance()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE` and `CMPI_RC_ERR_INVALID_CLASS`. It is
         believed that MB implementations needed to use these return codes
         already, so that their addition only fixes an omission in this
         standard and does not create a compatibility issue for MIs that
         conform to CMPI 2.0.
    */
    CMPIStatus (*deleteInstance) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* instPath);

    /**
     @brief Execute a query on a given class and return the query result.

     CMPIBrokerFT.execQuery() executes a query on a given class and returns the
     query result.

     The target MI is identified by the MB based on @p classPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param classPath Points to a CMPIObjectPath object that references
         the given class to be queried and that shall contain the namespace
         and class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @param query Select expression.
     @param lang Query language.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the query
         result.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p classPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - Query language not
         supported.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capqueryexec This function is part of the Query Execution capability.

     @convfunction CBExecQuery()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE` and `CMPI_RC_ERR_INVALID_CLASS`. It is
         believed that MB implementations needed to use these return codes
         already, so that their addition only fixes an omission in this
         standard and does not create a compatibility issue for MIs that
         conform to CMPI 2.0.
    */
    CMPIEnumeration* (*execQuery) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* classPath,
        const char* query, const char* lang, CMPIStatus* rc);

    /**
     @brief Enumerate the instances of a given class (and its subclasses).

     CMPIBrokerFT.enumerateInstances() enumerates the instances of a given
     class (and its subclasses). The set of properties in the result instances
     can be controlled via @p properties and via the CMPI_FLAG_LocalOnly and
     CMPI_FLAG_DeepInheritance flags in the @ref CMPIInvocationFlags entry of
     @p ctx.

     The target MIs are identified by the MB based on @p classPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         The MI may specify invocation flags (@ref CMPIInvocationFlags entry)
         as needed.
     @param classPath Points to a CMPIObjectPath object that references
         the given class and that shall contain the namespace and class
         name components. The hostname and key components, if present,
         will be ignored by the MB.
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If the properties
         argument is NULL, this indicates that all properties will be included
         in each returned instance.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p classPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property list specified in
         @p properties is invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - No instances found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capread This function is part of the Basic Read capability.

     @convfunction CBEnumInstances()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*enumerateInstances) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* classPath,
        const char** properties, CMPIStatus* rc);

    /**
     @brief Enumerate the instances associated with a given source instance.

     CMPIBrokerFT.associators() enumerates the instances associated with a
     given source instance.

     The target MIs are identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references
         the given source instance that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @param assocClass If not NULL, shall be a valid association class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be associated to the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be either an instance of this class or one
         of its subclasses.
     @param role If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the source object plays the specified role
         (i.e. the name of the property in the association class that refers
         to the source object shall match the value of this parameter).
     @param resultRole If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the returned object plays the specified
         role (i.e. the name of the property in the association class that
         refers to the returned object shall match the value of this parameter).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If @p properties
         is NULL, this indicates that all properties will be included in each
         returned instance.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p assocClass,
         @p resultClass, @p role, @p resultRole, or
         @p properties arguments are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Source instance not found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBAssociators()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*associators) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* assocClass, const char* resultClass, const char* role,
        const char* resultRole, const char** properties, CMPIStatus* rc);

    /**
     @brief Enumerate the instance paths of the instances associated with a
         given source instance.

     CMPIBrokerFT.associatorNames() enumerates the instance paths of the
     instances associated with a given source instance.

     The target MIs are identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references
         the given source instance that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @param assocClass If not NULL, shall be a valid association class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be associated to the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be either an instance of this class or one
         of its subclasses.
     @param role If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the source object plays the specified role
         (i.e. the name of the property in the association class that refers
         to the source object shall match the value of this parameter).
     @param resultRole If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the returned object plays the specified
         role (i.e. the name of the property in the association class that
         refers to the returned object shall match the value of this parameter).
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIObjectPath objects that represent the
         enumerated instance paths.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p assocClass, @p resultClass,
         @p role, or @p resultRole arguments are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Source instance not found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBAssociatorNames()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*associatorNames) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* assocClass, const char* resultClass, const char* role,
        const char* resultRole, CMPIStatus* rc);

    /**
     @brief Enumerate the association instances referencing a given source
         instance.

     CMPIBrokerFT.references() enumerates the association instances referencing
     a given source instance.

     The target MIs are identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references
         the given source instance that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @param resultClass If not NULL, shall be a valid class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be either an instance of this class or one
         of its subclasses.
     @param role If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the source object plays the specified role
         (i.e. the name of the property in the association class that refers
         to the source object shall match the value of this parameter).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If @p properties
         is NULL, this indicates that all properties will be included in each
         returned instance.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The
         @p resultClass, or @p role arguments are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Source instance not found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBReferences()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*references) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* resultClass, const char* role, const char** properties,
        CMPIStatus* rc);

    /**
     @brief Enumerate the instance paths of the association instances
         referencing a given source instance.

     CMPIBrokerFT.referenceNames() enumerates the instance paths of the
     association instances referencing a given source instance.

     The target MIs are identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references
         the given source instance that shall contain the namespace,
         class name, and key components. The hostname component, if present,
         will be ignored by the MB.
     @param resultClass If not NULL, shall be a valid class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object shall be either an instance of this class or one
         of its subclasses.
     @param role If not NULL, shall be a valid property name.
         It acts as a filter on the returned set of objects by mandating
         that each returned object shall be associated to the source object
         via an association in which the source object plays the specified role
         (i.e. the name of the property in the association class that refers
         to the source object shall match the value of this parameter).
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIObjectPath objects that represent the
         enumerated instance paths.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p resultClass, or @p role
         arguments are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Source instance not found. (**Deprecated**)
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBReferenceNames()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function
         is deprecated since CMPI 2.1. If no instances exist, the MB should
         instead return success with an empty result set.
         The MI shall treat this return code as a successful return of an
         empty result set.
    */
    CMPIEnumeration* (*referenceNames) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* resultClass, const char* role, CMPIStatus* rc);

    /**
     @brief Invoke a method on a target object.

     CMPIBrokerFT.invokeMethod() invokes a named, extrinsic method on a target
     object. Instance methods (i.e., non-static methods) can be invoked only
     on instances. Class methods (i.e., static methods) can be invoked on
     instances and classes.

     The target MI is identified by the MB based on @p objPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param objPath
     @parblock
         Points to the CMPIObjectPath object that references the target object
         on which the method is invoked.

         If the target object is an instance, this object path shall contain
         the namespace, class name, and key components. The hostname component,
         if present, will be ignored by the MB.

         If the target object is a class, this object path shall contain the
         namespace and class name components. The hostname and key components,
         if present, will be ignored by the MB.
     @endparblock
     @param method Method name.
     @param in Points to a CMPIArgs object containing the method input
         parameters.
     @param [out] out
     @parblock
         Points to an empty CMPIArgs object that, upon successful return of the
         method, will have been updated to contain the method output parameters.

         The objects returned in the CMPIArgs object shall not be explicitly
         released by the MI; they will be automatically released by the MB, as
         described in
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
     @endparblock
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the method return
         value will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Invocation of extrinsic methods is not
         supported by the MB (that is, the
         @ref CMPI_MB_InstanceManipulation "Instance Manipulation" capability
         is not available).
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx, @p objPath, @p in, or @p out
         handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p objPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p objPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The method parameters specified in
         the @p in or @p out arguments are invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - Target object not found.
     @li `CMPI_RC_ERR_METHOD_NOT_AVAILABLE` - The extrinsic method is not
         supported by the targeted MI.
     @li `CMPI_RC_ERR_METHOD_NOT_FOUND` - Method not defined in the class.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capmanipulation This function is part of the Instance Manipulation
         capability.

     @convfunction CBInvokeMethod()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`. It is believed that MB
         implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
    */
    CMPIData (*invokeMethod) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* objPath, const char* method,
        const CMPIArgs* in, CMPIArgs* out, CMPIStatus* rc);

    /**
     @brief Set or modify a property of an existing instance. (**Deprecated**)

     CMPIBrokerFT.setProperty() sets or modifies a property of an existing
     instance.

     The target MI is identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.

     @param instPath Points to a CMPIObjectPath object that references the
         instance to be modified and that shall contain the namespace, class
         name, and key components. The hostname component, if present, will
         be ignored by the MB.
     @param name Property name.
     @param value Points to a CMPIValue structure containing the non-NULL value
         to be assigned to the property, or is NULL to specify that NULL is to
         be assigned.
     @param type
     @parblock
         A CMPIType value defining the type of the value to be assigned to the
         property.

         If the value of @p type is @ref CMPI_chars or @ref CMPI_charsA, the
         C-language string to which @p value.chars points is copied by this
         function and the original string memory may be freed by the MI right
         after this function returns.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in @p instPath
         is not found.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - Value types incompatible.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capwrite This function is part of the Basic Write capability.
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE` and `CMPI_RC_ERR_INVALID_CLASS`. It is
         believed that MB implementations needed to use these return codes
         already, so that their addition only fixes an omission in this
         standard and does not create a compatibility issue for MIs that
         conform to CMPI 2.0.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
         MBs shall implement this function by invoking
         CMPIInstanceMIFT.modifyInstance() if CMPIPropertyMIFT.setProperty()
         is not implemented by the target MI.
         New MIs should replace the use of CMPIBrokerFT.setProperty() with the
         use of CMPIBrokerFT.modifyInstance().
    */
    CMPIStatus (*setProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* instPath, const char* name,
        const CMPIValue* value, CMPIType type);

    /**
     @brief Get a property of an existing instance. (**Deprecated**)

     CMPIBrokerFT.getProperty() function gets a property of an existing
     instance.

     The target MI is identified by the MB based on @p instPath.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be retrieved and that shall contain the namespace, class
         name, and key components. The hostname component, if present, will be
         ignored by the MB.
     @param name Property name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified property
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - Instance not found.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capread This function is part of the Basic Read capability.

     @convfunction CMGetProperty()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE` and `CMPI_RC_ERR_INVALID_CLASS`. It is
         believed that MB implementations needed to use these return codes
         already, so that their addition only fixes an omission in this
         standard and does not create a compatibility issue for MIs that
         conform to CMPI 2.0.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
         MBs shall implement this function by invoking
         CMPIInstanceMIFT.getInstance() if CMPIPropertyMIFT.getProperty()
         is not implemented by the target MI.
         New MIs should replace the use of CMPIBrokerFT.getProperty() with the
         use of CMPIBrokerFT.getInstance().
      */
    CMPIData (*getProperty) (const CMPIBroker* mb, const CMPIContext* ctx,
        const CMPIObjectPath* instPath, const char* name, CMPIStatus* rc);

    /**
     @brief Enumerate the instances of a given class (and its subclasses),
         returning only those that match the given query filter.

     CMPIBrokerFT.enumerateInstancesFiltered() enumerates the instances of a
     given class and its subclasses, returning only instances that match
     @p filterQuery. If no such instances are found, the function will return
     success with an empty enumeration.

     The target MIs are identified by the MB based on @p classPath.

     The set of properties in the result instances can be controlled via
     @p properties and via the @ref CMPI_FLAG_LocalOnly and
     @ref CMPI_FLAG_DeepInheritance flags in the @ref CMPIInvocationFlags entry
     of @p ctx.

     Because the response interface does not support extended error responses,
     there is no argument to request continue on error as part of this function.
     The MB is expected to invoke any target MIs with @p continueOnError set to
     false.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         The MI may specify invocation flags (@ref CMPIInvocationFlags entry)
         as needed.
     @param classPath Points to a CMPIObjectPath object that references the
         given class and that shall contain the namespace and class name
         components. The hostname and key components, if present, will be
         ignored by the MB.
     @param properties If not NULL, an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If this argument
         is NULL, this indicates that all properties will be included in each
         returned instance.
     @param filterQueryLanguage Defines the query language used by
         @p filterQuery. If @p filterQueryLanguage is NULL, @p filterQuery is
         ignored and no filtering is performed.
     @param filterQuery Defines the query in the query language defined by
         @p filterQueryLanguage. If NULL, no filtering is performed.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p classPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property list specified
         in @p properties is invalid.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The MB does not support
         the query language defined in the input arguments.
     @li `CMPI_RC_ERR_INVALID_QUERY` - @p filterQuery is not a valid filter in
         the language defined by @p filterQueryLanguage.
     @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of the query
         language is not supported.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capread This function is part of the Basic Read capability.

     @convfunction CBEnumInstancesFiltered()
     @added210 Added in CMPI 2.1.
    */
    CMPIEnumeration* (*enumerateInstancesFiltered) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* classPath,
        const char** properties, const char* filterQueryLanguage,
        const char* filterQuery, CMPIStatus* rc);

    /**
     @brief Enumerate the instances associated with a given source instance,
         returning only those that match the given filters.

     CMPIBrokerFT.associatorsFiltered() enumerates the instances associated with
     a given source instance, applying any filters defined in the arguments to
     return only instances that match the filters. If no such instances are
     found, the function will return success with an empty enumeration.

     The target MIs are identified by the MB based on @p instPath.

     Because the response interface does not support extended error responses,
     there is no argument to request continue on error as part of this function.
     The MB is expected to invoke any target MIs with @p continueOnError set to
     false.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB.
     @param assocClass If not NULL, shall be a valid association class name.
         It acts as a filter on the returned set of objects by mandating that
         each returned object must be associated with the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object must be associated with the source object via an association in
         which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param resultRole If not NULL, shall be a valid property name. It acts as
         a filter on the returned set of objects by mandating that each
         returned object must be associated with the source object via an
         association in which the returned object plays the specified role
         (i.e., the name of the property in the association class that refers
         to the returned object shall match the value of this argument).
     @param properties If not NULL, an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If this argument
         is NULL, this indicates that all properties will be included in each
         returned instance.
     @param filterQueryLanguage Defines the query language used by
         @p filterQuery. If @p filterQueryLanguage is NULL, @p filterQuery is
         ignored and no filtering is performed.
     @param filterQuery Defines the query in the query language defined by
         @p filterQueryLanguage. If NULL, no filtering is performed.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p assocClass, @p resultClass,
         @p role, @p resultRole, or @p properties arguments are invalid.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The MB does not support
         the query language defined in the input arguments.
     @li `CMPI_RC_ERR_INVALID_QUERY` - @p filterQuery is not a valid filter in
         the language defined by @p filterQueryLanguage.
     @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of the query
         language is not supported.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBAssociatorsFiltered()
     @added210 Added in CMPI 2.1.
    */
    CMPIEnumeration* (*associatorsFiltered) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* assocClass, const char* resultClass,
        const char* role, const char* resultRole,
        const char** properties, const char* filterQueryLanguage,
        const char* filterQuery, CMPIStatus* rc);

    /**
     @brief Enumerate the instances referencing a given source instance,
         returning only those that match the given filters.

     CMPIBrokerFT.referencesFiltered() enumerates the instances referencing
     a given source instance, applying any filters defined in the arguments to
     return only instances that match the filters. If no such instances are
     found, the function will return success with an empty enumeration.

     The target MIs are identified by the MB based on @p instPath.

     Because the response interface does not support extended error responses,
     there is no argument to request continue on error as part of this function.
     The MB is expected to invoke any target MIs with @p continueOnError set to
     false.

     @param mb Points to a CMPIBroker structure.
     @param ctx Points to a CMPIContext object that specifies the same
         principal (@ref CMPIPrincipal entry), role (@ref CMPIRole entry),
         accept language (@ref CMPIAcceptLanguage entry), and content language
         (@ref CMPIContentLanguage entry) as the CMPIContext object that was
         used to invoke the MI function that calls this MB function.
         Any invocation flags (@ref CMPIInvocationFlags entry) will be ignored
         by this function.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that shall contain the namespace, class name,
         and key components. The hostname component, if present, will be
         ignored by the MB.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object must be associated with the source object via an association in
         which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param properties If not NULL, an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. Each returned instance will not include
         elements for any properties missing from this list. If this argument
         is NULL, this indicates that all properties will be included in each
         returned instance.
     @param filterQueryLanguage Defines the query language used by
         @p filterQuery. If @p filterQueryLanguage is NULL, @p filterQuery is
         ignored and no filtering is performed.
     @param filterQuery Defines the query in the query language defined by
         @p filterQueryLanguage. If NULL, no filtering is performed.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumeration object will be
         returned, containing CMPIInstance objects that represent the
         enumerated instances.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx or @p instPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p resultClass, @p role, or
         @p properties arguments are invalid.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The MB does not support
         the query language defined in the input arguments.
     @li `CMPI_RC_ERR_INVALID_QUERY` - @p filterQuery is not a valid filter in
         the language defined by @p filterQueryLanguage.
     @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of the query
         language is not supported.
     @li `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED` - Limits exceeded.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     Extended error handling is not supported by this MB function; thus, any
     CMPIError objects returned by the targeted MI cannot be made available to
     the calling MI.
     @capassociations This function is part of the Association Traversal
         capability.

     @convfunction CBAssociatorsFiltered()
     @added210 Added in CMPI 2.1.
    */
    CMPIEnumeration* (*referencesFiltered) (const CMPIBroker* mb,
        const CMPIContext* ctx, const CMPIObjectPath* instPath,
        const char* resultClass, const char* role,
        const char** properties, const char* filterQueryLanguage,
        const char* filterQuery, CMPIStatus* rc);

    /**
     *   @}
     */

} CMPIBrokerFT;

/**
 * @brief Function table for some MB services (factory and miscellaneous
 *     services).
 *
 * This function table is referenced by the CMPIBroker structure, and provides
 * @ref brokerenc-factory "Factory Services" and
 * @ref brokerenc-misc "Miscellaneous Services".
 *
 * For functions that are not supported, their function pointers in this
 * function table shall not be NULL, but shall point to a function that can be
 * called and then indicate back to the caller that it is not supported, as
 * specified in the description of the function.
 */
typedef struct _CMPIBrokerEncFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokerenc-factory
     *   @{
     */

    /**
     @brief Create a new CMPIInstance object initialized to a given instance
         path.

     CMPIBrokerEncFT.newInstance() creates a new CMPIInstance object that is
     initialized to a given instance path.

     The new CMPIInstance object should have no properties. In CMPI 2.1, all
     other behaviors w.r.t. setting properties in the new CMPIInstance object
     (such as setting all class-defined properties, or setting properties with
     non-Null default values in their class definition), were deprecated. Note
     that the purpose of class-defined default values for properties is to act
     as defaults for unspecified input properties when a client creates an
     instance, and not to act as defaults for not explicitly set properties
     when a client retrieves an instance.

     @param mb Points to a CMPIBroker structure.
     @param instPath Points to a CMPIObjectPath object. The object path of the
         new CMPIInstance object will be set to the object path in @p instPath
         The object path in @p instPath shall specify a non-NULL namespace and
         a non-NULL creation class name. The object path shall specify no or
         all keys for the instance. The object path may specify a non-NULL host
         name for the instance (this is used for instances returned by
         cross-host associations).
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIInstance object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard". If
         the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeInstance().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p instPath handle is invalid, or
         other object path components specified in @p instPath are invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p instPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in
         @p instPath is not found.

     @convfunction CMNewInstance()
    */
    CMPIInstance* (*newInstance) (const CMPIBroker* mb,
        const CMPIObjectPath* instPath, CMPIStatus* rc);

    /**
     @brief Create a new CMPIObjectPath initialized to a given namespace and
         class name

     CMPIBrokerEncFT.newObjectPath() creates a new CMPIObjectPath object that
     is initialized to a given namespace and class name.

     @param mb Points to a CMPIBroker structure.
     @param ns Namespace name.
     @param cn Class name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIObjectPath object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard". If
         the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeObjectPath().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p ns is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in @p cn is invalid or
         does not exist.

     @convfunction CMNewObjectPath()
    */
    CMPIObjectPath* (*newObjectPath) (const CMPIBroker* mb, const char* ns,
        const char* cn, CMPIStatus* rc);

    /**
     @brief Create a new CMPIArgs object initialized to have no method
         parameters.

     CMPIBrokerEncFT.newArgs() creates a new CMPIArgs object that is
     initialized to have no method parameters.

     @param mb Points to a CMPIBroker structure.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIArgs object will be returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard". If
         the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeArgs().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.

     @convfunction CMNewArgs()
    */
    CMPIArgs* (*newArgs) (const CMPIBroker* mb, CMPIStatus* rc);

    /**
     @brief Create a new CMPIString object initialized from a C-language string.

     CMPIBrokerEncFT.newString() creates a new CMPIString object that is
     initialized from a C-language string.

     @param mb Points to a CMPIBroker structure.
     @param data C-language string used to initialize the new CMPIString object.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, the newly created CMPIString will be returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard". If
         the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeString().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.

     @convfunction CMNewString()
    */
    CMPIString* (*newString) (const CMPIBroker* mb, const char* data,
        CMPIStatus* rc);

    /**
     @brief Create a new CMPIArray object of a given size and type of elements.

     CMPIBrokerEncFT.newArray() returns a new CMPIArray object of a given size
     and type of elements. The elements of the array will exist and will have
     been set to the specified type and to NULL.

     Once created, the size of the array cannot be changed. This is still
     suitable for both fixed-size and variable-size CIM arrays, because
     CMPIArray is used only during the time a particular array value is
     transmitted between MB and MI, and even for variable-size CIM arrays, the
     actual array value does not change during that time.

     @param mb Points to a CMPIBroker structure.
     @param size Size of the array. A value of 0 is valid and
         specifies an empty array.
     @param type Type of each element. @p type specifies the type
         of single array elements; for example, the value for an array that
         contains CMPIString objects will be @ref CMPI_string, and not @ref
         CMPI_stringA.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIArray object will be returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeArray().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - Data type not valid.

     @convfunction CMNewArray()
     @bug In the CMPI Standards document, update the description of the function
         and of the @p size argument to match the header file.
    */
    CMPIArray* (*newArray) (const CMPIBroker* mb, CMPICount size,
        CMPIType type, CMPIStatus* rc);

    /**
     @brief Create a new CMPIDateTime object initialized to the current date
     and time.

     CMPIBrokerEncFT.newDateTime() creates a new CMPIDateTime object that is
     initialized with the current date and time.

     @param mb Points to a CMPIBroker structure.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIDateTime object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeDateTime().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.

     @convfunction CMNewDateTime()
    */
    CMPIDateTime* (*newDateTime) (const CMPIBroker* mb, CMPIStatus* rc);

    /**
     @brief Create a new CMPIDateTime object initialized to a specific value.

     CMPIBrokerEncFT.newDateTimeFromBinary() creates a new CMPIDateTime object
     that is initialized with the specified date and time.

     @param mb Points to a CMPIBroker structure.
     @param binTime When @p interval is false, @p binTime
         contains a point in time value expressed as a 64-bit unsigned integer
         in microseconds since 00:00:00 GMT, January 1, 1970. Otherwise,
         @p binTime contains a time interval expressed as
         a 64-bit unsigned integer in microseconds.
     @param interval If true, indicates that @p binTime is considered to be a
         time interval.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIDateTime object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeDateTime().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.

     @convfunction CMNewDateTimeFromBinary()
    */
    CMPIDateTime* (*newDateTimeFromBinary) (const CMPIBroker* mb,
        CMPIUint64 binTime, CMPIBoolean interval, CMPIStatus* rc);

    /**
     @brief Create a new CMPIDateTime object initialized to a specified value.

     CMPIBrokerEncFT.newDateTimeFromChars() creates a new CMPIDateTime object
     that is initialized with the specified date and time.

     @param mb Points to a CMPIBroker structure.
     @param datetime Date/time value to be used for the new object in the
         string format for CIM datetime values defined in
         @ref ref-dmtf-dsp0004 "DSP0004". Both the interval and point in time
         formats are supported.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIDateTime object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeDateTime().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p datetime format is invalid.

     @convfunction CMNewDateTimeFromChars()
    */
    CMPIDateTime* (*newDateTimeFromChars) (const CMPIBroker* mb,
        const char* datetime, CMPIStatus* rc);

    /**
     @brief Create a new CMPISelectExp object initialized from a select
         expression specified in a query language.

     CMPIBrokerEncFT.newSelectExp() creates a new CMPISelectExp object that is
     initialized from a select expression specified in a query language.

     @param mb Points to a CMPIBroker structure.
     @param query Select expression.
     @param lang Query language.
     @param [out] projection Points to a CMPIArray pointer that upon success
         will have been updated to point to a new CMPIArray object of
         CMPIString entries containing the projection specification. The
         pointer will be set to NULL if no projection was specified in the
         select expression. The projection specification is query
         language-specific. Hence the entries format of the projection output
         array CMPIString might be different depending on the query language.
         Be sure to check @p lang for the query language your MI will support.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPISelectExp object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeSelectExp().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - The query language is not
         supported.
     @li `CMPI_RC_ERR_INVALID_QUERY` - The query expression is not valid.
     @capquerynorm This function is part of the Query Normalization
                   capability.

     @convfunction CMNewSelectExp()
     @changed210 In CMPI 2.1, added the return code `CMPI_RC_ERR_NOT_SUPPORTED`,
         because this function depends on support for the @ref
         CMPI_MB_QueryNormalization "Query Normalization" capability in the MB.
     @bug In the CMPI Standard document, the @p projection argument is
         mistakenly declared as `const CMPIArray** projection`. Fix that by
         removing the `const`.
    */
    CMPISelectExp* (*newSelectExp) (const CMPIBroker* mb, const char* query,
        const char* lang, CMPIArray** projection, CMPIStatus* rc);

    /**
     *   @}
     *   @addtogroup brokerenc-misc
     *   @{
     */

    /**
     @brief Test whether a class path is of a specified class or any of its
        subclasses.

     CMPIBrokerEncFT.classPathIsA() tests whether a class path is of a
     specified class or any of that class’s subclasses.

     @param mb Points to a CMPIBroker structure.
     @param classPath Points to the CMPIObjectPath object representing
         the class path that is being tested. It shall contain the namespace
         and class name components. Any key components in that CMPIObjectPath
         object will be ignored.
     @param className Class name to be tested for.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the class path is of the specified class or
             any of that class's subclasses
         @li False indicates that this is not the case

         If not successful, false will be returned.
     @endparblock
     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p classPath handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in
         @p classPath is invalid or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - The class specified in @p classPath is
         invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p className format is invalid.

     @convfunction CMClassPathIsA()
    */
    CMPIBoolean (*classPathIsA) (const CMPIBroker* mb,
        const CMPIObjectPath* classPath, const char* className,
        CMPIStatus* rc);

    /**
     @brief Convert any CMPI encapsulated data type object into a string
         representation.

     CMPIBrokerEncFT.toString() converts any CMPI encapsulated data type object
     (see @ref mb-edt "MB Encapsulated Data Type Support") into an MB
     implementation-specific string representation.

     @param mb Points to a CMPIBroker structure.
     @param object Points to a CMPI encapsulated data type object.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the MB
         implementation-specific string representation of the CMPI encapsulated
         data type object will be returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPI encapsulated data
         type object which will be released along with that object, or a new
         object created by the MB which will be automatically released by the MB
         (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p object handle is
         invalid.

     @convfunction CDToString()
    */
    CMPIString* (*toString) (const CMPIBroker* mb, const void* object,
        CMPIStatus* rc);

    /**
     @brief Test whether a CMPI encapsulated data type object is of a specified
         CMPI type.

     CMPIBrokerEncFT.isOfType() tests whether a CMPI encapsulated data type
     object (see @ref mb-edt "MB Encapsulated Data Type Support") is of a
     specified CMPI type.

     @param mb Points to a CMPIBroker structure.
     @param object Points to a CMPI encapsulated data type object.
     @param type Type name of the encapsulated data type to be tested for
         (e.g., "CMPIInstance").
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the object is of the specified CMPI type
         @li False indicates that this is not the case

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p object handle is
         invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p type format is invalid.

     @convfunction CDIsOfType()
    */
    CMPIBoolean (*isOfType) (const CMPIBroker* mb, const void* object,
        const char* type, CMPIStatus* rc);

    /**
     @brief Get the type name of a CMPI ensapsulated data type object.

     CMPIBrokerEncFT.getType() gets the type name of a CMPI encapsulated data
     type object.

     @param mb Points to a CMPIBroker structure.
     @param [out] object Points to a CMPI encapsulated data type object.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object specifying the type
         name of the encapsulated data type (e.g., "CMPIInstance") will be
         returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPI encapsulated data
         type object which will be released along with that object, or a new
         object created by the MB which will be automatically released by the MB
         (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p object handle is
         invalid.

     @convfunction CDGetType()
    */
    CMPIString* (*getType) (const CMPIBroker* mb, const void* object,
        CMPIStatus* rc);

    /**
     @brief Get a translated MB implementation-specific message text by message
         ID. (**Deprecated**)

     CMPIBrokerEncFT.getMessage() gets a translated MB implementation-specific
     message text by message ID. The language of the message text depends on
     the MB language setting.

     @param mb Points to a CMPIBroker structure.
     @param msgId Message ID that is used by the MB to locate a message
         template. The message ID values and corresponding message templates
         are MB implementation-specific.
     @param defMsg Default message template that will be used when message
         translation is not supported by the MB or @p msgId cannot be located.
         The message template string specified in @p defMsg may contain up to
         ten message insert triggers ($0 through $9). Each insert trigger
         string will be replaced with a string representation of the value of
         the corresponding insert pair in the variable arguments of this
         function. The MI is not affected when message translation is not
         supported by the MB, or the message cannot be found, because this
         function still succeeds and returns a message with expanded message
         insert triggers.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @param count Number of message insert pairs in the range 0 to 10.
     @param ... The variable arguments of this function are @p count pairs of
         arguments representing the message insert pairs as follows:
         `type, value`
         whereby @p type is a @ref CMPIType value and @p value is a value of
         that type.
         The following types are supported: @ref CMPI_sint32,
         @ref CMPI_uint32, @ref CMPI_sint64, @ref CMPI_uint64, @ref CMPI_real64,
         @ref CMPI_boolean, @ref CMPI_chars, and @ref CMPI_string.
     @return @parblock
         If successful, a pointer to a new CMPIString object containing either
         the translated or default message will be returned.

         If not successful, the default message without insert resolution will
         be returned.

         In both cases, the new object will be automatically released by the
         MB, as described in Subclause 4.1.7 of the @ref ref-cmpi-standard
         "CMPI Standard". There is no function to explicitly release the new
         object. Specifically, the MI shall not use
         CMPIBrokerMemFT.freeString() on the new object.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - Invalid insert pair.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p count value range violation.
     @captranslation This function is part of the Message Translation
         capability.

     @convfunction CMGetErrorMessage()
     @deprecated This function is deprecated since CMPI 2.1. Use
         CMPIBrokerEncFT.getMessage2() instead.
    */
    CMPIString* (*getMessage) (const CMPIBroker* mb, const char* msgId,
        const char* defMsg, CMPIStatus* rc, CMPICount count, ...);

    /**
     @brief Log a diagnostic message.

     CMPIBrokerEncFT.logMessage() logs a diagnostic message. This function
     exists to provide a mechanism to MIs by which to provide information about
     errors.

     @param mb Points to a CMPIBroker structure.
     @param severity Severity of the log message. Severity levels
         are defined in @ref CMPISeverity.
     @param id If not NULL, message ID or any other identifying string.
     @param text If not NULL, message text to be logged.
     @param string If not NULL, points to a CMPIString object specifying the
         message text to be logged. @p string will be ignored when @p text is
         not NULL.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p string handle is
         invalid.
     @caplogging This function is part of the Logging capability.

     @convfunction CMLogMessage()
     @changed210 In CMPI 2.1, fixed inconsistencies in presence and
         definition of @p severity by changing its type from `int` to @ref
         CMPISeverity. This is a compatible change for MIs.
    */
    CMPIStatus (*logMessage) (const CMPIBroker* mb, int severity,
        const char* id, const char* text, const CMPIString* string);

    /**
     @brief Trace a diagnostic message with a specific trace level.

     CMPIBrokerEncFT.trace() traces a diagnostic message with a specific trace
     level. This function exists to provide a mechanism to MIs by which
     debugging information may be generated.

     MBs may support tracing in such a way that trace level and component ID
     can be used for deciding whether a diagnostic message is actually kept
     versus discarded.

     @param mb Points to a CMPIBroker structure.
     @param level Trace level of the message. Trace levels are
         defined in @ref CMPILevel.
     @param component If not NULL, MI implementation-specific component ID.
     @param text If not NULL, message text to be traced.
     @param string If not NULL, points to a CMPIString object specifying the
         message text to be traced. @p string will be ignored when @p text is
         not NULL.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p string handle is
         invalid.
     @captracing This function is part of the Tracing capability.

     @convfunction CMTraceMessage()
     @changed210 In CMPI 2.1, fixed inconsistencies in presence and
         definition of @p level by changing its type from `int` to @ref
         CMPILevel. This is a compatible change for MIs.
    */
    CMPIStatus (*trace) (const CMPIBroker* mb, CMPILevel level,
        const char* component, const char* text, const CMPIString* string);

#ifdef CMPI_VER_200

    /**
     *   @}
     *   @addtogroup brokerenc-factory
     *   @{
     */

    /**
     @brief Create a new CMPIError object initialized with certain core
         attributes.

     CMPIBrokerEncFT.newCMPIError() creates a new CMPIError object that is
     initialized with certain core attributes.

     The input data may (or may not) be defined in a DMTF message registry (see
     @ref ref-dmtf-dsp0228 "DSP0228" for the format of message registries, and
     @ref ref-dmtf-dsp8016 "DSP8016" for the messages defined for the MI
     functions of CMPI).

     Any attributes of the new CMPIError object that are not initializeable via
     input arguments of this function will have an initial value of NULL.

     @param mb Points to a CMPIBroker structure.
     @param owner Value for the `OwningEntity` attribute of the CMPIError
         object. For a description of the `OwningEntity` attribute, see the
         description of the `OwningEntity` property in the `CIM_Error` class in
         the CIM Schema. If the error message is defined in a DMTF message
         registry, the string value of @p owner shall be the content of the
         OWNING_ENTITY element defined for the registry.
     @param msgID Value for the `MessageID` attribute of the CMPIError object.
         For a description of the `MessageID` attribute, see the description of
         the `MessageID` property in the `CIM_Error` class in the CIM Schema.
         If the error message is defined in a DMTF message registry, the string
         value of @p msgID shall be the message ID defined for the message in
         the registry (the concatenation of the values of the PREFIX and
         SEQUENCE_NUMBER attributes of the MESSAGE_ID element for the message).
     @param msg Value for the `Message` attribute of the CMPIError object. For
         a description of the `Message` attribute, see the description of the
         `Message` property in the `CIM_Error` class in the CIM Schema. This
         message is the formatted and translated message, with any dynamic
         values expanded.
     @param sev A @ref CMPIErrorSeverity enumeration value specifying the value
         for the `PerceivedSeverity` attribute of the CMPIError object. For a
         description of the `PerceivedSeverity` attribute, see the description
         of the `PerceivedSeverity` property in the `CIM_Error` class in the
         CIM Schema. If the error message is defined in a DMTF message
         registry, the string value of @p sev shall be the content of the
         PERCEIVED_SEVERITY element defined for the message in the registry.
     @param pc A @ref CMPIErrorProbableCause enumeration value specifying the
         value for the `PerceivedSeverity` attribute of the CMPIError object.
         For a description of the `PerceivedSeverity` attribute, see the
         description of the `PerceivedSeverity` property in the `CIM_Error`
         class in the CIM Schema. If the error message is defined in a DMTF
         message registry, note that the string value of @p pc is not defined
         in the message in the registry.
     @param cimStatusCode A @ref CMPIrc enumeration value specifying the value
         for the `CIMStatusCode` attribute of the CMPIError object. For a
         description of the `CIMStatusCode` attribute, see the description of
         the `CIMStatusCode` property in the `CIM_Error` class in the CIM
         Schema. Not all status codes are valid for each operation. The
         specification for each MI function defines the status codes that may
         be returned. If the error message is defined in a DMTF message
         registry, @p cimStatusCode shall reflect the content of the
         CIMSTATUSCODE element defined for the message in the registry.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIError object will be returned.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the parameters is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @caperrors This function is part of the Extended Errors capability.

     @convfunction CMNewCMPIError()
     @added200 Added in CMPI 2.0.
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIError* (*newCMPIError) (const CMPIBroker* mb, const char* owner,
        const char* msgID, const char* msg, const CMPIErrorSeverity sev,
        const CMPIErrorProbableCause pc, const CMPIrc cimStatusCode,
        CMPIStatus* rc);

    /**
     *   @}
     *   @addtogroup brokerenc-misc
     *   @{
     */

    /**
     @brief Open a message file and return a handle to the file.

     If the MB supports the @ref cap-translation "Message Translation"
     capability, CMPIBrokerEncFT.openMessageFile() opens a message file and
     returns a message file handle to that file. This function will use the
     @ref CMPIAcceptLanguage entry from the current context to determine the
     language for the messages, and will set the @ref CMPIContentLanguage entry
     in the current context to the language that was used. All subsequent calls
     to CMPIBrokerEncFT.getMessage2() using this message file handle will
     return messages based on that language.

     If the MB does not support the @ref cap-translation "Message Translation"
     capability, or if the function fails for other reasons, the function
     returns NULL as the message file handle. Subsequent calls to
     CMPIBrokerEncFT.getMessage2() using the NULL message file handle will
     cause the default message template to be used.

     @param mb Points to a CMPIBroker structure.
     @param msgFile
     @parblock
         Points to a string specifying the implementation-specific file path to
         the message file, or a part thereof.

         Examples for such implementation-specific file paths are:
         @li Base name of the message file (does not include file extension and
             directory path). The message file contains all languages, and the
             language is used to locate the message in the correct language
             within the message file.
         @li Base name of the message file (does not include file extension and
             directory path). The message file contains messages in only one
             language, and some identifier for that language is part of the
             base name.
         @li Absolute path of the message file. The message file contains all
             languages, and the language is used to locate the message in the
             correct language within the message file.
         @li Absolute path of the message file. The message file contains
             messages in only one language, and some identifier for that
             language is part of the file path.

         The format of the content of the message file is also
         implementation-specific.
     @endparblock
     @param [out] msgFileHandle Points to a @ref CMPIMsgFileHandle structure
         that will have been updated with a handle that can be passed to the
         CMPIBrokerEncFT.getMessage2() and CMPIBrokerEncFT.closeMessageFile()
         functions. If the MB supports the
         @ref cap-translation "Message Translation" capability and the function
         was successful, the @ref CMPIMsgFileHandle structure will have been
         updated with a non-NULL handle to the open message file. If the MB
         does not support the @ref cap-translation "Message Translation"
         capability, or if the function failed for other reasons, the
         @ref CMPIMsgFileHandle structure will have been updated with a NULL
         handle.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_NOT_FOUND` - The MB supports the
         @ref cap-translation "Message Translation" capability and the message
         file was not found, or the MB does not support the
         @ref cap-translation "Message Translation" capability.
     @captranslation This function is part of the Message Translation
         capability.

     @convfunction CMOpenMessageFile()
     @added200 Added in CMPI 2.0.
    */
    CMPIStatus (*openMessageFile) (const CMPIBroker* mb, const char* msgFile,
        CMPIMsgFileHandle* msgFileHandle);

    /**
     @brief Close a message file.

     CMPIBrokerEncFT.closeMessageFile() closes a message file previously opened
     by CMPIBrokerEncFT.openMessageFile(). If the message file handle is NULL,
     the message file is not closed, and this is not considered a failure.

     @param mb Points to a CMPIBroker structure.
     @param msgFileHandle @p Contains a message file handle (including NULL)
         that was returned by a previous call to
         CMPIBrokerEncFT.openMessageFile().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful (including if the message file
         handle is NULL).
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p msgFileHandle handle
         is invalid.
     @captranslation This function is part of the Message Translation
         capability.

     @convfunction CMCloseMessageFile()
     @added200 Added in CMPI 2.0.
    */
    CMPIStatus (*closeMessageFile) (const CMPIBroker* mb,
        const CMPIMsgFileHandle msgFileHandle);

    /**
     @brief Get a translated message text from an open message file by
         message ID.

     CMPIBrokerEncFT.getMessage2() gets a translated message text from an open
     message file, by message ID.

     @param mb Points to a CMPIBroker structure.
     @param msgId Message ID that is used to locate a message template in the
         open message file.
     @param msgFileHandle Message file handle that was returned by a previous
         call to CMPIBrokerEncFT.openMessageFile(). If the MB supports the
         @ref cap-translation "Message Translation" capability, that handle
         identifies an open message file. If the MB does not support the
         @ref cap-translation "Message Translation" capability, that handle is
         NULL.
     @param defMsg
     @parblock
         Default message template that will be used when the MB does not
         support the @ref cap-translation "Message Translation" capability or
         when the message ID cannot be located.

         The message template string specified in @p defMsg may contain up to
         ten message insert triggers ($0 through $9). Each insert trigger will
         be expanded; that is, the insert trigger string will be replaced with
         a string representation of the value of the corresponding insert pair
         in the variable arguments of this function. The MI is not affected
         when the MB does not support the
         @ref cap-translation "Message Translation" capability or when the
         message ID cannot be located, because this function still succeeds and
         returns a message with expanded message insert triggers.
     @endparblock
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @param count Number of message insert pairs in the range 0 to 10.
     @param ... The variable arguments of this function are @p count pairs of
         arguments representing the message insert pairs as follows:
         `type, value` whereby @p type is a @ref CMPIType value and @p value
         is a value of that type.
         The following types are supported: @ref CMPI_sint32, @ref CMPI_uint32,
         @ref CMPI_sint64, @ref CMPI_uint64, @ref CMPI_real64,
         @ref CMPI_boolean, @ref CMPI_chars, and @ref CMPI_string.
     @return @parblock
         If successful, a pointer to a new CMPIString object containing either
         the translated or default message will be returned. In both cases, the
         insert triggers will have been expanded.

         If not successful, the default message template without any insert
         triggers expanded will be returned.

         In both cases, the new object will be automatically released by the MB,
         as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.
         Specifically, the MI shall not use CMPIBrokerMemFT.freeString()
         on the new object.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb or @p msgFileHandle handle
         is invalid.@n
         Note that NULL is a valid value for the @p msgFileHandle handle.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - Invalid insert pair.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Count value range violation.
     @captranslation This function is part of the Message Translation
         capability.

     @convfunction CMGetMessage2()
     @added200 Added in CMPI 2.0.
    */
    CMPIString* (*getMessage2) (const CMPIBroker* mb, const char* msgId,
        const CMPIMsgFileHandle msgFileHandle, const char* defMsg,
        CMPIStatus* rc, CMPICount count, ...);

#endif /*CMPI_VER_200*/

    /**
     *   @}
     *   @addtogroup brokerenc-factory
     *   @{
     */

#ifdef CMPI_VER_210

    /**
     @brief Create a new CMPIPropertyList object initialized to a list of
         property names.

     CMPIBrokerEncFT.newPropertyList() creates a new CMPIPropertyList that is
     initialized to a list of property names.

     @param mb Points to a CMPIBroker structure.
     @param properties Points to the first entry of a NULL-terminated array of
         pointers to C strings that specify the property names in the property
         list. The entries in that array may be in any order and in any lexical
         case.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIPropertyList object will be
         returned.

         The new object will be automatically released by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.

     @added210 Added in CMPI 2.1.
    */
    CMPIPropertyList* (*newPropertyList) (const CMPIBroker* mb,
        const char** properties, CMPIStatus* rc);

    /**
     @brief Create a new CMPIString object from a C-language string in a
         specific codepage.

     CMPIBrokerEncFT.newStringCP() creates a new CMPIString object that is
     initialized from a C-language string in a specific codepage

     @param mb Points to a CMPIBroker structure.
     @param data C-language string represented in the codepage specified in
         @p cpid. @p data is used to initialize the new CMPIString object after
         converting it from its codepage to UTF-8.
     @param cpid CMPI-specific codepage ID for the codepage that is used to
         interpret the Bytes in the @p data argument. See @ref CMPICodepageID
         for a list of supported codepages and their codepage ID values.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the new CMPIString object containing the
         UTF-8 represented string will be returned.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         If the new object is no longer used by the MI, it may be explicitly
         released by the MI using CMPIBrokerMemFT.freeString().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @capcodepage This function is part of the Codepage Conversion
         capability.

     @note No corresponding macro
     @added210 Added in CMPI 2.1.
    */
    CMPIString* (*newStringCP) (const CMPIBroker* mb, const char* data,
        const CMPICodepageID cpid, CMPIStatus* rc);

    /**
     @brief Create a new CMPIEnumerationFilter object initialized with a
         filter query.

     CMPIBrokerEncFT.newEnumerationFilter() creates a new CMPIEnumerationFilter
     object that is initialized with a filter query.

     @param mb Points to a CMPIBroker structure.
     @param filterQueryLanguage Query language used for @p filterQuery. If this
         argument is NULL, the new CMPIEnumerationFilter object will be set to
         define that no filtering is to be performed.
     @param filterQuery Valid query in the query language defined by @p
         filterQueryLanguage. If this argument is NULL, the new
         CMPIEnumerationFilter object will be set to define that no filtering
         is to be performed.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a new CMPIEnumerationFilter object will be
         returned.

         The new object will be released automatically by the MB, as described
         in Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard".
         There is no function to explicitly release the new object.

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid.
     @li `CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED` - @p filterQueryLanguage
         defines a query language that the MI does not recognize.
     @li `CMPI_RC_ERR_INVALID_QUERY` - @p filterQuery is not a valid query in
         the specified filter query language.
     @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of the query
         language is not supported.

     @added210 Added in CMPI 2.1.
    */
    CMPIEnumerationFilter* (*newEnumerationFilter) (const CMPIBroker* mb,
            const char* filterQueryLanguage, const char* filterQuery,
            CMPIStatus* rc);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

} CMPIBrokerEncFT;

struct timespec;

/**
 * @brief Function table for MB operating system encapsulation services.
 *
 * This function table is referenced by the CMPIBroker structure, and provides
 * the following operating system encapsulation services:
 * @ref brokerext-lib "Library Resolution",
 * @ref brokerext-thread "POSIX-conformant Threads",
 * @ref brokerext-mutex "POSIX-conformant Mutexes", and
 * @ref brokerext-condition "POSIX-conformant Conditions".
 *
 * @capopsys All functions defined in this structure are part of the
 *     OS Encapsulation Services capability.
 *
 * If the OS Encapsulation Services capability is not supported, the
 * function pointers in this function table shall not be NULL, but shall point
 * to a function that can be called and then indicate back to the caller that
 * it is not supported, as specified in the description of the function.
 */
typedef struct _CMPIBrokerExtFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokerext-lib
     *   @{
     */

    /**
     @brief Resolve a generic load library name to its file name.

     CMPIBrokerExtFT.resolveFileName() resolves a generic load library name to
     its file name.

     @param libName A generic load library name. Depending on the underlying OS,
         load library names have specific formats: For the generic load library
         name "MyLibrary", the corresponding file name on Linux is
         "libMyLibrary.so". The corresponding file name on Windows is
         "MyLibrary.dll".
     @return @parblock
         If successful, a pointer to a new C-language string containing the
         file name of the load library (without path) will be returned.

         The character array of the returned string shall not be explicitly
         released by the MI, because it will be automatically released by the
         MB (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock
     @todo TBD AM: The old text in the description of the return value said:@n
         "Space for this string has been obtained using POSIX ``malloc()`` and
         must be released using POSIX ``free()`` by the caller.
         In case no storage could be obtained for the complemented library
         name, returns NULL."@n
         The spec says we changed that to auto-release by MB.
         Double check in implementation whether that is really true.
    */
    char* (*resolveFileName) (const char* libName);

    /**
     *   @}
     *   @addtogroup brokerext-thread
     *   @{
     */

    /**
     @brief Start a new thread, using POSIX threading semantics.

     CMPIBrokerExtFT.newThread() starts a new thread, using POSIX threading
     semantics.

     Creating a thread using CMPIBrokerExtFT.newThread() does not inform
     the MB that the new thread will begin using MB functions. Thus,
     @ref CMPIBrokerFT::attachThread "CMPIBrokerFT.attachThread()"
     must be called by the new thread before it uses MB functions.

     @param start Points to the function to be started as a thread.
         For details, see type @ref CMPIThreadFunc.
     @param parm Points to argument(s) to be passed to that function.
     @param detached If not zero, defines that the new thread should run in
         detached mode. In detached mode, termination of the thread that called
         this function does not cause the new thread to be canceled. See
         @ref ref-ieee-1003-1 "IEEE 1003.1" for details on detached mode.
     @return @parblock
         If successful, the handle of the started thread will be returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
     For historical reasons, no additional error information is passed back.
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @todo TBD AM: Done, but please review the new function types:
           @ref CMPIThreadFunc,
           @ref CMPIThreadOnceFunc,
           @ref CMPIThreadKeyCleanupFunc.
    */
    CMPI_THREAD_TYPE (*newThread) (CMPIThreadFunc start, void* parm,
        int detached);

    /**
     @brief Wait until the specified thread ends, using POSIX threading
         semantics.

     CMPIBrokerExtFT.joinThread() suspends the current thread to wait until the
     specified thread ends, using POSIX threading semantics.

     @param thread Handle of the thread to wait for.
     @param retval Points to the return value of the thread. On successful
         completion, the return value of the thread will be stored in this
         location.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
     Error codes are defined in `errno.h`, specifically for the
     ``pthread_join()`` function; both are defined in
     @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @note No corresponding macro
    */
    int (*joinThread) (CMPI_THREAD_TYPE thread, CMPI_THREAD_RETURN* retval);

    /**
     @brief Cause current thread to exit with the passed-in return code, using
         POSIX threading semantics.

     CMPIBrokerExtFT.exitThread() causes the current thread to exit with the
     passed-in return code, using POSIX threading semantics.

     The current thread can also exit by simply returning from its thread
     function; the purpose of the CMPIBrokerExtFT.exitThread() function is to
     make premature returns more convenient.

     @param return_code The return code that should be used for the thread.
     @return The function never returns, regardless of whether it is
         successful or encounters errors.
     @par Errors
     None; the function never returns.
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard document, the change history of this function
         states that the function was added in CMPI 2.0. That needs to be
         corrected to state that a description for the function was added in
         CMPI 2.0 (the function already existed in the function table in CMPI
         1.0).
    */
    int (*exitThread) (CMPI_THREAD_RETURN return_code);

    /**
     @brief Cancel a running thread, using POSIX threading semantics.

     CMPIBrokerExtFT.cancelThread() cancels the thread identified by @p thread,
     using POSIX threading semantics.

     @param thread Handle of the thread to be canceled.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
     @parblock
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_cancel()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".

         The ``pthread_cancel()`` function does not define any error codes in
         @ref ref-ieee-1003-1 "IEEE 1003.1". Some POSIX implementations use the
         following error code for that function:
         @li `ESRCH` -The specified thread could not be found.
     @endparblock
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*cancelThread) (CMPI_THREAD_TYPE thread);

    /**
     @brief Suspend execution of current thread for a specified duration.

     CMPIBrokerExtFT.threadSleep() suspends the execution of the
     current thread for a specified duration.

     @param msec Suspend duration in milliseconds.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*threadSleep) (CMPIUint32 msec);

    /**
     @brief Call a function once for a given once-object.

     CMPIBrokerExtFT.threadOnce() calls a function once for a given
     <i>once-object</i>. The once-object is an integer that initially shall
     have a value of zero. The first call to CMPIBrokerExtFT.threadOnce() with
     an initialized once-object will call the specified function. On return
     from CMPIBrokerExtFT.threadOnce(), it is guaranteed that the specified
     function has completed, and that the once-object has been updated to
     indicate that. Subsequent calls to CMPIBrokerExtFT.threadOnce() by any
     thread within the process with that once-object will not call the
     specified function.

     @param [inout] once Points to the once-object. The value of the
         once-object controls whether the specified function has yet to be
         called. The once-object may be located in thread-specific memory
         (that is, each thread has its own separate copy), or in memory
         that is accessible to all threads of the process. The function
         will behave in a thread-safe way. The once-object shall be
         initialized to zero before the first call to the
         CMPIBrokerExtFT.threadOnce() function.
     @param function Points to the function to be invoked.
         For details, see type @ref CMPIThreadOnceFunc.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_once()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @note No corresponding macro.
    */
    int (*threadOnce) (int* once, CMPIThreadOnceFunc function);

    /**
     @brief Create a POSIX threading-conformant thread key for
         accessing the thread local store.

     CMPIBrokerExtFT.createThreadKey() creates a POSIX threading-conformant
     thread key that can be used as a key to access the thread local store.

     @param [out] key Points to the thread key to be returned.
     @param cleanup Points to the function to be invoked during thread local
         store cleanup. For details, see type @ref CMPIThreadKeyCleanupFunc.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_key_create()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*createThreadKey) (CMPI_THREAD_KEY_TYPE* key,
        CMPIThreadKeyCleanupFunc cleanup);

    /**
     @brief Destroy a POSIX threading-conformant thread key for accessing the
         thread local store.

     CMPIBrokerExtFT.destroyThreadKey() destroys a POSIX threading-conformant
     thread key for accessing the thread local store.

     @param key Thread key to be destroyed.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_key_delete()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*destroyThreadKey) (CMPI_THREAD_KEY_TYPE key);

    /**
     @brief Get a data pointer from the thread local store using a POSIX
         threading-conformant thread key.

     CMPIBrokerExtFT.getThreadSpecific() gets a data pointer from the thread
     local store using a POSIX threading-conformant thread key.

     @param key Thread key to be used to retrieve the data pointer.
     @return @parblock
         If successful, the data pointer will be returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
         For historical reasons, no additional error information is passed back.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    void* (*getThreadSpecific) (CMPI_THREAD_KEY_TYPE key);

    /**
     @brief Set a data pointer in the thread local store using a POSIX
         threading-conformant thread key.

     CMPIBrokerExtFT.setThreadSpecific() sets a data pointer in the thread
     local store using a POSIX threading-conformant thread key.

     @param key Thread key to be used.
     @param value Data pointer that is stored in the thread local store.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_setspecific()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @note No corresponding macro.
    */
    int (*setThreadSpecific) (CMPI_THREAD_KEY_TYPE key, void* value);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

    /**
     @brief Create a POSIX threading-conformant mutex.

     CMPIBrokerExtFT.newMutex() creates a POSIX threading-conformant mutex.

     The mutex that is created shall be of a type that exhibits the following
     behavior:
     @li For locking a locked mutex: A thread that holds a lock on a mutex and
         attempts to lock that mutex again without first unlocking it shall
         succeed in locking the mutex. Multiple locks of the mutex (by the same
         thread) shall require the same number of unlocks (by that same thread)
         to release the mutex before another thread can acquire the mutex.
     @li For unlocking an unlocked mutex: A thread attempting to unlock a mutex
         that is not locked by that thread (that is, the mutex is either
         entirely unlocked or locked by another thread) shall fail in unlocking
         the mutex.

     This behavior is consistent with mutex type PTHREAD_MUTEX_RECURSIVE
     defined in @ref ref-ieee-1003-1 "IEEE 1003.1".

     @param opt For future use. It should be ignored by the MB, and MIs should
         pass a value of 0.
     @return @parblock
         If successful, the handle of the new mutex will be returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
         For historical reasons, no additional error information is passed back.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @changed210 In CMPI 2.1, changed @p opt to be for future use.
     @changed210 In CMPI 2.1, required that the mutex behaves consistent with
         mutex type `PTHREAD_MUTEX_RECURSIVE` defined in @ref ref-ieee-1003-1
         "IEEE 1003.1".
    */
    CMPI_MUTEX_TYPE (*newMutex) (int opt);

    /**
     @brief Destroy a POSIX threading-conformant mutex. (**Deprecated**)

     CMPIBrokerExtFT.destroyMutex() destroys a POSIX threading-conformant
     mutex.

     @param mutex Handle of the mutex to be destroyed.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @deprecated This function is deprecated since CMPI 2.1, because it does
         not indicate whether it succeeded or failed. Use
         CMPIBrokerExtFT.destroyMutex2() instead.
    */
    void (*destroyMutex) (CMPI_MUTEX_TYPE mutex);

    /**
     @brief Lock a POSIX threading-conformant mutex. (**Deprecated**)

     CMPIBrokerExtFT.lockMutex() locks a POSIX threading-conformant mutex.

     If the mutex is locked by another thread, the current thread is suspended
     until the lock is granted.

     The behavior in case the mutex is already locked by the current thread is
     defined in the description of CMPIBrokerExtFT.newMutex().

     @param mutex Handle of the mutex to be locked.
     @return None.

     @par Errors
         For historical reasons, this function does not indicate whether it
         succeeded or failed.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @deprecated This function is deprecated since CMPI 2.1, because it does
         not indicate whether it succeeded or failed. Use
         CMPIBrokerExtFT.lockMutex2() instead.
    */
    void (*lockMutex) (CMPI_MUTEX_TYPE mutex);

    /**
     @brief Unlock a POSIX threading-conformant mutex. (**Deprecated**)

     CMPIBrokerExtFT.unlockMutex() unlocks a POSIX threading-conformant mutex.

     The behavior in case the mutex is not locked by the current thread is
     defined in the description of CMPIBrokerExtFT.newMutex().

     @param mutex Handle of the mutex to be unlocked.
     @return None.

     @par Errors
         For historical reasons, this function does not indicate whether it
         succeeded or failed.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @deprecated This function is deprecated since CMPI 2.1, because it does
         not indicate whether it succeeded or failed. Use
         CMPIBrokerExtFT.unlockMutex2() instead.
    */
    void (*unlockMutex) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /**
     @brief Create a new POSIX threading-conformant condition variable.

     CMPIBrokerExtFT.newCondition() creates a new POSIX threading-conformant
     condition variable.

     @param opt For future use. It should be ignored by the MB, and MIs should
         pass a value of 0.
     @return @parblock
         If successful, the handle of the new condition variable will be
         returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
         For historical reasons, no additional error information is passed back.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @changed210 In CMPI 2.1, changed @p opt to be for future use.
    */
    CMPI_COND_TYPE (*newCondition) (int opt);

    /**
     @brief Destroy a POSIX threading-conformant condition variable.
         (**Deprecated**)

     CMPIBrokerExtFT.destroyCondition() destroys a POSIX threading-conformant
     condition variable.

     @param cond Handle of the condition variable to be destroyed.
     @return None.

     @par Errors
         For historical reasons, this function does not indicate whether it
         succeeded or failed.
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @deprecated This function is deprecated since CMPI 2.1,
         because it does not indicate whether it succeeded or failed. Use
         CMPIBrokerExtFT.destroyCondition2() instead.
    */
    void (*destroyCondition) (CMPI_COND_TYPE cond);

    /**
     @brief Wait until a POSIX threading-conformant condition variable is
         signalled.

     CMPIBrokerExtFT.condWait() waits until a POSIX threading-conformant
     condition variable is signaled. If the condition variable has been
     signaled already, the function returns immediately; otherwise, it
     suspends the current thread to wait for the signal and then returns.

     @param cond Handle of the condition variable to be used.
     @param mutex Handle of a locked mutex guarding this condition
         variable.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
        ``pthread_cond_wait()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*condWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex);

    /**
     @brief Wait until a POSIX threading-conformant condition variable is
         signaled using a timeout value.

     CMPIBrokerExtFT.timedCondWait() waits until a POSIX threading-conformant
     condition variable is signalled. If the condition variable has been
     signalled already, the function returns immediately; otherwise, it
     suspends the current thread to wait for the signal and then returns. The
     function returns when the timeout expires before the condition is
     signalled.

     @param cond Handle of the condition variable to be used.
     @param mutex Handle of a locked mutex guarding this condition variable.
     @param wait Timeout value. See structure ``timespec`` defined in `time.h`
         for details; both are defined in @ref ref-ieee-1003-1 "IEEE 1003.1".
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_cond_timedwait()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*timedCondWait) (CMPI_COND_TYPE cond, CMPI_MUTEX_TYPE mutex,
        struct timespec* wait);

    /**
     @brief Send a signal to a POSIX threading-conformant condition variable.

     CMPIBrokerExtFT.signalCondition() sends a signal to a POSIX
     threading-conformant condition variable.

     @param cond Handle of the target condition variable.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_cond_signal()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
    */
    int (*signalCondition) (CMPI_COND_TYPE cond);

    /**
     *   @}
     *   @addtogroup brokerext-mutex
     *   @{
     */

#ifdef CMPI_VER_210

    /**
     @brief Destroy a POSIX threading-conformant mutex.

     CMPIBrokerExtFT.destroyMutex2() destroys a POSIX threading-conformant
     mutex.

     @param mutex Handle of the mutex to be destroyed.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_mutex_destroy()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @added210 Added in CMPI 2.1, superseding the deprecated
         CMPIBrokerExtFT.destroyMutex() function.
    */
    int (*destroyMutex2) (CMPI_MUTEX_TYPE mutex);

    /**
     @brief Lock a POSIX threading-conformant mutex.

     CMPIBrokerExtFT.lockMutex2() locks a POSIX threading conformant mutex.

     If the mutex is locked by another thread, the current thread is suspended
     until the lock is granted.

     The behavior in case the mutex is already locked by the current thread
     is defined in the description of CMPIBrokerExtFT.newMutex().

     @param mutex Handle of the mutex to be locked.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_mutex_lock()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @added210 Added in CMPI 2.1, superseding the deprecated
         CMPIBrokerExtFT.lockMutex() function.
    */
    int (*lockMutex2) (CMPI_MUTEX_TYPE mutex);

    /**
     @brief Unlock a POSIX threading-conformant mutex.

     CMPIBrokerExtFT.unlockMutex2() unlocks a POSIX threading conformant mutex.

     The behavior in case the mutex is not locked by the current thread is
     defined in the description of CMPIBrokerExtFT.newMutex().

     @param mutex Handle of the mutex to be unlocked.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_mutex_lock()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.
     @added210 Added in CMPI 2.1, superseding the deprecated
         CMPIBrokerExtFT.unlockMutex() function.
    */
    int (*unlockMutex2) (CMPI_MUTEX_TYPE mutex);

    /**
     *   @}
     *   @addtogroup brokerext-condition
     *   @{
     */

    /**
     @brief Destroy a POSIX threading-conformant condition variable.

     CMPIBrokerExtFT.destroyCondition2() destroys a POSIX threading-conformant
     condition variable.

     @param cond Handle of the condition variable to be destroyed.
     @return @parblock
         If successful, zero will be returned.

         If not successful, a non-zero error code will be returned.
     @endparblock
     @par Errors
         Error codes are defined in `errno.h`, specifically for the
         ``pthread_cond_destroy()`` function; both are defined in
         @ref ref-ieee-1003-1 "IEEE 1003.1".
     @capopsys This function is part of the OS Encapsulation Services
         capability.

     @note No corresponding macro
     @added210 Added in CMPI 2.1, superseding the deprecated
         CMPIBrokerExtFT.destroyCondition() function.
    */
    int (*destroyCondition2) (CMPI_COND_TYPE cond);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

} CMPIBrokerExtFT;

#ifdef CMPI_VER_200

/**
 * @brief Function table for MB memory enhancement services.
 *
 * This function table is referenced by the CMPIBroker structure, and provides
 * @ref brokermem-all "Memory Enhancement Services".
 *
 * @capmemory This function table is part of the Memory Enhancement Services
 *     capability.
 * @added200 Added in CMPI 2.0.
 */
typedef struct _CMPIBrokerMemFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     *   @addtogroup brokermem-all
     *   @{
     */

    /**
     @brief Mark a new object lifecycle level for subsequent newly created
         CMPI encapsulated data type objects.

     CMPIBrokerMemFT.mark() marks a new object lifecycle level for the calling
     MI. Subsequent newly created CMPI encapsulated data type objects in that
     MI will be associated with that new object lifecycle level. A subsequent
     invocation of CMPIBrokerMemFT.release() with the returned @ref CMPIGcStat
     pointer will release only the objects associated with that object
     lifecycle level.

     The mark() and release() function calls may be stacked.

     Stacked object lifecycle levels shall not overlap other than inner levels
     being completely contained in outer levels.

     @param mb Points to a CMPIBroker structure.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a @ref CMPIGcStat structure will be
         returned, for use with CMPIBrokerMemFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capmemory This function is part of the Memory Enhancement Services
         capability.
     @bug In the CMPI Standard document, add the more specific statement about
         overlapping stacked object lifecycle levels.
    */
    CMPIGcStat* (*mark) (const CMPIBroker* mb, CMPIStatus* rc);

    /**
     @brief Release all CMPI encapsulated data type objects created at the
         specified object lifecycle level, and remove that level.

     CMPIBrokerMemFT.release() releases all CMPI encapsulated data type objects
     created other than with `clone()` at the specified object lifecycle level,
     and removes that object lifecycle level. This indicates to the MB that
     these objects (including any objects they contain) will no longer be used
     by the MI. The MB may free (=reclaim) the memory associated with these
     objects during the call to this function, or later during some garbage
     collection cycle (see
     Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     The mark() and release() function calls may be stacked. See
     CMPIBrokerMemFT.mark() for details.

     @param mb Points to a CMPIBroker structure.
     @param gc Points to the @ref CMPIGcStat structure returned from the
         CMPIBrokerMemFT.mark() function, that identifies the object lifecycle
         level.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p mb handle is invalid
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (const CMPIBroker* mb, const CMPIGcStat* gc);

    /**
     @brief Allocate an uninitalized memory block of the specified size.

     CMPIBrokerMemFT.cmpiMalloc() allocates an uninitalized memory block of
     the specified size. This function behaves consistently with the
     POSIX ``malloc()`` function (see @ref ref-ieee-1003-1 "IEEE 1003.1").

     The allocated memory block can be explicitly released by the MI using
     CMPIBrokerMemFT.cmpiFree(), or will be automatically released by the MB
     after cleanup of the MI (see
     Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param size Amount of memory to allocate, in Bytes.
     @return @parblock
         If successful, a pointer to the allocated memory block will be
         returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
         No additional error information is passed back.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard document, add a reference to Subclause 4.1.7.
    */
    void* (*cmpiMalloc) (const CMPIBroker* mb, size_t size);

    /**
     @brief Allocate a memory block of the specified size and initialize it to
         zero.

     CMPIBrokerMemFT.cmpiCalloc() allocates a memory block of the specified
     size and initializes it to zero. This function behaves consistently with
     the POSIX ``calloc()`` function (see @ref ref-ieee-1003-1 "IEEE 1003.1").
     The allocated memory block can be explicitly released by the MI using
     CMPIBrokerMemFT.cmpiFree(), or will be automatically released by the MB
     after cleanup of the MI (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param nElems Number of elements to allocate.
     @param sizeElem Size of each element to allocate, in Bytes.
     @return @parblock
         If successful, a pointer to the allocated and initialized memory block
         will be returned.

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
         No additional error information is passed back.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard document, add a reference to Subclause 4.1.7.
    */
    void* (*cmpiCalloc) (const CMPIBroker* mb, size_t nElems, size_t sizeElem);

    /**
     @brief Change the size of a memory block.

     CMPIBrokerMemFT.cmpiRealloc() changes the size of the memory block pointed
     to by @p ptr which shall have been returned by a previous call to
     CMPIBrokerMemFT.cmpiMalloc() or CMPIBrokerMemFT.cmpiCalloc(). This
     function behaves consistently with the POSIX ``realloc()`` function (see
     @ref ref-ieee-1003-1 "IEEE 1003.1"). The allocated memory block can be
     explicitly released by the MI using  CMPIBrokerMemFT.cmpiFree(), or will
     be automatically released by the MB after cleanup of the MI (see
     Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     The function may move the memory block to a new location (whose address
     is returned by the function). The content of the memory block is
     preserved up to the lesser of the new and old sizes, even if the
     block is moved to a new location. If the new size is larger, the value
     of the newly allocated portion is indeterminate.

     @param mb Points to a CMPIBroker structure.
     @param ptr If not NULL, points to previosuly allocated memory.  Passing a
         non-NULL pointer to this function which was not allocated explicitly
         by cmpiMalloc() or cmpiCalloc() is undefined. If @p ptr is NULL, the
         function behaves like cmpiMalloc(), assigning a new memory block of
         size Bytes and returning a pointer to its beginning.
     @param size New size of the memory block, in Bytes. The new size may
         be larger or smaller than (or equal to) the current size.
     @return @parblock
         If successful, a pointer to the resized memory block will be returned.

         If not successful, NULL will be returned returned and the original
         memory block pointed to by @p ptr is not deallocated and is unchanged.
     @endparblock
     @par Errors
         No additional error information is passed back.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard document, add a reference to Subclause 4.1.7.
    */
    void* (*cmpiRealloc) (const CMPIBroker* mb, void* ptr, size_t size);

    /**
     @brief Allocate a memory block and initialize it with a string.

     CMPIBrokerMemFT.cmpiStrDup() allocates a memory block and initializes it
     by copying a C-language string into it. This function behaves consistently
     with the POSIX ``strdup()`` function (see
     @ref ref-ieee-1003-1 "IEEE 1003.1"). The allocated memory block can be
     explicitly released by the MI using CMPIBrokerMemFT.cmpiFree(), or will be
     automatically released by the MB after cleanup of the MI (see Subclause
     4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param str C-language string to be duplicated.
     @return @parblock
         If successful, a pointer to the new memory block (that is, to the new
         C-language string) will be returned.

         If not successful, NULL will be returned returned.
     @endparblock
     @par Errors
         No additional error information is passed back.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard document, add a reference to Subclause 4.1.7.
    */
    char* (*cmpiStrDup) (const CMPIBroker* mb, const char* str);

    /**
     @brief Release a memory block.

     CMPIBrokerMemFT.cmpiFree() releases a memory block. This function behaves
     consistently with the POSIX ``free()`` function (see IEEE 1003.1). This
     indicates to the MB that the memory block will no longer be used by the
     MI. The MB may free (=reclaim) the memory block during the call to this
     function, or later during some garbage collection cycle (see Subclause
     4.1.7 of the @ref ref-cmpi-standard "CMPI Standard"). Memory blocks that
     have not been explicitly released that way, will be automatically released
     after cleanup of the MI.

     @param mb Points to a CMPIBroker structure.
     @param ptr Points to the memory block to free. The memory block shall have
         been allocated via the cmpiMalloc(), cmpiCalloc(), cmpiRealloc(), or
         cmpiStrDup() functions.
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
    */
    void (*cmpiFree) (const CMPIBroker* mb, void* ptr);

    /**
     @brief Release a CMPIInstance object.

     CMPIBrokerMemFT.freeInstance() releases a CMPIInstance object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param inst Points to the CMPIInstance object that is to be released.
         That object shall have been created using CMPIBrokerEncFT.newInstance().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
    */
    void (*freeInstance) (const CMPIBroker* mb, CMPIInstance* inst);

    /**
     @brief Release a CMPIObjectPath object.

     CMPIBrokerMemFT.freeObjectPath() releases a CMPIObjectPath object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param obj Points to the CMPIObjectPath object that is to be released.
         That object shall have been created using
         CMPIBrokerEncFT.newObjectPath().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
    */
    void (*freeObjectPath) (const CMPIBroker* mb, CMPIObjectPath* obj);

    /**
     @brief Release a CMPIArgs object.

     CMPIBrokerMemFT.freeArgs() releases a CMPIArgs object. This indicates to
     the MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param args Points to the CMPIArgs object that is to be released.
         That object shall have been created using CMPIBrokerEncFT.newArgs().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.
    */
    void (*freeArgs) (const CMPIBroker* mb, CMPIArgs* args);

    /**
     @brief Release a CMPIString object.

     CMPIBrokerMemFT.freeString() releases a CMPIString object. This indicates
     to the MB that the object (including any objects it contains) will no
     longer be used by the MI. The MB may free (=reclaim) the memory associated
     with the object during the call to this function, or later during some
     garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param args Points to the CMPIString object that is to be released. That
         object shall have been created using CMPIBrokerEncFT.newString() or
         CMPIBrokerEncFT.newStringCP().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
    */
    void (*freeString) (const CMPIBroker* mb, CMPIString* str);

    /**
     @brief Release a CMPIArray object.

     CMPIBrokerMemFT.freeArray() releases a CMPIArray object. This indicates to
     the MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param array Points to the CMPIArray object that is to be released. That
         object shall have been created using CMPIBrokerEncFT.newArray().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
    */
    void (*freeArray) (const CMPIBroker* mb, CMPIArray* array);

    /**
     @brief Release a CMPIDateTime object.

     CMPIBrokerMemFT.freeDateTime() releases a CMPIDateTime object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param dt Points to the CMPIDateTime object that is to be released. That
         object shall have been created using CMPIBrokerEncFT.newDateTime(),
         CMPIBrokerEncFT.newDateTimeFromBinary(), or
         CMPIBrokerEncFT.newDateTimeFromChars().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability.

     @note No corresponding macro
     @bug In the CMPI Standard, add newDateTimeFromBinary() and
         newDateTimeFromChars() as additional functions that may have created
         the object.
    */
    void (*freeDateTime) (const CMPIBroker* mb, CMPIDateTime* dt);

    /**
     @brief Release a CMPISelectExp object.

     CMPIBrokerMemFT.freeSelectExp() releases a CMPISelectExp object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param se Points to the CMPISelectExp object that is to be released.
         That object shall have been created using CMPIBrokerEncFT.newSelectExp().
     @return None.
     @par Errors
         This function does not indicate whether it succeeded or failed.
     @capmemory This function is part of the Memory Enhancement Services
         capability but can be implemented only if the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability is
         supported as well.

     @note No corresponding macro
     @todo KS: implement macro form of all of the free functions
     @todo KS: Note that there appears to be no OpenPegasus use of any of
           these free functions
    */
    void (*freeSelectExp) (const CMPIBroker* mb, CMPISelectExp* se);

#ifdef CMPI_VER_210

    /**
     @brief Free the memory of a C-language string.

     CMPIBrokerMemFT.freeChars() releases a C-language string. This indicates
     to the MB that the string will no longer be used by the MI. The MB may
     free (=reclaim) the memory associated with the string during the call to
     this function, or later during some garbage collection cycle (see
     Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param mb Points to a CMPIBroker structure.
     @param chars Points to the C-language string to be released. This
         C-language string shall have been created using
         CMPIStringFT.newCharsCP().
     @return None.
     @capcodepage This function is part of the Memory Enhancement Services
         capability but can be implemented only if the
         @ref CMPI_MB_CodepageConversion "Codepage Conversion" capability is
         supported as well.

     @added210 Added in CMPI 2.1.

     @note No corresponding macro
     @bug In the CMPI Standard document, add the additional dependency on
         supporting the Codepage Conversion capability.
    */
    void (*freeChars) (const CMPIBroker* mb, char* chars);

#endif /*CMPI_VER_210*/

    /**
     *   @}
     */

} CMPIBrokerMemFT;

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
 * invoked operation to the MI. The context data is organized as name-value
 * pairs. See
 * @ref def-context-fieldnames "Names of CMPIContext fields" for defined names
 * of contex data entries.
 *
 * For more details, see Subclause 8.1 of the
 * @ref ref-cmpi-standard "CMPI Standard".
 *
 * @capcontext This encapsulated data type is part of the Context Data
 *     capability.
 */
typedef struct _CMPIContext {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIContextFT* ft;

} CMPIContext;

/**
 * @brief Function table of CMPIContext encapsulated data type object.
 */
typedef struct _CMPIContextFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIContext object.

     CMPIContextFT.release() releases a CMPIContext object.

     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim)
     the memory associated with the object during the call to this function,
     or later during some garbage collection cycle
     (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param ctx Points to the CMPIContext object that is to be released.
         That object shall have been created using CMPIContextFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIContext* ctx);

    /**
     @brief Create an independent copy of a CMPIContext object.

     CMPIContextFT.clone() creates an independent copy of a CMPIContext
     object.

     @param ctx Points to the CMPIContext object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIContext object will be
         returned.

         The returned CMPIContext object shall be explicitly released by the MI
         using CMPIContextFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.

     @convfunction CMClone()
    */
    CMPIContext* (*clone) (const CMPIContext* ctx, CMPIStatus* rc);

    /**
     @brief Get a context entry in a CMPIContext object by name.

     CMPIContextFT.getEntry() gets a context entry in a CMPIContext object by
     supplying its name.

     @param ctx Points to the CMPIContext object for this function.
     @param name Context entry name.
         See @ref def-context-fieldnames "Names of CMPIContext fields"
         for defined names.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified context
         entry will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.

     @convfunction CMGetContextEntry()
    */
    CMPIData (*getEntry) (const CMPIContext* ctx, const char* name,
        CMPIStatus* rc);

    /**
     @brief Get a context entry in a CMPIContext object by index.

     CMPIContextFT.getEntryAt() gets a context entry in a CMPIContext object by
     supplying its index.

     @param ctx Points to the CMPIContext object for this function.
     @param index Zero-based position of the context entry in the
         internal data array. The order of context entries in the internal data
         array is implementation-defined.
     @param [out] name
     @parblock
         If not NULL, points to a CMPIString pointer that upon success will
         have been updated to point to a CMPIString object containing the name
         of the returned context entry.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIContext object
         which will be released along with that object, or a new object created
         by the MB which will be automatically released by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").
     @endparblock
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified context
         entry will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.

     @convfunction CMGetContextEntryAt()
    */
    CMPIData (*getEntryAt) (const CMPIContext* ctx, CMPICount index,
        CMPIString** name, CMPIStatus* rc);

    /**
     @brief Get the number of context entries in a CMPIContext object.

     CMPIContextFT.getEntryCount() gets the number of entries in a CMPIContext
     object.

     @param ctx Points to the CMPIContext object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of entries
         in the CMPIContext object will be returned.

         If not successful, the return value will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Entry not found.

     @convfunction CMGetContextEntryCount()
    */
    CMPICount (*getEntryCount) (const CMPIContext* ctx, CMPIStatus* rc);

    /**
     @brief Add or replace a context entry in a CMPIContext object.

     CMPIContextFT.addEntry() adds or replaces a context entry in a CMPIContext
     object.

     @param ctx Points to the CMPIContext object for this function.
     @param name Context entry name.
         See @ref def-context-fieldnames "Names of CMPIContext fields" for
         defined names.
     @param value Points to a CMPIValue structure containing the non-NULL value
         to be assigned to the context entry, or NULL to specify that NULL is
         to be assigned.
     @param type
     @parblock
         @ref CMPIType value specifying the type of the value to be assigned to
         the context entry.

         If the value of @p type is @ref CMPI_chars or @ref CMPI_charsA, the
         C-language string to which the @p chars member of @p value points is
         copied by this function and the original string memory may be freed
         by the MI right after this function returns.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.
     @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - Type not supported for this call, or
         type is not recognized.

     @convfunction CMAddContextEntry()
    */
    CMPIStatus (*addEntry) (const CMPIContext* ctx, const char* name,
        const CMPIValue* value, const CMPIType type);

} CMPIContextFT;

/**
 * @}
 * @addtogroup edt-result
 * @{
 */

/**
 * @brief CMPIResult encapsulated data type object.
 *
 * CMPI enables an MB to actively accept result data as it is generated, using
 * the CMPIResult encapsulated data type.
 *
 * For more details, see Subclause 8.2 of the
 * @ref ref-cmpi-standard "CMPI Standard".
 */
typedef struct _CMPIResult {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIResultFT* ft;

} CMPIResult;

/**
 * @brief Function table of CMPIResult encapsulated data type object.
 */
typedef struct _CMPIResultFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIResult object.

     CMPIResultFT.release() releases a CMPIResult object. This indicates to the
     MB that the object (including any objects it contains) will no longer be
     used by the MI. The MB may free (=reclaim) the memory associated with the
     object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param rslt Points to the CMPIResult object that is to be released.
         That object shall have been created using CMPIResultFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIResult* rslt);

    /**
     @brief Create an independent copy of a CMPIResult object.

     CMPIResultFT.clone() creates an independent copy of a CMPIResult object.

     @param rslt Points to the CMPIResult object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIPropertyList object will be
         returned.

         The returned CMPIResult object shall be explicitly released by the MI
         using CMPIResultFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid.

     @convfunction CMClone()
    */
    CMPIResult* (*clone) (const CMPIResult* rslt, CMPIStatus* rc);

    /**
     @brief Add a value/type pair to a CMPIResult object.

     CMPIResultFT.returnData() adds a value/type pair to be returned to the MB,
     to a CMPIResult object.

     @param rslt Points to the CMPIResult object for this function.
     @param value Points to a CMPIValue structure specifying the non-NULL value
         to be returned, or is NULL to specify that NULL is to be returned
     @param type CMPIType value specifying the type to be returned. Specific
         return types are defined for each function that returns CMPIResult
         objects. If the value of @p type is @ref CMPI_chars or
         @ref CMPI_charsA, the C-language string to which the @p chars member of
         @p value points is copied by this function and the original string
         memory may be freed by the MI right after this function returns.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid,
         or the MB has aborted the request operation for which this data is
         being returned.
     @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - An attempt to return a data type
         that is not allowed for this MI function invocation or @p type is not
         recognized.

     @convfunction CMReturnData()
    */
    CMPIStatus (*returnData) (const CMPIResult* rslt, const CMPIValue* value,
        const CMPIType type);

    /**
     @brief Add an instance to a CMPIResult object.

     CMPIResultFT.returnInstance() adds an instance to be returned to the MB,
     to a CMPIResult object.

     @param rslt Points to the CMPIResult object for this function.
     @param inst Points to a CMPIInstance object representing the instance to
         be returned.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid or the MB
         has aborted the request for which this data is returned.

     @convfunction CMReturnInstance()
    */
    CMPIStatus (*returnInstance) (const CMPIResult* rslt,
        const CMPIInstance* inst);

    /**
     @brief Add an object path to a CMPIResult object.

     CMPIResultFT.returnObjectPath() adds an object path to be returned to the
     MB, to a CMPIResult object.

     @param rslt Points to the CMPIResult object for this function.
     @param op Points to a CMPIObjectPath object representing the object path
         to be returned.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt or @p op handle is invalid,
         or the MB has aborted the request for which this data is being
         returned.

     @convfunction CMReturnObjectPath()
    */
    CMPIStatus (*returnObjectPath) (const CMPIResult* rslt,
        const CMPIObjectPath* op);

    /**
     @brief Indicate that no further items will be added to a CMPIResult object.

     CMPIResultFT.returnDone() indicates to the MB that no further items will
     be added to a CMPIResult object; that is, the MI will not return any more
     data to the MB.

     @param rslt Points to the CMPIResult object for this function.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid,
         or the MB has aborted the request for which this result is defined.

     @convfunction CMReturnDone()
    */
    CMPIStatus (*returnDone) (const CMPIResult* rslt);

#ifdef CMPI_VER_200

    /**
     @brief Add an error to a CMPIResult object.

     CMPIResultFT.returnError() adds an error to be returned to the MB, to a
     CMPIResult object.

     This function may be called multiple times, each time adding one CMPIError
     object to the set of extended errors for this result.

     In WBEM protocols that support multiple extended errors in an error
     response, the MB shall represent the extended errors in the protocol in
     the order of calls to this function. In WBEM protocols that support only
     one extended error in an error response, the MB shall represent the
     extended error from the first call to this function for a particular
     result.

     @param rslt Points to the CMPIResult object for this function.
     @param er
     @parblock
         Points to a CMPIError object representing the error to be returned.

         The CIM status code in the CMPIError object of the first call to this
         function for the result data container of an MI function must match
         the CMPIrc code returned by that MI function.

         The messages in the CMPIError objects are described in each MI
         function.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p rslt handle is invalid or the MB
         has aborted the request for which this data is returned.
     @caperrors This function is part of the Extended Errors capability.

     @convfunction CMReturnError()
     @added200 Added in CMPI 2.0.
    */
    CMPIStatus (*returnError) (const CMPIResult* rslt, const CMPIError* er);

#endif /*CMPI_VER_200*/

} CMPIResultFT;

/**
 * @}
 * @addtogroup edt-string
 * @{
 */

/**
 * @brief CMPIString encapsulated data type object.
 *
 * CMPIString objects represent a sequence of UCS characters. The rules stated
 * in Subclause 5.2.1 of the @ref ref-cmpi-standard "CMPI Standard" apply to
 * any C-language strings that are passed into or returned from CMPIString
 * functions (including the CMPIBrokerEncFT.newString() factory function).
 */
typedef struct _CMPIString {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIStringFT* ft;

} CMPIString;

/**
 * @brief Function table of CMPIString encapsulated data type object.
 */
typedef struct _CMPIStringFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIString object.

     CMPIStringFT.release() releases a CMPIString object. This indicates to the
     MB that the object (including any objects it contains) will no longer be
     used by the MI. The MB may free (=reclaim) the memory associated with the
     object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param str Points to the CMPIString object that is to be released.
         That object shall have been created using CMPIStringFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p str handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIString* str);

    /**
     @brief Create an independent copy of a CMPIString object.

     CMPIStringFT.clone() creates an independent copy of a CMPIString object.

     @param str Points to the CMPIString object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIString object will be
         returned.

         The returned CMPIString object shall be explicitly released by the MI
         using CMPIStringFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p str handle is invalid.

     @convfunction CMClone()
    */
    CMPIString* (*clone) (const CMPIString* str, CMPIStatus* rc);

    /**
     @brief Get a pointer to a C-language string representation of a
         CMPIString object.

     CMPIStringFT.getCharPtr() gets a pointer to a C-language string that
     represents the characters of the CMPIString object.

     @param str Points to the CMPIString object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a C-language string will be returned.

         The character array of the returned string shall not be explicitly
         released by the MI, because it may point to an internal data area in
         the CMPIString object which will be released along with that object,
         or it may point to a new character array created by the MB which will
         be released automatically by the MB (see Subclause 4.1.7 of the
         @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p str handle is invalid.

     @convfunction CMGetCharsPtr()
    */
    const char* (*getCharPtr) (const CMPIString* str, CMPIStatus* rc);

#ifdef CMPI_VER_210

    /**
     @brief Create a C-language string that has converted a CMPIString
         object into a specific codepage.

     CMPIStringFT.newCharsCP() creates a new C-language string that contains
     the string in a CMPIString object, converted into a specific codepage.

     @param str Points to the CMPIString object for this function.
     @param cpid CMPI-specific codepage ID for the codepage to convert to.
         See @ref CMPICodepageID for a list of supported codepages and their
         codepage ID values.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a new C-language string will be returned, in the
         codepage specified in @p cpid.

         The returned C-language string must be freed by the MI using
         CMPIBrokerMemFT.freeChars().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p str handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p cpid is invalid.
     @li `CMPI_RC_ERR_NOT_IN_CODEPAGE` - The string contains characters that
         are not representable in the specified codepage.
     @capcodepage This function is part of the Codepage Conversion
         capability.
     @added210 Added in CMPI 2.1.

     @note No corresponding macro.
    */
    char* (*newCharsCP) (const CMPIString* str, const CMPICodepageID cpid,
        CMPIStatus* rc);

#endif /*CMPI_VER_210*/

} CMPIStringFT;

/**
 * @}
 * @addtogroup edt-array
 * @{
 */

/**
 * @brief CMPIArray encapsulated data type object.
 *
 * CMPIArray objects represent arrays of values of the same base types;
 * however, some of them can be CIM NULL values. CMPIArray objects are used for
 * example in CMPIData structures that are returned from and passed to many MB
 * and MI functions and are returned directly from some specific retrieval
 * functions, such as CMPIErrorFT.getMessageArguments().
 *
 * @bug In the CMPI Standard document, replace the introductory description
 *     for CMPIArray support (first three paragraphs) with the description from
 *     the header file.
 */
typedef struct _CMPIArray {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIArrayFT* ft;

} CMPIArray;

/**
 * @brief Function table of CMPIArray encapsulated data type object.
 */
typedef struct _CMPIArrayFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIArray object.

     CMPIArrayFT.release() releases a CMPIArray object. This indicates to the
     MB that the object (including any objects it contains) will no longer be
     used by the MI. The MB may free (=reclaim) the memory associated with the
     object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param ar Points to the CMPIArray object that is to be released.
         That object shall have been created using CMPIArrayFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIArray* ar);

    /**
     @brief Create an independent copy of a CMPIArray object.

     CMPIArrayFT.clone() creates an independent copy of a CMPIArray object.

     @param ar Points to the CMPIArray object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIArray object will be
         returned.

         The returned CMPIArray object shall be explicitly released by the MI
         using CMPIArrayFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.

     @convfunction CMClone()
    */
    CMPIArray* (*clone) (const CMPIArray* ar, CMPIStatus* rc);

    /**
     @brief Get the number of array elements in a CMPIArray object.

     CMPIArrayFT.getSize() gets the number of array elements in a CMPIArray
     object.

     @param ar Points to the CMPIArray object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of array
         elements will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.

     @convfunction CMGetArrayCount()
    */
    CMPICount (*getSize) (const CMPIArray* ar, CMPIStatus* rc);

    /**
     @brief Get the type of the array elements in a CMPIArray object.

     CMPIArrayFT.getSimpleType() gets the type of the array elements in a
     CMPIArray object.

     @param ar Points to the CMPIArray object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIType value indicating the type of the
         CMPIArray elements will be returned. The returned value indicates the
         type of single array elements; for example, the value returned for
         a CMPIArray object that contains CMPIString objects, will be
         @ref CMPI_string, and not @ref CMPI_stringA.

         If not successful, @ref CMPI_null will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.

     @convfunction CMGetArrayType()
    */
    CMPIType (*getSimpleType) (const CMPIArray* ar, CMPIStatus* rc);

    /**
     @brief Get the value of an array element in a CMPIArray object by index.

     CMPIArrayFT.getElementAt() gets the value of an array element of an array
     element in a CMPIArray object by index.

     @param ar Points to the CMPIArray object for this function.
     @param index Zero-based position in the CMPIArray. The position shall
         be equal to or greater than 0 and less than the size of the array.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified array
         element will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - @p index value out of range.

     @convfunction CMGetArrayElementAt()
     @bug In the CMPI Standard document, add the phrase "by index" to the
         description.
    */
    CMPIData (*getElementAt) (const CMPIArray* ar, CMPICount index,
        CMPIStatus* rc);

    /**
     @brief Set the value of an existing array element in a CMPIArray object
         by index.

     CMPIArrayFT.setElementAt() sets the value of an existing array element in
     a CMPIArray object by index.

     @param ar Points to the CMPIArray object for this function.
     @param index Zero-based position of the existing element in the
         CMPIArray object. The position shall be equal to or greater than 0 and
         less than the size of the array.
     @param value Points to a CMPIValue structure containing the non-NULL value
         to be assigned to the element, or is NULL to specify that the element
         will be set to NULL.
     @param type
     @parblock
         Either the simple base type of the array or @ref CMPI_null.

         The use of @ref CMPI_null for @p type is deprecated. Specify the
         simple base type of the array instead. (**Deprecated**)

         If the value of @p type is @ref CMPI_chars, the C-language string to
         which the @p chars member of @p value points is copied by this
         function and the original string memory may be freed by the MI right
         after this function returns.
     @endparblock
     @return @parblock
         CMPIStatus structure containing the function return status.

         If not successful, the array element’s state shall be set to
         @ref CMPI_nullValue, if possible.

         This behavior has been deprecated in CMPI 2.1, and callers should now
         assume that it is undefined whether the array element's state has
         changed in case of error. (**Deprecated**)
     @endparblock
     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ar handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - @p index value out of range.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - @p type does not correspond to the
         simple base type of @p ar.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p value is invalid.

     @convfunction CMSetArrayElementAt()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @deprecated The use of @ref CMPI_null for @p type is deprecated since
         CMPI 2.1. Specify the simple base type of the array instead.
     @deprecated The behavior of setting the array element's state to
         @ref CMPI_nullValue when the function was not successful, is deprecated
         since CMPI 2.1.
         Instead, callers should assume that it is undefined whether the array
         element's state has changed when the function was not successful.
     @bug In the CMPI Standard document, add the phrase "by index" to the
         description.
    */
    CMPIStatus (*setElementAt) (const CMPIArray* ar, CMPICount index,
        const CMPIValue* value, CMPIType type);

} CMPIArrayFT;

/**
 * @}
 * @addtogroup edt-enumeration
 * @{
 */

/**
 * @brief CMPIEnumeration encapsulated data type object.
 *
 * CMPIEnumeration objects are used to store the results of enumerating MB
 * functions, such as CMPIBrokerFT.enumerateInstances(), or
 * CMPIBrokerFT.associatorNames().
 *
 * @bug In the CMPI Standard document, replace the introductory description
 *     for CMPIEnumeration support (first two paragraphs) with the description
 *     from the header file.
 */
typedef struct _CMPIEnumeration {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIEnumerationFT* ft;

} CMPIEnumeration;

/**
 * @brief Function table of CMPIEnumeration encapsulated data type object.
 */
typedef struct _CMPIEnumerationFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIEnumeration object.

     CMPIEnumerationFT.release() releases a CMPIEnumeration object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param en Points to the CMPIEnumeration object that is to be released.
        That object shall have been created using CMPIEnumerationFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p en handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIEnumeration* en);

    /**
     @brief Create an independent copy of a CMPIEnumeration object.

     CMPIEnumerationFT.clone() creates an independent copy of a CMPIEnumeration
     object.

     @param en Points to the CMPIEnumeration object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIEnumeration object will be
         returned.

         The returned CMPIEnumeration object shall be explicitly released by
         the MI using CMPIEnumerationFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p en handle is invalid.

     @convfunction CMClone()
    */
    CMPIEnumeration* (*clone) (const CMPIEnumeration* en, CMPIStatus* rc);

    /**
     @brief Get the next element in a CMPIEnumeration object.

     CMPIEnumerationFT.getNext() gets the next element in a CMPIEnumeration
     object.

     @param en Points to the CMPIEnumeration object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the next element will
         be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p en handle is invalid.
     @li `CMPI_RC_NO_MORE_ELEMENTS` - No more elements in @p en.

     @convfunction CMGetNext()
     @changed210 In CMPI 2.1, added the return code `CMPI_RC_NO_MORE_ELEMENTS`
         (which had been used by this function before).
    */
    CMPIData (*getNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /**
     @brief Test for any elements left in a CMPIEnumeration object.

     CMPIEnumerationFT.hasNext() tests for any elements left in a
     CMPIEnumeration object.

     @param en Points to the CMPIEnumeration object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIBoolean value indicating the test result will be
         returned, as follows:
         @li True indicates that the enumeration has more elements left;
         @li False indicates that this is not the case.

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p en handle is invalid.

     @convfunction CMHasNext()
     @required210 In CMPI 2.1, added a requirement for the MB to return False
         if not successful.
    */
    CMPIBoolean (*hasNext) (const CMPIEnumeration* en, CMPIStatus* rc);

    /**
     @brief Convert a CMPIEnumeration object to a CMPIArray object.

     CMPIEnumerationFT.toArray() converts a CMPIEnumeration object into a
     CMPIArray object.

     @param en Points to the CMPIEnumeration object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIArray object containing the elements
         from the CMPIEnumeration object will be returned.

         The returned CMPIArray object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIEnumeration object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p en handle is invalid.

     @convfunction CMToArray()
    */
    CMPIArray* (*toArray) (const CMPIEnumeration* en, CMPIStatus* rc);

} CMPIEnumerationFT;

/**
 * @}
 * @addtogroup edt-instance
 * @{
 */

/**
 * @brief CMPIInstance encapsulated data type object.
 *
 * CMPIInstance represents an instance specification, consisting of instance
 * path, class name, and property values. It is used to transfer the state of
 * an instance between MB and MI (and vice versa).
 *
 * @bug In the CMPI Standard document, add an introductory description
 *     for CMPIInstance support, using the description from the header file.
 */
typedef struct _CMPIInstance {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIInstanceFT* ft;

} CMPIInstance;

/**
 * @brief Function table of CMPIInstance encapsulated data type object.
 *
 * For functions that are not supported, their function pointers in the
 * CMPIInstanceFT function table shall not be NULL, but shall point to a
 * function that can be called and then indicates back to the caller that it is
 * not supported, as specified in the description of the function.
 */
typedef struct _CMPIInstanceFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIInstance object.

     CMPIInstanceFT.release() releases a CMPIInstance object. This indicates to
     the MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param inst Points to the CMPIInstance object that is to be released.
         That object shall have been created using CMPIInstanceFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIInstance* inst);

    /**
     @brief Create an independent copy of a CMPIInstance object.

     CMPIInstanceFT.clone() creates an independent copy of a CMPIInstance
     object.

     @param inst Points to the CMPIInstance object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIInstance object will be
         returned.

         The returned CMPIInstance object shall be explicitly released by the
         MI using CMPIInstanceFT.release().

         If not successful, NULL will be returned.
     @endparblock
     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.

     @convfunction CMClone()
    */
    CMPIInstance* (*clone) (const CMPIInstance* inst, CMPIStatus* rc);

    /**
     @brief Get a property in a CMPIInstance object by name.

     CMPIInstanceFT.getProperty() gets a gets a property in a CMPIInstance
     object by name.

     @param inst Points to the CMPIInstance object for this function.
     @param name Property name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified property
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.

     @convfunction CMGetProperty()
     @bug In the CMPI Standard document, add "by name" to the long description.
    */
    CMPIData (*getProperty) (const CMPIInstance* inst, const char* name,
        CMPIStatus* rc);

    /**
     @brief Get a property in a CMPIInstance object by index.

     CMPIInstanceFT.getPropertyAt() gets a property in a CMPIInstance object by
     index.

     @param inst Points to the CMPIInstance object for this function.
     @param index Zero-based position of the property in the internal data
         array.
     @param [out] name If not NULL, points to a CMPIString pointer that upon
         success is updated to point to a CMPIString object containing the
         property name. The returned CMPIString object shall not be explicitly
         released by the MI, because it may be an internal object of the
         CMPIString object which will be released along with that object, or a
         new object created by the MB which will be released automatically by
         the MB (see Subclause 4.1.7 of the
         @ref ref-cmpi-standard "CMPI Standard").
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified property.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Property not found.

     @convfunction CMGetPropertyAt()
     @bug In the CMPI Standard document, add "by index" to the long
         description, and change "index number" to "position" in the
         description of the index argument.
    */
    CMPIData (*getPropertyAt) (const CMPIInstance* inst, CMPICount index,
        CMPIString** name, CMPIStatus* rc);

    /**
     @brief Get the number of properties in a CMPIInstance object.

     CMPIInstanceFT.getPropertyCount() gets the number of properties
     in a CMPIInstance object.

     @param inst Points to the CMPIInstance object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of
         properties in the instance will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.

     @convfunction CMGetPropertyCount()
    */
    CMPICount (*getPropertyCount) (const CMPIInstance* inst, CMPIStatus* rc);

    /**
     @brief Add or replace a property value in a CMPIInstance object by name.

     CMPIInstanceFT.setProperty() adds or replaces a property value in a
     CMPIInstance object by name.

     If the property is a key property, the function may or may not in addition
     add or update the key binding in the object path of the instance. In order
     for MIs not to be dependent on this behavior, MIs should set key property
     values in instances and key binding values in object paths separately. Key
     binding values can be set during CMPIBrokerEncFT.newInstance() and by
     using CMPIInstanceFT.setObjectPath(). The MI shall specify consistent
     values for key bindings and key properties.

     @param inst Points to the CMPIInstance object for this function.
     @param name Property name.
     @param value Points to a CMPIValue structure containing the non-NULL value
         to be assigned to the property, or NULL to specify that NULL is to be
         assigned.
     @param type
     @parblock
         CMPIType value specifying the type of the value to be assigned to the
         property.

         All types of CIM values are supported.

         If the value of @p type is @ref CMPI_chars or @ref CMPI_charsA, the
         C-language string to which the chars member of @p value points is
         copied by this function and the original string memory may be freed by
         the MI right after this function returns.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ctx handle is invalid.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - @p type does not correspond to the
         class-defined type.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p name is not a valid property
         name.

     @convfunction CMSetProperty()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.

     @bug In the CMPI Standard document, add "by name" to the long description.
    */
    CMPIStatus (*setProperty) (const CMPIInstance* inst, const char* name,
        const CMPIValue* value, CMPIType type);

    /**
     @brief Get the instance path component of a CMPIInstance object.

     CMPIInstanceFT.getObjectPath() generates a CMPIObjectPath object from the
     namespace, class name, and key properties of a CMPIInstance object.

     @param inst Points to the CMPIInstance object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIObjectPath object representing the
         instance path of the CMPIInstance will be returned.

         The returned CMPIObjectPath object shall not be explicitly released by
         the MI, because it may be an internal object of the CMPIInstance
         object which will be released along with that object, or a new object
         created by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.

     @convfunction CMGetObjectPath()
    */
    CMPIObjectPath* (*getObjectPath) (const CMPIInstance* inst,
        CMPIStatus* rc);

    /**
     @brief Attach a property filter to a CMPIInstance object.

     CMPIInstanceFT.setPropertyFilter() attaches a property filter to a
     CMPIInstance object, replacing any previous property filter settings for
     this object.

     By calling this function, the MI delegates property list filtering to the
     MB for this CMPIInstance object, for all of its properties including those
     that had already been set before the call to setPropertyFilter().

     @param inst Points to the CMPIInstance object for this function.
     @param properties
     @parblock
         The properties that will be accepted by subsequent setProperty()
         function calls. The properties argument is an array of pointers to
         strings, terminated by a NULL pointer. A NULL value effectively means
         that all properties will be accepted. A pointer to an empty array
         means that no properties will be accepted.

         The list of properties specified in the properties argument shall
         match the list of properties specified in the call to the MI function
         that calls CMPIInstanceFT.setPropertyFilter().
     @endparblock
     @param keyList This argument shall be ignored by the MB; it is here to
         maintain binary compatibility with previous specifications. MIs
         conforming to CMPI 2.0 or later shall set the key names and values via
         the CMPIInstanceMI.setObjectPath() function.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid arguments.
     @capfiltering This function is part of the Property Filtering
         capability.

     @convfunction CMSetPropertyFilter()
     @bug In the CMPI Standard document, the description of the
         CMPI_RC_ERR_INVALID_PARAMETER return code states "The keyList argument
         is missing", and the change history states that that return code
         should not be returned by the MB because the keyList argument is now
         ignored. That is incorrect, because that return code can also be used
         to indicate issues in the `properties` argument. The document needs to
         be updated to match the description in the header file.
    */
    CMPIStatus (*setPropertyFilter) (const CMPIInstance* inst,
        const char** properties, const char** keyList);

    /**
     @brief Set the instance path component of a CMPIInstance object.

     CMPIInstanceFT.setObjectPath() sets the instance path component of a
     CMPIInstance object.

     The function may or may not in addition update the key property values in
     the instance to the values of the key bindings in the object path. In
     order for MIs not to be dependent on this behavior, MIs should set key
     property values in instances and key binding values in object paths
     separately. Property values can be set by using
     CMPIInstanceFT.setProperty() or CMPIInstanceFT.setPropertyWithOrigin().
     The MI shall specify consistent values for key bindings and key
     properties.

     @param inst Points to the CMPIInstance object for this function.
     @param op Points to a CMPIObjectPath object. All components of the object
         path of the instance will be set/replaced from the object path in this
         argument. The object path in this argument shall specify a non-NULL
         namespace, a non-NULL creation class name, as well as all keys for the
         instance. The object path may specify a non-NULL host for the instance
         (this is used for instances returned by cross-host associations).
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst or @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Object path components specified in
         @p op are invalid.

     @convfunction CMSetObjectPath()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @bug In the CMPI Standard document, change the first sentence of the
         description to use wording that is consistent with the short
         description.
    */
    CMPIStatus (*setObjectPath) (const CMPIInstance* inst,
        const CMPIObjectPath* op);

#ifdef CMPI_VER_200

    /**
     @brief Add or replace a property value and class origin in a CMPIInstance
         object by name.

     CMPIInstanceFT.setPropertyWithOrigin() adds or replaces a property value
     and class origin in a CMPIInstance object by name.

     If the property is a key property, the function may or may not in addition
     add or update the key binding in the object path of the instance. In order
     for MIs not to be dependent on this behavior, MIs should set key property
     values in instances and key binding values in object paths separately. Key
     binding values can be set during CMPIBrokerEncFT.newInstance() and by
     using CMPIInstanceFT.setObjectPath(). The MI shall specify consistent
     values for key bindings and key properties.

     @param inst Points to the CMPIInstance object for this function.
     @param name Property name.
     @param value Points to a CMPIValue structure containing non-NULL value to
         be assigned to the property, or is NULL to specify that NULL is to be
         assigned.
     @param type
     @parblock
         The type of the value to be assigned to the property.

         All types of CIM values are supported.

         If the value of @p type is @ref CMPI_chars or @ref CMPI_charsA, the
         C-language string to which the @p chars member of @p value points is
         copied by this function and the original string memory may be freed by
         the MI right after this function returns.
     @endparblock
     @param origin
     @parblock
         The name of the class in which this property was originally defined.
         If NULL, then no origin is attached to the property.

         The MB shall conform to the requirements of the client protocol
         regarding class origin information.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p inst handle is invalid.
     @li `CMPI_RC_ERR_TYPE_MISMATCH` - @p type does not correspond to
         class-defined type.

     @convfunction CMSetPropertyWithOrigin()
     @added200 Added in CMPI 2.0.
     @bug In the CMPI Standard document, add "and class origin" in the short
         and long descriptions.
     @bug In the CMPI Standard document, add to the change history that the
         function was added in CMPI 2.0.
    */
    CMPIStatus (*setPropertyWithOrigin) (const CMPIInstance* inst,
        const char* name, const CMPIValue* value, const CMPIType type,
        const char* origin);

#endif /*CMPI_VER_200*/

} CMPIInstanceFT;

/**
 * @}
 * @addtogroup edt-objectpath
 * @{
 */

/**
 * @brief CMPIObjectPath encapsulated data type object.
 *
 * CMPIObjectPath represents a CIM object path, consisting of hostname,
 * namespace name, class name and key bindings. It can be used to represent
 * namespace paths, class paths, or instance paths.
 * See @ref ref-dmtf-dsp0004 "DSP0004" for more details on object paths.
 *
 * @bug In the CMPI Standard document, add an introductory description
 *     for CMPIObjectPath support, using the description from the header file.
 */
typedef struct _CMPIObjectPath {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIObjectPathFT* ft;

} CMPIObjectPath;

/**
 * @brief Function table of CMPIObjectPath encapsulated data type object.
 */
typedef struct _CMPIObjectPathFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIObjectPath object.

     CMPIObjectPathFT.release() releases a CMPIObjectPath object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param op Points to the CMPIObjectPath object that is to be released.
         That object shall have been created using CMPIObjectPathFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIObjectPath* op);

    /**
     @brief Create an independent copy of a CMPIObjectPath object.

     CMPIObjectPathFT.clone() creates an independent copy of a CMPIObjectPath
     object.

     @param op Points to the CMPIObjectPath object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIObjectPath object will be
         returned.

         The returned CMPIObjectPath object shall be explicitly released by the
         MI using CMPIObjectPathFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMClone()
    */
    CMPIObjectPath* (*clone) (const CMPIObjectPath* op, CMPIStatus* rc);

    /**
     @brief Set the namespace component in a CMPIObjectPath object.

     CMPIObjectPathFT.setNameSpace() sets the namespace component in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param ns New namespace name.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMSetNameSpace()
     @changed210 In CMPI 2.1, added const-ness to @p op.
     @bug In the CMPI Standard document, change "set or replace" to "set", in
         the short and long descriptions.
    */
    CMPIStatus (*setNameSpace) (const CMPIObjectPath* op, const char* ns);

    /**
     @brief Get the namespace component from a CMPIObjectPath object.

     CMPIObjectPathFT.getNameSpace() gets the namespace component from a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the
         namespace component of the object path will be returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIObjectPath object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMGetNameSpace()
    */
    CMPIString* (*getNameSpace) (const CMPIObjectPath* op, CMPIStatus* rc);

    /**
     @brief Set the host name component in a CMPIObjectPath object.

     CMPIObjectPathFT.setHostname() sets the host name component in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param hn Points to a CMPIString containing the host name.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMSetHostname()
     @changed210 In CMPI 2.1, added const-ness to @p op.
     @bug In the CMPI Standard document, change "set or replace" to "set", in
         the short and long descriptions.
    */
    CMPIStatus (*setHostname) (const CMPIObjectPath* op, const char* hn);

    /**
     @brief Get the host name component in a CMPIObjectPath object.

     CMPIObjectPathFT.getHostname() gets the host name component in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the host
         name component of the object path will be returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIObjectPath object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMGetHostname()
    */
    CMPIString* (*getHostname) (const CMPIObjectPath* op, CMPIStatus* rc);

    /**
     @brief Set the class name component in a CMPIObjectPath object.

     CMPIObjectPathFT.setClassName() sets the class name component in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param cn New class name.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMGetClassName()
     @changed210 In CMPI 2.1, added const-ness to @p op.
     @bug In the CMPI Standard document, change "set or replace" to "set", in
         the short and long descriptions.
    */
    CMPIStatus (*setClassName) (const CMPIObjectPath* op, const char* cn);

    /**
     @brief Get the class name component in a CIMObjectPath object.

     CMPIObjectPathFT.getClassName() gets the classname component in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the class
         name component of the object path will be returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIObjectPath object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMGetClassName()
    */
    CMPIString* (*getClassName) (const CMPIObjectPath* op, CMPIStatus* rc);

    /**
     @brief Add or replace a key binding in a CMPIObjectPath object by name.

     CMPIObjectPathFT.addKey() adds or replaces a key binding in a
     CMPIObjectPath object by name.

     @param op Points to the CMPIObjectPath object for this function.
     @param key Name of the key binding.
     @param value Points to a CMPIValue structure containing the value to be
         assigned to the key binding. Key bindings are not permitted to be NULL.
     @param type
     @parblock
         The type of the value to be assigned to the key binding.

         All types of CIM values valid for keys are supported.

         If the value of the type argument is @ref CMPI_chars or @ref
         CMPI_charsA, the C-language string to which the chars member of @p
         value points is copied by this function and the original string memory
         may be freed by the MI right after this function returns.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p key or @p value is invalid.

     @convfunction CMAddKey()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @bug In the CMPI Standard document, add "by name" to the long description.
    */
    CMPIStatus (*addKey) (const CMPIObjectPath* op, const char* key,
        const CMPIValue* value, const CMPIType type);

    /**
     @brief Get a key binding in a CMPIObjectPath object by name.

     CMPIObjectPathFT.getKey() gets a key binding in a CMPIObjectPath object by
     name.

     @param op Points to the CMPIObjectPath object for this function.
     @param key Name of the key binding.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified key
         binding will be returned.

         The MB will attempt to set the type in the returned CMPIData structure
         to the precise CIM type, if available. Versions of the CIM-XML protocol
         before @ref ref-dmtf-dsp0200 "DSP0200" Version 1.4 did not mandate the
         presence of the precise CIM type. In those versions, the precise CIM
         type was only recommended to be present. If the precise CIM type is not
         available to the MB, it will use the following more general types in
         the returned CMPIData structure:

         <pre>
         \#define CMPI_keyInteger   (CMPI_sint64)
         \#define CMPI_keyString    (CMPI_string)
         \#define CMPI_keyBoolean   (CMPI_boolean)
         \#define CMPI_keyRef       (CMPI_ref)</pre>

         In addition, the @ref CMPI_keyValue flag will be set in CMPIData.state
         to indicate that the value is a key binding.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Key not found.

     @convfunction CMGetKey()
    */
    CMPIData (*getKey) (const CMPIObjectPath* op, const char* key,
        CMPIStatus* rc);

    /**
     @brief Get a key binding in a CMPIObjectPath object by index.

     CMPIObjectPathFT.getKeyAt() gets a key binding in a CMPIObjectPath object
     by index.

     @param op Points to the CMPIObjectPath object for this function.
     @param index Zero-based position of the key binding within the internal
         data array.
     @param [out] name Points to a CMPIString pointer that upon success
         will have been updated to point to a CMPIString object specifying the
         name of the key binding. That CMPIString object shall not be
         explicitly released by the MI, because it may be an internal object of
         the CMPIObjectPath object which will be released along with that
         object, or a new object created by the MB which will be released
         automatically by the MB (see Subclause 4.1.7 of the
         @ref ref-cmpi-standard "CMPI Standard").
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified key
         binding will be returned.

         The MB will attempt to set the type in the returned CMPIData structure
         to the precise CIM type, if available. Versions of the CIM-XML
         protocol before @ref ref-dmtf-dsp0200 "DSP0200" Version 1.4 did not
         mandate the presence of the precise CIM type. In those versions, the
         precise CIM type was only recommended to be present. If the precise
         CIM type is not available to the MB, it will use the following more
         general types in the returned CMPIData structure:

         <pre>
         \#define CMPI_keyInteger   (CMPI_sint64)
         \#define CMPI_keyString    (CMPI_string)
         \#define CMPI_keyBoolean   (CMPI_boolean)
         \#define CMPI_keyRef       (CMPI_ref)</pre>

         In addition, the @ref CMPI_keyValue flag will be set in CMPIData.state
         to indicate that the value is a key binding.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Key not found.

     @convfunction CMGetKeyAt()
    */
    CMPIData (*getKeyAt) (const CMPIObjectPath* op, CMPICount index,
            CMPIString** name, CMPIStatus* rc);

    /**
     @brief Get the number of key bindings in a CMPIObjectPath object.

     CMPIObjectPathFT.getKeyCount() gets the number of key bindings in a
     CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of key
         bindings will be returned. If the CMPIObjectPath object does not have
         a key component, the function will succeed and return 0.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @convfunction CMGetKeyCount()
    */
    CMPICount (*getKeyCount) (const CMPIObjectPath* op, CMPIStatus* rc);

    /**
     @brief Set the namespace and class name components in a CMPIObjectPath
         object from another CMPIObjectPath object.

     CMPIObjectPathFT.setNameSpaceFromObjectPath() sets the namespace and class
     name components in a CMPIObjectPath object from another CMPIObjectPath
     object.

     @param op Points to the CMPIObjectPath object for this function.
     @param src Points to a CMPIObjectPath object used as the source for the
         new namespace and class name components.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p src is invalid.

     @convfunction CMSetNameSpaceFromObjectPath()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @bug In the CMPI Standard document, change "set or replace" to "set", in
         the short and long descriptions.
    */
    CMPIStatus (*setNameSpaceFromObjectPath) (const CMPIObjectPath* op,
        const CMPIObjectPath* src);

    /**
     @brief Set the host name, namespace, and class name components in a
         CMPIObjectPath object from another CMPIObjectPath object.

     CMPIObjectPathFT.setHostAndNameSpaceFromObjectPath() sets the host name,
     namespace, and class name components in a CMPIObjectPath object from
     another CMPIObjectPath object.

     @param op Points to the CMPIObjectPath object for this function.
     @param src Points to a CMPIObjectPath object used as the source for the
         new host name, namespace, and class name components.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p src is invalid.

     @convfunction CMSetHostAndNameSpaceFromObjectPath()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @bug In the CMPI Standard document, change "set or replace" to "set", in
         the short and long descriptions.
    */
    CMPIStatus (*setHostAndNameSpaceFromObjectPath) (const CMPIObjectPath* op,
        const CMPIObjectPath* src);

    /**
     @brief Get a class qualifier.

     CMPIObjectPathFT.getClassQualifier() gets a class qualifier in the class
     identified by this object path.

     @param op Points to a CMPIObjectPath object that references the class
         and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by the MB.
     @param qName Qualifier name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified qualifier
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in @p op is
         invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in @p op is invalid
         or does not exist.
     @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in @p qName is
         invalid for classes.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capqualifiers This function is part of the Basic Qualifier capability.

     @convfunction CMGetClassQualifier()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`,
         `CMPI_RC_ERR_NOT_FOUND`, and `CMPI_RC_ERR_FAILED`. It is believed that
         MB implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
    */
    CMPIData (*getClassQualifier) (const CMPIObjectPath* op,
        const char* qName, CMPIStatus* rc);

    /**
     @brief Get a property qualifier.

     CMPIObjectPathFT.getPropertyQualifier() gets a property qualifier in the
     class identified by this object path.

     @param op Points to a CMPIObjectPath object that references the
         class and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by the MB.
     @param pName Property name.
     @param qName Qualifier name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified qualifier
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in @p op is
         invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in @p op is invalid
         or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property (or reference)
         specified in @p pName is not exposed by the class specified in @p op.
     @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in @p qName is
         invalid for properties (including references).
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capqualifiers This function is part of the Basic Qualifier capability.

     @convfunction CMGetPropertyQualifier()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`,
         `CMPI_RC_ERR_INVALID_PARAMETER`, `CMPI_RC_ERR_NOT_FOUND`, and
         `CMPI_RC_ERR_FAILED`. It is believed that MB implementations needed to
         use these return codes already, so that their addition only fixes an
         omission in this standard and does not create a compatibility issue
         for MIs that conform to CMPI 2.0.
    */
    CMPIData (*getPropertyQualifier) (const CMPIObjectPath* op,
        const char* pName, const char* qName, CMPIStatus* rc);

    /**
     @brief Get a method qualifier.

     CMPIObjectPathFT.getMethodQualifier() gets a method qualifier in the class
     identified by this object path.

     @param op Points to a CMPIObjectPath object that references the class
         and that shall contain the namespace and class components. The
         hostname and key components, if present, will be ignored by the MB.
     @param mName Method name.
     @param qName Qualifier name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified qualifier
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in @p op is
         invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in @p op is invalid
         or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The property (or reference)
         specified in @p pName is not exposed by the class specified in @p op.
     @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in @p qName is
         invalid for methods.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capqualifiers This function is part of the Basic Qualifier capability.

     @convfunction CMGetMethodQualifier()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`,
         `CMPI_RC_ERR_NOT_FOUND`, and `CMPI_RC_ERR_FAILED`. It is believed that
         MB implementations needed to use these return codes already, so that
         their addition only fixes an omission in this standard and does not
         create a compatibility issue for MIs that conform to CMPI 2.0.
    */
    CMPIData (*getMethodQualifier) (const CMPIObjectPath* op,
        const char* methodName, const char* qName, CMPIStatus* rc);

    /**
     @brief Get a parameter qualifier.

     CMPIObjectPathFT.getParameterQualifier() gets a parameter qualifier in
     the class identified by this object path.

     @param op Points to a CMPIObjectPath object that references the
         class and that shall contain the namespace and class components.
         The hostname and key components, if present, will be ignored by
         the MB.
     @param mName Method name.
     @param pName Parameter name.
     @param qName Qualifier name.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified qualifier
         will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.
     @li `CMPI_RC_ERR_INVALID_NAMESPACE` - The namespace specified in @p op is
         invalid or does not exist.
     @li `CMPI_RC_ERR_INVALID_CLASS` - The class specified in @p op is invalid
         or does not exist.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The method specified in @p mName is
         not exposed by the class specified in @p op, or it does not have a
         parameter with the name specified in @p pName.
     @li `CMPI_RC_ERR_NOT_FOUND` - The qualifier specified in @p qName is
         invalid for parameters.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @capqualifiers This function is part of the Basic Qualifier capability.

     @convfunction CMGetParameterQualifier()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_NAMESPACE`, `CMPI_RC_ERR_INVALID_CLASS`,
         `CMPI_RC_ERR_INVALID_PARAMETER`, `CMPI_RC_ERR_NOT_FOUND`, and
         `CMPI_RC_ERR_FAILED`. It is believed that MB implementations needed to
         use these return codes already, so that their addition only fixes an
         omission in this standard and does not create a compatibility issue
         for MIs that conform to CMPI 2.0.
    */
    CMPIData (*getParameterQualifier) (const CMPIObjectPath* op,
        const char* mName, const char* pName, const char* qName,
        CMPIStatus* rc);

    /**
     @brief Convert a CMPIObjectPath object into an implementation-specific
         string format.

     CMPIObjectPathFT.toString() converts the object path in a CMPIObjectPath
     object into an MB implementation-specific string representation.

     @param op Points to the CMPIObjectPath object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the string
         representation of the object path will be returned. The format of the
         string representation will vary depending on the specific MB
         implementation.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIObjectPath object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p op handle is invalid.

     @note No corresponding macro
    */
    CMPIString* (*toString) (const CMPIObjectPath* op, CMPIStatus* rc);

} CMPIObjectPathFT;

/**
 * @}
 * @addtogroup qualifier-services
 * @{
 *   The qualifier services are the following member functions from the
 *   CMPIObjectPath encapsulated data type object:
 *
 *   @li CMPIObjectPathFT.getClassQualifier()
 *   @li CMPIObjectPathFT.getPropertyQualifier()
 *   @li CMPIObjectPathFT.getMethodQualifier()
 *   @li CMPIObjectPathFT.getParameterQualifier()
 */

/**
 * @}
 * @addtogroup edt-args
 * @{
 */

/**
 * @brief CMPIArgs encapsulated data type object.
 *
 * CMPIArgs is a container that is used to represent method parameter values for
 * method invocations.
 *
 * @bug In the CMPI Standard document, replace the introductory description
 *     for CMPIArgs support (first paragraph) with the description from the
 *     header file.
 */
typedef struct _CMPIArgs {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIArgsFT* ft;

} CMPIArgs;

/**
 * @brief Function table of CMPIArgs encapsulated data type object.
 */
typedef struct _CMPIArgsFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIArgs object.

     CMPIArgsFT.release() releases a CMPIArgs object. This indicates to the
     MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated
     with the object during the call to this function, or later during some
     garbage collection cycle
     (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param args Points to the CMPIArgs object that is to be released.
         That object shall have been created using CMPIArgsFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIArgs* args);

    /**
     @brief Create an independent copy of a CMPIRArgs object.

     CMPIArgsFT.clone() creates an independent copy of a CMPIRArgs object.

     @param args Points to the CMPIArgs object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIArgs object will be
         returned.

         The returned CMPIArgs object shall be explicitly released by the MI
         using CMPIArgsFT.release().

         If not successful, NULL will be returned
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.

     @convfunction CMClone()
    */
    CMPIArgs* (*clone) (const CMPIArgs* args, CMPIStatus* rc);

    /**
     @brief Add or replace a method parameter in a CMPIArgs object.

     CMPIArgsFT.addArg() adds or replaces a method parameter in a CMPIArgs
     object.

     @param args Points to the CMPIArgs object for this function.
     @param name Name of the method parameter to be added or replaced.
     @param value Points to a CMPIValue structure containing the non-NULL
         value to be assigned to the method parameter, or NULL to specify that
         NULL is to be assigned
     @param type
     @parblock
         Type of the method parameter.

         All types of CIM values are supported.

         If the value of @p type is @ref CMPI_chars or @ref CMPI_charsA, the
         C-language string to which the @p chars member of @p value points is
         copied by this function and the original string memory may be freed by
         the MI right after this function returns.
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.
     @li `CMPI_RC_ERR_INVALID_DATA_TYPE` - Data type not valid.

     @convfunction CMAddArg()
    */
    CMPIStatus (*addArg) (const CMPIArgs* args, const char* name,
            const CMPIValue* value, const CMPIType type);

    /**
     @brief Get a method parameter in a CMPIArgs object by name.

     CMPIArgsFT.getArg() gets a method parameter in a CMPIArgs object, by name.

     @param args Points to the CMPIArgs object for this function.
     @param name Name of the method parameter.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified method
         parameter will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Method parameter not found.

     @convfunction CMGetArg()
    */
    CMPIData (*getArg) (const CMPIArgs* args, const char* name, CMPIStatus* rc);

    /**
     @brief Get a method parameter in a CMPIArgs object by index.

     CMPIArgsFT.getArgAt() gets a method parameter in a CMPIArgs object by
     index.

     @param args Points to the CMPIArgs object for this function.
     @param index Zero-based position of the method parameter in the internal
         data array.
     @param [out] name
     @parblock
         If not NULL, points to a CMPIString pointer that upon success will
         have been updated to point to a CMPIString object containing the
         method parameter name.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIArgs object which
         will be released along with that object, or a new object created by
         the MB which will be automatically released by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").
     @endparblock
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a CMPIData structure containing the specified method
         parameter will be returned.

         If not successful, CMPIData.state will be undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - Method parameter not found.

     @convfunction CMGetArgAt()
    */
    CMPIData (*getArgAt) (const CMPIArgs* args, CMPICount index,
        CMPIString** name, CMPIStatus* rc);

    /**
     @brief Get the number of method parameters in a CMPIArgs object.

     CMPIArgsFT.getArgCount() gets the number of method parameters in a
     CMPIArgs object.

     @param args Points to the CMPIArgs object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of method
         parameters in the CMPIArgs object will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p args handle is invalid.

     @convfunction CMGetArgCount()
    */
    CMPICount (*getArgCount) (const CMPIArgs* args, CMPIStatus* rc);

} CMPIArgsFT;

/**
 * @}
 * @addtogroup edt-datetime
 * @{
 */

/**
 * @brief CMPIDateTime encapsulated data type object.
 *
 * In order to be platform-independent, support for the CIM ``datetime`` data
 * type is encapsulated using CMPIDateTime. It supports both point-in-time and
 * interval values. For details on the CIM ``datetime`` data type, see
 * @ref ref-dmtf-dsp0004 "DSP0004".
 *
 * @bug In the CMPI Standard document, replace the introductory description
 *     for CMPIDateTime support (first paragraph) with the description from the
 *     header file.
 */
typedef struct _CMPIDateTime {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIDateTimeFT* ft;

} CMPIDateTime;

/**
 * @brief Function table of CMPIDateTime encapsulated data type object.
 */
typedef struct _CMPIDateTimeFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIDateTime object.

     CMPIDateTimeFT.release() releases a CMPIDateTime object. This indicates to
     the MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param dt Points to the CMPIDateTime object that is to be released.
         That object shall have been created using CMPIDateTimeFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p dt handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIDateTime* dt);

    /**
     @brief Create an independent copy of a CMPIDateTime object.

     CMPIDateTimeFT.clone() creates an independent copy of a CMPIDateTime
     object.

     @param dt Points to the CMPIDateTime object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIDateTime object will be
         returned.

         The returned CMPIDateTime object shall be explicitly released by the MI
         using CMPIDateTimeFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p dt handle is invalid.

     @convfunction CMClone()
    */
    CMPIDateTime* (*clone) (const CMPIDateTime* dt, CMPIStatus* rc);

    /**
     @brief Get the value of a CMPIDateTime object in binary format.

     CMPIDateTimeFT.getBinaryFormat() gets the value of a CMPIDateTime object
     as a 64-bit unsigned integer in microseconds starting since 00:00:00 GMT,
     January 1, 1970, or as an interval in microseconds, depending on what kind
     of value the CMPIDateTime object contains.

     @param dt Points to the CMPIDateTime object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIUint64 value containing the value of the
         CMPIDateTime object in binary format will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p dt handle is invalid.

     @convfunction CMGetBinaryFormat()
    */
    CMPIUint64 (*getBinaryFormat) (const CMPIDateTime* dt,
        CMPIStatus* rc);

    /**
     @brief Get the value of a CMPIDateTime object in the string
         format defined for the CIM ``datetime`` type.

     CMPIDateTimeFT.getStringFormat() gets the value of a CMPIDateTime object
     as a string in the format defined in @ref ref-dmtf-dsp0004 "DSP0004" for
     the CIM ``datetime`` type.

     @param dt Points to the CMPIDateTime object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object containing the value
         of a CMPIDateTime object in the format defined in
         @ref ref-dmtf-dsp0004 "DSP0004" for the CIM ``datetime`` type will be
         returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIDateTime object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p dt handle is invalid.

     @convfunction CMGetStringFormat()
    */
    CMPIString* (*getStringFormat) (const CMPIDateTime* dt, CMPIStatus* rc);

    /**
     @brief Test whether a CMPIDateTime object contains an interval value.

     CMPIDateTimeFT.isInterval() tests whether a CMPIDateTime object contains
     an interval value.

     @param dt Points to the CMPIDateTime object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the CMPIDateTime object contains an interval
         value;
         @li False indicates that this is not an interval.

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p dt handle is invalid.

     @convfunction CMGetStringFormat()
    */
    CMPIBoolean (*isInterval) (const CMPIDateTime* dt, CMPIStatus* rc);

} CMPIDateTimeFT;

/**
 * @}
 * @addtogroup edt-selectexp
 * @{
 */

/**
 * @brief CMPISelectExp encapsulated data type object.
 *
 * @capquerynorm This encapsulated data type is part of the Query Normalization
 *     capability.
 */
typedef struct _CMPISelectExp {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPISelectExpFT* ft;

} CMPISelectExp;

/**
 * @brief Function table of CMPISelectExp encapsulated data type object.
 */
typedef struct _CMPISelectExpFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPISelectExp object.

     CMPISelectExpFT.release() releases a CMPISelectExp object. This indicates
     to the MB that the object (including any objects it contains) will no
     longer be used by the MI. The MB may free (=reclaim) the memory associated
     with the object during the call to this function, or later during some
     garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param se Points to the CMPISelectExp object that is to be released.
         That object shall have been created using CMPISelectExpFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPISelectExp* se);

    /**
     @brief Create an independent copy of a CMPISelectExp object.

     CMPISelectExpFT.clone() creates an independent copy of a CMPISelectExp
     object.

     @param se Points to the CMPISelectExp object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPISelectExp object will be
         returned.

         The returned CMPISelectExp object shall be explicitly released by the
         MI using CMPISelectExpFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.

     @convfunction CMClone()
    */
    CMPISelectExp* (*clone) (const CMPISelectExp* se, CMPIStatus* rc);

    /**
     @brief Test whether an instance matches the select expression in a
         CMPISelectExp object.

     CMPISelectExpFT.evaluate() tests whether an instance matches the select
     expression in a CMPISelectExp object.

     @param se Points to the CMPISelectExp object for this function.
     @param inst Points to a CMPIInstance object containing the instance to be
         tested.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value will be returned, indicating
         the test result as follows:
         @li True indicates that the instance matches the select expression;
         @li False indicates that this is not the case.

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p inst is invalid.

     @convfunction CMEvaluateSelExp()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_INVALID_PARAMETER`.
    */
    CMPIBoolean (*evaluate) (const CMPISelectExp* se, const CMPIInstance* inst,
        CMPIStatus* rc);

    /**
     @brief Get the select expression in a CMPISelectExp object as a string.

     CMPISelectExpFT.getString() gets the select expression in a CMPISelectExp
     object as a string.

     @param se Points to the CMPISelectExp object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIString object cointaining the select
         expression in string format will be returned.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPISelectExp object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.

     @convfunction CMGetSelExpString()
    */
    CMPIString* (*getString) (const CMPISelectExp* se, CMPIStatus* rc);

    /**
     @brief Get the select expression in a CMPISelectExp object
         as a disjunction of conjunctions.

     CMPISelectExpFT.getDOC() gets the select expression as a disjunction of
     conjunctions. This function transforms the WHERE clause of the select
     expression into a canonical disjunction of onjunctions (DOC) form (OR'ing
     of AND'ed comparison expressions). This enables handling of the expression
     in the WHERE clause more easily than using a tree form.

     @param se Points to the CMPISelectExp object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPISelectCond object containing the
         transformed select expression will be returned.

         The returned CMPISelectCond object shall not be explicitly released by
         the MI, because it may be an internal object of the CMPISelectExp
         object which will be released along with that object, or a new object
         created by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.

     @convfunction CMGetDOC()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` is deprecated
         since CMPI 2.1. If the @ref CMPI_MB_QueryNormalization "Query
         Normalization" capability is not available, this function cannot be
         called by the MI because no instance of its encapsulated data type can
         exist.
    */
    CMPISelectCond* (*getDOC) (const CMPISelectExp* se, CMPIStatus* rc);

    /**
     @brief Get the select expression in a CMPISelectExp object as
         a conjunction of disjunctions.

     CMPISelectExpFT.getCOD() returns the select expression as conjunction of
     disjunctions.This function transforms the WHERE clause of the select
     expression into a canonical conjunction of disjunctions (COD) form
     (AND'ing of OR'ed comparison expressions). This enables handling of the
     expression in the WHERE clause more easily than using a tree form. See
     Subclause 4.6.3 of the @ref ref-cmpi-standard "CMPI Standard" for details.

     @param se Points to the CMPISelectExp object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPISelectCond object containing the
         transformed select expression will be returned.

         The returned CMPISelectCond object shall not be explicitly released by
         the MI, because it may be an internal object of the CMPISelectExp
         object which will be released along with that object, or a new object
         created by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.

     @convfunction CMGetCOD()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` is deprecated
         since CMPI 2.1. If the @ref CMPI_MB_QueryNormalization "Query
         Normalization" capability is not available, this function cannot be
         called by the MI because no instance of its encapsulated data type can
         exist.
    */
    CMPISelectCond* (*getCOD) (const CMPISelectExp* se, CMPIStatus* rc);

    /**
     @brief Test whether the properties returned by an accessor
        function match the select expression in a CMPISelectExp object.

     CMPISelectExpFT.evaluateUsingAccessor() tests whether the properties
     returned by an accessor function match the select expression in a
     CMPISelectExp object. This function is a variation of
     CMPISelectExpFT.evaluate(). It enables evaluation without the need to
     create a CMPIInstance object.

     @param se Points to the CMPISelectExp object for this function, containing
         the select expression.
     @param accessorFnc Points to a property value accessor function. The
         evaluation process will invoke this function to request a CMPIData
         structure for a particular property. For a definition of the signature
         of the accessor function, see @ref CMPIAccessor.
     @param parm A parameter that will be passed to the accessor function and
         can be used for providing context data to the accessor function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the properties returned by the accessor
             function match the select expression;
         @li False indicates that this is not the case.

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p se handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p accessorFnc is invalid.

     @convfunction CMEvaluateSelExpUsingAccessor()
    */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPISelectExp* se,
        const CMPIAccessor* accessor, void* parm, CMPIStatus* rc);

} CMPISelectExpFT;

/**
 * @}
 * @addtogroup edt-selectcond
 * @{
 */

/**
 * @brief CMPISelectCond encapsulated data type object.
 *
 * @capquerynorm This encapsulated data type is part of the Query Normalization
 *     capability.
 */
typedef struct _CMPISelectCond {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPISelectCondFT* ft;

} CMPISelectCond;

/**
 * @brief Function table of CMPISelectCond encapsulated data type object.
 */
typedef struct _CMPISelectCondFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPISelectCond object.

     CMPISelectCondFT.release() releases a CMPISelectCond object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param sc Points to the CMPISelectCond object that is to be released.
         That object shall have been created using CMPISelectCondFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMRelease()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIStatus (*release) (CMPISelectCond* sc);

    /**
     @brief Create an independent copy of a CMPISelectCond object.

     CMPISelectCondFT.clone() creates an independent copy of a CMPISelectCond
     object.

     @param sc Points to the CMPISelectCond object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPISelectCond object will be
         returned.

         The returned CMPISelectCond object shall be explicitly released by the
         MI using CMPISelectCondFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMClone()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPISelectCond* (*clone) (const CMPISelectCond* sc, CMPIStatus* rc);

    /**
     @brief Get the number and type of subconditions in a CMPISelectCond object.

     CMPISelectCondFT.getCountAndType() gets the number and type of the
     subconditions in a CMPISelectCond object.

     @param sc Points to the CMPISelectCond object for this function.
     @param [out] type If not NULL, points to an integer that upon success
         is updated with the subcondition type. A value of 0 indicates a
         DOC type, and a value of 1 indicates a COD type. If @p type is NULL,
         no type information is returned.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of
         subconditions will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMGetSubCondCountAndType()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPICount (*getCountAndType) (const CMPISelectCond* sc, int* type,
            CMPIStatus* rc);

    /**
     @brief Get a subcondition in a CMPISelectCond object by index.

     CMPISelectCondFT.getSubCondAt() gets the subcondition in a
     CMPISelectCond object, by its index in the internal data array.

     @param sc Points to the CMPISelectCond object for this function.
     @param index Zero-based position of the subcondition in the internal data
         array.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the specified CMPISubCond object will be
         returned.

         The returned CMPISubCond object shall not be explicitly released
         by the MI, because it may be an internal object of the CMPISelectCond
         object which will be released along with that object, or a new object
         created by the MB which will be released automatically by the MB
         (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
         @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - @p index value out of bounds.

     @convfunction CMGetSubCondAt()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPISubCond* (*getSubCondAt) (const CMPISelectCond* sc, CMPICount index,
        CMPIStatus* rc);

} CMPISelectCondFT;

/**
 * @}
 * @addtogroup edt-subcond
 * @{
 */

/**
 * @brief CMPISubCond encapsulated data type object.
 *
 * @capquerynorm This encapsulated data type is part of the Query Normalization
 *     capability.
 */
typedef struct _CMPISubCond {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPISubCondFT* ft;

} CMPISubCond;

/**
 * @brief Function table of CMPISubCond encapsulated data type object.
 */
typedef struct _CMPISubCondFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPISubCond object.

     CMPISubCondFT.release() releases a CMPISubCond object. This indicates to
     the MB that the object (including any objects it contains) will no longer
     be used by the MI. The MB may free (=reclaim) the memory associated with
     the object during the call to this function, or later during some garbage
     collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param sc Points to the CMPISubCond object that is to be released.
         That object shall have been created using CMPISubCondFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMRelease()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIStatus (*release) (CMPISubCond* sc);

    /**
     @brief Create an independent copy of a CMPISubCond object.

     CMPISubCondFT.clone() creates an independent copy of a CMPISubCond object.

     @param sc Points to the CMPISubCond object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPISubCond object will be
         returned.

         The returned CMPISubCond object shall be explicitly released by the MI
         using CMPISubCondFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMClone()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
     */
    CMPISubCond* (*clone) (const CMPISubCond* sc, CMPIStatus* rc);

    /**
     @brief Get the number of predicates in a CMPISubCond object.

     CMPISubCondFT.getCount() gets the number of predicates in a CMPISubCond
     object.

     @param sc Points to the CMPISubCond object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPICount value indicating the number of
         predicates in the CMPISubCond object will be returned.

         If not successful, 0 will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.

     @convfunction CMGetPredicateCount()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
     @bug In the CMPI Standard document, change "CMPISubCondFT object" to
         "CMPISubCond object" in the description of the sc argument.
    */
    CMPICount (*getCount) (const CMPISubCond* sc, CMPIStatus* rc);

    /**
     @brief Get a predicate in a CMPISubCond object by index.

     CMPISubCondFT.getPredicateAt() gets a predicate in a CMPISubCond object,
     by its index in the internal data array.

     @param sc Points to the CMPISubCond object for this function.
     @param index Zero-based position of the predicate in the internal data
         array.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIPredicate object containing the
         specified predicate will be returned.

         The returned CMPIPredicate object shall not be explicitly released by
         the MI, because it may be an internal object of the CMPISubCond object
         which will be released along with that object, or a new object created
         by the MB which will be released automatically by the MB (see
         Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - @p index value out of bounds.

     @convfunction CMGetPredicateAt()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
     @bug In the CMPI Standard document, change "index" to "position" in the
         description of the index argument.
    */
    CMPIPredicate* (*getPredicateAt) (const CMPISubCond* sc, CMPICount index,
        CMPIStatus* rc);

    /**
     @brief Get a predicate in a CMPISubCond object by name.

     CMPISubCondFT.getPredicate() gets a predicate in a CMPISubCond object by
     name.

     @param sc Points to the CMPISubCond object for this function.
     @param name Predicate name. The name is the left-hand side of the
         predicate.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to a CMPIPredicate object containing the
         specified predicate will be returned.

         The returned CMPIPredicate object shall not be explicitly released
         by the MI, because it may be an internal object of the CMPISubCond
         object which will be released along with that object, or a new object
         created by the MB which will be released automatically by the MB
         (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p sc handle is invalid.
     @li `CMPI_RC_ERR_NO_SUCH_PROPERTY` - @p index value out of bounds.

     @convfunction CMGetPredicate()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_NO_SUCH_PROPERTY`.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIPredicate* (*getPredicate) (const CMPISubCond* sc, const char* name,
        CMPIStatus* rc);

} CMPISubCondFT;

/**
 * @}
 * @addtogroup edt-predicate
 * @{
 */

/**
 * @brief CMPIPredicate encapsulated data type object.
 *
 * @capquerynorm This encapsulated data type is part of the Query Normalization
 *     capability.
 */
typedef struct _CMPIPredicate {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIPredicateFT* ft;

} CMPIPredicate;

/**
 * @brief Function table of CMPIPredicate encapsulated data type object.
 */
typedef struct _CMPIPredicateFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPPredicate object.

     CMPIPredicateFT.release() releases a CMPIPredicate object. This indicates
     to the MB that the object (including any objects it contains) will no
     longer be used by the MI. The MB may free (=reclaim) the memory associated
     with the object during the call to this function, or later during some
     garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param pr Points to the CMPIPredicate object that is to be released.
         That object shall have been created using CMPIPredicateFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p pr handle is invalid.

     @convfunction CMRelease()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIStatus (*release) (CMPIPredicate* pr);

    /**
     @brief Create an independent copy of a CMPIPredicate object.

     CMPIPredicateFT.clone() creates an independent copy of a CMPIPredicate
     object.

     @param pr Points to the CMPIPredicate object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIPredicate object will be
         returned.

         The returned CMPIPredicate object shall be explicitly released by the
         MI using CMPIPredicateFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p pr handle is invalid.

     @convfunction CMClone()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIPredicate* (*clone) (const CMPIPredicate* pr, CMPIStatus* rc);

    /**
     @brief Get the predicate components of a CMPIPredicate object.

     CMPIPredicateFT.getData() gets the predicate components of a CMPIPredicate
     object.

     The CMPIString objects returned by @p lhs and @p rhs shall not be
     explicitly released by the MI, because they may be internal objects of the
     CMPIContext object which will be released along with that object, or new
     objects created by the MB which will be automatically released by the MB
     (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param pr Points to the CMPIPredicate object for this function.
     @param [out] type If not NULL, points to a @ref CMPIType structure that
         upon success will have been updated with the data type of the
         predicate.
     @param [out] prop If not NULL, points to a @ref CMPIPredOp object that upon
         success will have been updated with the predicate operation.
     @param [out] lhs If not NULL, points to a pointer to a CMPIString object
         that upon success will have been updated with the address of a
         CMPIString object representing the left-hand side of the predicate.
     @param [out] rhs If not NULL, points to a pointer to a CMPIString object
         that upon success will have been updated with the address of a
         CMPIString object representing the right-hand side of the predicate.
     @return @parblock
         A CMPIStatus structure indicating the function return status will be
         returned.

         If not successful, @p lhs and @p rhs will be set to NULL, and the
         state of @p type and @p prop is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p pr handle is invalid.

     @convfunction CMGetPredicateData()
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. If the
         @ref CMPI_MB_QueryNormalization "Query Normalization" capability
         is not available, this function cannot be called by the MI because no
         instance of its encapsulated data type can exist.
    */
    CMPIStatus (*getData) (const CMPIPredicate* pr, CMPIType* type,
            CMPIPredOp* prop, CMPIString** lhs, CMPIString** rhs);

    /**
     @brief Test whether the properties returned by an accessor
         function match the predicate in a CMPIPredicate object.

     CMPIPredicateFT.evaluateUsingAccessor() tests whether the properties
     returned by an accessor function match the predicate in a CMPIPredicate
     object.

     The CMPIString objects returned by @p lhs and @p rhs shall not be
     explicitly released by the MI, because they may be internal objects of the
     CMPIContext object which will be released along with that object, or new
     objects created by the MB which will be automatically released by the MB
     (see Subclause 4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

     @param pr Points to the CMPIPredicate object for this function.
     @param accessorFnc Points to a property value accessor function. The
         evaluation process will invoke this function to request a CMPIData
         structure for a particular property. For a definition of the signature
         of the accessor function, see @ref CMPIAccessor.
     @param parm A parameter that will be passed to the accessor function and
         can be used for providing context data to the accessor function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the properties returned by the accessor
             function match the predicate;
         @li False indicates that this is not the case.

         If not successful, false will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p pr handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p accessorFnc is invalid.

     @convfunction CMEvaluatePredicateUsingAccessor()
     @changed210 In CMPI 2.1, added the return code `CMPI_RC_ERR_INVALID_PARAMETER`.
    */
    CMPIBoolean (*evaluateUsingAccessor) (const CMPIPredicate* pr,
        const CMPIAccessor* accessorFnc, void* parm, CMPIStatus* rc);

} CMPIPredicateFT;

/**
 * @}
 * @addtogroup edt-error
 * @{
 */

#ifdef CMPI_VER_200

/**
 * @brief CMPIError encapsulated data type object.
 *
 * CMPIError encapsulates extended errors as described in
 * @ref ref-dmtf-dsp0223 "DSP0223". MIs can supply extended errors in order to
 * provide more detailed error information, compared to CMPI status codes. MBs
 * will return such extended error information back to WBEM clients, in WBEM
 * protocols that support the representation of extended errors.
 *
 * @caperrors This encapsulated data type is part of the Extended Errors
 *     capability.
 *
 * @added200 Added in CMPI 2.0.
 * @required210 Required to be supported since CMPI 2.1.
 *
 * @bug In the CMPI Standard document, add this description to the
 *     introductory description of the CMPIError support.
 */
typedef struct _CMPIError {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIErrorFT* ft;

} CMPIError;

/**
 * @brief Function table of CMPIError encapsulated data type object.
 *
 * @added200 Added in CMPI 2.0.
 * @required210 Required to be supported since CMPI 2.1.
 */
typedef struct _CMPIErrorFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIError object.

     CMPIErrorFT.release() releases a CMPIError object.

     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim) the
     memory associated with the object during the call to this function, or
     later during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param er Points to the CMPIError object that is to be released.
         That object shall have been created using CMPIErrorFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - @p er is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMRelease()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*release) (CMPIError* er);

    /**
     @brief Create an independent copy of a CMPIError object.

     CMPIErrorFT.clone() creates an independent copy of a CMPIError object.

     @param er Points to the CMPIError object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIError object will be
         returned.

         The returned CMPIError object shall be explicitly released by the MI
         using CMPIErrorFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMClone()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIError* (*clone) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `ErrorType` attribute of a CMPIError object.

     CMPIErrorFT.getErrorType() gets the value of the `ErrorType` attribute of
     a CMPIError object.

     For a description of the `ErrorType` attribute, see @ref CMPIErrorType and
     the description of the `ErrorType` property in the `CIM_Error` class in
     the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIErrorType enumeration value will be returned,
         indicating the value of the `ErrorType` attribute of the CMPIError
         object.

         If not successful, the returned value is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetErrorType()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIErrorType (*getErrorType) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `OtherErrorType` attribute of a CMPIError object.

     CMPIErrorFT.getOtherErrorType() gets the value of the `OtherErrorType`
     attribute of a CMPIError object.

     For a description of the `OtherErrorType` attribute, see the description of
     the `OtherErrorType` property in the `CIM_Error` class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `OtherErrorType` attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the `OtherErrorType` attribute of the
         CMPIError object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether the
         function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetOtherErrorType()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, update the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getOtherErrorType) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `OwningEntity` attribute of a CMPIError object.

     CMPIErrorFT.getOwningEntity() gets the value of the `OwningEntity`
     attribute of a CMPIError object.

     For a description of the `OwningEntity` attribute, see the description of
     the `OwningEntity` property in the `CIM_Error` class in the CIM Schema,
     and the description of the @p owner argument of
     CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `OwningEntity` attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIString object will be
         returned, indicating the value of the `OwningEntity` attribute of the
         CMPIError object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetOwningEntity()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, update the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getOwningEntity) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `MessageID` attribute of a CMPIError object.

     CMPIErrorFT.getMessageID() gets the value of the `MessageID` attribute of
     a CMPIError object.

     For a description of the `MessageID` attribute, see the description of the
     `MessageID` property in the `CIM_Error` class in the CIM Schema, and the
     description of the @p msgID argument of CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `MessageID` attribute of the CMPIError object is
         non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the `MessageID` attribute of the CMPIError
         object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether the
         function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetMessageID()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, update the paragraph defining the
         attribute.
    */
    CMPIString* (*getMessageID) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `Message` attribute of a CMPIError object.

     CMPIErrorFT.getMessage() gets the value of the `Message` attribute of a
     CMPIError object.

     For a description of the `Message` attribute, see the description of the
     `Message` property in the `CIM_Error` class in the CIM Schema, and the
     description of the @p msg argument of CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `Message` attribute of the CMPIError object is
         non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the `Message` attribute of the CMPIError
         object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetErrorMessage()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph about releasing the
         returned object
    */
    CMPIString* (*getMessage) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `PerceivedSeverity` attribute of a CMPIError object

     CMPIErrorFT.getPerceivedSeverity() gets the value of the
     `PerceivedSeverity` attribute of a CMPIError object.

     For a description of the `PerceivedSeverity` attribute, see
     @ref CMPIErrorSeverity, the description of the `PerceivedSeverity`
     property in the `CIM_Error` class in the CIM Schema, and the description
     of the @p sev argument of CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIErrorSeverity enumeration
         value will be returned, indicating the value of the `PerceivedSeverity`
         attribute of the CMPIError object.

         If not successful, the returned value is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetPerceivedSeverity()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, update the paragraph defining the
         attribute.
    */
    CMPIErrorSeverity (*getPerceivedSeverity) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `ProbableCause` attribute of a CMPIError object.

     CMPIErrorFT.getProbableCause() gets the value of the `ProbableCause`
     attribute of a CMPIError object.

     For a description of the `ProbableCause` attribute, see @ref
     CMPIErrorProbableCause, the description of the `ProbableCause` property in
     the `CIM_Error` class in the CIM Schema, and the description of the @p pc
     argument of CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIErrorProbableCause enumeration value will be
         returned, indicating the value of the @p ProbableCause attribute of
         the CMPIError object.

         If not successful, the returned value is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetProbableCause()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, update the paragraph defining the
         attribute.
    */
    CMPIErrorProbableCause (*getProbableCause) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `ProbableCauseDescription` attribute of a CMPIError object.

     CMPIErrorFT.getProbableCauseDescription() gets the value of the
     `ProbableCauseDescription` attribute of a CMPIError object.

     For a description of the `ProbableCauseDescription` attribute, see the
     description of the `ProbableCauseDescription` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `ProbableCauseDescription` attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIString object will be
         returned, indicating the value of the `ProbableCauseDescription`
         attribute of the CMPIError object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetProbableCauseDescription()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getProbableCauseDescription) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `RecommendedActions` array attribute of a CMPIError object.

     CMPIErrorFT.getRecommendedActions() gets the value of the
     `RecommendedActions` array attribute of a CMPIError object.

     For a description of the `RecommendedActions` attribute, see the
     description of the `RecommendedActions` property in the `CIM_Error` class
     in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `RecommendedActions` array attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIArray object will be
         returned, containing CMPIString elements that represent the array
         elements of the `RecommendedActions` array attribute in the CMPIError
         object.

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetRecommendedActions()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute.
    */
    CMPIArray* (*getRecommendedActions) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `ErrorSource` attribute of a CMPIError object.

     CMPIErrorFT.getErrorSource() gets the value of the `ErrorSource` attribute
     of a CMPIError object.

     For a description of the `ErrorSource` attribute, see the description of
     the `ErrorSource` property in the `CIM_Error` class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `ErrorSource` attribute of the CMPIError object
         is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the `ErrorSource` attribute of the CMPIError
         object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetErrorSource()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getErrorSource) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `ErrorSourceFormat` attribute of a CMPIError object.

     CMPIErrorFT.getErrorSourceFormat() gets the value of the
     `ErrorSourceFormat` attribute of a CMPIError object.

     For a description of the `ErrorSourceFormat` attribute, see the
     description of the `ErrorSourceFormat` property in the `CIM_Error` class
     in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIErrorSrcFormat enumeration will be returned,
         indicating the value of the `ErrorSourceFormat` attribute of the
         CMPIError object.

         If not successful, the returned value is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetErrorSourceFormat()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute.
    */
    CMPIErrorSrcFormat (*getErrorSourceFormat) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `OtherErrorSourceFormat` attribute of a CMPIError object.

     CMPIErrorFT.getOtherErrorSourceFormat() gets the value of the
     `OtherErrorSourceFormat` attribute of a CMPIError object.

     For a description of the `OtherErrorSourceFormat` attribute, see the
     description of the `OtherErrorSourceFormat` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `OtherErrorSource` attribute of the CMPIError
         object is non-NULL, a pointer to a CMPIString object will be returned,
         indicating the value of the `OtherErrorSourceFormat` attribute of the
         CMPIError object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether
         the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetOtherErrorSourceFormat()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getOtherErrorSourceFormat) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `CIMStatusCode` attribute of a CMPIError object.

     CMPIErrorFT.getCIMStatusCode() gets the value of the `CIMStatusCode`
     attribute of a CMPIError object.

     For a description of the `CIMStatusCode` attribute, see the description of
     the `CIMStatusCode` property in the `CIM_Error` class in the CIM Schema,
     and the description of the @p cimStatusCode argument of
     CMPIBrokerEncFT.newCMPIError().

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIrc value will be returned, indicating the
         value of the `CIMStatusCode` attribute of the CMPIError object. Please
         note that not all status codes apply to all situations.

         It is up to the MI to ensure the correct status code is set.

         If not successful, the returned value is undefined.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetCIMStatusCode()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute.
    */
    CMPIrc (*getCIMStatusCode) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Get the `CIMStatusCodeDescription` attribute of a CMPIError object.

     CMPIErrorFT.getCIMStatusCodeDescription() gets the value of the
     `CIMStatusCodeDescription` attribute of a CMPIError object.

     For a description of the `CIMStatusCodeDescription` attribute, see the
     description of the `CIMStatusCodeDescription` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `CIMStatusCodeDescription` attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIString object will be
         returned, indicating the value of the `CIMStatusCodeDescription`
         attribute of the CMPIError object.

         The returned CMPIString object shall not be explicitly released by the
         MI, because it may be an internal object of the CMPIError object which
         will be released along with that object, or a new object created by
         the MB which will be released automatically by the MB (see Subclause
         4.1.7 of the @ref ref-cmpi-standard "CMPI Standard").

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see
         whether the function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetCIMStatusCodeDescription()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIString* (*getCIMStatusCodeDescription) (const CMPIError* er,
        CMPIStatus* rc);

    /**
     @brief Get the `MessageArguments` array attribute of a CMPIError object.

     CMPIErrorFT.getMessageArguments() gets the value of the `MessageArguments`
     array attribute of a CMPIError object.

     For a description of the `MessageArguments` attribute, see the description
     of the `MessageArguments` property in the `CIM_Error` class in the CIM
     Schema.

     @param er Points to the CMPIError object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful and the `MessageArguments` array attribute of the
         CMPIError object is non-NULL, a pointer to a CMPIArray object will be
         returned, containing CMPIString objects that represent the array
         elements of the `MessageArguments` array attribute of the CMPIError
         object.

         Otherwise, NULL will be returned.

         The caller must inspect the function return status to see whether the
         function failed.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMGetMessageArguments()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
     @bug In the CMPI Standard document, add the paragraph defining the
         attribute, and add the paragraph about releasing the returned object.
    */
    CMPIArray* (*getMessageArguments) (const CMPIError* er, CMPIStatus* rc);

    /**
     @brief Set the `ErrorType` attribute of a CMPIError object.

     CMPIErrorFT.setErrorType() sets the value of the `ErrorType` attribute of
     a CMPIError object.

     For a description of the `ErrorType` attribute, see @ref CMPIErrorType and
     the description of the `ErrorType` property in the `CIM_Error` class in
     the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param et A @ref CMPIErrorType enumeration value specifying the new value
         for the `ErrorType` attribute. If the error message in the CMPIError
         object is defined in a DMTF message registry, @p et shall reflect the
         content of the ERROR_TYPE element defined for the message in the
         registry.
     @return CMPIStatus structure containing the function return status

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetErrorType()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setErrorType) (const CMPIError* er, const CMPIErrorType et);

    /**
     @brief Set the `OtherErrorType` attribute of a CMPIError object.

     CMPIErrorFT.setOtherErrorType() sets the value of the `OtherErrorType`
     attribute of a CMPIError object.

     For a description of the `OtherErrorType` attribute, see the description of
     the `OtherErrorType` property in the `CIM_Error` class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param ot New non-NULL value for the `OtherErrorType` attribute, or is
         NULL specifying that the attribute will be set to NULL. If the error
         message is defined in a DMTF message registry, the string value of
         @p ot shall be the content of the OTHER_ERROR_TYPE element defined for
         the message in the registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetOtherErrorType()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setOtherErrorType) (const CMPIError* er, const char* ot);

    /**
     @brief Set the `ProbableCauseDescription` attribute of a CMPIError object.

     CMPIErrorFT.setProbableCauseDescription() sets the value of the
     `ProbableCauseDescription` attribute of a CMPIError object.

     For a description of the `ProbableCauseDescription` attribute, see the
     description of the `ProbableCauseDescription` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param pcd New non-NULL value for the `ProbableCauseDescription`
         attribute, or is NULL specifying that the attribute will be set to
         NULL. If the error message is defined in a DMTF message registry, note
         that the string value of @p pcd is not defined in the message in the
         registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetProbableCauseDescription()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setProbableCauseDescription) (const CMPIError* er,
        const char* pcd);

    /**
     @brief Set the `RecommendedActions` array attribute of a CMPIError object.

     CMPIErrorFT.setRecommendedActions() sets the value of the
     `RecommendedActions` array attribute of a CMPIError object.

     For a description of the `RecommendedActions` attribute, see the
     description of the `RecommendedActions` property in the `CIM_Error` class
     in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param ra Points to a CMPIArray object specifying the new array value for
         the `RecommendedActions` array attribute. The CMPIArray object
         contains CMPIString objects or NULL values as array elements. @p ra
         may be NULL, specifying that the `RecommendedActions` array attribute
         will be set to NULL. If the error message is defined in a DMTF message
         registry, @p ra shall reflect the values defined in the
         RECOMMENDED_ACTION elements defined for the message in the registry,
         in the order defined there.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetRecommendedActions()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setRecommendedActions) (const CMPIError* er,
        const CMPIArray* ra);

    /**
     @brief Set the `ErrorSource` attribute of a CMPIError object.

     CMPIErrorFT.setErrorSource() sets the value of the `ErrorSource` attribute
     of a CMPIError object.

     For a description of the `ErrorSource` attribute, see the description of
     the `ErrorSource` property in the `CIM_Error` class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param es New non-NULL value for the `ErrorSource` attribute, or is NULL
         specifying that the attribute will be set to NULL. If the error
         message is defined in a DMTF message registry, the string value of
         @p es shall be the content of the ERROR_SOURCE element defined for the
         message in the registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetErrorSource()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setErrorSource) (const CMPIError* er, const char* es);

    /**
     @brief Set the `ErrorSourceFormat` attribute of a CMPIError object.

     CMPIErrorFT.setErrorSourceFormat() sets the value of the
     `ErrorSourceFormat` attribute of a CMPIError object.

     For a description of the `ErrorSourceFormat` attribute, see the
     description of the `ErrorSourceFormat` property in the `CIM_Error` class
     in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param esf A @ref CMPIErrorSrcFormat enumeration value specifying the new
         value for the `ErrorSourceFormat` attribute. If the error message is
         defined in a DMTF message registry, the string value of @p esf shall
         be the content of the ERROR_SOURCE_FORMAT element defined for the
         message in the registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetErrorSourceFormat()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setErrorSourceFormat) (const CMPIError* er,
        const CMPIErrorSrcFormat esf);

    /**
     @brief Set the `OtherErrorSourceFormat` attribute of a CMPIError object.

     CMPIErrorFT.setOtherErrorSourceFormat() sets the value of the
     `OtherErrorSourceFormat` attribute of a CMPIError object.

     For a description of the `OtherErrorSourceFormat` attribute, see the
     description of the `OtherErrorSourceFormat` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param oef New non-NULL value for the `OtherErrorSourceFormat` attribute,
         or NULL specifying that the attribute will be set to NULL. If the
         error message is defined in a DMTF message registry, the string value
         of @p oef shall be the content of the OTHER_ERROR_SOURCE_FORMAT
         element defined for the message in the registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetOtherErrorSourceFormat()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setOtherErrorSourceFormat) (const CMPIError* er,
        const char* oef);

    /**
     @brief Set the `CIMStatusCodeDescription` attribute of a CMPIError object.

     CMPIErrorFT.setCIMStatusCodeDescription() sets the value of the
     `CIMStatusCodeDescription` attribute of a CMPIError object.

     For a description of the `CIMStatusCodeDescription` attribute, see the
     description of the `CIMStatusCodeDescription` property in the `CIM_Error`
     class in the CIM Schema.

     @param er Points to the CMPIError object for this function.
     @param scd New non-NULL value for the `CIMStatusCodeDescription`
         attribute, or NULL specifying that the attribute will be set to NULL.
         If the error message is defined in a DMTF message registry, note that
         the string value of @p scd is not defined in the message in the
         registry.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetCIMStatusCodeDescription()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setCIMStatusCodeDescription) (const CMPIError* er,
        const char* scd);

    /**
     @brief Set the `MessageArguments` array attribute of a CMPIError object.

     CMPIErrorFT.setMessageArguments() sets the value of the `MessageArguments`
     array attribute of a CMPIError object.

     For a description of the `MessageArguments` attribute, see the description
     of the `MessageArguments` property in the `CIM_Error` class in the CIM
     Schema.

     @param er Points to the CMPIError object for this function.
     @param values CMPIArray object specifying the new array value for the
         `MessageArguments` array attribute. The CMPIArray object contains
         CMPIString objects or NULL values as array elements. @p values may be
         NULL, specifying that the `MessageArguments` array attribute will be
         set to NULL. If the error message is defined in a DMTF message
         registry, @p values shall reflect the values defined in the
         DYNAMIC_ELEMENT elements defined for the message in the registry, in
         the order defined there.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by the MB.
         (**Deprecated**)
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - One of the arguments is invalid.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMSetMessageArguments()
     @required210 Support for this function is required since CMPI 2.1.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function
         is deprecated since CMPI 2.1. It will not be returned because the
         @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
         will be available.
    */
    CMPIStatus (*setMessageArguments) (const CMPIError* er,
        const CMPIArray* values);

} CMPIErrorFT;

#endif /*CMPI_VER_200*/

/**
 * @}
 * @addtogroup edt-propertylist
 * @{
 */

#ifdef CMPI_VER_210

/**
 * @brief CMPIPropertyList encapsulated data type object.
 *
 * CMPIPropertyList provides MIs with an efficient way to implement property
 * filtering. For more details, see Subclause 8.15 of the
 * @ref ref-cmpi-standard "CMPI Standard".
 *
 * @added210 Added in CMPI 2.1.
 */
typedef struct _CMPIPropertyList {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIPropertyListFT* ft;

} CMPIPropertyList;

/**
 * @brief Function table of CMPIPropertyList encapsulated data type object.
 *
 * @added210 Added in CMPI 2.1.
 */
typedef struct _CMPIPropertyListFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIPropertyList object.

     CMPIPropertyListFT.release() releases a CMPIPropertyList object. This
     indicates to the MB that the object (including any objects it contains)
     will no longer be used by the MI. The MB may free (=reclaim) the memory
     associated with the object during the call to this function, or later
     during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param plist Points to the CMPIPropertyList object that is to be released.
         That object shall have been created using CMPIPropertyListFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p plist handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIPropertyList* plist);

    /**
     @brief Create an independent copy of a CMPIPropertyList object.

     CMPIPropertyListFT.clone() creates an independent copy of a
     CMPIPropertyList object.

     @param plist Points to the CMPIPropertyList object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return @parblock
         If successful, a pointer to the copied CMPIPropertyList object will be
         returned.

         The returned CMPIPropertyList object shall be explicitly released by
         the MI using CMPIPropertyListFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p plist handle is invalid.

     @convfunction CMClone()
    */
    CMPIPropertyList* (*clone) (const CMPIPropertyList* plist, CMPIStatus* rc);

    /**
     @brief Test whether a property is in the property list
         represented by a CMPIPropertyList object.

     CMPIPropertyListFT.isPropertyInList() tests whether a property is in
     the property list represented by a CMPIPropertyList object.

     The MB's implementation of this function should be efficient. However,
     it is recommended that MIs when returning many instances invoke this
     function only once for each property, and cache the result.

     @param plist Points to the CMPIPropertyList object for this function.
     @param pname Name of the property to be tested.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return has been updated with the function return status
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned, as follows:
         @li True indicates that the property is in the property list;
         @li False indicates that this is not the case.

         If not successful, False will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p plist handle is invalid.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - The @p pname value is invalid.

     @todo KS: Add macro for this
    */
    CMPIBoolean (*isPropertyInList) (const CMPIPropertyList* plist,
        const char* pname, CMPIStatus* rc);

    /**
     @brief Return the property list represented by a CMPIPropertyList object
     as an array of strings.

     CMPIPropertyListFT.getProperties() returns the property list represented
     by a CMPIPropertyList object as a NULL-terminated array of pointers to
     strings.

     @param plist Points to the CMPIPropertyList object for this function.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the first entry of a NULL-terminated array
         of pointers to strings that represent the property names in the
         property list represented by the CMPIPropertyList object will be
         returned.

         The entries in that array may be in any order and in any lexical case
         (possibly different than originally specified in
         CMPIBrokerEncFT.newPropertyList()).

         The returned array shall not be explicitly released by the MI, because
         it may point to an internal data area in the CMPIPropertyList object
         which will be released along with that object, or it may point to a
         new array created by the MB which will be released automatically by
         the MB (see Subclause 4.1.7 of the
         @ref ref-cmpi-standard "CMPI Standard").

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p plist handle is invalid.

     @todo KS: Add macro for this
    */
    const char** (*getProperties) (const CMPIPropertyList* plist,
        CMPIStatus* rc);

} CMPIPropertyListFT;

/**
 * @}
 * @addtogroup edt-enumerationfilter
 * @{
 */

/**
 * @brief CMPIEnumerationFilter encapsulated data type object.
 *
 * CMPIEnumerationFilter provides MIs with an efficient way to implement
 * filtering of instances in the results of filtered operations. For more
 * details, see Subclause 8.16 of the @ref ref-cmpi-standard "CMPI Standard".
 *
 * @added210 Added in CMPI 2.1.
 */
typedef struct _CMPIEnumerationFilter {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this object.
     */
    const CMPIEnumerationFilterFT* ft;

} CMPIEnumerationFilter;

/**
 * @brief Function table of CMPIEnumerationFilter encapsulated data type object.
 *
 * @added210 Added in CMPI 2.1.
 */
typedef struct _CMPIEnumerationFilterFT {

    /**
     * @brief CMPI version supported by the MB for this function table.
     *
     * Any earlier CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     @brief Release a CMPIResult object.

     CMPIEnumerationFilterFT.release() releases a CMPIEnumerationFilter object.
     This indicates to the MB that the object (including any objects it
     contains) will no longer be used by the MI. The MB may free (=reclaim) the
     memory associated with the object during the call to this function, or
     later during some garbage collection cycle (see Subclause 4.1.7 of the
     @ref ref-cmpi-standard "CMPI Standard").

     @param ef Points to the CMPIEnumerationFilter object that is to be
         released. That object shall have been created using
         CMPIEnumerationFilterFT.clone().
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ef handle is invalid.

     @convfunction CMRelease()
    */
    CMPIStatus (*release) (CMPIEnumerationFilter* ef);

    /**
     @brief Create an independent copy of a CMPIEnumerationFilter object.

     CMPIEnumerationFilterFT.clone() creates an independent copy of a
     CMPIEnumerationFilter object.

     @param ef Points to the CMPIEnumerationFilter object that is to be copied.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a pointer to the copied CMPIEnumerationFilter object
         will be returned.

         The returned CMPIEnumerationFilter object shall be explicitly released
         by the MI using CMPIEnumerationFilterFT.release().

         If not successful, NULL will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ef handle is invalid.

     @convfunction CMClone()
    */
    CMPIEnumerationFilter* (*clone) (const CMPIEnumerationFilter* ef,
        CMPIStatus* rc);

    /**
     @brief Test whether an instance matches the filter represented by a
         CMPIEnumerationFilter object.

     CMPIEnumerationFilterFT.match() tests whether an instance matches the
     filter represented by a CMPIEnumerationFilter object. The filter matches
     the instance if the conditions defined in the filter are met by the
     properties of the instance.

     The MB's implementation of this function should be efficient.

     @param ef Points to the CMPIEnumerationFilter object for this function.
     @param inst Points to the CMPIInstance object to be tested against the
         filter.
     @param [out] rc If not NULL, points to a CMPIStatus structure that upon
         return will have been updated with the function return status.
     @return @parblock
         If successful, a @ref CMPIBoolean value indicating the test result
         will be returned as follows:
         @li True indicates that the instance matches the filter;
         @li False indicates that this is not the case.

         If not successful, False will be returned.
     @endparblock

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_INVALID_HANDLE` - The @p ef handle is invalid.
     @li `CMPI_RC_ERR_INVALID_QUERY` - The @p filterQuery is not a
         valid query in the specified filter query language
     @li `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` - A feature of
         the query language is not supported.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @todo KS: Create macro for this
     @bug In the CMPI Standard document, add the definition of when a filter
         matches.
    */
    CMPIBoolean (*match) (const CMPIEnumerationFilter* ef,
        const CMPIInstance* inst, CMPIStatus* rc);

} CMPIEnumerationFilterFT;

#endif /*CMPI_VER_210*/

/**
 * @}
 * @addtogroup instance-mi
 * @{
 */

/**
 * @brief CMPIInstanceMI object.
 *
 * This object is provided by an instance MI through
 * @ref mi-factory "MI factory functions", in order to make its MI functions
 * available to the MB.
 */
typedef struct _CMPIInstanceMI {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this MI
     *     object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this MI object.
     */
    const CMPIInstanceMIFT* ft;

} CMPIInstanceMI;

/**
 * @brief Function table of CMPIInstanceMI object.
 */
typedef struct _CMPIInstanceMIFT {

    /**
     * @brief CMPI version supported by the MI for this function table.
     *
     * Any later CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * @brief Informal MI-specific version number for this MI.
     */
    int miVersion;

    /**
     * @brief Informal MI-specific name for this MI.
     */
    const char* miName;

    /**
     @brief Perform cleanup for an Instance MI.

     CMPIInstanceMIFT.cleanup() shall perform any necessary cleanup for the
     Instance MI identified by @p mi, unless the MI postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. This function will be called once for a specific MI (unless
     the MI postpones the cleanup), even if that MI services more than one
     namespace. After this function returns, the MB may unload the load library
     this MI is part of, unless the MI postpones the cleanup.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. The context data entries are MB
         implementation-specific.
     @param terminating
     @parblock
         Indicates whether the MB is in the process of shutting down and thus
         cannot tolerate postponing of the cleanup, as follows:

         When True, the MB is in the process of shutting down. The MI shall
         perform any necessary cleanup and shall not postpone the cleanup.
         After this function returns (successful or in error), the MB will
         consider this MI to be uninitialized and will not call further MI
         functions for this MI.

         When False, the MI can choose to perform or postpone the cleanup, by
         performing one of these actions:

         @li The MI performs any necessary cleanup and does not request
             postponing the cleanup. After this function returns (successful or
             in error), the MB will consider this MI to be uninitialized and
             will not call further MI functions for this MI.
         @li The MI does not perform any cleanup and temporarily postpones the
             cleanup, by returning `CMPI_RC_DO_NOT_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB may call this
             function again after some MB implementation-specific time.
         @li The MI does not perform any cleanup and permanently postpones the
             cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB will not call this
             function again until the MB terminates (at which time the MB calls
             this function with terminating set to true).
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following @ref CMPIrc codes shall be used by the MI in the
     function return status:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not unload now;
         the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
         the MB will not retry an unload later unless it shuts down.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMInstanceMIStub()
     @bug In the CMPI Standard document, add the sentence about the number of
         invocations relative to the number of namespaces serviced.
    */
    CMPIStatus (*cleanup) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        CMPIBoolean terminating);

    /**
     @brief Enumerate instance paths of instances of a given class serviced by
         this MI.

     CMPIInstanceMIFT.enumerateInstanceNames() shall enumerate the instance
     paths of instances of a given class that are serviced by this MI, by
     accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p classPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p classPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all instance
         paths representing the result set into this container.
     @param classPath Points to a CMPIObjectPath object that references the
         given class and that contains the namespace and class name components.
         The hostname and key components, if present, have no meaning and
         should be ignored.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>N/A</TD>
         <TD>No instances found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if no
         instances are found, the MI should return success with an empty result
         data container. The MB shall treat this return code as a successful
         return of an empty result set.
    */
    CMPIStatus (*enumerateInstanceNames) (CMPIInstanceMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* classPath);

    /**
     @brief Enumerate the instances of a given class that are serviced by this
         MI.

     CMPIInstanceMIFT.enumerateInstances() shall enumerate the instances of a
     given class that are serviced by this MI, by accessing the underlying
     managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p classPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p classPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all instances
         representing the result set into this container.
     @param classPath Points to a CMPIObjectPath object that references the
         given class and that contains the namespace and class name components.
         The hostname and key components, if present, have no meaning and
         should be ignored.
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. This set of property names
         will reflect the effects of any invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx. The end of the array
         is identified by a NULL pointer. Each returned object shall not
         include elements for any properties missing from this list. If the
         properties argument is NULL, this indicates that all properties shall
         be included in each returned object.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>N/A</TD>
         <TD>No instances found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if no
         instances are found, the MI should return success with an empty result
         data container. The MB shall treat this return code as a successful
         return of an empty result set.
    */
    CMPIStatus (*enumerateInstances) (CMPIInstanceMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* classPath , const char** properties);

    /**
     @brief Get an existing instance.

     CMPIInstanceMIFT.getInstance() shall get an existing instance, by
     accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of the @p instPath argument for which this function will be
     called by the MB depends on the specifics of how the MB relates classes
     and MI names, which is out of scope for this standard. As a result, the
     MB may call this function for classes for which the MI is not responsible.
     In order for an MI to be portable across MB implementations with different
     approaches to relate MI names and classes, the MI must check whether it
     services the class specified in the @p instPath argument.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the retrieved
         instance into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be retrieved and that contains the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored.
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. This set of property names will reflect
         the effects of any invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx. The returned instance
         shall not include elements for any properties missing from this list.
         If @p properties is NULL, this indicates that all properties shall be
         included in the returned instance.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by this MI</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
    */
    CMPIStatus (*getInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* instPath,
        const char** properties);

    /**
     @brief Create an instance of a given class.

     CMPIInstanceMIFT.createInstance() shall create an instance of a given
     class in the namespace of that class, by creating the underlying managed
     elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p classPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p classPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the
         instance path of the created instance into this container.
     @param classPath Points to a CMPIObjectPath object that references the
         given class. The hostname and key components, if present, have no
         meaning and should be ignored.
     @param inst Points to a CMPIInstance object specifying property values for
         the new instance. The object path component within this CMPIInstance
         object has no meaning; it should not be provided by MBs and should not
         be used by MIs.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0228</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ALREADY_EXISTS`</TD><TD>WIPG0213</TD>
         <TD>Instance already exists.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_ACCESS_DENIED`.
     @deprecated The use of the key component in @p classPath is
         deprecated since CMPI 2.1; the key component should not be provided
         by MBs and should not be used by MIs.
    */
    CMPIStatus (*createInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* classPath,
        const CMPIInstance* inst);

    /**
     @brief Modify property values of an existing instance.

     CMPIInstanceMIFT.modifyInstance() shall modify property values of an
     existing instance, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class in @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be modified and that contains the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored.
     @param modInst Points to a CMIPInstance object specifying new values for
         the properties to be modified. The object path component within this
         CMPIInstance object has no meaning; it should not be provided by MBs
         and should not be used by MIs.
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx have no meaning for this
         function. The function shall not modify elements for any properties
         missing from this list. If @p properties is NULL, this indicates that
         all properties specified in @p modInst are modified.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0228</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NO_SUCH_PROPERTY`</TD><TD>WIPG0220</TD>
         <TD>No such property.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @changed210 In CMPI 2.1, added the return code
         `CMPI_RC_ERR_NO_SUCH_PROPERTY`.
    */
    CMPIStatus (*modifyInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* instPath,
        const CMPIInstance* modInst, const char** properties);

    /**
     @brief Delete an existing instance.

     CMPIInstanceMIFT.deleteInstance() shall delete an existing instance, by
     deleting the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class in @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be deleted and that contains the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0228</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
    */
    CMPIStatus (*deleteInstance) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* op);

    /**
     @brief Execute a query on a given class and return the query result.

     CMPIInstanceMIFT.execQuery() shall execute a query on a given class and
     return the query result, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class in @p classPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p classPath.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param classPath Points to a CMPIObjectPath object that references the
         given class and that contains the namespace and class name components.
         The hostname and key components, if present, have no meaning and
         should be ignored.
     @param query Select expression.
     @param lang Query language (case-sensitive).
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED`</TD>
         <TD>WIPG0221</TD>
         <TD>Query language not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED`</TD>
         <TD>WIPG0222</TD>
         <TD>A feature of the query language is not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_QUERY`</TD>
         <TD>WIPG02223</TD>
         <TD>Invalid Query.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED` and
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if no
         instances are found, the MI should return success with an empty result
         data container. The MB shall treat this return code as a successful
         return of an empty result set.
    */
    CMPIStatus (*execQuery) (CMPIInstanceMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* classPath,
        const char* query, const char* lang);

#ifdef CMPI_VER_210

    /**
     @brief Enumerate the instances of a given class that are serviced by this
         MI, returning only those that match a given query filter.

     CMPIInstanceMIFT.enumerateInstancesFiltered() shall enumerate the
     instances of a given class that are serviced by this MI, returning only
     those instances that match a given query filter, by enumerating the
     underlying managed elements. The returned instances shall have their
     instance paths set. If no such instances are found, the function shall
     return success with an empty result data container.

     @param mi Points to a CMPIInstanceMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return the MI shall have put all
         instances representing the result set into this container.
     @param classPath Points to a CMPIObjectPath object that references the
        given class and that contains namespace and class name components. The
        hostname and key components, if present, have no meaning and should be
        ignored.
     @param properties If not NULL, is an array of zero or more pointers
         to strings, each specifying a property name. The end of the array
         is identified by a NULL pointer. This set of property names will
         reflect the effects of any invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx. Each returned
         instance shall not include elements for any properties missing
         from this list. If @p properties is NULL, this indicates
         that all properties shall be included in each returned instance.
     @param filterQueryLanguage Query language used by @p filterQuery. If NULL,
         no filtering is performed. Note that FQL (see @ref ref-dmtf-dsp0212
         "DSP0212") is required to be supported by MIs as a query language; see
         Subclause 4.5 in the @ref ref-cmpi-standard "CMPI Standard".
     @param filterQuery Query in the query language defined by @p
         filterQueryLanguage. If NULL, no filtering is performed. A request
         that specifies a filter through valid and non-NULL @p
         filterQueryLanguage and @p filterQuery arguments shall return only
         instances that match that filter as defined in the filter
         specification.
     @param continueOnError Defines whether this operation may continue to
         return objects after it returns an error. If false, the MI shall
         terminate after returning an error to the result data container. If
         true, the MI may continue to return data (objects and subsequent
         errors) to the result data container after returning an error. An MI
         that cannot continue after returning an error shall ignore the value
         of @p continueOnError and shall behave as if it was specified as
         false.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_LANGUAGE_NOT_SUPPORTED`</TD>
         <TD>WIPG0221</TD><TD>Query language not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_QUERY_FEATURE_NOT_SUPPORTED`</TD>
         <TD>WIPG0222</TD>
         <TD>A feature of the query language is not supported.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_QUERY`</TD>
         <TD>WIPG0223</TD><TD>Invalid query.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMInstanceMIStub()
     @added210 Added in CMPI 2.1.

     @bug In the CMPI Standard document, simplify the description of
         filterQueryLanguage for the case of NULL, to match the description in
         the header file.
    */
    CMPIStatus (*enumerateInstancesFiltered) (CMPIInstanceMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* classPath,
        const char** properties, const char*filterQuerylanguage,
        const char* filterQuery, CMPIStatus* rc);

#endif /*CMPI_VER_210*/

} CMPIInstanceMIFT;

/**
 * @}
 * @addtogroup association-mi
 * @{
 */

/**
 * @brief CMPIAssociationMI object.
 *
 * This object is provided by an association MI through
 * @ref mi-factory "MI factory functions", in order to make its MI functions
 * available to the MB.
 */
typedef struct _CMPIAssociationMI {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this MI
     *     object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this MI object.
     */
    const CMPIAssociationMIFT* ft;

} CMPIAssociationMI;

/**
 * @brief Function table of CMPIAssociationMI object.
 */
typedef struct _CMPIAssociationMIFT {

    /**
     * @brief CMPI version supported by the MI for this function table.
     *
     * Any later CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * @brief Informal MI-specific version number for this MI.
     */
    int miVersion;

    /**
     * @brief Informal MI-specific name for this MI.
     */
    const char* miName;

    /**
     @brief Perform cleanup for an @ref CMPIAssociationMI object.

     CMPIAssociationMIFT.cleanup() shall perform any necessary cleanup for the
     Association MI identified by @p mi, unless the MI postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. This function will be called once for a specific MI (unless
     the MI postpones the cleanup), even if that MI services more than one
     namespace. After this function returns, the MB may unload the load library
     this MI is part of, unless the MI postpones the cleanup.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. The context data entries are MB
         implementation-specific.
     @param terminating
     @parblock
         Indicates whether the MB is in the process of shutting down and thus
         cannot tolerate postponing of the cleanup, as follows:

         When True, the MB is in the process of shutting down. The MI shall
         perform any necessary cleanup and shall not postpone the cleanup.
         After this function returns (successful or in error), the MB will
         consider this MI to be uninitialized and will not call further MI
         functions for this MI.

         When False, the MI can choose to perform or postpone the cleanup, by
         performing one of these actions:

         @li The MI performs any necessary cleanup and does not request
             postponing the cleanup. After this function returns (successful or
             in error), the MB will consider this MI to be uninitialized and
             will not call further MI functions for this MI.
         @li The MI does not perform any cleanup and temporarily postpones the
             cleanup, by returning `CMPI_RC_DO_NOT_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB may call this
             function again after some MB implementation-specific time.
         @li The MI does not perform any cleanup and permanently postpones the
             cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB will not call this
             function again until the MB terminates (at which time the MB calls
             this function with terminating set to true).
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following @ref CMPIrc codes shall be used by the MI in the
     function return status:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not unload now;
         the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
         the MB will not retry an unload later unless it shuts down.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @convfunction CMAssociationMIStub()
    */
    CMPIStatus (*cleanup) (CMPIAssociationMI* mi, const CMPIContext* ctx,
        CMPIBoolean terminating);

    /**
     @brief Enumerate the instances associated with a given source instance
         that are serviced by this MI.

     CMPIAssociationMIFT.associators() shall enumerate the instances associated
     with a given source instance and that are serviced by this MI, by
     accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p assocClass or @p resultClass filters are specified in a call to
     this function, the MB is not required to scope calls to this function to
     only the MIs that service these classes. As a result, the MB may (and
     will, in most implementations) call this function for classes in @p
     assocClass or @p resultClass for which the MI is not responsible. In order
     for an MI to be portable across MB implementations, the MI must check
     whether it services the classes specified in the @p assocClass and @p
     resultClass arguments.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall either return success with an empty result data
         container or `CMPI_RC_ERR_NOT_FOUND`. The use of
         `CMPI_RC_ERR_NOT_FOUND` if the source instance does not exist, is
         <b>deprecated</b>.
     @param assocClass If not NULL, shall be a valid association class name. It
         acts as a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param resultRole If not NULL, shall be a valid property name. It acts as
         a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         association in which the returned object plays the specified role
         (i.e., the name of the property in the association class that refers
         to the returned object shall match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         @ref CMPIInvocationFlags entry of the @p ctx argument have no meaning
         for this function. Each returned instance shall not include elements
         for any properties missing from this list. If the properties argument
         is NULL, this indicates that all properties shall be included in each
         returned instance.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Source instance not found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_PARAMETER` and
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if the
         source instance does not exist, the MI should return success with an
         empty result data container. The MB shall treat this return code as a
         successful return of an empty result set.
     @bug In the CMPI Standard document, the explanation of the deprecated use
         of CMPI_RC_ERR_NOT_FOUND in the description of the instPath argument
         should be updated with the wording from the header file.
    */
    CMPIStatus (*associators) (CMPIAssociationMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* op,
        const char* assocClass, const char* resultClass, const char* role,
        const char* resultRole, const char** properties);

    /**
     @brief Enumerate the instance paths of instances associated with a given
         source instance that are serviced by this MI.

     CMPIAssociationMIFT.associatorNames() shall enumerate the instance paths
     of instances associated with a given source instance and that are serviced
     by this MI, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p assocClass or @p resultClass filters are specified in a call to
     this function, the MB is not required to scope calls to this function to
     only the MIs that service these classes. As a result, the MB may (and
     will, in most implementations) call this function for classes in @p
     assocClass or @p resultClass for which the MI is not responsible. In order
     for an MI to be portable across MB implementations, the MI must check
     whether it services the classes specified in the @p assocClass and @p
     resultClass arguments.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall either return success with an empty result data
         container or `CMPI_RC_ERR_NOT_FOUND`. The use of
         `CMPI_RC_ERR_NOT_FOUND` if the source instance does not exist, is
         <b>deprecated</b>.
     @param assocClass If not NULL, shall be a valid association class name. It
         acts as a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param resultRole If not NULL, shall be a valid property name. It acts as
         a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         association in which the returned object plays the specified role
         (i.e., the name of the property in the association class that refers
         to the returned object shall match the value of this argument).
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Source instance not found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_PARAMETER` and
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if the
         source instance does not exist, the MI should return success with an
         empty result data container. The MB shall treat this return code as a
         successful return of an empty result set.
     @bug In the CMPI Standard document, the explanation of the deprecated use
         of CMPI_RC_ERR_NOT_FOUND in the description of the instPath argument
         should be updated with the wording from the header file.
    */
    CMPIStatus (*associatorNames) (CMPIAssociationMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* instPath, const char* assocClass,
        const char* resultClass, const char* role, const char* resultRole);

    /**
     @brief Enumerate the association instances referencing a given source
         instance that are serviced by this MI.

     CMPIAssociationMIFT.references() shall enumerate the association instances
     referencing a given source instance and that are serviced by this MI, by
     accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p resultClass filter is specified in a call to this function, the
     MB is not required to scope calls to this function to only the MIs that
     service this class. As a result, the MB may (and will, in most
     implementations) call this function for classes in @p resultClass for
     which the MI is not responsible. In order for an MI to be portable across
     MB implementations, the MI must check whether it services the class
     specified in @p resultClass.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall either return success with an empty result data
         container or `CMPI_RC_ERR_NOT_FOUND`. The use of
         `CMPI_RC_ERR_NOT_FOUND` if the source instance does not exist, is
         <b>deprecated</b>.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         @ref CMPIInvocationFlags entry of the @p ctx argument have no meaning
         for this function. Each returned instance shall not include elements
         for any properties missing from this list. If the properties argument
         is NULL, this indicates that all properties shall be included in each
         returned instance.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Source instance not found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_PARAMETER` and
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if the
         source instance does not exist, the MI should return success with an
         empty result data container. The MB shall treat this return code as a
         successful return of an empty result set.
     @bug In the CMPI Standard document, the explanation of the deprecated use
         of CMPI_RC_ERR_NOT_FOUND in the description of the instPath argument
         should be updated with the wording from the header file.
    */
    CMPIStatus (*references) (CMPIAssociationMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* instPath,
        const char* resultClass, const char* role,
        const char** properties);

    /**
     @brief Enumerate the instance paths of association instances
         referencing a given source instance that are serviced by this MI.

     CMPIAssociationMIFT.referenceNames() shall enumerate
     the instance paths of the association instances referencing a given
     source instance and that are serviced by this MI, by accessing the
     underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p resultClass filter is specified in a call to this function, the
     MB is not required to scope calls to this function to only the MIs that
     service this class. As a result, the MB may (and will, in most
     implementations) call this function for classes in @p resultClass for
     which the MI is not responsible. In order for an MI to be portable across
     MB implementations, the MI must check whether it services the class
     specified in @p resultClass.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall either return success with an empty result data
         container or `CMPI_RC_ERR_NOT_FOUND`. The use of
         `CMPI_RC_ERR_NOT_FOUND` if the source instance does not exist, is
         <b>deprecated</b>.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Source instance not found. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_INVALID_PARAMETER` and
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`.
     @deprecated The return code `CMPI_RC_ERR_NOT_FOUND` of this function is
         deprecated since CMPI 2.1. Instead of using this return code if the
         source instance does not exist, the MI should return success with an
         empty result data container. The MB shall treat this return code as a
         successful return of an empty result set.
     @bug In the CMPI Standard document, the explanation of the deprecated use
         of CMPI_RC_ERR_NOT_FOUND in the description of the instPath argument
         should be updated with the wording from the header file.
    */
    CMPIStatus (*referenceNames) (CMPIAssociationMI* mi,
            const CMPIContext* ctx, const CMPIResult* rslt,
            const CMPIObjectPath* instPath, const char* resultClass,
            const char* role);

#ifdef CMPI_VER_210

    /**
     @brief Enumerate the instances associated with a given source instance
         that are serviced by this MI, returning only those instances that
         match a given query filter.

     CMPIAssociationMIFT.associatorsFiltered() shall enumerate instances
     associated with a source instance and that are serviced by this MI,
     returning only those instances that match a given query filter, by
     accessing the underlying managed elements. The returned instances shall
     have their instance paths set. If no such instances are found, the
     function shall return success with an empty result data container.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p assocClass or @p resultClass filters are specified in a call to
     this function, the MB is not required to scope calls to this function to
     only the MIs that service these classes. As a result, the MB may (and
     will, in most implementations) call this function for classes in @p
     assocClass or @p resultClass for which the MI is not responsible. In order
     for an MI to be portable across MB implementations, the MI must check
     whether it services the classes specified in the @p assocClass and @p
     resultClass arguments.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall return success with an empty result data container.
     @param assocClass If not NULL, shall be a valid association class name. It
         acts as a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         instance of this class or one of its subclasses.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param resultRole If not NULL, shall be a valid property name. It acts as
         a filter on the returned set of objects by mandating that each
         returned object shall be associated with the source object via an
         association in which the returned object plays the specified role
         (i.e., the name of the property in the association class that refers
         to the returned object shall match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx have no meaning for this
         function. Each returned instance shall not include elements for any
         properties missing from this list. If @p properties is NULL, this
         indicates that all properties shall be included in each returned
         instance.
     @param filterQueryLanguage Query language used by @p filterQuery. If NULL,
         no filtering is performed. Note that FQL (see @ref ref-dmtf-dsp0212
         "DSP0212") is required to be supported by MIs as a query language; see
         Subclause 4.5 in the @ref ref-cmpi-standard "CMPI Standard".
     @param filterQuery Query in the query language defined by @p
         filterQueryLanguage. If NULL, no filtering is performed. A request
         that specifies a filter through valid and non-NULL @p
         filterQueryLanguage and @p filterQuery arguments shall return only
         instances that match that filter as defined in the filter
         specification.
     @param continueOnError Defines whether this operation may continue to
         return objects after it returns an error. If false, the MI shall
         terminate after returning an error to the result data container. If
         true, the MI may continue to returning data (objects and subsequent
         errors) to the result data container after returning an error. An MI
         that cannot continue after returning an error shall ignore the value
         of @p continueOnError and shall behave as if it was specified as
         false.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @added210 Added in CMPI 2.1.

     @bug In the CMPI Standard document, fix the incorrect structure name in
         the description of the mi argument, from CMPIInstanceMI to
         CMPIAssociationMI.
     @bug In the CMPI Standard document, simplify the description of
         filterQueryLanguage for the case of NULL, to match the description in
         the header file.
     @bug In the CMPI Standard document, add the second and third paragraph
        (about scope of MI) from the header file.
    */
    CMPIStatus (*associatorsFiltered) (CMPIAssociationMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* instPath, const char* assocClass,
        const char* resultClass, const char* role, const char* resultRole,
        const char** properties, const char* filterQueryLanguage,
        const char* filterQuery, CMPIBoolean continueOnError);

    /**
     @brief Enumerate the association instances referencing a given source
         instance that are serviced by this MI, returning only those instances
         that match a given query filter.

     CMPIAssociationMIFT.referencesFiltered() shall enumerate the association
     instances referencing a given source instance and that are serviced by
     this MI, returning only those instances that match a given query filter,
     by accessing the underlying managed elements. The returned instances shall
     have their instance paths set. If no such instances are found, the
     function shall return success with an empty result data container.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     If the @p resultClass filter is specified in a call to this function, the
     MB is not required to scope calls to this function to only the MIs that
     service this class. As a result, the MB may (and will, in most
     implementations) call this function for classes in @p resultClass for
     which the MI is not responsible. In order for an MI to be portable across
     MB implementations, the MI must check whether it services the class
     specified in @p resultClass.

     @param mi Points to a CMPIAssociationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put all
         instance paths representing the result set into this container.
     @param instPath Points to a CMPIObjectPath object that references the
         given source instance and that contains the namespace, class name, and
         key components. The hostname component, if present, has no meaning and
         should be ignored. If the source instance does not exist, this
         function shall return success with an empty result data container.
     @param resultClass If not NULL, shall be a valid class name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be an instance of this class or one of its subclasses.
     @param role If not NULL, shall be a valid property name. It acts as a
         filter on the returned set of objects by mandating that each returned
         object shall be associated with the source object via an association
         in which the source object plays the specified role (i.e., the name of
         the property in the association class that refers to the source object
         shall match the value of this argument).
     @param properties If not NULL, is an array of zero or more pointers to
         strings, each specifying a property name. The end of the array is
         identified by a NULL pointer. The invocation flags specified in the
         @ref CMPIInvocationFlags entry of @p ctx have no meaning for this
         function. Each returned instance shall not include elements for any
         properties missing from this list. If @p properties is NULL, this
         indicates that all properties shall be included in each returned
         instance.
     @param filterQueryLanguage Query language used by @p filterQuery. If NULL,
         no filtering is performed. Note that FQL (see @ref ref-dmtf-dsp0212
         "DSP0212") is required to be supported by MIs as a query language; see
         Subclause 4.5 in the @ref ref-cmpi-standard "CMPI Standard".
     @param filterQuery Query in the query language defined by @p
         filterQueryLanguage. If NULL, no filtering is performed. A request
         that specifies a filter through valid and non-NULL @p
         filterQueryLanguage and @p filterQuery arguments shall return only
         instances that match that filter as defined in the filter
         specification.
     @param continueOnError Defines whether this operation may continue to
         return objects after it returns an error. If false, the MI shall
         terminate after returning an error to the result data container. If
         true, the MI may continue to returning data (objects and subsequent
         errors) to the result data container after returning an error. An MI
         that cannot continue after returning an error shall ignore the value
         of @p continueOnError and shall behave as if it was specified as
         false.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid filter parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMAssociationMIStub()
     @added210 Added in CMPI 2.1.

     @bug In the CMPI Standard document, fix the incorrect structure name in
         the description of the mi argument, from CMPIInstanceMI to
         CMPIAssociationMI.
     @bug In the CMPI Standard document, simplify the description of
         filterQueryLanguage for the case of NULL, to match the description in
         the header file.
     @bug In the CMPI Standard document, add the second and third paragraph
        (about scope of MI) from the header file.
    */
    CMPIStatus (*referencesFiltered) (CMPIAssociationMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        const CMPIObjectPath* instPath, const char* resultClass,
        const char* role, const char** properties,
        const char* filterQueryLanguage, const char* filterQuery,
        CMPIBoolean continueOnError);

#endif /*CMPI_VER_210*/

} CMPIAssociationMIFT;

/**
 * @}
 * @addtogroup method-mi
 * @{
 */

/**
 * @brief CMPIMethodMI object.
 *
 * This object is provided by a method MI through
 * @ref mi-factory "MI factory functions", in order to make its MI functions
 * available to the MB.
 */
typedef struct _CMPIMethodMI {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this MI
     *     object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this MI object.
     */
    const CMPIMethodMIFT* ft;

} CMPIMethodMI;

/**
 * @brief Function table of CMPIMethodMI object.
 */
typedef struct _CMPIMethodMIFT {

    /**
     * @brief CMPI version supported by the MI for this function table.
     *
     * Any later CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * @brief Informal MI-specific version number for this MI.
     */
    int miVersion;

    /**
     * @brief Informal MI-specific name for this MI.
     */
    const char* miName;

    /**
     @brief Perform cleanup for an Instance MI.

     CMPIMethodMIFT.cleanup() shall perform any necessary cleanup for the
     Method MI identified by @p mi, unless the MI postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. This function will be called once for a specific MI (unless
     the MI postpones the cleanup), even if that MI services more than one
     namespace. After this function returns, the MB may unload the load library
     this MI is part of, unless the MI postpones the cleanup.

     @param mi Points to a CMPIMethodMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. The context data entries are MB
         implementation-specific.
     @param terminating
     @parblock
         Indicates whether the MB is in the process of shutting down and thus
         cannot tolerate postponing of the cleanup, as follows:

         When True, the MB is in the process of shutting down. The MI shall
         perform any necessary cleanup and shall not postpone the cleanup.
         After this function returns (successful or in error), the MB will
         consider this MI to be uninitialized and will not call further MI
         functions for this MI.

         When False, the MI can choose to perform or postpone the cleanup, by
         performing one of these actions:

         @li The MI performs any necessary cleanup and does not request
             postponing the cleanup. After this function returns (successful or
             in error), the MB will consider this MI to be uninitialized and
             will not call further MI functions for this MI.
         @li The MI does not perform any cleanup and temporarily postpones the
             cleanup, by returning `CMPI_RC_DO_NOT_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB may call this
             function again after some MB implementation-specific time.
         @li The MI does not perform any cleanup and permanently postpones the
             cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB will not call this
             function again until the MB terminates (at which time the MB calls
             this function with terminating set to true).
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following @ref CMPIrc codes shall be used by the MI in the
     function return status:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not unload now;
         the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
         the MB will not retry an unload later unless it shuts down.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @convfunction CMMethodMIStub()

     @bug In the CMPI Standard document, add the sentence about the number of
         invocations relative to the number of namespaces serviced.
    */
    CMPIStatus (*cleanup) (CMPIMethodMI* mi, const CMPIContext* ctx,
        CMPIBoolean terminating);

    /**
     @brief Invoke a method on a target object.

     CMPIMethodMIFT.invokeMethod() shall invoke a named, extrinsic method on a
     target object, by accessing the underlying managed elements. Instance
     methods (i.e., non-static methods) can be invoked only on instances. Class
     methods (i.e., static methods) can be invoked on instances and classes

     This function is provided by the MI in context of a particular MI name.
     The class of @p objPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p objPath.

     @param mi Points to a CMPIMethodMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the
         return value of the method into this container.
         The CMPIResultFT function to be used for that depends on the
         data type of the method return, as follows:
         @li Return values declared as embedded instances (see Subclause 4.1.3
             of the @ref ref-cmpi-standard "CMPI Standard") shall be returned
             using CMPIResultFT.returnInstance().
         @li Return values declared with type `ref <classname>` (see Subclause
             4.1.3 of the @ref ref-cmpi-standard "CMPI Standard") shall be
             returned using CMPIResultFT.returnObjectPath().
         @li Any other return values shall be returned using
             CMPIResultFT.returnData().
     @param objPath Points to the CMPIObjectPath object that references the
         target object on which the method is invoked. If the target object is
         an instance, this object path will contain the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored. If the target object is a class, this object
         path will contain the namespace and class name components. The
         hostname and key components, if present, have no meaning and should be
         ignored.
     @param method Method name.
     @param in Points to a CMPIArgs object (whether the method has any input
         parameters or not) that contains the method input parameters.
     @param [out] out Points to an empty CMPIArgs object (whether the method
         has any output parameters or not) that, upon successful return of the
         method, shall have been updated by the MI to contain the method output
         parameters.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>N/A</TD>
         <TD>Function is not supported by this MI. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_METHOD_NOT_AVAILABLE`</TD><TD>WIPG0219</TD>
         <TD>Function is not suppored by this MI.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>WIPG0249</TD>
         <TD>Invalid method parameters.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Target object not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`</TD><TD>WIPG0240</TD>
         <TD>Limits Exceeded.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMMethodMIStub()
     @changed210 In CMPI 2.1, added the return codes
         `CMPI_RC_ERR_METHOD_NOT_AVAILABLE`,
         `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`, and
         `CMPI_RC_ERR_INVALID_PARAMETER`.
     @deprecated The return code `CMPI_RC_ERR_NOT_SUPPORTED` of this function is
         deprecated since CMPI 2.1. Use `CMPI_RC_ERR_METHOD_NOT_AVAILABLE`
         instead for indicating that the function is not supported.
    */
    CMPIStatus (*invokeMethod) (CMPIMethodMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* objPath,
        const char* method, const CMPIArgs* in, CMPIArgs* out);

} CMPIMethodMIFT;

/**
 * @}
 * @addtogroup property-mi
 * @{
 */

/**
 * @brief CMPIPropertyMI object.
 *
 * This object is provided by a property MI through
 * @ref mi-factory "MI factory functions", in order to make its MI functions
 * available to the MB.
 *
 * @deprecated Property MIs are deprecated since CMPI 2.1,
 *     in accord with the deprecation of property client operations in
 *     DMTF specifications.
 */
typedef struct _CMPIPropertyMI {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this MI
     *     object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this MI object.
     */
    const CMPIPropertyMIFT* ft;

} CMPIPropertyMI;

/**
 * @brief Function table of CMPIPropertyMI object.
 */
typedef struct _CMPIPropertyMIFT {

    /**
     * @brief CMPI version supported by the MI for this function table.
     *
     * Any later CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * @brief Informal MI-specific version number for this MI.
     */
    int miVersion;

    /**
     * @brief Informal MI-specific name for this MI.
     */
    const char* miName;

    /**
     @brief Perform cleanup for a Property MI. (**Deprecated**)

     CMPIPropertyMIFT.cleanup() shall perform any necessary cleanup for the
     Property MI identified by @p mi, unless the MI postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. This function will be called once for a specific MI (unless
     the MI postpones the cleanup), even if that MI services more than one
     namespace. After this function returns, the MB may unload the load library
     this MI is part of, unless the MI postpones the cleanup.

     @param mi Points to a CMPIPropertyMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. The context data entries are MB
         implementation-specific.
     @param terminating
     @parblock
         Indicates whether the MB is in the process of shutting down and thus
         cannot tolerate postponing of the cleanup, as follows:

         When True, the MB is in the process of shutting down. The MI shall
         perform any necessary cleanup and shall not postpone the cleanup.
         After this function returns (successful or in error), the MB will
         consider this MI to be uninitialized and will not call further MI
         functions for this MI.

         When False, the MI can choose to perform or postpone the cleanup, by
         performing one of these actions:

         @li The MI performs any necessary cleanup and does not request
             postponing the cleanup. After this function returns (successful or
             in error), the MB will consider this MI to be uninitialized and
             will not call further MI functions for this MI.
         @li The MI does not perform any cleanup and temporarily postpones the
             cleanup, by returning `CMPI_RC_DO_NOT_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB may call this
             function again after some MB implementation-specific time.
         @li The MI does not perform any cleanup and permanently postpones the
             cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB will not call this
             function again until the MB terminates (at which time the MB calls
             this function with terminating set to true).
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following @ref CMPIrc codes shall be used by the MI in the
     function return status:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not unload now;
         the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
         the MB will not retry an unload later unless it shuts down.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMPropertyMIStub()
     @added200 Added in CMPI 2.0.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
     @bug In the CMPI Standard document, add the sentence about the number of
         invocations relative to the number of namespaces serviced.
    */
    CMPIStatus (*cleanup) (CMPIPropertyMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating); /*Deprecated*/

    /**
     @brief Set the value of a property of an existing instance.
         (**Deprecated**)

     CMPIPropertyMIFT.setProperty() shall set the value of a property of an
     existing instance, by accessing the underlying managed elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     @param mi Points to a CMPIPropertyMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be modified and that contains the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored.
     @param name Property name.
     @param data A CMPIData structure specifying the value to be assigned
         to the property.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_NAMESPACE`</TD><TD>N/A</TD>
         <TD>The namespace specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>N/A</TD>
         <TD>The parameter is invalid. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_CLASS`</TD><TD>N/A</TD>
         <TD>The class specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NO_SUCH_PROPERTY`</TD><TD>WIPG0220</TD>
         <TD>No such property.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMPropertyMIStub()
     @deprecated The return codes `CMPI_RC_ERR_INVALID_NAMESPACE`,
         `CMPI_RC_ERR_INVALID_PARAMETER`, and `CMPI_RC_ERR_INVALID_CLASS` for
         this function are deprecated since CMPI 2.1, because the corresponding
         conditions have already been verified by the MB.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
     @bug In the CMPI Standard document, change "set or modify" to "set" in the
         short and long descriptions.
    */
    CMPIStatus (*setProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* instPath,
        const char* name, const CMPIData data);

    /**
     @brief Retrieve a property value of an existing instance. (**Deprecated**)

     CMPIPropertyMIFT.getProperty() shall retrieve a property value of an
     existing instance, by accessing the underlying managed elements.

     @param mi Points to a CMPIPropertyMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have put the retrieved
         property value into this container. The CMPIResultFT function to be
         used for that depends on the data type of the property, as follows:
         @li The values of properties declared as embedded instances (see
             Subclause 4.1.3 of the @ref ref-cmpi-standard "CMPI Standard")
             shall be returned using CMPIResultFT.returnInstance().
         @li The values of references (see Subclause 4.1.3 of the @ref
             ref-cmpi-standard "CMPI Standard") shall be returned using
             CMPIResultFT.returnObjectPath().
         @li Any other property values shall be returned using
             CMPIResultFT.returnData().
     @param instPath Points to a CMPIObjectPath object that references the
         given instance and that contains the namespace, class name, and key
         components. The hostname component, if present, has no meaning and
         should be ignored.
     @param name Property name.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_NAMESPACE`</TD><TD>N/A</TD>
         <TD>The namespace specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>N/A</TD>
         <TD>The parameter is invalid. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_CLASS`</TD><TD>N/A</TD>
         <TD>The class specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NO_SUCH_PROPERTY`</TD><TD>WIPG0220</TD>
         <TD>No such property.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMPropertyMIStub()
     @deprecated The return codes `CMPI_RC_ERR_INVALID_NAMESPACE`,
         `CMPI_RC_ERR_INVALID_PARAMETER`, and `CMPI_RC_ERR_INVALID_CLASS` for
         this function are deprecated since CMPI 2.1, because the corresponding
         conditions have already been verified by the MB.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
    */
    CMPIStatus (*getProperty) (CMPIPropertyMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPIObjectPath* instPath,
        const char* name);

#ifdef CMPI_VER_200

    /**
     @brief Set the value and origin of a property of an existing instance.
         (**Deprecated**)

     CMPIPropertyMIFT.setPropertyWithOrigin() shall set the value and origin of
     a property of an existing instance, by accessing the underlying managed
     elements.

     This function is provided by the MI in context of a particular MI name.
     The class of @p instPath for which this function will be called by the MB
     depends on the specifics of how the MB relates classes and MI names, which
     is out of scope for this standard. As a result, the MB may call this
     function for classes for which the MI is not responsible. In order for an
     MI to be portable across MB implementations with different approaches to
     relate MI names and classes, the MI must check whether it services the
     class specified in @p instPath.

     @param mi Points to a CMPIPropertyMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation.
     @param rslt Points to a CMPIResult object that is the result data
         container. Upon successful return, the MI shall have left this
         container empty.
     @param instPath Points to a CMPIObjectPath object that references the
         instance to be retrieved and that contains the namespace, class name,
         and key components. The hostname component, if present, has no meaning
         and should be ignored.
     @param name Property name.
     @param data A CMPIData structure specifying the value to be assigned
         to the property.
     @param origin Origin (class name) to be set for the property. If NULL, no
         origin is set for the property.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following table lists the @ref CMPIrc codes that shall be used by the
     MI in the function return status, as well as the WBEM operation messages
     that should be used in the CMPIError object if the MI supports
     extended error handling (see the corresponding
     @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability):
     <TABLE>
     <TR><TH>CMPIRCCode</TH><TH>CMPIErrorMsg</TH><TH>Description</TH></TR>
     <TR><TD>`CMPI_RC_OK`</TD><TD>N/A</TD>
         <TD>Function Successful.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_SUPPORTED`</TD><TD>WIPG0228</TD>
         <TD>Function is not supported by the MB.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_ACCESS_DENIED`</TD><TD>WIPG0201</TD>
         <TD>Not authorized.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_NAMESPACE`</TD><TD>N/A</TD>
         <TD>The namespace specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_PARAMETER`</TD><TD>N/A</TD>
         <TD>The parameter is invalid. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_INVALID_CLASS`</TD><TD>N/A</TD>
         <TD>The class specified in @p instPath is invalid or does not
         exist. (**Deprecated**)</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NOT_FOUND`</TD><TD>WIPG0213</TD>
         <TD>Instance not found.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_NO_SUCH_PROPERTY`</TD><TD>WIPG0220</TD>
         <TD>No such property.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0243</TD>
         <TD>Timeout occurred.</TD></TR>
     <TR><TD>`CMPI_RC_ERR_FAILED`</TD><TD>WIPG0227 + implementation-specific
         message</TD>
         <TD>Other error occurred.</TD></TR>
     </TABLE>
     @convfunction CMPropertyMIStub()
     @added200 Added in CMPI 2.0.
     @deprecated The return codes `CMPI_RC_ERR_INVALID_NAMESPACE`,
         `CMPI_RC_ERR_INVALID_PARAMETER`, and `CMPI_RC_ERR_INVALID_CLASS` for
         this function are deprecated since CMPI 2.1, because the corresponding
         conditions have already been verified by the MB.
     @deprecated This function is deprecated since CMPI 2.1, in accord with the
         deprecation of property client operations in DMTF specifications.
    */
    CMPIStatus (*setPropertyWithOrigin) (CMPIPropertyMI* mi,
        const CMPIContext* ctx, const CMPIResult* rslt,
        CMPIObjectPath* instPath, const char* name, const CMPIData data,
        const char* origin);

#endif /*CMPI_VER_200*/

} CMPIPropertyMIFT;

/**
 * @}
 * @addtogroup indication-mi
 * @{
 */

/**
 * @brief CMPIIndicationMI object.
 *
 * This object is provided by an indication MI through
 * @ref mi-factory "MI factory functions", in order to make its MI functions
 * available to the MB.
 */
typedef struct _CMPIIndicationMI {

    /**
     * @brief Opaque pointer to MB-specific implementation data for this MI
     *     object.
     */
    const void* hdl;

    /**
     * @brief Pointer to the function table for this MI object.
     */
    const CMPIIndicationMIFT* ft;

} CMPIIndicationMI;

/**
 * @brief Function table of CMPIIndicationMI object.
 */
typedef struct _CMPIIndicationMIFT {

    /**
     * @brief CMPI version supported by the MI for this function table.
     *
     * Any later CMPI versions are implicitly also supported.
     *
     * See @ref sym-version-nnn "CMPIVersion\<NNN\>" for valid CMPI
     * version numbers.
     */
    CMPIVersion ftVersion;

    /**
     * @brief Informal MI-specific version number for this MI.
     */
    int miVersion;

    /**
     * @brief Informal MI-specific name for this MI.
     */
    const char* miName;

    /**
     @brief Perform cleanup for an Indication MI.

     CMPIIndicationMIFT.cleanup() shall perform any necessary cleanup for the
     Indication MI identified by @p mi, unless the MI postpones the cleanup.

     While this function executes, the MB will not call any other MI functions
     for this MI. This function will be called once for a specific MI (unless
     the MI postpones the cleanup), even if that MI services more than one
     namespace. After this function returns, the MB may unload the load library
     this MI is part of, unless the MI postpones the cleanup.

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. The context data entries are MB
         implementation-specific.
     @param terminating
     @parblock
         Indicates whether the MB is in the process of shutting down and thus
         cannot tolerate postponing of the cleanup, as follows:

         When True, the MB is in the process of shutting down. The MI shall
         perform any necessary cleanup and shall not postpone the cleanup.
         After this function returns (successful or in error), the MB will
         consider this MI to be uninitialized and will not call further MI
         functions for this MI.

         When False, the MI can choose to perform or postpone the cleanup, by
         performing one of these actions:

         @li The MI performs any necessary cleanup and does not request
             postponing the cleanup. After this function returns (successful or
             in error), the MB will consider this MI to be uninitialized and
             will not call further MI functions for this MI.
         @li The MI does not perform any cleanup and temporarily postpones the
             cleanup, by returning `CMPI_RC_DO_NOT_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB may call this
             function again after some MB implementation-specific time.
         @li The MI does not perform any cleanup and permanently postpones the
             cleanup, by returning `CMPI_RC_NEVER_UNLOAD`. This will cause the
             MB to consider this MI still to be initialized, and the MB may
             call further MI functions of this MI. The MB will not call this
             function again until the MB terminates (at which time the MB calls
             this function with terminating set to true).
     @endparblock
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The following @ref CMPIrc codes shall be used by the MI in the
     function return status:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_DO_NOT_UNLOAD` - Function successful, do not unload now;
         the MB may retry an unload later.
     @li `CMPI_RC_NEVER_UNLOAD` - Function successful, never unload;
         the MB will not retry an unload later unless it shuts down.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @bug In the CMPI Standard document, add the sentence about the number of
         invocations relative to the number of namespaces serviced.
    */
    CMPIStatus (*cleanup) (CMPIIndicationMI* mi, const CMPIContext* ctx,
            CMPIBoolean terminating);

    /**
     @brief Verify whether an indication filter is supported by the MI.

     CMPIIndicationMIFT.authorizeFilter() shall verify whether an indication
     filter is supported by the MI.

     An MB implementation is free to choose whether this function is called
     when the MB starts up independently of whether or not there are any
     subscriptions for the filter, or only when the first subscription to the
     filter is made.

     In any case, for any particular filter this function is called on, it
     shall be called by the MB before CMPIIndicationMIFT.activateFilter() is
     called for the first time on the same filter.

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation. There is no defined client operation that
         determines the context data. As a result, not all context data entries
         may be present.
     @param filter Points to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is being verified.
     @param className Class name extracted from the FROM-clause of the filter
         specification contained in the filter argument. If the filter
         specification contains joins, it is undefined which of the joined
         classes is used for this argument.
     @param classPath Points to a CMPIObjectPath object that is a reference
         to a class or to a namespace, as follows:
         @li If the filter specification covers lifecycle indications, the
            CMPIObjectPath object specifies the class path of the class for
            which lifecycle monitoring is required. Note that this class may be
            a subclass of the class specified in @p className, for example when
            the filter query constrains the class to be monitored using
            constructs such as the `ISA` operator of CQL.
         @li If the filter specification covers process indications, the
            CMPIObjectPath object specifies the namespace path of the origin
            namespace of the process indications.
     @param owner Destination owner. (**Deprecated**)
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful, filter is supported.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized. Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter itself would not be authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Filter query is invalid or too complex.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @deprecated @p owner is deprecated since CMPI 2.1. MBs may pass an empty
         string in @p owner. For compatibility reasons, MBs shall not pass a
         NULL pointer in @p owner.

     @bug In the CMPI Standard document, change "Ask an MI to verify" to
     "Verify", in the short description.
    */
    CMPIStatus (*authorizeFilter) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPISelectExp* filter,
        const char* className, const CMPIObjectPath* classPath,
        const char* owner);

    /**
     @brief Ask the MI whether indication polling should be used for an
         indication filter. (**Deprecated**)

     CMPIIndicationMIFT.mustPoll() asks the MI whether indication polling
     should be used for an indication filter.

     This function enables very simple MIs to support indications without
     providing a complete indication support implementation. When true is
     returned, the MI indicates to the MB that it relies on indication polling
     for this indication filter. If the MB supports indication polling and the
     MI relies on indication polling, the MB will invoke appropriate instance
     MI functions at regular intervals, apply the specified indication filter
     and deliver any resulting indications.

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. There is no defined client operation that determines
         the context data. As a result, not all context data entries may be
         present.
     @param [out] rslt Points to a CMPIResult object used to return a
         @ref CMPIBoolean indicating whether indication polling should be used.
     @param filter Points to a CMPISelectExp object containing the filter
         specification defined by the indication filter for which this request
         is made.
     @param className Class name extracted from the FROM-clause of the filter
         specification contained in the filter argument. If the filter
         specification contains joins, it is undefined which of the joined
         classes is used for this argument.
     @param classPath Points to a CMPIObjectPath object that is a reference to a
         class or to a namespace, as follows:
         @li If the filter specification covers lifecycle indications, the
             CMPIObjectPath object specifies the class path of the class for
             which lifecycle monitoring is required. Note that this class may
             be a subclass of the class specified in @p className, for example
             when the filter query constrains the class to be monitored using
             constructs such as the `ISA` operator of CQL.
         @li If the filter specification covers process indications, the
             CMPIObjectPath object specifies the namespace path of the origin
             namespace of the process indications.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Invalid query or too complex.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @deprecated This function is deprecated since CMPI 2.1,
         because the concept of indication polling has been deprecated in
         CMPI 2.1.
     @incompatible210 In CMPI 2.1, the @p rslt argument was added to the
         declaration of this function in the header file, in order to get the
         header files consistent with the CMPI Standard document, which always
         had this argument documented. It is believed that this function could
         not have been used without that argument, and that users of the
         function would have added the argument already.
    */
    CMPIStatus (*mustPoll) (CMPIIndicationMI* mi, const CMPIContext* ctx,
        const CMPIResult* rslt, const CMPISelectExp* filter,
        const char* className, const CMPIObjectPath* classPath);

    /**
     @brief Informs the MI that an indication filter has become active.

     CMPIIndicationMIFT.activateFilter() informs the MI that the specified
     indication filter has become active. This function shall be called by the
     MB:
     @li when a client creates a subscription to an indication filter, and
     @li if persisted subscriptions are supported by the MB, for any persisted
         subscriptions to indication filters when the MB starts up.

     An MB implementation is free to choose whether this function is called
     upon each subscription to a particular filter, or only upon the first
     subscription (see @p firstActivation). As a result, the MI will always be
     informed about the first activation of the filter after having been
     inactive, but has no guarantee to be informed about subsequent activations
     of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI needs to start the monitoring of any resources that
     trigger indications that are covered by the specified indication filter,
     during the first activation of the filter. For the concept of coverage of
     indications by an indication filter, see @ref ref-dmtf-dsp1054 "DSP1054".

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. If the filter is activated because a client creates a
         subscription to the filter, the client operation that creates the
         subscription determines the context data. If the filter is activated
         during MB startup on behalf of a persisted earlier subscription, the
         client operation that originally created the subscription determines
         the context data.
     @param filter Points to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is activated.
     @param className class name extracted from the FROM-clause of the filter
         specification contained in @p filter. If the filter specification
         contains joins, it is undefined which of the joined classes is used
         for this argument.
     @param classPath Points to a CMPIObjectPath object that is a reference to a
         class or to a namespace, as follows:
         @li If the filter specification covers lifecycle indications, the
             CMPIObjectPath object specifies the class path of the class for
             which lifecycle monitoring is required. Note that this class may
             be a subclass of the class specified in @p className, for example
             when the filter query constrains the class to be monitored using
             constructs such as the `ISA` operator of CQL.
         @li If the filter specification covers process indications, the
             CMPIObjectPath object specifies the namespace path of the origin
             namespace of the process indications.
     @param firstActivation Set to true if this is the first activation of this
         indication filter after having been inactive, and is set to false
         otherwise.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized. Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter itself would not be authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Filter query is invalid or too complex.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @bug In the CMPI Standard document, use the list form from the header file
         for the description of the call triggers in the first paragraph.
    */
    CMPIStatus (*activateFilter) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPISelectExp* filter,
        const char* className, const CMPIObjectPath* classPath,
        CMPIBoolean firstActivation);

    /**
     @brief Informs the MI that an indication filter has become inactive.

     CMPIIndicationMIFT.deActivateFilter() informs the MI that the specified
     indication filter has become inactive. This function shall be called by
     the MB:
     @li when a client deletes a subscription to an indication filter, and
     @li for any existing subscriptions to indication filters, when the MB
         shuts down.

     An MB implementation is free to choose whether this function is called for
     each deletion of a subscription to a particular filter, or only upon the
     last deletion (see @p lastDeActivation). As a result, the MI will always
     be informed about the last deactivation of the filter, but has no
     guarantee to be informed about prior deactivations of the same filter.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI should stop the monitoring of any resources that trigger
     indications that are covered by the specified indication filter, during
     the last deactivation of the filter. For the concept of coverage of
     indications by an indication filter, see @ref ref-dmtf-dsp1054 "DSP1054".

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data
         for the invocation. If the filter is deactivated because a client
         deletes a subscription to the filter, the client operation that
         deletes the subscription determines the context data. If the filter is
         deactivated during MB shutdown, the client operation that originally
         created the subscription determines the context data.
     @param filter Points to a CMPISelectExp object containing the filter
         specification defined by the indication filter that is deactivated.
     @param className Class name extracted from the FROM-clause of the filter
         specification contained in the @p filter argument. If the filter
         specification contains joins, it is undefined which of the joined
         classes is used for this argument.
     @param classPath Points to a CMPIObjectPath object is a reference to a
         class or to a namespace, as follows:
         @li If the filter specification covers lifecycle indications, the
             CMPIObjectPath object specifies the class path of the class for
             which lifecycle monitoring is required.  Note that this class may
             be a subclass of the class specified in @p className, for example
             when the filter query constrains the class to be monitored using
             constructs such as the `ISA` operator of CQL.
         @li If the filter specification covers process indications, the
             CMPIObjectPath object specifies the namespace path of the origin
             namespace of the process indications.
     @param lastDeActiviation Set to true if this is the last deactivation of
         this indication filter after having been active, and is set to false
         otherwise.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized.
     @li `CMPI_RC_ERR_INVALID_QUERY` - Filter query is invalid or too complex.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @bug In the CMPI Standard document, fix the incorrect name of the
         lastDeActivation argument (is lastActivation in the document).

     @bug In the CMPI Standard document, use the list form from the header file
        for the description of the call triggers in the first paragraph.
    */
    CMPIStatus (*deActivateFilter) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPISelectExp* filter,
        const char* className, const CMPIObjectPath* classPath,
        CMPIBoolean lastDeActiviation);

    /**
     @brief Informs the MI that the MB is now ready to process the delivery of
         indications.

     CMPIIndicationMIFT.enableIndications() informs the MI that the MB is now
     ready to process the delivery of indications. This function is typically
     called when the MB is starting up its indication services (from either a
     permanent or temporary shutdown of its indication services).

     The relative order in which an MB enables indications using this function
     and activates filters and filter collections is not defined. As a result,
     MIs need to track the readiness of the MB to process the delivery of
     indications and check that readiness before calling @ref
     CMPIBrokerFT.deliverIndication().

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. There is no defined client operation that determines
         the context data. As a result, not all context data entries may be
         present.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @convfunction CMIndicationMIStub()
    */
    CMPIStatus (*enableIndications) (CMPIIndicationMI* mi,
        const CMPIContext* ctx);

    /**
     @brief Informs the MI that the MB is no longer ready to process the
         delivery of indications.

     CMPIIndicationMIFT.disableIndications() informs the MI that the MB is no
     longer ready to process the delivery of indications.  This function is
     typically called when the MB is shutting down its indication services
     either temporarily or permanently.

     The relative order in which an MB disables indications using this function
     and deactivates filters and filter collections is not defined. As a
     result, MIs need to track the readiness of the MB to process the delivery
     of indications and check that readiness before calling @ref
     CMPIBrokerFT.deliverIndication().

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. There is no defined client operation that determines
         the context data. As a result, not all context data entries may be
         present.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.
     @convfunction CMIndicationMIStub()
    */
    CMPIStatus (*disableIndications) (CMPIIndicationMI* mi,
        const CMPIContext* ctx);

    /**
     @brief Verify whether an indication filter collection is supported by the
         MI.

     CMPIIndicationMIFT.authorizeFilterCollection() shall verify whether an
     indication filter collection is supported by the MI.

     An MB implementation is free to choose whether this function is called
     when the MB starts up independently of whether or not there are any
     subscriptions for the filter collection, or only when the first
     subscription to the filter collection is made.

     In any case, for any particular filter collection this function is called
     on, it shall be called by the MB before
     CMPIIndicationMIFT.activateFilterCollection() is called for the first time
     on the same filter collection.

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. There is no defined client operation that determines
         the context data. As a result, not all context data entries may be
         present.
     @param collInst Points to a CMPIInstance object with the
         `CIM_FilterCollection` instance representing the indication filter
         collection. Note that the indication filter collection can be
         identified by inspecting the `CollectionName` property of this
         instance.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful, filter collection is supported
         by the MI.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter collection is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized. Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter collection itself would not be
         authorized.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid indication filter
         collection.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @added210 Added in CMPI 2.1.

     @bug In the CMPI Standard document, change "Ask an MI to verify" to
     "Verify", in the short description.

     @bug In the CMPI Standard document, use the list form from the header file
        for the description of the call triggers in the first paragraph.
    */
    CMPIStatus (*authorizeFilterCollection) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPIInstance* collInst);

    /**
     @brief Informs the MI that an indication filter collection has become
         active.

     CMPIIndicationMIFT.activateFilterCollection() informs the MI that the
     specified indication filter collection has become active. This function
     shall be called by the MB:
     @li when a client creates a subscription to an indication filter
         collection, and
     @li if persisted subscriptions are supported by the MB, for any persisted
         subscriptions to indication filter collections when the MB starts up.

     An MB implementation is free to choose whether this function is called
     upon each subscription to a particular filter collection, or only upon the
     first subscription (see @p firstActivation).

     As a result, the MI will always be informed about the first activation of
     the filter collection, but has no guarantee to be informed about
     subsequent activations of the same filter collection.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI needs to start the monitoring of any resources that
     trigger indications that are covered by the specified indication filter
     collection, during the first activation of the filter collection. For the
     concept of coverage of indications by an indication filter collection, see
     @ref ref-dmtf-dsp1054 "DSP1054".

     As described in @ref ref-dmtf-dsp1054 "DSP1054", a filter collection
     conceptually has members, but these members do not need to be instantiated
     using CIM. An MB shall handle subscriptions to a filter collection by
     calling CMPIIndicationMIFT.activateFilterCollection() for that filter
     collection; the MB shall not additionally call the activation functions
     for the individual members of the filter collection. The implementation of
     CMPIIndicationMIFT.activateFilterCollection() is responsible for
     activating the entire filter collection including all of its members
     (regardless of whether or not these members are instantiated using CIM).

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. If the filter collection is activated because a client
         creates a subscription to the filter collection, the client operation
         that creates the subscription determines the context data. If the
         filter collection is activated during MB startup on behalf of a
         persisted earlier subscription, the client operation that originally
         created the subscription determines the context data.
     @param collInst Points to a CMPIInstance object with the
         `CIM_FilterCollection` instance representing the indication filter
         collection. Note that the indication filter collection can be
         identified by inspecting the `CollectionName` property of this
         instance.
     @param firstActivation Set to true if this is the first activation of this
         indication filter collection after having been inactive, and is set to
         false otherwise
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter collection is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized. Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter collection itself would not be
         authorized.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid indication filter collection.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @added210 Added in CMPI 2.1.
    */
    CMPIStatus (*activateFilterCollection) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPIInstance* collInst,
        CMPIBoolean firstActivation);

    /**
     @brief Informs the MI that an indication filter collection has become
         inactive.

     CMPIIndicationMIFT.deActivateFilterCollection() informs the MI that the
     specified indication filter collection has become inactive. This function
     shall be called by the MB:
     @li when a client deletes a subscription to an indication filter
         collection, and
     @li for any existing subscriptions to indication filter collections when
         the MB shuts down.

     This function is called either when a client deletes a subscription to an
     indication filter collection, or when the MB shuts down and deactivates a
     subscription.

     An MB implementation is free to choose whether this function is called
     upon each deletion of a subscription to a particular filter collection, or
     only upon the last deletion (see @p lastDeActivation). As a result, the MI
     will always be informed about the last deactivation of the filter
     collection, but has no guarantee to be informed about prior deactivations
     of the same filter collection.

     Generally, MIs should disable the monitoring of any resources for
     indications if there is no interest in them. Consequently, in this
     function the MI should stop the monitoring of any resources that trigger
     indications that are covered by the specified indication filter
     collection, during the last deactivation of the filter. For the concept of
     coverage of indications by an indication filter collection, see @ref
     ref-dmtf-dsp1054 "DSP1054".

     As described in @ref ref-dmtf-dsp1054 "DSP1054", a filter collection
     conceptually has members, but these members do not need to be instantiated
     using CIM. An MB shall handle deletions to subscriptions to a filter
     collection by calling CMPIIndicationMIFT.deActivateFilterCollection() for
     that filter collection; the MB shall not additionally call the
     deactivation functions for the individual members of the filter
     collection. The implementation of
     CMPIIndicationMIFT.deActivateFilterCollection() is responsible for
     deactivating the entire filter collection including all of its members
     (regardless of whether or not these members are instantiated using CIM).

     @param mi Points to a CMPIIndicationMI structure.
     @param ctx Points to a CMPIContext object containing the context data for
         the invocation. If the filter collection is activated because a client
         creates a subscription to the filter collection, the client operation
         that creates the subscription determines the context data. If the
         filter collection is activated during MB startup on behalf of a
         persisted earlier subscription, the client operation that originally
         created the subscription determines the context data.
     @param collInst Points to a CMPIInstance object with the
         `CIM_FilterCollection` instance representing the indication filter
         collection. Note that the indication filter collection can be
         identified by inspecting the `CollectionName` property of this
         instance.
     @param lastDeActivation Set to true if this is the last deactivation of
         this indication filter collection after having been active; set to
         false otherwise.
     @return CMPIStatus structure containing the function return status.

     @par Errors
     The function return status will indicate one of the following @ref CMPIrc
     codes:
     @li `CMPI_RC_OK` - Function successful.
     @li `CMPI_RC_ERR_NOT_SUPPORTED` - Function is not supported by this MI, or
         filter collection is not supported by this MI.
     @li `CMPI_RC_ERR_ACCESS_DENIED` - Not authorized. Note: This return code
         indicates general authorization related issues and does not
         specifically indicate that the filter collection itself would not be
         authorized.
     @li `CMPI_RC_ERR_INVALID_PARAMETER` - Invalid indication filter collection.
     @li `CMPI_RC_ERR_FAILED` - Other error occurred.

     @convfunction CMIndicationMIStub()
     @added210 Added in CMPI 2.1.

     @bug In the CMPI Standard document, use the list form from the header file
        for the description of the call triggers in the first paragraph.
    */
    CMPIStatus (*deActivateFilterCollection) (CMPIIndicationMI* mi,
        const CMPIContext* ctx, const CMPIInstance* collInst,
        CMPIBoolean lastDeActivation);

} CMPIIndicationMIFT;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /*_CMPIFT_H_ */
