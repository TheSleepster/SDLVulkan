#if !defined(ENTRY_VULKANTEST_H)
/* ========================================================================
   $File: entry_Vulkantest.h $
   $Date: October 25 2024 06:41 pm $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#define ENTRY_VULKANTEST_H

#include <vulkan/vulkan.h>
#include <SDL3/SDL.h>

#include "Intrinsics.h"
#include "util/Math.h"
#include "util/String.h"
#include "util/FileIO.h"
#include "util/Arena.h"
#include "util/Pairs.h"

struct application_data
{
    SDL_Window *Window;
    string      ApplicationName;

    ivec4 SizeData;
    bool  Running;
};

struct application_time
{
    uint64 PerformanceCountFrequency;
    uint64 LastTime;
    uint64 CurrentTime;
    real64 DeltaTime;
};

struct application_memory
{
    memory_arena PermanentStorage;
    memory_arena TemporaryStorage;
};

struct vulkan_data
{
    VkApplicationInfo    VKInfo;
    VkInstanceCreateInfo VKInstanceData;
    VkInstance           VKContext;

    uint32               VKExtensionCount;
};

#endif // ENTRY_VULKANTEST_H

