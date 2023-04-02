#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

class BBST {
    
public:
    BBST() {
        root = nullptr;
    }

    void insert(int data) {
        root = insertNode(root, data);
    }

    void remove(int data) {
        root = removeNode(root, data);
    }

    void printInorder() {
        printInorderHelper(root);
        cout << endl;
    }

private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    Node* insertNode(Node* node, int data) {
        if (node == nullptr) {
            Node* newNode = new Node();
            newNode->data = data;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            return newNode;
        }

        if (data < node->data) {
            node->left = insertNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = insertNode(node->right, data);
        }
        else {
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;

        int balance = balanceFactor(node);

        if (balance > 1 && data < node->left->data) {
            return rotateRight(node);
        }
        if (balance < -1 && data > node->right->data) {
            return rotateLeft(node);
        }
        if (balance > 1 && data > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && data < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node* removeNode(Node* node, int data) {
        if (node == nullptr) {
            return node;
        }

        if (data < node->data) {
            node->left = removeNode(node->left, data);
        }
        else if (data > node->data) {
            node->right = removeNode(node->right, data);
}
else {
if (node->left == nullptr && node->right == nullptr) {
delete node;
node = nullptr;
}
else if (node->left == nullptr) {
Node* temp = node;
node = node->right;
delete temp;
}
else if (node->right == NULL) {
Node* temp = node;
node = node->left;
delete temp;
}
else {
Node* temp = findMin(node->right);
node->data = temp->data;
node->right = removeNode(node->right, temp->data);
}
}
    if (node == NULL) {
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0) {
        return rotateRight(node);
    }
    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && balanceFactor(node->right) <= 0) {
        return rotateLeft(node);
    }
    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

static void printInorderHelper(Node* node) {
    if (node == nullptr) {
        return;
    }

    printInorderHelper(node->left);
    cout << node->data << " ";
    printInorderHelper(node->right);
}
};
int main() {
    BBST tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(40);
    tree.insert(50);
    cout << "Inorder traversal of the constructed tree is: ";
    tree.printInorder();

    tree.remove(20);

    cout << "Inorder traversal of the modified tree is: ";
    tree.printInorder();
}

