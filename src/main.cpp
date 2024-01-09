/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:57:56 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/10 00:47:36 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan.hpp>
#include <vulkan/vulkan_core.h>

const char* TITLE = "scop";
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class VulkanApp {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    vk::UniqueInstance instance;
    vk::UniqueSurfaceKHR surface;
    vk::PhysicalDevice physicalDevice;
    vk::UniqueDevice device;
    vk::Queue graphicsQueue;
    vk::Queue presentQueue;
    vk::UniqueSwapchainKHR swapChain;
    std::vector<vk::Image> swapChainImages;
    std::vector<vk::UniqueImageView> swapChainImageViews;
    vk::UniquePipelineLayout pipelineLayout;
    vk::UniqueRenderPass renderPass;
    vk::UniquePipeline graphicsPipeline;
    std::vector<vk::UniqueFramebuffer> swapChainFramebuffers;
    vk::UniqueCommandPool commandPool;
    std::vector<vk::UniqueCommandBuffer> commandBuffers;

    void initWindow() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }

        // Set GLFW hints to use Vulkan on macOS
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);

        window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
        if (!window) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        glfwSetWindowUserPointer(window, this);
        glfwSetWindowSizeCallback(window, VulkanApp::onWindowResized);
    }

    static void onWindowResized(GLFWwindow* window, int width, int height) {
        if (width == 0 || height == 0) return;

        VulkanApp* app = reinterpret_cast<VulkanApp*>(glfwGetWindowUserPointer(window));
        app->recreateSwapChain();
    }

    void initVulkan() {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        createLogicalDevice();
        createSwapChain();
        createImageViews();
        createRenderPass();
        createGraphicsPipeline();
        createFramebuffers();
        createCommandPool();
        createCommandBuffers();
    }

    void createInstance() {
        vk::ApplicationInfo appInfo("YourAppName", VK_MAKE_VERSION(1, 0, 0), "No Engine", VK_MAKE_VERSION(1, 0, 0), VK_API_VERSION_1_0);

        vk::InstanceCreateInfo createInfo({}, &appInfo);

        // Manually define VK_KHR_PORTABILITY_EXTENSION_NAME or include the Vulkan core header file
        const char* extensionName = "VK_KHR_portability_enumeration";

        createInfo.enabledExtensionCount = 1;
        createInfo.ppEnabledExtensionNames = &extensionName;

        // Set the VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR flag
        createInfo.flags = vk::InstanceCreateFlags(VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);

        instance = vk::createInstanceUnique(createInfo);

        // Print supported Vulkan extensions
        uint32_t extensionCount = 0;
        const char** extensions = glfwGetRequiredInstanceExtensions(&extensionCount);

        std::cout << "Supported Vulkan Extensions:" << std::endl;
        for (uint32_t i = 0; i < extensionCount; ++i) {
            std::cout << extensions[i] << std::endl;
        }
    }

    void createSurface() {
        // TODO
    }

    void pickPhysicalDevice() {
        // TODO: Implement physical device selection here
    }

    void createLogicalDevice() {
        // TODO: Implement logical device creation here
    }

    void createSwapChain() {
        // TODO: Implement swap chain creation here
    }

    void createImageViews() {
        // TODO: Implement image view creation here
    }

    void createRenderPass() {
        // TODO: Implement render pass creation here
    }

    void createGraphicsPipeline() {
        // TODO: Implement graphics pipeline creation here
    }

    void createFramebuffers() {
        // TODO: Implement framebuffer creation here
    }

    void createCommandPool() {
        // TODO: Implement command pool creation here
    }

    void createCommandBuffers() {
        // TODO: Implement command buffer creation here
    }

    void mainLoop() {
        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }
    }

    void cleanup() {
        // TODO: Implement cleanup code here
    }

    void recreateSwapChain() {
        // TODO: Implement swap chain recreation on window resize
    }
};

int main() {
    VulkanApp app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
