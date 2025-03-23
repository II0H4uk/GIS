file(GLOB SOURCES "src/*.cpp")

add_library(GIS_Parser SHARED ${SOURCES})

target_include_directories(GIS_Parser PUBLIC include ../GIS_Core/include ../GIS_Data/include)

target_compile_definitions(GIS_Parser PRIVATE GISPARSER_EXPORTS)

target_link_libraries(GIS_Parser PUBLIC GIS_Data)