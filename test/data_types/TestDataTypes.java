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
import java.nio.ByteBuffer;

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

class Image {
  public ByteBuffer data;
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
    native void testStringList(ArrayList<String> value);
    native void testByteBuffer(Image image);

    native int getInt();
    native long getLong();
    native String getString();
    native ExampleStruct getStruct();
    native ArrayList<Integer> getIntList();
    native OtherStruct getOtherStruct();
    native boolean getBoolean();
    native ArrayList<String> getStringList();
    native ByteBuffer getByteBuffer();
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

        ByteBuffer buffer = ByteBuffer.allocateDirect(4);
        buffer.put((byte)0xAA);
        buffer.put((byte)0xBB);
        buffer.put((byte)0xCC);
        buffer.put((byte)0xDD);

        Image image = new Image();
        image.data = buffer;

        obj.testByteBuffer(image);

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

        ArrayList<String> stringList = new ArrayList<String>();
        stringList.add("Hello");
        stringList.add("from");
        stringList.add("Java");
        obj.testStringList(stringList);

        ArrayList<String> stringListValue = obj.getStringList();
        System.out.println("getStringList: " + stringListValue.size());
        for (String item : stringListValue) {
          System.out.println("Item: " + item);
        }

        ByteBuffer byteBuffer = obj.getByteBuffer();
        try{
          byte[] arr = new byte[byteBuffer.remaining()];
          byteBuffer.get(arr);
          String byteBufferStr = new String(arr, "ASCII");
          System.out.println("getByteBuffer: " + byteBufferStr);
        } catch (Exception exception){
          System.out.println(exception);
          exception.printStackTrace();
        }


        System.out.println("Done");
    }
}
