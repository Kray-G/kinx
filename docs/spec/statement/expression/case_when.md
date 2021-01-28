# Case-When

## Overview

`case-when` expression is introduced as a syntax like `switch-case`, but the followings are different.

* `switch-case` is a statement, but `case-when` is an expression. `case-when` can be used inside an expression, and the result value can be assigned to a variable or be used with calculation.
* `case` clause in `switch` allows a fall through, but `when` clause in `case` never do it. Always the only one of `when` clause is used.
* `switch-case` will only check if the value is same, but `case-when` will check if the shape of an array or object is the same. This is like Ruby's pattern matching syntax of `case-in`.
* In `switch-case`, the order of checking value is normally not guaranteed, but when it is in `case-when`, the order of checking is always the written order on the source code and starting it with the top.
* When no condition is matched in `switch-case`, nothing is done. On the other hand, when it is in `case-when`, the exception of `NoMatchingPatternException` will be raised.
* Putting a block to a `when` clause means an on the fly function call. Therefore `return` in a block of `when` clause never returns to a caller function, and just returns a value as a result of `when` clause.
* `case-when` is an expression, so you need a block when you want to write a statement. As said above, a block is an automatically called function object, so you can write multiple statements in a block and do it.
* `case-when` is an expression, so the end of statement requires a semicolon of `;`.

### Basic Usage

#### Normal Case

`case-when` example is below.

```javascript
function example(y) {
    var x = case y
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5: {
            return 50000;
                // this is an automatically called internal function,
                // so 50000 will be returned to the case expression itself
                // and it is just assigned to the variable `x`.
        }
        else: -1
    ;
    return x + 1;
}
7.times { => System.println(example(_)) };
```

This code shows the following result.

```
0
2
21
301
4001
50001
0
```

#### Without Colon

You do not have to use the colon `:`, and using it is only for an appearance.

```javascript
function example(y) {
    var x = case y
        when 1 1
        when 2 20
        when 3 300
        when 4 4000
        when 5 {
            return 50000;
        }
        else -1
    ;
    return x + 1;
}
7.times { => System.println(example(_)) };
```

This will also show the same result above.

#### Inside Expression

If you want to use `case-when` inside an expression,
use `(` and `)` to avoid a syntax confusion or syntax error.

For example, sometimes the result may be different from your expectation as below.

```javascript
var y = 1;
var x = case y when 1: 1 when 2: 2 + 3;
// x means 4, or 1 ?
System.println(x);  // => 1, because it is `case y when 1: 1 when 2: (2 + 3)`.
```

If you want the result 4, you should write it below.

```javascript
var y = 1;
var x = (case y when 1: 1 when 2: 2) + 3;
// x means 4, or 1 ?
System.println(x);  // => 4
```

### No Fallthrough

No fallthrough mechanism in `case-when`.
Just one condition is selected and do it.
If not matching to any cases, it selects `else` clause.
And if no `else` clause, the exdeption of `NoMatchingPatternException` will be raised.

```javascript
function example(y) {
    return case y
        when 0 0
        when 1 1
        when 2 20
        when 3 300
        when 4 4000
        when 5 {
            return 50000;
        }
        // no else clause...
    ;
}
7.times { => System.println(example(_)) };
```

Here is the result.

```
0
1
20
300
4000
50000
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function example(test.kx:12)
        at function __test_kx_14___anonymous_func228(test.kx:14)
        at <main-block>(test.kx:14)
```

### Pattern Matching

As the same as an assignment, the `when` condition will check by a pattern matching.
Therefore, you can use it below.

```javascript
var obj = { x: 10, y: 20, z: { a: 100, b: 200 } };
case obj
when { x: vx, y: vy, z: { a: 100, b: 2000 } }: {
    System.println("Pattern 1 - %d %d" % vx % vy);
}
when { x: vx, y: vy, z: { a: 100, b: 200 } }: {
    System.println("Pattern 2 - %d %d" % vx % vy);
}
;
```

Here is a result.

```
Pattern 2 - 10 20
```

### If Modifier

As `case-when` uses a pattern matching, you can use `if-modifier` for the value check.

```javascript
var y = 20;
case y
when 1..10: System.println(y)
when v: System.println(v*2)
    // the above `when` condition does NOT mean `y equals v`.
    // it means `y is assigned to the variable v`.
    // as a result, this condition will match to any y value.
;
```

That is why, you can use `if-modifier` to check if `y` equals `v`.

```javascript
var v = 15;
var y = 20;
case y
when 1..10: System.println(y)
when m if (m == v): System.println(m*2)
when m: System.println(m*10)    // matched to any value.
;
```

## Examples

### Example 1. Normal Case

#### Code

```javascript
function example(y) {
    var x = case y
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5: {
            return 50000;
                // this is an automatically called internal function,
                // so 50000 will be returned to the case expression itself
                // and it is just assigned to the variable `x`.
        }
        else: -1
    ;
    return x + 1;
}
7.times { => System.println(example(_)) };
```

#### Result

```
0
2
21
301
4001
50001
0
```

### Example 2. Without Colon

#### Code

```javascript
function example(y) {
    var x = case y
        when 1 1
        when 2 20
        when 3 300
        when 4 4000
        when 5 {
            return 50000;
        }
        else -1
    ;
    return x + 1;
}
7.times { => System.println(example(_)) };
```

#### Result

```
0
2
21
301
4001
50001
0
```

### Example 3. Not Matched

#### Code

```javascript
function example(y) {
    return case y
        when 0 0
        when 1 1
        when 2 20
        when 3 300
        when 4 4000
        when 5 {
            return 50000;
        }
        // no else clause...
    ;
}
7.times { => System.println(example(_)) };
```

#### Result

```
0
1
20
300
4000
50000
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function example(test.kx:12)
        at function __test_14___anonymous_func228(test.kx:14)
        at <main-block>(test.kx:14)
```

### Example 4. Pattern Matching

#### Code

```javascript
var obj = { x: 10, y: 20, z: { a: 100, b: 200 } };
case obj
when { x: vx, y: vy, z: { a: 100, b: 2000 } }: {
    System.println("Pattern 1 - %d %d" % vx % vy);
}
when { x: vx, y: vy, z: { a: 100, b: 200 } }: {
    System.println("Pattern 2 - %d %d" % vx % vy);
}
;
```

#### Result

```
Pattern 2 - 10 20
```

### Example 5. If Modifier

#### Code

```javascript
var v = 15;
var y = 20;
case y
when 1..10: System.println(y)
when m if (m == v): System.println(m*2)
when m: System.println(m*10)    // matched to any value.
;
```

#### Result

```
200
```

### Example 6. Various Example (1)

#### Code

```javascript
function test(y, m, n) {
    return case y
        when 1:
            1
        when 2..10:
            10
        when v if (v == m):
            v + 42
        when v if (v == n):
            v + 58
        else:
            -1
    ;
}
System.println(test(-1));
System.println(test(1));
System.println(test(2));
System.println(test(5));
System.println(test(10));
System.println(test(100, 100, 2));
System.println(test(200, 1, 200));
```

#### Result

```
-1
1
10
10
10
142
258
```

### Example 7. Various Example (2)

#### Code

```javascript
function test([y, z, i, j, k, x]) {
    var val = case [y, z, i, j, k]
        when [1, ...a]:
            a[2]
        when [2..10, a, b]:
            a + b + 10
        when [v, m, ...n] if (10 < v && v <= 20):
            v + m + n[0] + 42
        when [v, 50, ...a] if (v == x):
            v + 58
        else:
            -1
    ;
    return val;
}
System.println(test([1, 2, 3, 4, 5, 6]));
System.println(test([2, 2, 3, 4, 5, 6]));
System.println(test([10, 12, 13, 14, 15, 16]));
System.println(test([11, 12, 13, 14, 15, 16]));
System.println(test([50, 50, 13, 14, 15, 50]));
System.println(test([50, 50, 13, 14, 15, 51]));
System.println(test([50, 51, 13, 14, 15, 50]));
```

#### Result

```
4
15
35
78
108
-1
-1
```

### Example 8. Various Example (3)

#### Code

```javascript
function test(m, obj) {
    return case obj
        when { x: 5, y: y, sub: z } if (y == m):
            { => y }()
        when { x: 6, y: y, sub: { a: 1, b: b, c: c} }:
            y + b + c
        when { x: 10, y: y, sub: z }:
            z
    ;
}
System.println(test(20, { x: 5, y: 20, sub: { a: 1, b: 2, c: 3 } }));
System.println(test(20, { x: 6, y: 10, sub: { a: 1, b: 2, c: 3 } }));
System.println(test(20, { x: 10, y: 10, sub: { a: 1, b: 2, c: 3 } }));
System.println(test(10, { x: 5, y: 20, sub: { a: 1, b: 2, c: 3 } }));
```

#### Result

```
20
15
{"a":1,"b":2,"c":3}
Uncaught exception: No one catch the exception.
NoMatchingPatternException: Pattern not matched
Stack Trace Information:
        at function test(test.kx:9)
        at <main-block>(test.kx:14)
```
