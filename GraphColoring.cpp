#include <bits/stdc++.h>
using namespace std;

vector<int> C;           // 决策序列
vector<vector<int>> adj; // 邻接矩阵存储图
int n, m;                // n个顶点和m种颜色

// 函数检查是否可以给顶点k着色为C[k]
bool OK(int k)
{
    for (int i = 0; i < k; i++)
    {
        if (adj[i][k] && C[i] == C[k])
        { // 如果i和k之间有边且颜色相同
            return false;
        }
    }
    return true;
}

// 图着色的主要回溯算法
bool MCOLORING()
{
    int k = 0;      // 从第0个顶点开始
    C.assign(n, 0); // 所有顶点颜色初始化为0

    while (k >= 0)
    {
        C[k] = C[k] + 1; // 尝试下一个颜色
        while (C[k] <= m && !OK(k))
        { // 检查着色是否合法
            C[k] = C[k] + 1;
        }
        if (C[k] <= m)
        {
            if (k == n - 1)
            {                // 所有顶点着色完成
                return true; // 返回成功
            }
            else
            {
                k++;      // 移动到下一个顶点
                C[k] = 0; // 重置下一个顶点的颜色
            }
        }
        else
        {
            C[k] = 0; // 重置当前顶点颜色并回溯
            k--;
        }
    }
    return false; // 如果k < 0，则无解
}

int main()
{
    cout << "Enter the number of vertices: ";
    cin >> n;
    cout << "Enter the number of colors: ";
    cin >> m;
    adj.assign(n, vector<int>(n, 0));

    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> adj[i][j];
        }
    }

    if (MCOLORING())
    {
        cout << "Solution exists: ";
        for (int i = 0; i < n; i++)
        {
            cout << C[i] << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No solution exists." << endl;
    }

    return 0;
}