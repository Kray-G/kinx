
# Try-Catch-Finally statement

## Overview

`try-catch-finally` statement is for exception mechanism.
Here is the basic format of `try-catch-finally` statement.

```javascript
try {
    // try clause
} catch (e) {
    // catch clause
} finally {
    // finally clause
}
```

Either `catch` or `finally` can be omitted.
If `catch` is omitted, rethrow a same exception after doing finally clause.

### Exception Type and Message

An exception type can be got via `type()` method,
and an exception message can be also got via `what()` method.
For example, use it as below.

```javascript
try {
    throw RuntimeException("error");
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
}
```

### Stack Trace

You can print a stack trace as below.

```javascript
try {
    throw RuntimeException("error");
} catch (e) {
    e.printStackTrace();
}
```

### Distinguish Exceptions

You can use an `instanceOf` method to distinguish what kind of exception has been occurred.
For example, when `RuntimeException` were thrown, the exception must be an instance of `RuntimeExceptionClass`.
Kinx will always provide excetions like `SomeException` which is an instance of `SomeExceptionClass` by standard.

```javascript
try {
    throw RuntimeException("error");
} catch (e) {
    if (e.instanceOf(RuntimeExceptionClass)) {
        // do something.
    }
}
```

### Define Own Exception

Here is a template to define your own exception.

```javascript
var YourExceptionClass = System.defineException("YourException");
var YourException = YourExceptionClass.create;
```

`YourExceptionClass` is needed for `instanceOf` for an exception object.
`YourException` is used by `throw` statement.

```javascript
try {
    throw YourException("error");
} catch (e) {
    if (e.instanceOf(YourExceptionClass)) {
        // do something.
    }
}
```

## Examples

### Example 1. Normal catch

#### Code

```javascript
try {
    throw RuntimeException("error");
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    e.printStackTrace();
}
```

#### Result

```
RuntimeException: error
Stack Trace Information:
        at <main-block>(test.kx:2)
```

### Example 2. Finally (1)

#### Code

```javascript
try {
    throw RuntimeException("error");
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    e.printStackTrace();
} finally {
    System.println("finally 1");
}
```

#### Result

```
RuntimeException: error
Stack Trace Information:
        at <main-block>(test.kx:2)
finally 1
```

### Example 2. Finally (2)

#### Code

```javascript
try {
    System.println("No exceptions");
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    e.printStackTrace();
} finally {
    System.println("finally 1");
}
```

#### Result

```
No exceptions
finally 1
```

### Example 3. Finally (3)

`finally` should not modify a value when returning a variable.
Even when the value is changed by `finally`, there is no effect for the returning value.

#### Code

```javascript
function test1() {
    var val = 1;
    try {
        return val;
    }
    finally {
        val = 2;
    }
}

var s_val;
function test2() {
    s_val = 1;
    try {
        return s_val;
    }
    finally {
        s_val = 2;
        System.print("(s_val = " + s_val + ") = ");
    }
};

System.println("Test1() = " + test1());
System.print("Test2() = ");
System.println(test2());
System.println("s_val = " + s_val);
```

#### Result

```
Test1() = 1
Test2() = (s_val = 2) = 1
s_val = 2
```

### Example 4. Define own exception

#### Code

```javascript
var YourExceptionClass = System.defineException("YourException");
var YourException = YourExceptionClass.create;

try {
    throw YourException("This is a 'YourException' instance.");
} catch (e) {
    if (e.instanceOf(YourExceptionClass)) {
        System.println(e.what());
    } else {
        System.println("Not a 'YourException' instance.");
    }
}
```

#### Result

```
This is a 'YourException' instance.
```

### Example 5. Complex example

#### Code

```javascript
var f =
"function func1() {\n"
"    try {\n"
"        try {\n"
"            System.println('Nothing is thrown, good.');\n"
"        } finally {\n"
"            System.println('finally: func1-1');\n"
"        }\n"
"        System.println('Throw exception');\n"
"        throw RuntimeException('Oh, it\\'s a careless mistake!');\n"
"    } finally {\n"
"        System.println('finally: func1-2');\n"
"    }\n"
"}\n"
"func1();";

# Catches the exception from func1, but rethrow it.
function func2() {
    try {
        try {
            f.eval();
        } finally {
            System.println('finally: func2-1');
        }
    } catch (e) {
        System.println('catch: func2');
        throw;
    } finally {
        System.println('finally: func2-2');
    }
}

# No one catch the exception, but finally clause will be correctly working.
function func3() {
    try {
        try {
            func2();
        } finally {
            System.println('finally: func3-1');
        }
    } finally {
        System.println('finally: func3-2');
    }
}

# Starts the test.
try {
    func3();
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    e.printStackTrace();
} finally {
    System.println('finally: main-block');
}
System.println("end-of-program.");
```

#### Result

```
Nothing is thrown, good.
finally: func1-1
Throw exception
finally: func1-2
finally: func2-1
catch: func2
finally: func2-2
finally: func3-1
finally: func3-2
RuntimeException: Oh, it's a careless mistake!
Stack Trace Information:
        at function func1(<eval>:9)
        at <eval-block>(<eval>:14)
        at function func2(test.kx:21)
        at function func3(test.kx:37)
        at <main-block>(test.kx:48)
finally: main-block
end-of-program.
```
