# Stock Management System

## Description
This is a simple C project to manage stock records.  
Each stock has:
- Name (string)  
- Quantity (integer)  
- Purchase price (float)  

The program lets you:
- Add stock  
- View all stocks  
- Search stock by name  
- Update quantity of a stock  
- Delete a stock by name  

The stock records are saved in a text file `stock_data.txt`.

## Project structure  
- `src/stock.c` - main program source code  
- `include/stock.h` - header file with struct and function declarations  
- `docs/` - project report folder  
- `README.md` - this file  

## How to compile and run

gcc src/stock.c -Iinclude -o stock_app ./stock_app

## Notes
- Stock name should be a single word (no spaces).  
- Quantity must be an integer.  
- Price is the purchase price per stock item.

This project follows the basic project guidelines for C programming.
