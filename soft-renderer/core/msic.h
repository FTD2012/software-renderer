#pragma once
#include <string.h>

inline int equals_to(const char *str1, const char *str2) {
	return strcmp(str1, str2) == 0;
}