# create main executable.
add_executable(GIS_Core)

target_sources(GIS_Core
	PRIVATE
		src/main.cpp
		src/Benchmark.cpp
		src/ValidateMatch.cpp
		src/pch.cpp
		include/Benchmark.h
		include/ValidateMatch.h
)

# add headers
target_include_directories(GIS_Core
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# link to libs
target_link_libraries(GIS_Core
	PRIVATE
		GIS_Algs
		GIS_Data
		GIS_Generator
		GIS_Parser
		GIS_Stats
)

# add pch
target_precompile_headers(GIS_Core
	PRIVATE
		src/pch.h
)