#include "Interlocked.h"
#include "vm/Exception.h"
#include "vm/Thread.h"
#include "os/Atomic.h"

NORETURN void RaiseInterlockedTypeNotSupportedException()
{
    il2cpp::vm::Exception::Raise(il2cpp::vm::Exception::GetNotSupportedException("The specified type must be a reference type, a primitive type, or an enum type."));
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
    void il2cpp_intrinsic_interlocked_memory_barrier()
    {
        il2cpp::vm::Thread::FullMemoryBarrier();
    }

    void il2cpp_intrinsic_interlocked_read_memory_barrier()
    {
        il2cpp::os::Atomic::ReadMemoryBarrier();
    }
} // namespace Threading
} // namespace System
} // namespace System_Private_CoreLib
} // namespace intrinsics
} // namespace il2cpp
