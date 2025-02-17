add_executable(matrix_unit_test
			   test.cpp)

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")

set_target_properties(matrix_unit_test PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED ON
	CXX_EXTENSIONS OFF
)

target_compile_definitions(matrix_unit_test PUBLIC
						   -DTEST_DATA_DIR="${TEST_DATA_DIR}")

target_link_libraries(matrix_unit_test PRIVATE
					  GTest::GTest
					  GTest::gtest_main)

target_include_directories(matrix_unit_test PUBLIC
	                       ${PROJECT_SOURCE_DIR}/includes
						   ${PROJECT_SOURCE_DIR}/unit_test)

include(GoogleTest)
gtest_discover_tests(matrix_unit_test)