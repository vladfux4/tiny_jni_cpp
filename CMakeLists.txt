cmake_minimum_required(VERSION 3.5)

project(tiny_jni_cpp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(JNI REQUIRED)

enable_testing()
add_subdirectory(test)
