#include <iostream>
#include <fstream>
#include <time.h>

#include "UI.h"
#include "parking_lot.h"

int main() {
    //random seed
    srand(time(NULL));

    FILE *customers = fopen("customers.dat", "wb"); // Use "rb" for reading
    FILE *parkingLot = fopen("parking_lot.dat", "wb"); // Use "rb" for reading
    createEmptyParkingLot();

    if (!customers || !parkingLot) {
        std::cerr << "Error opening files." << std::endl;
        return 1;
    }


    MENU(customers, parkingLot);

    fclose(customers);
    fclose(parkingLot);
    
    //codespace
    
    return 0;
}



