#!/usr/bin/env python3
alpha = set(input())
t = input()
r = []
for i in range(len(t)) :
    r.append(t[:i] + t[i+1:])
for i in range(len(t)) :
    for ch in alpha :
        r.append(t[:i] + ch + t[i+1:])
for i in range(len(t) + 1) :
    for ch in alpha :
        r.append(t[:i] + ch + t[i:])
r = sorted(set(r))
for res in r :
    print(res)
