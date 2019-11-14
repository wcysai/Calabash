#!/usr/bin/env python2
for _ in range(input()) :
    x, y = map(int, raw_input().split())
    if not y :
        print 'Yes'
    else :
        while y % 2 == 0 : y >>= 1
        if bin(y)[2:] in bin(x) :
            print 'Yes'
        else :
            print 'No'
