# create lib
add_library(GIS_Stats)

target_sources(GIS_Stats
	PRIVATE
		src/Statistics.cpp
		src/pch.cpp
		include/Statistics.h
)

# add headers
target_include_directories(GIS_Stats PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add pch
target_precompile_headers(GIS_Stats PRIVATE src/pch.h)

# link to other lib
target_link_libraries(GIS_Stats
	PRIVATE
		GIS_Parser
)