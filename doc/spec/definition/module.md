# Module

## Overview

Module is used to extend a class functionality. This is usually used for the common functionalities cross over a different kind of classes.

### Basic Style

The module definition is basically below.

```javascript
module M { 
    /* ... Defines a public method
        to extend a host class which this is mixined into. */
}
```

### Mixin

The module is mixed into a class by `mixin` keyword.

```javascript
class A {
    mixin M;
    /* ... */
}
```

`mixin` can have multiple modules like this.

```javascript
class A {
    mixin M1, M2, M3;
    /* ... */
}
```

### Extend a Class

By the module mixed into a class, the methods defined in the module are added to the class.
For example, when the module `M` having the method of `method1` is mixed into a class of `A`, `A` could have and use the method of `method1`. Note that the method of `method1` must be a public method then.


```javascript
module M {
    public method1() {
        System.println("This is a method1");
    }
}

class A {
    mixin M;
}

new A().method1();  // => This is a method1
```

## Examples

### Example 1. Normal case

#### Code

```javascript
module M {
    public method1() {
        System.println("This is a method1");
    }
}

class A {
    mixin M;
}

new A().method1();  // => This is a method1
```

#### Result

```
This is a method1
```

### Example 2. Add a common functionality

#### Code

```javascript
module Printable {
    public print() {
        System.println("value = " + @value);
    }
}

class A {
    mixin Printable;
    @value = "'This is A.'";
}

class B {
    mixin Printable;
    @value = 256;
}

var a = new A();
var b = new B();
a.print();
b.print();
```

#### Result

```
value = 'This is A.'
value = 256
```

### Example 3. Multiple mixin (1)

#### Code

```javascript
module M1 {
    public method1() {
        System.println("This is a method1");
    }
}
module M2 {
    public method2() {
        System.println("This is a method2");
    }
}

class A {
    mixin M1, M2;
}

var a = new A();
a.method1();  // => This is a method1
a.method2();  // => This is a method2
```

#### Result

```
This is a method1
This is a method2
```

### Example 4. Multiple mixin (2)

#### Code

```javascript
module M0 {
    public method0() {
        System.println("This is a method0");
    }
}
module M1 {
    public method1() {
        System.println("This is a method1");
    }
}
module M2 {
    public method2() {
        System.println("This is a method2");
    }
}
module M3 {
    public method3() {
        System.println("This is a method3");
    }
}

class A {
    mixin M0;
    mixin M1, M2, M3;
}

var a = new A();
a.method0();  // => This is a method0
a.method1();  // => This is a method1
a.method2();  // => This is a method2
a.method3();  // => This is a method3
```

#### Result

```
This is a method0
This is a method1
This is a method2
This is a method3
```
