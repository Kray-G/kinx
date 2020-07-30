# How to build libssh2

## libssh2

https://github.com/libssh2/libssh2

## How to Build

### Windows

Here is the procedure to build with Visual Studio 2017 x64 version. And the compile option is `/MT` for static link.

1. Clone it.
    ```
    $ git clone https://github.com/libssh2/libssh2.git
    ```

2. Make `dist` directory and do cmake under `dist`.
    ```
    $ mkdir dist
    $ cd dist
    $ %CMAKE_ROOT%\bin\cmake -DCRYPTO_BACKEND=WinCNG -DBUILD_SHARED_LIBS=ON -DCMAKE_INSTALL_PREFIX=./dll -G "Visual Studio 15 2017 Win64" ..
    ```
   > You should download cmake ad set `CMAKE_ROOT` of environment variable.

3. Modify CMakeCache.txt to replace `/MD` by `/MT`, and rerun cmake with above options.

4. Build it at first.
    ```
    $ cmake --build . --target install
    ```

This repository has `libssh2.lib` and `libssh2.dll`, which is built by Visual Studio 2017 x64 version. If you need it compiled by another compiler, follow the above procedure.

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/libssh2/libssh2.git
    ```

2. Do `autoreconf -fi`.
    ```
    $ autoreconf -fi
    ```

3. Build it.
    ```
    mkdir dist
    LDFLAGS="-Wl,-rpath,'\$\$ORIGIN' -ldl -pthread" ./configure --with-pic --with-libz --with-libz-prefix=$(minizip)/dist/install/zlib --with-crypto=openssl --with-ssl=$(openssl)/dist --prefix=$(libssh2)/dist
    make
    make install
    ```

This repository has `libssh2.a`, which is built by gcc 7.4.0. If you need it compiled by another compiler, follow the above procedure.
