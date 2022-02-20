find_package(JNI REQUIRED)

add_library(test_fields_native SHARED test_fields.cc)
target_include_directories(test_fields_native PRIVATE ${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(JAVA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/TestFields.java)
add_custom_target(
    test_fields_java ALL
    COMMAND javac ${JAVA_SRC} -d ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${JAVA_SRC} test_fields_native)

add_test(NAME Methods COMMAND java -cp ${CMAKE_CURRENT_BINARY_DIR} TestFields ${CMAKE_CURRENT_BINARY_DIR}/libtest_fields_native.so)
