include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)

add_executable(GIS_Tests)

target_sources(GIS_Tests
	PRIVATE
		src/main.cpp
		src/BaseTests.cpp
		src/BruteForceTests.cpp
		src/MaxMatching.cpp
		src/TruncEnumTests.cpp
		src/pch.cpp
)

# link to other lib
target_link_libraries(GIS_Tests
	PRIVATE
		GIS_Algs
		GIS_Data
		GIS_Generator
		GIS_Parser
		GIS_Stats
		gtest_main
)

# add pch
target_precompile_headers(GIS_Tests PRIVATE src/pch.h)

# add tests to CTest
enable_testing()
add_test(NAME AllTests COMMAND GIS_Tests)