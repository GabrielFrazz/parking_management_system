#ifndef PARKING_MANAGEMENT_SYSTEM_SORTS_H
#define PARKING_MANAGEMENT_SYSTEM_SORTS_H

#include "customer.h"

//sorts
void insertionSort(FILE *file, int size);
void bubbleSort(FILE *file, int size);
void shellSort(FILE *file, int size);
void printBubbleLog();
void printinsertionLog();
void printShellLog();
#endif //PARKING_MANAGEMENT_SYSTEM_SORTS_H