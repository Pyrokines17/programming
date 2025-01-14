#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int main(void) {
	size_t Count = 0,
		Weight = 0,
		counter = 1;

	if (scanf("%zu%zu", &Count, &Weight) != 2) {
		return 1;
	}

	size_t* table = init(Count, Weight);

	struct Item* item = (struct Item*)malloc(sizeof(struct Item));

	if (item == NULL) {
		free(table);
		return 1;
	}

	struct Cell* allObjects = (struct Cell*)malloc(sizeof(struct Cell) * Count);

	if (allObjects == NULL) {
		free(table);
		free(item);
		return 1;
	}

	while (counter <= Count) {
		if (scanf("%zu%zu", &item->weight, &item->cost) != 2) {
			free(table);
			free(item);
			free(allObjects);
			return 1;
		}

		createCells(counter, item, allObjects);

		createTable(counter, Weight + 1, item, table);

		counter++;
	}

	printf("%zu\n", table[(Count + 1) * (Weight + 1) - 1]); 

	struct Cell* ourObjects = (struct Cell*)malloc(sizeof(struct Cell) * Count);

	if (ourObjects == NULL) {
		free(table);
		free(item);
		free(allObjects);
		return 1;
	}

	counter = 0;

	findObjects(Count, Weight, table, ourObjects, allObjects, &counter, Weight + 1);

	size_t i = 0;

	while (i < counter) {
		printf("%zu %zu\n", (&ourObjects[i])->weight, (&ourObjects[i])->cost);
		i++;
	}

	free(table);
	free(item);
	free(allObjects);
	free(ourObjects);

	return 0;
}
