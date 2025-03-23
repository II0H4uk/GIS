file(GLOB SOURCES "src/*.cpp")

add_library(GIS_Algs SHARED ${SOURCES})

target_include_directories(GIS_Algs PUBLIC include ../GIS_Core/include ../GIS_Data/include)

target_compile_definitions(GIS_Algs PRIVATE GISALGS_EXPORTS)

target_link_libraries(GIS_Algs PUBLIC GIS_Data)