file(GLOB SOURCES "src/*.cpp")
file(GLOB TESTS "tests/*.cpp")

add_executable(GIS_Tests ${SOURCES} ${TESTS})

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
	${PROJECT_SOURCE_DIR}/GIS_Tests/src
)

#set_target_properties(GIS_Tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/test")
# include(GoogleTest)
# gtest_discover_tests(GIS_Tests)

## Create the custom target before loop.
#add_custom_target(examples)
#
#foreach (FILE ${EXAMPLE_FILES})
#    # Every executable target should have unique name.
#    # E.g. if every example source is given in form '<name>.c'
#    # Then we could use '<name>' as the executable target
#    string(REPLACE ".c" "" TARGET_NAME "${FILE}")
#    # Create an executable
#    add_executable({$TARGET_NAME} EXCLUDE_FROM_ALL ${FILE})
#    # And make 'examples' to depend from that executable
#    add_dependencies(examples ${TARGET_NAME})
#endforeach ()
