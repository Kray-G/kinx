# How to build libxml2

## libxml2

https://github.com/GNOME/libxml2

## How to Build

### Windows

Here is the procedure to build with Visual Studio 2017 x64 version. And the compile option is `/MT` for static link.

1. Clone it.
    ```
    $ git clone https://github.com/GNOME/libxml2.git
    ```

2. build and install to dist directory.
    ```
    $ cd win32
    $ mkdir dist
    $ cscript configure.js compiler=msvc iconv=no debug=no cruntime=/MT prefix=dist include=$(KINX)\src\extlib\zip\include lib=$(KINX)\src\extlib\zip\x64\vs2017
    $ nmake -f Makefile all install
    ```

This repository has `libxml2.lib` and `libxml2.dll`, which is built by Visual Studio 2017 x64 version. If you need it compiled by another compiler, follow the above procedure.

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/GNOME/libxml2.git
    ```

2. Build it.
    ```
    ./autogen.sh
    mkdir dist
    LDFLAGS="-Wl,-rpath,'\$\$ORIGIN'"  ./configure --with-zlib=/usr/local --with-pic --without-python --without-ftp --without-http --prefix=$(libxml2)/dist
    make
    make install
    ```

This repository has `libxml2.a`, which is built by gcc 7.4.0. If you need it compiled by another compiler, follow the above procedure.
