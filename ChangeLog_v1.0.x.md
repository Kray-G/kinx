# Change Log

## V1.0.3 (Officially Released) - 2021/08/10

*   Improvements
    *   #308: Improvement of the stack usage.
    *   Some feedbacks from V1.1.0.
        *   Supported putting a comma at the end of an argument's list for both declaration and calling.
*   Bug Fixed
    *   #302: Fixed a prblem of the string optimization.
    *   #305: Fixed a prblem of no POPC in try.

## V1.0.2 (Officially Released) - 2021/05/21

*   Bug Fixed
    *   #284: Fixed a segmentation fault problem on Linux.
    *   #288: Incorrect message is displayed when `File.open` failed.
    *   #289: `File.setFiledate` does not work correctly.
    *   #293: Fixed a problem of a stack overflow with `=~` or `!~`.

## V1.0.1 (Officially Released) - 2021/04/22

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

This is 1st official release version.
