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

const long long maxN = 1000090;
long long totN;
char KICK[maxN];
long double F;
long double nowLEN;

int main()
{
	totN = read();
	scanf("%s", KICK + 1);
	for (int i = 1; i <= totN; i++)
	{
		if (KICK[i] == '?')
		{
			F = F + nowLEN + 1.0 / 2.0;
			nowLEN = (nowLEN + 1.0) / 2.0;
		}
		else if (KICK[i] == 'x')
		{
			nowLEN = 0;
		}
		else
		{
			F = F + nowLEN * 2.0 + 1.0;
			nowLEN += 1.0;
		}
	}
	printf("%.4Lf", F);
	return 0;
} //Thomitics Code