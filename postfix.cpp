#include<bits/stdc++.h>
#define endl '\n'
#define int long long
#define FUP(i, begin, end) for(int i = begin; i <= end; i++)
#define FDN(i, end, begin) for(int i = end; i >= begin; i--)
using namespace std;

int priority(char ch) {
  if(ch == '^') return 3;
  if(ch == '*' || ch == '/') return 2;
  if(ch == '+' || ch == '-') return 1;
  return 0;// '('优先级最低，为0
}

//转后缀
void ToPostfix(string& S, vector<string>& postfix) {
  string num;//存放数字
  stack<char> op;//存放运算符，后进先出
  /*
    op优先级递减即可，否则弹出top，压入postfix
    (、)，以(作为分隔符，类似递归，碰到)时，全部弹出即可
  */
  for(auto ch : S) {
    if(isdigit(ch)) num += ch;//读到运算符再一并压入postfix
    else {
      if (!num.empty()) postfix.push_back(num), num.clear();
      if (ch == '(') op.push(ch);
      else if (ch == ')') {
        while (op.top() != '(') postfix.push_back(string(1,op.top())),op.pop();
        op.pop();
      }
      else {// + - * / ^
        while (!op.empty() && priority(op.top()) >= priority(ch)) //判断优先级
          postfix.push_back(string(1,op.top())),op.pop();
        op.push(ch);
      }
    }
  }
  if (!num.empty()) postfix.push_back(num), num.clear();
  while (!op.empty()) postfix.push_back(string(1, op.top())), op.pop();
}

int calculate(int x, int y, char op) {
  if(op == '+') return x + y;
  if(op == '-') return x - y;
  if(op == '*') return x * y;
  if(op == '/') return (y == 0) ? LLONG_MAX : x / y;
  if(op == '^') {//快速幂
    int res = 1;
    while(y){
      if(y & 1) res *= x;
      x *= x; y >>= 1;
    }
    return res;
  }
  return 0;
}

int CalPostifix(vector<string>& postfix) {
  stack<int> num;
  for(auto str : postfix) {
    if(isdigit(str[0])) num.push(stoll(str));
    else {
      int y = num.top(); num.pop();
      int x = num.top(); num.pop();
      int res = calculate(x, y, str[0]);
      if(res == LLONG_MAX) return LLONG_MAX;
      num.push(res);
    }
  }
  int ans = num.top(); num.pop();
  return ans;
}

signed main() {
  string S;
  while (cin >> S) {
    vector<string> postfix;
    ToPostfix(S, postfix);
    int ans = CalPostifix(postfix);
    if(ans == LLONG_MAX) cout << "INVALID" << endl;
    else cout << ans << endl;
  }
  return 0;
}