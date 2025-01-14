#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

void encode(FILE* input, FILE* output) {
	unsigned int freq[256] = { 0 };
	int sym = 0;
	unsigned int len = 0;

	while ((sym = fgetc(input)) != EOF) {
		len++;
		freq[sym]++;
	}

	if (len == 0) {
		fclose(input);
		fclose(output);
		exit(0);
	}

	struct Node* root = buildTree(freq, input, output);

	struct BitOut* bo = (struct BitOut*)malloc(sizeof(struct BitOut));

	if (bo == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	bo->buffer = (unsigned char*)malloc(BUFFER_SIZE);

	if (bo->buffer == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	memset(bo->buffer, 0, BUFFER_SIZE);

	bo->buffer[0] = (unsigned char)(len >> 24);
	bo->buffer[1] = (unsigned char)(len >> 16);
	bo->buffer[2] = (unsigned char)(len >> 8);
	bo->buffer[3] = (unsigned char)(len);

	fwrite(bo->buffer, sizeof(char), 4, output);

	memset(bo->buffer, 0, BUFFER_SIZE);

	bo->bitpos = 0;

	save(root, bo);

	bo->octpos = bo->bitpos / 8;
	bo->bitpos = bo->bitpos % 8;

	unsigned char* table[256] = { NULL },
		path[256] = { 0 };
	int i = 0;

	createTable(path, 0, table, root);
	fseek(input, 1, SEEK_SET);
	writeEncode(output, input, bo, table);

	while (i < 256) {
		free(table[i]);
		i++;
	}

	deleteTree(root);
	free(bo->buffer);
	free(bo);
}

void createTable(unsigned char path[256], unsigned int level, unsigned char* code[256], struct Node* root) {
	if (root->link[0]) {
		path[level] = '0';
		createTable(path, level + 1, code, root->link[0]);
	}

	if (root->link[1]) {
		path[level] = '1';
		createTable(path, level + 1, code, root->link[1]);
	}

	if (root->link[0] == NULL && root->link[1] == NULL) {
		path[level] = 0;

		unsigned char* mem = (unsigned char*)malloc(level + 1);

		if (mem == NULL) {
			exit(1);
		}

		unsigned int i = 0;

		while (i < level + 1) {
			mem[i] = path[i];
			i++;
		}

		code[root->sym] = mem;
	}
}

void save(struct Node* root, struct BitOut* bo) {
	if (root->link[0]) {
		bo->buffer[bo->bitpos / 8] |= 128u >> (bo->bitpos % 8);
		bo->bitpos += 1;
		save(root->link[0], bo);
		save(root->link[1], bo);
	}
	else {
		unsigned int bitpos1;

		bo->bitpos += 1;
		bitpos1 = bo->bitpos % 8;

		if (bitpos1 == 0) {
			bo->buffer[bo->bitpos / 8] = root->sym;
		}
		else {
			bo->buffer[bo->bitpos / 8] |= root->sym >> bitpos1;
			bo->buffer[bo->bitpos / 8 + 1] |= root->sym << (8 - bitpos1);
		}

		bo->bitpos += 8;
	}
}

void writeEncode(FILE* output, FILE* input, struct BitOut* bo, unsigned char* table[256]) {
	unsigned char inpbuf[BUFFER_SIZE] = { 0 };
	size_t frag = 0;

	while ((frag = fread(inpbuf, 1, BUFFER_SIZE, input)) > 0) {
		for (size_t i = 0; i < frag; i++) {
			unsigned char* currentCode = table[inpbuf[i]];

			for (unsigned int j = 0; currentCode[j] != 0; j++) {
				if (currentCode[j] == '1') {
					bo->buffer[bo->octpos] |= 128u >> bo->bitpos;
				}

				bo->bitpos++;

				if (bo->bitpos > 7) {
					bo->octpos++;
					bo->bitpos = 0;
					bo->buffer[bo->octpos] = 0;

					fwrite(bo->buffer, 1, bo->octpos, output);
					memset(bo->buffer, 0, BUFFER_SIZE);
					bo->octpos = 0;
				}
			}
		}
	}

	fwrite(bo->buffer, 1, (size_t)bo->octpos + (bo->bitpos > 0 ? 1 : 0), output);
}

struct Node* buildTree(unsigned int* letters, FILE* input, FILE* output) {
	struct Node* arr[256] = { NULL };
	int count = 0;

	for (int i = 0; i < 256; i++) {
		if (letters[i]) {
			arr[count] = (struct Node*)malloc(sizeof(struct Node));

			if (arr[count] == NULL) {
				fclose(input);
				fclose(output);
				exit(1);
			}

			arr[count]->freq = letters[i];
			arr[count]->sym = i;
			arr[count]->link[0] = NULL;
			arr[count]->link[1] = NULL;
			count++;
		}
	}

	while (count > 1) {
		for (int i = 0; i < count - 1; i++) {
			for (int j = 0; j < count - i - 1; j++) {
				if (arr[j]->freq < arr[j + 1]->freq) {
					struct Node* tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}

		struct Node* newNode = createNode(arr[count - 2], arr[count - 1], arr[count - 2]->freq + arr[count - 1]->freq, 0, input, output);

		arr[count - 2] = newNode;
		count--;
	}

	struct Node* root = arr[0];

	return root;
}

struct Node* createNode(struct Node* left, struct Node* right, unsigned int freq, int sym, FILE* input, FILE* output) {
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));

	if (temp == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	temp->freq = freq;
	temp->sym = sym;
	temp->link[0] = left;
	temp->link[1] = right;

	return temp;
}

void decode(FILE* input, FILE* output) {
	struct BitInput* bi = (struct BitInput*)malloc(sizeof(struct BitInput));

	if (bi == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	bi->buffer = (unsigned char*)malloc(BUFFER_SIZE);

	if (bi->buffer == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	bi->bitpos = 0;

	if (fread(bi->buffer, 1, BUFFER_SIZE, input) == 0) {
		fclose(input);
		fclose(output);
		exit(0);
	}

	struct Node* root = read(bi, input, output);

	if (bi->content_size == 0) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	write(bi, root, output, input);
	free(bi->buffer);
	free(bi);
}

struct Node* readTree(struct BitInput* bi, FILE* input, FILE* output) {
	struct Node* node = (struct Node*)malloc(sizeof(struct Node));

	if (node == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	int bit = bi->buffer[bi->bitpos / 8] & (128u >> (bi->bitpos % 8));

	bi->bitpos++;

	if (bit) {
		node->link[0] = readTree(bi, input, output);
		node->link[1] = readTree(bi, input, output);
	}
	else {
		unsigned int bitpos1 = bi->bitpos % 8;

		node->link[0] = NULL;
		node->link[1] = NULL;

		if (bitpos1 == 0) {
			node->sym = bi->buffer[bi->bitpos / 8];
		}
		else {
			node->sym = (unsigned char)(bi->buffer[bi->bitpos / 8] << bitpos1);
			node->sym |= bi->buffer[bi->bitpos / 8 + 1] >> (8 - bitpos1);
		}

		bi->bitpos += 8;
	}

	return node;
}

struct Node* read(struct BitInput* bi, FILE* input, FILE* output) {
	bi->content_size = bi->buffer[0] << 24;
	bi->content_size |= bi->buffer[1] << 16;
	bi->content_size |= bi->buffer[2] << 8;
	bi->content_size |= bi->buffer[3];
	bi->bitpos = 32;

	if (bi->content_size > 0) {
		return readTree(bi, input, output);
	}

	return NULL;
}

void write(struct BitInput* bi, struct Node* root, FILE* output, FILE* input) {
	struct BitOut* bo = (struct BitOut*)malloc(sizeof(struct BitOut));

	if (bo == NULL) {
		fclose(input);
		fclose(output);
		exit(1);
	}

	unsigned char outbuf[BUFFER_SIZE] = { 0 };
	size_t k,
		pos = bi->bitpos / 8;

	bo->octpos = 0;
	bo->bitpos = bi->bitpos % 8;

	for (k = 0; k < bi->content_size; k++) {
		struct Node* node = root;

		while (node->link[0] != NULL) {
			node = (bi->buffer[pos] & (128u >> bo->bitpos)) ? node->link[1] : node->link[0];

			if (8 == ++bo->bitpos) {
				bo->bitpos = 0;
				pos++;

				if (pos == BUFFER_SIZE) {
					if (fread(bi->buffer, 1, BUFFER_SIZE, input) == 0) {
						fclose(input);
						fclose(output);
						exit(1);
					};

					pos = 0;
				}
			}
		}

		outbuf[bo->octpos++] = (unsigned char)node->sym;

		if (BUFFER_SIZE == bo->octpos) {
			size_t written = fwrite(outbuf, 1, bo->octpos, output);

			memset(outbuf, 0, BUFFER_SIZE);

			if (bo->octpos != written) {
				fclose(input);
				fclose(output);
				exit(1);
			}

			bo->octpos = 0;
		}
	}

	if (bo->octpos > 0) {
		size_t written = fwrite(outbuf, 1, bo->octpos, output);

		if (bo->octpos != written) {
			fclose(input);
			fclose(output);
			exit(1);
		}
	}

	free(bo);
	deleteTree(root);
}

void deleteTree(struct Node* root) {
	if (root->link[0] != NULL) {
		deleteTree(root->link[0]);
	}

	if (root->link[1] != NULL) {
		deleteTree(root->link[1]);
	}

	free(root);
}
