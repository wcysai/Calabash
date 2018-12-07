import fractions
n = int(input())
a1 = list(map(int, input().split()))
k1 = list(map(int, input().split()))
a2 = list(map(int, input().split()))
k2 = list(map(int, input().split()))

def det(a11, a12, a21, a22) :
    return a11 * a22 - a12 * a21

def dot(a, b) :
    ans = 0
    for i in range(n) :
        ans += a[i] * b[i]
    return ans

for i in range(n) :
    k1[i] -= a1[i]
    k2[i] -= a2[i]

a11 = dot(k1, k1); a12 = -dot(k1, k2); b1 = dot(a2, k1) - dot(a1, k1);
a21 = dot(k1, k2); a22 = -dot(k2, k2); b2 = dot(a2, k2) - dot(a1, k2);
determ = det(a11, a12, a21, a22)

if determ == 0 :
    for i in range(n) :
        a1[i] -= a2[i]
    inner = dot(a1, a1) * dot(k1, k1) - dot(a1, k1) * dot(a1, k1)
    fans = fractions.Fraction(inner, dot(k1, k1))
else :
    t1 = det(b1, a12, b2, a22)
    t2 = det(a11, b1, a21, b2)
    ans = 0
    for i in range(n) :
        a1[i] = a1[i] * determ + t1 * k1[i]
        a2[i] = a2[i] * determ + t2 * k2[i]
        ans += (a1[i] - a2[i]) * (a1[i] - a2[i])
    fans = fractions.Fraction(ans, determ * determ)

print(fans.numerator, fans.denominator, sep='/')
