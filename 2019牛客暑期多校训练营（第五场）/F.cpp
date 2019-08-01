#include<bits/stdc++.h>
#define MAXN 5030
using namespace std;
#define Rep(i, n) for (int i = 1; i <= int(n); i++)
int n1,n2;
vector<int> G[MAXN];
int mx[MAXN],my[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
bool vis[MAXN];

bool vx[MAXN],vy[MAXN];
void markl(int u) {
    if (vx[u]) return;
    vx[u] = true;
    for (int v : G[u]) if (v != mx[u]) {
        vy[v] = true;
        assert(my[v]);
        markl(my[v]);
    }
}

bool find(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1)
        {
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]]))
            {
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching()
{
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n1;i++)
            if(!mx[i]) que.push(i);
        while(!que.empty())
        {
            int u=que.front();
            que.pop();
            for(int i=0;i<G[u].size();i++)
                if(!dy[G[u][i]])
                {
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]])
                    {
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n1;i++)
            if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}

int main() {
    int n;
    vector<int> x[2];
    set<int> xs;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int s; scanf("%d", &s); xs.insert(s);
        x[__builtin_parity(s)].push_back(s);
    }
    assert(xs.size() == n);
    n1 = x[0].size(); n2 = x[1].size();
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (__builtin_popcount(x[0][i] ^ x[1][j]) == 1)
                G[i+1].push_back(j+1);
        }
    }
    int ans = n - matching();
    cout << ans << endl;
    for (int i = 1; i <= n1; i++) if (!mx[i]) markl(i);
    vector<int> out;
    Rep (i, n1) if (vx[i]) out.push_back(x[0][i-1]);
    Rep (i, n2) if (!vy[i]) out.push_back(x[1][i-1]);
    for (int x : out) cout << x << ' ';
    cout << endl;
    /*
    cout << "_!_!_!_!_" << endl;
    for (int xx : x[0]) cout << xx << ' '; cout << endl;
    for (int xx : x[1]) cout << xx << ' '; cout << endl;
    Rep (i, n1) cout << mx[i] << ' '; cout << endl;
    Rep (i, n2) cout << my[i] << ' '; cout << endl;
    int tot [2] = {};
    Rep (i, n1) if (mx[i]) tot[0]++;
    Rep (i, n2) if (my[i]) tot[1]++;
    assert(tot[0] == tot[1] and tot[0] == n - ans);
    */
}
