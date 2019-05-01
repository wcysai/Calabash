a = b = 0
for u, v in zip(input(), input()) :
    if ord(u) < ord(v) : a += 1
    if ord(u) > ord(v) : b += 1

print(a)
print(b)
