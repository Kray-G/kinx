# Namespace

## Overview

`namespace` is a scope and an object which holds a class, a module, and so on.
For example, a class name will be a property of a namespace object.

```javascript
namespace A {
    class X {
        /* ... */
    }
}
var x = new A.X();
```

A namespace can be nested.
You can put a namespace into another namespace.

```javascript
namespace A {
    namespace B {
        class X {
            /* ... */
        }
    }
    var x = new B.X();
}
var x = new A.B.X();
```

## Examples

### Example 1. Normal case

#### Code

```javascript
namespace A {
    class X {
        public x() {
            System.println(__FUNC__);
        }
    }
}
var x = new A.X();
x.x();
```

#### Result

```
X#x
```

### Example 2. Nested namespace

#### Code

```javascript
namespace A {
namespace B {
    class X {
        public x() {
            System.println(__FUNC__);
        }
    }

    var x = new A.B.X();    // A.B.X is an available symbol in this scope.
    x.x();

    var x = new B.X();      // B.X is an available symbol in this scope.
    x.x();

    var x = new X();        // X is an available symbol in this scope.
    x.x();

} /* namespace B */
} /* namespace A */

var x = new A.B.X();        // Only A.B.X is an available symbol in this scope.
x.x();
```

#### Result

```
X#x
X#x
X#x
X#x
```
