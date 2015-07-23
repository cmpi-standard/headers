
23 July - Andy
--------------

* Added convenience functions for remaining new MB functions in 2.1.
* Added the erroneously removed convenience function for getMessage() back in.
* Changed the @fulldescription and @convfunction special commands to generate
  a paragraph instead of a cross reference item.

22 July - Andy
--------------

* Added support for a new @fulldescription special command that is used to link
  from the (abbridged) description of a convenience function to the full
  description in the underlying MB function.
* Added support for a new @convfunction special command that is used to link
  from the description of a MB function or other entity to its convenience
  function.
* Changed notation for 'template' values in documentation from {xxx} to <xxx>.
* Adjusted the introduction text for types of convenience functions to the
  types defined in the module structure.
* Renamed the macro version of CBGetClassification() to CBGetCapabilities() to
  make it consistent with the inline function.
* Improved description of several convenience functions.
* Added notes to the description of the MI factory stubs for C and C++, as
  discussed.
* Turned CMInitHook() into an officially documented macro.
* Removed all todo items marked with DONE.
* Updated examples/instancemi.c to use official CMInitHook().
* Finished syncing the description of all convenience functions with their
  underlying MB functions.

21 July - Andy
--------------

* Updated inline functions for CMPIContext to better describe the open
  questions.
* Improved descriptions of inline functions down to CMPIDateTime.

20 July - Andy
--------------

* Made wording consistent for descriptions of mb, ctx and rc arguments in
  convenience functions.

19 July - Andy
--------------

* Fixed overflow issue in CMIsNullValue(), CMIsKeyValue(), CMIsArray().
* Removed inline function in CMGetMessage2(), it is macro-only because of its
  variable arguments.
* Reinstantiated CMFmtArgsX and CMFmtX macros that were deleted by accident
  when deleting the deprecated CMGetMessage().
* Improved documentation of CMFmtArgsX(), CMFmtX() and CMGetMessage2().

18 July - Andy
--------------

* Applied description and implementation of CMInstanceMIStub() macro to
  all other plain C MI stub macros.
* Fixed a argument name typo 'asscClass' in CMPIAssociationMIFT.associators().
* Added sub-modules for each EDT, to the EDT convenience functions.
* Improved descriptions of all Helper Functions and Macros, and of CMRelease()
  and CMClone().

17 July - Andy
--------------

* Solved static inline issue by setting EXTRACT_STATIC=YES in Doxyfile. This
  allowed to get rid of the _CMPI_INLINE_STATIC symbol and its conditional
  definition.
* Solved issue that undocumented internal symbols showed up in the
  documentation, by setting HIDE_UNDOC_MEMBERS=YES in the Doxyfile.
* Renamed special command @testopenpegasus to @statusopenpegasus and updated
  its page introduction text accordingly;
  Added comments to Doxyfile and modules.dox hinting to keep the respective
  sections in sync when new MBs are added.
* Added any missing @see commands to convenience functions, referencing
  the corresponding MB functions.

16 July - Andy
--------------

* Many updates in cmpimacs.h and some fixes in cmpift.h:
  - Added missing `const` to @p accessor/accessorFnc argument of
    CMPISelectExpFT/CMPIPredicateFT.evaluateUsingAccessor() in cmpift.h.
  - Added spec bug that CMPIInstanceFT.setPropertyWithOrigin() misses "Added in
    CMPI 2.0" in its change history.
  - Added spec bug that newSelectExp() declares its projection argument
    mistakenly as `const CMPIArray** projection`, the `const` is incorrect for
    this output argument.
  - Added `const` to inline convenience functions in cmpimacs.h where missing;
    they are now in sync with function table functions in cmpift.h.
  - Made argument names of macros and inline functions incmpimacs.h consistent
    with functions in cmpift.h, down to and including the EDTs.
  - Finished switching order of inline functions and macros around in
    cmpimacs.h, in order to properly document the macros in Doxygen output for
    CMPI_NO_INLINE.
  - Added @hideinitializer for all remaining macro definitions.
  - Removed macro-style parenthesis from arguments of all inline function
    implementations in cmpimacs.h.
  - Reordered the EDT convenience functions in cmpimacs.h to be in sync with
    cmpift.h.
  - Fixed a few typos in function table type names, in the descriptions in
    cmpimacs.h.
* Fixed inconsistent nesting of #if/endif in cmpimacs.h.
* Updated some forgotten argument names.
* Removed remaining historical (pre 1.0) stuff from cmpimacs.h.
* Several changes and fixes in cmpimacs.h:
  - Added extern C for inline convenience functions and for plain C factory
    stubs, when compiling for C++.
  - Added conditionals to generate the C++ factory stubs only when compiling for
    C++.
  - Wrote description for CMPIInstanceMIStub() macro for review, and as master
    for updating the others (just the stubs for plain C MIs).
  - Renamed macro arguments that clashed with other uses of the name in the
    macro definition (undoing a previous 'fix').
  - As part of that, changed CMReturn*() macros to use CMStatus*() macros
    instead of repeating their code.
  - Changed the misleading name 'val' of the CMPIData argument to 'data', for
    macros CMIsKeyValue(), CMIsNullValue(), CMIsArray().
  - Changed CMGetCharsPtr() to return `const char*` instead of `char*`.
  - Changed keyList argument of CMSetPropertyFilter() top be `const char**`
    instead of `char**`.
  - Fixed a few erroneous closing parenthesis that were errors introduced by
    earlier commits.
  - Fixed incorrect argument name in CMNewArray().
* Changed _CMPI_INLINE_MOD to _CMPI_INLINE_STATIC and documented it.
* Deprecated CMGetCharPtr() and fixed its implementation by calling the
  corresponding function.

15 July - Karl
--------------

* Committed by Andy: Recorded notes from CMPI WG call.

15 July - Andy
--------------

* Fixed typo CMPIEnumerationFT in cmpimacs.h.
* Removed erroneous semicolon after header of some inline functions.
* Changed all @todo entries for OpenPegasus to use @testopenpegasus.
* Made formatting in cmpimacs.h more consistent.
* Removed duplicated intro to convenience function from file level docs of
  cmpimacs.h.
* Moved the documentation content from modules.dox to cmpimacs.h, only keeping
  the @defgroup statements there.
* Added documentation for CMPI_INLINE and CMPI_NO_INLINE.
* Reordered subgroups of group user-definable symbols.
* Switched macro and inline function into the right order for the first few
  functions in cmpimacs.h.
* In newArray(), documented a bug for the spec related to the array size.

14 July - Karl
--------------

* Moved all of the INLINE defs from top of comment to bottom
* Cleaned up several more convience functions.
* Add documentation on the macros to modules.dox
* Remove @see for documentation that uses word executes to define
  a one-one mapping macro.  Note that we have not added phrase "
  corresponding arguments yet"

13 July - Karl
--------------

* Merged macro_proposal branch back to head.  Resolved one conflict.
* Clean up some errors in macro_proposal, etc. that were causing
  doxygen warnings.  Note that there is one warning left now.
* modified the grouping for cmpimacs but still not happy.  Will do more in
  the morning.

14 July - Andy
---------------

* Fixed mispelled "convience-" tags to "convenience-" tags.
* Improved the headings and descriptions for the various types of convenience
  functions, and reordered them. Consider this a proposal.
* Renamed first argument of each macro in cmpimacs.h to match inline function.
* Reordered functions in cmpimacs.h to fit into their respective groups.

13 July - Karl (by Andy)
------------------------

* Merge of Andy's proposal for cmpimacs from macro_proposal branch into master.
* Updates in cmpimacs.

10 July - Andy
--------------

* Resolved issue that modules.h showed up in Files tab, by renaming it to
  modules.dox.
* Documented the formal incompatibility of adding the 'rslt' argument to
  CMPIIndicationMIFT.mustPoll().

9 July - Karl
-------------

* Worked on getting the new header files to compile in OpenPegasus. Not
  compiling yet but down to specific errors now, some of which are actually
  issue that OpenPegasus had when they modified the release files.
* Noted issue where OpenPegasus was dependent on the include cmpimacs.h
  being in cmpift.h
* Tested issues with the typedef that was failing.
* I did not commit anything back yet.
* For latest proposed by Andy found an issue in that cmpidt.h must include
  cmpios.h to correctly compile. The defines required for the typedef are in
  cmpios.h. Committed this change.

9 July - Andy
-------------

* Applied issue CMPI-C2 (Reordering of return codes);
  Fixed some typos and formatting issues in return codes.
* Added test source file examples/changetoenum.c.
* Added *.o to .gitignore.
* Added @changed210 and @incompatible210 commands to Doxyfile.
* Fixed some unsynced return codes;
  Shortened use of full versions 2.1.0 to 2.1, etc.;
  Changed tagging of added return codes to be changes, not additions;
  Synced all changes from spec, except clarifications.

6+7 July - Andy
---------------

* Completed syncing the functions in cmpift.h with spec.
* Changed use of 'todo' command for spec issues to use the 'bug' command. Makes
  them show up in the Related Pages as "Bug List". These are the bugs that did
  not make it into the TOG review. Most of them, we should be able to live with.
* Updated the main page to reflect changes in the rest of the documentation.
* Updated Doxyfile to use a more straight forward project name and project brief
  description.
* Cleaned up the module level description for the CMPI convenience functions.
* Added and improved the introductory descriptions of encapsulated data types.
* Reordered encapsulated data types to by in sync with spec chapter order.
* Removed 'MB' before 'capabilities'.
* Reflected solutions to all TOG review issues that are marked with
 "Header files: DONE" in issue 69.

5 July - Andy
-------------

* Synced some more functions in cmpift.h with spec.
* Addressed the new issue CMPI-C15 that the size of the new CMPIArray object
  returned by newArray() was stated to be fixed, with no elements in the
  object. The text now confirms that these elements exist and that they are
  NULL.
* Addressed the new issue CMPI-A7 that MB functions stated that CMPIData.state
  had to set CMPI_badValue in case of error. This was changed to state that
  CMPIData.state is undefined.

5 July - Karl
-------------

* Broke macros into modules but probably not correctly  Did it by type
  of macro and it should probably also be by CMPIBroker, others separation.
  The types I have so far are:
      * convience functions that just cmpift.d call functions
      * convience functions that extend functionality beyond cmpift.h functions
      * provider initialization stubs.
  In particular, there are a couple of extending function way down in the
  broker section that do not show up correctly
* Continuing cleanup of existing functions. Note that I have kept @params in
  them but very short form.
* Trying to sort out how we do the stubs since 2.1 is different than 2.0 and
  we need both.  Not done and I have a question about the filtered functions.
* First pass at documenting macros done except for stubs.  They are
  broken.  NOTE: Have lots of todos to indicate Openpegasus usage. Need
  to do something with those.
3 July - Karl

* Cleanup to some of cmpimacs.
* review of Changes Andy proposed an discussion. We agreed that what is in
  issue 69 is what we want.
* Worked on issues in trying to get the stub macros extended to handle
  for 2.1.

3 July - Andy
-------------

* Updated the spec issues to be ready for ballot.
* Resolved all Todos from spec issues, except for one that I'd like to see
  approved first.
* Improved description of version-related preprocessor symbols in cmpidt.h and
  modules.h.
* Added brief description to modules.h to clarify that it is not part of the
  CMPI header files.
* Resolved spec issue D15: Description improvements for CMPI_RC_ERR_NOT_FOUND;
  Resolved leftovers of other spec issues;
  Brought more function descriptions in sync with spec.

2 July - Karl
-------------

* Cleaned up part of individual doc on cmpimacs.  Not yet finished but started
  to remove params from doc entries so that macros that are not one-one
  to functions have @params but the ones that are one-one do not but they
  reference the corresponding function. This is only about 1/3 done now.
* Fixed the macros that where the inline code was completely wrong. I started
  to use @note for some things like, noting that the inline code had been
  fixed in 2.1
* Added doc to cmpimacs defining the different kinds of convience functions
* Added examples to cmpimacs.h
* changed <ref> </ref> to @code(.c) and @endcode.  Note that this actually
  color codes syntax in the examples.
* NOTE: // style comments work in example code but NOT  /* */
* First cut and CMInstanceStub for 2.1 adding enumerateInstancesFiltered. Not
  done
* Added some @see statements for macros to cmpift.h. Change number of TODOs
  for adding macros to @note No macro for this function.
  Probably needs more.
* Ran removetrailingblanks and chksrc on headers and cleaned up some issues.

2 July - Andy
-------------

* Worked on specissues.md;
  Found more spec issues;
  Resolved most of the spec issues in the headers.
* Changed all remaining references to documents to be links to the corresponding
  entry in the References section of the main page.
* Moved @defgroup commands from cmpios.h to modules.h, for consistency.
* Moved @defgroup commands from cmpipl.h to modules.h, for consistency;
  Created new modules group for symbols definable by CMPI user and moved
  CMPI_PLATFORM_xxx and CMPI_VERSION into that group.
* Added descriptions to invocation flags, and fixed linking to them.
* Solved warnings with @capopsys comand. Was caused by using @parblock.
* Backed out addition of invalid handle code to MI functions.

1 July - Andy
-------------

* Solved 80 column issue in cmpipl.h.
* Improved description for platform symbols in cmpipl.h
* Changed check for a defined platform symbol to verify for exactly one.
* Moved file TemplateReturnCodes.txt in Dropbox workspace to parent dir to get
  it out of the way (it is not in the git repo)
* Pushed changes left by Karl in local repo of Dropbox to remote git:
  - in Dropbox workspace: pull (which did a merge), push
  - in Andys local workspace: pull
* Renamed updates.txt to updates.md
* Moved issues from ISSUES.md to a new doxygenissues.md
* Removed use of 'integral' on some types in cmpidt.h
* Improved the way test mask sections are linked in cmpidt.h
* Improved description of CMPIFlags by copying text from spec
* Resolved issue with 'type' argument in return code description of
  CMPIBrokerEncFT.classPathIsA()
* Resolved issues with missing '...' args in CMPIBrokerEncFT.getMessage() and
  CMPIBrokerEncFT.getMessage2()
* Resolved some more todos.
* Ordered @see always before any @addedNNN, @requiredNNN, @deprecated.
* Moved some spec related todos from header files to specissues.md.
* Brought introductory text in Errors section in sync with spec.
* Moved thread function typedefs into cmpidt.h and described spec update.
* Created special commands @capXXXXX for capabilities and used them.
* Moved issues from ISSUES.md to TODOs.md and as @todo into headers.

30 June - Karl
--------------

* Added links betwen cmpimacs and cmpift.h.  Not all of them work yet.
  In particular having problems with link to a macro (CMClone and CMRelease).
* Generally all the macros have links back (but not all show up yet) but that
  gives you a clue how many functions do not have macros at this point.
* I have to go through and manually check each one
* Added a number of todos where I have not made the macro link yet or no macro
  exists.
* Note that I started Issue 69, post final issues that we want to fix in spec.
  We can move specissues.md there as we agree which ones to fix.
* Removed a couple of completed TODOs but we still have a bunch to remove.
* Note that there is another issue in the macro about lines 120 -150 that
  causes warnings.
* ran chksrc and found lots of lines in cmpipl.h over 80 char.
* ran removetrailingblanks on cmpift.h and cmpimacs.h

Tomorrow, continue to clean up cmpimacs cmpift links.

Committed changes at end of day.

30 June 2015 - Andy
-------------------

1. Started syncing function descriptions with spec. TODO_AM indicates
   where this work needs to be resumed (top to bottom in cmpift.h).
2. Discovered several new spec issues (see specissues.md for a list of them
   and which ones are already addressed in the header files). This includes
   adding the filtered up-calls to the CMPIBrokerFT table, which we had
   forgotten so far.
3. Cleaned up descriptions of common function arguments, such as mb, mi, ctx,
   rc.
4. Cleaned up descriptions of return values that are CMPIStatus.
5. Changed a few remaining @retval to @return. @retval does not support
   @parblock.
6. Moved deprecation notes for deprecated return codes from the return code
   list to a function-level @deprecated statement, so it shows up in the
   deprecation list (@deprecated starts a top level section, so having it
   as part of the return code list does not work anyway).
7. Made all references to capabilities in the same way, so that the respective
   MB capabilities bit is linked.
8. Changed return code list into return code table for
   CMPIPropertyMIFT.getProperty(), to be consistent with the other MI functions.
9. Added @p to more arguments and structure members.
10. Replaced remaining textual statements about required functionality with the
   @required210 command.
11. Made sure that references to CMPI spec subclauses have either been replaced
   by linking to the corresponding linkable entity, or are explicitly called
   out to be to "Subclause x.x.x. of the CMPI Standard", where "CMPI Standard"
   links to the respective spot on the main page. There are some remaining
   ones that will be handled during description sync, they are marked with
   (TBD).
12. Made some deprecation notes more consistent.
13. Brought @see, @added, @required, and @deprecated into a consistent order.
14. Fixed a heading structure flaw in the Modules grouping hierarchy, for
    the newly introduced Thread related typedefs.
15. Fixed the 80 column limit in modules.h.
16. Removed some more completed TODOs.

29 June 2015 - Karl
-------------------

1. Clean up some minor issues in @returns and standardize the text so says
same thing in every case.
2. Clean up rc so same text everywhere.
3. Clean up a number of minor issues
4. Started @see between cmpimacs and cmpift.h working down cmpimacs. about
25% finished and will finish tomorrow. These go both ways cmpift<->cmpimacs

