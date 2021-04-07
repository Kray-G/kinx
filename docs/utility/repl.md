# REPL

## What is REPL?

REPL means Read-Eval-Print-Loop.
You can try some language functionality and it is a playground of easy to use with the language.
It is also termed an interactive terminal or language shell.

Look at the following demonstration for your easy understanding.

<p align="center"><img src="images/repl.gif" width="90%" /></p>

As seeing the above, you will understand you can try many things of the Kinx on the REPL.
Have fun with the REPL!

## Known issues

* Currently `namespace` is not supported.

## How to Use

### Starting REPL

Here is the command line option to start the REPL.

```
$ ./kinx --exec:repl
kinx[  0]> _
```

By the way, as you see the above demonstration, the some words are highlighted.
But note that there is no color in this document because it is written by Markdown.

### Small Example

Here is the small example of REPL.

```
$ ./kinx --exec:repl
kinx[  0]> "Hello, world"
=> "Hello, world"

kinx[  1]> System.println("Hello, world")
Hello, world
=> (null)

kinx[  2]> 3+2
=> 5

kinx[  3]> 3*2
=> 6

kinx[  4]> 3**2
=> 9

kinx[  5]> Math.sqrt(9)
=> 3

kinx[  6]> a = 3 ** 2
=> 9

kinx[  7]> b = 4 ** 2
=> 16

kinx[  8]> Math.sqrt(a+b)
=> 5
```

### Commnd List

The name of all commands is starting with `.`.

|        Command        |                                  Outline                                   |
| --------------------- | -------------------------------------------------------------------------- |
| `.help`               | Display this help.                                                         |
| `.quit`               | Quit REPL.                                                                 |
| `.history`            | Display command history.                                                   |
| `.vars`               | Display variables with its value.                                          |
| `.delete name`        | Delete a variable by name.                                                 |
| `.showdef name`       | Display function/class definition by name.                                 |
| `.cursor [*on/off]`   | Set to 'off' to make the cursor invisible.                                 |
| `.fullcode [on/*off]` | Set to 'on', and the code will be executed by .run instead of immediately. |
| `.time [on/*off]`     | Set to 'on' to measure and display elapsed time.                           |
| `.run`                | Execute the code only with .fullcode on.                                   |

By the way, also press `Ctrl-C` to quit the REPL. Please note it.

Input `.help`, you can see below.

```
kinx[  0]> .help
Kinx REPL Command: * means by default
    .help               Display this help.
    .quit               Quit REPL.
    .history            Display command history.
    .vars               Display variables with its value.
    .delete name        Delete a variable by name.
    .showdef name       Display function/class definition by name.
    .cursor [*on|off]   Set to 'off' to make the cursor invisible.
    .fullcode [on|*off] Set to 'on', and the code will be executed by .run instead of immediately.
    .time [on|*off]     Set to 'on' to measure and display elapsed time.
    .run                Execute the code only with .fullcode 1.

REPL Operation:
    [^] Arrow up        Choose a previous command.
    [v] Arrow down      Choose a next command.
    [<] Arrow left      Move cursor to left.
    [>] Arrow right     Move cursor to right.
    Ctrl+[<]            Move cursor to left by word.
    Ctrl+[>]            Move cursor to right by word.
    [DEL]               Delete character on cursor.
    [BS]                Delete previous character.
    [TAB]               Move to the next tab stop, or auto-complete.
```

Move the cursor by the left/right arrow key.
If you want to move the cursor by word, use a `Ctrl` + arrow key.
And to refer the history, use the up/down arrow key.

### Line Editor

Basically input by line editor, press [Enter] to evaluate and run it immediately.

```
kinx[  0]> 10 * 2
=> 20
```

### Auto detection of multiple lines and auto indent

Detecting `{` and `}` automatically, line editor will continue editing until the end of whole block.
When continuing the edit, the editor will automatically insert 4 spaces corresponding to the count of `{`.

But you can edit the current line only.
It means you can not edit the previous line.

Using this editor's functionality, you can define the `function`, `class`, and `module`.

```
kinx[  0]> function func(...a) {
    [  1]>     return a.reduce(&(r, e) => r + e);
    [  2]> }
=> function func
```

By the above definition, you can use the defined function as below.

```
kinx[  0]> function func(...a) {
    [  1]>     return a.reduce(&(r, e) => r + e);
    [  2]> }
=> function func

kinx[  3]> func(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
=> 55
```

If you want to see the function you defined, use `.var` or `.showdef` command.

```
kinx[  4]> .vars
function func(...a)

kinx[  5]> .showdef func
function func(...a) {
    return a.reduce(&(r, e) => r + e);
}
```

### Autocomplete

You can use autocomplete by `[TAB]` key for commands and keywords.
The words which is autocompleted is shown with light gray.

See the demonstration on the top of this document for the work of autocomplete details.

In this situation, the candidate word is changed by pressing `[TAB]`.
And you can do some actions by the following keys.

* Input the character ... Cancelling the autocomplete once and adding an input character to a previous string.
* Blank or symbol character... Using a current candidate and adding an input character after that.
* `[BS]` or `[DEL]` key ... Using a current candidate and stay a cursor position.
* `[Enter]` key ... Using the current candidate and executing it immediately.

The candidate word by autocomplete will be changed by the context.
For example, if the object is assumed to the Array by history, the methods of Array will be displayed as a candidate.
And also, when the target variable is the instance created by `new` operator, the class methods will be displayed as a candidate.

You can see a part of this behaviour at the demonstration above of this document.

### Variable List

You can see the list of variables by `.var` command.
The name like variable name, function name and class name is shared then you can not use the same name for those. It will be overwritten by the last definition.

Here is the example.

```
kinx[ 20]> .vars
class Sample(...a)
a = 10
b = 20
c = 30
d = 40
e = 50
f = 60
g = 70
sample = new Sample(a, b, c, d, e, f, g)
```

### Deleting a variable

You can delete the registered variable.
It is a rare case to use this functionality, but sometimes it helps you.
For example, there is a situation below.

```
...(continuing above example)
kinx[ 25]> .delete g      // Deleting `g`
kinx[ 26]> sample.sum()   // Invalid `sample` instance because of deteled `g`
=> Error: Compile Error.

kinx[ 27]> .vars
class Sample(...a)
a = 10
b = 20
c = 30
d = 40
e = 50
f = 60
sample = new Sample(a, b, c, d, e, f, g)  // <- Invalid because 'g' is missing.

kinx[ 28]> g = 60         // Try to set 'g' but can't!
=> Error: Compile Error.

kinx[ 29> .delete sample  // Delete the root cause of Compile Error.
kinx[ 30]> g = 60         // Successful to set 'g'
=> 60

kinx[ 31]> var sample = new Sample(a, b, c, d, e, f, g)  // Assign `sample` again from history.
=> (null)

kinx[ 32]> sample.sum() // Execution is okay with the new `g'
=> 270
```

### Display the function/class/module definition

The name like function name can be displayed by `.vars` command, but not displaying a definition of the body.
If you want to see the function, class, or module body, use `showdef` command.

```
kinx[ 33]> .showdef Sample
class Sample(...a) {
    @value = a;
    public sum() {
        return @value.reduce(&(r, e) => r + e);
    }
}
```

### History

You can see the history by `.history` command.
Here is the example of history.

    [  0]: class Sample(...a) {
    [  1]:     @value = a;
    [  2]:     public sum() {
    [  3]:         return @value.reduce(&(r, e) => r + e);
    [  4]:     }
    [  5]: }
    [  6]: a = new Sample(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
    [  7]: .vars
    [  8]: System.println(a.sum());
    [  9]: a = 10
    [ 10]: b = 20
    [ 11]: c = 30
    [ 12]: d = 40
    [ 13]: e = 50
    [ 14]: f = 60
    [ 15]: g = 70
    [ 16]: .vars
    [ 17]: var sample = new Sample(a, b, c, d, e, f, g)
    [ 18]: sample.sum()
    [ 19]: .vars
    [ 20]: sample.sum()
    [ 21]: .showdef System
    [ 22]: .showdef Sample
    [ 23]: .vars
    [ 24]: sample.sum()
    [ 25]: .delete g
    [ 26]: sample.sum()
    [ 27]: .vars
    [ 28]: g = 60
    [ 29]: g = 60
    [ 30]: .vars
    [ 31]: .delete sample
    [ 32]: g = 60
    [ 33]: var sample = new Sample(a, b, c, d, e, f, g)
    [ 34]: sample.sum()
    [ 35]: .history

You can also use `!` with the history number to execute the line by selecting the line from the history.

```
kinx[ 36]> !34
=> "sample.sum()"
=> 270
```

And also you can use an up/down arrow key to select the line from the history.

### Measurement of Elapsed Time

When using `.time on`, the REPL will display an elapsed time after executing the line.
It is just an elapsed time between the start and the end of `eval()`, so it includes some overhead time. But you will be able to use it as a roughly estimate.

```
kinx[  0]> native fib(n) {
    [  1]>     return n if (n < 3);
    [  2]>     return fib(n-2) + fib(n-1);
    [  3]> }
=> native:int fib

kinx[  4]> .time on
.time: on

kinx[  5]> fib(39)
=> 102334155

elapsed:    1.238 s

kinx[  6]> fib(34)
=> 9227465

elapsed:    0.131 s
```

### Full Code Mode

By using `.fullcode on`, REPL done not execute the line immediately by pressing `[Enter]`.
You have to use `.run` command to execute the code.
But now you can **NOT** register the variable, the class definition, the function definition, and so on.
You can execute the code only the spot on it, and no information will be recorded.

Look at the example below and you will see no information was shown by `.vars` command.

```
kinx[  0]> .fullcode on
.fullcode: on

kinx[  1]> class Something() {
    [  2]>         public println(...a) {
    [  3]>                 System.println(a);
    [  4]>         }
    [  5]> }
    [  6]> s = new Something();
    [  7]> s.println(1, 2, 3, 4, 5, 6, 7, 8);
    [  8]> .run
[1, 2, 3, 4, 5, 6, 7, 8]
=> {"s":null}

kinx[  9]> .vars

kinx[ 10]>
```

### Load Extrnal File

To load an external file, use `.load` command with the name.
This is used also for the file which is loaded by `using` usually in the script.
By loading the file by `.load`, you can use the method name for the class instance with autocomplete.

For example, please look at the example of `DateTime`.

```
kinx[  0]> .load DateTime
=> Successfully loaded.

kinx[  1]> var dt = new DateTime(2020, 1, 1, 9, 30, 0)
=> (null)

kinx[  2]> .vars
dt = new DateTime(2020, 1, 1, 9, 30, 00)

kinx[  3]> dt.weekday()
=> 3

kinx[  4]> System.println(dt)
2020/01/01 09:30:00
```

The file name to be searched will be `DateTime.kx` for `DateTime`.
`kx` is automatically added for the name if the file name don't ends with `.kx`.

The search path is as below order.
Because of this search path, the standard library of Kinx can be loaded.

1. Current directory.
2. `lib` directory under the folder holding `kinx` executable.
3. `lib/std` directory under the folder holding `kinx` executable.
4. `../lib` directory from the folder holding `kinx` executable.
5. `kinxlib` directory under the folder holding `kinx` executable.
6. `kinxlib/std` directory under the folder holding `kinx` executable.

> Sorry about v0.9.2 pre-release module, the search path of 5 and 6 is not implemented yet. Those search path is needed for Linux. Therefore you can **NOT** use `.load DateTime` with v0.9.2 on Linux.
> As a workaround, you can use `.load /usr/bin/kinxlib/std/DateTime` on Linux. Sorry for inconvenience.

But about DateTime, there are 2 restrictions now.
I will improve those in the future version.

* Currently you can create `DateTime` object without `new` operator. But if you want to use autocomplete to the instance of `DateTime` class, you have to create it with `new` operator.
* `new DateTime()` will create the instance of the current date and time. But REPL will instanciate it each exection, so the date and time has been changed each execution.

### East Asian Width

Kinx REPL is now supporting UTF8 input. The move of cursor will follow the character width defined by East Asian Width.
The following is the example of UTF8 characters in Japanese.

```
$ ./kinx --exec:repl
kinx[  0]> a = "あいうえおｱｲｳｴｵ";
=> "あいうえおｱｲｳｴｵ"

kinx[  1]> System.println(a);
あいうえおｱｲｳｴｵ
=> (null)

kinx[  2]> a = "あいうおｱｲｴｵ";  // Press [DEL] on the `ｳ`, and press [BS] on the `お`.
=> "あいうおｱｲｴｵ"

kinx[  3]> System.println(a);
あいうおｱｲｴｵ
=> (null)
```
