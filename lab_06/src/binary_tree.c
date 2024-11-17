#include "binary_tree.h"

#include <stdio.h>
#include <stdlib.h>

#define COUNT 10

int N_COMPARE = 0;

tree_node_t *tree_node_create(int key, tree_node_t *left, tree_node_t *right)
{
    tree_node_t *node = malloc(sizeof(tree_node_t));
    if (node)
    {
        node->key = key;
        node->left = left;
        node->right = right;
    }
    return node;
}

void tree_node_destroy(tree_node_t *node)
{
    free(node);
}

void bin_tree_insert(tree_node_t **root, int key)
{
    if (!*root)
    {
        *root = tree_node_create(key, NULL, NULL);
        return;
    }

    tree_node_t *curr = *root;
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
                curr->left = tree_node_create(key, NULL, NULL);
        }

        else
        {
            if (curr->right)
                curr = curr->right;
            else
                curr->right = tree_node_create(key, NULL, NULL);
        }
    }
}

static tree_node_t *find_max(tree_node_t *root)
{
    if (!root->right)
        return root;

    return find_max(root->right);
}

static tree_node_t *remove_max(tree_node_t *root)
{
    if (!root)
        return NULL;

    if (!root->right)
    {
        tree_node_t *tmp = root->left;
        tree_node_destroy(root);
        return tmp;
    }

    root->right = remove_max(root->right);
    return root;
}

tree_node_t *bin_tree_remove(tree_node_t *root, int key)
{
    if (!root)
        return NULL;

    if (key < root->key)
        root->left = bin_tree_remove(root->left, key);
    if (key > root->key)
        root->right = bin_tree_remove(root->right, key);
    else
    {
        if (!root->left && !root->right)
        {
            tree_node_destroy(root);
            return NULL;
        }

        if (!root->left)
        {
            tree_node_t *tmp = root->right;
            tree_node_destroy(root);
            return tmp;
        }
        if (!root->right)
        {
            tree_node_t *tmp = root->left;
            tree_node_destroy(root);
            return tmp;
        }

        tree_node_t *successor = find_max(root->left);
        root->key = successor->key;
        root->left = remove_max(root->left);
    }

    return root;
}

tree_node_t *bin_tree_find(tree_node_t *root, int key)
{
    if (!root)
        return root;

    if (root->key == key)
        return root;

    if (key < root->key)
        return bin_tree_find(root->left, key);
    else
        return bin_tree_find(root->right, key);
}

void bin_tree_apply_pre_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param)
{
    if (!root)
        return;

    func(root, param);
    bin_tree_apply_pre_order(root->left, func, param);
    bin_tree_apply_pre_order(root->right, func, param);
}

void bin_tree_apply_in_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param)
{
    if (!root)
        return;

    bin_tree_apply_in_order(root->left, func, param);
    if (func)
        func(root, param);
    bin_tree_apply_in_order(root->right, func, param);
}

void bin_tree_apply_post_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param)
{
    if (!root)
        return;

    bin_tree_apply_post_order(root->left, func, param);
    bin_tree_apply_post_order(root->right, func, param);
    func(root, param);
}

static void destroy_apply(tree_node_t *node, void *param)
{
    tree_node_destroy(node);
}

void bin_tree_destroy(tree_node_t *root)
{
    bin_tree_apply_post_order(root, destroy_apply, NULL);
}

tree_node_t *read_tree(FILE *stream)
{
    tree_node_t *root = NULL;

    int key;
    while (fscanf(stream, "%d", &key) == 1)
    {
        bin_tree_insert(&root, key);
    }

    return root;
}

static void print2DUtil(tree_node_t *root, int space)
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

void print_2D(tree_node_t *root)
{
    print2DUtil(root, 0);
}
