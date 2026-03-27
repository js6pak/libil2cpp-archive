#include "Double.h"
#include "vm/Class.h"

namespace il2cpp
{
namespace intrinsics
{
namespace System_Private_CoreLib
{
namespace System
{
    // The implementation here is to handle the full generic sharing code path
    // When not shared a more direct call will be emitted (See Double.h & Single.h)

    template<typename TPrimitive, typename TFloat>
    void convert_to_integer_primitive(TFloat value, Il2CppFullySharedGenericAny ret)
    {
        TPrimitive result = ConvFloatingPointNative<TPrimitive, TFloat>::Conv(value);
        memcpy(ret, &result, sizeof(TPrimitive));
    }

    template<typename TFloat>
    void il2cpp_intrinsic_tfloat_convert_to_integer_native(TFloat value, RuntimeClass* toClass, Il2CppFullySharedGenericAny ret)
    {
        const Il2CppType* toType = vm::Class::GetType(toClass);

        switch (toType->type)
        {
            case IL2CPP_TYPE_I1:
                convert_to_integer_primitive<int8_t>(value, ret);
                break;
            case IL2CPP_TYPE_BOOLEAN:
            case IL2CPP_TYPE_U1:
                convert_to_integer_primitive<uint8_t>(value, ret);
                break;
            case IL2CPP_TYPE_I2:
                convert_to_integer_primitive<int16_t>(value, ret);
                break;
            case IL2CPP_TYPE_CHAR:
            case IL2CPP_TYPE_U2:
                convert_to_integer_primitive<uint16_t>(value, ret);
                break;
            case IL2CPP_TYPE_I4:
                convert_to_integer_primitive<int32_t>(value, ret);
                break;
            case IL2CPP_TYPE_U4:
                convert_to_integer_primitive<uint32_t>(value, ret);
                break;
            case IL2CPP_TYPE_I8:
                convert_to_integer_primitive<int64_t>(value, ret);
                break;
            case IL2CPP_TYPE_U8:
                convert_to_integer_primitive<uint64_t>(value, ret);
                break;
            case IL2CPP_TYPE_I:
                convert_to_integer_primitive<intptr_t>(value, ret);
                break;
            case IL2CPP_TYPE_U:
                convert_to_integer_primitive<uintptr_t>(value, ret);
                break;
            case IL2CPP_TYPE_R4:
                convert_to_integer_primitive<float>(value, ret);
                break;
            case IL2CPP_TYPE_R8:
                convert_to_integer_primitive<double>(value, ret);
                break;
            default:
                // This should only be called for primitive types
                // The intrinsic remapper should have prevented this from being called for non-primitive types
                IL2CPP_ASSERT(0 && "Unsupported call to ConvertToIntegerNative");
                vm::Exception::Raise(vm::Exception::GetInvalidOperationException("Unsupported type for ConvertToIntegerNative"));
                break;
        }
    }

    void il2cpp_intrinsic_double_convert_to_integer_native(double value, RuntimeClass* toClass, Il2CppFullySharedGenericAny ret)
    {
        il2cpp_intrinsic_tfloat_convert_to_integer_native<double>(value, toClass, ret);
    }

    void il2cpp_intrinsic_float_convert_to_integer_native(float value, RuntimeClass* toClass, Il2CppFullySharedGenericAny ret)
    {
        il2cpp_intrinsic_tfloat_convert_to_integer_native<float>(value, toClass, ret);
    }
} // namespace System
} // namespace System_Private_CoreLib
} // namespace intrinsics
} // namespace il2cpp
