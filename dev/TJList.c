#include "../include/TJUtil.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static const size_t PTR_SIZE = sizeof(PTR_T);

void TJList_create(TJList* list, void* ptrArr, size_t length) {
	if (ptrArr != NULL) {
		list->elems = malloc(PTR_SIZE * length);
		PTR_T* ptr_t_arr = (PTR_T*)ptrArr;
		for (int i = 0; i < length; i++) {
			list->elems[i] = ptr_t_arr[i];
		}
	} else list->elems = malloc(PTR_SIZE);
	list->length = length;
}

void TJList_resize(TJList* list, size_t newLength) {
	list->elems = realloc(list->elems, PTR_SIZE * (list->length = newLength));
}

void TJList_destroy(TJList* list) {
	free(list->elems);
	memset(list, 0, sizeof(*list));
}

void* TJList_get(TJList* list, size_t index) {
	return (void*) list->elems[index];
}

void** TJList_array(TJList* list) {
	return (void**) list->elems;
}

void TJList_add(TJList* list, void* elemAddr) {
	bool alreadyContained = false;
	for (int i = 0; i < list->length; i++) {
		alreadyContained = ((PTR_T*)list->elems[i] == (PTR_T*)elemAddr);
	}

	if (!alreadyContained) {
		TJList_resize(list, list->length + 1);
		list->elems[list->length - 1] = (PTR_T)elemAddr;
	} else {
		fprintf(stderr, "TJList %p already contains %p.\n", list, elemAddr);
		fflush(stderr);
	}
}

void TJList_insert(TJList* list, void* elem, size_t index) {
	TJList_resize(list, list->length + 1);
	memcpy(list->elems + index + 1, list->elems + index, PTR_SIZE * (list->length - index));
	list->elems[index] = (PTR_T)elem;
}

void TJList_removeAt(TJList* list, size_t index) {
	memcpy(list->elems + index, list->elems + index + 1, PTR_SIZE * (list->length - index));
	TJList_resize(list, list->length - 1);
}

void TJList_remove(TJList* list, void* elemAddr) {
	for (int i = 0; i < list->length; i++) {
		if (list->elems[i] == (PTR_T)elemAddr) {
			TJList_removeAt(list, i);
			return;
		}
	}
	fprintf(stderr, "%p was not found in TJList %p.\n", elemAddr, list);
	fflush(stderr);
}

void TJList_printbin(TJList* list) {
	printf("Printing TJList Binary:\n");
	printf("\tLength: %u\n", list->length);
	for (int i = 0; i < list->length; i++) {
		printf("\t0x%p contains %p\n", list->elems + i, list->elems[i]);
	}
}

int main() {
	TJList list;
	TJList_create(&list, NULL, 0);
	TJList_destroy(&list);
	printf("No crash!\n");
}