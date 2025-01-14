#pragma once

struct Item {
	size_t weight;
	size_t cost;
};

struct Cell {
	size_t weight;
	size_t cost;
};

size_t* init(size_t Count, size_t Weight);

void createCells(size_t counter, struct Item* item, struct Cell* allObjects);
void createTable(size_t str, size_t border, struct Item* item, size_t* table);

void findObjects(size_t str, size_t col, size_t* table, struct Cell* ourObjects, struct Cell* allObjects, size_t* counter, size_t border);
