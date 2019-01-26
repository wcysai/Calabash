#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
//int n,k,a[MAXN];
const int maxn = 305;
int n,m,D;
vector<int> E[maxn];
int d[maxn];
int d_t[maxn];
vector<int> ans;
int v[maxn];
bool check(int low,int high,int cnt){
    for (int i=1;i<=n;i++){
        v[i] = i;
        d_t[i] = d[i];
    }
    sort(v+1,v+1+n,[](int x,int y){
            if (d[x] == x[y]){
                return x < y;
            }else{
                return d[x] > d[y];
            }
        });
    memset(used,0,sizeof used);
    for (int i=1;i<=n;i++){
        int x = -1;
        for (int j=1;j<=n;j++){
            if (used[j])continue;
            if (x == -1)x = j;
            else if(d_t[j] > d_t[i]){
                x = j;
            }
        }
        if (d_t[x] <= high)return 1;
        int limit = high;
        if (i > cnt)limit = low;
        vector<int> nxt(0);
        for (int v : E[x]){
            if (used[v])continue;
            nxt.push_back(v);
        }
        sort(v.begin(),v.end(),[](int x,int y){
                return d_t[x] > d_t[y];
                });

    }
    return 0;
}
int main()
{
    scanf("%d%d%d",&n,&m,&D);
    for (int i=0;i<m;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        E[u].push_back(v);
        E[v].push_back(u);
        d[u] ++;
        d[v] ++;
    }
    int min_d = INT_MAX;
    for (int i=1;i<=n;i++){
        min_d = min(min_d,d[i]);
    }
    if (min_d < D-1)return puts("NO"),0;
    if (min_d == D-1){
        if(check(D-1,D)){
            puts("YES");
            printf("%d\n",(int)ans.size());
            for (int x : ans){
                printf("%d ",x);
            }
            puts("");
        }else{
            puts("NO");
        }
    }else{
        if (check(D-1,D) or check(D,D+1)){
            puts("YES");
            printf("%d\n",(int)ans.size());
            for (int x : ans){
                printf("%d ",x);
            }
            puts("");
        }else{
            puts("NO");
        }
    }
    return 0;
}

