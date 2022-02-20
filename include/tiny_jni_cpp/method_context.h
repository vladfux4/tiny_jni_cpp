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

#include "tiny_jni_cpp/method.h"

namespace tiny_jni_cpp {

template <typename ReturnType>
struct MethodContextBase {
  MethodContextBase() = delete;

  MethodContextBase(JNIEnv* env, jobject self, const std::string& name)
      : env_(env), self_(self), name_(name) {}

 protected:
  JNIEnv* env_;
  jobject self_;
  std::string name_;
};

template <typename ReturnType>
struct MethodContext : MethodContextBase<ReturnType> {
  using MethodContextBase<ReturnType>::MethodContextBase;

  template <typename... Args>
  auto operator()(Args... args) {
    return Method<ReturnType>::call(this->env_, this->self_,
                                    this->name_.c_str(), args...);
  }
};

template <>
struct MethodContext<void> : MethodContextBase<void> {
  using MethodContextBase<void>::MethodContextBase;

  template <typename... Args>
  void operator()(Args... args) {
    Method<void>::call(this->env_, this->self_, this->name_.c_str(), args...);
  }
};

}  // namespace tiny_jni_cpp
