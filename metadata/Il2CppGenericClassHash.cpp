#include "il2cpp-config.h"
#include "il2cpp-class-internals.h"
#include "Il2CppGenericClassHash.h"
#include "Il2CppGenericInstHash.h"
#include "Il2CppTypeHash.h"
#include "vm/GenericClass.h"
#include "utils/HashUtils.h"

using il2cpp::utils::HashUtils;

namespace il2cpp
{
namespace metadata
{
    size_t Il2CppGenericClassHash::operator()(const Il2CppGenericClass* item) const
    {
        return Hash(item);
    }

    size_t Il2CppGenericClassHash::Hash(const Il2CppGenericClass* item)
    {
        size_t containerHash = Il2CppTypeHash::Hash(item->type);
        size_t contextHash = Il2CppGenericInstHash::Hash(il2cpp::vm::GenericClass::GetInstance(item));

        return HashUtils::Combine(containerHash, contextHash);
    }
} /* namespace vm */
} /* namespace il2cpp */
