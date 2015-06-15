Common Manageability Programming Interface (CMPI) - Header Files
================================================================

![The Open Group Logo](../resources/tog_logo.png)

This online documentation has been generated from the header files of the
Open Group Standard:

<div style="margin-left:20px">
  **Systems Management: Common Manageability Programming Interface (CMPI),
  Issue 2, Version 1**<br/>

  ISBN: **TBA**<br/>
  Document Number: **TBA**<br/>
  Published by The Open Group, **Month** 2015<br/>
</div>

This standard is referred to as "CMPI Standard" in this online documentation.

Comments relating to the CMPI Standared, to this online documentation, or to
the CMPI header files may be submitted to:

<div style="margin-left:20px">
  The Open Group<br/>
  Apex Plaza, Forbury Road<br/>
  Reading, Berkshire, RG1 1AX<br/>
  United Kingdom<br/>
</div>

or by electronic mail to:

<div style="margin-left:20px">
  ogspecs@opengroup.org<br/>
</div>

This online documentation refers to subclauses of the CMPI Standard using the
following notation:

<div style="margin-left:20px">
  Subclause x.y
</div>

The subclause numbers belong to the above-mentioned version of the CMPI
Standard.

Structure of this online documentation
--------------------------------------

The [Related Pages](pages.html) tab (at the top of this page) provides
automatically generated lists, such as a to-do list and a list of deprecated
elements as of this version of the CMPI Standard.

The [Modules](modules.html) tab attempts to resemble the heading structure of
the CMPI Standard as much as possible. It should be used as a general entry
point, unless you know exactly what you are looking for.

The [Data Structures](annotated.html) tab provides an alphabetically sorted list
of all structures and unions of the CMPI standard, and of their data fields.
If there is a typedef for a structure or union, sometimes they are listed by
their typedef identifier instead of their structure or union tag. However, that
is not always done consistently (courtesy to the tool that is used for
generating the online documentation).
This list does not contain any enumerations, preprocessor symbols, or typedefs
that are unrelated to structures or unions.

The [Files](files.html) tab lists the CMPI header files, and with each of them,
the list of data structures (structs and unions), macros (including symbols),
typedefs, and enumerations. There is also an alphabetically sorted list of
globals.

C/C++ Language Considerations and Header Files (Subclause 4.7)
--------------------------------------------------------------

CMPI is a C Language API. The CMPI header files are usable for both C and C++.
The minimum language level that is required for CMPI is C99. However, not all
language features of C99 are used in the CMPI header files.

The CMPI header files are:

  * `cmpift.h` - Defines the various CMPI structures and function tables; all
    MIs should include this header; is included by `cmpimacs.h`.
  * `cmpidt.h` - Defines CMPI data types; is included and used by `cmpift.h` and
    `cmpimacs.h`.
  * `cmpios.h` - OS-specific defines (for threading structures, etc.); is
    included by `cmpift.h`.
  * `cmpipl.h` - Platform checker. This header verifies that a valid
    CMPI_PLATFORM has been specified; is included by `cmpidt.h` and `cmpios.h`.
  * `cmpimacs.h` - CMPI macro functions. A set of macro functions to ease the
    use of the various function tables.

For the benefit of developers, copies of these header files are downloadable
from the CMPI website
([http://www.opengroup.org/tech/management/cmpi](www.opengroup.org/tech/management/cmpi)).
These files are provided as a convenience only. In the case of any discrepancy
between the header files and the CMPI Standard (incorporating any subsequent
Technical Corrigenda), the CMPI Standard shall be definitive.

The following CMPI-related C preprocessor symbols can be set by users of the
CMPI header files:

  * @ref sym-version "CMPI_VERSION"

    CMPI version that is implemented by an MB or MI, as a numeric
    CMPI version (see Subclause 1.6).

    The CMPI header files define a default for this symbol, which is the
    current version of CMPI.

  * @ref sym-platform-xxx "CMPI_PLATFORM_<os>_<mach>_<comp>"

    Platform for which CMPI is compiled.
    <os> indicates the operating system, <mach> indicates the machine
    architecture, <comp> indicates the C/C++ compiler.

    The following platform symbols (defined in `cmpipl.h`) are valid.
    There is no default platform; one of these symbols must be defined by users
    of CMPI:

      - CMPI_PLATFORM_LINUX_GENERIC_GNU
      - CMPI_PLATFORM_HPUX_ACC
      - CMPI_PLATFORM_WIN32_IX86_MSVC
      - CMPI_PLATFORM_SOLARIS_SPARC_GNU
      - CMPI_PLATFORM_SOLARIS_SPARC_CC
      - CMPI_PLATFORM_AIX_RS_IBMCXX
      - CMPI_PLATFORM_ZOS_ZSERIES_IBM
      - CMPI_PLATFORM_TRU64_ALPHA_DECCXX
      - CMPI_PLATFORM_OS400_ISERIES_IBM
      - CMPI_PLATFORM_DARWIN_PPC_GNU
      - CMPI_PLATFORM_VMS_ALPHA_DECCXX
      - CMPI_PLATFORM_VMS_IA64_DECCXX

The following C preprocessor symbols can be used for exporting and importing
symbols from and to load libraries and programs:

  * @ref sym-extern-c "CMPI_EXTERN_C"

    Modifier for specifying the linkage of C functions that are
    to be exported from MI load libraries (in both C and C++ compile mode). This
    modifier (or an equivalent modifier) needs to be specified on the MI factory
    functions provided by MI load libraries (see Subclause 6.2). MB functions
    and other MI functions do not need to specify this modifier.

  * @ref sym-export "CMPI_EXPORT"

    Modifier for specifying the linkage of functions and data that
    are to be made visible (“exported”) to users of a load library when
    compiling that load library.
    The compile mode (C versus C++) needs to match between the exporter and
    the importer (see @ref sym-import "CMPI_IMPORT").
    CMPI-related data or functions do not need to be exported by MBs or MIs
    using this modifier; however, it can be used for non-CMPI-related purposes.

  * @ref sym-import "CMPI_IMPORT"

    Modifier for specifying the linkage of functions and data that
    are used (“imported”) by a program or load library, when compiling that
    program or load library.
    The compile mode (C versus C++) needs to match between the exporter and
    the importer (see @ref sym-export "CMPI_EXPORT").
    CMPI-related data or functions do not need to be imported by MBs or MIs
    using this modifier; however, it can be used for non-CMPI-related purposes.

