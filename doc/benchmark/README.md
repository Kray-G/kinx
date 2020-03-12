
# Kinx Benchmark

## Examples

### Example 1. fibonacci(normal)

#### Code

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

### Example 2. fibonacci(native)

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

### Example 3. fibonacci(Ruby)

#### Code (ruby)

```javascript
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

