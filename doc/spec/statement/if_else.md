
# If-Else statement

## Overview

`if-else` statement is a conditional jump.
`else` clause is not always necessary.

```javascript
if (a == 0) {
    // then clause
}
```

Here is the example with `else` clause.

```javascript
if (a == 0) {
    // then clause
} else {
    // else clause
}
```

You can combine multiple `if-else` statements like C.

```javascript
if (a == 0) {
    // then clause
} else if (b == 0) {
    // next if-else statement
} else {
    // else clause
}
```

## Examples

### Example 1. Normal case

#### Code

```javascript
var age = 10;
if (age < 20) {
    System.println("young");
} else {
    System.println("adult");
}
```

#### Result

```
young
```

### Example 2. No else clause

#### Code

```javascript
var age = 10;
if (age < 20) {
    System.println("young");
}
```

#### Result

```
young
```


### Example 3. If-else combination

#### Code

```javascript
var age = 20;
if (age < 20) {
    System.println("young");
} else if (age > 20) {
    System.println("adult");
} else {
    System.println("just 20");
}
```

#### Result

```
just 20
```
