#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
const int maxn = 4e5+100;
const int inf = 0x3f3f3f3f;
struct Node{
    int x,y,z,id;
};
vector<Node> a1(0),a2(0);
bool cmp(Node p,Node q)
{
    if(p.x!=q.x) return p.x<q.x;
    return p.y<q.y;
}
struct SAM{
    int nxt[maxn*2][26],fa[maxn*2],l[maxn*2];
    int last,cnt;
    int pos1[maxn*2],pos2[maxn*2];
    int cntA[maxn*2],A[maxn*2];
    SAM(){
        last = cnt = 1;
        memset(nxt[1],0,sizeof nxt[1]);
        fa[1] = l[1] = 0;
        memset(pos1,inf,sizeof pos1);
        memset(pos2,inf,sizeof pos2);
    }
    void init(char *s){
        while (*s){
            int id = *s - 'a';
            add(id);
            s++;
        }
    }
    void add(int c){
        int p = last;
        int np = ++cnt;
        memset(nxt[cnt],0,sizeof nxt[cnt]);
        l[np] = l[p] +1;
        last = np;
        while (p && !nxt[p][c])nxt[p][c] = np,p = fa[p];
        if (!p)fa[np] = 1;
        else{
            int q = nxt[p][c];
            if (l[q] == l[p] +1)fa[np] = q;
            else{
                int nq = ++cnt;
                l[nq] = l[p] +1;
                memcpy(nxt[nq],nxt[q],sizeof nxt[q]);
                fa[nq] = fa[q];
                fa[np] = fa[q] = nq;
                while (nxt[p][c] == q)nxt[p][c] = nq,p = fa[p];
            }
        }
    }
    vector<Node> extract(char *s,int lens,char *t,int lent,bool reverse = false){
        for (int i=1;i<=cnt;i++)cntA[l[i]] ++;
        for (int i=1;i<=cnt;i++) cntA[i] += cntA[i-1];
        for (int i=cnt;i>=1;i--)A[cntA[l[i]]--] = i;
        vector<Node> res(0);
        int temp = 1;
        for (int i=0;i<lens;i++){
            pos1[temp = nxt[temp][s[i] - 'a']] = i+1;
        }
        temp = 1;
        for (int i=0;i<lent;i++){
            pos2[temp = nxt[temp][t[i] - 'a']] = i+1;
        }
        int id = 0;
        for (int i=cnt;i>=2;i--){
            int x = A[i];
            pos1[fa[x]] = min(pos1[fa[x]],pos1[x]);
            pos2[fa[x]] = min(pos2[fa[x]],pos2[x]);
            if (pos1[x] == inf || pos2[x] == inf)continue;
            if (!reverse)
                res.push_back((Node){pos1[x],pos2[x],l[x],id});
            else
                res.push_back((Node){lens- pos1[x],lent-pos2[x],l[x],id});
            id++;
        }
        return res;
    }
}sam1,sam2;
char s[maxn],t[maxn],rs[maxn],rt[maxn];
int lens,lent;
struct segtree
{
    P val[8*maxn];
    void pushup(int k)
    {
        val[k]=max(val[k*2],val[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        val[k]=P(0,-1);
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int p,P x)
    {
        assert(p<=2*maxn);
        if(l==r) {val[k]=max(val[k],x); return;}
        int mid=(l+r)/2;
        if(p<=mid) update(k*2,l,mid,p,x); else update(k*2+1,mid+1,r,p,x);
        pushup(k);
    }
    P query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return P(0,-1);
        if(l>=x&&r<=y) return val[k];
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
P solve()
{
    sort(a1.begin(),a1.end(),cmp);
    sort(a2.begin(),a2.end(),cmp);
    int sz1=(int)a1.size();
    int sz2=(int)a2.size();   
    seg.build(1,1,2*maxn);
    int now=0,ans=0;
    P save=P(-1,-1);
    for(int i=0;i<sz2;i++)
    {
        while(now<sz1&&a1[now].x<=a2[i].x) {seg.update(1,1,2*maxn,a1[now].y,P(a1[now].z,a1[now].id)); now++;}
        P p=seg.query(1,1,2*maxn,1,a2[i].y);
        if(p.F+a2[i].z>ans) {ans=p.F+a2[i].z; save=P(p.S,a2[i].id);}
    }
    return save;
}
void print(char *s,const vector<Node> & a,int id,int suffix = false){
    if (id == -1){
        puts("");
        return;
    }
    for (auto node :a){
        //cerr<<node.id<<" ||"<<id<<endl;
        if (node.id == id){
            if (!suffix){
                int r = node.x;
                int l = r-node.z+1;
     //           cerr<<l<<" "<<r<<endl;
                for (int i=l;i<=r;i++){
                    printf("%c",s[i]);
                }
                puts("");
            }else{
                int l = node.x+1;
                int r = l + node.z -1;
       //         cerr<<"  "<<l<<" "<<r<<endl;
                for (int i=l;i<=r;i++){
                    printf("%c",s[i]);
                }
                puts("");
            }
            return;
        }
    }
}
int main(){
    scanf("%s",s+1);
    strcpy(rs+1,s+1);
    lens = strlen(s+1);
    reverse(rs+1,rs+1+lens);
    scanf("%s",t+1);
    strcpy(rt+1,t+1);
    lent = strlen(t+1);
    reverse(rt+1,rt+1+lent);
    sam1.init(s+1);
    sam1.last =1;
    sam1.init(t+1);
    sam2.init(rs+1);
    sam2.last = 1;
    sam2.init(rt+1);
    a1 = sam1.extract(s+1,lens,t+1,lent);
    a2 = sam2.extract(rs+1,lens,rt+1,lent,true);
  //  cerr<<"a1:"<<endl;
  //  for (auto tmp: a1){
  //      cerr<<tmp.x<<" "<<tmp.y<<" "<<tmp.z<<" "<<tmp.id<<endl;
  //  }
  //  cerr<<"a2:"<<endl;
  //  for (auto tmp : a2){
  //      cerr<<tmp.x<<" "<<tmp.y<<" "<<tmp.z<<" "<<tmp.id<<endl;
  //  }
//    cerr<<"init finished"<<endl;
    auto ans = solve();
//    cerr<<ans.first<<" "<<ans.second<<endl;
    print(s,a1,ans.first);
    print(s,a2,ans.second,true);
    //cout<<solve()<<endl;
    return 0;
} 
