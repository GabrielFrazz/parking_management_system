
#include "searches.h"
#include "customer.h"

#include <chrono>
#include <fstream>

Customer sequentialSearchOfACustomer(FILE *file, int id)
{
    Customer customer(0, "", "", "", "", "");
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
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start); // calculate duration in microseconds

    std::ofstream outfile;
    outfile.open("sequential_log.txt", std::ios_base::app); // open file in append mode
    outfile << "Time taken by function: " << duration.count() << " microseconds" << std::endl;
    outfile << "Number of comparisons: " << comparisons << std::endl;
    outfile.close(); // close file

    return customer;
}


Customer* binarySearchCustomer(FILE* file, int targetCod, int size) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left+right) / 2;

        // move the file cursor to the middle of the file
        fseek(file, mid * Customer().registerSize(), SEEK_SET);

        // read the customer at the middle position
        Customer *customer = Customer::readCustomer(file);

        if (customer->cod == targetCod) {
            return customer;
        } else if (customer->cod < targetCod) {
            // search the right half of the file
            left = mid + 1;
        } else {
            // search the left half of the file
            right = mid - 1;
        }
    }

    // customer not found
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





