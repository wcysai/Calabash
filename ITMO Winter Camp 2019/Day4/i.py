n, k = map(int, input().split())
p = [0] + list(map(int, input().split()))
q = [0] + list(map(int, input().split()))
a = [0] * (n + 1)
b = [0] * (n + 1)
for i in range(1, n + 1) : q[i] = n + 1 - q[i]
for i in range(1, n + 1) : b[q[i]] = i
for i in range(1, n + 1) :
    if k == 0 :
        a[p[i]] = n
    elif k < n - p[i] :
        a[p[i]] = sorted(b[p[i]+1:], reverse=1)[k]
        k = 0
    else :
        a[p[i]] = 0
        k -= n - p[i]
for i in range(1, n + 1) : b[i] = -b[i]
print('Yes')
print(*a[1:])
print(*b[1:])
