#include "Func.h"

template<typename T>
using fun = std::function<T>;

Func Func::fromLibrary(HINSTANCE const& library) {
	return Func(
		((string(*)(void))GetProcAddress(library, "name"))(),
		((Precedence(*)(void))GetProcAddress(library, "precedence"))(),
		((Associativity(*)(void))GetProcAddress(library, "associativity"))(),
		((int(*)(void))GetProcAddress(library, "arity"))(),
		fun<double(double,double)>((double(*)(double, double))GetProcAddress(library, "apply"))
	);
}