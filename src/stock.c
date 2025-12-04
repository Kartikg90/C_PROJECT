#include "../include/stock.h"

Portfolio portfolio = {0};
char current_password[50] = "stock123";

int main() {
    show_welcome();
    
    int auth_choice;
    printf("\n🔐 OPTIONS:\n");
    printf("1. Login\n");
    printf("2. Change Password\n");
    printf("Enter choice: ");
    scanf("%d", &auth_choice);
    clear_buffer();
    
    if (auth_choice == 2) {
        change_password();
        printf("\n💾 Password changed! Please login with new password.\n");
    }
    
    if (!authenticate()) {
        printf("❌ Access Denied! Exiting...\n");
        return 1;
    }
    
    load_portfolio();
    printf("\n✅ Login successful! Portfolio loaded.\n");
    
    int choice;
    while (1) {
        show_menu();
        if (scanf("%d", &choice) != 1) {
            printf("❌ Invalid input!\n");
            clear_buffer();
            continue;
        }
        clear_buffer();
        
        switch (choice) {
            case 1:  add_stock(); break;
            case 2:  view_portfolio(); break;
            case 3:  portfolio_analytics(); break;
            case 4:  search_stock(); break;
            case 5:  update_stock(); break;
            case 6:  sell_shares(); break;
            case 7:  delete_stock(); break;
            case 8:  low_risk_alerts(); break;
            case 9:  export_csv(); break;
            case 10: change_password(); break;
            case 11: 
                save_portfolio(); 
                printf("💾 Saved & Exiting. Happy Investing!\n"); 
                return 0;
            default: printf("⚠️  Choice 1-11 only!\n");
        }
        printf("\n⏸️  Press Enter...");
        getchar();
    }
    return 0;
}

void show_welcome(void) {
    printf("\n🌟 WELCOME TO STOCK MANAGER v5.0 🌟\n");
    printf("Advanced Portfolio Management System\n");
    printf("====================================\n");
}

void load_password(char *pass) {
    FILE *fp = fopen(PASSWORD_FILE, "r");
    if (fp) {
        fscanf(fp, "%49s", pass);
        fclose(fp);
    }
}

void save_password(const char *pass) {
    FILE *fp = fopen(PASSWORD_FILE, "w");
    if (fp) {
        fprintf(fp, "%s", pass);
        fclose(fp);
    }
}

void change_password(void) {
    printf("\n🔑 CHANGE PASSWORD\n");
    printf("═════════════════════\n");
    
    char old_pass[50], new_pass[50], confirm_pass[50], ch;
    int i;
    
    printf("Enter current password: ");
    i = 0;
    while ((ch = getchar()) != '\n') {
        if (i < 49) {
            old_pass[i++] = ch;
            printf("*");
        }
    }
    old_pass[i] = '\0';
    
    load_password(current_password);
    if (strcmp(old_pass, current_password) != 0) {
        printf("\n❌ Wrong password!\n");
        return;
    }
    
    printf("\nEnter new password: ");
    i = 0;
    while ((ch = getchar()) != '\n') {
        if (i < 49) {
            new_pass[i++] = ch;
            printf("*");
        }
    }
    new_pass[i] = '\0';
    
    printf("\nConfirm new password: ");
    i = 0;
    while ((ch = getchar()) != '\n') {
        if (i < 49) {
            confirm_pass[i++] = ch;
            printf("*");
        }
    }
    confirm_pass[i] = '\0';
    
    if (strcmp(new_pass, confirm_pass) != 0) {
        printf("\n❌ Passwords don't match!\n");
        return;
    }
    
    if (strlen(new_pass) < 6) {
        printf("\n⚠️  Password too short (min 6 chars)!\n");
        return;
    }
    
    save_password(new_pass);
    strcpy(current_password, new_pass);
    printf("\n✅ Password changed!\n");
}

int authenticate(void) {
    char pass[50], ch;
    int i = 0;
    
    load_password(current_password);
    printf("\n🔐 Enter Password: ");
    while ((ch = getchar()) != '\n') {
        if (i < 49) {
            pass[i++] = ch;
            printf("*");
        }
    }
    pass[i] = '\0';
    printf("\n");
    
    return strcmp(pass, current_password) == 0;
}

void load_portfolio(void) {
    FILE *fp = fopen(DATA_FILE, "rb");
    if (!fp) {
        printf("📂 New portfolio created.\n");
        return;
    }
    fread(&portfolio, sizeof(Portfolio), 1, fp);
    fclose(fp);
    
    if (portfolio.count > MAX_STOCKS) {
        portfolio.count = MAX_STOCKS;
        printf("⚠️  Portfolio truncated.\n");
    }
    printf("✅ Loaded %d stocks (₹%.2f)\n", portfolio.count, portfolio.total_invested);
}

void save_portfolio(void) {
    FILE *backup = fopen(BACKUP_FILE, "wb");
    if (backup) {
        fwrite(&portfolio, sizeof(Portfolio), 1, backup);
        fclose(backup);
    }
    
    FILE *fp = fopen(DATA_FILE, "wb");
    if (!fp) {
        printf("❌ Save failed!\n");
        return;
    }
    fwrite(&portfolio, sizeof(Portfolio), 1, fp);
    fclose(fp);
    printf("💾 Saved + backup created!\n");
}

void clear_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int get_date(void) {
    int date;
    printf("📅 Date (YYYYMMDD): ");
    scanf("%d", &date);
    clear_buffer();
    int year = date / 10000;
    if (year < 2020 || year > 2030) {
        printf("⚠️  Using today.\n");
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        return (tm->tm_year + 1900) * 10000 + (tm->tm_mon + 1) * 100 + tm->tm_mday;
    }
    return date;
}

double get_price(void) {
    double price;
    printf("💰 Price (₹): ");
    scanf("%lf", &price);
    clear_buffer();
    return price > 0 ? price : 100.0;
}

int get_shares(void) {
    int shares;
    printf("📊 Shares: ");
    scanf("%d", &shares);
    clear_buffer();
    return shares > 0 ? shares : 100;
}

void validate_stock(Stock *s) {
    for (int i = 0; s->symbol[i]; i++) {
        s->symbol[i] = toupper(s->symbol[i]);
        if (!isalnum(s->symbol[i]) && s->symbol[i] != '.') 
            s->symbol[i] = '_';
    }
}

void add_stock(void) {
    if (portfolio.count >= MAX_STOCKS) {
        printf("❌ Portfolio full!\n");
        return;
    }
    Stock *s = &portfolio.stocks[portfolio.count];
    printf("\n➕ ADD STOCK\n");
    printf("Symbol: "); scanf("%49s", s->symbol); clear_buffer(); validate_stock(s);
    printf("Company: "); scanf("%49[^\n]", s->company); clear_buffer();
    s->shares = get_shares();
    s->buy_price = get_price();
    s->buy_date = get_date();
    printf("Target Price: "); scanf("%lf", &s->target_price); clear_buffer();
    if (s->target_price <= 0) s->target_price = s->buy_price * 1.2;
    printf("Notes: "); scanf("%99[^\n]", s->notes); clear_buffer();
    
    portfolio.total_invested += s->shares * s->buy_price;
    portfolio.total_shares += s->shares;
    portfolio.count++;
    printf("✅ %s added! ₹%.2f\n", s->symbol, s->shares * s->buy_price);
}

void view_portfolio(void) {
    if (!portfolio.count) {
        printf("📭 Empty portfolio.\n");
        return;
    }
    printf("\n📈 PORTFOLIO (%d stocks)\n", portfolio.count);
    printf("%-8s %-20s %6s %8s %10s\n", "SYMBOL", "COMPANY", "SHARES", "AVG.PP", "VALUE");
    printf("──────────────────────────────────────────────\n");
    for (int i = 0; i < portfolio.count; i++) {
        Stock *s = &portfolio.stocks[i];
        double value = s->shares * s->buy_price;
        printf("%-8s %-20s %6d ₹%7.2f ₹%9.2f\n", s->symbol, s->company, s->shares, s->buy_price, value);
    }
    printf("──────────────────────────────────────────────\n");
    printf("TOTAL: %d shares | ₹%.2f\n", (int)portfolio.total_shares, portfolio.total_invested);
}

void portfolio_analytics(void) {
    if (!portfolio.count) {
        printf("📭 Empty portfolio.\n");
        return;
    }
    double max_gain = -999, min_gain = 999;
    Stock *best = NULL, *worst = NULL;
    for (int i = 0; i < portfolio.count; i++) {
        Stock *s = &portfolio.stocks[i];
        double gain = (s->target_price - s->buy_price) / s->buy_price * 100;
        if (gain > max_gain) { max_gain = gain; best = s; }
        if (gain < min_gain) { min_gain = gain; worst = s; }
    }
    printf("\n📊 ANALYTICS\n");
    printf("═══════════════════════\n");
    printf("Stocks: %d\n", portfolio.count);
    printf("Investment: ₹%.2f\n", portfolio.total_invested);
    printf("Avg Price: ₹%.2f\n", portfolio.total_invested / portfolio.total_shares);
    printf("Best: %s (+%.1f%%)\n", best->symbol, max_gain);
    printf("Worst: %s (%.1f%%)\n", worst->symbol, min_gain);
    printf("═══════════════════════\n");
}

void search_stock(void) {
    char symbol[MAX_NAME];
    printf("🔍 Symbol: "); scanf("%49s", symbol); clear_buffer();
    for (int i = 0; symbol[i]; i++) symbol[i] = toupper(symbol[i]);
    int found = 0;
    for (int i = 0; i < portfolio.count; i++) {
        if (strstr(portfolio.stocks[i].symbol, symbol)) {
            Stock *s = &portfolio.stocks[i];
            printf("\n✅ %s | %s | %d shares | ₹%.2f\n", s->symbol, s->company, s->shares, s->buy_price);
            found = 1;
        }
    }
    if (!found) printf("❌ Not found!\n");
}

void update_stock(void) {
    char symbol[MAX_NAME];
    printf("Symbol: "); scanf("%49s", symbol); clear_buffer();
    for (int i = 0; i < portfolio.count; i++) {
        if (strcmp(portfolio.stocks[i].symbol, symbol) == 0) {
            Stock *s = &portfolio.stocks[i];
            printf("Current: %d shares\n", s->shares);
            printf("New shares: "); int new_shares; scanf("%d", &new_shares); clear_buffer();
            portfolio.total_invested += (new_shares - s->shares) * s->buy_price;
            portfolio.total_shares += (new_shares - s->shares);
            s->shares = new_shares;
            printf("✅ Updated!\n");
            return;
        }
    }
    printf("❌ Not found!\n");
}

void sell_shares(void) {
    char symbol[MAX_NAME];
    printf("Symbol: "); scanf("%49s", symbol); clear_buffer();
    for (int i = 0; i < portfolio.count; i++) {
        if (strcmp(portfolio.stocks[i].symbol, symbol) == 0) {
            Stock *s = &portfolio.stocks[i];
            printf("Current: %d\n", s->shares);
            int sell; printf("Sell: "); scanf("%d", &sell); clear_buffer();
            if (sell <= s->shares && sell > 0) {
                s->shares -= sell;
                portfolio.total_invested -= sell * s->buy_price;
                portfolio.total_shares -= sell;
                printf("✅ Sold %d shares\n", sell);
            } else {
                printf("❌ Invalid!\n");
            }
            return;
        }
    }
    printf("❌ Not found!\n");
}

void delete_stock(void) {
    char symbol[MAX_NAME];
    printf("Symbol: "); scanf("%49s", symbol); clear_buffer();
    for (int i = 0; i < portfolio.count; i++) {
        if (strcmp(portfolio.stocks[i].symbol, symbol) == 0) {
            portfolio.total_invested -= portfolio.stocks[i].shares * portfolio.stocks[i].buy_price;
            portfolio.total_shares -= portfolio.stocks[i].shares;
            for (int j = i; j < portfolio.count - 1; j++) {
                portfolio.stocks[j] = portfolio.stocks[j + 1];
            }
            portfolio.count--;
            printf("🗑️ Deleted!\n");
            return;
        }
    }
    printf("❌ Not found!\n");
}

void low_risk_alerts(void) {
    if (!portfolio.count || portfolio.total_invested == 0) {
        printf("📭 No data.\n");
        return;
    }
    printf("\n🚨 RISK ALERTS (Threshold: >40%%)\n");
    int alerts = 0;
    for (int i = 0; i < portfolio.count; i++) {
        Stock *s = &portfolio.stocks[i];
        double allocation = (s->shares * s->buy_price) / portfolio.total_invested * 100;
        if (allocation > 40) {  // CHANGED: 25% → 40%
            printf("⚠️  %s: %.1f%% (HIGH RISK - Over 40%%)\n", s->symbol, allocation);
            alerts++;
        }
    }
    if (!alerts) printf("✅ Portfolio balanced! No stock exceeds 40%%.\n");
}

void export_csv(void) {
    FILE *csv = fopen("portfolio.csv", "w");
    if (!csv) {
        printf("❌ Export failed!\n");
        return;
    }
    fprintf(csv, "Symbol,Company,Shares,AvgPrice,Value,Target\n");
    for (int i = 0; i < portfolio.count; i++) {
        Stock *s = &portfolio.stocks[i];
        fprintf(csv, "%s,%s,%d,%.2f,%.2f,%.2f\n", s->symbol, s->company, s->shares,
                s->buy_price, s->shares * s->buy_price, s->target_price);
    }
    fclose(csv);
    printf("📤 portfolio.csv created!\n");
}

void show_menu(void) {
    printf("\n📋 MAIN MENU\n");
    printf("═══════════════════════════════════════\n");
    printf("1.  ➕ Add Stock      7.  🗑️  Delete\n");
    printf("2.  👁️  View         8.  🚨 Alerts\n");
    printf("3.  📊 Analytics     9.  📤 Export\n");
    printf("4.  🔍 Search       10. 🔑 Password\n");
    printf("5.  ✏️  Update      11. 💾 Exit\n");
    printf("6.  💸 Sell Shares\n");
    printf("═══════════════════════════════════════\n");
    printf("Choice: ");
}
