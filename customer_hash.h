#ifndef CUSTOMER_HASH_H
#define CUSTOMER_HASH_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct CustomerHash {
    int cod;
    char name[50];
    char cpf[50];
    char carModel[50];
    char color[50];
    char date[50];
    int next;
} TCustomerHash;

// Print customer
void printCustomer(TCustomerHash *customer);

// Create customer. Remember to use free(customer)
TCustomerHash *createCustomer(int id, const char *name, const char *cpf, const char *carModel, const char *color, const char *date, int next);

// Save customer to the file at the current cursor position
void saveCustomer(TCustomerHash *customer, FILE *out);

// Read a customer from the file at the current cursor position
// Returns a pointer to the customer read from the file
TCustomerHash *readCustomer(FILE *in);

// Returns the size of the customer in bytes
int customerSize();

// Print file
void printFile(FILE *file);

// Returns the size of the file
int fileSize(FILE *file);

const char* generateNames();
const char* generateCPF();

const char* generateCarModel();

const char* generateColor();

const char* generateDate();

#endif // CUSTOMER_HASH_H

