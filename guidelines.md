Guidelines for documenting the CMPI header files
================================================

Choice of tools
---------------

CMPI header files are documented using Doxygen. Doxygen 1.8.6 is the minimum
version required.

Defining module structure
-------------------------

Doxygen output has a "Modules" section, which lists entities defined using
the doxygen @defgroup statement.

Doxygen orders these entities by their occurrence in the order of files parsed.
As a general guideline, we keep all @defgroup statements in a dummy header
file modules.h, that is parsed first (see INPUT parameter in Doxyfile).

Because the modules.h file is a normal header file, it can have C/C++
preprocessor statements for conditionally generating documentation. One use of
that is the documentation for CMPISelectCondType that depends on
CMPI_DEFINE_CMPISelectCondType being defined.

The code in the CMPI header files uses the @addtogroup statement to put
specific code sections into specific groups. That does not reorder the groups
in any way (unless a new group is defined that way).

Syntax choices
--------------

Doxygen allows for a number of equivalent syntactical choices. In the CMPI
header files, we use the following:

* Comment syntax for Doxygen statements uses `/**`, either with or without
  leading `*` on each line:

  <pre>
  /**
   doxygen description
   of functions
  */

  /**
   * doxygen description
   * of other constructs
   */
  </pre>

* Doxygen keywords are prefixed with `@` (not with `\`):

  <pre>
  @defgroup
  </pre>

Column limit
------------

In CMPI header files, we strictly apply a column limit of 80 characters.

The reason for this rule are projects that have checking on that (e.g.
OpenPegasus).

That does not apply to the dummy header file modules.h, because the
@defgroup statements it contains sometimes define lengthy titles and cannot be
split across multiple lines.

Conditional documentation generation
------------------------------------

If pieces of code in CMPI header files are conditionally generated, depending
on the definition of preprocessor symbols, their documentation (including
any statements in modules.h) must also be generated conditionally, using
the same preprocessor tests.

Links
-----

The goal is that every occurrence of a C/C++ name in the Doxygen output is a
link to its definition, with the following exceptions:

* The occurrence of the name within its definition. Such occurrences should
  become monospaced, by using backquotes (\`).

* Long comma-separated lists of names that are not automatically generated as
  links. Instead of turning each one of them into a link, a phrase like
  `(see @ref sectionname)` can be added, referencing the section in which they
  are defined.

* CMPI function return status values, e.g. CMPI_RC_OK. Those should be tagged
  to become monospaced, using backquotes (\`).

Doxygen attempts to automatically generate all C/C++ names to be links to their
definition. However, there are circumstances under which Doxygen does not do
that and shows just the name without any special formatting. For those names,
we apply special syntax to turn them into links. The following such
circumstances are known:

* Names of typedefs for CMPI encapsulated data types,
  e.g. CMPIString.

  This is probably caused by the fact that the data type name
  is a typedef name, and that the typedef is defined in a C/C++ statement
  separate from the struct definition.

  Use the following Doxygen syntax for those:

  <pre>
  @ref _CMPIString "CMPIString"
  </pre>

* Names of typedefs for enum types, e.g. CMPIrc.

  It is not clear what causes this not to work automatically. For all enums in
  CMPI, their typedef is defined in the same C/C++ construct where the
  enum is defined, so it is consistent with combined typedef / struct
  constructs, for which Doxygen does generate the links automatically.
  Possibly this is a Doxygen bug.

  Use the following Doxygen syntax for those:

  <pre>
  @ref CMPIrc
  </pre>

* Names of functions with their function table names in dot notation,
  e.g. CMPIContext.release().

  This is caused by the fact that using the dot notation with the typedef name
  is simply incorrect C/C++. We did not want to change that in the CMPI
  standard, and for consistency we continue to use that syntax in the
  CMPI header files.

  Use the following Doxygen syntax for those:

  <pre>
  @ref _CMPIContextFT::release "CMPIContextFT.release()"
  </pre>

  That syntax allows splitting the line, if the identifiers are too long for
  the column limit:
  
  <pre>
  @ref _CMPIContextFT::release
  "CMPIContextFT.release()"
  </pre>

Consistency with the CMPI standard
----------------------------------

Nearly anything in the CMPI header files is also described in the CMPI standard.
The exception is deprecated material that was never part of the CMPI standard.

The description of anything in the header files must use the same wording as
the CMPI standard uses, except for the following adjustments:

* Description of function parameters.

  Generally, the phrase "The xxx argument" used in the CMPI standard is removed
  in the Doxygen description.

  For example, the following descriptions from the CMPI standard:

    * The ar argument points to the CMPIArray object for this function.

    * The rc output argument, if not NULL, points to a CMPIStatus structure that
      upon return will have been updated with the function return status.

  would become in the CMPI header file:

  <pre>
  @param ar Points to the CMPIArray object for this function.
  @param[out] rc If not NULL, points to a CMPIStatus structure that
      upon return will have been updated with the function return status.
  </pre>

* Mentioning of function names.

  Phrases like the following in the CMPI standard:

    * ... the CMPIArrayFT.getSize() function ...

  would become in the CMPI header file:
  
  <pre>
  ... `CMPIArrayFT.getSize()` ...
  </pre>

Return values
-------------

**TODO_KS:** Karl comes up with a proposal

Other
-----

* @brief needs a period at the end of a sentence, and an empty line following
  it.

* We use @li for list items, particularly for function status.

  Make sure the preceding line does not have any trailing spaces; Doxygen is a
  bit picky there and sometimes ignores the @li in the presence of trailing
  spaces on the preceding line.

* We use the backquote (\`) for generating fixed font text for names that are
  not intended to become links, e.g. \`CMPI_RC_OK\`.
 
