n = input()
cnt = 0
a = map(int, raw_input().split())
for i in range(1, n) :
    if a[i-1] >= a[i] :
        cnt += 1

print pow(2, cnt)
