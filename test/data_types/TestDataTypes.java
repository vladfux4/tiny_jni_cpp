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

class OtherStruct {
  public String string;
  public ArrayList<ExampleStruct> list;
}


class TestDataTypesJNI {
    TestDataTypesJNI(String nativeLibPath) {
        System.load(nativeLibPath);
    }

    native void testInt(int value);
    native void testLong(long value);
    native void testString(String value);
    native void testStruct(ExampleStruct value);
    native void testIntList(ArrayList<Integer> value);
    native void testOtherStruct(OtherStruct value);
    native void testBoolean(boolean value);

    native int getInt();
    native long getLong();
    native String getString();
    native ExampleStruct getStruct();
    native ArrayList<Integer> getIntList();
    native OtherStruct getOtherStruct();
    native boolean getBoolean();
}

public class TestDataTypes {

    public static void main(String[] args) {
        TestDataTypesJNI obj = new TestDataTypesJNI(args[0]);

        obj.testInt(0xFF);
        obj.testLong(0xABC);
        obj.testString("SOME_STRING");

        ExampleStruct exampleStruct = new ExampleStruct();
        exampleStruct.intValue = 0xAA;
        exampleStruct.longValue = 0xBB;
        obj.testStruct(exampleStruct);

        ArrayList<Integer> intList = new ArrayList<Integer>();
        intList.add(1);
        intList.add(2);
        intList.add(3);
        obj.testIntList(intList);

        OtherStruct otherStruct = new OtherStruct();
        otherStruct.string = "STRING_VALUE";
        otherStruct.list = new ArrayList<ExampleStruct>();
        otherStruct.list.add(new ExampleStruct(1, 2));
        otherStruct.list.add(new ExampleStruct(3, 4));
        obj.testOtherStruct(otherStruct);

        int intValue = obj.getInt();
        System.out.println("getInt: " + intValue);

        long longValue = obj.getLong();
        System.out.println("getLong: " + longValue);

        String stringValue = obj.getString();
        System.out.println("getString: " + stringValue);

        ExampleStruct structValue = obj.getStruct();
        System.out.println("getStruct: " + structValue.intValue + " " + structValue.longValue);

        ArrayList<Integer> intListValue = obj.getIntList();
        System.out.println("getIntList: " + intListValue.size());
        for (Integer num : intListValue) {
          System.out.println("Item: " + num);
        }

        OtherStruct otherStructValue = obj.getOtherStruct();
        System.out.println("otherStructValue.string: " + otherStructValue.string);
        System.out.println("otherStructValue.list: " + otherStructValue.list.size());
        for (ExampleStruct item : otherStructValue.list) {
          System.out.println("Item: " + item.intValue + " " + item.longValue);
        }

        obj.testBoolean(true);
        System.out.println("getBoolean: " + obj.getBoolean());

        System.out.println("Done");
    }
}
