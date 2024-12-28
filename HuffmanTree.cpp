#include<bits/stdc++.h>
#define endl '\n'
#define int long long
using namespace std;

struct HuffmanNode {
    char data;
    int weight;
    HuffmanNode *left;
    HuffmanNode *right;
};

void Sort_HuffmanNode(vector<HuffmanNode*>& H) {
    for(int i = 0; i < H.size(); i++) {
        for(int j = i; j < H.size(); j++) {
            if(H[i]->weight > H[j]->weight) {
                swap(H[i], H[j]);
            }
        }
    }
}

void CreatHuffmanNode(vector<char> ch, vector<int> freq) {
    vector<HuffmanNode*> H;

    for(int i = 0; i < ch.size(); i++) {
        H.push_back(new HuffmanNode);
        H[i]->data = ch[i];
        H[i]->weight = freq[i];
        H[i]->left = H[i]->right = nullptr;
    }

    Sort_HuffmanNode(H);
}

HuffmanNode* CreatHuffmanTree(vector<HuffmanNode*> H) {
    for(int i = 0; i < H.size(); i++) {
        HuffmanNode *t = new HuffmanNode;
        t->data = ' ';
        t->weight = H[i]->weight + H[i + 1]->weight;
        t->left = H[i];
        t->right = H[i + 1];

        int j = i + 2;
        for(; j < H.size() && H[j]->weight < t->weight; j++) {
            H[j - 1] = H[j];
        }
        H[j - 1] = t;
    }

    return H[H.size() - 1];
}

int INT_WPL_PreOrder;
void WpL_PreOrder(HuffmanNode *root, int k) {
    if(root == nullptr) return;
    if(root->left == nullptr && root->right == nullptr) {
        INT_WPL_PreOrder += root->weight * k;
    }

    WpL_PreOrder(root->left, k + 1);
    WpL_PreOrder(root->right, k + 1);
}

signed main() {
    return 0;
}