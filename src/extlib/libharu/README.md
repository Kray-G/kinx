# How to build libharu

## libharu

https://github.com/libharu/libharu

## How to Build

### Windows

1. Clone it.
    ```
    $ git clone https://github.com/madler/zlib.git
    $ git clone https://github.com/glennrp/libpng.git
    $ git clone https://github.com/libharu/libharu.git
    ```
2. Build zlib.
    1. Change directory.
    ```
    $ cd zlib
    ```
    2. Modify `win32/Makefile.msc`, from `-MD` to `-MT`.
    3. Build it.
    ```
    $ nmake -f win32\Makefile.msc
    ```
    4. Copy the built library.
    ```
    $ copy zlib.lib ${kinx}/src/extlib/libharu/x64/vs2017/zlib_a.lib
    ```
2. Build libpng.
    1. Change directory.
    ```
    $ cd libpng
    ```
    2. Modify `scripts/Makefile.vcwin32`, from `-MD` to `-MT`.
    3. Build it.
    ```
    $ nmake -f scripts/Makefile.vcwin32
    ```
    4. Copy the built library.
    ```
    $ copy libpng.lib ${kinx}/src/extlib/libharu/x64/vs2017/libpng.lib
    ```
3. Build libharu.
    1. Change directory.
    ```
    $ cd libharu
    ```
    1. Modify `script/Makefile.msvc`, add `src\hpdf_encoder_utf.obj` to the `OBJS` list.
    2. Build it.
    ```
    $ nmake -f script/Makefile.msvc
    ```
    4. Copy the built library.
    ```
    $ copy libharu.lib ${kinx}/src/extlib/libharu/x64/vs2017/libharu.lib
    ```

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/glennrp/libpng.git
    $ git clone https://github.com/libharu/libharu.git
    ```
2. Build libpng.
    ```
    $ cd libpng
    $ mkdir dist
    $ LDFLAGS="-Wl,-rpath,'\$\$ORIGIN'" ./configure --prefix=`pwd`/dist --with-zlib-prefix=`$(minizip)`/dist/install/zlib --with-pic
    $ make
    $ make install
    $ cp dist/lib/libpng16.a cp libpng16.a ${kinx}/src/extlib/libharu/x64/gcc/libpng.a
    ```
3. Build libharu.
    ```
    $ cd libharu
    $ ./buildconf.sh
    $ mkdir dist
    $ LDFLAGS="-Wl,-rpath,'\$\$ORIGIN'" ./configure --prefix=`pwd`/dist --with-zlib=$(minizip)/dist/install/zlib --with-zlib=$(libpng)/dist --with-pic
    $ make
    $ make install
    $ cp dist/lib/libharu.a cp libpng16.a ${kinx}/src/extlib/libharu/x64/gcc/libharu.a
    ```
