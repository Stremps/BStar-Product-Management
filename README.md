# B-Star Tree Indexed Product Management System

## Description
This repository hosts the implementation of a product management system designed to handle large-scale inventory using a B* tree for indexing and binary files for persistent data storage. Developed for the Data Structures II course at UNIOESTE, this complex system is tailored for managing extensive product catalogs in a highly efficient manner.

## Features
The system allows for various operations to manage a product catalog effectively:
- **Add Product**: Insert new product details into the system.
- **Remove Product**: Delete a product from the catalog using its unique product code.
- **Update Product**: Modify existing product details, such as price and stock.
- **Search Product**: Retrieve product information using its code.
- **List All Products**: Display an in-order traversal of the B* tree, listing product codes and names.
- **Visualize Tree Structure**: Graphically represent the B* tree structure to visualize node organization.
- **Batch Operations**: Execute multiple operations like insertions, deletions, and modifications from a batch file.

### Technical Details
- **Implementation**: The system is implemented in C programming language.
- **Data Structures**: Utilizes a B* tree for efficient indexing.
- **Storage**: Uses binary files to store product data and index information, maintaining data integrity and operational efficiency.

## Known Issues
- **Code Complexity**: The current implementation, due to its complex nature, has some unresolved issues that may affect performance and stability.
- **Documentation**: Documentation is currently minimal and will be expanded in future updates to better describe the system's functionality and architecture.

## Future Enhancements
- **Code Refinement**: Plans include refactoring the code to enhance readability and efficiency.
- **Documentation Improvement**: Comprehensive documentation will be developed to thoroughly explain the use and structure of the B* tree and its integration into the system.

## How to Use
### Compilation and Execution
To compile and run the program:
```bash
gcc -o productSystem *.c
./productSystem
