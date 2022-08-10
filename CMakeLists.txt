# CMakeList.txt : CMake project for CRP, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.13...3.21)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
endif()

project(
    MoM  # Project name, change this as needed.
    LANGUAGES C CXX
)

# Add source to this project's executable.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")  # Keep all runtime files in one directory.
file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS  # Automatically reconfigure if source files are added/removed.
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# FIXME Works to copy tileset except this is really hacky, setup to copy all png's maybe? and also fix file location?
FILE(COPY data/16x16-sb-ascii.png DESTINATION "${PROJECT_BINARY_DIR}/bin")

# Ensure the C++17 standard is available.
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Enforce UTF-8 encoding on MSVC.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

# Enable warnings recommended for new projects.
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()

find_package(libtcod CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE libtcod::libtcod)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)