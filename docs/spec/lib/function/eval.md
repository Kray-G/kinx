# eval

## Overview

### function `eval`


#### Use `eval` for String


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
