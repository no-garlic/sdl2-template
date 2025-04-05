cmake_minimum_required(VERSION 3.16)
project(sdl2-template VERSION 0.1.0 LANGUAGES C CXX)

# Set C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Prefer Clang compiler if available
if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    message(STATUS "Using ${CMAKE_CXX_COMPILER_ID} compiler, Clang is recommended")
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add SDL2 as a submodule
add_subdirectory(sdl2 EXCLUDE_FROM_ALL)

# Set include directories
include_directories(include)
include_directories(${SDL2_INCLUDE_DIRS})

# Platform specific settings
if(APPLE)
    # macOS specific flags
    set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15)
    
    # Check for Apple Silicon
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        add_compile_definitions(SDL_METAL_ENABLED=1)
        set(SDL_METAL_ENABLED ON CACHE BOOL "Enable Metal rendering backend" FORCE)
        message(STATUS "Configuring for Apple Silicon with Metal support")
    endif()
elseif(WIN32)
    # Windows specific flags
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# Application source files
file(GLOB_RECURSE APP_SOURCES source/*.cpp)

# Define the executable
add_executable(${PROJECT_NAME} ${APP_SOURCES})

# Link SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)

# Post-build copy of necessary DLL files on Windows
if(WIN32)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL2::SDL2>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# Installation instructions
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
