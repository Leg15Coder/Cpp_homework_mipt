#include <iostream>
#include <memory>
#include <queue>
#include <stack>
#include <string>
#include <vector>

class Tree;

class Tree {
public:
    struct Node {
        int value;
        std::shared_ptr<Node> left;
        std::shared_ptr<Node> right;
        std::weak_ptr<Node> parent;

        Node(int val) : value(val) {}
    };

    std::shared_ptr<Node> root;

    Tree() : root(nullptr) {}

    void traverse_v1() const {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::cout << "BFS Traversal: ";
        std::queue<std::shared_ptr<Node>> q;
        q.push(root);

        while (!q.empty()) {
            std::shared_ptr<Node> current = q.front();
            q.pop();

            std::cout << current->value << " ";

            if (current->left) {
                q.push(current->left);
            }
            if (current->right) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }

    void traverse_v2() const {
        if (!root) {
            std::cout << "Tree is empty." << std::endl;
            return;
        }

        std::cout << "DFS Traversal: ";
        std::stack<std::shared_ptr<Node>> s;
        s.push(root);

        while (!s.empty()) {
            std::shared_ptr<Node> current = s.top();
            s.pop();

            std::cout << current->value << " ";

            if (current->right) {
                s.push(current->right);
            }
            if (current->left) {
                s.push(current->left);
            }
        }
        std::cout << std::endl;
    }
};

int main() {
    Tree myTree;
    myTree.root = std::make_shared<Tree::Node>(1);

    myTree.root->left = std::make_shared<Tree::Node>(2);
    myTree.root->right = std::make_shared<Tree::Node>(3);

    myTree.root->left->parent = myTree.root;
    myTree.root->right->parent = myTree.root;

    myTree.root->left->left = std::make_shared<Tree::Node>(4);
    myTree.root->left->right = std::make_shared<Tree::Node>(5);
    myTree.root->right->left = std::make_shared<Tree::Node>(6);
    myTree.root->right->right = std::make_shared<Tree::Node>(7);

    myTree.root->left->left->parent = myTree.root->left;
    myTree.root->left->right->parent = myTree.root->left;
    myTree.root->right->left->parent = myTree.root->right;
    myTree.root->right->right->parent = myTree.root->right;

    std::cout << "\nTree traversals:" << std::endl;
    myTree.traverse_v1();
    myTree.traverse_v2();

    if (auto parent_of_4 = myTree.root->left->left->parent.lock()) {
        std::cout << "Node 4's parent value: " << parent_of_4->value << std::endl;
    }
    
    if (auto parent_of_7 = myTree.root->right->right->parent.lock()) {
        std::cout << "Node 7's parent value: " << parent_of_7->value << std::endl;
    }
}
