def bin(n):
    b = ["0"]
    i = 0
    while 2**(i+1) <= n:
        b.append("0")
        i += 1
    
    while i >= 0:
        if 2**i <= n:
            n -= 2**i
            b[len(b) - (i+1)] = "1"
        i -= 1
    
    return "".join(b)

def is_palindrome(str_n):
    i = 0
    j = len(str_n) - 1

    while j > i:
        if str_n[i] != str_n[j]:
            return False
        i += 1
        j -= 1
    
    return True

def double_base_palindromes(N):
    sum_ = 0
    for n in range(0, N+1):
        if is_palindrome(str(n)) and is_palindrome(bin(n)):
            print(f"Found {n}")
            sum_ += n
    return sum_

answer = double_base_palindromes(1000000)

print(f"Answer: {answer}")