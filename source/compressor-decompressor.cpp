#include "compressor-decompressor.h"

// HuffmanNode constructor
HuffmanNode::HuffmanNode(char character, int frequency, HuffmanNode* left, HuffmanNode* right) {
    this->character = character;
    this->frequency = frequency;
    this->left = left;
    this->right = right;
}

// HuffmanNode destructor
HuffmanNode::~HuffmanNode() {
    delete left;
    delete right;
}

// Compare structure for priority queue
bool Compare::operator()(HuffmanNode* l, HuffmanNode* r) {
    return l->frequency > r->frequency;
}

// Function to print Huffman codes
void printHuffmanCodes(HuffmanNode* root, string str, map<char, string>& huffmanCode) {
    if (!root)
        return;

    if (root->character != '$')
        huffmanCode[root->character] = str;

    printHuffmanCodes(root->left, str + "0", huffmanCode);
    printHuffmanCodes(root->right, str + "1", huffmanCode);
}

// Function to build Huffman Tree
HuffmanNode* buildHuffmanTree(map<char, int>& frequencyMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto pair : frequencyMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() != 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        int sum = left->frequency + right->frequency;
        pq.push(new HuffmanNode('$', sum, left, right));
    }

    return pq.top();
}

// Function to compress a file
void compressFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << outputFilename << endl;
        return;
    }

    map<char, int> frequencyMap;
    char ch;
    while (inputFile.get(ch)) {
        frequencyMap[ch]++;
    }

    if (frequencyMap.empty()) {
        cerr << "The input file is empty!" << endl;
        return;
    }

    inputFile.clear();
    inputFile.seekg(0, ios::beg);

    HuffmanNode* root = buildHuffmanTree(frequencyMap);

    map<char, string> huffmanCode;
    printHuffmanCodes(root, "", huffmanCode);

    outputFile << frequencyMap.size() << "\n";
    for (auto pair : frequencyMap) {
        outputFile << pair.first << " " << pair.second << "\n";
    }

    string encodedString;
    while (inputFile.get(ch)) {
        encodedString += huffmanCode[ch];
    }

    int padding = 8 - (encodedString.size() % 8);
    if (padding == 8) padding = 0;
    for (int i = 0; i < padding; ++i) {
        encodedString += "0";
    }
    outputFile << padding << "\n";

    for (size_t i = 0; i < encodedString.size(); i += 8) {
        bitset<8> bits(encodedString.substr(i, 8));
        outputFile.put(static_cast<unsigned char>(bits.to_ulong()));
    }

    inputFile.close();
    outputFile.close();
    delete root;
}

// Function to decompress a file
void decompressFile(const string& inputFilename, const string& outputFilename) {
    ifstream inputFile(inputFilename, ios::binary);
    if (!inputFile.is_open()) {
        cerr << "Error opening input file: " << inputFilename << endl;
        return;
    }

    ofstream outputFile(outputFilename, ios::binary);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << outputFilename << endl;
        return;
    }

    int size;
    inputFile >> size;

    map<char, int> frequencyMap;
    char ch;
    int frequency;
    inputFile.ignore();
    for (int i = 0; i < size; ++i) {
        inputFile.get(ch);
        inputFile >> frequency;
        frequencyMap[ch] = frequency;
        inputFile.ignore();
    }

    HuffmanNode* root = buildHuffmanTree(frequencyMap);

    int padding;
    inputFile >> padding;
    inputFile.ignore();

    string encodedString;
    char byte;
    while (inputFile.get(byte)) {
        bitset<8> bits(byte);
        encodedString += bits.to_string();
    }
    encodedString = encodedString.substr(0, encodedString.size() - padding);

    HuffmanNode* current = root;
    for (char bit : encodedString) {
        current = (bit == '0') ? current->left : current->right;

        if (!current->left && !current->right) {
            outputFile.put(current->character);
            current = root;
        }
    }

    inputFile.close();
    outputFile.close();
    delete root;
}

// Main function
int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <compress|decompress> <input file> <output file>" << endl;
        return 1;
    }

    string command = argv[1];
    string inputFilename = argv[2];
    string outputFilename = argv[3];

    if (command == "compress") {
        compressFile(inputFilename, outputFilename);
    } else if (command == "decompress") {
        decompressFile(inputFilename, outputFilename);
    } else {
        cerr << "Invalid command: " << command << endl;
        return 1;
    }

    cout << "Operation completed successfully." << endl;
    return 0;
}
