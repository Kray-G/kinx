
# class Range

## Overview

### class Range

The class of `Range` shows a range between begin and end. The object is created by `new Range` as below.

```javascript
new Range(begin, end, excludingEnd)
```

### dot style

The instance of class `Range` is also created by the dot style syntax as below.
There are 2 styles of `..` and `...`. `..` means to include the end, but `...` means to exclude the end.

```javascript
var a = 2..10;  // new Range(2, 10)
var b = 2...10; // new Range(2, 10, true)
```

### Interfaces

The class `Range` have following methods.

|       Name        |                                                    Outline                                                    |
| ----------------- | ------------------------------------------------------------------------------------------------------------- |
| `begin()`         | The value of the beginning point.                                                                             |
| `end()`           | The value of the end point. If you put nothing, returns `null`. This do not care about the `excludeEnd` flag. |
| `next()`          | Returns the next value. If it is called a first time, the beginning value will be returned.                   |
| `isEndExcluded()` | `true` if the `Range` excludes the end.                                                                       |
| `each([func])`    | Iterates the range with callback to `func`.                                                                   |

Note that in `each(func)` with no end point, it will be an infinite loop.

### Mechanism

The object used at the begin and end point of the class `Range` must have followings.

* The operator `<=>`.
    * It is used when comparing with the begin and end point.
* The method named as `next()`.
    * It is used when iterating the object.

### Restriction

The style of omitting the end point like `n..` is available.

But currently you can **NOT** omit the beginning value because it causes a conflict with the spread/rest operator of `...`.
If you need this, you can use the workaround with `null` as below.

```javascript
a = null..10;   // no beginning point of Range.
```

## Examples

### Example 1. Normal case

#### Code

```javascript
System.println((2..10).toArray());
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10]
```

### Example 2. With variable/expression

#### Code

You can use a variable or expression.

```javascript
function makeRange(begin, len) {
    return begin..(begin+len);
}
System.println(makeRange(100, 2).end()); // => 102
```

#### Result

```
102
```

### Example 3. String

#### Code

```javascript
var a = "a".."z";     // new Range("a", "z")
var b = "ab"..."ax";  // new Range("ab", "ax", true)
System.println(a.toArray());
System.println(b.toArray());
```

#### Result

```
["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"]
["ab", "ac", "ad", "ae", "af", "ag", "ah", "ai", "aj", "ak", "al", "am", "an", "ao", "ap", "aq", "ar", "as", "at", "au", "av", "aw"]
```

### Example 4. DateTime

#### Code

```javascript
using DateTime;
for (var dt in DateTime(2000, 1, 1)..DateTime(2000, 1, 10)) {
    System.println(dt);
}
```

#### Result

```
2000/01/01 00:00:00
2000/01/02 00:00:00
2000/01/03 00:00:00
2000/01/04 00:00:00
2000/01/05 00:00:00
2000/01/06 00:00:00
2000/01/07 00:00:00
2000/01/08 00:00:00
2000/01/09 00:00:00
2000/01/10 00:00:00
```

### Example 5. Range for Switch-Case (1)

#### Code

```javascript
for (var i = 0; i <= 10; ++i) {
    switch (i) {
    case 1..4:
        System.println("okay 1 (%{i})");
        break;
    case 7...9:
        System.println("okay 2 (%{i})");
        break;
    default:
        System.println("out of range (%{i})");
        break;
    }
}
```

#### Result

```
out of range (0)
okay 1 (1)
okay 1 (2)
okay 1 (3)
okay 1 (4)
out of range (5)
out of range (6)
okay 2 (7)
okay 2 (8)
out of range (9)
out of range (10)
```

### Example 5. Range for Switch-Case (2)

#### Code

```javascript
for (var i in 'o'..'af') {
    switch (i) {
    case 'ac'..'ae':
        System.println("okay 1 (%{i})");
        break;
    case 'p'...'w':
        System.println("okay 2 (%{i})");
        break;
    default:
        System.println("out of range (%{i})");
        break;
    }
}
```

#### Result

```
out of range (o)
okay 2 (p)
okay 2 (q)
okay 2 (r)
okay 2 (s)
okay 2 (t)
okay 2 (u)
okay 2 (v)
out of range (w)
out of range (x)
out of range (y)
out of range (z)
out of range (aa)
out of range (ab)
okay 1 (ac)
okay 1 (ad)
okay 1 (ae)
out of range (af)
```
