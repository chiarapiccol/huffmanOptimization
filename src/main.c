#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/symbol_table.h"
#include "../include/node.h"
#include "../include/heap.h"
#include "../include/huffman.h"

// is the size of the tables as small as possible? is there a way to make it best fitting?
// can a coded variable be built just out of nulls, ending to be equal to the default variable?
//

#define MAX_NU_SYMB 256 // From ASCII-Tabelle
#define NUM_CHILDREN 2 // Number of children in the k-ary Huffman tree (2, 4, 8, 16)
#define LOAD_INSTEAD_OF_CALC_TAB 0 // Whatever the symbol table shall be calculated or loaded
#define PRINT_INSTEAD_OF_SAVE_TREE 1

int main(){
    // ### 1. Create freq_table
    char file_name[] = "tests/input.txt";
    char freq_file[] = "tests/freq_table.txt";
    uint16_t freq_table[MAX_NU_SYMB] = {0};
    if (LOAD_INSTEAD_OF_CALC_TAB) {
        // ...either generate and save the frequency table
        count_frequencies(file_name, freq_table);
        print_freq_table(freq_table, MAX_NU_SYMB);
        save_freq_table(freq_file, freq_table, MAX_NU_SYMB);
    } else {
        // ...or load the frequency table from file
        load_freq_table(freq_file, freq_table, MAX_NU_SYMB);
        print_freq_table(freq_table, MAX_NU_SYMB);

    }

    // ### 2. Create the k-ary Huffman tree
    // ## 2.1 Create the heap
    MinHeap* minheap = create_heap(MAX_NU_SYMB);
    // For each relevant (freq!=0) symbol of the symbol table
    for (uint16_t i = 0; i < MAX_NU_SYMB; i++) {
        if (*(freq_table + i)) {
            // Create and insert the corresponding node in the heap
            Node* node = create_node(i, *(freq_table + i), NUM_CHILDREN);
            insert_node_in_minheap(minheap, node);
        }
    }
    print_heap(minheap);

    // ## 2.2 Create the tree
    Node* root = build_huffman_tree(minheap, NUM_CHILDREN);
    if (PRINT_INSTEAD_OF_SAVE_TREE) {
        //...either print the tree
        print_huffman_tree_nary(root, "", 1, stdout);
    } else {
        //...or visualize and save it in the following file
        FILE* file_name = fopen("tests/huffman_tree.txt", "w");
        print_huffman_tree_nary(root, "", 1, file_name);
        fclose(file_name);
    }
    // Free the allocated space for min heap
    free_minheap(minheap);

    // ### 3. Optimize tree
    //optimize_tree();

    // ### 4. Encode
    uint16_t coding_table[MAX_NU_SYMB] = {0};
    //decode_symbols();

    // ### 5. Decode
    exit(EXIT_SUCCESS);
}