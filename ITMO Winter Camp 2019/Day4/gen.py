from random import *
import sys
n = int(sys.argv[1])
k = int(sys.argv[2])
a, b = [list(range(1, n + 1)) for _ in range(2)]
shuffle(a)
shuffle(b)
print(n, k)
print(*a)
print(*b)
