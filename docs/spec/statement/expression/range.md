# Range Operator

## Overview

### Basic Usage

The easy way to create `Range` object is to use Range operator of `..` and `...`.

```javascript
var r1 = 1..10;     // same as `new Range(1, 10)`
var r2 = 1...10;    // same as `new Range(1, 10, true)`, true means `exclude-end`.
```

`..` means to create `Range` object with including the end parameter,
but `...` means to create `Range` object without the end parameter.

You can also use a variable or an expression with the range operator.

```javascript
function makeRange(begin, len) {
    return begin..(begin+len);
}
System.println(makeRange(100, 2).end()); // => 102
```

You can use String.
There are no differences between Double-quoted and Single-quoted.

```javascript
var a = "a".."z";     // new Range("a", "z")
var b = "ab"..."ax";  // new Range("ab", "ax", true)
var c = 'a'..'z';     // 'a', 'b', 'c', ..., 'z'
```

You can omit the end, but can not omit the first.

```javascript
1..;   // => Okay
1...;  // => Okay
..10;  // => error
...10; // => error
```

If you want to omit the first, use `null` like this.

```javascript
null..10;  // => Okay
```

### Switch Case

`Range` object can be used in `switch-case` statement as below.

```javascript
switch (n) {
case 1..10:
    // do it when 1 <= n and n <= 10.
    break;
case 100...200:
    // do it when 100 <= n and n < 200. Because this range does not include 200.
    break;
}
```

### Index as `Range` for String, Binary, Array, or Rnage

`Range` object can be also used as an index for String, Binary, Array, or Range.
That means a sub sequence of the source object with specified range as below.

```javascript
var str = "abcdefghijklmnopqrstuvwxyz";
System.println(str[2..25]);            // "cdefghijklmnopqrstuvwxyz"
System.println(str[2...25]);           // "cdefghijklmnopqrstuvwxy"
System.println(str.subString(2, 23));  // "cdefghijklmnopqrstuvwxy"
```

Also for Binary, Array, or Range, that is same.

## Examples

### Example 1. Simple use

#### Code

```javascript
System.println((1..100).sum()); // => 5050
```

#### Result

```
5050
```

### Example 2. With Variable and Expression

#### Code

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

### Example 3. Switch Case (1)

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

### Example 4. Switch Case (2)

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

### Example 5. For-in (1)

#### Code

```javascript
for (var e in 2..10) {
    System.println(e);
}
```

#### Result

```
2
3
4
5
6
7
8
9
10
```

### Example 6. For-in (2)

#### Code

```javascript
for (var e in 2..) {
    if (0 < e && e <= 5) {
        System.println(e);
    } else if (e == 200) {
        System.println(e);
    } else if (e == 300) {
        break;
    }
}
```

#### Result

```
2
3
4
5
200
```
