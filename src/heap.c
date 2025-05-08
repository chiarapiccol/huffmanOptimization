# include "../include/heap.h"
#include <stdint.h>
#include <malloc.h>
#include <math.h>
#include <ctype.h>

// Quelle: https://www.digitalocean.com/community/tutorials/min-heap-binary-tree

MinHeap* create_heap(uint16_t capacity) {
    MinHeap* heap = calloc (1, sizeof(MinHeap));
    heap -> size = 0;
    heap -> capacity = capacity;
    heap -> data = (Node**) calloc (capacity, sizeof(Node*));
    return heap;
}

Node* get_min(MinHeap* heap) {
    return *(heap ->data);
}

uint16_t get_right_child_position(uint16_t i) {
    return (2*i + 2);
}

uint16_t get_left_child_position(uint16_t i) {
    return (2*i + 1);
}

uint16_t get_parent_position(uint16_t i) {
    return (i - 1)/2;
}

void insert_node_in_minheap(MinHeap* heap, Node* node) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Cannot insert the node. Heap is already full!");
        return;
    }
    uint16_t curr_position = heap->size;
    heap -> size++;
    // ...add to the heap
    heap -> data[curr_position] = node;
    // ...order within the heap:
    // As long as it is not the root node and while the parent of the last element is greater than it
    while ((curr_position > 0 && (heap->data[get_parent_position(curr_position)])->freq > (heap->data[curr_position]) -> freq)) {
        // Swap
        Node* temp = heap->data[get_parent_position(curr_position)];
        heap->data[get_parent_position(curr_position)] = heap->data[curr_position];
        heap->data[curr_position] = temp;
        // Update the current index of element
        curr_position = get_parent_position(curr_position);
    }
}

void insert_node_in_the_last_pos(MinHeap* heap, Node* node) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Cannot insert the node. Heap is already full!");
        return;
    }
    uint16_t curr_position = heap->size;
    heap -> size++;
    heap -> data[curr_position] = node;
}

MinHeap* heapify(MinHeap* heap, uint16_t index) {
    if (heap -> size <= 1) {
        return heap;
    }
    uint16_t left_position = get_left_child_position(index);
    uint16_t right_position = get_right_child_position(index);
    uint16_t smallest_position = index;
    if (left_position < heap->size && (heap->data[left_position])-> freq < (heap -> data[smallest_position])-> freq) {
        smallest_position = left_position;
    }
    if (right_position < heap->size && (heap->data[right_position])-> freq < (heap -> data[smallest_position])-> freq) {
        smallest_position = right_position;
    }
    if (smallest_position != index){
        Node* temp = heap->data[index];
        heap->data[index] = heap->data[smallest_position];
        heap->data[smallest_position] = temp;
        heapify(heap, smallest_position);
    }
    return heap;
}

void remove_current_root_and_heapify(MinHeap* heap) {
    if (!heap || heap -> size == 0) {
        fprintf(stderr, "The heap is empty");
    }
    heap -> data[0] = heap -> data[(heap->size)-1];
    heap-> size--;
    heapify(heap, 0);
}

// Helper function to print a single node's symbol and frequency
void print_heap_node(Node* node, FILE* out) {
    if (!node) {
        fprintf(out, "[NULL]");
        return;
    }

    if (node->symbol != 255 && isprint(node->symbol)) {
        fprintf(out, "'%c' (%u)", node->symbol, node->freq);
    } else if (node->symbol != 255) {
        fprintf(out, "0x%02X (%u)", node->symbol, node->freq);
    } else {
        fprintf(out, "* (%u)", node->freq);  // Internal node
    }
}

// Recursive function to print the heap as a binary tree
void print_minheap_tree(MinHeap* heap, int index, int depth, const char* prefix, int is_left, FILE* out) {
    if (index >= heap->size || !heap->data[index]) return;

    // Print the branch
    for (int i = 0; i < depth; i++) {
        fprintf(out, "│   ");
    }
    fprintf(out, "%s── ", is_left ? "├" : "└");
    print_heap_node(heap->data[index], out);
    fprintf(out, "\n");

    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size || right < heap->size) {
        if (left < heap->size)
            print_minheap_tree(heap, left, depth + 1, prefix, 1, out);
        if (right < heap->size)
            print_minheap_tree(heap, right, depth + 1, prefix, 0, out);
    }
}

void free_minheap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->data);
    free(heap);
}

