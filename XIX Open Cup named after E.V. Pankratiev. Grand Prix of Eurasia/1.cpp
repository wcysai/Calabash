#define MAXN 105
#include <bits/stdc++.h>
using namespace std;
int T,H,W;
string str;
int a[MAXN][MAXN];
int ans[MAXN][MAXN];
int main()
{
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d", &H, &W);
        cin >> str;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++)
                scanf("%d", &a[i][j]);
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                int x = i, y = j, cnt = a[x][y];
                bool f = true;
                for (int k = 0; k < (int) str.size(); k++) {
                    if (str[k] == 'R') y++;
                    else if (str[k] == 'L') y--;
                    else if (str[k] == 'U') x--;
                    else x++;
                    if (x < 0 || x >= H || y < 0 || y >= W)
                    {
                        f = false;
                        ans[i][j] = 0;
                        break;
                    }
                    cnt += a[x][y];
                }
                if (f) ans[i][j] = cnt;
            }
        }
        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++)
                printf("%d%c", ans[i][j], j == W - 1 ? '\n' : ' ');
    }
    return 0;
}
