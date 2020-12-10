# Kinx Object Reference

## File

`File` object is used to access a file.
`File` is a class, so the instance will be created by `new` operator.
But `File` object also has some static values and methods.
See below.

|           Method           |                                     Meaning                                     |
| -------------------------- | ------------------------------------------------------------------------------- |
| `f = new File(name, mode)` | Creates an instance.                                                            |
|                            | `name`: File name.                                                              |
|                            | `mode`: Bit-OR of the following values.                                         |
|                            | - `File.TEXT`, `File.BINARY`                                                    |
|                            | - `File.READ`, `File.WRITE`, `File.APPEND`                                      |
| `f.close()`                | Closes a file.                                                                  |
| `f.load()`                 | Reads an entire file. Internal file pointer will be rewind to the head.         |
| `f.readLine()`             | Reads a line from the current file pointer's position.                          |
| `f.eachLine(func)`         | `func` is callback.                                                             |
|                            | - `func`: `function(line:<String>, lineNo:<Integer>)`.                          |
| `f.print(...)`             | Prints a text to the file, converted if necessary, without a newline character. |
| `f.println(...)`           | Prints a text to the file, converted if necessary, with a newline character.    |

Here are static methods.

|            Method             |                                         Meaning                                         |
| ----------------------------- | --------------------------------------------------------------------------------------- |
| `File.open(name, mode, func)` | About `name` and `mode`, same as `new`. `func` is callback.                             |
|                               | - `func`: `function(f:<File>)`.                                                         |
| `File.load(filename[, mode])` | Loads an entire file. Internal file pointer will be automatically closed after loading. |
