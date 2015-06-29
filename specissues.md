Changes during finalization of the CMPI specification
=====================================================

1. Global change of "CMPIBroker object" to "CMPIBroker structure". The former occurs 15 times, the latter already 52 times.

2. The description fix mentioned on the mailing list

3. In prepareAttachThread, we wanted to remove the error codes, but failed to
   apply the CR correctly.
   Replace the content of the ERRORS section with:
   "For historical reasons, 
   no additional error information is passed back."
	
