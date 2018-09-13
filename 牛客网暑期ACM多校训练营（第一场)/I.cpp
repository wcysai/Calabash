//
// Created by calabash_boy on 18-6-4.
//SPOJ substring
// calc ans_i=长度=i的所有子串，出现次数最多的一种出现了多少次。
//
#include<bits/stdc++.h>
#define int LL
using namespace std;
typedef long long LL;
const int maxn = 40e4+100;
char s[maxn];
int Ch[6][300];
int T=1;
/*注意需要按l将节点基数排序来拓扑更新parent树*/
struct Suffix_Automaton{
    //basic
    int nxt[maxn*2][3],fa[maxn*2],l[maxn*2];
    int last,cnt;
    //extension
    int num[maxn*2];/*每个节点代表的所有串的出现次数*/
    int Done[maxn*2];
    void clear(){
        last =cnt=1;
        fa[1]=l[1]=0;
        memset(nxt[1],0,sizeof nxt[1]);
    }
    void init(char *s,int mod){
        while (*s){
            add(Ch[mod][*s]-'a');
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p]+1;
        last = np;
        while (p&&!nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np]=1;
        else{
            int q = nxt[p][c];
            if (l[q]==l[p]+1)fa[np] =q;
            else{
                int nq = ++ cnt;
                l[nq] = l[p]+1;
                memcpy(nxt[nq],nxt[q],sizeof (nxt[q]));
                fa[nq] =fa[q];
                fa[np] = fa[q] =nq;
                while (nxt[p][c]==q)nxt[p][c] =nq,p = fa[p];
            }
        }
    }
    int dfs(int x){
        Done[x] = T;
        int ans =l[x]-l[fa[x]];
        for (int i=0;i<3;i++){
            if (nxt[x][i]&&Done[nxt[x][i]]!=T){
                ans+=dfs(nxt[x][i]);
            }
        }
        return ans;
    }
    int query(){
        int ans = dfs(1);
        int now =1;
        while (1){
            if (nxt[now][0]){
                now = nxt[now][0];
                ans+=l[now]-l[fa[now]];
            }else{
                break;
            }
        }
        now =1;
        while (1){
            if (nxt[now][1]){
                now = nxt[now][1];
                ans+=l[now]-l[fa[now]];
            }else{
                break;
            }
        }
        now =1;
        while (1){
            if (nxt[now][2]){
                now = nxt[now][2];
                ans+=l[now]-l[fa[now]];
            }else{
                break;
            }
        }
        //assert((ans)%6==0);
        return (ans)/6;
    }
    void debug(){
        for (int i=cnt;i>=1;i--){
            printf("num[%d]=%d l[%d]=%d fa[%d]=%d\n",i,num[i],i,l[i],i,fa[i]);
        }
    }
}sam;
signed main(){
    int len;
    Ch[0]['a']='a';
    Ch[0]['b']='b';
    Ch[0]['c']='c';
 
    Ch[1]['a']='a';
    Ch[1]['b']='c';
    Ch[1]['c']='b';
 
    Ch[2]['a']='b';
    Ch[2]['b']='a';
    Ch[2]['c']='c';
 
    Ch[3]['a']='b';
    Ch[3]['b']='c';
    Ch[3]['c']='a';
 
    Ch[4]['a']='c';
    Ch[4]['b']='b';
    Ch[4]['c']='a';
 
    Ch[5]['a']='c';
    Ch[5]['b']='a';
    Ch[5]['c']='b';
 
    while (scanf("%lld",&len)!=EOF){
        T++;
        scanf("%s",s);
        sam.clear();
        for (int i=0;i<6;i++){
            sam.init(s,i);
            sam.last =1;
        }
        printf("%lld\n",sam.query());
    }
    return 0;
}
