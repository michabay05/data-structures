#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int* items;
	size_t length;
} Vec;

Vec vec_init() {
	return (Vec) {
		.items = NULL,
		.length = 0,
	};
}

void vec_append(Vec* vec, int val) {
	// Increase the length attribute to account for the new value
	vec->length++;
	// Reallocate the array to fit the new value
	vec->items = (int*)realloc(vec->items, sizeof(int)*vec->length);
	// Place the final value at the end of the array, i.e. append it
	vec->items[vec->length - 1] = val;
}

void vec_insert(Vec* vec, int val, size_t index) {
	assert(index <= vec->length);
	// Increase the length attribute to account for the new value
	if (index == vec->length) {
		vec_append(vec, val);
		return;
	}
	vec->length++;
	// Reallocate the array to fit the new value
	vec->items = (int*)realloc(vec->items, sizeof(int)*vec->length);
	// Traverse the array backwards and move every value with an index
	// greater than the specified index one position to the right
	for (size_t i = vec->length - 1; i > index; i--) {
		vec->items[i] = vec->items[i - 1];
	}
	// At the specified index, place the specified value
	vec->items[index] = val;

	// NOTE: the values before the index should maintain their previous position
}

void vec_print(const Vec* const vec) {
	printf("[");
	for (size_t i = 0; i < vec->length; i++) {
		printf("%d", vec->items[i]);
		if (i + 1 != vec->length) {
			printf(", ");
		}
	}
	printf("]\n");
}

void vec_deinit(Vec* vec) {
	free(vec->items);
}

int main() {
	Vec vec = vec_init();
	vec_print(&vec);
	for (int i = 0; i < 1000; i++) {
		vec_append(&vec, i * 2 + 10);
	}
	vec_print(&vec);
	vec_insert(&vec, 34, 1);
	vec_print(&vec);

	vec_deinit(&vec);
	return 0;
}
