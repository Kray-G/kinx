# Switch-Case in Native

## Overview

Switch-Case is supported only with integer label in native function.
The label should be integer but also it can be the expression with the type of integer.

## Examples

### Example 1. Switch-case in native

#### Code

```javascript
var y = 19;
native f(a, x) {
    var b = 0;
    switch (a) {
    case 1:
        b = a;
        break;
    case 5:
        b = a;
        break;
    default:
        b = 100;
        break;
    case 4:
        b = a;
        break;
    case 3:
        b = a;
        break;
    case 8:
        b = 10;
        break;
    case 9:
        b = a;
        break;
    case x:
        b = 1000;
        break;
    case y:
        b = 10000;
        break;
    case y+1:
        b = 100000;
        /* fallthrough */
    case x+3:
        b += 1000000;
        break;
    }
    return b;
}
System.println(f(1, 18));
System.println(f(2, 18));
System.println(f(3, 18));
System.println(f(4, 18));
System.println(f(5, 18));
System.println(f(6, 18));
System.println(f(7, 18));
System.println(f(8, 18));
System.println(f(9, 18));
System.println(f(18, 18));
System.println(f(19, 18));
System.println(f(20, 18));
System.println(f(21, 18));
```

#### Result

```
1
100
3
4
5
100
100
10
9
1000
10000
1100000
1000000
```
