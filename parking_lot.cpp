#include "parking_lot.h"
#include "searches.h"
#include "customer.h"

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <winbase.h>

void createEmptyParkingLot() {
    std::ofstream parkingLotFile("parking_lot.dat", std::ios::out);

    if (!parkingLotFile) {
        std::cerr << "Erro ao criar o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    for (int spot = 1; spot <= 50; ++spot) {
        parkingLotFile << "spot" << spot << " : " << "-1" << std::endl;
    }

    parkingLotFile.close();
}

void populateParkingLot() {
    //delete previus parking lot
    std::remove("parking_lot.dat");
    std::ofstream parkingLotFile("parking_lot.dat", std::ios::out);

    if (!parkingLotFile) {
        std::cerr << "Erro ao criar o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    std::vector<int> cod; // Initialize vector with 50 elements
    for(int i = 0; i < 100; ++i) {
        cod.push_back(i);
    }
    shuffle(cod);

    for (int spot = 1; spot <= 50; ++spot) {
        //place the cod on the spot
        std::string codString = std::to_string(cod[spot]);
        parkingLotFile << "spot" << spot << " : " << codString << std::endl;
    }

    parkingLotFile.close();
}

void parkACar(int id, int parkingSpot) {
    std::ifstream inFile("parking_lot.dat");
    if (!inFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read all lines into a vector
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    if (parkingSpot <= 0 || parkingSpot > lines.size()) {
        std::cerr << "spot não encontrada." << std::endl;
        return;
    }

    // Update the specific line
    std::stringstream ss;
    ss << "spot" << parkingSpot << " : " << id;
    std::string newLine = ss.str();
    lines[parkingSpot - 1] = newLine;

    // Write the updated lines back to the file
    std::ofstream outFile("parking_lot.dat");
    if (!outFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    for (const auto &updatedLine : lines) {
        outFile << updatedLine << std::endl;
    }

    outFile.close();
}


void printParkingLot(FILE *file) {

    std::ifstream parkingLotFile("parking_lot.dat", std::ios::in | std::ios::binary);

    if (!parkingLotFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return;
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
        if(customerId != -1){
            fseek(file, 0, SEEK_SET); // Reset the file pointer to the beginning of the file
            c = sequentialSearchOfACustomer(file, customerId);
            std::cout << spot << " : " << c.name << std::endl;
        }else{
            std::cout << spot << " : " << "empty parking space" << std::endl;
        }
    }

    parkingLotFile.close();

}

void leave(int parkingSpot) {
    std::ifstream inFile("parking_lot.dat");
    if (!inFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read all lines into a vector
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    if (parkingSpot <= 0 || parkingSpot > lines.size()) {
        std::cerr << "spot não encontrada." << std::endl;
        return;
    }

    // Update the specific line
    std::stringstream ss;
    ss << "spot" << parkingSpot << " : " << "-1";
    std::string newLine = ss.str();
    lines[parkingSpot - 1] = newLine;

    // Write the updated lines back to the file
    std::ofstream outFile("parking_lot.dat");
    if (!outFile) {
        std::cerr << "Erro ao abrir o arquivo " << "parking_lot.dat" << std::endl;
        return;
    }

    for (const auto &updatedLine : lines) {
        outFile << updatedLine << std::endl;
    }

    outFile.close();
}


