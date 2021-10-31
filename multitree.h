//
// Created by Freedom Coder on 19.10.2021.
//

#ifndef LAB7_MTREE_H
#define LAB7_MTREE_H

typedef int TNode;

struct MTNode
{
    TNode data;
    struct MTNode* parent;
    struct MTNode* left; //child
    struct MTNode* right; //sibling
};

#define MT_STRATEGY_LEAFS 0
#define MT_STRATEGY_BRANCHES 1
#define MT_STRATEGY_ALL 2

struct MTNode* MT_vertex(struct MTNode **tree, TNode from, TNode to);
struct MTNode* MT_find(struct MTNode *branch, TNode element);
struct MTNode* MT_create_node(TNode element);
struct MTNode* MT_add_child(struct MTNode* tree, TNode element);
int MT_count_child(struct MTNode* tree);
struct MTNode* MT_get_child(struct MTNode* tree);
struct MTNode* MT_get_parent(struct MTNode* tree);
struct MTNode* MT_get_next_sibling(struct MTNode* tree);
void MT_consume(struct MTNode* tree, void (*consumer)(struct MTNode* element, int depth), int bt_strategy);
void MT_consume_layer(struct MTNode* tree, void (*consumer)(struct MTNode* element), int layer_depth);
void MT_destruct(struct MTNode** tree);

#endif //LAB7_MTREE_H
