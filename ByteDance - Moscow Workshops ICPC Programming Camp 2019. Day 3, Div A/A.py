#!/usr/bin/python2

p, n = map(int, raw_input().split())

a = []

while n :
    a.append(n % p)
    n /= p
a.append(0)

l = len(a)

mod = 1000000007 * 2
mod1 = 1000000007
inv2 = 500000004
dp = [ [ [ [0] * 2 for ___ in range(2)] for __ in range(2) ] for _ in range(l + 1) ]
dp[0][0][0][0] = 1

for i in range(l) :
    for borrow in range(2) :
        cur = a[i] + borrow
        for used1 in range(2) :
            for used2 in range(2) :
                curdp = dp[i][borrow][used1][used2]
                if curdp == 0 : continue

                for sel1 in range(-1, 2) :
                    if used1 and sel1 != 0 : continue
                    nused1 = int(used1 or sel1 == 1)

                    for sel2 in range(-1, 2) :
                        if used2 and sel2 != 0 : continue
                        nused2 = int(used2 or sel2 == 1)

                        res = sel1 + sel2

                        if res == cur :
                            dp[i+1][0][nused1][nused2] = (dp[i+1][0][nused1][nused2] + curdp) % mod
                        if res + p == cur :
                            dp[i+1][1][nused1][nused2] = (dp[i+1][1][nused1][nused2] + curdp) % mod

ans = dp[l][0][1][1]

# print ans

if ans & 1 :
    ans -= 1

ans %= mod1
ans = ans * inv2 % mod1

print ans
