#ifndef OPTIMIZEDHUFFMANCODING_HUFFMAN_H
#define OPTIMIZEDHUFFMANCODING_HUFFMAN_H

#include <stdint.h>
#include "node.h"

Node* build_huffman_tree(MinHeap* heap, uint8_t num_child);
void print_huffman_tree_nary(Node* root, const char* prefix, int is_last, FILE* out);

#endif //OPTIMIZEDHUFFMANCODING_HUFFMAN_H
