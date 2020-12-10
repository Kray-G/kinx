
# Switch-Case statement

## Overview

`switch-case` statement is a multiple conditional jump.
In a condition of `case` statement, you can put an expression.
If the condition's value in case as a result is same, direct value is checked first.
Otherwise, the condition written first is checked first.

You need `break` for exitting `case` statement because kinx `switch-case` is **fall through**.

```javascript
switch (x) {
case 1:
    /* ... */
    break;
case 2:
    /* ... */
    break;
}
```

### Default case

It is not necessary to put `default` case at the bottom.

```javascript
switch (x) {
case 1:
    /* ... */
    break;
default: /* fall through */
case 2:
    /* ... */
    break;
}
```

### Case label

Any value is available for `case` label.

```javascript
switch (x) {
case 1:         // Number is available
    break;
case a:         // variable is available
    break;
case x[1]+1:    // expression is available
    break;
case f():       // function call is available, but calling a function will be performed every time when comparing here.
    break;
}
```

## Examples

### Example 1. Normal case

#### Code

```javascript
function test(a) {
    switch (a) {
    case 1: return a * 2;
    case 2: return a * 4;
    case 3: return a * 8;
    case 4: return a * 16;
    default:
    }
    return -1;
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
    default: do {   System.println("%d" % count); count++;
    case 0:         System.println("%d" % count); count++;
    case 1:         System.println("%d" % count); count++;
    case 2:         System.println("%d" % count); count++;
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
    var x = [1, 1.2, "a2", "a"];
    switch (a) {
    case "a1":     return 2;
    case x[-2]:    return 4;
    case x[3]+"3": return 8;
    case f():      return 16;
    default:
    }
    return -1;
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

### Example 4. Complex switch-case pattern

#### Code

```javascript
var array = [1,2,3,4,5,6,7,8,9,10];
function switchTest(n) {
    switch (n) {
    case 1:     System.println(n); break;
    case 2:     System.println(n); break;
    case 3:     System.println(n); break;
    case 4:     System.println(n); break;
    case 5:     System.println(n); break;
    case 6:     System.println(n); break;
    case 7:     System.println(n); break;
    case 8:     System.println(n); break;

    default:
        System.print("default - ");
        // fall through
    case 100:   System.println(n); break;
        break;
    case array.length():
        System.println("array-length:%{n}");
        break;
    case "aaa":
        System.println(n);
        break;
    case "bbb":
        System.println(n);
        break;
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
