n = int(input())
a = list(map(int, input().split()))
r1 = a[0]
x1 = a[1:]
a = list(map(int, input().split()))
r2 = a[0]
x2 = a[1:]
dist = sum(map(lambda x, y:(x-y)*(x-y), x1, x2));
out = (r1+r2)*(r1+r2)
inn = (r1-r2)*(r1-r2)

if dist > out :
    print(0)
elif dist == out :
    print(1)
elif dist > inn and dist < out :
    print(2 if n == 2 else -1)
elif dist == inn :
    print(-1 if dist == 0 else 1)
else :
    print(0)
