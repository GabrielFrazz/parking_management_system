#ifndef HASH_TABLE_HASH_COMPARTMENT_H
#define HASH_TABLE_HASH_COMPARTMENT_H

#include <stdlib.h>
#include <stdio.h>

typedef struct HashCompartment {
    int next;
} HashCompartment;

HashCompartment *hash_compartment(int next);

void saves_compartment(HashCompartment *compartment, FILE *out);

HashCompartment *reads_compartment(FILE *in);

int compartment_size();

#endif //HASH_TABLE_HASH_COMPARTMENT_H