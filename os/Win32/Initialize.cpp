#include "il2cpp-config.h"
#include "os/Initialize.h"
#if IL2CPP_TARGET_WINDOWS

#include "os/Environment.h"
#include "os/WindowsRuntime.h"

#include "DllMain.h"
#include <crtdbg.h>

void il2cpp::os::Initialize()
{
    if (il2cpp::os::Environment::IsBuildMachine())
        _set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);

    // This is needed so we could extract exception text from bad hresults
    os::WindowsRuntime::EnableErrorReporting();
    os::InitializeDllMain();
}

#if !IL2CPP_TARGET_WINRT
void il2cpp::os::Uninitialize()
{
}

#endif

#endif
