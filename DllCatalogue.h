#pragma once

#include <string>
#include <vector>
#include <Windows.h>
#include "Funcs.h"

class DllCatalogue {
private:
	std::string folder;
	std::vector<HINSTANCE> libraries;
public:
	DllCatalogue(std::string folder) : folder(folder), libraries({}) {}

	void loadFuncsFromDll(Funcs& funcs);

	~DllCatalogue();

	DllCatalogue() = default;
	DllCatalogue(DllCatalogue const& other) = default;
	DllCatalogue(DllCatalogue&& other) = default;
	DllCatalogue& operator = (DllCatalogue const& other) = default;
	DllCatalogue& operator = (DllCatalogue&& other) = default;
};