/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VulkanApp.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourgea <rbourgea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 08:57:56 by rbourgea          #+#    #+#             */
/*   Updated: 2024/01/18 11:27:47 by rbourgea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VULKAN_APP_HPP
#define VULKAN_APP_HPP

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <chrono>
#include <limits>
#include <optional>
#include <iomanip>
#include <array>
#include <set>

#define MATH_FORCE_DEPTH_ZERO_TO_ONE
#include "Math.hpp"
#include "Image.hpp"

inline const char* TITLE = "scop";
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const int MAX_FRAMES_IN_FLIGHT = 2;

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation",
#ifdef __linux__
    "VK_LAYER_MESA_overlay", // display fps
#endif
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

#ifdef DEBUG
    constexpr bool debugMode = true;
#else
    constexpr bool debugMode = false;
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator);

struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete() {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;
    std::vector<VkSurfaceFormatKHR> formats;
    std::vector<VkPresentModeKHR> presentModes;
};

struct Camera {
    vec3 eye;
    vec3 center;
    vec3 up;
};

struct Vertex {
    vec3 pos;
    vec3 color;
    vec2 texCoord;
    vec3 ambientColor;
    vec3 specularColor;
    float dissolveFactor;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 5> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 5> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(Vertex, ambientColor);

        attributeDescriptions[4].binding = 0;
        attributeDescriptions[4].location = 4;
        attributeDescriptions[4].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[4].offset = offsetof(Vertex, specularColor);

        return attributeDescriptions;
    }
};

struct UniformBufferObject {
    alignas(16) mat4 model;
    alignas(16) mat4 view;
    alignas(16) mat4 proj;
};

// const std::vector<Vertex> vertices = {
//     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//     {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//     {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
// };

// const std::vector<uint32_t> indices = {
//     0, 1, 2, 2, 3, 0
// };

// const std::vector<Vertex> vertices = {
//     {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//     {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//     {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

//     {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
//     {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
//     {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
//     {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
// };

// const std::vector<uint32_t> indices = {
//     0, 1, 2, 2, 3, 0,
//     4, 5, 6, 6, 7, 4
// };

class VulkanApp {
public:
    void run(const std::string& objFile1);

private:
    GLFWwindow* window;

    Camera cameraView {
        vec3(5.0f, 5.0f, 0.0f),
        vec3(0.0f, 0.0f, 0.0f),
        vec3(0.0f, 1.0f, 0.0f)
    };

    vec3 positionModel;
    vec3 rotationModel;

    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool mouseDrag = false;

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;

    VkInstance instance;
    VkDebugUtilsMessengerEXT debugMessenger;
    VkSurfaceKHR surface;

    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;

    VkQueue graphicsQueue;
    VkQueue presentQueue;

    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    VkFormat swapChainImageFormat;
    VkExtent2D swapChainExtent;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;

    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;

    VkImage depthImage;
    VkDeviceMemory depthImageMemory;
    VkImageView depthImageView;

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;
    VkImageView textureImageView;
    VkSampler textureSampler;

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;

    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    size_t currentFrame = 0;

    bool framebufferResized = false;

    /* ================================= **
    ** Vulkan initialization             **
    ** File: VulkanInit.cpp              **
    ** ================================= */
    void initWindow();
    void initVulkan();
    void mainLoop();

    bool checkValidationLayerSupport();
    std::vector<const char*> getRequiredExtensions();
    void createInstance();
    void createSurface();

    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
    bool isDeviceSuitable(VkPhysicalDevice device);
    void pickPhysicalDevice();
    void createLogicalDevice();

    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    void createSwapChain();
    void recreateSwapChain();

    /* ================================= **
    ** Vulkan cleaning                   **
    ** File: VulkanClean.cpp             **
    ** ================================= */
    void cleanup();
    void cleanupSwapChain();
    void cleanupVertexBuffer();

    /* ================================= **
    ** Vulkan debug logs                 **
    ** File: VulkanDebug.cpp             **
    ** ================================= */
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void setupDebugMessenger();

    /* ================================= **
    ** Vulkan graphics pipeline          **
    ** File: VulkanPipeline.cpp          **
    ** ================================= */
    void createRenderPass();
    VkShaderModule createShaderModule(const std::vector<char>& code);
    void createGraphicsPipeline();
    void createDescriptorSetLayout();
    void createUniformBuffers();
    void updateUniformBuffer(uint32_t currentImage);
    void createDescriptorPool();
    void createDescriptorSets();

    /* ================================= **
    ** Vulkan render                     **
    ** File: VulkanRender.cpp            **
    ** ================================= */
    void createFramebuffers();
    void createCommandPool();
    void createCommandBuffers();
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
    void createSyncObjects();
    void drawFrame();
    VkCommandBuffer beginSingleTimeCommands();
    void endSingleTimeCommands(VkCommandBuffer commandBuffer);
    void createDepthResources();

    /* ================================= **
    ** Vertex buffers                    **
    ** File: VulkanVertex.cpp            **
    ** ================================= */
    void createVertexBuffer();
    void updateVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    /* ================================= **
    ** Index buffers                     **
    ** File: VulkanIndex.cpp             **
    ** ================================= */
    void createIndexBuffer();
   
    /* ================================= **
    ** Images and Textures               **
    ** File: VulkanTexture.cpp           **
    ** ================================= */ 
    void createTextureImage();
    void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
    void createImageViews();
    void createTextureImageView();
    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags);
    void createTextureSampler();
    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
    VkFormat findDepthFormat();
    bool hasStencilComponent(VkFormat format);

    /* ================================= **
    ** Parsing files                     **
    ** File: Parsing.cpp                 **
    ** ================================= */
    void parseObjFile(const std::string& filename);
    void parseMtlFile(const std::string& objFilePath, const std::string& mtlFilename);
    static std::vector<char> readFile(const std::string& filename);

    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        (void)scancode;
        auto app = reinterpret_cast<VulkanApp*>(glfwGetWindowUserPointer(window));

        if ((action == GLFW_PRESS || action == GLFW_REPEAT) && !(mods & GLFW_MOD_SHIFT)) {
            switch (key) {
                // CameraView Center
                case GLFW_KEY_UP:
                    app->cameraView.center += vec3(0, 1, 0);
                    break;
                case GLFW_KEY_DOWN:
                    app->cameraView.center += vec3(0, -1, 0);
                    break;
                case GLFW_KEY_LEFT:
                    app->cameraView.center += vec3(0, 0, 1);
                    break;
                case GLFW_KEY_RIGHT:
                    app->cameraView.center += vec3(0, 0, -1);
                    break;
                // Position X, Y, Z
                case GLFW_KEY_1:
                    app->positionModel += vec3(1.0f, 0.0f, 0.0f);
                    break;
                case GLFW_KEY_2:
                    app->positionModel += vec3(0.0f, 1.0f, 0.0f);
                    break;
                case GLFW_KEY_3:
                    app->positionModel += vec3(0.0f, 0.0f, 1.0f);
                    break;
                // Rotation X, Y, Z
                case GLFW_KEY_4:
                    app->rotationModel += vec3(1.0f, 0.0f, 0.0f);
                    break;
                case GLFW_KEY_5:
                    app->rotationModel += vec3(0.0f, 1.0f, 0.0f);
                    break;
                case GLFW_KEY_6:
                    app->rotationModel += vec3(0.0f, 0.0f, 1.0f);
                    break;
                // RESET
                case GLFW_KEY_SPACE:
                    app->positionModel = vec3(0.0f, 0.0f, 0.0f);
                    app->rotationModel = vec3(0.0f, 0.0f, 0.0f);
                    break;
                // RGB COLORS
                case GLFW_KEY_R:
                    for (auto& vertex : app->vertices) {
                        vertex.color = vec3(1, 0.3, 0.3);
                    }
                    app->updateVertexBuffer();
                    break;
                case GLFW_KEY_G:
                    for (auto& vertex : app->vertices) {
                        vertex.color = vec3(0.3, 1, 0.3);
                    }
                    app->updateVertexBuffer();
                    break;
                case GLFW_KEY_B:
                    for (auto& vertex : app->vertices) {
                        vertex.color = vec3(0.3, 0.3, 1);
                    }
                    app->updateVertexBuffer();
                    break;
                case GLFW_KEY_D:
                    for (size_t i = 0; i < app->vertices.size(); ++i) {
                        auto& vertex = app->vertices[i];
                        if (i % 2 == 0) {
                            vertex.color = vec3(0, 0, 0);
                        } else {
                            vertex.color = vec3(1, 1, 1);
                        }
                    }
                    app->updateVertexBuffer();
                    break;
                default:
                    break;
            }
        } else if ((action == GLFW_PRESS || action == GLFW_REPEAT) && (mods & GLFW_MOD_SHIFT)) {
            switch (key) {
            // Position X, Y, Z
            case GLFW_KEY_1:
                app->positionModel += vec3(-1.0f, 0.0f, 0.0f);
                break;
            case GLFW_KEY_2:
                app->positionModel += vec3(0.0f, -1.0f, 0.0f);
                break;
            case GLFW_KEY_3:
                app->positionModel += vec3(0.0f, 0.0f, -1.0f);
                break;
            // Rotation X, Y, Z
            case GLFW_KEY_4:
                app->rotationModel += vec3(-1.0f, 0.0f, 0.0f);
                break;
            case GLFW_KEY_5:
                app->rotationModel += vec3(0.0f, -1.0f, 0.0f);
                break;
            case GLFW_KEY_6:
                app->rotationModel += vec3(0.0f, 0.0f, -1.0f);
                break;
            default:
                break;
            }
        }
    }

    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        (void)mods;
        VulkanApp* app = reinterpret_cast<VulkanApp*>(glfwGetWindowUserPointer(window));

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            if (action == GLFW_PRESS) {
                app->mouseDrag = true;
                glfwGetCursorPos(window, &app->lastMouseX, &app->lastMouseY);
            } else if (action == GLFW_RELEASE) {
                app->mouseDrag = false;
            }
        }
    }

    static void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
        VulkanApp* app = reinterpret_cast<VulkanApp*>(glfwGetWindowUserPointer(window));

        if (app->mouseDrag) {
            float deltaX = static_cast<float>(xpos - app->lastMouseX);
            float deltaY = static_cast<float>(ypos - app->lastMouseY);

            app->rotationModel.x += deltaY * -0.1f;
            app->rotationModel.y += deltaX * -0.1f;

            app->lastMouseX = xpos;
            app->lastMouseY = ypos;
        }
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        (void)messageSeverity;
        (void)messageType;
        (void)pUserData;
        std::cerr << "- Validation layer: " << pCallbackData->pMessage << std::endl;
        return VK_FALSE;
    }

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
        (void)width;
        (void)height;
        auto app = reinterpret_cast<VulkanApp*>(glfwGetWindowUserPointer(window));
        app->framebufferResized = true;
    }
};

#endif
