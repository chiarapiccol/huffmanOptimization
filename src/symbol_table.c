#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "../include/symbol_table.h"

void count_frequencies(const char* file_name, uint16_t* freq_table) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        perror("There is no such file\n");
        exit(EXIT_FAILURE);
    }
    int ch;
    while ((ch =getc(file)) != EOF) {
        freq_table[ch]++;
    }
    fclose(file);
}

char* return_binary(uint8_t value) {
    static char bin[9];
    for (int i = 7; i >= 0; i--) {
        bin[7 - i] = (value & (1 << i)) ? '1' : '0';
    }
    bin[8] = '\0';
    return bin;
}

void print_freq_table(const uint16_t* freq_table, uint16_t size) {
    printf("\n### TABLE ###\n");
    for (uint16_t i = 0; i < size; i++) {
        if (* (freq_table + i)) {
            if (i >= 32 && i <= 126) // sichtbare ASCII-Zeichen
                printf("symbol: %c (%d - %s): frequency: %d\n", i, i, return_binary(i), freq_table[i]);
            else
                printf("symbol: (non-printable %d - %s): frequency: %d\n", i, return_binary(i), freq_table[i]);

        }
    }
}

void save_freq_table(const char* file_name, uint16_t* freq_table, uint16_t size) {
    FILE* file = fopen(file_name, "w");
    if (!file) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    for (uint16_t i = 0; i <= size; i++) {
        if (* (freq_table + i)) {
            fprintf(file, "%c %hu %hu \n", i, i, * (freq_table + i));
        }
    }
    fclose(file);
}

void load_freq_table(const char* file_name, uint16_t* freq_table, uint16_t size) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    char symbol;
    uint16_t index;
    uint16_t freq;
    while (fscanf(file, "%c %hu %hu \n", &symbol, &index, &freq) == 3) {
        if (index <= size) {
            freq_table[index] = freq;
        }
    }
    fclose(file);
}

