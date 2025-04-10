#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height; // Wysokość węzła
};

// Funkcja pomocnicza do obliczania wysokości węzła
int height(Node* node) {
    if (node == nullptr) {
        return 0; // Jeśli węzeł jest pusty, wysokość to 0
    }
    return node->height;
}


// Rotacja w lewo
Node* rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left; // Przemieszczamy lewe poddrzewo y na prawe poddrzewo x
    y->left = x;        // x staje się lewym dzieckiem y

    // Aktualizacja wysokości
    x->height = max(height(x->left), height(x->right)) + 1;  // Nowa wysokość x
    y->height = max(height(y->left), height(y->right)) + 1;  // Nowa wysokość y
    
    return y; // Zwracamy nowy korzeń
}

// Rotacja w prawo
Node* rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right; // Przemieszczamy prawe poddrzewo x na lewe poddrzewo y
    x->right = y;       // y staje się prawym dzieckiem x

    // Aktualizacja wysokości
    y->height = max(height(y->left), height(y->right)) + 1;  // Nowa wysokość y
    x->height = max(height(x->left), height(x->right)) + 1;  // Nowa wysokość x
    
    return x; // Zwracamy nowy korzeń
}

// Rotacja lewo-prawo
Node* rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left); // Najpierw wykonujemy rotację w lewo
    return rotateRight(node);            // Następnie wykonujemy rotację w prawo
}

// Rotacja prawo-lewo
Node* rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right); // Najpierw wykonujemy rotację w prawo
    return rotateLeft(node);                // Następnie wykonujemy rotację w lewo
}

// Funkcja balansująca - sprawdza, czy węzeł jest zrównoważony, jeśli nie, wykonuje odpowiednią rotację
Node* balance(Node* node) {
    int balanceFactor = height(node->left) - height(node->right); // Różnica wysokości lewego i prawego poddrzewa

    // Lewo-Lewo (LL) - Wykonujemy rotację w prawo
    if (balanceFactor > 1 && node->left->key > node->left->left->key) {
        return rotateRight(node);
    }

    // Prawo-Prawo (RR) - Wykonujemy rotację w lewo
    if (balanceFactor < -1 && node->right->key < node->right->right->key) {
        return rotateLeft(node);
    }

    // Lewo-Prawo (LR) - Wykonujemy rotację lewo-prawo
    if (balanceFactor > 1 && node->left->key < node->left->right->key) {
        return rotateLeftRight(node);
    }

    // Prawo-Lewo (RL) - Wykonujemy rotację prawo-lewo
    if (balanceFactor < -1 && node->right->key > node->right->left->key) {
        return rotateRightLeft(node);
    }

    return node; // Drzewo jest zrównoważone, nie musimy nic robić
}

// Funkcja wstawiająca nowy węzeł do drzewa
Node* insert(Node* node, int key) {
    // Jeśli drzewo jest puste, tworzymy nowy węzeł
    if (node == nullptr) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->left = newNode->right = nullptr;
        newNode->height = 1; // Wysokość nowego węzła to 1
        return newNode;
    }

    // Wstawiamy element jak w standardowym drzewie BST
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // Duplikaty nie są dozwolone
    }

    // Po wstawieniu węzła aktualizujemy wysokość węzła
    node->height = 1 + max(height(node->left), height(node->right));

    // Po każdej operacji wstawiania balansujemy drzewo
    return balance(node);
}

// Funkcja do wyświetlania drzewa (pre-order)
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Główna funkcja do testowania
int main() {
    Node* root = nullptr;

    // Wstawiamy elementy do drzewa AVL
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 25);
    root = insert(root, 5);

    // Wyświetlamy drzewo
    cout << "Pre-order traversal of the AVL tree is: ";
    preOrder(root);

    return 0;
}
