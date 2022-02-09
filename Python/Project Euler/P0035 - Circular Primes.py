from copy import deepcopy
from math import sqrt

def circular_primes(N):
    ncp = 0
    for i in range(2, N):
        if is_cp(i):
            ncp += 1
    return ncp

def is_cp(n):
    for rotation in rotations(n):
        if not is_prime(rotation):
            return False
    return True

def rotations(n):
    ar = list(str(n))

    for _ in range(len(ar)):
        yield int(''.join(ar))
        ar = rotate(ar)

def rotate(ar):
    temp = ar[0]

    for j in range(len(ar) - 1):
        ar[j] = ar[j+1]

    ar[-1] = temp

    return ar

def is_prime(n):
    if n <= 1:
        return False
    
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False

    return True

print(f"Answer: {circular_primes(1000000)}")
