
N = 5
MID = N // 2 + 1

for i in range(N):
    row = [int(num) for num in input().split(" ")]

    result = -1

    for j in range(len(row)):
        if row[j] == 1:
            result = abs(i + 1 - MID) + abs(j + 1 - MID)
            break
    
    if result != -1:
        break

print(result)
