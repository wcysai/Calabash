#pragma GCC optimize(3)
#include <bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 100;
const int inf = 0x3f3f3f3f;
int n,l,r;
int a[maxn];
int sum[maxn];
int dp[maxn];
struct Node{
    int Idx;
    int Sum;
    int Min[20];
    bool operator < (const Node &other)const{
        return Idx < other.Idx;
    }
    Node(int idx){
        Idx = idx;
        Sum = sum[idx];
        Min[0]  = Sum;
    }
};
map<int,vector<Node> > mp;
struct SegmentTree{
    pair<int,int> Max[maxn * 4];
    void build(int x,int l,int r){
        if (l == r){
            Max[x] = make_pair(-inf,-inf);
            return;
        }
        int mid = l + r >> 1;
        build(x<<1,l,mid);
        build(x<<1|1,mid+1,r);
        up(x);
    }
    /*
    pair<int,int> merge(pair<int,int> p1,pair<int,int> p2){
        vector<int> nums(0);
        nums.push_back(p1.first);
        nums.push_back(p1.second);
        nums.push_back(p2.first);
        nums.push_back(p2.second);
        sort(nums.begin(),nums.end(),[](int x,int y){
            return x > y; 
        });
        nums.erase(unique(nums.begin(),nums.end()),nums.end());
        if (nums.size() >= 2){
            return make_pair(nums[0],nums[1]);
        }else{
            return make_pair(nums[0],-inf);
        }

    }
    */
    pair<int,int> merge(pair<int,int>  p1,pair<int,int> p2){
        if (p1.first < p2.first)swap(p1,p2);
        pair<int,int> ans = make_pair(p1.first,-inf);
        if (p2.first == p1.first){
            ans.second = max(ans.second,max(p1.second,p2.second));
        }else{
            ans.second = max(ans.second,max(p1.second,p2.first));
        }
        return ans;


    }
    void up(int x){
        Max[x] = merge(Max[x<<1],Max[x<<1|1]);       
    }
    void update(int x,int l,int r,int pos,int val){
        if (l == r){
            Max[x].first = max(Max[x].first,val);
            return;
        }
        int mid = l + r >> 1;
        if (pos <= mid) update(x << 1,l,mid,pos,val);
        else update(x << 1| 1,mid+1,r,pos,val);
        up(x);
    }
    pair<int,int> query(int x,int l,int r,int L,int R){
        if (l > R || L > r)return make_pair(-inf,-inf);
        if (L <= l && r <= R)return Max[x];
        int mid =l + r >> 1;
        pair<int,int> lans = query(x << 1,l,mid,L,R);
        pair<int,int> rans = query(x << 1 | 1,mid + 1,r,L,R);
        return merge(lans,rans);
    }
}tree;
int gao(int i,int Max,int L,int R){
    int Sum = sum[i];
    vector<Node> & vec = mp[Max];
    Node nl = Node(L);
    Node nr = Node(R);
    int idxl = lower_bound(vec.begin(),vec.end(),nl) - vec.begin();
    int idxr = upper_bound(vec.begin(),vec.end(),nr) - vec.begin() - 1;
    if (idxl > idxr)assert(0);
    int len = idxr - idxl + 1;
    int base = 20;
    while ((1<< base) > len)base --;
    int block = 1 << base;
    int min_sum = min(vec[idxr].Min[base],vec[idxl + block - 1].Min[base]);
    if(Sum > min_sum)return Max + 1;
    if (Sum == min_sum)return Max;
    return Max - 1;
}
void add(int i){
    Node node = Node(i);
    int dpval = dp[i];
    vector<Node> &vec = mp[dpval];
    vec.push_back(node);
    for (int i=1;i<20;i++){
        int len = 1 << (i-1);
        if (len+1 > vec.size())break;
        vec[vec.size() -1].Min[i] = min(vec[vec.size()-1].Min[i-1],vec[vec.size()-1 - len].Min[i-1]);
    }
}
int main(){
    scanf("%d%d%d",&n,&l,&r);
    for (int i=1;i<=n;i++){
        scanf("%d",a+i);
        sum[i] = sum[i-1] + a[i];
    }
    for (int i=1;i<=n;i++)dp[i] = -inf;
    dp[0] = 0;
    mp[0].push_back(Node(0));
    tree.build(1,0,n);
    tree.update(1,0,n,0,0);
    for (int i=1;i<=n;i++){
        if (i < l)continue;
        int L = max(0,i - r);
        int R = max(0,i-l);
        pair<int,int> Max = tree.query(1,0,n,L,R);
        if (Max.first != -inf){
            dp[i] = max(dp[i],gao(i,Max.first,L,R));
        }
        if (Max.second != -inf){
            dp[i] = max(dp[i],gao(i,Max.second,L,R));
        }
        tree.update(1,0,n,i,dp[i]);
        if (dp[i] != -inf){
            add(i);
        }
    }
    int Ans = tree.query(1,0,n,n,n).first;
    if (Ans  == -inf){
        puts("Impossible");
    }else{
        cout<<Ans<<endl;
    }
    return 0;
}
