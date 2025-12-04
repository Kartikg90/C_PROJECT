#ifndef STOCK_MANAGER_H
#define STOCK_MANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_STOCKS     1000
#define MAX_NAME       50
#define MAX_NOTES      100
#define PASSWORD_FILE  "password.txt"
#define DATA_FILE      "portfolio.dat"
#define BACKUP_FILE    "portfolio_backup.dat"

typedef struct {
    char symbol[MAX_NAME];
    char company[MAX_NAME];
    int shares;
    double buy_price;
    int buy_date;
    double target_price;
    char notes[MAX_NOTES];
} Stock;

typedef struct {
    Stock stocks[MAX_STOCKS];
    int count;
    double total_invested;
    double total_shares;
} Portfolio;

void clear_buffer(void);
int authenticate(void);
void load_password(char *pass);
void save_password(const char *pass);
void change_password(void);
void load_portfolio(void);
void save_portfolio(void);
void show_welcome(void);
void show_menu(void);
int get_date(void);
double get_price(void);
int get_shares(void);
void validate_stock(Stock *s);
void add_stock(void);
void view_portfolio(void);
void portfolio_analytics(void);
void search_stock(void);
void update_stock(void);
void sell_shares(void);
void delete_stock(void);
void low_risk_alerts(void);
void export_csv(void);

extern Portfolio portfolio;
extern char current_password[50];

#endif
