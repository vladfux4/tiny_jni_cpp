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
#include "tiny_jni_cpp/constructor_delegate_base.h"
#include "tiny_jni_cpp/converter.h"
#include "tiny_jni_cpp/type_descriptor_base.h"

namespace tiny_jni_cpp {
namespace fundamental_types {

template <typename Type>
struct FundamentalType {
  FundamentalType() = default;
  FundamentalType(Type value) : value(value) {}

  Type value;

  operator Type() const { return value; }
};

using Integer = FundamentalType<int>;

}  // namespace fundamental_types

template <>
struct Converter<std::vector<int>>
    : public Converter<std::vector<fundamental_types::Integer>> {};

template <>
struct Builder<std::vector<int>>
    : public Builder<std::vector<fundamental_types::Integer>> {};

}  // namespace tiny_jni_cpp

template <>
struct ConstructorDelegate<tiny_jni_cpp::fundamental_types::Integer>
    : tiny_jni_cpp::ConstructorDelegateBase<
          tiny_jni_cpp::fundamental_types::Integer> {
  using Type = tiny_jni_cpp::fundamental_types::Integer;
  using Base = ConstructorDelegateBase<Type>;
  using Base::Base;

  jobject Apply(const Type& value)  // call default ctr for default case
  {
    return Base::CallConstructor("(I)V", value.value);
  }
};

template <typename Delegate>
struct TypeDescriptor<Delegate, tiny_jni_cpp::fundamental_types::Integer>
    : public tiny_jni_cpp::TypeDescriptorBase<
          Delegate, tiny_jni_cpp::fundamental_types::Integer> {
  using Base = tiny_jni_cpp::TypeDescriptorBase<
      Delegate, tiny_jni_cpp::fundamental_types::Integer>;
  using Type = tiny_jni_cpp::fundamental_types::Integer;
  using Base::Base;

  static constexpr const char* java_type_id = "Ljava/lang/Integer;";

  void Apply(Type* out) { Base::CallMethod(&out->value, "intValue"); }
};
