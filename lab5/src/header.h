#pragma once

#define BUFFER_SIZE 4096

struct Node {
	struct Node* link[2];
	unsigned int freq;
	int sym;
};

struct BitOut{
	unsigned char* buffer;
	unsigned int octpos;
	unsigned int bitpos;
};

struct BitInput {
	unsigned char* buffer;
	unsigned int content_size;
	unsigned int octpos;
	unsigned int bitpos;
};

void encode(FILE* input, FILE* output);

void createTable(unsigned char path[256], unsigned int level, unsigned char* code[256], struct Node* root);
void save(struct Node* root, struct BitOut* bo);
void writeEncode(FILE* output, FILE* input, struct BitOut* bo, unsigned char* table[256]);

struct Node* buildTree(unsigned int* letters, FILE* input, FILE* output);
struct Node* createNode(struct Node* left, struct Node* right, unsigned int freq, int sym, FILE* input, FILE* output);

void decode(FILE* input, FILE* output);

struct Node* readTree(struct BitInput* bi, FILE* input, FILE* output);

struct Node* read(struct BitInput* bi, FILE* input, FILE* output);
void write(struct BitInput* bi, struct Node* root, FILE* output, FILE* input);

void deleteTree(struct Node* root);
