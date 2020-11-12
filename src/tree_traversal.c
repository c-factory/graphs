/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The implementation of tree traversal methods
*/

#include "tree_traversal.h"
#include "vector.h"
#include "tree_map.h"
#include "allocator.h"

void destroy_tree_traversal_result(tree_traversal_result_t *result)
{
    free(result->list);
    free(result);
}

typedef struct
{
    vector_t *list;
    tree_map_t *visited_nodes;
} topological_sort_data_t;

typedef enum
{
    node_color_grey,
    node_color_black
} node_color_t;

static bool topological_sort_iteration(tree_node_t *node, topological_sort_data_t *data)
{
    const pair_t *pair = get_pair_from_tree_map(data->visited_nodes, node);
    if (pair)
    {
        node_color_t color = *((node_color_t*)pair->value);
        return color == node_color_black;
    }

    node_color_t *color = nnalloc(sizeof(node_color_t));
    *color = node_color_grey;
    add_pair_to_tree_map(data->visited_nodes, node, color);
    size_t children_count =  get_number_of_children_of_tree_node(node);
    for (size_t i = 0; i < children_count; i++)
    {
        tree_node_t *child = get_child_of_tree_node(node, i);
        if (!topological_sort_iteration(child, data))
            return false;
    }
    *color = node_color_black;
    add_item_to_vector(data->list, node);
    return true;
}

tree_traversal_result_t * topological_sort(tree_node_t *root)
{
    if (!root)
        return NULL;
    tree_traversal_result_t * result = NULL;
    topological_sort_data_t data;
    data.list = create_vector();
    data.visited_nodes = create_tree_map(NULL);
    bool success = topological_sort_iteration(root, &data);
    if (success)
    {
        size_t count = data.list->size;
        result = nnalloc(sizeof(tree_traversal_result_t));
        result->list = nnalloc(sizeof(tree_node_t*) * count);
        result->count = count;
        for (size_t i = 0; i < count; i++)
        {
            result->list[i] = (tree_node_t*)data.list->data[count - i - 1];
        }
    }
    destroy_vector(data.list);
    destroy_tree_map_and_content(data.visited_nodes, NULL, free);
    return result;
}
