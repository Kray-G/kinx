# Kinx Object Reference

## SystemTimer

`SystemTimer` object is used to measure time.
`SystemTimer` is a class, so the instance will be always created by `new` operator.

|          Method           |                            Meaning                             |
| ------------------------- | -------------------------------------------------------------- |
| `tmr = new SystemTimer()` | Creates an instance.                                           |
| `tmr.restart()`           | Restarts the timer.                                            |
| `tmr.elapsed()`           | Returns a elapsed from starting or restarting the measurement. |
