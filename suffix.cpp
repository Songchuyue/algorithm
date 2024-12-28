#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

char* _Creat_Suffix(char *infix) {
    static char suffix[100];  int suffix_pointer = 0;

    stack<char> op;

    int priority[200]; //运算符优先级
    priority[')'] = 0, priority['('] = 3;
    priority['+'] = priority['-'] = 1;
    priority['*'] = priority['/'] = 2;

    int len = strlen(infix);
    for(int i = 0; i <len; i++) {

        if(infix[i] >= '0' && infix[i] <= '9') {
            //若为数字，直接放入后缀表达式
            suffix[suffix_pointer++] = infix[i];
        } else {
            if(op.empty() || op.top() == '(' || priority[infix[i]] > priority[op.top()]) {
                op.push(infix[i]);
            } else {
                while(priority[infix[i]] <= priority[op.top()] && op.top() != '(') {
                    suffix[suffix_pointer++] = op.top();
                    op.pop();
                }
                if(infix[i] == ')') {
                    op.pop();
                } else {
                    op.push(infix[i]);
                }
            }
        }
    }
    while(!op.empty()) {
        suffix[suffix_pointer++] = op.top();
        op.pop();
    }
    return suffix;
}

signed main() {
    char infix[100];
    cin >> infix;

    char *suffix = _Creat_Suffix(infix);

    cout << suffix;

    return 0;
}