# https://codeforces.com/problemset/problem/227/B

n = int(input())
ls = [int(num) for num in input().split(" ")]
m = int(input())

indexes = [None for _ in range(n)]

for i, num in enumerate(ls):
    indexes[num-1] = i

queries = [int(query) for query in input().split(" ")]

sums = [0, 0]

for query in queries:
    front_nc = indexes[query-1] + 1
    back_nc = n - indexes[query-1]

    sums[0] += front_nc
    sums[1] += back_nc

print(f"{sums[0]} {sums[1]}")
