#!/usr/bin/python2
n = input()
x = map(int, raw_input().split())
nz = x.count(0)
if nz == 1 :
    print 'No'
    exit(0)
if nz > 1 :
    print 'Yes'
    print 0
    exit(0)
prod = 1
for a in x :
    prod *= a
    if abs(prod) > 1e18 + 5 :
        print 'No'
        exit(0)
for a in x :
    if a * a == prod :
        print 'Yes'
        print a
        exit(0)
print 'No'
