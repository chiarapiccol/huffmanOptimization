cmake_minimum_required(VERSION 3.30)
project(optimizedHuffmanCoding C)

set(CMAKE_C_STANDARD 11)

add_executable(optimizedHuffmanCoding
        include/huffman.h
        include/heap.h
        include/node.h
        src/encode.c
        src/decode.c
        src/heap.c
        src/node.c
        src/main.c
        tests/tests.c)
