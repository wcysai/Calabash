/*************************************************************************
    > File Name: K.cpp
    > Author: Roundgod
    > Mail: wcysai@foxmail.com 
    > Created Time: 2018-05-23 10:15:19
 ************************************************************************/

#include<bits/stdc++.h>
#pragma GCC optimize(3)
#define MAXN 100005
#define MAXK 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],b[MAXN],cnt[7],dp[MAXK][MAXK][MAXK],t;
string str[MAXN];
int find_pos(string x)
{
    bool f=true;
    int pos=1;
    string tt=x,res=x;
    for(int i=0;i<6;i++)
    {
        tt=tt.substr(1,6)+tt[0];
        if(tt!=x) f=false;
        if(tt>res) {res=tt; pos=2+i;}
    }
    if(f) return 0; else return pos;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        cin>>str[i];
    for(int i=0;i<n;i++)
    {
        //printf("%d\n",find_pos(str[i]));
        if(find_pos(str[i])==0) continue; else a[++t]=find_pos(str[i])-1;
    }
    a[++t]=0;
    for(int i=0;i<t;i++)
        b[i]=(a[i+1]-a[i]+7)%7;
    for(int i=0;i<t;i++) cnt[b[i]]++;
    int ans=0;
    int xx=min(cnt[1],cnt[6]); ans+=xx; cnt[1]-=xx;cnt[6]-=xx;
    xx=min(cnt[2],cnt[5]); ans+=xx; cnt[2]-=xx;cnt[5]-=xx;
    xx=min(cnt[3],cnt[4]); ans+=xx; cnt[3]-=xx;cnt[4]-=xx;
    int x,y,z,A,B,C;
    x=cnt[1]?1:6,A=cnt[1]?cnt[1]:cnt[6],y=cnt[2]?2:5,B=cnt[2]?cnt[2]:cnt[5],z=cnt[3]?3:4,C=cnt[3]?cnt[3]:cnt[4];
    int m=0,e[MAXN][4];
    //printf("%d %d %d %d %d %d %d\n",ans,x,y,z,A,B,C);
    for(int i=0;i<=7;i++)
        for(int j=0;j<=7;j++)
            for(int k=0;k<=7;k++)
                if((i*x+j*y+k*z)%7==0&&(i+j+k>0))
                {
                    e[m][0]=i;e[m][1]=j;e[m][2]=k;e[m++][3]=i+j+k-1;
                }
    for(int i=0;i<=A;i++)
        for(int j=0;j<=B;j++)
            for(int k=0;k<=C;k++)
            {
                if(i+j+k>0)
                {
                    int p=INF;
                    for(int l=0;l<m;l++)
                        if(i>=e[l][0]&&j>=e[l][1]&&k>=e[l][2])
                            p=min(p,dp[i-e[l][0]][j-e[l][1]][k-e[l][2]]+e[l][3]);
                    dp[i][j][k]=p;
                }
                //printf("%d %d %d %d\n",i,j,k,dp[i][j][k]);
            }
    printf("%d\n",dp[A][B][C]+ans);
    return 0;
}
