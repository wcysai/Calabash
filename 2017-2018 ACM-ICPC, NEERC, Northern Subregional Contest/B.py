#!/usr/bin/env python3
import sys, string
sys.stdin = open("boolean.in", "r")
sys.stdout = open("boolean.out", "w")
s = list(set(input().split('|')))
sch = set(ch[-1] for ch in s)
nlit = len(sch)
for ch in sch :
    if ch in s and ('~' + ch) in s :
        print(2**nlit)
        exit(0)
print(2**nlit-1)
