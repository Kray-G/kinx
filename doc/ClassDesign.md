# Class Design

## Overview

`class` is an important part of object-oriented programming,
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
    var super = System.makeSuper(this);

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

#### `initialize` method

The class can have the method named as `initialize` for initialization.
By this method, you can write an initialization code at one place.

For example,

```coffee
class Example1 {
    private initialize() {
        @value = 100;
        System.println("This 'initialize' method is automatically called at the end of creating this instance.");
    }
}

var e1 = new Example1();
System.println("e1.value = ", e1.value);
```

The result is here.

```
This 'initialize' method is automatically called at the end of creating this instance.
e1.value = 100
```

Of cource, you can also do it without `initialize` method like this.

```coffee
class Example1 {

    @value = 100;

    public method() {
        /* ... */
    }

}
```

You can choose it as you like.

#### `instanceOf` method

The class instance has a `instanceOf` method automatically.
This method tests if it is the instance of the specified class.
It will be true even if the class is a parent one.

Here is an example.

```coffee
class Example1 {}
class Example2 : Example1 {}
class Example3 : Example2 {}

var e2 = new Example2();
if (e2.instanceOf(Example1)) System.println("e2 is the instance of Example1.");
if (e2.instanceOf(Example2)) System.println("e2 is the instance of Example2.");
if (e2.instanceOf(Example3)) System.println("e2 is the instance of Example3.");
```

The result is here.

```
e2 is the instance of Example1.
e2 is the instance of Example2.
```

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
