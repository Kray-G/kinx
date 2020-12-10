
# While statement

## Overview

`while` statement is a pre-test loop.
The condition will be evaluated at the head of loop.

```javascript
while (a == 0) {
    // loop while a equals 0.
}
```

### Infinite loop

If you put `true` or non-zero value at the condition, it means infinite loop.
`break` statement is needed to exit an infinite loop.

```javascript
while (true) {
    // infinite loop.
    if (codition) break;
}
```

## Examples

### Example 1. Normal case

#### Code

```javascript
var a = 5;
while (a--) {
    System.println(a);
}
```

#### Result

```
4
3
2
1
0
```

### Example 2. Infinaite loop

#### Code

```javascript
var i = 0;
while (true) {
    if (i > 1000) break;
    ++i;
}
System.println(i);
```

#### Result

```
1001
```
