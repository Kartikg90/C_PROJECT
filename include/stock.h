#ifndef STOCK_H
#define STOCK_H

#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
    int quantity;
    float price;
} StockItem;

void showMenu();
void addStock();
void viewStock();
void searchStock();
void updateStock();
void deleteStock();

#endif
