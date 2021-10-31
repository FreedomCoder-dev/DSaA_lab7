#include <stdio.h>
#include "multitree.h"

struct MTNode *root;

void print_node2(struct MTNode *data, int depth) {
    printf("%d ", data->data);
}

void print_node(struct MTNode *data) {
    printf("%d ", data->data);
}

void print_node_altered(struct MTNode *data, int depth) {
    while (depth--)
        printf("--");
    printf("%d\n", data->data);
}

void print_node_pair(struct MTNode *data, int depth) {
    struct MTNode *node = MT_get_parent(data);
    printf("%d %d\n", node ? node->data : -1, data->data);
}

int main() {
    FILE *in = fopen("../in.txt", "r");
    int a, b;
    while ((fscanf(in, "%d %d", &a, &b)) != EOF)
        MT_edge(&root, a, b);
    fclose(in);
//    struct MTNode *curr = root = MT_create_node(1);
//    curr = MT_add_child(root, 2);
//    curr = MT_get_parent(curr);
//    MT_add_child(curr, 5);
//    curr = MT_add_child(root, 3);
//    MT_add_child(curr, 6);
//    MT_add_child(curr, 7);
//    MT_add_child(curr, 8);
//    MT_add_child(curr, 9);
//    MT_add_child(root, 4);
//    curr = MT_add_child(root, 10);
//    MT_add_child(curr, 11);

    printf("tree leafs: ");
//    MT_consume(root, print_node_pair, MT_STRATEGY_ALL);
    MT_consume(root, print_node2, MT_STRATEGY_LEAFS);
    printf("\ntree branches: ");
    MT_consume(root, print_node2, MT_STRATEGY_BRANCHES);
    for (int i = 0; i < 4; ++i) {
        printf("\ntree layer %d: ", i);
        MT_consume_layer(root, print_node, i);
    }
    printf("\ntree layout: \n");
    MT_consume(root, print_node_altered, MT_STRATEGY_ALL);
    printf("\n---END---");

    MT_destruct(&root);
    return 0;
}
