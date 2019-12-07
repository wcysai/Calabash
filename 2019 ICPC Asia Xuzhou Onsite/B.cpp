#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000000000000LL
#define BASE 19260817
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<int> vec;
typedef vector<vec> mat;
int T,N,K,tot;
vector<int> perm;
int ans[4][MAXN];
bool used[MAXN];
mat trans;
map<int,int> mp;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int v[32],tmp[32];
int pos1[10][2]
{
0,0,
0,3,
0,4,
1,0,
2,1,
2,2,
3,1,
4,4,
};
int pos2[100][2]
{
0,0,
0,8,
0,23,
1,0,
2,0,
2,8,
2,23,
3,2,
4,2,
4,7,
4,25,
5,2,
5,7,
5,25,
6,5,
6,16,
7,5,
7,14,
8,5,
8,11,
8,14,
8,16,
8,20,
8,26,
8,27,
9,3,
9,4,
9,9,
9,10,
9,12,
9,18,
9,19,
9,22,
10,4,
10,9,
11,4,
11,12,
12,1,
12,17,
13,1,
14,1,
14,6,
14,17,
14,29,
15,3,
15,10,
16,3,
16,18,
17,11,
17,26,
18,6,
18,29,
19,13,
19,21,
20,13,
21,15,
22,15,
23,24,
23,28,
23,30,
24,23,
25,30,
26,25,
27,29,
28,26,
28,27,
29,24,
30,24,
30,28,
30,30,
};
mat mul(mat &A,mat &B)
{
    mat C(A.size(),vec(B[0].size()));
    for(int i=0;i<(int)A.size();i++)
        for(int k=0;k<(int)B.size();k++)
        {
            if(!A[i][k]) continue;
            for(int j=0;j<(int)B[0].size();j++) 
                C[i][j]=(C[i][j]+1LL*A[i][k]*B[k][j])%MOD;
        }
    return C;
}
int get_hash(vector<int> &v)
{
    bool f=true;
    for(int i=1;i<(int)v.size();i++)
        if(max(v[i]-v[i-1],v[i-1]-v[i])>K) {f=false; break;}
    if(!f) return -1;
    vector<int> v1,v2; v1.clear(); v2.clear();
    int k1=0,k2=0,cnt=0;
    for(int i=0;i<(int)v.size();i++)
    {
        if(v[i]>=(int)v.size()+1-K)
        {
            if(i==0) k1=1;
            if(i==(int)v.size()-1) k2=1;
            v1.push_back(v[i]-(v.size()-K));
            cnt++;
            if(cnt>1)
            {
                if(v[i-1]>=(int)v.size()+1-K) v2.push_back(1); else v2.push_back(0); 
            }
        }
    }
    if(v1[0]>v1.back()) {reverse(v1.begin(),v1.end()); reverse(v2.begin(),v2.end()); swap(k1,k2);}
    v2.push_back(k1); v2.push_back(k2);
    int cur=0;
    for(auto it:v1) cur=(1LL*cur*BASE+it)%MOD;
    for(auto it:v2) cur=(1LL*cur*BASE+it)%MOD;
    if(mp.find(cur)==mp.end()) mp[cur]=tot++;
    return mp[cur]; 
}
int main()
{
    ans[1][1]=1;
    for(int i=2;i<=1000000;i++) ans[1][i]=2;
    for(K=2;K<=3;K++)
    {
        mp.clear(); tot=0;
        ans[K][0]=1;
        for(int N=1;N<=K;N++) ans[K][N]=ans[K][N-1]*N;
        perm.clear();
        for(int i=1;i<=2*K+1;i++) perm.push_back(i);
        trans.clear();
        trans.resize(100);
        for(int i=0;i<100;i++) trans[i].resize(100);
        memset(used,false,sizeof(used));
        do
        {
            int num=get_hash(perm);
            if(num==-1||used[num]) continue;
            used[num]=true;
            for(int i=0;i<2*K+2;i++)
            {
                perm.insert(perm.begin()+i,2*K+2);
                int num2=get_hash(perm);
                perm.erase(perm.begin()+i);
                if(num2!=-1) trans[num2][num]++;
            }
        }while(next_permutation(perm.begin(),perm.end()));
        trans.resize(tot);
        for(int i=0;i<tot;i++) trans[i].resize(tot);
        perm.clear();
        for(int i=1;i<=K+1;i++) perm.push_back(i);
        memset(v,0,sizeof(v));
        do
        {
            int num=get_hash(perm);
            if(num!=-1) v[num]++;
        }while(next_permutation(perm.begin(),perm.end()));
        for(int N=K+1;N<=1000000;N++)
        {
            for(int i=0;i<tot;i++) add(ans[K][N],v[i]);
            memset(tmp,0,sizeof(tmp));
            if(K==3)
            {
                for(int i=0;i<70;i++) add(tmp[pos2[i][0]],v[pos2[i][1]]);
            }
            else for(int i=0;i<8;i++) add(tmp[pos1[i][0]],v[pos1[i][1]]); 
            for(int i=0;i<tot;i++) v[i]=tmp[i];
        }
    }
    scanf("%d",&T);
    for(int i=0;i<T;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",ans[y][x]);
    }
    return 0;
}