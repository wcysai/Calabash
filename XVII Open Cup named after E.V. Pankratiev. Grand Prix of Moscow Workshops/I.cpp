#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e7 + 100;
typedef unsigned int uint;
const uint seed = 10099;
uint x0,a,x1,b,c;
int n,q;
uint nxt(){
    uint t = x0 * a + x1 * b + c;
    x0 = x1;
    x1 = t;
    return x0 >> 2;
}
uint Ans[maxn*5];
uint A[maxn];
uint min_val = (1ll<<31)-1;
int ans_idx = 0;
int main(){
    cin>>n>>q>>x0>>x1>>a>>b>>c;
    for (int i=0;i<n;i++){
        A[i] = (1ll<<31) - 1;
    }
    uint ans = 0;
    for (int i=1;i<=q;i++){
        uint idx = nxt() % n;
        uint val = nxt();
        if (idx != ans_idx){
            A[idx] = val;
            if (A[idx] < min_val){
                min_val = A[idx];
                ans_idx = idx;
            }
        }else{
            if (val <= min_val){
                min_val = val;
                A[idx] = val;
            }else{
                A[idx] = val;
                min_val = A[0];
                ans_idx = 0;
                for (int i=1;i<n;i++){
                    if (A[i] < min_val){
                        min_val = A[i];
                        ans_idx = i;
                    }
                }
            }
        }
        Ans[i] = min_val;
        //ans = ans * seed + min_val; 
    }
    uint base = seed;
    for (int i=1;i<=q;i++){
        ans += base * Ans[i];
        base *= seed;
    }
    cout<<ans<<endl;
    return 0;


}
