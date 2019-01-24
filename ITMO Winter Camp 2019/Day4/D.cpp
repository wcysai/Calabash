#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 14
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<int> ans;
vector<int> tmp;
int main()
{
    int n;
    cin>>n;
    ans =  {0,1,3,2};
    for (int i=2;i<n;i++){
        tmp.clear();
        int dig = 0;
        if (i % 2 == 0){
            for (int x : ans){
                tmp.push_back(x << 1);
            }
            for (int x : ans){
                tmp.push_back(x << 1 |1);
            }
        }else{

            for (int x : ans){
                tmp.push_back(x << 1| dig);
                dig ^=1;
            }
            dig ^=1;
            for (int x : ans){
                tmp.push_back(x<<1 |dig);
                dig ^=1;
            }
        }
        ans = tmp;
    }
    for (int i=0;i<ans.size();i++){
        int x = ans[i];
        for (int j=0;j<n;j++){
            int dig = x & 1;
            x >>=1;
            printf("%d",dig);
        }
        puts("");
    }
    return 0;
}

