file(GLOB SOURCES "src/*.cpp")

add_library(GIS_Stats SHARED ${SOURCES})

target_include_directories(GIS_Stats PUBLIC include ../GIS_Core/include)
target_include_directories(GIS_Stats PUBLIC include ../GIS_Parser/include)

target_compile_definitions(GIS_Stats PRIVATE GISSTATS_EXPORTS)
