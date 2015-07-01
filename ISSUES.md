KNOWN/Possible Issues
=====================

This is a list of issues/problems/etc with the documentation.  It is intended
to just list those things that are not specific and could be listed by
@todo in the headers.


* The macro page is a mess in Doxygen
  KS: In Process. Want to discuss the doc in macs

* Needs lead page before going on line but that is not issue for the
  headers themselves.

  AM: Done, by using mainpage.md? Agreed. Karl

* The Modules list is really incomprenensible.  Somehow we need to organize
  and describe the modules doc definitions better.  Also, apparently doxygen
  does this all as one line entries so that one of them just shows up as

  "Definition of symbols for"

  since that is all that is on the first line.

  AM: Is that issue still current? We organized the Modules list to be
      consistent with the spec, and I did not find a "Definition of symbols for"
      at all.
  KS: I think this one resolved.

* This stuff cries out for examples.

  AM: Where?
  KS: Discuss next telecon.

* There is a more... hyperlink in a number of places but nothing behind it
  apparently

  AM: Where?
  KS: Think you really cleaned most of that up.

* See C Data Types for CIM Data Types (Subclause 5.4).  Why the more...
  What does it mean?

  AM: It means there is description in addition to the brief description.
  KS: Will recheck but in some cases there was nothing.  That was the confusion.

* Note that typedef is a tile but that CMPIString, etc. show up under it
  Andy has a TODO for that one

  AM: With the use of typedef on the full struct definition, we now have
  consistent linking, and the typedef names show up consistently in
  "Data Structures". The struct tag names do not appear anymore at all, however.

* Why doesn't CMPIString show up in the general list of Typedefs.

  AM: Old comment? It does now. See previous issue.
  KS: Agreed. DONE

* Inconsistent in using out.  The original definition for args that were output
  was either nothing or Output: as the first word.  Doxygen offers a form
  @param[...]  where ... can be in, out or in,out.  I modified some as a test.
  Not great looking but it is doxygen (put the out before the name in html).

  AM: Agree on using "@param [xxx]".
  KS: Complete for the rc but I think that there were some other out args
      that we will find. With info in guidelines lets mark this DONE

* CMPI flags.  Use of word integral.  Is that the word we want?

  Also in this section there is statement "Test masks for CMPIFlags are
  defined here" with here a hyperlink.  But it goes nowhere.

  AM: DONE, removed 'integral' and improved linking to test masks, for
  all occurrences.
  KS: Another one to close.

* modules.h shows up in file list of HTML output (Files tab).

* Should we use @since instead of @version for indicating that a function was
  added? From its description, seems to match better:
  http://www.stack.nl/~dimitri/doxygen/manual/commands.html#cmdsince

  AM: Done, by using our own @addedNNN commands.
  KS: Agreed DONE
