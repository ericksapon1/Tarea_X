#include "AVL.h"
#include <iostream>
#include <algorithm>

AVLTree::AVLTree() : root(nullptr), node_count(0) {}

AVLTree::~AVLTree() { destroyTree(root); }

void AVLTree::destroyTree(AVLNode* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

int AVLTree::height(AVLNode* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(AVLNode* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

bool AVLTree::isLess(const Student& a, const Student& b) const {
    if (a.skill_score == b.skill_score) {
        return a.student_id < b.student_id;
    }
    return a.skill_score < b.skill_score;
}

AVLTree::AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTree::AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

AVLTree::AVLNode* AVLTree::insert(AVLNode* node, const Student& student) {
    if (!node) {
        node_count++;
        return new AVLNode(student);
    }

    if (isLess(student, node->data))
        node->left = insert(node->left, student);
    else if (isLess(node->data, student))
        node->right = insert(node->right, student);
    else
        return node; // Duplicado exacto

    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Balanceo (considerando desempate)
    if (balance > 1 && isLess(student, node->left->data))
        return rightRotate(node);

    if (balance < -1 && isLess(node->right->data, student))
        return leftRotate(node);

    if (balance > 1 && isLess(node->left->data, student)) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && isLess(student, node->right->data)) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void AVLTree::insert(const Student& student) {
    root = insert(root, student);
}

void AVLTree::reverseInOrder(AVLNode* node, int& rank) const {
    if (!node) return;
    reverseInOrder(node->right, rank);
    std::cout << rank++ << ". " << node->data.full_name 
              << " - Score: " << node->data.skill_score 
              << " (ID: " << node->data.student_id << ")\n";
    reverseInOrder(node->left, rank);
}

void AVLTree::displayRanking() const {
    if (!root) {
        std::cout << "Ranking vacio.\n";
        return;
    }
    int rank = 1;
    reverseInOrder(root, rank);
}

AVLTree::AVLNode* AVLTree::searchExactScore(AVLNode* node, int score) const {
    if (!node) return nullptr;
    if (node->data.skill_score == score) return node;
    
    if (score < node->data.skill_score)
        return searchExactScore(node->left, score);
    return searchExactScore(node->right, score);
}

void AVLTree::searchByScore(int score) const {
    AVLNode* result = searchExactScore(root, score);
    if (result) {
        std::cout << "Encontrado: " << result->data.full_name << " | ID: " << result->data.student_id << "\n";
    } else {
        std::cout << "Estudiante con score " << score << " no encontrado.\n";
    }
}

void AVLTree::displayStats() const {
    std::cout << "--- Estadisticas AVL ---\n"
              << "Altura actual: " << height(root) << "\n"
              << "Factor de balance raiz: " << getBalance(root) << "\n"
              << "Nodos insertados: " << node_count << "\n";
}