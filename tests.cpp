#include "tests.h"
#include "customer.h"
#include "sorts.h"
#include "external_sorting.h"
#include <iostream>
#include <fstream>
#include <iomanip>



void testSorts(int start, int finish, int interval) {
    //creates a vector of integers from start to finish with interval
    std::vector<int> sizes;
    for (int i = start; i <= finish; i += interval) {
        sizes.push_back(i);
    }

    //creates a vector with the names of the logs for each size of base
    std::vector<std::string> shelllogs;
    std::vector<std::string> ExternalLogs;
    
    for (int i = 0; i < sizes.size(); i++) {
        std::string name = "ShellSort" + std::to_string(sizes[i]) + "_log.txt";
        shelllogs.push_back(name);
        name = "ExternalSort" + std::to_string(sizes[i]) + "_log.txt";
        ExternalLogs.push_back(name);

    }

    FILE* customers;

    std::cout <<  std::endl;
    //creates a loop that runs through the vector and creates a file for each size
    for (int i = 0; i < sizes.size(); i++) {

        std::cout << "Testing for " << sizes[i] << " elements...\n" << std::endl;

        customers = fopen("customers.dat", "wb");
        if (!customers)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        std::cout << "* Creating unsorted database"  << std::endl;
        createsUnsortedDatabase(customers, sizes[i]);
        fclose(customers); 

        //creates a file for each sort, using fstream
        std::fstream shellLog(shelllogs[i], std::ios::out);
        std::fstream ExternalLog(ExternalLogs[i], std::ios::out);

        customers = fopen("customers.dat", "rb+");
        if (!customers)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        int size = databaseSize();
        std::cout << "* Shell Sort"  << std::endl;
        shellSort(customers, size);
        fclose(customers); 

        //open already existing shellLog file, called "ShellSort_log.txt" and copy it to the new file
        std::fstream shelllogCopy("ShellSort_log.txt", std::ios::in);
        if (!shelllogCopy)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        shellLog << shelllogCopy.rdbuf();

        customers = fopen("customers.dat", "wb");
        if (!customers)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        std::cout << "* Creating unsorted database"  << std::endl;
        createsUnsortedDatabase(customers, sizes[i]);
        fclose(customers); 

        destroyPartitions();
        
        int databaseSiz = databaseSize();
    
        int partitionSize = databaseSiz / 10;

        std::cout << "* External Sort"  << std::endl;

        // Create partitions
        FILE* mainFile = fopen("customers.dat", "rb+");
        substitutionSelectionSort(mainFile, databaseSiz, partitionSize);
        fclose(mainFile);

        // Calculate number of partitions
        int numberOfPartitions = (databaseSiz + partitionSize - 1) / partitionSize;

        
        mainFile = fopen("customers.dat", "rb+");
        optimalInterleaving(mainFile, numberOfPartitions, partitionSize);
        fclose(mainFile);

        writeLog();

        //open already existing ExternalLog file, called "ExternalSort_log.txt" and copy it to the new file
        std::fstream ExternalLogCopy("ExternalSort_log.txt", std::ios::in);
        if (!ExternalLogCopy)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        ExternalLog << ExternalLogCopy.rdbuf();

        destroyPartitions();

        //close the files
        shellLog.close();
        ExternalLog.close();
        shelllogCopy.close();
        ExternalLogCopy.close();

        std::cout << std::endl;

    }


    //print the logs for each size
    for (int i = 0; i < sizes.size(); i++) {
        std::cout << "\n>>>>>>>>>> Logs for " << sizes[i] << " elements <<<<<<<<<<\n" << std::endl;

        // Bubble Sort Log
        std::fstream shellLog(shelllogs[i], std::ios::in);
        if (!shellLog) {
            std::cerr << "Error opening file for reading: " << shelllogs[i] << std::endl;
        } else {
            std::cout << shellLog.rdbuf() << std::endl;
            shellLog.close();
        }

        // External Sort Log
        std::fstream externalLog(ExternalLogs[i], std::ios::in);
        if (!externalLog) {
            std::cerr << "Error opening file for reading: " << ExternalLogs[i] << std::endl;
        } else {
            std::cout << externalLog.rdbuf() << std::endl;
            externalLog.close();
        }

        std::cout << std::endl;

        system("PAUSE");
    }

    //saves the logs in a file called "allLogs.txt"
    std::ofstream allLogs("allLogs.txt", std::ios::out);
    if (!allLogs)
    {
        std::cerr << "Error opening file for reading." << std::endl;
    }

    for (int i = 0; i < sizes.size(); i++) {
        allLogs << "\n>>>>>>>>>> Logs for " << sizes[i] << " elements <<<<<<<<<<\n" << std::endl;

        // Bubble Sort Log
        std::fstream shellLog(shelllogs[i], std::ios::in);
        if (!shellLog) {
            std::cerr << "Error opening file for reading: " << shelllogs[i] << std::endl;
        } else {
            allLogs << shellLog.rdbuf() << std::endl;
            shellLog.close();
        }

        // External Sort Log
        std::fstream externalLog(ExternalLogs[i], std::ios::in);
        if (!externalLog) {
            std::cerr << "Error opening file for reading: " << ExternalLogs[i] << std::endl;
        } else {
            allLogs << externalLog.rdbuf() << std::endl;
            externalLog.close();
        }

        allLogs << std::endl;

        //divider
        allLogs << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

        allLogs << std::endl;

    }

    //delete the logs for each size
    for (int i = 0; i < sizes.size(); i++) {
        remove(shelllogs[i].c_str());
        remove(ExternalLogs[i].c_str());
    }

}