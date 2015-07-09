// changetoenum.c - Verify compatibility of type change of level argument from
// int to enum CMPILevel in trace().

#if defined(__GNUC__)
#define CMPI_PLATFORM_LINUX_GENERIC_GNU
#elif defined(_MSC_VER)
#define CMPI_PLATFORM_WIN32_IX86_MSVC
#endif

#include <cmpift.h>

extern CMPIBroker* broker;

void test(void) {
    CMPIStatus status;

    int level = 3;   // old MI still using int; function now decl. with enum.
        
    status = broker->eft->trace(broker, level, NULL, NULL, NULL);
}
