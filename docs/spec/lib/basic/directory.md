# class Directory

## Outline

The `Directory` object will be used to traverse a directory/folder tree.
There are 2 methods below.

|            Methods             |                                    Outline                                     |
| ------------------------------ | ------------------------------------------------------------------------------ |
| `recursiveWalk(dir, callback)` | When finding a sub directory, it goes into that sub directoty.                 |
| `walk(dir, callback)`          | Even when finding a sub directory, it does **NOT** go into that sub directoty. |

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

## Examples

### Example 1. Display files (1) by `walk`

#### Code

```
Directory.walk("template/theme/standard") { &(name)
    System.println(name);
};
```

#### Result

```
template/theme/standard/installer.ico
template/theme/standard/installer.png
template/theme/standard/uninstaller.ico
template/theme/standard/uninstaller.png
template/theme/standard/wizard-uninst.bmp
template/theme/standard/wizard.bmp
```

### Example 2. Display files (2) by `walk`

#### Code

```
Directory.walk("template/theme") { &(name)
    System.println(name);
};
```

#### Result

```
template/theme/standard
```

### Example 3. Display files by `recursiveWalk`

#### Code

```
Directory.recursiveWalk("template/theme") { &(name)
    System.println(name);
};
```

#### Result

```
template/theme/standard
template/theme/standard/installer.ico
template/theme/standard/installer.png
template/theme/standard/uninstaller.ico
template/theme/standard/uninstaller.png
template/theme/standard/wizard-uninst.bmp
template/theme/standard/wizard.bmp
```
