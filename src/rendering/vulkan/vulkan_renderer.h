#pragma once

#include <tngin/rendering/renderer.h>

#include <vulkan/vulkan.h>


namespace TAL {
    class VulkanRenderer : public Renderer {
            /*
            * FUNCTIONS
            */
        public:
            void Init(RendererSettings settings) override;
            void Shutdown() override;
            void RenderFrame() override;

        private:
        void init_core();
            /*
            * MEMBERS
            */

        private:
            RendererSettings _rendererSettings {};

            /*
            * CORE VULKAN
            */
            VkInstance _instance;
            VkDebugUtilsMessengerEXT _debug_messenger;
            VkPhysicalDevice _physical_device;
            VkDevice _device;                   // logical device
            VkSurfaceKHR _surface;
    };
}