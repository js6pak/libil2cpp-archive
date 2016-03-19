#pragma once

#include "il2cpp-config.h"
struct Il2CppGuid;
struct Il2CppIUnknown;
struct Il2CppRCW;

namespace il2cpp
{
namespace vm
{

class LIBIL2CPP_CODEGEN_API RCW
{
public:
	static void Initialize(Il2CppRCW* rcw, const Il2CppGuid& clsid);
	static Il2CppIUnknown* QueryInterface(Il2CppRCW* rcw, const Il2CppGuid& iid);
	static Il2CppObject* Create(Il2CppIUnknown* unknown);

private:
	static void Cleanup(void* obj, void* data);
};

} /* namespace vm */
} /* namespace il2cpp */
