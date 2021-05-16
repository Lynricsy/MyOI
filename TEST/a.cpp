#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define INF 999999999

using namespace std;

inline long long read()
{
    long long x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
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
void write(const long long &x)
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

long long totN;
long long totK;
long long amatix[509][509];
long long ematix[509][509];
long long cmatix[509][509];
long long treat[10090];
const long long MOD=998244353;

long long ultra_quick_pow(long long a,long long ci)
{
	if(a==1)
	{
		return 1;
	}
	else if(!ci)
	{
		return 1;
	}
	long long base=a%MOD;
	long long result=1;
	while(ci)
	{
		if(ci&1)
		{
			result*=base;
			result%=MOD;
		}
		base=(base*base)%MOD;
		ci>>=1;
	}
	return result%MOD;
}

void egnmatix()
{
	for(long long i=1;i<=totN;++i)
	{
		ematix[i][i]=1;
		for(int j=i-1;j>=1;--j)
		{
			long long secret_key=0;
			long long mitm_key=ultra_quick_pow((treat[i]-amatix[j][j]+MOD),MOD-2);
			for(int k=j+1;k<=i;++k)
			{
				secret_key=(secret_key + (long long)amatix[j][k] * ematix[k][i])% MOD;
			}
			ematix[j][i]=(long long)(secret_key*mitm_key)%MOD;
		}
	}
}
void jdnmatix()
{
	for(int i=totN;i>=1;--i)
	{
		cmatix[i][i]=ultra_quick_pow(ematix[i][i],MOD-2);
		for(int j=1;j<i;++j)
		{
			long long extra_key=(long long)ematix[j][i]*ultra_quick_pow(ematix[j][j],MOD-2)%MOD;
			for(int k=i;k<=totN;++k)
			{
				cmatix[j][k]-=(long long)cmatix[i][k]*extra_key%MOD;
				if(cmatix[i][j]<0)
				{
					cmatix[i][j]+=MOD;
				}
			}
		}
	}
}

void rent()
{
	for(int i=1;i<=totN;++i)
	{
		for(int j=i;j<=totN;++j)
		{
			ematix[i][j]=(long long )ematix[i][j]*treat[j]%MOD;
		}
	}
	for(int i=1;i<=totN;++i)
	{
		for(int j=i;j<=totN;++j)
		{
			amatix[i][j]=0;
			for(int k=i;k<=j;++k)
			{
				amatix[i][j]=(amatix[i][j]+ematix[i][k]*cmatix[k][j])%MOD;
			}
		}
	}
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	totN=read();
	totK=read();
	for(int i=1;i<=totN;++i)
	{
		for(int j=1;j<=totN;++j)
		{
			amatix[i][j]=read()%MOD;
		}
		treat[i]=amatix[i][i];
	}
	egnmatix();
	jdnmatix();
	for(int i=1;i<=totN;++i)
	{
		treat[i]=ultra_quick_pow(treat[i],totK)%MOD;
	}
	rent();
	long long sum=0;
	long long ssas=0;
    for(int i=1;i<=totN;++i)
	{
		for(int j=1;j<=totN;++j)
		{
			if(amatix[i][j]<0)
            {
                amatix[i][j]+=MOD;
            }
		}
	}
	for(int i=1;i<=totN;++i)
	{
		for(int j=i;j<=totN;++j)
		{
			sum+=amatix[i][j]%MOD;
			ssas^=amatix[i][j]%MOD;
		}
	}
	printf("%lld %lld",sum,ssas);
}
//https://foxex-my.sharepoint.com/personal/i_foxex_cn/_layouts/15/download.aspx?UniqueId=7f5c7e98-8fe5-412a-94e3-dbab8f1e9c00&Translate=false&tempauth=eyJ0eXAiOiJKV1QiLCJhbGciOiJub25lIn0.eyJhdWQiOiIwMDAwMDAwMy0wMDAwLTBmZjEtY2UwMC0wMDAwMDAwMDAwMDAvZm94ZXgtbXkuc2hhcmVwb2ludC5jb21AZGRiMWJjZDUtZmU3Mi00NDU3LWFjZmUtNmNmZWFiYTgxMWUxIiwiaXNzIjoiMDAwMDAwMDMtMDAwMC0wZmYxLWNlMDAtMDAwMDAwMDAwMDAwIiwibmJmIjoiMTYyMTE0OTg1NSIsImV4cCI6IjE2MjExNTM0NTUiLCJlbmRwb2ludHVybCI6ImgvM1NHanFUZEQwUURhUXRuRHd4anhqb3FOZG00U1B1ZGNKN2ptMFk5Ym89IiwiZW5kcG9pbnR1cmxMZW5ndGgiOiIxMzkiLCJpc2xvb3BiYWNrIjoiVHJ1ZSIsImNpZCI6Ik1EaG1ZV1ppTUdJdFkySm1NaTAwTUdRMUxUaGtZemN0TjJJeU4yWm1NR1EzWWpnNSIsInZlciI6Imhhc2hlZHByb29mdG9rZW4iLCJzaXRlaWQiOiJZV0k0TTJSbU1qY3RNbUZoWVMwMFlXUXhMVGcwWTJJdE5UZG1abU0xWVRCbFpqbGoiLCJhcHBfZGlzcGxheW5hbWUiOiJvbmVpbmRleCIsImdpdmVuX25hbWUiOiLpn7XmtrUiLCJmYW1pbHlfbmFtZSI6IueOiyIsInNpZ25pbl9zdGF0ZSI6IltcImttc2lcIl0iLCJhcHBpZCI6IjNlODI2NzgyLTExZjgtNGY2OC05ZGQxLWUwZjBmNWYyZTViMSIsInRpZCI6ImRkYjFiY2Q1LWZlNzItNDQ1Ny1hY2ZlLTZjZmVhYmE4MTFlMSIsInVwbiI6ImlAZm94ZXguY24iLCJwdWlkIjoiMTAwMzIwMDBBQjE4Qzc3MCIsImNhY2hla2V5IjoiMGguZnxtZW1iZXJzaGlwfDEwMDMyMDAwYWIxOGM3NzBAbGl2ZS5jb20iLCJzY3AiOiJhbGxmaWxlcy53cml0ZSIsImFjcnMiOiJyMSxyMixyMyxjMSxjMixjMyIsInR0IjoiMiIsInVzZVBlcnNpc3RlbnRDb29raWUiOm51bGx9.WjI5WFJodE5mMVphNkdFQjU5NmpnYlBuTlBWTE9xZzZjc25PekhveEVsND0&ApiVersion=2.0