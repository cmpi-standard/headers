Issues with Doxygen
-------------------

Here are some issues with and possible improvement for Doxygen, all in context
of CMPI header files (C/C++).

* Function pointer prototypes are shown using the "::" scoping notation:

    `CMPIStatus(* CMPIIndicationMIFT::activateFilter)(CMPIIndicationMI *mi,
     const CMPIContext *ctx, const CMPISelectExp *filter,
     const char *className, const CMPIObjectPath *classPath,
     CMPIBoolean firstActivation)`

  Note that "::" is a scoping definition, so it is right, but it is also
  confusing.

  More ideal would be the dot notation:

    `CMPIStatus(* CMPIIndicationMIFT.activateFilter)...`

  which would be in sync with how we reference functions in the CMPI Standard.

  Note that Doxygen does support referencing such functions with:

    `CMPIIndicationMIFT.activateFilter()`

  Does Doxygen support styles where this can be configured?

* The function APIs are documented as variables, not as functions.

  I assume that this is because of the indirect definition. Looks like
  Doxygen cannot handle this.

* Use of @parblock for parameters triggers a new "Parameters" section heading
  for any subsequent parameters of the function.

  This is probably fixed in Doxygen 1.8.10 (needs verification), see:
  https://github.com/doxygen/doxygen/blob/master/testing/054_parblock.cpp

* When defining a preprocessor symbol using PREDEFINED, it is no longer
  recognized to be a defined symbol. This becomes an issue when a header
  designs the symbol to be set by the user, and defines a default in the header
  file if the symbol is not set. Doxygen accepts such a conditional definition
  as a valid definition for the symbol, but when the symbol is set outside via
  PREDEFINED, it no longer recognizes that there is a definition, does not
  generate the documentation for the symbol, and issues a warning when @def
  is used in the description section for the symbol.

* There is no way to generate parts of a description section conditionally on
  a preprocessor symbol (e.g. one that specifies a version of the interface
  defined by the header file). The #ifdef construct works to exclude a part
  of a description, but the excluded part and the part after that are not
  considered a part of the original section.
