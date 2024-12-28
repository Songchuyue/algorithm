#include<bits/stdc++.h>
#define endl '\n'
using namespace std;

struct TreeNode {
    int key;
    int height;
    int level;
    TreeNode *l;
    TreeNode *r;

    TreeNode(): key(0), height(0), level(0), l(nullptr), r(nullptr) {}
    //TreeNode(int x): key(x), height(0), level(0), l(nullptr), r(nullptr) {}
    TreeNode(int x, int y): key(x), height(0), level(y), l(nullptr), r(nullptr) {}
};

inline int Height(TreeNode *root) {
    return (root == nullptr) ? -1 : root->height;
}

inline void UpdateHeight(TreeNode *root) {
    root->height = max(Height(root->l), Height(root->r)) + 1;
}

inline void UpdateLevel(TreeNode *root, int level) {
    if(root == nullptr) return;
    root->level = level;
    UpdateLevel(root->l, level + 1);
    UpdateLevel(root->r, level + 1);
}

inline void LL(TreeNode* &A) {
    TreeNode *B = A->l;
    A->l = B->r;
    B->r = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;

    A->level--;
    UpdateLevel(A, A->level);
}

inline void RR(TreeNode* &A) {
    TreeNode *B = A->r;
    A->r = B->l;
    B->l = A;
    UpdateHeight(A);
    UpdateHeight(B);
    A = B;

    A->level--;
    UpdateLevel(A, A->level);
}

inline void LR(TreeNode* &A) {
    RR(A->l);
    LL(A);
}

inline void RL(TreeNode* &A) {
    LL(A->r);
    RR(A);
}

int last_ini = INT_MAX;
bool fir = true;

inline void Balance(TreeNode* &root, int num, int flags) {
    if(Height(root->l) - Height(root->r) == 2) {
        if(num != last_ini && !fir) printf("\n");
        if(Height(root->l->l) >= Height(root->l->r)) {

            if(flags == 1 && num != last_ini) printf("Insert %d: ", num);
            else if(flags == 2 && num != last_ini) printf("Remove %d: ", num);

            printf("Reblance subtree rooted at node %d on level %d with r rotation. ", root->key, root->level);

            LL(root);
        }
        else {

            if(flags == 1 && num != last_ini) printf("Insert %d: ", num);
            else if(flags == 2 && num != last_ini) printf("Remove %d: ", num);

            printf("Reblance subtree rooted at node %d on level %d with l rotation and r rotation. ", root->key, root->level);

            LR(root);
        }
        last_ini = num;
        fir = false;
    }
    else if(Height(root->r) - Height(root->l) == 2) {
        if(num != last_ini && !fir) printf("\n");
        if(Height(root->r->r) >= Height(root->r->l)) {

            if(flags == 1 && num != last_ini) printf("Insert %d: ", num);
            else if(flags == 2 && num != last_ini) printf("Remove %d: ", num);

            printf("Reblance subtree rooted at node %d on level %d with l rotation. ", root->key, root->level);

            RR(root);
        }
        else {

            if(flags == 1 && num != last_ini) printf("Insert %d: ", num);
            else if(flags == 2 && num != last_ini) printf("Remove %d: ", num);

            printf("Reblance subtree rooted at node %d on level %d with r rotation and l rotation. ", root->key, root->level);

            RL(root);
        }
        last_ini = num;
        fir = false;
    }
    UpdateHeight(root);
    return;
}

inline void Insert(TreeNode* &root, int num, int level) {
    if(root == nullptr) root = new TreeNode(num, level);
    else if(num < root->key) Insert(root->l, num, level + 1);
    else if(num > root->key) Insert(root->r, num, level + 1);
    else return;
    Balance(root, num, 1);
    return;
}

inline void Remove(TreeNode* &root, int num, int ini) {
    if(root == nullptr) return;
    if(num < root->key) Remove(root->l, num, ini);
    else if(num > root->key) Remove(root->r, num, ini);
    else if(root->l != nullptr && root->r != nullptr) {
        TreeNode *s = root->r;
        while(s->l != nullptr) s = s->l;
        root->key = s->key;
        Remove(root->r, s->key, ini);
    } 
    else {
        TreeNode *oldroot = root;
        root = (root->l != nullptr) ? root->l : root->r;
        delete oldroot;
    }
    if(root != nullptr) Balance(root, ini, 2);
    return;
}

inline void PrintInOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root;
    while(1) {
        while(p != nullptr) {
            S.push(p);
            p = p->l;
        }
        if(S.empty()) return;
        p = S.top(); S.pop();
        printf("%d ", p->key); 
        p = p->r;
    }
}

inline void PrintPreOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root;
    while(1) {
        while(p != nullptr) {
            printf("%d ", p->key);
            S.push(p);
            p = p->l;
        }
        if(S.empty()) return;
        p = S.top(); S.pop();
        p = p->r;
    }
}

int main() {
    int T; scanf("%d", &T);
    TreeNode *root = new TreeNode;
    char tem[10]; int num;
    for(int i = 0; i < T; i++) {
        if(root == nullptr) root = new TreeNode;
        scanf("%s %d", tem, &num);
        if(root->key == 0) root->key = num;
        else if(tem[0] == 'I') Insert(root, num, 0);
        else Remove(root, num, num);
    }
    if(!fir) printf("\n\n");
    PrintInOrder(root);
    printf("\n\n");
    PrintPreOrder(root);

    return 0;
}