# JIT Compiler - Just In Time Compiler

## Overview

Kinx has a JIT Compiler Library to use JIT easily.

### using Jit

JIT Library is not a embedded library, so you should load it by `using`.

```javascript
using Jit;
```

### Jit Object

Jit object has methods for Jit parameters and `Compiler` class.

#### Methods for Jit

As a Jit parameter, there are immediate values, registers, and a memory access. It can be used as the way below.

##### Immediate Value and Memory Access

As for an immediate value and a memory access, the following methods are prepared.
`Jit.VAR()` is a special method to use a local variable area. This method will prepare the local variable on the stack and use it.

|          Method           |                                                                                          Remark                                                                                          |
| ------------------------- | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Jit.IMM(v)`              | 64-bit Integer, or floating point number. The type which will be selected is determined with the destination register of assignment.                                                     |
| `Jit.VAR(n)`              | This means a local variable. The area on the stack is automatically allocated. The variable is always 8 bytes.                                                                           |
| `Jit.MEM1(r1, offset)`    | This means a memory address which is the address pointed by r1 register and offset.                                                                                                      |
| `Jit.MEM2(r1, r2, shift)` | This means `r1 + r2 * (bytes by shift)` and (bytes by shift) means 1 byte when the shift is 0, 2 bytes when the shift is 1, 4 bytes when the shift is 2, or 8 bytes when the shift is 3. |

##### Registers

The following registers are available. The number of available registers in a function will be automatically calculated for each function.

|       Registers        |                                       Meaning                                        |
| ---------------------- | ------------------------------------------------------------------------------------ |
| `Jit.R0` .. `Jit.R5`   | General Purpose Register. It may be destroyed after calling a function.              |
| `Jit.S0` .. `Jit.S5`   | General Purpose Register. It is saved and can be used also after calling a function. |
| `Jit.FR0` .. `Jit.FR5` | Floating Point Register. It may be destroyed after calling a function.               |
| `Jit.FS0` .. `Jit.FS5` | Floating Point Register. It is saved and can be used also after calling a function.  |

By the way, note that a Floating Point Register can be used until max 6 registers for both `FR` and `FS`, that is why only `FS0` is available when you use `FR5`.
See below for this.

|              `FR*` Register              |              `FS*` Register              |
| ---------------------------------------- | ---------------------------------------- |
| (Can not be used)                        | `FS0`, `FS1`, `FS2`, `FS3`, `FS4`, `FS5` |
| `FR0`                                    | `FS0`, `FS1`, `FS2`, `FS3`, `FS4`        |
| `FR0`, `FR1`                             | `FS0`, `FS1`, `FS2`, `FS3`               |
| `FR0`, `FR1`, `FR2`                      | `FS0`, `FS1`, `FS2`                      |
| `FR0`, `FR1`, `FR2`, `FR3`               | `FS0`, `FS1`                             |
| `FR0`, `FR1`, `FR2`, `FR3`, `FR4`        | `FS0`                                    |
| `FR0`, `FR1`, `FR2`, `FR3`, `FR4`, `FR5` | (Can not be used)                        |

#### Jit Compiler

`Jit.Compiler()` will create a Jit Compiler object to generate Jit instructions.

```javascript
var c = new Jit.Compiler();
```

Jit Compiler has the following methods.

|        Jit Compiler Methods         | Return Value |                                                                              Outline                                                                              |
| ----------------------------------- | ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Jit.Compiler#label()`              | label        | Adds a label to a current location.                                                                                                                               |
| `Jit.Compiler#makeConst(reg, init)` | ConstTarget  | Returns a temporary code to set an immediate value after generating the Jit code.                                                                                 |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#localp(dst, offset)`  |              | Generates the code to get an address of a local variable. The address will be set to the register of `dst`. `offset` means an index of a local variable.          |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#enter(argType)`       | label        | Generates an entry point of a function. You can specify the argument type, but it can be also omitted.                                                            |
| `Jit.Compiler#fastEnter(reg)`       | label        | Generates an entry point of a function without prologue and epilogue. `reg` will hold a return address.                                                           |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#ret(val)`             |              | Generates a `ret` code with the return value of `val`. `val` will be returned by `FR0` register when it is a floating point, otherwise returned by `R0` register. |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#f2i(dst, op1)`        |              | Generates the code to cast from double to int64_t. `dst` should be a general purpose register and `op1` should be a floating point register.                      |
| `Jit.Compiler#i2f(dst, op1)`        |              | Generates the code to cast from int64_t to double. `dst` should be a floating point register and `op1` should be a general purpose register.                      |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#mov(dst, op1)`        |              | Generates the code to assign `op1` to `dst`. It will automatically determine if it is a floating point or not.                                                    |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#neg(dst, op1)`        |              | Generates the code to store a sign inverted `op 1` to `dst`.                                                                                                      |
| `Jit.Compiler#clz(dst, op1)`        |              | Generates the code to count the number of bits with 0 from the head of `op1` and to store it to `dst`.                                                            |
| `Jit.Compiler#add(dst, op1, op2)`   |              | Generates the code of addition of `op1` and `op2` and to store it to `dst`.                                                                                       |
| `Jit.Compiler#sub(dst, op1, op2)`   |              | Generates the code of subtract of `op1` and `op2` and to store it to `dst`.                                                                                       |
| `Jit.Compiler#mul(dst, op1, op2)`   |              | Generates the code to multiply `op1` by `op2` and to store it to `dst`.                                                                                           |
| `Jit.Compiler#div(dst, op1, op2)`   |              | Only for a floating point number, generates the code to divide `op1` and `op2`, and store it to `dst`.                                                            |
| `Jit.Compiler#div()`                |              | Generates the code to divide `R0` register by `R1` register as an unsigned integer, and store a result to `R0` register.                                          |
| `Jit.Compiler#sdiv()`               |              | Generates the code to divide `R0` register by `R1` register as a signed integer, and store a result to `R0` register.                                             |
| `Jit.Compiler#divmod()`             |              | Generates the code to divide `R0` register by `R1` register as an unsigned integer, and store a result to `R0` register and to store a reminder to `R1` register. |
| `Jit.Compiler#sdivmod()`            |              | Generates the code to divide `R0` register by `R1` register as a signed integer, and store a result to `R0` register and to store a reminder to `R1` register.    |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#not(dst, op1)`        |              | Generates the code to store a bitwise inverted `op1` to `dst`.                                                                                                    |
| `Jit.Compiler#and(dst, op1, op2)`   |              | Generates the code to store the result of a bitwise AND between `op1` and `op2` to `dst`.                                                                         |
| `Jit.Compiler#or(dst, op1, op2)`    |              | Generates the code to store the result of a bitwise OR between `op1` and `op2` to `dst`.                                                                          |
| `Jit.Compiler#xor(dst, op1, op2)`   |              | Generates the code to store the result of a bitwise XOR between `op1` and `op2` to `dst`.                                                                         |
| `Jit.Compiler#shl(dst, op1, op2)`   |              | Generates the code to store the result shifted `op1` by `op2`-bits to `dst`.                                                                                      |
| `Jit.Compiler#lshr(dst, op1, op2)`  |              | Generates the code to store the result of logical-shift of `op1` by `op2`-bits to `dst`.                                                                          |
| `Jit.Compiler#ashr(dst, op1, op2)`  |              | Generates the code to store the result of arithmetic-shift of `op1` by `op2`-bits to `dst`.                                                                       |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#call(label)`          | JumpTarget   | Generates the code to call a function defined by `enter()`. This returns a JumpTarget when `label` is not specified.                                              |
| `Jit.Compiler#fastCall(label)`      | JumpTarget   | Generates the code to call a function defined by `fastEnter()`. This returns a JumpTarget when `label` is not specified.                                          |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#jmp(label)`           | JumpTarget   | Generates the code of `jmp`. Use and set the destination by JumpTarget if you do not specify `label`.                                                             |
| `Jit.Compiler#ijmp(dst)`            | JumpTarget   | Generates the code of `jmp`.  `dst` is an immediate value or a register holding an address.                                                                       |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#eq(op1, op2)`         | JumpTarget   | Generates the code to check `op1 == op2`, and returns JumpTarget used to specify the destination to jump when the result is true.                                 |
| `Jit.Compiler#neq(op1, op2)`        | JumpTarget   | Generates the code to check `op1 != op2`, and returns JumpTarget used to specify the destination to jump when the result is true.                                 |
| `Jit.Compiler#lt(op1, op2)`         | JumpTarget   | Generates the code to check `op1 < op2` as an unsigned integer, and returns JumpTarget used to specify the destination to jump when the result is true.           |
| `Jit.Compiler#le(op1, op2)`         | JumpTarget   | Generates the code to check `op1 <= op2` as an unsigned integer, and returns JumpTarget used to specify the destination to jump when the result is true.          |
| `Jit.Compiler#gt(op1, op2)`         | JumpTarget   | Generates the code to check `op1 > op2` as an unsigned integer, and returns JumpTarget used to specify the destination to jump when the result is true.           |
| `Jit.Compiler#ge(op1, op2)`         | JumpTarget   | Generates the code to check `op1 >= op2` as an unsigned integer, and returns JumpTarget used to specify the destination to jump when the result is true.          |
| `Jit.Compiler#slt(op1, op2)`        | JumpTarget   | Generates the code to check `op1 < op2` as a signed integer, and returns JumpTarget used to specify the destination to jump when the result is true.              |
| `Jit.Compiler#sle(op1, op2)`        | JumpTarget   | Generates the code to check `op1 <= op2` as a signed integer, and returns JumpTarget used to specify the destination to jump when the result is true.             |
| `Jit.Compiler#sgt(op1, op2)`        | JumpTarget   | Generates the code to check `op1 > op2` as a signed integer, and returns JumpTarget used to specify the destination to jump when the result is true.              |
| `Jit.Compiler#sge(op1, op2)`        | JumpTarget   | Generates the code to check `op1 >= op2` as a signed integer, and returns JumpTarget used to specify the destination to jump when the result is true.             |
|                                     |              |                                                                                                                                                                   |
| `Jit.Compiler#generate()`           | JitCode      | Returns an actual generated code.                                                                                                                                 |

#### Jit.Compiler#enter(argType)

Defines an entry point of a function by `enter()` method with `argType` like `Jit.ArgType.SW_SW_SW`.
The type of `argType` is combination of followings and arguments are specified until the max 3 arguments.

* `SW` ... Signed Word (64bit)
* `UW` ... Unsigned Word (64bit)
* `FP` ... Floating Point (64bit)

If you do not specify the `argType`, it means `Jit.ArgType.SW_SW_SW`.
But in fact, `SW` and `UW` is same because its bit sequence is same.
You can omit the type from the tail, so the followings are same meaning.

* `Jit.ArgType.SW_SW_SW`
* `Jit.ArgType.SW_SW`
* `Jit.ArgType.SW`

The registers used as arguments are fixed. See below.

* Caller

|  Type   | 1st argument | 2nd argument | 3rd argument |
| ------- | :----------: | :----------: | :----------: |
| Integer |   `Jit.R0`   |   `Jit.R1`   |   `Jit.R2`   |
| Double  |  `Jit.FR0`   |  `Jit.FR1`   |  `Jit.FR2`   |

* Callee

|  Type   | 1st argument | 2nd argument | 3rd argument |
| ------- | :----------: | :----------: | :----------: |
| Integer |   `Jit.S0`   |   `Jit.S1`   |   `Jit.S2`   |
| Double  |  `Jit.FS0`   |  `Jit.FS1`   |  `Jit.FS2`   |

Note that the registers are different between caller and callee.

#### ConstTarget

Label address is set by the method of `setLabel()`.
It is used when you want to set the label as an immediate value.
Now it is hard to use this interface so far, so I would like to prepare this as more useful interface.

#### JumpTarget

This object has a `setLabel()` method and set the destination to jump, or the destination of a function call.

For example, the following shows a branch.

```javascript
var c = new Jit.Compiler();
// Entry point
c.enter();
// S0 >= 3
var jump0 = c.ge(Jit.S0, Jit.IMM(3));
... // The code when the condition is false.
var jump1 = c.jmp();
var label0 = c.label();
... // The code when the condition is true.
var label1 = c.label();
...

jump0.setLabel(label0);
jump1.setLabel(label1);
```

#### JitCode

When generating the code is successful, returns a JitCode object.
JitCode object has methods below.

|          メソッド          |                   概要                    |
| -------------------------- | ----------------------------------------- |
| `JitCode#run(a1, a2, a3)`  | Returns a value as Integer.               |
| `JitCode#frun(a1, a2, a3)` | Returns a value as Double.                |
| `JitCode#dump()`           | Output the assemble list to be generated. |

By the way note that you can specify only the max 3 arguments as a specification.

## Examples

### Example 1. Fibonacci by JIT lib

#### Code

```
using Jit;

var c = new Jit.Compiler();
var entry1 = c.enter();
    var jump0 = c.ge(Jit.S0, Jit.IMM(3));
    c.ret(Jit.S0);
    var l1 = c.label();
    c.sub(Jit.R0, Jit.S0, Jit.IMM(2));
    c.call(entry1);
    c.mov(Jit.S1, Jit.R0);
    c.sub(Jit.R0, Jit.S0, Jit.IMM(1));
    c.call(entry1);
    c.add(Jit.R0, Jit.R0, Jit.S1);
    c.ret(Jit.R0);

jump0.setLabel(l1);
var code = c.generate();

for (var i = 1; i <= 42; ++i) {
    var r = code.run(i);
    System.println("fib(%2d) = %d" % i % r);
}
```

#### Result

```
fib( 1) = 1
fib( 2) = 2
fib( 3) = 3
fib( 4) = 5
fib( 5) = 8
fib( 6) = 13
fib( 7) = 21
fib( 8) = 34
fib( 9) = 55
fib(10) = 89
fib(11) = 144
fib(12) = 233
fib(13) = 377
fib(14) = 610
fib(15) = 987
fib(16) = 1597
fib(17) = 2584
fib(18) = 4181
fib(19) = 6765
fib(20) = 10946
fib(21) = 17711
fib(22) = 28657
fib(23) = 46368
fib(24) = 75025
fib(25) = 121393
fib(26) = 196418
fib(27) = 317811
fib(28) = 514229
fib(29) = 832040
fib(30) = 1346269
fib(31) = 2178309
fib(32) = 3524578
fib(33) = 5702887
fib(34) = 9227465
fib(35) = 14930352
fib(36) = 24157817
fib(37) = 39088169
fib(38) = 63245986
fib(39) = 102334155
fib(40) = 165580141
fib(41) = 267914296
fib(42) = 433494437
```

### Example 2. Fibonacci(double) by JIT lib

#### Code

```
using Jit;

var c = new Jit.Compiler();
var entry1 = c.enter(Jit.ArgType.FP);
    c.mov(Jit.FR0, Jit.IMM(0.3));
    var jump0 = c.ge(Jit.FS0, Jit.FR0);
    c.ret(Jit.FS0);
    var l1 = c.label();
    c.mov(Jit.FR0, Jit.IMM(0.2));
    c.sub(Jit.FR0, Jit.FS0, Jit.FR0);
    c.call(entry1);
    c.mov(Jit.FS1, Jit.FR0);
    c.mov(Jit.FR0, Jit.IMM(0.1));
    c.sub(Jit.FR0, Jit.FS0, Jit.FR0);
    c.call(entry1);
    c.add(Jit.FR0, Jit.FR0, Jit.FS1);
    c.ret(Jit.FR0);

jump0.setLabel(l1);
var code = c.generate();

for (var i = 0.1; i < 3.5; i += 0.1) {
    var r = code.frun(i);
    System.println("fib(%3.1f) = %.1f" % i % r);
}
```

#### Result

```
fib(0.1) = 0.1
fib(0.2) = 0.2
fib(0.3) = 0.3
fib(0.4) = 0.5
fib(0.5) = 0.8
fib(0.6) = 1.3
fib(0.7) = 2.1
fib(0.8) = 3.4
fib(0.9) = 5.5
fib(1.0) = 8.9
fib(1.1) = 14.4
fib(1.2) = 23.3
fib(1.3) = 37.7
fib(1.4) = 61.0
fib(1.5) = 98.7
fib(1.6) = 159.7
fib(1.7) = 258.4
fib(1.8) = 418.1
fib(1.9) = 676.5
fib(2.0) = 1094.6
fib(2.1) = 1771.1
fib(2.2) = 2865.7
fib(2.3) = 4636.8
fib(2.4) = 7502.5
fib(2.5) = 12139.3
fib(2.6) = 19641.8
fib(2.7) = 31781.1
fib(2.8) = 51422.9
fib(2.9) = 83204.0
fib(3.0) = 134626.9
fib(3.1) = 217830.9
fib(3.2) = 352457.8
fib(3.3) = 570288.7
fib(3.4) = 922746.5
```
