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

#include "tiny_jni_cpp/tiny_jni_cpp.h"

namespace example {
struct ExampleStruct {
  int intValue;
  long longValue;
};

}  // namespace example

template <typename Delegate>
struct TypeDescriptor<Delegate, example::ExampleStruct>
    : public tiny_jni_cpp::TypeDescriptorBase<Delegate,
                                              example::ExampleStruct> {
  using Base =
      tiny_jni_cpp::TypeDescriptorBase<Delegate, example::ExampleStruct>;
  using Type = example::ExampleStruct;
  using Base::Base;

  static constexpr const char* java_type_id = "LExampleStruct;";

  void Apply(Type* out) {
    Base::GetField(&out->intValue, "intValue");
    Base::GetField(&out->longValue, "longValue");
  }
};

extern "C" {

using tiny_jni_cpp::Method;

/*
 * Class:     TestMethodsJNI
 * Method:    runMethodCalls
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_TestMethodsJNI_runMethodCalls(JNIEnv* env,
                                                          jobject self) {
  Method<void>::call(env, self, "intMethod", int(1));
  Method<void>::call(env, self, "intLongMethod", int(1), long(2));
  Method<void>::call(env, self, "intListMethod",
                     std::vector<int>({1, 2, 3, 4, 5}));

  auto int_list = Method<std::vector<int>>::call(
      env, self, "structListIntListMethod",
      std::vector<example::ExampleStruct>({{1, 2}, {3, 4}}));
  for (const auto& item : int_list) {
    std::cout << "intList item: " << item << std::endl;
  }

  auto string = Method<std::string>::call(env, self, "stringMethod",
                                          std::string("Hello from C++"));
  std::cout << "Result: " << string << std::endl;
}
}
