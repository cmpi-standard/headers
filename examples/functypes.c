// functypes.c - Try out the function typedefs.

#if defined(__GNUC__)
#define CMPI_PLATFORM_LINUX_GENERIC_GNU
#elif defined(_MSC_VER)
#define CMPI_PLATFORM_WIN32_IX86_MSVC
#endif

#include <cmpift.h>

CMPI_THREAD_RETURN CMPI_THREAD_CDECL threadfunc(void* parm) {
  return 0;
}

extern CMPIBroker* broker;

void test(void) {
    CMPI_THREAD_TYPE thd;

    thd = broker->xft->newThread(threadfunc, 0, 0);
}
