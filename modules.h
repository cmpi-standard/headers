/* ------------------------------------------------------------------------- */
/* Dummy header file defining the module structure for Doxygen               */
/* ------------------------------------------------------------------------- */

/**
@defgroup symbols Preprocessor Symbols
@{
  @todo TBD(DONE): Should we keep the `defgroup` statements (which are used
      to define
      the order of groups, e.g. in the Modules tab) in the `cmpidt.h` header
      file or move them to the `mainpage.md` file? One difficulty when moving
      is the conditional definition of the group section for
      CMPISelectCondType, which depends on the CMPI_DEFINE_CMPISelectCondType
      symbol. Andy: Solved, by moving defgroup stmts to new modules.h file.
      That also solves the onditional definition issue.
  @defgroup symbols-versioning Symbols related to CMPI versioning
  @{
    @defgroup sym-version-nnn CMPIVersion{NNN}
    @{
      @brief These symbols encapsulate the values for the numeric CMPI
      version numbers
      Note: Historical CMPI levels (before the first CMPI Standard, e.g.
      86, 90) are not supported by this header file.
      @todo TBD: The description of CMPIVersion{NNN} is in its `defgroup`
          statement, which causes the "Modules" tab to show its brief
          description in a second column.
          The description of CMPICurrentVersion is where its symbol
          definition is, i.e. within an `addtogroup` statement. That causes
          the "Modules" tab not to show its brief description; however
          the description needs to be there, otherwise the references to
          the symbol (via its group name) do not work.
          So we cannot have both the references work and the brief
          description showing up in the "Modules" tab. Should we leave
          it inconsistent or remove the brief description anywhere?
    @}
    @defgroup sym-current-version CMPICurrentVersion
    @{
    @}
    @defgroup sym-version CMPI_VERSION
    @{
    @}
    @defgroup sym-ver-nnn CMPI_VER_{NNN}
    @{
      @brief Boolean flags for testing whether CMPI version dependent
      features should be available, given the implemented version

      The term 'available' as used here means that the feature is defined in
      the header files and subsequently can be supported in the MB or MI
      implementation.

      A symbol for a particular version (e.g. CMPI_VER_200) is defined if its
      version is lower than or equal to the CMPI version that is implemented
      (as indicated by @ref CMPI_VERSION). Otherwise, it is undefined.

      This allows a feature that was introduced in a particular CMPI version
      to be defined like in the following example:

        <pre>
        #ifdef CMPI_VER_200
        // definition of feature that was added in CMPI 2.0.0
        #endif
        </pre>
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
    @defgroup type-accessor CMPIAccessor
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
  @defgroup type-error-type CMPIErrorType (Extended Error Types) (Subclause 5.12)
  @{
  @}
  @defgroup type-error-severity CMPIErrorSeverity (Extended Error Severity Levels) (Subclause 5.13)
  @{
  @}
  @defgroup type-error-probable-cause CMPIErrorProbableCause (Extended Error Probable Causes) (Subclause 5.14)
  @{
  @}
  @defgroup type-error-src-format CMPIErrorSrcFormat (Extended Error Source Formats) (Subclause 5.15)
  @{
  @}
  @defgroup type-flags CMPIFlags (Subclause 5.16)
  @{
  @}
@}
@defgroup mi-functions MI Functions (Subclause 6)
@{
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
  @defgroup brokerext-lib OS Encapsulation Services - Library Resolution (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-thread OS Encapsulation Services - POSIX-conformant Threads (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-mutex OS Encapsulation Services - POSIX-conformant Mutexes (Subclause 9.14)
  @{
  @}
  @defgroup brokerext-condition OS Encapsulation Services - POSIX-conformant Conditions (Subclause 9.14)
  @{
  @}
  @defgroup brokermem-all Memory Enhancement Services (Subclause 9.15)
  @{
  @}
@}
@todo can we get these descriptions within the 80 column
      rule.
*/
