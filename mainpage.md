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

The specification is available from the OpengGroup at:
    **TBA**

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
The minimum language level that is required for CMPI is C99 (see
@ref ref-iso-iec-9899-1999 "ISO/IEC 9899:1999"). However, not all language
features of C99 are used in the CMPI header files.

The CMPI header files are:

  * `cmpift.h` - Defines the various CMPI structures and function tables; all
    MIs should include this header; is included by `cmpimacs.h`.
  * `cmpidt.h` - Defines CMPI data types; is included and used by `cmpift.h` and
    `cmpimacs.h`.
  * `cmpios.h` - OS-specific defines (for threading structures, etc.); is
    included by `cmpift.h`.
  * `cmpipl.h` - Platform checker. This header verifies that a valid
    CMPI_PLATFORM_{xxx} symbol has been defined; is included by `cmpidt.h`
    and `cmpios.h`.
  * `cmpimacs.h` - CMPI macro functions. A set of macro functions to ease the
    use of the various function tables.

For the benefit of developers, copies of these header files are downloadable
from the CMPI website
([www.opengroup.org/tech/management/cmpi](http://www.opengroup.org/tech/management/cmpi)).
These files are provided as a convenience only. In the case of any discrepancy
between the header files and the CMPI Standard (incorporating any subsequent
Technical Corrigenda), the CMPI Standard shall be definitive.

The following CMPI-related C preprocessor symbols can be set by users of the
CMPI header files:

  * @ref sym-version "CMPI_VERSION"

    CMPI version that is implemented by an MB or MI, as a numeric CMPI version
    (see Subclause 1.6).

    The default for this symbol is the current version of CMPI
    (see @ref sym-current-version "CMPICurrentVersion").

  * @ref sym-platform "CMPI_PLATFORM_{xxx}"

    The platform for which CMPI is compiled.

    There is no default platform; one of the platform symbols must be defined
    by users of CMPI. See @ref sym-platform for details.

References
----------

  * @anchor ref-ansi-ieee-754
    ANSI/IEEE Std 754-1985: *IEEE Standard for Binary Floating-Point
    Arithmetic*, August 1985;<br/>
    http://ieeexplore.ieee.org/xpl/freeabs_all.jsp?arnumber=30711

  * @anchor ref-dmtf-dsp0004
    DMTF DSP0004: *CIM Infrastructure*, Version 2.8.0;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0004_2.8.0.pdf

  * @anchor ref-dmtf-dsp0200
    DMTF DSP0200: *CIM Operations over HTTP*, Version 1.4.0;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0200_1.4.0.pdf

  * @anchor ref-dmtf-dsp0201
    DMTF DSP0201: *Representation of CIM in XML*, Version 2.4.0;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0201_2.4.0.pdf

  * @anchor ref-dmtf-dsp0202
    DMTF DSP0202: *CIM Query Language Specification*, Version 1.0.0;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0202_1.0.0.pdf

  * @anchor ref-dmtf-dsp0212
    DMTF DSP0212: *Filter Query Language*, Version 1.0.1;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0212_1.0.1.pdf

  * @anchor ref-dmtf-dsp0223
    DMTF DSP0223: *Generic Operations*, Version 1.1.0;<br/>
    http://www.dmtf.org/standards/published_documents/DSP0223_1.1.0.pdf

  * @anchor ref-dmtf-dsp0228
    DMTF DSP0228: *Message Registry XML Schema*, Version 1.2.0;<br/>
    http://schemas.dmtf.org/wbem/messageregistry/1/dsp0228_1.2.0.xsd

  * @anchor ref-dmtf-dsp1054
    DMTF DSP1054: *Indications Profile*, Version 1.2.2;<br/>
    http://www.dmtf.org/standards/published_documents/DSP1054_1.2.2.pdf

  * @anchor ref-dmtf-dsp8016
    DMTF DSP8016: *WBEM Operations Message Registry*, Version 1.1.0;<br/>
    http://schemas.dmtf.org/wbem/messageregistry/1/dsp8016_1.1.0.xml

  * @anchor ref-ieee-1003-1
    IEEE 1003.1-2008: *Standard for Information Technology – Portable Operating
    System Interface (POSIX)*;<br/>
    http://www.opengroup.org/onlinepubs/9699919799/

  * @anchor ref-ietf-rfc-2616
    IETF RFC 2616: *Hypertext Transfer Protocol – HTTP/1.1*, June 1999;<br/>
    http://tools.ietf.org/html/rfc2616

  * @anchor ref-iso-iec-646-1991
    ISO/IEC 646:1991: *Information Technology – ISO 7-bit Coded Character Set
    for Information Interchange*;<br/>
    http://www.iso.org/iso/catalogue_detail.htm?csnumber=4777

  * @anchor ref-iso-iec-9899-1999
    ISO/IEC 9899:1999: <em>(C99) Programming Languages – C</em>;<br/>
    http://www.iso.org/iso/catalogue_detail.htm?csnumber=29237
