#pragma once

void create_shift(size_t shift[256], const char* substr, size_t substr_len);
size_t BMH_search(const char* str, size_t str_len, const char* substr, size_t substr_len, size_t shift[256], size_t id_part);
void alt_memcmp(const char* str, const char* substr, size_t substr_len, size_t i);
