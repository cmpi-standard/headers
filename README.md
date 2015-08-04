CMPI header files
=================

This Github project maintains the C/C++ header files of the OpenGroup CMPI
Standard.

CMPI stands for "Common Manageability Programming Interface" and is a C-language
API between a Management Broker (aka CIMOM) and Management Instrumentation (aka
Providers). CMPI supports the CIM and WBEM standards defined by
[DMTF](http://www.dmtf.org).

The CMPI Standard (that is, the document) is maintained on the
[CMPI Working Group web space](https://wiki.opengroup.org/councils-wiki/doku.php?id=forums:enterprise_management:cmpi:start).

The CMPI header files are enabled for generating documentation using Doxygen.
You can generate your own copy of the CMPI documentation by cloning this Github
repository and running the `doxygen` command in the project's root directory,
after creating a 'doxygen' output directory. It requires Doxygen v1.8.6 or
higher and being on a Linux system. This will generate HTML output (open
doxygen/html/index.html) and LaTex output for further processing into PDF (see
doxygen/latex/).
 
The CMPI header files are also published on
[cmpi-headers.readthedocs.org](https://cmpi-headers.readthedocs.org/). They are
updated automatically whenever files are changed in this Github project.
However, the generated HTML is not as nice as the direct Doxygen-generated HTML
at this point. We are working to improve that, but for now you're better off by
generating the Doxygen HTML yourself.

Status
------

At this point, version 2.1 of the CMPI Standard is being finalized, and the
CMPI header files are nearly done as well.

Feedback and contributions
--------------------------

Feedback on the CMPI header files is welcome. Please provide any feedback via
the [issue tracker](./issues) of this Github project.

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
