#include <bits/stdc++.h>
using namespace std;

// bool PLACE(vector<int> &X, int k) // �ж�X[k]�Ƿ���Է��ã�������ͬһ��ͬһ��ͬһб����
// {
//     for (int i = 1; i < k; i++)
//     {
//         if (X[i] == X[k] || abs(X[i] - X[k]) == abs(i - k))
//         {
//             return false;
//         }
//     }
//     return true;
// }

// // �ǵݹ���ݷ�
// void nQueen(int n)
// {
//     int k = 1;
//     vector<int> X(n + 1, 0);

//     while (k > 0)
//     {
//         do {
//             X[k]++;
//         }
//         while (X[k] <= n && !PLACE(X, k)); // �����ҵ�һ�����Է��ûʺ��λ��,����(k, X[k])

//         if (X[k] <= n)
//         {
//             if (k == n) // �ҵ���һ����
//             {
//                 for (int i = 1; i < X.size(); i++)
//                 {
//                     cout << X[i] << ' ';
//                 }
//                 cout << endl;
//             }
//             else // ����������һ��λ��
//             {
//                 X[++k] = 0;
//             }
//         }
//         else // k > n
//         {
//             k--;
//         }
//     }
// }

// int main()
// {
//     int n;
//     cin >> n;

//     nQueen(n);

//     return 0;
// }

int cnt = 0;


bool Place(vector<int>& X, int k)
{
    // �ж�(k, X[k])�Ƿ���Է��ûʺ�
    for(int i = 1; i < k; i++) {
        if(X[i] == X[k] || abs(X[i] - X[k]) == abs(i - k)) {
            return false;
        }
    }
    return true;
}

void nQueen(int n)
{
    vector<int> X(n + 1, 0);
    int k = 1;
    while (k)
    {
        // �ҵ����õ�k���ʺ��λ��
        do X[k]++;
        while(X[k] <= n && !Place(X, k));

        if(X[k] > n) { // δ���ҵ�λ�÷��õ�k���ʺ󣬻���
            X[k--] = 0;
        }
        else if(X[k] <= n) { // �ҵ�λ��
            // ���k == n�� ������
            if(k == n) {
                // for(int i = 1; i < k; i++) cout << X[i] << ' ';
                // cout << endl;
                cnt++;
            }
            // ���k < n��k++
            else if(k < n) {
                k++;
            }
        }
    }
}

int main()
{
    int n;
    cin >> n;
    nQueen(n);
    cout << cnt << endl;
    return 0;
}