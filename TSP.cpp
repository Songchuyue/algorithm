#include "bits/stdc++.h"
using namespace std;

const int INF = numeric_limits<int>::max();

// ʹ��DP���TSP
int solveTSP(const vector<vector<int>> &dist, int n)
{
    int V = 1 << (n - 1); // �������1֮��Ľ����������Ӧ��״̬��
    vector<vector<int>> dp(n, vector<int>(V, INF));
    // ��ʼ�������е㵽���1��ֱ������
    for (int i = 1; i < n; ++i)
    {
        dp[i][0] = dist[i][0];
    }

    // ���dp��
    for (int s = 1; s < V; ++s)
    {
        for (int i = 1; i < n; ++i)
        {
            if (!(s & (1 << (i - 1))))
            { // ȷ��i�ڼ���s��
                continue;
            }
            for (int j = 1; j < n; ++j)
            {
                if (i == j)
                    continue;
                if (s & (1 << (j - 1)))
                { // jҲ�����ڼ���s��
                    int s_without_i = s & ~(1 << (i - 1));
                    dp[i][s] = min(dp[i][s], dp[j][s_without_i] + dist[j][i]);
                }
            }
        }
    }

    // ������С��·
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