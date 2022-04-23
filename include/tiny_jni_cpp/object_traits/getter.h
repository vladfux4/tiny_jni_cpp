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

#include "tiny_jni_cpp/byte_buffer.h"

template <typename Delegate, typename Type>
struct TypeDescriptor;

namespace tiny_jni_cpp {

namespace object_traits {
template <typename Type>
struct Getter {
  static jobject Get(JNIEnv* env, jobject obj, const char* name) {
    struct Delegate;

    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(
        jni_class, name, TypeDescriptor<Delegate, Type>::java_type_id);
    return env->GetObjectField(obj, field_id);
  }
};

template <>
struct Getter<std::string> {
  static jstring Get(JNIEnv* env, jobject obj, const char* name) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "Ljava/lang/String;");
    jobject string_obj = env->GetObjectField(obj, field_id);
    return static_cast<jstring>(string_obj);
  }
};

template <>
struct Getter<ByteBuffer> {
  static jobject Get(JNIEnv* env, jobject obj, const char* name) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id =
        env->GetFieldID(jni_class, name, "Ljava/nio/ByteBuffer;");
    jobject object = env->GetObjectField(obj, field_id);
    return object;
  }
};

template <>  /// TODO Add other specializations
struct Getter<int> {
  static int Get(JNIEnv* env, jobject obj, const char* name) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "I");
    return env->GetIntField(obj, field_id);
  }
};

template <>  /// TODO Add other specializations
struct Getter<long> {
  static long Get(JNIEnv* env, jobject obj, const char* name) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "J");
    return env->GetLongField(obj, field_id);
  }
};

template <typename Type>
struct Getter<std::vector<Type>> {
  static jobject Get(JNIEnv* env, jobject obj, const char* name) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id =
        env->GetFieldID(jni_class, name, "Ljava/util/ArrayList;");
    return env->GetObjectField(obj, field_id);
  }
};

}  // namespace object_traits

}  // namespace tiny_jni_cpp
