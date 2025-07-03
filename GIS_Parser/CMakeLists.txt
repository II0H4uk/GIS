# create lib
add_library(GIS_Parser)

target_sources(GIS_Parser
	PRIVATE
		src/ConfigParser.cpp
		src/FileWriter.cpp
		src/GraphParser.cpp
		src/HyperGraphToGraph.cpp
		src/SpiceParser.cpp
		src/Utils.cxx
		src/pch.cpp
		include/ConfigParser.h
		include/FileWriter.h
		include/GraphParser.h
		include/HyperGraphToGraph.h
		include/SpiceParser.h
		include/Utils.hxx
)

# add headers
target_include_directories(GIS_Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add pch
target_precompile_headers(GIS_Parser PRIVATE src/pch.h)

# link to other lib
target_link_libraries(GIS_Parser PRIVATE GIS_Data)