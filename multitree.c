//
// Created by Freedom Coder on 19.10.2021.
//
#include <stdlib.h>
#include "multitree.h"


struct MTNode *MT_vertex(struct MTNode **tree, TNode from, TNode to) {
    if (!*tree) return MT_add_child((*tree = MT_create_node(from)), to);
    return MT_add_child(MT_find(*tree, from), to);
}

struct MTNode *MT_find(struct MTNode *branch, TNode elem) {
    if (!branch) return NULL;
    if (elem == branch->data) return branch;
    struct MTNode *curr;
    if ((curr = MT_find(branch->left, elem))) return curr;
    return MT_find(branch->right, elem);
}

struct MTNode *MT_create_node(TNode element) {
    struct MTNode *currNode = malloc(sizeof(struct MTNode));
    currNode->data = element;
    currNode->left = NULL;
    currNode->right = NULL;
    currNode->parent = NULL;
    return currNode;
}

struct MTNode *MT_add_child(struct MTNode *tree, TNode element) {
    struct MTNode *parent = tree;
    tree = tree->left;

    struct MTNode *currNode = MT_create_node(element);

    currNode->parent = parent;

    if (!tree) parent->left = currNode;
    else {
        currNode->right = tree->right;
        tree->right = currNode;
    }
    return currNode;
}

int MT_count_child(struct MTNode *tree) {
    if (!tree) return 0;
    int cnt = 0;
    struct MTNode *currNode = tree->left;
    while (currNode) {
        currNode = currNode->right;
        cnt++;
    }
    return cnt;
}

struct MTNode *MT_get_child(struct MTNode *tree) {
    return tree->left;
}

struct MTNode *MT_get_parent(struct MTNode *tree) {
    return tree->parent;
}

struct MTNode *MT_get_next_sibling(struct MTNode *tree) {
    return tree->right;
}

void MT_consume_internal(struct MTNode *tree, void (*consumer)(struct MTNode* element, int depth), int bt_strategy, int depth) {
    if (!tree) return;
    switch (bt_strategy) {
        case MT_STRATEGY_BRANCHES:
            if (tree->left) consumer(tree, depth);
            break;
        case MT_STRATEGY_LEAFS:
            if (!tree->left) consumer(tree, depth);
            break;
        case MT_STRATEGY_ALL:
            consumer(tree, depth);
            break;
    }
    MT_consume_internal(tree->left, consumer, bt_strategy, depth + 1);
    MT_consume_internal(tree->right, consumer, bt_strategy, depth);
}

void MT_consume(struct MTNode *tree, void (*consumer)(struct MTNode* element, int depth), int bt_strategy) {
    return MT_consume_internal(tree, consumer, bt_strategy, 0);
}

void MT_consume_layer(struct MTNode *tree, void (*consumer)(struct MTNode* element), int layer_depth) {
    if (!tree) return;
    if (layer_depth)
        while (tree) {
            MT_consume_layer(tree->left, consumer, layer_depth - 1);
            tree = tree->right;
        }
    else
        while (tree) {
            consumer(tree);
            tree = tree->right;
        }
}

void MT_destruct_internal(struct MTNode *branch) {
    if (!branch) return;
    MT_destruct_internal(branch->left);
    MT_destruct_internal(branch->right);
    free(branch);
}

void MT_destruct(struct MTNode **tree) {
    MT_destruct_internal(*tree);
    *tree = NULL;
}