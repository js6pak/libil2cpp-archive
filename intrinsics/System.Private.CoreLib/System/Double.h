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
        Method: TInteger System.Double::ConvertToIntegerNative(System.Double)
        AssemblyName: System.Private.CoreLib
        EmitTemplateParams: true
    */
    template<typename TRet>
    inline TRet il2cpp_intrinsic_double_convert_to_integer_native(double value)
    {
        return ConvFloatingPointNative<TRet, double>::Conv(value);
    }

    void il2cpp_intrinsic_double_convert_to_integer_native(double value, RuntimeClass* valueClass, Il2CppFullySharedGenericAny ret);
} // namespace System
} // namespace System_Private_CoreLib
} // namespace intrinsics
} // namespace il2cpp
