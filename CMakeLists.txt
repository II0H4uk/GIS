# Set CMake minimum required version.
cmake_minimum_required(VERSION 3.16)

# Set project name.
set(PROJECT_NAME GIS)
project(${PROJECT_NAME})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GIS_Core)
configure_file(${CMAKE_SOURCE_DIR}/config.ini ${CMAKE_BINARY_DIR}/config.ini COPYONLY)

# Set standard for C++.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    message(STATUS "Building for Windows...")
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Auto-export symbols in DLLs
elseif(UNIX AND NOT APPLE)
    message(STATUS "Building for Linux...")
endif()

# Add project's subdirectories.
add_subdirectory(GIS_Data)
add_subdirectory(GIS_Algs)
add_subdirectory(GIS_Generator)
add_subdirectory(GIS_Parser)
add_subdirectory(GIS_Stats)
add_subdirectory(GIS_Core)

# Add subdirectory responsible for testing.
add_subdirectory(GIS_Tests)