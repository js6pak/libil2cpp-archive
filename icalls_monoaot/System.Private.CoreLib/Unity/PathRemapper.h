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
namespace Unity
{
    class LIBIL2CPP_CODEGEN_API PathRemapper
    {
    public:
        static int32_t InvokeNativeRemapper(uint8_t* pathUtf8, uint8_t* buffer, int32_t bufferLen);
    };
} // namespace Unity
} // namespace CoreLib
} // namespace Private
} // namespace System
} // namespace icalls
} // namespace il2cpp
