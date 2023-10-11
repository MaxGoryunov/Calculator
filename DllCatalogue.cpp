#include <filesystem>
#include <iostream>
#include "DllCatalogue.h"

using std::cout;
using std::endl;
using std::filesystem::path;
using std::filesystem::directory_iterator;

void DllCatalogue::loadFuncsFromDll(Funcs& funcs) {
	vector<path> paths;
	for (auto const& file : directory_iterator(this->folder)) {
		path filepath = file.path();
		if (filepath.extension() == ".dll") {
			HINSTANCE library = LoadLibraryW(filepath.c_str());
			if (library) {
				this->libraries.push_back(library);
				//add func to funcs
			}
			else {
				cout << "Could not open .dll file " << filepath.c_str() << endl;
			}
		}
	}

}