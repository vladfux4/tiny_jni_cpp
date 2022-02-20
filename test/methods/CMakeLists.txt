find_package(JNI REQUIRED)

add_library(test_methods_native SHARED test_methods.cc)
target_include_directories(test_methods_native PRIVATE ${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(JAVA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/TestMethods.java)
add_custom_target(
    test_methods_java ALL
    COMMAND javac ${JAVA_SRC} -d ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${JAVA_SRC} test_methods_native)

add_test(NAME Methods COMMAND java -cp ${CMAKE_CURRENT_BINARY_DIR} TestMethods ${CMAKE_CURRENT_BINARY_DIR}/libtest_methods_native.so)
