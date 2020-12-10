
# Return statement

## Overview

`return` statement is used for returning back from a function.

```javascript
function func() {
    return 10;
}
```

### Expession

`return` statement can have any expression and returning the evaluated value to caller function.
If there is no expression, `null` will be returned Implicitly.

```javascript
function func1() {
    return 10 + funcX();    // if funcX() returns 5, then func1() returns 15.
}
function func2() {
    return;                 // same as `return null`.
}
```

### if-modifier

`return` statement can have `if-modifier`.
See the example below.


```javascript
return 10 if (a < 10);  // return 10 if `a` is less than 10.
return if (b < 10);     // return null if `b` is less than 10.
```

## Examples

### Example 1. Normal case

#### Code

```javascript
function func() {
    return 10;
}
System.println(func());
```

#### Result

```
10
```

### Example 2. Without expression

#### Code

```javascript
function func() {
    return;
}
System.println(func().isUndefined ? "null" : "defined");
```

#### Result

```
null
```

### Example 3. if-modifier (1)

#### Code

```javascript
function func(a) {
    return if (a < 10);
    return a * 20;
}
System.println((a = func( 8)).isUndefined ? "null" : a);
System.println((a = func( 9)).isUndefined ? "null" : a);
System.println((a = func(10)).isUndefined ? "null" : a);
```

#### Result

```
null
null
200
```

### Example 4. if-modifier (2)

#### Code

```javascript
function func(a) {
    return a * 20 if (a < 10);
    return;
}
System.println((a = func( 8)).isUndefined ? "null" : a);
System.println((a = func( 9)).isUndefined ? "null" : a);
System.println((a = func(10)).isUndefined ? "null" : a);
```

#### Result

```
160
180
null
```
