

def champernownes_constant(N):
    pnds = 0
    M = 0
    i = 1
    answer = 1

    while M <= N:
        str_i = str(i)

        if pnds + len(str_i) >= 10**M:
            answer *= int(str_i[10**M - pnds - 1])
            print(f"d{10**M} = {int(str_i[10**M - pnds - 1])}")
            M += 1

        pnds += len(str_i)
        i += 1
    
    return answer

print(champernownes_constant(6))