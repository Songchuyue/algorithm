#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

signed main() {
    int n, m, L, R; cin >> n;
    vector<int> array(n);
    for(int i = 0; i < n; i++) {
        cin >> array[i];
    }

    int logn = log2(n);

    vector<vector<int>> STorder(n, vector<int>(logn));

    for(int i = 0; i < n; i++) {
        STorder[i][0] = array[i];
    }

    for(int j = 1; j <= logn; j++) {
        for(int i = 1; i <= n - (1 << j); i++) {
            STorder[i][j] = max(STorder[i][j - 1], STorder[i + (1 << (j - 1))][j - 1]);
        }
    }

    cin >> L >> R;
    int k = log2(R - L + 1);
    int ans = max(STorder[L][k], STorder[R - (1 << k) + 1][k]);
    cout << ans;
    return 0;
}