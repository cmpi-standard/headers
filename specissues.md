Changes during finalization of the CMPI specification
=====================================================

These are proposals for spec changes that will be voted in the CMPI WG,
and will be brought forward as review comments to the TOG review of the spec.

1.  Terminology inconsistency between "CMPIBroker object" and
    "CMPIBroker structure". The former occurs 15 times, the latter occurs
    52 times.

    Proposal: Change all occurrences of "CMPIBroker object" to
    "CMPIBroker structure", throughout the entire spec document.

    Already done in header files.

2.  In CMPIObjectPathFT.getKeyAt(), the description for the "name" output
    argument misses one level of pointer indirection.

    Proposal: Change the first sentence in the description of the "name"
    argument of that function
    from:

    "The name output argument points to a CMPIString object that upon success
     will have been updated with the name of the key binding."

    to:

    "The name output argument, if not NULL, points to a CMPIString pointer
     that upon success will have been updated to point to a CMPIString object
     containing the name of the key binding."

    Already done in header files.

3.  In CMPIObjectPathFT.getKey() and CMPIObjectPathFT.getKeyAt():

    Their "RETURN VALUE" section has a paragraph "If successful, ...",
    followed by a paragraph "If not successful", followed by remaining
    paragraphs. The remaining paragraphs are meant to apply only to the
    successful case, but given their location after the paragraph about the
    not successful case, they can easily be misunderstood to apply to
    both cases, or even to just the not successful case.

    Proposal: Move the paragraph "If not successful, ..." to the end of the
    "RETURN VALUE" section.

    Already done in header files.

4.  In CMPIBrokerFT.prepareAttachThread(), there are return codes documented,
    but the function has no means to return return codes.

    Our original CR during spec development proposed to remove the return
    codes, but we apparently failed to correctly apply that part of the CR to
    the spec during the spec development cycle.

    Proposal: Replace the content of the ERRORS section of
    CMPIBrokerFT.prepareAttachThread() with this sentence:

    "For historical reasons, no additional error information is passed back."

    Already done in header files.

5.  In CMPIBrokerFT.enumerateInstanceNames(), the deprecation note for return
    code CMPI_RC_ERR_NOT_FOUND mentions a "source instance", which is a term we
    use for association calls but not for enumeration calls.

    Proposal: Change the description of return code CMPI_RC_ERR_NOT_FOUND in
    CMPIBrokerFT.enumerateInstanceNames() from:

    "Instead of using this return code if the source instance does not exist,..."

    To:

    "Instead of using this return code if no instances exist,..."

    Already done in header files.

6.  The entries of CMPIContext are referenced inconsistently:

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
      * language(s) used by the MB for any language-specific data passed to MI
        functions

    Proposal: Change the references to these entries in any MI or MB functions
    to be of the form "CMPIInitNameSpace entry", etc.

    Need to apply the result to the header files.

7.  The CMPIBrokerFT structure was not extended to add the prototypes for the
    new filtered "up-calls":

      * CMPIBrokerFT.enumerateInstancesFiltered()
      * CMPIBrokerFT.associatorsFiltered()
      * CMPIBrokerFT.referencesFiltered()

    Proposal: Insert the following code statements at the end of
    "typedef struct _CMPIBrokerFT",
    in subclause 9.2 (CMPIBroker and its MB Function Tables), as follows:

        typedef struct _CMPIBrokerFT {

            . . .

            CMPIEnumeration* (*enumerateInstancesFiltered)
                (const CMPIBroker*, const CMPIContext*,
                 const CMPIObjectPath*, const char**, const char*,
                 const char*, CMPIStatus*);
            CMPIEnumeration* (*associatorsFiltered)
                (const CMPIBroker*, const CMPIContext*,
                 const CMPIObjectPath*, const char*, const char*,
                 const char*, const char*, const char**, const char*,
                 const char*, CMPIStatus*);
            CMPIEnumeration* (*referencesFiltered)
                (const CMPIBroker*, const CMPIContext*,
                 const CMPIObjectPath*, const char*, const char*,
                 const char**, const char*, const char*, CMPIStatus*);
        } CMPIBrokerFT;

    Already done in header files.

8.  In CMPIBrokerFT.enumerateInstancesFiltered(), the list of return codes
    has these issues:

    a)  The following return codes are missing:

        * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in classPath
          does not exist.
        * CMPI_RC_ERR_INVALID_CLASS - The class specified in classPath does not
          exist.
        * CMPI_RC_ERR_INVALID_PARAMETER - The property list specified in
          properties is invalid.
        * CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED - Limits exceeded.

        Proposal: Add those return codes to the ERRORS section of the function.

        Reason: These return codes are needed because the target MI could
        return them, and this MB function needs to be able to handle them by
        passing them on to its caller.

    b)  The following return code is defined by mistake:

        * CMPI_RC_ERR_NOT_FOUND

        Proposal: Remove this return code from the ERRORS section of the
        function.

        Reason: It is not needed because the corresponding newly added
        MI function CMPIInstanceMIFT.enumerateInstancesFiltered(), has not
        defined this return code in the first place. Also, for consistency with
        CMPIBrokerFT.enumerateInstances(), which has this return code
        deprecated.

    Need to apply the result to the header files.

9.  In CMPIBrokerFT.associatorsFiltered(), the list of return codes misses
    these return codes:

    * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath does
      not exist.
    * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath does not
      exist.
    * CMPI_RC_ERR_INVALID_PARAMETER - The assocClass, resultClass, role,
      resultRole, or properties arguments are invalid.

    Proposal: Add those return codes to the ERRORS section of the function.

    Need to apply the result to the header files.

10. In CMPIBrokerFT.referencesFiltered(), the list of return codes misses
    these return codes:

    * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath does
      not exist.
    * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath does not
      exist.
    * CMPI_RC_ERR_INVALID_PARAMETER - The resultClass, role, or properties
      arguments are invalid.

    Proposal: Add those return codes to the ERRORS section of the function.

    Need to apply the result to the header files.

11. Incorrect use of "shall" for some MB functions.

    Reason: The spec is generally written from an MI perspective, i.e. it uses
    normative requirements language ("shall", "should") when it comes to
    requirements against the MI, and it uses "will" or factual statements (e.g.
    "returns") when it comes to descriptions about the behavior of MB functions.
    The MB functions mentioned below use "shall" inconsistently with this
    approach.

    Proposal: Update the following sentence in the first paragraph of the
    DESCRIPTION section, from:

    "If no such instances are found, the function shall return success ..."

    to:

    "If no such instances are found, the function will return success ..."

    For the following functions:

    * CMPIBrokerFT.enumerateInstancesFiltered()
    * CMPIBrokerFT.associatorsFiltered()
    * CMPIBrokerFT.referencesFiltered()

    Already done in header files.

12. The short description of CMPIBrokerFT.associatorsFiltered() and
    CMPIBrokerFT.referencesFiltered() refers to just one filter
    "filterQuery", when they actually have the usual association filters as
    well.

    Proposal:

    1. In the short description of these two functions, change:
       From:

       "... returning only those that match the filterQuery argument"

       To:

       "... returning only those that match the given filters"

    2. In the long description of these two functions, change the end of the
       first sentence from "the filter." to "the filters."

    Already done in header files.

13. The short description of CMPIBrokerFT.enumerateInstancesFiltered(),
    refers specifically to "filterQuery". It would be consistent with the
    previous issue to generalize this as well, so that the argument name
    is not mentioned in the short description.

    Proposal: Change the short description
    from:

    "... returning only those that match the filterQuery argument"

    to:

    "... returning only those that match the given query filter"

    Already done in header files.

14. Terminology inconsistency in the description of the CMPIStatus return value.

    Proposal:

    1. Change all (3) occurrences of the following text throughout the spec
       from:

       "A CMPIStatus structure containing the function return status ..."

       to:

       "A CMPIStatus structure whose rc member specifies the function
        return status ..."

    2. Change all (84) occurrences of the following text throughout the spec
       from:

       "A CMPIStatus structure indicating the function return status ..."

       to:

       "A CMPIStatus structure whose rc member specifies the function
        return status ..."

    Already done in header files.

15. In CMPIPredicateFT.getData(), the name of the "pr" argument is referred
    to as "sc" in the description of the CMPI_RC_ERR_INVALID_HANDLE return code.

    Proposal: Change "sc" to "pr" in that description.

    Already done in header files.

16. In CMPIPredicateFT.evaluateUsingAccessor(), the name of the "pr" argument
    is referred to as "se" in the description of the CMPI_RC_ERR_INVALID_HANDLE
    return code.

    Proposal: Change "se" to "pr" in that description.

    Already done in header files.

17. In CMPIBrokerEncFT.classPathIsA(), the description text of return code
    CMPI_RC_INVALID_PARAMETER is: "The type format is invalid". However, this
    function does not have a 'type' argument. Instead, the function does have
    a "className" argument, to which this error applies.

    Proposal: Change that description text to:
    "The className format is invalid".

    Already done in header files.

18. In CMPIBrokerEncFT.getMessage(), the description of the "msgId" argument
    says:

    "The msgId argument is a message ID ..."

    This is flawed terminology,and inconsistent with other similar descriptions.

    Proposal: Change that description to:

    "The msgId argument points to a string specifying a message ID ..."

    Already done in header files.

19. In CMPIContextFT.addEntry(), there is no information about the
    possibly entry names. We have defined those entry names in Table 10
    (Standard CMPIContext Entries).

    Proposal: Add a reference to Table 10 to the description of the 'name'
    argument in that function:

    "See Table 10 for a definition of entry names."

    Already done in header files.

20. Inconsistencies in description text for common return codes:
    * CMPI_RC_OK:
      - Function successful (144) <- use this one
      - Function succeeded (25)
    * CMPI_RC_ERR_FAILED
      - Unspecific error occurred (35)
      - A generic error occurred (27)
      - Other error occurred (4) <- use this one
    * CMPI_RC_ERR_NOT_SUPPORTED
      - Function is not supported ... (72) <- use this one
      - Function not supported ... (3)
    * CMPI_RC_ERR_INVALID_HANDLE
      - The {xxx} handle is invalid (103) <- use this one
      - Invalid encapsulated data type handle (18)
      - The {xxx} argument is invalid (2)
    * CMPI_RC_ERR_INVALID_NAMESPACE
      - The namespace specified in the {xxx} argument does not exist (18)
      - The namespace is invalid (3)
      - The namespace {xxx} is invalid (1)
      - The namespace specified in {xxx} is invalid (1)
      - The namespace implied by {xxx} is invalid (1)
      - The namespace specified in the {xxx} argument is invalid or does not exist (0) <- use this one
    * CMPI_RC_ERR_INVALID_CLASS
      - The CIM class does not exist in the specified namespace (3)
      - The class specified in the {xxx} argument does not exist (18)
      - The class specified in the {xxx} argument is invalid or does not exist (0) <- use this one

    Suggest to use the proposed ones, consistently.

    Need to apply the result to the header files.

21. Some return code names are split into two words at an underscore boundary.
    That is mostly done in tables, and looks nicer than breaking the name at
    whatever character hits the cell boundary, but it makes searching for a
    return code name much harder.

    Proposal: Remove the break character between the two parts of the return
    code name, so that it becomes one word.

    There are 29 occurrences of this issue, and they can be found by searching
    for "_ " (underscore followed by space).

    The header files did not have this issue.

22. Inconsistencies in referencing the attributes of CMPIError objects:

    * "attribute of a/the CMPIError ..." (76) <- proposed form
    * "attribute in a/the CMPIError ..." (3)

    Proposal: Change any other forms to the proposed form.

    Need to apply the result to the header files.

23. In the qualifier functions, the name of the CMPIObjectPath argument
    was changed from "op" to "classPath", which is inconsistent with the
    other functions on CMPIObjectPath.

    Proposal: Change the "classPath" argument name back to "op", for the
    following functions:

    * CMPIObjectPathFT.getClassQualifier()
    * CMPIObjectPathFT.getPropertyQualifier()
    * CMPIObjectPathFT.getMethodQualifier()
    * CMPIObjectPathFT.getParameterQualifier()

    Need to apply the result to the header files.

24. The ordering of return codes is partly inconsistent.

    We never reviewed the order, and probably we don't have the time now to do
    that now at a large scale, but I propose to do these little fixes:

    * CMPISubCondFT.getPredicate(): Its "invalid handle" rc is second to last,
      while quite often and particularly in CMPISubCondFT.getPredicateAt(),
      it is last.

      Proposal: In CMPISubCondFT.getPredicate(), move the return code for
      "invalid handle" to become last in the list.

    Need to apply the result to the header files.

25. In CMPIPredicateFT.release() and CMPIPredicateFT.clone(), the description
    of CMPI_RC_ERR_INVALID_HANDLE uses the argument name "sc".
    The synopsis and description sections correctly use "pr".

    Proposal: Change "sc" to "pr" in the return code description of these
    functions.

    Already done in header files.

26. In CMPIInstanceMIFT.getInstance(), there is no return code for
    "server limits exceeded".

    Reason: First of all, the result set can be large even for a single instance
    (e.g. via an array of embedded instances), and the server can get to its
    limits also because of other things than a large result set.
    Finally, supporting this return code makes it easier for up-call
    implementations, which then can revert to functions that do not map 1:1.

    Proposal: Suggest to add "server limits exceeded" return code to
    CMPIInstanceMIFT.getInstance(), and to CMPIBrokerFT.getInstance().

27. In CMPIBrokerFT.invokeMethod(), the description of the "out" argument states
    that the MI shall not release the CMPIArgs object. However, that object is
    allocated by the MI, and the statement in the description should not be
    about the CMPIArgs object, but about the objects that are being filled into
    the CMPIArgs object, which are representing the method output parameters.

    Proposal: Change the following sentence in the description of the "out"
    argument
    from:

    "The returned CMPIArgs object shall not be explicitly released by the MI,
     because it will be automatically released by the MB (see Subclause 4.1.7)."

    to:

    "The objects returned in the CMPIArgs object shall not be explicitly
     released by the MI; they will be automatically released by the MB, as
     described in Subclause 4.1.7."

