# Zip

## Overview

### Zip archive creation

#### Create Zip Instance (`class Zip`)

Basically it looks like this.

```javascript
var zip = new Zip("zipfile.zip", File.READ|File.WRITE);
```

Specify the file name and mode.

##### Mode

|     Mode      |   Meaning   |                       Operation overview                                |
| ------------- | ----------- | ----------------------------------------------------------------------- |
| `File.READ`   | Read mode   | When specified alone and the file does not exist, throw `ZipException`. |
| `File.WRITE`  | Write mode  | Mode to create a new file even if it exists.                            |
| `File.APPEND` | Append mode | Appends to the file if it exists.                                       |

These are same as `File`.

##### Methods

The methods of the Zip instance are as follows.

|              Method              |                      Content                        |              Options               |
| -------------------------------- | --------------------------------------------------- | ---------------------------------- |
| `extract(name, [opts])`          | Extract and get it as a string.                     | `{ password, overwrite, skip, }`   |
| `extractTo(name, file [, opts])` | Extract to file.                                    | (same as above)                    |
| `find(name)`                     | Finds an entry and returns the entry object.        |                                    |
| `addFile(filename [, opts])`     | Adds an entry to the Zip file.                      | `{ password, method, aes, level }` |
| `addString(text [, opts])`       | Adds an entry to the Zip file.                      | (same as above)                    |
| `setPassword(password)`          | Sets the password that is used for all Zip entries. |                                    |
| `setOverwrite(truefalse)`        | Used to specify overwrite settings for all.         |                                    |

#### Add entry (`addFile()`/`addString()`)

Use `addFile()` or `addString()`. The entry is added immediately.

```javascript
zip.addFile("README.md");
```

If a directory name is given to the file, the files will be added as the files inside the directory. You can also pass an option as the second argument. The options are as follows.

* `password`: Password for the Zip with password. No default.
* `method`: Compression method. The default is `deflate`. In addition, you can specify `"store"`, `"bzip2"`, `"lzma"`.
* `aes`: Whether to enable WinZIP compatible AES encryption (true/false). Default false. It is ignored in the case of `addString`.
* `level`: Compression level. 0-9.

An example of adding options is as below.

```javascript
zip.addFile("README.md", {
    method: "bzip2",
    password: "password",
    aes: true,
});
zip.addString("test/test1.txt", {
    content: "test/test\n",
    // aes: true, // ignored by addString.
});
```

The password can be set separately for each entry if it is specified individually during extracting.

#### encryption

It can be specified as an option at the time of `addFile()`, but if you want to set it all at the beginning, you can use `setPassword()`.

```javascript
var zip = new Zip("zipfile.zip", File.READ|File.WRITE);
zip.setPassword("password");
```

### Display Zip file list

The `zip` instance already contains the entry objects as an array. A list can be displayed as follows. The number of entries is stored in `zip.totalFiles`.

```javascript
var zip = new Zip("zipfile.zip", File.READ);
System.println("totalFiles = ", zip.totalFiles);
zip.each(function(e) {
    System.println("%s:" % e.filename);
    e.keySet().each(&(key) => {
        if (e[key].isFunction || e[key].isObject || e[key].isUndefined) {
            return; // Skip a function, etc.
        }
        if (key == "crc32") { // CRC is in hex.
            System.println("    %-14s = %10X" % key % e[key]);
        } else if (key != "time" && key != "filename") { // Display in another.
            System.println("    %-14s = %10d" % key % e[key]);
        }
    });
    // time is a structure of an object.
    e.time.keySet().each(&(k) => {
        System.println("      time.%-7d = %10d" % k % e.time[k]);
    });
    // // Entry can be extracted for each.
    // if (e.filename == "README.md") {
    //     e.extractTo("READMEXX.md", { password: "text", overwrite: true });
    // }
});
```

It is displayed as below.

```
totalFiles = 4
README.md:
    compsize       =       4413
    size           =      11621
    isDirectory    =          0
    crc32          =   EFD9A09C
    isEncrypted    =          1
    method         =    deflate
      time.month   =          3
      time.minute  =          1
      time.day     =         19
      time.year    =       2020
      time.second  =          2
      time.hour    =         16
...
```

### Extract

There are two ways to extract the Zip file.

* Extract directly from a Zip instance.
* Extract from Zip entry object.

Extracting from a Zip entry is to do for each entry. In that case, there are two methods as follows.

* Iterating and selecting an entry.
* Using the `find` method to get directly your target entry.

The `find` method returns a Zip entry object if there is an entry with the specified filename.

The meanings of the options when extracting are as follows.

* `password`: Password to use for extraction. If not specified, the one set with `setPassword()` is used. If it is not set even with `setPassword()`, it tries to expand without a password.
* `overwrite`: Specify true and overwrite if a file with the same name already exists.
* `skip`: Specify true and skip if a file with the same name already exists.

If `overwrite` or `skip` is not specified and a file with the same name exists, a `ZipException` exception is thrown.

#### Extract all

To extract all, execute `extractTo` on the iterated entry. The necessary directories will be created automatically.

```javascript
zip.each(&(e) => e.extractTo("examples/zip/dst" / e.filename, {password: "text", skip: true }));
```

The string becomes a string joined with `/` when the `/` operator is applied to a string.

#### Specify the file and extract

You can use the `extract` or `extractTo` methods directly to the Zip instance.

```javascript
zip.extractTo("README.md", "READMEXX.md", {password: "text", skip: true });
```

If you use `extract`, it returns the extracted contents as a string.

```javascript
var text = zip.extract("README.md", {password: "text" });
```

For Zip entry objects, there are no arguments to specify the entry name.

|           Method           |             Content             |             Options              |
| -------------------------- | ------------------------------- | -------------------------------- |
| `extract([opts])`          | Extract and acquire as a string | `{ password, overwrite, skip, }` |
| `extractTo(file [, opts])` | Extract to file                 | (same as above)                  |

Here is an example using `find`.

```javascript
zip.find("README.md")
   .extractTo("READMEXX.md", {password: "text", skip: true });
```

```javascript
var text = zip.find("README.md")
              .extract({ password: "text" });
```

## Examples

### Example 1. Archive a file

#### Code

```javascript
File.remove("TEST.md");
File.remove("zipfile.zip");

var zip = new Zip("zipfile.zip", File.READ|File.WRITE);
zip.setPassword("password");

zip.addFile("README.md");

System.println("totalFiles = ", zip.totalFiles);
```

#### Result

```
totalFiles = 1
```

### Example 2. Listing an archived file

#### Code

```javascript
var zip = new Zip("zipfile.zip", File.READ);
zip.setPassword("password");
System.println("totalFiles = ", zip.totalFiles);
zip.each(function(e) {
    System.println("%s" % e.filename);
});
zip.find("README.md")
   .extractTo("TEST.md", { password: "password", skip: true });
if (File.exists("TEST.md")) {
    System.println("Successful");
    File.remove("TEST.md");
}
```

#### Result

```
totalFiles = 1
README.md
Successful
```

### Example 2. No password

#### Code

```javascript
var zip = new Zip("zipfile.zip", File.READ);
System.println("totalFiles = ", zip.totalFiles);
zip.each(function(e) {
    System.println("%s" % e.filename);
});
zip.find("README.md")
   .extractTo("TEST.md");
if (File.exists("TEST.md")) {
    System.println("Successful");
    File.remove("TEST.md");
}
```

#### Result

```
totalFiles = 1
README.md
Uncaught exception: No one catch the exception.
ZipException: Failed to extract the file(README.md) in zip file(zipfile.zip)
Stack Trace Information:
        at <main-block>(test.kx:7)
```
