LIST OF TODOs for CMPI header file Documentation
================================================

* Karl: Test against a build.

* Karl: Clean up cmpimacs.

  Status: Most links from macs back in place but not all working.  Many of the
  functions do not have macros.  Also lots of @todo add macros in cmpift.h
  as I worked my way through and I have to weed those out.

  Status: Any remaining issues are documented in the header files as @todo.
  The Examples question is a separate item in this file here.
  This item here can be closed, IMO.

* Karl: Make decision about the poor doc in macro files. Remove much of it, make
  same as cmpift, or leave it.

  Discuss on telecon.

  Telecon 7/1: Direction was to minimize documentation to brief description and
  see to the underlying function, unless that is not possible.

  Status: DONE

* Karl: This stuff cries out for examples.

  Discuss next telecon.

* Andy: Move those @bug entries that are editorial or would otherwise not go
  into an errata release, from being a @bug entry to some file.

  Discuss next telecon.

* NOTE: The close date for this work is actually shortly before the final release
  of the spec at end of July.

* Both: figure out how we can get this mess of files into a web without
  uploading the many hundreds of files. Or into the wiki with the same issue.
  The manual upload tools these sites offer are not really logical for this
  large set of files that may change from time to time.

  Andy: I looked at readthedocs.org, and while not officially supported yet, it
  seems to be possible to use Doxygen there. They clone the repo 