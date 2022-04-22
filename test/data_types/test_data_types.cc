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
#include <string.h>

#include <iostream>

#include "tiny_jni_cpp/tiny_jni_cpp.h"

namespace example {
struct ExampleStruct {
  int intValue;
  long longValue;
};

struct OtherStruct {
  std::string string;
  std::vector<ExampleStruct> list;
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

template <typename Delegate>
struct TypeDescriptor<Delegate, example::OtherStruct>
    : public tiny_jni_cpp::TypeDescriptorBase<Delegate, example::OtherStruct> {
  using Base = tiny_jni_cpp::TypeDescriptorBase<Delegate, example::OtherStruct>;
  using Type = example::OtherStruct;
  using Base::Base;

  static constexpr const char* java_type_id = "LOtherStruct;";

  void Apply(Type* out) {
    Base::GetField(&out->string, "string");
    Base::GetField(&out->list, "list");
  }
};

using tiny_jni_cpp::Builder;
using tiny_jni_cpp::Converter;

extern "C" {

/*
 * Class:     TestDataTypesJNI
 * Method:    testInt
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testInt(JNIEnv* env,
                                                     jobject /*self*/,
                                                     jint value) {
  std::cout << "Java_TestDataTypesJNI_testInt" << std::endl;

  auto result = Converter<int>::Convert(env, value);
  std::cout << "Result: " << result << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testLong
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testLong(JNIEnv* env,
                                                      jobject /*self*/,
                                                      jlong value) {
  std::cout << "Java_TestDataTypesJNI_testLong" << std::endl;

  auto result = Converter<long>::Convert(env, value);
  std::cout << "Result: " << result << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testString
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testString(JNIEnv* env,
                                                        jobject /*self*/,
                                                        jstring value) {
  std::cout << "Java_TestDataTypesJNI_testString" << std::endl;

  auto result = Converter<std::string>::Convert(env, value);
  std::cout << "Result: " << result << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testStruct
 * Signature: (LExampleStruct;)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testStruct(JNIEnv* env,
                                                        jobject, /*self*/
                                                        jobject value) {
  std::cout << "Java_TestDataTypesJNI_testString" << std::endl;

  auto result = Converter<example::ExampleStruct>::Convert(env, value);
  std::cout << "Result: " << result.intValue << " " << result.longValue
            << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testIntList
 * Signature: (Ljava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testIntList(JNIEnv* env,
                                                         jobject /*self*/,
                                                         jobject value) {
  std::cout << "Java_TestDataTypesJNI_testIntList" << std::endl;

  auto result = Converter<std::vector<int>>::Convert(env, value);
  for (const auto& item : result) {
    std::cout << "intList item: " << item << std::endl;
  }

  std::cout << "Done" << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testOtherStruct
 * Signature: (LOtherStruct;)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testOtherStruct(JNIEnv* env,
                                                             jobject /*self*/,
                                                             jobject value) {
  std::cout << "Java_TestDataTypesJNI_testOtherStruct" << std::endl;

  auto result = Converter<example::OtherStruct>::Convert(env, value);
  std::cout << "In list string : " << result.string << std::endl;
  for (const auto& item : result.list) {
    std::cout << "In list struct item: " << item.intValue << " "
              << item.longValue << std::endl;
  }

  std::cout << "Done" << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getInt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_TestDataTypesJNI_getInt(JNIEnv* env,
                                                    jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getInt" << std::endl;
  return Builder<int>::Build(env, 0xFF);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getLong
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_TestDataTypesJNI_getLong(JNIEnv* env,
                                                      jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getLong" << std::endl;
  return Builder<long>::Build(env, 0xFFFF);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getString
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_TestDataTypesJNI_getString(JNIEnv* env,
                                                          jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getString" << std::endl;
  return Builder<std::string>::Build(env, "SOME_STRING");
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getStruct
 * Signature: ()LExampleStruct;
 */
JNIEXPORT jobject JNICALL Java_TestDataTypesJNI_getStruct(JNIEnv* env,
                                                          jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getStruct" << std::endl;

  example::ExampleStruct value;
  value.intValue = 0xAA;
  value.longValue = 0xBB;

  return Builder<example::ExampleStruct>::Build(env, value);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getIntList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL Java_TestDataTypesJNI_getIntList(JNIEnv* env,
                                                           jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getIntList" << std::endl;

  using ValueType = std::vector<int>;

  ValueType ints;
  ints.push_back(1);
  ints.push_back(2);
  ints.push_back(3);
  ints.push_back(4);

  return Builder<ValueType>::Build(env, ints);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getOtherStruct
 * Signature: ()LOtherStruct;
 */
JNIEXPORT jobject JNICALL
Java_TestDataTypesJNI_getOtherStruct(JNIEnv* env, jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getOtherStruct" << std::endl;

  example::OtherStruct otherStruct;
  otherStruct.string = "STRING_VALUE_FROM_CPP";
  otherStruct.list.push_back({0xAA, 0xBB});
  otherStruct.list.push_back({0xCC, 0xDD});

  return Builder<example::OtherStruct>::Build(env, otherStruct);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testBoolean
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testBoolean(JNIEnv* env,
                                                         jobject /*self*/,
                                                         jboolean value) {
  std::cout << "Java_TestDataTypesJNI_testBoolean "
            << Converter<bool>::Convert(env, value) << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getBoolean
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_TestDataTypesJNI_getBoolean(JNIEnv* env,
                                                            jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getBoolean" << std::endl;
  return Builder<bool>::Build(env, true);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testStringList
 * Signature: (Ljava/util/ArrayList;)V
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testStringList(JNIEnv* env,
                                                            jobject self,
                                                            jobject obj) {
  std::cout << "Java_TestDataTypesJNI_testStringList " << std::endl;
  auto value = Converter<std::vector<std::string>>::Convert(env, obj);
  for (const auto& item : value) {
    std::cout << "stringList item: " << item << std::endl;
  }
}

/*
 * Class:     TestDataTypesJNI
 * Method:    testByteBuffer
 */
JNIEXPORT void JNICALL Java_TestDataTypesJNI_testByteBuffer(JNIEnv* env,
                                                            jobject self,
                                                            jobject obj) {
  std::cout << "Java_TestDataTypesJNI_testByteBuffer " << std::endl;

  auto result = Converter<tiny_jni_cpp::ByteBuffer>::Convert(env, obj);
  std::cout << "Result: " << result.data << " " << result.size << std::endl;

  for (int i = 0; i < result.size; i++) {
    std::cout << static_cast<int>(result.data[i]) << " ";
  }
  std::cout << std::endl;
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getStringList
 * Signature: ()Ljava/util/ArrayList;
 */
JNIEXPORT jobject JNICALL
Java_TestDataTypesJNI_getStringList(JNIEnv* env, jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getStringList" << std::endl;

  std::vector<std::string> value = {"Hello", "from", "C++"};
  return Builder<std::vector<std::string>>::Build(env, value);
}

/*
 * Class:     TestDataTypesJNI
 * Method:    getByteBuffer
 */
JNIEXPORT jobject JNICALL
Java_TestDataTypesJNI_getByteBuffer(JNIEnv* env, jobject /*self*/) {
  std::cout << "Java_TestDataTypesJNI_getStringList" << std::endl;

  char* data = new char[8];
  strcpy(data, "AABBCCD");

  tiny_jni_cpp::ByteBuffer value = {reinterpret_cast<uint8_t*>(data), 8};

  // free buffer from Java
  return Builder<tiny_jni_cpp::ByteBuffer>::Build(env, value);
}
}
