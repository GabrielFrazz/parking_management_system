#include "sorts.h"
#include "customer.h"
#include <chrono>
//sorts

//insertion sort
void insertionSort(FILE *file, int size) {

    int comparisons = 0; // initialize comparison counter
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    int i, j;
    Customer *customer1, *customer2;

    for (i = 1; i < size; i++) {
        customer1 = Customer::readCustomerSpecific(file, i);
        j = i - 1;
        customer2 = Customer::readCustomerSpecific(file, j);

        while (j >= 0 && customer1->cod < customer2->cod) {
            comparisons++;
            writeCustomer(file, customer2, j + 1);
            j--;
            customer2 = Customer::readCustomerSpecific(file, j);
        }
        writeCustomer(file, customer1, j + 1);
    }


    auto end = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

    std::ofstream outfile;
    outfile.open("InsertionSort_log.txt", std::ios_base::out); // open file in append mode
    outfile << "\t>>>>> Insertion Sort <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() <<std::endl;
    outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparisons << std::endl;
    outfile.close(); // close file
}


//bubble sort
void bubbleSort(FILE *file, int size) {

    int comparisons = 0; // initialize comparison counter
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    int i, j;
    Customer *customer1, *customer2;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            customer1 = Customer::readCustomerSpecific(file, j);
            customer2 = Customer::readCustomerSpecific(file, j + 1);
            comparisons++;
            if (customer1->cod > customer2->cod) {
                writeCustomer(file, customer1, j + 1);
                writeCustomer(file, customer2, j);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

    std::ofstream outfile;
    outfile.open("BubbleSort_log.txt", std::ios_base::out); // open file in append mode
    outfile << "\t>>>>> Bubble Sort <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << databaseSize() <<std::endl;
    outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparisons << std::endl;
    outfile.close(); // close file
}

void shellSort(FILE *file, int size) {

    int gap, i, j;
    int comparisons = 0; // initialize comparison counter
    auto start = std::chrono::high_resolution_clock::now(); // start timer

    try {
        for (gap = size / 2; gap > 0; gap /= 2) {
            for (i = gap; i < size; i += 1) {
                Customer *temp = Customer::readCustomerSpecific(file, i);

                j = i;
                comparisons++;
                Customer *gapCustomer = Customer::readCustomerSpecific(file, j - gap);
                while (j >= gap && gapCustomer->cod > temp->cod) {
                    writeCustomer(file, gapCustomer, j);
                    j -= gap;
                    delete gapCustomer;
                    gapCustomer = Customer::readCustomerSpecific(file, j - gap);
                }

                writeCustomer(file, temp, j);

                delete temp;
                if (j >= gap) {
                    delete gapCustomer;
                }
            }
        }
    } catch (std::bad_alloc& ba) {
        std::cerr << "bad_alloc caught in shellSort: " << ba.what() << '\n';
    }

    auto end = std::chrono::high_resolution_clock::now(); // end timer
    auto duration = std::chrono::duration<double>(end - start); // calculate duration in seconds as a double // calculate duration in seconds

    std::ofstream outfile;
    outfile.open("ShellSort_log.txt", std::ios_base::out); // open file in append mode
    outfile << "\t>>>>> Shell Sort <<<<<" << std::endl;
    outfile << "\t\tDatabase size: " << size << std::endl;
    outfile << "- Time taken by function: " << duration.count() << " seconds" << std::endl;
    outfile << "- Number of comparisons: " << comparisons << std::endl;
    outfile.close(); // close file

}


void printBubbleLog(){
    // Print the contents of the binary_log.txt
    std::ifstream bubbleLog("BubbleSort_log.txt");
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Sort Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << bubbleLog.rdbuf();
    bubbleLog.close();
}

void printinsertionLog(){
    // Print the contents of the binary_log.txt
    std::ifstream insertionLog("InsertionSort_log.txt");
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Sort Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << insertionLog.rdbuf();
    insertionLog.close();
}

void printShellLog(){
    // Print the contents of the binary_log.txt
    std::ifstream shellLog("ShellSort_log.txt");
    std::cout << "\n\n\t>>>>>>>>>>>>>>>>>>>>>>> MSG: Sort Info!!! <<<<<<<<<<<<<<<<<<<<<<<<\n\n";
    std::cout << shellLog.rdbuf();
    shellLog.close();
}

