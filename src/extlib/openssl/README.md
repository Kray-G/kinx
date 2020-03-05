# How to build OpenSSL

## OpenSSL

https://github.com/openssl/openssl

## How to Build

### Windows

> Needs Perl & NASM. Install those first.

1. Clone it.
    ```
    $ git clone https://github.com/openssl/openssl.git
    ```
2. Prepare `dist` folder.
    ```
    $ cd openssl
    $ mkdir dist
    ```
3. Configure it and generate `makefile`.
    ```
    $ perl Configure VC-WIN64A no-ssl3 --prefix=%CD%\dist --openssldir=%CD%\dist
    $ perl -pe "s/[-\/]MD/\/MT/g" makefile > sample.mak
    $ del makefile
    $ move sample.mak makefile
    ```
4. Make it.
    ```
    $ nmake -f makefile
    $ nmake -f makefile install
    ```

### Linux

1. Clone it.
    ```
    $ git clone https://github.com/openssl/openssl.git
    ```
2. Prepare `dist` folder.
    ```
    $ cd openssl
    $ mkdir dist
    ```
3. Configure it and generate `makefile`.
    ```
    $ ./config --prefix=`pwd`/dist --openssldir=`pwd`/dist "-Wl,-rpath,'\$\$ORIGIN'"
    ```
4. Make it.
    ```
    $ make
    $ make install
    ```
