#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define prev asfkjdoidafk
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,m,l;
int a[MAXN],x[MAXN],y[MAXN];

int content[MAXN];
int sz[MAXN], *head[MAXN];

// vector<int> v[MAXN];
int prev[MAXN],st[MAXN],ed[MAXN],last[MAXN],tot;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++) content[i] = i;
    
    sort(content + 1, content + n + 1, [](int x, int y) {
        if (a[x] != a[y]) return a[x] < a[y];
        else return  x < y;});

    for(int i=1;i<=n;i++) head[i] = content;
    for(int i=n;i;i--) {
        head[a[content[i]]] = content + i;
        sz[a[content[i]]]++;
    }
/*
    for (int i=1; i<=n; i++) {
        cout << sz[i] << ' ';
        for (int j = 0; j < sz[i]; j++) cout << head[i][j] << ' ';
        cout << endl;
    }
    return 0;
  */  
    // for(int i=1;i<=n;i++) v[a[i]].push_back(i);
    scanf("%d%d",&m,&l);
    for(int i=1;i<=m;i++) scanf("%d",&x[i]);
    for(int i=1;i<=l;i++) scanf("%d",&y[i]);
    for(int i=2;i<=m;i++) prev[x[i]]=x[i-1];
    for(int i=1;i<=n;i++)
    {
        if(a[i]==x[1]) st[i]=i-1;
        else if(!prev[a[i]]) continue;
        else
        {
            auto it=upper_bound(head[prev[a[i]]],head[prev[a[i]]] + sz[prev[a[i]]],i);
            if(it==head[prev[a[i]]]) st[i]=0;
            else {it--; st[i]=st[*it];/* printf("%d %d\n",i,*it)*/;}
        }
    }
    memset(prev,0,sizeof(prev));
    for(int i=2;i<=l;i++) prev[y[i]]=y[i-1];
    for(int i=n;i>=1;i--)
    {
        if(a[i]==y[1]) ed[i]=i+1;
        else if(!prev[a[i]]) {ed[i]=INF; continue;}
        else
        {
            auto it=lower_bound(head[prev[a[i]]],head[prev[a[i]]] + sz[prev[a[i]]],i);
            if(it==head[prev[a[i]]]+sz[prev[a[i]]]) ed[i]=INF;
            else ed[i]=ed[*it];
        }
    }
//     for(int i=1;i<=n;i++) printf("%d %d %d\n",i,st[i],ed[i]);
    fill(last,last+MAXN,-INF);
    for(int i=1;i<=1000000;i++)
    {
        if(sz[i] == 0) continue;
        last[head[i][0]]=max(last[head[i][0]],head[i][sz[i] - 1]);
    }
    for(int i=2;i<=n;i++) last[i]=max(last[i],last[i-1]);
    tot=0;
    for(int i=1;i<=n;i++)
    {
        if(a[i]!=x[m]) continue;
        int l=st[i],r=last[l];
        if(r>=ed[i]) y[++tot]=i;
    }
    printf("%d\n",tot);
    for(int i=1;i<=tot;i++)
    {
        printf("%d%c",y[i],i==tot?'\n':' ');
    }
    return 0;
}
