
def swap(queue, i, j):
    temp = queue[i]
    queue[i] = queue[j]
    queue[j] = temp

n, t = [int(i) for i in input().split(" ")]

queue = list(input())

x = 0
num_swaps = 1

while x < t and num_swaps > 0:
    num_swaps = 0
    i = 0
    while i < n-1:
        if queue[i] == "B" and queue[i+1] == "G":
            swap(queue, i, i+1)
            num_swaps += 1
            i += 1
        i += 1
    x += 1

print("".join(queue))
