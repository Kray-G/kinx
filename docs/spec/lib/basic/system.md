# System

## Overview

`System` object is a very basic object including primitive methods in the overall of Kinx system.

### Action Methods

Here are methods to act something.

|                      Method                      |                                   Content                                    |
| ------------------------------------------------ | ---------------------------------------------------------------------------- |
| `System.abort()`                                 | Abort the program.                                                           |
| `System.halt()`                                  | Halt the program.                                                            |
| `System.exec(cmd)`                               | Execute the `cmd` on shell via `system()`.                                   |
| `System.gc()`                                    | Force GC.                                                                    |
| `System.localtime(unixtime)`                     | Returns a [JSON structured object](#json-structured-object) of a localtime.  |
| `System.mktime(tmobject)`                        | Returns a unixtime from a [JSON structured object](#json-structured-object). |
| `System.print(...)`                              | Prints it out without a new line at the tail.                                |
| `System.println(...)`                            | Prints it out with a new line at the tail.                                   |
| `System.sleep(ms)`                               | Sleep the program with `ms` milliseconds.                                    |
| `System.try(func){.else(alt)/.retry(times,ms)}*` | See [this section](#how-to-use-systemtry) for details.                       |

### Checking Methods

Here are methods to check something.

|             Method             |                                     Content                                     |
| ------------------------------ | ------------------------------------------------------------------------------- |
| `System.exepath()`             | The path of this executable.                                                    |
| `System.kinxpath()`            | The path of the Kinx executable.                                                |
| `System.getPlatform()`         | The string of this system such as architecture, an operating system, and so on. |
| `System.isUtf8Bytes(code/str)` | Check if the `code` is utf8 code, or if the head of char of `str` is utf8 code. |

### Definition Methods

Here are methods to define something.

|             Method             |                                             Content                                             |
| ------------------------------ | ----------------------------------------------------------------------------------------------- |
| `System.defineException(name)` | Defines your own exception. See [defineException](../function/define_exception.md) for details. |

### Details

#### JSON Structured Object

Here is the object shape.

```javascript
{
    year:   year,
    month:  month,
    day:    day,
    hour:   hour,
    minute: minute,
    second: second,
}
```

#### How To Use `System.try`

`System.try` is used to handle an exception, and if an exception occurs, it is used to return a value to be alternative.
Here is a basic usage.

```javascript
var x = System.try({ => getData() }).else(null);
```

In this case, x will be `null` if `getData` raised an exception.
As to pass nothing to `.else` means that `.else` returns `null`, you can write `.else()` instead of `.else(null)`.

```javascript
var x = System.try({ => getData() }).else(null);
```

If you want to retry the `getData()` function, you can write it such as following example.

```javascript
var x = System.try({ => getData() }).retry(2, 100).else(null);
```

`.retry` method has 2 arguments.
The first argument is the number of retry, and the second argument is an interval between retries in milliseconds.

## Examples

Methods of `System` is often used in many examples.
This section will show some examples which is not used other examples.

### Example 1. Abort

#### Code

```javascript
for (n in 1..100) {
    System.println(n);
    if (n == 10) System.abort();
}
```

#### Result

```
1
2
3
4
5
6
7
8
9
10
This program aborted.
```

### Example 2. Halt

#### Code

```javascript
for (n in 1..20) {
    System.println(n);
    if (n == 10) System.halt();
}
```

#### Result

```
1
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

### Example 3. Sleep

#### Code

```javascript
var tmr = new SystemTimer();
System.sleep(500);      // waiting 500 milliseconds.
if (tmr.elapsed() > 0.4) {
    System.println("Successful");
}
```

#### Result

```
Successful
```

### Example 4. System.try()

#### Code

```javascript
var n = 0;
function test1() {
    if (++n == 5) {
        return "Successful";
    }
    throw RuntimeException("Error");
}

var x;
x = System.try({ => test1() }).else(1000);
System.println(x);
x = System.try({ => test1() }).retry(2, 50).else(500);
System.println(x);
x = System.try({ => test1() }).retry(10, 50).else(300);
System.println(x);
```

#### Result

```
1000
500
Successful
```
