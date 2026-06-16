#include "metadata/Il2CppMethodSpecOrGenericMethod.h"
#include "il2cpp-runtime-metadata.h"
#include "vm/GlobalMetadata.h"

il2cpp::metadata::Il2CppMethodSpecOrGenericMethod::Il2CppMethodSpecOrGenericMethod(const Il2CppGenericMethod* gmethod)
{
    IL2CPP_ASSERT((reinterpret_cast<uintptr_t>(gmethod) & 1) == 0);
    storage = reinterpret_cast<uintptr_t>(gmethod) | 1;
}

il2cpp::metadata::Il2CppMethodSpecOrGenericMethod::Il2CppMethodSpecOrGenericMethod(GenericMethodIndex genericMethodIndex)
{
    storage = static_cast<uintptr_t>(genericMethodIndex) << 1;
}

Il2CppGenericMethodKey il2cpp::metadata::Il2CppMethodSpecOrGenericMethod::BuildGenericMethodKey() const
{
    if (storage & 1)
    {
        const Il2CppGenericMethod* gmethod = reinterpret_cast<const Il2CppGenericMethod*>(storage & ~(uintptr_t)1);
        return { gmethod->methodDefinition->methodMetadataHandle, gmethod->context };
    }

    return il2cpp::vm::GlobalMetadata::BuildGenericMethodFromMethodSpec(static_cast<GenericMethodIndex>(storage >> 1));
}
