#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <stdio.h>

typedef struct tree_node tree_node_t;

struct tree_node
{
    int key;
    tree_node_t *left;
    tree_node_t *right;
};

tree_node_t *tree_node_create(int key, tree_node_t *left, tree_node_t *right);
void tree_node_destroy(tree_node_t *node);
void bin_tree_insert(tree_node_t **root, int key);
tree_node_t *bin_tree_remove(tree_node_t *root, int key);
tree_node_t *bin_tree_find(tree_node_t *root, int key);
void bin_tree_apply_pre_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param);
void bin_tree_apply_in_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param);
void bin_tree_apply_post_order(tree_node_t *root, void (*func)(tree_node_t *node, void *param), void *param);
void bin_tree_destroy(tree_node_t *root);

tree_node_t *read_tree(FILE *stream);
void print_2D(tree_node_t *root);

extern int N_COMPARE;

#endif //BINARY_TREE_H
