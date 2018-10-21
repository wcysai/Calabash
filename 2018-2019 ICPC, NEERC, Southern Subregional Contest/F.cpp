#pragma  GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef long double db;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
const int inf = 0x3f3f3f3f;

#define PB(x) push_back(x)
#define rep(i,l,r) for (ll i = l,_ = r;i< _;i++)
#define REP(i,l,r) for (ll i=l,_=r;i<=_;i++)
#define leave(x) do {cout<<#x<<endl;fflush(stdout);return 0;}while (0);
#define untie do{ios::sync_with_stdio(false);cin.tie(nullptr);cout.tie(nullptr);}while (0)

/************* header ******************/
const int maxn = 4e5+100;
int n;
vector<ll> a[4];
vector<ll> sum[4];
int atomask(string & mask){
    int ret = 0;
    if (mask[0] - '0')ret += 2;
    if (mask[1] - '0')ret += 1;
    return ret;
}
ll work(){
    vector<ll> max_val(maxn,-1);
    rep(i,0,min(a[3].size(),a[0].size())){
        ll sum_val = sum[3].back() + sum[0][i];
        int delta = a[3].size() - i -1;
        max_val[delta] = sum_val;
    }
    if (a[3].size())
    max_val[a[3].size()] = sum[3].back();
    max_val[0] = max(max_val[0],0ll);
    for (int i=maxn-2;i>=0;i--){
        max_val[i] = max(max_val[i],max_val[i+1]);
    }
    ll ans = max_val[0];
    REP(i,0,min(a[1].size(),a[3].size())){
        ll sum_val = max_val[i];
        if (sum_val == -1)continue;
        int x = min((int)a[1].size(),(int)a[2].size() + (int)i);
        if (x>=0 && x - i>=0){
            if (x >=1)
            sum_val += sum[1][x-1];
            if (x-i>=1)
            sum_val += sum[2][x - i -1];
            ans = max(ans,sum_val);
        }
       // cerr<<x<<" "<<sum_val<<endl;
    }
    return ans;
}
int main(){
    untie;
    cin>>n;
    rep(i,0,n){
        string mask;
        ll val;
        cin>>mask>>val;
        int tar = atomask(mask);
        a[tar].push_back(val);
        sum[tar].push_back(0);
    }
    if (a[3].size() == 0 && 1ll * a[1].size() * a[2].size() == 0)return puts("0"),0;
    rep(i,0,4){
        if (a[i].size() == 0)continue;
        sort(a[i].begin(),a[i].end(),[](ll x,ll y){return x>y;});
        sum[i][0] = a[i][0];
        rep(j,1,a[i].size()){
            sum[i][j] = sum[i][j-1] + a[i][j];
        }
    }
    ll ans = work();
    swap(a[2],a[1]);
    swap(sum[2],sum[1]);
    ans = max(ans,work());
    cout<<ans<<endl;
    return 0;
}
