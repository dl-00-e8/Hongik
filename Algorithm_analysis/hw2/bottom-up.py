def bottom_up(n):
    memo = {}

    if n<0:
        return 0
    
    # boundaries first
    memo[0] = 1
    
    # interior
    for i in range(1,n + 1):
        memo[i] = 0
        for j in range(0, i):
            memo[i] += memo[j]*memo[i - 1 - j]
    
    return memo[n]

# check result
# print(bottom_up(23))