/* 
	Eamon Wolfgram

	This program will calculate the z-score from a list of inputs
	formatted like the included dataset.cpp file. Also calculates
	the minimum/maximum inputs of the included file. 

*/


#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

struct data_row {
	char employee;
	int salary;
};

//Calculate the minimum input
int min(std::vector<data_row> input) {
	int min = 99999999;
	for(int i = 0; i < input.size(); i++) {
		if (input[i].salary < min)
			min = input[i].salary;
	}

	return min;
}

//Calculate the maximum
int max(std::vector<data_row> input) {
	int max = 0;
	for(int i = 0; i < input.size(); i++) {
		if (input[i].salary > max)
			max = input[i].salary;
	}

	return max;
}

/*
A function that admittedly does not use the most efficient algorithm to locate the
position of a value on the array.
*/
int find_i(std::vector<data_row> input, char emp) {
	for(int i = 0; i < input.size(); i++) {
		if (input[i].employee == emp)
			return i;
	}
}

//Retunrs the min/max value for the provided data set input.
double min_max(std::vector<data_row> input, char emp) {
	double ret_val;
	ret_val = input[find_i(input,emp)].salary - min(input);
	ret_val = ret_val/(max(input) - min(input));

	return ret_val;
}
//Calculates the mean from the data set.
double mean(std::vector<data_row> input) {
	int salary = 0;
	for(int i = 0; i < input.size();i++) {
		salary += input[i].salary;
	}
	salary = salary/input.size();

	return salary;
}

//Calculates variance from the inputted data set.
double variance(std::vector<data_row> input) {
	std::vector<double> subs;

	double mn = mean(input);
	double sum = 0;
	double square;

	for(int i = 0; i < input.size(); i++) {
		square = input[i].salary - mn;
		subs.push_back(square*square);
	}
	
	for(int i = 0; i < subs.size(); i++)
		sum += subs[i];
	
	sum = sum/(subs.size()-1);

	return sum;
}

//Calculates deviation from the inputted data set.
double deviation(std::vector<data_row> input) {
	double varia = variance(input);
	double root = sqrt(varia);

	return root;
}

//Calculates Z-score for the inputted data set point.
double zscore(std::vector<data_row> input, char emp) {
	double score = input[find_i(input,emp)].salary - mean(input);
	score = score/deviation(input);

	return score;
}

int main() {
	std::ifstream input;
	input.open("dataset.txt");
	std::vector<data_row> employee_vector;

	char emp;
	int sal;
	data_row new_row;
	while(input >> emp >> sal) {
		new_row.employee = emp;
		new_row.salary = sal;
		employee_vector.push_back(new_row);
	}

	//Various sample lines to display output 
	std::cout << "min-max for A: " << min_max(employee_vector,'A') << "\n";
	std::cout << "min-max for C: " << min_max(employee_vector,'C') << "\n";
	std::cout << "min-max for E: " << min_max(employee_vector,'E') << "\n";

	std::cout << "Z-score for A: " << zscore(employee_vector,'A') << "\n";
	std::cout << "Z-score for C: " << zscore(employee_vector,'C') << "\n";
	std::cout << "Z-score for E: " << zscore(employee_vector,'E') << "\n";

	return 0;	
}