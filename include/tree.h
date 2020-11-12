/*
    Copyright (c) 2020 Ivan Kniazkov <ivan.kniazkov.com>

    The declaration of structures that describes a tree
*/

#pragma once

#include <stdlib.h>

typedef struct tree_node_t tree_node_t;

typedef struct
{
    size_t (* get_number_of_children)(const tree_node_t *iface);
    tree_node_t * (* get_child)(const tree_node_t *iface, size_t index);
} tree_node_vtbl_t;

struct tree_node_t
{
    const tree_node_vtbl_t *vtbl;
};

static __inline size_t get_number_of_children_of_tree_node(const tree_node_t *iface)
{
    return iface->vtbl->get_number_of_children(iface);
}

static __inline tree_node_t * get_child_of_tree_node(const tree_node_t *iface, size_t index)
{
    return iface->vtbl->get_child(iface, index);
}
