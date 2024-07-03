# Text Compressor using Huffman coding in C++

## Overview
Huffman Compression is a lossless data compression algorithm. It assigns variable-length codes to input characters, with shorter codes assigned to more frequent characters. This project implements the Huffman Compression algorithm in C++.

## Features
- *Encoding*: Compress text files using Huffman coding.
- *Decoding*: Decompress Huffman coded files back to their original text.
- *Frequency Table*: Display frequency of each character in the input file.

## Table of Contents
- [Installation](#installation)
- [Usage](#usage)

## Installation
1. Clone the repository:
    ````bash
    git clone https://github.com/sonali9569/TextCompressor.git
    cd TextCompressor
    
2. Ensure you have a C++ compiler installed (e.g., g++).

## Usage
### Compiling
To compile the code:
```bash
g++ -o HuffmanCode compressor-decompressor.cpp
````

### Encoding
To compress a file:
````bash
./HuffmanCode compressFile inputfile.txt compressed.bin
````

### Decoding
To decompress a file:
````bash
./HuffmanCode decompressFile compressed.bin outputfile.txt
