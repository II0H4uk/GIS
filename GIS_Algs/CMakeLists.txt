# create lib
add_library(GIS_Algs)

target_sources(GIS_Algs
	PRIVATE
		src/SignalMatching.cpp
		src/pch.cpp
		src/AlgStrat.cpp
		src/Reduction.cpp
		include/SignalMatching.h
		include/AlgStrat.h
		include/Reduction.h
)

# add headers
target_include_directories(GIS_Algs
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add pch
target_precompile_headers(GIS_Algs PRIVATE src/pch.h)

# link to other lib
target_link_libraries(GIS_Algs
    PRIVATE
        GIS_Data
)