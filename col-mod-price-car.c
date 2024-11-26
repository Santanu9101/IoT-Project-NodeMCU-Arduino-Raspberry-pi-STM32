#include <stdio.h>

struct Car {
    char model[50];
    char colour[30];
    float price;
};

void printCar(struct Car car) {
    printf("Car Model: %s\n", car.model);
    printf("Car Colour: %s\n", car.colour);
    printf("Car Price: %.2f\n", car.price);
}

int main() {
    // Create a global Car instance
    struct Car myCar = {"BMW", "Red", 0001};

    // Print car details
    printCar(myCar);

    return 0;
}