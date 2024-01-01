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

	void* res = vhash_map_find(&map, type, "Jack");
	int p = 0;
	if (res != NULL) {
		p = *(int*)res;
	}

	printf("Found: %d\n", p);

	vhash_map_debug_print(&map);
	return getchar();
}