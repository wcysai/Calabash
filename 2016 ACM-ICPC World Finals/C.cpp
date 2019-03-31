#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
struct node
{
    int val;
    node* lc;
    node* rc;
};
node* newnode(int val)
{
    node* x=(node *)malloc(sizeof(node));
    x->lc=NULL; x->rc=NULL;
    x->val=val;
    return x;
}
void add(node* x,int val)
{
    if(val<x->val)
    {
        if(x->lc==NULL) x->lc=newnode(val);
        else add(x->lc,val);
    }
    else
    {
        if(x->rc==NULL) x->rc=newnode(val);
        else add(x->rc,val);
    }
}
bool same(node *x,node *y)
{
    if(x==NULL&&y==NULL) return true;
    if(x==NULL||y==NULL) return false;
    return same(x->lc,y->lc)&&same(x->rc,y->rc);
}
vector<node*> v;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
    {
        int x;scanf("%d",&x);
        node* nd=newnode(x);
        for(int j=1;j<k;j++)
        {
            int x;
            scanf("%d",&x);
            add(nd,x);
        }
        bool f=false;
        for(int j=0;j<(int)v.size();j++) f|=same(v[j],nd);
        if(!f) v.push_back(nd);
    }
    printf("%d\n",(int)v.size());
    return 0;
}
