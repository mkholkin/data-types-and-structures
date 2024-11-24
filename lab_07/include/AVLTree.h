#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <stdio.h>

typedef struct AVLTreeNode_* AVLTreeNode;

struct AVLTreeNode_
{
    int key;
    AVLTreeNode left;
    AVLTreeNode right;
};

AVLTreeNode AVLTreeNode_create(int key, AVLTreeNode left, AVLTreeNode right);
void        AVLTreeNode_destroy(AVLTreeNode node);

void        AVLTree_insert(AVLTreeNode* root, int key);
AVLTreeNode AVLTree_remove(AVLTreeNode root, int key);
AVLTreeNode AVLTree_find(AVLTreeNode root, int key);
void        AVLTree_applyPreOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param);
void        AVLTree_applyInOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param);
void        AVLTree_applyPostOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param);
void        AVLTree_destroy(AVLTreeNode root);

AVLTreeNode readAVLTree(FILE* stream);
void        print2D(AVLTreeNode root);

extern int N_COMPARE;

#endif //AVL_TREE_H
