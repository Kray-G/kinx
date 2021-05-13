# Change Log

## V1.0.2 (Current Development Version)

*   Bug Fixed
    *   #284: Fixed a segmentation fault problem on Linux.

## V1.0.1 (Officially Released)

*   Improvements
    *   Improved type analysis for the language server.
    *   Improved Array.keySet() for `Array` itself.
    *   #264: Supported to change directory.
    *   #265: Supported `$pwd` for getting a current directory.
*   Bug Fixed
    *   #235: Crash when using `_` outside a function.
    *   #236: Can't specify the class as a return type of function.
    *   #237: Comparing between variables having a string is failed.
    *   #256: Comparison operator will be failed with an integer on LHS and a variable(double) on RHS.
    *   #257: Fails a destructuring assignment when declaration with const.
    *   #258: There is a case that the bytecode is not outputted.
    *   #267: Can't use a variable name using an upper case in debugger.
    *   #269: Object item is removed by flatten().

## V1.0.0 (Official Release) - 2021/03/16

This is a 1st official release version.
