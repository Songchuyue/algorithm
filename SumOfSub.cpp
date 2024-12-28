#include <bits/stdc++.h>
using namespace std;

void SumOfSub(vector<int> &W, vector<int> &X, int n, int M, int k, int s, int r)
{
    X[k] = 1;          // 选择该项
    if (s + W[k] == M) // 满足题意，输出结果
    {
        for (int i = 1; i <= n; i++)
            if (X[i] == 1)
                cout << W[i] << ' ';
        cout << endl;
    }
    else // 不够
    {
        if (k + 1 <= n && s + W[k] + W[k + 1] <= M)
        {
            SumOfSub(W, X, n, M, k + 1, s + W[k], r - W[k]);
        }
    }

    X[k] = 0; // 不选择该项
    if (k + 1 <= n && s + r - W[k] >= M && s + W[k + 1] <= M)
    {
        SumOfSub(W, X, n, M, k + 1, s, r - W[k]);
    }
}

int main()
{
    int n;
    cin >> n; // num
    int M;
    cin >> M;                // target
    vector<int> W(n + 1, 0); // weight
    vector<int> X(n + 1, 0); // choose

    int r = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> W[i];
        r += W[i];
    }
    sort(W.begin() + 1, W.end());

    SumOfSub(W, X, n, M, 1, 0, r);

    return 0;
}