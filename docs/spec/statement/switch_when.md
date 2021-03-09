
# Switch-When statement

## Overview

`switch-when` statement is a multiple conditional jump.
In a condition of `when` statement, you can put an expression.
If the condition's value in when as a result is same, direct value is checked first.
Otherwise, the condition written first is checked first.

You DO NOT need `break` for exitting `when` statement because kinx `switch-when` is automatically break it.
Instead, if you need to do fallthrough, put the `fallthrough` keyword at the last statement in `when` clause.

```javascript
switch (x) {
when 1:
    /* ... */
when 2:
    /* ... */
}
```

### Else case

It is not necessary to put `else` case at the bottom.

```javascript
switch (x) {
when 1:
    /* ... */
else: /* fallthrough */
    fallthrough;
when 2:
    /* ... */
}
```

### When label

Any value is available for `when` label.

```javascript
switch (x) {
when 1:         // Number is available
    /* ... */
when a:         // variable is available
    /* ... */
when x[1]+1:    // expression is available
    /* ... */
when f():       // function call is available, but calling a function will be performed every time when comparing here.
    /* ... */
}
```

## Examples

### Example 1. Normal when

#### Code

```javascript
function test(a) {
    var r;
    switch (a) {
    when 1: r = a * 2;
    when 2: r = a * 4;
    when 3: r = a * 8;
    when 4: r = a * 16;
    else:
    }
    return r ?? -1;
}
0.upto(8, &(n) => System.println("%d => %3d" % n % test(n)));
```

#### Result

```
0 =>  -1
1 =>   2
2 =>   8
3 =>  24
4 =>  64
5 =>  -1
6 =>  -1
7 =>  -1
8 =>  -1
```

### Example 2. With do-while

#### Code

```javascript
function test(count) {
    switch (count) {
    else: do {  System.println("%d" % count); count++; fallthrough;
    when 0:     System.println("%d" % count); count++; fallthrough;
    when 1:     System.println("%d" % count); count++; fallthrough;
    when 2:     System.println("%d" % count); count++; fallthrough;
            } while (count < 8);
    }
}
test(2);
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

### Example 3. Non-integer value

#### Code

```javascript
function f() {
    return "a4";
}
function test(a) {
    var r, x = [1, 1.2, "a2", "a"];
    switch (a) {
    when "a1":     r = 2;
    when x[-2]:    r = 4;
    when x[3]+"3": r = 8;
    when f():      r = 16;
    else:
    }
    return r ?? -1;
}
0.upto(8, &(n) => System.println("%d => %3d" % n % test("a" + n)));
```

#### Result

```
0 =>  -1
1 =>   2
2 =>   4
3 =>   8
4 =>  16
5 =>  -1
6 =>  -1
7 =>  -1
8 =>  -1
```

### Example 4. Complex switch-when pattern

#### Code

```javascript
var array = [1,2,3,4,5,6,7,8,9,10];
function switchTest(n) {
    switch (n) {
    when 1:     System.println(n);
    when 2:     System.println(n);
    when 3:     System.println(n);
    when 4:     System.println(n);
    when 5:     System.println(n);
    when 6:     System.println(n);
    when 7:     System.println(n);
    when 8:     System.println(n);

    else:
        System.print("default - ");
        fallthrough;
    when 100:
        System.println(n);
    when array.length():
        System.println("array-length:%{n}");
    when "aaa":
        System.println(n);
    when "bbb":
        System.println(n);
    }
}
0.upto(100, function(i) {
    if (12 < i && i <= 97) {
        return; // omitted.
    }
    System.print("%{i} => ");
    switchTest(i);
});
```

#### Result

```
0 => default - 0
1 => 1
2 => 2
3 => 3
4 => 4
5 => 5
6 => 6
7 => 7
8 => 8
9 => default - 9
10 => array-length:10
11 => default - 11
12 => default - 12
98 => default - 98
99 => default - 99
100 => 100
```
