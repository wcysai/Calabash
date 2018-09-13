//
// Created by calabash_boy on 18-6-8.
//
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int a,b,c;
bool used[MAXN][MAXN];
int main()
{
    scanf("%d%d%d",&a,&b,&c);
    if(a>=b&&a>=c)
    {
        if(a>b*c) {puts("-1"); return 0;}
        int cnt=a;
        memset(used,false,sizeof(used));
        printf("%d\n",a);
        for(int i=0;i<min(b,c);i++)
        {
            used[i][i]=true;
            printf("%d %d %d\n",i,i,0);
            cnt--;
        }
        if(b>min(b,c))
        {
            for(int i=c;i<b;i++)
            {
                printf("%d %d %d\n", i, 0, 0);
                used[i][0] = true;
                cnt--;
            }
        }
        else
        {
            for(int i=b;i<c;i++)
            {
                printf("%d %d %d\n",0,i,0);
                used[0][i]=true;
                cnt--;
            }
        }
        for(int i=0;i<b;i++)
            for(int j=0;j<c;j++)
            {
                if(cnt==0) break;
                if(used[i][j]) continue;
                printf("%d %d %d\n",i,j,0);
                used[i][j]=true;
                cnt--;
            }
    }
    else if(b>=a&&b>=c)
    {
        if(b>a*c) {puts("-1"); return 0;}
        int cnt=b;
        memset(used,false,sizeof(used));
        printf("%d\n",b);
        for(int i=0;i<min(a,c);i++)
        {
            used[i][i]=true;
            printf("%d %d %d\n",i,0,i);
            cnt--;
        }
        if(a>min(a,c))
        {
            for(int i=c;i<a;i++)
            {
                printf("%d %d %d\n", i, 0, 0);
                used[i][0] = true;
                cnt--;
            }
        }
        else
        {
            for(int i=a;i<c;i++)
            {
                printf("%d %d %d\n",0,0,i);
                used[0][i]=true;
                cnt--;
            }
        }
        for(int i=0;i<a;i++)
            for(int j=0;j<c;j++)
            {
                if(cnt==0) break;
                if(used[i][j]) continue;
                printf("%d %d %d\n",i,0,j);
                used[i][j]=true;
                cnt--;
            }
    }
    else if(c>=b&&c>=a)
    {
        if(c>b*a) {puts("-1"); return 0;}
        int cnt=c;
        memset(used,false,sizeof(used));
        printf("%d\n",c);
        for(int i=0;i<min(a,b);i++)
        {
            used[i][i]=true;
            printf("%d %d %d\n",0,i,i);
            cnt--;
        }
        if(b>min(a,b))
        {
            for(int i=a;i<b;i++)
            {
                printf("%d %d %d\n", 0, 0, i);
                used[0][i] = true;
                cnt--;
            }
        }
        else
        {
            for(int i=b;i<a;i++)
            {
                printf("%d %d %d\n",0,i,0);
                used[i][0]=true;
                cnt--;
            }
        }
        for(int i=0;i<a;i++)
            for(int j=0;j<b;j++)
            {
                if(cnt==0) break;
                if(used[i][j]) continue;
                printf("%d %d %d\n",0,i,j);
                used[i][j]=true;
                cnt--;
            }
    }
    return 0;
}
