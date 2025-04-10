#include <stdint.h>
#include <malloc.h>
#include <stdio.h>

// ToDo:
// 1. do not forget to free heap.
// 2. verify if enough space for

typedef struct Node {
    uint8_t symbol;
    uint16_t freq;
    uint8_t num_children; // Number of children (2, 4, 8, 16)
    struct Node** children; // Array of pointers to the children
} Node;

Node* create_node(uint8_t ch, uint32_t freq, uint8_t num_ch){
    Node* newNode = malloc(sizeof(Node));
    newNode -> symbol = ch;
    newNode -> freq = freq;
    newNode -> num_children = num_ch;
    newNode -> children = malloc(sizeof(Node) * num_ch);
    return newNode;
}

int main(){
    printf("Hallo");
    return 0;
}