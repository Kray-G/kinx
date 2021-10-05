# Case-When

## Overview

`case-when` expression is introduced as a syntax like **[`switch-case`](../../statement/switch_case.md)** and **[`switch-when`](../../statement/switch_when.md)**, but there are some following differences.

* `switch-case` and `switch-when` is a statement, but `case-when` is an expression. `case-when` can be used inside an expression, and the result value can be assigned to a variable or be used with calculation.
* `switch-case` is a fallthrough by default, but `case-when` will do automatically `break` similarly as `switch-when`. Always the only one of `when` clauses is used.
* `switch-case` and `switch-when` will only check if the value is same, but `case-when` will check if the shape of an array or object is the same. This is like Ruby's pattern matching syntax of `case-in`.
* In `switch-case` and `switch-when`, the order of checking value is normally not guaranteed and it will generate a jump by table in some cases for performance. But when it is in `case-when`, the order of checking is always the written order on the source code and starting it with the top.
* When no condition is matched in `switch-case` and `switch-when`, nothing will be done. On the other hand, when it is in `case-when`, the exception of `NoMatchingPatternException` will be raised.
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
        otherwise: -1
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

You can omit the colon `:` when the `when` body is a block, there is a modifier, or it is `otherwise` clause.
This example uses an `if-modifier` and a pattern matching by `v`,
but a modifier and a pattern matching will be described later.

```javascript
function example(y) {
    var x = case y
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5 {
            return 50000;
        }
        when v if (v == 6) {
            return 600000;
        }
        when v if (v == 7)
            7000000
        otherwise -1
    ;
    return x + 1;
}
9.times { => System.println(example(_)) };
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

If you need the result 4, you should write it below.

```javascript
var y = 1;
var x = (case y when 1: 1 when 2: 2) + 3;
// x means 4, or 1 ?
System.println(x);  // => 4
```

### No Fallthrough

No fallthrough mechanism in `case-when`.
Just one condition is selected and do it.
If not matching to any cases, it selects `otherwise` clause.
And if no `otherwise` clause, the exception of `NoMatchingPatternException` will be raised.

```javascript
function example(y) {
    return case y
        when 0: 0
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5: {
            return 50000;
        }
        // no otherwise clause...
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
} when { x: vx, y: vy, z: { a: 100, b: 200 } }: {
    System.println("Pattern 2 - %d %d" % vx % vy);
};
```

Here is a result.

```
Pattern 2 - 10 20
```

### Pin Operator

As `case-when` uses a pattern matching, you can use `^` as a pin operator for the value check.

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

That is why, you can use `^` as a pin operator to check if `y` equals `v`.

```javascript
var v = 15;
var y = 20;
case y
when 1..10: System.println(y)
when ^v:    System.println(v*2)     // v is not an lvalue, just check it.
when v:     System.println(v*10)    // v is matched to any value.
;
```

It will show the result below.

```
200
```

### If Modifier

Instead of a pin operator, you can also use `if-modifier` for the value check.

Here is an example of `if-modifier` to check if `y` equals `v`.

```javascript
var v = 15;
var y = 20;
case y
when 1..10:         System.println(y)
when m if (m == v): System.println(m*2)     // m is always matched,
                                            // but failed because of m != v.
when m:             System.println(m*10)    // m is matched to any value.
;
```

### Alternative Pattern

You can put multiple conditions in `when` clause.
This is called as an alternative pattern.
The pattern should be separated by `|`.
This separator of `|` is a kind of a shortcut operator, and the condition will be never evaluated after that if it is matched.

Here is a simple example of this.

```javascript
case n
when 1 | 2 | 3: System.println(n)
;
```

Of course you can also use it for an array or object.

```javascript
function test(n) {
    case [n]
    when [1] | [2] | [3]: System.println(n)
    when [v]: System.println(v)
    ;
}
test(1);
test(2);
test(3);
test(10);
```

### Function Object in When Condition

You can put a simple function object in `when` condition.
Here is an example below.

```javascript
function test(n) {
    case n
    when { => _1.isInteger }: System.println("%d is Integer" % n)
    when { => _1.isDouble }:  System.println("%f is Double" % n)
    when { => _1.isString }:  System.println("%s is String" % n)
    ;
}
test(10);
test(10.0);
test("10.0");
```

Note that you should wrap it by `(` and `)` if you want to put an anonymous function as `when` consition.
Otherwise it will cause a compile error.

```javascript
function test(n) {
    case n
    when (&() => _1.isInteger): System.println("%d is Integer" % n)
    when (&() => _1.isDouble):  System.println("%f is Double" % n)
    when (&() => _1.isString):  System.println("%s is String" % n)
    ;
}
test(10);
test(10.0);
test("10.0");
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
        otherwise: -1
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
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5 {
            return 50000;
        }
        when v if (v == 6) {
            return 600000;
        }
        when v if (v == 7)
            7000000
        otherwise -1
    ;
    return x + 1;
}
9.times { => System.println(example(_)) };
```

#### Result

```
0
2
21
301
4001
50001
600001
7000001
0
```

### Example 3. Not Matched

#### Code

```javascript
function example(y) {
    return case y
        when 0: 0
        when 1: 1
        when 2: 20
        when 3: 300
        when 4: 4000
        when 5: {
            return 50000;
        }
        // no otherwise clause...
    ;
}

function test(n) {
    System.println(example(n));
}
7.times().each(test);
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
        at function test(test.kx:16)
        at <main-block>(test.kx:18)
```

### Example 4. Pattern Matching

#### Code

```javascript
var obj = { x: 10, y: 20, z: { a: 100, b: 200 } };
case obj
when { x: vx, y: vy, z: { a: 100, b: 2000 } }: {
    System.println("Pattern 1 - %d %d" % vx % vy);
} when { x: vx, y: vy, z: { a: 100, b: 200 } }: {
    System.println("Pattern 2 - %d %d" % vx % vy);
};
```

#### Result

```
Pattern 2 - 10 20
```

### Example 5. Pin Operator

#### Code

```javascript
var v = 15;
var y = 20;
case y
when 1..10: System.println(y)
when ^v: System.println(v*2)
when v: System.println(v*10)    // matched to any value.
;
```

#### Result

```
200
```

### Example 6. If Modifier

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

### Example 7. DateTime

#### Code

```javascript
using DateTime;

function func(n) {
    case n
    when (DateTime("2000/1/1")..DateTime("2000/1/5")) {
        System.print("range 1 - ");
        System.println(n);
    } when (DateTime("2000/1/6")...DateTime("2000/1/10")) {
        System.print("range 2 - ");
        System.println(n);
    } when (DateTime("2000/1/11")..) {
        System.print("range 3 - ");
        System.println(n);
    } otherwise {
        System.print("not matched - ");
        System.println(n);
    };
}

(DateTime("1999/12/30")..DateTime("2000/1/20")).each { => func(_1) };
```

#### Result

```
not matched - 1999/12/30 00:00:00
not matched - 1999/12/31 00:00:00
range 1 - 2000/01/01 00:00:00
range 1 - 2000/01/02 00:00:00
range 1 - 2000/01/03 00:00:00
range 1 - 2000/01/04 00:00:00
range 1 - 2000/01/05 00:00:00
range 2 - 2000/01/06 00:00:00
range 2 - 2000/01/07 00:00:00
range 2 - 2000/01/08 00:00:00
range 2 - 2000/01/09 00:00:00
not matched - 2000/01/10 00:00:00
range 3 - 2000/01/11 00:00:00
range 3 - 2000/01/12 00:00:00
range 3 - 2000/01/13 00:00:00
range 3 - 2000/01/14 00:00:00
range 3 - 2000/01/15 00:00:00
range 3 - 2000/01/16 00:00:00
range 3 - 2000/01/17 00:00:00
range 3 - 2000/01/18 00:00:00
range 3 - 2000/01/19 00:00:00
range 3 - 2000/01/20 00:00:00
```

### Example 8. Alternative Pattern

#### Code

```javascript
var v = 18;
function func(n) {
    case n
    when 1 | 2 | 3 {
        System.print("range 1 - ");
        System.println(n);
    } when 4 | ^v {
        System.print("range 2 - ");
        System.println(n);
    } when 5..7 | 10...15 {
        System.print("range 3 - ");
        System.println(n);
    } otherwise {
        System.print("not matched - ");
        System.println(n);
    };
}

20.times().each { => func(_1) };
```

#### Result

```
not matched - 0
range 1 - 1
range 1 - 2
range 1 - 3
range 2 - 4
range 3 - 5
range 3 - 6
range 3 - 7
not matched - 8
not matched - 9
range 3 - 10
range 3 - 11
range 3 - 12
range 3 - 13
range 3 - 14
not matched - 15
not matched - 16
not matched - 17
range 2 - 18
not matched - 19
```

### Example 9. Various Example (1)

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
        otherwise:
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

### Example 10. Various Example (2)

#### Code

```javascript
function test([y, z, i, j, k, x]) {
    var val = case [y, z, i, j, k]
        when [1, ...a]:
            a[2]
        when [2..10, a, b]:
            a + b + 10
        when [2..10, a, b, _, _]:
            a + b + 10
        when [v, m, ...n] if (10 < v && v <= 20):
            v + m + n[0] + 42
        when [v, 50, ...a] if (v == x):
            v + 58
        otherwise:
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

### Example 11. Various Example (3)

#### Code

```javascript
function test([y, z, i, j, k, x]) {
    var val = case [y, z, i, j, k]
        when [1, ...a]:
            a[2]
        when [v, m, ...n] if (10 < v && v <= 20):
            v + m + n[0] + 42
        when [v, 50, ...a] if (v == x):
            v + 58
        when [2..10, a, b, ...x]:
            a + b + 10
        otherwise:
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

### Example 12. Various Example (4)

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

### Example 13. Various Example (5)

#### Code

```javascript
json = %{
    {
        "name": "Alice",
        "age": 30,
        "children": [
            {
                "name": "Bob",
                "age": 2
            }
        ]
    }
};

case JSON.parse(json)
when {name: "Alice", children: [{name: "Bob", age: age}]}: {
    System.println(age);
};
```

#### Result

```
2
```

### Example 14. Various Example (6)

#### Code

```javascript
function test(n) {
    case n
    when { => _1.isInteger }: System.println("%d is Integer" % n)
    when { => _1.isDouble }:  System.println("%f is Double" % n)
    when { => _1.isString }:  System.println("%s is String" % n)
    ;
}
test(10);
test(10.0);
test("10.0");
```

#### Result

```
10 is Integer
10.000000 is Double
10.0 is String
```

### Example 15. Various Example (7)

#### Code

```javascript
var cond1 = { => _1.isInteger };
var cond2 = { => _1.isDouble };
var cond3 = { => _1.isString };

function test(n) {
    case n
    when ^cond1: System.println("%d is Integer" % n)
    when ^cond2: System.println("%f is Double" % n)
    when ^cond3: System.println("%s is String" % n)
    ;
}
test(10);
test(10.0);
test("10.0");
```

#### Result

```
10 is Integer
10.000000 is Double
10.0 is String
```

### Example 16. Various Example (8)

#### Code

```javascript
var cond1 = { => _1.isInteger };
var cond3 = { => _1.isString };

function test(n) {
    case n
    when ^cond1:             System.println("%d is Integer" % n)
    when { => _1.isDouble }: System.println("%f is Double" % n)
    when ^cond3:             System.println("%s is String" % n)
    ;
}
test(10);
test(10.0);
test("10.0");
```

#### Result

```
10 is Integer
10.000000 is Double
10.0 is String
```
