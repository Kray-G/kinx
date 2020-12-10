# Using statement

## Overview

`using` is used to load an external library.
As some of standard library is not loaded automatically, you have to load it before using it.

For example, [DateTime](../basic/datetime.md) has to be loaded before using it if you want to use `DateTime` object.

```javascript
using DateTime;
```

`using` will search the source file like `DateTime.kx` when it is used as `using DateTime;`,
and loading it dynamically as a source code.
It means the source code will be compiled together.

## Examples

### Example 1. DateTime

#### Code

```javascript
using DateTime;
var a = new DateTime("2000-01-01 09:30:00");
System.println(a);
```

#### Result

```
2000/01/01 09:30:00
```
