find_package(JNI REQUIRED)

add_library(test_data_types_native SHARED test_data_types.cc)
target_include_directories(test_data_types_native PRIVATE ${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set(JAVA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/TestDataTypes.java)
add_custom_target(
    test_data_types_java ALL
    COMMAND javac ${JAVA_SRC} -d ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${JAVA_SRC} test_data_types_native)

add_test(NAME DataTypes COMMAND java -cp ${CMAKE_CURRENT_BINARY_DIR} TestDataTypes)
set_tests_properties(DataTypes PROPERTIES ENVIRONMENT "JNI_SO_PATH=${CMAKE_CURRENT_BINARY_DIR}/libtest_data_types_native.so")
