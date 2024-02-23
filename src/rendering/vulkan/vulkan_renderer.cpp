#include "vulkan_renderer.h"

#include <iostream>

#include <VkBootstrap.h>
#include <tngin/service_locator.h>

#include "vulkan_initializers.h"
#include "vulkan_types.h"
#include "vulkan_utilities.h"

namespace TAL {
    void VulkanRenderer::Init(RendererSettings settings) {
        _rendererSettings = settings;

        init_core();
    }

    void VulkanRenderer::Shutdown() {

    }

    void VulkanRenderer::RenderFrame() {

    }


    /*
    * PRIVATE
    */

   void VulkanRenderer::init_core() {
        // Initialize Vulkan Instance
        vkb::InstanceBuilder builder;

        // Enable MoltenVK extensions
        builder.enable_extension("VK_MVK_macos_surface");
        auto builderInstance = builder.set_app_name(_rendererSettings.app_name.c_str())
            .request_validation_layers()
            .use_default_debug_messenger()
            .build();

        if (!builderInstance) {
            std::cerr << "Failed to create Vulkan instance. Error: " << builderInstance.error().message() << std::endl;
        }


        vkb::Instance vkbInstance = builderInstance.value();

        _instance = vkbInstance.instance;
        _debug_messenger = vkbInstance.debug_messenger;

        // request vulkan surface
        std::unordered_map<SurfaceArgs, int*> surfaceArgs {
            {SurfaceArgs::INSTANCE, reinterpret_cast<int*>(_instance)},
            {SurfaceArgs::OUT_SURFACE, reinterpret_cast<int*>(&_surface)}
        };
        ServiceLocator::GetWindow()->RequestDrawSurface(surfaceArgs);

        // Select a physical device
        vkb::PhysicalDeviceSelector selector {vkbInstance};
        selector.add_required_extension("VK_KHR_portability_subset");

             vkb::PhysicalDevice vkbPhysicalDevice{
                selector
                    .set_minimum_version(1, 1)
                    .set_surface(_surface)
                    .select()
                    .value()
             };
        
        // create the vulkan device
        vkb::DeviceBuilder deviceBuilder { vkbPhysicalDevice };
        vkb::Device vkbDevice { deviceBuilder.build().value() };

        _device = vkbDevice.device;
        _physical_device = vkbPhysicalDevice.physical_device;

        _graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
        _graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
   }
}