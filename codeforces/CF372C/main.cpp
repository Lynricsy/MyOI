/*
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

#pragma region DEFINE
int totN;
int totM;
int totD;
int A[100090];
int B[100090];
int T[100090];
int DP[2][100090];
deque<int> Q;
bool flag = true;
int totANS = -INF;
#pragma endregion

void init()
{
	memset(DP, 207, sizeof(DP));
	for (int i = 1; i <= totN; i++)
	{
		DP[0][i] = 0;
	}
	flag = true;
}

void DPing()
{
	for (int i = 1; i <= totM; ++i)
	{
		int k = 1;
		for (int j = 1; j <= totN; j++)
		{
			for (; k <= min(totN, j + (T[i] - T[i - 1]) * totD); k++)
			{
				while (!Q.empty() && DP[(!flag)][k] >= DP[(!flag)][Q.back()])
				{
					Q.pop_back();
				}
				Q.push_back(k);
			}
			while (!Q.empty() && Q.front() < min(1, j - (T[i] - T[i - 1]) * totD))
			{
				Q.pop_front();
			}
			DP[flag][j] = DP[(!flag)][Q.back()] + B[i] - abs(A[i] - j);
		}
		flag ^= 1;
		Q.clear();
	}
}

int main()
{
	init();
	totN = read();
	totM = read();
	totD = read();
	for (int i = 1; i <= totM; ++i)
	{
		A[i] = read();
		B[i] = read();
		T[i] = read();
	}
	DPing();
	for (int i = 1; i <= totN; ++i)
	{
		totANS = max(totANS, DP[(!flag)][i]);
	}
	write(totANS);
	return 0;
} //Thomitics Code
*/
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

#pragma region DEFINE
int totN;
int totM;
int totD;
int A[100090];
int B[100090];
int T[100090];
int DP[2][100090];
deque<int> Q;
bool flag = true;
int totANS = -INF;
#pragma endregion

void init()
{
//	memset(DP, 207, sizeof(DP));
	for (int i = 0; i <= totN; i++)
	{
		DP[0][i] = 0;
	}
	flag=true;
}

void DPing()
{
	for (int i = 1; i <= totM; ++i)
	{
		memset(DP[flag], -0x3f, sizeof(DP[flag]));
		for (int j = 1; j <= totN; j++)
		{
			while (!Q.empty() && Q.front() < j - (T[i] - T[i - 1]) * totD) Q.pop_front();
//			while(!Q.empty()&&Q.front()<j+(T[i]-T[i-1])*totD) Q.pop_front();
			while (!Q.empty() && DP[!flag][j] >= DP[!flag][Q.back()]) Q.pop_back();
			Q.push_back(j);
			DP[flag][j] = max(DP[flag][j], DP[!flag][Q.front()] + B[i] - abs(A[i] - j));
		}
		flag = !flag;
		Q.clear();
	}
}

int main()
{
	init();
	totN = read();
	totM = read();
	totD = read();
	for (int i = 1; i <= totM; ++i)
	{
		A[i] = read();
		B[i] = read();
		T[i] = read();
	}
	DPing();
	for (int i = 1; i <= totN; ++i)
	{
		totANS = max(totANS, DP[!flag][i]);
	}
	write(totANS);
	return 0;
} //Thomitics Code