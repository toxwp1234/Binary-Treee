#include <iostream>
#include <vector>
#include <algorithm>
#include <random>   

using namespace std;

// Struktura węzła drzewa
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {} //konsturktor klasy
};












////Trewresacje 

void inorder(Node* root) { //działa
    if (root != nullptr) {
        inorder(root->left);              // najpierw lewe poddrzewo
        cout << root->key << " ";         // potem bieżący węzeł
        inorder(root->right);             // potem prawe poddrzewo
    }
}

////

// Wstawianie elementu do BST
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key); //jeżeli ten node jest nullptr to ustwiama jego key na nową watośc
    }
    if (key < root->key) //jeżeli wartośc jest mniejsza od watości noda na któą patrzymy idziemy w lewo
        root->left = insert(root->left, key); // wzywanie funkcji przez funkcje 
    else //jeżeli wartośc jest wieksza lub równa od watości noda na któą patrzymy idziemy w prawo
        root->right = insert(root->right, key); // wzywanie funkcji przez funkcje 
    return root;
}



// ffunkcja obliczająca wysokość drzewa
int height(Node* node) {
    // jeśli węzeł jest pusty  to wysokość 0 
    if (node == nullptr)
        return 0;

    //jak nie  to obliczamy wysokość lewego i prawego poddrzewa\
     Funkcja wywołuje się rekurencyjnie dla dzieci
    // Wybieramy większą z dwóch wysokości i dodajemy 1 (bo obecny węzeł też się liczy)
    return std::max(height(node->left), height(node->right)) + 1;


}

// Funkcja obliczająca współczynnik równowagi węzła uzywając wyskości 
int getBalance(Node* node) {
    if (node != nullptr) { //jeżeli node nie jest pusty to obliczamy jego wspólczycnnik



        return height(node->left) - height(node->right); //moze być ujemne 
    } else { /// a jeżeli jest niczym to wpisujemy 0 jako jego wspólczynnik
        return 0;
    }
}




// Wstawianie elementu do BST
Node* insert(Node* root, int key) {
    if (root == nullptr) {
        return new Node(key); //jeżeli ten node jest nullptr to ustwiama jego key na nową watośc
    }
    if (key < root->key) //jeżeli wartośc jest mniejsza od watości noda na któą patrzymy idziemy w lewo
        root->left = insert(root->left, key); // wzywanie funkcji przez funkcje 
    else //jeżeli wartośc jest wieksza lub równa od watości noda na któą patrzymy idziemy w prawo
        root->right = insert(root->right, key); // wzywanie funkcji przez funkcje 
    return root;
}



Node* minValueNode(Node* node) { /// chcąc usunąć node z dwoma dziećmi ide do lewej storny Prawgo dziecka usuwanego i biore go jako nowy rodzic
    Node* current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}


Node* deleteNode(Node* root, int key) {
    if (root == nullptr) return root;

    if (key < root->key) // jeżeli szukany klucz jest mniejszy to idziemy w lewo
        root->left = deleteNode(root->left, key);
    else if (key > root->key) // jeżeli szukany klucz jest większy to idziemy w prawo
        root->right = deleteNode(root->right, key);
    else { //znaleslismy node z wartoścą którą chcemy usunąć
        // przypadek kiedy znaleźliśmy węzeł do usunięcia
        


        //przypadki jeżeli są pojedyńcze dzieci
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root; // usuwamy węzeł
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root; // usuwamy węzeł
            return temp;
        }
        // koniec przypadków dla pojedyńczych dzieci


        // jeżeli węzeł ma dwoje dzieci, szukam zastępcy kogoś kto go zastąpi
        Node* temp = minValueNode(root->right);
        root->key = temp->key; // kopiujemy wartość następcy

        root->right = deleteNode(root->right, temp->key); // usuwamy następnika rekurencyjnie 
    }
    return root;
}



Node* balanceTree(Node* root) {
    if (root == nullptr) return root;

    // Sprawdzamy balans drzewa
    if (getBalance(root) > 1 || getBalance(root) < -1) {
        int val = root->key;

        // Usuwamy korzeń i dodajemy go ponownie
        root = deleteNode(root, val);
        root = insert(root, val); // Dodajemy korzeń z powrotem, aby przywrócić równowagę
    }

    // Powtarzamy dla każdego dziecka, jeśli są niezbalansowane
    if (root->left != nullptr)
        root->left = balanceTree(root->left);
    if (root->right != nullptr)
        root->right = balanceTree(root->right);

    return root;
}





int main(){

    vector<int> random ={12, 22, 63, 4, 55, 61, 7, 32, 89, 17, 25, 48,1, 91, 36, 58, 19, 77, 49, 64, 81, 92, 33, 18, 56, 44};

    Node* root = nullptr;
    for (int val : random) {
        root = insert(root, val);
    }



    
    inorder(root);

 


};