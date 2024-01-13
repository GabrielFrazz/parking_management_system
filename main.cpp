#include <iostream>
#include <fstream>
#include <time.h>

#include "parking_lot.h"
#include "customer.h"
#include "UI.h"

int main() {
    //random seed
    srand(time(NULL));

    FILE *customers = fopen("customers.dat", "wb"); // Use "rb" for reading
    createEmptyParkingLot();

    if (!customers) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }

    MENU(customers);

    fclose(customers);

    return 0;
}