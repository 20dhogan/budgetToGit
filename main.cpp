#include "header.hpp"

int main() {
	// Read input file
	size_t input_size = 25;
	std::vector<double> input = readFile("input.txt", input_size);

	// Read memory file
	size_t memory_size = 12;
	std::vector<double> memory = readFile("memory.txt", memory_size);

	//declare variables. LM stands for last month, TM stands for this month
	int month = static_cast<int>(std::round(input[0]));
	int year = static_cast<int>(std::round(input[1]));
	double netTM = input[3] + input[4] - input[5] - input[6] - input[8];
	double naturalGasTM = input[7];
	double electricityTM = input[8];
	double schoolSuppliesTM = input[9];
	double groceryTM = input[11];
	double giftTM = input[14];
	double carGasTM = input[17];
	double funTM = input[20];
	double costToLiveTM = input[6] + input[7] + input[8] + input[9] + input[11] + input[14] + input[17] + input[20] + input[23] - input[24];

	double netLM = memory[0];
	double naturalGasLM = memory[1];
	double electricityLM = memory[2];
	double schoolSuppliesLM = memory[3];
	double groceryLM = memory[4];
	double giftLM = memory[5];
	double carGasLM = memory[6];
	double funLM = memory[7];
	int numberOfMonths = static_cast<int>(std::round(memory[8]));
	double costToLiveLM = memory[9];
	double avgCostToLive = memory[10];

	double newAvgCostToLive = ((avgCostToLive * numberOfMonths) + costToLiveTM) / (numberOfMonths + 1);
	numberOfMonths += 1;
	double monthsWeCanLive = netTM / newAvgCostToLive;

	//print title
	printTitle(month, year);
	printDash();

	//print goal
	printGoal(input[12], input[11], "GROCRIES:    ");
	printDash();
	printGoal(input[15], input[14], "GIFTS:       ");
	printDash();
	printGoal(input[18], input[17], "CAR GAS:     ");
	printDash();
	printGoal(input[21], input[20], "PERSONAL/FUN:");
	printStar();

	//print second header
	std::ofstream output("output.txt", std::ios_base::app); // Open file in append mode
	if (output.is_open()) {
		output << "                VALUE                   DIFF. TO LAST MONTH" << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
	printDash();

	//print comparison	
	printCompare(netTM, netLM, "NET-BALANCE: ");
	printDash();
	printCompare(naturalGasTM, naturalGasLM, "NATURAL GAS: ");
	printDash();
	printCompare(electricityTM, electricityLM, "ELECTRICITY: ");
	printDash();
	printCompare(schoolSuppliesTM, schoolSuppliesLM, "SCHOOL:      ");
	printDash();
	printCompare(groceryTM, groceryLM, "GROCERIES:   ");
	printDash();
	printCompare(giftTM, giftLM, "GIFTS:       ");
	printDash();
	printCompare(carGasTM, carGasLM, "CAR GAS:     ");
	printDash();
	printCompare(funTM, funLM, "PERSONAL/FUN:");
	printDash();

	//print monthly cost of living
	std::ofstream output1("output.txt", std::ios_base::app); // Open file in append mode
	if (output1.is_open()) {
		output1 << "MONTH COST" << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;

	printCompare(costToLiveTM, costToLiveLM, "OF LIVING:   ");

	//print avg. monthly cost to live
	printDash();
	std::ofstream output2("output.txt", std::ios_base::app); // Open file in append mode
	if (output2.is_open()) {
		output2 << "AVG. MONTHLY" << std::endl;
		output << "COST TO LIVE:" << "   $" << std::setw(8) << std::left << newAvgCostToLive << "                ******" << std::endl;
	}
	else std::cout << "couldn't open output file" << std::endl;
	printStar();

	//print the number of months we can survive if we only had our savings
	printMonthsToSurvive(monthsWeCanLive);
	printHash();

	//update memory file
	std::ofstream memoryfile_out("memory.txt");
	if (memoryfile_out.is_open())
	{
		memoryfile_out << "net balance: " << netTM << std::endl;
		memoryfile_out << "natural gas: " << naturalGasTM << std::endl;
		memoryfile_out << "electricity: " << electricityTM << std::endl;
		memoryfile_out << "school supplies: " << schoolSuppliesTM << std::endl;
		memoryfile_out << "groceries: " << groceryTM << std::endl;
		memoryfile_out << "gifts: " << giftTM << std::endl;
		memoryfile_out << "car gas: " << carGasTM << std::endl;
		memoryfile_out << "personal/fun: " << funTM << std::endl;
		memoryfile_out << "number of months: " << numberOfMonths << std::endl;
		memoryfile_out << "last month cost of living: " << costToLiveTM << std::endl;
		memoryfile_out << "total average: " << newAvgCostToLive << std::endl;
		memoryfile_out.close();
	}
	else std::cout << "Unable to open file";

	printScreen();

	return 0;
}