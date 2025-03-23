cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -g")

project(GIS)

file(GLOB SOURCE_EXE "GIS_Core/src/*.cpp")
add_executable(GIS ${SOURCE_EXE})

file(COPY config.ini DESTINATION ${CMAKE_BINARY_DIR})
file(COPY Graph_Data DESTINATION ${CMAKE_BINARY_DIR})

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

target_include_directories(GIS PRIVATE
    GIS_Algs/include
    GIS_Core/include
    GIS_Data/include
    GIS_Generator/include
    GIS_Parser/include
    GIS_Stats/include
    GIS_Tests/include
)

add_subdirectory(GIS_Algs)
add_subdirectory(GIS_Data)
add_subdirectory(GIS_Generator)
add_subdirectory(GIS_Parser)
add_subdirectory(GIS_Stats)
add_subdirectory(GIS_Tests)

target_link_libraries(GIS PRIVATE GIS_Algs)
target_link_libraries(GIS PRIVATE GIS_Data)
target_link_libraries(GIS PRIVATE GIS_Generator)
target_link_libraries(GIS PRIVATE GIS_Parser)
target_link_libraries(GIS PRIVATE GIS_Stats)

add_custom_command(TARGET GIS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GIS_Algs>
        $<TARGET_FILE_DIR:GIS>
)

add_custom_command(TARGET GIS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GIS_Data>
        $<TARGET_FILE_DIR:GIS>
)

add_custom_command(TARGET GIS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GIS_Generator>
        $<TARGET_FILE_DIR:GIS>
)

add_custom_command(TARGET GIS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GIS_Parser>
        $<TARGET_FILE_DIR:GIS>
)

add_custom_command(TARGET GIS POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:GIS_Stats>
        $<TARGET_FILE_DIR:GIS>
)