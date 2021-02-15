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
    $ perl Configure VC-WIN64A no-ssl3 --prefix=%CD%\dist --openssldir="C:\Program Files\Kinx\V1\ssl"
    ```
4. Replace `/MD` by `/MT` in `makefile`.
5. Replace `C:\\Git\\hub\\openssl\\dist\\lib` to `C:\\Program Files\\Kinx\\V1\\ssl\\lib`
6. Make it.
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
    $ ./config --prefix=/usr/bin/kinxlib/ssl --openssldir=/usr/bin/kinxlib/ssl "-Wl,-rpath,'\$\$ORIGIN'"
    ```
4. Make it.
    ```
    $ make
    $ make install
    ```
