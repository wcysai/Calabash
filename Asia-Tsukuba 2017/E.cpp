#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n, k, pre[MAXN], deq[MAXN], dp[MAXN], a[MAXN];
char s1[MAXN], s2[MAXN];

int main() {
    scanf("%d%d", &n, &k);
    scanf("%s", s1 + 1);
    scanf("%s", s2 + 1);
    pre[0] = 0;
    for(int i = 1; i <= n; i++)
        pre[i] = pre[i-1] + bool(s2[i] != s2[i-1]);
    pre[0] = -1;
    int s = 0, t = 0;
    deq[t++] = 0;
    for(int i = 1; i <= n; i++) {
        if (s1[i] == s2[i])
            dp[i] = min(dp[i-1], pre[deq[s]] + pre[i] + 2);
        else
            dp[i] = pre[deq[s]] + pre[i] + 2;
        if(dp[i] & 1) dp[i]++;
        pre[i] = dp[i] - pre[i + 1];
        while (s < t && pre[deq[t-1]] >= pre[i])
            t--;
        deq[t++] = i;
        if (i - k >= 0)
            if(deq[s] == i - k)
                s++;
    }
    printf("%d\n",dp[n]/2);
    return 0;
}

/*
4 4
BWWB
WBBW
 */
