#ifndef PARKING_MANAGEMENT_SYSTEM_SEARCHES_H
#define PARKING_MANAGEMENT_SYSTEM_SEARCHES_H
#include "customer.h"

//searches
Customer sequentialSearchOfACustomer(FILE *file, int id);
Customer* binarySearchCustomer(FILE* file, int customerId);
Customer ParkingLotSearch(FILE *file, int parkingSpot);
void printBinaryLog();
void printSequentialLog();
#endif //PARKING_MANAGEMENT_SYSTEM_SEARCHES_H
