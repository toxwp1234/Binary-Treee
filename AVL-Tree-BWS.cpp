#include <iostream>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* node) {
    if (node != nullptr)
        return node->height;
    else
        return 0;
}

int balanceFactor(Node* node) {
    if (node != nullptr)
        return height(node->left) - height(node->right);
    else
        return 0;
}

void updateHeight(Node* node) {
    if (node)
        node->height = max(height(node->left), height(node->right))+1;
}
//======================================FUnkcje Obrotu
Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

Node* balance(Node* node) {
    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* insert(Node* node, int key) {
    if (!node) return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);
    return balance(node);//dodaje node ale musze jeszcze wszysko zbalansować
}

// ========== DSW Algorithm ==========

// Utworzenie vina
void treeToVine(Node*& root, int& size) {
    Node Temp_2(0); // 
    Temp_2.right = root;
    Node* vineTail = &Temp_2;
    Node* reszta = root;
    size = 0;

    while (reszta) {
        if (reszta->left) {
            Node* temp = reszta->left;
            reszta->left = temp->right;
            temp->right = reszta;
            vineTail->right = temp;
            reszta = temp;
        } else {
            vineTail = reszta;
            reszta = reszta->right;
            ++size;//zwiekszam size
        }
    }

    root = Temp_2.right;
}

// Kompresowanie drzewa
void compress(Node*& root, int count) {
    Node Temp_2(0);
    Temp_2.right = root;
    Node* scanner = &Temp_2;

    for (int i = 0; i < count; ++i) {
        Node* child = scanner->right;
        if (!child || !child->right) break;
        Node* grandChild = child->right;

        scanner->right = grandChild;
        child->right = grandChild->left;
        grandChild->left = child;

        scanner = grandChild;
    }

    root = Temp_2.right;
}

// Zamiana vine w idealnie zbalansowane drzewo
void vineToTree(Node*& root, int size) {
    int m = pow(2, floor(log2(size + 1))) - 1;
    compress(root, size - m);
    for (m = m / 2; m > 0; m /= 2)
        compress(root, m);
}

// =================== DRUKOWANIE ====================

void printPreOrder(Node* node) {
    if (node) {
        cout << node->key << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

void printPostOrder(Node* node) {
    if (node) {
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->key << " ";
    }
}

void printInOrder(Node* node) {
    if (node) {
        printInOrder(node->left);
        cout << node->key << " ";
        printInOrder(node->right);
    }
}


//=========================================== Funkcja do zbalanzowania BSW


void balansuj(Node* root){
  
   // DSW balance
    int size = 0;//liczba węzłów w vine
    treeToVine(root, size);
    vineToTree(root, size);
  
  
}


int main() {
    Node* root = nullptr;

    int values[] = {10, 20, 3,1,1,1,5, 4, 8, 15, 30, 25, 35};
    for (int v : values)
        root = insert(root, v);

    cout << "przed DSW ->";
    printInOrder(root);
    cout << endl;

   
    
    
    balansuj(root); 


    cout << "DSW PO ->";
    printInOrder(root);
    cout << endl;

    return 0;
}
