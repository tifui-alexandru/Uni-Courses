// Splay Trees
// insert(x) => insert x into the tree if it is not already in the tree
// find(x) => return pointer to the value of x in the tree or nullptr if x does not exist in the tree
// erase(x) => erase x from the tree if it is in the tree
// predecessor(x) => return pointer to the largest value in the tree that is <= than x or nullptr if all elements are > than x
// successor(x) =? return pointer to the smallest value in the tree that is >= than x or nullptr if all elements are < than x
#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

class SplayTree {
private:
    struct node {
        int value;
        node *left, *right, *parent;
        node(const int &vl = 0, node* p = nullptr, node* l = nullptr, node* r = nullptr) : value(vl), parent(p), left(l), right(r) {}
    };
    node* root;

    // rotation on the edge A - left(A)
    void left_rotate(node *A) {
        node *B = A -> right;

        if (A -> right) A -> right = B -> left;
        if (B -> left) B -> left -> parent = A;

        B -> parent = A -> parent;
        if (A -> parent == nullptr) {
            if (A == root)
                root = B;
        }
        else if (A == A -> parent -> left)
                A -> parent -> left = B;
        else
            A -> parent -> right = B;

        B -> left = A;
        A -> parent = B; 
    }

    // rotation on the edge A - right(A)
    void right_rotate(node *A) {
        node *B = A -> left;

        if (A -> left) A -> left = B -> right;
        if (B -> right) B -> right -> parent = A;

        B -> parent = A -> parent;
        if (A -> parent == nullptr) {
            if (A == root)
                root = B;
        }
        else if (A == A -> parent -> left)
                A -> parent -> left = B;
        else
            A -> parent -> right = B;

        B -> right = A;
        A -> parent = B; 
    }

    void splay(node *x) {
        if (!x) return;
        while (x -> parent) {
            if (x -> parent -> parent == nullptr) { // zig
                if (x -> parent -> left == x) right_rotate(x -> parent);
                else left_rotate(x -> parent);
            }
            else {
                if (x -> parent -> left == x) {
                    if (x -> parent -> parent -> left == x -> parent) {
                        // zig-zig
                        right_rotate(x -> parent -> parent);
                        right_rotate(x -> parent);
                    }
                    else {
                        // zig-zag
                        right_rotate(x -> parent);
                        left_rotate(x -> parent);
                    }
                }
                else {
                    if (x -> parent -> parent -> right == x -> parent) {
                        // zig-zig
                        left_rotate(x -> parent -> parent);
                        left_rotate(x -> parent);
                    }
                    else {
                        // zig-zag
                        left_rotate(x -> parent);
                        right_rotate(x -> parent);
                    }
                }
            }
        }
    }

    void replace(node* A, node* B) {
        if (!A -> parent) 
            root = B;
        else if (A == A -> parent -> left)
            A -> parent -> left = B;
        else
            A -> parent -> right = B;
        if (B) B -> parent = A -> parent;
    }

    node* get_max_node(node *x) const {
        if (!x) return nullptr;
        node *current_node = x;
        while (current_node -> right) 
            current_node = current_node -> right;
        return current_node;
    }

    node* get_min_node(node* x) const {
        if (!x) return nullptr;
        node *current_node = x;
        while (current_node -> left)
            current_node = current_node -> left;
        return current_node;
    }

public:
    SplayTree(node* r = nullptr, int sz = 0) : root(r){}

    node* predecessor(const int &x) {
        node *current_node = root, *last_node = nullptr;
        while (current_node) {
            if (x == current_node -> value) {
                splay(current_node);
                return current_node; // found
            }
            if (x < current_node -> value)
                current_node = current_node -> left;
            else{
                last_node = current_node;
                current_node = current_node -> right;
            }
        }
        splay(last_node);
        return last_node;
    }

    node* successor(const int &x) {
        node *current_node = root, *last_node = nullptr;
        while (current_node) {
            if (x == current_node -> value) {
                splay(current_node);
                return current_node; // found
            }
            if (x < current_node -> value){
                last_node = current_node;
                current_node = current_node -> left;
            }
            else
                current_node = current_node -> right;
        }
        splay(last_node);
        return last_node;
    }

    node* find(const int &x) {
        node *current_node = root;
        while (current_node) {
            if (x == current_node -> value) {
                splay(current_node);
                return current_node; // found;
            }
            if (x < current_node -> value)
                current_node = current_node -> left;
            else
                current_node = current_node -> right;
        }
        return nullptr;
    }

    void insert(const int &x) {
        node *current_node = root, *last_node = nullptr;
        while (current_node) {
            last_node = current_node;
            if (x == current_node -> value) return; // already in the tree
            if (x < current_node -> value)
                current_node = current_node -> left;
            else
                current_node = current_node -> right; 
        }

        current_node = new node(x, last_node);
        if (!last_node) root = current_node;
        else if (x < last_node -> value) last_node -> left = current_node;
        else last_node -> right = current_node;

        splay(current_node);
    }

    void erase(const int &x) {
        node *current_node = find(x);
        if (!current_node) return; // not in the tree

        splay(current_node);

        if (!current_node -> left)
            replace(current_node, current_node -> right);
        else if (!current_node -> right)
            replace(current_node, current_node -> left);
        else {
            node *minn = get_min_node(current_node -> right);
            if (minn -> parent != current_node) {
                replace(minn, minn -> right);
                minn -> right = current_node -> right;
                minn -> right -> parent = minn;
            }
            replace(current_node, minn);
            minn -> left = current_node -> left;
            minn -> left -> parent = minn;
        }

        delete current_node;
    }

    void print_interval(const int &lsh, const int &rsh) {
        int x = lsh;
        while (true) {
            auto it = successor(x);
            if (!it or it -> value > rsh) break;
            fout << it -> value << ' ';
            x = it -> value + 1;
        }
        fout << '\n';
    }
};

int main() {
    int Q, op, x, y;
    fin >> Q;
    SplayTree T;
    while (Q--) {
        fin >> op >> x;
        switch (op) {
        case 1:
            T.insert(x);
            break;
        case 2:
            T.erase(x);
            break;
        case 3:
            fout << (bool)T.find(x) << '\n';
            break;
        case 4:
            fout << T.predecessor(x) -> value << '\n';
            break;
        case 5:
            fout << T.successor(x) -> value << '\n';
            break;
        case 6:
            fin >> y;
            T.print_interval(x, y);
            break;
        }
    }

    return 0;
}