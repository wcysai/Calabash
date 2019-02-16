//
// Created by bytedance on 19-2-16.
//
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5005 + 10;
char s[maxn];
int n;
struct SAM{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    bool vis[maxn*2];
    int cntA[maxn*2],A[maxn*2];
    int num[maxn*2];
    vector<ll> sum[maxn*2];
    SAM(){clear();}
    void clear(){
        last = cnt = 1;
        fa[1] = l[1] = 0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s){
        while (*s){
            add(*s - 'a');
            s ++;
        }
    }
    void add(int c){
        int p = last ;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] + 1;
        last = np;
        while (p && !nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] + 1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] + 1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (nxt[p][c] == q)nxt[p][c] = nq,p = fa[p];
            }
        }
    }
    void dfs( int u){
        for (int i=0;i<26;i++){
            int Nxt = nxt[u][i];
            if (Nxt == 0)continue;
            if (!vis[Nxt])dfs(Nxt);
            for (int L = l[fa[u]]+ 1;L <= l[u];L++){
                sum[u][L - l[fa[u]]-1] += sum[Nxt][L+1 - l[fa[Nxt]]-1];
            }
        }
        for (int L = l[fa[u]] + 1;L <= l[u];L ++){
            sum[u][L - l[fa[u]]-1] += 1ll * num[u] * L;
        }
        vis[u] = 1;
    }
    void debug(){
        for (int i=1;i<=cnt;i++){
            for (int j=l[fa[i]] + 1;j <= l[i];j++){
                printf("sum[%d][%d]=%lld\n",i,j,sum[i][j]);
            }
        }
        for (int i=1;i<=cnt;i++){
            printf("l[%d]=%d num[%d]=%d\n",i,l[i],i,num[i]);
        }
    }
    void build(){

        for (int i=1;i<=cnt;i++){
            cntA[i] = num[i] =0;
            sum[i].resize(l[i] - l[fa[i]] + 2,0);
            for (int j=0;j<sum[i].size();j++){
                sum[i][j] = 0;
            }
            sum[i].shrink_to_fit();
            vis[i] = 0;
        }
        for (int i=1;i<=cnt;i++){
            cntA[l[i]] ++;
        }
        for (int i=1;i<=cnt;i++)cntA[i] += cntA[i-1];
        for (int i=cnt;i>=1;i--)A[cntA[l[i]] --] = i;
        int temp = 1;
        for (int i=0;i<n;i++){
            num[temp = nxt[temp][s[i] - 'a']] = 1;
        }
        for (int i=cnt;i>=1;i--){
            int x = A[i];
            num[fa[x]] += num[x];
        }
        dfs(1);
    }
    char query(ll pos){
        string temp = "";
        int now = 1;
        while (1){
            ll t_cnt = 1ll * temp.size() * num[now];
            if (pos <=t_cnt){
                return temp[(pos-1)%temp.size()];
            }else{
                pos -= t_cnt;
                for (int i=0;i<26;i++){
                    int Nxt = nxt[now][i];
                    if (Nxt == 0)continue;
                    if (pos <= sum[Nxt][temp.size()- l[fa[Nxt]]]){
                        now = Nxt;
                        temp += i+'a';
                        break;
                    }else{
                        pos -= sum[Nxt][temp.size() - l[fa[Nxt]]];
                    }
                }
            }
        }
    }
}sam;
char ans[maxn];
int main(){
    int Case = 1;
    int q;
    while (scanf("%d",&q)!= EOF && q){
        scanf("%s",s);
        n = strlen(s);
        sam.clear();
        sam.init(s);
        sam.build();
        //sam.debug();
        int idx = 0;
        while (q--){
            ll pos;
            scanf("%lld",&pos);
            ans[idx++] = sam.query(pos);
        }
        ans[idx] = '\0';
        printf("Case #%d: %s\n",Case++,ans);
    }
    return 0;
}
