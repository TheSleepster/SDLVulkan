/* ========================================================================
   $File: entry_VulkanTest.cpp $
   $Date: October 25 2024 06:27 pm $
   $Revision: $
   $Creator: Justin Lewis $
   ======================================================================== */

#include <stdio.h>
#include <SDL3/SDL.h>
#include <vulkan/vulkan.h>
#include <SDL3/SDL_vulkan.h>

#include "Intrinsics.h"
#include "util/Math.h"
#include "util/String.h"
#include "util/FileIO.h"
#include "util/Arena.h"
#include "util/Pairs.h"

#include "entry_VulkanTest.h"

int main()
{
    application_data   ApplicationData = {};
    application_time   Time = {};
    application_memory MemoryPools = {};
    vulkan_data        VulkanData = {};

    if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_EVENTS|SDL_INIT_AUDIO))
    {
        MemoryPools.PermanentStorage = ArenaCreate(Megabytes(100));
        MemoryPools.TemporaryStorage = ArenaCreate(Megabytes(100));

        ApplicationData.SizeData = {0, 0, 1920, 1080};
        ApplicationData.ApplicationName = STR("Vulkan Test");
        ApplicationData.Window = SDL_CreateWindow(CSTR(ApplicationData.ApplicationName), 
                ApplicationData.SizeData.Width,
                ApplicationData.SizeData.Height,
                SDL_WINDOW_VULKAN|SDL_WINDOW_FULLSCREEN);

        Time.PerformanceCountFrequency = SDL_GetPerformanceFrequency();
        if(ApplicationData.Window)
        {
            VulkanData.VKInfo = {};
            VulkanData.VKInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            VulkanData.VKInfo.pApplicationName = "Hello, Vulkan!";
            VulkanData.VKInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            VulkanData.VKInfo.pEngineName = "No Engine";
            VulkanData.VKInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            VulkanData.VKInfo.apiVersion = VK_API_VERSION_1_0;

            VulkanData.VKInstanceData = {};
            VulkanData.VKInstanceData.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            VulkanData.VKInstanceData.pApplicationInfo = &VulkanData.VKInfo;

            const char* const *InstanceExtensions = SDL_Vulkan_GetInstanceExtensions(&VulkanData.VKExtensionCount);
            VulkanData.VKInstanceData.enabledExtensionCount = VulkanData.VKExtensionCount;
            VulkanData.VKInstanceData.ppEnabledExtensionNames = InstanceExtensions;
            VulkanData.VKInstanceData.enabledLayerCount = 0;
            VkResult Result = vkCreateInstance(&VulkanData.VKInstanceData, 0, &VulkanData.VKContext);
            Check(Result == VK_SUCCESS, "Failure To Create the VKContext\n");

            Time.LastTime = SDL_GetPerformanceCounter();

            ApplicationData.Running = 1;
            while(ApplicationData.Running)
            {
                Time.CurrentTime = SDL_GetPerformanceCounter();
                Time.DeltaTime   = real64((Time.CurrentTime - Time.LastTime)) / real64(Time.PerformanceCountFrequency);
                Time.LastTime    = Time.CurrentTime;

                SDL_Event Evnt;
                while(SDL_PollEvent(&Evnt))
                {
                    switch(Evnt.type)
                    {
                        case SDL_EVENT_KEY_DOWN:
                        {
                            if(Evnt.key.key == SDLK_ESCAPE)
                            {
                                ApplicationData.Running = false;
                            }
                        }break;
                        case SDL_EVENT_QUIT:
                        {
                            ApplicationData.Running = false;
                        }break;
                    }
                }
                // CODE
                printm("[INFO]: DeltaTime = %f", Time.DeltaTime);
            }
        }
        else
        {
            const char *Error = SDL_GetError();
            printm("[ERROR] SDL Failed To Init, Code: %s\n", Error);
        }
    }
    else
    {
        const char *Error = SDL_GetError();
        printm("[ERROR] SDL Failed To Init, Code: %s\n", Error);
    }
    return(0);
}
