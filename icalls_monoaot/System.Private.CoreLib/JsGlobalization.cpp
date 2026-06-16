#include "il2cpp-config.h"
#include "JsGlobalization.h"

#if IL2CPP_TARGET_JAVASCRIPT

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
    // Implemented in javascript
    extern "C" intptr_t mono_wasm_get_locale_info(Il2CppChar* locale, int32_t localeLength, Il2CppChar* culture, int32_t cultureLength, Il2CppChar* buffer, int32_t bufferLength, int32_t* resultLength);

    intptr_t JsGlobalization::GetLocaleInfo(Il2CppChar* locale, int32_t localeLength, Il2CppChar* culture, int32_t cultureLength, Il2CppChar* buffer, int32_t bufferLength, int32_t* resultLength)
    {
        return mono_wasm_get_locale_info(locale, localeLength, culture, cultureLength, buffer, bufferLength, resultLength);
    }
} // namespace CoreLib
} // namespace Private
} // namespace System
} // namespace icalls
} // namespace il2cpp

#endif // IL2CPP_TARGET_JAVASCRIPT
