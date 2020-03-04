# How to build libxml2

## libxml2

https://github.com/GNOME/libxml2

## How to Build

### Windows

```
$ cd win32
$ mkdir dist
$ cscript configure.js compiler=msvc iconv=no debug=no cruntime=/MT prefix=dist include=$(KINX)\src\extlib\zip\include lib=$(KINX)\src\extlib\zip\x64\vs2017
$ nmake -f Makefile all install
```
