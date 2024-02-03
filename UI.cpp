#include "UI.h"
#include "customer.h"
#include "parking_lot.h"
#include "searches.h"
#include "sorts.h"
#include "external_sorting.h"
#include "tests.h"
#include "external_chaining.h"
#include "customer_hash.h"


#include <iostream>
#include <fstream>
#include <winbase.h>
#include <unordered_map>

#include <chrono>
#include <atomic>

void loadingAnimation() {
    std::string animation = "|/-\\";
    int animationIndex = 0;

    for (int i = 0; i < 30; i++) {
        std::cout << "Loading " << animation[animationIndex] << " ";
        Sleep(100); 
        std::cout << "\r";
        animationIndex = (animationIndex + 1) % 4;
    }
}

void MSG_MENU()
{
    system("cls");
    // Add a small delay
#ifdef _WIN32
    Sleep(100); // Sleep for 100 milliseconds on Windows
#else
    usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MENU OPTIONS <<<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n\n\t1. Create a sorted customer database";   // done
    std::cout << "\n\n\t2. Create a unsorted customer database"; // done
    std::cout << "\n\n\t3. Print database";                      // done
    std::cout << "\n\n\t4. Sequential search for a customer";    // done
    std::cout << "\n\n\t5. Binary search for a customer";        // done
    std::cout << "\n\n\t6. Populate parking lot";                // done
    std::cout << "\n\n\t7. Print parking lot";                   // done
    std::cout << "\n\n\t8. search for a parking space";          // done
    std::cout << "\n\n\t9. Park a car";                          // done
    std::cout << "\n\n\t10. Leave";                              // done
    std::cout << "\n\n\t11. Bubble sort";                        // done
    std::cout << "\n\n\t12. Selection sort";                     // done
    std::cout << "\n\n\t13. Shell sort";                         // done
    std::cout << "\n\n\t14. External sort";                      // done
    std::cout << "\n\n\t15. Print partitions";                   // done
    std::cout << "\n\n\t16. Create Partitions";                  // done
    std::cout << "\n\n\t17. Merge Partitions";                   // done
    std::cout << "\n\n\t18. Sorting tests";                      // done
    std::cout << "\n\n\t19. Create hash table";                  // done
    std::cout << "\n\n\t20. Search hash table";                  // done
    std::cout << "\n\n\t21. Delete in hash table";               // done
    std::cout << "\n\n\t22. Print hash table";                   // done
    std::cout << "\n\n\t23. Exit";
}

void MENU(FILE *customers)
{

    //customer
    Customer c = Customer();
    Customer* customer = new Customer();
    Customer *foundCustomer = NULL;
    TCustomerHash *customerHash = NULL;

    //variable for switch
    int option;

    //variables for sorts
    int numberOfPartitions;
    int databaseSiz;
    FILE* mainFile;
    int partitionSize;
    std::ofstream outfile;


    // create default database
    int size = 100;
    createsSortedDatabase(customers, size);



    // variables for tests
    int start;
    int finish;
    int interval;

    //hash 
    FILE *arq_hash;
    FILE *aux;
    FILE *data_file;
    int position;
    int cod;
    int hash_size = databaseSize()/4;




    do
    {
        MSG_MENU();
        std::cout << "\n\nEnter an option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "wb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }

            std::cout << "\n\n\t >>>>>> MSG: Creating Database...!!! <<<<<<\n";
            // reads the size of the database
            std::cout << "\nEnter the size of the database: ";
            std::cin >> size;
            createsSortedDatabase(customers, size);
            std::cout << "\n\t >>>>>> MSG: Database created...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 2:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "wb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\t >>>>>> MSG: Creating Database...!!! <<<<<<\n";
            // reads the size of the database
            std::cout << "\nEnter the size of the database: ";
            std::cin >> size;
            createsUnsortedDatabase(customers, size);
            std::cout << "\n\t >>>>>> MSG: Database created...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 3:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "rb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\t >>>>>> MSG: Printing database...!!! <<<<<<\n";
            // call the function to print the database
            printDatabase(customers);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 4:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "rb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            // flush the buffer
            std::cout.flush();
            std::cout << "\n\n\t >>>>>> MSG: Sequential search for a customer...!!! <<<<<<\n";
            // ask for the customer id
            int id;
            std::cout << "\nEnter customer ID: ";
            std::cin >> id;
            // call the function to search for a customer
            c = sequentialSearchOfACustomer(customers, id);
            if (c.cod != -1)
            {
                std::cout << "\nCustomer found:\n";
                c.printCustomer();
            }
            else
            {
                std::cout << "\nCustomer not found.\n";
            }

            // Print the contents of the sequential_log.txt
            printSequentialLog();

            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 5:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "rb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }

            std::cout << "\n\n\n\t >>>>>> MSG: Binary search for a customer...!!! <<<<<<\n";
            // ask for the customer id
            std::cout << "\nEnter customer ID: ";
            std::cin >> id;

            // call the function to search for a customer

            foundCustomer = binarySearchCustomer(customers, id);

            if (foundCustomer)
            {
                std::cout << "\nCustomer found:\n";
                foundCustomer->printCustomer();
                delete foundCustomer;
            }
            else
            {
                std::cout << "\nCustomer not found.\n";
            }
            // Print the contents of the binary_log.txt
            printBinaryLog();

            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 6:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\t >>>>>> MSG: Populating parking lot...!!! <<<<<<\n";
            // call the function to populate the parking lot
            populateParkingLot();
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 7:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "rb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\n\t >>>>>> MSG: Printing parking lot...!!! <<<<<<\n";
            // call the function to print the parking lot
            printParkingLot(customers);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 8:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            customers = fopen("customers.dat", "rb");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            system("cls");
            std::cout.flush();
            std::cout << "\n\n\n\t >>>>>> MSG: choose the spot...!!! <<<<<<\n";
            int spot;
            std::cout << "Enter parking spot: ";
            std::cin >> spot;
            // call the function to search for a parking space
            c = ParkingLotSearch(customers, spot);
            std::cout << "spot" + std::to_string(spot) + " : " << std::endl;
            c.printCustomer();
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 9:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\t >>>>>> MSG: choose the option...!!! <<<<<<\n";
            std::cout << "\n[1] park an existing customer\n[2] park a new customer\n";
            std::cout << "--->";
            std::cin >> option;
            if (option == 1)
            {
                std::cout << "\n\n\t >>>>>> MSG: choose the spot and customer id...!!! <<<<<<\n";
                std::cout << "\nEnter customer ID: ";
                std::cin >> id;
                std::cout << "Enter parking spot: ";
                std::cin >> spot;
                // call the function to park the car
                parkACar(id, spot);
                std::cout << "\n\n\t >>>>>> MSG: customer parked...!!! <<<<<<\n";
            }
            else if (option == 2)
            {
                c = addNewCustomer(customers, size);
                if (c.cod == -1)
                {
                    std::cout << "\n\n\t >>>>>> MSG: Error adding customer...!!! <<<<<<\n";
                    break;
                }
                std::cout << "Enter parking spot: ";
                std::cin >> spot;
                // call the function to park the car
                parkACar(size, spot);
                size++;
                std::cout << "\n\n\t >>>>>> MSG: customer parked...!!! <<<<<<\n";
            }

            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 10:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\n\t >>>>>> MSG: choose the spot to leave...!!! <<<<<<\n";
            std::cout << "Enter parking spot: ";
            std::cin >> spot;
            // call the function to leave the parking lot
            leave(spot);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 11:
            system("cls");
            // Add a small delay
#ifdef _WIN32
        Sleep(100); // Sleep for 100 milliseconds on Windows
#else
        usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\n\t >>>>>> MSG: Bubble sort...!!! <<<<<<\n";
            customers = fopen("customers.dat", "rb+");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            size = databaseSize();
            bubbleSort(customers, size);
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            printBubbleLog();
            system("PAUSE");
            std::cin.get();
            break;
        case 12: 
        system("cls");
            // Add a small delay
#ifdef _WIN32
        Sleep(100); // Sleep for 100 milliseconds on Windows
#else
        usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\n\t >>>>>> MSG: insertion sort...!!! <<<<<<\n";
            customers = fopen("customers.dat", "rb+");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            size = databaseSize();
            insertionSort(customers, size);
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            printinsertionLog();
            system("PAUSE");
            std::cin.get();
            break;

        case 13:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else   
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif

            std::cout << "\n\n\n\t >>>>>> MSG: Shell sort...!!! <<<<<<\n";
            customers = fopen("customers.dat", "rb+");
            if (!customers)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            size = databaseSize();
            shellSort(customers, size);
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            printShellLog();
            system("PAUSE");
            std::cin.get();
            break;

        case 14:

            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else   
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif

            destroyPartitions();
            std::cout << "\n\n\n\t >>>>>> MSG: External sort...!!! <<<<<<\n";


            databaseSiz = databaseSize();
        
            // partition size definition
            partitionSize = databaseSiz / 10;

            // Creates partitions and sorts them
            mainFile = fopen("customers.dat", "rb+");
            substitutionSelectionSort(mainFile, databaseSiz, partitionSize);
            fclose(mainFile);

            // Get the number of partitions created
            numberOfPartitions = (databaseSiz + partitionSize - 1) / partitionSize;

            // Interleave partitions to rebuild the sorted main file
            mainFile = fopen("customers.dat", "rb+");
            optimalInterleaving(mainFile, numberOfPartitions, partitionSize);
            fclose(mainFile);

            writeLog();

            printExternalLog("ExternalSort_log.txt");

            destroyPartitions();


            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 15:

            system("cls");
            // Add a small delay    
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 

#endif  

            std::cout << "\n\n\t >>>>>> MSG: Printing partitions...!!! <<<<<<\n";
            system("PAUSE");
            printPartitions();

            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 16:
            
            system("cls");
            // Add a small delay    
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else   
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 

#endif     

            destroyPartitions();
            std::cout << "\n\n\n\t >>>>>> MSG: Creating partitions...!!! <<<<<<\n";

            databaseSiz = databaseSize();
        
            // partition size definition
            partitionSize = databaseSiz / 10;

            // Creates partitions and sorts them
            mainFile = fopen("customers.dat", "rb+");
            substitutionSelectionSort(mainFile, databaseSiz, partitionSize);
            fclose(mainFile);

            writeSubstitutionSelectionSort();
            printExternalLog("SubstitutionSelection_log.txt");

            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 17:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif  

            std::cout << "\n\n\n\t >>>>>> MSG: Merging...!!! <<<<<<\n";
            
            numberOfPartitions = (databaseSiz + partitionSize - 1) / partitionSize;

            // Interleave partitions to rebuild the sorted main file
            mainFile = fopen("customers.dat", "rb+");
            optimalInterleaving(mainFile, numberOfPartitions, partitionSize);
            fclose(mainFile);

            writeOptimalInterleaving();
            printExternalLog("OptimalInterleaving_log.txt");

            destroyPartitions();


            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 18:
            system("cls");
            // Add a small delay
#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

            std::cout << "\n\n\n\t >>>>>> MSG: Sorting tests...!!! <<<<<<\n";

            std::cout << "\nEnter the start size: ";
            std::cin >> start;
            std::cout << "\nEnter the finish size: ";
            std::cin >> finish;
            std::cout << "\nEnter the interval: ";
            std::cin >> interval;

            testSorts(start, finish, interval);

            std::cin.get();
            break;

        case 19:
            system("cls");
            // Add a small delay
#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

            std::cout << "\n\n\n\t >>>>>> MSG: Creating hash table...!!! <<<<<<\n";

            arq_hash = fopen("hash_table.dat", "wb+");
            data_file = fopen("customers_hash.dat", "wb+");
            customers = fopen("customers.dat", "rb+");

            if (arq_hash == NULL)
            {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }   

            if(data_file == NULL){
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            hash_size = databaseSize()/4;

            creates_hash("hash_table.dat", hash_size);

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

            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 20:
            system("cls");
            // Add a small delay
#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

            std::cout << "\n\n\n\t >>>>>> MSG: Searching hash table...!!! <<<<<<\n";


            std::cout << "\nEnter the customer code: ";
            std::cin >> cod;

            hash_size = databaseSize()/4;

            position = search(cod, arq_hash, "customers_hash.dat", hash_size);

            if(position != -1){
                aux = fopen("customers_hash.dat", "rb");
                fseek(aux, customerSize() * position, SEEK_SET);
                customerHash = readCustomer(aux);
                printCustomer(customerHash);
                fclose(aux);
            }else{
                std::cout << "Customer not found" << std::endl;
            }




            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 21:
            system("cls");
            // Add a small delay
#ifdef _WIN32   
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else           
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems 
#endif

            std::cout << "\n\n\n\t >>>>>> MSG: Deleting in hash table...!!! <<<<<<\n";

            std::cout << "\nEnter the customer code: ";
            std::cin >> cod;

            hash_size = databaseSize()/4;

            delete_in_hash(cod, arq_hash, "customers_hash.dat", hash_size);

            
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 22:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else   
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems

#endif  


            std::cout << "\n\n\n\t >>>>>> MSG: Printing hash ...!!! <<<<<<\n";
            arq_hash = fopen("hash_table.dat", "rb");

            

            print_hash(arq_hash, "customers_hash.dat", hash_size);
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;


        case 23:

            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\n\t >>>>>> MSG: Exiting the module...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        default:
            system("cls");
            // Add a small delay
#ifdef _WIN32
            Sleep(100); // Sleep for 100 milliseconds on Windows
#else
            usleep(100000); // Sleep for 100 milliseconds on Unix-based systems
#endif
            std::cout << "\n\n\n\t >>>>>> MSG: Enter a valid option!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
        }
        
    } while (option != 23);
}


