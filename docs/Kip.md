# Kip - `kip Installs Packages`

## Introduction

Kip is a package manager of Kinx.
You can easily use a package by Kip.

Regarding the package of Kinx, see the [Package](Package.md) page for details.

## Overview

Kip has features below.

* Kip Configuration
* Central Repository Management
* Package Control

### Kip Configuration

You can setup the configuration and environment in order to use Kip by `Configuration` feature.

### Central Repository Management

Kip system will work by connected with a central repository which has a list of packages.
There is a default central repository and you can use Kip soon.
The default central repository is below, and you can see all standard packages there.

* https://github.com/Kray-G/kinx-package-repository

### Package Control

Kip can control packages like an installation, an uninstallation, or searching a package.

## How To Use

### Configuration

#### `kip confg set <name> <value>`

Set the `<value>` to the parameter specified by the `name`.

#### `kip confg remove <name>`

Remove the value which was set to the parameter specified by the `name`.

#### `kip confg show [<name>]`

Show the list of parameters with name and value.
If specified the `<name>`, it shows only that parameter.

### Available Parameters

Currently the following settings are available.

|       Name       |           Meaning            |             Example             |
| ---------------- | ---------------------------- | ------------------------------- |
| `proxy.url`      | URL of Proxy Server.         | `http://proxy.example.com:8080` |
| `proxy.username` | User name for the proxy.     | `username`                      |
| `proxy.password` | Password for the proxy user. | `password`                      |

### Central Repository Management

#### `kip repo add <url>`

Add the other central repository which you specified by `<url>`.
This feature will be used if you want to use your own repository.
For example, you think it is not a standard or in the case that you do not want to register your package to the default central repository.

#### `kip repo remove <url>`

Remove the repository which you specified by `<url>`.

Note that you can remove also a default central repository.
If you removed it, you should add it again.

#### `kip repo list`

Show the list of central repositories.
Moreover, it shows also the list of packages registered to each repository.

### Package Control

#### `kip search [<key>]`

Show the list of all packages.
If specified the `<key>`, it shows the package registered as `<key>` if exists.

> TODO: Searching packages with pattern matching.

#### `kip install <key> [<ver>]`

Install the package which you specified by the `<key>`.
If not specified the `<ver>`, it installs the latest version of the package.
If specified it, it installs the specified version of the package only.

#### `kip uninstall <key> <ver>|all`

Unnstall the package which you specified by the `<key>`.
The `<ver>` is necessary to uninstall the package, and it uninstalls the specified version of the package only.
If you want to uninstall all versions in the package, specify it as `all` instead of an actual version.

#### `kip devinstall`

Install a developing package which you are developing in progress.

You must move to the package repository root and you should prepare `build/build.kx` file in advance.
`build/build.kx` is the code to install the package like the following code for example.
This code is the stuff prepared in the `typesetting` package.

```javascript
using pkg.Develop;

var pkgname = "typesetting";
var version = "0.0.2";

new PackageUpdater($$, pkgname, version).update { &(util)
    Directory.change("src") {
        Directory.walk(".") {
            util.dircopy(_1, util.root / _1.filename());
        };
    };
    Directory.walk("docs") {
        util.dircopy(_1, util.root / _1);
    };
};
```

As you see, you can use `PackageUpdater` class and use `util.dircopy()` to install your developped components into the Kinx package directory.
The package name will be `typesetting-dev` when you install it like this.
The `-dev` postfix means this package is a developing package.
Therefore you can not use a `-dev` postfix to any package name.

By the way, you can uninstall it with normally `kip uninstall` command.
You can use just `kip uninstall typesetting-dev all` and uninstall it correctly.

#### `kip list`

Show the list of installed packages with installed versions.

#### `kip update [<key>]`

> **Not supported yet.**

Check if there are some updates, and update to the latest version if exists.

> TODO: Supporting this feature.
