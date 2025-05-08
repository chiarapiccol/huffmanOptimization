#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "../include/huffman.h"

Node* build_huffman_tree(MinHeap* heap, uint8_t num_childs) {
    if (num_childs > 16 || num_childs % 2 != 0) {
        perror("This number of children is not allowed");
        exit(EXIT_FAILURE);
    }
    while (heap->size > 1) {
        uint8_t actual = (heap->size < num_childs) ? heap->size : num_childs;
        Node* parent = create_node(UNUSED_SYMB, 0, actual);
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

Node* build_opt_huffman_tree(MinHeap* heap, uint8_t num_childs, uint16_t num_symbols) {
    if (num_childs > 16 || num_childs % 2 != 0) {
        perror("This number of children is not allowed");
        exit(EXIT_FAILURE);
    }
    // Find best nummber to add
    uint8_t block = ((num_symbols - 1) % (num_childs - 1) > 0) ? ((num_symbols - 1) / (num_childs - 1)) + 1 : (num_symbols - 1) / (num_childs - 1);
    uint16_t full_blocks = block*(num_childs -1) + 1;
    uint8_t to_add = ((num_symbols - full_blocks) > 0 ? (num_symbols - full_blocks) : (num_symbols - full_blocks)*(-1));
    printf("%d, %d", (int16_t)num_childs,  (int16_t)full_blocks);
    printf("The following number of elements are to add: %d", to_add);
    // add extras into heap
    for (uint16_t i = 0; i < to_add; i++) {
        // Create and insert the corresponding node in the heap
        Node* node = create_node(UNUSED_SYMB, 1, num_childs);
        insert_node_in_the_last_pos(heap, node);
    }
    // build
    build_huffman_tree(heap, num_childs);

}

void print_huffman_tree_nary(Node* node, const char* prefix, int is_last, FILE* out) {
    if (!node) return;
    // Print the branch line
    fprintf(out, "%s", prefix);
    fprintf(out, is_last ? "└── " : "├── ");
    // Print node content
    if (node->symbol != UNUSED_SYMB && isprint(node->symbol)) {
        fprintf(out, "'%c' (%u)\n", node->symbol, node->freq);
    } else if (node->symbol != UNUSED_SYMB) {
        fprintf(out, "0x%02X (%u)\n", node->symbol, node->freq);
    } else if (node->symbol == UNUSED_SYMB && node-> freq == 1){
        fprintf(out, "EXTRA (%u)\n", node->freq);
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


void free_tree(Node* node) {
    if (!node) return;

    // Recursively free children
    for (uint8_t i = 0; i < node->num_children; i++) {
        if (node->children[i]) {
            free_tree(node->children[i]);
        }
    }
    // Free the children array itself
    free(node->children);
    // Free the node
    free(node);
}




