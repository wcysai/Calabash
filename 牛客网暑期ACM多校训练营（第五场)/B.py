x = 3
y = 2
ans = [2, 6]
for i in range(10000):
    [x, y] = [3*x+4*y, 2*x+3*y]
    ans.append(y)
    if (y>10**10000) : break

x = 7
y = 2
for i in range(10000):
    [x, y] = [7*x+24*y, 2*x+7*y]
    ans.append(y*3)
    if (y*3>10**10000) : break

ans.sort()
t = int(input());
for i in ans :
    if (i >= t) :
        print(i)
        break
