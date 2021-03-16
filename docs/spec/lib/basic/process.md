# class Process

## Overview

### using Process

The Process library is not built-in, so it is explicitly loaded using the `using` directive.

```javascript
using Process;
```

### class Process

#### Exec

Create a Process object with `new Process(command, opts)`. The argument is a command name and an array of arguments, or a command string. In the case of an array, it is like passing arguments separately, and in the case of a command line character string, it is analyzed internally and automatically decomposed into an array format.

* Array: for example, `["ls", "-1"]`.
* String: for example, `"ls -1"`.

The created process object has the following methods.

|   Method   |                                           Overview                                            |
| ---------- | --------------------------------------------------------------------------------------------- |
| `run()`    | Starts the process.                                                                           |
| `launch()` | Starts the process and detaches it.                                                           |
| `std()`    | Returns the options passed as arguments. <br/>`{ in: opts.in, out: opts.out, err: opts.err }` |

Not done yet only with created a new object. It is started when `run()` or `launch()` is executed. `run()` returns an object of the `ProcessController` class.

##### Run

By doing `run()`, an object of `ProcessController` class is returned.

```javascript
var p = new Process(["cmd","arg1"]).run();
```

##### Launch

`launch()` returns nothing (or returns null). This is the method of not taking care of the child after starting.

```javascript
new Process(["cmd","arg1"]).launch();
```

### class ProcessController

The `ProcessController` class returned by `run()` has the following methods.

|   Method    |                                                    Outline                                                      |
| ----------- | --------------------------------------------------------------------------------------------------------------- |
| `isAlive()` | true if the process is alive, false if it has already exited, or false after being `detach`                     |
| `wait()`    | Waits for the end of the process, and then returns the exit code of the process. After `detach`, 0 is returned. |
| `detach()`  | Detaches the process                                                                                            |

`detach()` is to detach the process after starting it. On Linux, the operation is slightly different from when detached with `launch()`, but the thing I want to do is the same. On Windows, the internal operation is the same.

On Linux, it is detached by the so-called **double-fork** method in order to detach it at process startup, but this can only be used at process startup. It is practically impossible to detach it after the process is started, and the child will survive as a zombie unless it is properly `wait` or `waitpid` in the parent process.

So, at the moment of doing `detach()`, I start a thread just for `waitpid` and take care of the child until death.

By the way, double-fork on Linux is...

* When the parent process dies, the child process will be connected to the init process and the init process will do `wait` for that child.

By using the functionality of init above, you can fork again from the process that was once forked, then by quickly terminating the first forked process and let init manage the grandchild process.

The top parent process must not forget the `waitpid` for the child that first forked. The grandchild is the target what you let the init process take care of.

#### Wait

An example of waiting for the end and acquiring the end code is as follows.

```javascript
var p = new Process(["cmd", "arg1"]).run();
var status = p.wait();
```

If you are doing `detach`, you cannot get it (0 is returned).

#### Detach

It has been already described but it is a `detach`.
The process can also be `detach` (detached).
If doing a detach, the communication with the child will be cut.
You don't have to wait and wait for the end.
Or rather, you can't do it even if you want to care.

```javascript
var p = new Process(["cmd", "arg1"]).run();
p.detach();
```

### class Pipe

It is about the pipe. The main purpose of making `Process` is a pipe. The most desired function is that you can freely connect standard input/output with child processes to a pipe to exchange information.

Specify the pipe with `opts` of `new Process(cmd, opts)`. The following three types of parameters are available.

| Parameter |                                                   Outline                                                   |
| --------- | ----------------------------------------------------------------------------------------------------------- |
| `in`      | Specify standard input. <br /> Can specify a pipe object, character string, or `$stdin`                  |
| `out`     | Specify standard output. <br /> Can specify a pipe object, string, `$stdout`, or `$stderr`             |
| `err`     | Specifies the standard error output. <br /> Can specify a pipe object, string, `$stdout`, or `$stderr` |

* Pipe object ... An object for using a pipe. Details will be described later.
* Character string ... Input source, output destination file as file name.
* `$stdin`, `$stdout`, `$stderr` ... Bind the input source and output destination of the child process to the standard input/output of this proocess.

#### Pipe object

Create a pipe object with `new Pipe()`, and it returns an array of two objects, `[Read, Write]`. The pipe object has the following methods.

Normally, specify the `Write` pipe as the `out` or `err` of the child process, and read from the `Read` pipe.

##### Read Pipe

Close the pipe after doing `run()` because it is set after doing `run()`.

|  Method   |                                             Outline                                              |
| --------- | ------------------------------------------------------------------------------------------------ |
| `peek()`  | Returns 0 if there is no data in the pipe, and a number greater than 0 if there. -1 is an error. |
| `read()`  | Gets all pipe data as a string. If there is no data, it returns an empty string.                 |
| `close()` | Closes the pipe.                                                                                 |

##### Write Pipe

Close the pipe after doing `run()` because it is set after doing `run()`.

|    Method     |                                            Outline                                            |
| ------------- | --------------------------------------------------------------------------------------------- |
| `write(data)` | Writes data to the pipe. When not all can be written, the number of written bytes will be returned. |
| `close()`     | Closes the pipe.                                                                              |

##### Pipe Example

The general form is as follows.

```javascript
using Process;

var [r1, w1] = new Pipe();
var p1 = new Process([ "ls", "-1" ], {out: w1 }).run();
w1.close(); // You can close it as it is no longer used
while (p1.isAlive() || r1.peek() >0) {
    var buf = r1.read();
    if (buf.length() <0) {
        System.println("Error...");
        return -1;
    } else if (buf.length()> 0) {
        System.print(buf);
    } else {
        // System.println("no input...");
    }
}
System.println("");
```

When using Write Pipe on the parent process side, it looks like this.

```javascript
using Process;

// stdin read from pipe and output to standard output
[r1, w1] = new Pipe();
var p1 = new Process("cat", {in: r1, out: $stdout }).run();
r1.close(); // You can close it as it is no longer used

// send to stdin of p1
var nwrite = w1.write("Message\n");
w1.close(); // Pipe close, transmission end

p1.wait();
```

By the way, this way you can control the standard output and standard error output.

```javascript
new Process("cmd", {out: $stdout, err: $stdout }); // merge standard error output to standard output
new Process("cmd", {out: $stderr, err: $stderr }); // join standard output to standard error output
new Process("cmd", {out: $stderr, err: $stdout }); // swap
```

### Process.pipeline

Since connecting pipes is a rather troublesome work (in other words, which one is `read`...?), I also defined a `Process.pipeline` that does all at once. Put a callback function at the end and use it as follows.

```javascript
var r = Process.pipeline(cmd1, cmd2, cmd3/* , ... */) { &(i, o, pipeline):
    // i ... write pipe to stdin for first command
    // o ... read pipe from stdout of last command
    // pipeline ... pipeline object
    // pipeline.input ....... same as i above
    // pipeline.output ...... same as o above
    // pipeline.peek() ... same as pipeline.output.peek()
    // pipeline.read() ... same as pipeline.output.read()
    // same as pipeline.write() ..... pipeline.input.write()
    // pipeline.isAlive() ... true if any process in the pipeline is alive
    // pipeline.wait() ......waits for all processes in the pipeline to complete,
    // return the exit code as an array

    // The return value of the callback becomes the return value of Process.pipeline() as it is.
    return pipeline.wait();
};
```

The last block is a callback function. This can be included in the arugument as the last parameter as follows. But I added this separated syntax by requested recently.

```javascript
var r = Process.pipeline(cmd1, cmd2, cmd3/* , ... */, &(i, o, pipeline) => {
    ...
});

// or

var r = Process.pipeline(cmd1, cmd2, cmd3/* , ... */, function(i, o, pipeline) {
    ...
});
```

It can be used even without calling back.

```javascript
var pipeline = Process.pipeline(cmd1, cmd2, cmd3 /* , ... */);
// pipeline ... pipeline object
// omitted the same information.
```

## Examples

### Example 1. Normal case

#### Code

```javascript
using Process;
var cmd = "echo examples/fib.kx";
var p = new Process(cmd, { out: $stdout }).run();
p.wait();
```

#### Result

```
examples/fib.kx
```

### Example 2. Getting as a string

#### Code

```javascript
using Process;

var [r1, w1] = new Pipe();
var p1 = new Process([ $kinxpath / "kinx", "-h" ], { out: w1 }).run();
w1.close(); // You can close it as it is no longer used

var str;
while (p1.isAlive() || r1.peek() > 0) {
    var buf = r1.read();
    if (buf.length() < 0) {
        System.println("Error...");
        return -1;
    } else if (buf.length() > 0) {
        str += buf;
    } else {
        // System.println("no input...");
    }
}

System.println(str.split(/\r?\n/).filter({ => _1.find("kinx") < 0 }).join("\n"));
```

#### Result

```
Main options:
    -h      Display this help.
    -c      Check the syntax only.
    -d      Dump compiled code.
    -D      Display AST.
    -u      Use UTF8 in standard I/O without converting. (Windows only)
    -q      Quiet mode in compiling.
    -i      Input source code from stdin.
    -v, --version
            Display the version number. --version shows also a detail.
    --debug Run the script with a debugger mode.
    --dot   Display the dump by .dot format.
    --exec:spectest
            Run SpecTest based on .spectest file under the current directory.
    --exec:repl
            Run the REPL. This is more useful than -i, and friendly with UTF8.
    --with-native
            Use this with -d to dump a compiled native function.
    --native-call-max-depth
            Specify the max depth to call a native function. 1024 by default.
```
