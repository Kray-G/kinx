# Logical AND Operator

## Overview

Logical AND operator is a shortcut operator,
and when using `&&` and LHS is `true`, the RHS will be evaluated.

```javascript
var b = a && 10;    // initializing 10 when a is true.
```

This can be also used with assignment operator as `&&=`.

```javascript
a &&= func();       // calling func and assign it to the variable of a, only when a is true.
```

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a) {
    return a && 10;
}

System.println(test(0) ?? "null");
System.println(test(1) ?? "null");
System.println(test(null) ?? "null");
```

#### Result

```
0
10
null
```

### Example 2. With assignment

#### Code

```javascript
var id;
class A() { @id = id++; }

function test(a) {
    a &&= new A();
    return a ?? { id: 1 };
}

var a;
id = 10;
System.println((a = test(a)).id);
System.println((a = test(a)).id);
System.println((a = test(a)).id);
```

#### Result

```
1
10
11
```
