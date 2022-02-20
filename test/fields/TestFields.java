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

import java.lang.System;
import java.util.ArrayList;

class ExampleStruct {
  ExampleStruct() {
    intValue = 0;
    longValue = 0;
  }

  ExampleStruct(int v0, long v1) {
    intValue = v0;
    longValue = v1;
  }

  public int intValue;
  public long longValue;
}

class TestFieldsJNI {
    TestFieldsJNI(String nativeLibPath) {
        System.load(nativeLibPath);
    }

    public int intField;
    public ExampleStruct structField;
    public ArrayList<Integer> intListField;
    public String stringField;

    native void runTest();
}

public class TestFields {
    public static void main(String[] args) {
        TestFieldsJNI obj = new TestFieldsJNI(args[0]);
        obj.runTest();

        System.out.println("Done");
    }
}
