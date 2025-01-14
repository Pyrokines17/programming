#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

size_t* init(size_t Count, size_t Weight) {
	size_t* table = (size_t*)malloc((Count + 1) * (Weight + 1) * sizeof(size_t));

	if (table == NULL) {
		exit(1);
	}

	memset(table, 0, (Count + 1) * (Weight + 1) * sizeof(size_t));

	return table;
}

void createCells(size_t counter,struct Item* item, struct Cell* allObjects) {
	(&allObjects[counter - 1])->weight = item->weight;
	(&allObjects[counter - 1])->cost = item->cost;
}

void createTable(size_t str, size_t border, struct Item* item, size_t* table) {
	size_t i = 0,
		id = item->weight;

	while (i < id && i < border) {
		size_t upper = table[(str - 1) * border + i];

		if (upper) {
			table[str * border + i] = upper;
		}

		i++;
	}

	while (id < border) {
		size_t upper = table[(str - 1) * border + id],
			summary = table[(str - 1) * border + (id - item->weight)] + item->cost;

		table[str * border + id] = (upper > summary) ? upper : summary;

		id++;
	}
}

void findObjects(size_t str, size_t col, size_t* table, struct Cell* ourObjects, struct Cell* allObjects, size_t* counter, size_t border) {
	if (table[str * border + col] == 0) {
		return;
	}

	if (table[str * border + col] == table[(str - 1) * border + col]) {
		findObjects(str - 1, col, table, ourObjects, allObjects, counter, border);
	}
	else {
		findObjects(str - 1, col - (&allObjects[str - 1])->weight, table, ourObjects, allObjects, counter, border);
		(&ourObjects[*counter])->weight = (&allObjects[str - 1])->weight;
		(&ourObjects[*counter])->cost = (&allObjects[str - 1])->cost;
		(*counter)++;
	}
}
