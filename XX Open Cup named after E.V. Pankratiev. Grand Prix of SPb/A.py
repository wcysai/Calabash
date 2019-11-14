#!/usr/bin/env python2
import sys
mod = 1000000007

def polymul(a, b) :
    p = [0] * (len(a) + len(b) - 1)
    for e1, c1 in enumerate(a) :
        for e2, c2 in enumerate(b) :
            p[e1+e2] += c1 * c2 % mod
    return p

def interpol(x, y, n) :
    lj = [reduce(polymul, [[-x[m] * pow(x[j]-x[m], mod - 2, mod), pow(x[j]-x[m], mod - 2, mod)]
        for m in range(n) if m != j]) for j in range(n)]
    return map(sum, zip(*map(lambda a, b : [x*a for x in b], y, lj)))

def ask(x) :
    print 'ask', x
    sys.stdout.flush()
    return input()

x = [0]
y = [ask(0)]
for deg in range(1, 100) :
    x.append(deg)
    y.append(ask(deg))
    poly = interpol(x, y, len(x))
    if poly[-1] % mod == 0  :
        print 'degree', deg - 1
        exit(0)

