#ifndef REPLACEMENT_SELECTION_H
#define REPLACEMENT_SELECTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>


void substitutionSelectionSort(FILE* mainFile, int databaseSize, int partitionSize);
void optimalInterleaving(FILE* mainFile, int numberOfPartitions, int partitionSize);
void printPartitions();
void destroyPartitions();
void writeLog();
void writeSubstitutionSelectionSort();
void writeOptimalInterleaving();
void printExternalLog(std::string logName);


#endif // REPLACEMENT_SELECTION_H
