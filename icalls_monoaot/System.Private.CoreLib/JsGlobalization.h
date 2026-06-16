#pragma once

#include "il2cpp-object-internals.h"
#include "il2cpp-class-internals.h"
#include "mono-structs.h"

namespace il2cpp
{
namespace icalls
{
namespace System
{
namespace Private
{
namespace CoreLib
{
    class LIBIL2CPP_CODEGEN_API JsGlobalization
    {
    public:
        static intptr_t GetLocaleInfo(Il2CppChar* locale, int32_t localeLength, Il2CppChar* culture, int32_t cultureLength, Il2CppChar* buffer, int32_t bufferLength, int32_t* resultLength);
    };
} // namespace CoreLib
} // namespace Private
} // namespace System
} // namespace icalls
} // namespace il2cpp
