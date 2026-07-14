#pragma once
#include "il2cpp-object-internals.h"
#include "vm/Class.h"

namespace il2cpp
{
namespace vm
{
    class IDynamicInterfaceCastable
    {
    public:
        static void Initialize();

        static bool IsDynamicallyCastable(const Il2CppClass* klass)
        {
            return klass->has_idynamic_interface_castable && !Class::IsValuetype(klass);
        }

        static Il2CppObject* IsInst(Il2CppObject *obj, Il2CppClass *klass, bool throwIfNotImplemented);
        static const VirtualInvokeData& GetInvokeData(Il2CppObject* obj, const Il2CppClass* itf, Il2CppMethodSlot slot);
    };
}
}
