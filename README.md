# AtakaEngine

A lightweight DirectX 3D game engine built from scratch in C++. AtakaEngine provides a simple yet powerful framework for developing 3D graphics applications with DirectX 11 support.

## Features

- DirectX 11 graphics pipeline implementation
- Comprehensive shader and buffer management
- Window management and input handling
- Resource management system
- Modern C++ design patterns
- Support for 3D models via tinyobjloader
- DirectXTK integration for utility functions

## Prerequisites

### Required Software

- **Visual Studio 2022** or later with C++ development tools
- **Windows SDK** (DirectX 11 support required)
- **Windows 10/11** operating system

### Recommended Hardware

- DirectX 11 compatible graphics card
- 8GB RAM minimum (16GB recommended)
- SSD for faster compilation and asset loading

## Getting Started

### Building the Project

1. Open `DirectXGame/DirectXGame.sln` in Visual Studio

2. Select your desired build configuration (Debug/Release)

3. Build the solution:
   - Menu: Build > Build Solution
   - Or use the keyboard shortcut: Ctrl+Shift+B

4. Run the project:
   - Menu: Debug > Start Without Debugging
   - Or press: Ctrl+F5

### Project Configuration

The project uses the following directories for output:
- **Bin/** - Contains compiled binaries (.exe and .dll files)
- **Intermediate/** - Contains intermediate build files
- **DirectXGame/DX3D/Assets/** - Place game assets here

## Dependencies

The engine leverages the following libraries:

- **DirectX 11** - Core graphics API
- **DirectXTK** - Helper utilities for DirectX development
- **DirectXTex** - Texture processing library
- **tinyobjloader** - Wavefront OBJ model loader

All dependencies are included in the `DirectXGame/Libs/` directory and are pre-configured in the project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

This is a personal project developed for learning and experimentation with DirectX 11 game engine development. While I appreciate the interest, this project is not currently accepting external contributions.

Feel free to fork the repository and experiment with it as you wish!
