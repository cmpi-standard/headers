Changes during finalization of the CMPI specification
=====================================================

These are proposals for spec changes that will be voted in the CMPI WG,
and will be brought forward as review comments to the TOG review of the spec.

A: New substantive changes
--------------------------

* A1. Add CMPI_RC_ERR_INVALID_HANDLE to CMPIBrokerMemFT.mark/release().

  The CMPI_RC_ERR_INVALID_HANDLE return code is missing for some MB functions
  that get handles. All other MB functions that get handles have that return
  code, in order to express that the handle was invalid.

  Proposal: Add return code:

  `CMPI_RC_ERR_INVALID_HANDLE`    The {xxx} handle is invalid.

  before return code CMPI_RC_ERR_FAILED, for the following functions and
  {xxx}:
    
  * CMPIBrokerMemFT.mark(): mb
  * CMPIBrokerMemFT.release(): mb

  Change history: Update needed.

  Header files: DONE

* A2. Add CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED to CMPIInstanceMIFT.getInstance().

  There are several reasons for adding this return code to getInstance():
  - The result set can be large even for a single instance (e.g. via an array
    of embedded instances),
  - The MB or MI can get to its limits also because of other things than a
    large result set,

  Proposal: Add return code:

  CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED | WIPG0240 | Limits exceeded.

  before CMPI_RC_ERR_FAILED, in CMPIInstanceMIFT.getInstance().

  Change history: Update needed.

  Header files: DONE

* A3. Add CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED to some client services.

  None of the client services has return code
  CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED. Because some of them call target MI
  functions that may return this return code, they would be faced with the
  difficulty on how to handle it.

  Proposal: Add return code:

  `CMPI_RC_ERR_SERVER_LIMITS_EXCEEDED`    Limits exceeded.

  at the end of the list, or before CMPI_RC_ERR_FAILED if that is at the end
  of the list, for the following functions:

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

  Change history: Update needed.

  Header files: DONE

* A4. Remove CMPI_RC_ERR_NOT_FOUND from CMPIBrokerFT.enumerateInstancesFiltered().

  The CMPI_RC_ERR_NOT_FOUND return code is not needed because the case of no
  instances found is supposed to be represented as success with an empty
  result set.

  For this reason, the corresponding target MI function
  CMPIInstanceMIFT.enumerateInstancesFiltered() we added as not defined this
  return code in the first place (nor do the related new filtering
  association functions), and for CMPIBrokerFT.enumerateInstances() and
  CMPIBrokerFT.enumerateInstanceNames(), we deprecated this return code.

  Proposal: Remove CMPI_RC_ERR_NOT_FOUND from
  CMPIBrokerFT.enumerateInstancesFiltered().

  Change history: Update needed.

  Header files: DONE

* A5. Add return codes about invalid input to filtering client services.

  These return codes are needed because the target MI could return them, and
  this MB function needs to be able to handle them by passing them on to its
  caller.

  Proposal: Add the following return codes, after CMPI_RC_ERR_ACCESS_DENIED:

  * to function CMPIBrokerFT.enumerateInstancesFiltered():
    - `CMPI_RC_ERR_INVALID_NAMESPACE`    The namespace specified in `classPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_CLASS`        The class specified in `classPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_PARAMETER`    The property list specified in `properties` is invalid.

  * to function CMPIBrokerFT.associatorsFiltered():
    - `CMPI_RC_ERR_INVALID_NAMESPACE`    The namespace specified in `instPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_CLASS`        The class specified in `instPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_PARAMETER`    The `assocClass`, `resultClass`, `role`, `resultRole`, or `properties` arguments are invalid.

  * to function CMPIBrokerFT.referencesFiltered():
    - `CMPI_RC_ERR_INVALID_NAMESPACE`    The namespace specified in `instPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_CLASS`        The class specified in `instPath` is invalid or does not exist.
    - `CMPI_RC_ERR_INVALID_PARAMETER`    The `resultClass`, `role`, or `properties` arguments are invalid.

  Change history: Update needed.

  Header files: DONE

* A6. Add three function typedefs for thread functions.

  The definition of function prototypes without these new typedefs was always
  quite unwieldy, and it was not possible to properly create Doxygen
  documentation for these functions without the typedefs.

  The introduction of three new typedefs cleans up the prototypes of functions
  that use them, and it enables proper documentation creation.

  Proposal: Make the three new typedefs part of the CMPI 2.1 standard.

  More specifically:

  * In subclause 9.14 (Operating System Encapsulation Services), insert the
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

  * In subclause 9.14 (Operating System Encapsulation Services), change the
    following function prototypes in the _CMPIBrokerExtFT structure:

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

  * In CMPIBrokerExtFT.newThread(), change the SYNOPSIS section
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

  * In CMPIBrokerExtFT.threadOnce(), change the SYNOPSIS section
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

  * In CMPIBrokerExtFT.createThreadKey(), change the SYNOPSIS section
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

  Change history: Update needed.

  Header files: DONE

B: Changes from approved CRs
----------------------------

These are changes that correct incorrectly applied CRs.

* B1. In CMPIBrokerFT.prepareAttachThread(), no means to return return codes.

  In CMPIBrokerFT.prepareAttachThread(), there are return codes documented,
  but the function has no means to return any return codes.
    
  Our original CR during spec development proposed to remove the return
  codes, but we apparently failed to correctly apply that part of the CR to
  the spec during the spec development cycle.
    
  Proposal: Replace the content of the ERRORS section of
  CMPIBrokerFT.prepareAttachThread() with this sentence:
    
  "For historical reasons, no additional error information is passed back."
    
  Change history: Update needed.
    
  Header files: DONE

* B2. Prototypes for new filtered client services missing in CMPIBrokerFT.

  The CMPIBrokerFT structure was not extended to add the prototypes for the
  new filtered client services:

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

  Change history: No update needed.

  Header files: DONE

C: Minor changes
----------------

This class of changes is not really substantive (they don't change anything
in the API), but they are also not strictly editorial.

* C1. Undocumented additional dependency on Query Normalization cabability.

  In Subclause 7.1 (MB Capabilities), the freeSelectExp() function listed in
  Table 8 in the row for Memory Enhancement Services can only be implemented
  if the Query Normalization capability is available in addition. This is the
  only function for which two independent capabilities are needed.

  Proposal: Add "(Note 6)" behind "freeSelectExp()", and add a Note 6 below
  the table:

  "6. The CMPIBrokerExtFT.freeSelectExp() function, while part of the Memory
  Enhancement Services capability can only be implemented if the Query
  Normalization capability is available as well."

  Change history: Update needed.

  Header files: DONE

* C2. Ordering of return codes.

  Some functions got new return codes in CMPI 2.1, and for the most part,
  they were simply added to the end of the existing list, without considering
  any rules for their ordering.

  In addition, CMPI_RC_ERR_FAILED is usually high in the list, which does not
  make sense given its meaning of "other error for which there is no specific
  code".
  
  In addition, CMPI_RC_ERR_INVALID_HANDLE is usually low or last in the list,
  which does not make sense given that it is likely a very early reson for
  failing.
  
  Proposals:

  - Move CMPI_RC_ERR_FAILED to the end of the list, for all functions where
    that is not the case yet.

  - Move CMPI_RC_ERR_NOT_SUPPORTED after CMPI_RC_OK, for all functions where
    that is not the case yet. These are:

    * CMPIInstanceFT.setPropertyFilter()
    * CMPIErrorFT.release()
    * CMPIBrokerEncFT.newCMPIError()
    * CMPIPropertyMIFT.setProperty()
    * CMPIPropertyMIFT.getProperty()
    * CMPIPropertyMIFT.setPropertyWithOrigin()

  - Move CMPI_RC_ERR_ACCESS_DENIED after CMPI_RC_ERR_NOT_SUPPORTED, for all
    functions where that is not the case yet. These are:

    * CMPIPropertyMIFT.setProperty()
    * CMPIPropertyMIFT.getProperty()
    * CMPIPropertyMIFT.setPropertyWithOrigin()

  - Move CMPI_RC_ERR_INVALID_HANDLE up in the list, to the following
    position:

    * after CMPI_RC_ERR_ACCESS_DENIED (if that exists), or
    * after CMPI_RC_ERR_NOT_SUPPORTED (if that exists), or
    * after CMPI_RC_OK,

    for all functions where that is not the case yet. (Many functions).
          
  Change history: No update needed.

  Header files: TODO: Apply proposal, once approved.

* C3. Flaw in description of "out" argument of CMPIBrokerFT.invokeMethod().

  The description of the "out" argument states that the MI shall not release
  the CMPIArgs object. However, that object is allocated by the MI, and the
  statement in the description should not be about the CMPIArgs object, but
  about the objects that are being filled into the CMPIArgs object, which are
  representing the method output parameters.

  Proposal: Change the following sentence in the description of the "out"
  argument from:

  "The returned CMPIArgs object shall not be explicitly released by the MI,
  because it will be automatically released by the MB (see Subclause 4.1.7)."

  to:

  "The objects returned in the CMPIArgs object shall not be explicitly
  released by the MI; they will be automatically released by the MB, as
  described in Subclause 4.1.7."

  Change history: No update needed.

  Header files: DONE

* C4. Incorrect use of "shall" for some MB functions.

  The spec is generally written from an MI perspective, i.e. it uses
  normative requirements language ("shall", "should") when it comes to
  requirements against the MI, and it uses "will" or factual statements (e.g.
  "returns") when it comes to descriptions about the behavior of MB
  functions. The MB functions mentioned below use "shall" inconsistently with
  this approach.

  Proposal: Update the following sentence in the first paragraph of the
  DESCRIPTION section, from:

  "If no such instances are found, the function shall return success ..."

  to:

  "If no such instances are found, the function will return success ..."

  For the following functions:

  * CMPIBrokerFT.enumerateInstancesFiltered()
  * CMPIBrokerFT.associatorsFiltered()
  * CMPIBrokerFT.referencesFiltered()

  Change history: No update needed.

  Header files: DONE

* C5. Incorrect pointer indirection for "name" argument in CMPIObjectPathFT.getKeyAt().

  The description of the "name" output argument misses one level of pointer
  indirection.

  Proposal: Change the first sentence in the description of the "name"
  argument of that function from:

  "The name output argument points to a CMPIString object that upon success
  will have been updated with the name of the key binding."

  to:

  "The name output argument, if not NULL, points to a CMPIString pointer that
  upon success will have been updated to point to a CMPIString object
  containing the name of the key binding."

  Change history: No update needed.

  Header files: DONE

* C6. Missing functions in capabilities table.

  In Subclause 7.1 (MB Capabilities), Table 8 is missing some functions that
  are part of MB capabilities.

  Proposal: Add the missing function names in column "Provided Support" of
  that table, as follows:
  
  * In the row for capability "OS Encapsulation Services", add at the bottom:
    - destroyCondition2()
    - destroyMutex2()
    - lockMutex2()
    - unlockMutex2()

  * In the row for capability "Memory Enhancement Services", add at the
    bottom:
    - freeChars()

  * In the row for capability "Extended Errors", add before
    "Encapsulated data types:"
    - CMPIResultFT functions: returnError()

  Change history: No update needed.

  Header files: DONE (via @capXXX tagging of the entities)

* C7. Entries of CMPIContext referenced inconsistently.

  The description of CMPIContext pointer arguments in any MI or MB functions
  uses these terms:

  * CMPIInitNameSpace entry
  * invocation flags, CMPIInvocationFlags entry
  * principal
  * role
  * accept language
  * content language

  The description of the entries defines them as follows (same order as
  above):

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

* C8. Inconsistent use of "shall" for the ctx argument in some MB functions.

  Some MB functions use "The ctx argument shall point to ...", and some use
  "The ctx argument points to ...". That inconsistency has no technical
  reason, and may raise questions as to why there is a difference. Similar
  arguments are specified without "shall".

  Proposal: Change all (8) occurrences of:

  "The ctx argument shall point"

  to:

  "The ctx argument points"

  Header files: DONE

* C9. Change name of CMPIObjectPath argument in qualifier functions.

  In the qualifier functions, the name of the CMPIObjectPath argument
  was changed from "op" to "classPath", which is inconsistent with the
  other functions on CMPIObjectPath.

  Proposal: Change the "classPath" argument name back to "op", for the
  following functions:

  * CMPIObjectPathFT.getClassQualifier()
  * CMPIObjectPathFT.getPropertyQualifier()
  * CMPIObjectPathFT.getMethodQualifier()
  * CMPIObjectPathFT.getParameterQualifier()

  Header files: DONE

* C10. Confusing order of paragraphs in CMPIObjectPathFT.getKey/getKeyAt().

  Their "RETURN VALUE" section has a paragraph "If successful, ...",
  followed by a paragraph "If not successful", followed by remaining
  paragraphs. The remaining paragraphs are meant to apply only to the
  successful case, but given their location after the paragraph about the
  not successful case, they can easily be misunderstood to apply to
  both cases, or even to just the not successful case.

  Proposal: Move the paragraph "If not successful, ..." to the end of the
  "RETURN VALUE" section, for functions CMPIObjectPathFT.getKey() and
  CMPIObjectPathFT.getKeyAt().

  Header files: DONE

* C11. Flawed terminology in return code description of CMPIBrokerFT.enumerateInstanceNames().

  The deprecation note for return code CMPI_RC_ERR_NOT_FOUND in
  CMPIBrokerFT.enumerateInstanceNames() mentions a "source instance", which
  is a term we use for association calls but not for enumeration calls.

  Proposal: Change the description of return code CMPI_RC_ERR_NOT_FOUND in
  CMPIBrokerFT.enumerateInstanceNames() from:

  "Instead of using this return code if the source instance does not exist,..."

  to:

  "Instead of using this return code if no instances exist,..."

  Header files: DONE

* C12. Flawed description in filtered association client services.

  The short description of CMPIBrokerFT.associatorsFiltered() and
  CMPIBrokerFT.referencesFiltered() refers to just one filter "filterQuery",
  when they actually have the usual association filters as well.

  Proposals:

  * In the short description of these two functions, change from:

    "... returning only those that match the filterQuery argument"

    to:

    "... returning only those that match the given filters"

  * In the long description of these two functions, change the end of the
    first sentence from: "the filter." to: "the filters."

  Header files: DONE

* C13. Flawed description in filtered association client services, part 2.

  The short description of CMPIBrokerFT.enumerateInstancesFiltered(),
  refers specifically to "filterQuery". It would be consistent with 
  issue D11 to generalize this as well, so that the argument name
  is not mentioned in the short description.

  Proposal: Change the short description from:

  "... returning only those that match the filterQuery argument"

  to:

  "... returning only those that match the given query filter"

  Header files: DONE

* C14. Incorrect about what is controlled in CMPIBrokerFT.enumerateInstancesFiltered().

  The following sentence in the description of
  CMPIBrokerFT.enumerateInstancesFiltered() is incorrect w.r.t. what is
  controlled.

  In addition, the specific subset of the invocation flags that can be used
  for this controlling, are not mentioned.

  Furthermore, the option to control via the properties argument is missing.

  Change from:

  "Instance structures can be controlled using the CMPIInvocationFlags entry
  in ctx."

  to:

  "The set of properties in the result instances can be controlled via the
  properties argument and via the CMPI_FLAG_LocalOnly and
  CMPI_FLAG_DeepInheritance flags in the CMPIInvocationFlags entry of the ctx
  argument.

  Header files: DONE

D: Editorial changes
--------------------

* D1. Terminology inconsistency between "CMPIBroker object" and
  "CMPIBroker structure".

  On the one hand, it is not an encapsulated data type object (so "structure"
  would be appropriate), on the other hand, it does have a handle member and
  could be considreed an object therefore.

  I don't care which term we use, but it should be one term, consistently.    

  Proposal: Change all (15) occurrences of "CMPIBroker object" to
  "CMPIBroker structure", throughout the spec document.

  Header files: DONE

* D2. Terminology inconsistency in the description of the CMPIStatus return value.

  Proposal: Change all (84) occurrences of the following text throughout
  the spec from:

  "A CMPIStatus structure indicating the function return status ..."

  to:

  "A CMPIStatus structure containing the function return status ..."

  Header files: DONE

* D3. Remove CMPI_RC_ERR_INVALID_HANDLE item from change history of some indication functions.

  Some of the indication MI functions have an item in their change history:

  "In CMPI 2.1, added the CMPI_RC_ERR_INVALID_HANDLE return code."

  However, that return code does not show up in the list of return codes.

  The item in the change histories was introduced by CR 20, and that CR added
  the change history items at some point during its development, but it never
  shows the return code actually added to the return code list.

  Proposal: Fix the inconsistency by removing the change history entry:

  "In CMPI 2.1, added the CMPI_RC_ERR_INVALID_HANDLE return code."

  for the following functions:
  
  * CMPIIndicationMIFT.authorizeFilter()
  * CMPIIndicationMIFT.activateFilter()
  * CMPIIndicationMIFT.deActivateFilter()

  Header files: Not relevant

* D4. Inconsistency between change history and actual change in CMPISubCondFT.getPredicate().

  In CMPISubCondFT.getPredicate(), CMPI_RC_ERR_NO_SUCH_PROPERTY was added.
  The change history in the function description incorrectly states that
  CMPI_RC_ERR_INVALID_PARAMETER was added.

  Also, a corresponding entry in the global change history is missing.

  Proposals:

  * In the change history text of the function, change
    "CMPI_RC_ERR_INVALID_PARAMETER" to "CMPI_RC_ERR_NO_SUCH_PROPERTY".

  * In C.1 "Changes in CMPI 2.1", add a bullet item at the end of section
    "Changes to Return Codes":

    "Added return code CMPI_RC_ERR_NO_SUCH_PROPERTY to
    CMPISubCondFT.getPredicate()."

  Header files: Not relevant.
  
* D5. Font changes for argument names

  The name of an argument in the description of a return code has regular font
  and should be changed to have monospaced font, in these functions:

  * CMPIInstanceFT.setPropertyFilter(): "keyList" in CMPI_RC_ERR_INVALID_PARAMETER
  * CMPIBrokerEncFT.logMessage(): "string" in CMPI_RC_ERR_INVALID_HANDLE
  * CMPIBrokerEncFT.trace(): "string" in CMPI_RC_ERR_INVALID_HANDLE

  Header files: Not relevant.
  
* D6. Incorrect argument names in CMPI_RC_ERR_INVALID_HANDLE return code descriptions.

  The names of arguments are incorrect in some descriptions of the
  CMPI_RC_ERR_INVALID_HANDLE return code.
  
  Proposal: Fix the incorrect names as follows:

  * CMPIPredicateFT.getData(): Change "sc" to "pr".
  * CMPIPredicateFT.evaluateUsingAccessor(): Change "se" to "pr".
  * CMPIPredicateFT.release(): Change "sc" to "pr".
  * CMPIPredicateFT.clone(): Change "sc" to "pr".

  Header files: DONE

* D7. Incorrect argument name in return code description of CMPIBrokerEncFT.classPathIsA().

  The description text for return code CMPI_RC_INVALID_PARAMETER is:

  "The type format is invalid".

  However, this function does not have a 'type' argument. Instead, the
  function does have a "className" argument, to which this error applies.

  Proposal: Change that description text to:

  "The className format is invalid".

  Header files: DONE

* D8. Flawed terminology in argument description of CMPIBrokerEncFT.getMessage().

  The description of the "msgId" argument says:

  "The msgId argument is a message ID ..."

  This is flawed terminology, and inconsistent with other similar descriptions.

  Proposal: Change that description to:

  "The msgId argument points to a string specifying a message ID ..."

  Header files: DONE

* D9. Add link to context entry definitions in CMPIContextFT.addEntry().

  In CMPIContextFT.addEntry(), there is no information about the
  possibly entry names. We have defined those entry names in Table 10
  (Standard CMPIContext Entries).

  Proposal: Add a reference to Table 10 to the description of the 'name'
  argument in that function:

  "See Table 10 for a definition of entry names."

  Header files: DONE

* D10. Confusing order of control options in CMPIBrokerFT.enumerateInstances().

  The following sentence is confusing w.r.t. the two possibilities for
  control.

  In addition, the two flags are referenced by their protocol names but
  should be referenced by their CMPI symbols.

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

* D11. Inconsistencies in description text for some common return codes.

  Proposal: Change all return code descriptions listed below. The number in
  parenthesis is the number of occurrences in the spec document.

  * For CMPI_RC_OK, change these descriptions:
    - "Function succeeded" (25)
    - "Operation successful" (9)
    - "Indicates the CMPIError object was successfully created" (2)
    to this form:
    - "Function successful" (144)

    Header files: DONE

  * For CMPI_RC_ERR_FAILED, change these descriptions:
    - "Unspecific error occurred" (35)
    - "A generic error occurred" (27)
    to this form:
    - "Other error occurred" (23)

    Header files: DONE

  * For CMPI_RC_ERR_NOT_SUPPORTED, change these descriptions:
    - "Function not supported by ..." (3)
    to this form:
    - "Function is not supported by ..." (91)

    Header files: DONE

  * For CMPI_RC_ERR_INVALID_HANDLE, change all of the following occurrences
    to the form mentioned at the bottom:

    - Change "Invalid encapsulated data type handle", for these
      functions with {xxx} being:
      * CMPIBrokerFT.enumerateInstances(): mb, ctx or classPath
      * CMPIBrokerFT.enumerateInstanceNames(): mb, ctx or classPath
      * CMPIBrokerFT.getInstance(): mb, ctx or instPath
      * CMPIBrokerFT.getProperty(): mb, ctx or instPath
      * CMPIBrokerFT.setProperty(): mb, ctx or instPath
      * CMPIBrokerFT.createInstance(): mb, ctx, classPath, or newInst
      * CMPIBrokerFT.modifyInstance(): mb, ctx, instPath, or modInst
      * CMPIBrokerFT.deleteInstance(): mb, ctx or instPath
      * CMPIBrokerFT.invokeMethod(): mb, ctx, objPath, in, or out
      * CMPIBrokerFT.associators(): mb, ctx or instPath
      * CMPIBrokerFT.associatorNames(): mb, ctx or instPath
      * CMPIBrokerFT.references(): mb, ctx or instPath
      * CMPIBrokerFT.referenceNames(): mb, ctx or instPath
      * CMPIBrokerFT.enumerateInstancesFiltered(): mb, ctx or classPath
      * CMPIBrokerFT.associatorsFiltered(): mb, ctx or instPath
      * CMPIBrokerFT.referencesFiltered(): mb, ctx or instPath
      * CMPIBrokerFT.execQuery(): mb, ctx or classPath
      * CMPIBrokerFT.prepareAttachThread(): mb, ctx

    - Change "The {xxx} argument is invalid", for these functions:
      * CMPIObjectPathFT.toString()
      * CMPIBrokerEncFT.newCMPIError()

    - Change "Either the {xxx} or {yyy} handle is invalid" (8)

    - Change "The handle specified by the {xxx} argument is invalid",
      for these functions with {xxx} being:
      * CMPIBrokerFT.deliverIndication(): mb, ctx or ind

    - Change "The {xxx} handle or {yyy} handle is invalid"

    To this form:
      - "The {xxx} handle is invalid", with {xxx} listed below.

    Header files: DONE

  * For CMPI_RC_ERR_INVALID_NAMESPACE, change these descriptions:
    - "The namespace specified in the {xxx} argument does not exist" (18)
    - "The namespace is invalid" (3)
    - "The namespace {xxx} is invalid" (1)
    - "The namespace specified in {xxx} is invalid" (1)
    - "The namespace implied by {xxx} is invalid" (1)
    to this form:
    - "The namespace specified in the {xxx} argument is invalid or does not
      exist" (0)

    Header files: DONE

  * For CMPI_RC_ERR_INVALID_CLASS, change these descriptions:
    - "The CIM class does not exist in the specified namespace" (3)
    - "The class specified in the {xxx} argument does not exist" (18)
    to this form:
    - The class specified in the {xxx} argument is invalid or does not
      exist" (0)

    Header files: DONE

* D12. Return code names split into two words to match table cell boundaries.

  Some return code names are split into two words at an underscore boundary.
  That is mostly done in tables, and looks nicer than breaking the name at
  whatever character hits the cell boundary, but it makes searching for a
  return code name much harder.

  Proposal: Remove the break character between the two parts of the return
  code name, so that it becomes one word.

  There are 29 occurrences of this issue, and they can be found by searching
  for "_ " (underscore followed by space).

  Header files: Not relevant.

* D13. Inconsistencies in referencing the attributes of CMPIError objects.

  Proposal: Change the following text from:

  "attribute in a/the CMPIError ..." (3 occurrences)

  to:

  "attribute of a/the CMPIError ..." (already 76 occurrences)

  Header files: DONE

* D14. Inconsistency in how the Context Data capability is referenced.

  In Table 8, this capability is named "Context Data", however it is
  referenced throughout the document as
  "Context Data Support capability" (4 occurrences).

  Proposal: Consistent with other capability names, change the phrase
  "Context Data Support capability" to "Context Data capability", throughout
  the document.

  Header files: DONE

