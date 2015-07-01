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

