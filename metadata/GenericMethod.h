#pragma once

#include <string>

struct MethodInfo;
struct Il2CppGenericMethod;
struct Il2CppGenericContext;

namespace il2cpp
{
namespace metadata
{
    class GenericMethod
    {
    public:
        // exported

    public:
        //internal
        static const MethodInfo* GetGenericVirtualMethod(const MethodInfo* vtableSlotMethod, const MethodInfo* genericVirtualMethod);
        static const MethodInfo* GetMethod(const Il2CppGenericMethod* gmethod, bool copyMethodPtr = false);
        static const Il2CppGenericContext* GetContext(const Il2CppGenericMethod* gmethod);
        static std::string GetFullName(const Il2CppGenericMethod* gmethod);

        static void ClearStatics();

    private:
        static const MethodInfo* CreateMethodLocked(const Il2CppGenericMethod* gmethod, bool copyMethodPtr);
    };
} /* namespace vm */
} /* namespace il2cpp */
