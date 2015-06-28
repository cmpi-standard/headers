KNOWN/Possible Issues:
=====================


This is a list of issues/problems/etc with the documentation.  It is intended
to just list those things that are not specific and could be listed by
@todo in the headers.
* Shows prototype as :

  CMPIStatus(* _CMPIIndicationMIFT::activateFilter)(CMPIIndicationMI *mi, const CMPIContext *ctx, const CMPISelectExp *filter, const char *className, const CMPIObjectPath *classPath, CMPIBoolean firstActivation)

  Note that ::  is a scoping definition but it is confusing.

* The macro page is a mess in Doxygen

* Needs lead page before going on line but that is not issue for the
   headers themselves.


* The Modules list is really incomprenensible.  Somehow we need to organize
   and describe the modules doc definitions better.  Also, apparently doxygen
   does this all as one line entries so that one of them just shows up as

   "Definition of symbols for"

   since that is all that is on the first line.

* The function APIs are documented as Variables, not functions.  I assume that
   this is because of the indirect definition. Looks like Doxygen cannot
   handle this.

* This stuff cries out for examples.

* There is a more... hyperlink in a number of places but nothing behind it apparently


* See C Data Types for CIM Data Types (Subclause 5.4).  Why the more...
what does it mean

* Note that typedef is a tile but that CMPIString, etc. show up under it
Andy has a TODO for that one

* Why doesn't CMPIString show up in the general list of Typedefs.

* Inconsistent in using out.  The original definition for args that were output was either nothing or Output: as the first word.  Doxygen offers a form
@param[...]  where ... can be in, out or in,out.  I modified some as a test. Not great looking but it is doxygen (put the out before the name in html).

* CMPI flags.  Use of word integral.  Is that the word we want? Also in this section there is statement "Test masks for CMPIFlags are defined here" with here a hyperlink.  But it goes nowhere.
