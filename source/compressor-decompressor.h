#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <bitset>
#include <string>

using namespace std;

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char character, int frequency, HuffmanNode* left = nullptr, HuffmanNode* right = nullptr);
    ~HuffmanNode();
};

struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r);
};

void printHuffmanCodes(HuffmanNode* root, string str, map<char, string>& huffmanCode);
HuffmanNode* buildHuffmanTree(map<char, int>& frequencyMap);
void compressFile(const string& inputFilename, const string& outputFilename);
void decompressFile(const string& inputFilename, const string& outputFilename);

#endif 
