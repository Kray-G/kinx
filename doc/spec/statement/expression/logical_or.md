# Logical OR Operator

## Overview

Logical Undef operator is a shortcut operator,
and when using `||` and LHS is `false`, the RHS will be evaluated.

```javascript
var b = a || 10;    // initializing 10 when a is false.
```

This can be also used with assignment operator as `||=`.

```javascript
a ||= new A();  // creating an instance only when a is false.
```

## Examples

### Example 1. Simple use

#### Code

```javascript
function test(a) {
    return a || 10;
}

System.println(test(0));
System.println(test(1));
System.println(test(null));
```

#### Result

```
10
1
10
```

### Example 2. With assignment

#### Code

```javascript
var id;
class A() { @id = id++; }

function test(a) {
    a ||= new A();
    return a;
}

var a;
id = 10;
System.println((a = test(a)).id);
System.println((a = test(a)).id);
System.println((a = test(a)).id);
```

#### Result

```
10
10
10
```
