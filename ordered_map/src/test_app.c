#include <stdio.h>

#define VHASH_MAP_IMPLEMENTATION
#include "map.h"

int main(int argc, char** argv) {
	HashMap map = vhash_map_create();
	int a = 10;
	int b = 11;
	int c = 12;
	const KeyType type = KEY_TYPE_STR;
	vhash_map_insert(&map, type, "Jack", &a);
	vhash_map_insert(&map, type, "Fred", &b);
	vhash_map_insert(&map, type, "Amy", &c);

	vhash_map_erase(&map, type, "Amy");

	char* key = "Amy";
	void* result = vhash_map_find(&map, type, key);
	if (result == NULL) {
		printf("Key: '%s' was not found in map!\n", key);
	} else {
		printf("'%s' -> '%d'\n", key, *(int*)result);
	}

	vhash_map_debug_print(&map);
	return getchar();
}