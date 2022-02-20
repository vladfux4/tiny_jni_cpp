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

#include <jni.h>

#include <iostream>
#include <thread>

#include "tiny_jni_cpp/tiny_jni_cpp.h"

extern "C" {

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM* vm, void* /*reserved*/) {
  std::cout << "JNI_OnLoad: " << vm << std::endl;
  tiny_jni_cpp::GlobalVM::Initialize(vm);
  return tiny_jni_cpp::GlobalVM::kJniVersion;
}

/*
 * Class:     TestAsyncJNI
 * Method:    runTest
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_TestAsyncJNI_runTest(JNIEnv* env, jobject self) {
  jobject self_ref = env->NewGlobalRef(self);
  std::thread async_call_thread([self_ref]() {
    std::cout << "Start async thread" << std::endl;
    tiny_jni_cpp::AttachThreadGuard guard;
    std::cout << "Async thread is attached" << std::endl;

    tiny_jni_cpp::MethodContext<std::string> stringMethod(
        guard.GetEnv(), self_ref, "stringMethod");
    std::cout << "Result: "
              << stringMethod(std::string("Message from C++ async thread"))
              << std::endl;
    std::cout << "Finish Async thread" << std::endl;
  });

  async_call_thread.join();
  std::cout << "C++ Done" << std::endl;
}
}
