#include <stdint.h>
#include <malloc.h>
#include "../include/node.h"

// ToDo:
// 1. do not forget to free heap.
// 2. verify if enough space for

Node* create_node(uint8_t ch, uint16_t freq, uint8_t num_ch){
    Node* newNode = calloc(1,sizeof(Node));
    newNode -> symbol = ch;
    newNode -> freq = freq;
    newNode -> num_children = num_ch;
    newNode -> children = (Node**) calloc(num_ch, sizeof(Node*));
    return newNode;
}

void print_node(Node* node) {
    printf("Node: symbol %c (%d) with frequency: %u \n", node -> symbol, node -> symbol, node-> freq);
}

void free_node(Node* node) {
    free(node->children);
    free(node);
}