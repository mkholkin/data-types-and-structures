#include "BSTree.h"

#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

TreeNode TreeNode_create(int key, TreeNode left, TreeNode right)
{
    TreeNode node = malloc(sizeof(TreeNode));
    if (node)
    {
        node->key = key;
        node->left = left;
        node->right = right;
    }
    return node;
}

void TreeNode_destroy(TreeNode node)
{
    free(node);
}

void BSTree_insert(TreeNode* root, int key)
{
    if (!*root)
    {
        *root = TreeNode_create(key, NULL, NULL);
        return;
    }

    TreeNode curr = *root;
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
                curr->left = TreeNode_create(key, NULL, NULL);
        }

        else
        {
            if (curr->right)
                curr = curr->right;
            else
                curr->right = TreeNode_create(key, NULL, NULL);
        }
    }
}

static TreeNode findMax(TreeNode root)
{
    if (!root->right)
        return root;

    return findMax(root->right);
}

static TreeNode removeMax(TreeNode root)
{
    if (!root)
        return NULL;

    if (!root->right)
    {
        TreeNode tmp = root->left;
        TreeNode_destroy(root);
        return tmp;
    }

    root->right = removeMax(root->right);
    return root;
}

TreeNode BSTree_remove(TreeNode root, int key)
{
    if (!root)
        return NULL;

    if (++N_COMPARE && key < root->key)
        root->left = BSTree_remove(root->left, key);
    else if (++N_COMPARE && key > root->key)
        root->right = BSTree_remove(root->right, key);
    else
    {
        if (!root->left && !root->right)
        {
            TreeNode_destroy(root);
            return NULL;
        }

        if (!root->left)
        {
            TreeNode tmp = root->right;
            TreeNode_destroy(root);
            return tmp;
        }
        if (!root->right)
        {
            TreeNode tmp = root->left;
            TreeNode_destroy(root);
            return tmp;
        }

        TreeNode successor = findMax(root->left);
        root->key = successor->key;
        root->left = removeMax(root->left);
    }

    return root;
}

TreeNode BSTree_find(TreeNode root, int key)
{
    if (!root)
        return root;

    N_COMPARE++;
    if (root->key == key)
        return root;

    N_COMPARE++;
    if (key < root->key)
        return BSTree_find(root->left, key);
    else
        return BSTree_find(root->right, key);
}

void BSTree_applyPreOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param)
{
    if (!root)
        return;

    func(root, param);
    BSTree_applyPreOrder(root->left, func, param);
    BSTree_applyPreOrder(root->right, func, param);
}

void BSTree_applyInOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param)
{
    if (!root)
        return;

    BSTree_applyInOrder(root->left, func, param);
    if (func)
        func(root, param);
    BSTree_applyInOrder(root->right, func, param);
}

void BSTree_applyPostOrder(TreeNode root, void (*func)(TreeNode node, void* param), void* param)
{
    if (!root)
        return;

    BSTree_applyPostOrder(root->left, func, param);
    BSTree_applyPostOrder(root->right, func, param);
    func(root, param);
}

static void destroy_apply(TreeNode node, void* param)
{
    TreeNode_destroy(node);
}

void BSTree_destroy(TreeNode root)
{
    BSTree_applyPostOrder(root, destroy_apply, NULL);
}

TreeNode readBSTree(FILE* stream)
{
    TreeNode root = NULL;

    int key;
    while (fscanf(stream, "%d", &key) == 1)
    {
        BSTree_insert(&root, key);
    }

    return root;
}

static void print2DUtil(TreeNode root, int space)
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

void print2D(TreeNode root)
{
    print2DUtil(root, 0);
}
