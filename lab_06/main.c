#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_tree.h"
#include "commands.h"
#include "io.h"
#include "return_codes.h"

#define CHOICE_COMMANDS_MENU \
"Chose command:\n"\
"   [1] Print tree\n"\
"   [2] Tree: insert\n"\
"   [3] Tree: find\n"\
"   [4] Tree: remove\n"\
"   [5] Tree: count nodes in each level\n"\
"   [6] File: insert\n"\
"   [7] Insert both (tree & file)\n"\
"   [8] Tree: pre-order print\n"\
"   [9] Tree: in-order print\n"\
"   [10] Tree: post-order print\n"\
"   [11] Show stat (insert)\n"\
"   [12] Show stat\n"\
"\n"\
"   [0] Exit\n"

return_code start_polling(tree_node_t *tree);
return_code exec_command(tree_node_t *tree);

int main(void)
{
    FILE *stream = fopen(TREE_FILEPATH, "r");
    tree_node_t *tree = read_tree(stream);
    fclose(stream);
    return start_polling(tree);
}


return_code start_polling(tree_node_t *tree)
{
    return_code rc;

    do
    {
        rc = exec_command(tree);
    }
    while (rc == OK);

    return rc;
}

return_code exec_command(tree_node_t *tree)
{
    return_code rc;
    char *user_choice = NULL;

    printf(CHOICE_COMMANDS_MENU);
    do
    {
        rc = input_user_choice(&user_choice, "0", 12, "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12");
    }
    while ((rc == OK || should_retry(rc)) && user_choice == NULL);

    if (rc == OK)
    {
        switch (atoi(user_choice))
        {
        case 1:
            process_show_tree(tree);
            break;
        case 2:
            process_tree_insert(tree);
            break;
        case 3:
            process_tree_find(tree);
            break;
        case 4:
            process_tree_remove(&tree);
            break;
        case 5:
            process_count_nodes_in_each_level(tree);
            break;
        case 6:
            process_file_insert();
            break;
        case 7:
            process_insert_both(tree);
            break;
        case 8:
            process_tree_pre_order(tree);
            break;
        case 9:
            process_tree_in_order(tree);
            break;
        case 10:
            process_tree_post_order(tree);
            break;
        case 11:
            process_show_stat1();
            break;
        case 12:
            process_show_stat2();
            break;
        default:
            assert(0);
        }

        if (rc == DIALOG_EXIT)
            rc = OK;
    }

    return rc;
}
