#include "customer_hash.h"
#include <string>
#include <iostream>

// Print customer
void printCustomer(TCustomerHash *customer) {
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> CUSTOMER <<<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n\n\tCod: " << customer -> cod;
    std::cout << "\n\n\tName: " << customer -> name;
    std::cout << "\n\n\tCPF: " << customer->cpf;
    std::cout << "\n\n\tCar Model: " << customer->carModel;
    std::cout << "\n\n\tColor: " << customer->color;
    std::cout << "\n\n\tDate: " << customer->date;
    std::cout << "\n\n\tNext: " << customer->next;
}

// Create customer. Remember to use free(customer)
TCustomerHash *createCustomer(int id, const char *name, const char *cpf, const char *carModel, const char *color, const char *date, int next) {
    TCustomerHash *customer = (TCustomerHash *) malloc(sizeof(TCustomerHash));
    if (customer) memset(customer, 0, sizeof(TCustomerHash));
    customer->cod = id;
    strcpy(customer->name, name);
    strcpy(customer->cpf, cpf);
    strcpy(customer->carModel, carModel);
    strcpy(customer->color, color);
    strcpy(customer->date, date);
    customer->next = next;
    return customer;
}

// Save customer to the file at the current cursor position
void saveCustomer(TCustomerHash *customer, FILE *out) {
    fwrite(&customer->cod, sizeof(int), 1, out);
    fwrite(customer->name, sizeof(char), sizeof(customer->name), out);
    fwrite(customer->cpf, sizeof(char), sizeof(customer->cpf), out);
    fwrite(customer->carModel, sizeof(char), sizeof(customer->carModel), out);
    fwrite(customer->color, sizeof(char), sizeof(customer->color), out);
    fwrite(customer->date, sizeof(char), sizeof(customer->date), out);
    fwrite(&customer->next, sizeof(int), 1, out);
}

// Read a customer from the file at the current cursor position
// Returns a pointer to the customer read from the file
TCustomerHash *readCustomer(FILE *in) {
    TCustomerHash *customer = (TCustomerHash *) malloc(sizeof(TCustomerHash));
    if (0 >= fread(&customer->cod, sizeof(int), 1, in)) {
        free(customer);
        return NULL;
    }
    fread(customer->name, sizeof(char), sizeof(customer->name), in);
    fread(customer->cpf, sizeof(char), sizeof(customer->cpf), in);
    fread(customer->carModel, sizeof(char), sizeof(customer->carModel), in);
    fread(customer->color, sizeof(char), sizeof(customer->color), in);
    fread(customer->date, sizeof(char), sizeof(customer->date), in);
    fread(&customer->next, sizeof(int), 1, in);
    return customer;
}

// Returns the size of the customer in bytes
int customerSize() {
    return sizeof(int) + // cod
           sizeof(char) * 50 + // name
           sizeof(char) * 50 + // cpf
           sizeof(char) * 50 + // carModel
           sizeof(char) * 50 + // color
           sizeof(char) * 50 + // date
           sizeof(int); // next
}

// Print file
void printFile(FILE *file) {
    rewind(file);
    TCustomerHash *customer = readCustomer(file);
    while (!feof(file)) {
        printCustomer(customer);
        customer = readCustomer(file);
    }
}

// Returns the size of the file
int fileSize(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = trunc(ftell(file) / customerSize());
    return size;
}

const char* generateNames() {
    static const char* names[] = {"John", "Emma", "Michael", "Sophia", "William", "Olivia"};
    int randomIndex = rand() % (sizeof(names) / sizeof(names[0]));
    return names[randomIndex];
}

const char* generateCPF() {
    static const char* cpf = "1234567890";
    return cpf;
}

const char* generateCarModel() {
    static const char* carModels[] = {"Toyota Camry", "Honda Civic", "Ford Mustang", "Chevrolet Corvette"};
    int randomIndex = rand() % (sizeof(carModels) / sizeof(carModels[0]));
    return carModels[randomIndex];
}

const char* generateColor() {
    static const char* colors[] = {"Red", "Blue", "Green", "Yellow"};
    int randomIndex = rand() % (sizeof(colors) / sizeof(colors[0]));
    return colors[randomIndex];
}

const char* generateDate() {
    static const char* dates[] = {"2022-01-01", "2022-02-15", "2022-03-10", "2022-04-20"};
    int randomIndex = rand() % (sizeof(dates) / sizeof(dates[0]));
    return dates[randomIndex];
}