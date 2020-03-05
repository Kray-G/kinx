# How to build OpenSSL

## libCurl

https://github.com/curl/curl

## How to Build

> You must build OpenSSL & Minizip first.

### Windows

1. Clone it.
    ```
    $ git clone https://github.com/curl/curl.git
    ```
2. Do `buildconf.bat`.
    ```
    $ cd curl
    $ buildconf.bat
    ```
3. Make it.
    ```
    $ cd winbuild
    $ Set RTLIBCFG=static
    $ nmake /f MakeFile.vc mode=static DEBUG=no WITH_SSL=dll WITH_ZLIB=dll ZLIB_PATH=$(minizip)\dist\install\zlib SSL_PATH=$(openssl)\dist WITH_PREFIX=%CD%\dist MACHINE=x64
    ```

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/curl/curl.git
    ```
2. Do `buildconf`.
    ```
    $ cd curl
    $ ./buildconf
    ```
3. Make it.
    ```
    $ mkdir dist
    $ LDFLAGS="-Wl,-rpath,'\$\$ORIGIN'" ./configure --prefix=`pwd`/dist --with-zlib=/home/kazuya/github/minizip/dist/install/zlib --with-ssl=/home/kazuya/github/openssl/dist
    $ make
    $ make install
    ```
