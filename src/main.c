#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/huffman.h"
#include "../include/node.h"

// is the size of the tables as small as possible? is there a way to make it best fitting?
// can a coded variable be built just out of nulls, ending to be equal to the default variable?

#define MAX_NU_SYMB 256
#define NUM_CHILDREN 2

int main(){
    // 1. Create freq_table
    // Import file
    char file_name[] = "tests/input.txt";
    // Create frequency table
    uint16_t freq_table[MAX_NU_SYMB] = {0};
    count_frequencies(file_name, freq_table);
    print_freq_table(freq_table);

    // 2. Create tree
    // Create nodes
    for (int i = 0; i < MAX_NU_SYMB; i++) {
        create_node(i, *(freq_table + i), NUM_CHILDREN);
    }

    // Save nodes as min heap
    // create tree

    // 3. Optimize tree
    //optimize_tree();

    // 4. Encode
    uint16_t coding_table[MAX_NU_SYMB] = {0};
    //decode_symbols();

    // 5. Decode
    exit(EXIT_SUCCESS);
}