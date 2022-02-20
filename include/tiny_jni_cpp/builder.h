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

#include <stdexcept>
#include <string>

#include "tiny_jni_cpp/constructor_delegate_base.h"
#include "tiny_jni_cpp/container_helpers.h"
#include "tiny_jni_cpp/object_traits/setter.h"

template <typename Type>
struct ConstructorDelegate : tiny_jni_cpp::ConstructorDelegateBase<Type> {
  using Base = tiny_jni_cpp::ConstructorDelegateBase<Type>;
  using Base::Base;

  jobject Apply(const Type& /*value*/)  // call default ctr for default case
  {
    return Base::CallConstructor("()V");
  }
};

namespace tiny_jni_cpp {

template <typename Type>
struct Builder;

struct BuilderDelegate {
  template <typename Type>
  static void ApplyField(Type* in, JNIEnv* env, jobject obj, const char* name) {
    auto jni_val = Builder<Type>::Build(env, *in);
    object_traits::Setter<Type>::Set(env, obj, name, jni_val);
  }

  template <typename Type>
  static void ApplyGetter(Type* /*out*/, JNIEnv* /*env*/, jobject /*obj*/,
                          const char* /*name*/)  // Getter Methods are scipped
                                                 // during object construction
  {}
};

template <typename Type>
struct Builder {
  using Descriptor = TypeDescriptor<BuilderDelegate, Type>;

  static jobject Build(JNIEnv* env, const Type& value) {
    ConstructorDelegate<Type> constructor(env);
    jobject obj = constructor.Apply(value);

    Descriptor desc(env, obj);
    Type copy = value;
    desc.Apply(&copy);

    return obj;
  }
};

template <>
struct Builder<int> {
  static jint Build(JNIEnv* /*env*/, int obj) { return obj; }
};

template <>
struct Builder<long> {
  static jlong Build(JNIEnv* /*env*/, long obj) { return obj; }
};

template <>
struct Builder<std::string> {
  static jstring Build(JNIEnv* env, const std::string& obj) {
    return container_helpers::string::Build(env, obj);
  }
};

template <typename Type>
struct Builder<std::vector<Type>> {
  template <typename ValueType>
  static jobject Build(JNIEnv* env, const ValueType& value) {
    jobject list = container_helpers::list::BuildArrayList(env);

    for (const auto& item : value) {
      jobject item_object = Builder<Type>::Build(env, item);
      bool added = container_helpers::list::Add(env, list, item_object);
      if (!added) {
        throw std::runtime_error("");
      }
    }

    return list;
  }
};

}  // namespace tiny_jni_cpp
