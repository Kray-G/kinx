
# class Range

## Overview

### class Range

The class of `Range` shows a range between begin and end. The object is created by `new Range` as below.

```javascript
new Range(begin, end, excludingEnd)
```

### dot style

The instance of class `Range` is also created by the dot style syntax as below.

There are 2 styles of `..` and `...`.
The style of `..` means to include the end, but the style of `...` means to exclude the end.

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

### Range as an index

`Range` object can be used as an index for Array, String, Binary, or Range like this.

```javascript
a[2..3] // The variable `a` can be Array, String, Binary, or Range.
        // This means to return a set of elements from 2nd element to 3rd element.
```

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

### Example 6. Range for Switch-Case (2)

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

### Example 7. Range for String

Range for String means to return a part of string between the start and the end of `Range`.
It is like `String#subString()` but note that `String#subString()` requires a length.

#### Code

```javascript
var str = "abcdefghijklmnopqrstuvwxyz";
System.println(str[2..25]);            // "cdefghijklmnopqrstuvwxyz"
System.println(str[2...25]);           // "cdefghijklmnopqrstuvwxy"
System.println(str.subString(2, 23));  // "cdefghijklmnopqrstuvwxy"
```

#### Result

```
cdefghijklmnopqrstuvwxyz
cdefghijklmnopqrstuvwxy
cdefghijklmnopqrstuvwxy
```

### Example 8. Range for Array

Range for Array means to return a part of array between the start and the end of `Range`.
It is like `Array#subArray()` but note that `Array#subArray()` requires a length.

#### Code

```javascript
var ary = 16.times();
System.println(ary[2..12]);            // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
System.println(ary[2...12]);           // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
System.println(ary.subArray(2, 10));   // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

### Example 9. Range for Binary

Range for Binary means to return a part of binary between the start and the end of `Range`.
It is like `Binary#subBinary()` but note that `Binary#subBinary()` requires a length.

#### Code

```javascript
var bin = <0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f>;
System.println(bin[2..12]);            // <0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c>
System.println(bin[2...12]);           // <0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b>
System.println(bin.subBinary(2, 10));  // <0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b>
```

#### Result

```
<0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c>
<0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b>
<0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b>
```

### Example 10. Range for Range

Range for Range means to return parts between the start and the end by `Range` at the index.

#### Code

```javascript
var range = 0..16;
System.println(range[2..12]);   // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
System.println(range[2...12]);  // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

### Example 11. Infinite Range (Range Index)

Range for Range means to return parts between the start and the end by `Range` at the index.

#### Code

```javascript
var range = 0..;
System.println(range[2..12]);   // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
System.println(range[2...12]);  // [2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

#### Result

```
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
[2, 3, 4, 5, 6, 7, 8, 9, 10, 11]
```

### Example 12. Infinite Range (Integer Index)

Range for Range means to return parts between the start and the end by `Range` at the index.

#### Code

```javascript
var range = 1..;
System.println(range[2]);       // 3
System.println(range[22]);      // 23
System.println(range[1050]);    // 1051
```

#### Result

```
3
23
1051
```

### Example 13. Range for Range (Infinite Range Index 1)

Range for Range means to return parts between the start and the end by `Range` at the index.

#### Code

```javascript
System.println((1..10)[2..]);   // 3..10
System.println((1...10)[2..]);  // 3...10
System.println((100..)[2..]);   // 102..
```

#### Result

```
Range(3, 10, false)
Range(3, 10, true)
Range(102, null, false)
```

### Example 14. Range for Range (Infinite Range Index 2)

Range for Range means to return parts between the start and the end by `Range` at the index.

#### Code

```javascript
var range = (1...10)[2..];
for (e in range) {
    System.println(e);
}
```

#### Result

```
3
4
5
6
7
8
9
```
