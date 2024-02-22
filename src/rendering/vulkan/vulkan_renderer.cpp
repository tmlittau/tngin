#include "vulkan_renderer.h"

#include <VkBootstrap.h>

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
        auto builderInstance = builder.set_app_name(_rendererSettings.app_name.c_str())
            .request_validation_layers(true)
            .require_api_version(1, 2, 0)
            .use_default_debug_messenger()
            .build();

        vkb::Instance vkbInstance = builderInstance.value();

        _instance = vkbInstance.instance;
        _debug_messenger = vkbInstance.debug_messenger;
   }
}