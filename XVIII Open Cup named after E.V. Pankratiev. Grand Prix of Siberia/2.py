#!/usr/bin/python3
import sys

def emit(s) :
    print(s)
    sys.stdout.flush()

def forward() :
    emit('forward')
    return input()

def uturn() :
    emit('left')
    emit('left')


def retreat() :
    uturn()
    forward()
    uturn()

def work() :
    last = forward()
    while True :
        cur = forward()
        if cur == 'farther' and last != 'farther' :
            retreat()
            break
        last = cur

def work2() :
    closer = farther = 0
    last = forward()
    if last == 'farther' : farther += 1
    if last == 'closer' : closer += 1
    while True :
        cur = forward()
        if cur == 'farther' and last != 'farther' :
            retreat()
            break
        last = cur
        if last == 'farther' : farther+= 1
        if last == 'closer' : closer += 1
    return closer > farther

work()
emit('left')
work()
if not work2() : work()
emit('dig')
