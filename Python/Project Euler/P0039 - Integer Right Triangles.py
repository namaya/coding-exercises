from math import atan, asin

def is_rt(a, b, c, tol=0.001):
    theta_a1 = atan(b/a)
    theta_a2 = asin(b/c)

    return theta_a1 <= theta_a2 + tol and theta_a1 >= theta_a2 - tol


def num_solutions(p):
    ns = 0

    for a in range(1, p//2 + 1):
        for b in range(a, (p-a)//2 + 1):
            c = p-a-b
            if is_rt(a, b, c, tol=0.00000001):
                ns += 1

    return ns

def integer_right_triangles(N):
    max_p = 0
    max_ns = 0

    for p in range(1, N+1):
        ns = num_solutions(p)
        if ns > max_ns:
            print(f"p = {p} has largest num of solutions with {ns}")
            max_ns = ns
            max_p = p

    return max_p

print(integer_right_triangles(1000))