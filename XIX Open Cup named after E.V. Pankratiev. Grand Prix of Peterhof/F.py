#!/usr/bin/python2
n = input()
print ''.join(map(lambda x : 'B' if x % 5 == 0 else 'F', map(int, raw_input().split())))
