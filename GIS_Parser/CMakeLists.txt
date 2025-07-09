# create lib
add_library(GIS_Parser)

target_sources(GIS_Parser
	PRIVATE
		src/ConfigParser.cpp
		src/SpiceParser.cpp
		src/FileWriter.cpp
		src/CircuitLayout.cpp
		src/pch.cpp
		include/ConfigParser.h
		include/SpiceParser.h
		include/FileWriter.h
		include/CircuitLayout.h
)

# add headers
target_include_directories(GIS_Parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# add pch
target_precompile_headers(GIS_Parser PRIVATE src/pch.h)

# link to other lib
target_link_libraries(GIS_Parser PRIVATE GIS_Data)