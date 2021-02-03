
# Getopt - `System.getopt`

## Overview

### How to use

Look at an example below. You put it in the while condition part,
and specify the array of argument, the option string,
and the object for long options.
You can omit to specify the object for long options.

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

### Option String

* If you specify the option with an argument but there is no argument to the option, ArgumentException will be raised.
* When it is an option without an argument, the options can be combine within one option like `-df` instead of `-d -t`.
* When it is an option with an argument, you can combine the option and the argument like `-aARG`. This means it is same as `-a ARG`.
* By above mechanism, you can write `-d -a ARG` as either `-da ARG` or `-daARG`.

### Long Option

* If you specified a long option with the option character of an option string, the argument style is following an option string parameter.
* If you specify the option with an argument but there is no argument to the option, ArgumentException will be raised.
* The argument for a long option is specified as the style of `--long-option=argument`. When it is a long option, the empty argument is also acceptable. 

## Examples

### Example 1. Option Pattern (1)

#### Code [args ->  -d -a arg]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
-d
-a with "arg"
Program options: ["test.kx"]
```

### Example 2. Option Pattern (2)

#### Code [args -> -da arg]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
-d
-a with "arg"
Program options: ["test.kx"]
```

### Example 3. Option Pattern (3)

#### Code [args -> -daarg]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
-d
-a with "arg"
Program options: ["test.kx"]
```

### Example 4. Option Pattern (4)

#### Code [args -> --help something]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
--help
Program options: ["test.kx", "something"]
```

### Example 5. Option Pattern (5)

#### Code [args -> --do-check=]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
--do-check with ""
Program options: ["test.kx"]
```

### Example 6. Option Pattern (6)

#### Code [args -> --do-check=abc]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
--do-check with "abc"
Program options: ["test.kx"]
```

### Example 7. Option Pattern (7)

#### Code [args -> -a]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
Uncaught exception: No one catch the exception.
ArgumentException: Needs an argument for -a
Stack Trace Information:
        at <main-block>(test.kx:2)
```

### Example 8. Option Pattern (8)

#### Code [args -> --unknown]

```javascript
var opt, add, check, list = [];
while (opt = System.getopt($$, "a:df", { add: 'a', delete: 'd', help: null, "do-check": '=' })) {
    switch (opt.type) {
    case 'a':               // Returns 'a' when a user specified '--add'.
        add = opt.arg;      // ':' means the option has an argument.
        System.println('-a with "%{add}"');
        break;
    case 'd':               // Returns 'd' when a user specified '--delete'.
        System.println('-d');
        break;
    case 'f':               // This means that a user specified '-f'.
        System.println('-f');
        break;
    case 'help':            // This means that a user specified '--help'.
        System.println('--help');
        break;
    case 'do-check':        // This means that a user specified '--do-check'
        check = opt.arg;    // '=' means the option has an argument.
        System.println('--do-check with "%{check}"');
        break;
    case '-':               // This means that the argument is not an option.
        list.push(opt.arg);
        break;
    }
}

// Displaying arguments which is not an option.
System.println("Program options: ", list);
```

#### Result

```
Uncaught exception: No one catch the exception.
ArgumentException: Unknown option: --unknown
Stack Trace Information:
        at <main-block>(test.kx:2)
```
