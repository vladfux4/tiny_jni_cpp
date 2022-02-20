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

#include "tiny_jni_cpp/object_traits/caller.h"

template <typename Delegate, typename Type>
struct TypeDescriptor;

namespace tiny_jni_cpp {

template <typename Type>
struct Builder;

template <typename Type>
struct ConstructorDelegateBase {
  ConstructorDelegateBase(JNIEnv* env) : env_(env) {}

  template <typename... Args>
  jobject CallConstructor(Args... args) {
    struct Delegate;
    using Descriptor = TypeDescriptor<Delegate, Type>;

    jclass jni_class = env_->FindClass(Descriptor::java_type_id);
    std::string signature =
        object_traits::internal::MethodSignature<void>::Make(args...);

    jmethodID method_id =
        env_->GetMethodID(jni_class, "<init>", signature.c_str());
    return env_->NewObject(jni_class, method_id,
                           Builder<Args>::Build(env_, args)...);
  }

 private:
  JNIEnv* env_;
};

}  // namespace tiny_jni_cpp
