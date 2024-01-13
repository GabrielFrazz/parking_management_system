#include "searches.h"
#include "customer.h"

#include <chrono>
#include <fstream>

Customer sequentialSearchOfACustomer(FILE *file, int id)
{
    Customer customer(-1, "", "", "", "", "");
    int cod;
    std::string name;
    std::string cpf;
    std::string carModel;
    std::string color;
    std::string date;

    int comparisons = 0; // initialize comparison counter

    auto start = std::chrono::high_resolution_clock::now(); // start timer

    while (fread(&cod, sizeof(int), 1, file)) {
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

        comparisons++; // increment comparison counter

        if (cod == id) {
            customer = Customer(cod, name, cpf, carModel, color, date);
            break;
        }
        //reset strings
        name = "";
        cpf = "";
        carModel = "";
        color = "";
        date = "";

    }

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

    std::ofstream outfile;
    outfile.open("sequential_log.txt", std::ios_base::out); // open file in append mode
    outfile << "\t>>>>> Sequential search <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() << "\n\t\tCustomer cod: " << id <<std::endl;
    if(customer.cod == -1){
        outfile << "Customer not found" << std::endl;
    }
    outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparisons << std::endl;
    outfile.close(); // close file

    return customer;
}

Customer* binarySearchCustomer(FILE* file, int customerId) {
    int left = 0;
    int right = databaseSize() - 1;

    int comparisons = 0; // initialize comparison counter

    auto start = std::chrono::high_resolution_clock::now(); // start timer

    while (left <= right) {
        int mid = left + (right - left) / 2;

        Customer* customer = Customer::readCustomerSpecific(file, mid);

        comparisons++;
        if (customer == nullptr) {
            // Error reading the customer
            return nullptr;
        }

        comparisons++;
        if (customer->cod == customerId) {
            auto end = std::chrono::high_resolution_clock::now(); // end timer
            auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

            std::ofstream outfile;
            outfile.open("binary_log.txt", std::ios_base::out); // open file in append mode
            outfile << "\t>>>>> Binary search <<<<<" << std::endl;
            outfile << "\t\tDatabase size: " << databaseSize() << "\n\t\tCustomer cod: " << customerId <<std::endl;
            outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
            outfile << "- Number of comparisons: " << comparisons << std::endl;
            outfile.close(); // close file
            // Found the customer
            return customer;
        } else if (customer->cod < customerId) {
            // The customer is in the right half
            left = mid + 1;
        } else {
            // The customer is in the left half
            right = mid - 1;
        }

        delete customer;
    }

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

    //erease previous content


    std::ofstream outfile;
    outfile.open("binary_log.txt", std::ios_base::out); // open file in append mode
    outfile << "\t>>>>> Binary search <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() << "\n\t\tCustomer cod: " << customerId <<std::endl;
    outfile << "- !Customer not found!" << std::endl;
    outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparisons << std::endl;
    outfile.flush(); // flush buffer
    outfile.close(); // close file

    // Customer not found
    return nullptr;
}

Customer ParkingLotSearch(FILE *file, int parkingSpot) {
    std::ifstream parkingLotFile("parking_lot.dat", std::ios::in | std::ios::binary);

    if (!parkingLotFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return Customer();
    }

    Customer c = Customer();

    //set the cursor at the beginning of the file
    parkingLotFile.seekg(0, std::ios::beg);

    std::string line;
    while (std::getline(parkingLotFile, line)) {
        std::string delimiter = " : ";
        size_t pos = line.find(delimiter);
        std::string spot = line.substr(0, pos);
        std::string id = line.substr(pos + delimiter.length());
        int customerId = std::stoi(id);
        std::string desiredSpot = "spot" + std::to_string(parkingSpot);
        if (spot == desiredSpot) {
            if(customerId != -1){
                c = sequentialSearchOfACustomer(file, customerId);
                return c;
            }else{
                std::cout << spot << " : " << "empty parking space" << std::endl;
            }
        }
    }

    parkingLotFile.close();
}


void printBinaryLog(){
    // Print the contents of the binary_log.txt
    std::ifstream binaryLog("binary_log.txt");
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Search Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << binaryLog.rdbuf();
    binaryLog.close();
}

void printSequentialLog(){
    // Print the contents of the binary_log.txt
    std::ifstream sequentialLog("sequential_log.txt");
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Search Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << sequentialLog.rdbuf();
    sequentialLog.close();
}