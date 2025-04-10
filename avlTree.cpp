#include <iostream>
#include <algorithm>
#include <vector>
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

/////////////tam nie patrz 








///trewersacjev
///trewersacje
///trewersacje
///trewersacje
///trewersacje
///trewersacje
///trewersacje
///trewersacje
///trewersacje
//wypisanie wszystkich elementów drzewa w porządku rosnącym (in-order),
void inorder(Node* root) { //działa
    if (root != nullptr) {
        inorder(root->left); // najpierw lewe poddrzewo
        cout << root->key << " ";      // potem bieżący węzeł
        inorder(root->right);  // potem prawe poddrzewo
    }
}


/// wypisanie wszystkich elementów drzewa w porządku pre-order,
/// @brief Wypisuje najpierw korzeń potem całośc lewego a potem cały prawy
///  
void preOrder(Node* node) {
    if (node == nullptr) return;  // Jeśli węzeł jest pusty, nic nie rób

    //Wypisz korzeń
    std::cout << node->key<< " ";
    
    //lewe poddrzewo
    preOrder(node->left);
    
    //prawe poddrzewo
    preOrder(node->right);
}

/////////////////





/// @brief Usuwam najpier lewe poddrzewa a potem prawe
/// @param node 
void postOrderDelete(Node* node) {
    if (node == nullptr) return;  // Jeśli węzeł jest pusty, nic nie rób
    
    // Rekurencyjnie usuń lewe poddrzewo
    postOrderDelete(node->left);
    
    // Rekurencyjnie usuń prawe poddrzewo
    postOrderDelete(node->right);
    
    // Usuń węzeł i wypisz element
    cout <<"Usuwam :"<< node->key << " \n";
    delete node;
}


////



////////////////
////////////////
////////////////
////////////////
////////////////
////////////////
////////////////



Node* search(Node* node, int val){
    if (node == nullptr || node->key == val) {
        return node;
    }
    
    // Jeśli klucz jest mniejszy niż bieżący węzeł, szukamy w lewym poddrzewie
    if (val < node->key) {
        return search(node->left, val);
    }
    
    // Jeśli klucz jest większy niż bieżący węzeł, szukamy w prawym poddrzewie
    return search(node->right, val);
};


void look_andpreorder(Node* node, int val){
   
    Node* fragment = search(node,val);


    if(fragment != nullptr){
    preOrder(fragment);
    }
    else{cout<<"Nie znaleziono węzła o podanym kluczu.";};





}

















///MIN MAX


///wyszukanie w drzewie elementu o najmniejszej i największej wartości i wypisanie ścieżki poszukiwania (od korzenia do elementu szukanego),


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
    cout <<"\n\n";
}
//

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
    cout <<"\n\n";


}


////////////////
////////////////
////////////////
////////////////usuwanie





//szukam najmniejszego node w drzewie obecnie
Node* findMinNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, int key) {
    if (root == nullptr) { // Jeśli drzewo jest puste, nic nie rób
        return root;    
    }

    // Szukamy węzła do usunięcia
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {// jeżeli szukany klucz jest większy to idziemy w prawe dziecko
        root->right = deleteNode(root->right, key); //  jeżeli szukany klucz jest mniejszy to idziemy w lewe dziecko
    } else {
        // Węzeł znaleziony
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {// jeżeli węzeł ma dwoje dzieci, szukam zastępcy kogoś kto go zastąpi
            Node* temp = findMinNode(root->right);
            root->key = temp->key;// kopiujemy wartość następcy
            root->right = deleteNode(root->right, temp->key);// usuwamy następnika rekurencyjnie 
        }
    }

    if (root == nullptr) {
        return root;
    }

    // Aktualizacja wysokości
    root->height = max(height(root->left), height(root->right)) + 1;

    // Sprawdzenie balansu
    int balance = getBalance(root);

    // Przypadki rotacji
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

///usunięcie elementu drzewa o wartości klucza podanej przez użytkownika (użytkownik wpisuje ile węzłów chce usunąć i podaje wartości kluczy),
/// @param root 
void polecenieusuwania(Node* root){
    int n;
    cout << "Ile kluczy chcesz usunąć? ";
    cin >> n;
    cout << "\n\n";
    for (int i = 0; i < n; ++i) {
        int key;
        cout << "Podaj wartość klucza do usunięcia: ";
        cin >> key;
        root = deleteNode(root, key);
        cout << "Drzewo po usunięciu klucza " << key << ":\n";
        inorder(root);
        cout << "\n";
    }
}


////usunięcie całego drzewa element po elemencie metodą post-order (wypisz element przed usunięciem),


void deleteEntireTree(Node*& root) {
    if (root == nullptr) {
        cout << "Drzewo jest już puste.\n";
        return;
    }
    cout << "Usuwanie drzewa metodą post-order:\n";
    postOrderDelete(root); // Usuwanie elementów w kolejności post-order
    root = nullptr; // Ustawienie wskaźnika na nullptr po usunięciu
    cout << "\nDrzewo zostało całkowicie usunięte.\n";
}



/////wypisanie w porządku pre-order poddrzewa, którego korzeń (klucz) podaje użytkownik,

void printSubtreePreOrder(Node* root, int key) {
    Node* subtreeRoot = search(root, key); // Wyszukaj węzeł o podanym kluczu
    if (subtreeRoot != nullptr) {
        cout << "Poddrzewo w porządku pre-order dla klucza " << key << ":\n";
        preOrder(subtreeRoot); // Wypisz poddrzewo w porządku pre-order
        cout << "\n";
    } else {
        cout << "Nie znaleziono węzła o kluczu " << key << ".\n";
    }
}


////////////////
////////////////
////////////////
////////////////




int main(){

    vector<int> random ={12, 22, 63, 4, 55, 61, 7, 32, 89, 17, 25, 48,1, 91};
    //{12, 22, 63, 4, 55, 61, 7, 32, 89, 17, 25, 48,1, 91, 36, 58, 19, 77, 49, 64, 81, 92, 33, 18, 56, 44};

    Node* root = nullptr;
    for (int val : random) {
        root = insert(root, val);
    }
    findMax(root);



};