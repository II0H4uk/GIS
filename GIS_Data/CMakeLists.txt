# create lib
add_library(GIS_Data)

target_sources(GIS_Data
	PRIVATE
		src/Config.cpp
		src/KoenigGraph.cpp
		src/LogicBlock.cpp
		src/pch.cpp

		include/Config.h
		include/KoenigGraph.h
		include/LogicBlock.h
		src/pch.h
		include/Subcircuit.h
)

# add headers
target_include_directories(GIS_Data
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
)

# add pch
target_precompile_headers(GIS_Data PRIVATE src/pch.h)