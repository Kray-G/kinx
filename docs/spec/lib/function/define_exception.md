# defineException

## Overview

You can define your own exception by `System.defineException()` as below.

```javascript
YourOwnExceptionClass = System.defineException('YourOwnException');
YourOwnException = YourOwnExceptionClass.create;
```

If you want to make your own library, it will be useful for your error notification.

## Examples

### Example 1. Normal case

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

test();
```

#### Result

```
Uncaught exception: No one catch the exception.
YourOwnException: Error!
Stack Trace Information:
        at function TheClass#initialize(test.kx:6)
        at function TheClass(test.kx:4)
        at function test(test.kx:11)
        at <main-block>(test.kx:15)
```
