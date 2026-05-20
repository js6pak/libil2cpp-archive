#include "os/Assert.h"
#include "os/Environment.h"
#include <string>

#if IL2CPP_DEBUG

#if IL2CPP_TARGET_WINDOWS
#include <crtdbg.h>

void il2cpp_assert(const char* assertion, const char* file, unsigned int line)
{
    if (il2cpp::os::Environment::IsBuildMachine())
    {
        il2cpp_assert_generic(assertion, file, line);
        _exit(-1);
    }
    else
    {
        if (_CrtDbgReport(_CRT_ASSERT, file, line, "", "%s", assertion) == 1)
            _CrtDbgBreak();
    }
}

#endif // IL2CPP_TARGET_WINDOWS

#endif // IL2CPP_DEBUG
