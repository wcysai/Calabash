for _ in range(int(input()))  :
    n = int(input())
    for _ in range(n - 1) :
        input()
    print('Alice' if n & 1 else 'Bob')