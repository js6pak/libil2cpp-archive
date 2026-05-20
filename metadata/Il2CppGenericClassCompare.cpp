#include "il2cpp-config.h"
#include "il2cpp-class-internals.h"
#include "Il2CppGenericClassCompare.h"
#include "Il2CppGenericInstCompare.h"
#include "Il2CppTypeCompare.h"
#include "vm/GenericClass.h"

namespace il2cpp
{
namespace metadata
{
    bool Il2CppGenericClassCompare::operator()(const Il2CppGenericClass* gc1, const Il2CppGenericClass* gc2) const
    {
        return Compare(gc1, gc2);
    }

    bool Il2CppGenericClassCompare::Compare(const Il2CppGenericClass* gc1, const Il2CppGenericClass* gc2)
    {
        if (!Il2CppTypeEqualityComparer::AreEqual(gc1->type, gc2->type))
            return false;

        return Il2CppGenericInstCompare::Compare(il2cpp::vm::GenericClass::GetInstance(gc1), il2cpp::vm::GenericClass::GetInstance(gc2));
    }
} /* namespace vm */
} /* namespace il2cpp */
