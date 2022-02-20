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

#include "tiny_jni_cpp/builder.h"
#include "tiny_jni_cpp/converter.h"
#include "tiny_jni_cpp/object_traits/getter.h"
#include "tiny_jni_cpp/object_traits/setter.h"

namespace tiny_jni_cpp {

template <typename Type>
struct Field {
  static void Set(JNIEnv* env, jobject obj, const char* name,
                  const Type& value) {
    auto jni_value = Builder<Type>::Build(env, value);
    object_traits::Setter<Type>::Set(env, obj, name, jni_value);
  }

  static auto Get(JNIEnv* env, jobject obj, const char* name) {
    auto jni_value = object_traits::Getter<Type>::Get(env, obj, name);
    return Converter<Type>::Convert(env, jni_value);
  }
};

}  // namespace tiny_jni_cpp
