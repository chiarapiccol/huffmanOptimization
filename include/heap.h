#ifndef OPTIMIZEDHUFFMANCODING_HEAP_H
#define OPTIMIZEDHUFFMANCODING_HEAP_H

#include <stdint.h>
#include <stdio.h>

#include "node.h"


// A Min Heap Binary Tree is a (possibly except for the last node) binary tree where the root element is the minimum.
// It is represented as an Array, which makes it easy to implement as foreach node "i" holds that:
// the parent is in arr[(i-1)/2] and the children respectively in arr[(2*i) + 1] and arr[(2*i) + 2]

typedef struct MinHeap {
    Node** data; // array of pointers to the nodes (Node*) i.e. first pointer to a pointer to nodes
    uint16_t size; // Current Size of the Heap
    uint16_t capacity; // Maximum capacity of the heap = number of symbols (MAX_NU_SYMB)
} MinHeap;

MinHeap* create_heap(uint16_t capacity);
Node* get_min(MinHeap* heap);
uint16_t get_right_child_position(uint16_t i);
uint16_t get_left_child_position(uint16_t i);
uint16_t get_parent_position(uint16_t i);
void insert_node_in_minheap(MinHeap* heap, Node* node);
void insert_node_in_the_last_pos(MinHeap* heap, Node* node);
MinHeap* heapify(MinHeap* heap, uint16_t index);
void remove_current_root_and_heapify(MinHeap* heap);
void print_minheap_tree(MinHeap* heap, int index, int depth, const char* prefix, int is_left, FILE* out);
void free_minheap(MinHeap* heap);

#endif //OPTIMIZEDHUFFMANCODING_HEAP_H
