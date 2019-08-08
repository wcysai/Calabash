for _ in range(int(input())) :
    n = int(input())
    s = list(map(int, input().split()))
    if n >= 3 :
        print('No')
        continue
    if n <= 1 :
        print('Yes')
        continue
    d = s[1] * s[1] - 4 * s[0] * s[2]
    print('Yes' if d < 0 else 'No')
