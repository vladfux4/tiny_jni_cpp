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

namespace tiny_jni_cpp {

/**
 *  Add next function in your native lib.
 *
 * jint JNI_OnLoad(JavaVM* vm, void* reserved) {
 *   tiny_jni_cpp::GlobalVM::Initialize(vm);
 *   return tiny_jni_cpp::GlobalVM::kJniVersion;
 * }
 */
class GlobalVM {
 public:
  static const jint kJniVersion = JNI_VERSION_1_6;

  GlobalVM() = delete;

  static void Initialize(JavaVM* vm) {
    if (vm_ != nullptr) {
      throw std::runtime_error("GlobalVM double initialization");
    }

    vm_ = vm;
  }

  static JavaVM* Get() {
    if (vm_ == nullptr) {
      throw std::runtime_error("Native lib is not loaded yet");
    }

    return vm_;
  }

 private:
  static inline JavaVM* vm_ = nullptr;
};

}  // namespace tiny_jni_cpp
