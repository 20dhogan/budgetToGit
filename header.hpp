#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

std::vector<double> readFile(const std::string& filename, size_t vector_size) {
	std::vector<double> result(vector_size, 0);
	double value = 0;
	std::string line;
	std::ifstream file(filename);

	if (file.is_open()) {
		int i = 0;
		while (getline(file, line)) {
			std::stringstream ss(line);
			std::string label;
			double total = 0;
			std::getline(ss, label, ':');

			while (ss >> value) {
				total += value;
			}

			result[i] = total;
			i++;
		}
		file.close();
	}
	else {
		std::cout << "Unable to open file " << filename << std::endl;
	}

	return result;
}

void printGoal(double goal, double actual, const std::string& type) {
	std::ofstream output("output.txt", std::ios_base::app); //this opens the file in append mode so it won't write over itself
	if (output.is_open()) {
		double diff = actual - goal;
		output << type << "  $" << std::setw(8) << std::left << std::fixed <<
			std::setprecision(2) << goal << "      $" << std::setw(8) <<
			std::left << actual << "        $" << std::setw(8)
			<< std::left << diff;
		if (diff > 0) {
			output << "        !";
		}
		output << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printCompare(double TM, double LM, const std::string& type) {
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		double diff = TM - LM;
		output << type << "   $" << std::setw(8) << std::fixed << std::setprecision(2) <<
			std::left << TM << "               $" << std::setw(8) << std::left << diff;
		if (type == "NET-BALANCE: ") {
			if (diff < 0) {
				output << "               !";
			}
		}
		else {
			if (diff > 0) {
				output << "               !";
			}
		}
		output << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printTitle(int month, int year) {
	std::string monthStr;
	switch (month) {
	case 1: monthStr = "** JANUARY "; break;
	case 2: monthStr = "* FEBRUARY "; break;
	case 3: monthStr = "**** MARCH "; break;
	case 4: monthStr = "**** APRIL "; break;
	case 5: monthStr = "****** MAY "; break;
	case 6: monthStr = "***** JUNE "; break;
	case 7: monthStr = "***** JULY "; break;
	case 8: monthStr = "*** AUGUST "; break;
	case 9: monthStr = " SEPTEMBER "; break;
	case 10: monthStr = "** OCTOBER "; break;
	case 11: monthStr = "* NOVEMBER "; break;
	case 12: monthStr = "* DECEMBER "; break;
	default: monthStr = "INVALID MONTH"; break;
	}
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << "***************************" << monthStr << year << " ***************************" << std::endl << std::endl;
		output << "               GOAL            MARK            DIFF. FROM GOAL" << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printDash() {
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << "----------------------------------------------------------------------" << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printStar() {
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << std::endl;
		output << "**********************************************************************" << std::endl;
		output << "**********************************************************************" << std::endl;
		output << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printHash() {
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << std::endl;
		output << "#######################################################################" << std::endl;
		output << "#######################################################################" << std::endl;
		output << "#######################################################################" << std::endl;
		output << std::endl << std::endl << std::endl << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printMonthsToSurvive(double time) {
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << "You can survive " << std::setprecision(2) << time << " months off of savings at this rate." << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
}

void printScreen() {
	std::ifstream inputFile("output.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Unable to open output.txt" << std::endl;
		return;
	}

	// Read all lines into a vector
	std::vector<std::string> lines;
	std::string line;
	while (getline(inputFile, line)) {
		lines.push_back(line);
	}
	inputFile.close();

	// Determine the starting index for the last 52 lines
	size_t start = lines.size() > 54 ? lines.size() - 54 : 0;

	// Print the last 52 lines
	for (size_t i = start; i < lines.size(); ++i) {
		std::cout << lines[i] << std::endl;
	}
}
#endif
