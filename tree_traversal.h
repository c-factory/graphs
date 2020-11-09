/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of tree traversal methods
*/

#pragma  once

#include "tree.h"

typedef struct
{
    tree_node_t **list;
    size_t count;
} tree_traversal_result_t;

void destroy_tree_traversal_result(tree_traversal_result_t *result);
tree_traversal_result_t * topological_sort(tree_node_t * root);