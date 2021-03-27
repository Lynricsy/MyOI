/*---------------------------------
 *Title number: L2OJ 
 *Creation date: 2021.3
 *Author: EdisonBa 
 *-------------------------------*/
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stack>
#include <cmath>
#include <queue>
#include <map>
#define Ba 0
#define Edison return
#define rint register int
#define ull unsigned long long
using namespace std;
typedef long long ll;

inline ll read()
{
    ll x = 0, f = 0;
    char ch = getchar();
    while (!isdigit(ch))
        f |= (ch == '-'), ch = getchar();
    while (isdigit(ch))
        x = (x << 1) + (x << 3) + (ch ^= 48), ch = getchar();
    return f ? -x : x;
}


const ll mod=1e9+7;

string s,ak;
ll len,n,a[502],ans;

ll f(ll x)
{
    ll anss=a[0];
    ll xx=1;
    for(int i=1;i<n;++i)
    {
        xx*=x;
         xx%=mod;
        if(a[i]==0) continue;
        anss+=a[i]*xx;
        anss%=mod;
    }
    return anss;
}

void make_s()
{
    s="a";
    for(int i=1;i<=len;++i)
    {
        string k=s;
        for(int j=0;j<k.size();++j)
        {
            if(k[j]=='a') k[j]='b';
            else k[j]='a';
            s.push_back(k[j]);
        }
    }
}

void k_1()
{
    n=read();//n->10
    ll a0;
    a0=read();
    n=0;
    char ch;
    for (int i = 0; i < len; i++)
    {
        ch = ak[i];
        n = (n << 1) + (ch ^ 48);
        if(i!=len-1)
        {
            n%=mod;
        }
    }
    n/=2;
    n%=mod;
    ans=(n*a0)%mod;
    printf("%lld\n",ans);
    // cout<<n<<endl;
    // cout<<"233"<<endl;
}

int main()
{
    freopen("angry.in","r",stdin);
    freopen("angry.out","w",stdout);
    cin>>ak;
    len=ak.size(); //size/length
    
    if(len>500)
    {
        k_1();
        return 0;
    }

    make_s();
    //    cout<<s;
    n=read();
    for(int i=0;i<n;++i)
    {
        a[i]=read();
    }

    ll nn=0; //->10

    for(int i=0;i<len;++i)
    {
        if(ak[i]=='1')
        {
            nn+=(1<<(len-i-1));
        }
    }
    //   cout<<nn<<endl;

    for(int i=0;i<nn;++i)
    {
        if(s[i]=='b')
        {
            // cout<<i<<endl;
            ans+=f(i);
            // ans%=mod;
        }
    }
    printf("%lld\n",ans%mod);
    Edison Ba;
}
/*
1001011001101001
16
1 0 0 1 0 1 1 0 0 1 1 0 1 0 0 1

11111100101
4
2 0 2 1

1000
3
3 2 1
for (int i = 0; i < len; i++)
{
    ch = s[i];
    n = (n << 1) + (ch ^ 48);
}
*/
