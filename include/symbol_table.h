#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdint.h>

void count_frequencies(const char* filename, uint16_t* freq_table);
void print_freq_table(const uint16_t* freq_table, uint16_t size);
void save_freq_table(const char* freq_filename, uint16_t*freq_table, uint16_t size);
void load_freq_table(const char*  freq_filename, uint16_t* freq_table, uint16_t size);

#endif //SYMBOL_TABLE_H
