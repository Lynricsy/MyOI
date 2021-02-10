#include <iostream>
#include <cmath>
using namespace std;
int num[1010];
int totANS = 1;
int sum1[1010], sum2[1010];
int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> num[i];
        sum1[i] = 1;
        sum2[i] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < i; j++)
        {
            if(num[i]>num[j] )
            {
                sum1[i]=max(sum1[i],sum1[j]+1);
            }
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int j=n;j>i;j--)
        {
            if(num[i]>num[j])
            {
                sum2[i]=max(sum2[i],sum2[j]+1);
            }
        }
    }
    for(int i=1;i<=n;i++)
    {
        totANS=max(totANS,(sum2[i]+sum1[i]-1));
    }
    cout<<n-totANS<<endl;
    return 0;
}