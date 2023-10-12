#pragma once

#include <string>
#include <vector>
#include "Funcs.h"

class CalculationMessage {
private:
	std::string current;
	std::vector<std::string>& labels;
	std::vector<double> values;
public:
	CalculationMessage(std::vector<std::string>& labels, std::vector<double> values) :
		current(current), labels(labels), values(values) {}

	void setLabel(std::string label, int ind);

	void setValue(double value, int ind);

	void printStep(std::string& current, Funcs& funcs, int& iteration, int& last);

	void printPairAt(int ind);

	CalculationMessage(CalculationMessage const& other) = default;
	CalculationMessage(CalculationMessage&& other) = default;
	CalculationMessage& operator =(CalculationMessage const& other) = default;
	CalculationMessage& operator =(CalculationMessage&& other) = default;
	~CalculationMessage() = default;
};