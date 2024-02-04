#include "tests.h"
#include "customer.h"
#include "sorts.h"
#include "external_sorting.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "external_chaining.h"
#include "customer_hash.h"
#include <winbase.h>



void testSorts(int start, int finish, int interval) {
    //creates a vector of integers from start to finish with interval
    std::vector<int> sizes;
    if(start == finish)
        sizes.push_back(start);
    else if (start > finish)
        for (int i = start; i >= finish; i -= interval) {
            sizes.push_back(i);
        }
    else if (start < finish){
        for (int i = start; i <= finish; i += interval) {
            sizes.push_back(i);
        }
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
\
    
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


void testHash(int start, int finish, int interval){
    //creates a vector of integers from start to finish with interval
    std::vector<int> sizes;
    if(start == finish)
        sizes.push_back(start);
    else if (start > finish)
        for (int i = start; i >= finish; i -= interval) {
            sizes.push_back(i);
        }
    else if (start < finish){
        for (int i = start; i <= finish; i += interval) {
            sizes.push_back(i);
        }
    }

    //creates a vector with the names of the logs for each size of base
    std::vector<std::string> searchlogs;
    std::vector<std::string> insertlogs;
    std::vector<std::string> deletelogs;

    
    for (int i = 0; i < sizes.size(); i++) {
        std::string name = "Search" + std::to_string(sizes[i]) + "_log.txt";
        searchlogs.push_back(name);
        name = "Insert" + std::to_string(sizes[i]) + "_log.txt";
        insertlogs.push_back(name);
        name = "Delete" + std::to_string(sizes[i]) + "_log.txt";
        deletelogs.push_back(name);
    }

    TCustomerHash *customerHash;
    Customer *customer;
    FILE* customers;
    FILE *arq_hash;
    FILE *aux;
    FILE *data_file;
    int position;
    int cod;
    int hash_size;

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
        std::cout << "* Creating database"  << std::endl;
        createsSortedDatabase(customers, sizes[i]);

        //creates a file for each sort, using fstream
        std::fstream searchLog(searchlogs[i], std::ios::out);
        std::fstream insertLog(insertlogs[i], std::ios::out);
        std::fstream deleteLog(deletelogs[i], std::ios::out);

        std::cout << "* Creating hash"  << std::endl;

        arq_hash = fopen("hash_table.dat", "wb+");
        data_file = fopen("customers_hash.dat", "wb+");
        customers = fopen("customers.dat", "rb+");

        hash_size = databaseSize()/4;

#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

        creates_hash("hash_table.dat", hash_size);

        
        auto start = std::chrono::high_resolution_clock::now(); // start timer


        for (int i = 0; i < databaseSize(); i++)
        {
            customer = Customer::readCustomerSpecific(customers,i);

            char name[50]; // Adjust the size as needed
            strncpy(name, customer->name.c_str(), sizeof(name));
            name[sizeof(name) - 1] = '\0'; // Ensure null termination

            char cpf[50]; // Adjust the size as needed
            strncpy(cpf, customer->cpf.c_str(), sizeof(cpf));
            cpf[sizeof(cpf) - 1] = '\0'; // Ensure null termination

            char carModel[50]; // Adjust the size as needed
            strncpy(carModel, customer->carModel.c_str(), sizeof(carModel));
            carModel[sizeof(carModel) - 1] = '\0'; // Ensure null termination

            char color[50]; // Adjust the size as needed
            strncpy(color, customer->color.c_str(), sizeof(color));
            color[sizeof(color) - 1] = '\0'; // Ensure null termination

            char date[50]; // Adjust the size as needed
            strncpy(date, customer->date.c_str(), sizeof(date));
            date[sizeof(date) - 1] = '\0'; // Ensure null termination



            customerHash = createCustomer(i, name, cpf, carModel, color, date, -1);
            insert(customerHash, arq_hash, "customers_hash.dat", hash_size);
        }
        auto end = std::chrono::high_resolution_clock::now(); // end timer
        auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

        insertLog << "\t>>>>> Hash Insertion <<<<<" << std::endl;
        insertLog << "\t\tDatabase size: " << databaseSize() <<std::endl;
        insertLog << "\033[33m- Total time taken: " << duration.count() << " seconds\033[0m" << std::endl;
        insertLog << "\033[34m- Time taken by each insertion: " << duration.count()/databaseSize() << " seconds\033[0m" << std::endl;
        insertLog.close(); // close file

        std::cout << "* Searching in hash"  << std::endl;
        //search for one random cod within the database
        //generate a random number between 0 and the size of the database
        int random = rand() % databaseSize();

            // Add a small delay
#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

        hash_size = databaseSize()/4;
        search(random, arq_hash, "customers_hash.dat", hash_size);

        //open already existing hashSearch file, called "HashSearch_log.txt" and copy it to the new file
        std::fstream searchLogCopy("HashSearch_log.txt", std::ios::in);
        if (!searchLogCopy)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        searchLog << searchLogCopy.rdbuf();
        searchLog.close();
        searchLogCopy.close();

        std::cout << "* Deleting in hash\n"  << std::endl;
        //search for one random cod within the database
        //generate a random number between 0 and the size of the database
        random = rand() % databaseSize();

#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

        delete_in_hash(random, arq_hash, "customers_hash.dat", hash_size);

        //open already existing hashdeletion file, called "HashDeletion_log.txt" and copy it to the new file
        std::fstream deleteLogCopy("HashDeletion_log.txt", std::ios::in);
        if (!deleteLogCopy)
        {
            std::cerr << "Error opening file for reading." << std::endl;
            break;
        }
        deleteLog << deleteLogCopy.rdbuf();
        deleteLog.close();
        deleteLogCopy.close();

        //delete the files
        fclose(arq_hash);
        fclose(data_file);
        remove("hash_table.dat");
        remove("customers_hash.dat");

        
    }



    //print the logs for each size
    for (int i = 0; i < sizes.size(); i++) {
        std::cout << "\n>>>>>>>>>> Logs for " << sizes[i] << " elements <<<<<<<<<<\n" << std::endl;

        // insertion
        std::fstream insertLog(insertlogs[i], std::ios::in);
        if (!insertLog) {
            std::cerr << "Error opening file for reading: " << insertlogs[i] << std::endl;
        } else {
            std::cout << insertLog.rdbuf() << std::endl;
            insertLog.close();
        }
        // search Log
        std::fstream searchLog(searchlogs[i], std::ios::in);
        if (!searchLog) {
            std::cerr << "Error opening file for reading: " << searchlogs[i] << std::endl;
        } else {
            std::cout << searchLog.rdbuf() << std::endl;
            searchLog.close();
        }

        // deletion log
        std::fstream deleteLog(deletelogs[i], std::ios::in);
        if (!deleteLog) {
            std::cerr << "Error opening file for reading: " << deletelogs[i] << std::endl;
        } else {
            std::cout << deleteLog.rdbuf() << std::endl;
            deleteLog.close();
        }

        std::cout << std::endl;

        system("PAUSE");
    }

    //saves the logs in a file called "allLogs.txt"
    std::ofstream allLogs("allLogsHash.txt", std::ios::out);
    if (!allLogs)
    {
        std::cerr << "Error opening file for reading." << std::endl;
    }

    for (int i = 0; i < sizes.size(); i++) {
        allLogs << "\n>>>>>>>>>> Logs for " << sizes[i] << " elements <<<<<<<<<<\n" << std::endl;

        // insertion
        std::fstream insertLog(insertlogs[i], std::ios::in);
        if (!insertLog) {
            std::cerr << "Error opening file for reading: " << insertlogs[i] << std::endl;
        } else {
            allLogs << insertLog.rdbuf() << std::endl;
            insertLog.close();
        }
        // search Log
        std::fstream searchLog(searchlogs[i], std::ios::in);
        if (!searchLog) {
            std::cerr << "Error opening file for reading: " << searchlogs[i] << std::endl;
        } else {
            allLogs << searchLog.rdbuf() << std::endl;
            searchLog.close();
        }

        // deletion log
        std::fstream deleteLog(deletelogs[i], std::ios::in);
        if (!deleteLog) {
            std::cerr << "Error opening file for reading: " << deletelogs[i] << std::endl;
        } else {
            allLogs << deleteLog.rdbuf() << std::endl;
            deleteLog.close();
        }

        allLogs << std::endl;

        //divider
        allLogs << "------------------------------------------------------------------------------------------------------------------------" << std::endl;

        allLogs << std::endl;

    }

    //delete the logs for each size
    for (int i = 0; i < sizes.size(); i++) {
        remove(searchlogs[i].c_str());
        remove(insertlogs[i].c_str());
        remove(deletelogs[i].c_str());

    }
    
    //delete the files
    fclose(arq_hash);
    fclose(data_file);
    remove("hash_table.dat");
    remove("customers_hash.dat");

    //creates a standard database
    customers = fopen("customers.dat", "wb");
    if (!customers)
    {
        std::cerr << "Error opening file for reading." << std::endl;
        return;
    }
    createsSortedDatabase(customers, 100);



}


