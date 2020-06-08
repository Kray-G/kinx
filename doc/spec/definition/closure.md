# Closure

## Overview

Closure is a function object which has a lexical scope.

## Examples

### Example 1. Closure example

#### Code

```javascript
function newCounter() {
    var i = 0;          // a lexical variable.

    return function() { // an anonymous function.
        ++i;            // a reference to a lexical variable.
        return i;
    };
}

var c1 = newCounter();
System.println(c1()); // 1
System.println(c1()); // 2
System.println(c1()); // 3
System.println(c1()); // 4
System.println(c1()); // 5
```

#### Result

```
1
2
3
4
5
```
