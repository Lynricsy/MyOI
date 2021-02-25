#pragma GCC optimize(2)
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
int totN;
int A[100090];
int B[100090];
long long PB[100090];
long long totCOS;
long long DP[100090];
long long ANS;
long long l = 1, r;
long long q[100090];

void pre_SUM_B()
{
    for (int i = 1; i <= totN; ++i)
    {
        PB[i] = PB[i - 1] + B[i];
    }
}
double cal(int j, int k)
{
    return (double)(DP[k] - DP[j]) / (double)(j - k);
}

int main()
{
    freopen("pasture.in", "r", stdin);
    freopen("pasture.out", "w", stdout);
    totN = read();
    for (int i = 1; i <= totN; ++i)
    {
        A[i] = read();
    }
    for (int i = 1; i <= totN; ++i)
    {
        B[i] = read();
    }
    pre_SUM_B();
    for (int i = 1; i < totN; ++i)
    {
        totCOS += B[i] * (totN - i);
    }
    totCOS += A[totN];
    /*
    for (register int i = totN; i; --i)
    {
        for (register int j = i; j <= totN; ++j)
        {
            DP[i] = max(DP[i], DP[j] + PB[i] * (j - i) - A[i]);
        }
    }
    */
    q[++r] = totN;
    for (int i = totN - 1; i; i--)
    {
        while (l < r && cal(q[l], q[l + 1]) > PB[i])
            l++;
        int j = q[l];
        DP[i] = DP[j] + PB[i] * (j - i) - A[i];
        ANS = max(ANS, DP[i]);
        while (l < r && cal(q[r], i) > cal(q[r - 1], q[r]))
            r--;
        q[++r] = i;
    }
    write(totCOS - ANS);
    return 0;
} //LikiBlaze Code