#pragma once

#include <stdint.h>
#include <vector>
#include "Assembly.h"

struct MethodInfo;
struct TypeInfo;
struct Il2CppGenericContainer;
struct Il2CppGenericContext;
struct Il2CppGenericMethodData;
struct Il2CppMethodGenericContainerData;
struct Il2CppType;

namespace il2cpp
{
namespace vm
{

class MetadataCache
{
public:
	typedef std::vector<const Il2CppType*> Il2CppTypeVec;

	static void RegisterGenericTypes(TypeInfo** types, size_t typeCount);
	static void RegisterSZArrays(TypeInfo** types, size_t typeCount);
	static void RegisterArrays(TypeInfo** types, size_t typeCount);
	static void RegisterGenericInstanceMethodData(Il2CppGenericMethodData* methods, size_t methodCount);
	static void RegisterGenericMethodDefinitionData(Il2CppMethodGenericContainerData* methodData, size_t methodCount);

	static void Initialize(const AssemblyVector& assemblies);

	static TypeInfo* GetBoundedArrayClass(TypeInfo* elementClass, uint32_t rank, bool bounded);
	static TypeInfo* GetGenericInstanceType(TypeInfo* genericTypeDefinition, const Il2CppTypeVec& genericArgumentTypes);
	static MethodInfo* GetGenericInstanceMethod(const MethodInfo* genericMethodDefinition, const Il2CppTypeVec& genericArgumentTypes);
	static MethodInfo* GetGenericVirtualMethod(const MethodInfo* methodDefinition, const MethodInfo* inflatedMethod);
	static Il2CppGenericContext* GetMethodGenericContext(const MethodInfo* method);
	static Il2CppGenericContainer* GetMethodGenericContainer(const MethodInfo* method);
	static MethodInfo* GetGenericMethodDefinition(const MethodInfo* method);

	static MethodInfo* GetNativeDelegate(methodPointerType nativeFunctionPointer);
	static void AddNativeDelegate(methodPointerType nativeFunctionPointer, MethodInfo* managedMethodInfo);

	static TypeInfo* GetPointerType(TypeInfo* type);
	static void AddPointerType(TypeInfo* type, TypeInfo* pointerType);
};

} // namespace vm
} // namespace il2cpp
