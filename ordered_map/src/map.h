#ifndef VHASH_MAP_H
#define VHASH_MAP_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define VHASH_MAP_SIZE 10
#define VHASH_MAP_ASSERT(expr, msg) assert((expr))

typedef enum {
	KEY_TYPE_I32,
	KEY_TYPE_F32,
	KEY_TYPE_CHAR,
	KEY_TYPE_STR,
} KeyType;

typedef struct {
	void* data[VHASH_MAP_SIZE];
} HashMap;

HashMap vhash_map_create(void);
bool vhash_map_insert(HashMap* this, KeyType type, const void* key, void* value);
bool vhash_map_insert_i(HashMap* this, const int key, void* value);
bool vhash_map_insert_f(HashMap* this, const float key, void* value);
bool vhash_map_insert_c(HashMap* this, const char key, void* value);
bool vhash_map_insert_str(HashMap* this, const char* key, void* value);
void* vhash_map_find(const HashMap* this, KeyType type, const void* key);
void* vhash_map_find_i(const HashMap* this, const int key);
void* vhash_map_find_f(const HashMap* this, const float key);
void* vhash_map_find_c(const HashMap* this, const char key);
void* vhash_map_find_str(const HashMap* this, const char* key);
void vhash_map_debug_print(const HashMap* this);

uint64_t vhash_i(int value);
uint64_t vhash_f(float value);
uint64_t vhash_c(char value);
uint64_t vhash_str(const char* value);

#endif

#ifdef VHASH_MAP_IMPLEMENTATION

HashMap vhash_map_create(void) {
	HashMap map = { .data = NULL };
	for (int i = 0; i < VHASH_MAP_SIZE; i++) {
		(&map)->data[i] = NULL;
	}
	return map;
}

bool vhash_map_insert(HashMap* this, KeyType type, const void* key, void* value) {
	switch (type) {
		case KEY_TYPE_I32: return vhash_map_insert_i(this, (*(const int*)key), value);
		case KEY_TYPE_F32: return vhash_map_insert_f(this, (*(const float*)key), value);
		case KEY_TYPE_CHAR: return vhash_map_insert_c(this, (*(const char*)key), value);
		case KEY_TYPE_STR: return vhash_map_insert_str(this, (const char*)key, value);
	}

	VHASH_MAP_ASSERT(false, "unknown key type!");
	return false;
}

bool vhash_map_insert_i(HashMap* this, const int key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t index = vhash_i(key);
	if (this->data[index] != NULL) {
		printf("HashMap collision occurred with key: '%d'\n", key);
		return false;
	}
	else {
		this->data[index] = value;
		return true;
	}
}

bool vhash_map_insert_f(HashMap* this, const float key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t index = vhash_f(key);
	if (this->data[index] != NULL) {
		printf("HashMap collision occurred with key: '%f'\n", key);
		return false;
	}
	else {
		this->data[index] = value;
		return true;
	}
}

bool vhash_map_insert_c(HashMap* this, const char key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t index = vhash_c(key);
	if (this->data[index] != NULL) {
		printf("HashMap collision occurred with key: '%c'\n", key);
		return false;
	}
	else {
		this->data[index] = value;
		return true;
	}
}

bool vhash_map_insert_str(HashMap* this, const char* key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t index = vhash_str(key);
	if (this->data[index] != NULL) {
		printf("HashMap collision occurred with key: '%s'\n", key);
		return false;
	} else {
		this->data[index] = value;
		return true;
	}
}

void* vhash_map_find(const HashMap* this, KeyType type, const void* key) {
	switch (type) {
		case KEY_TYPE_I32: return vhash_map_find_i(this, (*(const int*)key));
		case KEY_TYPE_F32: return vhash_map_find_f(this, (*(const float*)key));
		case KEY_TYPE_CHAR: return vhash_map_find_c(this, (*(const char*)key));
		case KEY_TYPE_STR: return vhash_map_find_str(this, (const char*)key);
	}

	VHASH_MAP_ASSERT(false, "unknown key type!");
	return NULL;
}

void* vhash_map_find_i(const HashMap* this, const int key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t index = vhash_i(key);
	if (this->data[index] != NULL) {
		return this->data[index];
	}

	return NULL;
}

void* vhash_map_find_f(const HashMap* this, const float key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t index = vhash_f(key);
	if (this->data[index] != NULL) {
		return this->data[index];
	}

	return NULL;
}

void* vhash_map_find_c(const HashMap* this, const char key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t index = vhash_c(key);
	if (this->data[index] != NULL) {
		return this->data[index];
	}

	return NULL;
}

void* vhash_map_find_str(const HashMap* this, const char* key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t index = vhash_str(key);
	if (this->data[index] != NULL) {
		return this->data[index];
	}

	return NULL;
}

void vhash_map_debug_print(const HashMap* this) {
	for (int i = 0; i < VHASH_MAP_SIZE; i++) {
		printf("\t%i.\t%u\n", i, this->data[i] == NULL ? 0 : 1);
	}
}

uint64_t vhash_i(int value) {
	return 5;
}

uint64_t vhash_f(float value) {
	return 5;
}

uint64_t vhash_c(char value) {
	return 5;
}

uint64_t vhash_str(const char* value) {
	const size_t length = strlen(value);
	uint32_t hash = 0;
	for (int i = 0; i < length; i++) {
		const int rounds = 2;
		for (int j = 0; j < rounds; j++) {
			char c = value[i];
			hash = hash + c;
			hash = hash * c;
		}
		hash = (hash + value[i] * value[i]) % VHASH_MAP_SIZE;
	}
	return hash;
}

#endif