# create lib
add_library(GIS_Data)

target_sources(GIS_Data
	PRIVATE
		src/BipartGraph.cpp
		src/Config.cpp
		src/Element.cpp
		src/Graph.cpp
		src/GraphPair.cpp
		src/KoenigGraph.cpp
		src/pch.cpp

		include/BipartGraph.h
		include/Config.h
		include/Element.h
		include/Graph.h
		include/GraphPair.h
		include/KoenigGraph.h
)

# add headers
target_include_directories(GIS_Data
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add pch
target_precompile_headers(GIS_Data PRIVATE src/pch.h)