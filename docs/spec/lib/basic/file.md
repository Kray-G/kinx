# class File

## Outline

File class is the class which reads and writes files and has static methods.
And also by `new File(filename, attr)` you can create an instance for a specific file as you specifyed.

### Static Methods

The static methods of `File` class is below.

|             Method              |              Outline              |         Return Value(Type)         |    Arguments    |              Meaning               |
| ------------------------------- | --------------------------------- | ---------------------------------- | --------------- | ---------------------------------- |
| `File.load(path)`               | Read all contents of a text file. | String                             | path: String    | File path to be read.              |
| `File.mkdir(path)`              | Make a directory.                 | 1: Success                         | path: String    | Directory path to be created.      |
| `File.rename(oldname, newname)` | Change a file name.               | 1: Success                         | oldname: String | File path before changed.          |
|                                 |                                   |                                    | newname: String | File path after changed.           |
| `File.unlink(path)`             | Remove a file.                    | 1: Success                         | path: String    | File path to be removed.           |
| `File.exists(path)`             | Check if a file exists.           | 1: Exists                          | path: String    | File path to be checked.           |
| `File.isDirectory(path)`        | Check if it is a directory.       | 1: The file is directory.          | path: String    | File path to be checked.           |
| `File.isSymlink(path)`          | Check if it is a symbolic link.   | 1: The file is symbolic link.      | path: String    | File path to be checked.           |
| `File.filesize(path)`           | Return a file size.               | Integer                            | path: String    | File path to be checked.           |
| `File.filedate(path)`           | Return a date and time of a file. | `{ modified, accessed, creation }` | path: String    | File path to be checked.           |
| `File.setFiledate(path, obj)`   | Set a date and time of a file.    |                                    | path: String    | File path to be checked.           |
|                                 |                                   |                                    | obj: Object     | `{ modified, accessed, creation }` |

### File Instance

An instance of the `File` is created by `new`.
Here is an example.

```javascript
var f = new File(filename, attr);
```

The following parameters are passed to a constructor.

| Parameter |       Values       |   Meaning   |
| --------- | ------------------ | ----------- |
| filename  | String             | File name   |
| attr      | `File.READ`        | Readable    |
|           | `File.WRITE`       | Writable    |
|           | `File.APPEND`      | Append mode |
|           | `File.TEXT`        | Text mode   |
|           | `File.BINARY`      | Binary mode |

*   The followins are how to use attributes to open file.
    *   `File.READ|File.APPEND`... Readable and Append mode.
    *   `File.READ|File.WRITE` ... Readable and Writable, and the file will be newly created.
    *   `File.READ|File.TEXT`  ... Read only with Text mode.

A `File` instance has following methods.

|        Method        |             Outline              |      Return Value(Type)      |  Arguments  |                Meanning                |
| -------------------- | -------------------------------- | ---------------------------- | ----------- | -------------------------------------- |
| `f.load()`           | Read all contents of a file.     | String                       |             |                                        |
| `f.close()`          | Close a file.                    |                              |             |                                        |
| `f.readLine()`       | Read a line.                     | String, 0: EOF               |             |                                        |
| `f.peek(ms)`         | Check if there is an input.      | 1: Exists, 0: Not exists     | ms: Integer | Timeout in milliseconds.               |
| `f.getch()`          | Read a character.                | Integer as a character code. |             |                                        |
| `f.putch(ch)`        | Put a character.                 |                              | ch: Integer | Integer as a character code to output. |
| `f.print(...args)`   | Output a string without newline. | Output count: Integer        | ...args     | Items to be output.                    |
| `f.println(...args)` | Output a string with newline.    | Output count: Integer        | ...args     | Items to be output.                    |

### File.open()

If you create an instance of `File` class, you have to do `close` at the end.
GC will automatically close a file, but it can not be controlled a moment of closing.
`File.open` method is useful when you want to close the file after exiting a scope.

Here is an example.

```javascript
File.open("README.md", File.READ, &(f) => {
    var l, n = 0;
    while ((l = f.readLine()).isString) {
        System.println("%4d: %s" % (++n) % l);
    }
});
```

`File.open` implementation is almost same as below.

```javascript
function FileOpen(filename, attr, func) {
    var f = new File(filename, attr);
    try {
        return func(f);
    } finally {
        f.close();
    }
}
```

## Examples

### Example 1. Static methods (1)

#### Code

```
File.mkdir("TEMPTESTDIR");
System.println(File.isDirectory("TEMPTESTDIR"));
```

#### Result

```
1
```

### Example 2. Static methods (2)

#### Code

```
File.rename("TEMPTESTDIR", "TEMPTESTDIR2");
System.println(File.exists("TEMPTESTDIR"));
System.println(File.exists("TEMPTESTDIR2"));
```

#### Result

```
0
1
```

### Example 3. Static methods (3)

#### Code

```
for (var i = 0; i < 10; ++i) {
    File.open("TEMPTESTDIR2/test.txt", File.READ|File.WRITE|File.APPEND) { &(f)
        f.println("[%d] This is a sample file." % i);
    };
}
System.println(File.load("TEMPTESTDIR2/test.txt"));
```

#### Result

```
[0] This is a sample file.
[1] This is a sample file.
[2] This is a sample file.
[3] This is a sample file.
[4] This is a sample file.
[5] This is a sample file.
[6] This is a sample file.
[7] This is a sample file.
[8] This is a sample file.
[9] This is a sample file.
```

### Example 4. Static methods (4)

#### Code

```
File.open("TEMPTESTDIR2/test.txt", File.READ|File.TEXT) { &(f)
    var l, n = 0;
    while ((l = f.readLine()).isString && l.length() > 0) {
        System.println("* %2d: %s" % (++n) % l);
    }
};
```

#### Result

```
*  1: [0] This is a sample file.
*  2: [1] This is a sample file.
*  3: [2] This is a sample file.
*  4: [3] This is a sample file.
*  5: [4] This is a sample file.
*  6: [5] This is a sample file.
*  7: [6] This is a sample file.
*  8: [7] This is a sample file.
*  9: [8] This is a sample file.
* 10: [9] This is a sample file.
```

### Example 5. Static methods (5)

#### Code

```
System.println(File.exists("TEMPTESTDIR2/test.txt"));
File.remove("TEMPTESTDIR2/test.txt");
System.println(File.exists("TEMPTESTDIR2/test.txt"));
File.remove("TEMPTESTDIR2");
System.println(File.exists("TEMPTESTDIR2"));
```

#### Result

```
1
0
0
```

