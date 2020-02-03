# Kinx Object

## Auto-loaded Object

### System

`System` object is used to realize a basic functionality.

|         Method         |                               Meaning                               |
| ---------------------- | ------------------------------------------------------------------- |
| `System.print(...)`    | Prints a text, converted if necessary, without a newline character. |
| `System.println(...)`  | Prints a text, converted if necessary, with a newline character.    |
| `System.abort()`       | Aborting the program.                                               |
| `System.exec(cmdline)` | Executing the command with shell.                                   |

### String

`String` object is used to operate for a text.

|          Method           |               Meaning               |
| ------------------------- | ----------------------------------- |
| `String.length(str)`      | Returns the length of a string.     |
| `String.parseInt(val)`    | Converts `val` to an integer value. |
| `String.parseDouble(val)` | Converts `val` to a double value.   |

There is a special use case for this object.
The following 2 example means the same work.

```js
String.length(str);
str.length();
```

### Integer

`Integer` object is used to operate for an integer like `100`.
And Math object's function is available for Integer object like `2.pow(10)`.

|                Method                |                          Meaning                          |
| ------------------------------------ | --------------------------------------------------------- |
| `Integer.parseInt(val)`              | Converts `val` to an integer value.                       |
| `Integer.parseDouble(val)`           | Converts `val` to a double value.                         |
| `Integer.times(val, callback)`       | Loop and callback with the range from `0` to `(val - 1)`. |
| `Integer.upto(val, max, callback)`   | Loop and callback with the range from `val` to `max`.     |
| `Integer.downto(val, min, callback)` | Loop and callback with the range from `val` to `min`.     |

There is a special use case for this object.
The following 2 example means the same work.

```js
Integer.times(100, callback);
100.times(callback);
```

### Double

`Double` object is used to operate for a double like `1.5`.
And Math object's function is available for Integer object like `2.0.pow(10.0)`.

|          Method           |               Meaning               |
| ------------------------- | ----------------------------------- |
| `Double.parseInt(val)`    | Converts `val` to an integer value. |
| `Double.parseDouble(val)` | Converts `val` to a double value.   |

There is a special use case for this object.
The following 2 example means the same work.

```js
Double.parseDouble("1.5");
"1.5".parseDouble();
```

### Binary

`Binary` object is used to operate for a binary object like `<0x01,0x02>`.

|        Method        |             Meaning             |
| -------------------- | ------------------------------- |
| `Binary.length(bin)` | Returns the length of a binary. |

There is a special use case for this object.
The following 2 example means the same work.

```js
Binary.length(bin);
bin.length();
```

### Array

`Array` object is used to operate for an array object like `[1,2,3]`.

|              Method              |                   Meaning                    |
| -------------------------------- | -------------------------------------------- |
| `Array.length(ary)`              | Returns the length of an array.              |
| `Array.each(ary, callback, idx)` | Loop and call `callback` with index of `idx` |

There is a special use case for this object.
The following 2 example means the same work.

```js
Array.length(ary);
ary.length();
```

### Math

`Math` object is mathematical functions to perform mathematical operations.
These fnctions are also available for Integer and Double object.

|         Method         |         Meaning          |
| ---------------------- | ------------------------ |
| `Math.acos(dbl)`       | Calculation of `acos()`  |
| `Math.asin(dbl)`       | Calculation of `asin()`  |
| `Math.atan(dbl)`       | Calculation of `atan()`  |
| `Math.atan2(dbl, dbl)` | Calculation of `atan2()` |
| `Math.cos(dbl)`        | Calculation of `cos()`   |
| `Math.sin(dbl)`        | Calculation of `sin()`   |
| `Math.tan(dbl)`        | Calculation of `tan()`   |
| `Math.cosh(dbl)`       | Calculation of `cosh()`  |
| `Math.sinh(dbl)`       | Calculation of `sinh()`  |
| `Math.tanh(dbl)`       | Calculation of `tanh()`  |
| `Math.exp(dbl)`        | Calculation of `exp()`   |
| `Math.ldexp(dbl, int)` | Calculation of `ldexp()` |
| `Math.log(dbl)`        | Calculation of `log()`   |
| `Math.log10(dbl)`      | Calculation of `log10()` |
| `Math.pow(dbl, dbl)`   | Calculation of `pow()`   |
| `Math.sqrt(dbl)`       | Calculation of `sqrt()`  |
| `Math.ceil(dbl)`       | Calculation of `ceil()`  |
| `Math.fabs(dbl)`       | Calculation of `fabs()`  |
| `Math.floor(dbl)`      | Calculation of `floor()` |
| `Math.fmod(dbl)`       | Calculation of `fmod()`  |

### SystemTimer

`SystemTimer` object is used to measure time.
`SystemTimer` is a class, so the instance will be always created by `new` operator.

|          Method           |                            Meaning                             |
| ------------------------- | -------------------------------------------------------------- |
| `tmr = new SystemTimer()` | Creates an instance.                                           |
| `tmr.restart()`           | Restarts the timer.                                            |
| `tmr.elapsed()`           | Returns a elapsed from starting or restarting the measurement. |

### Regex

`Regex` object is used for a regular expression.
`Regex` is a class, so the instance will be always created by `new` operator.

|          Method           |                                                  Meaning                                                   |
| ------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `re = new Regex(pattern)` | Creates an instance.                                                                                       |
| `re.reset(str)`           | Reset the search target string.                                                                            |
| `re.find()`               | `true` if found. This can be used continuously until it has been not found.                                |
| `re.matches()`            | `true` if matches. This can be used only one time because this is checking if the target is fully matched. |

## Exceptions

### RuntimeException

This is a standard exception, do it like `throw RuntimeException("message");`.
