n, k = map(int, raw_input().split())
x = map(int, raw_input().split())
x.sort()
i = 0
for i in range(0, n - 1) :
    if x[i] + x[i+1] > k :
        print i + 1
        exit(0)
print n
