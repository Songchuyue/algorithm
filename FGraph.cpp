#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max(); // 用于表示无穷大的常量

// 定义边的结构体
struct Edge
{
    int from, to, cost;
};

// 多段图向前处理算法
void forwardGraph(const vector<Edge> &edges, int k, int n, vector<int> &P)
{
    vector<int> COST(n + 1, INF);
    COST[n] = 0;
    vector<int> D(n + 1, -1);

    for (int i = n - 1; i >= 1; i--)
    {
        for (const Edge &edge : edges)
        {
            if (edge.from == i && COST[i] > edge.cost + COST[edge.to])
            {
                COST[i] = edge.cost + COST[edge.to];
                D[i] = edge.to;
            }
        }
    }

    // 最优路径
    P[0] = 1; // 起点
    for (int i = 1; i < k; i++)
    {
        P[i] = D[P[i - 1]];
    }
}

int main()
{
    int k, n; // k 表示多段数，n 表示总节点数
    cout << "Enter the number of stages (k): ";
    cin >> k;
    cout << "Enter the total number of nodes (n): ";
    cin >> n;

    // 从标准输入读取边的信息
    cout << "Enter the number of edges: ";
    int m; // 边的数量
    cin >> m;

    vector<Edge> edges(m); // 存放边的信息
    cout << "Enter the edges in the format 'from to cost':" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    // 调用多段图向前处理算法计算最优路径 P
    vector<int> P(k);
    forwardGraph(edges, k, n, P);

    // 输出最优路径 P
    cout << "Optimal path P: ";
    for (int i = 0; i < k; ++i)
    {
        cout << P[i] << " ";
    }
    cout << endl;

    return 0;
}