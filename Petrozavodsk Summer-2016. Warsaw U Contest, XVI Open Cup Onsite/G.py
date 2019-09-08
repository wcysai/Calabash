#!/usr/bin/python3
k, a, b = map(int, input().split())
ans = 0
for fn in range(1, 5000) :
    n = k * fn
    if n < a or n > b : continue
    s = 0
    for ch in str(n) :
        s += int(ch) ** 2
    if s == fn : ans += 1
print(ans)
