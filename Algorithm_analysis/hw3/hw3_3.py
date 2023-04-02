d = [8, 3, 5, 5, 2, 8, 7, 6, 5, 4]
opt = [[0 for _ in range(len(d))] for _ in range(len(d))]
k = [[0 for _ in range(len(d))] for _ in range(len(d))]
matrix = ""

def opt_calc(i, j):
    result = 1e9

    if i == j:
        return 0

    for num in range(i, j):
        temp = opt_calc(i, num) + opt_calc(num + 1, j) + d[i - 1] * d[num] * d[j]

        if(temp < result):
            result = temp 
            opt[i][j] = result
            k[i][j] = num  

    return result


def chained_matrix(i, j):
    global matrix
    
    if i == j:
        matrix += "A" + str(i)
    else:
        matrix += "("
        chained_matrix(i, k[i][j])
        chained_matrix(k[i][j] + 1, j)
        matrix += ")"


if __name__ == "__main__":
    # table of opt 출력
    print("table of opt[i,j]", end = "\n\n")
    opt_calc(1, len(d) - 1) # 계산 진행
    for i in range(1, len(opt)):
        for j in range(1, len(opt[i])):
            if(i > j):
                print(" ", end = "\t")
            else:
                print(opt[i][j], end = "\t")     
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

    # Matrix 출력
    print("optimal chained matrix multiplication", end = "\n\n")
    chained_matrix(1, len(d) - 1)
    print(matrix[1:len(matrix) - 1])