for _ in range(int(input())) :
    x, y = input().split()
    x = x[::-1]
    y = y[::-1]
    z = int(x) + int(y)
    z = str(z)[::-1]
    print(int(z))
