# Pipeline Operator

## Overview

The pipeline operator is a syntactic sugar of a function call with a single argument.
For example, `64 |> Math.sqrt` is absolutely same as `Math.sqrt(64)`.
This provides a greater readability when chaining multiple functions together.

For example, see examples below a little modified from https://github.com/tc39/proposal-pipeline-operator/.

```javascript
function doubleSay(str) {
    return "%{str}, %{str}";
}
function capitalize(str) {
    return str.toUpper(0, 1);
}
function exclaim(str) {
    return str + '!';
}

var result = exclaim(capitalize(doubleSay("hello")));
System.println(result); // => "Hello, hello!"

var result = "hello"
  |> doubleSay
  |> capitalize
  |> exclaim;

System.println(result); // => "Hello, hello!"
```

The operator `<|` is also available.
This is connected in opposite direction and passing a value from the right to the left.
Here is an example.

```
var result =
     exclaim
  <| capitalize
  <| doubleSay
  <| "hello";

System.println(result); // => "Hello, hello!"
```

If you want to use multiple arguments with pipeline, use a lambda as a spot.

```javascript
function double(x) { return x + x; }
function add(x, y) { return x + y; }

function boundScore(min, max, score) {
    return Math.max(min, Math.min(max, score));
}

var person = { score: 25 };

var newScore = person.score
  |> double
  |> { => add(7, _) }
  |> { => boundScore(0, 100, _) };

System.println(newScore); // => 57
```

## Examples

### Example 1. ESNext Proposal Example (1)

#### Code

```javascript
function doubleSay(str) {
    return "%{str}, %{str}";
}
function capitalize(str) {
    return str.toUpper(0, 1);
}
function exclaim(str) {
    return str + '!';
}

var result = exclaim(capitalize(doubleSay("hello")));
System.println(result); // => "Hello, hello!"

var result = "hello"
  |> doubleSay
  |> capitalize
  |> exclaim;

System.println(result); // => "Hello, hello!"
```

#### Result

```
Hello, hello!
Hello, hello!
```

### Example 2. ESNext Proposal Example (2)

#### Code

```javascript
function double(x) { return x + x; }
function add(x, y) { return x + y; }

function boundScore(min, max, score) {
    return Math.max(min, Math.min(max, score));
}

var person = { score: 25 };

var newScore = person.score
  |> double
  |> { => add(7, _) }
  |> { => boundScore(0, 100, _) };

System.println(newScore); // => 57
```

#### Result

```
57
```

### Example 3. ESNext Proposal Example (3)

#### Code

```javascript
const double = &(n) => n * 2;
const increment = &(n) => n + 1;

// Normal case.
var r1 = double(increment(double(double(5)))); // 42
System.println(r1);

// Rewrite it with a pipeline operator.
var r2 = 5 |> double |> double |> increment |> double; // 42
System.println(r2);
```

#### Result

```
42
42
```

### Example 4. Array Example

#### Code

```javascript
var test = ["first", "second", "third"];

var r = test
    |> { => Array.map(_) { => _1 + ":" + _1 } }
    |> { => Array.map(_) { => String.split(_1, ":") } }
    |> Array.flatten
    ;
System.println(r);
```

#### Result

```
["first", "first", "second", "second", "third", "third"]
```

### Example 5. String Example

#### Code

```javascript
var str = "This is a sample string.";
str |> String.length |> System.println;
```

#### Result

```
24
```

### Example 6. Opposite Direction

#### Code

```javascript
function doubleSay(str) {
    return "%{str}, %{str}";
}
function capitalize(str) {
    return str.toUpper(0, 1);
}
function exclaim(str) {
    return str + '!';
}

var result =
     exclaim
  <| capitalize
  <| doubleSay
  <| "hello";

System.println(result); // => "Hello, hello!"
```

#### Result

```
Hello, hello!
```
