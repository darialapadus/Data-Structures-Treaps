#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <ctime>
using namespace std;
ifstream fin("abce.in");
ofstream fout("abce.out");

struct TreapNode {
    int key, priority;
    TreapNode *left, *right;

    TreapNode(int k) {
        key = k;
        priority = rand();
        left = right = nullptr;
    }
};

class Treap {
private:
    TreapNode* root;

    void subarbore(TreapNode* node, int key, TreapNode* &left, TreapNode* &right) {
        if (node == nullptr) {
            left = right = nullptr;
        }
        else if (node->key <= key) {
            subarbore(node->right, key, node->right, right);
            left = node;
        }
        else {
            subarbore(node->left, key, left, node->left);
            right = node;
        }
    }

    void inserare(TreapNode* &node, TreapNode* new_node) {
        TreapNode* current_node = node;
        TreapNode* parent_node = nullptr;
        while (current_node != nullptr && current_node->priority > new_node->priority) {
            parent_node = current_node;
            current_node = new_node->key <= current_node->key ? current_node->left : current_node->right;
        }
        subarbore(current_node, new_node->key, new_node->left, new_node->right);
        if (parent_node == nullptr) {
            node = new_node;
        }
        else if (new_node->key <= parent_node->key) {
            parent_node->left = new_node;
        }
        else {
            parent_node->right = new_node;
        }
    }

    TreapNode* arbore(TreapNode* left, TreapNode* right) {
        if (left == nullptr || right == nullptr) {
            return left == nullptr ? right : left;
        }
        else if (left->priority > right->priority) {
            left->right = arbore(left->right, right);
            return left;
        }
        else {
            right->left = arbore(left, right->left);
            return right;
        }
    }

    TreapNode* gasire(TreapNode* node, int key) {
        while (node != nullptr && node->key != key) {
            node = key < node->key ? node->left : node->right;
        }
        return node;
    }

    TreapNode* stergere(TreapNode* node, int key) {
        if (node == nullptr) {
            return nullptr;
        }
        else if (node->key == key) {
            TreapNode* temp = arbore(node->left, node->right);
            delete node;
            return temp;
        }
        else {
            node->left = stergere(node->left, key);
            node->right = stergere(node->right, key);
            return node;
        }
    }

    int cautare(TreapNode* node, int key) {
        while (node != nullptr) {
            if (node->key == key) {
                return 1;
            }
            node = key < node->key ? node->left : node->right;
        }
        return 0;
    }

    int MaxY(TreapNode* node, int key) {
        int max_val = INT_MIN;
        while (node != nullptr) {
            if (node->key <= key) {
                max_val = max(max_val, node->key);
                node = node->right;
            }
            else {
                node = node->left;
            }
        }
        return max_val;
    }

    int MinY(TreapNode* node, int key) {
        int min_val = INT_MAX;
        while (node != nullptr) {
            if (node->key >= key) {
                min_val = min(min_val, node->key);
                node = node->left;
            }
            else {
                node = node->right;
            }
        }
        return min_val;
    }

    void ordonare(TreapNode* node, int low, int high, vector<int>& res) {
        if (node == nullptr) {
            return;
        }
        ordonare(node->left, low, high, res);
        if (node->key >= low && node->key <= high) {
            res.push_back(node->key);
        }
        ordonare(node->right, low, high, res);
    }

public:
    Treap() {
        root = nullptr;
    }

    void inserare(int key) {
        inserare(root, new TreapNode(key));
    }

    void stergere(int key) {
        root = stergere(root, key);
    }

    int cautare(int key) {
        return cautare(root, key);
    }

    int MaxY(int key) {
        return MaxY(root, key);
    }

    int MinY(int key) {
        return MinY(root, key);
    }

    vector<int> ordonare(int low, int high) {
        vector<int> res;
        ordonare(root, low, high, res);
        return res;
    }
};

int main() {
    srand(time(nullptr));

    int Q;
    fin >> Q;

    Treap t;

    while (Q--) {
        int op, X, Y;
        fin >> op >> X;
        if (op == 1) {
            t.inserare(X);
        }
        else if (op == 2) {
            t.stergere(X);
        }
        else if (op == 3) {
            fout << t.cautare(X) << "\n";
        }
        else if (op == 4) {
            fout << t.MaxY(X) << "\n";
        }
        else if (op == 5) {
            fout << t.MinY(X) << "\n";
        }
        else if (op == 6) {
            fin >> Y;
            vector<int> res = t.ordonare(X, Y);
            for (int z : res) {
                fout << z << " ";
            }
            fout << "\n";
        }
    }

    fin.close();
    fout.close();

    return 0;
}
