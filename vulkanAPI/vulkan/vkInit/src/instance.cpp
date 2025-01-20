#include "pch.h"

#include "vkInit\include\instance.h" 


bool vkInit::supported(std::vector<const char*>& extensions, std::vector<const char*>& layers, bool debug) 
{

	//check extension support
	std::vector<vk::ExtensionProperties> supportedExtensions = vk::enumerateInstanceExtensionProperties();

	if (debug) {
		std::cout << "Device can support the following extensions:\n";
		for (vk::ExtensionProperties supportedExtension : supportedExtensions) {
			std::cout << '\t' << supportedExtension.extensionName << '\n';
		}
	}

	bool found;
	for (const char* extension : extensions) {
		found = false;
		for (vk::ExtensionProperties supportedExtension : supportedExtensions) {
			if (strcmp(extension, supportedExtension.extensionName) == 0) {
				found = true;
				if (debug) {
					std::cout << "Extension \"" << extension << "\" is supported!\n";
				}
			}
		}
		if (!found) {
			if (debug) {
				std::cout << "Extension \"" << extension << "\" is not supported!\n";
			}
			return false;
		}
	}

	//check layer support
	std::vector<vk::LayerProperties> supportedLayers = vk::enumerateInstanceLayerProperties();

	if (debug) {
		std::cout << "Device can support the following layers:\n";
		for (vk::LayerProperties supportedLayer : supportedLayers) {
			std::cout << '\t' << supportedLayer.layerName << '\n';
		}
	}

	for (const char* layer : layers) {
		found = false;
		for (vk::LayerProperties supportedLayer : supportedLayers) {
			if (strcmp(layer, supportedLayer.layerName) == 0) {
				found = true;
				if (debug) {
					std::cout << "Layer \"" << layer << "\" is supported!\n";
				}
			}
		}
		if (!found) {
			if (debug) {
				std::cout << "Layer \"" << layer << "\" is not supported!\n";
			}
			return false;
		}
	}

	return true;
}

vk::Instance vkInit::make_instance(const char* applicationName, bool debug)
{

	if (debug) {
		std::cout << "Making an instance...\n";
	}


	uint32_t version{ 0 };
	vkEnumerateInstanceVersion(&version);

	if (debug) {
		std::cout << "System can support vulkan Variant: " << VK_API_VERSION_VARIANT(version)
			<< ", Major: " << VK_API_VERSION_MAJOR(version)
			<< ", Minor: " << VK_API_VERSION_MINOR(version)
			<< ", Patch: " << VK_API_VERSION_PATCH(version) << '\n';
	}


	version &= ~(0xFFFU);

	version = VK_MAKE_API_VERSION(0, 1, 3, 0);


	vk::ApplicationInfo appInfo = vk::ApplicationInfo( 
		applicationName,
		version,
		"Doing it the hard way",
		version,
		version
	);


	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	//In order to hook in a custom validation callback
	if (debug) {
		extensions.push_back("VK_EXT_debug_utils");
	}

	if (debug) {
		std::cout << "extensions to be requested:\n";

		for (const char* extensionName : extensions) {
			std::cout << "\t\"" << extensionName << "\"\n";
		}
	}

	std::vector<const char*> layers;
	if (debug) {
		layers.push_back("VK_LAYER_KHRONOS_validation");
	}

	if (!supported(extensions, layers, debug)) {
		return nullptr;
	}

	vk::InstanceCreateInfo createInfo = vk::InstanceCreateInfo(
		vk::InstanceCreateFlags(),
		&appInfo,
		static_cast<uint32_t>(layers.size()), layers.data(), // enabled layers
		static_cast<uint32_t>(extensions.size()), extensions.data() // enabled extensions
	);


	try {

		return vk::createInstance(createInfo);
	}
	catch (vk::SystemError err) {
		if (debug) {
			std::cout << "Failed to create Instance!\n";
		}
		return nullptr;
	}
}