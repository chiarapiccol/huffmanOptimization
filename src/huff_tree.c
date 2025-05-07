#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "../include/node.h"
#include "../include/heap.h"

#define INTERNAL_NODE_SYMBOL 129  // Used for internal non-leaf nodes, as it is not used character

Node* build_huffman_tree(MinHeap* heap, uint8_t num_child) {
    if (num_child > 16 || num_child % 2 != 0) {
        perror("This number of children is not allowed");
        exit(EXIT_FAILURE);
    }
    while (heap->size > 1) {
        uint8_t actual = (heap->size < num_child) ? heap->size : num_child;
        Node* parent = create_node(INTERNAL_NODE_SYMBOL, 0, actual);
        uint32_t total_freq = 0;

        for (uint8_t i = 0; i < actual; i++) {
            Node* child = get_min(heap);
            total_freq += child->freq;
            parent->children[i] = child;
            remove_current_root_and_heapify(heap);
        }

        parent->freq = total_freq;
        insert_node_in_minheap(heap, parent);
    }

    Node* root = get_min(heap);
    remove_current_root_and_heapify(heap);
    return root;
}

void print_huffman_tree_nary(Node* node, const char* prefix, int is_last, FILE* out) {
    if (!node) return;
    // Print the branch line
    fprintf(out, "%s", prefix);
    fprintf(out, is_last ? "└── " : "├── ");
    // Print node content
    if (node->symbol != INTERNAL_NODE_SYMBOL && isprint(node->symbol)) {
        fprintf(out, "'%c' (%u)\n", node->symbol, node->freq);
    } else if (node->symbol != INTERNAL_NODE_SYMBOL) {
        fprintf(out, "0x%02X (%u)\n", node->symbol, node->freq);
    } else {
        fprintf(out, "* (%u)\n", node->freq);  // Internal node
    }
    // Prepare the new prefix
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_last ? "    " : "│   ");
    // Print all children recursively
    for (uint8_t i = 0; i < node->num_children; i++) {
        int is_last_child = (i == node->num_children - 1);
        print_huffman_tree_nary(node->children[i], new_prefix, is_last_child, out);
    }
}


