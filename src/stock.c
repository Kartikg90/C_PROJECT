#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/stock.h"

#define DATA_FILE "stock_data.txt"

void showMenu() {
    printf("\n--- STOCK MANAGEMENT ---\n");
    printf("1. Add stock\n");
    printf("2. View all stocks\n");
    printf("3. Search stock by name\n");
    printf("4. Update stock quantity\n");
    printf("5. Delete stock by name\n");
    printf("6. Exit\n");
    printf("Enter choice: ");
}

void addStock() {
    FILE *fp = fopen(DATA_FILE, "a");
    if (!fp) {
        printf("Error opening file.\n");
        return;
    }

    StockItem item;

    printf("Enter stock name: ");
    scanf("%49s", item.name);
    printf("Enter quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter purchase price: ");
    scanf("%f", &item.price);

    fprintf(fp, "%s %d %.2f\n", item.name, item.quantity, item.price);

    fclose(fp);
    printf("Stock added successfully.\n");
}

void viewStock() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No stock data found.\n");
        return;
    }

    StockItem item;
    printf("\nName\tQuantity\tPrice\n");
    printf("-----------------------------\n");

    while (fscanf(fp, "%49s %d %f", item.name, &item.quantity, &item.price) == 3) {
        printf("%s\t%d\t\t%.2f\n", item.name, item.quantity, item.price);
    }

    fclose(fp);
}

void searchStock() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No stock data found.\n");
        return;
    }

    char searchName[NAME_LEN];
    printf("Enter stock name to search: ");
    scanf("%49s", searchName);

    StockItem item;
    int found = 0;

    while (fscanf(fp, "%49s %d %f", item.name, &item.quantity, &item.price) == 3) {
        if (strcmp(item.name, searchName) == 0) {
            printf("\nStock found:\nName: %s\nQuantity: %d\nPrice: %.2f\n", item.name, item.quantity, item.price);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Stock not found.\n");
    }

    fclose(fp);
}

void updateStock() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No stock data found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    char searchName[NAME_LEN];
    printf("Enter stock name to update quantity: ");
    scanf("%49s", searchName);

    int newQuantity;
    printf("Enter new quantity: ");
    scanf("%d", &newQuantity);

    StockItem item;
    int found = 0;

    while (fscanf(fp, "%49s %d %f", item.name, &item.quantity, &item.price) == 3) {
        if (strcmp(item.name, searchName) == 0) {
            item.quantity = newQuantity;
            found = 1;
        }
        fprintf(temp, "%s %d %.2f\n", item.name, item.quantity, item.price);
    }

    fclose(fp);
    fclose(temp);

    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    if (found)
        printf("Stock quantity updated.\n");
    else
        printf("Stock not found.\n");
}

void deleteStock() {
    FILE *fp = fopen(DATA_FILE, "r");
    if (!fp) {
        printf("No stock data found.\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    char deleteName[NAME_LEN];
    printf("Enter stock name to delete: ");
    scanf("%49s", deleteName);

    StockItem item;
    int found = 0;

    while (fscanf(fp, "%49s %d %f", item.name, &item.quantity, &item.price) == 3) {
        if (strcmp(item.name, deleteName) != 0) {
            fprintf(temp, "%s %d %.2f\n", item.name, item.quantity, item.price);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(DATA_FILE);
    rename("temp.txt", DATA_FILE);

    if (found)
        printf("Stock deleted successfully.\n");
    else
        printf("Stock not found.\n");
}

int main() {
    int choice;

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch(choice) {
            case 1: addStock(); break;
            case 2: viewStock(); break;
            case 3: searchStock(); break;
            case 4: updateStock(); break;
            case 5: deleteStock(); break;
            case 6: printf("Exiting program.\n"); exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
