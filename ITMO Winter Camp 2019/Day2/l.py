a, b, c = open('sum.in', 'rU').read().splitlines()
fo = open('sum.out', 'w')
aa, bb, cc = a, b, c
n, m, k = map(len, (a, b, c))
c += 100005 * '0'

def ok() :
    fo.write('YES\n')
    fo.write(' '.join(map(str, (len(a) - n, len(b) - m, len(c) - k))))
    fo.write('\n')
    exit(0)

a += (len(c) - len(a)) * '0'
if a > c : a = a[:-1]
bp = str(int(c) - int(a))
if len(bp) >= len(b) and bp[:len(b)] == b and int(bp[len(b):]) == 0:
    b = bp
    ok()

a, b = aa, bb
b += (len(c) -  len(b)) * '0'
if b > c : b = b[:-1]
ap = str(int(c) - int(b))
if len(ap) >= len(a) and ap[:len(a)] == a and int(ap[len(a):]) == 0:
    a = ap
    ok()

fo.write('NO\n')

