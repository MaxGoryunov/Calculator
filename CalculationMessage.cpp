#include <stdexcept>
#include "CalculationMessage.h"

using std::string;
using std::cout;
using std::endl;
using std::to_string;
using std::runtime_error;

void CalculationMessage::setLabel(string label, int ind) {
    this->labels[ind] = label;
}

void CalculationMessage::setValue(double value, int ind) {
    this->values[ind] = value;
}

void CalculationMessage::printStep(string& current, Funcs& funcs, int& iteration, int& last) {
    //cout << "current " << current << endl;
    int arity = funcs.arity(current);
    string label = "[" + to_string(iteration++) + "]";
    cout << label << " = ";
    if (last < arity) {
        throw runtime_error("Not enough arguments");
        return;
    }
    --last;
    double prev = this->values[last];
    double value;
    if (arity == 1) {
        if (funcs.associativity(current) == LEFT) {
            cout << (current + " " + this->labels[last]);
        }
        else {
            cout << (this->labels[last] + " " + current);
        }
        value = funcs.call(current, prev, 0);
        cout << " = " << value << endl;
    }
    else {
        --last;
        value = funcs.call(current, this->values[last], prev);
        cout << this->labels[last] << " " << current << " " <<
            this->labels[last + 1] << " = " << value << endl;
    }
    this->labels[last] = label;
    this->values[last] = value;
    ++last;
}

void CalculationMessage::printPairAt(int ind) {
    cout << "Finally: " << this->labels[ind] << " = " << this->values[ind] << endl;
}