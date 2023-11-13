
#include "UI.h"
#include "customer.h"
#include "parking_lot.h"
#include "searches.h"

#include <iostream>
#include <fstream>

void MSG_MENU()
{
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MENU OPTIONS <<<<<<<<<<<<<<<<<<<<<<<<";
    std::cout << "\n\n\t1. Create a sorted customer database"; //done
    std::cout << "\n\n\t2. Create a unsorted customer database"; //done
    std::cout << "\n\n\t3. Print database"; //done
    std::cout << "\n\n\t4. Sequential search for a customer"; //done
    std::cout << "\n\n\t5. Binary search for a customer"; //unimplemented
    std::cout << "\n\n\t6. Populate parking lot"; //unimplemented
    std::cout << "\n\n\t7. Print parking lot"; //done
    std::cout << "\n\n\t8. search for a parking space"; //done
    std::cout << "\n\n\t9. Park a car"; //done
    std::cout << "\n\n\t10. Leave"; //unimplemented
    std::cout << "\n\n\t11. Exit";

}

void MENU(FILE *customers, FILE *parkingLot)
{

    int option;
    Customer c = Customer();

    //create default database
    int size = 100;
    createsSortedDatabase(customers, size);

    do
    {
        MSG_MENU();
        std::cout << "\n\nEnter an option: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            system("cls");
            customers = fopen("customers.dat", "wb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }

            std::cout << "\n\n\t >>>>>> MSG: Creating Database...!!! <<<<<<\n";
            //reads the size of the database
            std::cout << "\nEnter the size of the database: ";
            std::cin >> size;
            createsSortedDatabase(customers,size);
            std::cout << "\n\t >>>>>> MSG: Database created...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 2:
            system("cls");
            customers = fopen("customers.dat", "wb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\t >>>>>> MSG: Creating Database...!!! <<<<<<\n";
            //reads the size of the database
            std::cout << "\nEnter the size of the database: ";
            std::cin >> size;
            createsUnsortedDatabase(customers,size); 
            std::cout << "\n\t >>>>>> MSG: Database created...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;    

        case 3:
            system("cls");
            customers = fopen("customers.dat", "rb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\t >>>>>> MSG: Printing database...!!! <<<<<<\n";
            //call the function to print the database
            printDatabase(customers);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;    

        case 4:
            system("cls");
            customers = fopen("customers.dat", "rb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\t >>>>>> MSG: Sequential search for a customer...!!! <<<<<<\n";
            //ask for the customer id
            int id;
            std::cout << "\nEnter customer ID: ";
            std::cin >> id;
            //call the function to search for a customer
            c = sequentialSearchOfACustomer(customers, id);
            c.printCustomer();
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 5:
            system("cls");
            customers = fopen("customers.dat", "rb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\n\t >>>>>> MSG: Binary search for a customer...!!! <<<<<<\n";
            //ask for the customer id
            std::cout << "\nEnter customer ID: ";
            std::cin >> id;

            //call the function to search for a customer

            Customer *foundCustomer ;
            foundCustomer = binarySearchCustomer(customers, id, 100);

            if (foundCustomer) {
                std::cout << "\nCustomer found:\n";
                foundCustomer->printCustomer();
                delete foundCustomer;
            } else {
                std::cout << "\nCustomer not found.\n";
            }
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 6:
            system("cls");
            std::cout << "\n\n\t >>>>>> MSG: Populating parking lot...!!! <<<<<<\n";
            //call the function to populate the parking lot
            populateParkingLot();
            std::cout << "\n\n\t >>>>>> MSG: Done...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 7:
            system("cls");
            customers = fopen("customers.dat", "rb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            std::cout << "\n\n\n\t >>>>>> MSG: Printing parking lot...!!! <<<<<<\n";
            //call the function to print the parking lot
            printParkingLot(customers);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;

        case 8:
            customers = fopen("customers.dat", "rb");
            if (!customers) {
                std::cerr << "Error opening file for reading." << std::endl;
                break;
            }
            system("cls");
            std::cout << "\n\n\t >>>>>> MSG: choose the option...!!! <<<<<<\n";
            std::cout << "\n[1] park an existing customer\n[2] park a new customer\n-->";
            std::cin >> option;
            if(option == 1){

            }
            std::cout << "\n\n\n\t >>>>>> MSG: choose the spot...!!! <<<<<<\n";
            int spot;
            std::cout << "Enter parking spot: ";
            std::cin >> spot;
            //call the function to search for a parking space
            c = ParkingLotSearch(customers, spot);
            std::cout << "spot" + std::to_string(spot) + " : "  << std::endl;
            c.printCustomer();
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;
        case 9:
            std::cout << "\n\n\t >>>>>> MSG: choose the option...!!! <<<<<<\n";
            std::cout << "\n[1] park an existing customer\n[2] park a new customer\n";
            std::cout << "--->";
            std::cin >> option;
            if(option == 1){
                std::cout << "\n\n\t >>>>>> MSG: choose the spot and customer id...!!! <<<<<<\n";
                std::cout << "\nEnter customer ID: ";
                std::cin >> id;
                std::cout << "Enter parking spot: ";
                std::cin >> spot;
                //call the function to park the car
                parkACar(id, spot);
                std::cout << "\n\n\t >>>>>> MSG: customer parked...!!! <<<<<<\n";
            }else if(option == 2){
                c = addNewCustomer(customers, size);
                if(c.cod == -1){
                    std::cout << "\n\n\t >>>>>> MSG: Error adding customer...!!! <<<<<<\n";
                    break;
                }
                std::cout << "Enter parking spot: ";
                std::cin >> spot;
                //call the function to park the car
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
            std::cout << "\n\n\n\t >>>>>> MSG: choose the spot to leave...!!! <<<<<<\n";
            std::cout << "Enter parking spot: ";
            std::cin >> spot;
            //call the function to leave the parking lot
            leave(spot);
            std::cout << "\n";
            system("PAUSE");
            std::cin.get();
            break;    
        case 11:
            system("cls");
            std::cout << "\n\n\n\t >>>>>> MSG: Exiting the module...!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
            break;
        default:
            system("cls");
            std::cout << "\n\n\n\t >>>>>> MSG: Enter a valid option!!! <<<<<<\n";
            system("PAUSE");
            std::cin.get();
        }
    } while (option != 11);
}
