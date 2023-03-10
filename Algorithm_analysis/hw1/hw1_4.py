#!python3
#coding:utf-8-*-

def memoize(f):
    memo = {}
    
    def helper(x):
        if x not in memo:
            memo[x] = f(x)
        return memo[x]
    
    return helper

def fib(n):
    if n==0:
        return 0
    if n==1:
        return 1
    else:
        return fib(n-1)+fib(n-2)

if __name__ == "__main__":  
    fib=memoize(fib)

    # fib = helper(x) 
    print(fib(1000))