#include <stdlib.h>
#include "os/Assert.h"
#include "os/Console.h"

#if IL2CPP_DEBUG

void il2cpp_assert_generic(const char* assertion, const char* file, unsigned int line)
{
    il2cpp_console_printf_error("Assertion failed: %s, file %s, line %u\n", assertion, file, line);
    abort();
}

#if IL2CPP_USE_GENERIC_ASSERT


void il2cpp_assert(const char* assertion, const char* file, unsigned int line)
{
    il2cpp_assert_generic(assertion, file, line);
}

#endif // IL2CPP_USE_GENERIC_ASSERT

#endif // IL2CPP_DEBUG
