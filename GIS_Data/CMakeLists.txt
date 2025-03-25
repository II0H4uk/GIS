file(GLOB SOURCES "src/*.cpp")

add_library(GIS_Data SHARED ${SOURCES})

target_include_directories(GIS_Data PUBLIC include ../GIS_Core/include)

target_compile_definitions(GIS_Data PRIVATE GISDATA_EXPORTS)