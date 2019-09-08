#!/usr/bin/python2
from fractions import gcd
def modinv(q,m):
    if q==0:
        return 0
    a1,b1,a2,b2=m,0,q,1
    while a2!=1:
        t=a1/a2
        a1,a2,b1,b2=a2,a1-t*a2,b2,b1-t*b2%m
        if b2<0:
            b2+=m
    return b2

def merge(a,b,c,d):
    c-=a
    dd=gcd(b,d)
    if c%dd!=0:
        return -1
    b,c,d=b/dd,c/dd,d/dd
    t=c*modinv(b,d)%d
    if t<0:
        t+=d
    return b*t*dd+a

def CRT(d):
    r,x=1,0
    for p in d:
        if x!=-1:
            x=merge(x,r,p[1],p[0])
        r=r/gcd(r,p[0])*p[0]
    return x

n = input()
d=[]

for i in xrange(n):
    d.append(map(int,raw_input().split()))

x=CRT(d)

fib = [0, 1]
for _ in range(100) :
    fib.append(fib[-1] + fib[-2])

if x==-1:
    print "Tankernb!"
elif x not in fib:
    print "Zgxnb!"
else:
    print 'Lbnb!'
