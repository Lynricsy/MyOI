#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <map>
#include <queue>
using namespace std;
typedef long long ll;
inline int read()
{
	int x = 0, f = 1;
	char ch = getchar();
	while (!isdigit(ch))
	{
		if (ch == '-')
			f = -1;
		ch = getchar();
	}
	while (isdigit(ch))
	{
		x = x * 10 + ch - 48;
		ch = getchar();
	}
	return x * f;
}
map<int, int> dfsaofief;
int n, len;
int pweomrqic[200005], qwericunwaex[200005], p2[200005], wer98m23498x4e[200005], asdjfoenwfoejfoifnasdoif[200005];
bool cmp(int a, int b)
{
	return a < b;
}
int main()
{
	//	freopen("mc10.in","r",stdin);
	//	freopen("mc10.out","w",stdout);
	n = read();
	for (int i = 1; i <= n; i++)
	{
		pweomrqic[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		qwericunwaex[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		p2[i] = read();
	}
	for (int i = 1; i <= n; i++)
	{
		dfsaofief[pweomrqic[i]] = i;
	}
	for (int i = 1; i <= n; i++)
	{
		wer98m23498x4e[i] = dfsaofief[p2[i]];
	}
	len = 1, asdjfoenwfoejfoifnasdoif[1] = wer98m23498x4e[1];
	for (int i = 2; i <= n; i++)
	{
		if (wer98m23498x4e[i] > asdjfoenwfoejfoifnasdoif[len])
		{
			asdjfoenwfoejfoifnasdoif[++len] = wer98m23498x4e[i];
		}
		else
		{
			int k = lower_bound(asdjfoenwfoejfoifnasdoif + 1, asdjfoenwfoejfoifnasdoif + 1 + len, wer98m23498x4e[i]) - asdjfoenwfoejfoifnasdoif;
			asdjfoenwfoejfoifnasdoif[k] = wer98m23498x4e[i];
		}
	}
	printf("%d\n", len);
	return 0;
}
