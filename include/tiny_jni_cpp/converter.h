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

#include "container_helpers.h"
#include "tiny_jni_cpp/object_traits/caller.h"
#include "tiny_jni_cpp/object_traits/getter.h"

namespace tiny_jni_cpp {

template <typename Type>
struct Converter;

struct ConverterDelegate {
  template <typename Type>
  static void ApplyField(Type* out, JNIEnv* env, jobject obj,
                         const char* name) {
    auto jni_value = object_traits::Getter<Type>::Get(env, obj, name);
    *out = Converter<Type>::Convert(env, jni_value);
  }

  template <typename Type>
  static void ApplyGetter(Type* out, JNIEnv* env, jobject obj,
                          const char* name) {
    auto jni_value = object_traits::Caller<Type>::call(env, obj, name);
    *out = Converter<Type>::Convert(env, jni_value);
  }
};

template <typename Type>
struct Converter {
  static Type Convert(JNIEnv* env, jobject obj) {
    Type out;
    TypeDescriptor<ConverterDelegate, Type> desc(env, obj);
    desc.Apply(&out);
    return out;
  }
};

template <>
struct Converter<int> {  /// TODO Add other specializations
  using Type = int;
  static Type Convert(JNIEnv* /*env*/, Type obj) { return obj; }
};

template <>
struct Converter<long> {  /// TODO Add other specializations
  using Type = long;
  static Type Convert(JNIEnv* /*env*/, Type obj) { return obj; }
};

template <typename Type>
struct Converter<std::vector<Type>> {
  using ResultType = std::vector<Type>;

  static ResultType Convert(JNIEnv* env, jobject obj) {
    ResultType result;

    auto array = container_helpers::list::ToArray(env, obj);
    std::size_t length = container_helpers::array::Length(env, array);
    for (std::size_t i = 0; i < length; i++) {
      auto item = container_helpers::array::Get(env, array, i);
      result.push_back(Converter<Type>::Convert(env, item));
    }

    return result;
  }
};

template <>
struct Converter<std::string> {
  static std::string Convert(JNIEnv* env, jstring obj) {
    return container_helpers::string::Get(env, obj);
  }
};

}  // namespace tiny_jni_cpp
