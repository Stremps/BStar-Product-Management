# B-Star Tree Product Management System

## Description
This repository contains a product management system implemented using a B* tree for efficient data indexing and binary files for persistent storage. Developed for the Data Structures II course at UNIOESTE, this project aims to handle large volumes of product data efficiently.

## Features
The system supports various functionalities crucial for product management in high-volume settings:
- **Insert Product**: Adds new products to the system with complete details.
- **Delete Product**: Removes products from the system by their unique identifiers.
- **Search Product**: Searches for products using different criteria.
- **Update Product**: Updates details of existing products.
- **List Products**: Lists all products in an ordered manner through B* tree traversal.
- **Visualize Tree Structure**: Provides a visual representation of the B* tree to understand its layout and node distribution.

### Technical Details
- **Implementation**: Written in C.
- **Data Structure**: B* Tree.
- **Storage Mechanism**: Binary files, incorporating complex tree node management for reusability and efficiency.

## Known Issues
- **Code Complexity**: Due to the advanced data structure used, the current implementation has some issues that need debugging.
- **Documentation**: The documentation is sparse and needs to be improved to better explain the functions and design decisions.

## Future Improvements
- **Code Optimization**: Plans to refactor code for better efficiency and readability.
- **Enhanced Documentation**: Comprehensive documentation will be added to explain all operational details and data structure nuances.

## How to Use
### Compilation and Execution
Compile and run the application using:
```bash
gcc -o bStarManager *.c
./bStarManager
