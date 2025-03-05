A simple Vulkan renderer with a movable camera and basic abstraction to simplify Vulkan's complex API. This project provides an easy-to-understand framework for using Vulkan for 3D rendering while abstracting the more complicated aspects of the API.

## Features
- A simple Vulkan renderer.
- A movable camera for navigating the scene.
- Basic abstraction to ease the usage of Vulkan.
- Tested with MSVC 2022.

## Requirements
- **Vulkan SDK**: You need to have the Vulkan SDK installed to build this project.
- **MSVC 2022**: This project has been tested with Visual Studio 2022.
- **Premake5**: Used for project configuration (ensure Premake5 is installed).

## Setup

1. **Install Vulkan SDK**: You need to have the [Vulkan SDK](https://vulkan.lunarg.com/sdk/home) installed. Set the `VULKAN_SDK` environment variable to the installation path of Vulkan.

2. **Install Visual Studio 2022**: Make sure you have Visual Studio 2022 with C++ development tools installed.

3. **Build with Premake**:
   - The project uses Premake5 for configuration. Simply click and run the `premake5.bat` file to generate project files for MSVC 2022.
   
4. **C++ Version**: There is a known issue with Premake's default C++ version. To build this project, you need to manually change the C++ version in Visual Studio:
   - Open the generated Visual Studio project.
   - Go to **Project Properties** -> **C/C++** -> **Language** -> **C++ Language Standard**.
   - Set it to **C++23**.

5. **Build the Project**: After running the `premake5.bat` file, open the project in Visual Studio, build it, and run the resulting executable.

## Contributing

This project is open to contributions. If you'd like to contribute, please fork the repository and create a pull request with your changes.

## Known Issues

- Premake has some known bugs, particularly around handling the C++ version and generating the correct configurations. Please ensure you manually adjust the C++ version to C++23 in Visual Studio after generating the project files.
  
## License

This project is open-source and free to use and modify. Please feel free to contribute or adapt it for your needs.
