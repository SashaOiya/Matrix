enable_testing()

add_test(NAME MatrixE2E
    COMMAND bash ${CMAKE_CURRENT_SOURCE_DIR}/test.sh $<TARGET_FILE:matrix> ${CMAKE_CURRENT_SOURCE_DIR}/../../tests/e2e_test/data
)
