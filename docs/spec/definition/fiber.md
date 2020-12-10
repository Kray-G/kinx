# Fiber

## Overview

Fiber is a continuous function.
In the fiber, it is possible to interrupt the process of statements by `yield` and resume it again by `resume`.

## Examples

### Example 1. Fiber

#### Code

```javascript
var fiber = new Fiber {
    System.println("fiber 1");
    yield;
    System.println("fiber 2");
};

System.println("main 1");
fiber.resume();
System.println("main 2");
fiber.resume();
System.println("main 3");
```

#### Result

```
main 1
fiber 1
main 2
fiber 2
main 3
```

### Example 2. Exchange information

#### Code

`yield` will return the value and received some value from `resume`.
The return value from `resume` is an array of arguments.

```javascript
var fiber = new Fiber { &(a1, ...a2)
    System.println("Fiber 1");
    System.println("    a1 = %d, a2 = [%s]" % a1 % a2.join(', '));
    [b1, ...b2] = yield 1;
    System.println("Fiber 2");
    System.println("    b1 = %d, b2 = [%s]" % b1 % b2.join(', '));
    [c1, ...c2] = yield 2;
    System.println("Fiber 3");
    System.println("    c1 = %d, c2 = [%s]" % c1 % c2.join(', '));
    return a1 + b1 + c1;
};

System.println("try[1] = ", fiber.resume(100, 200, 300));
System.println("try[2] = ", fiber.resume(200, 300, 400));
System.println("try[3] = ", fiber.resume(300, 400, 500));
System.println("try[4] = ", fiber.resume(400, 500, 600));  // => FiberException
```

#### Result

```
Fiber 1
    a1 = 100, a2 = [200, 300]
try[1] = 1
Fiber 2
    b1 = 200, b2 = [300, 400]
try[2] = 2
Fiber 3
    c1 = 300, c2 = [400, 500]
try[3] = 600
Uncaught exception: No one catch the exception.
FiberException: Fiber has been already dead
Stack Trace Information:
        at <main-block>(test.kx:16)
```

### Example 3. Fibonacci in Fiber

#### Code

Another sample of Fiber.
This is calculating fibonacci number.

```javascript
var fib = new Fiber {
    var a = 0, b = 1;
    while (true) {
        yield b;
        [a, b] = [b, a + b];
    }
};

var r = 35.times().map(&(i) => fib.resume());
r.each(&(v, i) => System.println("fibonacci[%2d] = %7d" % i % v));
```

#### Result

```
fibonacci[ 0] =       1
fibonacci[ 1] =       1
fibonacci[ 2] =       2
fibonacci[ 3] =       3
fibonacci[ 4] =       5
fibonacci[ 5] =       8
fibonacci[ 6] =      13
fibonacci[ 7] =      21
fibonacci[ 8] =      34
fibonacci[ 9] =      55
fibonacci[10] =      89
fibonacci[11] =     144
fibonacci[12] =     233
fibonacci[13] =     377
fibonacci[14] =     610
fibonacci[15] =     987
fibonacci[16] =    1597
fibonacci[17] =    2584
fibonacci[18] =    4181
fibonacci[19] =    6765
fibonacci[20] =   10946
fibonacci[21] =   17711
fibonacci[22] =   28657
fibonacci[23] =   46368
fibonacci[24] =   75025
fibonacci[25] =  121393
fibonacci[26] =  196418
fibonacci[27] =  317811
fibonacci[28] =  514229
fibonacci[29] =  832040
fibonacci[30] = 1346269
fibonacci[31] = 2178309
fibonacci[32] = 3524578
fibonacci[33] = 5702887
fibonacci[34] = 9227465
```
