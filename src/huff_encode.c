#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../include/huffman.h"

void encode(Node* node, char* code, int pos, char** table) {
    if (!node) return;

    // Leaf: store code
    if (node->children[0] == NULL && node -> symbol != UNUSED_SYMB) {
        code[pos] = '\0';  // end string
        table[node->symbol] = strdup(code);  // save a copy
        return;
    }
    // Traverse children
    for (int i = 0; i < node->num_children; i++) {
        if (node->children[i] != NULL) {
            code[pos] = '0' + i;  // use ASCII digits
            encode(node->children[i], code, pos + 1, table);
        } else {return;}
    }
}






