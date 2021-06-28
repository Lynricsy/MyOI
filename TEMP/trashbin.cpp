#include <stdio.h>
#include <iostream>
#include <algorithm>
#define lson (x << 1)
#define rson (x << 1 | 1)
using namespace std;
const int MAXN = 1e6 + 10;
typedef long long ll;

int n, cnt = 0;
ll x1, y1, x2, y2, X[MAXN << 1];

struct ScanLine
{
	ll l, r, h;
	int mark;
	//  mark用于保存权值 (1 / -1)
	bool operator<(const ScanLine &rhs) const
	{
		return h < rhs.h;
	}
} line[MAXN << 1];

struct SegTree
{
	int l, r, sum;
	ll len;
	//  sum: 被完全覆盖的次数；
	//  len: 区间内被截的长度。
} tree[MAXN << 2];

void build_tree(int x, int l, int r)
{
	//  我觉得最不容易写错的一种建树方法
	tree[x].l = l, tree[x].r = r;
	tree[x].len = 0;
	tree[x].sum = 0;
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build_tree(lson, l, mid);
	build_tree(rson, mid + 1, r);
	return;
}

void pushup(int x)
{
	int l = tree[x].l, r = tree[x].r;
	if (tree[x].sum /* 也就是说被覆盖过 */)
		tree[x].len = X[r + 1] - X[l];
	//      更新长度
	else
		tree[x].len = tree[lson].len + tree[rson].len;
	//      合并儿子信息
}

void edit_tree(int x, ll L, ll R, int c)
{
	int l = tree[x].l, r = tree[x].r;
	//  注意，l、r和L、R的意义完全不同
	//  l、r表示这个节点管辖的下标范围
	//  而L、R则表示需要修改的真实区间
	if (X[r + 1] <= L || R <= X[l])
		return;
	//  这里加等号的原因：
	//  假设现在考虑 [2,5], [5,8] 两条线段，要修改 [1,5] 区间的sum
	//  很明显，虽然5在这个区间内，[5,8] 却并不是我们希望修改的线段
	//  所以总结一下，就加上了等号
	if (L <= X[l] && X[r + 1] <= R)
	{
		tree[x].sum += c;
		pushup(x);
		return;
	}
	edit_tree(lson, L, R, c);
	edit_tree(rson, L, R, c);
	pushup(x);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lli %lli %lli %lli", &x1, &y1, &x2, &y2);
		X[2 * i - 1] = x1, X[2 * i] = x2;
		line[2 * i - 1] = (ScanLine){x1, x2, y1, 1};
		line[2 * i] = (ScanLine){x1, x2, y2, -1};
		//      一条线段含两个端点，一个矩形的上下边都需要扫描线扫过
	}
	n <<= 1;
	//  直接把 n <<= 1 方便操作
	sort(line + 1, line + n + 1);
	sort(X + 1, X + n + 1);
	int tot = unique(X + 1, X + n + 1) - X - 1;
	//  去重最简单的方法：使用unique！（在<algorithm>库中）
	build_tree(1, 1, tot - 1);
	//  为什么是 tot - 1 ：
	//  因为右端点的对应关系已经被篡改了嘛…
	//  [1, tot - 1]描述的就是[X[1], X[tot]]
	ll ans = 0;
	for (int i = 1; i < n /* 最后一条边是不用管的 */; i++)
	{
		edit_tree(1, line[i].l, line[i].r, line[i].mark);
		//      先把扫描线信息导入线段树
		ans += tree[1].len * (line[i + 1].h - line[i].h);
		//      然后统计面积
	}
	printf("%lli", ans);
	return 0;
}