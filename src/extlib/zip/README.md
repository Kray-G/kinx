# How to build minizip

## Minizip

https://github.com/nmoinvaz/minizip

## How to Build

### Windows

Here is the procedure to build with Visual Studio 2017 x64 version. And the compile option is `/MT` for static link.

1. Clone it.
    ```
    $ git clone https://github.com/zlib-ng/minizip-ng
    ```

2. Make `dist` directory and do cmake under `dist`.
    ```
    $ mkdir dist
    $ cd dist
    $ cmake -G "Visual Studio 15 2017 Win64" ..
    ```
   > You should download cmake ad set `CMAKE_ROOT` of environment variable.

3. Modify CMakeCache.txt to replace `/MD` by `/MT`, and set `MZ_LZMA` and `MZ_ZSTD` to `OFF`.

4. Reconfiguration & Build it at first.
    ```
    $ cmake -DCMAKE_INSTALL_PREFIX=.\install -G "Visual Studio 15 2017 Win64" ..
    $ msbuild /p:Configuration=Release ALL_BUILD.vcxproj
    ```

5. Move to zlib directory where is `../lib/zlib` from `dist`.

6. Build zlib first, or git clone will be done again.
    ```
    $ pwd
    dist
    $ cd ../lib/zlib
    $ mkdir dist
    $ cd dist
    $ cmake -G "Visual Studio 15 2017 Win64" ..
    ```

7. Modify CMakeCache.txt of zlib to replace `/MD` by `/MT` like above.
    ```
    $ cmake -DCMAKE_INSTALL_PREFIX=.\install\zlib -G "Visual Studio 15 2017 Win64" ..
    $ msbuild /p:Configuration=Release ALL_BUILD.vcxproj
    $ msbuild /p:Configuration=Release INSTALL.vcxproj
    ```

That is all.

This repository has `minizip.lib` and a necessary lib files like `zlib.lib`, which is built by Visual Studio 2017 x64 version.
If you need it compiled by another compiler, follow the above procedure.

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/nmoinvaz/minizip
    ```

2. Install the following packages if needed.
    ```
    $ sudo apt install pkg-config
    $ sudo apt install pkgconf
    ```
3. Make `dist` directory and do cmake under `dist`.
    ```
    $ mkdir dist
    $ cd dist
    $ cmake ..
    ```

That is all.

This repository has `libminizip.a`, which is built by gcc 7.4.0. If you need it compiled by another compiler, follow the above procedure.

