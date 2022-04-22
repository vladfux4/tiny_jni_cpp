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

#include "tiny_jni_cpp/byte_buffer.h"

namespace tiny_jni_cpp {
namespace container_helpers {
namespace list {

inline jobject BuildArrayList(JNIEnv* env) {
  jclass jni_class = env->FindClass("Ljava/util/ArrayList;");
  jmethodID method_id = env->GetMethodID(jni_class, "<init>", "()V");
  return env->NewObject(jni_class, method_id);
}

inline bool Add(JNIEnv* env, jobject list, jobject item) {
  jclass jni_class = env->GetObjectClass(list);
  jmethodID method_id =
      env->GetMethodID(jni_class, "add", "(Ljava/lang/Object;)Z");
  return env->CallBooleanMethod(list, method_id, item);
}

inline jobjectArray ToArray(JNIEnv* env, jobject list) {
  jclass jni_class = env->GetObjectClass(list);
  jmethodID method_id =
      env->GetMethodID(jni_class, "toArray", "()[Ljava/lang/Object;");
  return static_cast<jobjectArray>(env->CallObjectMethod(list, method_id));
}

}  // namespace list

namespace array {

inline std::size_t Length(JNIEnv* env, jobjectArray array) {
  return env->GetArrayLength(array);
}

inline jobject Get(JNIEnv* env, jobjectArray array, std::size_t index) {
  return env->GetObjectArrayElement(array, index);
}

}  // namespace array

namespace string {

inline std::string Get(JNIEnv* env, jstring obj) {
  const char* cstr = env->GetStringUTFChars(obj, nullptr);
  auto result = std::string(cstr);
  env->ReleaseStringUTFChars(obj, cstr);
  return result;
}

inline jstring Build(JNIEnv* env, const std::string& value) {
  return env->NewStringUTF(value.c_str());
}

}  // namespace string

namespace byte_buffer {

inline ByteBuffer Get(JNIEnv* env, jobject obj) {
  void* data = env->GetDirectBufferAddress(obj);
  const size_t size = env->GetDirectBufferCapacity(obj);
  return {reinterpret_cast<uint8_t*>(data), size};
}

inline jobject Build(JNIEnv* env, const ByteBuffer& value) {
  return env->NewDirectByteBuffer(value.data, value.size);
}

}  // namespace byte_buffer

}  // namespace container_helpers
}  // namespace tiny_jni_cpp
