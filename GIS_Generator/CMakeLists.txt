# create lib
add_library(GIS_Generator)

target_sources(GIS_Generator
	PRIVATE
		src/Generator.cpp
		src/pch.cpp
		include/Generator.h
)

# add headers
target_include_directories(GIS_Generator
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add pch
target_precompile_headers(GIS_Generator PRIVATE src/pch.h)

# link to other lib
target_link_libraries(GIS_Generator
    PRIVATE
        GIS_Data
)