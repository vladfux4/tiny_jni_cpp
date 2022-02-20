/*
 * MIT License
 * Copyright (c) 2022 Vladyslav Samodelok
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <jni.h>

#include <string>
#include <vector>

template <typename Delegate, typename Type>
struct TypeDescriptor;

namespace tiny_jni_cpp {
namespace object_traits {

template <typename Type>
struct Caller {
  static jobject call(JNIEnv* env, jobject obj, const char* name) {
    struct Delegate;
    std::string signature = "()" + TypeDescriptor<Delegate, Type>::java_type_id;

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallObjectMethod(obj, method_id);
  }
};

template <>
struct Caller<int> {
  static int call(JNIEnv* env, jobject obj, const char* name) {
    std::string signature = "()I";

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallIntMethod(obj, method_id);
  }
};

template <>
struct Caller<long> {
  static long call(JNIEnv* env, jobject obj, const char* name) {
    std::string signature = "()J";

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallLongMethod(obj, method_id);
  }
};

template <typename Type>
struct Caller<std::vector<Type>> {
  static jobject call(JNIEnv* env, jobject obj, const char* name) {
    std::string signature = "()Ljava/util/ArrayList;";

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallObjectMethod(obj, method_id);
  }
};

}  // namespace object_traits
}  // namespace tiny_jni_cpp
