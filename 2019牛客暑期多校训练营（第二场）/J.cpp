#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 7;
const int maxr = 2e7 + 7;
const int maxm = 3e7 + 7;
 
int n;
int cnt = 0;
ll L[maxn], R[maxn];
ll S[maxn];
ll tol[maxn], tor[maxn];
 
 
int CNT[maxm];
char num[maxm];
ll mn = 0;
ll ans = 0;
int r[maxr];
 
void input(){
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld%lld",L + i,R + i);
        cnt += R[i] - L[i] + 1;
    }
    S[1] = R[1] - L[1] + 1;
    for (int i = 2; i <= n; i++) {
        S[i] = S[i - 1] + (R[i] - L[i] + 1) - (L[i] - R[i - 1] - 1);
    }
}
void prework(){
    for (int i = 1; i <= n; i++) {
        mn = min(mn, 0ll + S[i] - (R[i] - L[i] + 1));
        tor[i] = S[i] - mn;
        if (i != n) tor[i] = min(tor[i], L[i + 1] - R[i] - 1);
    }
 
    S[n] = R[n] - L[n] + 1;
    for (int i = n - 1; i >= 1; i--)
        S[i] = S[i + 1] + (R[i] - L[i] + 1) - (L[i + 1] - R[i] - 1);
 
    mn = 0;
    for (int i = n; i >= 1; i--) {
        mn = min(mn, 0ll + S[i] - (R[i] - L[i] + 1));
        tol[i] = S[i] - mn;
        if (i != 1) tol[i] = min(tol[i], L[i] - R[i - 1] - 1);
    }
 
}
int tail = 0;
int last = -1000000000;
void gao(int i){
    for (int j = max((ll)last + 1, L[i] - tol[i]); j <= R[i] + tor[i]; j++)
        if (j > CNT[tail] && j >= 0 && j < 1000000000) {
            CNT[++tail] = j;
            if (j >= L[i] && j <= R[i]) num[tail] = 1;
            else num[tail] = 0;
        }
    last = CNT[tail];
}
void gao2(int & x){
    int y = x + 1;
    while (y <= tail && CNT[y] == CNT[y - 1] + 1) y++;
    y--;
    int cur = 1e7 +3;
    ll temp_ans = 0;
    r[cur]++;
    for (int i = x; i <= y; i++) {
        temp_ans += num[i] == 1?r[cur] : -r[cur-1];
        cur += num[i] == 1?1 : -1;
        r[cur]++;
        ans += temp_ans;
    }
    cur = 1e7 + 3;
    r[cur]--;
    for (int i = x; i <= y; i++) cur += num[i] == 0?-1 : 1,r[cur] --;
    x = y;
}
void work(){
    prework();
    CNT[tail] = -1000000000;
    for (int i = 1; i <= n; i++) {
        gao(i);
    }
    assert(tail <= 3 * cnt);
    for (int x = 1; x <= tail; x++) {
        gao2(x);
    }
 
}
signed main() {
    input();
    work();
    cout << ans << endl;
 
    return 0;
}
