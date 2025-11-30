# C_PROJECT
# Stock Management System

## Overview
A comprehensive C program for managing product inventory with add, delete, search, and update functionalities. This project demonstrates core C programming concepts including dynamic memory allocation, file I/O, and modular design.

## Features
- **Add Product**: Add new products with ID, name, quantity, and price
- **Display Inventory**: View all products in a formatted table
- **Search Product**: Find products by ID
- **Update Quantity**: Buy (add) or sell (remove) products from stock
- **Delete Product**: Remove products with confirmation
- **Persistent Storage**: Save/load inventory from file
- **Input Validation**: Robust error handling for user inputs

## Project Structure
-├── src/ 
-│    ├── main.c              - Main program entry point 
-│    ├── stock.c             - Core inventory functions 
-│    ├── input_validation.c  - Input validation functions 
-│    └── file_operations.c   - File I/O functions 
-│
-├── include/ 
-│    ├── stock.h             - Stock management header 
-│    ├── input_validation.h  - Validation header 
-│    └── file_operations.h   - File operations header 
-│
-└── README.md                - This file

## Compilation

### Using GCC directly:
gcc -o stock_management src/main.c src/stock.c src/input_validation.c src/file_operations.c -I./include

### Run the program:
./stock_management

## Usage Example

Welcome to Stock Management System
	1.	Add Product
	2.	Display All Products
	3.	Search Product
	4.	Update Quantity
	5.	Delete Product
	6.	Exit
Enter choice: 1 Enter Product ID: 101 Enter Product Name: Laptop Enter Initial Quantity: 5 Enter Price per Unit: 50000.00 ✓ Product added successfully!

## Data Structure
typedef struct { int product_id;        // Unique identifier char product_name; // Product name int quantity;          // Stock quantity float price;           // Unit price time_t last_updated;   // Last modification time } Stock;


## Key Functions

| Function | Purpose |
|----------|---------|
| `add_product()` | Add new product to inventory |
| `display_stock()` | Display all products |
| `search_product()` | Find product by ID |
| `update_quantity()` | Buy or sell products |
| `delete_product()` | Remove product |
| `save_to_file()` | Save inventory to file |
| `load_from_file()` | Load inventory from file |
| `validate_integer()` | Validate integer input |
| `validate_string()` | Validate string input |

## Concepts Used
- Dynamic memory allocation (`malloc`, `realloc`)
- Dynamic arrays
- File I/O (binary mode)
- Structures
- Modular programming with header files
- Input validation and error handling
- Timestamps (`time.h`)

## Testing
Test the program with various inputs:
- Add multiple products
- Search for products
- Update quantities
- Delete products
- Restart program to verify data persistence

## Future Enhancements
- Database integration
- GUI interface
- Advanced reporting
- User authentication
- Batch operations

## Author
[Your Name]

## Institution
UPES Dehradun - B.Tech CSE (AI/ML)

## Course
Programming in C (CSEG1032)


