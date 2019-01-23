n = int(open('string.in', 'r').read())
s = ''
for i in range(1, n+1) :
    if s.find(str(i)) == -1 :
        s += str(i)
open('string.out','w').write(s)
