#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
string str[MAXN];
vector<int> v1,v2;
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<n;i++) cin>>str[i];
    bool f=true;
    int cnt=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++) if(str[i][j]=='1') cnt++;
        if(cnt==k) {v1.push_back(i); cnt=0;}
        if(cnt>k) {f=false; break;}
    }
    if(cnt!=0) f=false;
    if(!f) {puts("NO"); return 0;}
    cnt=0;
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++) if(str[j][i]=='1') cnt++;
        if(cnt==k) {v2.push_back(i); cnt=0;}
        if(cnt>k) {f=false; break;}
    }
    if(cnt!=0) f=false;
    if(!f) {puts("NO"); return 0;}
    for(int i=0;i<k;i++)
        for(int j=0;j<k;j++)
        {
            int x1=(i==0)?0:v1[i-1]+1,y1=(j==0)?0:v2[j-1]+1;
            int x2=v1[i],y2=v2[j];
            int cnt=0;
            for(int a=x1;a<=x2;a++)
                for(int b=y1;b<=y2;b++)
                    if(str[a][b]=='1') cnt++;
            if(cnt!=1) f=false;
        }
    if(!f) {puts("NO"); return 0;}
    puts("YES");
    for(int i=0;i<k-1;i++) printf("%d\n",v1[i]+1);
    for(int i=0;i<k-1;i++) printf("%d\n",v2[i]+1);
    return 0;
}
