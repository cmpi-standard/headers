// Instance MI using the MI factory stub macros for plain C.

#if defined(__GNUC__)
#define CMPI_PLATFORM_LINUX_GENERIC_GNU
#elif defined(_MSC_VER)
#define CMPI_PLATFORM_WIN32_IX86_MSVC
#endif

#include <cmpimacs.h>

static const CMPIBroker *_broker;

static CMPIStatus MyProvInstanceInitialize(
    CMPIInstanceMI *mi,
    const CMPIContext *ctx)
{
    // ... Initialization code when loading the MI load library

    mi->hdl = NULL; // You can store data in the CMPIInstanceMI object

    if (1)
        CMReturn(CMPI_RC_ERR_FAILED);

    CMReturn(CMPI_RC_OK);
}


static CMPIStatus MyProvCleanup (
    CMPIInstanceMI *mi,
    const CMPIContext *ctx,
    CMPIBoolean terminating)
{
    // Clean up code when unloading the MI load library

    CMReturn(CMPI_RC_OK);
}

static CMPIStatus MyProvEnumInstanceNames (
    CMPIInstanceMI *mi,
    const CMPIContext *ctx,
    const CMPIResult *rslt,
    const CMPIObjectPath *classPath)
{
    // for an example, see TBD

    CMReturn(CMPI_RC_OK);
}

// Example of a function that is not going to be implemented.
static CMPIStatus MyProvExecQuery (
    CMPIInstanceMI *mi, const CMPIContext *ctx,
    const CMPIResult *rslt, const CMPIObjectPath *classPath,
    const char *query, const char *lang)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvEnumInstances(
    CMPIInstanceMI* mi,
    const CMPIContext* ctx, const CMPIResult* rslt,
    const CMPIObjectPath* classPath , const char** properties)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvGetInstance(
    CMPIInstanceMI* mi, const CMPIContext* ctx,
    const CMPIResult* rslt, const CMPIObjectPath* instPath,
    const char** properties)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvCreateInstance(
    CMPIInstanceMI* mi, const CMPIContext* ctx,
    const CMPIResult* rslt, const CMPIObjectPath* classPath,
    const CMPIInstance* inst)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvModifyInstance(
    CMPIInstanceMI* mi, const CMPIContext* ctx,
    const CMPIResult* rslt, const CMPIObjectPath* instPath,
    const CMPIInstance* modInst, const char** properties)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvDeleteInstance(
    CMPIInstanceMI* mi, const CMPIContext* ctx,
    const CMPIResult* rslt, const CMPIObjectPath* op)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

static CMPIStatus MyProvEnumInstancesFiltered(
    CMPIInstanceMI* mi,
    const CMPIContext* ctx, const CMPIResult* rslt,
    const CMPIObjectPath* classPath,
    const char** properties, const char*filterQuerylanguage,
    const char* filterQuery, CMPIStatus* rc)
{
    CMReturn(CMPI_RC_ERR_NOT_SUPPORTED);
}

CMInstanceMIStub(MyProv, MyProv, _broker, CMInitHook(MyProv,Instance));
