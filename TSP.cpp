#include "bits/stdc++.h"
using namespace std;

const int INF = numeric_limits<int>::max();

// 使用DP求解TSP
int solveTSP(const vector<vector<int>> &dist, int n)
{
    int V = 1 << (n - 1); // 除了起点1之外的结点数量，对应的状态数
    vector<vector<int>> dp(n, vector<int>(V, INF));
    // 初始化从所有点到起点1的直接连接
    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = dist[i][0];
    }

    // 填充dp表
    for (int s = 1; s < V; ++s)
    {
        for (int i = 1; i < n; ++i)
        {
            if (!(s & (1 << (i - 1))))
            { // 确保i在集合s中
                continue;
            }
            for (int j = 1; j < n; ++j)
            {
                if (i == j)
                    continue;
                if (s & (1 << (j - 1)))
                { // j也必须在集合s中
                    int s_without_i = s & ~(1 << (i - 1));
                    dp[i][s] = min(dp[i][s], dp[j][s_without_i] + dist[j][i]);
                }
            }
        }
    }

    // 计算最小环路
    int min_cost = INF;
    int final_state = V - 1;
    for (int i = 1; i < n; ++i)
    {
        min_cost = min(min_cost, dp[i][final_state] + dist[i][0]);
    }

    return min_cost;
}

int main()
{
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    cout << "Enter the distance matrix:" << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> dist[i][j];
        }
    }

    int result = solveTSP(dist, n);
    cout << "The minimum cost of the travelling salesman tour is: " << result << endl;

    return 0;
}