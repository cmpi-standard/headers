// msgfile.c - Try out the formatting arguments for message file strings.

#if defined(__GNUC__)
#define CMPI_PLATFORM_LINUX_GENERIC_GNU
#elif defined(_MSC_VER)
#define CMPI_PLATFORM_WIN32_IX86_MSVC
#endif

#include <cmpift.h>
#include <cmpimacs.h>

extern CMPIBroker* broker;

void func()
{
    CMPIString *msg;
    CMPIStatus rc;
    CMPIMsgFileHandle fh;

    CMPIString * cmpiStr = CMNewString(broker, "a CMPIString", &rc);

    rc = CMOpenMessageFile(broker, "msgfile.txt", &fh);

    msg = CMGetMessage2(broker,
        "Common.CIMStatusCode.CIM_ERR_SUCCESS",
        fh,
        "Test $0 $1, $2, $3, $4, $5, $6, $7, $8",
        &rc,
        CMFmtArgs9(CMFmtChars("Sint32, Uint32, Sint64, Uint64, Real64,"
            " Boolean, chars, String :: "), CMFmtSint(-1),
            CMFmtUint(1), CMFmtSint64(-64), CMFmtUint64(64),
            CMFmtReal(64.64), CMFmtBoolean(1),
            CMFmtChars("chars"), CMFmtString(cmpiStr)));

    // . . . do something with msg

    rc = CMCloseMessageFile(broker, fh);
}
