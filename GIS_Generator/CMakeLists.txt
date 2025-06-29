file(GLOB SOURCES "src/*.cpp")

add_library(GIS_Generator SHARED ${SOURCES})

target_include_directories(GIS_Generator PUBLIC include ../GIS_Core/include)
target_include_directories(GIS_Generator PUBLIC include ../GIS_Data/include)

target_compile_definitions(GIS_Generator PRIVATE GISGENERATOR_EXPORTS)
