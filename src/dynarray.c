#include "dynarray.h"

void CreateDynamicArray(DynamicArray *array, size_t element, int numOfSlots) {
    array->element_size = element;
    array->ptr = malloc(element * numOfSlots);
    array->length = numOfSlots;
}

void AddToArray(DynamicArray *array, void *data) {
    if (sizeof(*data) != array->element_size) {
        perror("Invalid Datatype");
        return;
    }
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
    if (sizeof(*data) != sizeof(array->element_size)) {
        perror("Invalid Datatype");
        return;
    }
    void *fptr = ReadIndex(array, index);
    memcpy(fptr, data, array->element_size);
}

void RemoveElement(DynamicArray *array, void * element) {
    if (sizeof(*element) != sizeof(array->element_size)) {
        perror("Invalid Datatype");
        return;
    }
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

void ResizeArray(DynamicArray *array, int size) {
    if (size < array->length) {
        for (int i = size; i < array->length; i++) {
            void *ptr = ReadIndex(array, i);
            free(ptr);
        }
    }
    else {
    array->ptr = realloc(array->ptr, size * array->element_size);
    }
    array->length = size;   
}

void ClearArray(DynamicArray *array) {
    for (int i = 0; i < array->length; i++) {
        void *ptr = ReadIndex(array, i);
        free(ptr);
    }
    array->length = 0;
}

void DeleteArray(DynamicArray *array) {
    ClearArray(array);
    free(array->ptr);
}