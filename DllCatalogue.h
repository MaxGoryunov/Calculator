#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "Funcs.h"

using std::string;
using std::vector;

class DllCatalogue {
private:
	string folder;
	vector<HINSTANCE> libraries;
public:
	DllCatalogue(string folder) : folder(folder), libraries({}) {}

	void loadFuncsFromDll(Funcs& funcs);

	~DllCatalogue();

	DllCatalogue() = default;
	DllCatalogue(DllCatalogue const& other) = default;
	DllCatalogue(DllCatalogue&& other) = default;
	DllCatalogue& operator = (DllCatalogue const& other) = default;
	DllCatalogue& operator = (DllCatalogue&& other) = default;
};