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


///Funkcje do drzew


// Minimalny Element


void findMin(Node* root) {
    if (root == nullptr) {
        cout << "Drzewo jest puste." << endl;
        return;
    }

    Node* current = root;
    cout << "";
    
    // Przechodzimy w lewo, aż do  końca
    while (current->left != nullptr) { //idz w lewo aż zobaczysz nullptr --? ostatnia node
        cout << current->key << " do ";
        current = current->left;
    }
    cout << current->key << endl;
}
//
///
//
//
// Maksymalny Element

void findMax(Node* root) {
    if (root == nullptr) {
        cout << "Drzewo jest puste." << endl;
        return;
    }

    Node* current = root;
    cout << "";
    
    // Przechodzimy w prawo końca
    while (current->right != nullptr) { // w prawo idz aż zobaczysz nullptr --? ostatnia node
        cout << current->key << " do ";
        current = current->right;
    }
    cout << current->key << endl;
}


/// pre order 


void preOrder(Node* root) { //działa
    if (root != nullptr) {
        cout << root->key << " ";// Najpierw wypisujemy korzeń
        preOrder(root->left); // lewe poddrzewo
        preOrder(root->right);   // prawe poddrzewo
    }
}


// inorder 


void inorder(Node* root) { //działa
    if (root != nullptr) {
        inorder(root->left);              // najpierw lewe poddrzewo
        cout << root->key << " ";         // potem bieżący węzeł
        inorder(root->right);             // potem prawe poddrzewo
    }
}




// Usuwanie drzewa od dzieci do góry


void postOrder_del(Node* root) { //działa
    if (root != nullptr) {
        postOrder_del(root->left);// Najpierw lewe poddrzewo
        postOrder_del(root->right);// Potem prawe poddrzewo
        cout << "Usuwam: " << root->key << endl;  // Wypisanie wartości przed usunięciem
        delete root;                  // Usuwanie 
    }
}


/// 



// Funkcja do znalezienia węzła o podanym kluczu 

// POMOCNICZA
Node* findNode(Node* root, int key) {
    if (root == nullptr || root->key == key) //jeżeli moja node jest pusta albo jej klucz jest równy poszukiwanemu zwróć
        return root;

    if (key < root->key) //jeżeli klucz jest mniejszy od klucza noda to idz porównaj go z dzieckiem po lewej
        return findNode(root->left, key);  // Szukamy w lewym poddrzewie
    else //jeżeli klucz nie jest mniejszy od klucza noda to idz porównaj go z dzieckiem po prwaej
        return findNode(root->right, key); // Szukamy w prawym poddrzewie
}

/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA



void Find_And_preOrder(Node* Full_tree,int key){ //DZIAŁA

    Node* node_with_key = findNode(Full_tree,key); // znajduje node z moją szukaną wartoścą


    preOrder(node_with_key); //wywołumje funkcje preorder czyli drukuje je najpier lewo dla każdego po tem prawo

};



/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA


/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA
/// GŁÓWNA FUNKCJA DO PREORDER OD DANEGO KLUCZA

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



void deletion(Node* root,int key,int ile){


    for (int i = 0; i < ile; ++i) {
        
        cout << "Podaj wartość klucza do usunięcia: "<< key<<"\n";
        // cin >> key;
        root = deleteNode(root, key);
        cout << "Drzewo po usunięciu " << key << ": ";
        preOrder(root);
        cout << endl;




};


}






int main(){


    vector<int> random ={12, 22, 63, 4, 55, 61, 7, 32, 89, 17, 25, 48,1, 91, 36, 58, 19, 77, 49, 64, 81, 92, 33, 18, 56, 44};

    Node* root = nullptr;
    for (int val : random) {
        root = insert(root, val);
    }
    preOrder(root);
    deletion(root,12,1);

};
