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
    }//ÿ��ѭ������nex[i]
    
    int ans = 0;
    bool ok = false;
    for(int i = 1, j = 0; i < S.size(); i++) {
        //ֱ��j����0 �� P[j+1]����S[i]ƥ��
        while(j && P[j + 1] != S[i]) j = nex[j];
        //��j��Ϊ0����������ͬǰ��׺������Ϊj����J+1������ͬ����j++���õ�ǰ��׺����
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