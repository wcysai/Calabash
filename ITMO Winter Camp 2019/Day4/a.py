b1, d1 = map(int, input().split())
b2, d2 = map(int, input().split())
l1 = b1**(d1-1)
r1 = (b1**d1)-1
l2 = b2**(d2-1)
r2 = (b2**d2)-1
l = max(l1, l2)
r = min(r1, r2)
print( max(0, r - l+1))
