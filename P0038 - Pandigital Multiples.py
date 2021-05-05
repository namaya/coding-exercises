def is_pandigital(n, digits=9):
    seen = set()

    if len(n) != digits:
        return False

    for d in n:
        if d in seen or d == '0':
            return False
        else:
            seen.add(d)
    
    return True

def con_prod(i, n):
    cp = []

    for j in range(1, n+1):
        cp.append(str(i * j))
    
    return "".join(cp)

def pandigital_multiples():
    pds = []

    for i in range(1, 1000000):
        for n in range(1, 9):
            p = con_prod(i, n)
            if is_pandigital(p, digits=9):
                print(f"Found {p}")
                pds.append(p)
    
    return max(pds)

pandigital_multiples()