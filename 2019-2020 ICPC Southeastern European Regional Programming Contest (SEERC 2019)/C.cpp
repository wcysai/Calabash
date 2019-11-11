#include<bits/stdc++.h>
#define MAXN 256
#define INF 1000000000
#define MOD 10000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,M,tot,t;
int pos,a[MAXN],b[MAXN],id[MAXN];
vector<int> f[10],g[10];
vector<int> all;
int askval(int id)
{
    tot++;
    assert(tot<=30);
    printf("1 %d\n",id);
    fflush(stdout);
    int x;
    scanf("%d",&x);
    return x;
}
vector<int> askdif(vector<int> &v)
{
    int k=(int)v.size();
    if(k<2) return vector<int>();
    tot++;
    assert(tot<=30);
    printf("2 %d",k);
    for(auto x:v) printf(" %d",x);
    printf("\n");
    fflush(stdout);
    vector<int> ret; ret.clear();
    int x;
    for(int i=0;i<k*(k-1)/2;i++)
    {
        scanf("%d",&x);
        ret.push_back(x);
    }
    return ret;
}
vector<int> askdif(int l,int r)
{
    vector<int> v; v.clear();
    for(int i=l;i<=r;i++) v.push_back(i);
    return askdif(v);
}
void answer()
{
    printf("3");
    for(int i=1;i<=n;i++) printf(" %d",a[i]);
    printf("\n");
    fflush(stdout);
    exit(0);
}
int find_maximum(vector<int> v)
{
    int ret=0;
    for(auto x:v) ret=max(ret,x);
    return ret;
}
vector<int> setdif(vector<int> &a,vector<int> &b)//a-b
{
    vector<int> ret; ret.clear();
    sort(a.begin(),a.end()); sort(b.begin(),b.end());
    int i=0,j=0;
    while(i<(int)a.size()&&j<(int)b.size())
    {
        if(a[i]==b[j]) {i++; j++;}
        else {ret.push_back(a[i]); i++;}
    }
    while(i<(int)a.size()) {ret.push_back(a[i]); i++;}
    return ret;
}
vector<int> find_set(vector<int> &id)
{
    vector<int> b=askdif(id);
    id.push_back(pos);
    vector<int> a=askdif(id);
    return setdif(a,b);
}
vector<int> setint(vector<int> &a,vector<int> &b)//a intersect b
{
    vector<int> ret; ret.clear();
    sort(a.begin(),a.end()); sort(b.begin(),b.end());
    int i=0,j=0;
    while(i<(int)a.size()&&j<(int)b.size())
    {
        if(a[i]==b[j]) {ret.push_back(a[i]); i++; j++;}
        else if(a[i]<b[j]) i++;
        else j++;
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    if(n==1)
    {
        a[1]=askval(1);
        answer();
        return 0;
    }
    int M=find_maximum(askdif(1,n));
    int l=1,r=n+1;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(find_maximum(askdif(mid,n))<M) r=mid; else l=mid;
    }
    pos=l;
    int limit=0;
    while((1<<(limit+1))<=n-1) limit++;
    vector<int> ttmp;
    for(int i=1;i<=n;i++) if(i!=pos) ttmp.push_back(i);
    all=find_set(ttmp);
    for(int i=1;i<=n;i++)
    {
        if(i==pos) continue;
        else
        {
            id[i]=++t;
            for(int j=0;j<=limit;j++) if(t&(1<<j)) f[j].push_back(i);
        }
    }
    for(int j=0;j<=limit;j++)
    {
        g[j]=find_set(f[j]);
        f[j]=setdif(all,g[j]);
        swap(f[j],g[j]);
    }
    for(int i=1;i<=n;i++)
    {
        if(i==pos) continue;
        vector<int> tmp; tmp.clear();
        for(int j=0;j<=limit;j++)
        {
            if(id[i]&(1<<j))
            {
                if(!tmp.size()) tmp=f[j];
                else tmp=setint(tmp,f[j]);
            }
            else
            {
                if(!tmp.size()) tmp=g[j];
                else tmp=setint(tmp,g[j]);
            }
        }
        assert(tmp.size()==1);
        b[i]=tmp[0];
    }
    int maxpos=-1,maxi=0;
    for(int i=1;i<=n;i++)
    {
        if(i==pos) continue;
        if(b[i]>maxi)
        {
            maxi=b[i];
            maxpos=i;
        }
    }
    int val1=askval(pos),val2=askval(maxpos);
    a[pos]=val1;
    if(val1>val2)
    {
        for(int i=1;i<=n;i++)
        {
            if(i==pos) continue;
            a[i]=val1-b[i];
        }
    }
    else
    {
        for(int i=1;i<=n;i++)
        {
            if(i==pos) continue;
            a[i]=val1+b[i];
        }
    }
    answer();
    return 0;
}
