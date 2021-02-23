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

const int Ns = 205;
const int Ms = 25;
int n, num[Ns];
char tmp[Ns];
struct bign
{
    int s[Ns], len;
    bign()
    {
        memset(s, 0, sizeof(s));
        len = 0;
    }
} f[Ns][Ms];

bign add(bign a, int st, int ed)
{
    int i, jw = 0;
    for (i = 1; st <= ed; ++i)
    {
        a.s[i] = a.s[i] + num[ed] + jw;
        jw = a.s[i] / 10;
        a.s[i] %= 10;
        --ed;
    }
    --i;
    while (jw != 0)
    {
        a.s[++i] += jw;
        jw = a.s[i] / 10;
        a.s[i] %= 10;
    }
    a.len = max(a.len, i);
    return a;
}

bool cmp(bign a, bign b)
{
    if (a.len < b.len)
        return true;
    else if (a.len > b.len)
        return false;
    for (int i = a.len; i > 0; --i)
    {
        if (a.s[i] < b.s[i])
            return true;
        else if (a.s[i] > b.s[i])
            return false;
        else
            continue;
    }
}

int main()
{
    scanf("%s", &tmp);
    scanf("%d", &n);
    int i, j, k, len = strlen(tmp);
    for (i = 0; i < len; ++i)
        num[i + 1] = int(tmp[i] - 48);
    for (i = 1; i <= len; ++i)
        f[i][0] = add(f[i][0], 1, i);
    for (i = 1; i <= n; ++i)
        for (j = i + 1; j <= len; ++j)
        {
            f[j][i].len = Ns;
            for (k = i + 1; k <= j; ++k)
            {
                bign c = add(f[k - 1][i - 1], k, j);
                if (!cmp(f[j][i], c))
                    f[j][i] = c;
            }
        }
    for (i = f[len][n].len; i > 0; --i)
        printf("%d", f[len][n].s[i]);
    printf("\n");
    return 0;
}