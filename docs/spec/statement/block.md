# Block statement

## Overview

Block will create a scope and holding the list of a statement.
Block is also one of statements.

For example, `if` statement has a statement in then clause or else clause,
but a block can be there instead of a single statement to hold a lot of statements.

```javascript
if (a > 0)      System.println("positive"); // a single statement.
else if (a < 0) System.println("negative"); // a single statement.
else {
    // block here, instead of a single statement.
}
```

And also the block has a scope.
The variable shadowing occurs if the same name of variable was declared.
Please see the example 1.

## Examples

### Example 1. Scope

#### Code

```javascript
var a = 10;
{
    var a = 100;
    System.println(a);  // => 100
}
System.println(a);  // => 10
```

#### Result

```
100
10
```
