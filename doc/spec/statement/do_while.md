
# Do-While statement

## Overview

`do-while` statement is a post-test loop.
The condition will be evaluated at the tail of loop.
This loop will be performed 1 time at least.

```javascript
do {
    // loop while a equals 0.
} while (a == 0);
```

### Infinite loop

If you put `true` or non-zero value at the condition, it means infinite loop.
`break` statement is needed to exit an infinite loop.

```javascript
do {
    // infinite loop.
    if (codition) break;
} while (true);
```

This is exactly the same as `while`, therefore you had better use `while` for readability.

## Examples

### Example 1. Normal case

#### Code

```javascript
var a = 5;
do {
    System.println(a);
} while (a--);
```

#### Result

```
5
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
do {
    if (i > 1000) break;
    ++i;
} while (true);
System.println(i);
```

#### Result

```
1001
```
