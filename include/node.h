#ifndef OPTIMIZEDHUFFMANCODING_NODE_H
#define OPTIMIZEDHUFFMANCODING_NODE_H

#include <stdint.h>

typedef struct Node {
    uint8_t symbol;
    uint16_t freq;
    uint8_t num_children; // Number of children (2, 4, 8, 16)
    struct Node** children; // Array of pointers to the children (Node*)
} Node;
Node* create_node(uint8_t ch, uint16_t freq, uint8_t num_ch);
void print_node(Node* node);
void free_node(Node* node);
#endif //OPTIMIZEDHUFFMANCODING_NODE_H
