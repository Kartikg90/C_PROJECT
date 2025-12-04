# 🌟 Stock Manager 

**Advanced C Portfolio Management System**  
Track stocks, analyze investments, manage risks, and export data - all in one secure console app!

## ✨ Features

- 🔐 Password protection with change option
- ➕ Add stocks with symbol, company, shares, price, date, target & notes
- 👁️ View full portfolio table with totals
- 📊 Analytics: Best/worst stocks, avg price, total invested
- 🔍 Search stocks by symbol
- ✏️ Update shares quantity
- 💸 Sell shares (reduce holdings)
- 🗑️ Delete stocks completely
- 🚨 Risk alerts for stocks >40% allocation
- 📤 Export to CSV file
- 💾 Auto-save + backup system
- 📂 Supports up to 1000 stocks

## 🛠️ Tech Stack

- **Language**: C (ANSI C99)
- **Data Storage**: Binary files (`portfolio.dat` + backup)
- **CSV Export**: `portfolio.csv`
- **Password**: `password.txt` (default: `stock123`)


## 🎮 Demo Usage

🌟 WELCOME TO STOCK MANAGER v5.0 🌟
	1.	Login → Enter “stock123”
	2.	Add RELIANCE: 100 shares @ ₹2500
	3.	View portfolio → See table
	4.	Analytics → Best/worst performance
	5.	Export → Get portfolio.csv
  
## 📊 Sample Output

📈 PORTFOLIO (2 stocks) 
SYMBOL   COMPANY             SHARES AVG.PP    VALUE 
────────────────────────────────────────────── 
RELIANCE Reliance Ind.          100  ₹2500.00 ₹250000.00 
TCS      TCS Ltd                50  ₹3500.00 ₹175000.00 
────────────────────────────────────────────── 
TOTAL: 150 shares | ₹425000.00


## 🔒 Security

- Hidden password input (****)
- File-based password storage
- Data encryption: None (future feature)

## ⚠️ Limitations

- Max 1000 stocks
- No live prices (manual entry)
- Console-only (no GUI)
- Binary data (not human-readable)

## 🛠️ Build Requirements

- GCC compiler
- Standard C library
- Linux/Mac/Windows (tested on Ubuntu)

## 🤝 Contributing

1. Fork repository
2. Create feature branch
3. Add features (live prices? GUI?)
4. Test thoroughly
5. Submit PR



## 👨‍💼 Author

**Kartik Gupta**  
B.Tech CSE Student | UPES Dehradun  

---

⭐ **Star if useful!** Happy Investing! 🚀

