#pragma once
#include <vulkan/vulkan.h>
#include <vector>

int deviceRate(VkPhysicalDevice physical_device);
void deviceQuery(std::vector<VkPhysicalDevice> physical_devices, VkPhysicalDevice& physicalDevice);
void findPhysicalDevices(VkInstance instance, VkPhysicalDevice& physicalDevice);
void createLogicalDevice(VkPhysicalDevice& physicalDevice, VkDevice& device);