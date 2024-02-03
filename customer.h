
#ifndef PARKING_MANAGEMENT_SYSTEM_CUSTOMER_H
#define PARKING_MANAGEMENT_SYSTEM_CUSTOMER_H


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Customer{
public:

    int cod;
    std::string name;
    std::string cpf;
    std::string carModel;
    std::string color;
    std::string date;

    //default constructor
    Customer() = default;
    //costructor
    Customer(int cod, std::string name, std::string cpf, std::string carModel, std::string color, std::string date);

    //returns the size of the register
    int registerSize() const;
    //save the customer in the file
    void savesCustomer(FILE *file) const;
    //read the customer from the file
    static Customer* readCustomer(FILE *file);
    static Customer* readCustomerSpecific(FILE *file, int position);
    void printCustomer() const;


};

//generate random data
std::string generateRandomNames();
std::string generateRandomCPF();
std::string generateRandomCarModel();
std::string generateRandomColor();
std::string generateRandomDate();

//add new customer
Customer addNewCustomer(FILE *file, int cod);

//write customer in the file
void writeCustomer(FILE *file, const Customer *customer, int position);

//create database
void createsSortedDatabase(FILE* file, int size);
void createsUnsortedDatabase(FILE* file, int size);

//returns the size of the database
int databaseSize();

void printDatabase(FILE* file);
void shuffle(std::vector<int> &vet);

#endif //PARKING_MANAGEMENT_SYSTEM_CUSTOMER_H