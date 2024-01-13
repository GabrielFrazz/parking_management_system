#include "customer.h"
#include <iostream>
#include <fstream>
#include <math.h>

//costructor
Customer::Customer(int cod, std::string name, std::string cpf, std::string carModel, std::string color, std::string date)
{
    this->cod = cod;
    this->name = name;
    this->cpf = cpf;
    this->carModel = carModel;
    this->color = color;
    this->date = date;
}


int Customer::registerSize() const
{
    return sizeof(int) + 5 * (50 * sizeof(char) + 1);
}

//save the customer in the file
void Customer::savesCustomer(FILE *file) const
{
    fwrite(&cod, sizeof(int), 1, file);
    fwrite(name.c_str(), sizeof(char), name.size() + 1, file);
    fwrite(cpf.c_str(), sizeof(char), cpf.size() + 1, file);
    fwrite(carModel.c_str(), sizeof(char), carModel.size() + 1, file);
    fwrite(color.c_str(), sizeof(char), color.size() + 1, file);
    fwrite(date.c_str(), sizeof(char), date.size() + 1, file);
}

//read the customer from the file
Customer* Customer::readCustomer(FILE *file)
{
    int cod;
    std::string name;
    std::string cpf;
    std::string carModel;
    std::string color;
    std::string date;

    // Read the code
    if (0 >= fread(&cod, sizeof(int), 1, file)) {
        // End of file or error
        return nullptr;
    }

    // Read the data
    char c;
    while (fread(&c, sizeof(char), 1, file) && c != '\0') {
        name.push_back(c);
    }

    while (fread(&c, sizeof(char), 1, file) && c != '\0') {
        cpf.push_back(c);
    }

    while (fread(&c, sizeof(char), 1, file) && c != '\0') {
        carModel.push_back(c);
    }

    while (fread(&c, sizeof(char), 1, file) && c != '\0') {
        color.push_back(c);
    }

    while (fread(&c, sizeof(char), 1, file) && c != '\0') {
        date.push_back(c);
    }

    return new Customer(cod, name, cpf, carModel, color, date);
}

// Read the customer at a specific position in the file
Customer* Customer::readCustomerSpecific(FILE *file, int position)
{
    // Create a temporary instance of Customer to call registerSize()
    Customer tempCustomer(0, "", "", "", "", "");

    // Calculate the position in the file
    long offset = position * tempCustomer.registerSize();

    // Move the file pointer to the correct position
    fseek(file, offset, SEEK_SET);

    // Now call the existing readCustomer function
    return readCustomer(file);
}

//print the customer
void Customer::printCustomer() const
{
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> CUSTOMER <<<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n\n\tCod: " << cod;
    std::cout << "\n\n\tName: " << name;
    std::cout << "\n\n\tCPF: " << cpf;
    std::cout << "\n\n\tCar Model: " << carModel;
    std::cout << "\n\n\tColor: " << color;
    std::cout << "\n\n\tDate: " << date;
}

//functions to generate random data
std::string generateRandomNames()
{
    std::string names[] = {"Patrick","Lucas", "Pedro", "Mariana", "Julia", "Gustavo", "Gabriel", "Fernanda", "Amanda", "Rafael", "Bruno", "Isabela", "Larissa", "Thiago", "Matheus", "Carolina", "Beatriz", "Vinicius", "Adam"};
    return names[rand() % 18];
}

std::string generateRandomCPF()
{
    //generate a random CPF with 11 digits plus the dot and the dash
    std::string cpf = "";
    for (int i = 0; i < 11; i++)
    {
        cpf += std::to_string(rand() % 10);
    }
    cpf.insert(3, ".");
    cpf.insert(7, ".");
    cpf.insert(11, "-");
    return cpf;

}

std::string generateRandomCarModel()
{
    std::string carModels[] = {"Fiat", "Ford", "Chevrolet", "Volkswagen", "Renault", "Toyota", "Hyundai", "Honda", "Jeep", "Nissan", "Citroën", "Mitsubishi", "Peugeot", "Chery", "BMW", "Mercedes-Benz", "Audi", "Kia", "Volvo", "Land Rover", "JAC", "Suzuki", "Subaru", "Chrysler", "Dodge", "Troller", "Jaguar", "Lifan", "Mini", "Lexus", "Porsche", "Ferrari", "Maserati", "Bentley", "Lamborghini", "Rolls-Royce", "Geely", "Cadillac", "Infiniti", "Lincoln", "Aston Martin", "Dongfeng", "Foton", "Shineray", "Triumph", "Agrale", "Asia Motors", "Audi", "BMW", "Changan", "Chery", "Chrysler", "Citroën", "Dodge", "Effa", "Emis", "Engesa", "Envemo", "Ferrari", "Fiat", "Ford", "Foton", "Geely", "Great Wall", "Gurgel", "Hafei", "Honda", "Hyundai", "Isuzu", "JAC", "Jaguar", "Jeep", "Jinbei", "JPX", "Kia", "Lada", "Lamborghini", "Land Rover", "Lexus", "Lifan", "Mahindra", "Maserati", "Matra", "Mazda", "Mercedes-Benz", "MG", "Mini", "Mitsubishi", "Miura", "Nissan", "Peugeot", "Plymouth", "Pontiac", "Porsche", "Ram", "Renault", "Rolls-Royce", "Rover", "Saab", "Saturn", "Seat", "Shineray", "Smart", "Ssangyong", "Subaru", "Suzuki", "TAC", "Toyota", "Troller", "Volkswagen", "Volvo"};
    return carModels[rand() % 100];
}

std::string generateRandomColor()
{
    //generate random colors
    std::string colors[] = {"White", "Black", "Gray", "Silver", "Red", "Blue", "Brown", "Beige", "Yellow", "Green", "Orange", "Gold", "Purple", "Pink"};
    return colors[rand() % 14];
}

std::string generateRandomDate()
{
    //generate a random date between 01/01/2000 and 31/12/2020
    int day = rand() % 31 + 1;
    int month = rand() % 12 + 1;
    int year = rand() % 21 + 2000;

    std::string date;

    if(month < 10){
        date = std::to_string(day) + "/" + "0" + std::to_string(month) + "/" + std::to_string(year);
    }else
        date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);

    return date;
}

//functions to add a new customer
Customer addNewCustomer(FILE *file, int cod) {

    //open file in append mode
    file = fopen("customers.dat", "ab");
    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return Customer(-1, "", "", "", "", "");
    }


    std::string name;
    std::string cpf;
    std::string carModel;
    std::string color;
    std::string date;


    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> CREATING A NEW CUSTOMER <<<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n\n\tName: ";
    std::cin >> name;
    std::cout << "\n\n\tCPF: ";
    std::cin >> cpf;
    std::cout << "\n\n\tCar Model: ";
    std::cin >> carModel;
    std::cout << "\n\n\tColor: ";
    std::cin >> color;
    std::cout << "\n\n\tDate: ";
    std::cin >> date;

    // Resize the strings to 50 characters
    name.resize(50, ' ');
    cpf.resize(50, ' ');
    carModel.resize(50, ' ');
    color.resize(50, ' ');
    date.resize(50, ' ');

    Customer customer(cod, name, cpf, carModel, color, date);
    customer.savesCustomer(file);
    fclose(file);
    return customer;

}

//write customer in the file
void writeCustomer(FILE *file, const Customer *customer, int position) {
    long offset = position * customer->registerSize();
    fseek(file, offset, SEEK_SET);
    customer->savesCustomer(file);
}


//returns the size of the database
int databaseSize() {
    std::fstream file("customers.dat", std::ios::in | std::ios::binary);

    if (!file) {
        std::cerr << "Error opening file for reading." << std::endl;
        return -1;
    }

    file.seekg(0, std::ios::end);
    int size = file.tellg() / Customer().registerSize();

    return size;
}


void createsSortedDatabase(FILE* file, int size) {
    for (int i = 0; i < size; i++) {
        //create a new customer and adds 50 spaces at the end of each string
        std::string name = generateRandomNames();
        name.resize(50, ' ');

        std::string cpf = generateRandomCPF();
        cpf.resize(50, ' ');

        std::string carModel = generateRandomCarModel();
        carModel.resize(50, ' ');

        std::string color = generateRandomColor();
        color.resize(50, ' ');

        std::string date = generateRandomDate();
        date.resize(50, ' ');

        Customer customer(i, name, cpf, carModel, color, date);
        customer.savesCustomer(file);
    }
    fclose(file);
}

void createsUnsortedDatabase(FILE* file, int size) {
    std::vector<int> vet;
    for (int i = 0; i < size; i++) {
        vet.push_back(i);
    }
    shuffle(vet);
    for (int i = 0; i < size; i++) {
        //create a new customer and adds 50 spaces at the end of each string
        std::string name = generateRandomNames();
        name.resize(50, ' ');

        std::string cpf = generateRandomCPF();
        cpf.resize(50, ' ');

        std::string carModel = generateRandomCarModel();
        carModel.resize(50, ' ');

        std::string color = generateRandomColor();
        color.resize(50, ' ');

        std::string date = generateRandomDate();
        date.resize(50, ' ');

        Customer customer(vet[i], name, cpf, carModel, color, date);
        customer.savesCustomer(file);
    }
    fclose(file);
}

// returns a vector shuffled
void shuffle(std::vector<int> &vet)
{
    for (int i = 0; i < vet.size(); i++)
    {
        int j = rand() % vet.size();
        int aux = vet[i];
        vet[i] = vet[j];
        vet[j] = aux;
    }
}

//print the database
void printDatabase(FILE *file) {
    rewind(file);

    Customer* customer;

    while ((customer = Customer::readCustomer(file)) != nullptr) {
        customer->printCustomer();
        delete customer;
    }
}