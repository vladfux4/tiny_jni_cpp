find_package(JNI REQUIRED)

add_library(test_async_native SHARED test_async.cc)
target_include_directories(test_async_native PRIVATE ${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

set(JAVA_SRC ${CMAKE_CURRENT_SOURCE_DIR}/TestAsync.java)
add_custom_target(
    test_async_java ALL
    COMMAND javac ${JAVA_SRC} -d ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${JAVA_SRC} test_async_native)

add_test(NAME Async COMMAND java -cp ${CMAKE_CURRENT_BINARY_DIR} TestAsync ${CMAKE_CURRENT_BINARY_DIR}/libtest_async_native.so)
