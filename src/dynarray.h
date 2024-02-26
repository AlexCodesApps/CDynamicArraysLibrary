#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#pragma once

typedef struct DynamicArray{
    void *ptr;
    size_t element_size;
    int length;
} DynamicArray;

void CreateDynamicArray(DynamicArray *array, size_t element, int numOfSlots);
void AddToArray(DynamicArray *array, void *data);
void *ReadIndex(DynamicArray *array, int index);
void RemoveElement(DynamicArray *array, void *element);
void ResizeArray(DynamicArray *array, int size);
void DeleteArray(DynamicArray *array);
void DeleteArray(DynamicArray *array);