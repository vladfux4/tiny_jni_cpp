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
struct Setter {
  static void Set(JNIEnv* env, jobject obj, const char* name, jobject value) {
    struct Delegate;

    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(
        jni_class, name, TypeDescriptor<Delegate, Type>::java_type_id);
    env->SetObjectField(obj, field_id, value);
  }
};

template <>
struct Setter<std::string> {
  static void Set(JNIEnv* env, jobject obj, const char* name, jstring value) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "Ljava/lang/String;");
    env->SetObjectField(obj, field_id, value);
  }
};

template <>
struct Setter<ByteBuffer> {
  static void Set(JNIEnv* env, jobject obj, const char* name, jobject value) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "Ljava/nio/ByteBuffer;");
    env->SetObjectField(obj, field_id, value);
  }
};

template <>  /// TODO Add other specializations
struct Setter<int> {
  static void Set(JNIEnv* env, jobject obj, const char* name, jint value) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "I");
    env->SetIntField(obj, field_id, value);
  }
};

template <>  /// TODO Add other specializations
struct Setter<long> {
  static void Set(JNIEnv* env, jobject obj, const char* name, long value) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id = env->GetFieldID(jni_class, name, "J");
    env->SetLongField(obj, field_id, value);
  }
};

template <typename Type>
struct Setter<std::vector<Type>> {
  static void Set(JNIEnv* env, jobject obj, const char* name, jobject value) {
    jclass jni_class = env->GetObjectClass(obj);
    jfieldID field_id =
        env->GetFieldID(jni_class, name, "Ljava/util/ArrayList;");
    env->SetObjectField(obj, field_id, value);
  }
};

}  // namespace object_traits
}  // namespace tiny_jni_cpp
