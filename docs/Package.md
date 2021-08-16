# Kinx Package

## Introduction

The package of Kinx is a sub module of Kinx features.
Its benefit is to add and to remove a new feature to the Kinx environment after installation.

The package system will make the Kinx more flexible, useful and extendable.

## Overview

This section describe about the package by a user perspective and a developper perspective.

### For Users

#### How To Install/Uninstall Package

To install the package you want to use, do it with `kip install` command.
Here is the example of installing a `typesetting` package.

```
$ kip install typesetting
[2021/08/07 14:23:12] Downloading the package typesetting(0.0.1) with 87423875 bytes.
[2021/08/07 14:23:12] from https://github.com/Kray-G/kinx-tiny-typesetting/releases/download/v0.0.1/package.zip
[2021/08/07 14:23:36] Received 87423875/87423875 (100%)
[2021/08/07 14:23:36] Created ********/typesetting0.0.1.zip done.
[2021/08/07 14:23:41] Extracted 268/268 (100%)
[2021/08/07 14:23:41] Set the latest version of typesetting to 0.0.1
[2021/08/07 14:23:41] Made the file of phantomjs executable
[2021/08/07 14:23:42] Generated a command of kxkitty.exe
```

To install the package you want to use, do it with `kip uninstall` command.
Here is the example of uninstall a `typesetting` package.

```
$ kip uninstall typesetting all
[2021/08/07 14:30:09] Removed an executable of kxkitty.exe
[2021/08/07 14:30:10] All versions of typesetting is successfully uninstalled
```

If you specified the installed version instead of `all`, you can uninstall the specified version only.

#### How To Use Package

To use the package module's library, use a `using` directive with `@` like the following.

```javascript
using @typesetting.Typesetting;
using @typesetting.reader.Markdown;
using @typesetting.style.Styles;
```

If you want to use the specific version, you can specify it as below.

```javascript
using @typesetting(0.0.2).Typesetting;
using @typesetting(0.0.2).reader.Markdown;
using @typesetting(0.0.2).style.Styles;
```

For the actual way to use the package, please see the document of each package.

### For Developpers

#### Package Directory Structure

The package is installed to the directory below.
This path will be called as `$PKGPATH` in this document.

```
$libpath/package/{package-key}/{package-version}
// For example:
//  $libpath/package/typesetting/0.0.2
```

The library search path is a `lib` directory under `$PKGPATH`.
For example, if you use the following code and the latest version of `typesetting` package is 0.0.2, the library code of `Typesetting` will be located to `$libpath/package/typesetting/0.0.2/lib/Typesetting.kx`

```javascript
using @typesetting.Typesetting;
```

Note that the latest version will be usually used if not specified the version.
However, if you specify the version and the library code is including other library code by `using` directive without specifying the version, then the specified version will be used instead of the latest version.

For example, when both the version 0.0.1 and 0.0.2 are installed, it will be as below.

```javascript
// When you write the following in your code.
//  using @typesetting.Typesetting;

// in Typesetting.kx
using @typesetting.Logger; // => use Logger.kx of the version 0.0.2 which is the latest.
```

```javascript
// When you write the following in your code.
//  using @typesetting(0.0.1).Typesetting;

// in Typesetting.kx
using @typesetting.Logger; // => use Logger.kx of the version 0.0.1 which you specified.
```

#### Install Your Package To Develop

You can use `kip devinst` command to instal your package as a development version.
For that, you must prepare the `build/build.kx` file to make the files locate to the correct location.

Here is the example which is used in the `typesetting` package.

```javascript
using pkg.Develop;

var pkgname = "typesetting";
var version = "0.0.2";

new PackageUpdater($$, pkgname, version).update { &(util)
    Directory.change("src") {
        Directory.walk(".") {
            // _1 will be `bin`, `etc` and `lib`.
            util.dircopy(_1, util.root / _1.filename());
        };
    };
    util.dircopy("docs", util.root / "docs");
};
```

The callback function is receiving `util` object and you can use it.
`util.root` is the root location of packages, which is located to `$libpath/package/typesetting/0.0.2` in this case.
It means the root directory is automatically created by your package name and versions.

In the `typesetting` package, the directories of `bin`, `etc`, and `lib` under `src` directory will be copied to the same name under the path under `uril.root`.
Besides, `docs` directory will be copied as is to the `docs` under the path of `util.root`.

You can install it correctly by running just `kip devinst` at the root of the package repository which has a `build` directory.
You can also uninstall it correctly by running just `kip devuninst` at the root of the package repository which has a `build` directory.

#### Special Directory

##### `bin`

If you locate the script file under the `bin` directory, the executable command will be automatically created to the same path as `kinx`.
For example, if you put the `something.kx` under the `bin`, `something.exe` will be automatically created.

Note that it will be `something` without `.exe` on Linux.
In this document, it is described as `something.exe` style because it is easy to understand.

##### `lib`

This `lib` directory is a search path of the package.
It means a root path when the library of the package is searched by `using`.
