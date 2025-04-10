#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

int height(Node* n) {
    if (n) {
        return n->height;
    } else {
        return 0;
    }
}

int getBalance(Node* n) {
    if (n) {
        return height(n->left) - height(n->right);
    } else {
        return 0;
    }
}

Node* createNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    node->height = 1;  // Nowy węzeł ma wysokość 1
    return node;
}
/// 


///
///         Funkcje Obrotu
///




/// 
//       y                 x
//      / \               / \
//     x   C      =>     A   y
//    / \                   / \
//    A  B                 B   C
Node* rightRotate(Node* y) {
    Node* x = y->left;    // x to lewe dziecko y
    Node* T = x->right;  // T2 to prawe dziecko x

    // Rotacja:
    x->right = y;         // y staje się prawym dzieckiem x
    y->left = T;         // T2 staje się lewym dzieckiem y

    // Aktualizacja wysokości
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}



//     x                 y
//    / \               / \
//   A   y      =>     x   C
//       / \             / \
//      B   C           A   B

Node* leftRotate(Node* x) {
    Node* y = x->right;   // y to prawe dziecko x
    Node* T = y->left;   // T2 to lewe dziecko y

    // Rotacja:
    y->left = x;          // x staje się lewym dzieckiem y
    x->right = T;        // T2 staje się prawym dzieckiem x

    // Aktualizacja wysokości
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* insert(Node* node, int key) {
    if (!node) //jeżeli ten node jest pusty to ustwiama jego key na nową watośc
        return createNode(key);

    if (key < node->key) //jeżeli wartośc jest mniejsza od watości noda na któą patrzymy idziemy w lewo
        node->left = insert(node->left, key);// wzywanie funkcji przez funkcje 
    else//jeżeli wartośc jest wieksza lub równa od watości noda na któą patrzymy idziemy w prawo
        node->right = insert(node->right, key);// wzywanie funkcji przez funkcje 
    
    
    
    
    
        // else // Duplicate keys not allowed
    //     return node;


    //     if (root == nullptr) {
    //         return new Node(key); //jeżeli ten node jest nullptr to ustwiama jego key na nową watośc
    //     }
    //     if (key < root->key) //jeżeli wartośc jest mniejsza od watości noda na któą patrzymy idziemy w lewo
    //         root->left = insert(root->left, key); // wzywanie funkcji przez funkcje 
    //     else //jeżeli wartośc jest wieksza lub równa od watości noda na któą patrzymy idziemy w prawo
    //         root->right = insert(root->right, key); // wzywanie funkcji przez funkcje 
    //     return root;
    // }
    


    // Aktualizacja wysokości
    node->height = max(height(node->left), height(node->right))+1;

    // Sprawdź balans
    int balance = getBalance(node);


    /// jeżeli wysokośc prawego jest większa to balans jest ujemny = obrót w lewo
    /// jeżeli wyskośc lewego jest większa to balans jest dodatkit ==> obrót w prawo

    // Przypadki rotacji

    // left left Case
    if (balance > 1 && key <= node->left->key)
        return rightRotate(node);

    // right right Case
    if (balance < -1 && key >= node->right->key)
        return leftRotate(node);


        /// Podwójne obroty


    // left right Case


     // środek stał się glownym węzłem poddrzewa

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left); //obręcam lewy node w lewo
        return rightRotate(node); // obrkęcem całośc w prawo 
    }

    // right left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);//obręcam prawy node w prawo
        return leftRotate(node); //obkrecam całośc w lewo 
    }

    return node;
}


// Funkcja pomocnicza do konwersji drzewa do "vine"
Node* treeToVine(Node* root) {
    Node* pseudoRoot = new Node();
    pseudoRoot->right = root;
    Node* tail = pseudoRoot;
    Node* rest = root;

    while (rest) {
        if (rest->left) {
            Node* temp = rest->left;
            rest->left = temp->right;
            temp->right = rest;
            rest = temp;
            tail->right = temp;
        } else {
            tail = rest;
            rest = rest->right;
        }
    }

    return pseudoRoot->right;
}

// Funkcja do wykonania rotacji w celu balansowania
// Funkcja do wykonania rotacji w celu balansowania
void compress(Node*& root, int count) {
    Node* piwot = root; // Ustawiamy wskaźnik na początek "vine"
    for (int i = 0; i < count; i++) { // Wykonujemy określoną liczbę rotacji
        Node* child = piwot->right; // Pobieramy prawe dziecko bieżącego węzła (następny węzeł w "vine")
        
        //  rotacja w lewo
        piwot->right = child->right; 
        piwot = piwot->right; // Przechodzimy do następnego węzła w "vine"
        
        // Przestawiamy wskaźniki, aby "child" stał się lewym dzieckiem bieżącego węzła
        child->right = piwot->left; // Lewy podwęzeł bieżącego węzła staje się prawym podwęzłem "child"
        piwot->left = child; // "child" staje się lewym dzieckiem bieżącego węzła
    }
}
// Funkcja do balansowania DSW
Node* balanceDSW(Node* root) {
    // Konwertujemy drzewo binarne na "vine" (ciąg węzłów przypominający listę jednokierunkową)
    root = treeToVine(root);

    // Liczymy liczbę węzłów w drzewie, aby wiedzieć, ile operacji balansowania będzie potrzebnych
    int size = 0;
    Node* temp = root;
    while (temp) {
        size++; // Zwiększamy licznik dla każdego węzła
        temp = temp->right; // Przechodzimy do następnego węzła w "vine"
    }

    
    //ile node powinno zostać w pełni zbalansowanych
    int m = pow(2, floor(log2(size + 1))) - 1;

    // Kompresujemy drzewo, aby uzyskać początkowy balans dla węzłów, które nie mieszczą się w pełnym drzewie binarnym
    compress(root, size - m);

    // Powtarzamy proces kompresji, zmniejszając liczbę węzłów do skompresowania o połowę w każdej iteracji,
    // aż drzewo stanie się w pełni zbalansowane
    for (m = m / 2; m > 0; m /= 2) {
        compress(root, m);
    }

    // Zwracamy zbalansowane drzewo
    return root;
}


void preOrder(Node* root) {
    if (root) {
        cout << root->key << " "; // Wypisujemy klucz bieżącego węzła
        preOrder(root->left);    // Przechodzimy do lewego poddrzewa
        preOrder(root->right);   // Przechodzimy do prawego poddrzewa
    }
}







// Funkcja do przechodzenia drzewa w porządku in-order
void inorder(Node* root) {
    if (root) {
        inorder(root->left); // Przechodzimy do lewego poddrzewa
        cout << root->key << " "; // Wypisujemy klucz bieżącego węzła
        inorder(root->right); // Przechodzimy do prawego poddrzewa
    }
}


int main(){

    vector<int> random ={12, 22, 63, 4, 55, 61, 7, 32, 89, 17, 25, 48,1, 91, 36, 58, 19, 77, 49, 64, 81, 92, 33, 18, 56, 44};

    Node* root = nullptr;
    for (int val : random) {
        root = insert(root, val);
    }


    cout << "Drzewo przed balansowaniem: ";
    inorder(root); // Wypisujemy drzewo przed balansowaniem
    cout << endl;
    root = balanceDSW(root); // Balansujemy drzewo
    cout << "Drzewo po balansowaniu: ";
    inorder(root); // Wypisujemy drzewo po balansowaniu
    cout << endl;
 


};