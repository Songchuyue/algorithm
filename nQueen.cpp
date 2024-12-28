#include <bits/stdc++.h>
using namespace std;

// bool PLACE(vector<int> &X, int k) // 判断X[k]是否可以放置，即不在同一列同一行同一斜角线
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

// // 非递归回溯法
// void nQueen(int n)
// {
//     int k = 1;
//     vector<int> X(n + 1, 0);

//     while (k > 0)
//     {
//         do {
//             X[k]++;
//         }
//         while (X[k] <= n && !PLACE(X, k)); // 尝试找到一个可以放置皇后的位置,坐标(k, X[k])

//         if (X[k] <= n)
//         {
//             if (k == n) // 找到了一个解
//             {
//                 for (int i = 1; i < X.size(); i++)
//                 {
//                     cout << X[i] << ' ';
//                 }
//                 cout << endl;
//             }
//             else // 继续处理下一个位置
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
    // 判断(k, X[k])是否可以放置皇后
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
        // 找到放置第k个皇后的位置
        do X[k]++;
        while(X[k] <= n && !Place(X, k));

        if(X[k] > n) { // 未能找到位置放置第k个皇后，回溯
            X[k--] = 0;
        }
        else if(X[k] <= n) { // 找到位置
            // 如果k == n， 输出结果
            if(k == n) {
                // for(int i = 1; i < k; i++) cout << X[i] << ' ';
                // cout << endl;
                cnt++;
            }
            // 如果k < n，k++
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