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
inline double dread()
{
    double r;
    double x = 0, t = 0;
    int s = 0, f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
    {
        if (c == '-')
        {
            f = -1;
        }
        if (c == '.')
        {
            goto readt;
        }
    }
    for (; isdigit(c) && c != '.'; c = getchar())
    {
        x = x * 10 + c - '0';
    }
    readt:
    for (; c == '.'; c = getchar())
        ;
    for (; isdigit(c); c = getchar())
    {
        t = t * 10 + c - '0';
        ++s;
    }
    r = (x + t / pow(10, s)) * f;
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
inline void write(double x, int k)
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
    if (x < 0)
        putchar('-'), x = -x;
    long long y = (long long)(x * n) % n;
    x = (long long)x;
    dwrite(x), putchar('.');
    int bit[10], p = 0, i;
    for (; p < k; y /= 10)
        bit[++p] = y % 10;
    for (i = p; i > 0; i--)
        putchar(bit[i] + 48);
}

const int maxN=109;
char A[maxN], B[maxN];
int totN;
int totM;
int Z[maxN], P[maxN];
int ansZ,ansP;

inline void Zfun()
{
    for (int i = 1; i <= totN; ++i)
    {
        Z[i] = 0;
    }
    Z[1] = totN;
    for (int i = 2, l = 0, r = 0; i <= totN; ++i)
    {
        if (i<=r)
        {
            Z[i]=min(Z[i-l+1],r-i+1);
        }
        while(i+Z[i]<=totN&&A[i+Z[i]]==A[Z[i]+1])
        {
            ++Z[i];
        }
        if(l+Z[i]-1>r)
        {
            l=i;
            r=l+Z[i]-1;
        }
    }
}
inline void Pfun()
{
	for (int i = 1; i <= totN; ++i)
	{
		P[i] = 0;
	}
	for (int i = 1, l = 0, r = 0; i <= totN; ++i)
	{
		if (i<=r)
		{
			P[i]=min(l+P[i]-1,r-i+1);
		}
		while(i+P[i]<=totN&&B[i+P[i]]==A[P[i]+1])
		{
			++P[i];
		}
		if(l+P[i]-1>r)
		{
			l=i;
			r=l+P[i]-1;
		}
	}
}

int main()
{
    scanf("%s", B + 1);
    scanf("%s", A + 1);
    A[0]=45;
    B[0]=45;
    totN = strlen(A)-1;
    totM = strlen(B)-1;
    Zfun();
    Pfun();
	for (int i = 2; i <= totN; ++i)
	{
		ansZ^=i*(Z[i]+1);
	}
	for (int i = 2; i <= totN; ++i)
	{
		ansP^=i*(P[i]+1);
	}
	write(ansZ);
	putchar('\n');
	write(ansP);
    return 0;
} //Thomitics Code
 /*
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

typedef long long int ll;

namespace OPT
{
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	int top=0;
	do {OPT::buf[++top] = static_cast<char>(x % 10 + '0');} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 20000007;

char S[maxn], T[maxn];
int z[maxn], ans[maxn];

int Init(char *p);
void Z_algorithm(char *const s, char *const t, const int n, const int m, int *const ret);
void Print(int *const A, const int n);

int main()
{
	int n = Init(S + 1);
	int m = Init(T + 1);
	Z_algorithm(T, T, m, m, z);
	Z_algorithm(S, T, n, m, ans);
	Print(z, m);
	Print(ans, n);
	return 0;
}

int Init(char *p)
{
	scanf("%s", p);
	return strlen(p);
}

void Z_algorithm(char *const s, char *const t, const int n, const int m, int *const ret)
{
	int p = 1, q = 1;
	if (s == t)
	{
		ret[1] = n;
		while (s[q + 1] == s[q]) ++q;
		ret[p = 2] = q - 1;
	} else
	{
		while ((q <= n) && (s[q] == t[q])) ++q;
		ret[p] = --q;
	}
	if (q < p) q = p;
	for (int i = 2 + (s == t), j; i <= n; ++i)
	{
		j = i - p + 1;
		if ((i + z[j] - 1) < q)
		{
			ret[i] = z[j];
		} else
		{
			int Ans = q - i + 1;
			while ((q < n) && (Ans < m) && (s[q + 1] == t[Ans + 1]))
			{
				++q;
				++Ans;
			}
			ret[p = i] = Ans;
			if (q < i) q = i;
		}
	}
}

void Print(int *const A, const int n)
{
	ll Ans = 0;
	for (ll i = 1; i <= n; ++i)
	{
		Ans ^= i * (A[i] + 1);
	}
	qw(Ans, '\n', true);
}*/