/* ------------------------------------------------------------------------- */
/* Dummy header file defining the module structure for Doxygen               */
/* ------------------------------------------------------------------------- */

/**
 * @file modules.h
 * @brief A dummy header file defining the module structure for Doxygen; it is
 *     not part of the CMPI header files.
 *
 * @todo AM: modules.h shows up in file list of HTML output (Files tab).
 */

/**
 * @page added200 Added in CMPI 2.0.0
 * @brief Entities that were added in CMPI 2.0.0
 */

/**
 * @page added210 Added in CMPI 2.1.0
 * @brief Entities that were added in CMPI 2.1.0
 */

/**
 * @page required200 Required since CMPI 2.0.0
 * @brief Entities that are required to be supported since CMPI 2.0.0
 */

/**
 * @page required210 Required since CMPI 2.1.0
 * @brief Entities that are required to be supported since CMPI 2.1.0
 */

/**
 * @page capread Basic Read capability
 * @brief Entities that are part of the Basic Read capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_BasicRead "Basic Read" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capwrite Basic Write capability
 * @brief Entities that are part of the Basic Write capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_BasicWrite "Basic Write" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capmanipulation Instance Manipulation capability
 * @brief Entities that are part of the Instance Manipulation capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_InstanceManipulation "Instance Manipulation" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capassociations Association Traversal capability
 * @brief Entities that are part of the Association Traversal capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_AssociationTraversal "Association Traversal" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capqueryexec Query Execution capability
 * @brief Entities that are part of the Query Execution capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_QueryExecution "Query Execution" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capquerynorm Query Normalization capability
 * @brief Entities that are part of the Query Normalization capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_QueryNormalization "Query Normalization" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capqualifiers Basic Qualifier capability
 * @brief Entities that are part of the Basic Qualifier capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_BasicQualifierSupport "Basic Qualifier" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capindications Indications capability
 * @brief Entities that are part of the Indications capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_Indications "Indications" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capopsys OS Encapsulation Services capability
 * @brief Entities that are part of the OS Encapsulation Services capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_OSEncapsulationSupport "OS Encapsulation Services" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capmemory Memory Enhancement Services capability
 * @brief Entities that are part of the Memory Enhancement Services MB
 *     Capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_Supports_MemEnhancements "Memory Enhancement Services" MB
 * capability is available; otherwise, they shall not be supported.
 */

/**
 * @page caperrors Extended Errors capability
 * @brief Entities that are part of the Extended Errors capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_Supports_Extended_Error "Extended Errors" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page caplogging Logging capability
 * @brief Entities that are part of the Logging capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_Logging "Logging" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page captracing Tracing capability
 * @brief Entities that are part of the Tracing capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_Tracing "Tracing" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capfiltering Property Filtering capability
 * @brief Entities that are part of the Property Filtering capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_PropertyFiltering "Property Filtering" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page capcodepage Codepage Conversion capability
 * @brief Entities that are part of the Codepage Conversion capability
 *
 * These entities shall be supported, if the
 * @ref CMPI_MB_CodepageConversion "Codepage Conversion" capability
 * is available; otherwise, they shall not be supported.
 */

/**
 * @page captranslation Message Translation capability
 * @anchor cap-translation
 * @brief Entities that are part of the Message Translation capability
 *
 * Optional to be supported.
 *
 * Support for the Message Translation capability cannot be discovered by
 * means of CMPIBrokerFT.brokerCapabilities. The functions that are part of
 * this capability perform a default behavior if the Message Translation MB
 * capability is not supported.
 */

/**
 * @page capcontext Context Data capability
 * @anchor cap-context
 * @brief Entities that are part of the Context Data capability
 *
 * Required to be supported.
 *
 * Support for the Context Data capability cannot be discovered by
 * means of CMPIBrokerFT.brokerCapabilities.
 *
 * @required210 Support for this capability is required since CMPI 2.1.0.
 */

/**
 * @page platformspecific Platform-specific Definitions
 * @brief Definitions that depend on the compile platform
 *
 * Some definitions in the CMPI header files depend on the specified platform
 * (see @ref sym-platform).
 *
 * This online documentation is generated for the platform
 * CMPI_PLATFORM_LINUX_GENERIC_GNU.
 *
 * Platform dependencies are mentioned where applicable, but those descriptions
 * may not be fully specific as to what the exact changes for each platform are.
 * For details, the respective CMPI header file needs to be examined.
 */

/**
 * @page cxxspecific C/C++-specific Definitions
 * @brief Definitions that depend on compiling for C vs. C++
 *
 * Some definitions in the CMPI header files depend on whether they are compiled
 * for C or for C++.
 *
 * The code shown in this online documentation is for C++.
 *
 * Such dependencies are mentioned where applicable, but those descriptions
 * may not be fully specific as to what the exact changes are.
 * For details, the respective CMPI header file needs to be examined.
 */

/**
@defgroup symbols Preprocessor Symbols
@{
  @defgroup symbols-user Symbols definable by the CMPI user
  @{
    These symbols can be defined by the user of the CMPI header files.

    @defgroup sym-version CMPI_VERSION
    @{
      @brief CMPI version that is implemented.
    @}
  @}
  @defgroup symbols-versioning Symbols related to CMPI versioning
  @{
    @defgroup sym-version-nnn CMPIVersion{NNN}
    @{
      @brief Numeric CMPI version numbers.

      Note: Historical CMPI levels (before the first CMPI Standard, e.g.
      86, 90) are not supported by this header file.
    @}
    @defgroup sym-current-version CMPICurrentVersion
    @{
      @brief Current CMPI version of the header files.
    @}
    @defgroup sym-ver-nnn CMPI_VER_{NNN}
    @{
      @brief Tests for CMPI version dependent features.

      These symbols are used by the CMPI headers and can be used by MB or MI
      implementations supporting multiple CMPI versions, to test whether CMPI
      version dependent features should be made available, given the
      implemented version defined by @ref CMPI_VERSION.

      The term *available* as used here means that the feature is defined in
      the header files and subsequently can be supported in the MB or MI
      implementation.

      A symbol for a particular version (e.g. @ref CMPI_VER_200) is defined if
      its version is lower than or equal to the CMPI version that is implemented
      (as indicated by @ref CMPI_VERSION). Otherwise, it is undefined.

      This allows a feature that was introduced in a particular CMPI version
      to be defined like in the following example:

<pre>
\#ifdef CMPI_VER_200
// definition or use of feature that was added in CMPI 2.0.0
\#endif
</pre>
    @}
  @}
  @defgroup symbols-os-encaps Symbols related to OS Encapsulation Services
  @{
    @defgroup sym-thread-type CMPI_THREAD_TYPE
    @{
    @}
    @defgroup sym-thread-return CMPI_THREAD_RETURN
    @{
    @}
    @defgroup sym-thread-cdecl CMPI_THREAD_CDECL
    @{
    @}
    @defgroup sym-thread-key-type CMPI_THREAD_KEY_TYPE
    @{
    @}
    @defgroup sym-mutex-type CMPI_MUTEX_TYPE
    @{
    @}
    @defgroup sym-cond-type CMPI_COND_TYPE
    @{
    @}
  @}
  @defgroup symbols-export-import Symbols for exporting and importing symbols
  @{
    @defgroup sym-export CMPI_EXPORT
    @{
    @}
    @defgroup sym-import CMPI_IMPORT
    @{
    @}
    @defgroup sym-extern-c CMPI_EXTERN_C
    @{
    @}
  @}
@}
@defgroup data-types Data Types (Subclause 5)
@{
  @defgroup type-codepage-id Codepage Conversion (Subclause 5.2.2)
  @{
  @}
  @defgroup types-cim-types C Data Types for CIM Data Types (Subclause 5.4)
  @{
  @}
  @defgroup types-misc CMPI Miscellaneous Data Types (Subclause 5.5)
  @{
    @defgroup type-valueptr CMPIValuePtr
    @{
    @}
*/
#ifdef CMPI_DEFINE_CMPISelectCondType
/**
    @defgroup type-select-cond-type CMPISelectCondType
    @{
    @}
*/
#endif
/**
  @}
  @defgroup types-data-items CMPI Data Items (Subclause 5.6)
  @{
    @defgroup type-data CMPIData
    @{
    @}
    @defgroup type-type CMPIType
    @{
    @}
    @defgroup type-value-state CMPIValueState
    @{
    @}
    @defgroup type-value CMPIValue
    @{
    @}
    @defgroup type-pred-op CMPIPredOp
    @{
    @}
    @defgroup type-count CMPICount
    @{
    @}
    @defgroup type-msg-file-handle CMPIMsgFileHandle
    @{
    @}
    @defgroup type-gc-stat CMPIGcStat
    @{
    @}
    @defgroup type-version CMPIVersion
    @{
    @}
  @}
  @defgroup type-status CMPIStatus (Subclause 5.8)
  @{
  @}
  @defgroup type-rc CMPIRc (Return Codes) (Subclause 5.9)
  @{
  @}
  @defgroup type-severity CMPISeverity (Severity Codes) (Subclause 5.10)
  @{
  @}
  @defgroup type-level CMPILevel (Trace Levels) (Subclause 5.11)
  @{
  @}
  @defgroup type-error-type CMPIErrorType (Extended Error Types) \
    (Subclause 5.12)
  @{
  @}
  @defgroup type-error-severity CMPIErrorSeverity (Extended Error Severity \
    Levels) (Subclause 5.13)
  @{
  @}
  @defgroup type-error-probable-cause CMPIErrorProbableCause (Extended Error \
    Probable Causes) (Subclause 5.14)
  @{
  @}
  @defgroup type-error-src-format CMPIErrorSrcFormat (Extended Error Source \
    Formats) (Subclause 5.15)
  @{
  @}
  @defgroup type-flags CMPIFlags (Subclause 5.16)
  @{
  @}
@}
@defgroup mi-functions MI Functions (Subclause 6)
@{
  @defgroup mi-factory MI Factory Functions (Subclause 6.2)
  @{
  @}
  @defgroup instance-mi Instance MI Functions (Subclause 6.3)
  @{
  @}
  @defgroup association-mi Association MI Functions (Subclause 6.4)
  @{
  @}
  @defgroup method-mi Method MI Functions (Subclause 6.5)
  @{
  @}
  @defgroup indication-mi Indication MI support (Subclause 6.6)
  @{
  @}
  @defgroup property-mi Property MI functions (Subclause 6.7) (Deprecated)
  @{
  @}
@}
@defgroup mb-capabilities MB Capabilities (Subclause 7.1)
@{
@}
@defgroup mb-edt MB Encapsulated Data Type Support (Subclause 8)
@{
  @defgroup edt-context CMPIContext Support (Subclause 8.1)
  @{
    @defgroup def-context-fieldnames Names of CMPIContext fields
    @{
    @}
  @}
  @defgroup edt-result CMPIResult Support (Subclause 8.2)
  @{
  @}
  @defgroup edt-string CMPIString Support (Subclause 8.3)
  @{
  @}
  @defgroup edt-array CMPIArray Support (Subclause 8.4)
  @{
  @}
  @defgroup edt-enumeration CMPIEnumeration Support (Subclause 8.5)
  @{
  @}
  @defgroup edt-instance CMPIInstance Support (Subclause 8.6)
  @{
  @}
  @defgroup edt-objectpath CMPIObjectPath Support (Subclause 8.7)
  @{
  @}
  @defgroup edt-args CMPIArgs Support (Subclause 8.8)
  @{
  @}
  @defgroup edt-datetime CMPIDateTime Support (Subclause 8.9)
  @{
  @}
  @defgroup edt-selectexp CMPISelectExp Support (Subclause 8.10)
  @{
  @}
  @defgroup edt-selectcond CMPISelectCond Support (Subclause 8.11)
  @{
  @}
  @defgroup edt-subcond CMPISubCond Support (Subclause 8.12)
  @{
  @}
  @defgroup edt-predicate CMPIPredicate Support (Subclause 8.13)
  @{
  @}
  @defgroup edt-error CMPIError Support (Subclause 8.14)
  @{
  @}
  @defgroup edt-propertylist CMPIPropertyList Support (Subclause 8.15)
  @{
  @}
  @defgroup edt-enumerationfilter CMPIEnumerationFilter Support (Subclause 8.16)
  @{
  @}
@}
@defgroup mb-services MB Services (Subclause 9)
@{
  @defgroup brokerenc-factory Factory Services (Subclause 9.1)
  @{
  @}
  @defgroup brokerenc-misc Miscellaneous Services (Subclause 9.1)
  @{
  @}
  @defgroup mb-tables CMPIBroker and its MB Function Tables (Subclause 9.2)
  @{
  @}
  @defgroup broker-indications Indications Services (Subclause 9.3)
  @{
  @}
  @defgroup broker-client Client Services ("up-calls") (Subclause 9.4 - 9.11)
  @{
  @}
  @defgroup qualifier-services Qualifier Services (Subclause 9.12)
  @{
  @}
  @defgroup broker-thread-reg Thread Registration Services (Subclause 9.13)
  @{
  @}
  @defgroup brokerext-lib OS Encapsulation Services - Library Resolution \
    (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-thread OS Encapsulation Services - POSIX-conformant \
    Threads (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-mutex OS Encapsulation Services - POSIX-conformant \
    Mutexes (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-condition OS Encapsulation Services - POSIX-conformant \
    Conditions (Subclause 9.14)
  @{
  @}
  @defgroup brokermem-all Memory Enhancement Services (Subclause 9.15)
  @{
  @}
@}
@defgroup cmpi-conviencefunc CMPI Convience functions
@{
   @defgroup cmpi-function-supplements Inline functions that supplement \
       function calls.
   @{
   The inline functions in this group supplement the functions defined in the
   specification, for example, adding a function that creates status and does
   a return in a single call

   They aid the access to cmpi selected variables or otherwise provide
   functionality not directly available through a function. Examples of
   this are CMReturn() andCMIsNull()
   @}
   @defgroup cmpi-conv-func-calls Convience functions that directly map to \
   cmpi specified functions.
   @{
   These macros simplify the code by eliminating the direct
   reference to the function table. Every convience function in this group
   directly maps to a cmpi function.
   @}
   @defgroup cmpi-providerfactories Provider Stub CreationFactories.
   @{
   @}
@}
*/
