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

#include "tiny_jni_cpp/attach_thread_guard.h"
#include "tiny_jni_cpp/container_helpers.h"
#include "tiny_jni_cpp/converter.h"
#include "tiny_jni_cpp/field.h"
#include "tiny_jni_cpp/field_context.h"
#include "tiny_jni_cpp/fundamental_types.h"
#include "tiny_jni_cpp/method.h"
#include "tiny_jni_cpp/method_context.h"
#include "tiny_jni_cpp/object_traits/caller.h"
#include "tiny_jni_cpp/object_traits/getter.h"
#include "tiny_jni_cpp/object_traits/setter.h"
#include "tiny_jni_cpp/type_descriptor_base.h"
