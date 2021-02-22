#include<bits/stdc++.h>

using namespace std;

unsigned long long read() {
	unsigned long long x=0;
	int f=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {
		if(ch=='-') {
			f=-1;
		}
		ch=getchar();
	}
	while(ch>='0'&&ch<='9') {
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*f;
}
void write(const __int128_t& x)
{
    if (!x)
    {
        putchar('0');
        return;
    }
    char f[100];
    __int128_t tmp = x;
    if (tmp < 0)
    {
        tmp = -tmp;
        putchar('-');
    }
    __int128_t s = 0;
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

int totN;
int totM;
int totC;
int totK;
__int128_t firstTOT;
__int128_t A[1000090];
__int128_t cntANS;
__int128_t FANS;
__int128_t ONE=1;
bool needing[1000];

int main() {
	//freopen()
	totN=read();
	totM=read();
	totC=read();
	totK=read();
	for(register int i=1; i<=totN; ++i) {
		A[i]=read();
		firstTOT|=A[i];
	}
	for(register int i=1; i<=totM; ++i) {
		int x=read();
		needing[x]=true;
		read();
	}
	for(register int i=0; i<=totK-1; ++i) {
		if((!needing[i])||firstTOT&(ONE<<i)) {
			++cntANS;
		}
	}
	FANS=((ONE<<cntANS)-(__int128_t)totN);
	printf("%llu",FANS);
	return 0;
}
