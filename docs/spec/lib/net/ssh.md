# class Ssh

## Overview

This is a network library of SSH.

### Using `net.Ssh`

This library will be available with `using` below.

```javascript
using net.Ssh;
```

### Conttructor

The destination host address is specified in the constructor's argument.

```javascript
var ssh = new Net.Ssh("127.0.0.1");
```

### Open and Login

SSH login should be done after `open()`.
The example below is a style in general.

```javascript
var ssh = new Net.Ssh("Target IP address");
ssh.open { &(con)
    // ... Set up before login.

    // Login. Exception will occur if failed.
    con.login("username", "password");

    // Communicates with the target.
}
// Closed automatically after exiting a block.
```

### Methods

|        Name         |                               Content                               |
| ------------------- | ------------------------------------------------------------------- |
| `setTimeout(msec)`  | Sets a timeout in millisec.                                         |
| `setPrompt(prompt)` | Sets a prompt to wait for.                                          |
| `getFingerprint()`  | Returns the computed digest of the remote system's hostkey in SHA1. |
| `getUserAuthList()` | Returns the list supported authentication methods.                  |
| `sendKeepAlive()`   | Sends a keepalive message if needed.                                |
| `open(f)`           | Opens a SSH session.                                                |
| `close()`           | Closes a SSH session.                                               |
| `login(user, pass)` | Logins ​with a specified username and a password                    |
| `logout()`          | Logouts from the target host.                                       |
| `print(...a)`       | Sends a message to the target host without a newline.               |
| `println(...a)`     | Sends a message to the target host with a newline.                  |
| `waitfor(pattern)`  | Waits for a text matched by the specified pattern.                  |

## Some Examples

### Normal Use

Here is an example about normal use of SSH.

```javascript
using net.Ssh;

var [, user, pass] = $$;

var ssh = new Net.Ssh("127.0.0.1");
# ssh.setTimeout(100); # for connection timeout.
ssh.open { &(con)
    System.println("Fingerprint: ", con.getFingerprint());

    con.setTimeout(10000);  # for user auth timeout.
    con.login(user, pass);
    System.println("UserAuthList: ", con.getUserAuthList());

    con.println("ls -lha");
    var mes = con.waitfor();
    System.println(mes);

    con.logout();
};
```
