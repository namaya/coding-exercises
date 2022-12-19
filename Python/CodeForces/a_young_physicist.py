
n = int(input())

rolling_sums = [0 for _ in range(3)]

for i in range(n):
    forces = [int(force) for force in input().split(" ")]

    for j in range(3):
        rolling_sums[j] += forces[j]

result = True

for j in range(3):
    if rolling_sums[j] != 0:
        result = False
        break

if result:
    print("YES")
else:
    print("NO")