# class Directory

## Outline

The `Directory` object will be used to traverse a directory/folder tree.
There are 2 methods below.

|            Methods             |                                    Outline                                     |
| ------------------------------ | ------------------------------------------------------------------------------ |
| `walk(dir, callback)`          | Even when finding a sub directory, it does **NOT** go into that sub directoty. |
| `recursiveWalk(dir, callback)` | When finding a sub directory, it goes into that sub directoty.                 |
| `change(dir, callback)`        | Do something `callback` in `dir` directory.                                    |

### Directory.walk()

Here is generally how to display files stored under some folder.

```javascript
Directory.walk("src") { &(name)
    System.println(name);
};
```

### Directory.recursiveWalk()

Here is how to traverse folders recursively and to display found files all.

```javascript
Directory.recursiveWalk("src") { &(name)
    System.println(name);
};
```

### Directory.change()

Here is how to work in a secified directory.

```javascript
Directory.change("src") {
    // Work in "src" directory.
    System.println(name);
};
```

## Examples

### Example 1. Display files (1) by `walk`

#### Code

```
var result = [];
Directory.walk("build/template/theme/standard") { &(name)
    result.push(name);
};
result.sort().each { System.println(_1); };
```

#### Result

```
build/template/theme/standard/installer.ico
build/template/theme/standard/installer.png
build/template/theme/standard/uninstaller.ico
build/template/theme/standard/uninstaller.png
build/template/theme/standard/wizard-uninst.bmp
build/template/theme/standard/wizard.bmp
```

### Example 2. Display files (2) by `walk`

#### Code

```
var result = [];
Directory.walk("build/template/theme") { &(name)
    result.push(name);
};
result.sort().each { System.println(_1); };
```

#### Result

```
build/template/theme/standard
```

### Example 3. Display files by `recursiveWalk`

#### Code

```
var result = [];
Directory.recursiveWalk("build/template/theme") { &(name)
    result.push(name);
};
result.sort().each { System.println(_1); };
```

#### Result

```
build/template/theme/standard
build/template/theme/standard/installer.ico
build/template/theme/standard/installer.png
build/template/theme/standard/uninstaller.ico
build/template/theme/standard/uninstaller.png
build/template/theme/standard/wizard-uninst.bmp
build/template/theme/standard/wizard.bmp
```

### Example 4. Directory changes by `change`

#### Code

```
var path = $pwd;
var dirname = path.filename();
Directory.change("..") {
    var d = $pwd / dirname;
    System.println(d == path);
};
```

#### Result

```
1
```
