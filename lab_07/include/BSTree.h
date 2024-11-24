#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdio.h>

typedef struct TreeNode_* TreeNode;

struct TreeNode_
{
    int key;
    TreeNode left;
    TreeNode right;
};

TreeNode TreeNode_create(int key, TreeNode left, TreeNode right);
void     TreeNode_destroy(TreeNode node);

void     BSTree_insert(TreeNode* root, int key);
TreeNode BSTree_remove(TreeNode root, int key);
TreeNode BSTree_find(TreeNode root, int key);
void     BSTree_applyPreOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param);
void     BSTree_applyInOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param);
void     BSTree_applyPostOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param);
void     BSTree_destroy(TreeNode root);

TreeNode readBSTree(FILE* stream);
void print2D(TreeNode root);

extern int N_COMPARE;

#endif //BINARY_TREE_H
