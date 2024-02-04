
#ifndef HASH_TABLE_EXTERNAL_CHAINING_H
#define HASH_TABLE_EXTERNAL_CHAINING_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "customer_hash.h"
#include "hash_compartment.h"

int hash(int cod, int size);

void creates_hash(const char *hash_name, int size);

int search(int cod, FILE* hash_file, const char* data_file_name, int size);

int insert(TCustomerHash *customer, FILE *hash_file, const char *data_file_name, int size);

int delete_in_hash(int cod, FILE *hash_file, const char *data_file_name, int size);

void print_hash(FILE *hash_file, const char* data_file_name, int size);

void printHashInsertLog();
void printHashSearchLog();

#endif //HASH_TABLE_EXTERNAL_CHAINING_H