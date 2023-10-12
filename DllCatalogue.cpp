#include <filesystem>
#include <iostream>
#include "DllCatalogue.h"

using std::cout;
using std::endl;
using std::filesystem::path;
using std::filesystem::directory_iterator;
using std::vector;

void DllCatalogue::loadFuncsFromDll(Funcs& funcs) {
	vector<path> paths;
	for (auto const& file : directory_iterator(this->folder)) {
		path filepath = file.path();
		if (filepath.extension() == ".dll") {
			HINSTANCE library = LoadLibraryW(filepath.c_str());
			cout << "Loaded " << filepath.c_str() << endl;
			if (library) {
				this->libraries.push_back(library);
				Func func = Func::fromLibrary(library);
				funcs.addFunc(func.Name(), func);
			}
			else {
				std::cerr << "Could not open .dll file " << filepath.c_str() << endl;
			}
		}
	}

}

DllCatalogue::~DllCatalogue() {
	for (auto const& library : this->libraries) {
		FreeLibrary(library);
	}
}