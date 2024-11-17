#ifndef COMMANDS_H
#define COMMANDS_H

#include "binary_tree.h"
#include "return_codes.h"

#define TREE_FILEPATH "../tree.txt"
#define FILEPATH "../tree.txt"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void process_show_tree(tree_node_t *root);
void process_tree_insert(tree_node_t *root);
void process_tree_remove(tree_node_t **root);
void process_tree_find(tree_node_t *root);
void process_file_insert(void);
void process_insert_both(tree_node_t *root);
void process_tree_pre_order(tree_node_t *root);
void process_tree_in_order(tree_node_t *root);
void process_tree_post_order(tree_node_t *root);
void process_count_nodes_in_each_level(tree_node_t *root);
void process_show_stat1(void);
void process_show_stat2(void);

#endif //COMMANDS_H
