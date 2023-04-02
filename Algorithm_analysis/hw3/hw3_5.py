p = [0.08, 0.12, 0.05, 0.15, 0.2, 0.05, 0.05, 0.1, 0.1, 0.1]
opt = [[0 for _ in range(len(p) + 1)] for _ in range(len(p) + 1)]
k = [[0 for _ in range(len(p) + 1)] for _ in range(len(p) + 1)]
preSum = [0 for _ in range(len(p) + 2)]
bst = [0 for _ in range(len(p) * 4)]
height = 1


def presum_calc():
    for i in range(1, len(p) + 1):
        preSum[i] = round(preSum[i - 1] + p[i - 1], 2)


def opt_calc(i, j):
    result = 1e9
    
    if i > j:
        return 0
    elif i == j:
        opt[i][j] = 1.00
        k[i][j] = i
        return 1
    else:
        for num in range(i, j + 1):
            temp = (1 + ((preSum[num - 1] - preSum[i - 1]) * opt_calc(i, num - 1) / (preSum[j] - preSum[i - 1])) + ((preSum[j] - preSum[num])* opt_calc(num + 1, j) / (preSum[j] - preSum[i - 1])))

            if(temp < result):
                result = temp
                opt[i][j] = round(result, 2)
                k[i][j] = num

    return result


def makeBST(i, j, idx, depth):
    global height

    if i > j:
        return
    else:
        height = max(height, depth)
        makeBST(i, k[i][j] - 1, idx * 2, depth + 1)
        bst[idx] = k[i][j]
        makeBST(k[i][j] + 1, j, idx * 2 + 1, depth + 1)


def printBST(level):
    row = pow(2, level + 1) + 1
    col = level + 1
    mid = pow(2, level + 1)
    bst_output = [[0 for _ in range(row)] for _ in range(col)]

    for temp in range(level):
        mid = mid // 2
        start = mid // 2
        for i in range(pow(2, temp)):
            bst_output[temp][start] = bst[pow(2, temp) + i]
            start += mid
    
    for i in range(len(bst_output)):
        for j in range(len(bst_output[i])):
            if bst_output[i][j] == 0:
                print(" ", end = " ")
            else:
                print(bst_output[i][j], end = " ")
        print()


if __name__ == "__main__":
    presum_calc()

    # table of opt 출력
    print("table of opt[i,j]", end = "\n\n")
    opt_calc(1, len(p)) # 계산 진행
    for i in range(1, len(opt)):
        for j in range(1, len(opt[i])):
            if(i > j):
                print(" ", end = "\t")
            else:
                print("{:.2f}".format(opt[i][j]), end = "\t")     
        print()
    print()

    # table of k 출력
    print("table of k[i,j]", end = "\n\n")
    for i in range(1, len(k)):
        for j in range(1, len(k[i])):
            if(i > j):
                print(" ", end = "\t")
            else:
                print(k[i][j], end = "\t")
        print()
    print()

    # BST 출력
    print("Need to figure out how to print out BST :)")
    makeBST(1, len(p), 1, 1)
    printBST(height)