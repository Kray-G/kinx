# Kinx Object Reference

## Regex

`Regex` object is used for a regular expression.
`Regex` is a class, so the instance will be always created by `new` operator.

|          Method           |                                                  Meaning                                                   |
| ------------------------- | ---------------------------------------------------------------------------------------------------------- |
| `re = new Regex(pattern)` | Creates an instance.                                                                                       |
| `re.reset(str)`           | Reset the search target string.                                                                            |
| `re.find()`               | `true` if found. This can be used continuously until it has been not found.                                |
| `re.matches()`            | `true` if matches. This can be used only one time because this is checking if the target is fully matched. |
