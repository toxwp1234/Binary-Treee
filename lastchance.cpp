#include <iostream>
#include <vector>
#include <cmath> // Dodano dla funkcji log2
using namespace std;
struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Funkcja do wstawiania elementów do drzewa BST
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return new Node(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Funkcja do wykonania rotacji w prawo
void rotateRight(Node*& grandparent, Node*& parent) {
    Node* child = parent->left;
    parent->left = child->right;
    child->right = parent;
    parent = child;
    if (grandparent) {
        grandparent->right = parent;
    }
}

// Funkcja do wykonania rotacji w lewo
void rotateLeft(Node*& grandparent, Node*& parent) {
    Node* child = parent->right;
    parent->right = child->left;
    child->left = parent;
    parent = child;
    if (grandparent) {
        grandparent->right = parent;
    }
}

// Funkcja do przekształcenia drzewa w "listę" (vine)
int treeToVine(Node*& root) {
    Node* grandparent = nullptr;
    Node* parent = root;
    int size = 0;

    while (parent != nullptr) {
        if (parent->left != nullptr) {
            rotateRight(grandparent, parent);
            if (grandparent == nullptr) {
                root = parent;
            }
        } else {
            grandparent = parent;
            parent = parent->right;
            size++;
        }
    }
    return size;
}

// Funkcja do przekształcenia "listy" w zrównoważone drzewo
void vineToTree(Node*& root, int size) {
    int leaves = size + 1 - (1 << (int)log2(size + 1));
    Node* grandparent = nullptr;
    Node* parent = root;

    for (int i = 0; i < leaves; ++i) {
        rotateLeft(grandparent, parent);
        if (grandparent == nullptr) {
            root = parent;
        }
        grandparent = parent;
        parent = parent->right;
    }

    size -= leaves;
    while (size > 1) {
        size /= 2;
        grandparent = nullptr;
        parent = root;

        for (int i = 0; i < size; ++i) {
            rotateLeft(grandparent, parent);
            if (grandparent == nullptr) {
                root = parent;
            }
            grandparent = parent;
            parent = parent->right;
        }
    }
}

// Funkcja do zrównoważenia drzewa za pomocą metody DSW
void balanceTree(Node*& root) {
    int size = treeToVine(root);
    vineToTree(root, size);
}

// Funkcja do wypisania drzewa w porządku in-order
void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    std::cout << root->value << " ";
    inOrder(root->right);
}

// Funkcja pomocnicza do obliczania wysokości drzewa
int height(Node* root) {
    if (root == nullptr) return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + std::max(leftHeight, rightHeight);
}

// Funkcja sprawdzająca, czy drzewo jest zrównoważone
bool isBalanced(Node* root) {
    if (root == nullptr) return true;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    // Sprawdzenie różnicy wysokości i rekurencyjne sprawdzenie poddrzew
    return std::abs(leftHeight - rightHeight) <= 1 &&
           isBalanced(root->left) &&
           isBalanced(root->right);
}


int main() {
    Node* root = nullptr;

    // Wstawianie elementów do drzewa BST

    vector<int> values = { 10, 20, 30, 40, 50, 25 };

    for (int value : values) {
        root = insert(root, value);
    } 


    std::cout << "Drzewo przed zrównoważeniem (in-order): ";
    inOrder(root);
    std::cout << std::endl;

    // Równoważenie drzewa
    balanceTree(root);

    std::cout << "Drzewo po zrównoważeniu (in-order): ";
    inOrder(root);
    std::cout << std::endl;


        // Sprawdzenie, czy drzewo jest zrównoważone po balansowaniu
        std::cout << "Czy drzewo jest zrównoważone? " 
        << (isBalanced(root) ? "Tak" : "Nie") << std::endl;

    return 0;
}