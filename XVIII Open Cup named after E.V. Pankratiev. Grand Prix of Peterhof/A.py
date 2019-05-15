fn = [
lambda x : 1 - 3 * x + 3 * x * x ,
lambda x : -2 * x + 3 * x * x,
lambda x : -x + 3 * x * x,
lambda x : 3 * x * x,
lambda x : x + 3 * x * x,
lambda x : 2 * x + 3 * x * x
]

def f(x) :
if x < 6 : return 0
return fn[x % 6](x / 6)

def bsch(x) :
l, r = 0, 500000
while l < r :
    mid = (l + r) / 2
    if f(mid) >= x :
        r = mid
    else :
        l = mid + 1
return l

print bsch(input())
