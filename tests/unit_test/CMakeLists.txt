add_executable(matrix_unit_test
			   array_test.cpp matrix_test.cpp)

target_link_libraries(matrix_unit_test 
PRIVATE
	GTest::GTest
	GTest::gtest_main
)

target_include_directories(matrix_unit_test PUBLIC ${PROJECT_SOURCE_DIR}/includes)

include(GoogleTest)
gtest_discover_tests(matrix_unit_test)
