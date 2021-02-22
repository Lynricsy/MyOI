#define ll long long
#define inf 0x3f3f3f3f
#define N 500010

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

int totN;
int c[N][2];
long long DP[N][2];
int superflag=0;
long long rot;
char s[N];

inline void DFS1(int &x)
{
	x = ++superflag;
	if (s[x] == '0')
		return;
	if (s[x] >= '1')
		DFS1(c[x][0]);
	if (s[x] == '2')
		DFS1(c[x][1]);
}
inline void DFS2(int x)
{
	DP[x][1] = 1;
	DP[x][0] = 0;
	if (c[x][0])
		DFS2(c[x][0]);
	if (c[x][1])
		DFS2(c[x][1]);
	DP[x][1] += DP[c[x][0]][0] + DP[c[x][1]][0];
	DP[x][0] = max(DP[c[x][0]][1] + DP[c[x][1]][0], DP[c[x][0]][0] + DP[c[x][1]][1]);
}
inline void DFS3(int x)
{
	DP[x][1] = 1;
	DP[x][0] = 0;
	if (c[x][0])
		DFS3(c[x][0]);
	if (c[x][1])
		DFS3(c[x][1]);
	DP[x][1] += DP[c[x][0]][0] + DP[c[x][1]][0];
	DP[x][0] = min(DP[c[x][0]][1] + DP[c[x][1]][0], DP[c[x][0]][0] + DP[c[x][1]][1]);
}
int main()
{
	scanf("%s", s + 1);
	totN = strlen(s + 1);
	DFS1(rot);
	DFS2(rot);
	printf("%d ", max(DP[rot][0], DP[rot][1]));
	memset(DP, 0, sizeof(DP));
	DFS3(rot);
	printf("%d\n", min(DP[rot][0], DP[rot][1]));
	return 0;
}