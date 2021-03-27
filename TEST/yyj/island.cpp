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

const ll N=100002;

ll n,q,a[N],b[N];

int main()
{
    freopen("island.in","r",stdin);
    freopen("island.out","w",stdout);
    n=read(); q=read();
    for(int i=1;i<=n;++i)
    {
        a[i]=read();
        b[i]=read();
    }
    for(int i=1;i<=q;++i)
    {
        ll l,r,c,d;
        ll ans=0;
        l=read();
        r=read();
        c=read();
        d=read();
        for(int i=l;i<=r;++i)
        {
            if((a[i]^c)<=min(b[i],d)) ans++;
        }
        printf("%lld\n",ans);
    }

    Edison Ba;
}
/*
4 2
1 1
4 2
5 1
2 7
1 4 6 5
2 4 3 3
*/
/*
20 10
215 144
2 110
174 132
214 142
116 108
155 192
236 208
216 214
99 220
236 118
190 81
230 131
10 238
189 198
183 13
45 193
14 234
208 192
126 19
49 38
7 14 251 184
2 18 89 76
11 15 49 196
8 11 83 139
10 15 119 239
9 16 148 120
11 17 225 34
15 16 3 46
14 15 86 227
7 18 252 103
*/