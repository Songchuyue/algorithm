#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

struct TreeNode{
    char data;
    TreeNode *left;
    TreeNode *right;
    TreeNode(){}
    TreeNode(char x): data(x){}
};

TreeNode* Father(TreeNode *root, TreeNode *p) {
    if(root == nullptr || p == root) return nullptr;
    if(root->left == p || root->right == p) return root;
    TreeNode *tem = Father(root->left, p);
    if(tem != nullptr) return tem;
    else return Father(root->right, p);
}

TreeNode* Find(TreeNode *root, char item) {
    if(root == nullptr) return nullptr;
    if(root->data == item) return root;
    TreeNode *tem = Find(root->left, item);
    if(tem != nullptr) return tem;
    else return Find(root->right, item);
}

void Del(TreeNode *root) {
    if(root == nullptr) return;
    Del(root->left);
    Del(root->right);
    delete root;
    root = nullptr;
}


void DeleteSubTree(TreeNode *root, TreeNode *p) {
    if(root == nullptr) return;
    if(root == p) {
        Del(p);
        p = nullptr;
        return;
    }
    TreeNode *fa = Father(root, p);
    if(fa == nullptr) return;
    else if(fa->left == p) fa->left = nullptr;
    else fa->right = nullptr;
    Del(p);
}

TreeNode *CreateBinTree(string &tree, int &index) {
    if(tree[index] == '#') {
        index++;
        return nullptr;
    }
    TreeNode *tem = new TreeNode;
    tem->data = tree[index++];
    tem->left = CreateBinTree(tree, index);
    tem->right = CreateBinTree(tree, index);
    return tem;
}

TreeNode* CopyTree(TreeNode *root) {
    if(root == nullptr) return nullptr;
    
    TreeNode *tem = new TreeNode;
    tem->data = root->data;

    tem->left = CopyTree(root->left);
    tem->right = CopyTree(root->right);

    return tem; 
}

TreeNode* CopyTree_(TreeNode *root) {
    if(root == nullptr) return nullptr;

    TreeNode *newlptr = CopyTree_(root->left);
    TreeNode *newrptr = CopyTree_(root->right);
    TreeNode *p = new TreeNode;

    p->data = root->data;
    p->left = newlptr;
    p->right = newrptr;
    return p;
}

int Count(TreeNode *root) {
    if(root == nullptr) return 0;
    return Count(root->left) + Count(root->right) + 1;
}

int depth(TreeNode *root) {
    if(root == nullptr) return -1;
    int dl = depth(root->left);
    int dr = depth(root->right);
    return max(dl + 1, dr + 1);
}

TreeNode* FindFirstNode_InOrder(TreeNode *root) {
    if(root == nullptr) return nullptr;
    TreeNode *p = root;
    while(p->left != nullptr) p = p->left;
    return p;
}

TreeNode* FindLastNode_InOrder(TreeNode *root) {
    if(root == nullptr) return nullptr;
    TreeNode *p = root;
    while(p->right != nullptr) p = p->right;
    return p;
}

TreeNode* FindFirstNode_PreOrder(TreeNode *root) {
    return root;
}

TreeNode* FindLastNode_PreOrder(TreeNode *root) {
    if(root == nullptr) return nullptr;
    TreeNode *p = root;
    while(1) {
        if(p->right != nullptr) p = p->right;
        else if(p->left != nullptr) p = p->left;
        else return p;
    }
}

TreeNode* FindFirstNode_PostOrder(TreeNode *root) {
    if(root == nullptr) return nullptr;
    TreeNode *p = root;
    while(1) {
        if(p->left != nullptr) p = p->left;
        else if(p->right != nullptr) p = p->right;
        else return p;
    }
}

TreeNode* FindLastNode_PostOrder(TreeNode *root) {
    return root;
}

void findPath(TreeNode *root, int path[], int k) {
    if(root == nullptr) return;

    path[k] = root->data;
    if(root->left == nullptr && root->right == nullptr) {
        for(int i = 0; i <= k; i++) cout << path[i] << ' ';
        cout << endl;
        return;
    }
    findPath(root->left, path, k + 1);
    findPath(root->right, path, k + 1);
}

TreeNode* buildTree(char *preorder, char *inorder, int n) {
    if(n <= 0) return nullptr;
    char rootval = preorder[0];
    TreeNode *root = new TreeNode(rootval);

    int i = 0;
    for(; i < n; i++) {
        if(rootval == inorder[i]) break;
    }

    root->left = buildTree(&preorder[1], &inorder[0], i);
    root->right = buildTree(&preorder[1], &inorder[i + 1], n - i - 1);

    return root;
}

TreeNode* Pre_In_buildTree(vector<char> preorder, vector<char> inorder) {
    char rootval = preorder[0];
    TreeNode *root = new TreeNode(rootval);

    int i = 0;
    for(; i < inorder.size(); i++) {
        if(inorder[i] == rootval) break;
    }

    root->left = Pre_In_buildTree(vector<char>(preorder.begin() + 1, preorder.begin() + i + 1), 
                                  vector<char>(inorder.begin(), inorder.begin() + i));
    root->right = Pre_In_buildTree(vector<char>(preorder.begin() + i + 1, preorder.end()), 
                                   vector<char>(inorder.begin() + i + 1, inorder.end()));

    return root;
}

TreeNode* In_Post_buildTree(vector<char> inorder, vector<char> postorder) {
    char rootval  =postorder[postorder.size() - 1];
    TreeNode *root = new TreeNode(rootval);

    int i = 0;
    for(; i < inorder.size(); i++) {
        if(inorder[i] == rootval) break;
    }

    root->left = In_Post_buildTree(vector<char>(inorder.begin(), inorder.begin() + i), 
                                   vector<char>(postorder.begin(), postorder.begin() + i));
    root->right = In_Post_buildTree(vector<char>(inorder.begin() + i + 1, inorder.end()),
                                    vector<char>(postorder.begin() + i, postorder.end() - 1));

    return root;
}

TreeNode *buildExpTree(char *s, int n) {
    stack<TreeNode*> stk;
    for(int i = 0; i < n; i++) {
        TreeNode *p = new TreeNode;
        p->data = s[i];
        if(s[i] >= 'a' && s[i] <= 'z') {
            p->left = p->right = nullptr;
        } else {
            p->right = stk.top(); stk.pop();
            p->left = stk.top(); stk.pop();
        }
        stk.push(p);
    }
    return stk.top();
}

TreeNode* buildExpTree_InOrder(char *s, int n) {
    char Priority[200]; 
    Priority['+'] = Priority['-'] = 1; 
    Priority['*'] = Priority['/'] = 2;

    stack<TreeNode*> EXP;
    stack<char> OP;

    for(int i = 0; i < n; i++) {
        if(s[i] >= 'a' && s[i] <= 'z') {
            TreeNode *p = new TreeNode;
            p->data = s[i]; p->left = p->right = nullptr;
            EXP.push(p);
        } else if(s[i] == '(') {
            OP.push(s[i]);
        } else if(s[i] == ')') {
            while(OP.top() != '(') {
                TreeNode *p = new TreeNode;
                p->data = OP.top(); OP.pop();
                p->left = EXP.top(); EXP.pop();
                p->right = EXP.top(); EXP.pop();
                EXP.push(p);
            }
            OP.pop();
        } else {
            while(!OP.empty() && OP.top() != '(' && Priority[s[i]] <= Priority[OP.top()]) {
                TreeNode *p = new TreeNode;
                p->data = OP.top(); OP.pop();
                p->left = EXP.top(); EXP.pop();
                p->right = EXP.top(); EXP.pop();
                EXP.push(p);
            }
            OP.push(s[i]);
        }
    }

    while(!OP.empty()) {
        TreeNode *p = new TreeNode;
        p->data = OP.top(); OP.pop();
        p->left = EXP.top(); EXP.pop();
        p->right = EXP.top(); EXP.pop();
        EXP.push(p);
    }

    return EXP.top();
}

int Calc(TreeNode *t){ 
    if(t->left == nullptr && t->right == nullptr) 
        return t->data - '0'; 

    int ans1 = Calc(t->left);
    int ans2 = Calc(t->right);

    if (t->data == '+') return ans1 + ans2;
        else if (t->data == '-') return ans1 - ans2;
        else if (t->data == '*') return ans1 * ans2;
    return ans1 / ans2;
}

void visit(TreeNode* root) {
    cout << root->data << endl;
}

void NonRecPreOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root;
    while(1) {
        while(p != nullptr) {
            visit(p);
            S.push(p);
            p = p->left;
        }
        if(S.empty()) return;
        p = S.top(); S.pop();
        p = p->right;
    }
}

void NonRecInOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root;
    while(1) {
        while(p != nullptr) {
            S.push(p);
            p = p->left;
        } 
        if(S.empty()) return;
        p = S.top(); S.pop();
        visit(p); 
        p = p->right;
    }
}

void NonRecPostOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root, *pre = nullptr;
    while(1) {
        while(p != nullptr) {
            S.push(p);
            p = p->left;
        }
        if(S.empty()) return;
        p = S.top();

        if(p->right == nullptr || p->right == pre) {
            S.pop();
            visit(p->right);
            pre = p;
            p = nullptr;
        } else {
            p = p ->right;
        }
    }
}

void NonRecPostOrder2(TreeNode *root) {
    stack<pair<TreeNode*, int>> S;
    if(root != nullptr) S.push({root, 1});
    pair<TreeNode*, int> p;
    while(!S.empty()) {
        p = S.top(); S.pop();
        if(p.second == 1) {
            S.push({p.first, 2});
            if(p.first->left != nullptr) S.push({p.first->left, 1});
        }
        if(p.second == 2) {
            S.push({p.first, 3});
            if(p.first->right != nullptr) S.push({p.first->right, 1});
        }
        if(p.second == 3) {
            visit(p.first);
        }
    }
}

int NumofEachLevel(TreeNode *root) {
    queue<TreeNode*> q;
    TreeNode *tem = nullptr;

    int level = 0;
    q.push(root); q.push(nullptr);
    
    while(!q.empty()) {
        tem = q.front();
        q.pop();

        if(tem == nullptr) {
            if(q.empty()) break;        
            q.push(nullptr);
            level++;
        } else {
            if(tem->left != nullptr) q.push(tem->left);
            if(tem->right != nullptr) q.push(tem->right);
        }
    }

    return level - 1;
}

int NumofEachLevel_(TreeNode *root) {
    queue<TreeNode*> q;
    TreeNode *p = nullptr;
    int cnt = 0, level = 0;
    q.push(root);
    while(!q.empty()) {
        int size = q.size();
        while(size--) {
            p = q.front();
            q.pop();
            cnt++;
            level++;

            if(p->left != nullptr) q.push(p->left);
            if(p->right != nullptr) q.push(p->right);
        }
    }

    return level - 1;
}

