#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/table.h"
#include "../include/node.h"
#include "../include/heap.h"
#include "../include/huffman.h"

// is the size of the tables as small as possible? is there a way to make it best fitting?
// can a coded variable be built just out of nulls, ending to be equal to the default variable?
//

#define MAX_NU_SYMB 256 // From ASCII-Tabelle
#define NUM_CHILDREN 4 // Number of children in the k-ary Huffman tree (2, 4, 8, 16)
#define CALC_INSTEAD_OF_LOAD_TAB 1 // Whatever the symbol table shall be calculated or loaded
#define PRINT_INSTEAD_OF_SAVE_STR 1
#define CREATE_STD_INSTEAD_OF_OPT_TREE 0

int main(){
    // ### 1. Create freq_table
    char inputfile_name[] = "tests/input.txt";
    char freqfile_name[] = "tests/freq_table.txt";
    uint16_t freq_table[MAX_NU_SYMB] = {0};
    if (CALC_INSTEAD_OF_LOAD_TAB) {
        // ...either generate and save the frequency table
        count_frequencies(inputfile_name, freq_table);
        print_freq_table(freq_table, MAX_NU_SYMB);
        save_table(freqfile_name, freq_table, MAX_NU_SYMB);
    } else {
        // ...or load the frequency table from file
        load_table(freqfile_name, freq_table, MAX_NU_SYMB);
        print_freq_table(freq_table, MAX_NU_SYMB);
    }

    // ### 2. Create the min Heap
    MinHeap* minheap = create_heap(MAX_NU_SYMB);
    // For each relevant (freq!=0) symbol of the symbol table
    for (uint16_t i = 0; i < MAX_NU_SYMB; i++) {
        if (*(freq_table + i)) {
            // Create and insert the corresponding node in the heap
            Node* node = create_node(i, *(freq_table + i), NUM_CHILDREN);
            insert_node_in_minheap(minheap, node);
        }
    }
    // Print the Min Heap
    if (PRINT_INSTEAD_OF_SAVE_STR) {
        //...either print the heap
        printf("\n### MIN HEAP ###\n");
        print_minheap_tree(minheap, 0, 0, "", 0, stdout);
    } else {
        //...or visualize and save it in the following file
        FILE* filename_heap = fopen("tests/min_heap.txt", "w");
        print_minheap_tree(minheap, 0, 0, "", 0, filename_heap);
        fclose(filename_heap);
    }

    // ### 3. Create the Tree
    Node* root;
    if (CREATE_STD_INSTEAD_OF_OPT_TREE) {
        // # 3.1 Create the standard Huffman tree
        root = build_huffman_tree(minheap, NUM_CHILDREN);
        // Print the tree
        if (PRINT_INSTEAD_OF_SAVE_STR) {
            //...either print the tree
            printf("\n### STANDARD HUFFMAN TREE ###\n");
            print_huffman_tree_nary(root, "", 1, stdout);
        } else {
            //...or visualize and save it in the following file
            FILE* file_name_tree = fopen("tests/huffman_tree.txt", "w");
            print_huffman_tree_nary(root, "#", 1, file_name_tree);
            fclose(file_name_tree);
        }
    } else {
        // # 3.2 Create the optimized Huffman tree
        root = build_opt_huffman_tree(minheap, NUM_CHILDREN, minheap ->size);
        // Print the tree
        if (PRINT_INSTEAD_OF_SAVE_STR) {
            //...either print the tree
            printf("\n### OPTIMIZED HUFFMAN TREE ###\n");
            print_huffman_tree_nary(root, "", 1, stdout);
        } else {
            //...or visualize and save it in the following file
            FILE* file_name_tree = fopen("tests/huffman_tree.txt", "w");
            print_huffman_tree_nary(root, "#", 1, file_name_tree);
            fclose(file_name_tree);
        }
    }

    // Free the allocated space for min heap
    free_minheap(minheap);

    // ### 4. Encode
    // Create and fill the ecoding table
    char* encoding_table[MAX_NU_SYMB] = {0};
    char code_buffer[MAX_NU_SYMB] = {0};
    encode(root, code_buffer, 0, encoding_table);
    print_encod_table(encoding_table, MAX_NU_SYMB);

    free_tree(root);


    // ### 5. Decode
    exit(EXIT_SUCCESS);
}