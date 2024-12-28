#include <bits/stdc++.h>
using namespace std;

vector<int> C;           // ��������
vector<vector<int>> adj; // �ڽӾ���洢ͼ
int n, m;                // n�������m����ɫ

// ��������Ƿ���Ը�����k��ɫΪC[k]
bool OK(int k)
{
    for (int i = 0; i < k; i++)
    {
        if (adj[i][k] && C[i] == C[k])
        { // ���i��k֮���б�����ɫ��ͬ
            return false;
        }
    }
    return true;
}

// ͼ��ɫ����Ҫ�����㷨
bool MCOLORING()
{
    int k = 0;      // �ӵ�0�����㿪ʼ
    C.assign(n, 0); // ���ж�����ɫ��ʼ��Ϊ0

    while (k >= 0)
    {
        C[k] = C[k] + 1; // ������һ����ɫ
        while (C[k] <= m && !OK(k))
        { // �����ɫ�Ƿ�Ϸ�
            C[k] = C[k] + 1;
        }
        if (C[k] <= m)
        {
            if (k == n - 1)
            {                // ���ж�����ɫ���
                return true; // ���سɹ�
            }
            else
            {
                k++;      // �ƶ�����һ������
                C[k] = 0; // ������һ���������ɫ
            }
        }
        else
        {
            C[k] = 0; // ���õ�ǰ������ɫ������
            k--;
        }
    }
    return false; // ���k < 0�����޽�
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