# Function Composition Operator

## Overview

The function composition operator generates a new function composed functions.
For example, `Math.abs +> Math.sqrt` means `&(a) => Math.sqrt(Math.abs(a))`.
This provides a new composed reusable function for a greater readability when chaining multiple functions together.

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

// Generates a new composed function.
var doubleSayThenCapitalizeThenExclaim
   = doubleSay
  +> capitalize
  +> exclaim;

var result = "hello" |> doubleSayThenCapitalizeThenExclaim;
System.println(result); // => "Hello, hello!"
```

The operator `<+` is also available.
This is connected in opposite direction and applying functions from the right to the left.
Here is an example.

```
var doubleSayThenCapitalizeThenExclaim
   = exclaim
  <+ capitalize
  <+ doubleSay;

var result = "hello" |> doubleSayThenCapitalizeThenExclaim;
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

// Generates a new composed function.
var newScoring
   = double
  +> { => add(7, _) }
  +> { => boundScore(0, 100, _) };

var newScore = person.score |> newScoring;
System.println(newScore); // => 57
```

## Examples

### Example 1. Example (1)

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

// Generates a new composed function.
var doubleSayThenCapitalizeThenExclaim
   = doubleSay
  +> capitalize
  +> exclaim;

var result = "hello" |> doubleSayThenCapitalizeThenExclaim |> System.println;
```

#### Result

```
Hello, hello!
Hello, hello!
```

### Example 2. Example (2)

#### Code

```javascript
function double(x) { return x + x; }
function add(x, y) { return x + y; }

function boundScore(min, max, score) {
    return Math.max(min, Math.min(max, score));
}

var person = { score: 25 };

// Generates a new composed function.
var newScoring
   = double
  +> { => add(7, _) }
  +> { => boundScore(0, 100, _) };

var newScore = person.score |> newScoring;
System.println(newScore); // => 57
```

#### Result

```
57
```

### Example 3. Example (3)

#### Code

```javascript
const double = &(n) => n * 2;
const increment = &(n) => n + 1;

// Normal case.
var r1 = double(increment(double(double(5)))); // 42
System.println(r1);

// Function composition operator is higher priority than a pipeline operator.
var r2 = 5 |> double +> double +> increment +> double; // 42
System.println(r2);
```

#### Result

```
42
42
```

### Example 4. Example (4)

#### Code

```javascript
const double = &(n) => n * 2;
const increment = &(n) => n + 1;

// Normal case.
var composed1 = double +> double +> increment +> double;
var r1 = 5 |> composed1; // 42
System.println(r1);

var composed2 = double <+ increment <+ double <+ double;
var r2 = composed2 <| 5; // 42
System.println(r2);
```

#### Result

```
42
42
```

### Example 5. Array Example (1)

#### Code

```javascript
var test = ["first", "second", "third"];

composed
     = { => Array.map(_) { => _1 + ":" + _1 } }
    +> { => Array.map(_) { => String.split(_1, ":") } }
    +> Array.flatten
    ;
test |> composed |> System.println;
```

#### Result

```
["first", "first", "second", "second", "third", "third"]
```

### Example 6. Array Example (2)

#### Code

```javascript
var test = ["first", "second", "third"];

composed
     = Array.flatten
    <+ { => Array.map(_) { => String.split(_1, ":") } }
    <+ { => Array.map(_) { => _1 + ":" + _1 } }
    ;
test |> composed |> System.println;
```

#### Result

```
["first", "first", "second", "second", "third", "third"]
```

### Example 7. String Example

#### Code

```javascript
var str = "This is a sample string.";
str |> String.length |> System.println;
```

#### Result

```
24
```

### Example 8. Opposite Direction

#### Code

```javascript
var str = "This is a sample string.";
str |> (System.println <+ String.length);
```

#### Result

```
24
```
