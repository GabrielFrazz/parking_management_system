#ifndef PARKING_MANAGEMENT_SYSTEM_PARKING_LOT_H
#define PARKING_MANAGEMENT_SYSTEM_PARKING_LOT_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

//create parking lot with empty spots
void createEmptyParkingLot();
//print parking lot
void printParkingLot(FILE *file);
//populate parking lot
void populateParkingLot();
//park a car in a parking spot
void parkACar(int id, int parkingSpot);
//leave a parking spot
void leave(int id);




#endif //PARKING_MANAGEMENT_SYSTEM_PARKING_LOT_H
