#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

struct TreeNode {
    int key;
    TreeNode *left;
    TreeNode *right;

    TreeNode(): key(-1), left(nullptr), right(nullptr) {};
    TreeNode(int x): key(x), left(nullptr), right(nullptr) {}
};

TreeNode* Find(TreeNode *root, int num) {
    if(root == nullptr || num == root->key) return root;
    else if(num > root->key) return Find(root->right, num);
    else if(num < root->key) return Find(root->left, num);
    return nullptr;
}

void Insert(TreeNode* &root, int num) {
    if(root == nullptr) root = new TreeNode(num);
    else if(num > root->key) Insert(root->right, num);
    else if(num < root->key) Insert(root->left, num);
    return;
}

void Remove(TreeNode* &root, int num) {
    if(root == nullptr) return;
    if(num < root->key) Remove(root->left, num);
    else if(num > root->key) Remove(root->right, num);
    //如果既有左子树又有右子树
    else if(root->left != nullptr && root->right != nullptr){
        TreeNode *s = root->right;
        while(s->left != nullptr) s = s->left;
        root->key = s->key; //s为t右子树中根序列第一个结点
        Remove(root->right, s->key);
    }
    else{ 
        TreeNode* oldroot = root;
        root = (root->left != nullptr) ? root->left : root->right;
        delete oldroot;
    }
}

void BuildTree(TreeNode *root, int arr[]) {
    for(int i = 0; arr[i] != 0; i++) {
        Insert(root, arr[i]);
    }
    return;
}

unsigned main() {
    int n, m; cin >> n >> m;
    int arr[10010] = {0};
    TreeNode *root = new TreeNode;

    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    BuildTree(root, arr);

    return 0;
}