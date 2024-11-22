// Task 1

// #include <stdio.h>
// struct Car {
//     char model[30];
//     char color[15];
//     int seats;
//     double price;
// };
// struct Car car = {"Honda Civic", "Blue", 4, 22000.00};

// void printCarDetails() {
//     printf("Car Details:\n");
//     printf("Model: %s\n", car.model);
//     printf("Color: %s\n", car.color);
//     printf("Seats: %d\n",car.seats);
//     printf("Price: $%.2lf\n", car.price);
// }

// int main() {
//     printCarDetails();
//     return 0;
// }

// // Task 2

// #include <stdio.h>


// struct Employee {
//     char name[50];
//     int age;
//     float salary;
// };


// struct Employee manager, employee;

// int main() {

//     printf("Enter Employee's Name: ");
//     scanf("%s", employee.name);
//     printf("Enter Employee's Age: ");
//     scanf("%d", &employee.age);
//     printf("Enter Employee's Salary: ");
//     scanf("%f", &employee.salary);


//     printf("\nEnter Manager's Name: ");
//     scanf("%s", manager.name);
//     printf("Enter Manager's Age: ");
//     scanf("%d", &manager.age);


//     if (manager.age > 30) {
//         manager.salary = 65000;
//     } else {
//         manager.salary = 55000;
//     }

//     printf("\nEmployee Details:\n");
//     printf("Name: %s\n", employee.name);
//     printf("Age: %d\n", employee.age);
//     printf("Salary: %.2f\n", employee.salary);


//     printf("\nManager Details:\n");
//     printf("Name: %s\n", manager.name);
//     printf("Age: %d\n", manager.age);
//     printf("Salary: %.2f\n", manager.salary);

//     return 0;
// }


// // Task 3

// #include <stdio.h>


// struct Book {
//     char title[100];
//     char author[100];
//     float price;
// };

// int main() {
//     struct Book books[3];
//     int most_expensive_index = 0, lowest_priced_index = 0;

//     for (int i = 0; i < 3; i++) {
//         printf("\nEnter details for Book %d:\n", i + 1);
//         printf("Title: ");
//         scanf(" %[^\n]", books[i].title); 
//         printf("Author: ");
//         scanf(" %[^\n]", books[i].author);
//         printf("Price: ");
//         scanf("%f", &books[i].price);

//         if (books[i].price > books[most_expensive_index].price) {
//             most_expensive_index = i;
//         }
//         if (books[i].price < books[lowest_priced_index].price) {
//             lowest_priced_index = i;
//         }
//     }

//     printf("\nMost Expensive Book:\n");
//     printf("Title: %s\n", books[most_expensive_index].title);
//     printf("Author: %s\n", books[most_expensive_index].author);
//     printf("Price: %.2f\n", books[most_expensive_index].price);

//     printf("\nLowest Priced Book:\n");
//     printf("Title: %s\n", books[lowest_priced_index].title);
//     printf("Author: %s\n", books[lowest_priced_index].author);
//     printf("Price: %.2f\n", books[lowest_priced_index].price);

//     return 0;
// }

// // Task 4

// #include <stdio.h>
// #define PI 3.14159


// struct Circle {
//     float radius;
// };

// float calculate_area(struct Circle c) {
//     return PI * c.radius * c.radius;
// }

// float calculate_perimeter(struct Circle c) {
//     return 2 * PI * c.radius;
// }

// int main() {
//     struct Circle circle1, circle2;

    
//     printf("Enter the radius of Circle 1: ");
//     scanf("%f", &circle1.radius);

    
//     printf("Enter the radius of Circle 2: ");
//     scanf("%f", &circle2.radius);

    
//     float area1 = calculate_area(circle1);
//     float perimeter1 = calculate_perimeter(circle1);

    
//     float area2 = calculate_area(circle2);
//     float perimeter2 = calculate_perimeter(circle2);

    
//     printf("\nCircle 1:\n");
//     printf("Radius: %.2f\n", circle1.radius);
//     printf("Area: %.2f\n", area1);
//     printf("Perimeter: %.2f\n", perimeter1);

    
//     printf("\nCircle 2:\n");
//     printf("Radius: %.2f\n", circle2.radius);
//     printf("Area: %.2f\n", area2);
//     printf("Perimeter: %.2f\n", perimeter2);

//     return 0;
// }