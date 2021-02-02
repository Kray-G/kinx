# Exceptions

## Overview

Exception system is a notification mechanism of an error, and generally this occurs by `throw` statement.
A library will raise some exceptions on error, and you can catch it by `try-catch` statement.
And also you can define your own exception as you like by `System.defineException()`.

See below for more details.

* [try-catch-finally](../../statement/try_catch_finally.md)
* [throw](../../statement/throw.md)
* [defineException](../function/define_exception.md)

## Structure of Exception Object

Basically an exception object has following two methods.

|       Method        |                      Meaning                      |
| ------------------- | ------------------------------------------------- |
| `type()`            | The name of the exception.                        |
| `what()`            | The message of the exception.                     |
| `printStackTrace()` | Outputs a stack trace with function call history. |

## Examples

### Example 1. Handling Exception

#### Code

```javascript
YourOwnExceptionClass = System.defineException('YourOwnException');
YourOwnException = YourOwnExceptionClass.create;

class TheClass {
    private initialize() {
        throw YourOwnException("Error!");
    }
}

function test() {
    var x = new TheClass();
    return x;
}

try {
    test();
} catch (e) {
    System.println("Exception Type   : ", e.type());
    System.println("Exception Message: ", e.what());
    e.printStackTrace();
}
```

#### Result

```
Exception Type   : YourOwnException
Exception Message: Error!
Stack Trace Information:
        at function TheClass#initialize(test.kx:6)
        at function TheClass(test.kx:4)
        at function test(test.kx:11)
        at <main-block>(test.kx:16)
```
