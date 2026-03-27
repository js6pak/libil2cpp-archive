#pragma once
#include "il2cpp-config.h"
#include "codegen/il2cpp-codegen-metadata.h"
#include "Baselib.h"
#include "Cpp/Atomic.h"
#include "gc/GarbageCollector.h"

NORETURN void RaiseInterlockedTypeNotSupportedException();

template<typename T, typename U>
inline typename std::enable_if<!(std::is_pointer<T>::value && std::is_integral<U>::value), T>::type static_cast_with_type_check(U value)
{
    if constexpr (!std::is_pointer<T>::value && !std::is_integral<T>::value && !std::is_floating_point<T>::value)
    {
        RaiseInterlockedTypeNotSupportedException();
    }
    return static_cast<T>(value);
}

template<typename T, typename U>
inline typename std::enable_if<std::is_pointer<T>::value && std::is_integral<U>::value, T>::type static_cast_with_type_check(U value)
{
    // When comparing/setting a pointer value to 0, the type of U will by int, but we need to cast it to uintptr_t first to avoid a compiler warning about casting an integer to a pointer type.
    return reinterpret_cast<T>(static_cast<uintptr_t>(value));
}

namespace il2cpp
{
namespace intrinsics
{
namespace System_Private_CoreLib
{
namespace System
{
namespace Threading
{
    /* METHOD MAPPING
        Method: System.Void System.Threading.Interlocked::MemoryBarrier()
        AssemblyName: System.Private.CoreLib
    */
    void il2cpp_intrinsic_interlocked_memory_barrier();

    /* METHOD MAPPING
        Method: System.Void System.Threading.Interlocked::ReadMemoryBarrier()
        AssemblyName: System.Private.CoreLib
    */
    void il2cpp_intrinsic_interlocked_read_memory_barrier();

    /* METHOD MAPPING
        Method: System.Byte System.Threading.Interlocked::Exchange(System.Byte&,System.Byte)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Double System.Threading.Interlocked::Exchange(System.Double&,System.Double)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int16 System.Threading.Interlocked::Exchange(System.Int16&,System.Int16)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int32 System.Threading.Interlocked::Exchange(System.Int32&,System.Int32)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int64 System.Threading.Interlocked::Exchange(System.Int64&,System.Int64)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.IntPtr System.Threading.Interlocked::Exchange(System.IntPtr&,System.IntPtr)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.SByte System.Threading.Interlocked::Exchange(System.SByte&,System.SByte)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Single System.Threading.Interlocked::Exchange(System.Single&,System.Single)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt16 System.Threading.Interlocked::Exchange(System.UInt16&,System.UInt16)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt32 System.Threading.Interlocked::Exchange(System.UInt32&,System.UInt32)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt64 System.Threading.Interlocked::Exchange(System.UInt64&,System.UInt64)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UIntPtr System.Threading.Interlocked::Exchange(System.UIntPtr&,System.UIntPtr)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Object System.Threading.Interlocked::Exchange(System.Object&,System.Object)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: T System.Threading.Interlocked::Exchange(T&,T)
        AssemblyName: System.Private.CoreLib
    */
    template<typename T, typename U = T>
    inline T il2cpp_intrinsic_interlocked_exchange(T* location1, U value)
    {
        T updated = baselib::atomic_exchange(*location1, static_cast_with_type_check<T>(value));
#if IL2CPP_TARGET_ARM64
        Baselib_atomic_thread_fence_seq_cst();
#endif

        if constexpr (std::is_base_of<RuntimeObject, typename std::remove_pointer<T>::type>::value)
        {
            il2cpp::gc::GarbageCollector::SetWriteBarrier((void**)location1);
        }

        return updated;
    }

    /* METHOD MAPPING
        Method: System.Byte System.Threading.Interlocked::CompareExchange(System.Byte&,System.Byte,System.Byte)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Double System.Threading.Interlocked::CompareExchange(System.Double&,System.Double,System.Double)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int16 System.Threading.Interlocked::CompareExchange(System.Int16&,System.Int16,System.Int16)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int32 System.Threading.Interlocked::CompareExchange(System.Int32&,System.Int32,System.Int32)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Int64 System.Threading.Interlocked::CompareExchange(System.Int64&,System.Int64,System.Int64)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.IntPtr System.Threading.Interlocked::CompareExchange(System.IntPtr&,System.IntPtr,System.IntPtr)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Object System.Threading.Interlocked::CompareExchange(System.Object&,System.Object,System.Object)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.SByte System.Threading.Interlocked::CompareExchange(System.SByte&,System.SByte,System.SByte)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.Single System.Threading.Interlocked::CompareExchange(System.Single&,System.Single,System.Single)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt16 System.Threading.Interlocked::CompareExchange(System.UInt16&,System.UInt16,System.UInt16)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt32 System.Threading.Interlocked::CompareExchange(System.UInt32&,System.UInt32,System.UInt32)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UInt64 System.Threading.Interlocked::CompareExchange(System.UInt64&,System.UInt64,System.UInt64)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: System.UIntPtr System.Threading.Interlocked::CompareExchange(System.UIntPtr&,System.UIntPtr,System.UIntPtr)
        AssemblyName: System.Private.CoreLib
    */
    /* METHOD MAPPING
        Method: T System.Threading.Interlocked::CompareExchange(T&,T,T)
        AssemblyName: System.Private.CoreLib
    */
    template<typename T, typename U = T, typename V = T>
    inline T il2cpp_intrinsic_interlocked_compare_exchange(T* location1, U value, V comparand)
    {
        T oldValue = static_cast_with_type_check<T>(comparand);

        baselib::atomic_compare_exchange_strong(*location1, oldValue, static_cast_with_type_check<T>(value));
#if IL2CPP_TARGET_ARM64
        Baselib_atomic_thread_fence_seq_cst();
#endif
        if constexpr (std::is_base_of<RuntimeObject, typename std::remove_pointer<T>::type>::value)
        {
            il2cpp::gc::GarbageCollector::SetWriteBarrier((void**)location1);
        }

        return oldValue;
    }
} // namespace Threading
} // namespace System
} // namespace System_Private_CoreLib
} // namespace intrinsics
} // namespace il2cpp
