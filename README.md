# SDL2 Template

A cross-platform C++ application template using SDL2 with proper Metal support for Apple Silicon Macs and Windows compatibility.

## Features

- C++20 compliant codebase
- Cross-platform (macOS including Apple Silicon, Windows)
- Metal rendering backend on macOS with Apple Silicon
- SDL2 integrated as a git submodule
- CMake build system

## Project Structure

```
sdl2-template/
├── source/          # Source code (.cpp files)
├── include/         # Header files (.h/.hpp files)
├── build/           # Build output (not in repo)
├── sdl2/            # SDL2 submodule
├── CMakeLists.txt   # CMake configuration
├── .gitignore       # Git ignore file
├── .gitmodules      # Git submodules configuration
└── README.md        # This file
```

## Prerequisites

- CMake 3.16 or newer
- C++20 compatible compiler (Clang recommended)
- Git

### macOS

- Xcode Command Line Tools
- macOS 10.15 or newer

### Windows

- Visual Studio 2019 or newer with C++ development workload
- Windows 10 or newer

## Getting Started

### Clone the Repository

```bash
# Clone the repository with submodules
git clone --recursive https://github.com/yourusername/sdl2-template.git
cd sdl2-template

# If you already cloned without --recursive, initialize submodules:
git submodule update --init --recursive
```

### Build on macOS

```bash
# Create the build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
cmake --build . --config Release

# Run the application
./bin/sdl2-template
```

### Build on Windows

#### Using Visual Studio

```bash
# Create the build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Open the generated solution in Visual Studio
start sdl2-template.sln
```

Then build and run using Visual Studio.

#### Using Command Line

```bash
# Create the build directory
mkdir build
cd build

# Configure with CMake
cmake .. -G "Visual Studio 17 2022" -A x64

# Build
cmake --build . --config Release

# Run the application
.\bin\Release\sdl2-template.exe
```

## Metal Support on macOS

For Apple Silicon Macs, the application automatically uses Metal as the rendering backend. This ensures optimal performance on newer macOS devices while maintaining compatibility with older Intel Macs.

## Adding New Source Files

1. Create your .cpp files in the `source/` directory
2. Create your .h/.hpp files in the `include/` directory
3. The CMake configuration will automatically detect and include new source files

## Troubleshooting

### Metal Not Working on macOS

Make sure you're running on a supported macOS version (10.15+) and that SDL2 is properly initialized with the Metal flag.

### Windows DLL Issues

If you encounter "missing DLL" errors on Windows, make sure the SDL2.dll file is correctly copied to the output directory. This should happen automatically during the build process.

### CMake Configuration Issues

- Make sure you have the correct version of CMake installed
- Ensure all submodules are properly initialized
- Check that your compiler supports C++20

## License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request