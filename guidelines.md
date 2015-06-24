Guidelines for documenting the CMPI header files
================================================

Choice of tools
---------------

CMPI header files are documented using Doxygen. Doxygen 1.8.6 is the minimum
version required.

Defining module structure
-------------------------

Doxygen output has a "Modules" section, which lists entities defined using
the doxygen `@defgroup` statement.

Doxygen orders these entities by their occurrence in the order of files parsed.
As a general guideline, we keep all @defgroup statements in a dummy header
file `modules.h`, that is parsed first (see `INPUT` parameter in `Doxyfile`).

Because the `modules.h` file is a normal header file, it can have C/C++
preprocessor statements for conditionally generating documentation. One use of
that is the documentation for `CMPISelectCondType` that depends on
`CMPI_DEFINE_CMPISelectCondType` being defined.

The code in the CMPI header files uses the `@addtogroup` statement to put
specific code sections into specific groups. That does not reorder the groups
in any way (unless a new group is defined that way).

Syntax choices
--------------

Doxygen allows for a number of equivalent syntactical choices. In the CMPI
header files, we use the following:

* Comment syntax for Doxygen statements uses `/**`, either with or without
  leading `*` on each line:

    /**
    <doxygen statements>
    */

    /**
     * <doxygen statements>
     */

* Doxygen statements are prefixed with `@`:

    @defgroup

Column limit
------------

In CMPI header files, we strictly apply a column limit of 80 characters.

The reason for this rule are projects that have checking on that (e.g.
OpenPegasus).

That does not apply to the dummy header file `modules.h`, because the
`@defgroup` statements it contains sometimes define lengthy titles and cannot be
split across multiple lines.

Conditional documentation generation
------------------------------------

If pieces of code in CMPI header files are conditionally generated, depending
on the definition of preprocessor symbols, their documentation (including
any statements in `modules.h`) must also be generated conditionally, using
the same preprocessor tests.

Consistency with the CMPI standard
----------------------------------

Nearly anything in the CMPI header files is also described in the CMPI standard.
The exception is deprecated material that was never part of the CMPI standard.

The description of anything in the header files must use the same wording as
the CMPI standard uses, except for the following adjustments:

* Description of function parameters.

  Generally, the text "The xxx argument" used in the CMPI standard is removed
  in the Doxygen description.

  For example, the following descriptions from the CMPI standard:

    The ar argument points to the CMPIArray object for this function.

    The rc output argument, if not NULL, points to a CMPIStatus structure that
    upon return will have been updated with the function return status.

  would become in the CMPI header file:

    @param ar Points to the CMPIArray object for this function.
    
    @param[out] rc If not NULL, points to a CMPIStatus structure that
        upon return will have been updated with the function return status.

