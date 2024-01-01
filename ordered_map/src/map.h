#ifndef VHASH_MAP_H
#define VHASH_MAP_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define VHASH_MAP_CAPACITY 10
#define VHASH_MAP_ASSERT(expr, msg) assert((expr))

typedef enum {
	KEY_TYPE_I32,
	KEY_TYPE_F32,
	KEY_TYPE_CHAR,
	KEY_TYPE_STR,
	KEY_TYPE_PTR,
} KeyType;

typedef struct {
	void* data[VHASH_MAP_CAPACITY];
	size_t size;
} HashMap;

HashMap vhash_map_create(void);
size_t vhash_map_size(const HashMap* this);
bool vhash_map_insert(HashMap* this, KeyType type, const void* key, void* value);
bool vhash_map_insert_i(HashMap* this, const int key, void* value);
bool vhash_map_insert_f(HashMap* this, const float key, void* value);
bool vhash_map_insert_c(HashMap* this, const char key, void* value);
bool vhash_map_insert_str(HashMap* this, const char* key, void* value);
bool vhash_map_insert_ptr(HashMap* this, const void* key, const void* value);
void* vhash_map_erase(HashMap* this, KeyType type, const void* key);
void* vhash_map_erase_i(HashMap* this, const int key);
void* vhash_map_erase_f(HashMap* this, const float key);
void* vhash_map_erase_c(HashMap* this, const char key);
void* vhash_map_erase_str(HashMap* this, const char* key);
void* vhash_map_erase_ptr(HashMap* this, const void* key);
void* vhash_map_find(const HashMap* this, KeyType type, const void* key);
void* vhash_map_find_i(const HashMap* this, const int key);
void* vhash_map_find_f(const HashMap* this, const float key);
void* vhash_map_find_c(const HashMap* this, const char key);
void* vhash_map_find_str(const HashMap* this, const char* key);
void* vhash_map_find_ptr(const HashMap* this, const void* key);
void vhash_map_debug_print(const HashMap* this);

uint64_t vhash_i(const int value);
uint64_t vhash_f(const float value);
uint64_t vhash_c(const char value);
uint64_t vhash_str(const char* value);
uint64_t vhash_ptr(const void* value);

#endif

#ifdef VHASH_MAP_IMPLEMENTATION

HashMap vhash_map_create(void) {
	HashMap map = { .data = NULL, .size = 0 };
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		(&map)->data[i] = NULL;
	}
	return map;
}

size_t vhash_map_size(const HashMap* this) {
	if (this == NULL) {
		return 0;
	}

	return this->size;
}

bool vhash_map_insert(HashMap* this, KeyType type, const void* key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	switch (type) {
		case KEY_TYPE_I32: return vhash_map_insert_i(this, (*(const int*)key), value);
		case KEY_TYPE_F32: return vhash_map_insert_f(this, (*(const float*)key), value);
		case KEY_TYPE_CHAR: return vhash_map_insert_c(this, (*(const char*)key), value);
		case KEY_TYPE_STR: return vhash_map_insert_str(this, (const char*)key, value);
		case KEY_TYPE_PTR: return vhash_map_insert_ptr(this, (const void*)key, value);
	}

	VHASH_MAP_ASSERT(false, "unknown key type!");
	return false;
}

bool vhash_map_insert_i(HashMap* this, const int key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t hash = vhash_i(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] == NULL) {
			// free space
			this->data[attempt] = value;
			this->size++;
			return true;
		}
	}

	printf("failed to insert key: '%d', collision occurred\n", key);
	return false;
}

bool vhash_map_insert_f(HashMap* this, const float key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t hash = vhash_f(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] == NULL) {
			// free space
			this->data[attempt] = value;
			this->size++;
			return true;
		}
	}

	printf("failed to insert key: '%f', collision occurred\n", key);
	return false;
}

bool vhash_map_insert_c(HashMap* this, const char key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t hash = vhash_c(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] == NULL) {
			// free space
			this->data[attempt] = value;
			this->size++;
			return true;
		}
	}

	printf("failed to insert key: '%c', collision occurred\n", key);
	return false;
}

bool vhash_map_insert_str(HashMap* this, const char* key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t hash = vhash_str(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] == NULL) {
			// free space
			this->data[attempt] = value;
			this->size++;
			return true;
		}
	}

	printf("failed to insert key: '%s', collision occurred\n", key);
	return false;
}

bool vhash_map_insert_ptr(HashMap* this, const void* key, void* value) {
	if (this == NULL || value == NULL) {
		return false;
	}

	const uint64_t hash = vhash_ptr(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] == NULL) {
			// free space
			this->data[attempt] = value;
			this->size++;
			return true;
		}
	}

	printf("failed to insert key: '%p', collision occurred\n", key);
	return false;
}

void* vhash_map_erase(HashMap* this, KeyType type, const void* key) {
	if (this == NULL) {
		return NULL;
	}

	switch (type) {
		case KEY_TYPE_I32: return vhash_map_erase_i(this, (*(const int*)key));
		case KEY_TYPE_F32: return vhash_map_erase_f(this, (*(const float*)key));
		case KEY_TYPE_CHAR: return vhash_map_erase_c(this, (*(const char*)key));
		case KEY_TYPE_STR: return vhash_map_erase_str(this, (const char*)key);
		case KEY_TYPE_PTR: return vhash_map_erase_ptr(this, (const void*)key);
	}

	VHASH_MAP_ASSERT(false, "unknown key type!");
	return NULL;
}

void* vhash_map_erase_i(HashMap* this, const int key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_i(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] != NULL) {
			void* data = this->data[attempt];
			this->data[attempt] = NULL;
			this->size--;
			return data;
		}
	}

	return NULL;
}

void* vhash_map_erase_f(HashMap* this, const float key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_f(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] != NULL) {
			void* data = this->data[attempt];
			this->data[attempt] = NULL;
			this->size--;
			return data;
		}
	}

	return NULL;
}

void* vhash_map_erase_c(HashMap* this, const char key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_c(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] != NULL) {
			void* data = this->data[attempt];
			this->data[attempt] = NULL;
			this->size--;
			return data;
		}
	}

	return NULL;
}

void* vhash_map_erase_str(HashMap* this, const char* key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_str(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] != NULL) {
			void* data = this->data[attempt];
			this->data[attempt] = NULL;
			this->size--;
			return data;
		}
	}

	return NULL;
}

void* vhash_map_erase_ptr(HashMap* this, const void* key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_ptr(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[attempt] != NULL) {
			void* data = this->data[attempt];
			this->data[attempt] = NULL;
			this->size--;
			return data;
		}
	}

	return NULL;
}

void* vhash_map_find(const HashMap* this, KeyType type, const void* key) {
	if (this == NULL) {
		return NULL;
	}

	switch (type) {
		case KEY_TYPE_I32: return vhash_map_find_i(this, (*(const int*)key));
		case KEY_TYPE_F32: return vhash_map_find_f(this, (*(const float*)key));
		case KEY_TYPE_CHAR: return vhash_map_find_c(this, (*(const char*)key));
		case KEY_TYPE_STR: return vhash_map_find_str(this, (const char*)key);
		case KEY_TYPE_PTR: return vhash_map_find_ptr(this, (const void*)key);
	}

	VHASH_MAP_ASSERT(false, "unknown key type!");
	return NULL;
}

void* vhash_map_find_i(const HashMap* this, const int key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_i(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[hash] != NULL) {
			return this->data[hash];
		}
	}

	return NULL;
}

void* vhash_map_find_f(const HashMap* this, const float key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_f(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[hash] != NULL) {
			return this->data[hash];
		}
	}

	return NULL;
}

void* vhash_map_find_c(const HashMap* this, const char key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_c(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[hash] != NULL) {
			return this->data[hash];
		}
	}

	return NULL;
}

void* vhash_map_find_str(const HashMap* this, const char* key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_str(key);
	
	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[hash] != NULL) {
			return this->data[hash];
		}
	}

	return NULL;
}

void* vhash_map_find_ptr(const HashMap* this, const void* key) {
	if (this == NULL) {
		return NULL;
	}

	const uint64_t hash = vhash_ptr(key);

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		const uint64_t attempt = (i + hash) % VHASH_MAP_CAPACITY;
		if (this->data[hash] != NULL) {
			return this->data[hash];
		}
	}

	return NULL;
}

void vhash_map_debug_print(const HashMap* this) {
	if (this == NULL) {
		return;
	}

	for (int i = 0; i < VHASH_MAP_CAPACITY; i++) {
		printf("\t%i.\t%u\n", i, this->data[i] == NULL ? 0 : 1);
	}
}

uint64_t vhash_i(const int value) {
	return 5;
}

uint64_t vhash_f(const float value) {
	return 5;
}

uint64_t vhash_c(const char value) {
	return 5;
}

uint64_t vhash_str(const char* value) {
	const size_t length = strlen(value);
	uint64_t hash = 0;
	for (int i = 0; i < length; i++) {
		char c = value[i];
		hash = hash + c;
		hash = (hash * c) % VHASH_MAP_CAPACITY;
	}
	return hash;
}

uint64_t vhash_ptr(const void* value) {
	const uint64_t address = (uint64_t)value;
	const uint64_t hash = address % VHASH_MAP_CAPACITY;
	return hash;
}

#endif