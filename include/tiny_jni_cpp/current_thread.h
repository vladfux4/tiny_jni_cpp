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

#include "tiny_jni_cpp/global_vm.h"

namespace tiny_jni_cpp {

struct CurrentThread {
  static JNIEnv* Attach() {
    JNIEnv* env = nullptr;
    JavaVM* vm = GlobalVM::Get();

    jint status =
        vm->GetEnv(reinterpret_cast<void**>(&env), GlobalVM::kJniVersion);

    if ((status != JNI_OK) && (status != JNI_EDETACHED)) {
      throw std::runtime_error("vm->GetEnv failed. ErrorCode: " +
                               std::to_string(status));
    }

    if (status == JNI_EDETACHED) {
      status = vm->AttachCurrentThread(reinterpret_cast<void**>(&env), nullptr);
      if (status != JNI_OK) {
        throw std::runtime_error("AttachCurrentThread failed. ErrorCode: " +
                                 std::to_string(status));
      }
    }

    return env;
  }

  static void Detach() {
    JavaVM* vm = GlobalVM::Get();
    jint status = vm->DetachCurrentThread();

    if (status != JNI_OK) {
      throw std::runtime_error("DetachCurrentThread failed. ErrorCode: " +
                               std::to_string(status));
    }
  }
};

}  // namespace tiny_jni_cpp
