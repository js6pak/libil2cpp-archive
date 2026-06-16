#pragma once

#include "il2cpp-runtime-metadata.h"

namespace il2cpp
{
namespace metadata
{
    // Stores either a runtime Il2CppGenericMethod pointer or a generic method metadata index, packed
    // into a single word. The low bit tags which one: 1 = pointer (always 2-byte aligned), 0 = index.
    // The index is shifted left by one. The method spec it refers to lives in one of three category
    // tables; BuildGenericMethodKey resolves it by index.
    class Il2CppMethodSpecOrGenericMethod
    {
    public:
        Il2CppMethodSpecOrGenericMethod() : storage(0) {}
        Il2CppMethodSpecOrGenericMethod(const Il2CppGenericMethod* gmethod);
        Il2CppMethodSpecOrGenericMethod(GenericMethodIndex genericMethodIndex);
        Il2CppGenericMethodKey BuildGenericMethodKey() const;

    private:
        uintptr_t storage;
    };
}
}
