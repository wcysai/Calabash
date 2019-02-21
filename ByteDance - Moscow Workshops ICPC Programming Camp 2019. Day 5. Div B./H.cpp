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
int n;
vector<char> v;
vector<char> st;
void dfs(int rem)
{
    if(rem==0)
    {
        for(int i=0;i<(int)v.size();i++) printf("%c",v[i]);
        puts("");
        return;
    }
    if(rem<=(int)st.size())
    {
        if(st.back()=='[') 
        {
            v.push_back(']'); st.pop_back();
            dfs(rem-1); v.pop_back(); st.push_back('[');
        }
        else
        {
            v.push_back(')'); st.pop_back();
            dfs(rem-1); v.pop_back(); st.push_back('(');
        }
    }
    else
    {
        v.push_back('(');st.push_back('('); dfs(rem-1); v.pop_back(); st.pop_back();
        v.push_back('[');st.push_back('['); dfs(rem-1); v.pop_back(); st.pop_back();
        if(st.size()&&st.back()=='(')
        {
            v.push_back(')'); st.pop_back();
            dfs(rem-1);
            v.pop_back(); st.push_back('(');
        }
        if(st.size()&&st.back()=='[')
        {
            v.push_back(']'); st.pop_back();
            dfs(rem-1);
            v.pop_back(); st.push_back('[');
        }
    }
}
int main()
{
    scanf("%d",&n);
    if(n&1||n==0) return 0;
    dfs(n);
    return 0;
}

