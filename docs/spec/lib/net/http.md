# class Http

## Overview

This is a network library of http connection.
Supported HTTP methods are GET, POST, PUT, and DELETE by default.
And also you can use a custom method by `request` interface.

### libcurl

This is based on the libcurl library.
As you know, libcurl library is supporting a lot of network interface.
This `Http` class is one of implementation with libcurl.
There is currently no other implementation with libcurl, but it is planned to be added one by one.

### Interfaces

|                Name                |                                            Content                                             |
| ---------------------------------- | ---------------------------------------------------------------------------------------------- |
| `sslVerifyPeer(tf)`                | Enable or disable of verifying the peer's SSL certificate.                                     |
| `sslVerifyHost(verify)`            | Enable or disable of verifying the certificate name against host.                              |
| `sslSetCaInfo(path)`               | Sets a path to Certificate Authority (CA) bundle.                                              |
| `sslSetCaPath(path)`               | Specifies a directory holding CA certificates.                                                 |
| `setDebugDetail(tf, opts)`         | Enable or disable a detail mode in debug. Hex dump will be shown when `opts.hex` is true.      |
| `setUserPassword(user, pass)`      | Sets a username and a password for authentication.                                             |
| `setProxy(url)`                    | Sets a proxy URL.                                                                              |
| `setProxyPort(port)`               | Sets a proxy port number.                                                                      |
| `setProxyUserPassword(user, pass)` | Sets a username and a password for proxy.                                                      |
| `setTimeout(millisec)`             | Sets a timeout in millisec.                                                                    |
| `setDebug(callback)`               | Sets a callback function for debug. `callback` will be called with an argument of `debugInfo`. |
| `addHeader(key, value)`            | Adds a HTTP header by a key and a value.                                                       |
| `removeHeader(key)`                | Removes a specified key from a header.                                                         |
| `setRedirect(tf, opts)`            | Enable or disable a redirect. `opts.max` is available to limit the number of redirection.      |
| `setPostData(data)`                | Sets data of POST.                                                                             |

## Some Examples

### GET

Here is an example of HTTP GET method.

```javascript
var http = new Net.Http();

# http.setDebugDetail(true, { hex: false });
# http.setDebug(&(info) => {
#     System.println("DBG> ", info);
# });

function get(http, url) {
    System.println("URL = %{url}");
    http.addHeader("X-Hook-K1", "What is this?");
    http.addHeader("X-Hook-K3");
    http.sslVerifyPeer(false);
    http.sslVerifyHost(false);
    var length = 0;
    http.get(url, &(data) => {
        System.println("Received: %d" % data.length());
        length += data.length();
    });
    System.println("Total = %d bytes" % length);
    System.println("");
}

get(http, "https://ja.wikipedia.org/wiki/OpenSSL");
get(http, "https://curl.haxx.se/libcurl/c/multi-debugcallback.html");
get(http, "http://herumi.in.coocan.jp/soft/xbyak.html");
```

