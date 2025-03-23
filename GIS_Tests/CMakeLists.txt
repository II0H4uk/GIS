file(GLOB SOURCES "src/*.cpp")

add_executable(GIS_Tests ${SOURCES})

target_link_libraries(GIS_Tests PRIVATE
	gtest
	gtest_main
	GIS_Algs
	GIS_Data
	GIS_Generator
	GIS_Parser
	GIS_Stats
)

target_include_directories(GIS_Tests PRIVATE
	${PROJECT_SOURCE_DIR}/GIS_Algs/include
	${PROJECT_SOURCE_DIR}/GIS_Data/include
	${PROJECT_SOURCE_DIR}/GIS_Generator/include
	${PROJECT_SOURCE_DIR}/GIS_Parser/include
	${PROJECT_SOURCE_DIR}/GIS_Stats/include
	${PROJECT_SOURCE_DIR}/GIS_Tests/include
)

# include(GoogleTest)
# gtest_discover_tests(GIS_Tests)