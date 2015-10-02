CMPI headers project
====================

Purpose of this project
-----------------------

This project maintains the C/C++ header files of the OpenGroup CMPI Standard,
including the build process to generate the CMPI API documentation using
Doxygen.

If you just want to read the CMPI API documentation generated from the CMPI
header files, stop reading here and visit
[http://cmpi-wg.github.io](http://cmpi-wg.github.io).
That page also contains links to the published versions of the CMPI Standard.

CMPI stands for "Common Manageability Programming Interface" and is a C-language
API between a Management Broker (aka CIMOM) and Management Instrumentation (aka
Providers). CMPI supports the CIM and WBEM standards defined by
[DMTF](http://www.dmtf.org).
The CMPI Standard (that is, the standards document) is maintained on the
[CMPI Working Group web space](https://wiki.opengroup.org/councils-wiki/doku.php?id=forums:enterprise_management:cmpi:start)
of the [Open Group](http://www.opengroup.org/).

Status
------

At this point, version 2.1 of the CMPI Standard is being finalized, and the
CMPI header files are nearly done as well.


CMPI API documentation
----------------------

The CMPI header files are enabled for generating the CMPI API documentation
using Doxygen.

You can generate your own local copy of the CMPI API documentation by cloning
this (CMPI headers) project and by issuing `make build` in its work directory
(e.g. `$HOME/cmpi-headers.git`).
See the Makefile for any prerequisites. This will generate HTML output; entry
point for browsing the HTML output is the file `doxygen/html/index.html` within
the work directory.
Generation of LaTex output (e.g. for further processing into PDF) is disabled
by default but can be enabled via the GENERATE_LATEX parameter in the Doxyfile.

In order to publish the CMPI API documentation on
[http://cmpi-wg.github.io/](http://cmpi-wg.github.io/), follow these steps:

* Make sure the
  [CMPI pages project](https://github.com/cmpi-wg/cmpi-wg.github.io)
  has been cloned as well, so that its work directory is
  `../cmpi-wg.github.io.git` as seen from the work directory of this
  (CMPI headers) project (e.g. to `$HOME/cmpi-wg.github.io.git`).
  That location can be customized in the Makefile.

* In the work directory of this (CMPI headers) project
  (e.g. in `$HOME/cmpi-headers.git`), issue:

      make publish

  This will invoke Doxygen on the CMPI header files, create the HTML files
  for the CMPI API documentation, zip them up, and unpack the zip file
  into a subdirectory of the CMPI pages project.

  Neither the generated HTML files nor the zip file are tracked by Git in this
  project, so they do not need to be committed.

* In the work directory of the CMPI pages project
  (e.g. in `$HOME/cmpi-wg.github.io.git`), issue:

      git add --all .
      git commit -m "Updated CMPI 2.1.0 API files from cmpi-headers."

  or whatever the current CMPI version is.

  This will add any new files and remove any files that are no longer generated.

  Because this is a [GitHub pages project](https://pages.github.com),
  this will cause the new API documentation to be published on its corresponding
  web site [http://cmpi-wg.github.io/](http://cmpi-wg.github.io/) within a few
  seconds.


Feedback and contributions
--------------------------

Feedback on the CMPI header files is welcome. Please provide any feedback via
the [issue tracker](https://github.com/cmpi-wg/cmpi-headers/issues) of this
(CMPI pages) project.

Contributions to the CMPI header files are welcome as well, specifically
contributions to the examples in the function descriptions of the header files.
For now, it is suggested that contributions be made also via the issue tracker.

The Open Group rules on feedback and contributions apply, as documented in the
CMPI Standard.

Note that feedback on the CMPI Standard itself should be made as directed in
the CMPI Standard.

License
-------

See [LICENSE.md](LICENSE.md) (preliminary license)
