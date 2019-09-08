#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string s,t;
int gr[MAXN][26];
int main()
{
    scanf("%d%d",&n,&m);
    cin>>s; cin>>t;
    for(int i=0;i<26;i++) gr[n][i]=n;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<26;j++) gr[i][j]=gr[i+1][j];
        int id=s[i]-'a';
        for(int j=0;j<id;j++) gr[i][j]=i;
    }
    int ans=-1;
    int now=0;
    if(gr[0][t[0]-'a']!=n) ans=max(ans,n-gr[0][t[0]-'a']);
    for(int i=0;i<m;i++)
    {
        while(now<n&&s[now]!=t[i]) now++;
        if(now==n) break;
        if(i!=m-1)
        {
            int pos=gr[now+1][t[i+1]-'a'];
            if(pos!=n) ans=max(ans,n-pos+(i+1));
        }
        else if(now!=n-1) ans=max(ans,n-now+i);
        now++;
    }
    printf("%d\n",ans);
    return 0;
}
