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

long long totN;
set<int> hadnum[39];
long long nownum;
bool intempty[1090];
set<int> finalnums;

int main()
{
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        nownum = read();
        for (int j = 0; j <= 30; j++)
        {
            if (nownum & (1ll << j))
            {
                hadnum[j].insert(nownum);
            }
        }
    }
    int mxwei = 0;
    for (int i = 30; i >= 0; --i)
    {
        if (hadnum[i].size() >= 2)
        {
            finalnums = hadnum[i];
            mxwei = i;
            for (int j = mxwei; j >= 0; --j)
            {
                int cnt = 0;
                set<int> nowve;
                for (auto ve : finalnums)
                {
                    if (hadnum[j].find(ve) != hadnum[j].end())
                    {
                        ++cnt;
                        nowve.insert(ve);
                    }
                }
                if (cnt >= 2)
                {
                    set<int> tempset = finalnums;
                    for (auto &&vee : finalnums)
                    {
                        if (nowve.find(vee) == nowve.end())
                        {
                            tempset.erase(vee);
                        }
                    }
                    finalnums = tempset;
                }
                if (cnt == 2)
                {
                    bool temp00 = false;
                    long long fi;
                    for (auto &&d : finalnums)
                    {
                        if (!temp00)
                        {
                            temp00 = true;
                            fi = d;
                        }
                        else
                        {
                            fi &= d;
                        }
                    }
                    write(fi);
                    return 0;
                }
            }
        }
    }
    return 0;
} //LikiBlaze Code