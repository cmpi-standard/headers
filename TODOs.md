LIST OF TODOs for CMPI header file Documentation
================================================

* TODO Karl: Test against a build.

* TODO Karl: Verify whether there are any remaining issues with using <> for
  the #include statements in the CMPI header files.

* DONE? Karl: Clean up cmpimacs.

  Status: Most links from macs back in place but not all working.  Many of the
  functions do not have macros.  Also lots of @todo add macros in cmpift.h
  as I worked my way through and I have to weed those out.

  Status: Any remaining issues are documented in the header files as @todo.
  The Examples question is a separate item in this file here.
  This item here can be closed, IMO.

* DONE Karl: Make decision about the poor doc in macro files. Remove much of it,
  make same as cmpift, or leave it.

  Discuss on telecon.

  Telecon 7/1: Direction was to minimize documentation to brief description and
  see to the underlying function, unless that is not possible.

  Status: DONE

* TBD Karl: This stuff cries out for examples.

  Discuss next telecon.

* TBD Both: Review order of sections for functions described in guidelines.md.

  Discuss next telecon.

* TBD Both: Review outline of Related Pages, outline of Modules tabs, and main
  page content.

  Discuss next telecon.

* DONE Andy: Move those @bug entries that are editorial or would otherwise not
  go into an errata release, from being a @bug entry to some file.

  Status: DONE

* NOTE: The close date for this work is actually shortly before the final
  release of the spec at end of July.

* TODO Both: figure out how we can get this mess of files into a web without
  uploading the many hundreds of files. Or into the wiki with the same issue.
  The manual upload tools these sites offer are not really logical for this
  large set of files that may change from time to time.

  Andy: I looked at readthedocs.org, and while not officially supported yet, it
  seems to be possible to use Doxygen there. They clone the repo and build the
  docs for themselves, as an automated process.
  The repo has to be public.

  KS: For some reason, (I have not received an answer that makes sense) OpenGroup
  was opposed to putting the headers on github so my guess is that they have
  issues with this also. His comment was:

* NOTE: Response from M.Kirk about using github:

    We have justs conducted a small experiment with using Github for development in
    another Forum, and the problem is that it puts it outside of our SSO
    environment, and that makes it difficult for meeting our rules on access
    to all Open Group members.

    I would therefore counsel against this.

    regards,

    Martin

  Therefore I am going elsewhere in OpenGroup to see if we can get better answer.
