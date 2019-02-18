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
double H;
mt19937 wcy(time(NULL));
vector<char> v;
double cnt[100];
const double eps=0.005;
int magic;
int myrand(int x)
{
    if(x==0) return 0;
    for(int k=0;k<magic;k++)
        x=wcy()%x+1;
    return x;
}
int main()
{
    for(int i=0;i<10;i++) v.push_back('0'+i);
    for(int i=0;i<26;i++) v.push_back('a'+i);
    for(int i=0;i<26;i++) v.push_back('A'+i);
    v.push_back('.'); v.push_back(' ');
    scanf("%lf",&H);
    magic=20;
    for(int iter=0;iter<1000;iter++)
    {
        double maxx=0,minx=INF;
        for(int k=0;k<20;k++)
        {
            int ch=64,sum=0;
            for(int i=0;i<ch;i++)
            {
                cnt[i]=myrand(1000-sum);
                sum+=cnt[i];
            }
            double ans=0;
            for(int i=0;i<ch;i++) 
            {
                double p=cnt[i]/sum;
                if(p!=0) ans-=p*log2(p);
            }
            maxx=max(maxx,ans);minx=min(minx,ans);
            if(fabs(ans-H)<eps)
            {
                for(int i=0;i<ch;i++)
                    for(int j=0;j<cnt[i];j++)
                        printf("%c",v[i]);
                puts("");
                return 0;
            }
        }
        if(minx>H) magic--; else if(maxx<H) magic++;
    }
    return 0;
}


