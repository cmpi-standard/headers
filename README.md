CMPI headers project
====================

Purpose of this project
-----------------------

This project maintains the C/C++ header files of the OpenGroup CMPI Standard,
including the build process to generate the CMPI API documentation using
Doxygen.

If you just want to read the CMPI Standard or the CMPI API documentation, or
download the CMPI header files, or if you just want to learn what CMPI is,
stop reading here and visit
[http://cmpi-wg.github.io](http://cmpi-wg.github.io).

That web site is maintained via the
[CMPI pages project](https://github.com/cmpi-wg/cmpi-wg.github.io).

How to generate the CMPI API documentation
------------------------------------------

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
      git push

  Adjust the commit comment to whatever the current CMPI version is.

  This will add any new files and remove any files that are no longer generated.

  Because this is a [GitHub pages project](https://pages.github.com),
  this will cause the new API documentation to be published on its corresponding
  web site [http://cmpi-wg.github.io/](http://cmpi-wg.github.io/) within a few
  seconds.

License
-------

See [LICENSE.md](LICENSE.md) (preliminary license)
