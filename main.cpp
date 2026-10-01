#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

using matrix = std::vector<std::vector<int> >;

/* Reads file to check for errors w/ file, N, or matrices */
int read_file (const std::string &file_name, int &N, matrix &a, matrix &b) { // "const std::string&" gets original file variable w/o modifying it or making a copy of it
	
	/* Opening file: */
	std::fstream input_file(file_name); // make file object
	
	if (!input_file) { // check if file exists and can be opened
		std::cerr << "File does not exist or cannot be opened" << std::endl; // print file error
		return 1; // return 1 for error
	}

	/* Reading file: */
	if (!(input_file >> N) || N <= 0) { // checks if first line, N, isn't an int, is empty, or is less than 0
		std::cerr << "Insufficient file size provided.\n" << std::endl; // print file error
		return 1; // return 1 for error
	}

	a.assign(N, std::vector<int>(N)); // resize matrix a to N rows of N zeroes
	b.assign(N, std::vector<int>(N)); // resize matrix b to N rows of N zeroes

	// iterate through matrix a 
	for (int i = 0; i < N; i++) { // iterate thru rows
        for (int j = 0; j < N; j++) { // iterate thru columns
            if (!(input_file >> a[i][j])) { // read thru values; fail if file runs out early
                std::cerr << "File does not contain enough data for Matrix A.\n" << std::endl;
                return 1; // return 1 for error
       	    }
		}
	}
	// iterate through matrix b
	for (int i = 0; i < N; i++) { // iterate thru rows
        for (int j = 0; j < N; j++) { // iterate thru columns
            if (!(input_file >> b[i][j])) { // read thru values; fail if file runs out early
                std::cerr << "File does not contain enough data for Matrix B.\n" << std::endl;
                return 1; // return 1 for error
       	    }
		}
	}

	input_file.close(); // close file read stream	
		
	return 0; // returned successfully w/o file or matrix reading errors
}

/* Prints a matrix w/ a name, right-aligned columns via std::setw() */
void print_matrix(const std::string &name, const matrix &m) {
	std::cout << name << ":\n"; 			  // print the matrix name
	for (const auto &row : m) {				  // walk thru each row
		for (int val : row) {				  // walk thru each value in row
			std::cout << std::setw(5) << val; // print value w/ right-align of 5
		}
		std::cout << "\n";					  // end each row w/ newline
	}
}


matrix add_matrices(const matrix &a, const matrix &b) {
    int N = static_cast<int>(a.size());          // matrix dimension, taken from matrix a
    matrix result(N, std::vector<int>(N, 0));    // result matrix, pre-filled with zeros
 
    for (int i = 0; i < N; i++)                  // loop over rows
        for (int j = 0; j < N; j++)              // loop over columns
            result[i][j] = a[i][j] + b[i][j];    // add corresponding elements
 
    return result;                               // hand back the sum matrix
}

/* Multiply two matrices */
matrix multiply_matrices(const matrix &a, const matrix &b) {
    int N = static_cast<int>(a.size());            // matrix dimension, taken from matrix a since len(a) = len(b)
    matrix result(N, std::vector<int>(N, 0));      // result matrix, pre-filled w/ zeros
 
    for (int i = 0; i < N; i++)                    // loop over result rows
        for (int j = 0; j < N; j++)                // loop over result columns
            for (int k = 0; k < N; k++)            // loop over the shared inner dimension
                result[i][j] += a[i][k] * b[k][j]; // accumulate the dot-product term
 
    return result;                                 // return product matrix
}
 
/* Sum diagonal values */
void diagonal_sums(const matrix &m, long &mainSum, long &secondarySum) { // long types used for large nums
    int N = static_cast<int>(m.size());          // matrix size
    mainSum = 0;                                 // start the main-diagonal total at zero
    secondarySum = 0;                            // start the secondary-diagonal total at zero
 
    for (int i = 0; i < N; i++) {                // walk down the diagonal, one row at a time
        mainSum += m[i][i];                      // add main-diagonal element (top-left to bottom-right)
        secondarySum += m[i][N - 1 - i];         // add secondary-diagonal element (top-right to bottom-left)
    }
}
 
/* Swaps matrix rows from user-provided numbers */
matrix swap_rows(const matrix &m, int row1, int row2) {
    int N = static_cast<int>(m.size());          // matrix dimension
    matrix result = m;                           // start from a copy so the original is untouched
 
    if (row1 < 0 || row1 >= N || row2 < 0 || row2 >= N) { // validate both row indices
        std::cout << "Invalid row indices for swap.\n";   // report the bad input
        return result;                           // return the unmodified copy
    }
 
    std::swap(result[row1], result[row2]);       // swap the two entire row vectors
    return result;                               // hand back the modified copy
}
 
/* Swaps matrix columns from user-provided numbers */
matrix swap_columns(const matrix &m, int col1, int col2) {
    int N = static_cast<int>(m.size());          // matrix dimension
    matrix result = m;                           // start from a copy so the original is untouched
 
    if (col1 < 0 || col1 >= N || col2 < 0 || col2 >= N) { // validate both column indices
        std::cout << "Invalid column indices for swap.\n"; // report the bad input
        return result;                           // return the unmodified copy
    }
 
    for (int i = 0; i < N; i++)                  // visit every row
        std::swap(result[i][col1], result[i][col2]); // swap the two column entries in that row
 
    return result;                               // hand back the modified copy
}

/* Updates value at user-provided matrix row and column */
matrix update_element(const matrix &m, int row, int col, int newValue) {
    int N = static_cast<int>(m.size());          // matrix dimension
    matrix result = m;                           // start from a copy so the original is untouched
 
    if (row < 0 || row >= N || col < 0 || col >= N) { // validate both indices
        std::cout << "Invalid indices for update.\n";    // report the bad input
        return result;                           // return the unmodified copy
    }
 
    result[row][col] = newValue;                 // overwrite the single target element
    return result;                               // hand back the modified copy
}
/* Main function */
int main() {
	int N; // will hold matrix size read from file
	matrix a, b; // will hold matrices read from file

	
	std::cout << "Enter input filename: "; // prompt user for input file
	
	
	std::string user_file; // initialize file name

	// scan/read input
	std::cin >> user_file;
	std::cout << std::endl; 
	
	if (read_file(user_file, N, a, b)) { // check for file reading errors
		return 1; // return 1 for errors
	}

	print_matrix("Matrix A", a);                  // print the loaded matrix a
    std::cout << "\n";
    print_matrix("Matrix B", b);                  // print the loaded matrix b
    std::cout << "\n";
 
    matrix sum = add_matrices(a, b);              // compute a + b
    print_matrix("A + B", sum);                   // display the sum
    std::cout << "\n";                           // blank line for readability
 
    matrix product = multiply_matrices(a, b);     // compute a * b
    print_matrix("A * B", product);               // display the product
    std::cout << "\n";                           // blank line for readability
 
    long mainSum, secondarySum;                  // will hold the two diagonal totals
    diagonal_sums(a, mainSum, secondarySum);      // compute both diagonal sums for matrix a
    std::cout << "Diagonal sums for Matrix A:\n";       // heading for the diagonal results
    std::cout << "Main diagonal sum: " << mainSum << "\n";             // print the main diagonal sum
    std::cout << "Secondary diagonal sum: " << secondarySum << "\n\n"; // print the secondary diagonal sum
 
    matrix rowSwapped = swap_rows(a, 0, 2);       // swap rows 0 and 2 of a copy of matrix a
    print_matrix("Problem 5 - Rows 0 and 2 swapped", rowSwapped); // display, width sized to its own values
    std::cout << "\n";                           // blank line for readability
 
    matrix colSwapped = swap_columns(a, 0, 2);    // swap columns 0 and 2 of a copy of matrix a
    print_matrix("Problem 6 - Columns 0 and 2 swapped", colSwapped); // display, width sized to its own values
    std::cout << "\n";                           // blank line for readability
 
    matrix updated = update_element(a, 1, 2, 99); // set element (row 1, col 2) to 99 on a copy of matrix a
    print_matrix("Problem 7 - Updated matrix", updated); // display, width sized to its own values

	return 0;
}