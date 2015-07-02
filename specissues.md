Changes during finalization of the CMPI specification
=====================================================

These are proposals for spec changes that will be voted in the CMPI WG,
and will be brought forward as review comments to the TOG review of the spec.

Changes throughout the spec document
------------------------------------

1.  Terminology inconsistency between "CMPIBroker object" and
    "CMPIBroker structure".

    Proposal: Change all (15) occurrences of "CMPIBroker object" to
    "CMPIBroker structure", throughout the spec document.

    Header files: DONE

2.  The entries of CMPIContext are referenced inconsistently:

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

    Proposal:

    The general approach is to change the references to these entries in any MI
    or MB functions to add the name of the context entry (e.g.
    CMPIInitNameSpace).

    More specifically:

    * Change all (17) occurrences of:

      "... CMPIContext object that specifies the same principal, role, accept
      language, and content language as the CMPIContext object ..."

      to:

      "... CMPIContext object that specifies the same principal (CMPIPrincipal
      entry), role (CMPIRole entry), accept language (CMPIAcceptLanguage
      entry), and content language (CMPIContentLanguage entry) as the
      CMPIContext object ..."

    * Change all (14) occurrences of:

      "Any invocation flags in the ctx argument ..."

      to:

      "Any invocation flags (CMPIInvocationFlags entry) in the ctx argument ..."

    * Change all (3) occurrences of:

      "The MI may specify invocation flags as needed."

      to:

      "The MI may specify invocation flags (CMPIInvocationFlags entry) as
      needed."
      
    Header files: DONE

3.  Inconsistent use of "shall" for the ctx argument in some MB functions.

    Some MB functions use "The ctx argument shall point to ...", and some use
    "The ctx argument points to ...". That inconsistency has no technical
    reason, and may raise questions as to why there is a difference. Similar
    arguments are specified without "shall".

    Proposal: Change all (8) occurrences of:

    "The ctx argument shall point"

    to:

    "The ctx argument points"

    Header files: DONE

4.  Terminology inconsistency in the description of the CMPIStatus return value.

    Proposal: Change all (84) occurrences of the following text throughout
    the spec from:

      "A CMPIStatus structure indicating the function return status ..."

      to:

      "A CMPIStatus structure containing the function return status ..."

    Header files: DONE

5.  There are inconsistencies in description text for some common return codes.

    Proposal: Change all return code descriptions listed below, to use the
    option marked with "use this one", throughout the document. The number in
    parenthesis is the number of occurrences in the spec document.

    * CMPI_RC_OK:
      - Function successful (144) <- use this one
      - Function succeeded (25)
      - Operation successful (9)
      - Indicates the CMPIError object was successfully created (2)

      Header files: DONE

    * CMPI_RC_ERR_FAILED
      - Other error occurred (23) <- use this one
      - Unspecific error occurred (35)
      - A generic error occurred (27)

      Header files: DONE

    * CMPI_RC_ERR_NOT_SUPPORTED
      - Function is not supported by ... (91) <- use this one
      - Function not supported by ... (3)

      Header files: DONE

    * CMPI_RC_ERR_INVALID_HANDLE
      - The {xxx} handle is invalid (103) <- use this one
      - Invalid encapsulated data type handle (18)
      - The {xxx} argument is invalid (2), in these functions:
        * CMPIObjectPathFT.toString()
        * CMPIBrokerEncFT.newCMPIError()

      TODO: List functions for second case.

      Header files: TODO

    * CMPI_RC_ERR_INVALID_NAMESPACE
      - The namespace specified in the {xxx} argument is invalid or does not
        exist (0) <- use this one
      - The namespace specified in the {xxx} argument does not exist (18)
      - The namespace is invalid (3)
      - The namespace {xxx} is invalid (1)
      - The namespace specified in {xxx} is invalid (1)
      - The namespace implied by {xxx} is invalid (1)

      Header files: TODO

    * CMPI_RC_ERR_INVALID_CLASS
      - The class specified in the {xxx} argument is invalid or does not
        exist (0) <- use this one
      - The CIM class does not exist in the specified namespace (3)
      - The class specified in the {xxx} argument does not exist (18)

      Header files: TODO

6.  Some return code names are split into two words at an underscore boundary.
    That is mostly done in tables, and looks nicer than breaking the name at
    whatever character hits the cell boundary, but it makes searching for a
    return code name much harder.

    Proposal: Remove the break character between the two parts of the return
    code name, so that it becomes one word.

    There are 29 occurrences of this issue, and they can be found by searching
    for "_ " (underscore followed by space).

    Header files: Not relevant.

7.  Inconsistencies in referencing the attributes of CMPIError objects:

    * "attribute of a/the CMPIError ..." (76) <- proposed form
    * "attribute in a/the CMPIError ..." (3)

    Proposal: Change any other forms to the proposed form.

    Header files: DONE

8.  Inconsistency in how the Context Data capability is referenced.
    In Table 8, this capability is named "Context Data", however it is
    referenced throughout the document as
    "Context Data Support capability" (4 occurrences).

    Proposal: Consistent with other capability names, change the phrase
    "Context Data Support capability" to "Context Data capability", throughout
    the document.

    Header files: DONE

Changes that apply to a number of functions
-------------------------------------------

1.  Some return codes were intended to be added in CMPI 2.1, and are also
    mentioned in the change history to have been added, but are not actually
    showing up in the list of return codes in the ERRORS section.

    Proposal: Add the missing return codes as follows:

    - Add an item with the following return code:

      * CMPI_RC_ERR_INVALID_HANDLE - The ctx, filter, or classPath handles are
        invalid.

      after the item for CMPI_RC_ERR_ACCESS_DENIED, for the following functions:
      
      * CMPIIndicationMIFT.authorizeFilter()
      * CMPIIndicationMIFT.activateFilter()
      * CMPIIndicationMIFT.deActivateFilter()

    - Add an item with the following return code:

      * CMPI_RC_ERR_INVALID_HANDLE - The ctx or collInst handles are invalid.

      after the item for CMPI_RC_ERR_ACCESS_DENIED, for the following functions:

      * CMPIIndicationMIFT.authorizeFilterCollection()
      * CMPIIndicationMIFT.activateFilterCollection()
      * CMPIIndicationMIFT.deActivateFilterCollection()

    Header files: DONE

2.  Some functions got new return codes in CMPI 2.1, and they were simply added
    to the end of the existing list, without considering any rules for their
    ordering. While we did not research in detail what the ordering rules might
    have been, there are some obvious ones that should be adhered to.

    Proposals:

    - Move the list item for CMPI_RC_ERR_FAILED to the end of the list, for all
      functions where that is not the case yet.

    - Move the list item for CMPI_RC_ERR_NOT_SUPPORTED after the list item for
      CMPI_RC_OK, for all functions where that is not the case yet. These are:

      * CMPIInstanceFT.setPropertyFilter()
      * CMPIErrorFT.release()
      * CMPIBrokerEncFT.newCMPIError()
      * CMPIPropertyMIFT.setProperty()
      * CMPIPropertyMIFT.getProperty()
      * CMPIPropertyMIFT.setPropertyWithOrigin()

    - Move the row for CMPI_RC_ERR_ACCESS_DENIED after the row for
      CMPI_RC_ERR_NOT_SUPPORTED, for all functions where that is not the case
      yet. These are:

      * CMPIPropertyMIFT.setProperty()
      * CMPIPropertyMIFT.getProperty()
      * CMPIPropertyMIFT.setPropertyWithOrigin()

    - Move the list item for CMPI_RC_ERR_INVALID_HANDLE up in the list, as
      follows:

      * after CMPI_RC_ERR_ACCESS_DENIED (if that exists), or
      * after CMPI_RC_ERR_NOT_SUPPORTED (if that exists), or
      * after CMPI_RC_OK.

      for all functions where that is not the case yet.
            
    Header files: TODO: Need to apply proposal, once approved.

3.  All "up-calls" do not have the return code for "limits exceeded".
    However, because some of them call target MI functions that may return this
    return code, they would be faced with the difficulty on how to handle it.

    Proposal: Add the following return code:

      * CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED - Limits exceeded.

    at the end (or before CMPI_RC_ERR_FAILED if that is at the end) of the
    return code list of only the following functions:

      * CMPIBrokerFT.enumerateInstances()
      * CMPIBrokerFT.enumerateInstanceNames()
      * CMPIBrokerFT.enumerateInstancesFiltered()
      * CMPIBrokerFT.associators()
      * CMPIBrokerFT.associatorNames()
      * CMPIBrokerFT.associatorsFiltered()
      * CMPIBrokerFT.references()
      * CMPIBrokerFT.referenceNames()
      * CMPIBrokerFT.referencesFiltered()
      * CMPIBrokerFT.execQuery()
      * CMPIBrokerFT.invokeMethod()
      * CMPIBrokerFT.getInstance()

    Header files: DONE

4.  Incorrect use of "shall" for some MB functions.

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

    Header files: DONE

5.  In the qualifier functions, the name of the CMPIObjectPath argument
    was changed from "op" to "classPath", which is inconsistent with the
    other functions on CMPIObjectPath.

    Proposal: Change the "classPath" argument name back to "op", for the
    following functions:

    * CMPIObjectPathFT.getClassQualifier()
    * CMPIObjectPathFT.getPropertyQualifier()
    * CMPIObjectPathFT.getMethodQualifier()
    * CMPIObjectPathFT.getParameterQualifier()

    Header files: DONE

Changes for specific spots in the spec document
-----------------------------------------------

1.  In CMPIObjectPathFT.getKeyAt(), the description for the "name" output
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

    Header files: DONE

2.  In CMPIObjectPathFT.getKey() and CMPIObjectPathFT.getKeyAt():

    Their "RETURN VALUE" section has a paragraph "If successful, ...",
    followed by a paragraph "If not successful", followed by remaining
    paragraphs. The remaining paragraphs are meant to apply only to the
    successful case, but given their location after the paragraph about the
    not successful case, they can easily be misunderstood to apply to
    both cases, or even to just the not successful case.

    Proposal: Move the paragraph "If not successful, ..." to the end of the
    "RETURN VALUE" section.

    Header files: DONE

3.  In CMPIBrokerFT.prepareAttachThread(), there are return codes documented,
    but the function has no means to return return codes.

    Our original CR during spec development proposed to remove the return
    codes, but we apparently failed to correctly apply that part of the CR to
    the spec during the spec development cycle.

    Proposal: Replace the content of the ERRORS section of
    CMPIBrokerFT.prepareAttachThread() with this sentence:

    "For historical reasons, no additional error information is passed back."

    Header files: DONE

4.  In CMPIBrokerFT.enumerateInstanceNames(), the deprecation note for return
    code CMPI_RC_ERR_NOT_FOUND mentions a "source instance", which is a term we
    use for association calls but not for enumeration calls.

    Proposal: Change the description of return code CMPI_RC_ERR_NOT_FOUND in
    CMPIBrokerFT.enumerateInstanceNames() from:

    "Instead of using this return code if the source instance does not exist,..."

    To:

    "Instead of using this return code if no instances exist,..."

    Header files: DONE

5.  The CMPIBrokerFT structure was not extended to add the prototypes for the
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

    Header files: DONE

6.  In CMPIBrokerFT.enumerateInstancesFiltered(), the list of return codes
    has these issues:

    a) The following return codes are missing:

      * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in classPath
        does not exist.
      * CMPI_RC_ERR_INVALID_CLASS - The class specified in classPath does not
        exist.
      * CMPI_RC_ERR_INVALID_PARAMETER - The property list specified in
        properties is invalid.

      Proposal: Add those return codes to the ERRORS section of the function,
      after the entry for "access denied".

      Reason: These return codes are needed because the target MI could
      return them, and this MB function needs to be able to handle them by
      passing them on to its caller.

    b) The following return code is defined by mistake:

      * CMPI_RC_ERR_NOT_FOUND

      Proposal: Remove this return code from the ERRORS section of the
      function.

      Reason: It is not needed because the corresponding newly added
      MI function CMPIInstanceMIFT.enumerateInstancesFiltered(), has not
      defined this return code in the first place. Also, for consistency with
      CMPIBrokerFT.enumerateInstances(), which has this return code
      deprecated.

    Header files: DONE

7.  In CMPIInstanceMIFT.getInstance(), there is no return code for
    "limits exceeded".

    Reason: First of all, the result set can be large even for a single instance
    (e.g. via an array of embedded instances), and the server can get to its
    limits also because of other things than a large result set.
    Finally, supporting this return code makes it easier for up-call
    implementations, which then can revert to functions that do not map 1:1.

    Proposal: Add the following row:

      * CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED | WIPG0240 | Limits exceeded.

    before the rows for CMPI_RC_ERR_FAILED.

    Header files: DONE

8.  In CMPISubCondFT.getPredicate(), CMPI_RC_ERR_NO_SUCH_PROPERTY was added.
    The change history in the function description incorrectly states that
    code CMPI_RC_ERR_INVALID_PARAMETER has added. A corresponding entry in
    the global change history is missing.

    Proposals:

    - In the change history text of the function, change
      "CMPI_RC_ERR_INVALID_PARAMETER" to "CMPI_RC_ERR_NO_SUCH_PROPERTY".

    - In C.1 "Changes in CMPI 2.1", add a bullet item at the end of section
      "Changes to Return Codes":

      "Added return code CMPI_RC_ERR_NO_SUCH_PROPERTY to
      CMPISubCondFT.getPredicate()."

    Header files: Not relevant.
    
9.  In CMPIInstanceFT.setPropertyFilter(), the "keyList" argument in the
    description of return code CMPI_RC_ERR_INVALID_PARAMETER has regular font
    and should be changed to have monospaced font.

    Header files: Not relevant.
    
10. In CMPIBrokerFT.associatorsFiltered(), the list of return codes misses
    these return codes:

    * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath is
      invalid or does not exist.
    * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath is invalid or
      does not exist.
    * CMPI_RC_ERR_INVALID_PARAMETER - The assocClass, resultClass, role,
      resultRole, or properties arguments are invalid.

    Proposal: Add those return codes to the ERRORS section of the function,
    after the entry for CMPI_RC_ERR_ACCESS_DENIED.

    Header files: DONE

11. In CMPIBrokerFT.referencesFiltered(), the list of return codes misses
    these return codes:

    * CMPI_RC_ERR_INVALID_NAMESPACE - The namespace specified in instPath is
      invalid or does not exist.
    * CMPI_RC_ERR_INVALID_CLASS - The class specified in instPath is invalid or
      does not exist.
    * CMPI_RC_ERR_INVALID_PARAMETER - The resultClass, role, or properties
      arguments are invalid.

    Proposal: Add those return codes to the ERRORS section of the function,
    after the entry for CMPI_RC_ERR_ACCESS_DENIED.

    Header files: DONE

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

    Header files: DONE

13. The short description of CMPIBrokerFT.enumerateInstancesFiltered(),
    refers specifically to "filterQuery". It would be consistent with the
    previous issue to generalize this as well, so that the argument name
    is not mentioned in the short description.

    Proposal: Change the short description
    from:

    "... returning only those that match the filterQuery argument"

    to:

    "... returning only those that match the given query filter"

    Header files: DONE

14. In CMPIPredicateFT.getData(), the name of the "pr" argument is referred
    to as "sc" in the description of the CMPI_RC_ERR_INVALID_HANDLE return code.

    Proposal: Change "sc" to "pr" in that description.

    Header files: DONE

15. In CMPIPredicateFT.evaluateUsingAccessor(), the name of the "pr" argument
    is referred to as "se" in the description of the CMPI_RC_ERR_INVALID_HANDLE
    return code.

    Proposal: Change "se" to "pr" in that description.

    Header files: DONE

16. In CMPIBrokerEncFT.classPathIsA(), the description text of return code
    CMPI_RC_INVALID_PARAMETER is: "The type format is invalid". However, this
    function does not have a 'type' argument. Instead, the function does have
    a "className" argument, to which this error applies.

    Proposal: Change that description text to:
    "The className format is invalid".

    Header files: DONE

17. In CMPIBrokerEncFT.getMessage(), the description of the "msgId" argument
    says:

    "The msgId argument is a message ID ..."

    This is flawed terminology,and inconsistent with other similar descriptions.

    Proposal: Change that description to:

    "The msgId argument points to a string specifying a message ID ..."

    Header files: DONE

18. In CMPIContextFT.addEntry(), there is no information about the
    possibly entry names. We have defined those entry names in Table 10
    (Standard CMPIContext Entries).

    Proposal: Add a reference to Table 10 to the description of the 'name'
    argument in that function:

    "See Table 10 for a definition of entry names."

    Header files: DONE

19. In CMPIPredicateFT.release() and CMPIPredicateFT.clone(), the description
    of CMPI_RC_ERR_INVALID_HANDLE uses the argument name "sc".
    The synopsis and description sections correctly use "pr".

    Proposal: Change "sc" to "pr" in the return code description of these
    functions.

    Header files: DONE

20. In CMPIBrokerFT.invokeMethod(), the description of the "out" argument states
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

    Header files: DONE

21. Add three function typedefs for thread functions:

    Reason: The definition of function prototypes without these new typedefs
    was always quite unwieldy, and it was not possible to properly create
    documentation for these functions.

    The introduction of three new typedefs cleans up the prototypes of functions
    that use them, and it enables proper documentation creation.

    The three new typedefs will become part of the CMPI 2.1 standard.

    Proposal:

    a)  In subclause 9.14 (Operating System Encapsulation Services), insert the
      following description before the line
      "typedef struct _CMPIBrokerExtFT {":

      --- begin of text ---

      `typedef CMPI_THREAD_CDECL CMPI_THREAD_RETURN CMPIThreadFunc(void *parm);`

      CMPIThreadFunc is a function type for a POSIX thread function. A pointer
      to such a function is passed to CMPIBrokerExtFT.newThread().

      The parm argument of the function is a pointer to arbitrary data,
      which was passed to CMPIBrokerExtFT.newThread().

      The return value of this function can be retrieved by the caller of
      CMPIBrokerExtFT.joinThread().

      For more details on such functions, see the pthread_create() function
      defined in IEEE 1003.1.

      `typedef void CMPIThreadOnceFunc(void);`

      CMPIThreadOnceFunc is a function type for a function that is called
      once in a POSIX thread. A pointer to such a function is passed to
      CMPIBrokerExtFT.threadOnce().

      For more details on such functions, see the pthread_once() function
      defined in IEEE 1003.1.

      `typedef void CMPIThreadKeyCleanupFunc(void *key);`

      CMPIThreadKeyCleanupFunc is a function type for a POSIX thread key
      cleanup function. A pointer to such a function is passed to
      CMPIBrokerExtFT.createThreadKey().

      The key argument of this function is a pointer to the previous key
      value before cleanup.

      For more details on such functions, see the pthread_key_create()
      function defined in IEEE 1003.1.

      --- end of text ---

    b) In subclause 9.14 (Operating System Encapsulation Services), change the
      following function prototypes in the _CMPIBrokerExtFT structure :

      from:

          CMPI_THREAD_TYPE (*newThread)
              (CMPI_THREAD_RETURN (CMPI_THREAD_CDECL*)(void*),
               void*, int);

          int (*threadOnce)
              (int*, void (*)(void));

          int (*createThreadKey)
              (CMPI_THREAD_KEY_TYPE*, void (*)(void*));

      to:

          CMPI_THREAD_TYPE (*newThread)
              (CMPIThreadFunc*, void*, int);

          int (*threadOnce)
              (int*, CMPIThreadOnceFunc*);

          int (*createThreadKey)
              (CMPI_THREAD_KEY_TYPE*, CMPIThreadKeyCleanupFunc*);

    c) In CMPIBrokerExtFT.newThread(), change the SYNOPSIS section
      from:

        CMPI_THREAD_TYPE CMPIBrokerExtFT.newThread(
            CMPI_THREAD_RETURN (CMPI_THREAD_CDECL* start) (void*),
            void* parm,
            int detached
        );

      to:

        CMPI_THREAD_TYPE CMPIBrokerExtFT.newThread(
            CMPIThreadFunc* start,
            void* parm,
            int detached
        );

    d) In CMPIBrokerExtFT.threadOnce(), change the SYNOPSIS section
      from:

        int CMPIBrokerExtFT.threadOnce(
            int* once,
            void (*function)(void)
        );

      to:

        int CMPIBrokerExtFT.threadOnce(
            int* once,
            CMPIThreadOnceFunc* function
        );

    e) In CMPIBrokerExtFT.createThreadKey(), change the SYNOPSIS section
      from:

        int CMPIBrokerExtFT.createThreadKey(
            CMPI_THREAD_KEY_TYPE* key,
            void (*cleanup)(void*)
        );

      to:

        int CMPIBrokerExtFT.createThreadKey(
            CMPI_THREAD_KEY_TYPE* key,
            CMPIThreadKeyCleanupFunc* cleanup
        );

    Header files: DONE

22. In Subclause 7.1 (MB Capabilities), Table 8 is missing some functions that
    are part of MB capabilities:

    Proposal: Add the missing function names in column "Provided Support",
    as follows:
    
    a) In the row for capability "OS Encapsulation Services", add at the bottom:
    - destroyCondition2()
    - destroyMutex2()
    - lockMutex2()
    - unlockMutex2()

    b) In the row for capability "Memory Enhancement Services", add at the
    bottom:
    - freeChars()

    c) In the row for capability "Extended Errors", add before
    "Encapsulated data types:"
    - CMPIResultFT functions: returnError()

    Header files: DONE (via @capXXX tagging of the entities)

23. In Subclause 7.1 (MB Capabilities), the freeSelectExp() function listed in
    Table 8 in the row for Memory Enhancement Services can only be implemented
    if the Query Normalization capability is available as well.

    Proposal: Add "(Note 6)" behind "freeSelectExp()", and add a Note 6 below
    the table:

    "6. The CMPIBrokerExtFT.freeSelectExp() function, while part of the Memory
    Enhancement Services capability can only be implemented if the Query
    Normalization capability is available as well."

    Header files: DONE

24. In CMPIBrokerFT.enumerateInstances(), the following sentence is confusing
    w.r.t. the two possibilities for control. In addition, the two flags
    are referenced by their protocol names but should be referenced by their
    CMPI symbols.

    Change from:

    "The set of properties in the result instances can be controlled using the
    LocalOnly and DeepInheritance flags in the CMPIInvocationFlags entry in ctx
    and the properties argument."

    to:

    "The set of properties in the result instances can be controlled via the
    properties argument and via the CMPI_FLAG_LocalOnly and
    CMPI_FLAG_DeepInheritance flags in the CMPIInvocationFlags entry of the ctx
    argument.

    Header files: DONE

25. In CMPIBrokerFT.enumerateInstancesFiltered(), the following sentence is
    incorrect w.r.t. what is controlled. In addition, the specific subset of
    the invocation flags that can be used for this controlling, are not
    mentioned. Furthermore, the option to control via the properties argument
    is missing.

    Change from:

    "Instance structures can be controlled using the CMPIInvocationFlags entry
    in ctx."

    to:

    "The set of properties in the result instances can be controlled via the
    properties argument and via the CMPI_FLAG_LocalOnly and
    CMPI_FLAG_DeepInheritance flags in the CMPIInvocationFlags entry of the ctx
    argument.

    Header files: DONE
