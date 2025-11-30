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
├── src/ 
│    ├── main.c              - Main program entry point 
│    ├── stock.c             - Core inventory functions 
│    ├── input_validation.c  - Input validation functions 
│    └── file_operations.c   - File I/O functions 
├── include/ 
│    ├── stock.h             - Stock management header 
│    ├── input_validation.h  - Validation header 
│    └── file_operations.h   - File operations header 
└── README.md                - This file

