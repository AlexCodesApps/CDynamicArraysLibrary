#include "dynarray.h"

void CreateDynamicArray(DynamicArray *array, size_t element, int numOfSlots) {
    array->element_size = element;
    array->ptr = malloc(element * numOfSlots);
    array->length = numOfSlots;
}

void AddToArray(DynamicArray *array, void *data) {
    array->length++;
    array->ptr = realloc(array->ptr, (array->length) * array->element_size);
    void *newptr = (char *)array->ptr + ((array->length - 1) * array->element_size);
    memcpy(newptr, data, array->element_size);
}

void *ReadIndex(DynamicArray *array, int index) {
    void *fptr = array->ptr + (index * array->element_size);
    return fptr;
}

void WriteToIndex(DynamicArray *array, void *data, int index) {
    void *fptr = ReadIndex(array, index);
    memcpy(fptr, data, array->element_size);
}

void RemoveElement(DynamicArray *array, void * element) {
    int removedIndex = -1;
    for (int i = 0; i < array->length; i++) {
        void *fptr = ReadIndex(array, i);
        if (memcmp(fptr, element, array->element_size) == 0) {
            free(fptr);
            removedIndex = i;
            break;
        }
    }
    if (removedIndex >= 0) {
        for (int i = removedIndex; i < array->length - 1; i++) {
            memcpy(ReadIndex(array, i), ReadIndex(array, i + 1), array->element_size);
        }
        free(ReadIndex(array, array->length-1));
        array->length--;
    }
}

