3 July - Andy
-------------

* Updated the spec issues to be ready for ballot.
* Resolved all Todos from spec issues, except for one that I'd like to see
  approved first.
* Improved description of version-related preprocessor symbols in cmpidt.h and
  modules.h.

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

