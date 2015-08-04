Issues with the CMPI Standard document
======================================

This is a list of issues/problems/etc with the final CMPI 2.1 Standard document.

Issues that are important for CMPI programmers to understand will be documented
using the Doxygen @bug command in the CMPI header files. Tose bugs are expected
to be released as an errata document at some point. Those bugs are not repeated
in this file.

The issues in this file are any other issues that do not fall into the category
mentioned above. They are usually minor or editorial issues, and given that
an OpenGroup errata document just lists the deltas to the standard document
(as opposed to releasing a new version of the standard document) these issues
are not expected to be released in an errata file, but are queued up here for
the next full release of the CMPI Standard.

* The following descriptions in the CMPI Standard document should be updated
  with the improved wording from the CMPI header file cmpift.h:
  - CMPIBrokerEncFT.newArray(): Function and size argument.
  - CMPIArray: Introductory description (replace first three paragraphs).
  - CMPIEnumeration: Introductory description (replace first two paragraphs).
  - CMPIInstance: Introductory description (add).
  - CMPIObjectPath: Introductory description (add).
  - CMPIArgs: Introductory description (replace first paragraph).
  - CMPIDateTime: Introductory description (replace first paragraph).
  - CMPIError: Introductory description (add).

* The following function descriptions in the CMPI Standard document should be
  updated in their description of the memory allocation / release rules
  to add a reference to Subclause 4.1.7:
  - CMPIBrokerMemFT.cmpiMalloc()
  - CMPIBrokerMemFT.cmpiCalloc()
  - CMPIBrokerMemFT.cmpiRealloc()
  - CMPIBrokerMemFT.cmpiStrDup()

* CMPIBrokerExtFT.exitThread():
  - In the CMPI Standard document, the change history of this function states
    that the function was added in CMPI 2.0. That needs to be corrected to
    state that only a description for the function was added in CMPI 2.0 (the
    function already existed in the function table in CMPI 1.0).

* CMPIArrayFT.getElementAt(), setElementAt():
  - Add the phrase "by index" to the description.

* CMPIInstanceFT.getProperty():
  - Add "by name" to the long description.

* CMPIInstanceFT.getPropertyAt():
  - Add "by index" to the long description, and change "index number" to
    "position" in the description of the index argument.

* CMPIInstanceFT.setProperty():
  - Add "by name" to the long description.

* CMPIInstanceFT.setObjectPath():
  - Change the first sentence of the description to use wording that is
    consistent with the short description.

* CMPIInstanceFT.setPropertyWithOrigin():
  - Add "and class origin" in the short and long descriptions. Add to the
    change history that the function was added in CMPI 2.0.

* CMPIObjectPathFT.setNameSpace(), setHostname(), setClassName(),
  setNameSpaceFromObjectPath(), setHostAndNameSpaceFromObjectPath():
  - Change "set or replace" to "set", in the short and long descriptions.

* CMPIPropertyMIFT.setProperty():
  - Change "set or modify" to "set" in the short and long descriptions.

* CMPIObjectPathFT.addKey():
  - Add "by name" to the long description.

* CMPISubCondFT.getCount():
  - Change "CMPISubCondFT object" to "CMPISubCond object" in the description of
    the sc argument.

* CMPISubCondFT.getPredicateAt():
  - Change "index" to "position" in the description of the index argument.

* CMPIInstanceFT.getPropertyAt():
  - Change "index number" to "position" in the description of the index
    argument.

* In the following CMPIErrorFT functions, update or add the paragraph defining
  the attribute:
  - getOtherErrorType()
  - getOwningEntity()
  - getMessageID()
  - getPerceivedSeverity()
  - getProbableCause()
  - getProbableCauseDescription()
  - getRecommendedActions()
  - getErrorSource()
  - getErrorSourceFormat()
  - getOtherErrorSourceFormat()
  - getCIMStatusCode()
  - getCIMStatusCodeDescription()
  - getMessageArguments()

* In the following CMPIErrorFT functions, add the paragraph about releasing the
  returned object:
  - getOtherErrorType()
  - getOwningEntity()
  - getMessage()
  - getProbableCauseDescription()
  - getErrorSource()
  - getOtherErrorSourceFormat()
  - getCIMStatusCodeDescription()
  - getMessageArguments()

* CMPIInstanceMIFT.enumerateInstancesFiltered():
  - Simplify the description of filterQueryLanguage for the case of NULL, to
    match the description in the header file.

* In the following MI functions, the explanation of the deprecated use
  of CMPI_RC_ERR_NOT_FOUND in the description of the instPath argument
  should be updated with the wording from the header file:
  - CMPIAssociationMIFT.associators()
  - CMPIAssociationMIFT.associatorNames()
  - CMPIAssociationMIFT.references()
  - CMPIAssociationMIFT.referenceNames()

* CMPIAssociationMIFT.associatorsFiltered(), referencesFiltered():
  - Simplify the description of filterQueryLanguage for the case of NULL, to
    match the description in the header file.
  - Fix the incorrect structure name in the description of the mi argument,
    from CMPIInstanceMI to CMPIAssociationMI.

* CMPIIndicationMIFT.authorizeFilter(), authorizeFilterCollection():
  - Change "Ask an MI to verify" to "Verify", in the short description.

* CMPIIndicationMIFT.deActivateFilter():
  - The lastDeActivation argument is incorrectly referenced as "lastActivation"
    in its description paragraph. Fix that by changing the name inthe
    description to "lastDeActivation".

* CMPIIndicationMIFT.activateFilter(), deActivateFilter(),
  authorizeFilterCollection(), deActivateFilterCollection():
  - The first paragraph of the function description lists two cases, the second
    of which is conditional. The sentence is a bit confusing, and that should
    be changed to use the list form of presenting the two options that is used
    in the header file.
