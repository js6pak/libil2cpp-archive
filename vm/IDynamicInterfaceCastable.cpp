#if MONO_NET_BCL

#include "vm/IDynamicInterfaceCastable.h"
#include "vm/ClassInlines.h"
#include "vm/Runtime.h"
#include "vm/Method.h"

namespace il2cpp
{
namespace vm
{
    static int is_interface_implemented_slot;
    static int get_interface_implementation_slot;

    typedef bool (*IsInterfaceImplementedFunc)(Il2CppObject*, RuntimeTypeHandle_t, bool, const MethodInfo*);
    typedef RuntimeTypeHandle_t(*GetInterfaceImplementationFunc)(Il2CppObject*, RuntimeTypeHandle_t, const MethodInfo*);

    void IDynamicInterfaceCastable::Initialize()
    {
        if (il2cpp_defaults.idynamic_interface_castable)
        {
            const MethodInfo* isInterfaceImplementedMethod = vm::Class::GetMethodFromName(il2cpp_defaults.idynamic_interface_castable, "IsInterfaceImplemented", 2);
            if (isInterfaceImplementedMethod)
            {
                is_interface_implemented_slot = isInterfaceImplementedMethod->slot;

                IL2CPP_ASSERT(Class::FromIl2CppType(Method::GetParam(isInterfaceImplementedMethod, 0)) == il2cpp_defaults.typehandle_class);
                IL2CPP_ASSERT(Method::GetParam(isInterfaceImplementedMethod, 1)->type == IL2CPP_TYPE_BOOLEAN);
                IL2CPP_ASSERT(Method::GetReturnType(isInterfaceImplementedMethod)->type == IL2CPP_TYPE_BOOLEAN);
            }

            const MethodInfo* getInterfaceImplementationMethod = vm::Class::GetMethodFromName(il2cpp_defaults.idynamic_interface_castable, "GetInterfaceImplementation", 1);
            if (getInterfaceImplementationMethod)
            {
                get_interface_implementation_slot = getInterfaceImplementationMethod->slot;
                IL2CPP_ASSERT(Class::FromIl2CppType(Method::GetParam(getInterfaceImplementationMethod, 0)) == il2cpp_defaults.typehandle_class);
                IL2CPP_ASSERT(Class::FromIl2CppType(Method::GetReturnType(getInterfaceImplementationMethod)) == il2cpp_defaults.typehandle_class);
            }
        }
    }

    Il2CppObject* IDynamicInterfaceCastable::IsInst(Il2CppObject *obj, Il2CppClass *klass, bool throwIfNotImplemented)
    {
        const VirtualInvokeData& invokeData = ClassInlines::GetInterfaceInvokeDataFromVTable(obj, il2cpp_defaults.idynamic_interface_castable, is_interface_implemented_slot);
        RuntimeTypeHandle_t itfHandle = { Class::GetType(klass) };
        if (((IsInterfaceImplementedFunc)invokeData.methodPtr)(obj, itfHandle, throwIfNotImplemented, invokeData.method))
            return obj;
        return NULL;
    }

    const VirtualInvokeData& IDynamicInterfaceCastable::GetInvokeData(Il2CppObject* obj, const Il2CppClass* itf, Il2CppMethodSlot slot)
    {
        const VirtualInvokeData& invokeData = ClassInlines::GetInterfaceInvokeDataFromVTable(obj, il2cpp_defaults.idynamic_interface_castable, get_interface_implementation_slot);

        RuntimeTypeHandle_t itfHandle = { Class::GetType(itf) };
        RuntimeTypeHandle_t implType = ((GetInterfaceImplementationFunc)invokeData.methodPtr)(obj, itfHandle, invokeData.method);

        if (implType.value == NULL)
            vm::Exception::Raise(vm::Exception::GetInvalidCastException("Object does not implement the interface."));

        Il2CppClass* implClass = Class::FromIl2CppType(implType.value);
        ClassInlines::InitFromCodegen(implClass);
        Runtime::ClassInit(implClass);
        return ClassInlines::GetInterfaceInvokeDataFromVTable(implClass, itf, slot);
    }
}
}
#endif // MONO_NET_BCL
