#include <ifstream>
#include <iostream>
#include <string>

#using matrix = std::vector<vector<int>>;

// function reading input file
int read_file (const std::string& file_name) { // "const std::string&" gets original file variable w/o modifying it or making a copy of it
	
	/* Opening file: */
	std::ifstream input_file(file_name); // make file object
	
	if (!input_file) { // check if file exists and can be opened
		std::cerr << "File does not exist or cannot be opened" << std::endl; // print file error
		return 1; // return 1 for error
	}

	/* Reading file: */
	// research vectors or 2D arrays as a means to store matrix data

	while (std::getline(input_file, line))

	inputFile.close(); // close file read stream	
		
	return 0; // returned successfully
}

int main() {
	// prompt user for input file
	std::cout << "Enter input filename: ";	
	
	// initialize file name
	std::string user_file;

	// scan/read input
	std::cin >> user_file;
	std::cout << std::endl; 
	
	read_file(user_file);
	return 0;
}
