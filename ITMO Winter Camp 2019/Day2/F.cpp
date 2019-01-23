#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define maxn 1000
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,l;
int q[maxn],qhead;
int a[maxn][maxn];
int stk[maxn],top;
int last_pos[maxn],maxi[maxn];
void dfs(int now,int fa,queue<int> & Q){
    stk[top++] = now;
    while (!Q.empty()){
        int nxt = Q.front();
        Q.pop();
        if (nxt == fa){
            top --;
            for (int i=0;i<top;i++){
                if(now > maxi[stk[i]])
                a[now][stk[i]] = 1;
            }
            return;
        }else{
            a[nxt][now]=1; 
            maxi[now]=max(maxi[now],nxt);
            dfs(nxt,now,Q);
        }
    }
}
void work(queue<int> Q){
    
    top = 0;
    dfs(0,0,Q);
}
int main()
{
    freopen("dfs.in","r",stdin);
    freopen("dfs.out","w",stdout);
    cin>>n>>l;
    for (int i=0;i<l;i++){
        cin>>q[i];
        last_pos[q[i]] = i;
    }
    int now = 0;
    while (now < l){
        int root = q[now];
        queue<int> Q;
        //cerr<<"work"<<endl;
        for (int i=now;i <= last_pos[root];i++){
          //  cerr<<q[i]<<" ";
            Q.push(q[i]);
        }
       // cerr<<endl;
        work(Q);
        now = last_pos[root] + 1;
    }
    int cnt = 0;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            cnt += a[i][j];
        }
    }
    cout<<cnt<<endl;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=n;j++){
            if (a[i][j]){
                cout<<i<<" "<<j<<endl;
            }
        }
    }
    return 0;
}

