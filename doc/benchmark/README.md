
# Kinx Benchmark

## Overview

This markdown document is another example of **SpecTest**.
Although there is overhead to run the script, SpecTest can measure the running time.
This means it can be an easy benchmark system.

To change the interpreter per test code, add `(interpreter)` name after the subject of `#### Code` like examples below.

Note that **Ruby** and **Python** must be installed
and the path for all interpreters must be set, to run this benchmark.

To run this benchmark, do the ommand below.

```
$ ./kinx --exec:spectest -v -f doc/benchmark/.spectest
```

## Examples

### Example 1. fibonacci(Kinx Native)

#### Code (kinx)

```javascript
native fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}
System.println(fib(34));
```

#### Result

```
9227465
```

### Example 2. fibonacci(Kinx Normal)

#### Code (kinx)

```javascript
function fib(n) {
    if (n < 3) return n;
    return fib(n-2) + fib(n-1);
}
System.println(fib(34));
```

#### Result

```
9227465
```

### Example 3. fibonacci(Ruby)

#### Code (ruby)

```ruby
def fib(n)
  if n < 3
    return n;
  else
    return fib(n-2) + fib(n-1);
  end
end

puts fib(34)
```

#### Result

```
9227465
```

### Example 4. fibonacci(Python)

#### Code (python)

```python
import sys

def fib(n):
    if n < 3:
        return n
    else:
        return fib(n-1) + fib(n-2)

print fib(int(34))
```

#### Result

```
9227465
```

