# Class

## Overview

`class` is a important part of object-oriented programming,
and here is the detail of how class works.

## Examples

### Simple Class

I guess sample is the best way to understand it.
Please look at the code below.

```coffee
class Example {

    # Private variable.
    var a_;

    # Public property.
    this.value = 10;

    # Private method.
    private getAimpl() { return a_; }

    # Public method.
    public getA() { return getAimpl(); }
    public setA(a) { a_ = a; }

    public calc(x) { return x + this.value; }
}

var instance = new Example();
System.println("init = ", instance.value, ", calc = ", instance.calc(100));
```

This code will be analyzed as below.

```js
Example.create = function() {

    var this;

    /* Private variable. */
    var a_;

    /* Public property. */
    this.value = 10;

    /* Private methods. */
    function getAimpl() { return a_; }

    /* public methods. */
    function getA() { return getAimpl(); }
    this.getA = getA;

    function setA(a) { a_ = a; }
    this.setA = setA;

    function calc(x) { return x + this.value; }
    this.calc = calc;

    return this;
};

var instance = Example.create();
System.println("init = ", instance.value, ", calc = ", instance.calc(100));
```

You can see below in the above code.

*   `new` operator is alias of the function call through `create` method.
*   There is a `this` object which can have public properties & public methods.
*   `this` object can be used in a private/public function.

The result of executing the above code is below.

```
init = 10, calc = 110
```

### Arguments to Constructor

Just specifying it as a variable list after class name like a function.
Here is an example below.

```coffee
class Example(initValue) {

    this.value = initValue;

    # ...

}

var instance = new Example(10);
```

### Inherit of Class

Use `:` after class name with arguments.
Here is an example below.

```coffee
class ExampleBase(initValue) {

    this.value = initValue;
    public method() { return this.value; }

    # ...

}

class Example(initValue1, initValue2) : ExampleBase(initValue1) {

    # ...
    public method() { return this.value + 100; } # Override the method.

}

var instance = new Example(10);
```

The above code is analyzed as below.

```js
ExampleBase.create = function(initValue) {

    var this;
    this.value = initValue;
    function method() { return this.value; }
    this.method = method;

    /* ... */

};

Example.create = function(initValue1, initValue2) {

    var this = ExampleBase.create(initValue1);
    var super = System.copyMethods(this);

    /* ... */
    function method() { return this.value + 100; }
    this.method = method; /* Override the function */

};

var instance = Example.create(10);
```

This means:

*   `this` object is constructed as `ExampleBase` class instance first.
*   Arguments can be passed to a constructor of a base class .
*   `super` object can be used due to use `ExampleBase` class methods.
*   As a public method is assigned to the property of `this`,
    overriding the method is done by overwriting the property's value.

### Others

#### `@` - alias of `this.`

For decreasing the count of writing `this`, you can use `@` as the alias of `this.`, which is `this` plus `.` (dot).
Here is a sample below.

```coffee
class Example(initValue) {

    @value = initValue;                 # This is same as `this.value = initValue;`.
    public method() { return @value; }  # This means also `@value` is same as `this.value`.

    # ...

}
```
