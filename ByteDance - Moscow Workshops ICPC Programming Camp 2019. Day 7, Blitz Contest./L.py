def f(n) :
    if n == 1 : return 1
    if n % 2 == 0 :
        return 2 * f(n / 2) - 1
    else :
        return 2 * f(n / 2) + 1

while True :
    n = input()
    if n == 0: break
    print f(n)
