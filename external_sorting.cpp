#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "customer.h"
#include <chrono>

// Global variables for durations
std::chrono::duration<double> durationSubstitutionSelectionSort(0);
std::chrono::duration<double> durationOptimalInterleaving(0);

int comparations = 0;

void substitutionSelectionSort(FILE* mainFile, int databaseSize, int partitionSize) {

    auto start = std::chrono::high_resolution_clock::now(); // Start measuring time


    std::vector<Customer*> partition;
    int partitionNumber = 1;

    for (int i = 0; i < databaseSize; i += partitionSize) {
        partition.clear();


        for (int j = 0; j < partitionSize && i + j < databaseSize; ++j) {
            partition.push_back(Customer::readCustomerSpecific(mainFile, i + j));
        }


        std::sort(partition.begin(), partition.end(), [](Customer* a, Customer* b) {
            return a->cod < b->cod;
            comparations++;
        });


        char partitionFileName[20];
        snprintf(partitionFileName, sizeof(partitionFileName), "partition%d.dat", partitionNumber);
        FILE* partitionFile = fopen(partitionFileName, "wb");

        for (Customer* customer : partition) {
            customer->savesCustomer(partitionFile);
            delete customer;
        }

        fclose(partitionFile);
        ++partitionNumber;
    }

    auto stop = std::chrono::high_resolution_clock::now(); // Stop measuring time
    durationSubstitutionSelectionSort += std::chrono::duration<double>(stop - start); // Calculate duration in seconds 

}


void optimalInterleaving(FILE* mainFile, int numberOfPartitions, int partitionSize) {

    auto start = std::chrono::high_resolution_clock::now(); // Start measuring time

    std::vector<FILE*> partitionFiles;
    std::vector<Customer*> customers;


    for (int i = 1; i <= numberOfPartitions; ++i) {
        char partitionFileName[20];
        snprintf(partitionFileName, sizeof(partitionFileName), "partition%d.dat", i);
        FILE* partitionFile = fopen(partitionFileName, "rb");
        partitionFiles.push_back(partitionFile);


        Customer* customer = Customer::readCustomer(partitionFile);
        comparations++;
        if (customer) {
            customers.push_back(customer);
        }
    }

    FILE* sortedMainFile = fopen("customers.dat", "wb");

 
    while (!customers.empty()) {
        
        auto minCustomer = std::min_element(customers.begin(), customers.end(), [](Customer* a, Customer* b) {
            return a->cod < b->cod;
            comparations++;
        });

        
        (*minCustomer)->savesCustomer(sortedMainFile);

        
        FILE* partitionFile = partitionFiles[minCustomer - customers.begin()];
        Customer* nextCustomer = Customer::readCustomer(partitionFile);

        
        delete *minCustomer;
        *minCustomer = nextCustomer;

        
        comparations++;
        if (!nextCustomer) {
            fclose(partitionFile);
            partitionFiles.erase(partitionFiles.begin() + (minCustomer - customers.begin()));
            customers.erase(minCustomer);
        }
    }


    fclose(sortedMainFile);
    for (FILE* partitionFile : partitionFiles) {
        fclose(partitionFile);
    }

    auto stop = std::chrono::high_resolution_clock::now(); // Stop measuring time
    durationOptimalInterleaving += std::chrono::duration<double>(stop - start); // Calculate duration in seconds

}

void printPartitions() {
    // if there are no partitions, print a message and return
    if (fopen("partition1.dat", "rb") == NULL) {
        std::cout << "No partitions exist." << std::endl;
        return;
    }
    
    int partitionNumber = 1;
    char partitionFileName[20];

    while (true) {
        // Construct the partition file name
        snprintf(partitionFileName, sizeof(partitionFileName), "partition%d.dat", partitionNumber);

        // Attempt to open the partition file
        FILE* partitionFile = fopen(partitionFileName, "rb");

        if (!partitionFile) {
            // If the file doesn't exist, break out of the loop
            break;
        }

        std::cout << "Partition " << partitionNumber << " contents:" << std::endl;

        // Print the contents of the partition
        while (!feof(partitionFile)) {
            Customer* customer = Customer::readCustomer(partitionFile);

            if (customer) {
                customer->printCustomer();
                delete customer;
            }
        }

        fclose(partitionFile);
        std::cout << std::endl;

        // Move on to the next partition
        partitionNumber++;
    }
}

void destroyPartitions() {
    int partitionNumber = 1;
    char partitionFileName[20];

    while (true) {
  
        snprintf(partitionFileName, sizeof(partitionFileName), "partition%d.dat", partitionNumber);


        FILE* partitionFile = fopen(partitionFileName, "rb");

        if (!partitionFile) {
            // If the file doesn't exist, break out of the loop
            break;
        }

        // Destroy the partition file
        fclose(partitionFile);
        remove(partitionFileName);

        // Move on to the next partition
        partitionNumber++;
    }
}

// Function to write the log
void writeLog() {
    std::ofstream outfile;
    outfile.open("ExternalSort_log.txt", std::ios_base::out); // open file in append mode

    // Calculate total duration
    auto totalDuration = durationSubstitutionSelectionSort + durationOptimalInterleaving;

    outfile << "\t>>>>> External Sort <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() << std::endl;
    outfile << "- Total time taken: " << totalDuration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparations << std::endl;
    outfile << "- Time taken by Substitution Selection: " << durationSubstitutionSelectionSort.count() << " seconds" << std::endl;
    outfile << "- Time taken by Optimal Interleaving: " << durationOptimalInterleaving.count() << " seconds" << std::endl;
    outfile.close(); // close file
    //reset global variables
    durationSubstitutionSelectionSort = std::chrono::seconds(0);
    durationOptimalInterleaving = std::chrono::seconds(0);
    comparations = 0;
}

void writeSubstitutionSelectionSort() {
    std::ofstream outfile;
    outfile.open("SubstitutionSelection_log.txt", std::ios_base::out); // open file in append mode

    outfile << "\n\t>>>>> Substitution Selection <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() << std::endl;
    outfile << "- Time taken by function: " << durationSubstitutionSelectionSort.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparations << std::endl;
    outfile.close(); // close file
    //reset global variables
    durationSubstitutionSelectionSort = std::chrono::seconds(0);
    comparations = 0;
}

void writeOptimalInterleaving() {
    std::ofstream outfile;
    outfile.open("OptimalInterleaving_log.txt", std::ios_base::out); // open file in append mode

    outfile << "\n\t>>>>> Optimal Interleaving <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() << std::endl;
    outfile << "- Time taken by function: " << durationOptimalInterleaving.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparations << std::endl;
    outfile.close(); // close file
    //reset global variables
    durationOptimalInterleaving = std::chrono::seconds(0);
    comparations = 0;
}

void printExternalLog(std::string logName){
    // Print the contents of the binary_log.txt
    std::ifstream externalLog(logName);
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << externalLog.rdbuf();
    externalLog.close();
}
