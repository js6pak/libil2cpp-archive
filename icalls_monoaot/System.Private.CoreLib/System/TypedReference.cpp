#include "il2cpp-config.h"
#include "TypedReference.h"

#include "vm/Array.h"
#include "vm/Class.h"
#include "vm/Exception.h"
#include "vm/Object.h"
#include "vm/Type.h"

namespace il2cpp
{
namespace icalls
{
namespace System
{
namespace Private
{
namespace CoreLib
{
namespace System
{
    Il2CppObject* TypedReference::InternalToObject(Il2CppTypedRef* value)
    {
        Il2CppObject* result = NULL;
        if (vm::Type::IsReference(value->type))
        {
            Il2CppObject** obj = (Il2CppObject**)value->value;
            return *obj;
        }

        result = vm::Object::Box(value->klass, value->value);
        return result;
    }
} // namespace System
} // namespace CoreLib
} // namespace Private
} // namespace System
} // namespace icalls
} // namespace il2cpp
