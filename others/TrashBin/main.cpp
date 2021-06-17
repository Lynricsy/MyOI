#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<queue>
#include<vector>
#define ll long long
#define ull unsigned long long
using namespace std;
const int N=500005;
const ull p=13331;
int tot;
int pri[N];
bool v[N];
vector<int> zhi[N];
void pre(){
	for(int i=2;i<=N;i++){
		zhi[i].push_back(1);
		if(!v[i]){
			v[i]=1;
			zhi[i].push_back(i);
			for(int j=2*i;j<=N;j+=i){
				zhi[j].push_back(i);
				v[j]=1;
			}
		}
	}
}
int n,q,ans;
ull mi[N],sum[N];
char s[N];
ull Hash(int l,int r){
	return sum[r]-sum[l-1]*mi[r-l+1];
}
bool check(int l,int r,int len)
{
	for (int i = l; i <= r - len; i += len)
	{
		if (Hash(i, i + len - 1) != Hash(i + len, i + 2 * len - 1))
			return false;
	}
	return true;
}
int main()
{
	pre();
	scanf("%d", &n);
	scanf("%s", s + 1);
	scanf("%d", &q);

	mi[0] = 1;
	for (int i = 1; i <= n; i++)
	{
		mi[i] = mi[i - 1] * p;
	}

	for (int i = 1; i <= n; i++)
	{
		sum[i] = sum[i - 1] * p + (ull) (s[i] - 'a');
	}

	while (q--)
	{
		int l, r;
		scanf("%d%d", &l, &r);

		if (l > r) swap(l, r);

		int len = r - l + 1;

		ans = len;

		for (int i = 0; i < (int) zhi[len].size(); i++)
		{
			if (check(l, r, zhi[len][i]))
			{
				ans = zhi[len][i];
				break;
			}
		}

		printf("%d\n", ans);
	}

	return 0;
}