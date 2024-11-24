#include "AVLTree.h"

#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

AVLTreeNode AVLTreeNode_create(int key, AVLTreeNode left, AVLTreeNode right)
{
    AVLTreeNode node = malloc(sizeof(AVLTreeNode));
    if (node)
    {
        node->key = key;
        node->left = left;
        node->right = right;
    }
    return node;
}

void AVLTreeNode_destroy(AVLTreeNode node)
{
    free(node);
}

void AVLTree_insert(AVLTreeNode* root, int key)
{
    if (!*root)
    {
        *root = AVLTreeNode_create(key, NULL, NULL);
        return;
    }

    AVLTreeNode curr = *root;
    while (curr)
    {
        N_COMPARE++;
        if (key == curr->key)
            return;

        N_COMPARE++;
        if (key < curr->key)
        {
            if (curr->left)
                curr = curr->left;
            else
                curr->left = AVLTreeNode_create(key, NULL, NULL);
        }

        else
        {
            if (curr->right)
                curr = curr->right;
            else
                curr->right = AVLTreeNode_create(key, NULL, NULL);
        }
    }
}

static AVLTreeNode findMax(AVLTreeNode root)
{
    if (!root->right)
        return root;

    return findMax(root->right);
}

static AVLTreeNode removeMax(AVLTreeNode root)
{
    if (!root)
        return NULL;

    if (!root->right)
    {
        AVLTreeNode tmp = root->left;
        AVLTreeNode_destroy(root);
        return tmp;
    }

    root->right = removeMax(root->right);
    return root;
}

AVLTreeNode AVLTree_remove(AVLTreeNode root, int key)
{
    if (!root)
        return NULL;

    if (++N_COMPARE && key < root->key)
        root->left = AVLTree_remove(root->left, key);
    else if (++N_COMPARE && key > root->key)
        root->right = AVLTree_remove(root->right, key);
    else
    {
        if (!root->left && !root->right)
        {
            AVLTreeNode_destroy(root);
            return NULL;
        }

        if (!root->left)
        {
            AVLTreeNode tmp = root->right;
            AVLTreeNode_destroy(root);
            return tmp;
        }
        if (!root->right)
        {
            AVLTreeNode tmp = root->left;
            AVLTreeNode_destroy(root);
            return tmp;
        }

        AVLTreeNode successor = findMax(root->left);
        root->key = successor->key;
        root->left = removeMax(root->left);
    }

    return root;
}

AVLTreeNode AVLTree_find(AVLTreeNode root, int key)
{
    if (!root)
        return root;

    N_COMPARE++;
    if (root->key == key)
        return root;

    N_COMPARE++;
    if (key < root->key)
        return AVLTree_find(root->left, key);
    else
        return AVLTree_find(root->right, key);
}

void AVLTree_applyPreOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param)
{
    if (!root)
        return;

    func(root, param);
    AVLTree_applyPreOrder(root->left, func, param);
    AVLTree_applyPreOrder(root->right, func, param);
}

void AVLTree_applyInOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param)
{
    if (!root)
        return;

    AVLTree_applyInOrder(root->left, func, param);
    if (func)
        func(root, param);
    AVLTree_applyInOrder(root->right, func, param);
}

void AVLTree_applyPostOrder(AVLTreeNode root, void (*func)(AVLTreeNode node, void* param), void* param)
{
    if (!root)
        return;

    AVLTree_applyPostOrder(root->left, func, param);
    AVLTree_applyPostOrder(root->right, func, param);
    func(root, param);
}

static void destroy_apply(AVLTreeNode node, void* param)
{
    AVLTreeNode_destroy(node);
}

void AVLTree_destroy(AVLTreeNode root)
{
    AVLTree_applyPostOrder(root, destroy_apply, NULL);
}

AVLTreeNode readAVLTree(FILE* stream)
{
    AVLTreeNode root = NULL;

    int key;
    while (fscanf(stream, "%d", &key) == 1)
    {
        AVLTree_insert(&root, key);
    }

    return root;
}

static void print2DUtil(AVLTreeNode root, int space)
{
    if (root == NULL)
        return;

    space += COUNT;

    print2DUtil(root->right, space);

    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->key);

    print2DUtil(root->left, space);
}

void print2D(AVLTreeNode root)
{
    print2DUtil(root, 0);
}
