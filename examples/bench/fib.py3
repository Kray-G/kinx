
def fib(n):
    if n < 3:
        return n
    return fib(n-2) + fib(n-1)

print(fib(34))

