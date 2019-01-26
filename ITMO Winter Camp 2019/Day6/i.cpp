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
const int maxn = 4e6;
typedef bitset<maxn> bs;
bs a[10][14];
bs aa[10][14];
vector<int> num;
void init(){
    num.resize(11);
    for (int i=0;i<maxn;i++){
        //vector<int> nums = work(i);
        for (int j=0;j<10;j++){
            num[j] = 0;
        }
        ll tmp = i;
        while (tmp){
            num[tmp%10]++;
            tmp /=10;
        }
        for (int j=0;j<10;j++){
            for (int k=num[j];k<14;k++){
                a[j][k].set(i);
            }
        }
        for (int j=0;j<10;j++){
            num[j] = 0;
        }
        tmp = 1ll * i * i;
        while (tmp){
            num[tmp%10] ++;
            tmp/=10;
        }
        for (int j=0;j<10;j++){
            for (int k = num[j];k<14;k++){
                aa[j][k].set(i);
            }
        }
    }
}
void solve(ll x){
    printf("Hidden squares in %lld\n",x);
    bs b;
    for (int i=0;i<10;i++){
        num[i] = 0;
    }
    ll tmp = x;
    while (tmp){
        num[tmp%10]++;
        tmp/=10;
    }
    b = ~b;
    for (int i=0;i<10;i++){
        b &= aa[i][num[i]];
        b &= a[i][num[i]];
    }
    for (int i=0;i<maxn;i++){
        if (b[i] &&(i == 0 && num[0] || i !=0)){
            printf("%d * %d = %lld\n",i,i,1ll * i * i);
        }
    }

}
//int n,k,a[MAXN];
int main()
{
    freopen("interesting.in","r",stdin);
    freopen("interesting.out","w",stdout);
    init();
    //cerr<<"init finished"<<endl;
    ll x;
    bool first = true;
    while (scanf("%lld",&x) != EOF && x != 0){
       // if (first){
       //     first = false;
       // }else{
      //      puts("");
       // }
        solve(x);
    }
    return 0;
}

