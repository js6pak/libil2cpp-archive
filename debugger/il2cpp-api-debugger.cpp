#if defined(RUNTIME_IL2CPP) && !defined(IL2CPP_MONO_DEBUGGER_DISABLED)

// This file implements an extension to the IL2CPP embedding API that the debugger code requires.
// It should not include any Mono headers.

#include "il2cpp-config.h"
#include "il2cpp-class-internals.h"
#include "il2cpp-mono-api.h"
#include "il2cpp-api-debugger.h"

#include "gc/GarbageCollector.h"
#include "gc/WriteBarrier.h"
#include "metadata/CustomAttributeDataReader.h"
#include "metadata/FieldLayout.h"
#include "metadata/GenericMetadata.h"
#include "vm/Array.h"
#include "vm/Assembly.h"
#include "vm/AssemblyName.h"
#include "vm/Class.h"
#include "vm/ClassInlines.h"
#include "vm/Field.h"
#include "vm/GenericClass.h"
#include "vm/GenericContainer.h"
#include "vm/GlobalMetadata.h"
#include "vm/Image.h"
#include "vm/MetadataCache.h"
#include "vm/Object.h"
#include "vm/Property.h"
#include "vm/Reflection.h"
#include "vm-utils/Debugger.h"

#include <algorithm>

#if IL2CPP_TARGET_XBOXONE
#define strdup _strdup
#endif

struct Il2CppMonoError
{
    unsigned short error_code;
    unsigned short flags;

    void *hidden_1[12];
};

static void error_init(MonoError* error)
{
    auto il2CppError = (Il2CppMonoError*)error;
    il2CppError->error_code = 0;
    il2CppError->flags = 0;
}

extern "C" {
    void* il2cpp_domain_get_agent_info(MonoAppDomain* domain)
    {
        return ((Il2CppDomain*)domain)->agent_info;
    }

    void il2cpp_domain_set_agent_info(MonoAppDomain* domain, void* agentInfo)
    {
        il2cpp::gc::WriteBarrier::GenericStore(&((Il2CppDomain*)domain)->agent_info, agentInfo);
    }

    const char* il2cpp_domain_get_friendly_name(MonoAppDomain* domain)
    {
        return ((Il2CppDomain*)domain)->friendly_name;
    }

    void il2cpp_start_debugger_thread()
    {
#if IL2CPP_MONO_DEBUGGER
        il2cpp::utils::Debugger::StartDebuggerThread();
#endif
    }

    const char* il2cpp_domain_get_name(MonoDomain* domain)
    {
        return ((Il2CppDomain*)domain)->friendly_name;
    }

    Il2CppSequencePoint* il2cpp_get_method_sequence_points(MonoMethod* method, void* *iter)
    {
#if IL2CPP_MONO_DEBUGGER
        if (method == NULL)
            return il2cpp::utils::Debugger::GetAllSequencePoints(iter);
        else
            return (Il2CppSequencePoint*)il2cpp::utils::Debugger::GetSequencePoints((const MethodInfo*)method, iter);
#else
        return NULL;
#endif
    }

    Il2CppCatchPoint* il2cpp_get_method_catch_points(MonoMethod* method, void* *iter)
    {
#if IL2CPP_MONO_DEBUGGER
        return (Il2CppCatchPoint*)il2cpp::utils::Debugger::GetCatchPoints((const MethodInfo*)method, iter);
#else
        return NULL;
#endif
    }

    Il2CppSequencePoint* il2cpp_get_seq_point_from_catch_point(Il2CppCatchPoint *cp)
    {
#if IL2CPP_MONO_DEBUGGER
        return (Il2CppSequencePoint*)il2cpp::utils::Debugger::GetSequencePoint(NULL, cp);
#else
        return NULL;
#endif
    }

    int32_t il2cpp_mono_methods_match(MonoMethod* left, MonoMethod* right)
    {
        MethodInfo* leftMethod = (MethodInfo*)left;
        MethodInfo* rightMethod = (MethodInfo*)right;

        if (rightMethod == leftMethod)
            return 1;
        if (rightMethod == NULL || leftMethod == NULL)
            return 0;
        if (leftMethod->methodMetadataHandle == rightMethod->methodMetadataHandle)
            return 1;

        return 0;
    }

    MonoClass* il2cpp_defaults_object_class()
    {
        return (MonoClass*)il2cpp_defaults.object_class;
    }

    const char* il2cpp_image_name(MonoImage *monoImage)
    {
        Il2CppImage *image = (Il2CppImage*)monoImage;
        return image->name;
    }

    uint8_t* il2cpp_field_get_address(MonoObject *obj, MonoClassField *monoField)
    {
        FieldInfo *field = (FieldInfo*)monoField;
        return (uint8_t*)obj + field->offset;
    }

    MonoClass* il2cpp_defaults_exception_class()
    {
        return (MonoClass*)il2cpp_defaults.exception_class;
    }

    MonoImage* il2cpp_defaults_corlib_image()
    {
        return (MonoImage*)il2cpp_defaults.corlib;
    }

    MonoClass* il2cpp_defaults_runtimetype_class()
    {
        return (MonoClass*)il2cpp_defaults.runtimetype_class;
    }

    bool il2cpp_method_is_string_ctor(const MonoMethod * method)
    {
        MethodInfo* methodInfo = (MethodInfo*)method;
        return methodInfo->klass == il2cpp_defaults.string_class && !strcmp(methodInfo->name, ".ctor");
    }

    MonoClass* il2cpp_defaults_void_class()
    {
        return (MonoClass*)il2cpp_defaults.void_class;
    }

    MonoMethod* il2cpp_get_interface_method(MonoClass* klass, MonoClass* itf, int slot)
    {
        const VirtualInvokeData* data = il2cpp::vm::ClassInlines::GetInterfaceInvokeDataFromVTable((Il2CppClass*)klass, (Il2CppClass*)itf, slot);
        if (!data)
            return NULL;

        return (MonoMethod*)data->method;
    }

    struct TypeIterState
    {
        il2cpp::vm::AssemblyVector* assemblies;
        il2cpp::vm::AssemblyVector::iterator assembly;
        Il2CppImage* image;
        il2cpp::vm::TypeVector types;
        il2cpp::vm::TypeVector::iterator type;
    };

    MonoClass* il2cpp_iterate_loaded_classes(void* *iter)
    {
        if (!iter)
            return NULL;

        if (!*iter)
        {
            TypeIterState *state = new TypeIterState();
            state->assemblies = il2cpp::vm::Assembly::GetAllAssemblies();
            state->assembly = state->assemblies->begin();
            state->image = il2cpp::vm::Assembly::GetImage(*state->assembly);
            il2cpp::vm::Image::GetTypes(state->image, false, &state->types);
            state->type = state->types.begin();
            *iter = state;
            return (MonoClass*)*state->type;
        }

        TypeIterState *state = (TypeIterState*)*iter;

        state->type++;
        if (state->type == state->types.end())
        {
            state->assembly++;
            if (state->assembly == state->assemblies->end())
            {
                delete state;
                *iter = NULL;
                return NULL;
            }

            state->image = il2cpp::vm::Assembly::GetImage(*state->assembly);
            il2cpp::vm::Image::GetTypes(state->image, false, &state->types);
            state->type = state->types.begin();
        }

        return (MonoClass*)*state->type;
    }

    const char** il2cpp_get_source_files_for_type(MonoClass *klass, int *count)
    {
#if IL2CPP_MONO_DEBUGGER
        return il2cpp::utils::Debugger::GetTypeSourceFiles((Il2CppClass*)klass, *count);
#else
        return NULL;
#endif
    }

    MonoMethod* il2cpp_method_get_generic_definition(MonoMethodInflated *imethod)
    {
        MethodInfo *method = (MethodInfo*)imethod;

        if (!method->is_inflated || method->is_generic)
            return NULL;

        return (MonoMethod*)((MethodInfo*)imethod)->genericMethod->methodDefinition;
    }

    MonoGenericInst* il2cpp_method_get_generic_class_inst(MonoMethodInflated *imethod)
    {
        MethodInfo *method = (MethodInfo*)imethod;

        if (!method->is_inflated || method->is_generic)
            return NULL;

        return (MonoGenericInst*)method->genericMethod->context.class_inst;
    }

    MonoClass* il2cpp_generic_class_get_container_class(MonoGenericClass *gclass)
    {
        return (MonoClass*)il2cpp::vm::GenericClass::GetTypeDefinition((Il2CppGenericClass*)gclass);
    }

    Il2CppSequencePoint* il2cpp_get_sequence_point(MonoImage* image, int id)
    {
#if IL2CPP_MONO_DEBUGGER
        return il2cpp::utils::Debugger::GetSequencePoint((const Il2CppImage*)image, id);
#else
        return NULL;
#endif
    }

    char* il2cpp_assembly_get_full_name(MonoAssembly *assembly)
    {
        std::string s = il2cpp::vm::AssemblyName::AssemblyNameToString(((Il2CppAssembly*)assembly)->aname);
        return strdup(s.c_str());
    }

    const MonoMethod* il2cpp_get_seq_point_method(Il2CppSequencePoint *seqPoint)
    {
#if IL2CPP_MONO_DEBUGGER
        return (const MonoMethod*)il2cpp::utils::Debugger::GetSequencePointMethod(NULL, seqPoint);
#else
        return NULL;
#endif
    }

    const MonoClass* il2cpp_get_class_from_index(int index)
    {
        if (index < 0)
            return NULL;

        return (const MonoClass*)il2cpp::vm::MetadataCache::GetTypeInfoFromTypeIndex(NULL, index);
    }

    const MonoType* il2cpp_type_inflate(MonoType* type, const MonoGenericContext* context)
    {
        return (MonoType*)il2cpp::metadata::GenericMetadata::InflateIfNeeded((Il2CppType*)type, (const Il2CppGenericContext*)context, true);
    }

    void il2cpp_debugger_get_method_execution_context_and_header_info(const MonoMethod* method, uint32_t* executionContextInfoCount, const Il2CppMethodExecutionContextInfo **executionContextInfo, const Il2CppMethodHeaderInfo **headerInfo, const Il2CppMethodScope **scopes)
    {
#if IL2CPP_MONO_DEBUGGER
        il2cpp::utils::Debugger::GetMethodExecutionContextInfo((const MethodInfo*)method, executionContextInfoCount, executionContextInfo, headerInfo, scopes);
#endif
    }

    Il2CppThreadUnwindState* il2cpp_debugger_get_thread_context()
    {
#if IL2CPP_MONO_DEBUGGER
        return il2cpp::utils::Debugger::GetThreadStatePointer();
#else
        return NULL;
#endif
    }

    Il2CppSequencePointSourceFile* il2cpp_debug_get_source_file(MonoImage* image, int index)
    {
        return ((Il2CppImage*)image)->codeGenModule->debuggerMetadata->sequencePointSourceFiles + index;
    }

    MonoMethod* il2cpp_get_generic_method_definition(MonoMethod* method)
    {
        return (MonoMethod*)((MethodInfo*)method)->genericMethod->methodDefinition;
    }

    bool il2cpp_class_is_initialized(MonoClass* klass)
    {
        return ((Il2CppClass*)klass)->initialized;
    }

    int il2cpp_generic_inst_get_argc(MonoGenericInst* inst)
    {
        return ((Il2CppGenericInst*)inst)->type_argc;
    }

    MonoType* il2cpp_generic_inst_get_argv(MonoGenericInst* inst, int index)
    {
        return (MonoType*)((Il2CppGenericInst*)inst)->type_argv[index];
    }

    MonoObject* il2cpp_assembly_get_object(MonoDomain* domain, MonoAssembly* assembly, MonoError* error)
    {
        return (MonoObject*)il2cpp::vm::Reflection::GetAssemblyObject((const Il2CppAssembly *)assembly);
    }

    const MonoType* il2cpp_get_type_from_index(int index)
    {
        return (const MonoType*)il2cpp::vm::MetadataCache::GetIl2CppTypeFromIndex(NULL, index);
    }

    void il2cpp_thread_info_safe_suspend_and_run(size_t /*Really MonoNativeThreadId*/ id, int32_t interrupt_kernel, MonoSuspendThreadCallback callback, void* user_data)
    {
        callback(NULL, user_data);
    }

    MonoGenericParam* il2cpp_generic_container_get_param(MonoGenericContainer *gc, int i)
    {
        return (MonoGenericParam*)il2cpp::vm::GenericContainer::GetGenericParameter((Il2CppMetadataGenericContainerHandle)gc, i);
    }

    void il2cpp_field_static_get_value_checked(MonoVTable* vt, MonoClassField* field, void* value, MonoError* error)
    {
        error_init(error);
        il2cpp::vm::Field::StaticGetValue((FieldInfo*)field, value);
    }

    void il2cpp_field_static_get_value_for_thread(MonoInternalThread* thread, MonoVTable* vt, MonoClassField* field, void* value, MonoError* error)
    {
        error_init(error);
        il2cpp::vm::Field::StaticGetValueForThread((FieldInfo*)field, value, (Il2CppInternalThread*)thread);
    }

    static bool IsFixedBufferAttribute(Il2CppClass* klass)
    {
        return strcmp(klass->name, "FixedBufferAttribute") == 0 &&
            strcmp(klass->namespaze, "System.Runtime.CompilerServices") == 0;
    }

    static bool IsInt32Type(Il2CppClass* klass)
    {
        return klass == il2cpp_defaults.int32_class;
    }

    struct FixedBufferAttributeConstructorVisitor : public il2cpp::metadata::CustomAttributeReaderVisitor
    {
        FixedBufferAttributeConstructorVisitor() : FixedArraySize(1) {}

        int32_t FixedArraySize;
        virtual void VisitCtor(const MethodInfo* ctor, il2cpp::metadata::CustomAttributeArgument args[], uint32_t argumentCount)
        {
            if (argumentCount == 2 && IsInt32Type(args[1].klass))
                FixedArraySize = *(int32_t*)&args[1].data;
        }
    };

    int32_t il2cpp_field_get_fixed_array_size(MonoClassField* field)
    {
        FieldInfo* il2cppField = (FieldInfo*)field;

        Il2CppMetadataCustomAttributeHandle attributeHandle = il2cpp::vm::MetadataCache::GetCustomAttributeTypeToken(il2cppField->parent->image, il2cppField->token);
        if (attributeHandle == NULL)
            return 1;

        void* start;
        void* end;
        std::tie(start, end) = il2cpp::vm::GlobalMetadata::GetCustomAttributeDataRange(attributeHandle);
        auto reader = il2cpp::metadata::CustomAttributeDataReader(start, end);

        il2cpp::metadata::LazyCustomAttributeData data;
        Il2CppException* exc = NULL;
        il2cpp::metadata::CustomAttributeDataIterator iter = reader.GetDataIterator();
        while (reader.ReadLazyCustomAttributeData(il2cppField->parent->image, &data, &iter, &exc))
        {
            // Assume there is only one fixed buffer attribute - we will use the first one.
            if (IsFixedBufferAttribute(data.ctor->klass))
            {
                FixedBufferAttributeConstructorVisitor visitor;
                il2cpp::metadata::CustomAttributeDataReader::VisitCustomAttributeData(il2cppField->parent->image, data.ctor, data.dataStart, data.dataLength, &visitor, &exc);
                if (exc != NULL)
                    return 1;
                return visitor.FixedArraySize;
            }
        }

        return 1;
    }

    class DebuggerCustomAttributeVisitor : public il2cpp::metadata::CustomAttributeReaderVisitor
    {
    public:
        DebuggerCustomAttributeVisitor(Il2CppCustomAttributeData* attributeData) : m_propertyIndexOffset(0), m_attributeData(attributeData) {}

        virtual void VisitArgumentSizes(uint32_t argumentCount, uint32_t fieldCount, uint32_t propertyCount)
        {
            m_attributeData->typedArgs = il2cpp::vm::Array::New(il2cpp_defaults.object_class, argumentCount);
            il2cpp::gc::GarbageCollector::SetWriteBarrier((void**)&m_attributeData->typedArgs);

            int32_t numberOfNamedArguments = fieldCount + propertyCount;
            m_attributeData->namedArgs = il2cpp::vm::Array::New(il2cpp_defaults.object_class, numberOfNamedArguments);
            il2cpp::gc::GarbageCollector::SetWriteBarrier((void**)&m_attributeData->namedArgs);

            m_propertyIndexOffset = fieldCount;
            m_attributeData->argInfo = (Il2CppCattrNamedArg*)IL2CPP_CALLOC(numberOfNamedArguments, sizeof(Il2CppCattrNamedArg));
        }

        virtual void VisitArgument(const il2cpp::metadata::CustomAttributeArgument& argument, uint32_t index)
        {
            AddArgumentValueToArray(m_attributeData->typedArgs, argument, index);
        }

        virtual void VisitField(const il2cpp::metadata::CustomAttributeFieldArgument& field, uint32_t index)
        {
            AddArgumentValueToArray(m_attributeData->namedArgs, field.arg, index);
            m_attributeData->argInfo[index].type = field.field->type;
            m_attributeData->argInfo[index].field = field.field;
        }

        virtual void VisitProperty(const il2cpp::metadata::CustomAttributePropertyArgument& prop, uint32_t index)
        {
            AddArgumentValueToArray(m_attributeData->namedArgs, prop.arg, index + m_propertyIndexOffset);
            m_attributeData->argInfo[index + m_propertyIndexOffset].type = il2cpp::vm::Property::GetType(prop.prop);
            m_attributeData->argInfo[index + m_propertyIndexOffset].prop = prop.prop;
        }

    private:
        int32_t m_propertyIndexOffset;
        Il2CppCustomAttributeData* m_attributeData;

        static void AddArgumentValueToArray(Il2CppArray* array, const il2cpp::metadata::CustomAttributeArgument arg, uint32_t index)
        {
            Il2CppObject* argumentValue = il2cpp::vm::Class::IsValuetype(arg.klass) ? il2cpp::vm::Object::Box(arg.klass, (void*)&arg.data) : reinterpret_cast<Il2CppObject*>(arg.data.obj);
            il2cpp_array_setref(array, index, argumentValue);
        }
    };

    static void free_custom_attribute_data(Il2CppCustomAttributeData* attr)
    {
        IL2CPP_FREE(attr->argInfo);
        il2cpp::gc::GarbageCollector::FreeFixed(attr);
    }

    void il2cpp_free_custom_attribute_data_list(Il2CppCustomAttributeDataList* attrs)
    {
        for (int32_t i = 0; i < attrs->numberOfAttributes; ++i)
            free_custom_attribute_data(attrs->attributeData[i]);

        IL2CPP_FREE(attrs->attributeData);
        IL2CPP_FREE(attrs);
    }

    Il2CppCustomAttributeDataList* il2cpp_get_custom_attribute_data_list(MonoClass* attr_klass, MonoCustomAttrInfo* cinfo, MonoImage* image)
    {
        // Get a reader to access the attribute data.
        void* start;
        void* end;
        std::tie(start, end) = il2cpp::vm::GlobalMetadata::GetCustomAttributeDataRange((Il2CppMetadataCustomAttributeHandle)cinfo);
        auto reader = il2cpp::metadata::CustomAttributeDataReader(start, end);

        std::vector<Il2CppCustomAttributeData*> attributeData;
        il2cpp::metadata::LazyCustomAttributeData data;
        Il2CppException* exc = NULL;

        // First, iterate the data lazily to get the attribute types.
        il2cpp::metadata::CustomAttributeDataIterator iter = reader.GetDataIterator();
        while (reader.ReadLazyCustomAttributeData((const Il2CppImage*)image, &data, &iter, &exc))
        {
            if (attr_klass == NULL || il2cpp::vm::Class::HasParent(data.ctor->klass, (Il2CppClass*)attr_klass))
            {
                // Now that we have found an attribute type we want to use (or we use all types), let's
                // fill out an Il2CppCustomAttributeData structure with all of the information the debugger will need.
                auto thisAttributeData = (Il2CppCustomAttributeData*)il2cpp::gc::GarbageCollector::AllocateFixed(sizeof(Il2CppCustomAttributeData), NULL);
                thisAttributeData->ctor = data.ctor;

                DebuggerCustomAttributeVisitor visitor(thisAttributeData);
                il2cpp::metadata::CustomAttributeDataReader::VisitCustomAttributeData((const Il2CppImage*)image, data.ctor, data.dataStart, data.dataLength, &visitor, &exc);

                attributeData.push_back(thisAttributeData);
            }
        }

        // If an error occured, we don't have a great way to communicate what it is. Just return NULL and let the client handle
        // it in a general way.
        if (exc != NULL)
        {
            for (auto attr : attributeData)
                free_custom_attribute_data(attr);
            return NULL;
        }

        // Allocate a structure to hold the data for all attributes.
        Il2CppCustomAttributeDataList* attrs = (Il2CppCustomAttributeDataList*)IL2CPP_MALLOC(sizeof(Il2CppCustomAttributeDataList));

        // Allocate an array of pointers (the size and the number of pointers) to provide to the C code for the debugger agent.
        attrs->numberOfAttributes = (int32_t)attributeData.size();
        attrs->attributeData = (Il2CppCustomAttributeData**)IL2CPP_MALLOC(attrs->numberOfAttributes * sizeof(Il2CppCustomAttributeData*));

        // Copy the GC allocated pointers to the C array.
        std::copy(attributeData.begin(), attributeData.end(), attrs->attributeData);

        return attrs;
    }

    MonoType* il2cpp_class_get_byval_arg(MonoClass* klass)
    {
        return (MonoType*)&((Il2CppClass*)klass)->byval_arg;
    }
}

#endif // RUNTIME_IL2CPP
