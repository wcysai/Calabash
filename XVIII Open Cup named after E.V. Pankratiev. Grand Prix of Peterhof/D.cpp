#include<bits/stdc++.h>
#define MAXN 40
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
int ans;
struct node
{
    vector<int> v;
    int layer;
    void init()
    {
        for(int i=0;i<35;i++) v.push_back(0);
        layer=0;
    }
    void spin()
    {
        if(layer==0) return;
        v[layer]--;
        int tmp=layer;
        while(tmp>0&&v[tmp]<0)
        {
            v[tmp]+=3; v[tmp-1]--;
            tmp--;
        }
        v[0]=0;
    }
    void antispin()
    {
        if(layer==0) return;
        v[layer]++;
        int tmp=layer;
        while(tmp>0&&v[tmp]>=3)
        {
            v[tmp]-=3; v[tmp-1]++;
            tmp--;
        }
        v[0]=0;
    }
    void centrifugal()
    {
        layer++;
    }
    void gravitational()
    {
        layer--;
    }
    void process(string str)
    {
        init();
        for(int i=0;i<(int)str.size();i++) 
        {
            if(str[i]=='c') centrifugal();
            else if(str[i]=='g') gravitational();
            else if(str[i]=='s') spin();
            else antispin();
        }
    }
    bool equal(node &rhs)
    {
        if(layer!=rhs.layer) return false;
        for(int i=layer;i>=0;i--) if(v[i]!=rhs.v[i]) return false;
        return true;
    }
    int find_clockwise_dist(node &rhs)
    {
        int cnt=0;
        while(!equal(rhs))
        {
            spin(); 
            cnt++; 
            if(cnt>ans) return -1;
        }
        return cnt;
    }
    int find_counterclockwise_dist(node &rhs)
    {
        int cnt=0;
        while(!equal(rhs))
        {
            antispin(); 
            cnt++; 
            if(cnt>ans) return -1;
        }
        return cnt;
    }
}a,b;
string s,t;
map<char,char> rev;
string opts;
string movea,moveb;
void downto(node &x,int l,string &save)
{
    while(x.layer>l)
    {
        if(x.v[x.layer]==2) {x.antispin(); save+='a';}
        else if(x.v[x.layer]==1) {x.spin(); save+='s';}
        x.gravitational(); save+='g';
    }
}
void init()
{
    rev['s']='a'; rev['a']='s'; rev['c']='g'; rev['g']='c';
}
string reversed_string(string str)
{
    string ret="";
    int sz=(int)str.size();
    for(int i=sz-1;i>=0;i--) ret+=rev[str[i]];
    return ret;
}
int main()
{
    init();
    cin>>s; cin>>t;
    a.process(s); b.process(t);
    bool rever=false;
    if(a.layer>b.layer) {swap(a,b); swap(s,t); rever=true;}
    ans=(int)s.size()+(int)t.size();
    opts=reversed_string(s)+t;
    for(int i=0;i<=a.layer;i++)
    {
        node tmpa=a,tmpb=b;
        movea=moveb="";
        downto(tmpa,i,movea);  downto(tmpb,i,moveb);
        if((int)movea.size()+(int)moveb.size()>=ans) continue;
        node dummy=tmpa;
        int cld=dummy.find_clockwise_dist(tmpb);
        dummy=tmpa;
        int ctd=dummy.find_counterclockwise_dist(tmpb);
        if(cld>=0&&(int)movea.size()+(int)moveb.size()+cld<ans)
        {
            ans=(int)movea.size()+(int)moveb.size()+cld;
            string cur=movea;
            for(int j=0;j<cld;j++) cur+='s';
            cur+=reversed_string(moveb);
            opts=cur;
        }
        if(ctd>=0&&(int)movea.size()+(int)moveb.size()+ctd<ans)
        {
            ans=(int)movea.size()+(int)moveb.size()+ctd;
            string cur=movea;
            for(int j=0;j<ctd;j++) cur+='a';
            cur+=reversed_string(moveb);
            opts=cur;
        }
    }
    if(!rever) cout<<opts<<endl; else cout<<reversed_string(opts)<<endl;
    return 0;
}
