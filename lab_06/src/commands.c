#include "../include/commands.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

#include "io.h"
#include "utils/time.h"

static bool validate_int(const char *str)
{
    const char *pend;
    strtol(str, &pend, 10);
    return !*pend;
}

static return_code input_int(const char *prompt, int *val)
{
    char buff[20 + 1] = {0};

    const return_code rc = input_until_valid(prompt, buff, 20 + 1, validate_int);
    if (rc == OK)
        *val = strtol(buff, NULL, 10);

    return rc;
}

static void file_append(const char *fliename, int num)
{
    FILE *stream = fopen(fliename, "a");
    assert(stream);

    fseek(stream, SEEK_END, 0);
    fprintf(stream, " %d", num);
    fseek(stream, SEEK_SET, 0);

    fclose(stream);
}


void process_show_tree(tree_node_t *root)
{
    if (!root)
    {
        printf("[!] Empty tree\n");
        return;
    }

    print_2D(root);
}

void process_tree_insert(tree_node_t **root)
{
    int num;
    input_int("Enter number: ", &num);
    bin_tree_insert(root, num);
}

void process_tree_remove(tree_node_t **root)
{
    int num;
    input_int("Enter number: ", &num);
    *root = bin_tree_remove(*root, num);
}

void process_tree_find(tree_node_t *root)
{
    int num;
    input_int("Enter number: ", &num);
    tree_node_t *node = bin_tree_find(root, num);
    if (!node)
    {
        printf("[!] Node not found\n");
        return;
    }

    printf(ANSI_COLOR_GREEN"    %d\n"ANSI_COLOR_RESET, node->key);
    printf("  /   \\\n");
    if (node->left)
        printf(" %d", node->left->key);
    else
        printf("  ");
    printf("     ");
    if (node->right)
        printf("%d", node->right->key);
    printf("\n");
}

void process_file_insert(void)
{
    int num;
    input_int("Enter number: ", &num);

    file_append(FILEPATH, num);

    printf("[+] Successfully inserted %d in file\n", num);
}

void process_insert_both(tree_node_t *root)
{
    int num;
    input_int("Enter number: ", &num);

    file_append(FILEPATH, num);

    printf("[+] Successfully inserted %d in file\n", num);

    bin_tree_insert(&root, num);
    printf("[+] Successfully inserted %d in tree\n", num);
}

static void print(tree_node_t *node, void *param)
{
    printf("%d ", node->key);
}

void process_tree_pre_order(tree_node_t *root)
{
    bin_tree_apply_pre_order(root, print, NULL);
    printf("\n");
}

void process_tree_in_order(tree_node_t *root)
{
    bin_tree_apply_in_order(root, print, NULL);
    printf("\n");
}

void process_tree_post_order(tree_node_t *root)
{
    bin_tree_apply_post_order(root, print, NULL);
    printf("\n");
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int maxDepth(tree_node_t *root)
{
    if (root == NULL)
        return 0;

    if (root->left == NULL && root->right == NULL)
        return 1;

    if (root->left == NULL)
        return 1 + maxDepth(root->right);

    if (root->right == NULL)
        return 1 + maxDepth(root->left);

    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

int countNodesOnDepth(tree_node_t *root, int depth, int curr_depth)
{
    if (root == NULL)
        return 0;

    if (curr_depth == depth)
        return 1;

    return countNodesOnDepth(root->left, depth, curr_depth + 1) + countNodesOnDepth(root->right, depth, curr_depth + 1);
}

void process_count_nodes_in_each_level(tree_node_t *root)
{
    int depth = maxDepth(root);
    for (int i = 0; i < depth; i++)
    {
        int n = countNodesOnDepth(root, i, 0);
        printf("[+] Level %d: %d\n", i, n);
    }
}

void process_show_stat_insert(void)
{
    srand(time(NULL));
    const char *file = "../stat.txt";

    tree_node_t *tree = NULL;

    printf(
        " Insertions   [BST] time total (ns)   [BST] time avg (ns)   [BST] comparisons avg    [File] time total (ns)   [File] time avg (ns) \n"\
        "------------ ----------------------- --------------------- ------------------------ ------------------------ ----------------------\n");
    for (int limit = 10; limit <= 100000; limit *= 10)
    {
        fclose(fopen(file, "w"));

        nsec_t tree_time = 0;
        nsec_t file_time = 0;
        int comparisons = 0;

        for (int i = 0; i < limit; i++)
        {
            int num = rand() % 100000;

            N_COMPARE = 0;
            nsec_t beg = nanoseconds_now();
            bin_tree_insert(&tree, num);
            nsec_t end = nanoseconds_now();
            tree_time += end - beg;
            comparisons += N_COMPARE;

            beg = nanoseconds_now();
            file_append(file, num);
            end = nanoseconds_now();
            file_time += end - beg;
        }

        printf(
            "%12d %23zu %21lf %24lf %24zu %22lf\n",
            limit, tree_time, (double)tree_time / limit, (double)comparisons / limit, file_time,
            (double)file_time / limit
        );
    }

    bin_tree_destroy(tree);
}

static tree_node_t *sortedArrayToBSTRecur(int arr[], int start, int end)
{
    if (start > end) return NULL;

    // Find the middle element
    int mid = start + (end - start) / 2;

    // Create root node
    tree_node_t *root = tree_node_create(arr[mid], NULL, NULL);

    // Create left subtree
    root->left = sortedArrayToBSTRecur(arr, start, mid - 1);

    // Create right subtree
    root->right = sortedArrayToBSTRecur(arr, mid + 1, end);

    return root;
}

static tree_node_t *sortedArrayToBST(int arr[], int n)
{
    return sortedArrayToBSTRecur(arr, 0, n - 1);
}

void process_show_stat(void)
{
    nsec_t beg, end;

    printf(
        "                 Degenerate tree                   |                 Unbalancded tree                  |                    Balanced tree\n"
        " ------------------------------------------------- | ------------------------------------------------- | ------------------------------------------------- \n"\
        "  Depth   Elements    Find (ns)       Sort(ns)     |  Depth   Elements    Find (ns)       Sort(ns)     |  Depth   Elements    Find (ns)       Sort(ns)     \n"\
        " ------- ---------- -------------- --------------- | ------- ---------- -------------- --------------- | ------- ---------- -------------- --------------- \n"
    );
    for (int depth = 1; depth <= 20; depth++)
    {
        tree_node_t *left_tree = NULL;
        double left_tree_find = 0;
        double left_tree_sort = 0;
        for (int i = depth - 1; i >= 0; i--)
        {
            bin_tree_insert(&left_tree, i);
        }

        int left_tree_depth = maxDepth(left_tree);

        for (int _ = 0; _ < 100; _++)
            for (int i = 0; i < depth; i++)
            {
                beg = nanoseconds_now();
                bin_tree_find(left_tree, i);
                end = nanoseconds_now();
                left_tree_find += (end - beg) / 100.;
            }
        for (int i = 0; i < 100; i++)
        {
            beg = nanoseconds_now();
            bin_tree_apply_in_order(left_tree, NULL, NULL);
            end = nanoseconds_now();
            left_tree_sort += end - beg;
        }

        bin_tree_destroy(left_tree);


        tree_node_t *right_tree = NULL;
        double right_tree_find = 0;
        double right_tree_sort = 0;
        int k = depth * 2 - 1;

        bin_tree_insert(&right_tree, 0);
        for (int i = 1; i < depth; i++)
        {
            bin_tree_insert(&right_tree, i);
            bin_tree_insert(&right_tree, -i);
        }

        int right_tree_depth = maxDepth(right_tree);

        for (int _ = 0; _ < 100; _++)
            for (int i = -depth + 1; i < depth; i++)
            {
                beg = nanoseconds_now();
                bin_tree_find(right_tree, i);
                end = nanoseconds_now();
                right_tree_find += (end - beg) / 100.;
            }
        for (int i = 0; i < 100; i++)
        {
            beg = nanoseconds_now();
            bin_tree_apply_in_order(right_tree, NULL, NULL);
            end = nanoseconds_now();
            right_tree_sort += end - beg;
        }

        bin_tree_destroy(right_tree);


        unsigned long long n = pow(2, depth) - 1;
        int *items = malloc(sizeof(int) * n);
        for (int i = 0; i < pow(2, depth); i++)
        {
            items[i] = i;
        }

        tree_node_t *balanced_tree = sortedArrayToBST(items, n);
        free(items);

        int balanced_tree_depth = maxDepth(balanced_tree);
        double balanced_tree_find = 0;
        double balanced_tree_sort = 0;

        for (unsigned long long i = 0; i < n; i++)
        {
            beg = nanoseconds_now();
            bin_tree_find(balanced_tree, i);
            end = nanoseconds_now();
            balanced_tree_find += end - beg;
        }
        for (int i = 0; i < 100; i++)
        {
            beg = nanoseconds_now();
            bin_tree_apply_in_order(balanced_tree, NULL, NULL);
            end = nanoseconds_now();
            balanced_tree_sort += end - beg;
        }

        bin_tree_destroy(balanced_tree);

        printf(
            " %7d %10d %14lf %15lf | %7d %10d %14lf %15lf | %7d %10lld %14lf %15lf\n",
            left_tree_depth, depth, left_tree_find / depth, left_tree_sort / 100,
            right_tree_depth, k, right_tree_find / k, right_tree_sort / 100,
            balanced_tree_depth, n, balanced_tree_find / n, balanced_tree_sort / 100
        );
    }
}
