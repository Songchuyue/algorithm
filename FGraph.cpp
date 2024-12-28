#include <bits/stdc++.h>
using namespace std;

const int INF = numeric_limits<int>::max(); // ���ڱ�ʾ�����ĳ���

// ����ߵĽṹ��
struct Edge
{
    int from, to, cost;
};

// ���ͼ��ǰ�����㷨
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

    // ����·��
    P[0] = 1; // ���
    for (int i = 1; i < k; i++)
    {
        P[i] = D[P[i - 1]];
    }
}

int main()
{
    int k, n; // k ��ʾ�������n ��ʾ�ܽڵ���
    cout << "Enter the number of stages (k): ";
    cin >> k;
    cout << "Enter the total number of nodes (n): ";
    cin >> n;

    // �ӱ�׼�����ȡ�ߵ���Ϣ
    cout << "Enter the number of edges: ";
    int m; // �ߵ�����
    cin >> m;

    vector<Edge> edges(m); // ��űߵ���Ϣ
    cout << "Enter the edges in the format 'from to cost':" << endl;
    for (int i = 0; i < m; ++i)
    {
        cin >> edges[i].from >> edges[i].to >> edges[i].cost;
    }

    // ���ö��ͼ��ǰ�����㷨��������·�� P
    vector<int> P(k);
    forwardGraph(edges, k, n, P);

    // �������·�� P
    cout << "Optimal path P: ";
    for (int i = 0; i < k; ++i)
    {
        cout << P[i] << " ";
    }
    cout << endl;

    return 0;
}