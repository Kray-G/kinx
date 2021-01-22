
def fib(n)
    if n < 3
        return n
    end
    return fib(n-2) + fib(n-1)
end

print(fib(34), "\n");

