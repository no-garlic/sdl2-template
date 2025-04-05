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

## Setting Up Visual Studio Code

Visual Studio Code provides excellent support for C++ development with CMake. Here's how to set it up for this project:

### Required Extensions

Install the following extensions in VS Code:
- C/C++ (`ms-vscode.cpptools`)
- CMake Tools (`ms-vscode.cmake-tools`)
- CMake Language Support (`twxs.cmake`)

### Setup on macOS

1. **Install the prerequisites**:
   ```bash
   # Install Homebrew if not already installed
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   
   # Install required packages
   brew install cmake llvm
   
   # Install Xcode Command Line Tools if not already installed
   xcode-select --install
   ```

2. **Open the project in VS Code**:
   ```bash
   code .
   ```

3. **Configure CMake**:
   - When prompted, select the Clang compiler kit
   - Select "Debug" or "Release" from the bottom toolbar

4. **Configure launch.json for debugging**:
   - Press `Cmd+Shift+P` and select "Add Debug Configuration..."
   - Choose "C++ (GDB/LLDB)"
   - Select "LLDB: Launch"
   - Modify the generated file to look like this:

   ```json
   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "Debug SDL2 Template",
               "type": "lldb",
               "request": "launch",
               "program": "${workspaceFolder}/build/bin/sdl2-template",
               "args": [],
               "cwd": "${workspaceFolder}",
               "preLaunchTask": "Build SDL2 Template"
           }
       ]
   }
   ```

5. **Configure tasks.json**:
   - Create a `.vscode/tasks.json` file:

   ```json
   {
       "version": "2.0.0",
       "tasks": [
           {
               "label": "Build SDL2 Template",
               "type": "shell",
               "command": "cmake --build ${workspaceFolder}/build --config Debug",
               "group": {
                   "kind": "build",
                   "isDefault": true
               },
               "problemMatcher": [
                   "$gcc"
               ]
           }
       ]
   }
   ```

6. **Build and Debug**:
   - Build: Press `F7` or click the "Build" button in the CMake toolbar
   - Debug: Press `F5` to start debugging

### Setup on Windows

1. **Install prerequisites**:
   - Install Visual Studio 2019 or newer with C++ development workload
   - Install Git for Windows
   - Install CMake

2. **Open the project in VS Code**:
   ```bash
   code .
   ```

3. **Configure CMake**:
   - When prompted, select the Visual Studio compiler kit
   - Select "Debug" or "Release" from the bottom toolbar

4. **Configure launch.json for debugging**:
   - Press `Ctrl+Shift+P` and select "Add Debug Configuration..."
   - Choose "C++ (Windows)"
   - Select "cl.exe build and debug active file"
   - Modify the generated file to look like this:

   ```json
   {
       "version": "0.2.0",
       "configurations": [
           {
               "name": "Debug SDL2 Template",
               "type": "cppvsdbg",
               "request": "launch",
               "program": "${workspaceFolder}/build/bin/Debug/sdl2-template.exe",
               "args": [],
               "stopAtEntry": false,
               "cwd": "${workspaceFolder}",
               "environment": [],
               "externalConsole": false,
               "preLaunchTask": "Build SDL2 Template"
           }
       ]
   }
   ```

5. **Configure tasks.json**:
   - Create a `.vscode/tasks.json` file:

   ```json
   {
       "version": "2.0.0",
       "tasks": [
           {
               "label": "Build SDL2 Template",
               "type": "shell",
               "command": "cmake --build ${workspaceFolder}/build --config Debug",
               "group": {
                   "kind": "build",
                   "isDefault": true
               },
               "problemMatcher": [
                   "$msCompile"
               ]
           }
       ]
   }
   ```

6. **Build and Debug**:
   - Build: Press `F7` or click the "Build" button in the CMake toolbar
   - Debug: Press `F5` to start debugging

### Useful VS Code Keyboard Shortcuts

- `F5`: Start debugging
- `Shift+F5`: Stop debugging
- `F7`: Build
- `F9`: Toggle breakpoint
- `F10`: Step over
- `F11`: Step into
- `Shift+F11`: Step out
- `Ctrl+Shift+B` (Windows) / `Cmd+Shift+B` (macOS): Run build task

### VS Code Settings for Better C++ Development

Create a `.vscode/settings.json` file with these recommended settings:

```json
{
    "cmake.configureOnOpen": true,
    "cmake.buildDirectory": "${workspaceFolder}/build",
    "cmake.defaultVariants": {
        "buildType": {
            "default": "debug",
            "description": "The build type.",
            "choices": {
                "debug": {
                    "short": "Debug",
                    "long": "Debug build with no optimizations",
                    "buildType": "Debug"
                },
                "release": {
                    "short": "Release",
                    "long": "Release build with optimizations",
                    "buildType": "Release"
                }
            }
        }
    },
    "C_Cpp.default.configurationProvider": "ms-vscode.cmake-tools",
    "files.associations": {
        "*.h": "cpp",
        "*.hpp": "cpp",
        "*.cpp": "cpp"
    },
    "editor.formatOnSave": true,
    "C_Cpp.clang_format_style": "Google"
}
```

## Metal Support on macOS

For Apple Silicon Macs, the application automatically uses Metal as the rendering backend. This ensures optimal performance on newer macOS devices while maintaining compatibility with older Intel Macs.

## Adding New Source Files

1. Create your .cpp files in the `source/` directory
2. Create your .h/.hpp files in the `include/` directory
3. The CMake configuration will automatically detect and include new source files

## Advanced VS Code Tips

### Integrated Terminal

You can use VS Code's integrated terminal to run commands:
- Press `` Ctrl+` `` (macOS and Windows) to open the terminal
- Run build commands directly from this terminal

### Custom Tasks

You can add custom tasks in `.vscode/tasks.json` for common operations:
- Clean build
- Run tests
- Package application

Example for a "Clean" task:

```json
{
    "label": "Clean Build",
    "type": "shell",
    "command": "rm -rf ${workspaceFolder}/build/* && mkdir -p ${workspaceFolder}/build && cd ${workspaceFolder}/build && cmake ..",
    "windows": {
        "command": "if exist ${workspaceFolder}\\build rmdir /s /q ${workspaceFolder}\\build && mkdir ${workspaceFolder}\\build && cd ${workspaceFolder}\\build && cmake .."
    },
    "group": "build",
    "problemMatcher": []
}
```

### IntelliSense Configuration

VS Code's IntelliSense provides code completion, parameter info, quick info, and member lists. To configure it:

1. Press `Ctrl+Shift+P` (Windows) or `Cmd+Shift+P` (macOS)
2. Type "C/C++: Edit Configurations (JSON)"
3. Add the following to the generated file:

```json
{
    "configurations": [
        {
            "name": "Mac",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/include/**",
                "${workspaceFolder}/sdl2/include/**"
            ],
            "defines": [],
            "macFrameworkPath": [
                "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks"
            ],
            "compilerPath": "/usr/bin/clang++",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "macos-clang-arm64",
            "configurationProvider": "ms-vscode.cmake-tools"
        },
        {
            "name": "Win32",
            "includePath": [
                "${workspaceFolder}/**",
                "${workspaceFolder}/include/**",
                "${workspaceFolder}/sdl2/include/**"
            ],
            "defines": [
                "_DEBUG",
                "UNICODE",
                "_UNICODE"
            ],
            "windowsSdkVersion": "10.0.19041.0",
            "compilerPath": "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.33.31629/bin/Hostx64/x64/cl.exe",
            "cStandard": "c17",
            "cppStandard": "c++20",
            "intelliSenseMode": "windows-msvc-x64",
            "configurationProvider": "ms-vscode.cmake-tools"
        }
    ],
    "version": 4
}
```

## Troubleshooting

### Metal Not Working on macOS

Make sure you're running on a supported macOS version (10.15+) and that SDL2 is properly initialized with the Metal flag.

### Windows DLL Issues

If you encounter "missing DLL" errors on Windows, make sure the SDL2.dll file is correctly copied to the output directory. This should happen automatically during the build process.

### CMake Configuration Issues

- Make sure you have the correct version of CMake installed
- Ensure all submodules are properly initialized
- Check that your compiler supports C++20

### VS Code Debug Issues

- **Issue**: "Build task failed" when debugging
  - **Solution**: Check that the build directory exists and is properly configured in tasks.json

- **Issue**: "Debug adapter process has terminated unexpectedly"
  - **Solution**: Make sure you have the LLDB extension installed on macOS or the C++ extension on Windows

- **Issue**: Cannot find executable
  - **Solution**: Verify the path in launch.json points to the correct location of your built executable

## License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.

## Contributing

1. Fork the repository
2. Create your feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add some amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request