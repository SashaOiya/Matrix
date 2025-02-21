add_executable(matrix_e2e_test
			   test.cpp)

set(TEST_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../")

target_compile_definitions(matrix_e2e_test PUBLIC
						   -DTEST_DATA_DIR="${TEST_DATA_DIR}")

target_link_libraries(matrix_e2e_test PUBLIC
					  GTest::GTest
					  GTest::gtest_main)

target_include_directories(matrix_e2e_test PUBLIC
	                       ${PROJECT_SOURCE_DIR}/includes
						   ${PROJECT_SOURCE_DIR}/e2e_test)

include(GoogleTest)
gtest_discover_tests(matrix_e2e_test)