from math import *
inc = sqrt(2.0) - 1.0
n = int(open('journey.in', 'r').read())
if n == 1 :
    ans = 0.0
else :
    ans = n * n + (n - 2) * (n - 2) * inc

open('journey.out', 'w').write("%.8f" % ans)
