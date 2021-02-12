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
    $ perl Configure VC-WIN64A no-ssl3 --prefix=$(openssl)\dist --openssldir=C:\kinx\lib\ssl
    ```
4. Replace `/MD` by `/MT` in `makefile`.
5. Make it.
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
    $ sudo mkdir -p /usr/bin/kinxlib/ssl
    ```
3. Configure it and generate `makefile`.
    ```
    $ ./config --prefix=$(openssl)/dist --openssldir=/usr/bin/kinxlib/ssl "-Wl,-rpath,'\$\$ORIGIN'"
    ```
4. Make it.
    ```
    $ make
    $ make install
    ```
