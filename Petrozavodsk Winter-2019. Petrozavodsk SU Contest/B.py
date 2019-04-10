n = input()
a = map(int, raw_input().split())
x = [i % n for i in range(n+n)]
s = []
for _ in range(n+n-1) :
    s.append(x[:-1])
    x = x[1:] + x[:1]
print len(s)
for row in s :
    for col in row :
        print a[col],
    print
