#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
    int key, c;//0黑，1红
    TreeNode *l, *r;
    TreeNode(int x, int y): key(x), c(y), l(nullptr), r(nullptr) {}
};

inline void LL(TreeNode* &A, TreeNode *B) {
    A->l = B->r;
    B->r = A;
    A = B;
}

inline void RR(TreeNode* &A, TreeNode *B) {
    A->r = B->l;
    B->l = A;
    A = B;
}

inline TreeNode *RBson(TreeNode *root) {
    if((root->l && root->l->c == 1 && (root->r == nullptr || (root->r && root->r->c == 0))) || ((root->l == nullptr || (root->l && root->l->c == 0)) && root->r && root->r->c == 1))
        if(root->l && root->l->c == 1) return root->l;
        else if(root->r && root->r->c == 1) return root->r;
    return nullptr;
}

void Insert(TreeNode* &root, int num) {
    if(root == nullptr) root = new TreeNode(num, 1);
    else if(num > root->key) Insert(root->r, num);
    else if(num < root->key) Insert(root->l, num);
    else if(num == root->key) return;  
    if(root->c == 0) {//root为黑
        TreeNode *Rson = nullptr, *Rgson = nullptr;
        if(root->l && root->l->c == 1 && root->r && root->r->c == 1) {//root孩子为红红
            if((root->l->l && root->l->l->c == 1) || (root->l->r && root->l->r->c == 1) || (root->r->l && root->r->l->c == 1) || (root->r->r && root->r->r->c == 1))
                root->c = 1, root->l->c = 0, root->r->c = 0;
        }
        else if((Rson = RBson(root)) != nullptr) {//root孩子为红黑
            if((Rgson = RBson(Rson)) != nullptr) {//root的红孩子的孩子为红黑
                if((root->l == Rson && Rson->l == Rgson) || (root->r == Rson && Rson->r == Rgson))
                    if(root->l == Rson) {//左左
                        LL(root, Rson);
                        root->c = 0, root->r->c = 1;
                    }
                    else {//右右
                        RR(root, Rson);
                        root->c = 0, root->l->c = 1;
                    }
                else
                    if(root->l == Rson) {//左右
                        RR(root->l, Rgson), LL(root, root->l);
                        root->c = 0, root->r->c = 1;
                    }
                    else {//右左
                        LL(root->r, Rgson), RR(root, root->r);
                        root->c = 0, root->l->c = 1;
                    }
            }
        }
    }
    return;
}

void Remove(TreeNode* &pa, TreeNode* &root, int num) {
    if(root == nullptr) return;
    if(num < root->key) Remove(root, root->l, num);
    else if(num > root->key) Remove(root, root->r, num);
    else if(root->l != nullptr && root->r != nullptr) {//左右孩子均存在
        TreeNode *tem = root, *s = root->r;//tem为s的父节点
        while(s->l != nullptr) tem = s, s = s->l;
        root->key = s->key;
        Remove(tem, root->r, s->key);
    }
    else if(root->l == nullptr && root->r == nullptr) {//左右孩子不存在
        if(root->c == 0) {//删除节点为黑，且没有孩子
            if(pa->c == 0 && root != pa->r && pa->r->c == 0) {//黑黑黑结构（删左下黑）
                if(pa->r->l == nullptr && pa->r->r == nullptr) {}//黑黑黑
                else if(pa->r->l == nullptr && pa->r->r->c == 1) {
                    RR(pa, pa->r); 
                    pa->c = 1, pa->r->c = 0;
                }//黑黑黑+4号红
                else if(pa->r->l->c == 1 && (pa->r->r == nullptr || pa->r->r->c == 1)) {
                    LL(pa->r, pa->r->l), RR(pa, pa->r);
                    pa->c = 0;
                }//黑黑黑+3号红 或 黑黑黑+34号红
            }
            else if(pa->c == 0 && root != pa->l && pa->l->c == 0) {//黑黑黑结构（删右下黑）
                if(pa->l->l == nullptr && pa->l->r == nullptr) {}//黑黑黑
                else if(pa->l->l->c == 1 && pa->l->r == nullptr) {
                    LL(pa, pa->l);
                    pa->c = 1, pa->l->c = 0;             
                }//黑黑黑+1号红
                else if((pa->l->l == nullptr || pa->l->l->c == 1) && pa->l->r->c == 1) {
                    RR(pa->l, pa->l->r), LL(pa, pa->l);
                    pa->c = 0;
                }//黑黑黑+2号红 或 黑黑黑+12号红
            }
            else if(pa->c == 1 && root != pa->r && pa->r->c == 0) {//红黑黑结构（删左下黑）
                if(pa->r->l == nullptr && pa->r->r == nullptr) {
                    pa->c = 0, pa->r->c = 1;
                }//红黑黑
                else if(pa->r->l == nullptr && pa->r->r->c == 1) {
                    RR(pa, pa->r);
                    pa->c = 1, pa->l->c = 0, pa->r->c = 1;
                }//红黑黑+4号红
                else if(pa->r->l->c == 1 && (pa->r->r == nullptr || pa->r->r->c == 1)) {
                    LL(pa->r, pa->r->l), RR(pa, pa->r);
                    pa->l->c = 0;
                }//红黑黑+3号红 或 红黑黑+34号红
            }
            else if(pa->c == 1 && root != pa->l && pa->l->c == 0) {//红黑黑结构（删右下黑）
                if(pa->l->l == nullptr && pa->l->r == nullptr) {}//红黑黑
                else if(pa->l->l->c == 1 && pa->l->r == nullptr) {
                    LL(pa, pa->l);
                    pa->c = 1, pa->l->c = 0, pa->r->c = 1;             
                }//红黑黑+1号红
                else if((pa->l->l == nullptr || pa->l->l->c == 1) && pa->l->r->c == 1) {
                    RR(pa->l, pa->l->r), LL(pa, pa->l);
                    pa->r->c = 0;
                }//红黑黑+2号红 或 红黑黑+12号红
            }
            else if(pa->c == 0 && RBson(pa)) {//
                if(root == pa->l) {LL(pa, pa->r), pa->c = 0, pa->l->r->c = 1;}
                else if(root == pa->r) {RR(pa, pa->l), pa->c = 0, pa->r->l->c = 1;}
            }
        }
        TreeNode* oldroot = root;
        root = (root->l != nullptr) ? root->l : root->r;
        delete oldroot;
    }
    else {//存在一个孩子（黑父子红）
        TreeNode* oldroot = root;
        root = (root->l != nullptr) ? root->l : root->r;//root指向红孩子
        delete oldroot;
        root->c = 0;//将红孩子染黑
    }
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
        if(p->c == 1) printf("R ");
        else printf("B ");
        p = p->r;
    }
}

inline void PrintPreOrder(TreeNode *root) {
    stack<TreeNode*> S;
    TreeNode *p = root;
    while(1) {
        while(p != nullptr) {
            printf("%d ", p->key);
            if(p->c == 1) printf("R ");
            else printf("B ");
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
    TreeNode *root = new TreeNode(0, 0), *temp = new TreeNode(0, 0);//根节点为黑
    char tem[10]; int num;
    for(int i = 0; i < T; i++) {
        if(root == nullptr) root = new TreeNode(0, 0);
        scanf("%s %d", tem, &num);
        if(root->key == 0) root->key = num;//输入根节点
        else if(tem[0] == 'I') Insert(root, num);//插入
        else Remove(temp, root, num);//删除
        root->c = 0;
    }
    PrintInOrder(root);
    printf("\n\n");
    PrintPreOrder(root);
    printf("\n");
    return 0;
}

/*
5
Insert 8
Insert 9
Insert 3
Insert 4
Insert 5

4
Insert 8
Insert 9
Insert 3
Insert 4

3
Insert 5
Insert 3
Insert 4
*/