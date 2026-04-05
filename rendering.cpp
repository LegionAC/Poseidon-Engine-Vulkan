#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <vector>
#include "device.h"

class rendering {
public:
        void initialiseObjs() {
            initVulkan();
            initWindow();
            mainLoop();
            cleanup();
        };
private:
    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice logicalDevice = VK_NULL_HANDLE;

        void initVulkan() {
            createInstance();

            vkEnumerate();

            createLogicalDevice(physicalDevice, logicalDevice);
        }
        void mainLoop() {
            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                
                glfwSwapBuffers(window);
            }
        }
        void cleanup() {
            vkDestroyDevice(logicalDevice, nullptr);

            vkDestroyInstance(instance, nullptr);

            glfwDestroyWindow(window);

            glfwTerminate();
        }
        void initWindow() {
            glfwInit();

            GLFWmonitor* monitor = glfwGetPrimaryMonitor();

            const GLFWvidmode* mode = glfwGetVideoMode(monitor); // const due to read only video mode

            int width = mode->width;
            int height = mode->height;

            window = glfwCreateWindow(width, height, "Poseidon Engine", nullptr, window);
        }

        void createInstance() {
            VkApplicationInfo appInfo;
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "Poseidon Engine";
            appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
            appInfo.pEngineName = "No Engine";
            appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;

            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
                throw std::runtime_error("Failed to create instance!");
            } else {
                std::cout << "Successful creation of instance.\n";
            }
        }

        void vkEnumerate() {
            findPhysicalDevices(instance, physicalDevice);

            if (physicalDevice != VK_NULL_HANDLE) {
                std::cout << "Physical device successfully selected.\n";
            } else {
                throw std::runtime_error("No device selected. Exiting...");
            }
        }

};