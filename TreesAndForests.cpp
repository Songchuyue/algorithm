#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

struct TreeNode {
    int data;
    TreeNode *FirstChild;
    TreeNode *NextBrother;
};

void visit(TreeNode *root) {
    cout << root->data << endl;
}

void PreOrder(TreeNode *root) {
    if(root == nullptr) return;

    visit(root);
    
    for(TreeNode *p = root->FirstChild; p != nullptr; p = p->NextBrother) {
        PreOrder(p);
    }
}
 
 TreeNode* FindTarget(TreeNode *root, int target) {
    if(root == nullptr) return nullptr;

    if(root->data == target) return root;

    for(TreeNode *p = root->FirstChild; p != nullptr; p = p->NextBrother) {
        TreeNode *ans = FindTarget(p, target);
        if(ans != nullptr) return ans;
    }

    return nullptr;
 }

TreeNode* FindFather(TreeNode *root, TreeNode *p) {
    if(root == nullptr || p == nullptr || root == p) return nullptr;

    for(TreeNode *ptr = root->FirstChild; p != nullptr; p = p->NextBrother) {
        if(p = ptr) return root;
        TreeNode *ans = FindFather(ptr, p);
        if(ans != nullptr) return ans;
    }

    return nullptr;
}

void Del(TreeNode *p) {
    if(p == nullptr) return;

    for(TreeNode *ptr = p->FirstChild; p != nullptr; p = p->NextBrother) {
        Del(ptr);
    }

    delete p;
    p = nullptr;
}

void DelSubTree(TreeNode *t, TreeNode *p) {
    if(t == nullptr || p == nullptr) return;

    if(t == p) {
        Del(p);
        t = p = nullptr;
        return;
    } else {
        TreeNode *fa = FindFather(t, p);
        if(fa == nullptr) {
            return;
        } else if(fa->FirstChild == p) {
            fa->FirstChild = p->NextBrother;
            Del(p);
        } else {
            TreeNode *pre = fa->FirstChild;
            while(pre->NextBrother != p) pre = pre->NextBrother;
            pre->NextBrother = p->NextBrother;
            Del(p);
        }
    }
}

void LevelOrder(TreeNode *t) {
    queue<TreeNode*> q; 
    for(TreeNode *p = t; p != nullptr; p = p->NextBrother) {
        q.push(p);
    }

    while(!q.empty()) {
        TreeNode *p = q.front(); q.pop();
        visit(p);
        for(TreeNode *child = p; child != nullptr; child = child->NextBrother) {
            q.push(child);
        }
    }
}