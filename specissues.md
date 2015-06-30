Changes during finalization of the CMPI specification
=====================================================

1. Global change of "CMPIBroker object" to "CMPIBroker structure".
   The former occurs 15 times, the latter already 52 times.

   Already done in header files.

2. The description fix mentioned on the mailing list (TBD: Provide details).

3. In prepareAttachThread(), we wanted to remove the error codes, but failed to
   apply the CR correctly.

   Replace the content of the ERRORS section with:

   "For historical reasons, no additional error information is passed back."

   Already done in header files.

4. In CMPIBrokerFT.enumerateInstanceNames(), the deprecation note for return
   code CMPI_RC_ERR_NOT_FOUND mentiones a source instance, which is a term we
   use for association calls but not for enumeration calls:

   "Instead of using this return code if the source instance does not exist,..."

   Replace with:

   "Instead of using this return code if no instances exist,..."

   Already done in header files.

5. The entries of CMPIContext are referenced inconsistently:

   The description of CMPIContext pointer arguments in any MI or MB functions
   uses:
     * CMPIInitNameSpace entry
     * invocation flags, CMPIInvocationFlags entry
     * principal
     * role
     * accept language
     * content language

   The description of the entries uses:
     * name of the target namespace for the invoked operation
     * invocation flags for the invoked operation
     * authenticated ID of the user requesting the invoked operation
     * role assumed by the current authenticated user
     * preferred language(s) to be used by the MI for any language-specific
       data in any results from MI functions
     * language(s) used by the MB for any language-specific data passed to MI functions

   Need to figure out a consistent terminology.

   Need to apply the result to the header files.

6. The CMPIBrokerFT table was not extended to add the three new pulled up-calls:

     * CMPIBrokerFT.enumerateInstancesFiltered()
     * CMPIBrokerFT.associatorsFiltered()
     * CMPIBrokerFT.referencesFiltered()

   Add the respective function pointers to the end of the table, in this order.

   Already done in header files. Double check order between header file and
   spec.

7. The list of return codes documented for the up-call
   CMPIBrokerFT.enumerateInstancesFiltered() has these issues:

   a) The up-call seems to be missing these return codes, which handle errors
      in its arguments:

      * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in classPath
        does not exist.
      * CMPI_RC_ERR_INVALID_CLASS - The class specified in classPath does not
        exist.
      * CMPI_RC_ERR_INVALID_PARAMETER - The property list specified in
        properties is invalid.

      It seems we need to add those to the up-call.
      
   b) The corresponding MI function (CMPIInstanceMIFT.enumerateInstancesFiltered())
      has return codes for which the following direct equivalents are missing
      in this up-call:
      
      * CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED - Limits exceeded.

      The MI function of the MI targeted by the up-call could return these,
      and the MB would have the difficulty of not being able to return these
      in the up-call.

      It seems we need to add those to the up-call.

   c) The CMPI_RC_ERR_NOT_FOUND return code is defined in this up-call.

      In the corresponding non-pulled up-call (CMPIBrokerFT.enumerateInstances()),
      this return code is defined but deprecated.

      In the corresponding MI function (CMPIInstanceMIFT.enumerateInstancesFiltered()),
      this return code had not been defined in the first place.

      It seems we need to remove this return code from the up-call.

   Review, to make sure.
   If possible, compare with implementations.

   Need to apply the result to the header files.

8. The list of return codes documented for
   CMPIBrokerFT.associatorsFiltered() seems to be missing these:

     * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath does
       not exist.
     * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath does not
       exist.
     * CMPI_RC_ERR_INVALID_PARAMETER - The assocClass, resultClass, role,
       resultRole, or properties arguments are invalid.

   Review, to make sure.
   If possible, compare with implementations.

   Need to apply the result to the header files.

9. The list of return codes documented for
   CMPIBrokerFT.referencesFiltered() seems to be missing these:

     * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath does
       not exist.
     * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath does not
       exist.
     * CMPI_RC_ERR_INVALID_PARAMETER - The resultClass, role, or properties
       arguments are invalid.

   Review, to make sure.
   If possible, compare with implementations.

   Need to apply the result to the header files.

10. Incorrect use of "shall" for MB functions.

   The spec is generally written from an MI perspective, i.e. it uses
   normative requirements language ("shall", "should") when it comes to
   requirements against the MI, and it uses "will" or factual statements (e.g.
   "returns") when it comes to requirements against the MB.

   That concept is not followed entirely throughout the spec, and deviations
   are usually where normative requirements language is also used for the MB.

   The following places should be updated to change "shall" to "will":
   
   * "If no such instances are found, the function shall return success with
     an empty enumeration", in CMPIBrokerFT.enumerateInstancesFiltered(),
     CMPIBrokerFT.associatorsFiltered(), and
     CMPIBrokerFT.referencesFiltered().

   Already done in header files.

11. The short description of the filtered association up-calls refers to just
    one filter "filterQuery", when they actually have the usual association
    filters as well.

    This applies to CMPIBrokerFT.associatorsFiltered() and
    CMPIBrokerFT.referencesFiltered(), and only to their short descriptions.

    Change:

    "... returning only those that match the filterQuery argument"

    To:

    "... returning only those that match the given filters"

    In the first sentence of the long description of these functions,
    change its end from "the filter." to "the filters."

    Already done in header files.

11. The short description of CMPIBrokerFT.enumerateInstancesFiltered(),
    refers specifically to "filterQuery". It would be consistent with the
    previous issue to generalize this as well, so that the argument name
    is not mentioned in the short description.
    
    Change:

    "... returning only those that match the filterQuery argument"

    To:

    "... returning only those that match the given query filter"

    Already done in header files.

12. Terminology inconsistency in CMPIStatus return value:

    Change (3 occurrences):

    "A CMPIStatus structure containing the function return status ..."

    To (already 84 occurences):

    "A CMPIStatus structure indicating the function return status ..."

    Already done in header files.

13. In CMPIPredicateFT.getData(), the name of the
    "CMPIPredicate* pr" argument is referred to as "sc" in the description of
    the CMPI_RC_ERR_INVALID_HANDLE return code.

    Should be changed to "pr".

    Already done in header files.

14. In CMPIPredicateFT.evaluateUsingAccessor(), the name of the
    "CMPIPredicate* pr" argument is referred to as "se" in the description of
    the CMPI_RC_ERR_INVALID_HANDLE return code.

    Should be changed to "pr".

    Already done in header files.

