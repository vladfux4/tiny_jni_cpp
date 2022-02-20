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

#include <iostream>
#include <string>
#include <vector>

template <typename Delegate, typename Type>
struct TypeDescriptor;

namespace tiny_jni_cpp {

template <typename Type>
struct Builder;

namespace object_traits {
namespace internal {

template <typename Type>
struct Parameter {
  struct Delegate {};
  static constexpr const char* java_type_id =
      TypeDescriptor<Delegate, Type>::java_type_id;
};

template <>
struct Parameter<void> {
  static constexpr const char* java_type_id = "V";
};

template <>
struct Parameter<int> {
  static constexpr const char* java_type_id = "I";
};

template <>
struct Parameter<long> {
  static constexpr const char* java_type_id = "J";
};

template <>
struct Parameter<std::string> {
  static constexpr const char* java_type_id = "Ljava/lang/String;";
};

template <typename Type>
struct Parameter<std::vector<Type>> {
  static constexpr const char* java_type_id = "Ljava/util/ArrayList;";
};

template <typename Type>
struct ReturnType {
  using type = jobject;
};

template <>
struct ReturnType<std::string> {
  using type = jstring;
};

template <typename ReturnType>
struct MethodSignature {
  template <typename... Args>
  static std::string Make(Args... /*args*/) {
    std::string signature =
        "(" + (... + std::string(Parameter<Args>::java_type_id)) + ")" +
        std::string(Parameter<ReturnType>::java_type_id);
    return signature;
  }

  static std::string Make() {
    std::string signature =
        "()" + std::string(Parameter<ReturnType>::java_type_id);
    return signature;
  }
};

}  // namespace internal

template <typename Type>
struct Caller {
  using ReturnType = typename internal::ReturnType<Type>::type;

  template <typename... Args>
  static ReturnType call(JNIEnv* env, jobject obj, const char* name,
                         Args... args) {
    std::string signature = internal::MethodSignature<Type>::Make(args...);

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());

    return static_cast<ReturnType>(env->CallObjectMethod(
        obj, method_id, Builder<Args>::Build(env, args)...));
  }
};

template <>
struct Caller<void> {
  template <typename... Args>
  static void call(JNIEnv* env, jobject obj, const char* name, Args... args) {
    std::string signature = internal::MethodSignature<void>::Make(args...);

    std::cout << "NAME: " << name << std::endl;
    std::cout << "SIGNATURE: " << signature << std::endl;

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());

    std::cout << "METHOD_ID: " << method_id << std::endl;

    env->CallVoidMethod(obj, method_id, Builder<Args>::Build(env, args)...);
  }
};

template <>
struct Caller<int> {
  template <typename... Args>
  static int call(JNIEnv* env, jobject obj, const char* name, Args... args) {
    std::string signature = internal::MethodSignature<int>::Make(args...);

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallIntMethod(obj, method_id,
                              Builder<Args>::Build(env, args)...);
  }
};

template <>
struct Caller<long> {
  template <typename... Args>
  static long call(JNIEnv* env, jobject obj, const char* name, Args... args) {
    std::string signature = internal::MethodSignature<long>::Make(args...);

    jclass jni_class = env->GetObjectClass(obj);
    jmethodID method_id = env->GetMethodID(jni_class, name, signature.c_str());
    return env->CallLongMethod(obj, method_id,
                               Builder<Args>::Build(env, args)...);
  }
};

// template <typename Type>
// struct Caller<std::vector<Type>> {
//   template <typename... Args>
//   static jobject call(JNIEnv* env, jobject obj, const char* name,
//                       Args... args) {
//     std::string signature =
//         internal::MethodSignature<std::vector<Type>>::Make(args...);

//    jclass jni_class = env->GetObjectClass(obj);
//    jmethodID method_id = env->GetMethodID(jni_class, name,
//    signature.c_str()); return env->CallObjectMethod(obj, method_id,
//                                 Builder<Args>::Build(env, args)...);
//  }
//};

}  // namespace object_traits
}  // namespace tiny_jni_cpp
