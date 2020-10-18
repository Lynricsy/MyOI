#ifdef ONLINE_JUDGE
#pragma GCC optimize(2)
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(3)
#endif // ONLINE_JUDGE

#include <bits/stdc++.h>

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch>'9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = (x << 1) + (x << 3) + (ch ^ 48);
        ch = getchar();
    }
    return x * f;
}
void write(const long long& x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    char f[100];
    long long tmp = x;
    if (tmp < 0)
    {
        tmp = -tmp;
        putchar('-');
    }
    long long s = 0;
    while (tmp > 0)
    {
        f[s++] = tmp % 10 + '0';
        tmp /= 10;
    }
    while (s > 0)
    {
        putchar(f[--s]);
    }
}
inline double dread()
{
    double r;
    double x=0,t=0;
    int s=0,f=1;
    char c=getchar();
    for (;!isdigit(c);c=getchar())
    {
        if (c=='-')
        {
            f=-1;
        }
        if (c=='.')
        {
            goto readt;
        }
    }
    for (;isdigit(c)&&c!='.';c=getchar())
    {
        x=x*10+c-'0';
    }
    readt:
    for (;c=='.';c=getchar());
    for (;isdigit(c);c=getchar())
    {
        t=t*10+c-'0';
        ++s;
    }
    r=(x+t/pow(10,s))*f;
    return r;
}

inline void dwrite(long long x)
{
    if (x == 0)
    {
        putchar(48);
        return;
    }
    int bit[20], p = 0, i;
    for (; x; x /= 10) 
        bit[++p] = x % 10;
    for (i = p; i > 0; --i) 
        putchar(bit[i] + 48);
}
inline void write(double x,int k)
{
    static int n = pow(10, k);
    if (x == 0)
    {
        putchar('0');
        putchar('.');
        for (int i = 1; i <= k; ++i) 
            putchar('0');
        return;
    }
    if (x < 0) putchar('-'), x = -x;
    long long y = (long long) (x * n) % n;
    x = (long long) x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10) 
        bit[++p] = y % 10;
    for (i = p; i > 0; i--) 
        putchar(bit[i] + 48);
}

char minstr[10005];

char a[10005],b[10005];
int c[5005],d[5005],e[10005];
char chengres[10005];
int chengcnt;
int u,v,w;
char s33[10005];
int aa[10005],bb,cc[10005],x=0;
char s1[10005],s2[10005],s3[10005];
void cheng()
{
	int i,j;
	memcpy(a,s33,sizeof(s33));
	memcpy(b,minstr,sizeof(minstr));
    u=strlen(a);
    v=strlen(b);
    memset(c,0,4005);
    for(int i=0;i<u;i++)
        c[u-1-i]=a[i]-'0';
    for(int i=0;i<v;i++)
        d[v-1-i]=b[i]-'0';
    for(i=0;i<u;i++)
	{
        for(j=0;j<v;j++)
		{
            w=c[i]*d[j];
            if(e[i+j]+w<10)    e[i+j]+=w;
            else
			{
                e[i+j+1]+=(e[i+j]+w)/10;
                e[i+j]=(e[i+j]+w)%10;
            }
        }
    }
    for(i=u+v-1;i>0&&e[i]==0;i--);
    for(;i>=0;i--)    chengres[chengcnt++]=e[i]+'0';
}

char see[10005];

void chu()
{
	x=0;
	bb=2;
	memcpy(see,chengres,sizeof(chengres));
    aa[0]=strlen(see);
    for(int i=1;i<=aa[0];i++)
	   aa[i]=see[i-1]-48;
    memset(cc,0,sizeof(cc));
    for(int i=1;i<=aa[0];i++)
	{
        cc[i]=(x*10+aa[i])/bb;
        x=(x*10+aa[i])%bb;
    }
    x=1;
    while(cc[x]==0&&x<aa[0])    x++;
    for(;x<=aa[0];x++)    putchar(cc[x]+'0');
}

bool compare(char s1[],char s2[]){
    int u=strlen(s1),v=strlen(s2);
    if(u!=v)
        return u>v;
    for(int i=0;i<u;i++)
        if(s1[i]!=s2[i])    return s1[i]>s2[i];
    return true;
}

void jian()
{
    int flag=1,i,j;
    memcpy(s1,minstr,sizeof(minstr));
    memset(s2,0,sizeof(s2));
    s2[0]='1';
    if(compare(s1,s2));
    else{
        flag=-1;
        strcpy(s3,s1);
        strcpy(s1,s2);
        strcpy(s2,s3);
    }
    int u=strlen(s1),v=strlen(s2);
    for(i=u-1,j=v-1;j>=0;i--,j--){
        if(s1[i]<s2[j]){
            s1[i-1]-=1;
            s3[i]=s1[i]-s2[j]+10+'0';
        }
        else    s3[i]=s1[i]-s2[j]+'0';
    }
    for(;i>=0;i--)    {
        if(s1[i]<'0'){
            s1[i-1]-=1;
            s3[i]=s1[i]+10;
        }
        else    s3[i]=s1[i];
    }  
    for(i=0;i<u-1&&s3[i]=='0';i++);
    if(flag==-1)    cout<<'-';
    memcpy(s33,s3+i,sizeof(s3));
}

int totT;

int main()
{
	totT=read();
	for(int i=1;i<=totT;i++)
	{
		cin>>minstr;
		jian();
		cheng();
		chu();
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		memset(d,0,sizeof(d));
		memset(e,0,sizeof(e));
		memset(chengres,0,sizeof(chengres));
		memset(s33,0,sizeof(s33));
		memset(aa,0,sizeof(aa));
		memset(cc,0,sizeof(cc));
		memset(s1,0,sizeof(s1));
		memset(s2,0,sizeof(s2));
		memset(s3,0,sizeof(s3));
		chengcnt=0;
		putchar('\n');
	}
    return 0;
}//LikiBlaze Code

