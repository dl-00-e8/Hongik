def memoize(f):
    memo = {}

    def helper(x):
        if (x) not in memo:
            memo[x] = f(x)
        return memo[x]

    return helper


def top_down(n):
    print(n)

    # condition
    if n<0: 
        return 0
    if n==0:
        return 1
    
    sum = 0
    for i in range(0, n):
        sum += top_down(i) * top_down(n - 1 - i)

    return sum

top_down=memoize(top_down)

# check the result
# print(top_down(23))