#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;
signed main() {
    string S, P; cin >> S >> P;
    S = ' ' + S; P = ' ' + P;
    
    vector<int> nex(P.size(), 0);
    for(int i = 2, j = 0; i < P.size(); i++) {
        while(j && P[j + 1] != P[i]) j = nex[j];
        if(P[j + 1] == P[i]) j++;
        nex[i] = j;
    }//每个循环计算nex[i]
    
    int ans = 0;
    bool ok = false;
    for(int i = 1, j = 0; i < S.size(); i++) {
        //直至j等于0 或 P[j+1]项与S[i]匹配
        while(j && P[j + 1] != S[i]) j = nex[j];
        //若j不为0，即存在相同前后缀，长度为j，且J+1项仍相同，令j++，得到前后缀长度
        if(P[j + 1] == S[i]) j++;
        if(j == P.size() - 1) {
            ans = i - P.size() + 1;
            ok = true;
            break;
        }
    }
    
    if (ok) cout << ans << endl;
    else cout << "-1" << endl;

    return 0;
}