from time import time, sleep

fibonacci = [0 for i in range(47)]

def fib(n):
    fibonacci[n] += 1
    if n == 0:
        return 0
    if n == 1:
        return 1
    else:
        return fib(n - 1) + fib(n - 2)
    

if __name__ == "__main__":
    start = time()
    print(fib(15))
    end = time()

    print('How long', end - start)

    for i in range(46):
        print(fibonacci[i], end = " ")