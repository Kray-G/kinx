# eval function

## Overview

`eval` is used to execute the code on the fly.
The string has an `eval` method and directly to call it as below.

```javascript
"System.println(100);".eval();
```

The eval's arguments are assigned to `$$` like command line arguments as an array.

```javascript
"System.println($$.sum());".eval(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);    // => 55
```

## Examples

### Example 1. Normal case

#### Code

```javascript
var code = 'System.println("hello, world");';
code.eval();
```

#### Result

```
hello, world
```

### Example 2. Multiple lines

#### Code

```javascript
var code = %{
    using DateTime;
    var dt = new DateTime("2020/12/24");
    System.println(dt.toString());
};
code.eval();
```

#### Result

```
2020/12/24 00:00:00
```

### Example 3. Exception in eval

#### Code

```javascript
var code = %{
    function evalFunction() {
        try {
            throw RuntimeException("Thrown from eval");
        } catch (e) {
            System.println("The message in eval");
            throw;
        }
    }
    evalFunction();
};
function mainFunction(code) {
    code.eval();
}

try {
    mainFunction(code);
} catch (e) {
    System.println(e.type(), ": ", e.what());
    e.printStackTrace();
}
```

#### Result

```
The message in eval
RuntimeException: Thrown from eval
Stack Trace Information:
        at function evalFunction(<eval>:4)
        at <eval-block>(<eval>:10)
        at function mainFunction(test.kx:13)
        at <main-block>(test.kx:17)
```

### Example 4. Arguments in eval

#### Code

```javascript
"System.println($$.sum());".eval(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);    // => 55
```

#### Result

```
55
```
