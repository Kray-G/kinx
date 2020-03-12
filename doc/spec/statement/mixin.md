
# Mixin statement

## Overview

`mixin` keyword is used in a Class definition to include `Module`.
As the example below, class Value will become having methods of `print` and `println` by `mixin`.

```javascript
module Printable {
    public print() {
        System.print(@value);
    }
    public println() {
        System.println(@value);
    }
}

class Value(v) {
    mixin Printable;
    private initialize() {
        @value = v;
    }
}
```

## Examples

### Example 1. Normal case

Here is the whole code of the use case of the above example.

#### Code

```javascript
module Printable {
    public print() {
        System.print(@value);
    }
    public println() {
        System.println(@value);
    }
}

class Value(v) {
    mixin Printable;
    private initialize() {
        @value = v;
    }
}

var val = new Value(100);
val.println();  // => 100
```

#### Result

```
100
```
