cmake_minimum_required(VERSION 3.30)
project(optimizedHuffmanCoding C)

set(CMAKE_C_STANDARD 11)

add_executable(optimizedHuffmanCoding
        include/huffman.h
        include/heap.h
        include/node.h
        src/huff_encode.c
        src/huff_decode.c
        src/heap.c
        src/node.c
        src/main.c
        tests/tests.c
        src/symbol_table.c
        include/symbol_table.h
        src/huff_table.c
        src/huff_tree.c)

target_link_libraries(optimizedHuffmanCoding m)