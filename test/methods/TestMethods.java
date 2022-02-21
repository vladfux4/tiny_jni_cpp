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

class TestMethodsJNI {
    TestMethodsJNI(String nativeLibPath) {
        System.load(nativeLibPath);
    }

    native void runMethodCalls();

    void intMethod(int value) {
        System.out.println("JAVA: intMethod: " + value);
    }

    void intLongMethod(int v0, long v1) {
        System.out.println("JAVA: intLongMethod: " + v0 + " " + v1);
    }

    void intListMethod(ArrayList<Integer> intList) {
        System.out.println("JAVA: intListMethod: " + intList.size());
        for (Integer num : intList) {
          System.out.println("Item: " + num);
        }
    }

    ArrayList<Integer> structListIntListMethod(ArrayList<ExampleStruct> structList) {
        System.out.println("JAVA: structListIntListMethod: " + structList.size());
        for (ExampleStruct item : structList) {
          System.out.println("Item: " + item.intValue + " " + item.longValue);
        }

        ArrayList<Integer> intList = new ArrayList<Integer>();
        intList.add(3);
        intList.add(4);

        return intList;
    }

    String stringMethod(String value) {
        System.out.println("JAVA: stringMethod: " + value);
        return "Hello from JAVA";
    }

    boolean booleanMethod(boolean value) {
        System.out.println("JAVA: booleanMethod: " + value);
        return true;
    }
}

public class TestMethods {
    public static void main(String[] args) {
        TestMethodsJNI obj = new TestMethodsJNI(args[0]);
        obj.runMethodCalls();

        System.out.println("Done");
    }
}
