KNOWN/Possible Issues
=====================

This is a list of issues/problems/etc with the documentation.  It is intended
to just list those things that are not specific and could be listed by
@todo in the headers.

* At least some of 210 functions not showing up in html output. There is a
  @todo for enumerateInstancesFiltered

  AM: Fixed for enumerateInstancesFiltered (last line of prototype deleted by
      accident).

* Shows prototype as :

  CMPIStatus(* _CMPIIndicationMIFT::activateFilter)(CMPIIndicationMI *mi, const CMPIContext *ctx, const CMPISelectExp *filter, const char *className, const CMPIObjectPath *classPath, CMPIBoolean firstActivation)

  Note that ::  is a scoping definition but it is confusing.

  AM: Unless we dig into Doxygen styles, we should accept that for now. Maybe
  something for a list of Doxygen improvements.

* The macro page is a mess in Doxygen

* Needs lead page before going on line but that is not issue for the
  headers themselves.

  AM: Done, by using mainpage.md?

* The Modules list is really incomprenensible.  Somehow we need to organize
  and describe the modules doc definitions better.  Also, apparently doxygen
  does this all as one line entries so that one of them just shows up as

  "Definition of symbols for"

  since that is all that is on the first line.

  AM: Is that issue still current? We organized the Modules list to be
      consistent with the spec, and I did not find a "Definition of symbols for"
      at all.

* The function APIs are documented as Variables, not functions.  I assume that
  this is because of the indirect definition. Looks like Doxygen cannot
  handle this.

  AM: I don't think we can change this. I suggest we move this to a list
      of potential Doxygen improvements.

* This stuff cries out for examples.

  AM: Where?

* There is a more... hyperlink in a number of places but nothing behind it
  apparently

  AM: Where?

* See C Data Types for CIM Data Types (Subclause 5.4).  Why the more...
  What does it mean?

  AM: It means there is description in addition to the brief description.

* Note that typedef is a tile but that CMPIString, etc. show up under it
  Andy has a TODO for that one

  AM: With the use of typedef on the full struct definition, we now have
  consistent linking, and the typedef names show up consistently in
  "Data Structures". The struct tag names do not appear anymore at all, however.

* Why doesn't CMPIString show up in the general list of Typedefs.

  AM: Old comment? It does now. See previous issue.

* Inconsistent in using out.  The original definition for args that were output
  was either nothing or Output: as the first word.  Doxygen offers a form
  @param[...]  where ... can be in, out or in,out.  I modified some as a test.
  Not great looking but it is doxygen (put the out before the name in html).

  AM: Do we

* CMPI flags.  Use of word integral.  Is that the word we want?

  Also in this section there is statement "Test masks for CMPIFlags are
  defined here" with here a hyperlink.  But it goes nowhere.

* modules.h shows up in file list of HTML output (Files tab).

* Should we use @since instead of @version for indicating that a function was
  added? From its description, seems to match better:
  http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsince

* Use of @parblock for parameters triggers a new "Parameters" section heading
  fopr any subsequent parameters of the function.
  This is probably fixed in Doxygen 1.8.10 (needs verification), see:
  https://github.com/doxygen/doxygen/blob/master/testing/054_parblock.cpp
