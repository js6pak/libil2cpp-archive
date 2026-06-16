#pragma once

#include "il2cpp-config.h"
#include <stdint.h>
#include "il2cpp-tokentype.h"

typedef int32_t TypeIndex;
typedef int32_t TypeDefinitionIndex;
typedef int32_t FieldIndex;
typedef int32_t DefaultValueIndex;
typedef int32_t DefaultValueDataIndex;
typedef int32_t CustomAttributeIndex;
typedef int32_t ParameterIndex;
typedef int32_t MethodIndex;
typedef int32_t GenericMethodIndex;
typedef int32_t PropertyIndex;
typedef int32_t EventIndex;
typedef int32_t GenericContainerIndex;
typedef int32_t GenericParameterIndex;
typedef int16_t GenericParameterConstraintIndex;
typedef int32_t NestedTypeIndex;
typedef int32_t InterfacesIndex;
typedef int32_t VTableIndex;
typedef int32_t RGCTXIndex;
typedef int32_t StringIndex;
typedef int32_t StringLiteralIndex;
typedef int32_t GenericInstIndex;
typedef int32_t ImageIndex;
typedef int32_t AssemblyIndex;
typedef int32_t InteropDataIndex;

// "Relative" indexes - based on their parent
typedef int32_t TypeFieldIndex;
typedef int32_t TypeMethodIndex;
typedef int32_t MethodParameterIndex;
typedef int32_t TypePropertyIndex;
typedef int32_t TypeEventIndex;
typedef int32_t TypeInterfaceIndex;
typedef int32_t TypeNestedTypeIndex;
typedef int32_t TypeInterfaceOffsetIndex;
typedef int32_t GenericContainerParameterIndex;
typedef int32_t AssemblyTypeIndex;
typedef int32_t AssemblyExportedTypeIndex;

// Custom indexes - see GlobalMetadataFileInternals.h
typedef uint32_t EncodedMethodIndex;

static const TypeIndex kTypeIndexInvalid = -1;
static const TypeDefinitionIndex kTypeDefinitionIndexInvalid = -1;
static const DefaultValueDataIndex kDefaultValueIndexNull = -1;
static const CustomAttributeIndex kCustomAttributeIndexInvalid = -1;
static const EventIndex kEventIndexInvalid = -1;
static const FieldIndex kFieldIndexInvalid = -1;
static const MethodIndex kMethodIndexInvalid = -1;
static const PropertyIndex kPropertyIndexInvalid = -1;
static const GenericContainerIndex kGenericContainerIndexInvalid = -1;
static const GenericParameterIndex kGenericParameterIndexInvalid = -1;
static const RGCTXIndex kRGCTXIndexInvalid = -1;
static const StringLiteralIndex kStringLiteralIndexInvalid = -1;
static const InteropDataIndex kInteropDataIndexInvalid = -1;

#define PUBLIC_KEY_BYTE_LENGTH 8
static const int kPublicKeyByteLength = PUBLIC_KEY_BYTE_LENGTH;

// Generic methods fall into three categories, each emitted to its own table so that an entry only
// stores the generic instance indices it actually needs. Generic method indices are
// laid out in three contiguous, category-ordered ranges in global-metadata.dat:
//   methodSpecsOnGenericType section  -> Il2CppMethodSpecOnGenericType
//   genericMethodSpecsOnType section  -> Il2CppGenericMethodSpecOnType
//   methodSpecs section               -> Il2CppMethodSpec
// Keep this layout in sync with the il2cpp generator (GenericMethodCollectorComponent).

// Category 1: a non-generic method on a generic type (e.g. List<int>.get_Count)
typedef struct Il2CppMethodSpecOnGenericType
{
    MethodIndex methodDefinitionIndex;
    GenericInstIndex classIndexIndex;
} Il2CppMethodSpecOnGenericType;

// Category 2: a generic method on a non-generic type (e.g. Enumerable.Range<int>)
typedef struct Il2CppGenericMethodSpecOnType
{
    MethodIndex methodDefinitionIndex;
    GenericInstIndex methodIndexIndex;
} Il2CppGenericMethodSpecOnType;

// Category 3: a generic method on a generic type - needs both generic instances.
typedef struct Il2CppMethodSpec
{
    MethodIndex methodDefinitionIndex;
    GenericInstIndex classIndexIndex;
    GenericInstIndex methodIndexIndex;
} Il2CppMethodSpec;

// Must match Unity.IL2CPP.Metadata.RGCTXType
typedef enum Il2CppRGCTXDataType
{
    IL2CPP_RGCTX_DATA_INVALID,
    IL2CPP_RGCTX_DATA_TYPE,
    IL2CPP_RGCTX_DATA_CLASS,
    IL2CPP_RGCTX_DATA_METHOD,
    IL2CPP_RGCTX_DATA_ARRAY,
    IL2CPP_RGCTX_DATA_CONSTRAINED_CALL_TYPE,
    IL2CPP_RGCTX_DATA_CONSTRAINED_CALL_METHOD,
    IL2CPP_RGCTX_DATA_FIELD_OFFSET_TYPE,
    IL2CPP_RGCTX_DATA_FIELD_OFFSET_FIELD,
} Il2CppRGCTXDataType;

typedef union Il2CppRGCTXDefinitionData
{
    uint32_t rgctxDataDummy;
    MethodIndex __methodIndex;
    TypeIndex __typeIndex;
    FieldIndex __fieldIndex;
    uint32_t  __encodedMethodIndex;
} Il2CppRGCTXDefinitionData;

typedef struct Il2CppRGCTXDefinition
{
    Il2CppRGCTXDataType type;
    Il2CppRGCTXDefinitionData data;
} Il2CppRGCTXDefinition;

// Runtime-only in-memory representation of the per-generic-method indices.
// Generated source code emits one of the two table-entry structs below
// (Il2CppGenericMethodFunctionsDefinitions or
// Il2CppGenericMethodFunctionsDefinitionsWithAdjustor) instead.
typedef struct
{
    MethodIndex methodIndex;
    MethodIndex invokerIndex;
    MethodIndex adjustorThunkIndex;
} Il2CppGenericMethodIndices;

// Entry layout used for static methods and instance methods on reference types.
// adjustorThunkIndex is always -1 for these, so the field is omitted.
typedef struct Il2CppGenericMethodFunctionsDefinitions
{
    GenericMethodIndex genericMethodIndex;
    MethodIndex methodIndex;
    MethodIndex invokerIndex;
} Il2CppGenericMethodFunctionsDefinitions;

// Entry layout used for instance methods on value types, which may need an
// adjustor thunk when invoked virtually.
typedef struct Il2CppGenericMethodFunctionsDefinitionsWithAdjustor
{
    GenericMethodIndex genericMethodIndex;
    MethodIndex methodIndex;
    MethodIndex invokerIndex;
    MethodIndex adjustorThunkIndex;
} Il2CppGenericMethodFunctionsDefinitionsWithAdjustor;

static inline uint32_t GetTokenType(uint32_t token)
{
    return token & 0xFF000000;
}

static inline uint32_t GetTokenRowId(uint32_t token)
{
    return token & 0x00FFFFFF;
}

/* Runtime metadata tokens  */
typedef const struct ___Il2CppMetadataImageHandle* Il2CppMetadataImageHandle;
typedef const struct ___Il2CppMetadataCustomAttributeHandle* Il2CppMetadataCustomAttributeHandle;
typedef const struct ___Il2CppMetadataTypeHandle* Il2CppMetadataTypeHandle;
typedef const struct ___Il2CppMetadataMethodHandle* Il2CppMetadataMethodDefinitionHandle;
typedef const struct ___Il2CppMetadataGenericContainerHandle* Il2CppMetadataGenericContainerHandle;
typedef const struct ___Il2CppMetadataGenericParameterHandle* Il2CppMetadataGenericParameterHandle;
