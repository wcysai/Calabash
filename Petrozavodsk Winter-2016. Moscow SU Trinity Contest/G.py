k = int(input())
mod = k + k
print(mod)

s = [(0, k)]
for i in range(1, k) :
    s.append((0, i))
    s.append((k, i + k))

def emit(off) :
    for u, v in s :
        print((u + off) % mod + 1, (v + off) % mod + 1)

for i in range(k) : emit(i)
