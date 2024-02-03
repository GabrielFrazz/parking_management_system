#include "hash_compartment.h"

HashCompartment *hash_compartment(int next)
{
    HashCompartment *compartimento = (HashCompartment *) malloc(sizeof(HashCompartment));
    compartimento->next = next;
    return compartimento;
}

void saves_compartment(HashCompartment *compartment, FILE *out)
{
    fwrite(&compartment->next, sizeof(int), 1, out);
}

HashCompartment *reads_compartment(FILE *in)
{
    HashCompartment *compartimento = (HashCompartment *) malloc(sizeof(HashCompartment));
    if (0 >= fread(&compartimento->next, sizeof(int), 1, in)) {
        free(compartimento);
        return NULL;
    }
    return compartimento;
}

int compartment_size()
{
    return sizeof(int); // next
}