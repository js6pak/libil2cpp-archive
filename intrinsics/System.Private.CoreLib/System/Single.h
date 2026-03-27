#pragma once
#include "il2cpp-config.h"
#include "codegen/il2cpp-codegen.h"

#include "codegen/il2cpp-codegen-metadata.h"
namespace il2cpp
{
namespace intrinsics
{
namespace System_Private_CoreLib
{
namespace System
{
    /* METHOD MAPPING
        Method: TInteger System.Single::ConvertToIntegerNative(System.Single)
        AssemblyName: System.Private.CoreLib
    */
    template<typename TRet>
    inline TRet il2cpp_intrinsic_float_convert_to_integer_native(float value)
    {
        return ConvFloatingPointNative<TRet, float>::Conv(value);
    }

    void il2cpp_intrinsic_float_convert_to_integer_native(float value, RuntimeClass* valueClass, Il2CppFullySharedGenericAny ret);
} // namespace System
} // namespace System_Private_CoreLib
} // namespace intrinsics
} // namespace il2cpp
