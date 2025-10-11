# create lib
add_library(GIS_Utils)

target_sources(GIS_Utils
	PRIVATE
		src/pch.cpp
		src/Utils.cpp
		include/Utils.h
)

# add headers
target_include_directories(GIS_Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# link to libs
target_link_libraries(GIS_Utils
	PRIVATE
		GIS_Data
)

# add pch
target_precompile_headers(GIS_Utils PRIVATE src/pch.h)