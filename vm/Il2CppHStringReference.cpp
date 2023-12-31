#include "il2cpp-config.h"
#include <il2cpp-object-internals.h>
#include "Il2CppHStringReference.h"
#include "vm/WindowsRuntime.h"

namespace il2cpp
{
namespace vm
{
    Il2CppHStringReference::Il2CppHStringReference(const utils::StringView<Il2CppNativeChar>& str)
    {
        il2cpp::vm::WindowsRuntime::CreateHStringReference(str, &m_Header, &m_String);
    }
}
}
