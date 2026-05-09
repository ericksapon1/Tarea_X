#pragma once
#include "Student.h"

class AVLTree {
private:
    struct AVLNode {
        Student data;
        int height;
        AVLNode* left;
        AVLNode* right;
        AVLNode(const Student& s) : data(s), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode* root;
    int node_count;

    int height(AVLNode* node) const;
    int getBalance(AVLNode* node) const;
    bool isLess(const Student& a, const Student& b) const;
    void destroyTree(AVLNode* node);

    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);

    AVLNode* insert(AVLNode* node, const Student& student);
    void reverseInOrder(AVLNode* node, int& rank) const;
    AVLNode* searchExactScore(AVLNode* node, int score) const;

public:
    AVLTree();
    ~AVLTree();

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    void insert(const Student& student);
    void displayRanking() const;
    void searchByScore(int skill_score) const;
    void displayStats() const;
};