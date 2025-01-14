#pragma once

void create_shift(const char* substr, size_t substr_len, size_t* shift);
size_t search_KMP(const char* str, const char* substr, size_t str_len, size_t substr_len, size_t* shift, size_t id_part);
