//
// Created by sy-chen on 18-5-20.
//

#include<bits/stdc++.h>
#define MAXN 400005
#define MAXM 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
const double PI=acos(-1.0);
struct Complex
{
    double x,y;
    Complex(double _x=0.0,double _y=0.0)
    {
        x=_x;
        y=_y;
    }
    Complex operator-(const Complex &b)const
    {
        return Complex(x-b.x,y-b.y);
    }
    Complex operator+(const Complex &b)const
    {
        return Complex(x+b.x,y+b.y);
    }
    Complex operator*(const Complex &b)const
    {
        return Complex(x*b.x-y*b.y,x*b.y+y*b.x);
    }
};
void change(Complex y[],int len)
{
    int i,j,k;
    for(int i=1,j=len/2;i<len-1;i++)
    {
        if (i < j) swap(y[i], y[j]);
        k = len / 2;
        while (j >= k) {
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}
void fft(Complex y[],int len,int on)
{
    change(y,len);
    for(int h=2;h<=len;h<<=1)
    {
        Complex wn(cos(-on*2*PI/h),sin(-on*2*PI/h));
        for(int j=0;j<len;j+=h)
        {
            Complex w(1,0);
            for(int k=j;k<j+h/2;k++)
            {
                Complex u=y[k];
                Complex t=w*y[k+h/2];
                y[k]=u+t;
                y[k+h/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
        for(int i=0;i<len;i++)
            y[i].x/=len;
}
int dbit(int x)
{
    while(x!=(x&-x)) x+=(x&-x);
    return x;
}
int n,m;
char str1[100005],str2[100005];
Complex A[MAXN],B[MAXN];
int ans[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    scanf("%s",str1);
    scanf("%s",str2);
    int len=dbit(n+m);
    for(int i=0;i<n;i++) A[i]=str1[i]=='S'?Complex(1,0):Complex(0,0);
    for(int i=n;i<len;i++) A[i]=Complex(0,0);
    for(int i=0;i<m;i++) B[i]=str2[m-1-i]=='R'?Complex(1,0):Complex(0,0);
    for(int i=m;i<len;i++) B[i]=Complex(0,0);
    fft(A,len,1);fft(B,len,1);
    for(int i=0;i<len;i++)
        A[i]=A[i]*B[i];
    fft(A,len,-1);
    for(int i=m-1;i<n+m-1;i++)
        ans[i]+=(int)(A[i].x+0.5);
    for(int i=0;i<n;i++) A[i]=str1[i]=='R'?Complex(1,0):Complex(0,0);
    for(int i=n;i<len;i++) A[i]=Complex(0,0);
    for(int i=0;i<m;i++) B[i]=str2[m-1-i]=='P'?Complex(1,0):Complex(0,0);
    for(int i=m;i<len;i++) B[i]=Complex(0,0);
    fft(A,len,1);fft(B,len,1);
    for(int i=0;i<len;i++)
        A[i]=A[i]*B[i];
    fft(A,len,-1);
    for(int i=m-1;i<n+m-1;i++)
        ans[i]+=(int)(A[i].x+0.5);
    for(int i=0;i<n;i++) A[i]=str1[i]=='P'?Complex(1,0):Complex(0,0);
    for(int i=n;i<len;i++) A[i]=Complex(0,0);
    for(int i=0;i<m;i++) B[i]=str2[m-1-i]=='S'?Complex(1,0):Complex(0,0);
    for(int i=m;i<len;i++) B[i]=Complex(0,0);
    fft(A,len,1);fft(B,len,1);
    for(int i=0;i<len;i++)
        A[i]=A[i]*B[i];
    fft(A,len,-1);
    for(int i=m-1;i<n+m-1;i++)
        ans[i]+=(int)(A[i].x+0.5);
    int res=0;
    for(int i=m-1;i<n+m-1;i++)
        res=max(res,ans[i]);
    printf("%d\n",res);
    return 0;
}
