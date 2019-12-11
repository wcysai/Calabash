#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,N,a[MAXN];
string str;
vector<int> v;
int maxdif(string str)//if we can remain a 1
{
    int cnt0=0,cnt1=0;
    for(int i=0;i<(int)str.size();i++) if(str[i]=='1') cnt1++; else cnt0++;
    int s=0;
    v.clear();
    for(int i=0;i<(int)str.size();i++)
    {
        if(str[i]=='1')
        {
            if(s!=1) v.push_back(s);
            s=0;
        }
        else 
        {
            s++;
            if(s>2)
            {
                s-=2;
                cnt0-=2;
            }
        }
    }
    v.push_back(s);
    s=0;
    for(int i=0;i<(int)v.size();i++)
    {
        s+=v[i];
        if(s>2)
        {
            s-=2;
            cnt0-=2;
        }
        s--;
        if(s<0) s=0;
    }
    return cnt1-cnt0;
}
void flip(string &str)
{
    for(int i=0;i<(int)str.size();i++) if(str[i]=='0') str[i]='1'; else str[i]='0';
}
int ans[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&N);
        for(int i=1;i<=N;i++) scanf("%d",&a[i]);
        string s,t;
        for(int i=1;i<=N;i++) 
        {
            s=""; t="";
            for(int j=1;j<i;j++) if(a[j]<=a[i]) s+='0'; else s+='1';
            for(int j=i+1;j<=N;j++) if(a[j]<=a[i]) t+='0'; else t+='1';
            if(maxdif(s)+maxdif(t)<0) {ans[i]=0; continue;}
            flip(s); flip(t);
            if(maxdif(s)+maxdif(t)<0) ans[i]=0; else ans[i]=1;
        }
        for(int i=1;i<=N;i++) printf("%d",ans[i]);
        puts("");
    }
}