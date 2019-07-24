#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int N,C,K;
int a[MAXN],pos1[MAXN],pos2[MAXN];
vector<int> pos[MAXN];
int val[MAXN];
struct segtree
{
    int maxi[4*MAXN],lazy[4*MAXN],maxpos[4*MAXN];
    void pushup(int k)
    {
        if(maxi[k*2]>maxi[k*2+1]) {maxi[k]=maxi[k*2]; maxpos[k]=maxpos[k*2];}
        else {maxi[k]=maxi[k*2+1]; maxpos[k]=maxpos[k*2+1];}
    }
    void pushdown(int k)
    {
        if(lazy[k]==0) return;
        for(int i=k*2;i<=k*2+1;i++)
        {
            lazy[i]+=lazy[k];
            maxi[i]+=lazy[k];
        }
        lazy[k]=0;
    }
    void build(int k,int l,int r)
    {
        lazy[k]=0;
        if(l==r)
        {
            maxpos[k]=l;
            maxi[k]=val[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y)
        {
            lazy[k]+=v;
            maxi[k]+=v;
            return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    P query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return make_pair(-INF,-INF);
        if(l>=x&&r<=y) return make_pair(maxi[k],maxpos[k]);
        pushdown(k);
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int main()
{
    while(scanf("%d%d%d",&N,&C,&K)==3)
    {
        for(int i=1;i<=C;i++) pos[i].clear();
        for(int i=1;i<=N;i++) 
        {
            val[i]=0;
            scanf("%d",&a[i]);
            pos[a[i]].push_back(i);
        }
        if(K==1)
        {
            printf("%d\n",N);
            continue;
        }
        for(int i=1;i<=C;i++)
        {
            for(int j=0;j<(int)pos[i].size();j++)
            {
                if(j+K-1<(int)pos[i].size()) pos1[pos[i][j]]=pos[i][j+K-1]; else pos1[pos[i][j]]=-1;
                if(j+K<(int)pos[i].size()) pos2[pos[i][j]]=pos[i][j+K]; else pos2[pos[i][j]]=-1;
                if(j<K-1) val[pos[i][j]]=-1;
                if(j==K-1) val[pos[i][j]]=K-1;
            }
        }
        for(int i=1;i<=N;i++) val[i]+=val[i-1];
        int ans=0;
        seg.build(1,1,N);
        for(int i=1;i<=N;i++)
        {
            P p=seg.query(1,1,N,i,N);
            if(p.F==0) ans=max(ans,p.S-i+1);
            seg.update(1,1,N,i+1,N,1);
            if(pos1[i]!=-1) seg.update(1,1,N,pos1[i],N,-K);
            if(pos2[i]!=-1) seg.update(1,1,N,pos2[i],N,K-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
