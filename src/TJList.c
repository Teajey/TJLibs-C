#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/TJUtil.h"

void TJList_addArray(TJList* list, void* array, size_t arrLength) {
	list->elements = realloc(list->elements, (list->length + list->elementSize) * arrLength);
	for (int i = 0; i < arrLength; i++) {
		uint8_t* dst = (uint8_t*)list->elements + list->length + list->elementSize * i;
		uint8_t* src = (uint8_t*)array + i * list->elementSize;
		memcpy(dst, src, list->elementSize);
	}
	list->length += arrLength;
}

void TJList_add(TJList* list, void* element) {
	list->elements = realloc(list->elements, list->length * list->elementSize + list->elementSize);
	uint8_t* dst = (uint8_t*)list->elements + list->length * list->elementSize;
	uint8_t* src = (uint8_t*)element;
	memcpy(dst, src, list->elementSize);
	list->length++;
}

void TJList_remove(TJList* list, size_t index) {
	memcpy((uint8_t*)list->elements + (index - 1) * list->elementSize, (uint8_t*)list->elements + index * list->elementSize, list->elementSize * (list->length - index));
	realloc(list->elements, --list->length);
}

void TJList_init(TJList* list, void* initArray, size_t elementSize, size_t length) {
	list->elementSize = elementSize;
	list->elements = malloc(elementSize * length);
	list->length = 0;
	if (initArray != NULL) {
		printf("Adding initArray\n");
		TJList_addArray(list, initArray, length);
	}
}

void TJList_destroy(TJList* list) {
	printf("Destroying list @%p\n", list);
	memset(list->elements, 0, list->length * list->elementSize);
	free(list->elements);
	list->elementSize = 0;
	list->length = 0;
}

void* TJList_get(TJList* list, size_t index) {
	void* ptr;
	if (index < list->length) {
		ptr = (uint8_t*)list->elements + index * list->elementSize;
	} else {
		fprintf(stderr, "TJList @%p attempted to \'get\' out of bounds! Index: %u Length: %u\n", 
			list, index, list->length);
		fflush(stderr);
		ptr = NULL;
	}
	return ptr;
}

