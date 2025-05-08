#ifndef OPTIMIZEDHUFFMANCODING_HUFFMAN_H
#define OPTIMIZEDHUFFMANCODING_HUFFMAN_H

#include <stdint.h>
#include "heap.h"

Node* build_huffman_tree(MinHeap* heap, uint8_t num_child);
Node* build_opt_huffman_tree(MinHeap* heap, uint8_t num_child, uint16_t num_symbols);
void print_huffman_tree_nary(Node* root, const char* prefix, int is_last, FILE* out);

#endif //OPTIMIZEDHUFFMANCODING_HUFFMAN_H
