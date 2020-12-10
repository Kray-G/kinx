
# Throw statement

## Overview

`throw` statement is used to throw exception.

```javascript
throw RuntimeException("Error Message");
```

### Expession

`throw` statement can have any expression but generally it should be an exception object.
In general, RuntimeException will be useful for any runtime errors.
As for exception objects, see [try-catch-finally](try_catch_finally.md) for details.

### In Catch Clause

Only when there is `throw` in catch clause, no expression do not have to be written
because `throw` statement can rethrow a caught exception.

```javascript
try {
    throw RuntimeException("Some error occurred");
} catch (e) {
    throw;  // e will be re-thrown.
} finally {
    /* ... */;
}
```

### if-modifier

`throw` statement can have `if-modifier`.
See the example below.


```javascript
throw RuntimeException("Some error occurred") if (a < 10);   // throw an exception if `a` is less than 10.
```

## Examples

### Example 1. Normal case with if-modifier

#### Code

```javascript
function test(a) {
    throw RuntimeException("Some error occurred") if (a < 10);
    System.println("No throw exception because a is %{a} which means %{a} >= 10");
}
try {
    test(11);
    test(10);
    test(9);
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
}
```

#### Result

```
No throw exception because a is 11 which means 11 >= 10
No throw exception because a is 10 which means 10 >= 10
RuntimeException: Some error occurred
```

### Example 2. Rethrow not in catch

#### Code

```javascript
try {
    throw;  // what is thrown?
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    throw;
} finally {
    System.println("Finally");
}
```

#### Result

```
Error: Can not use throw without expression outside catch clause near the test.kx:2
```

### Example 3. Rethrow in catch

#### Code

```javascript
try {
    throw RuntimeException("Some error occurred");
} catch (e) {
    System.println("%{e.type()}: %{e.what()}");
    throw;  // e will be re-thrown.
} finally {
    System.println("Finally");
}
```

#### Result

```
RuntimeException: Some error occurred
Finally
Uncaught exception: No one catch the exception.
RuntimeException: Some error occurred
Stack Trace Information:
        at <main-block>(test.kx:2)
```
