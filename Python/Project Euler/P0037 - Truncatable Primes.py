from math import sqrt

def is_prime(n):
    if n < 2:
        return False
    
    for i in range(2, int(sqrt(n)) + 1):
        if n % i == 0:
            return False

    return True

def is_tp(n):
    str_n = str(n)

    for i in range(len(str_n)):
        if not is_prime(int(str_n[i:])) or not is_prime(int(str_n[:len(str_n)-i])):
            return False

    return True

def truncatable_primes():
    tps = []
    n = 11

    while len(tps
    ) < 11:
        if is_tp(n):
            print(f"Found {n}")
            tps.append(n)
        
        n += 1
    
    return sum(tps)

print(f"Answer: {truncatable_primes()}")