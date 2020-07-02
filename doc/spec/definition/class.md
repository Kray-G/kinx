# Class

## Overview

Class is a set of data and procedure.
Kinx is a prototype based language but `class` keyword is prepared as a syntax sugar of creating an object instance.

### Basic Style

The class definition is basically that there are the case of having arguments and the case of no arguments.

```javascript
class A { /* ... */ }
class A() { /* ... */ }
class A(a, b) { /* ... */ }
```

In the above case, `class A` is the same as `class A()`.

### Inheritance

The `:` is used for inheritance of class.
About arguments for inheritance, it is also same as a simple class definition, and the arguments with `(` and `)` are able to be omitted.
The examples of inheritance are below.

```javascript
class A : B { /* ... */ }
class A() : B { /* ... */ }
class A : B(true) { /* ... */ }
class A(a, b) : B(b) { /* ... */ }
```

### Instantiate

The class object is instantiated by `new` operator.
When instantiating the object, you have to use a function call style like `new ClassName()`.
It makes no sense with `new ClassName` only.

```javascript
class A { /* ... */ }
var a = new A();
```

### Keyword `this` and `@`

`this` means the instance itself.

```javascript
class A {
    public flagOnAlt() {
        this.flagOn();
    }
    public flagOn() {
        this.flag = true;
    }
}
```

You can use `@` instead of `this.`, which is `this` plus `dot`.
By this, you can write the following for the above code.

```javascript
class A {
    public flagOnAlt() {
        @flagOn();
    }
    public flagOn() {
        @flag = true;
    }
}
```

### Data

#### Private data and public data

The variable declared in class scope is a local private variable.
A property of `this` is a public variable.

```javascript
class A {
    var flag_ = false;  // a local private variable.
    public flagOn() {
        @flagOnActual();
    }
    public flagOnActual() {
        @flag = true;   // a public variable.
    }
}

var a = new A();
a.flagOn();
System.println(a.flag ? "true" : "false");  // => true
```

### Methods

Methods are defined with `public` and `private` keyword.
The function defined with `private` is used only in a local scope, which is inside a class scope.

On the other hand, the function defined with `public` can be accessed by an instance's property.

```javascript
class A {
    private method1() {
        /* ... */
    }
    public method2() {
        method1();  // Okay, the `method1` is accessible inside the class scope.
        /* ... */
    }
    private method3() {
        method2();  // The `method2` is also accessible inside the class scope.
        @method2(); // The `method2` is also accessible through `this`.
    }
}

var a = new A();
// a.method1();     // Error, the `method1` is accessible through the instance.
a.method2();        // Okay, the `method2` is accessible through the instance.
```

### Special Methods

The `class` keyword will define some special methods.

#### `initialize`

If `initialize` method is defined, the `initialize` method is automatically called right after instantiated. The `initialize` method can be defined either `public` or `private`.

```javascript
class A {
    private initialize() {
        System.println("called");
    }
}

var a = new A();    // => "called"
```

#### `instanceOf`

A class instance has an `instanceOf` method automatically.
This method accepts a class name as a variable, and it will return true if a target object is an instance of a specified class or a base class.

```javascript
class C {};
class B {};
class A : B {};

var a = new A();
System.println(a.instanceOf(A) ? "true" : "false"); // => "true"
System.println(a.instanceOf(B) ? "true" : "false"); // => "true"
System.println(a.instanceOf(C) ? "true" : "false"); // => "false"
```

## Examples

### Example 1. Normal case (1)

#### Code

```javascript
class A(name) {
    public method() {
        System.println(name, " called.");
    }
}
class B : A("class B") {}
class C() : A("class C") {}
class D(name) : A("class "+name) {}
new B().method();
new C().method();
new D("D").method();
```

#### Result

```
class B called.
class C called.
class D called.
```

### Example 2. Normal case (2)

#### Code

```javascript
class A {
    var flag_ = false;  // a local private variable.
    public flagOn() {
        @flagOnActual();
    }
    public flagOnActual() {
        @flag = true;   // a public variable.
    }
}

var a = new A();
a.flagOn();
System.println(a.flag ? "true" : "false");  // => true
```

#### Result

```
true
```

### Example 3. `initialize` method

#### Code

```javascript
class A {
    private initialize() {
        System.println("called");
    }
}

var a = new A();    // => "called"
```

#### Result

```
called
```

### Example 3. `instanceOf` method

#### Code

```javascript
class C {};
class B {};
class A : B {};

var a = new A();
System.println(a.instanceOf(A) ? "true" : "false"); // => "true"
System.println(a.instanceOf(B) ? "true" : "false"); // => "true"
System.println(a.instanceOf(C) ? "true" : "false"); // => "false"
```

#### Result

```
true
true
false
```
