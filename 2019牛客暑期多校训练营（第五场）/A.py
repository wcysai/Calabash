import random as r

for _ in range(int(input())) :
    n = int(input())
    while True :
        x = n * r.randint(1, 10**100)
        ans = 0
        for d in str(x) :
            ans += ord(d) - ord('0')
        if ans % n == 0 :
            print(x)
            break
