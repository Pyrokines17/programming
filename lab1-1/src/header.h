#pragma once

size_t hash(const char* str, size_t str_len, int* degree);
size_t RK_search(const char* str, size_t str_len, const char* substr, size_t substr_hash, size_t substr_len, size_t id_part);
size_t check(const char* str, const char* substr, size_t substr_len, size_t i);
